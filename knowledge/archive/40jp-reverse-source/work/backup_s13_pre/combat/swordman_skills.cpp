// ============================================================
// 【40JP逆向源代码工程】src/combat/swordman_skills.cpp
// 模块: 0x5F0000-0x600000
// 来源: work/dump 素材  区块: 0x5F0020-0x5FFE71 §A 技能 PO 基础与波系
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: 129
// ============================================================


#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============================================================
// §A 技能 PO 基础与波系
// ============================================================
// 0x5F0020 CNSwordman__vmt518
// ------------------------------------------------------------
// 调: sub_53FE50 sub_4C2820 sub_5F9DD0 sub_5EE770 sub_650950
void /*thiscall*/ sub_5F0020(int *this, void *pArg2, void *Block)  // 【CNSwordman__vmt518】
{
  void *pMem; // eax
  int pObj2; // eax
  int fld_e2137; // ecx
  int pObj5; // eax
  int fld_e2138; // ecx
  int fld_e21382; // ecx
  int pObj3; // eax
  uint32_t *v11; // edi
  int v12; // eax
  int v13; // eax
  int fld_e2139; // ecx
  int v15; // ebx
  int pObj4; // eax
  int pObj; // ecx
  float v18; // [esp+4h] [ebp-1Ch]
  void *Blocka; // [esp+2Ch] [ebp+Ch]

  sub_4B3E70(this, pArg2, (int)Block);  // Buff 图标/状态附加物增删
  if ( pArg2 == (void *)12 || pArg2 == (void *)13 || pArg2 == (void *)14 || pArg2 == (void *)15 || pArg2 == (void *)4 )
  {
    v15 = 0;
    if ( pArg2 == (void *)13 )
    {
      v15 = 1;
    }
    else if ( pArg2 == (void *)14 )
    {
      v15 = 2;
    }
    else if ( pArg2 == (void *)15 )
    {
      v15 = 3;
    }
    else if ( pArg2 == (void *)4 )
    {
      v15 = 4;
    }
    if ( (int)Block <= 0 )
    {
      pObj = *(this + v15 + 2132);
      if ( pObj == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 80))(pObj) == 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        return;
      fld_e21382 = *(this + v15 + 2132);
      goto LABEL_61;
    }
    if ( *(this + v15 + 2132) == 0 )
    {
      if ( operator new(0x88u) != nullptr )  // 堆分配 136 字节对象
        pObj4 = sub_4C2820(0, pArg2);  // 调 于 this+8556/8560 并经·sub_5F9DD0 起效
      else
        pObj4 = 0;
      *(this + v15 + 2132) = pObj4;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 64))(pObj4) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
    }
    sub_5F9DD0(Block);
    (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + v15 + 2132) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
      *(this + v15 + 2132),
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  else
  {
    if ( pArg2 == (void *)19 )
    {
      if ( (int)Block <= 0 )
      {
        fld_e2137 = *(this + 2137);  // this+8548〔nPhaseEndB〕
        if ( fld_e2137 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2137 + 80))(fld_e2137) != 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
          sub_53FE50(*(this + 2137));  // this+8548〔nPhaseEndB〕
      }
      else
      {
        if ( *(this + 2137) == 0 )  // this+8548〔nPhaseEndB〕
        {
          pMem = operator new(0x64u);  // 堆分配 100 字节对象
          if ( pMem != nullptr )  // 若 pMem 有效（非空）
            pObj2 = sub_5EE770(pMem);
          else
            pObj2 = 0;
          *(this + 2137) = pObj2;  // this+8548〔nPhaseEndB〕
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
        }
        sub_650950((uint32_t *)*(this + 2137), (int)Block);  // 参数装配（19 号表 → 11 号参数表）
        (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2137) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
          *(this + 2137),  // this+8548〔nPhaseEndB〕
          this,
          this,
          0,
          0,
          0,
          -1);
      }
      return;
    }
    if ( pArg2 == (void *)43 )
    {
      if ( (int)Block > 0 )
      {
        if ( *(this + 2138) == 0 )
        {
          if ( operator new(0x7Cu) != nullptr )  // 堆分配 124 字节对象
            pObj5 = sub_4B3C90(0, 0);  // 结果 = CNChangeStatus 构造（双参）
          else
            pObj5 = 0;
          *(this + 2138) = pObj5;
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 64))(pObj5) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
        }
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 43);  // 虚调用 vt+1160
        Blocka = (void *)sub_47EE70(2, 3, Block);
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2138) + 124))(*(this + 2138));  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        v18 = (float)(int)Blocka;
        (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)*(this + 2138) + 120))(6, 0, LODWORD(v18));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2138) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
          *(this + 2138),
          this,
          this,
          0,
          0,
          0,
          -1);
        return;
      }
      fld_e2138 = *(this + 2138);
      if ( fld_e2138 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2138 + 80))(fld_e2138) == 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        return;
      fld_e21382 = *(this + 2138);
LABEL_61:
      sub_53FE50(fld_e21382);
      return;
    }
    if ( pArg2 == (void *)29 )
    {
      if ( (int)Block <= 0 )
      {
        fld_e2139 = *(this + 2139);
        if ( fld_e2139 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2139 + 80))(fld_e2139) == 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
          return;
        fld_e21382 = *(this + 2139);
        goto LABEL_61;
      }
      if ( *(this + 2139) == 0 )
      {
        if ( operator new(0x84u) != nullptr )  // 堆分配 132 字节对象
          pObj3 = sub_5E5B20(0, 0, nullptr);
        else
          pObj3 = 0;
        *(this + 2139) = pObj3;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 64))(pObj3) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
        v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 29);  // 结果 = 虚调用 vt+1160
        v12 = sub_47E9D0(v11, 0);  // 调 收招/结束例程
        sub_5E5ED0(2, 0, v12);
        v13 = sub_47E9D0(v11, 1u);  // 调 收招/结束例程
        sub_5E5ED0(3, 0, v13);
      }
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2139) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
        *(this + 2139),
        this,
        this,
        0,
        0,
        0,
        -1);
    }
    else if ( pArg2 == (void *)39 )
    {
      if ( (int)Block <= 0 )
      {
        *(this + 2131) = 0;  // this+8524〔bMonCfgFlag〕
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 39);  // 虚调用 vt+1160
        *(this + 2131) = sub_47EF20(0, Block, -1, -1, 11);  // 调 读攻击数据表
      }
    }
  }
}


// ------------------------------------------------------------
// 0x5F0460 sub_5F0460
// ------------------------------------------------------------
// 调: sub_5F0460 sub_431230
void /*usercall*/ sub_5F0460(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：调: sub_5F0460 sub_431230
{
  int pObj4; // ecx
  int v4; // eax
  int pObj3; // ecx
  int v6; // eax
  int pObj; // ecx
  int v8; // edi
  char v9; // al
  int v10; // edx
  bool v11; // zf
  int v12; // eax
  int pObj2; // ecx
  uint8_t v14[4]; // [esp+8h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-24h]
  int v16; // [esp+10h] [ebp-20h]
  int v17; // [esp+14h] [ebp-1Ch]
  int v18; // [esp+18h] [ebp-18h] BYREF
  int v19; // [esp+1Ch] [ebp-14h] BYREF
  int v20; // [esp+20h] [ebp-10h] BYREF
  int v21; // [esp+2Ch] [ebp-4h]

  pObj4 = pArg1[2114];
  if ( pObj4 != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 308))(pObj4) != 0 )  // 虚函数调用 槽+308
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pArg1[2114] + 120))(pArg1[2114], nArg2);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      pObj3 = pArg1[2114];
      v19 = v4;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      pObj = pArg1[2114];
      v20 = v6;
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)pArg1[2114] + 136))(  // 虚函数调用 槽+136：槽（10 行）
             pArg1[2114],
             v19,
             v20,
             0) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pArg1[2114] + 132))(pArg1[2114], v8) != 0 )  // 虚函数调用 槽+132：受击事件槽（钉刺王变体，23 行）
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)pArg1[2114] + 108))(pArg1[2114], v19, v20, v8);  // 虚函数调用 槽+108：槽（10 行）
      }
      else
      {
        v9 = (*(int (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)pArg1[2114] + 140))(  // 虚函数调用 槽+140：槽（17 行）
               pArg1[2114],
               &v19,
               &v20,
               v19,
               v20,
               100,
               1,
               1);
        v10 = *(uint32_t *)pArg1[2114];
        if ( v9 != 0 )
        {
          (*(void (/*stdcall*/ **)(int, int))(v10 + 108))(v19, v20);  // 虚函数调用 槽+108：槽（10 行）
        }
        else
        {
          v11 = (*(uint8_t (/*cdecl*/ **)(int))(v10 + 132))(v8) == 0;  // 虚函数调用 槽+132：受击事件槽（钉刺王变体，23 行）
          v12 = *(uint32_t *)pArg1[2114];
          if ( v11 )
            (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t))(v12 + 108))(pArg1[2115], pArg1[2116], pArg1[2117]);  // 虚函数调用 槽+108：槽（10 行）
          else
            (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int))(v12 + 108))(pArg1[2115], pArg1[2116], v8);  // 虚函数调用 槽+108：槽（10 行）
        }
      }
      Block = nullptr;
      v16 = 0;
      v17 = 0;
      v21 = 0;
      v18 = 4;
      sub_431230((int)v14, &v18);  // uint32 vector push_back
      v18 = 0;
      sub_431230((int)v14, &v18);  // uint32 vector push_back
      v18 = 1;
      sub_431230((int)v14, &v18);  // uint32 vector push_back
      v18 = 1000;
      sub_431230((int)v14, &v18);  // uint32 vector push_back
      v18 = 100;
      sub_431230((int)v14, &v18);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int))(*(uint32_t *)pArg1[2114] + 560))(pArg1[2114], 4, v14, 2);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2114] + 564))(pArg1[2114]);  // 虚函数调用 槽+564：位移同步包 vt+234（会话 3 定案：UDP type=5）
      v21 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
      Block = nullptr;
      v16 = 0;
      v17 = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pArg1[2114] + 596))(pArg1[2114], 1);  // 虚函数调用 槽+596：[RTTI: IRDCollisionObject__vmt254…
    pObj2 = pArg1[2120];
    pArg1[2114] = 0;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);  // 虚函数调用 槽+76：槽（542940 + 485020）
  }
}



// ------------------------------------------------------------
// 0x5F0660 sub_5F0660
// ------------------------------------------------------------
// 调: sub_5F0660 sub_5910D0 sub_650F20 sub_6519E0
uint32_t */*thiscall*/ sub_5F0660(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：调: sub_5F0660 sub_5910D0 sub_650F20 sub_6519E0
{
  sub_5910D0(0, 18, 250, 0);  // CNRDAuraMaster 构造函数
  *this = &vftbl_CNDOTArea;  // 构造装配 vftable：CNDOTArea
  *(this + 43) = 0;  // this+172〔pAppendVecEnd(推断)〕
  *(this + 44) = 0;  // this+44 剩余时间 ms
  *(this + 45) = 0;  // this+180〔nRadius(推断)〕
  sub_650F20(this);  // 计时/缩放块复位（+128..+164）
  sub_6519E0(nArg2, nArg3, nArg4, nArg5, nArg6);
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x5F06F0 CNDOTArea__vmt0
// ------------------------------------------------------------
// 调: sub_5F0720
void */*thiscall*/ CNDOTArea__vmt0(void *Block, char pszArg2)  // 实现：调: sub_5F0720
{
  sub_5F0720();
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x5F0720 sub_5F0720
// ------------------------------------------------------------
// 调: sub_5F0720 sub_650F70 sub_591190
int /*thiscall*/ sub_5F0720(void **this)  // 实现：调: sub_5F0720 sub_650F70 sub_591190
{
  *this = &vftbl_CNDOTArea;  // 构造装配 vftable：CNDOTArea
  sub_650F70();  // 批量释放 +156 起 3 个挂接件
  if ( *(this + 43) != nullptr )  // this+172〔pAppendVecEnd(推断)〕
    j__free(*(this + 43));  // 调 堆释放
  *(this + 43) = nullptr;  // this+172〔pAppendVecEnd(推断)〕
  *(this + 44) = nullptr;  // this+44 剩余时间 ms
  *(this + 45) = nullptr;  // this+180〔nRadius(推断)〕
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// ------------------------------------------------------------
// 0x5F07A0 CNSwordman__vmt514
// ------------------------------------------------------------
// 证: "Common/CommonEffect/BuffIcon.img"
// 调: sub_41A5E0 sub_47EF20 sub_510350 sub_418DD0
int /*thiscall*/ sub_5F07A0(int this, char *pszArg2, void *pArg3)  // 【CNSwordman__vmt514】
{
  int result; // eax
  int fld_74; // eax  | +0x0074 → 特效容器对象（CNSwordman；va=005F07A0）
  int v7; // ecx
  unsigned int v8; // ebx
  int fld_742; // ecx  | +0x0074 → 特效容器对象（CNSwordman；va=005F07A0）
  int v10; // edx
  int v11; // eax
  int pObj2; // edi
  int v13; // ebx
  int *v14; // eax
  int v15; // ebx
  uint32_t *v16; // eax
  int pThis_184; // eax
  void *pMem; // eax
  int pObj5; // eax
  int fld_20EC; // ebx  | +0x20EC → Buff 表现对象·过载（CNSwordman；va=005F07A0）
  uint32_t *v21; // eax
  int v22; // eax
  float v23; // edx
  void *pMem2; // eax
  int pObj4; // eax
  int fld_20F0; // edi  | +0x20F0 → Buff 表现对象·气血（CNSwordman；va=005F07A0）
  uint32_t *v27; // eax
  uint8_t *pMem3; // eax
  uint8_t *pObj3; // eax
  int fld_20F4; // edi  | +0x20F4 → Buff 表现对象·鬼步（CNSwordman；va=005F07A0）
  int v31; // ebx
  int fld_20F42; // edi  | +0x20F4 → Buff 表现对象·鬼步（CNSwordman；va=005F07A0）
  uint32_t *v33; // eax
  int v34; // eax
  int pObj; // eax
  int pThis_1842; // eax
  int v37; // eax
  int fld_20FC; // ebx  | +0x20FC → Buff 表现对象·夺取（CNSwordman；va=005F07A0）
  int v39; // eax
  float v40; // [esp+0h] [ebp-34h]
  int pThis_474; // [esp+4h] [ebp-30h]
  float v42; // [esp+8h] [ebp-2Ch]
  float v43; // [esp+Ch] [ebp-28h]
  int v44; // [esp+Ch] [ebp-28h]
  unsigned int v45; // [esp+10h] [ebp-24h]
  int v46; // [esp+10h] [ebp-24h]
  int v47; // [esp+14h] [ebp-20h]
  int v48; // [esp+1Ch] [ebp-18h]
  int v49; // [esp+1Ch] [ebp-18h]
  void *v50; // [esp+20h] [ebp-14h]
  int *Block; // [esp+24h] [ebp-10h]
  void *v52; // [esp+3Ch] [ebp+8h]
  void *v53; // [esp+3Ch] [ebp+8h]
  float v54; // [esp+3Ch] [ebp+8h]
  void *v55; // [esp+40h] [ebp+Ch]

  sub_4B4170((float *)this, pszArg2, pArg3);  // 调 Buff 图标条装配
  result = sub_41A5E0((unsigned int)(pszArg2 + 4));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  switch ( result )  // 按 result 分派
  {
    case 30:  // case 30 = ENUM_CMDPACKET_USE_LOTTERY_ITEM
      v50 = (void *)sub_47EF20(0, pArg3, -1, -1, 11);  // 调 读攻击数据表
      v48 = sub_47EF20(1, pArg3, -1, -1, 11);  // 调 读攻击数据表
      fld_74 = *(uint32_t *)(this + 116);  // 读 fld_74 = this+116（特效容器对象）
      v7 = *(uint32_t *)(fld_74 + 120);
      result = fld_74 + 116;
      v8 = 0;
      if ( v7 != 0 )
      {
        result = (*(uint32_t *)(result + 8) - v7) >> 2;  // 向量元素数 = (end−begin)/4
        v52 = (void *)result;
      }
      else
      {
        v52 = nullptr;
      }
      v55 = nullptr;
      if ( (int)v52 > 0 )
      {
        do
        {
          fld_742 = *(uint32_t *)(this + 116);  // 读 fld_742 = this+116（特效容器对象）
          v10 = *(uint32_t *)(fld_742 + 120);
          if ( v10 != 0 && v8 < (*(uint32_t *)(fld_742 + 124) - v10) >> 2 )  // 向量元素数 = (end−begin)/4
            v11 = *(uint32_t *)(v10 + 4 * v8);
          else
            v11 = 0;
          pObj2 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                  v11,
                  0,
                  &IRDCollisionObject `RTTI Type Descriptor',
                  &IRDActiveObject `RTTI Type Descriptor',
                  0);
          if ( pObj2 != 0 )
          {
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);  // 虚函数调用 槽+376：坐标同步包（type 37）
            if ( v13 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 376))(this) )  // this+376 绑定参考值 B
            {
              if ( operator new(0x84u) != nullptr )  // 堆分配 132 字节对象
                v14 = (int *)sub_510350(2, 0, v48, v50, 1, nullptr);  // 调 存 CNChangeElementTolerance 元素抗性变更…
              else
                v14 = nullptr;
              v15 = *v14;
              Block = v14;
              v16 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, int, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
                                dword_8F84B8,  // 全局 攻击判定管理器
                                "Common/CommonEffect/BuffIcon.img",  // 字符串 “Common/CommonEffect/BuffIcon.img”
                                1,
                                6,
                                -1);
              v45 = sub_418DD0(v16, v45);  // 调 资源句柄 (101)
              (*(void (/*thiscall*/ **)(int *, int, int, int))(v15 + 56))(Block, pObj2, this, 1);  // 虚函数调用 槽+56：确认动作：+84 标志时 4
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
                pObj2,
                "BUFF_MOONCURTAIN",  // 字符串 “BUFF_MOONCURTAIN”
                -1,
                0,
                0);
            }
            v8 = (unsigned int)v55;
          }
          result = (int)v52;
          v55 = (void *)++v8;
        }
        while ( (int)v8 < (int)v52 );
      }
      break;
    case 38:  // case 38 = ENUM_CMDPACKET_SET_USER_POSITION
      v53 = (void *)sub_47EF20(0, pArg3, -1, -1, 11);  // 调 读攻击数据表
      pThis_184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // this+388 攻击上下文浮点值
      v49 = sub_47EFD0(pszArg2, COERCE_FLOAT(2), (int)pArg3, pThis_184, pThis_184, 0);
      if ( *(uint32_t *)(this + 8428) == 0 )  // 判定 “+8428 Buff 表现对象·过载”
      {
        pMem = operator new(0x7Cu);  // 堆分配 124 字节对象
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          pObj5 = sub_4B3C90((int)pMem, 0, 1);  // 结果 = CNChangeStatus 构造（双参）
        else
          pObj5 = 0;
        *(uint32_t *)(this + 8428) = pObj5;  // 写 this+8428 = pObj5（Buff 表现对象·过载）
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 64))(pObj5) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
      }
      *(uint32_t *)(*(uint32_t *)(this + 8428) + 44) = v53;  // this+8428 Buff 表现对象·过载
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8428) + 124))(*(uint32_t *)(this + 8428));  // this+8428 Buff 表现对象·过载
      v43 = (float)v49;
      (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(**(uint32_t **)(this + 8428) + 120))(4, 0, LODWORD(v43));  // this+8428 Buff 表现对象·过载
      fld_20EC = **(uint32_t **)(this + 8428);  // this+8428 Buff 表现对象·过载
      v21 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
                        dword_8F84B8,  // 全局 攻击判定管理器
                        "Common/CommonEffect/BuffIcon.img",  // 字符串 “Common/CommonEffect/BuffIcon.img”
                        7,
                        0,
                        -1);
      sub_418DD0(v21, v45);  // 调 资源句柄 (101)
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(fld_20EC + 56))(*(uint32_t *)(this + 8428), this, this, 1);  // this+8428 Buff 表现对象·过载
      v22 = sub_47EF20(1, pArg3, -1, -1, 11);  // 调 读攻击数据表
      v23 = *(float *)this;
      *(uint32_t *)(this + 8520) = v22;  // 写 this+8520 = v22（Buff 上下文槽）
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(LODWORD(v23) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
               this,
               "BUFF_OVERDRIVE",  // 字符串 “BUFF_OVERDRIVE”
               -1,
               0,
               0);
    case 40:  // case 40 = ENUM_CMDPACKET_FISHING
      if ( *(uint32_t *)(this + 8432) == 0 )  // 判定 “+8432 Buff 表现对象·气血”
      {
        pMem2 = operator new(0x70u);  // 堆分配 112 字节对象
        if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
          pObj4 = sub_5EE850(pMem2);
        else
          pObj4 = 0;
        *(uint32_t *)(this + 8432) = pObj4;  // 写 this+8432 = pObj4（Buff 表现对象·气血）
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 64))(pObj4) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
      }
      (*(void (/*thiscall*/ **)(uint32_t, void *))(**(uint32_t **)(this + 8432) + 120))(*(uint32_t *)(this + 8432), pArg3);  // this+8432 Buff 表现对象·气血
      fld_20F0 = **(uint32_t **)(this + 8432);  // this+8432 Buff 表现对象·气血
      v27 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
                        dword_8F84B8,  // 全局 攻击判定管理器
                        "Common/CommonEffect/BuffIcon.img",  // 字符串 “Common/CommonEffect/BuffIcon.img”
                        12,
                        0,
                        -1);
      v46 = sub_418DD0(v27, v45);  // 调 资源句柄 (101)
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(fld_20F0 + 56))(*(uint32_t *)(this + 8432), this, this, 1);  // this+8432 Buff 表现对象·气血
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)this + 1160))(this, 40, this, -1);  // 虚函数调用 槽+1160
      sub_47DCD0(v46, v47);  // 调 震动/资源档位设置
      return (*(int (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)this + 212))(this, "BUFF_CONGESTION", -1);  // 字符串 “BUFF_CONGESTION”
    case 18:  // case 18 = ENUM_CMDPACKET_SEND_MESSAGE
      if ( *(uint32_t *)(this + 8436) == 0 )  // 判定 “+8436 Buff 表现对象·鬼步”
      {
        pMem3 = operator new(0x50u);  // 堆分配 80 字节对象
        if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
          pObj3 = sub_4B1030(pMem3);  // 结果 = IRDAppendage 基类构造
        else
          pObj3 = nullptr;
        *(uint32_t *)(this + 8436) = pObj3;  // 写 this+8436 = pObj3（Buff 表现对象·鬼步）
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj3 + 64))(pObj3) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
      }
      fld_20F4 = *(uint32_t *)(this + 8436);  // 读 fld_20F4 = this+8436（Buff 表现对象·鬼步）
      pThis_474 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1140))(this, 18, -1);  // 虚函数调用 槽+1140
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1160))(this);  // 虚函数调用 槽+1160
      v31 = sub_47EF20(18, 0, pThis_474, -1, 11);  // 调 读攻击数据表
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_20F4 + 64))(fld_20F4) + 40) = v31;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
      fld_20F42 = **(uint32_t **)(this + 8436);  // this+8436 Buff 表现对象·鬼步
      v33 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
                        dword_8F84B8,  // 全局 攻击判定管理器
                        "Common/CommonEffect/BuffIcon.img",  // 字符串 “Common/CommonEffect/BuffIcon.img”
                        20,
                        0,
                        -1);
      sub_418DD0(v33, v45);  // 调 资源句柄 (101)
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(fld_20F42 + 56))(*(uint32_t *)(this + 8436), this, this, 1);  // this+8436 Buff 表现对象·鬼步
      *(uint8_t *)(this + 8440) = 1;  // 写 this+8440 = 1（鬼步/隐身标志字节）
      sub_49C620((int *)this, 1, 1, 0);  // 命令下发包装（组 id = this+4，值重复两遍）
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // this+212 【推断】子链状态槽
               this,
               "G_GHOSTSTEP_DISAPPEAR",  // 字符串 “G_GHOSTSTEP_DISAPPEAR”
               -1,
               0,
               0);
    case 52:  // case 52 = ENUM_CMDPACKET_DECREASE_DURABILITY
      if ( *(uint32_t *)(this + 8444) == 0 )  // 判定 “+8444 Buff 表现对象·夺取”
      {
        if ( operator new(0xBCu) != nullptr )  // 堆分配 188 字节对象
        {
          v34 = sub_47E9D0(pszArg2, 0);  // 调 收招/结束例程
          pObj = sub_5F0660(0, 0, 0, 0, v34);
        }
        else
        {
          pObj = 0;
        }
        *(uint32_t *)(this + 8444) = pObj;  // 写 this+8444 = pObj（Buff 表现对象·夺取）
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
      }
      pThis_1842 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // this+388 攻击上下文浮点值
      v37 = sub_47EFD0(pszArg2, COERCE_FLOAT(1), (int)pArg3, pThis_1842, pThis_1842, 0);
      fld_20FC = **(uint32_t **)(this + 8444);  // this+8444 Buff 表现对象·夺取
      v54 = (double)v37 * 0.1;
      v44 = sub_47E9D0(pszArg2, 0);  // 调 收招/结束例程
      v42 = (double)sub_47E9D0(pszArg2, 1u) * v54 * 0.0099999998;  // 调 收招/结束例程
      v40 = (double)(int)sub_47EF20(0, pArg3, -1, -1, 11) * 0.1;  // 调 读攻击数据表
      v39 = sub_47EF20(2, pArg3, -1, -1, 11);  // 调 读攻击数据表
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t, int))(fld_20FC + 148))(  // 虚函数调用 槽+148：槽（12 行）
        *(uint32_t *)(this + 8444),  // this+8444 Buff 表现对象·夺取
        v39 / 2,
        LODWORD(v40),  // 调 取 64 位值低 32 位
        LODWORD(v54),  // 调 取 64 位值低 32 位
        LODWORD(v42),  // 调 取 64 位值低 32 位
        v44);
      return (*(int (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8444) + 56))(  // this+8444 Buff 表现对象·夺取
               *(uint32_t *)(this + 8444),  // this+8444 Buff 表现对象·夺取
               this,
               this,
               1,
               0,
               0,
               -1);
    default:
      break;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5F0D40 sub_5F0D40
// ------------------------------------------------------------
// 调: sub_5F0D40 sub_42AF90 sub_657740
int /*thiscall*/ sub_5F0D40(int this)  // 实现：调: sub_5F0D40 sub_42AF90 sub_657740
{
  void (/*thiscall*/ ***pThis_2044)(uint32_t, int); // ecx
  void ***pThis_2068; // edi
  int v4; // ebx
  void **v5; // ebx
  bool v6; // zf
  int fld_2090; // edi
  void **fld_20B0; // edi
  void **fld_20B4; // edi
  void **fld_20B8; // edi
  void ***pThis_20C4; // edi
  int v12; // ebx
  void **v13; // ebx
  void ***pThis_20D4; // edi
  void **v15; // ebx
  int fld_20E0; // edi
  void (/*thiscall*/ ***pThis_20EC)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_20F0)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_20F4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_20FC)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_2120)(uint32_t, int); // ecx
  void **fld_2124; // edi
  void **fld_2134; // edi
  void ***pThis_2138; // edi
  void **v25; // ebx
  uint32_t *pThis_2150; // edi
  int n; // ebx
  void (/*thiscall*/ ***pThis_2164)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_2168)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_216C)(uint32_t, int); // ecx
  int result; // eax
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]
  int k; // [esp+4h] [ebp-4h]
  int m; // [esp+4h] [ebp-4h]

  pThis_2044 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8260);  // this+8260 相位值 A
  if ( pThis_2044 != nullptr )  // 若 pThis_2044 有效（非空）
    (**pThis_2044)(pThis_2044, 1);  // 调 pThis_2044 的虚函数（vt+0）
  *(uint32_t *)(this + 8260) = 0;  // this+8260 相位值 A
  pThis_2068 = (void ***)(this + 8296);  // this+8296 【推断】0x5EA970 写 -250
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
  {
    v4 = (int)*(pThis_2068 - 2);
    if ( v4 != 0 )
    {
      sub_42AF90(*(pThis_2068 - 2));  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v4, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    v5 = *pThis_2068;
    v6 = *pThis_2068 == nullptr;
    *(pThis_2068 - 2) = nullptr;
    if ( !v6 )
    {
      sub_42AF90(v5);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v5, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_2068++ = nullptr;
  }
  fld_2090 = *(uint32_t *)(this + 8336);  // this+8336 0x5EA970: pThis_2090=
  if ( fld_2090 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8336));  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_2090, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_20B0 = *(void ***)(this + 8368);  // this+8368 同三元组第 2 项
  *(uint32_t *)(this + 8336) = 0;  // this+8336 0x5EA970: pThis_2090=
  if ( fld_20B0 != nullptr )  // 若 fld_20B0 有效（非空）
  {
    sub_42AF90(fld_20B0);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_20B0, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_20B4 = *(void ***)(this + 8372);  // this+8372 0x5EA970: *
  *(uint32_t *)(this + 8368) = 0;  // this+8368 同三元组第 2 项
  if ( fld_20B4 != nullptr )  // 若 fld_20B4 有效（非空）
  {
    sub_42AF90(fld_20B4);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_20B4, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_20B8 = *(void ***)(this + 8376);  // this+8376 【推断】特效/技能对象B
  *(uint32_t *)(this + 8372) = 0;  // this+8372 0x5EA970: *
  if ( fld_20B8 != nullptr )  // 若 fld_20B8 有效（非空）
  {
    sub_42AF90(fld_20B8);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_20B8, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 8376) = 0;  // this+8376 【推断】特效/技能对象B
  pThis_20C4 = (void ***)(this + 8388);  // this+8388 【推断】动画对象 D
  for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
  {
    v12 = (int)*(pThis_20C4 - 2);
    if ( v12 != 0 )
    {
      sub_42AF90(*(pThis_20C4 - 2));  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v12, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    v13 = *pThis_20C4;
    v6 = *pThis_20C4 == nullptr;
    *(pThis_20C4 - 2) = nullptr;
    if ( !v6 )
    {
      sub_42AF90(v13);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v13, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_20C4++ = nullptr;
  }
  pThis_20D4 = (void ***)(this + 8404);  // this+8404 【推断】特效/技能对象D
  for ( k = 2; k != 0; --k )  // 循环：k 从 2 递减到 0
  {
    v15 = *pThis_20D4;
    if ( *pThis_20D4 != nullptr )
    {
      sub_42AF90(*pThis_20D4);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v15, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_20D4++ = nullptr;
  }
  fld_20E0 = *(uint32_t *)(this + 8416);
  if ( fld_20E0 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8416));  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_20E0, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_20EC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8428);  // this+8428 【推断】对象数组 cap
  *(uint32_t *)(this + 8416) = 0;
  if ( pThis_20EC != nullptr )  // 若 pThis_20EC 有效（非空）
    (**pThis_20EC)(pThis_20EC, 1);  // 调 pThis_20EC 的虚函数（vt+0）
  pThis_20F0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8432);  // this+8432 【推断】Buff 挂件A
  *(uint32_t *)(this + 8428) = 0;  // this+8428 【推断】对象数组 cap
  if ( pThis_20F0 != nullptr )  // 若 pThis_20F0 有效（非空）
    (**pThis_20F0)(pThis_20F0, 1);  // 调 pThis_20F0 的虚函数（vt+0）
  pThis_20F4 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8436);  // this+8436 【推断】Buff 挂件B
  *(uint32_t *)(this + 8432) = 0;  // this+8432 【推断】Buff 挂件A
  if ( pThis_20F4 != nullptr )  // 若 pThis_20F4 有效（非空）
    (**pThis_20F4)(pThis_20F4, 1);  // 调 pThis_20F4 的虚函数（vt+0）
  pThis_20FC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8444);  // this+8444 0x5EA970: nArg2!=21 && nArg2!=6 && *
  *(uint32_t *)(this + 8436) = 0;  // this+8436 【推断】Buff 挂件B
  if ( pThis_20FC != nullptr )  // 若 pThis_20FC 有效（非空）
    (**pThis_20FC)(pThis_20FC, 1);  // 调 pThis_20FC 的虚函数（vt+0）
  pThis_2120 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8480);  // this+8480 【推断】攻击挂接对象
  *(uint32_t *)(this + 8444) = 0;  // this+8444 0x5EA970: nArg2!=21 && nArg2!=6 && *
  if ( pThis_2120 != nullptr )  // 若 pThis_2120 有效（非空）
    (**pThis_2120)(pThis_2120, 1);  // 调 pThis_2120 的虚函数（vt+0）
  fld_2124 = *(void ***)(this + 8484);
  *(uint32_t *)(this + 8480) = 0;  // this+8480 【推断】攻击挂接对象
  if ( fld_2124 != nullptr )  // 若 fld_2124 有效（非空）
  {
    sub_42AF90(fld_2124);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_2124, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_2134 = *(void ***)(this + 8500);  // this+8500 【推断】充能计时
  *(uint32_t *)(this + 8484) = 0;
  if ( fld_2134 != nullptr )  // 若 fld_2134 有效（非空）
  {
    sub_42AF90(fld_2134);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_2134, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 8500) = 0;  // this+8500 【推断】充能计时
  pThis_2138 = (void ***)(this + 8504);  // this+8504 仅见写
  for ( m = 2; m != 0; --m )  // 循环：m 从 2 递减到 0
  {
    v25 = *pThis_2138;
    if ( *pThis_2138 != nullptr )
    {
      sub_42AF90(*pThis_2138);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v25, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_2138++ = nullptr;
  }
  pThis_2150 = (uint32_t *)(this + 8528);  // this+8528 std::string 文案串起点
  for ( n = 5; n != 0; --n )  // 循环：n 从 5 递减到 0
  {
    if ( *pThis_2150 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_2150)(*pThis_2150, 1);
    *pThis_2150++ = 0;
  }
  pThis_2164 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8548);  // this+8548 相位段 B 结束时刻
  if ( pThis_2164 != nullptr )  // 若 pThis_2164 有效（非空）
    (**pThis_2164)(pThis_2164, 1);  // 调 pThis_2164 的虚函数（vt+0）
  pThis_2168 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8552);
  *(uint32_t *)(this + 8548) = 0;  // this+8548 相位段 B 结束时刻
  if ( pThis_2168 != nullptr )  // 若 pThis_2168 有效（非空）
    (**pThis_2168)(pThis_2168, 1);  // 调 pThis_2168 的虚函数（vt+0）
  pThis_216C = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8556);
  result = 0;
  *(uint32_t *)(this + 8552) = 0;
  if ( pThis_216C != nullptr )  // 若 pThis_216C 有效（非空）
    result = (**pThis_216C)(pThis_216C, 1);  // 调 pThis_216C 的虚函数（vt+0）
  *(uint32_t *)(this + 8556) = 0;
  return result;
}


// ------------------------------------------------------------
// ============================================================
// §B 蓄力与血系
// ============================================================
// 0x5F6610 sub_5F6610
// ------------------------------------------------------------
// 调: sub_5F6610
int /*thiscall*/ sub_5F6610(int this)  // 实现：调: sub_5F6610
{
  *(uint32_t *)(this + 48) = 0;  // this+48 UDP 上报使能位
  *(uint8_t *)(this + 52) = 0;  // this+52 光环状态字节
  *(uint8_t *)(this + 53) = 0;  // this+212〔nField212(推断)〕
  *(uint8_t *)(this + 54) = 0;  // this+216〔bField216(推断)〕
  *(uint32_t *)(this + 56) = 0;  // this+56 键盘输入使能
  *(uint32_t *)(this + 60) = -1;  // this+60 fade 值
  *(uint32_t *)(this + 64) = 0;  // this+64 服务器页签按钮组 6 个
  *(uint32_t *)(this + 76) = -1;  // this+76 纹章路径串
  *(uint32_t *)(this + 72) = 0;  // this+72 【推断】快照槽
  return 0;
}



// ------------------------------------------------------------
// 0x5F6640 sub_5F6640
// ------------------------------------------------------------
// 调: sub_5F6640 sub_53FE50
int /*thiscall*/ sub_5F6640(uint32_t *this)  // 函数定义: 基类析构
{
  int result; // eax
  uint32_t *fld_e12; // ecx

  result = (int)this;
  fld_e12 = (uint32_t *)*(this + 12);  // this+12 物品类型号
  if ( fld_e12 != nullptr )  // 若 fld_e12 有效（非空）
    return sub_53FE50(fld_e12, result);
  return result;
}



// ------------------------------------------------------------
// 0x5F6650 IRDAppendage__vmt54
// ------------------------------------------------------------
// 调: sub_699030 sub_698FE0
char /*thiscall*/ IRDAppendage__vmt54(uint8_t *this, char pszArg2)  // 实现：调: sub_699030 sub_698FE0
{
  char result; // al
  uint8_t *pThis_8; // ecx

  result = pszArg2;
  if ( *(this + 53) != pszArg2 )  // this+212〔nField212(推断)〕
  {
    *(this + 53) = pszArg2;  // this+212〔nField212(推断)〕
    pThis_8 = this + 8;  // this+8 物品 id
    if ( pszArg2 != 0 )
      return sub_699030((int)pThis_8);  // 【clock_freeze(clk)】
    else
      return sub_698FE0((int)pThis_8);  // 【clock_unfreeze(clk)】
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F6680 IRDAppendage__vmt30
// ------------------------------------------------------------
// 证: 叶子函数（9 行，无外调无字符串）
int /*thiscall*/ IRDAppendage__vmt30(uint32_t *this, int nArg2)  // 实现：证: 叶子函数（9 行，无外调无字符串）
{
  int result; // eax

  result = *(this + 9);  // 读 result = this+36（状态字）
  if ( result == nArg2 )
    *(this + 9) = 0;  // 写 this+36 = 0（状态字）
  return result;
}



// ------------------------------------------------------------
// 0x5F66A0 sub_5F66A0
// ------------------------------------------------------------
// 调: sub_5F66A0 sub_699000
char /*thiscall*/ sub_5F66A0(int this, char pszArg2)  // 实现：调: sub_5F66A0 sub_699000
{
  int pThis_8; // eax

  LOBYTE(pThis_8) = pszArg2;  // 调 取 16 位值低 8 位
  *(uint8_t *)(this + 68) = pszArg2;  // this+68 角色数
  if ( pszArg2 != 0 )
  {
    pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
    *(uint32_t *)(this + 76) = pThis_8;  // this+76 纹章路径串
  }
  return pThis_8;
}



// ------------------------------------------------------------
// 0x5F66C0 IRDAppendage__vmt4
// ------------------------------------------------------------
// 调: sub_699000
char /*thiscall*/ IRDAppendage__vmt4(int *this)  // 实现：调: sub_699000
{
  int pThis_2; // eax
  int fld_e11; // edi
  int pThis_24; // ebx
  unsigned int pThis_22; // eax
  int pThis_23; // eax
  int v7; // edx

  pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
  fld_e11 = *(this + 11);  // this+44〔nExpireMs(推断)〕
  pThis_24 = pThis_2;
  if ( fld_e11 != 0 && pThis_2 >= fld_e11 )  // 若 fld_e11 != 0 与/或 pThis_2 >= fld_e11
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);  // 虚调用 vt+76
  if ( *((uint8_t *)this + 54) != 0 && *(this + 14) != 0 )  // this+56〔pCmdVecCap56(推断)〕
  {
    if ( fld_e11 != 0 && pThis_24 >= fld_e11 - 1200 )  // 若 fld_e11 != 0 与/或 pThis_24 >= fld_e11
    {
      if ( *(this + 15) == -1 )  // this+60〔nFadeValue60(推断)〕
        (*(void (/*thiscall*/ **)(int *))(*this + 112))(this);  // 虚调用 vt+112
    }
    else if ( pThis_24 >= 1000 )
    {
      *(this + 15) = -1;  // this+60〔nFadeValue60(推断)〕
    }
  }
  LOBYTE(pThis_22) = *((uint8_t *)this + 68);  // this+68 角色数
  if ( (uint8_t)pThis_22 != 0 )
  {
    pThis_22 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
    if ( *(this + 19) + *(this + 18) < pThis_22 )  // this+76〔pBtnActionE〕
    {
      pThis_23 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
      v7 = *this;
      *(this + 19) = pThis_23;  // this+76〔pBtnActionE〕
      LOBYTE(pThis_22) = (*(int (/*thiscall*/ **)(int *))(v7 + 104))(this);  // 虚函数调用 槽+104：页绘制（114 行：43C250/69A5F
    }
  }
  return pThis_22;
}



// ------------------------------------------------------------
// 0x5F6750 sub_5F6750
// ------------------------------------------------------------
// 调: sub_5F6750
int /*thiscall*/ sub_5F6750(int this)  // 实现：调: sub_5F6750
{
  *(uint32_t *)(this + 72) = 0;  // this+72 【推断】快照槽
  *(uint8_t *)(this + 68) = 0;  // this+68 角色数
  return 0;
}



// ------------------------------------------------------------
// 0x5F6760 IRDAppendage__vmt38
// ------------------------------------------------------------
// 调: sub_53FE50 sub_53FEE0 sub_5402D0 sub_698F90
void /*thiscall*/ IRDAppendage__vmt38(uint32_t *this, int nArg2, int nArg3, char pszArg4, int nArg5, unsigned int ArgList, int nArg7)  // 函数定义: y | z<<16 组合
{
  int pObj; // ebx
  uint32_t *fld_e12; // ecx
  uint32_t *v10; // edi
  int (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  int v12; // eax
  unsigned int v13; // ebx
  int v14; // ecx
  uint32_t *v15; // edi
  uint32_t *v16; // [esp+8h] [ebp-10h]
  int v17; // [esp+Ch] [ebp-Ch]
  int nArg72; // [esp+10h] [ebp-8h]
  int v19; // [esp+14h] [ebp-4h]
  int (/*thiscall*/ ***v20)(uint32_t, int); // [esp+34h] [ebp+1Ch]

  pObj = nArg2;
  if ( nArg2 == 0 )
    return;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 80))(this) != 0 )  // 虚调用 vt+80
  {
    fld_e12 = (uint32_t *)*(this + 12);  // this+12 物品类型号
    if ( fld_e12 != nullptr )  // 若 fld_e12 有效（非空）
      sub_53FE50(fld_e12, (int)this);
  }
  v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 虚函数调用 槽+700：读 +6296 槽
  v16 = v10;
  nArg72 = nArg7;
  if ( nArg7 != -1 )
    goto LABEL_9;
  if ( ArgList < 0x38 )
  {
    nArg72 = dword_73A0D0[ArgList];
LABEL_9:
    v11 = nullptr;
    if ( nArg72 != 0 )
    {
      v12 = v10[1];
      v17 = 0;
      v20 = nullptr;
      if ( v12 != 0 )
        v19 = (v10[2] - v12) >> 2;  // 向量元素数 = (end−begin)/4
      else
        v19 = 0;
      v13 = 0;
      if ( v19 > 0 )
      {
        do
        {
          v14 = v10[1];
          if ( v14 != 0 && v13 < (v10[2] - v14) >> 2 )  // 向量元素数 = (end−begin)/4
            v15 = *(uint32_t **)(v14 + 4 * v13);
          else
            v15 = nullptr;
          if ( v15[16] == ArgList && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v15 + 80))(v15) != 0 )  // 虚调用 vt+80
          {
            if ( v20 == nullptr )  // 若 v20 为空
              v20 = (int (/*thiscall*/ ***)(uint32_t, int))v15;
            ++v17;
          }
          v10 = v16;
          ++v13;
        }
        while ( (int)v13 < v19 );
        v11 = v20;
      }
      if ( v17 >= nArg72 )
      {
        if ( *(uint8_t *)(((int (/*thiscall*/ *)(int (/*thiscall*/ ***)(uint32_t, int)))(*v11)[16])(v11) + 36) != 0 )
          sub_53FEE0(v10, v20);
        else
          sub_53FE50(v10, (int)v20);
      }
      pObj = nArg2;
    }
    goto LABEL_30;
  }
  off_77F3FC(aCriticalErorrA, ArgList);  // 读 off_77F3FC（引擎日志输出函数）
LABEL_30:
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);  // 虚函数调用 槽+700：读 +6296 槽
  sub_5402D0(this);  // 窗口数据准备中层（转发 540280）
  *(this + 1) = pObj;  // 写 this+4 = pObj（宿主对象指针）
  *((uint8_t *)this + 21) = 0;  // this+21 【推断】霸体状态字节
  *((uint8_t *)this + 22) = 0;
  sub_698F90((int)(this + 2), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(this + 9) = nArg3;  // 写 this+36 = nArg3（状态字）
  *((uint8_t *)this + 54) = pszArg4;
  *(this + 14) = nArg5;  // this+56〔pCmdVecCap56(推断)〕
  *(this + 16) = ArgList;  // this+16 频道型选中索引
  if ( pszArg4 != 0 && nArg5 != 0 )  // 若 pszArg4 != 0 与/或 nArg5 != 0
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 108))(this);  // 虚调用 vt+108
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 76))(this, 1);  // 虚调用 vt+76
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 28))(this);  // 虚调用 vt+28
}



// ------------------------------------------------------------
// 0x5F68E0 IRDAppendage__vmt74
// ------------------------------------------------------------
// 证: 叶子函数（37 行，无外调无字符串）
int /*thiscall*/ IRDAppendage__vmt74(uint32_t *this)  // 实现：证: 叶子函数（37 行，无外调无字符串）
{
  int fld_e12; // eax
  int v4; // ecx
  int v5; // edi
  unsigned int j; // esi
  int fld_e122; // eax
  int v8; // ecx
  uint32_t *v9; // ecx
  int i; // [esp+4h] [ebp-4h]

  if ( *(this + 12) == 0 )  // this+12 物品类型号
    return 0;
  for ( i = 0; ; ++i )
  {
    fld_e12 = *(this + 12);  // this+12 物品类型号
    v4 = *(uint32_t *)(fld_e12 + 4);
    if ( v4 != 0 )
      v5 = (*(uint32_t *)(fld_e12 + 8) - v4) >> 2;  // 向量元素数 = (end−begin)/4
    else
      v5 = 0;
    for ( j = 0; (int)j < v5; ++j )
    {
      fld_e122 = *(this + 12);  // this+12 物品类型号
      v8 = *(uint32_t *)(fld_e122 + 4);
      if ( v8 != 0 && j < (*(uint32_t *)(fld_e122 + 8) - v8) >> 2 )  // 向量元素数 = (end−begin)/4
        v9 = *(uint32_t **)(v8 + 4 * j);
      else
        v9 = nullptr;
      if ( v9 != this && (*(int (/*thiscall*/ **)(uint32_t *))(*v9 + 100))(v9) == i )  // 虚调用 vt+100
        break;
    }
    if ( j == v5 )
      break;
  }
  return i;
}



// ------------------------------------------------------------
// 0x5F6970 IRDAppendage__vmt6C
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/BuffStartIcon." | "Common/CommonEffect/Animation/BuffStartIconG" |
//  "Common/CommonEffect/Animation/BuffStartGlow."
// 调: sub_42FCB0 sub_431860 sub_4924C0 sub_44B6C0 sub_44E0D0
void /*usercall*/ sub_5F6970(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 【IRDAppendage__vmt6C】
{
  int v3; // eax
  int pObj; // esi
  int v5; // eax
  int v6; // edx
  int v7; // edi
  int *v8; // edi
  int v9; // eax
  char *v10; // eax
  char *v11; // ebx
  char *v12; // eax
  int v13; // ebx
  char *v14; // eax
  char *v15; // edi
  int v16; // ebx
  char *v17; // eax
  char *v18; // edi
  int j; // edi
  int v20; // eax
  int pObj2; // edi
  uint8_t v22[4]; // [esp+8h] [ebp-3Ch] BYREF
  void *Block; // [esp+Ch] [ebp-38h]
  uint32_t v24[3]; // [esp+18h] [ebp-2Ch]
  void *v25; // [esp+24h] [ebp-20h]
  int v26; // [esp+28h] [ebp-1Ch]
  int v27; // [esp+2Ch] [ebp-18h]
  int v28; // [esp+30h] [ebp-14h]
  char *i; // [esp+34h] [ebp-10h]
  int v30; // [esp+40h] [ebp-4h]

  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 116))(pArg1);  // 结果 = 虚调用 vt+116
  pObj = pArg1[1];
  pArg1[15] = v3;
  if ( pObj != 0 )
  {
    v25 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 80))(pObj);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    if ( v25 != nullptr )  // 若 v25 有效（非空）
    {
      v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, nArg2);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      v6 = *(uint32_t *)pObj;
      v26 = v5;
      v27 = (*(int (/*thiscall*/ **)(int))(v6 + 124))(pObj);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 192))(pObj);  // 虚函数调用 槽+192
      v28 = 30 * (pArg1[15] + 1) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) + v7;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      v8 = nullptr;
      v30 = 0;
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v8 = (int *)sub_431860((char)"Common/CommonEffect/Animation/BuffStartIcon.ani", 1);  // 字符串 “Common/CommonEffect/Animation/BuffStartIcon.”
      v30 = -1;
      for ( i = nullptr; ; ++i )
      {
        v9 = v8[11];
        if ( v9 != 0 )
          v9 = (v8[12] - v9) / 88;
        if ( (int)i >= v9 )
          break;
        *(uint32_t *)sub_4924C0(v8, (int)i) = pArg1[14];  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
      }
      v10 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      v11 = v10;
      i = v10;
      v30 = 1;
      if ( v10 != nullptr )  // 若 v10 有效（非空）
      {
        sub_44E0D0(v10, (int)v8, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)v11 = &CNRDPooledObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
        v12 = v11;
      }
      else
      {
        v12 = nullptr;
      }
      v24[0] = v12;
      v30 = 2;
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v13 = sub_431860((char)"Common/CommonEffect/Animation/BuffStartIconGlow.ani", 1);  // 字符串 “Common/CommonEffect/Animation/BuffStartIconG”
      else
        v13 = 0;
      v14 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      v15 = v14;
      i = v14;
      v30 = 3;
      if ( v14 != nullptr )  // 若 v14 有效（非空）
      {
        sub_44E0D0(v14, v13, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)v15 = &CNRDPooledObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
      }
      else
      {
        v15 = nullptr;
      }
      v24[1] = v15;
      v30 = 4;
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v16 = sub_431860((char)"Common/CommonEffect/Animation/BuffStartGlow.ani", 1);  // 字符串 “Common/CommonEffect/Animation/BuffStartGlow.”
      else
        v16 = 0;
      v17 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      v18 = v17;
      i = v17;
      v30 = 5;
      if ( v17 != nullptr )  // 若 v17 有效（非空）
      {
        sub_44E0D0(v17, v16, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)v18 = &CNRDPooledObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
      }
      else
      {
        v18 = nullptr;
      }
      v24[2] = v18;
      v30 = -1;
      for ( j = 0; j < 3; ++j )  // 循环：j 从 0 递增到 3
      {
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v24[j] + 72))(v24[j]);  // 虚函数调用 槽+72：槽（4BE520/4F2D40 + 4848
        sub_45FE80((int)v25, j, 2, 0, v24[j], pObj, 0);  // 调 对象注册
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)v24[j] + 112))(v24[j], v26, v27, v28);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
        v20 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v24[j] + 60))(v24[j], pObj);  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
        sub_4A06D0(v20, 2);  // 调 绑定目标对象并记录相对偏移
      }
      pObj2 = dword_8F82E4;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F82E4 + 112))(dword_8F82E4, pObj);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 40))(pObj2, v26, v27, v28);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj2 + 92))(pObj2, v22);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
      v30 = 6;
      sub_4600B0(v25, 2, 0, (int)v22);  // 调 演播层注册(槽号)
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        pObj,
        "BUFF_ICON_SET",  // 字符串 “BUFF_ICON_SET”
        -1,
        0,
        0);
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
    }
  }
}


// ------------------------------------------------------------
// 0x5F6C50 IRDAppendage__vmt70
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/BuffEndIcon.an" | "Common/CommonEffect/Animation/BuffEndIconGlo"
// 调: sub_42FCB0 sub_431860 sub_4924C0 sub_44B6C0 sub_44E0D0
int /*thiscall*/ IRDAppendage__vmt70(int *this)  // 实现：调: sub_42FCB0 sub_431860 sub_4924C0 sub_44B6C0 sub_44E0D0
{
  int result; // eax
  int fld_e1; // esi
  int v4; // eax
  int v5; // edx
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  char *v10; // eax
  char *v11; // ebx
  char *v12; // eax
  int v13; // eax
  int v14; // ebx
  char *v15; // eax
  char *v16; // edi
  int j; // edi
  uint32_t v18[2]; // [esp+8h] [ebp-28h]
  int v19; // [esp+10h] [ebp-20h]
  int v20; // [esp+14h] [ebp-1Ch]
  int fld_e15; // [esp+18h] [ebp-18h]
  int v22; // [esp+1Ch] [ebp-14h]
  char *i; // [esp+20h] [ebp-10h]
  int v24; // [esp+2Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*this + 116))(this);  // 结果 = 虚调用 vt+116
  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  *(this + 15) = result;  // this+60〔nFadeValue60(推断)〕
  if ( fld_e1 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 80))(fld_e1);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    v22 = result;
    if ( result != 0 )  // 若结果非 0（成功）
    {
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 120))(fld_e1);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      v5 = *(uint32_t *)fld_e1;
      v19 = v4;
      v20 = (*(int (/*thiscall*/ **)(int))(v5 + 124))(fld_e1);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 192))(fld_e1);  // 虚函数调用 槽+192
      fld_e15 = 30 * (*(this + 15) + 1) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 128))(fld_e1) + v6;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      v7 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
      i = (char *)v7;
      v8 = 0;
      v24 = 0;
      if ( v7 != 0 )
        v8 = sub_431860(v7, "Common/CommonEffect/Animation/BuffEndIcon.ani", 1);  // 字符串 “Common/CommonEffect/Animation/BuffEndIcon.an”
      v24 = -1;
      for ( i = nullptr; ; ++i )
      {
        v9 = *(uint32_t *)(v8 + 44);
        if ( v9 != 0 )
          v9 = (*(uint32_t *)(v8 + 48) - v9) / 88;
        if ( (int)i >= v9 )
          break;
        *(uint32_t *)sub_4924C0(i) = *(this + 14);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
      }
      v10 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      v11 = v10;
      i = v10;
      v24 = 1;
      if ( v10 != nullptr )  // 若 v10 有效（非空）
      {
        sub_44E0D0(v10, v8, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)v11 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
        v12 = v11;
      }
      else
      {
        v12 = nullptr;
      }
      v18[0] = v12;
      v13 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
      i = (char *)v13;
      v24 = 2;
      if ( v13 != 0 )
        v14 = sub_431860(v13, "Common/CommonEffect/Animation/BuffEndIconGlow.ani", 1);  // 字符串 “Common/CommonEffect/Animation/BuffEndIconGlo”
      else
        v14 = 0;
      v15 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      v16 = v15;
      i = v15;
      v24 = 3;
      if ( v15 != nullptr )  // 若 v15 有效（非空）
      {
        sub_44E0D0(v15, v14, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)v16 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
      }
      else
      {
        v16 = nullptr;
      }
      v18[1] = v16;
      v24 = -1;
      for ( j = 0; j < 2; ++j )  // 循环：j 从 0 递增到 2
      {
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v18[j] + 72))(v18[j]);  // 虚函数调用 槽+72：槽（4BE520/4F2D40 + 4848
        sub_45FE80(v22, j, 2, 0, v18[j], fld_e1, 0);  // 调 对象注册
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)v18[j] + 112))(v18[j], v19, v20, fld_e15);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v18[j] + 60))(v18[j], fld_e1);  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
        result = sub_4A06D0(2);  // 调 绑定目标对象并记录相对偏移
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F6E50 sub_5F6E50
// ------------------------------------------------------------
// 调: sub_5F6E50
int /*thiscall*/ sub_5F6E50(uint32_t *this)  // 实现：调: sub_5F6E50
{
  *(this + 20) = 4;  // this+20 频道页号
  *(this + 21) = 0;  // this+21 【推断】霸体状态字节
  *(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  *(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *(this + 24) = 0;  // this+24 页数上限
  *(this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
  *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *(this + 28) = 0;  // 写 this+112 = 0（宿主组件）
  *(this + 29) = 0;  // 写 this+116 = 0（观察者容器）
  *(this + 30) = 0;  // 写 this+120 = 0（动画对象）
  *(this + 31) = 0;  // 写 this+124 = 0（光环动画件）
  *(this + 32) = 0;  // this+32 格子像素尺寸
  *(this + 33) = 0;  // this+33 【推断】职业数据脏位
  *(this + 34) = 0;  // this+136〔nCtx136(推断)〕
  *(this + 35) = 0;  // this+140〔nAdd140(推断)〕
  *(this + 36) = 0;  // this+36 物品状态字
  *(this + 37) = 0;  // 写 this+148 = 0（动画帧计数）
  *(this + 38) = 0;  // this+38 【推断】淡入收尾标志 B
  *(this + 39) = 0;  // this+156〔nAdd156(推断)〕
  *(this + 40) = 0;  // this+40 物品状态附属标志
  *(this + 41) = 0;  // this+164〔fAdd164(推断)〕
  *(this + 42) = 0;  // this+168〔pAppendVec(推断)〕
  *(this + 43) = 0;  // this+172〔pAppendVecEnd(推断)〕
  *(this + 44) = 0;  // this+44 剩余时间 ms
  return 0;
}



// ------------------------------------------------------------
// 0x5F6ED0 sub_5F6ED0
// ------------------------------------------------------------
// 调: sub_5F6ED0
int /*thiscall*/ sub_5F6ED0(uint32_t *this, int nArg2)  // 实现：调: sub_5F6ED0
{
  *(this + 20) = nArg2;  // this+20 频道页号
  return nArg2;
}



// ------------------------------------------------------------
// 0x5F6EE0 sub_5F6EE0
// ------------------------------------------------------------
// 调: sub_5F6EE0
int /*thiscall*/ sub_5F6EE0(uint32_t *this, int nArg2)  // 实现：调: sub_5F6EE0
{
  int result; // eax

  result = nArg2 - 172;
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 172:
      *(this + 33) = 0;  // this+33 【推断】职业数据脏位
      *(this + 34) = 0;  // this+136〔nCtx136(推断)〕
      *(this + 35) = 0;  // this+140〔nAdd140(推断)〕
      result = 0;
      break;
    case 173:
      *(this + 36) = 0;  // this+36 物品状态字
      *(this + 37) = 0;  // 写 this+148 = 0（动画帧计数）
      *(this + 38) = 0;  // this+38 【推断】淡入收尾标志 B
      *(this + 39) = 0;  // this+156〔nAdd156(推断)〕
      result = 0;
      break;
    case 174:
      *(this + 40) = 0;  // this+40 物品状态附属标志
      *(this + 41) = 0;  // this+164〔fAdd164(推断)〕
      *(this + 42) = 0;  // this+168〔pAppendVec(推断)〕
      *(this + 43) = 0;  // this+172〔pAppendVecEnd(推断)〕
      *(this + 44) = 0;  // this+44 剩余时间 ms
      result = 0;
      break;
    case 185:
      *(this + 31) = 0;  // 写 this+124 = 0（光环动画件）
      *(this + 32) = 0;  // this+32 格子像素尺寸
      result = 0;
      break;
    case 187:
      *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
      *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
      *(this + 28) = 0;  // 写 this+112 = 0（宿主组件）
      *(this + 29) = 0;  // 写 this+116 = 0（观察者容器）
      *(this + 30) = 0;  // 写 this+120 = 0（动画对象）
      result = 0;
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F6FB0 sub_5F6FB0
// ------------------------------------------------------------
// 调: sub_5F6FB0 sub_41A5E0
int /*thiscall*/ sub_5F6FB0(int this)  // 实现：调: sub_5F6FB0 sub_41A5E0
{
  float *v2; // ebx
  int result; // eax
  int pObj; // esi
  int v5; // eax
  int v6; // eax
  double pThis_4; // st7
  int v8; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 84) = 0;  // this+84 插值起点 X
  *(uint32_t *)(this + 88) = 0;  // this+88 插值起点 Y
  *(uint32_t *)(this + 92) = 0;  // this+92 插值起点 Z
  *(uint32_t *)(this + 96) = 0;  // this+96 插值终点 X / 落点偏移
  *(uint32_t *)(this + 100) = 0;  // this+100 插值终点 Y
  v8 = 10;
  v2 = (float *)&unk_73A2F4;
  do
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 792))(*(uint32_t *)(this + 4), v8);  // 涉及字段 “+4 宿主对象指针”
    pObj = result;
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 200))(result);  // 虚函数调用 槽+200：取动画对象
      if ( (uint8_t)result == 0 )
      {
        v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);  // 虚函数调用 槽+172：朝目标方向按比例取点: p = this +…
        v6 = sub_41A5E0(v5 + 4);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        pThis_4 = *v2 + *(float *)(this + 4 * v6 + 84);  // this+4 宿主对象
        result = this + 4 * v6 + 84;  // this+4 宿主对象
        *(float *)result = pThis_4;
      }
    }
    ++v2;
    ++v8;
  }
  while ( (int)v2 <= (int)&flt_73A304 );
  return result;
}



// ------------------------------------------------------------
// 0x5F7040 CNArmorMastery__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
void /*thiscall*/ sub_5F7040(int this, int pArg2)  // 【CNArmorMastery__vmtC】
{
  int v4; // edx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // edx
  int v16; // edx
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // edx
  int v22; // edx
  float fld_68; // [esp+Ch] [ebp-4h]  | +0x0068 → 第 1 组·宿主属性 +802 增量子倍率（× fMul84 累加）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_6C; // [esp+Ch] [ebp-4h]  | +0x006C → 第 1 组·宿主属性 +886 增量（×0.001×fMul84 累加）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_70; // [esp+Ch] [ebp-4h]  | +0x0070 → 第 1 组·宿主属性 +46 增量子倍率（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_7C; // [esp+Ch] [ebp-4h]  | +0x007C → 第 2 组·+858/+1292 增量（×0.001×fMul88）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_7C2; // [esp+Ch] [ebp-4h]  | +0x007C → 第 2 组·+858/+1292 增量（×0.001×fMul88）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_80; // [esp+Ch] [ebp-4h]  | +0x0080 → 第 2 组·+1208 增量子倍率（× fMul88）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_94; // [esp+Ch] [ebp-4h]  | +0x0094 → 第 4 组·+802 增量子倍率（× fMul96）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_98; // [esp+Ch] [ebp-4h]  | +0x0098 → 第 4 组·+886 增量（×0.001×fMul96）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_9C; // [esp+Ch] [ebp-4h]  | +0x009C → 第 4 组·+858/+1292 增量（×0.001×fMul96；两址同源双写）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_9C2; // [esp+Ch] [ebp-4h]  | +0x009C → 第 4 组·+858/+1292 增量（×0.001×fMul96；两址同源双写）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_A8; // [esp+Ch] [ebp-4h]  | +0x00A8 → 第 5 组·+802 增量子倍率（× fMul100）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_AC; // [esp+Ch] [ebp-4h]  | +0x00AC → 第 5 组·+886 增量（×0.001×fMul100）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  float fld_B0; // [esp+Ch] [ebp-4h]  | +0x00B0 → 第 5 组·+858/+1292 增量（CNArmorMastery；va=005F7040）
  float fld_B02; // [esp+Ch] [ebp-4h]  | +0x00B0 → 第 5 组·+858/+1292 增量（CNArmorMastery；va=005F7040）
  int v37; // [esp+18h] [ebp+8h]
  int v38; // [esp+18h] [ebp+8h]
  int v39; // [esp+18h] [ebp+8h]
  int fld_4; // [esp+18h] [ebp+8h]  | +0x0004 → 宿主对象（CNArmorMastery；va=005F7040）
  int v41; // [esp+18h] [ebp+8h]
  int v42; // [esp+18h] [ebp+8h]
  int v43; // [esp+18h] [ebp+8h]
  int fld_42; // [esp+18h] [ebp+8h]  | +0x0004 → 宿主对象（CNArmorMastery；va=005F7040）
  int fld_8C; // [esp+18h] [ebp+8h]  | +0x008C → 第 3 组·+900 增量（×0.001×fMul92）（证据: va=005F7040）（CNArmorMastery；va=005F7040）
  int fld_43; // [esp+18h] [ebp+8h]  | +0x0004 → 宿主对象（CNArmorMastery；va=005F7040）
  int v47; // [esp+18h] [ebp+8h]
  int v48; // [esp+18h] [ebp+8h]
  int v49; // [esp+18h] [ebp+8h]
  int v50; // [esp+18h] [ebp+8h]
  int fld_44; // [esp+18h] [ebp+8h]  | +0x0004 → 宿主对象（CNArmorMastery；va=005F7040）
  int fld_45; // [esp+18h] [ebp+8h]  | +0x0004 → 宿主对象（CNArmorMastery；va=005F7040）
  int v53; // [esp+18h] [ebp+8h]
  int v54; // [esp+18h] [ebp+8h]
  int v55; // [esp+18h] [ebp+8h]
  int v56; // [esp+18h] [ebp+8h]

  if ( *(float *)(this + 84) != 0.0 )  // 判定 “+84 第 1 段增幅倍率门”
  {
    fld_68 = *(float *)(this + 104) * *(float *)(this + 84);  // this+104 第 1 组·宿主属性 +802 增量子倍率
    *(float *)&v37 = COERCE_FLOAT(sub_41A5E0(pArg2 + 802)) + fld_68;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 802, v4, v37);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_6C = (double)*(int *)(this + 108) * *(float *)(this + 84) * 0.001;  // this+108 第 1 组·宿主属性 +886 增量
    *(float *)&v38 = COERCE_FLOAT(sub_41A5E0(pArg2 + 886)) + fld_6C;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 886, v5, v38);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_70 = *(float *)(this + 112) * *(float *)(this + 84);  // 涉及字段 “+112 宿主组件”
    *(float *)&v39 = COERCE_FLOAT(sub_41A5E0(pArg2 + 46)) + fld_70;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 46, v39, v39);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_4 = (uint64_t)(((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))  // 涉及字段 “+4 宿主对象指针”
                            * *(float *)(this + 120)  // 涉及字段 “+120 动画对象”
                            + (double)*(int *)(this + 116))  // 涉及字段 “+116 观察者容器”
                           * *(float *)(this + 84));  // this+84 第 1 段增幅倍率门
    v6 = sub_41A5E0(pArg2 + 116);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 116, v7, fld_4 + v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  if ( *(float *)(this + 88) != 0.0 )  // 判定 “+88 第 2 段增幅倍率门”
  {
    fld_7C = (double)*(int *)(this + 124) * *(float *)(this + 88) * 0.001;  // 涉及字段 “+124 光环动画件”
    *(float *)&v41 = COERCE_FLOAT(sub_41A5E0(pArg2 + 858)) + fld_7C;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 858, v41, v41);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_7C2 = (double)*(int *)(this + 124) * *(float *)(this + 88) * 0.001;  // 涉及字段 “+124 光环动画件”
    *(float *)&v42 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1292)) + fld_7C2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 1292, v8, v42);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_80 = *(float *)(this + 128) * *(float *)(this + 88);  // this+128 第 2 组·+1208 增量子倍率
    *(float *)&v43 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1208)) + fld_80;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 1208, v9, v43);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  if ( *(float *)(this + 92) != 0.0 )  // 判定 “+92 第 3 段增幅倍率门”
  {
    fld_42 = (uint64_t)(((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))  // 涉及字段 “+4 宿主对象指针”
                            * *(float *)(this + 136)  // this+136 第 3 组·+60 增量子倍率
                            + (double)*(int *)(this + 132))  // this+132 第 3 组·+60 增量项
                           * *(float *)(this + 92));  // this+92 第 3 段增幅倍率门
    v10 = sub_41A5E0(pArg2 + 60);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 60, v11, fld_42 + v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_8C = (uint64_t)((double)*(int *)(this + 140) * *(float *)(this + 92));  // this+140 第 3 组·+900 增量
    v12 = sub_41A5E0(pArg2 + 900);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 900, fld_8C, fld_8C + v12);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  if ( *(float *)(this + 96) != 0.0 )  // 判定 “+96 第 4 段增幅倍率门”
  {
    fld_43 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))  // 涉及字段 “+4 宿主对象指针”
                           * *(float *)(this + 144)  // this+144 第 4 组·+1040 增量子倍率
                           * *(float *)(this + 96));  // this+96 第 4 段增幅倍率门
    v13 = sub_41A5E0(pArg2 + 1040);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 1040, v14, fld_43 + v13);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_94 = *(float *)(this + 148) * *(float *)(this + 96);  // 涉及字段 “+148 动画帧计数”
    *(float *)&v47 = COERCE_FLOAT(sub_41A5E0(pArg2 + 802)) + fld_94;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 802, v47, v47);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_98 = (double)*(int *)(this + 152) * *(float *)(this + 96) * 0.001;  // this+152 第 4 组·+886 增量
    *(float *)&v48 = COERCE_FLOAT(sub_41A5E0(pArg2 + 886)) + fld_98;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 886, v15, v48);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_9C = (double)*(int *)(this + 156) * *(float *)(this + 96) * 0.001;  // this+156 第 4 组·+858/+1292 增量
    *(float *)&v49 = COERCE_FLOAT(sub_41A5E0(pArg2 + 858)) + fld_9C;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 858, v16, v49);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_9C2 = (double)*(int *)(this + 156) * *(float *)(this + 96) * 0.001;  // this+156 第 4 组·+858/+1292 增量
    *(float *)&v50 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1292)) + fld_9C2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 1292, v50, v50);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  if ( *(float *)(this + 100) != 0.0 )  // 判定 “+100 第 5 段增幅倍率门”
  {
    fld_44 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))  // 涉及字段 “+4 宿主对象指针”
                           * *(float *)(this + 160)  // this+160 第 5 组·+1040 增量子倍率
                           * *(float *)(this + 100));  // this+100 第 5 段增幅倍率门
    v17 = sub_41A5E0(pArg2 + 1040);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 1040, v18, fld_44 + v17);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_45 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))  // 涉及字段 “+4 宿主对象指针”
                           * *(float *)(this + 164)  // this+164 第 5 组·+88 增量子倍率
                           * *(float *)(this + 100));  // this+100 第 5 段增幅倍率门
    v19 = sub_41A5E0(pArg2 + 88);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 88, v20, fld_45 + v19);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_A8 = *(float *)(this + 168) * *(float *)(this + 100);  // this+168 第 5 组·+802 增量子倍率
    *(float *)&v53 = COERCE_FLOAT(sub_41A5E0(pArg2 + 802)) + fld_A8;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 802, v53, v53);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_AC = (double)*(int *)(this + 172) * *(float *)(this + 100) * 0.001;  // this+172 第 5 组·+886 增量
    *(float *)&v54 = COERCE_FLOAT(sub_41A5E0(pArg2 + 886)) + fld_AC;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 886, v21, v54);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_B0 = (double)*(int *)(this + 176) * *(float *)(this + 100) * 0.001;  // this+176 第 5 组·+858/+1292 增量
    *(float *)&v55 = COERCE_FLOAT(sub_41A5E0(pArg2 + 858)) + fld_B0;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 858, v22, v55);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_B02 = (double)*(int *)(this + 176) * *(float *)(this + 100) * 0.001;  // this+176 第 5 组·+858/+1292 增量
    *(float *)&v56 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1292)) + fld_B02;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 1292, v56, v56);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
}


// ------------------------------------------------------------
// 0x5F74E0 sub_5F74E0
// ------------------------------------------------------------
// 调: sub_5F74E0 sub_47E720 sub_47E9D0
int /*thiscall*/ sub_5F74E0(int this, int nArg2)  // 实现：调: sub_5F74E0 sub_47E720 sub_47E9D0
{
  int result; // eax

  sub_47E720(*(uint32_t *)(this + 80), nArg2);  // 调 调 sub_47E720
  result = nArg2 - 172;
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 172:
      *(uint32_t *)(this + 132) = sub_47E9D0(0);  // 调 收招/结束例程
      *(float *)(this + 136) = (double)(int)sub_47E9D0(1) * 0.1;  // 调 收招/结束例程
      result = sub_47E9D0(2);  // 调 收招/结束例程
      *(uint32_t *)(this + 140) = result;  // this+140 第 3 组·+900 增量
      break;
    case 173:
      *(float *)(this + 144) = (double)(int)sub_47E9D0(0) * 0.1;  // 调 收招/结束例程
      *(float *)(this + 148) = (double)(int)sub_47E9D0(1) * 0.0099999998;  // 调 收招/结束例程
      *(uint32_t *)(this + 152) = sub_47E9D0(2);  // 调 收招/结束例程
      result = sub_47E9D0(3);  // 调 收招/结束例程
      *(uint32_t *)(this + 156) = result;  // this+156 第 4 组·+858/+1292 增量
      break;
    case 174:
      *(float *)(this + 160) = (double)(int)sub_47E9D0(0) * 0.1;  // 调 收招/结束例程
      *(float *)(this + 164) = (double)(int)sub_47E9D0(1) * 0.1;  // 调 收招/结束例程
      *(float *)(this + 168) = (double)(int)sub_47E9D0(2) * 0.0099999998;  // 调 收招/结束例程
      *(uint32_t *)(this + 172) = sub_47E9D0(3);  // 调 收招/结束例程
      result = sub_47E9D0(4);  // 调 收招/结束例程
      *(uint32_t *)(this + 176) = result;  // this+176 附属对象向量 cap
      break;
    case 185:
      *(uint32_t *)(this + 124) = sub_47E9D0(0);  // 调 收招/结束例程
      result = sub_47E9D0(1);  // 调 收招/结束例程
      *(float *)(this + 128) = (double)result * 0.1;  // this+128 第 2 组·+1208 增量子倍率
      break;
    case 187:
      *(float *)(this + 104) = (double)(int)sub_47E9D0(0) * 0.0099999998;  // 调 收招/结束例程
      *(uint32_t *)(this + 108) = sub_47E9D0(1);  // 调 收招/结束例程
      *(float *)(this + 112) = (double)(int)sub_47E9D0(2) * 0.0099999998;  // 调 收招/结束例程
      *(uint32_t *)(this + 116) = sub_47E9D0(3);  // 调 收招/结束例程
      result = sub_47E9D0(4);  // 调 收招/结束例程
      *(float *)(this + 120) = (double)result * 0.1;  // 写 this+120 = (double)result * 0.1（动画对象）
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F7700 sub_5F7700
// ------------------------------------------------------------
// 调: sub_5F7700
int /*thiscall*/ sub_5F7700(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_5F7700
{
  *(this + 11) = nArg2;  // this+44〔nExpireMs(推断)〕
  *(this + 24) = nArg3;  // this+24 页数上限
  return nArg2;
}



// ------------------------------------------------------------
// 0x5F7720 sub_5F7720
// ------------------------------------------------------------
// 调: sub_5F7720
int /*thiscall*/ sub_5F7720(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：调: sub_5F7720
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 120))(this, nArg2, nArg3, nArg4);  // 虚调用 vt+120
  *(this + 11) = nArg5;  // this+44〔nExpireMs(推断)〕
  *(this + 24) = nArg6;  // this+24 页数上限
  return nArg6;
}



// ------------------------------------------------------------
// 0x5F7750 sub_5F7750
// ------------------------------------------------------------
// 调: sub_5F7750
int /*thiscall*/ sub_5F7750(uint32_t *this, int pArg2, int nArg3, int nArg4, int nArg5)  // 实现：调: sub_5F7750
{
  int nArg32; // ebx
  uint8_t *v7; // esi
  int result; // eax

  nArg32 = nArg3;
  if ( nArg3 <= 0 )
  {
    *(this + 11) = nArg4;  // this+44〔nExpireMs(推断)〕
    *(this + 24) = nArg5;  // this+24 页数上限
  }
  else
  {
    v7 = (uint8_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t))(*this + 120))(  // 虚调用 vt+120
        this,
        *((uint32_t *)v7 - 1),
        *v7,
        *((uint32_t *)v7 + 1));
      v7 += 12;
      --nArg32;
    }
    while ( nArg32 != 0 );
    *(this + 11) = nArg4;  // this+44〔nExpireMs(推断)〕
    *(this + 24) = nArg5;  // this+24 页数上限
    return nArg5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F77B0 CNChangeStatus__vmt20
// ------------------------------------------------------------
// 证: 叶子函数（12 行，无外调无字符串）
char /*thiscall*/ CNChangeStatus__vmt20(int this, char pszArg2)  // 函数定义: 设置坐标三元组 (this+100..112)
{
  char result; // al

  if ( *(uint32_t *)(this + 96) == 4 )  // 判定 “+96 状态模式”
  {
    result = pszArg2;
    if ( pszArg2 == 0 )
      return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 216))(*(uint32_t *)(this + 4), 6);  // 涉及字段 “+4 宿主对象指针”
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F77E0 CNChangeStatus__vmt34
// ------------------------------------------------------------
// 证: "BUFF_SHOWTIME_LOOP"
int /*thiscall*/ CNChangeStatus__vmt34(int this)  // 实现：证: BUFF_SHOWTIME_LOOP
{
  int result; // eax

  if ( *(uint32_t *)(this + 96) == 4 )  // 判定 “+96 状态模式”
    return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(  // this+4 宿主对象指针
             *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
             "BUFF_SHOWTIME_LOOP",  // 字符串 “BUFF_SHOWTIME_LOOP”
             6,
             0,
             0);
  return result;
}



// ------------------------------------------------------------
// 0x5F7800 CNChangeStatus__vmt8
// ------------------------------------------------------------
// 证: 叶子函数（19 行，无外调无字符串）
unsigned int /*thiscall*/ CNChangeStatus__vmt8(uint32_t *this, int nArg2)  // 实现：证: 叶子函数（19 行，无外调无字符串）
{
  unsigned int result; // eax
  int fld_e21; // esi
  unsigned int i; // edi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
  if ( (uint8_t)result != 1 )
  {
    fld_e21 = *(this + 21);  // this+21 【推断】霸体状态字节
    for ( i = 0; fld_e21 != 0; ++i )
    {
      result = (*(this + 22) - fld_e21) / 12;  // this+88〔pFxObjB(推断)〕
      if ( i >= result )
        break;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F7840 CNChangeStatus__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
unsigned int /*thiscall*/ sub_5F7840(int *this, int nArg2)  // 【CNChangeStatus__vmtC】
{
  int *pThis; // ebx
  unsigned int result; // eax
  int nArg22; // edi
  unsigned int v5; // esi
  int v6; // eax
  int v7; // esi
  int v8; // eax
  unsigned int v9; // esi
  int fld_e1; // eax  | +0x0004 → 宿主对象指针（CNChangeStatus；va=005F8570）
  int v11; // eax
  int v12; // edx
  int fld_e12; // eax  | +0x0004 → 宿主对象指针（CNChangeStatus；va=005F8570）
  int v14; // edx
  int v15; // esi
  int v16; // ebx
  int fld_e21; // edx
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  int v24; // ebx
  double v25; // st7
  unsigned int v26; // ebx
  int v27; // edx
  unsigned int v28; // ebx
  int v29; // eax
  int v30; // edx
  float v31; // [esp+0h] [ebp-28h]
  float v32; // [esp+0h] [ebp-28h]
  float v33; // [esp+0h] [ebp-28h]
  float v34; // [esp+0h] [ebp-28h]
  float v35; // [esp+0h] [ebp-28h]
  float v36; // [esp+0h] [ebp-28h]
  float v37; // [esp+0h] [ebp-28h]
  float v38; // [esp+0h] [ebp-28h]
  float v39; // [esp+0h] [ebp-28h]
  float v40; // [esp+0h] [ebp-28h]
  int v41; // [esp+10h] [ebp-18h]
  float v42; // [esp+10h] [ebp-18h]
  int v43; // [esp+10h] [ebp-18h]
  int v44; // [esp+10h] [ebp-18h]
  int v45; // [esp+14h] [ebp-14h]
  float v46; // [esp+14h] [ebp-14h]
  int v47; // [esp+18h] [ebp-10h]
  unsigned int v48; // [esp+1Ch] [ebp-Ch]
  int i; // [esp+20h] [ebp-8h]

  pThis = this;
  result = (*(int (/*fastcall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
  if ( (uint8_t)result != 1 )
  {
    nArg22 = nArg2;
    v5 = 0;
    while ( 1 )  // 无限循环
    {
      while ( 1 )  // 无限循环
      {
        result = pThis[21];
        v48 = v5;
        if ( result == 0 )
          return result;
        result = (int)(pThis[22] - result) / 12;
        if ( v5 >= result )
          return result;
        v6 = 12 * v5;
        v7 = pThis[21] + 12 * v5;
        v41 = v6;
        v8 = *(uint32_t *)v7;
        if ( *(uint32_t *)v7 != 16 && v8 != 17 && v8 != 18 && v8 != 19 )  // 若 v8 != 17 与/或 v8 != 18
          break;
        v24 = 4;
        switch ( *(uint32_t *)v7 )  // 按 *(uint32_t *)v7 分派
        {
          case 0x10:
            v24 = 0;
            break;
          case 0x11:
            v24 = 1;
            break;
          case 0x12:
            v24 = 2;
            break;
          case 0x13:
            v24 = 3;
            break;
          default:
            break;
        }
        v25 = *(float *)(v7 + 8);
        if ( *(uint8_t *)(v7 + 4) != 0 )
        {
          v46 = v25 * 0.0099999998;  // ×0.01f（百分数转比例）
          v26 = 14 * v24 + nArg22 + 228;
          *(float *)&v44 = COERCE_FLOAT(sub_41A5E0(v26)) + v46;  // crypt4byte 解密校验（·0x41A590 逆运算）
          sub_41A590(v26, v27, v44);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          pThis = this;
          v5 = v48 + 1;
        }
        else
        {
          v28 = 14 * v24 + nArg22 + 172;
          v29 = sub_41A5E0(v28);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          sub_41A590(v28, v30, (uint64_t)v25 + v29);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
LABEL_104:
          pThis = this;
          v5 = v48 + 1;
        }
      }
      if ( v8 == 20 )
      {
        v9 = nArg22 + 228;
        v47 = -228 - nArg22;
        for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
        {
          fld_e1 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 672))(*(this + 1), 3);  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
          v45 = sub_41A5E0(fld_e1 + v9 + v47 + 172);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          v11 = sub_41A5E0(v9 - 56);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          sub_41A590(v9 - 56, v12, v11 - v45);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          fld_e12 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 672))(*(this + 1), 3);  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
          v42 = COERCE_FLOAT(sub_41A5E0(fld_e12 + v9 + v47 + 228));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          *(float *)&v43 = COERCE_FLOAT(sub_41A5E0(v9)) - v42;  // crypt4byte 解密校验（·0x41A590 逆运算）
          sub_41A590(v9, v14, v43);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          v9 += 14;
        }
        nArg22 = nArg2;
        pThis = this;
        v5 = v48 + 1;
      }
      else
      {
        switch ( *(uint32_t *)v7 )  // 按 *(uint32_t *)v7 分派
        {
          case 0x15:
            v15 = 0;
            v16 = nArg22 + 284;
            do
            {
              if ( sub_497040(v15) != 17 )  // 状态号映射表（12 直通、14→15、15→16，其余→17）
              {
                fld_e21 = *(this + 21);  // this+21 【推断】霸体状态字节
                v18 = *(float *)(v41 + fld_e21 + 8);
                if ( *(uint8_t *)(v41 + fld_e21 + 4) != 0 )
                {
                  v31 = v18 * 0.0099999998;  // ×0.01f（百分数转比例）
                  sub_4AED60(v31);
                }
                else
                {
                  sub_4450B0((uint64_t)v18);  // 计数器加值
                }
              }
              ++v15;
              v16 += 14;
            }
            while ( v15 < 16 );
            pThis = this;
            v5 = v48 + 1;
            break;
          case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) == 0 )
              goto LABEL_50;
            goto LABEL_59;
          case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 0x16:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 4:  // case 4 = ENUM_CMDPACKET_EXIT
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 0x19:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 0x1A:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
LABEL_50:
            sub_4450B0((uint64_t)v19);  // 计数器加值
            pThis = this;
            v5 = v48 + 1;
            break;
          case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) == 0 )
              goto LABEL_50;
            goto LABEL_59;
          case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_53;
          case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_53;
          case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
LABEL_53:
            v32 = v19 * 0.001;
            sub_4AED60(v32);
            pThis = this;
            v5 = v48 + 1;
            break;
          case 0xA:
            if ( *(uint8_t *)(v7 + 4) != 0 )
            {
              v34 = *(float *)(v7 + 8) * 0.0099999998;  // ×0.01f（百分数转比例）
              sub_4AED60(v34);
            }
            else
            {
              v21 = sub_433F60(pThis[1], 2) * (double)(int)(uint64_t)*(float *)(v7 + 8);  // 调 PVP 平衡系数路由（研究第 17/27 轮）
              sub_4450B0((uint64_t)v21);  // 计数器加值
            }
            pThis = this;
            v5 = v48 + 1;
            break;
          case 0xB:
            v22 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
            {
              v35 = v22 * 0.0099999998;  // ×0.01f（百分数转比例）
              sub_4AED60(v35);
            }
            else
            {
              sub_4450B0((uint64_t)v22);  // 计数器加值
            }
            pThis = this;
            v5 = v48 + 1;
            break;
          case 0x17:
            v23 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
            {
              v36 = v23 * 0.0099999998;  // ×0.01f（百分数转比例）
              sub_4AED60(v36);
            }
            else
            {
              sub_4450B0((uint64_t)v23);  // 计数器加值
            }
            pThis = this;
            v5 = v48 + 1;
            break;
          case 0x18:
            if ( *(uint8_t *)(v7 + 4) == 0 )
            {
              v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
              goto LABEL_60;
            }
            v37 = sub_43B5A0((void *)(nArg22 + 1292)) * *(float *)(v7 + 8) * 0.0099999998;  // 结果 = 防篡读壳（槽值转 float）
            sub_4AED60(v37);
            pThis = this;
            v5 = v48 + 1;
            break;
          case 0xC:
            if ( *(uint8_t *)(v7 + 4) == 0 )
            {
              v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
              goto LABEL_60;
            }
            v38 = sub_43B5A0((void *)(nArg22 + 1208)) * *(float *)(v7 + 8) * 0.0099999998;  // 结果 = 防篡读壳（槽值转 float）
            sub_4AED60(v38);
            pThis = this;
            v5 = v48 + 1;
            break;
          case 0xD:
            if ( *(uint8_t *)(v7 + 4) == 0 )
            {
              v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
              goto LABEL_60;
            }
            v39 = sub_43B5A0((void *)(nArg22 + 1222)) * *(float *)(v7 + 8) * 0.0099999998;  // 结果 = 防篡读壳（槽值转 float）
            sub_4AED60(v39);
            pThis = this;
            v5 = v48 + 1;
            break;
          case 0xE:
            if ( *(uint8_t *)(v7 + 4) == 0 )
            {
              v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
              goto LABEL_60;
            }
            v40 = sub_43B5A0((void *)(nArg22 + 1236)) * *(float *)(v7 + 8) * 0.0099999998;  // 结果 = 防篡读壳（槽值转 float）
            sub_4AED60(v40);
            pThis = this;
            v5 = v48 + 1;
            break;
          case 0xF:
            if ( *(uint8_t *)(v7 + 4) != 0 )
            {
              v19 = sub_43B5A0((void *)(nArg22 + 1250)) * *(float *)(v7 + 8);  // 结果 = 防篡读壳（槽值转 float）
LABEL_59:
              v20 = v19 * 0.0099999998;  // ×0.01f（百分数转比例）
              goto LABEL_60;
            }
            v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
LABEL_60:
            v33 = v20;
            sub_4AED60(v33);
            pThis = this;
            v5 = v48 + 1;
            break;
          default:
            goto LABEL_104;
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// ============================================================
// §C 状态与buff
// ============================================================
// 0x5F8000 sub_5F8000
// ------------------------------------------------------------
// 调: sub_5F8000
char /*thiscall*/ sub_5F8000(int *this, char *pszArg2, int nArg3)  // 实现：调: sub_5F8000
{
  int fld_e21; // eax
  int v5; // edx
  char *pszArg22; // eax
  int fld_e212; // esi
  int fld_e2122; // [esp+8h] [ebp+8h]

  fld_e21 = *(this + 21);  // this+21 【推断】霸体状态字节
  if ( fld_e21 != 0 )
    fld_e21 = (*(this + 22) - fld_e21) / 12;  // this+88〔pFxObjB(推断)〕
  if ( fld_e21 != nArg3 )
    return 0;
  v5 = 0;
  if ( nArg3 <= 0 )
    return 1;  // 返回 1(成功)
  pszArg22 = pszArg2;
  fld_e212 = *(this + 21) - (uint32_t)pszArg2;  // this+21 【推断】霸体状态字节
  fld_e2122 = fld_e212;
  while ( memcmp(&pszArg22[fld_e212], pszArg22, 0xCu) == 0 )  // 调 按 4 字节块比较缓冲
  {
    ++v5;
    pszArg22 += 12;
    if ( v5 >= nArg3 )
      return 1;  // 返回 1(成功)
    fld_e212 = fld_e2122;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5F8080 CNChangeStatus__vmt14
// ------------------------------------------------------------
// 调: sub_699000 sub_4938F0 sub_4049C0 sub_491F80 sub_491D00
char /*thiscall*/ CNChangeStatus__vmt14(int this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 实现：调: sub_699000 sub_4938F0 sub_4049C0 sub_491F80 sub_491D00
{
  int fld_60; // eax  | +0x0060 → 状态模式（0x5F8080: switch 3/5/6/7 分派动画组；0x5F8570: ==1/==2 分派）（CNChangeStatus；va=005F8570）
  int fld_2C; // edi  | +0x002C → 剩余时间 ms（CNChangeStatus；va=005F8080）
  double v8; // st7
  int fld_70; // ecx  | +0x0070 → 状态件数组（CNChangeStatus；va=005F8080）
  int v10; // eax
  int fld_2C2; // ecx  | +0x002C → 剩余时间 ms（CNChangeStatus；va=005F8080）
  double v12; // st7
  int fld_4; // ecx  | +0x0004 → 宿主对象指针（CNChangeStatus；va=005F8570）
  int i; // ebx
  int fld_42; // eax  | +0x0004 → 宿主对象指针（CNChangeStatus；va=005F8570）

  LOBYTE(fld_60) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
  if ( (uint8_t)fld_60 == 0 )
  {
    fld_60 = *(uint32_t *)(this + 96);  // 读 fld_60 = this+96（状态模式）
    switch ( fld_60 )  // 按 fld_60 分派
    {
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        LOBYTE(fld_60) = pszArg2;  // 调 取 16 位值低 8 位
        if ( pszArg2 != 0 )
        {
          fld_2C = *(uint32_t *)(this + 44) - sub_699000(this + 8);  // 【clock_now(clk)】
          sub_4938F0(*(uint32_t *)(4 * (*(uint8_t *)(**(uint32_t **)(this + 112) + 170) != 0) + *(uint32_t *)(this + 112)));  // 调 调 sub_4938F0
          if ( fld_2C < 500 )
          {
            v8 = sub_4049C0(255.0, 0.0, 500 - fld_2C, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            sub_491F80(-1, -1, -1, (uint64_t)v8, 1);  // RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
          }
          LOBYTE(fld_60) = sub_491D00(dword_79C0B0, nArg3, nArg4, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        }
        break;
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        fld_70 = *(uint32_t *)(this + 112);  // 读 fld_70 = this+112（状态件数组）
        v10 = pszArg2 != 0;
        if ( *(uint8_t *)(*(uint32_t *)(fld_70 + 4 * v10) + 170) != 0 )
          v10 += 2;
        sub_4938F0(*(uint32_t *)(4 * v10 + fld_70));  // 调 调 sub_4938F0
        fld_2C2 = *(uint32_t *)(this + 44) - sub_699000(this + 8);  // 【clock_now(clk)】
        if ( fld_2C2 < 500 )
        {
          v12 = sub_4049C0(255.0, 0.0, 500 - fld_2C2, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          sub_491F80(-1, -1, -1, (uint64_t)v12, 1);  // RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
        }
        fld_4 = nArg4 - (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4)) / 2;  // 涉及字段 “+4 宿主对象指针”
        LOBYTE(fld_60) = sub_491D00(dword_79C0B0, nArg3, fld_4, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        break;
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
        for ( i = 0; i < 8; i += 4 )
        {
          sub_4938F0(*(uint32_t *)(*(uint32_t *)(this + 112) + i));  // 调 调 sub_4938F0
          fld_42 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
          LOBYTE(fld_60) = sub_491D00(dword_79C0B0, nArg3, nArg4 - fld_42, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        }
        break;
      default:
        break;
    }
  }
  return fld_60;  // | +0x0060 → 状态模式（0x5F8080: switch 3/5/6/7 分派动画组；0x5F8570: ==1/==2 分派）（CNChangeStatus；va=005F8570）
}



// ------------------------------------------------------------
// 0x5F8250 sub_5F8250
// ------------------------------------------------------------
// 调: sub_5F8250 sub_4B2F20 sub_59EE30 sub_504450 sub_5043B0
int /*thiscall*/ sub_5F8250(int *this, int pArg2, unsigned int uArg3, int *Block)  // 实现：调: sub_5F8250 sub_4B2F20 sub_59EE30 sub_504450 sub_5043B0
{
  int v5; // ecx
  int v6; // edx
  int fld_e1; // ebx
  int result; // eax
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v13; // ecx
  int fld_e27; // eax
  int v15; // ebx
  int fld_e13; // eax
  unsigned int v17; // edi
  void *fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-40h]
  int fld_e25; // [esp-Ch] [ebp-34h]
  unsigned int fld_e24; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  int v27; // [esp+30h] [ebp+8h]
  int v28; // [esp+34h] [ebp+Ch]
  char *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];
  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 12;  // this+12〔nSkillRec12(推断)〕
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_4B2F20(this);  // vector 长度超限抛出
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 12 >= uArg3 )
      {
        v27 = (int)fld_e23 - 12 * uArg3;
        *(this + 2) = sub_59EE30(v27, fld_e23, fld_e23);  // 三元组块搬移辅助
        sub_504450(pArg2, v27, Blockb);  // 调 搬移插入位后元素
        return sub_5043B0(pArg2, pArg2 + 12 * uArg3, v25);  // 调 在插入位填 n 条
      }
      else
      {
        sub_59EE30(pArg2, fld_e23, pArg2 + 12 * uArg3);  // 三元组块搬移辅助
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 12;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // 读 fld_e25 = this+8（技能槽记录首字）
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);  // 调 填充补足尾段
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // 写 this+8 = fld_e26（技能槽记录首字）
        return sub_5043B0(pArg2, fld_e26 - 12 * uArg3, v25);  // 调 在插入位填 n 条
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);  // 调 v13 = 插入数 + sub_4DA030（当前数）
      v15 = 12 * v13;
      Blocka = (char *)operator new(12 * v13);
      fld_e12 = *(this + 1);  // 读 fld_e12 = this+4（宿主对象指针）
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pArg2, Blocka);  // 结果 = 三元组块搬移辅助
      sub_623C10(v28, uArg3, v25);  // 12 字节元素区间填充
      sub_59EE30(pArg2, *(this + 2), v28 + 12 * uArg3);  // 三元组块搬移辅助
      fld_e13 = *(this + 1);  // 读 fld_e13 = this+4（宿主对象指针）
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 12;  // this+8〔nSkillRec8(推断)〕
      v17 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )  // 判定 “+4 宿主对象指针”
        j__free((void *)*(this + 1));  // 调 堆释放
      *(this + 3) = (int)&Blocka[v15];  // 写 this+12 = (int)&Blocka[v15]（技能槽记录次字）
      *(this + 2) = (int)&Blocka[12 * v17];  // 写 this+8 = (int)&Blocka[12 * v17]（技能槽记录首字）
      *(this + 1) = (int)Blocka;  // 写 this+4 = (int)Blocka（宿主对象指针）
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5F8500 sub_5F8500
// ------------------------------------------------------------
// 调: sub_5F8500 sub_5F8250
uint32_t */*thiscall*/ sub_5F8500(int *this, uint32_t *uArg2, int nArg3, int *Block)  // 实现：调: sub_5F8500 sub_5F8250
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )  // 判定 “+8 技能槽记录首字”
    v6 = (nArg3 - fld_e1) / 12;
  else
    v6 = 0;
  sub_5F8250(this, nArg3, 1u, Block);
  *uArg2 = *(this + 1) + 12 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x5F8570 CNChangeStatus__vmt4
// ------------------------------------------------------------
// 调: sub_4600B0 sub_4E77D0 sub_5E5260
void /*thiscall*/ sub_5F8570(int this)  // 【CNChangeStatus__vmt4】
{
  int fld_60; // eax  | +0x0060 → 状态模式（0x5F8080: switch 3/5/6/7 分派动画组；0x5F8570: ==1/==2 分派）（CNChangeStatus；va=005F8570）
  int *fld_43; // esi
  int fld_643; // ebx  | +0x0064 → 状态件 A（CNChangeStatus；va=005F8570）
  int v5; // edx
  void *v6; // eax
  int *fld_4; // esi
  int v8; // ebx
  int fld_64; // ebx  | +0x0064 → 状态件 A（CNChangeStatus；va=005F8570）
  int pThis2; // edi
  int v11; // edx
  void *v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  void *v18; // eax
  void **v19; // ecx
  int *fld_42; // esi
  int fld_642; // ebx  | +0x0064 → 状态件 A（CNChangeStatus；va=005F8570）
  int pThis3; // edi
  int v23; // edx
  void *v24; // eax
  int v25; // ebx
  int v26; // edi
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int pThis4; // edi
  int v31; // eax
  void *v32; // eax
  int v33; // [esp-14h] [ebp-5Ch]
  int v34; // [esp-14h] [ebp-5Ch]
  int v35; // [esp-14h] [ebp-5Ch]
  int v36; // [esp-10h] [ebp-58h]
  int v37; // [esp-10h] [ebp-58h]
  int v38; // [esp-10h] [ebp-58h]
  int v39; // [esp-Ch] [ebp-54h]
  int v40; // [esp-Ch] [ebp-54h]
  int v41; // [esp-Ch] [ebp-54h]
  void *v42[4]; // [esp+4h] [ebp-44h] BYREF
  void *v43[4]; // [esp+14h] [ebp-34h] BYREF
  uint8_t v44[4]; // [esp+24h] [ebp-24h] BYREF
  void *Block; // [esp+28h] [ebp-20h]
  int v46; // [esp+34h] [ebp-14h]
  int pThis; // [esp+38h] [ebp-10h]
  int v48; // [esp+44h] [ebp-4h]

  pThis = this;
  sub_5F66C0();  // 【IRDAppendage__vmt4】
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4)) == 0 )  // 判定 “+4 宿主对象指针”
  {
    fld_60 = *(uint32_t *)(this + 96);  // 读 fld_60 = this+96（状态模式）
    if ( fld_60 != 1 )
    {
      if ( fld_60 == 2 )
      {
        fld_4 = *(int **)(this + 4);  // this+4 宿主对象指针
        if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*fld_4 + 340))(fld_4) == 60003 && dword_8F7C04 != 0 )  // 虚调用 vt+340
        {
          v8 = (*(int (/*thiscall*/ **)(int *))(*fld_4 + 376))(fld_4);  // 结果 = 虚调用 vt+376
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) != v8 )  // 全局 dword_8F7C04 = 本机角色对象
            return;
        }
        fld_64 = **(uint32_t **)(this + 100);  // this+100 状态件 A
        v46 = (*(int (/*thiscall*/ **)(int *))(*fld_4 + 192))(fld_4);  // 结果 = 虚调用 vt+192
        v40 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*fld_4 + 128))(fld_4, (uint64_t)((double)v46 * -0.5) >> 32)  // 结果 = 虚调用 vt+128
            - (uint64_t)((double)v46 * -0.5);
        v37 = (*(int (/*thiscall*/ **)(int *))(*fld_4 + 124))(fld_4);  // 结果 = 虚调用 vt+124
        pThis2 = pThis;
        v34 = (*(int (/*thiscall*/ **)(int *))(*fld_4 + 120))(fld_4);  // 结果 = 虚调用 vt+120
        (*(void (/*thiscall*/ **)(uint32_t))(fld_64 + 40))(*(uint32_t *)(pThis + 100));  // this+100 状态件 A
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(pThis2 + 100) + 92))(*(uint32_t *)(pThis2 + 100), v44);  // this+100 状态件 A
        v11 = *fld_4;
        v48 = 1;
        v12 = (void *)(*(int (/*thiscall*/ **)(int *))(v11 + 80))(fld_4);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        sub_4600B0(v12, 2, 0, (int)v44);  // 调 演播层注册(槽号)
        v13 = **(uint32_t **)(pThis2 + 104);  // this+104 状态件 B
        v14 = (*(int (/*thiscall*/ **)(int *))(*fld_4 + 128))(fld_4);  // 结果 = 虚调用 vt+128
        v15 = (*(int (/*thiscall*/ **)(int *, int))(*fld_4 + 124))(fld_4, v14);  // 结果 = 虚调用 vt+124
        v16 = (*(int (/*thiscall*/ **)(int *, int))(*fld_4 + 120))(fld_4, v15);  // 结果 = 虚调用 vt+120
        (*(void (/*thiscall*/ **)(uint32_t, int))(v13 + 40))(*(uint32_t *)(pThis2 + 104), v16);  // this+104 状态件 B
        v17 = (*(int (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(pThis2 + 104) + 92))(*(uint32_t *)(pThis2 + 104), v43);  // this+104 状态件 B
        LOBYTE(v48) = 2;  // 调 取 16 位值低 8 位
        sub_4E77D0((int)v44, v17);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
        LOBYTE(v48) = 1;  // 调 取 16 位值低 8 位
        sub_5E5260(v43);  // 调 动画子对象清理临时缓冲
        v18 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(*fld_4 + 80))(fld_4, 2, 0, v44);  // 结果 = 虚调用 vt+80
        sub_4600B0(v18, v34, v37, v40);  // 调 演播层注册(槽号)
        v19 = (void **)v44;
      }
      else
      {
        if ( fld_60 != 4 )
          return;
        fld_42 = *(int **)(this + 4);  // this+4 宿主对象指针
        fld_642 = **(uint32_t **)(this + 100);  // this+100 状态件 A
        v46 = (*(int (/*thiscall*/ **)(int *))(*fld_42 + 192))(fld_42);  // 结果 = 虚调用 vt+192
        v41 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*fld_42 + 128))(fld_42, (uint64_t)((double)v46 * -0.5) >> 32)  // 结果 = 虚调用 vt+128
            - (uint64_t)((double)v46 * -0.5);
        v38 = (*(int (/*thiscall*/ **)(int *))(*fld_42 + 124))(fld_42);  // 结果 = 虚调用 vt+124
        pThis3 = pThis;
        v35 = (*(int (/*thiscall*/ **)(int *))(*fld_42 + 120))(fld_42);  // 结果 = 虚调用 vt+120
        (*(void (/*thiscall*/ **)(uint32_t))(fld_642 + 40))(*(uint32_t *)(pThis + 100));  // this+100 状态件 A
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(pThis3 + 100) + 92))(*(uint32_t *)(pThis3 + 100), v43);  // this+100 状态件 A
        v23 = *fld_42;
        v48 = 3;
        v24 = (void *)(*(int (/*thiscall*/ **)(int *))(v23 + 80))(fld_42);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        sub_4600B0(v24, 2, 0, (int)v43);  // 调 演播层注册(槽号)
        v25 = **(uint32_t **)(pThis3 + 104);  // this+104 状态件 B
        v46 = (*(int (/*thiscall*/ **)(int *))(*fld_42 + 192))(fld_42);  // 结果 = 虚调用 vt+192
        v26 = (uint64_t)((double)v46 * -0.30000001);
        v27 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*fld_42 + 128))(  // 结果 = 虚调用 vt+128
                fld_42,
                (uint64_t)((double)v46 * -0.30000001) >> 32);
        v28 = (*(int (/*thiscall*/ **)(int *, int))(*fld_42 + 124))(fld_42, v27 - v26);  // 结果 = 虚调用 vt+124
        v29 = (*(int (/*thiscall*/ **)(int *, int))(*fld_42 + 120))(fld_42, v28);  // 结果 = 虚调用 vt+120
        pThis4 = pThis;
        (*(void (/*thiscall*/ **)(uint32_t, int))(v25 + 40))(*(uint32_t *)(pThis + 104), v29);  // this+104 状态件 B
        v31 = (*(int (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(pThis4 + 104) + 92))(*(uint32_t *)(pThis4 + 104), v42);  // this+104 状态件 B
        LOBYTE(v48) = 4;  // 调 取 16 位值低 8 位
        sub_4E77D0((int)v43, v31);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
        LOBYTE(v48) = 3;  // 调 取 16 位值低 8 位
        sub_5E5260(v42);  // 调 动画子对象清理临时缓冲
        v32 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(*fld_42 + 80))(fld_42, 2, 0, v43);  // 结果 = 虚调用 vt+80
        sub_4600B0(v32, v35, v38, v41);  // 调 演播层注册(槽号)
        v19 = v43;
      }
      sub_5E5260(v19);  // 调 动画子对象清理临时缓冲
      return;
    }
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 4 || *(uint32_t *)(this + 4) == dword_8F7C04 )  // 全局 dword_8F7A24 = 登录/选区管理器
    {
      fld_43 = *(int **)(this + 4);  // this+4 宿主对象指针
      fld_643 = **(uint32_t **)(this + 100);  // this+100 状态件 A
      v46 = (*(int (/*thiscall*/ **)(int *))(*fld_43 + 192))(fld_43);  // 结果 = 虚调用 vt+192
      v39 = (*(int (/*thiscall*/ **)(int *))(*fld_43 + 128))(fld_43) - (uint64_t)((double)v46 * -0.5);  // 结果 = 虚调用 vt+128
      v36 = (*(int (/*thiscall*/ **)(int *))(*fld_43 + 124))(fld_43);  // 结果 = 虚调用 vt+124
      v33 = (*(int (/*thiscall*/ **)(int *))(*fld_43 + 120))(fld_43);  // 结果 = 虚调用 vt+120
      (*(void (/*thiscall*/ **)(uint32_t))(fld_643 + 40))(*(uint32_t *)(pThis + 100));  // this+100 状态件 A
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(pThis + 100) + 92))(*(uint32_t *)(pThis + 100), v44);  // this+100 状态件 A
      v5 = *fld_43;
      v48 = 0;
      v6 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v5 + 80))(fld_43, 2, 0, v44);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      sub_4600B0(v6, v33, v36, v39);  // 调 演播层注册(槽号)
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
    }
  }
}


// ------------------------------------------------------------
// 0x5F88B0 sub_5F88B0
// ------------------------------------------------------------
// 调: sub_5F88B0 sub_5F8500 sub_623C10
uint32_t */*thiscall*/ sub_5F88B0(int *this, int *Block)  // 实现：调: sub_5F88B0 sub_5F8500 sub_623C10
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 12 )  // 判定 “+12 技能槽记录次字”
    return sub_5F8500(this, &Block, *(this + 2), Block);  // this+8〔nSkillRec8(推断)〕
  fld_e22 = *(this + 2);  // 读 fld_e22 = this+8（技能槽记录首字）
  result = (uint32_t *)sub_623C10(fld_e22, 1, Block);  // 结果 = 12 字节元素区间填充
  *(this + 2) = fld_e22 + 12;  // 写 this+8 = fld_e22 + 12（技能槽记录首字）
  return result;
}



// ------------------------------------------------------------
// 0x5F8930 CNChangeStatus__vmt78
// ------------------------------------------------------------
// 调: sub_5F88B0
uint32_t */*thiscall*/ CNChangeStatus__vmt78(int *this, int nArg2, char pszArg3, int nArg4)  // 实现：调: sub_5F88B0
{
  int Block; // [esp+0h] [ebp-Ch] BYREF
  char pszArg32; // [esp+4h] [ebp-8h]
  int nArg42; // [esp+8h] [ebp-4h]

  pszArg32 = pszArg3;
  Block = nArg2;
  nArg42 = nArg4;
  return sub_5F88B0(this + 20, &Block);  // this+20 频道页号
}



// ------------------------------------------------------------
// 0x5F8960 sub_5F8960
// ------------------------------------------------------------
// 调: sub_5F8960 sub_42AF90 sub_657740
void /*thiscall*/ sub_5F8960(int this)  // 实现：调: sub_5F8960 sub_42AF90 sub_657740
{
  uint32_t *pThis_64; // edi
  int i; // ebx
  unsigned int j; // ebx
  int fld_70; // ecx
  void **v6; // ecx
  void **v7; // [esp+Ch] [ebp-4h]

  pThis_64 = (uint32_t *)(this + 100);  // this+100 插值终点 Y
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
  {
    if ( *pThis_64 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_64)(*pThis_64, 1);
    *pThis_64++ = 0;
  }
  for ( j = 0; ; ++j )
  {
    fld_70 = *(uint32_t *)(this + 112);  // 读 fld_70 = this+112（宿主组件）
    if ( fld_70 == 0 || j >= (*(uint32_t *)(this + 116) - fld_70) >> 2 )  // 判定 “+116 观察者容器”
      break;
    v6 = *(void ***)(fld_70 + 4 * j);
    if ( v6 != nullptr )  // 若 v6 有效（非空）
    {
      v7 = v6;
      sub_42AF90(v6);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v7, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *(uint32_t *)(4 * j + *(uint32_t *)(this + 112)) = 0;  // 涉及字段 “+112 宿主组件”
  }
  if ( *(uint32_t *)(this + 112) != 0 )  // 判定 “+112 宿主组件”
    j__free(*(void **)(this + 112));  // this+112 第 1 组·宿主属性 +46 增量子倍率
  *(uint32_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  *(uint32_t *)(this + 116) = 0;  // 写 this+116 = 0（观察者容器）
  *(uint32_t *)(this + 120) = 0;  // 写 this+120 = 0（动画对象）
}



// ------------------------------------------------------------
// 0x5F8A10 CNChangeStatus__vmt1C
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Particle/AttackPowerUp.p" | "Common/CommonEffect/Particle/PowerSpeedHpUp."
// 调: sub_428F30
void /*usercall*/ sub_5F8A10(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 【CNChangeStatus__vmt1C】
{
  int v3; // eax
  uint32_t *pMem; // eax
  int *v5; // eax
  int v6; // ecx
  int v7; // edx
  uint32_t *pMem2; // eax
  int *v9; // eax
  int v10; // ecx
  int v11; // edx
  uint32_t *pMem3; // eax
  int *v13; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  uint32_t *v17; // eax
  uint32_t *v18; // eax
  int i; // edi
  uint32_t *pMem4; // eax
  int *v21; // eax
  int v22; // ecx
  int v23; // edx
  uint32_t *pMem5; // eax
  int *v25; // eax
  int v26; // ecx
  int v27; // edx
  uint32_t *v28; // eax
  uint32_t *v29; // eax
  uint32_t *v30; // eax
  uint32_t *v31; // eax
  int j; // ebx
  int v33; // edi
  uint32_t *v34; // eax
  uint32_t *v35; // ebx
  int *v36; // ecx
  int v37; // edx
  int v38; // eax
  int *v39; // edi
  int v40; // eax
  int v41; // ebx
  void *v42; // eax
  int v43; // edx
  int v44; // eax
  int v45; // eax
  uint32_t *v46; // edi
  void *v47; // eax
  void *v48; // eax
  int v49; // edi
  void *v50; // ebx
  void *v51; // eax
  void *v52; // eax
  int k; // edi
  int v54; // eax
  int v55; // ecx
  int v56; // eax
  unsigned int v57; // edx
  int v58; // eax
  int m; // edi
  int v60; // [esp-8h] [ebp-28h]
  void *Block[2]; // [esp+8h] [ebp-18h] BYREF
  uint32_t *v62; // [esp+10h] [ebp-10h] BYREF
  int v63; // [esp+1Ch] [ebp-4h]

  v3 = pDwArg1[24];
  switch ( v3 )  // 按 v3 分派
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( pDwArg1[25] == 0 )
      {
        pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
        Block[0] = pMem;
        v63 = 0;
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          v5 = sub_428F30(pMem, (int)"Common/CommonEffect/Particle/AttackPowerUp.ptl", pDwArg1[1]);  // 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
        else
          v5 = nullptr;
        v6 = pDwArg1[1];
        pDwArg1[25] = (int)v5;
        v7 = *v5;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v7 + 112))(v5, v6);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[25] + 12))(pDwArg1[25], 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      if ( pDwArg1[25] == 0 )
      {
        pMem2 = operator new(0x12Cu);  // 堆分配 300 字节对象
        Block[0] = pMem2;
        v63 = 1;
        if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
          v9 = sub_428F30(pMem2, (int)"Common/CommonEffect/Particle/PowerSpeedHpUp.ptl", pDwArg1[1]);  // 字符串 “Common/CommonEffect/Particle/PowerSpeedHpUp.”
        else
          v9 = nullptr;
        v10 = pDwArg1[1];
        pDwArg1[25] = (int)v9;
        v11 = *v9;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v11 + 112))(v9, v10);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
        pMem3 = operator new(0x12Cu);  // 堆分配 300 字节对象
        Block[0] = pMem3;
        v63 = 2;
        if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
          v13 = sub_428F30(pMem3, (int)"Character/Gunner/Effect/Particle/Robotics.ptl", pDwArg1[1]);  // 字符串 “Character/Gunner/Effect/Particle/Robotics.pt”
        else
          v13 = nullptr;
        v14 = pDwArg1[1];
        pDwArg1[26] = (int)v13;
        v15 = *v13;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v15 + 112))(v13, v14);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[25] + 12))(pDwArg1[25], 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[26] + 12))(pDwArg1[26], 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[1] + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        pDwArg1[1],
        "POWER_UP",  // 字符串 “POWER_UP”
        -1,
        0,
        0);
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      v16 = pDwArg1[28];
      if ( v16 == 0 || (pDwArg1[29] - v16) >> 2 == 0 )  // 向量元素数 = (end−begin)/4
      {
        v63 = 3;
        if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
          v17 = (uint32_t *)sub_431860((char)"Character/Mage/Effect/Animation/MpRegenRateUpStart.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/MpRegenRateU”
        else
          v17 = nullptr;
        v62 = v17;
        v63 = -1;
        sub_42ABE0(&v62);  // 向量尾插（含扩容）
        Block[0] = (void *)sub_42FCB0(228);  // 结果 = CRT 一次性初始化
        v63 = 4;
        if ( Block[0] != nullptr )
          v18 = (uint32_t *)sub_431860((char)"Character/Mage/Effect/Animation/MpRegenRateUpLoop.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/MpRegenRateU”
        else
          v18 = nullptr;
        v63 = -1;
        v62 = v18;
        sub_42ABE0(&v62);  // 向量尾插（含扩容）
      }
      for ( i = 0; i < 8; i += 4 )
        sub_4926A0(*(uint32_t *)(pDwArg1[28] + i));  // 帧游标复位（+44 帧数组；递归子链 +204）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( pDwArg1[25] == 0 )
      {
        pMem4 = operator new(0x12Cu);  // 堆分配 300 字节对象
        Block[0] = pMem4;
        v63 = 5;
        if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
          v21 = sub_428F30(pMem4, (int)"Character/Mage/Effect/Particle/MagicalTempoUp1.ptl", pDwArg1[1]);  // 字符串 “Character/Mage/Effect/Particle/MagicalTempoU”
        else
          v21 = nullptr;
        v22 = pDwArg1[1];
        pDwArg1[25] = (int)v21;
        v23 = *v21;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int, int))(v23 + 112))(v21, v22, nArg2);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
        pMem5 = operator new(0x12Cu);  // 堆分配 300 字节对象
        Block[0] = pMem5;
        v63 = 6;
        if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
          v25 = sub_428F30(pMem5, (int)"Character/Mage/Effect/Particle/MagicalTempoUp2.ptl", pDwArg1[1]);  // 字符串 “Character/Mage/Effect/Particle/MagicalTempoU”
        else
          v25 = nullptr;
        v26 = pDwArg1[1];
        pDwArg1[26] = (int)v25;
        v27 = *v25;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v27 + 112))(v25, v26);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[25] + 12))(pDwArg1[25], 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[26] + 12))(pDwArg1[26], 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[1] + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        pDwArg1[1],
        "BUFF_SHOWTIME_LOOP",  // 字符串 “BUFF_SHOWTIME_LOOP”
        6,
        0,
        0);
      break;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( (uint8_t)sub_484F10(pDwArg1 + 27) != 0 )  // 32 字节对象列表空判定（+4 为 0 或元素数 0）
      {
        v63 = 7;
        if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
          v28 = (uint32_t *)sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashUnderStart.ani", 1);  // 字符串 “Character/Swordman/Effect/Animation/MindFlas”
        else
          v28 = nullptr;
        v62 = v28;
        v63 = -1;
        sub_42ABE0(&v62);  // 向量尾插（含扩容）
        Block[0] = (void *)sub_42FCB0(228);  // 结果 = CRT 一次性初始化
        v63 = 8;
        if ( Block[0] != nullptr )
          v29 = (uint32_t *)sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashOverStart.ani", 1);  // 字符串 “Character/Swordman/Effect/Animation/MindFlas”
        else
          v29 = nullptr;
        v63 = -1;
        v62 = v29;
        sub_42ABE0(&v62);  // 向量尾插（含扩容）
        Block[0] = (void *)sub_42FCB0(228);  // 结果 = CRT 一次性初始化
        v63 = 9;
        if ( Block[0] != nullptr )
          v30 = (uint32_t *)sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashUnderLoop.ani", 1);  // 字符串 “Character/Swordman/Effect/Animation/MindFlas”
        else
          v30 = nullptr;
        v63 = -1;
        v62 = v30;
        sub_42ABE0(&v62);  // 向量尾插（含扩容）
        Block[0] = (void *)sub_42FCB0(228);  // 结果 = CRT 一次性初始化
        v63 = 10;
        if ( Block[0] != nullptr )
          v31 = (uint32_t *)sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashOverLoop.ani", 1);  // 字符串 “Character/Swordman/Effect/Animation/MindFlas”
        else
          v31 = nullptr;
        v62 = v31;
        v63 = -1;
        sub_42ABE0(&v62);  // 向量尾插（含扩容）
      }
      for ( j = 0; j < 16; j += 4 )
        sub_4926A0(*(uint32_t *)(j + pDwArg1[28]));  // 帧游标复位（+44 帧数组；递归子链 +204）
      Block[0] = (void *)sub_42FCB0(228);  // 结果 = CRT 一次性初始化
      v63 = 11;
      if ( Block[0] != nullptr )
        v33 = sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashHead.ani", 1);  // 字符串 “Character/Swordman/Effect/Animation/MindFlas”
      else
        v33 = 0;
      v63 = -1;
      v34 = (uint32_t *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      v35 = v34;
      Block[0] = v34;
      v63 = 12;
      if ( v34 != nullptr )  // 若 v34 有效（非空）
      {
        sub_44E0D0((char *)v34, v33, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *v35 = &CNRDPooledObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
      }
      else
      {
        v35 = nullptr;
      }
      v36 = (int *)pDwArg1[1];
      v37 = *v36;
      v62 = v35;
      v63 = -1;
      v38 = (*(int (/*thiscall*/ **)(int *))(v37 + 80))(v36);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      sub_45FE80(v38, v33, 2, 0, (int)v35, 0, 0);  // 调 对象注册
      v39 = (int *)pDwArg1[1];
      v40 = *v39;
      v41 = *v35;
      Block[0] = v39;
      v42 = (void *)(*(int (/*thiscall*/ **)(int *))(v40 + 128))(v39);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      v43 = *v39;
      Block[1] = v42;
      v60 = (int)v42 + (*(int (/*thiscall*/ **)(int *))(v43 + 192))(v39) + 10;  // 虚函数调用 槽+192
      v44 = (*(int (/*thiscall*/ **)(int *))(*v39 + 124))(v39);  // 结果 = 虚调用 vt+124
      v45 = (*(int (/*thiscall*/ **)(int *, int))(*v39 + 120))(v39, v44 + 1);  // 结果 = 虚调用 vt+120
      v46 = v62;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v41 + 112))(v62, v45);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v46 + 60))(v46, pDwArg1[1]);  // 虚调用 vt+60
      sub_4A06D0(v60);  // 调 绑定目标对象并记录相对偏移
      break;
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      if ( (uint8_t)sub_484F10(pDwArg1 + 27) != 0 )  // 32 字节对象列表空判定（+4 为 0 或元素数 0）
      {
        v63 = 13;
        if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
          v47 = (void *)sub_431860((char)"Character/Mage/Effect/Animation/ProvocationDollBuff1.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/ProvocationD”
        else
          v47 = nullptr;
        Block[0] = v47;
        v63 = -1;
        sub_42ABE0(Block);  // 向量尾插（含扩容）
        Block[0] = (void *)sub_42FCB0(228);  // 结果 = CRT 一次性初始化
        v63 = 14;
        if ( Block[0] != nullptr )
          v48 = (void *)sub_431860((char)"Character/Mage/Effect/Animation/ProvocationDollBuff2.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/ProvocationD”
        else
          v48 = nullptr;
        v63 = -1;
        Block[0] = v48;
        sub_42ABE0(Block);  // 向量尾插（含扩容）
      }
      v49 = 0;
      *(float *)Block = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1] + 192))(pDwArg1[1]) * 0.0049999999;  // 虚函数调用 槽+192
      v50 = Block[0];
      do
      {
        sub_4926A0(*(uint32_t *)(pDwArg1[28] + v49));  // 帧游标复位（+44 帧数组；递归子链 +204）
        sub_4920E0(*(uint32_t **)(pDwArg1[28] + v49), *(float *)&v50, *(float *)&v50);  // 调 批量改写全帧缩放
        v49 += 4;
      }
      while ( v49 < 8 );
      break;
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      if ( (uint8_t)sub_484F10(pDwArg1 + 27) != 0 )  // 32 字节对象列表空判定（+4 为 0 或元素数 0）
      {
        v63 = 15;
        if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
          v51 = (void *)sub_431860((char)"Character/Mage/Effect/Animation/SummonMonsterAura1.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/SummonMonste”
        else
          v51 = nullptr;
        Block[0] = v51;
        v63 = -1;
        sub_42ABE0(Block);  // 向量尾插（含扩容）
        Block[0] = (void *)sub_42FCB0(228);  // 结果 = CRT 一次性初始化
        v63 = 16;
        if ( Block[0] != nullptr )
          v52 = (void *)sub_431860((char)"Character/Mage/Effect/Animation/SummonMonsterAura2.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/SummonMonste”
        else
          v52 = nullptr;
        v63 = -1;
        Block[0] = v52;
        sub_42ABE0(Block);  // 向量尾插（含扩容）
      }
      for ( k = 0; k < 8; k += 4 )
        sub_4926A0(*(uint32_t *)(pDwArg1[28] + k));  // 帧游标复位（+44 帧数组；递归子链 +204）
      break;
    default:
      break;
  }
  v54 = pDwArg1[21];
  if ( v54 != 0 )
  {
    Block[0] = (void *)((pDwArg1[22] - v54) / 12);
    if ( Block[0] != nullptr )
    {
      v55 = *(uint32_t *)pDwArg1[21];
      if ( v55 == 12 || v55 == 13 )  // 若 v55 == 12 与/或 v55 == 13
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[1] + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          pDwArg1[1],
          "CRITICAL_UP",  // 字符串 “CRITICAL_UP”
          -1,
          0,
          0);
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1] + 308))(pDwArg1[1]) != 0 )  // 虚函数调用 槽+308
  {
    v56 = pDwArg1[21];
    if ( v56 != 0 )
    {
      v57 = (int)((uint64_t)(715827883LL * (pDwArg1[22] - v56)) >> 32) >> 1;
      Block[0] = (void *)((pDwArg1[22] - v56) / 12);
      if ( v57 + (v57 >> 31) != 0 )
      {
        v58 = pDwArg1[21];
        if ( *(uint32_t *)v58 == 21 && *(uint8_t *)(v58 + 4) == 0 && *(float *)(v58 + 8) >= 100.0 )
        {
          for ( m = 0; m < 17; ++m )  // 循环：m 从 0 递增到 17
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[1] + 776))(pDwArg1[1], m) != 0  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
              && sub_496F80(m) != 16 )  // 状态号映射表（12 直通、15→14、16→15，其余→16）
            {
              (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)pDwArg1[1] + 764))(pDwArg1[1], m, 0, pDwArg1[9], 0);  // 虚函数调用 槽+764
            }
          }
        }
      }
    }
  }
}


// ------------------------------------------------------------
// 0x5F9170 CNBulletBuff__vmt1C
// ------------------------------------------------------------
// 调: sub_47EF20
int /*thiscall*/ CNBulletBuff__vmt1C(int *this)  // 实现：调: sub_47EF20
{
  uint32_t *fld_e20; // ecx
  int result; // eax

  fld_e20 = (uint32_t *)*(this + 20);  // this+20 频道页号
  if ( fld_e20 != nullptr )  // 若 fld_e20 有效（非空）
  {
    result = *(this + 22) + sub_47EF20(fld_e20, 0, *(this + 21), -1, -1, 11);  // 调 读攻击数据表
    *(this + 23) = result;  // this+92〔pFxObjC(推断)〕
    *(this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  }
  else
  {
    off_77F3FC(aCriticalError_42);  // 读 off_77F3FC（引擎日志输出函数）
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);  // 虚调用 vt+76
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F91C0 CNBulletBuff__vmt88
// ------------------------------------------------------------
// 调: sub_699000
char /*thiscall*/ CNBulletBuff__vmt88(uint32_t *this)  // 实现：调: sub_699000
{
  if ( (int)*(this + 23) <= 0 || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 80))(this) == 0 )  // 虚调用 vt+80
    return 0;
  if ( (*(this + 23))-- == 1 )  // this+92〔pFxObjC(推断)〕
    *(this + 11) = sub_699000((int)(this + 2)) + 1200;  // clock_now(clk)
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x5F91F0 sub_5F91F0
// ------------------------------------------------------------
// 调: sub_5F91F0
int /*thiscall*/ sub_5F91F0(int this)  // 实现：调: sub_5F91F0
{
  *(uint32_t *)(this + 80) = 0;  // this+80 关联角色对象
  *(uint32_t *)(this + 84) = -1;  // this+84 插值起点 X
  *(uint8_t *)(this + 88) = 0;  // this+88 插值起点 Y
  return 0;
}



// ------------------------------------------------------------
// 0x5F9200 CNTrodden__vmt1C
// ------------------------------------------------------------
// 证: 叶子函数（21 行，无外调无字符串）
int /*thiscall*/ CNTrodden__vmt1C(int this)  // 实现：证: 叶子函数（21 行，无外调无字符串）
{
  int fld_4; // ecx  | +0x0004 → 宿主对象指针（CNTrodden；va=005F9200）
  int result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
  *(uint32_t *)(this + 84) = -1;  // 写 this+84 = -1（踏地侧/哨兵）
  *(uint8_t *)(this + 88) = 0;  // 写 this+88 = 0（踏地标志）
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_4 + 776))(fld_4, 3);  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 0);  // 涉及字段 “+4 宿主对象指针”
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 768))(  // this+4 宿主对象指针
      *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
      3,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 1);  // 涉及字段 “+4 宿主对象指针”
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F9250 CNTrodden__vmt20
// ------------------------------------------------------------
// 证: 叶子函数（14 行，无外调无字符串）
char /*thiscall*/ CNTrodden__vmt20(uint32_t *this, char pszArg2)  // 函数定义: 设置坐标三元组 (this+100..112)
{
  char result; // al
  int fld_e1; // esi  | +0x0004 → 宿主对象指针（CNTrodden；va=005F9200）

  result = pszArg2;
  if ( pszArg2 == 0 )
  {
    fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)fld_e1 + 612))(fld_e1, 0, 0);  // 虚函数调用 槽+612：帧时刻覆盖开关（this+642 标志 / this+644 时刻）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1 + 820))(fld_e1, 1);  // 虚函数调用 槽+820：写 +6740 字节
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F9280 CNTrodden__vmt10
// ------------------------------------------------------------
// 证: "DOWN_HEAVY" | "DOWN_MIDDLE" | "DOWN_LIGHT" | "STEP_ON"
// 调: sub_432E50 sub_4938F0 sub_42FC90 sub_4AECE0 sub_4B0D20
uint32_t */*usercall*/ sub_5F9280@<eax>(int pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)  // 实现：调: sub_432E50 sub_4938F0 sub_42FC90 sub_4AECE0 sub_4B0D20
{
  uint32_t *result; // eax
  int *v5; // esi
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edx
  int v12; // edi
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // edi
  int v17; // eax
  void *v18; // edi
  int v19; // eax
  void *v20; // eax
  int v21; // eax
  int v22; // eax
  int v25; // [esp+0h] [ebp-Ch]
  int v26; // [esp+0h] [ebp-Ch]
  int v27; // [esp+4h] [ebp-8h]
  int v28; // [esp+8h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 840))(*(uint32_t *)(pArg1 + 80));  // 虚函数调用 槽+840：大状态 getter（this+6556）
  if ( result == (uint32_t *)18 )
  {
    v5 = *(int **)(pArg1 + 4);  // pArg1+4〔pHostObj〕
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);  // 结果 = 虚调用 vt+840
    if ( result == (uint32_t *)9 )
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 200))(*(uint32_t *)(pArg1 + 80));  // 虚函数调用 槽+200：取动画对象
      v27 = (int)result;
      if ( result != nullptr )  // 若 result 有效（非空）
      {
        v6 = *v5;
        v7 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80), nArg2, nArg3);  // 虚函数调用 槽+152：效果通道 3
        v8 = sub_432E50(v7);  // 结果 = 关系码对调映射
        (*(void (/*thiscall*/ **)(int *, int))(v6 + 144))(v5, v8);  // 虚函数调用 槽+144：槽（13 行）
        if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 236))(v5) == 1 )  // 虚调用 vt+236
          (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);  // 虚调用 vt+228
        sub_4938F0(v27);  // 调 调 sub_4938F0
        v9 = *(uint32_t *)(v27 + 148);
        v28 = v9;
        if ( v9 != *(uint32_t *)(pArg1 + 84) )  // pArg1+84〔nTroddenSide〕
        {
          if ( v9 > 2 )
          {
            v18 = *(void **)((*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5) + 20);  // 结果 = 虚调用 vt+688
            if ( (void *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5) != v18 )  // 虚调用 vt+200
              (*(void (/*thiscall*/ **)(int *, void *))(*v5 + 196))(v5, v18);  // 虚调用 vt+196
            if ( v28 == 10 )
              v19 = (*(int (/*thiscall*/ **)(int *))(*v5 + 912))(v5);  // 结果 = 虚调用 vt+912
            else
              v19 = sub_42FC90(v27) - 1;  // 结果 = 88B 元素计数（+44 组）
            sub_4AECE0(v18, v19);  // 调 切武器动画
            if ( *(uint8_t *)(pArg1 + 88) == 0 )  // pArg1+88〔bTroddenFlag〕
            {
              v20 = (void *)(*(int (/*thiscall*/ **)(int *, int))(*v5 + 672))(v5, 3);  // 结果 = 虚调用 vt+672
              v21 = sub_4B0D20(v20);  // 结果 = 双字段乘积取值
              v28 = 0;
              v25 = -1;
              if ( v21 > 60000 )
              {
                if ( v21 > 100000 )
                  (*(void (/*thiscall*/ **)(int *, const char *))(*v5 + 212))(v5, "DOWN_HEAVY");  // 字符串 “DOWN_HEAVY”
                else
                  (*(void (/*thiscall*/ **)(int *, const char *))(*v5 + 212))(v5, "DOWN_MIDDLE");  // 字符串 “DOWN_MIDDLE”
              }
              else
              {
                (*(void (/*thiscall*/ **)(int *, const char *))(*v5 + 212))(v5, "DOWN_LIGHT");  // 字符串 “DOWN_LIGHT”
              }
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*v5 + 212))(v5, "STEP_ON", -1, 0, 0);  // 字符串 “STEP_ON”
              *(uint8_t *)(pArg1 + 88) = 1;  // pArg1+88〔bTroddenFlag〕
            }
          }
          else
          {
            v10 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);  // 结果 = 虚调用 vt+688
            v11 = *v5;
            if ( *(uint32_t *)(v10 + 16) != 0 )
            {
              v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 688))(v5);  // 虚函数调用 槽+688：附加块基址 this+6160
              if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5) != *(uint32_t *)(v12 + 16) )  // 虚调用 vt+200
              {
                v13 = *v5;
                v14 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);  // 结果 = 虚调用 vt+688
                (*(void (/*thiscall*/ **)(int *, uint32_t))(v13 + 196))(v5, *(uint32_t *)(v14 + 16));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
              }
            }
            else if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v11 + 688))(v5) + 12) != 0 )  // 虚函数调用 槽+688：附加块基址 this+6160
            {
              v15 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);  // 结果 = 虚调用 vt+688
              if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5) != *(uint32_t *)(v15 + 12) )  // 虚调用 vt+200
              {
                v16 = *v5;
                v17 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);  // 结果 = 虚调用 vt+688
                (*(void (/*thiscall*/ **)(int *, uint32_t))(v16 + 196))(v5, *(uint32_t *)(v17 + 12));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
              }
            }
          }
          *(uint32_t *)(pArg1 + 84) = v28;  // pArg1+84〔nTroddenSide〕
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80), v25);  // 虚函数调用 槽+152：效果通道 3
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 120))(*(uint32_t *)(pArg1 + 80));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 80) + 124))(*(uint32_t *)(pArg1 + 80), v26);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        (*(void (/*thiscall*/ **)(int *))(*v5 + 112))(v5);  // 虚调用 vt+112
        (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);  // 虚调用 vt+612
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);  // 虚调用 vt+820
        result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);  // 结果 = 虚调用 vt+200
        if ( result != nullptr )  // 若 result 有效（非空）
        {
          v22 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);  // 结果 = 虚调用 vt+200
          return sub_4938F0(v22);  // 调 调 sub_4938F0
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5F9510 sub_5F9510
// ------------------------------------------------------------
// 调: sub_5F9510
int /*thiscall*/ sub_5F9510(int this)  // 实现：调: sub_5F9510
{
  *(uint32_t *)(this + 80) = 0;  // this+80 关联角色对象
  *(uint32_t *)(this + 84) = 0;  // this+84 插值起点 X
  *(uint32_t *)(this + 96) = 0;  // this+96 插值终点 X / 落点偏移
  *(uint32_t *)(this + 88) = 0;  // this+88 插值起点 Y
  *(uint32_t *)(this + 100) = 0;  // this+100 插值终点 Y
  *(uint32_t *)(this + 92) = 0;  // this+92 插值起点 Z
  *(uint32_t *)(this + 104) = 0;  // this+104 插值终点 Z
  *(uint8_t *)(this + 136) = 0;  // this+136 演出已播标志
  return 0;
}



// ------------------------------------------------------------
// 0x5F9530 CNAerialGatlinged__vmt10
// ------------------------------------------------------------
// 调: sub_432E50 sub_699000 sub_4049C0 sub_423AB0 sub_4049F0
int /*thiscall*/ sub_5F9530(int this)  // 【CNAerialGatlinged__vmt10】
{
  int *fld_4; // ebx
  int v3; // edi
  int fld_50; // eax  | +0x0050 → 关联角色对象（CNAerialGatlinged；va=005F9530）
  int v5; // eax
  int pThis_8; // edi
  int fld_5C2; // eax  | +0x005C → 插值起点 Z（证据: va=005F9530）（CNAerialGatlinged；va=005F9530）
  double v8; // st7
  int fld_68; // eax  | +0x0068 → 插值终点 Z（vmt4：*(this+104) + 宿主 y + 高/2）（证据: va=005F9970）（CNAerialGatlinged；va=005F9970）
  uint64_t v10; // rax
  int v11; // edi
  int v12; // edi
  int fld_502; // ecx  | +0x0050 → 关联角色对象（CNAerialGatlinged；va=005F9530）
  int v14; // esi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  float v19; // [esp+10h] [ebp-30h]
  float v20; // [esp+14h] [ebp-2Ch]
  float v21; // [esp+14h] [ebp-2Ch]
  float fld_602; // [esp+14h] [ebp-2Ch]  | +0x0060 → 插值终点 X / 落点偏移（CNAerialGatlinged；va=005F9970）
  float fld_642; // [esp+14h] [ebp-2Ch]  | +0x0064 → 插值终点 Y（证据: va=005F9530）（CNAerialGatlinged；va=005F9530）
  float fld_682; // [esp+14h] [ebp-2Ch]  | +0x0068 → 插值终点 Z（vmt4：*(this+104) + 宿主 y + 高/2）（证据: va=005F9970）（CNAerialGatlinged；va=005F9970）
  float fld_542; // [esp+18h] [ebp-28h]  | +0x0054 → 插值起点 X（CNAerialGatlinged；va=005F9530）
  float fld_582; // [esp+18h] [ebp-28h]  | +0x0058 → 插值起点 Y（证据: va=005F9530）（CNAerialGatlinged；va=005F9530）
  float fld_60; // [esp+18h] [ebp-28h]  | +0x0060 → 插值终点 X / 落点偏移（CNAerialGatlinged；va=005F9970）
  float fld_64; // [esp+18h] [ebp-28h]  | +0x0064 → 插值终点 Y（证据: va=005F9530）（CNAerialGatlinged；va=005F9530）
  float fld_54; // [esp+18h] [ebp-28h]  | +0x0054 → 插值起点 X（CNAerialGatlinged；va=005F9530）
  float fld_58; // [esp+18h] [ebp-28h]  | +0x0058 → 插值起点 Y（证据: va=005F9530）（CNAerialGatlinged；va=005F9530）
  float fld_5C; // [esp+18h] [ebp-28h]  | +0x005C → 插值起点 Z（证据: va=005F9530）（CNAerialGatlinged；va=005F9530）
  int pObj; // [esp+30h] [ebp-10h]
  int pObj2; // [esp+34h] [ebp-Ch]
  int v34; // [esp+38h] [ebp-8h]
  int v35; // [esp+3Ch] [ebp-4h]

  fld_4 = *(int **)(this + 4);  // this+4 宿主对象
  v3 = *fld_4;
  fld_50 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80));  // this+80 关联角色对象
  v5 = sub_432E50(fld_50);  // 结果 = 关系码对调映射
  (*(void (/*thiscall*/ **)(int *, int))(v3 + 144))(fld_4, v5);  // 虚函数调用 槽+144：槽（13 行）
  if ( (*(int (/*thiscall*/ **)(int *))(*fld_4 + 236))(fld_4) == 1 )  // 虚调用 vt+236
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*fld_4 + 228))(fld_4, 0, -1, 0);  // 虚调用 vt+228
  if ( (*(int (/*thiscall*/ **)(int *))(*fld_4 + 236))(fld_4) == 0 )  // 虚调用 vt+236
  {
    pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
    if ( *(uint8_t *)(*(uint32_t *)(this + 80) + 9368) != 0 )  // 判定 “+80 关联角色对象”
    {
      if ( pThis_8 < 610 )
      {
        fld_60 = (float)*(int *)(this + 96);  // this+96 插值终点 X / 落点偏移
        v35 = (uint64_t)sub_4049C0(0.0, fld_60, pThis_8, 610);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        fld_64 = (float)*(int *)(this + 100);  // this+100 插值终点 Y
        v34 = (uint64_t)sub_4049C0(0.0, fld_64, pThis_8, 610);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        fld_68 = *(uint32_t *)(this + 104);  // 读 fld_68 = this+104（插值终点 Z）
        if ( pThis_8 >= 410 )
          LODWORD(v10) = sub_423AB0(fld_68 + 50, fld_68, pThis_8 - 410, 200, 0);  // 区间插值取整（sub_4049F0 版）
        else
          LODWORD(v10) = sub_423AB0(0, fld_68 + 50, pThis_8, 410, 1);  // 区间插值取整（sub_4049F0 版）
        goto LABEL_14;
      }
      v11 = pThis_8 - 610;
      fld_54 = (float)*(int *)(this + 84);  // this+84 插值起点 X
      fld_602 = (float)*(int *)(this + 96);  // this+96 插值终点 X / 落点偏移
      v35 = (uint64_t)sub_4049C0(fld_602, fld_54, v11, 40);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      fld_58 = (float)*(int *)(this + 88);  // this+88 插值起点 Y
      fld_642 = (float)*(int *)(this + 100);  // this+100 插值终点 Y
      v34 = (uint64_t)sub_4049C0(fld_642, fld_58, v11, 40);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      fld_5C = (float)*(int *)(this + 92);  // this+92 插值起点 Z
      fld_682 = (float)*(int *)(this + 104);  // this+104 插值终点 Z
      v8 = sub_4049C0(fld_682, fld_5C, v11, 40);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    }
    else
    {
      fld_542 = (float)*(int *)(this + 84);  // this+84 插值起点 X
      v35 = (uint64_t)sub_4049C0(0.0, fld_542, pThis_8, 850);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      fld_582 = (float)*(int *)(this + 88);  // this+88 插值起点 Y
      v34 = (uint64_t)sub_4049C0(0.0, fld_582, pThis_8, 850);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      fld_5C2 = *(uint32_t *)(this + 92);  // 读 fld_5C2 = this+92（插值起点 Z）
      if ( pThis_8 >= 600 )
      {
        v21 = (float)fld_5C2;
        v8 = (double)(fld_5C2 + 40);
        v19 = v8;
        sub_4049F0(v19, v21, pThis_8 - 600, 250, 0);  // 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正
      }
      else
      {
        v8 = (double)(fld_5C2 + 40);
        v20 = v8;
        sub_4049F0(0.0, v20, pThis_8, 600, 1);  // 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正
      }
    }
    v10 = (uint64_t)v8;
LABEL_14:
    v12 = v10;
    if ( *(uint8_t *)(this + 120) != 0 && sub_699000(this + 108) <= 50 )  // 【clock_now(clk)】
    {
      v35 += (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80)) != 0 ? 1 : -1;  // this+80 关联角色对象
      ++v12;
    }
    fld_502 = *(uint32_t *)(this + 80);  // 读 fld_502 = this+80（关联角色对象）
    v14 = *fld_4;
    pObj = fld_502;
    pObj2 = fld_502;
    v15 = (*(int (**)(void))(*(uint32_t *)fld_502 + 128))();  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 124))(pObj, v12 + v15);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v34 + v16);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    (*(void (/*thiscall*/ **)(int *, int))(v14 + 112))(fld_4, v35 + v17);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  }
  (*(void (/*thiscall*/ **)(int *, int, int))(*fld_4 + 612))(fld_4, 1, 1);  // 虚调用 vt+612
  return (*(int (/*thiscall*/ **)(int *, uint32_t))(*fld_4 + 820))(fld_4, 0);  // 虚调用 vt+820
}


// ------------------------------------------------------------
// 0x5F9810 CNAerialGatlinged__vmt1C
// ------------------------------------------------------------
// 证: "LIFT_UP"
// 调: sub_699070
int /*thiscall*/ CNAerialGatlinged__vmt1C(int this)  // 实现：调: sub_699070
{
  int *fld_4; // edi
  int v3; // ebx
  int v4; // eax
  int fld_58; // eax  | +0x0058 → 插值起点 Y（证据: va=005F9530）（CNAerialGatlinged；va=005F9530）
  char fld_54; // al  | +0x0054 → 插值起点 X（CNAerialGatlinged；va=005F9530）
  uint8_t *fld_502; // ecx
  int v8; // eax
  int fld_503; // edx  | +0x0050 → 关联角色对象（CNAerialGatlinged；va=005F9530）
  int fld_50; // [esp+Ch] [ebp-4h]  | +0x0050 → 关联角色对象（CNAerialGatlinged；va=005F9530）

  sub_699070(this + 8, 1u);  // 【clock_bind_domain(clk, newDomainId)】
  fld_4 = *(int **)(this + 4);  // this+4 宿主对象
  *(uint32_t *)(this + 84) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80)) != 0  // this+84 插值起点 X
                         ? 214
                         : -214;
  *(uint32_t *)(this + 88) = 0;  // 写 this+88 = 0（插值起点 Y）
  *(uint32_t *)(this + 92) = 220 - (*(int (/*thiscall*/ **)(int *))(*fld_4 + 192))(fld_4) / 2;  // 虚调用 vt+192
  v3 = *fld_4;
  fld_50 = *(uint32_t *)(this + 80);  // 读 fld_50 = this+80（关联角色对象）
  v4 = (*(int (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_50 + 124))(0);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  fld_58 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_50 + 120))(fld_50, *(uint32_t *)(this + 88) + v4);  // this+88 插值起点 Y
  fld_54 = (*(int (/*thiscall*/ **)(int *, int))(v3 + 136))(fld_4, *(uint32_t *)(this + 84) + fld_58);  // this+84 插值起点 X
  fld_502 = *(uint8_t **)(this + 80);  // this+80 关联角色对象
  if ( fld_54 != 0 )
  {
    fld_502[9368] = 0;
  }
  else
  {
    *(uint32_t *)(this + 96) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)fld_502 + 152))(fld_502) != 0 ? 128 : -128;  // 写 this+96 = (*(int (／*thiscall*／ **)(uint8_t *))(*(uint32_t *)fld_502 + 152))(fld_502) != 0 ? 128 : -128（插值终点 X / 落点偏移）
    *(uint32_t *)(this + 100) = -1;  // 写 this+100 = -1（插值终点 Y）
    *(uint32_t *)(this + 104) = 188 - (*(int (/*thiscall*/ **)(int *))(*fld_4 + 192))(fld_4) / 2;  // 虚调用 vt+192
    *(uint32_t *)(this + 84) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80)) != 0  // this+84 插值起点 X
                           ? 150
                           : -150;
    *(uint32_t *)(this + 88) = *(uint32_t *)(this + 100);  // 写 this+88 = *(uint32_t *)(this + 100)（插值起点 Y）
    v8 = (*(int (/*thiscall*/ **)(int *))(*fld_4 + 192))(fld_4);  // 结果 = 虚调用 vt+192
    fld_503 = *(uint32_t *)(this + 80);  // 读 fld_503 = this+80（关联角色对象）
    *(uint32_t *)(this + 92) = 155 - v8 / 2;  // 写 this+92 = 155 - v8 / 2（插值起点 Z）
    *(uint8_t *)(fld_503 + 9368) = 1;
  }
  *(uint8_t *)(this + 120) = 0;  // 写 this+120 = 0（近段修正门字节）
  *(uint8_t *)(this + 136) = 0;  // 写 this+136 = 0（演出已播标志）
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*fld_4 + 776))(fld_4, 3) != 0 )  // 虚调用 vt+776
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*fld_4 + 556))(fld_4, 0);  // 虚调用 vt+556
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t))(*fld_4 + 768))(fld_4, 3, 0, 0);  // 虚调用 vt+768
    (*(void (/*thiscall*/ **)(int *, int))(*fld_4 + 556))(fld_4, 1);  // 虚调用 vt+556
  }
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*fld_4 + 212))(fld_4, "LIFT_UP", -1, 0, 0);  // 字符串 “LIFT_UP”
}



// ------------------------------------------------------------
// 0x5F9970 CNAerialGatlinged__vmt4
// ------------------------------------------------------------
// 证: "Common/HitEffect/Animation/KnockSmall.ani" | "BBQ_STUCK"
// 调: sub_699000 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E1F0
char /*thiscall*/ CNAerialGatlinged__vmt4(int this)  // 实现：调: sub_699000 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E1F0
{
  int fld_50; // eax  | +0x0050 → 关联角色对象（CNAerialGatlinged；va=005F9530）
  int fld_4; // esi  | +0x0004 → 宿主对象（CNAerialGatlinged；va=005F9970）
  int v4; // eax
  int v5; // edi
  char *v6; // eax
  char *v7; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int fld_503; // ebx  | +0x0050 → 关联角色对象（CNAerialGatlinged；va=005F9530）
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int fld_502; // [esp-10h] [ebp-30h]  | +0x0050 → 关联角色对象（CNAerialGatlinged；va=005F9530）
  int fld_68; // [esp-Ch] [ebp-2Ch]  | +0x0068 → 插值终点 Z（vmt4：*(this+104) + 宿主 y + 高/2）（证据: va=005F9970）（CNAerialGatlinged；va=005F9970）
  int v18; // [esp+4h] [ebp-1Ch]
  char *v19; // [esp+Ch] [ebp-14h]

  LOBYTE(fld_50) = *(uint8_t *)(this + 136);  // this+136 演出已播标志
  if ( (uint8_t)fld_50 == 0 )
  {
    fld_50 = *(uint32_t *)(this + 80);  // 读 fld_50 = this+80（关联角色对象）
    if ( *(uint8_t *)(fld_50 + 9368) != 0 )
    {
      fld_50 = sub_699000(this + 8);  // 【clock_now(clk)】
      if ( fld_50 >= 610 )
      {
        fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象）
        v4 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
        v5 = 0;
        if ( v4 != 0 )
          v5 = sub_431860(v4, "Common/HitEffect/Animation/KnockSmall.ani", 1);  // 字符串 “Common/HitEffect/Animation/KnockSmall.ani”
        v6 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
        if ( v6 != nullptr )  // 若 v6 有效（非空）
          v7 = sub_44E1F0(v6, v5, 1);  // 结果 = CNRDPooledObject 构造（虚表覆盖壳）
        else
          v7 = nullptr;
        fld_502 = *(uint32_t *)(this + 80);  // 读 fld_502 = this+80（关联角色对象）
        v19 = v7;
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 80))(fld_4);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        sub_45FE80(v8, (int)v7, 2, 0, (int)v7, fld_502, 0);  // 调 对象注册
        v9 = *(uint32_t *)v7;
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 152))(fld_4);  // 虚函数调用 槽+152：效果通道 3
        (*(void (/*thiscall*/ **)(char *, int))(v9 + 148))(v7, v10);  // 虚函数调用 槽+148：槽（12 行）
        fld_503 = *(uint32_t *)(this + 80);  // 读 fld_503 = this+80（关联角色对象）
        v18 = *(uint32_t *)v7;
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 192))(fld_4) / 2;  // 虚函数调用 槽+192
        fld_68 = *(uint32_t *)(this + 104) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_503 + 128))(fld_503) + v12;  // this+104 插值终点 Z
        v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_503 + 124))(fld_503, fld_68);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_503 + 120))(fld_503, v13);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        (*(void (/*thiscall*/ **)(char *, int))(v18 + 112))(v19, *(uint32_t *)(this + 96) + v14);  // this+96 插值终点 X / 落点偏移
        LOBYTE(fld_50) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)fld_4 + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
                       fld_4,
                       "BBQ_STUCK",  // 字符串 “BBQ_STUCK”
                       -1,
                       0,
                       0);
        *(uint8_t *)(this + 136) = 1;  // 写 this+136 = 1（演出已播标志）
      }
    }
  }
  return fld_50;  // | +0x0050 → 关联角色对象（CNAerialGatlinged；va=005F9530）
}



// ------------------------------------------------------------
// 0x5F9AE0 sub_5F9AE0
// ------------------------------------------------------------
// 调: sub_5F9AE0
int /*thiscall*/ sub_5F9AE0(uint32_t *this)  // 实现：调: sub_5F9AE0
{
  *(this + 24) = 17;  // this+24 页数上限
  *(this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
  *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *(this + 28) = 0;  // 写 this+112 = 0（宿主组件）
  *(this + 29) = 1065353216;  // 写 this+116 = 1065353216（观察者容器）
  *(this + 30) = 0;  // 写 this+120 = 0（动画对象）
  *(this + 31) = 4;  // 写 this+124 = 4（光环动画件）
  *(this + 32) = 0;  // this+32 格子像素尺寸
  *(this + 33) = 0;  // this+33 【推断】职业数据脏位
  return 0;
}



// ------------------------------------------------------------
// 0x5F9B20 sub_5F9B20
// ------------------------------------------------------------
// 调: sub_5F9B20
int /*thiscall*/ sub_5F9B20(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_5F9B20
{
  *(this + 31) = nArg2;  // 写 this+124 = nArg2（光环动画件）
  *(this + 32) = nArg3;  // this+32 格子像素尺寸
  return nArg2;
}



// ------------------------------------------------------------
// 0x5F9B40 CNWeaponMastery__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590 sub_4AED60
void /*thiscall*/ CNWeaponMastery__vmtC(int this, int pArg2)  // 实现：调: sub_41A5E0 sub_41A590 sub_4AED60
{
  int fld_4; // eax  | +0x0004 → 宿主对象指针（CNWeaponMastery；va=005F9CA0）
  int pObj2; // esi
  int pObj; // eax
  int v6; // eax
  uint32_t *fld_58; // edx
  uint32_t *fld_54; // ecx
  int v9; // edx
  int v10; // edx
  float fld_6C; // [esp+8h] [ebp-8h]  | +0x006C → 攻击加值 1（0x5F9B40: sub_41A590(pArg2+858, +108) 累加）（CNWeaponMastery；va=005F9B40）
  int v12; // [esp+8h] [ebp-8h]
  int v13; // [esp+8h] [ebp-8h]
  int v14; // [esp+8h] [ebp-8h]
  float fld_6C2; // [esp+Ch] [ebp-4h]  | +0x006C → 攻击加值 1（0x5F9B40: sub_41A590(pArg2+858, +108) 累加）（CNWeaponMastery；va=005F9B40）
  float fld_70; // [esp+Ch] [ebp-4h]  | +0x0070 → 攻击加值 2（0x5F9B40: 累加进 pArg2+1292）（CNWeaponMastery；va=005F9B40）

  fld_4 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
         *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
         0,
         &IRDActiveObject `RTTI Type Descriptor',
         &IRDCharacter `RTTI Type Descriptor',
         0);
  pObj2 = fld_4;
  if ( fld_4 != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_4 + 792))(fld_4, 8) == 0  // 虚函数调用 槽+792：18 观察者槽数组访问（+6468+4*a2）
      || (pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 792))(pObj2, 8),  // 虚函数调用 槽+792：18 观察者槽数组访问（+6468+4*a2）
          (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 200))(pObj) == 0) )  // 虚函数调用 槽+200：取动画对象
    {
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 1096))(pObj2);  // 虚函数调用 槽+1096
      fld_58 = *(uint32_t **)(this + 88);  // this+88 角色上下文槽
      fld_54 = *(uint32_t **)(this + 84);  // this+84 插值起点 X
      if ( fld_54 != fld_58 )
      {
        do
        {
          if ( *fld_54 == v6 )
            break;
          ++fld_54;
        }
        while ( fld_54 != fld_58 );
        if ( fld_54 != fld_58 )
        {
          fld_6C = *(float *)(this + 108);  // 读 fld_6C = this+108（攻击加值 1）
          *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(pArg2 + 858)) + fld_6C;  // crypt4byte 解密校验（·0x41A590 逆运算）
          sub_41A590(pArg2 + 858, v12, v12);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          fld_6C2 = *(float *)(this + 108);  // 读 fld_6C2 = this+108（攻击加值 1）
          *(float *)&v13 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1292)) + fld_6C2;  // crypt4byte 解密校验（·0x41A590 逆运算）
          sub_41A590(pArg2 + 1292, v9, v13);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          fld_70 = *(float *)(this + 112);  // 读 fld_70 = this+112（攻击加值 2）
          *(float *)&v14 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1208)) + fld_70;  // crypt4byte 解密校验（·0x41A590 逆运算）
          sub_41A590(pArg2 + 1208, v10, v14);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          if ( *(float *)(this + 120) != 0.0  // 判定 “+120 特殊/暴击率”
            && ((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 792))(pObj2, 8) != 0  // 虚函数调用 槽+792：18 观察者槽数组访问（+6468+4*a2）
             || (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 1084))(pObj2, 8) != 0) )  // 虚函数调用 槽+1084
          {
            sub_4AED60(*(float *)(this + 120));  // this+120 特殊/暴击率
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x5F9CA0 CNWeaponMastery__vmt8
// ------------------------------------------------------------
// 调: sub_45E5A0
void /*thiscall*/ CNWeaponMastery__vmt8(int this, int pArg2)  // 实现：调: sub_45E5A0
{
  int fld_4; // eax  | +0x0004 → 宿主对象指针（CNWeaponMastery；va=005F9CA0）
  int pObj; // ebx
  int pObj2; // eax
  int v7; // eax
  uint32_t *fld_54; // ecx
  int v9; // eax
  uint32_t *v10; // edx
  int fld_68; // edx  | +0x0068 → 攻击属性时长（0x5F9CA0: fld_68=*(this+104) 写入属性面第三天）（CNWeaponMastery；va=005F9CA0）
  int v12; // edx
  int v13; // [esp+8h] [ebp-8h] BYREF
  int v14; // [esp+Ch] [ebp-4h] BYREF
  int fld_42; // [esp+18h] [ebp+8h]

  if ( *(uint8_t *)(pArg2 + 16) != 0 )  // pArg2+16〔nChannelTypeSel(推断)〕
  {
    fld_4 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
           *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
           0,
           &IRDActiveObject `RTTI Type Descriptor',
           &IRDCharacter `RTTI Type Descriptor',
           0);
    pObj = fld_4;
    fld_42 = fld_4;
    if ( fld_4 != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_4 + 792))(fld_4, 8) == 0  // 虚函数调用 槽+792：18 观察者槽数组访问（+6468+4*a2）
        || (pObj2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 792))(pObj, 8),  // 虚函数调用 槽+792：18 观察者槽数组访问（+6468+4*a2）
            (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 200))(pObj2) == 0) )  // 虚函数调用 槽+200：取动画对象
      {
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1096))(pObj);  // 虚函数调用 槽+1096
        fld_54 = *(uint32_t **)(this + 84);  // this+84 插值起点 X
        v14 = v7;
        sub_45E5A0(&v13, fld_54, *(uint32_t **)(this + 88), &v14);  // uint32 区间线性查找
        if ( v13 != *(uint32_t *)(this + 88) )  // 判定 “+88 角色上下文槽”
        {
          if ( *(uint32_t *)(this + 96) != 17 )  // 判定 “+96 攻击属性类型”
          {
            v9 = 0;
            v10 = (uint32_t *)(pArg2 + 24);  // pArg2+24〔nPageMax(推断)〕
            while ( 1 )  // 无限循环
            {
              if ( *v10 == 17 )
              {
                *(uint32_t *)(pArg2 + 4 * v9 + 24) = *(uint32_t *)(this + 96);  // this+96 攻击属性类型
                *(uint32_t *)(pArg2 + 4 * v9 + 36) = *(uint32_t *)(this + 100);  // this+100 攻击属性值
                fld_68 = *(uint32_t *)(this + 104);  // 读 fld_68 = this+104（攻击属性时长）
                goto LABEL_14;
              }
              pObj = fld_42;
              if ( *v10 == *(uint32_t *)(this + 96) )  // 判定 “+96 攻击属性类型”
                break;
              ++v9;
              ++v10;
              if ( v9 >= 3 )
                goto LABEL_15;
            }
            v12 = *(uint32_t *)(pArg2 + 4 * v9 + 48);
            *(float *)(pArg2 + 4 * v9 + 36) = *(float *)(this + 100) + *(float *)(pArg2 + 4 * v9 + 36);  // this+100 攻击属性值
            fld_68 = *(uint32_t *)(this + 104) + v12;  // this+104 攻击属性时长
LABEL_14:
            *(uint32_t *)(pArg2 + 4 * v9 + 48) = fld_68;
          }
LABEL_15:
          if ( *(uint32_t *)(pArg2 + 136) == -1082130432 )  // pArg2+136〔nCtx136(推断)〕
            *(float *)(pArg2 + 136) = ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)pObj + 1188))(pObj);  // 虚函数调用 槽+1188
          *(float *)(pArg2 + 136) = *(float *)(this + 116) * *(float *)(pArg2 + 136);  // 涉及字段 “+116 观察者容器”
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x5F9DD0 sub_5F9DD0
// ------------------------------------------------------------
// 调: sub_5F9DD0 sub_47E720 sub_47EF20 sub_431230
int /*thiscall*/ sub_5F9DD0(int this, int nArg2)  // 实现：调: sub_5F9DD0 sub_47E720 sub_47EF20 sub_431230
{
  int result; // eax
  int fld_80; // eax
  void *fld_54; // ecx
  uint32_t *pThis_50; // eax
  int fld_7C; // [esp-Ch] [ebp-18h]
  int v9; // [esp+8h] [ebp-4h] BYREF
  int pThis_502; // [esp+14h] [ebp+8h]

  result = *(uint32_t *)(this + 132);  // this+132 第 3 组·+60 增量项
  if ( nArg2 != result )
  {
    fld_80 = *(uint32_t *)(this + 128);  // this+128 第 2 组·+1208 增量子倍率
    fld_7C = *(uint32_t *)(this + 124);  // 读 fld_7C = this+124（光环动画件）
    *(uint32_t *)(this + 132) = nArg2;  // this+132 第 3 组·+60 增量项
    sub_47E720(fld_7C, fld_80);  // 调 调 sub_47E720
    fld_54 = *(void **)(this + 84);  // this+84 插值起点 X
    pThis_50 = (uint32_t *)(this + 80);  // this+80 关联角色对象
    pThis_502 = this + 80;  // this+80 关联角色对象
    if ( fld_54 != nullptr )  // 若 fld_54 有效（非空）
    {
      j__free(fld_54);  // 调 堆释放
      pThis_50 = (uint32_t *)(this + 80);  // this+80 关联角色对象
    }
    pThis_50[1] = 0;
    pThis_50[2] = 0;
    pThis_50[3] = 0;
    result = *(uint32_t *)(this + 124);  // 读 result = this+124（光环动画件）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      switch ( result )  // 按 result 分派
      {
        case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
          if ( *(uint32_t *)(this + 128) == 45 )  // this+128 第 2 组·+1208 增量子倍率
          {
            *(uint32_t *)(this + 96) = 11;  // this+96 插值终点 X / 落点偏移
            *(float *)(this + 100) = (double)(int)sub_47EF20(0, nArg2, -1, -1, 11) * 0.1;  // 调 读攻击数据表
            *(uint32_t *)(this + 104) = sub_47EF20(1, nArg2, -1, -1, 11);  // 调 读攻击数据表
            v9 = 2;
            return sub_431230(pThis_502, &v9);  // uint32 vector push_back
          }
          break;
        case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          if ( *(uint32_t *)(this + 128) == 52 )  // this+128 第 2 组·+1208 增量子倍率
          {
            v9 = 3;
            *(float *)(this + 108) = (double)(int)sub_47EF20(0, nArg2, -1, -1, 11) * 0.001;  // 调 读攻击数据表
            return sub_431230(pThis_502, &v9);  // uint32 vector push_back
          }
          break;
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
          result = *(uint32_t *)(this + 128);  // this+128 第 2 组·+1208 增量子倍率
          if ( result == 35 )
          {
            *(float *)(this + 108) = (double)(int)sub_47EF20(0, nArg2, -1, -1, 11) * 0.001;  // 调 读攻击数据表
            v9 = 0;
            *(float *)(this + 120) = (double)(int)sub_47EF20(1, nArg2, -1, -1, 11) * 0.001;  // 调 读攻击数据表
            return sub_431230(pThis_502, &v9);  // uint32 vector push_back
          }
          if ( result == 36 )
          {
            *(float *)(this + 108) = (double)(int)sub_47EF20(0, nArg2, -1, -1, 11) * 0.001;  // 调 读攻击数据表
            *(float *)(this + 120) = (double)(int)sub_47EF20(1, nArg2, -1, -1, 11) * 0.001;  // 调 读攻击数据表
            goto LABEL_26;
          }
          break;
        default:
          return result;
      }
    }
    else
    {
      result = *(uint32_t *)(this + 128);  // this+128 第 2 组·+1208 增量子倍率
      switch ( result )  // 按 result 分派
      {
        case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
          v9 = 0;
          *(float *)(this + 112) = (double)(int)sub_47EF20(0, nArg2, -1, -1, 11) * 0.1;  // 调 读攻击数据表
          return sub_431230(pThis_502, &v9);  // uint32 vector push_back
        case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
          *(uint32_t *)(this + 96) = 11;  // this+96 插值终点 X / 落点偏移
          *(uint32_t *)(this + 104) = sub_47EF20(0, nArg2, -1, -1, 11);  // 调 读攻击数据表
          *(float *)(this + 100) = (double)(int)sub_47EF20(1, nArg2, -1, -1, 11) * 0.1;  // 调 读攻击数据表
LABEL_26:
          v9 = 1;
          return sub_431230(pThis_502, &v9);  // uint32 vector push_back
        case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
          *(float *)(this + 116) = (double)(int)sub_47EF20(0, nArg2, -1, -1, 11) * 0.0099999998 + 1.0;  // 调 读攻击数据表
          v9 = 3;
          *(float *)(this + 108) = (double)(int)sub_47EF20(1, nArg2, -1, -1, 11) * 0.001;  // 调 读攻击数据表
          return sub_431230(pThis_502, &v9);  // uint32 vector push_back
        case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
          *(uint32_t *)(this + 96) = 3;  // this+96 插值终点 X / 落点偏移
          *(uint32_t *)(this + 104) = sub_47EF20(0, nArg2, -1, -1, 11);  // 调 读攻击数据表
          v9 = 2;
          *(float *)(this + 100) = (double)(int)sub_47EF20(1, nArg2, -1, -1, 11) * 0.1;  // 调 读攻击数据表
          return sub_431230(pThis_502, &v9);  // uint32 vector push_back
        case 4:  // case 4 = ENUM_CMDPACKET_EXIT
          *(uint32_t *)(this + 96) = 6;  // this+96 插值终点 X / 落点偏移
          *(uint32_t *)(this + 104) = sub_47EF20(0, nArg2, -1, -1, 11);  // 调 读攻击数据表
          v9 = 5;
          *(float *)(this + 100) = (double)(int)sub_47EF20(1, nArg2, -1, -1, 11) * 0.1;  // 调 读攻击数据表
          return sub_431230(pThis_502, &v9);  // uint32 vector push_back
        default:
          break;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5FA160 sub_5FA160
// ------------------------------------------------------------
// 调: sub_5FA160
int /*thiscall*/ sub_5FA160(uint32_t *this)  // 实现：调: sub_5FA160
{
  *(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *(this + 24) = 0;  // this+24 页数上限
  *(this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
  return 0;
}



// ------------------------------------------------------------
// 0x5FA170 CNRobotics__vmt1C
// ------------------------------------------------------------
// 证: "POWER_UP"
// 调: sub_47EF20
int /*thiscall*/ CNRobotics__vmt1C(int *this)  // 实现：调: sub_47EF20
{
  int result; // eax
  int pObj; // esi
  uint32_t *v3; // edi
  int v4; // ebx

  result = __RTDynamicCast(*(this + 1), 0, &IRDActiveObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
  pObj = result;
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 1160))(result, 46);  // 虚函数调用 槽+1160
    v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 46);  // 虚函数调用 槽+1140
    *(this + 23) = sub_47EF20(v3, 1u, v4, -1, -1, 11);  // 调 读攻击数据表
    *(this + 24) = sub_47EF20(v3, 2u, v4, -1, -1, 11);  // 调 读攻击数据表
    *(this + 25) = sub_47EF20(v3, 3u, v4, -1, -1, 11);  // 调 读攻击数据表
    *(this + 26) = sub_47EF20(v3, 4u, v4, -1, -1, 11);  // 调 读攻击数据表
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
             pObj,
             "POWER_UP",  // 字符串 “POWER_UP”
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FA230 CNRobotics__vmt20
// ------------------------------------------------------------
// 调: sub_41C5E0 sub_4C1400
uint32_t */*thiscall*/ CNRobotics__vmt20(uint32_t *this, int nArg2)  // 函数定义: 设置坐标三元组 (this+100..112)
{
  uint32_t *fld_e21; // ecx
  uint32_t *v4; // eax
  void *i; // ebx
  uint32_t *pThis_14; // edi
  uint32_t *fld_e212; // esi
  uint32_t *result; // eax
  uint32_t *v9; // [esp+Ch] [ebp-4h] BYREF

  fld_e21 = (uint32_t *)*(this + 21);  // this+21 【推断】霸体状态字节
  v4 = (uint32_t *)*fld_e21;
  v9 = (uint32_t *)*fld_e21;
  if ( v9 != fld_e21 )
  {
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)v4[4] + 76))(v4[4], 0);  // 虚函数调用 槽+76：槽（542940 + 485020）
      sub_41C5E0(&v9);  // 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
      v4 = v9;
    }
    while ( v9 != (uint32_t *)*(this + 21) );  // this+21 【推断】霸体状态字节
  }
  pThis_14 = this + 20;  // this+20 频道页号
  fld_e212 = *(uint32_t **)(*(this + 21) + 4);  // this+21 【推断】霸体状态字节
  for ( i = fld_e212; *((uint8_t *)fld_e212 + 21) == 0; i = fld_e212 )
  {
    sub_4C1400((void *)fld_e212[2]);
    fld_e212 = (uint32_t *)*fld_e212;
    j__free(i);  // 调 堆释放
  }
  *(uint32_t *)(pThis_14[1] + 4) = pThis_14[1];
  result = (uint32_t *)pThis_14[1];
  pThis_14[2] = 0;
  *result = result;
  *(uint32_t *)(pThis_14[1] + 8) = pThis_14[1];
  return result;
}



// ------------------------------------------------------------
// 0x5FA2C0 sub_5FA2C0
// ------------------------------------------------------------
// 调: sub_5FA2C0 sub_4015C0 sub_401740 sub_5648C0 sub_433130
int */*thiscall*/ sub_5FA2C0(int **this, int *pDwArg2, char pszArg3, int *pDwArg4, int nArg5)  // 实现：调: sub_5FA2C0 sub_4015C0 sub_401740 sub_5648C0 sub_433130
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

  if ( (unsigned int)*(this + 2) >= 0x1FFFFFFE )  // 判定 “+8 技能槽记录首字”
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
    pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_5648C0(*(this + 1), pDwArg4, *(this + 1), nArg5, 0);  // 结果 = 商店文本
  fld_e12 = *(this + 1);  // 读 fld_e12 = this+4（宿主对象指针）
  fld_e15 = fld_e1;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);  // 写 this+8 = (int *)((char *)*(this + 2) + 1)（技能槽记录首字）
  if ( pDwArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    **(this + 1) = fld_e1;  // this+4〔宿主对象〕
    (*(this + 1))[2] = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pDwArg4 = fld_e1;
    fld_e13 = *(this + 1);  // 读 fld_e13 = this+4（宿主对象指针）
    if ( pDwArg4 == (int *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pDwArg4[2] = fld_e1;
    fld_e14 = (int)*(this + 1);  // this+4〔宿主对象〕
    if ( pDwArg4 == *(int **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
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
            sub_433130(this, *v10);  // 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(this, *(uint32_t **)(*(uint32_t *)(fld_e16 + 4) + 4));  // STL 内联红黑树节点摘除重连
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(this, (uint32_t *)*v10);  // STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(this, *(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 红黑树左旋（节点 0x18 版）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;  // 虚调用 vt+4
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
// 0x5FA470 CNRobotics__vmt30
// ------------------------------------------------------------
// 调: sub_41C5E0 sub_4C1400 sub_4BE520 sub_4C20A0
int /*thiscall*/ CNRobotics__vmt30(int **this, int nArg2)  // 实现：调: sub_41C5E0 sub_4C1400 sub_4BE520 sub_4C20A0
{
  int nArg22; // esi
  int *fld_e21; // ecx
  int v5; // eax
  uint32_t *fld_e212; // eax
  int result; // eax
  int v8; // esi
  int v9; // [esp+Ch] [ebp-4h] BYREF

  nArg22 = nArg2;
  IRDAppendage__vmt30(this, nArg2);
  if ( (int *)nArg22 == *(this + 1) )  // 判定 “+4 宿主对象指针”
  {
    fld_e21 = *(this + 21);  // 读 fld_e21 = this+84（目标查找键）
    v5 = *fld_e21;
    v9 = *fld_e21;
    if ( (int *)v9 != fld_e21 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v5 + 16) + 76))(*(uint32_t *)(v5 + 16), 0);  // 虚函数调用 槽+76：槽（542940 + 485020）
        sub_41C5E0(&v9);  // 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
        v5 = v9;
      }
      while ( (int *)v9 != *(this + 21) );  // this+21 【推断】霸体状态字节
    }
    sub_4C1400((void *)(*(this + 21))[1]);  // this+21 【推断】霸体状态字节
    (*(this + 21))[1] = (int)*(this + 21);  // this+21 【推断】霸体状态字节
    fld_e212 = *(this + 21);  // 读 fld_e212 = this+84（目标查找键）
    *(this + 22) = nullptr;  // this+88〔pFxObjB(推断)〕
    *fld_e212 = fld_e212;
    (*(this + 21))[2] = (int)*(this + 21);  // this+21 【推断】霸体状态字节
  }
  result = sub_4BE520(&v9, &nArg2);  // 结果 = 映射下界查找（lower_bound）
  v8 = v9;
  if ( (int *)v9 != *(this + 21) )  // this+21 【推断】霸体状态字节
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v9 + 16) + 76))(*(uint32_t *)(v9 + 16), 0);  // 虚函数调用 槽+76：槽（542940 + 485020）
    return sub_4C20A0(&nArg2, v8);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FA510 sub_5FA510
// ------------------------------------------------------------
// 调: sub_5FA510 sub_5FA2C0 sub_4A3B30
int /*thiscall*/ sub_5FA510(int **this, int pArg2, int *pDwArg3)  // 实现：调: sub_5FA510 sub_5FA2C0 sub_4A3B30
{
  int *pDwArg32; // ebx
  int *fld_e1; // esi
  int v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  int *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  pDwArg32 = pDwArg3;
  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  v6 = fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *(uint8_t *)(v6 + 21) == 0 )
  {
    v8 = *pDwArg3;
    do
    {
      v7 = v8 < *(uint32_t *)(v6 + 12);
      fld_e1 = (int *)v6;
      v13 = v7;
      if ( v8 >= *(uint32_t *)(v6 + 12) )
        v6 = *(uint32_t *)(v6 + 8);
      else
        v6 = *(uint32_t *)v6;
    }
    while ( *(uint8_t *)(v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;
  pDwArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == (int *)**(this + 1) )  // 判定 “+4 宿主对象指针”
    {
      v10 = *sub_5FA2C0(this, (int *)&pDwArg3, 1, fld_e1, (int)pDwArg32);
      *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&pDwArg3);  // 调 取后继再插
    fld_e12 = pDwArg3;
  }
  if ( fld_e12[3] >= (unsigned int)*pDwArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4〔宿主对象〕
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_5FA2C0(this, (int *)&pDwArg3, v13, fld_e1, (int)pDwArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x5FA5D0 sub_5FA5D0
// ------------------------------------------------------------
// 调: sub_5FA5D0 sub_4B3C90
int /*thiscall*/ sub_5FA5D0(int *this)  // 实现：调: sub_5FA5D0 sub_4B3C90
{
  int pObj; // esi
  float fld_e23; // [esp+24h] [ebp-1Ch]
  float fld_e24; // [esp+24h] [ebp-1Ch]
  float fld_e25; // [esp+24h] [ebp-1Ch]
  float fld_e26; // [esp+24h] [ebp-1Ch]

  if ( operator new(0x7Cu) != nullptr )  // 堆分配 124 字节对象
    pObj = sub_4B3C90(0, 2);  // 结果 = CNChangeStatus 构造（双参）
  else
    pObj = 0;
  fld_e23 = (float)*(this + 23);  // this+92〔pFxObjC(推断)〕
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 120))(pObj, 10, 1, LODWORD(fld_e23));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
  fld_e24 = (float)*(this + 24);  // this+24 页数上限
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj + 120))(pObj, 0, 0, LODWORD(fld_e24));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
  fld_e25 = (float)*(this + 25);  // this+100〔bEnchantDone(推断)〕
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 120))(pObj, 1, 0, LODWORD(fld_e25));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
  fld_e26 = (float)*(this + 26);  // this+104〔nTimerEnd(推断)〕
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 120))(pObj, 8, 0, LODWORD(fld_e26));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
  return pObj;
}



// ------------------------------------------------------------
// 0x5FA680 CNRobotics__vmt4
// ------------------------------------------------------------
// 调: sub_4C0400 sub_4BE520 sub_5FA5D0 sub_5FA510
int /*thiscall*/ CNRobotics__vmt4(int this)  // 实现：调: sub_4C0400 sub_4BE520 sub_5FA5D0 sub_5FA510
{
  int fld_4; // eax  | +0x0004 → 宿主对象指针（CNRobotics；va=005FA680）
  int fld_42; // eax  | +0x0004 → 宿主对象指针（CNRobotics；va=005FA680）
  int fld_422; // ebx
  int v5; // ecx
  int result; // eax
  unsigned int v7; // edx
  int v8; // ecx
  int v9; // eax
  int pObj2; // eax
  int pObj3; // esi
  uint32_t *v12; // eax
  int pObj; // ebx
  int v14; // ebx
  int fld_43; // eax  | +0x0004 → 宿主对象指针（CNRobotics；va=005FA680）
  int v16[2]; // [esp+4h] [ebp-20h] BYREF
  uint8_t v17[4]; // [esp+Ch] [ebp-18h] BYREF
  int fld_423; // [esp+10h] [ebp-14h]
  uint8_t v19[4]; // [esp+14h] [ebp-10h] BYREF
  int pObj32; // [esp+18h] [ebp-Ch] BYREF
  int v21; // [esp+1Ch] [ebp-8h]
  signed int v22; // [esp+20h] [ebp-4h]

  IRDAppendage__vmt4((int *)this);
  fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
  if ( fld_4 == 0 || (*(int (**)(void))(*(uint32_t *)fld_4 + 80))() == 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 76))(this, 0);  // this+76 纹章路径串
  fld_42 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
  fld_422 = fld_42;
  v5 = *(uint32_t *)(fld_42 + 120);
  fld_423 = fld_42;
  if ( v5 != 0 )
    v21 = (*(uint32_t *)(fld_42 + 124) - v5) >> 2;  // 向量元素数 = (end−begin)/4
  else
    v21 = 0;
  result = v21;
  v7 = 0;
  v22 = 0;
  if ( v21 > 0 )
  {
    while ( 1 )  // 无限循环
    {
      v8 = *(uint32_t *)(fld_422 + 120);
      if ( v8 != 0 && v7 < (*(uint32_t *)(fld_422 + 124) - v8) >> 2 )  // 向量元素数 = (end−begin)/4
        v9 = *(uint32_t *)(v8 + 4 * v7);
      else
        v9 = 0;
      pObj2 = __RTDynamicCast(v9, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pObj3 = pObj2;
      if ( pObj2 != 0 )
      {
        v12 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2);  // 虚函数调用 槽+340：三元组基址（+284，vt+340）
        if ( (uint8_t)sub_4C0400(*v12) != 0 )
        {
          pObj32 = pObj3;
          if ( *(uint32_t *)sub_4BE520(v17, &pObj32) == *(uint32_t *)(this + 84) )  // 映射下界查找（lower_bound）
          {
            pObj = sub_5FA5D0((int *)this);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
              pObj,
              pObj3,
              *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
              0,
              0,
              0,
              -1);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 676))(pObj3, 2);  // 虚函数调用 槽+676：观察者/状态的对象绑定与解绑（a2 = 0/1/2）
            v16[0] = pObj3;
            v16[1] = pObj;
            sub_5FA510((int **)(this + 80), (int)v19, v16);  // this+80 关联角色对象
            v14 = *(uint32_t *)pObj3;
            fld_43 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj3 + 736))(pObj3, *(uint32_t *)(this + 4), 1);  // 涉及字段 “+4 宿主对象指针”
            (*(void (/*thiscall*/ **)(int, int))(v14 + 732))(pObj3, *(uint32_t *)(this + 92) + fld_43);  // this+92 机器人动画件
            fld_422 = fld_423;
          }
        }
      }
      result = ++v22;
      if ( v22 >= v21 )
        break;
      v7 = v22;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FA7E0 CNRDActiveStatus__vmt50
// ------------------------------------------------------------
// 调: sub_699000 sub_698F90
void /*thiscall*/ CNRDActiveStatus__vmt50(int this, int nArg2)  // 实现：调: sub_699000 sub_698F90
{
  int fld_54; // ebx  | +0x0054 → 状态结束时刻（CNRDActiveStatus；va=005FA7E0）
  int fld_542; // ebx  | +0x0054 → 状态结束时刻（CNRDActiveStatus；va=005FA7E0）
  int pThis_3C; // ebx
  int fld_58; // eax  | +0x0058 → 累计推进量（CNRDActiveStatus；va=005FA7E0）
  double fld_582; // st7  | +0x0058 → 累计推进量（CNRDActiveStatus；va=005FA7E0）
  int fld_4; // ecx  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）

  if ( nArg2 == *(uint32_t *)(this + 4)  // 判定 “+4 宿主/关联对象”
    && (*(uint32_t *)(this + 8) == 1 || *(uint32_t *)(this + 8) == 3 || *(uint32_t *)(this + 8) == 7) )  // 涉及字段 “+8 技能槽记录首字”
  {
    fld_54 = *(uint32_t *)(this + 84);  // 读 fld_54 = this+84（状态结束时刻）
    if ( fld_54 < sub_699000(this + 60) )  // 【clock_now(clk)】
    {
      pThis_3C = 0;
    }
    else
    {
      fld_542 = *(uint32_t *)(this + 84);  // 读 fld_542 = this+84（状态结束时刻）
      pThis_3C = fld_542 - sub_699000(this + 60);  // 【clock_now(clk)】
    }
    fld_58 = *(uint32_t *)(this + 88) + 500;  // this+88 累计推进量
    *(uint32_t *)(this + 88) = fld_58;  // 写 this+88 = fld_58（累计推进量）
    fld_582 = (double)*(int *)(this + 88);  // this+88 累计推进量
    if ( fld_58 < 0 )
      fld_582 = fld_582 + 4294967300.0;
    if ( (double)*(unsigned int *)(this + 92) * 0.80000001 >= fld_582 )  // this+92 插值起点 Z
    {
      if ( pThis_3C - 500 > 0 )
      {
        *(uint8_t *)(this + 73) = 0;  // 写 this+73 = 0（复位字节 A）
        *(uint8_t *)(this + 74) = 0;  // 写 this+74 = 0（复位字节 B）
        sub_698F90(this + 60, pThis_3C - 500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主/关联对象）
      if ( *(uint32_t *)(this + 8) == 3 )  // 判定 “+8 状态模式号”
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 920))(fld_4);  // 虚函数调用 槽+920
      else
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 916))(fld_4);  // 虚函数调用 槽+916
    }
  }
}



// ------------------------------------------------------------
// 0x5FA8B0 CNRDActiveStatus__vmt38
// ------------------------------------------------------------
// 调: sub_4938F0 sub_491EA0
char /*thiscall*/ CNRDActiveStatus__vmt38(int this, char pszArg2, int nArg3, int nArg4, float fArg5)  // 函数定义: y | z<<16 组合
{
  int fld_8; // eax  | +0x0008 → 状态模式号（CNRDActiveStatus；va=004973B0）
  int fld_4; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int fld_1C; // ecx  | +0x001C → 子动画链 3（模式 1 三条全广播）（证据: va=004973B0）（CNRDActiveStatus；va=004973B0）
  int fld_42; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int fld_43; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）

  fld_8 = *(uint32_t *)(this + 8) - 1;  // 涉及字段 “+8 技能槽记录首字”
  if ( *(uint32_t *)(this + 8) == 1 )  // 判定 “+8 状态模式号”
  {
    LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
    if ( (uint8_t)fld_8 == 0 )
    {
      if ( pszArg2 != 0 )
      {
        sub_4938F0(*(uint32_t *)(this + 24));  // 调 调 sub_4938F0
        fld_4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
        sub_491EA0(dword_79C0B0, nArg3, nArg4, fArg5, fld_4, 0.40000001, 0.30000001, 100);  // 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161
        fld_1C = *(uint32_t *)(this + 28);  // 读 fld_1C = this+28（子动画链 3）
        LOBYTE(fld_8) = *(uint8_t *)(fld_1C + 170);  // 调 取 16 位值低 8 位
        if ( (uint8_t)fld_8 == 0 )
        {
          sub_4938F0(fld_1C);  // 调 调 sub_4938F0
          fld_42 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
          LOBYTE(fld_8) = sub_491EA0(dword_79C0B0, nArg3, nArg4, fArg5, fld_42, 0.40000001, 0.30000001, 100);  // 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161
        }
      }
      else
      {
        sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
        fld_43 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
        LOBYTE(fld_8) = sub_491EA0(dword_79C0B0, nArg3, nArg4, fArg5, fld_43, 0.40000001, 0.30000001, 100);  // 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161
      }
    }
  }
  return fld_8;  // | +0x0008 → 状态模式号（CNRDActiveStatus；va=004973B0）
}



// ------------------------------------------------------------
// 0x5FA9A0 CNRDActiveStatus__vmt4C
// ------------------------------------------------------------
// 证: "STONE_CUT"
// 调: sub_4AED00 sub_497120 sub_605840 sub_4E4A50
char /*userpurge*/ sub_5FA9A0@<al>(uint32_t *pArg1@<ecx>, double fArg2@<st0>, int *pDwArg3, int pArg4, int nArg5)  // 实现：调: sub_4AED00 sub_497120 sub_605840 sub_4E4A50
{
  int v6; // eax
  int v8; // edx
  float *v9; // eax
  int pObj; // esi
  float v11; // ecx
  float v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int nRand3; // eax
  int v17; // eax
  int v19; // [esp-28h] [ebp-48h]
  int v20; // [esp-24h] [ebp-44h]
  int v21; // [esp-20h] [ebp-40h]
  int v22; // [esp-1Ch] [ebp-3Ch]
  int v23; // [esp-1Ch] [ebp-3Ch]
  int nArg52; // [esp-10h] [ebp-30h]
  int v25; // [esp-Ch] [ebp-2Ch]
  float nRand; // [esp+4h] [ebp-1Ch] BYREF
  float nRand2; // [esp+8h] [ebp-18h]
  float v28; // [esp+Ch] [ebp-14h]
  int v29; // [esp+10h] [ebp-10h]
  int v30; // [esp+14h] [ebp-Ch]
  int v31; // [esp+18h] [ebp-8h]
  int v32; // [esp+1Ch] [ebp-4h]
  int v33; // [esp+28h] [ebp+8h]

  if ( pArg1[2] == 6 )
  {
    LOBYTE(v6) = nArg5;  // 调 取 16 位值低 8 位
    if ( (uint8_t)nArg5 == 0 )
    {
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1] + 308))(pArg1[1]);  // 虚函数调用 槽+308
      if ( (uint8_t)v6 != 0 )
      {
        v8 = *pDwArg3;
        HIBYTE(nArg5) = 1;  // 调 取 16 位值高 8 位
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v8 + 40))(pDwArg3, 33) != 0  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
          && *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pDwArg3 + 340))(pDwArg3) == 46002 )  // 虚调用 vt+340
        {
          HIBYTE(nArg5) = 0;  // 调 取 16 位值高 8 位
        }
        v9 = (float *)(*(int (/*thiscall*/ **)(int *))(*pDwArg3 + 348))(pDwArg3);  // 结果 = 虚调用 vt+348
        if ( !sub_4AED00(v9) )
          HIBYTE(nArg5) = 0;  // 调 取 16 位值高 8 位
        pObj = pArg1[1];
        v33 = (*(int (/*thiscall*/ **)(int *))(*pDwArg3 + 376))(pDwArg3);  // 结果 = 虚调用 vt+376
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 虚函数调用 槽+376：坐标同步包（type 37）
        if ( v33 != v6 )
        {
          LOBYTE(v6) = HIBYTE(nArg5);  // 调 取 16 位值低 8 位
          if ( HIBYTE(nArg5) != 0 )  // 调 取 16 位值高 8 位
          {
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1] + 564))(pArg1[1]);  // 虚函数调用 槽+564：位移同步包 vt+234（会话 3 定案：UDP type=5）
            sub_497120(6, pArg1[3]);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
            v32 = (uint64_t)fArg2;
            v11 = *(float *)(pArg4 + 4);  // pArg4+4〔pHost4〕
            nRand = *(float *)pArg4;
            v12 = *(float *)(pArg4 + 8);  // pArg4+8〔nMode8〕
            nRand2 = v11;
            v13 = *(uint32_t *)(pArg4 + 12);  // pArg4+12〔nSkillRec12(推断)〕
            v28 = v12;
            v14 = *(uint32_t *)(pArg4 + 16);  // pArg4+16〔nChannelTypeSel(推断)〕
            v29 = v13;
            v15 = *(uint32_t *)(pArg4 + 20);  // pArg4+20〔pAnimLink20〕
            v30 = v14;
            v31 = v15;
            nRand = (double)(rand() % 60 - 30) + nRand;  // 调 取伪随机数
            nRand2 = (double)(rand() % 60 - 30) + nRand2;  // 调 取伪随机数
            nRand3 = rand();  // 调 取伪随机数
            v22 = pArg1[1];
            nArg5 = 0;
            v28 = (double)(nRand3 % 60 - 30) + v28;
            v25 = sub_605840(&nArg5, v22, &nRand, 0);  // 结果 = 30 字节全局包
            nArg52 = nArg5;
            v23 = (uint64_t)*(float *)(pArg4 + 8);  // pArg4+8〔nMode8〕
            v21 = (uint64_t)*(float *)(pArg4 + 4);  // pArg4+4〔pHost4〕
            v20 = (uint64_t)*(float *)pArg4;
            v19 = v32;
            v17 = (*(int (/*thiscall*/ **)(int *))(*pDwArg3 + 576))(pDwArg3);  // 结果 = 虚调用 vt+576
            LOBYTE(v6) = sub_4E4A50((int)pArg1, v17, 46002, v19, v20, v21, v23, 1, 0, nArg52, v25);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
          }
        }
      }
    }
  }
  else if ( pArg1[2] == 7 )
  {
    LOBYTE(v6) = nArg5;  // 调 取 16 位值低 8 位
    if ( (uint8_t)nArg5 == 0 )
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1[1] + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
                     pArg1[1],
                     "STONE_CUT",  // 字符串 “STONE_CUT”
                     -1,
                     0,
                     0);
  }
  else
  {
    v6 = pArg1[2] - 8;
    if ( pArg1[2] == 8 )
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 28))(pArg1);  // 结果 = 虚调用 vt+28
      if ( v6 > 200 )
        LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int *))(*pArg1 + 4))(pArg1, 0, pDwArg3);  // 虚调用 vt+4
    }
  }
  return v6;
}


// ------------------------------------------------------------
// 0x5FABA0 sub_5FABA0
// ------------------------------------------------------------
// 调: sub_5FABA0
int /*thiscall*/ sub_5FABA0(int this)  // 实现：调: sub_5FABA0
{
  int result; // eax

  if ( *(uint8_t *)(this + 97) == 0  // this+97 【推断】附加门字节
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4)) != 9  // 涉及字段 “+4 宿主对象指针”
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 568))(*(uint32_t *)(this + 4)) != 9 )  // 涉及字段 “+4 宿主对象指针”
  {
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 560))(  // this+4 宿主对象
      *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
      9,
      0,
      0,
      0);
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 0) != 100 )  // 判定 “+4 宿主对象指针”
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 0, 100);  // 涉及字段 “+4 宿主对象指针”
  if ( (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 1) != 200 )  // 判定 “+4 宿主对象指针”
    (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 1, 200);  // 涉及字段 “+4 宿主对象指针”
  result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 2);  // 涉及字段 “+4 宿主对象指针”
  if ( result != 255 )
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 2, 255);  // 涉及字段 “+4 宿主对象指针”
  return result;
}



// ------------------------------------------------------------
// 0x5FAC50 sub_5FAC50
// ------------------------------------------------------------
// 调: sub_5FAC50 sub_4938F0 sub_491D00
char /*thiscall*/ sub_5FAC50(int this, char pszArg2, int nArg3, int nArg4, float fArg5)  // 实现：调: sub_5FAC50 sub_4938F0 sub_491D00
{
  char result; // al
  int fld_1C; // ecx

  result = *(uint8_t *)(this + 97);  // this+97 【推断】附加门字节
  if ( result == 0 )
  {
    if ( pszArg2 != 0 )
    {
      sub_4938F0(*(uint32_t *)(this + 24));  // 调 调 sub_4938F0
      sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      fld_1C = *(uint32_t *)(this + 28);  // this+28 【推断】逐帧驱动对象
      result = *(uint8_t *)(fld_1C + 170);
      if ( result == 0 )
      {
        sub_4938F0(fld_1C);  // 调 调 sub_4938F0
        return sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
    }
    else
    {
      sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
      return sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FACE0 sub_5FACE0
// ------------------------------------------------------------
// 调: sub_5FACE0 sub_41A5E0 sub_41A590
int /*stdcall*/ sub_5FACE0(int pArg1)  // 实现：调: sub_5FACE0 sub_41A5E0 sub_41A590
{
  int v1; // eax
  int v2; // edx
  int v3; // edx

  v1 = sub_41A5E0(pArg1 + 88);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 88, v2, v1 + 100);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return sub_41A590(pArg1 + 382, v3, 1000);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x5FAD20 sub_5FAD20
// ------------------------------------------------------------
// 调: sub_5FAD20 sub_4938F0 sub_491D00
char /*thiscall*/ sub_5FAD20(int this, char pszArg2, int nArg3, int nArg4, float fArg5)  // 实现：调: sub_5FAD20 sub_4938F0 sub_491D00
{
  char result; // al

  result = *(uint8_t *)(this + 97);  // this+97 【推断】附加门字节
  if ( result == 0 )
  {
    result = pszArg2;
    if ( pszArg2 != 0 )
    {
      sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
      return sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FAD60 CNRDActiveStatus__vmt30
// ------------------------------------------------------------
// 调: sub_4E99C0 sub_4D8700 sub_4450B0 sub_41A590 sub_5FACE0
int /*fastcall*/ CNRDActiveStatus__vmt30(int pArg1, int nArg2, int pArg3)  // 实现：调: sub_4E99C0 sub_4D8700 sub_4450B0 sub_41A590 sub_5FACE0
{
  int result; // eax
  int v5; // edx
  float v6; // [esp+0h] [ebp-Ch]
  float v7; // [esp+0h] [ebp-Ch]
  float v8; // [esp+0h] [ebp-Ch]
  float v9; // [esp+0h] [ebp-Ch]
  float v10; // [esp+0h] [ebp-Ch]
  float v11; // [esp+0h] [ebp-Ch]
  float v12; // [esp+0h] [ebp-Ch]
  float v13; // [esp+0h] [ebp-Ch]
  float v14; // [esp+0h] [ebp-Ch]
  float v15; // [esp+0h] [ebp-Ch]
  float v16; // [esp+0h] [ebp-Ch]
  float v17; // [esp+0h] [ebp-Ch]

  result = *(uint32_t *)(pArg1 + 8);  // 读 result = pArg1+8（状态模式号）
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      v6 = 1.0 - *(float *)(pArg1 + 104);  // pArg1+104〔nTimerEnd(推断)〕
      sub_4E99C0(v6);  // 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
      v7 = 1.0 - *(float *)(pArg1 + 104);  // pArg1+104〔nTimerEnd(推断)〕
      result = sub_4E99C0(v7);  // 结果 = 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
      break;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      sub_4D8700(50);
      sub_4450B0((void *)(pArg3 + 186), 50);  // 计数器加值
      result = sub_41A590(pArg3 + 298, v5, 1000);  // 结果 = crypt4byte 加密初始化（随机密钥 + 双校验字）
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      result = sub_41A590(pArg3 + 326, nArg2, 1000);  // 结果 = crypt4byte 加密初始化（随机密钥 + 双校验字）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      v8 = 1.0 - *(float *)(pArg1 + 184);  // pArg1+184〔bSingleTarget(推断)〕
      sub_4E99C0(v8);  // 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
      v9 = 1.0 - *(float *)(pArg1 + 184);  // pArg1+184〔bSingleTarget(推断)〕
      sub_4E99C0(v9);  // 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
      v10 = 1.0 - *(float *)(pArg1 + 184);  // pArg1+184〔bSingleTarget(推断)〕
      sub_4E99C0(v10);  // 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
      v11 = 1.0 - *(float *)(pArg1 + 184);  // pArg1+184〔bSingleTarget(推断)〕
      result = sub_4E99C0(v11);  // 结果 = 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
      break;
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      result = sub_5FACE0(pArg3);
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      result = sub_41A590(pArg3 + 396, nArg2, 1000);  // 结果 = crypt4byte 加密初始化（随机密钥 + 双校验字）
      break;
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
      v12 = *(float *)(pArg1 + 188) - 1.0;  // pArg1+188〔nStatusIdx(推断)〕
      sub_4AED60(v12);
      v13 = *(float *)(pArg1 + 188) - 1.0;  // pArg1+188〔nStatusIdx(推断)〕
      result = sub_4AED60(v13);
      break;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      v14 = *(float *)(pArg1 + 192) - 1.0;  // pArg1+192〔nDlgId(推断)〕
      sub_4AED60(v14);
      v15 = *(float *)(pArg1 + 192) - 1.0;  // pArg1+192〔nDlgId(推断)〕
      sub_4AED60(v15);
      v16 = *(float *)(pArg1 + 192) - 1.0;  // pArg1+192〔nDlgId(推断)〕
      sub_4AED60(v16);
      v17 = *(float *)(pArg1 + 192) - 1.0;  // pArg1+192〔nDlgId(推断)〕
      result = sub_4AED60(v17);
      break;
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      result = sub_41A590(pArg3 + 494, nArg2, 1000);  // 结果 = crypt4byte 加密初始化（随机密钥 + 双校验字）
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FAFC0 CNRDActiveStatus__vmt34
// ------------------------------------------------------------
// 调: sub_4938F0 sub_491D00 sub_5FAC50 sub_491DE0
char /*thiscall*/ sub_5FAFC0(int this, float fArg2, int nArg3, int nArg4, float fArg5)  // 【CNRDActiveStatus__vmt34】
{
  int v6; // edi
  int fld_8; // eax  | +0x0008 → 状态模式号（CNRDActiveStatus；va=004973B0）
  int fld_42; // esi  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int v9; // eax
  int fld_49; // ebx  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int v11; // eax
  double fld_410; // st7
  int fld_411; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int fld_412; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  double fld_413; // st7
  double fld_414; // st7
  double fld_415; // st7
  int fld_45; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int fld_46; // ecx  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int v20; // eax
  int v21; // eax
  int nArg32; // edi
  int fld_47; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int v24; // eax
  int fld_48; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int v26; // eax
  double v27; // st7
  int fld_43; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int fld_44; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int fld_4; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int dword_79C0B02; // [esp-24h] [ebp-34h]
  int dword_79C0B03; // [esp-24h] [ebp-34h]
  int dword_79C0B04; // [esp-24h] [ebp-34h]
  float v35; // [esp-18h] [ebp-28h]
  float v36; // [esp-18h] [ebp-28h]
  double dwNow; // [esp+8h] [ebp-8h]
  double dwNow2; // [esp+8h] [ebp-8h]
  double dwNow3; // [esp+8h] [ebp-8h]
  float v40; // [esp+18h] [ebp+8h]
  float v41; // [esp+20h] [ebp+10h]
  float v42; // [esp+20h] [ebp+10h]
  float v43; // [esp+20h] [ebp+10h]

  v6 = *(uint32_t *)(dword_8F7A24 + 244) != 2 ? 50 : 30;  // 全局 dword_8F7A24 = 登录/选区管理器
  fld_8 = *(uint32_t *)(this + 8);  // this+8 状态模式号
  switch ( fld_8 )  // 按 fld_8 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
      LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
      if ( (uint8_t)fld_8 == 0 )
      {
        LOBYTE(fld_8) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
        if ( (uint8_t)fld_8 == 0 )
        {
          LOBYTE(fld_8) = LOBYTE(fArg2);  // 调 取 16 位值低 8 位
          if ( LOBYTE(fArg2) != 0 )  // 调 取 16 位值低 8 位
          {
            sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
            fld_4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
            LOBYTE(fld_8) = sub_491D00(dword_79C0B0, nArg3, nArg4 + fld_4, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          }
        }
      }
      break;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      LOBYTE(fld_8) = sub_5FAC50(SLOBYTE(fArg2), nArg3, nArg4, fArg5);  // 调 取 16 位值低 8 位
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
      if ( (uint8_t)fld_8 == 0 )
      {
        LOBYTE(fld_8) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
        if ( (uint8_t)fld_8 == 0 )
        {
          LOBYTE(fld_8) = LOBYTE(fArg2);  // 调 取 16 位值低 8 位
          if ( LOBYTE(fArg2) != 0 )  // 调 取 16 位值低 8 位
          {
            dwNow = sin((double)timeGetTime() * 0.008975979010256551) * 25.0 + (double)(unsigned int)v6;  // 调 正弦
            fld_8 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
            if ( fld_8 != 0 )
            {
              fld_42 = *(uint32_t *)(this + 4);  // this+4 宿主/关联对象
              v9 = -(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_42 + 152))(fld_42);  // 虚函数调用 槽+152：效果通道 3
              LOBYTE(v9) = v9 == 0;  // 调 取 16 位值低 8 位
              v35 = *(float *)&v9;
              dword_79C0B02 = dword_79C0B0;  // 读 dword_79C0B0（文本/图像绘制对象）
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_42 + 200))(fld_42);  // 虚函数调用 槽+200：取动画对象
              LOBYTE(fld_8) = sub_491DE0(  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
                             dword_79C0B02,  // 默认字体/绘制资源
                             nArg3,
                             nArg4,
                             v35,
                             0,
                             1,
                             -65281,
                             ((uint8_t)(uint64_t)dwNow << 24) | 0xFFFFFF);
            }
          }
        }
      }
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
      if ( (uint8_t)fld_8 == 0 )
      {
        LOBYTE(fld_8) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
        if ( (uint8_t)fld_8 == 0 )
        {
          sub_4938F0(*(uint32_t *)(this + 4 * (LOBYTE(fArg2) != 0) + 20));  // 调 调 sub_4938F0
          fld_43 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
          LOBYTE(fld_8) = sub_491D00(dword_79C0B0, nArg3, nArg4 - fld_43 - 5, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        }
      }
      break;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
      if ( (uint8_t)fld_8 == 0 )
      {
        LOBYTE(fld_8) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
        if ( (uint8_t)fld_8 == 0 )
        {
          if ( LOBYTE(fArg2) != 0 )  // 调 取 16 位值低 8 位
            sub_4938F0(*(uint32_t *)(this + 24));  // 调 调 sub_4938F0
          else
            sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
          fld_44 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
          LOBYTE(fld_8) = sub_491D00(dword_79C0B0, nArg3, nArg4 - fld_44 - 5, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        }
      }
      break;
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
      if ( (uint8_t)fld_8 == 0 )
      {
        LOBYTE(fld_8) = LOBYTE(fArg2);  // 调 取 16 位值低 8 位
        if ( LOBYTE(fArg2) != 0 )  // 调 取 16 位值低 8 位
          goto LABEL_44;
      }
      break;
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      LOBYTE(fld_8) = sub_5FAD20(SLOBYTE(fArg2), nArg3, nArg4, fArg5);  // 调 取 16 位值低 8 位
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      fld_8 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
      if ( fld_8 == 4 )
      {
        LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
        if ( (uint8_t)fld_8 == 0 )
        {
          LOBYTE(fld_8) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
          if ( (uint8_t)fld_8 == 0 )
          {
            LOBYTE(fld_8) = LOBYTE(fArg2);  // 调 取 16 位值低 8 位
            if ( LOBYTE(fArg2) != 0 )  // 调 取 16 位值低 8 位
            {
              fld_45 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 152))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
              fld_46 = *(uint32_t *)(this + 4);  // this+4 宿主/关联对象
              if ( fld_45 != 0 )
              {
                if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_46 + 152))(fld_46) == 1 )  // 虚函数调用 槽+152：效果通道 3
                {
                  v40 = (float)nArg3;
                  fld_47 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
                  v24 = sub_42F220(fld_47);  // 结果 = 取动画帧对象
                  nArg32 = (uint64_t)(v40 - (double)(int)sub_4918E0(v24, 1) * 0.75);  // 结果 = 动画盒四边界提取（研究 P29 族）
                }
                else
                {
                  nArg32 = nArg3;
                }
              }
              else
              {
                v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_46 + 200))(fld_46);  // 虚函数调用 槽+200：取动画对象
                v21 = sub_42F220(v20);  // 结果 = 取动画帧对象
                nArg32 = (uint64_t)((double)(int)sub_4918E0(v21, 1) * 0.75 + (double)nArg3);  // 结果 = 动画盒四边界提取（研究 P29 族）
              }
              sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
              v43 = (float)nArg4;
              fld_48 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
              v26 = sub_42F220(fld_48);  // 结果 = 取动画帧对象
              v27 = v43 - (double)(int)sub_4918E0(v26, 2) * 0.5;  // 结果 = 动画盒四边界提取（研究 P29 族）
              LOBYTE(fld_8) = sub_491D00(dword_79C0B0, nArg32, (uint64_t)v27, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            }
          }
        }
      }
      break;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
      if ( (uint8_t)fld_8 == 0 )
      {
        LOBYTE(fld_8) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
        if ( (uint8_t)fld_8 == 0 )
        {
          LOBYTE(fld_8) = LOBYTE(fArg2);  // 调 取 16 位值低 8 位
          if ( LOBYTE(fArg2) != 0 )  // 调 取 16 位值低 8 位
          {
            dwNow2 = sin((double)timeGetTime() * 0.008975979010256551) * 25.0 + (double)(unsigned int)v6;  // 调 正弦
            if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) != 0 )  // this+4 宿主/关联对象
            {
              fld_49 = *(uint32_t *)(this + 4);  // this+4 宿主/关联对象
              v11 = -(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_49 + 152))(fld_49);  // 虚函数调用 槽+152：效果通道 3
              LOBYTE(v11) = v11 == 0;  // 调 取 16 位值低 8 位
              v36 = *(float *)&v11;
              dword_79C0B03 = dword_79C0B0;  // 读 dword_79C0B0（文本/图像绘制对象）
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_49 + 200))(fld_49);  // 虚函数调用 槽+200：取动画对象
              sub_491DE0(dword_79C0B03, nArg3, nArg4, v36, 0, 1, -16776961, ((uint8_t)(uint64_t)dwNow2 << 24) | 0xFFFFFF);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
            }
LABEL_44:
            sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
            LOBYTE(fld_8) = sub_491D00(dword_79C0B0, nArg3, nArg4, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          }
        }
      }
      break;
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
      if ( (uint8_t)fld_8 == 0 )
      {
        LOBYTE(fld_8) = LOBYTE(fArg2);  // 调 取 16 位值低 8 位
        if ( LOBYTE(fArg2) != 0 )  // 调 取 16 位值低 8 位
        {
          LOBYTE(fArg2) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 152))(*(uint32_t *)(this + 4)) == 0;  // this+4 宿主/关联对象
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4)) == 0 )  // this+4 宿主/关联对象
          {
            dwNow3 = sin((double)timeGetTime() * 0.008975979010256551) * 25.0 + (double)(unsigned int)v6;  // 调 正弦
            if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) != 0 )  // this+4 宿主/关联对象
            {
              dword_79C0B04 = dword_79C0B0;  // 读 dword_79C0B0（文本/图像绘制对象）
              (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
              sub_491DE0(dword_79C0B04, nArg3, nArg4, fArg2, 0, 1, -16776961, ((uint8_t)(uint64_t)dwNow3 << 24) | 0xFFFFFF);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
            }
          }
          LOBYTE(fld_8) = dword_8F7A24;  // 全局 dword_8F7A24 = 登录/选区管理器
          if ( *(uint32_t *)(dword_8F7A24 + 244) != 2 )  // 全局 dword_8F7A24 = 登录/选区管理器
          {
            sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
            v41 = (float)nArg4;
            fld_410 = v41
                - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))  // this+4 宿主/关联对象
                * 0.80000001;
            LOBYTE(fld_8) = sub_491D00(dword_79C0B0, nArg3, (uint64_t)fld_410, fArg2);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          }
        }
      }
      break;
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
      if ( (uint8_t)fld_8 == 0 )
      {
        LOBYTE(fld_8) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
        if ( (uint8_t)fld_8 == 0 )
        {
          LOBYTE(fld_8) = LOBYTE(fArg2);  // 调 取 16 位值低 8 位
          if ( LOBYTE(fArg2) != 0 )  // 调 取 16 位值低 8 位
          {
            sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
            sub_4938F0(*(uint32_t *)(this + 24));  // 调 调 sub_4938F0
            fld_411 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
            sub_491D00(dword_79C0B0, nArg3, nArg4 - fld_411 - 50, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            fld_412 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
            LOBYTE(fld_8) = sub_491D00(dword_79C0B0, nArg3, nArg4 - fld_412 - 50, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          }
        }
      }
      break;
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      LOBYTE(fld_8) = *(uint8_t *)(this + 97);  // this+97 附加门字节
      if ( (uint8_t)fld_8 == 0 )
      {
        LOBYTE(fld_8) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // this+4 宿主/关联对象
        if ( (uint8_t)fld_8 == 0 )
        {
          LOBYTE(fld_8) = LOBYTE(fArg2);  // 调 取 16 位值低 8 位
          if ( LOBYTE(fArg2) != 0 )  // 调 取 16 位值低 8 位
          {
            sub_4938F0(*(uint32_t *)(this + 20));  // 调 调 sub_4938F0
            sub_4938F0(*(uint32_t *)(this + 24));  // 调 调 sub_4938F0
            sub_4938F0(*(uint32_t *)(this + 28));  // 调 调 sub_4938F0
            v42 = (float)nArg4;
            fld_413 = v42
                - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))  // this+4 宿主/关联对象
                * 0.85000002;
            sub_491D00(dword_79C0B0, nArg3, (uint64_t)fld_413, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            fld_414 = v42
                - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))  // this+4 宿主/关联对象
                * 0.55000001;
            sub_491D00(dword_79C0B0, nArg3, (uint64_t)fld_414, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            fld_415 = v42
                - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4)) * 0.25;  // this+4 宿主/关联对象
            LOBYTE(fld_8) = sub_491D00(dword_79C0B0, nArg3, (uint64_t)fld_415, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          }
        }
      }
      break;
    default:
      return fld_8;  // | +0x0008 → 状态模式号（CNRDActiveStatus；va=004973B0）
  }
  return fld_8;  // | +0x0008 → 状态模式号（CNRDActiveStatus；va=004973B0）
}


// ------------------------------------------------------------
// 0x5FB780 sub_5FB780
// ------------------------------------------------------------
// 证: "CONDITION_STONE"
// 调: sub_5FB780 sub_4926A0 sub_497150 sub_41A5E0
char /*thiscall*/ sub_5FB780(int this, char pszArg2)  // 实现：调: sub_5FB780 sub_4926A0 sub_497150 sub_41A5E0
{
  char result; // al
  uint64_t fld_8; // rax
  int fld_4; // ecx
  int v6; // edi
  int v7; // [esp+10h] [ebp+8h]

  result = pszArg2;
  if ( pszArg2 != 0 )
  {
    sub_4926A0(*(uint32_t *)(this + 20));  // 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 40) + 12))(*(uint32_t *)(this + 40), 0);  // 涉及字段 “+40 状态子标志”
    fld_8 = (uint64_t)sub_497150(*(uint32_t *)(this + 8), *(uint32_t *)(this + 12));  // 结果 = 第二组状态时长插值（flt_6CB2F0 → flt_6CB2F4）
    fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
    *(uint32_t *)(this + 124) = fld_8;  // 写 this+124 = fld_8（光环动画件）
    v6 = (*(int (/*fastcall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_4 + 672))(fld_4, HIDWORD(fld_8), 3);  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
    v7 = sub_41A5E0(v6 + 382);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(uint32_t *)(this + 124) = (int)(*(uint32_t *)(this + 124)  // 涉及字段 “+124 光环动画件”
                                  * (100 - (uint64_t)((double)v7 * COERCE_FLOAT(sub_41A5E0(v6 + 606)))))  // crypt4byte 解密校验（·0x41A590 逆运算）
                            / 100;
    return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(  // this+4 宿主对象
             *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
             "CONDITION_STONE",  // 字符串 “CONDITION_STONE”
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FB830 CNRDActiveStatus__vmt3C
// ------------------------------------------------------------
// 证: "CONDITION_SLOW" | "FROZEN" | "CONDITION_POSION" | "G_POISON_LOOP"
// 调: sub_497120 sub_4926A0 sub_699000 sub_699030
char /*thiscall*/ sub_5FB830(uint32_t *this, int nArg2)  // 【CNRDActiveStatus__vmt3C】
{
  int v3; // eax
  int v4; // edi
  int fld_e1; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  int pThis_F2; // eax
  int fld_e2; // ecx  | +0x0008 → 状态模式号（CNRDActiveStatus；va=004973B0）
  uint32_t *pThis_5; // edi
  int i; // ebx
  int pThis_F; // eax
  int fld_e10; // ecx
  float *v12; // eax
  float v13; // ecx
  uint32_t *pThis_A; // edi
  int j; // ebx
  int fld_e12; // eax  | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
  float v18; // [esp+Ch] [ebp-8h]
  float v19; // [esp+10h] [ebp-4h]

  v3 = *this;
  v4 = 0;
  *(this + 22) = 0;  // this+88〔nElapsed88〕
  *((uint8_t *)this + 97) = 0;  // 写 this+97 = 0（附加门字节）
  (*(void (/*stdcall*/ **)(uint32_t))(v3 + 36))(0);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
  switch ( *(this + 2) )  // this+8〔nMode8〕
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      *((float *)this + 26) = sub_497120(0, *(this + 3));  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      if ( (uint8_t)nArg2 != 0 )
        sub_4926A0(*(this + 5));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDITION_SLOW",  // 字符串 “CONDITION_SLOW”
        -1,
        0,
        0);
      goto LABEL_61;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1)) + 12) == 0 )  // 虚函数调用 槽+688：附加块基址 this+6160
        goto LABEL_18;
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 940))(*(this + 1)) != 0 )  // 虚函数调用 槽+940
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(*(uint32_t *)*(this + 1) + 944))(*(this + 1), 0, -1);  // 虚函数调用 槽+944
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 848))(*(this + 1), 1);  // 虚函数调用 槽+848：冻结标志写入（+6744，0→-1 / 非0→0）
      if ( (uint8_t)nArg2 != 0 )
      {
        pThis_5 = this + 5;
        for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
          sub_4926A0(*pThis_5++);  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          *(this + 1),  // this+4〔pHost4〕
          "FROZEN",  // 字符串 “FROZEN”
          -1,
          0,
          0);
        v4 = 0;
      }
      goto LABEL_61;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      *(this + 32) = 0;  // this+32 格子像素尺寸
      *(this + 34) = 0;  // this+136〔nCtx136(推断)〕
      *(this + 33) = -300;  // this+33 【推断】职业数据脏位
      pThis_F = sub_699000((int)(this + 15));  // 【clock_now(clk)】
      fld_e10 = *(this + 10);  // this+40〔bStateSub40(推断)〕
      *(this + 35) = pThis_F + 500;  // this+140〔nAdd140(推断)〕
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e10 + 12))(fld_e10, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDITION_POSION",  // 字符串 “CONDITION_POSION”
        -1,
        0,
        0);
      if ( (uint8_t)nArg2 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          *(this + 1),  // this+4〔pHost4〕
          "G_POISON_LOOP",  // 字符串 “G_POISON_LOOP”
          2,
          0,
          0);
      goto LABEL_61;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 776))(*(this + 1), 8) != 0 )  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
        goto LABEL_18;
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 848))(*(this + 1), 1);  // 虚函数调用 槽+848：冻结标志写入（+6744，0→-1 / 非0→0）
      sub_699030((int)(this + 15));  // 【clock_freeze(clk)】
      goto LABEL_61;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      *((float *)this + 46) = sub_497120(4, *(this + 3));  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      if ( (uint8_t)nArg2 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 10) + 12))(*(this + 10), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDITION_CURSE",  // 字符串 “CONDITION_CURSE”
        -1,
        0,
        0);
      goto LABEL_61;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDITION_BLIND",  // 字符串 “CONDITION_BLIND”
        -1,
        0,
        0);
      goto LABEL_61;
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      if ( (uint8_t)nArg2 != 0 )
        sub_4926A0(*(this + 5));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDTION_LIGHT",  // 字符串 “CONDTION_LIGHT”
        -1,
        0,
        0);
      if ( (uint8_t)nArg2 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          *(this + 1),  // this+4〔pHost4〕
          "CONDITION_LIGTHNING_LOOP",  // 字符串 “CONDITION_LIGTHNING_LOOP”
          4,
          0,
          0);
      goto LABEL_61;
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1)) + 12) == 0 )  // 虚函数调用 槽+688：附加块基址 this+6160
      {
LABEL_18:
        LOBYTE(fld_e1) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 4))(this, 0, 0);  // 虚调用 vt+4
        return fld_e1;  // | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 940))(*(this + 1)) != 0 )  // 虚函数调用 槽+940
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(*(uint32_t *)*(this + 1) + 944))(*(this + 1), 0, -1);  // 虚函数调用 槽+944
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 848))(*(this + 1), 1);  // 虚函数调用 槽+848：冻结标志写入（+6744，0→-1 / 非0→0）
      sub_5FB780(nArg2);
      goto LABEL_61;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 776))(*(this + 1), 3) != 0 )  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 4))(this, 0, 0);  // 虚调用 vt+4
        LOBYTE(fld_e1) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 840))(*(this + 1)) == 9;  // 虚函数调用 槽+840：大状态 getter（this+6556）
        *((uint8_t *)this + 204) = fld_e1;  // this+204 子动画链指针
      }
      else
      {
        sub_699030((int)(this + 15));  // 【clock_freeze(clk)】
        if ( (uint8_t)nArg2 != 0 )
          sub_4926A0(*(this + 5));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          *(this + 1),  // this+4〔pHost4〕
          "CONDITION_SLEEP",  // 字符串 “CONDITION_SLEEP”
          -1,
          0,
          0);
LABEL_61:
        LOBYTE(fld_e1) = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 40))(*(this + 1), 273);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
        if ( (uint8_t)fld_e1 != 0 )
        {
          do
          {
            fld_e1 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 792))(*(this + 1), v4);  // 虚函数调用 槽+792：18 观察者槽数组访问（+6468+4*a2）
            if ( fld_e1 != 0 )
            {
              fld_e12 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 792))(*(this + 1), v4);  // 虚函数调用 槽+792：18 观察者槽数组访问（+6468+4*a2）
              LOBYTE(fld_e1) = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e12 + 288))(fld_e12, *(this + 2), nArg2);  // 虚函数调用 槽+288
            }
            ++v4;
          }
          while ( v4 < 18 );
        }
      }
      return fld_e1;  // | +0x0004 → 宿主/关联对象（CNRDActiveStatus；va=005FA7E0）
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      *(this + 36) = 0;  // 写 this+36 = 0（状态字）
      *(this + 37) = 0;  // this+37 【推断】淡入收尾标志 A
      *(this + 38) = sub_699000((int)(this + 15)) + 500;  // clock_now(clk)
      if ( (uint8_t)nArg2 != 0 )
      {
        *((uint8_t *)this + 169) = 0;
        *((uint8_t *)this + 170) = 0;  // 写 this+170 = 0（动画状态字节）
        sub_698F90((int)(this + 39), 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        sub_4926A0(*(this + 5));  // 帧游标复位（+44 帧数组；递归子链 +204）
        if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1)) != 0 )  // 虚函数调用 槽+688：附加块基址 this+6160
        {
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1));  // 虚函数调用 槽+688：附加块基址 this+6160
          if ( sub_4924C0(0) != 0 )  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
          {
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1));  // 虚函数调用 槽+688：附加块基址 this+6160
            v12 = (float *)sub_4924C0(0);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
            v13 = *v12;
            if ( *(uint32_t *)v12 != 0 )
            {
              v18 = (double)*(unsigned int *)(LODWORD(v13) + 20) * 1.5 * v12[5] * 0.0099999998;  // 调 取 64 位值低 32 位
              v19 = (double)*(unsigned int *)(LODWORD(v13) + 24) * 1.5 * v12[6] * 0.0070921984;  // 调 取 64 位值低 32 位
              if ( v18 > 1.0 )
                v18 = 1.0;
              if ( v19 > 1.0 )
                v19 = 1.0;
              sub_4920E0(v18, v19);  // 调 批量改写全帧缩放
            }
          }
        }
      }
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDITION_POSION",  // 字符串 “CONDITION_POSION”
        -1,
        0,
        0);
      if ( (uint8_t)nArg2 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          *(this + 1),  // this+4〔pHost4〕
          "G_POISON_LOOP",  // 字符串 “G_POISON_LOOP”
          3,
          0,
          0);
      goto LABEL_61;
    case 0xB:
      pThis_F2 = sub_699000((int)(this + 15));  // 【clock_now(clk)】
      fld_e2 = *(this + 2);  // this+8〔nMode8〕
      *(this + 49) = pThis_F2;  // this+49 UDP 已上报标志
      *(this + 50) = (uint64_t)sub_497120(fld_e2, *(this + 3));  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      if ( (uint8_t)nArg2 != 0 )
        sub_4926A0(*(this + 5));  // 帧游标复位（+44 帧数组；递归子链 +204）
      *(this + 50) = (uint64_t)(sub_433F60(*(this + 4), 0) * (double)(int)*(this + 50));  // 调 PVP 平衡系数路由（研究第 17/27 轮）
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDITION_BLOODING",  // 字符串 “CONDITION_BLOODING”
        -1,
        0,
        0);
      goto LABEL_61;
    case 0xC:
      *((float *)this + 47) = sub_497120(12, *(this + 3));  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      if ( (uint8_t)nArg2 != 0 )
        sub_4926A0(*(this + 5));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDITION_HASTE",  // 字符串 “CONDITION_HASTE”
        -1,
        0,
        0);
      goto LABEL_61;
    case 0xD:
      *((float *)this + 48) = sub_497120(13, *(this + 3));  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      if ( (uint8_t)nArg2 != 0 )
      {
        pThis_A = this + 10;
        for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_A + 12))(*pThis_A, 0);  // 虚调用 vt+12
          ++pThis_A;
        }
        v4 = 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDITION_BLESS",  // 字符串 “CONDITION_BLESS”
        -1,
        0,
        0);
      goto LABEL_61;
    case 0xF:
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHost4〕
        "CONDITION_CONFUSE",  // 字符串 “CONDITION_CONFUSE”
        -1,
        0,
        0);
      goto LABEL_61;
    case 0x10:
      if ( (uint8_t)nArg2 != 0 )
      {
        sub_4926A0(*(this + 5));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          *(this + 1),  // this+4〔pHost4〕
          "ZIEG_NOVA_READY_LOOP",  // 字符串 “ZIEG_NOVA_READY_LOOP”
          40100,
          0,
          0);
      }
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)*(this + 1) + 896))(*(this + 1), 4, 4);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
      goto LABEL_61;
    default:
      goto LABEL_61;
  }
}


// ------------------------------------------------------------
// 0x5FBE20 sub_5FBE20
// ------------------------------------------------------------
// 调: sub_5FBE20 sub_4920E0 sub_4600B0
int /*thiscall*/ sub_5FBE20(int this)  // 实现：调: sub_5FBE20 sub_4920E0 sub_4600B0
{
  int v2; // edi
  int fld_14; // edi
  int fld_28; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  uint32_t *Block2; // edi
  uint32_t *v9; // eax
  void *fld_42; // eax
  uint32_t *fld_142; // eax
  int v12; // edx
  int v13; // edi
  signed int v14; // ecx
  unsigned int v15; // edx
  int result; // eax
  float fld_74; // [esp-8h] [ebp-38h]
  float fld_78; // [esp-4h] [ebp-34h]
  uint8_t v19[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  uint32_t *v21; // [esp+14h] [ebp-1Ch]
  int v22; // [esp+18h] [ebp-18h]
  int pObj; // [esp+1Ch] [ebp-14h]
  int fld_4; // [esp+20h] [ebp-10h]
  int v25; // [esp+2Ch] [ebp-4h]

  if ( *(uint8_t *)(this + 97) == 0  // this+97 【推断】附加门字节
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4)) != 9  // 涉及字段 “+4 宿主对象指针”
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 568))(*(uint32_t *)(this + 4)) != 9 )  // 涉及字段 “+4 宿主对象指针”
  {
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 560))(  // this+4 宿主对象
      *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
      9,
      0,
      0,
      0);
  }
  v2 = 100;
  if ( *(uint8_t *)(*(uint32_t *)(this + 20) + 170) == 0  // this+20 频道页号
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4)) != 0 )  // 涉及字段 “+4 宿主对象指针”
  {
    fld_14 = *(uint32_t *)(*(uint32_t *)(this + 20) + 148);  // this+20 频道页号
    fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
    fld_28 = **(uint32_t **)(this + 40);  // this+40 物品状态附属标志
    pObj = fld_4;
    v5 = (*(int (**)(void))(*(uint32_t *)fld_4 + 128))();  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_4 + 124))(fld_4, v5 + 10 * fld_14);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_28 + 40))(*(uint32_t *)(this + 40), v7);  // 涉及字段 “+40 状态子标志”
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 40) + 92))(*(uint32_t *)(this + 40), v19);  // 涉及字段 “+40 状态子标志”
    Block2 = Block;
    v25 = 0;
    if ( Block != v21 )
    {
      do
      {
        fld_78 = *(float *)(this + 120);  // 读 fld_78 = this+120（动画对象）
        fld_74 = *(float *)(this + 116);  // 读 fld_74 = this+116（观察者容器）
        v9 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 96))(*Block2);  // 结果 = 虚调用 vt+96
        sub_4920E0(v9, fld_74, fld_78);  // 调 批量改写全帧缩放
        ++Block2;
      }
      while ( Block2 != v21 );
    }
    fld_42 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
    sub_4600B0(fld_42, 2, 0, (int)v19);  // 调 演播层注册(槽号)
    fld_142 = *(uint32_t **)(this + 20);  // this+20 频道页号
    v12 = fld_142[11];
    v13 = fld_142[37];
    if ( v12 != 0 )
    {
      v15 = (int)((uint64_t)(780903145LL * (fld_142[12] - v12)) >> 32) >> 4;
      v14 = v15 + (v15 >> 31);
    }
    else
    {
      v14 = 0;
    }
    pObj = v13 / v14;
    v2 = (uint64_t)(255.0 - (double)(v13 / v14) * 155.0);
    v25 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
    Block = nullptr;
    v21 = nullptr;
    v22 = 0;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 0) != v2 )  // 判定 “+4 宿主对象指针”
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 0, v2);  // 涉及字段 “+4 宿主对象指针”
  if ( (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 1) != v2 )  // 判定 “+4 宿主对象指针”
    (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 1, v2);  // 涉及字段 “+4 宿主对象指针”
  result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 2);  // 涉及字段 “+4 宿主对象指针”
  if ( result != v2 )
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 2, v2);  // 涉及字段 “+4 宿主对象指针”
  return result;
}



// ------------------------------------------------------------
// 0x5FC010 sub_5FC010
// ------------------------------------------------------------
// 证: "STONE_DIE"
// 调: sub_5FC010 sub_4920E0 sub_4600B0
int /*thiscall*/ sub_5FC010(int this)  // 实现：调: sub_5FC010 sub_4920E0 sub_4600B0
{
  int fld_2C; // ebx
  int pObj; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  uint32_t *Block2; // edi
  uint32_t *v8; // eax
  void *fld_42; // eax
  float fld_74; // [esp-Ch] [ebp-34h]
  float fld_78; // [esp-8h] [ebp-30h]
  uint8_t v13[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  uint32_t *v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]
  int fld_4; // [esp+18h] [ebp-10h]
  int v18; // [esp+24h] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4)) != 0 )  // 判定 “+4 宿主对象指针”
  {
    fld_2C = **(uint32_t **)(this + 44);  // this+44 剩余时间 ms
    fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
    pObj = fld_4;
    v4 = (*(int (**)(void))(*(uint32_t *)fld_4 + 128))();  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 124))(pObj, v4 + 50);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v5);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_2C + 40))(*(uint32_t *)(this + 44), v6);  // this+44 剩余时间 ms
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 44) + 12))(*(uint32_t *)(this + 44), 0);  // this+44 剩余时间 ms
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 44) + 92))(*(uint32_t *)(this + 44), v13);  // this+44 剩余时间 ms
    Block2 = Block;
    v18 = 0;
    if ( Block != v15 )
    {
      do
      {
        fld_78 = *(float *)(this + 120);  // 读 fld_78 = this+120（动画对象）
        fld_74 = *(float *)(this + 116);  // 读 fld_74 = this+116（观察者容器）
        v8 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 96))(*Block2);  // 结果 = 虚调用 vt+96
        sub_4920E0(v8, fld_74, fld_78);  // 调 批量改写全帧缩放
        ++Block2;
      }
      while ( Block2 != v15 );
    }
    fld_42 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
    sub_4600B0(fld_42, 2, 0, (int)v13);  // 调 演播层注册(槽号)
    v18 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
    Block = nullptr;
    v15 = nullptr;
    v16 = 0;
  }
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(  // this+4 宿主对象
           *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
           "STONE_DIE",  // 字符串 “STONE_DIE”
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5FC120 sub_5FC120
// ------------------------------------------------------------
// 调: sub_5FC120 sub_699000 sub_698F90 sub_4D5E40 sub_497150
int /*thiscall*/ sub_5FC120(uint32_t *this)  // 实现：调: sub_5FC120 sub_699000 sub_698F90 sub_4D5E40 sub_497150
{
  uint32_t *pThis; // ebx
  int *fld_e1; // ecx
  int v3; // eax
  int result; // eax
  int v5; // edi
  int v6; // edi
  unsigned int i; // edx
  int v8; // ecx
  int v9; // ecx
  int *v10; // esi
  uint64_t v11; // rax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  int v17; // eax
  float v18; // [esp+4h] [ebp-2Ch] BYREF
  float v19; // [esp+8h] [ebp-28h]
  float v20; // [esp+Ch] [ebp-24h]
  int v21; // [esp+10h] [ebp-20h]
  int v22; // [esp+14h] [ebp-1Ch]
  int v23; // [esp+18h] [ebp-18h]
  uint32_t *pThis2; // [esp+1Ch] [ebp-14h]
  int v25; // [esp+20h] [ebp-10h]
  int v26; // [esp+24h] [ebp-Ch]
  int v27; // [esp+28h] [ebp-8h] BYREF
  unsigned int v28; // [esp+2Ch] [ebp-4h]

  pThis = this;
  fld_e1 = (int *)*(this + 1);  // this+4〔宿主对象〕
  v3 = *fld_e1;
  pThis2 = pThis;
  result = (*(int (/*thiscall*/ **)(int *))(v3 + 308))(fld_e1);  // 虚函数调用 槽+308
  if ( (uint8_t)result != 0 )
  {
    v5 = pThis[45];
    result = sub_699000((int)(pThis + 39));  // 【clock_now(clk)】
    if ( result >= v5 )
    {
      *((uint8_t *)pThis + 169) = 0;
      *((uint8_t *)pThis + 170) = 0;
      sub_698F90((int)(pThis + 39), 3000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pThis[1] + 80))(pThis[1]);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      v6 = result;
      v25 = result;
      if ( result != 0 )  // 若结果非 0（成功）
      {
        for ( i = 0; ; ++i )
        {
          v8 = *(uint32_t *)(v6 + 120);
          v28 = i;
          result = v8 != 0 ? (*(uint32_t *)(v6 + 124) - v8) >> 2 : 0;  // 向量元素数 = (end−begin)/4
          if ( (int)i >= result )
            break;
          v9 = *(uint32_t *)(v6 + 120);
          if ( v9 != 0 && i < (*(uint32_t *)(v6 + 124) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
            v10 = *(int **)(v9 + 4 * i);
          else
            v10 = nullptr;
          if ( (int *)pThis[1] != v10 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v10 + 40))(v10, 17) != 0 )  // 虚调用 vt+40
            {
              (*(void (/*thiscall*/ **)(int *, int))(*v10 + 672))(v10, 3);  // 虚调用 vt+672
              if ( (int)sub_4D5E40(9) < 100
                && (*(int (/*thiscall*/ **)(uint32_t, int *, uint32_t))(*(uint32_t *)pThis[1] + 8))(pThis[1], v10, 0) < 200 )  // 虚函数调用 槽+8：Update（166 行：CLICK_BUTTON2/DISSOLVE
              {
                v11 = (uint64_t)sub_497150(9, pThis[3]);  // 结果 = 第二组状态时长插值（flt_6CB2F0 → flt_6CB2F4）
                HIDWORD(v11) = *v10;  // 调 取 64 位值高 32 位
                v12 = v11;
                v18 = 0.0;
                v19 = 0.0;
                v20 = 0.0;
                v21 = 0;
                v22 = 0;
                v23 = 0;
                v26 = (*(int (/*thiscall*/ **)(int *))(HIDWORD(v11) + 120))(v10);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
                v13 = *v10;
                v18 = (float)v26;
                v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 124))(v10);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
                v15 = *v10;
                v26 = v14;
                v19 = (float)v14;
                v16 = (*(int (/*thiscall*/ **)(int *))(v15 + 192))(v10) / 2;  // 虚函数调用 槽+192
                v26 = (*(int (/*thiscall*/ **)(int *))(*v10 + 128))(v10) + v16;  // 结果 = 虚调用 vt+128
                v20 = (float)v26;
                v27 = 0;
                v17 = sub_605840(&v27, v10, &v18, 0);  // 结果 = 30 字节全局包
                sub_4E4A50(0, 48039, v12, 0, 0, 0, 1, 0, v27, v17);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
                v6 = v25;
                pThis = pThis2;
              }
            }
            i = v28;
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FC2F0 sub_5FC2F0
// ------------------------------------------------------------
// 调: sub_5FC2F0 sub_605840 sub_4E4A50 sub_5FC010
int /*thiscall*/ sub_5FC2F0(int this)  // 实现：调: sub_5FC2F0 sub_605840 sub_4E4A50 sub_5FC010
{
  unsigned int fld_58; // ecx
  unsigned int fld_5C; // eax
  uint64_t fld_7C; // rax
  int fld_4; // ecx
  int v6; // eax
  int fld_42; // ecx
  int v8; // eax
  int fld_43; // edi
  int v10; // ebx
  int v11; // eax
  int fld_44; // edx
  int v13; // eax
  float v15; // [esp+4h] [ebp-20h] BYREF
  float v16; // [esp+8h] [ebp-1Ch]
  float v17; // [esp+Ch] [ebp-18h]
  int v18; // [esp+10h] [ebp-14h]
  int v19; // [esp+14h] [ebp-10h]
  int v20; // [esp+18h] [ebp-Ch]
  int fld_5C2; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h] BYREF

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4)) == 9 )  // 判定 “+4 宿主对象指针”
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 560))(  // this+4 宿主对象
      *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
      0,
      0,
      0,
      0);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 0, -1);  // 涉及字段 “+4 宿主对象指针”
  (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 1, -1);  // 涉及字段 “+4 宿主对象指针”
  (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 2, -1);  // 涉及字段 “+4 宿主对象指针”
  fld_58 = *(uint32_t *)(this + 88);  // this+88 插值起点 Y
  fld_5C = *(uint32_t *)(this + 92) >> 1;  // this+92 插值起点 Z
  if ( fld_58 <= fld_5C )
  {
    fld_5C2 = *(uint32_t *)(this + 92) >> 1;  // this+92 插值起点 Z
    fld_7C = (uint64_t)((1.0 - (double)fld_58 / (double)fld_5C) * (double)*(int *)(this + 124));  // 涉及字段 “+124 光环动画件”
    fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
    *(uint32_t *)(this + 124) = fld_7C;  // 写 this+124 = fld_7C（光环动画件）
    v15 = 0.0;
    v16 = 0.0;
    v17 = 0.0;
    v18 = 0;
    v19 = 0;
    v20 = 0;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 120))(fld_4);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    fld_42 = *(uint32_t *)(this + 4);  // 读 fld_42 = this+4（宿主对象指针）
    fld_5C2 = v6;
    v15 = (float)v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_42 + 124))(fld_42);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    fld_43 = *(uint32_t *)(this + 4);  // 读 fld_43 = this+4（宿主对象指针）
    fld_5C2 = v8;
    v16 = (float)v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 192))(fld_43) / 2;  // 虚函数调用 槽+192
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 128))(fld_43);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    fld_44 = *(uint32_t *)(this + 4);  // 读 fld_44 = this+4（宿主对象指针）
    fld_5C2 = v11 + v10;
    v17 = (float)(v11 + v10);
    v22 = 0;
    v13 = sub_605840(&v22, fld_44, &v15, 1);  // 结果 = 30 字节全局包
    sub_4E4A50(*(uint32_t *)(this + 16), 48011, *(uint32_t *)(this + 124), 0, 0, 0, 1, 0, v22, v13);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  }
  return sub_5FC010(this);
}



// ------------------------------------------------------------
// 0x5FC450 sub_5FC450
// ------------------------------------------------------------
// 调: sub_5FC450 sub_41A5E0 sub_4DA0F0 sub_699000 sub_497120
char /*thiscall*/ sub_5FC450(int this)  // 实现：调: sub_5FC450 sub_41A5E0 sub_4DA0F0 sub_699000 sub_497120
{
  char result; // al
  int fld_4; // edi
  double v4; // st7
  int fld_54; // ebx
  int fld_90; // ebx
  int *fld_42; // ecx
  int v8; // edi
  int fld_102; // eax
  int fld_94; // edx
  int fld_103; // ebx
  int fld_902; // eax
  int fld_43; // edi
  int v14; // ebx
  int v15; // eax
  int v16; // [esp-20h] [ebp-2Ch]
  int v17; // [esp-1Ch] [ebp-28h]
  int v18; // [esp-18h] [ebp-24h]
  char v19; // [esp-Ch] [ebp-18h]
  int fld_64; // [esp-8h] [ebp-14h]
  int v21; // [esp+4h] [ebp-8h]
  int v22; // [esp+8h] [ebp-4h]
  int fld_542; // [esp+8h] [ebp-4h]
  int v24; // [esp+8h] [ebp-4h]
  int fld_10; // [esp+8h] [ebp-4h]

  result = *(uint8_t *)(this + 97);  // this+97 【推断】附加门字节
  if ( result == 0 )
  {
    fld_4 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 3);  // 涉及字段 “+4 宿主对象指针”
    v22 = sub_41A5E0(fld_4 + 410);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v4 = (double)v22 * COERCE_FLOAT(sub_41A5E0(fld_4 + 634));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    if ( (int)(uint64_t)v4 < 100 )
    {
      fld_64 = *(uint32_t *)(this + 100);  // this+100 插值终点 Y
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 3);  // 涉及字段 “+4 宿主对象指针”
      v21 = sub_4DA0F0(fld_64);  // 调 受方属性抗性值
      if ( v21 < 150 )
      {
        fld_54 = *(uint32_t *)(this + 84);  // this+84 插值起点 X
        if ( sub_699000(this + 60) >= fld_54 )  // 【clock_now(clk)】
          fld_542 = *(uint32_t *)(this + 84);  // this+84 插值起点 X
        else
          fld_542 = sub_699000(this + 60);  // 【clock_now(clk)】
        sub_497120(*(uint32_t *)(this + 8), *(uint32_t *)(this + 12));  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
        v24 = (uint64_t)((flt_9A0624 - (double)v21 * flt_9A0628)
                               * (double)(int)(uint64_t)(v4 * (double)fld_542 * 0.001)
                               * 0.0099999998);  // ×0.01f（百分数转比例）
        fld_10 = (uint64_t)(sub_433F60(*(uint32_t *)(this + 16), 0) * (double)v24);  // 调 PVP 平衡系数路由（研究第 17/27 轮）
        fld_90 = fld_10 - *(uint32_t *)(this + 144);  // this+144 第 4 组·+1040 增量子倍率
        if ( fld_10 != *(uint32_t *)(this + 144) )  // this+144 第 4 组·+1040 增量子倍率
        {
          fld_42 = *(int **)(this + 4);  // this+4 宿主对象
          v8 = *fld_42;
          fld_102 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*fld_42 + 736))(fld_42, 0, *(uint32_t *)(this + 16));  // 结果 = 虚调用 vt+736
          (*(void (/*thiscall*/ **)(uint32_t, int))(v8 + 728))(*(uint32_t *)(this + 4), fld_102 - fld_90);  // 涉及字段 “+4 宿主对象指针”
          *(uint32_t *)(this + 144) = fld_10;  // this+144 第 4 组·+1040 增量子倍率
        }
        if ( *(uint32_t *)(this + 152) < (unsigned int)sub_699000(this + 60) )  // 【clock_now(clk)】
        {
          fld_94 = *(uint32_t *)(this + 148);  // 读 fld_94 = this+148（动画帧计数）
          fld_103 = *(uint32_t *)(this + 16);  // this+16 频道型选中索引
          fld_902 = *(uint32_t *)(this + 144);  // this+144 第 4 组·+1040 增量子倍率
          *(uint32_t *)(this + 148) = fld_902;  // 写 this+148 = fld_902（动画帧计数）
          fld_43 = *(uint32_t *)(this + 4);  // 读 fld_43 = this+4（宿主对象指针）
          v19 = dword_8F7C04 == fld_103;  // 全局 dword_8F7C04 = 本机角色对象
          v18 = fld_902 - fld_94;
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 192))(fld_43);  // 虚函数调用 槽+192
          v17 = v14 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 128))(fld_43) + 15;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 124))(fld_43);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
          v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 120))(fld_43);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
          sub_4D7960(v14, fld_43, this, v15, v16, v17, v18, 4, 0, v19);  // 【飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）】
          *(uint32_t *)(this + 152) = sub_699000(this + 60) + 500;  // clock_now(clk)
        }
      }
    }
    return sub_5FC120((uint32_t *)this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FC610 sub_5FC610
// ------------------------------------------------------------
// 证: "BLOOD_DROP_LOOP"
// 调: sub_5FC610 sub_699000 sub_4924C0 sub_4D7960
void /*usercall*/ sub_5FC610(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：调: sub_5FC610 sub_699000 sub_4924C0 sub_4D7960
{
  int v4; // edi
  double v5; // st7
  int i; // edi
  int *v7; // ecx
  int v8; // eax
  int v9; // ebx
  bool v10; // cl
  int pObj2; // edi
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int *v15; // ecx
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int pObj3; // edi
  uint32_t *v21; // ebx
  uint8_t v22; // al
  bool v23; // cf
  uint64_t v24; // rax
  int v25; // ebx
  int v26; // edx
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  void *v31; // eax
  int v32; // [esp-18h] [ebp-58h]
  int v33; // [esp-14h] [ebp-54h]
  char v34; // [esp-4h] [ebp-44h]
  uint8_t v35[4]; // [esp+4h] [ebp-3Ch] BYREF
  void *Block; // [esp+8h] [ebp-38h]
  uint8_t v37[4]; // [esp+14h] [ebp-2Ch] BYREF
  void *v38; // [esp+18h] [ebp-28h]
  int v39; // [esp+1Ch] [ebp-24h]
  int v40; // [esp+20h] [ebp-20h]
  int v41; // [esp+24h] [ebp-1Ch]
  int v42; // [esp+28h] [ebp-18h]
  int pObj; // [esp+2Ch] [ebp-14h]
  uint8_t v44; // [esp+33h] [ebp-Dh]
  int v45; // [esp+3Ch] [ebp-4h]

  if ( *(uint8_t *)(pArg1 + 97) == 0 && *(uint32_t *)(pArg1 + 196) < (unsigned int)sub_699000(pArg1 + 60) )  // 【clock_now(clk)】
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 4) + 200))(*(uint32_t *)(pArg1 + 4), nArg3, nArg2);  // 涉及字段 “+4 宿主对象指针”
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 40))(*(uint32_t *)(pArg1 + 4), 273) == 0  // 判定 “+4 宿主对象指针”
      || v4 == *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 688))(*(uint32_t *)(pArg1 + 4))  // 涉及字段 “+4 宿主对象指针”
      || v4 == *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 688))(*(uint32_t *)(pArg1 + 4)) + 8)  // 涉及字段 “+4 宿主对象指针”
      || v4 == *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 688))(*(uint32_t *)(pArg1 + 4)) + 20)  // 涉及字段 “+4 宿主对象指针”
      || v4 == *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 1068))(*(uint32_t *)(pArg1 + 4)) )  // 涉及字段 “+4 宿主对象指针”
    {
      v5 = 1.0;
      v44 = 0;
    }
    else
    {
      v5 = 1.5;
      v44 = 1;
    }
    v41 = (uint64_t)((double)*(int *)(pArg1 + 200) * v5);  // pArg1+200〔nMainState(推断)〕
    v42 = 120;
    pObj = 70;
    for ( i = 0; ; ++i )
    {
      v7 = *(int **)(pArg1 + 20);  // pArg1+20〔nPage(推断)〕
      v8 = v7[11];
      if ( v8 != 0 )
        v8 = (v7[12] - v8) / 88;
      if ( i >= v8 )
        break;
      v9 = v44;
      *(uint32_t *)(sub_4924C0(v7, i) + 48) = *(&v42 + v9);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
    }
    v10 = dword_8F7C04 == *(uint32_t *)(pArg1 + 16);  // 全局 dword_8F7C04 = 本机角色对象
    pObj2 = *(uint32_t *)(pArg1 + 4);  // 读 pObj2 = pArg1+4（宿主对象指针）
    v12 = *(uint32_t *)pObj2;
    pObj = pObj2;
    v34 = v10;
    v13 = (*(int (/*thiscall*/ **)(int))(v12 + 192))(pObj2);  // 虚函数调用 槽+192
    v33 = v13 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2) + 15;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 124))(pObj2);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    sub_4D7960(v13, pObj2, pArg1, v14, v32, v33, v41, 4, 0, v34);  // 【飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）】
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 308))(*(uint32_t *)(pArg1 + 4)) != 0 )  // 判定 “+4 宿主对象指针”
    {
      v15 = *(int **)(pArg1 + 4);  // pArg1+4〔宿主对象〕
      v16 = *v15;
      v17 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*v15 + 736))(v15, 1, 0);  // 结果 = 虚调用 vt+736
      (*(void (/*thiscall*/ **)(uint32_t, int))(v16 + 728))(*(uint32_t *)(pArg1 + 4), v17 - v41);  // 涉及字段 “+4 宿主对象指针”
    }
    v38 = nullptr;
    v39 = 0;
    v40 = 0;
    v18 = *(uint32_t *)(dword_8F7A24 + 244);  // 全局 dword_8F7A24 = 登录/选区管理器
    v45 = 0;
    if ( v18 != 0 )
    {
      v19 = v18 - 1;
      if ( v19 != 0 )
      {
        if ( v19 == 1 )
        {
LABEL_28:
          *(uint32_t *)(pArg1 + 196) = sub_699000(pArg1 + 60) + 1000;  // clock_now(clk)
          (*(void (/*thiscall*/ **)(uint32_t, const char *, int))(**(uint32_t **)(pArg1 + 4) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
            *(uint32_t *)(pArg1 + 4),  // 涉及字段 “+4 宿主对象指针”
            "BLOOD_DROP_LOOP",  // 字符串 “BLOOD_DROP_LOOP”
            -1);
          if ( v38 != nullptr )  // 若 v38 有效（非空）
            j__free(v38);  // 调 堆释放
          return;
        }
        pObj3 = v41;
      }
      else
      {
        pObj3 = dword_8F82CC;
      }
    }
    else
    {
      pObj3 = dword_8F82D0;
    }
    if ( pObj3 != 0 )
    {
      v21 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 36))(pObj3);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
      v22 = v44;
      v23 = v44 != 0;
      v21[4] = 50;
      v21[1] = v23 ? 10 : 3;
      v21[3] = v22 != 0 ? 80 : 30;
      v41 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 192))(*(uint32_t *)(pArg1 + 4));  // 涉及字段 “+4 宿主对象指针”
      v24 = (uint64_t)((double)v41 * 0.69999999);
      v21[5] = v24;
      if ( (*(int (/*fastcall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4), HIDWORD(v24)) != 0 )  // 判定 “+4 宿主对象指针”
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 12))(pObj3, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
        v25 = *(uint32_t *)pObj3;
        v26 = **(uint32_t **)(pArg1 + 4);  // pArg1+4〔宿主对象〕
        pObj = *(uint32_t *)(pArg1 + 4);  // 读 pObj = pArg1+4（宿主对象指针）
        v27 = (*(int (**)(void))(v26 + 128))();  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
        v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 124))(pObj, v27);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        v29 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v28);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        (*(void (/*thiscall*/ **)(int, int))(v25 + 40))(pObj3, v29);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
        v30 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj3 + 92))(pObj3, v35);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
        LOBYTE(v45) = 1;  // 调 取 16 位值低 8 位
        sub_4E77D0((int)v37, v30);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
        LOBYTE(v45) = 0;  // 调 取 16 位值低 8 位
        if ( Block != nullptr )  // 若 Block 有效（非空）
          j__free(Block);  // 调 堆释放
        v31 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4));  // 涉及字段 “+4 宿主对象指针”
        sub_4600B0(v31, 2, 0, (int)v37);  // 调 演播层注册(槽号)
      }
    }
    goto LABEL_28;
  }
}


// ------------------------------------------------------------
// 0x5FC900 sub_5FC900
// ------------------------------------------------------------
// 调: sub_5FC900 sub_698FE0 sub_699030 sub_431230 sub_5E5260
void /*thiscall*/ sub_5FC900(int this)  // 实现：调: sub_5FC900 sub_698FE0 sub_699030 sub_431230 sub_5E5260
{
  int fld_4; // edi
  int fld_42; // eax
  uint8_t v4[4]; // [esp+8h] [ebp-20h] BYREF
  int v5; // [esp+Ch] [ebp-1Ch]
  int v6; // [esp+10h] [ebp-18h]
  int v7; // [esp+14h] [ebp-14h]
  uint32_t v8[4]; // [esp+18h] [ebp-10h] BYREF

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4)) == 4 )  // 判定 “+4 宿主对象指针”
  {
    if ( *(uint8_t *)(this + 74) != 0 && *(uint8_t *)(this + 96) == 0 )  // this+74 【推断】复位字节 B
      sub_698FE0(this + 60);  // 【clock_unfreeze(clk)】
  }
  else
  {
    if ( *(uint8_t *)(this + 74) == 0 )  // this+74 【推断】复位字节 B
      sub_699030(this + 60);  // 【clock_freeze(clk)】
    fld_4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
    fld_42 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 568))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
    if ( *(uint8_t *)(this + 97) == 0 && fld_4 != 3 && fld_42 != 3 && fld_4 != 4 && fld_42 != 4 && fld_4 != 5 && fld_42 != 5 )  // this+97 【推断】附加门字节
    {
      v5 = 0;
      v6 = 0;
      v7 = 0;
      v8[3] = 0;
      v8[0] = 4;
      sub_431230(v8);  // uint32 vector push_back
      v8[0] = 2;
      sub_431230(v8);  // uint32 vector push_back
      v8[0] = 0;
      sub_431230(v8);  // uint32 vector push_back
      v8[0] = 0;
      sub_431230(v8);  // uint32 vector push_back
      v8[0] = 0;
      sub_431230(v8);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int, uint32_t))(**(uint32_t **)(this + 4) + 560))(  // this+4 宿主对象
        *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
        4,
        v4,
        2,
        0);
      sub_5E5260(v4);  // 调 动画子对象清理临时缓冲
    }
  }
}



// ------------------------------------------------------------
// 0x5FCA50 sub_5FCA50
// ------------------------------------------------------------
// 调: sub_5FCA50 sub_699000 sub_497120 sub_41A5E0 sub_433F60
char /*usercall*/ sub_5FCA50@<al>(int pArg1@<ecx>, double fArg2@<st0>)  // 实现：调: sub_5FCA50 sub_699000 sub_497120 sub_41A5E0 sub_433F60
{
  int v3; // eax
  int v4; // ebx
  int v5; // eax
  int pObj3; // ecx
  int v7; // edi
  int v8; // edi
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  int v12; // ebx
  int *v13; // ecx
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int pObj4; // edi
  int v20; // edx
  int v21; // ebx
  int v22; // eax
  int v23; // ebx
  int pObj2; // edi
  int v25; // eax
  int *v26; // ecx
  int v27; // eax
  void *v28; // eax
  bool v29; // zf
  signed int nRand; // eax
  int v31; // eax
  const char *v32; // ecx
  int v33; // eax
  int *v34; // edi
  int v35; // eax
  int v36; // eax
  int v37; // ebx
  int v38; // eax
  int v39; // edx
  int v40; // ebx
  int v41; // eax
  int v42; // eax
  int v44; // [esp-20h] [ebp-6Ch]
  int v45; // [esp-1Ch] [ebp-68h]
  int v46; // [esp-18h] [ebp-64h]
  int v47; // [esp-14h] [ebp-60h]
  int v48; // [esp-10h] [ebp-5Ch]
  int v49; // [esp-10h] [ebp-5Ch]
  int v50; // [esp-Ch] [ebp-58h]
  int v51; // [esp-Ch] [ebp-58h]
  char v52; // [esp-Ch] [ebp-58h]
  int v53; // [esp-Ch] [ebp-58h]
  void *v54[4]; // [esp+4h] [ebp-48h] BYREF
  float v55; // [esp+14h] [ebp-38h]
  int v56; // [esp+18h] [ebp-34h]
  int pObj; // [esp+1Ch] [ebp-30h]
  uint8_t v58[4]; // [esp+20h] [ebp-2Ch] BYREF
  uint32_t v59[7]; // [esp+24h] [ebp-28h] BYREF
  int v60; // [esp+48h] [ebp-4h]

  v59[6] = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  LOBYTE(v3) = *(uint8_t *)(pArg1 + 97);  // 调 取 16 位值低 8 位
  if ( (uint8_t)v3 == 0 )
  {
    v4 = *(uint32_t *)(pArg1 + 84);  // pArg1+84〔pFxObjA(推断)〕
    if ( sub_699000(pArg1 + 60) >= v4 )  // 【clock_now(clk)】
      v5 = *(uint32_t *)(pArg1 + 84);  // pArg1+84〔pFxObjA(推断)〕
    else
      v5 = sub_699000(pArg1 + 60);  // 【clock_now(clk)】
    v50 = *(uint32_t *)(pArg1 + 12);  // pArg1+12〔nSkillRec12(推断)〕
    v48 = *(uint32_t *)(pArg1 + 8);  // pArg1+8〔nSkillRec8(推断)〕
    pObj = v5;
    sub_497120(v48, v50);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
    pObj3 = *(uint32_t *)(pArg1 + 4);  // pArg1+4〔宿主对象〕
    v56 = (uint64_t)(fArg2 * (double)pObj * 0.001);
    v7 = (*(int (/*fastcall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj3 + 672))(  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
           pObj3,
           (uint64_t)(fArg2 * (double)pObj * 0.001) >> 32,
           3);
    pObj = sub_41A5E0(v7 + 312);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v55 = COERCE_FLOAT(sub_41A5E0(v7 + 536));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v8 = (uint64_t)((double)pObj * v55);
    if ( v8 < 100 )
    {
      v9 = (100 - v8) * (uint64_t)(sub_433F60(*(uint32_t *)(pArg1 + 16), 0) * (double)v56);  // 调 PVP 平衡系数路由（研究第 17/27 轮）
      v10 = *(uint32_t *)(pArg1 + 128);  // pArg1+128〔szStatusKeyBuf(推断)〕
      v11 = v9 / 100;
      v12 = v9 / 100 - v10;
      if ( v9 / 100 != v10 )
      {
        v13 = *(int **)(pArg1 + 4);  // pArg1+4〔宿主对象〕
        v51 = *(uint32_t *)(pArg1 + 16);  // pArg1+16〔nChannelTypeSel(推断)〕
        v56 = *v13;
        v14 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(v56 + 736))(v13, 0, v51);  // 虚函数调用 槽+736：属性块首值（GetHP 族，此处索引）
        (*(void (/*thiscall*/ **)(uint32_t, int))(v56 + 728))(*(uint32_t *)(pArg1 + 4), v14 - v12);  // 虚函数调用 槽+728：vec3 尾插 thunk（+1076 表）
        *(uint32_t *)(pArg1 + 128) = v11;  // pArg1+128〔szStatusKeyBuf(推断)〕
      }
      if ( *(uint32_t *)(pArg1 + 140) < (unsigned int)sub_699000(pArg1 + 60) )  // 【clock_now(clk)】
      {
        v15 = *(uint32_t *)(pArg1 + 136);  // pArg1+136〔nCtx136(推断)〕
        v16 = *(uint32_t *)(pArg1 + 16);  // pArg1+16〔nChannelTypeSel(推断)〕
        v17 = *(uint32_t *)(pArg1 + 128);  // pArg1+128〔szStatusKeyBuf(推断)〕
        *(uint32_t *)(pArg1 + 136) = v17;  // pArg1+136〔nCtx136(推断)〕
        v18 = v17 - v15;
        pObj4 = *(uint32_t *)(pArg1 + 4);  // pArg1+4〔宿主对象〕
        v20 = *(uint32_t *)pObj4;
        pObj = pObj4;
        v52 = dword_8F7C04 == v16;  // 全局 dword_8F7C04 = 本机角色对象
        v46 = v18;
        v21 = (*(int (/*thiscall*/ **)(int))(v20 + 192))(pObj4);  // 虚函数调用 槽+192
        v45 = v21 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 128))(pObj4) + 15;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
        v44 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 124))(pObj4);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 120))(pObj4);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        sub_4D7960(v21, pObj4, pArg1, v22, v44, v45, v46, 4, 0, v52);  // 【飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）】
        *(uint32_t *)(pArg1 + 140) = sub_699000(pArg1 + 60) + 500;  // clock_now(clk)
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 940))(*(uint32_t *)(pArg1 + 4)) == 0  // 虚函数调用 槽+940
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4)) != 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      {
        v23 = **(uint32_t **)(pArg1 + 40);  // pArg1+40〔bStateSub40(推断)〕
        pObj2 = *(uint32_t *)(pArg1 + 4);  // pArg1+4〔宿主对象〕
        v25 = *(uint32_t *)pObj2;
        pObj = pObj2;
        v53 = (*(int (**)(void))(v25 + 128))() + 70;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
        v49 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 124))(pObj2);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        v47 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        (*(void (/*thiscall*/ **)(uint32_t))(v23 + 40))(*(uint32_t *)(pArg1 + 40));  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(pArg1 + 40) + 92))(*(uint32_t *)(pArg1 + 40), v54);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
        v26 = *(int **)(pArg1 + 4);  // pArg1+4〔宿主对象〕
        v27 = *v26;
        v60 = 0;
        v28 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v27 + 80))(v26, 2, 0, v54);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        sub_4600B0(v28, v47, v49, v53);  // 调 演播层注册(槽号)
        v60 = -1;
        sub_5E5260(v54);  // 调 动画子对象清理临时缓冲
      }
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 28))(pArg1);  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
      if ( v3 >= *(uint32_t *)(pArg1 + 132) + 300 )  // pArg1+132〔nAgeTicks〕
      {
        if ( rand() % 5 == 0 && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4)) != 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        {
          sub_401710("Common/ActiveStatus/Animation/");  // 字符串 “Common/ActiveStatus/Animation/”
          v60 = 1;
          nRand = rand() & 0x80000001;  // 调 取伪随机数
          v29 = nRand == 0;
          if ( nRand < 0 )
            v29 = (((uint8_t)nRand - 1) | 0xFFFFFFFE) == -1;
          if ( v29 )
            sub_402410("PoisonFloor1.ani");  // 字符串 “PoisonFloor1.ani”
          else
            sub_402410("PoisonFloor2.ani");  // 字符串 “PoisonFloor2.ani”
          v56 = sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
          LOBYTE(v60) = 2;  // 调 取 16 位值低 8 位
          if ( v56 != 0 )
          {
            v31 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
            v55 = *(float *)&v31;
            LOBYTE(v60) = 3;  // 调 取 16 位值低 8 位
            if ( v31 != 0 )
            {
              v32 = (const char *)v59[0];
              if ( v59[5] < 0x10u )
                v32 = (const char *)v59;
              v33 = sub_431860(v31, v32, 1);  // 结果 = 动画件构造（资源 id 版）
              LOBYTE(v60) = 2;  // 调 取 16 位值低 8 位
              v34 = (int *)sub_44E1F0(v33, 1);  // 结果 = CNRDPooledObject 构造（虚表覆盖壳）
            }
            else
            {
              LOBYTE(v60) = 2;  // 调 取 16 位值低 8 位
              v34 = (int *)sub_44E1F0(0, 1);  // 结果 = CNRDPooledObject 构造（虚表覆盖壳）
            }
          }
          else
          {
            v34 = nullptr;
          }
          v35 = *v34;
          LOBYTE(v60) = 1;  // 调 取 16 位值低 8 位
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v35 + 36))(v34) + 8) = 2;  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
          v36 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4));  // 虚函数调用 槽+80：槽（参数写入 3 转发）
          sub_45FE80(v36, (int)v34, 2, 0, (int)v34, 0, 0);  // 调 对象注册
          v37 = *v34;
          v38 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 152))(*(uint32_t *)(pArg1 + 4));  // 虚函数调用 槽+152：效果通道 3
          (*(void (/*thiscall*/ **)(int *, int))(v37 + 148))(v34, v38);  // 虚函数调用 槽+148：槽（12 行）
          v39 = **(uint32_t **)(pArg1 + 4);  // pArg1+4〔宿主对象〕
          v40 = *v34;
          pObj = *(uint32_t *)(pArg1 + 4);  // pArg1+4〔宿主对象〕
          v41 = (*(int (/*stdcall*/ **)(uint32_t))(v39 + 124))(0);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
          v42 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v41);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
          (*(void (/*thiscall*/ **)(int *, int))(v40 + 112))(v34, v42);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
          v60 = -1;
          sub_501490(v58);  // 调 对象析构后释放堆块
        }
        v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 28))(pArg1);  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
        *(uint32_t *)(pArg1 + 132) = v3;  // pArg1+132〔nAgeTicks〕
      }
    }
    else
    {
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 4))(pArg1, 0, 0);  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x5FCE10 sub_5FCE10
// ------------------------------------------------------------
// 证: "Common/ActiveStatus/Animation/FreezeDie.ani" | "FROZEN_DIE"
// 调: sub_5FCE10 sub_42FCB0 sub_431860 sub_4920E0 sub_44B6C0
void /*userpurge*/ sub_5FCE10(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, char pszArg4)  // 实现：调: sub_5FCE10 sub_42FCB0 sub_431860 sub_4920E0 sub_44B6C0
{
  uint32_t *v5; // ebx
  char *v6; // eax
  char *v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int pObj; // edi
  int v18; // ebx
  int v19; // edx
  int v20; // eax
  int v21; // eax
  int v22; // eax
  char *v23; // edi
  uint32_t *v24; // eax
  void *v25; // eax
  int v26; // [esp+24h] [ebp-34h]
  int nArg32; // [esp+2Ch] [ebp-2Ch]
  float v28; // [esp+2Ch] [ebp-2Ch]
  int nArg22; // [esp+30h] [ebp-28h]
  float v30; // [esp+30h] [ebp-28h]
  int v31; // [esp+34h] [ebp-24h]
  char v32[4]; // [esp+38h] [ebp-20h] BYREF
  void *Block; // [esp+3Ch] [ebp-1Ch]
  char *v34; // [esp+40h] [ebp-18h]
  int *v35; // [esp+48h] [ebp-10h]
  int v36; // [esp+54h] [ebp-4h]
  int *v37; // [esp+60h] [ebp+8h]
  int *v38; // [esp+60h] [ebp+8h]

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4)) != 0 )  // 判定 “+4 宿主对象指针”
  {
    nArg22 = nArg2;
    nArg32 = nArg3;
    if ( pszArg4 != 0 )
    {
      v5 = nullptr;
      v36 = 0;
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v5 = (uint32_t *)sub_431860((char)"Common/ActiveStatus/Animation/FreezeDie.ani", 1);  // 字符串 “Common/ActiveStatus/Animation/FreezeDie.ani”
      sub_4920E0(v5, *(float *)(pArg1 + 108), *(float *)(pArg1 + 112));  // 调 批量改写全帧缩放
      v6 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      v7 = v6;
      v36 = 1;
      if ( v6 != nullptr )  // 若 v6 有效（非空）
      {
        sub_44E0D0(v6, (int)v5, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)v7 = &CNRDPooledObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
      }
      else
      {
        v7 = nullptr;
      }
      v8 = **(uint32_t **)(pArg1 + 4);  // pArg1+4〔宿主对象〕
      v26 = *(uint32_t *)(pArg1 + 4);  // 读 v26 = pArg1+4（宿主对象指针）
      v36 = -1;
      v9 = (*(int (**)(void))(v8 + 80))();  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      sub_45FE80(v9, (int)v7, 2, 0, (int)v7, v26, 0);  // 调 对象注册
      v10 = *(uint32_t *)v7;
      v11 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 4) + 152))(*(uint32_t *)(pArg1 + 4), nArg32, nArg22);  // 涉及字段 “+4 宿主对象指针”
      (*(void (/*thiscall*/ **)(char *, int))(v10 + 148))(v7, v11);  // 虚函数调用 槽+148：槽（12 行）
      v12 = *(uint32_t *)v7;
      v37 = *(int **)(pArg1 + 4);  // pArg1+4〔宿主对象〕
      v13 = *v37;
      v35 = v37;
      v14 = (*(int (**)(void))(v13 + 128))();  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      v15 = (*(int (/*thiscall*/ **)(int *, int))(*v37 + 124))(v37, v14);  // 结果 = 虚调用 vt+124
      v16 = (*(int (/*thiscall*/ **)(int *, int))(*v35 + 120))(v35, v15);  // 结果 = 虚调用 vt+120
      (*(void (/*thiscall*/ **)(char *, int))(v12 + 112))(v7, v16);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    }
    pObj = dword_8F82BC;
    v18 = *(uint32_t *)dword_8F82BC;
    v38 = *(int **)(pArg1 + 4);  // pArg1+4〔宿主对象〕
    v19 = *v38;
    v35 = v38;
    v20 = (*(int (/*stdcall*/ **)(int, int))(v19 + 128))(nArg32, nArg22);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v21 = (*(int (/*thiscall*/ **)(int *, int))(*v38 + 124))(v38, v20 + 50);  // 结果 = 虚调用 vt+124
    v22 = (*(int (/*thiscall*/ **)(int *, int))(*v35 + 120))(v35, v21);  // 结果 = 虚调用 vt+120
    (*(void (/*thiscall*/ **)(int, int))(v18 + 40))(pObj, v22);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj + 92))(pObj, v32);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    v23 = (char *)Block;
    v36 = 2;
    if ( Block != v34 )
    {
      do
      {
        v30 = *(float *)(pArg1 + 112) * 1.5;  // 涉及字段 “+112 宿主组件”
        v28 = *(float *)(pArg1 + 108) * 1.5;  // pArg1+108〔nAdd108(推断)〕
        v24 = (uint32_t *)(*(int (**)(void))(**(uint32_t **)v23 + 96))();  // 虚函数调用 槽+96：槽（4BE520 + 44E8D0）
        sub_4920E0(v24, v28, v30);  // 调 批量改写全帧缩放
        v23 += 4;
      }
      while ( v23 != v34 );
    }
    v25 = (void *)(*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4), 2);  // 涉及字段 “+4 宿主对象指针”
    sub_4600B0(v25, 0, (int)v32, v31);  // 调 演播层注册(槽号)
    (*(void (/*thiscall*/ **)(uint32_t, const char *))(**(uint32_t **)(pArg1 + 4) + 212))(*(uint32_t *)(pArg1 + 4), "FROZEN_DIE");  // 字符串 “FROZEN_DIE”
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
  }
}


// ------------------------------------------------------------
// 0x5FD010 CNRDActiveStatus__vmt2C
// ------------------------------------------------------------
// 调: sub_5FABA0 sub_5FCA50 sub_698FE0 sub_699030 sub_4600B0
char /*usercall*/ sub_5FD010@<al>(int pArg1@<ecx>, int nArg2@<ebx>)  // 实现：调: sub_5FABA0 sub_5FCA50 sub_698FE0 sub_699030 sub_4600B0
{
  bool v3; // zf
  char v4; // al
  int v5; // edi
  int v6; // eax
  int v7; // ebx
  int pObj; // edi
  int v9; // edx
  int *v10; // ecx
  int v11; // edx
  void *v12; // eax
  int i; // edi
  int v14; // ebx
  int v15; // eax
  int pObj2; // ecx
  int v17; // eax
  int *v18; // ecx
  int v19; // eax
  void *v20; // eax
  int v21; // edi
  int v22; // eax
  int v24; // [esp-10h] [ebp-48h]
  int v25; // [esp-Ch] [ebp-44h]
  int v26; // [esp-8h] [ebp-40h]
  int pObj32; // [esp-8h] [ebp-40h]
  uint8_t v29[16]; // [esp+8h] [ebp-30h] BYREF
  uint8_t v30[16]; // [esp+18h] [ebp-20h] BYREF
  int pObj3; // [esp+28h] [ebp-10h]
  int v32; // [esp+34h] [ebp-4h]

  switch ( *(uint32_t *)(pArg1 + 8) )  // 按 *(uint32_t *)(pArg1 + 8) 分派
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      sub_5FABA0(pArg1);
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      sub_5FCA50(pArg1);
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 840))(*(uint32_t *)(pArg1 + 4)) == 9;  // 涉及字段 “+4 宿主对象指针”
      v4 = *(uint8_t *)(pArg1 + 74);  // 读 v4 = pArg1+74（复位字节 B）
      if ( v3 )
      {
        if ( v4 != 0 && *(uint8_t *)(pArg1 + 96) == 0 )  // 判定 “+96 状态开关字节”
        {
          sub_698FE0(pArg1 + 60);  // 【clock_unfreeze(clk)】
          *(uint8_t *)(pArg1 + 204) = 1;  // pArg1+204〔pSubAnim204(推断)〕
        }
      }
      else
      {
        if ( v4 == 0 && *(uint8_t *)(pArg1 + 204) == 0 )  // pArg1+204〔pSubAnim204(推断)〕
          sub_699030(pArg1 + 60);  // 【clock_freeze(clk)】
        v5 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 840))(*(uint32_t *)(pArg1 + 4));  // 涉及字段 “+4 宿主对象指针”
        v6 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 568))(*(uint32_t *)(pArg1 + 4));  // 涉及字段 “+4 宿主对象指针”
        if ( *(uint8_t *)(pArg1 + 97) == 0 && v5 != 3 && v6 != 3 && v5 != 4 && v6 != 4 && v5 != 5 && v6 != 5 && v6 != 9 )  // 判定 “+97 附加门字节”
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 560))(  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
            *(uint32_t *)(pArg1 + 4),  // 涉及字段 “+4 宿主对象指针”
            9,
            0,
            0,
            0);
      }
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 940))(*(uint32_t *)(pArg1 + 4)) == 0  // 判定 “+4 宿主/关联对象”
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4)) != 0 )  // 涉及字段 “+4 宿主对象指针”
      {
        v7 = **(uint32_t **)(pArg1 + 40);  // pArg1+40〔bStateSub40(推断)〕
        pObj = *(uint32_t *)(pArg1 + 4);  // 读 pObj = pArg1+4（宿主/关联对象）
        v9 = *(uint32_t *)pObj;
        pObj3 = pObj;
        v26 = (*(int (/*thiscall*/ **)(int))(v9 + 128))(pObj) + 70;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
        v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        (*(void (/*thiscall*/ **)(uint32_t))(v7 + 40))(*(uint32_t *)(pArg1 + 40));  // 涉及字段 “+40 状态子标志”
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(pArg1 + 40) + 92))(*(uint32_t *)(pArg1 + 40), v30);  // 涉及字段 “+40 状态子标志”
        v10 = *(int **)(pArg1 + 4);  // pArg1+4〔pHost4〕
        v11 = *v10;
        v32 = 0;
        v12 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v11 + 80))(v10, 2, 0, v30);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        sub_4600B0(v12, v24, v25, v26);  // 调 演播层注册(槽号)
        v32 = -1;
        sub_5E5260(v30);  // 调 动画子对象清理临时缓冲
      }
      break;
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      sub_5FBE20(pArg1);
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      sub_5FC900(pArg1);
      break;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      sub_5FC450(pArg1);
      break;
    case 0xB:
      sub_5FC610(pArg1);
      break;
    case 0xD:
      if ( *(uint8_t *)(pArg1 + 97) == 0  // 判定 “+97 附加门字节”
        && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 940))(*(uint32_t *)(pArg1 + 4)) == 0  // 涉及字段 “+4 宿主对象指针”
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4)) != 0 )  // 涉及字段 “+4 宿主对象指针”
      {
        for ( i = 0; i < 2; ++i )  // 循环：i 从 0 递增到 2
        {
          v14 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 120))(*(uint32_t *)(pArg1 + 4), nArg2);  // 涉及字段 “+4 宿主对象指针”
          v15 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 124))(*(uint32_t *)(pArg1 + 4));  // 涉及字段 “+4 宿主对象指针”
          pObj2 = *(uint32_t *)(pArg1 + 4);  // 读 pObj2 = pArg1+4（宿主/关联对象）
          pObj3 = v15;
          if ( i != 0 )
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
          else
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2) + 50;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
          nArg2 = v17;
          pObj32 = pObj3;
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4 * i + 40) + 40))(*(uint32_t *)(pArg1 + 4 * i + 40));  // 虚调用 vt+40
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4 * i + 40) + 92))(*(uint32_t *)(pArg1 + 4 * i + 40));  // 虚调用 vt+40
          v18 = *(int **)(pArg1 + 4);  // pArg1+4〔pHost4〕
          v19 = *v18;
          v32 = 1;
          v20 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v19 + 80))(v18, 2, 0, v29);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
          sub_4600B0(v20, (int)v29, v14, pObj32);  // 调 演播层注册(槽号)
          v32 = -1;
          sub_5E5260(v29);  // 调 动画子对象清理临时缓冲
        }
      }
      break;
    default:
      break;
  }
  v21 = *(uint32_t *)(pArg1 + 84);  // 读 v21 = pArg1+84（状态结束时刻）
  v22 = sub_699000(pArg1 + 60);  // 【clock_now(clk)】
  if ( v22 >= v21 )
  {
    LOBYTE(v22) = *(uint8_t *)(pArg1 + 97);  // 调 取 16 位值低 8 位
    if ( (uint8_t)v22 == 0 )
      LOBYTE(v22) = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 764))(  // 虚函数调用 槽+764
                      *(uint32_t *)(pArg1 + 4),  // 涉及字段 “+4 宿主对象指针”
                      *(uint32_t *)(pArg1 + 8),  // 涉及字段 “+8 技能槽记录首字”
                      0,
                      0,
                      0);
  }
  return v22;
}


// ------------------------------------------------------------
// 0x5FD310 CNRDActiveStatus__vmt40
// ------------------------------------------------------------
// 证: "CONDITION_REMOVE"
// 调: sub_5FCE10 sub_5FC2F0 sub_431230 sub_5E5260
void /*usercall*/ CNRDActiveStatus__vmt40(int pArg1@<ecx>, int nArg2@<ebx>)  // 函数定义: 取观察者容器
{
  void *pBuf[4]; // [esp+8h] [ebp-20h] BYREF
  uint32_t v4[4]; // [esp+18h] [ebp-10h] BYREF

  (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
    *(uint32_t *)(pArg1 + 4),  // 涉及字段 “+4 宿主对象指针”
    "CONDITION_REMOVE",  // 字符串 “CONDITION_REMOVE”
    -1,
    0,
    0);
  switch ( *(uint32_t *)(pArg1 + 8) )  // 按 *(uint32_t *)(pArg1 + 8) 分派
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 848))(*(uint32_t *)(pArg1 + 4), 0);  // 涉及字段 “+4 宿主对象指针”
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 840))(*(uint32_t *)(pArg1 + 4)) == 9 )  // 判定 “+4 宿主/关联对象”
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 560))(  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
          *(uint32_t *)(pArg1 + 4),  // 涉及字段 “+4 宿主对象指针”
          0,
          0,
          0,
          0);
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 252))(*(uint32_t *)(pArg1 + 4), 0, -1);  // 涉及字段 “+4 宿主对象指针”
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 4) + 252))(*(uint32_t *)(pArg1 + 4), 1, -1);  // 涉及字段 “+4 宿主对象指针”
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 4) + 252))(*(uint32_t *)(pArg1 + 4), 2, -1);  // 涉及字段 “+4 宿主对象指针”
      if ( *(uint32_t *)(pArg1 + 88) <= *(uint32_t *)(pArg1 + 92) >> 1 )  // 判定 “+88 累计推进量”
        sub_5FCE10(pArg1, nArg2, 0, 1);
      else
        sub_5FCE10(pArg1, nArg2, 0, 0);
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 216))(*(uint32_t *)(pArg1 + 4), 2);  // 涉及字段 “+4 宿主对象指针”
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 848))(*(uint32_t *)(pArg1 + 4), 0);  // 涉及字段 “+4 宿主对象指针”
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 840))(*(uint32_t *)(pArg1 + 4)) == 9 )  // 判定 “+4 宿主/关联对象”
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 560))(  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
          *(uint32_t *)(pArg1 + 4),  // 涉及字段 “+4 宿主对象指针”
          0,
          0,
          0,
          0);
      break;
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 216))(*(uint32_t *)(pArg1 + 4), 4);  // 涉及字段 “+4 宿主对象指针”
      break;
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 848))(*(uint32_t *)(pArg1 + 4), 0);  // 涉及字段 “+4 宿主对象指针”
      sub_5FC2F0(pArg1);
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 840))(*(uint32_t *)(pArg1 + 4)) == 4 )  // 判定 “+4 宿主/关联对象”
      {
        memset(&pBuf[1], 0, 12);  // 清零 12 字节块
        v4[0] = 4;
        v4[3] = 0;
        sub_431230((int)pBuf, v4);  // uint32 vector push_back
        v4[0] = 2;
        sub_431230((int)pBuf, v4);  // uint32 vector push_back
        v4[0] = 0;
        sub_431230((int)pBuf, v4);  // uint32 vector push_back
        v4[0] = 0;
        sub_431230((int)pBuf, v4);  // uint32 vector push_back
        v4[0] = 0;
        sub_431230((int)pBuf, v4);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t, int, void **, int, uint32_t))(**(uint32_t **)(pArg1 + 4) + 560))(  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
          *(uint32_t *)(pArg1 + 4),  // 涉及字段 “+4 宿主对象指针”
          4,
          pBuf,
          2,
          0);
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      }
      break;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 216))(*(uint32_t *)(pArg1 + 4), 3);  // 涉及字段 “+4 宿主对象指针”
      break;
    case 0xB:
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 4) + 208))(*(uint32_t *)(pArg1 + 4), *(uint32_t *)(pArg1 + 20));  // 涉及字段 “+4 宿主对象指针”
      break;
    case 0x10:
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 216))(*(uint32_t *)(pArg1 + 4), 40100);  // 涉及字段 “+4 宿主对象指针”
      break;
    default:
      return;
  }
}



// ------------------------------------------------------------
// 0x5FD5C0 CNRDActiveStatus__vmt44
// ------------------------------------------------------------
// 调: sub_5FC010 sub_5FCE10
int /*usercall*/ CNRDActiveStatus__vmt44@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：调: sub_5FC010 sub_5FCE10
{
  int v4; // eax

  v4 = *(uint32_t *)(pArg1 + 8) - 1;  // 涉及字段 “+8 技能槽记录首字”
  *(uint8_t *)(pArg1 + 97) = 1;  // 写 pArg1+97 = 1（附加门字节）
  if ( v4 != 0 )
  {
    if ( v4 == 6 )
    {
      sub_5FC010(pArg1);
      return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 4))(pArg1, 0, 0);  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
    }
  }
  else
  {
    sub_5FCE10(pArg1, nArg2, nArg3, 1);
  }
  return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 4))(pArg1, 0, 0);  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
}



// ------------------------------------------------------------
// 0x5FD600 sub_5FD600
// ------------------------------------------------------------
// 调: sub_5FD600
int /*thiscall*/ sub_5FD600(int this)  // 实现：调: sub_5FD600
{
  *(uint32_t *)(this + 80) = 0;  // this+80 关联角色对象
  *(uint32_t *)(this + 84) = 0;  // this+84 插值起点 X
  *(uint8_t *)(this + 88) = 0;  // this+88 插值起点 Y
  *(uint32_t *)(this + 92) = 0;  // this+92 插值起点 Z
  *(uint8_t *)(this + 96) = 0;  // this+96 插值终点 X / 落点偏移
  *(uint32_t *)(this + 100) = 0;  // this+100 插值终点 Y
  *(uint8_t *)(this + 104) = 1;  // this+104 插值终点 Z
  *(uint32_t *)(this + 108) = 0;  // this+108 第 1 组·宿主属性 +886 增量
  *(uint32_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  *(uint32_t *)(this + 116) = 0;  // 写 this+116 = 0（观察者容器）
  *(uint8_t *)(this + 120) = 0;  // 写 this+120 = 0（动画对象）
  *(uint32_t *)(this + 124) = 0;  // 写 this+124 = 0（光环动画件）
  return 0;
}



// ------------------------------------------------------------
// 0x5FD630 sub_5FD630
// ------------------------------------------------------------
// 调: sub_5FD630
int /*thiscall*/ sub_5FD630(void *this)  // 实现：调: sub_5FD630
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);  // this+120 动画对象指针
}



// ------------------------------------------------------------
// 0x5FD640 CNChangeHp__vmt78
// ------------------------------------------------------------
// 证: 叶子函数（10 行，无外调无字符串）
char /*thiscall*/ CNChangeHp__vmt78(int this, int nArg2, int nArg3, char pszArg4, int nArg5)  // 实现：证: 叶子函数（10 行，无外调无字符串）
{
  *(uint32_t *)(this + 80) = nArg2;  // 写 this+80 = nArg2（HP 变更值）
  *(uint32_t *)(this + 84) = nArg3;  // 写 this+84 = nArg3（持续时长 ms）
  *(uint8_t *)(this + 88) = pszArg4;  // 写 this+88 = pszArg4（显示控制标志）
  *(uint32_t *)(this + 100) = nArg5;  // 写 this+100 = nArg5（效果模式）
  *(uint8_t *)(this + 96) = 0;  // 写 this+96 = 0（模式 2 分支标志）
  return pszArg4;
}



// ------------------------------------------------------------
// 0x5FD670 CNChangeHp__vmt20
// ------------------------------------------------------------
// 证: 叶子函数（9 行，无外调无字符串）
char /*thiscall*/ CNChangeHp__vmt20(uint32_t **this, char pszArg2)  // 函数定义: 设置坐标三元组 (this+100..112)
{
  char result; // al

  result = pszArg2;
  if ( pszArg2 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 1) + 216))(*(this + 1), 8);  // 虚函数调用 槽+216：音效 TAG 查询
  return result;
}



// ------------------------------------------------------------
// 0x5FD690 CNChangeHp__vmt54
// ------------------------------------------------------------
// 调: sub_4939E0
char /*thiscall*/ CNChangeHp__vmt54(int this, char pszArg2)  // 实现：调: sub_4939E0
{
  char result; // al
  int fld_74; // ecx  | +0x0074 → 飘字动画件（0x5FD6C0: sub_4938F0(*(this+116)) 驱动恢复数字飘字）（CNChangeHp；va=005FD6C0）

  result = IRDAppendage__vmt54((uint8_t *)this, pszArg2);  // result = 调 IRDAppendage__vmt54
  fld_74 = *(uint32_t *)(this + 116);  // 读 fld_74 = this+116（飘字动画件）
  if ( fld_74 != 0 )
    return sub_4939E0(fld_74, pszArg2);  // 播放/暂停级联（递归子链 +204）
  return result;
}



// ------------------------------------------------------------
// 0x5FD6C0 CNChangeHp__vmt14
// ------------------------------------------------------------
// 调: sub_4938F0 sub_491D00 sub_699000 sub_491690
uint32_t **/*thiscall*/ CNChangeHp__vmt14(int this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 实现：调: sub_4938F0 sub_491D00 sub_699000 sub_491690
{
  uint32_t **result; // eax
  int fld_74; // ecx  | +0x0074 → 飘字动画件（0x5FD6C0: sub_4938F0(*(this+116)) 驱动恢复数字飘字）（CNChangeHp；va=005FD6C0）
  uint64_t fld_4; // rax  | +0x0004 → 宿主对象指针（CNChangeHp；va=005FD6C0）
  uint32_t **v9; // ebx
  int pThis_8; // edi
  uint32_t *v11; // esi
  float v12; // [esp+14h] [ebp+10h]

  result = *(uint32_t ***)(this + 100);  // this+100 效果模式
  if ( pszArg2 != 0 )
  {
    if ( result == (uint32_t **)1 )
    {
      fld_74 = *(uint32_t *)(this + 116);  // 读 fld_74 = this+116（飘字动画件）
      if ( fld_74 != 0 )
      {
        sub_4938F0(fld_74);  // 调 调 sub_4938F0
        v12 = (float)nArg4;
        fld_4 = (uint64_t)(v12
                              - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))  // 涉及字段 “+4 宿主对象指针”
                              * 0.60000002);
        return (uint32_t **)sub_491D00(dword_79C0B0, nArg3, fld_4, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
    }
  }
  else if ( result == (uint32_t **)2 )
  {
    result = (uint32_t **)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
    v9 = result;
    if ( result != nullptr )  // 若 result 有效（非空）
    {
      pThis_8 = ((uint8_t)(((sub_699000(this + 8) / 0x50u) & 1) != 0 ? -78 : 80) << 24) | 0xFFFFFF;  // 【clock_now(clk)】
      sub_491690(1, 2, 1, -13487361, pThis_8, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
      result = (uint32_t **)v9[51];
      v11 = *result;
      if ( *result != result )
      {
        do
        {
          result = (uint32_t **)sub_491690(1, 2, 1, -13487361, pThis_8, 1);  // 结果 = 图层后处理配置（this+176..196 图层参数块写入）
          v11 = (uint32_t *)*v11;
        }
        while ( v11 != v9[51] );
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FD7C0 CNChangeHp__vmt4
// ------------------------------------------------------------
// 调: sub_433F60 sub_699000
void /*usercall*/ sub_5FD7C0(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 【CNChangeHp__vmt4】
{
  double v4; // st7
  double v5; // st7
  int v6; // eax
  int v7; // ecx
  char *v8; // eax
  int pObj7; // ecx
  int v10; // eax
  int *v11; // ecx
  int v12; // edx
  int v13; // eax
  int pObj2; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int *v18; // ecx
  int v19; // edx
  char *v20; // eax
  int pObj; // edi
  int v22; // ebx
  int v23; // ebx
  int v24; // eax
  int v25; // edi
  double v26; // st7
  int v27; // eax
  uint64_t v28; // rax
  int v29; // ecx
  void **v30; // ebx
  int v31; // edi
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int pObj4; // edi
  int v36; // ebx
  int v37; // edx
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int *v41; // ecx
  int v42; // eax
  void *v43; // eax
  int v44; // eax
  int *v45; // ecx
  int v46; // edx
  char *v47; // eax
  int pObj3; // edi
  int v49; // ebx
  int v50; // ebx
  int *v51; // ecx
  int v52; // edx
  void *v53; // eax
  void *Block2; // eax
  uint32_t *Block3; // edi
  int v56; // eax
  int pObj5; // ecx
  int v58; // eax
  double v59; // st7
  int v60; // eax
  int nRand; // eax
  double v62; // st7
  int pObj8; // ecx
  int v64; // edi
  int v65; // eax
  int v66; // eax
  int v67; // eax
  float v68; // [esp+1Ch] [ebp-58h]
  float v69; // [esp+20h] [ebp-54h]
  int pObj62; // [esp+20h] [ebp-54h]
  float v71; // [esp+20h] [ebp-54h]
  int v72; // [esp+24h] [ebp-50h]
  int v75; // [esp+34h] [ebp-40h]
  void *v76[4]; // [esp+38h] [ebp-3Ch] BYREF
  char v77[4]; // [esp+48h] [ebp-2Ch] BYREF
  void *Block; // [esp+4Ch] [ebp-28h]
  char *v79; // [esp+50h] [ebp-24h]
  int v80; // [esp+54h] [ebp-20h]
  float v81; // [esp+58h] [ebp-1Ch]
  char *v82; // [esp+5Ch] [ebp-18h]
  float i; // [esp+60h] [ebp-14h]
  int pObj6; // [esp+64h] [ebp-10h]
  int v85; // [esp+70h] [ebp-4h]

  sub_5F66C0();  // 【IRDAppendage__vmt4】
  if ( *(uint8_t *)(pArg1 + 96) == 0 && *(uint8_t *)(pArg1 + 88) != 0 )  // pArg1+96〔bMode2Flag〕
  {
    if ( *(float *)(pArg1 + 80) <= 0.0 )  // pArg1+80〔nHpDelta〕
      v4 = sub_433F60(*(uint32_t *)(pArg1 + 36), 0);  // 调 PVP 平衡系数路由（研究第 17/27 轮）
    else
      v4 = sub_433F60(*(uint32_t *)(pArg1 + 4), 2);  // 调 PVP 平衡系数路由（研究第 17/27 轮）
    v5 = v4 * *(float *)(pArg1 + 80);  // pArg1+80〔nHpDelta〕
    *(uint8_t *)(pArg1 + 96) = 1;  // pArg1+96〔bMode2Flag〕
    *(float *)(pArg1 + 80) = v5;  // pArg1+80〔nHpDelta〕
  }
  if ( *(uint8_t *)(pArg1 + 104) != 0 )  // pArg1+104〔nTimerEnd(推断)〕
  {
    if ( *(uint32_t *)(pArg1 + 84) == -1 )  // pArg1+84〔nDurationMs〕
    {
      if ( sub_699000(pArg1 + 8) >= *(uint32_t *)(pArg1 + 112) + 500 )  // 【clock_now(clk)】
      {
        v6 = *(uint32_t *)(pArg1 + 92);  // pArg1+92〔pFxObjC(推断)〕
        v7 = *(uint32_t *)(pArg1 + 108);  // pArg1+108〔nAdd108(推断)〕
        if ( v6 != v7 )
        {
          v8 = (char *)(v6 - v7);
          pObj7 = *(uint32_t *)(pArg1 + 4);  // pArg1+4〔pHostObj〕
          v82 = v8;
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj7 + 120))(pObj7);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
          v11 = *(int **)(pArg1 + 4);  // pArg1+4〔pHostObj〕
          v12 = *v11;
          pObj6 = v10;
          v13 = (*(int (/*thiscall*/ **)(int *))(v12 + 124))(v11);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
          pObj2 = *(uint32_t *)(pArg1 + 4);  // pArg1+4〔pHostObj〕
          i = *(float *)&v13;
          v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 192))(pObj2);  // 虚函数调用 槽+192
          sub_4D7960(  // 【飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）】
            v16 + v15,
            pObj2,
            pArg1,
            pObj6,
            SLODWORD(i),  // 调 取 64 位值低 32 位(带符号)
            v16 + v15,
            (int)v82,
            2 * ((int)v82 <= 0) + 2,
            0,
            dword_8F7C04 == *(uint32_t *)(pArg1 + 36));  // 全局 dword_8F7C04 = 本机角色对象
          *(uint32_t *)(pArg1 + 108) = *(uint32_t *)(pArg1 + 92);  // pArg1+108〔nAdd108(推断)〕
          *(uint32_t *)(pArg1 + 112) = sub_699000(pArg1 + 8);  // clock_now(clk)
        }
      }
    }
    else if ( *(uint32_t *)(pArg1 + 112) == 0 )  // pArg1+112〔pHostComp112〕
    {
      v17 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 120))(*(uint32_t *)(pArg1 + 4));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      v18 = *(int **)(pArg1 + 4);  // pArg1+4〔pHostObj〕
      v19 = *v18;
      i = *(float *)&v17;
      v20 = (char *)(*(int (/*thiscall*/ **)(int *))(v19 + 124))(v18);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      pObj = *(uint32_t *)(pArg1 + 4);  // pArg1+4〔pHostObj〕
      v82 = v20;
      v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 192))(pObj) + v22;  // 虚函数调用 槽+192
      v24 = 2;
      if ( *(float *)(pArg1 + 80) <= 0.0 )  // pArg1+80〔nHpDelta〕
        v24 = 1;
      sub_4D7960(v23, pObj, pArg1, SLODWORD(i), (int)v82, v23, (uint64_t)*(float *)(pArg1 + 80), v24, 0, 0);  // 【飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）】
      *(uint32_t *)(pArg1 + 112) = 1;  // pArg1+112〔pHostComp112〕
    }
  }
  v25 = *(uint32_t *)(pArg1 + 84);  // pArg1+84〔nDurationMs〕
  if ( v25 == -1 )
  {
    v82 = (char *)sub_699000(pArg1 + 8);  // 【clock_now(clk)】
    v26 = (double)(int)v82 * *(float *)(pArg1 + 80) * 0.001;  // pArg1+80〔nHpDelta〕
  }
  else if ( v25 != 0 )
  {
    v27 = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
    v82 = (char *)(uint64_t)*(float *)(pArg1 + 80);  // pArg1+80〔nHpDelta〕
    v69 = (float)(int)v82;
    v26 = sub_4049C0(0.0, v69, v27, v25);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  }
  else
  {
    v26 = *(float *)(pArg1 + 80);  // pArg1+80〔nHpDelta〕
  }
  v28 = (uint64_t)v26;
  v29 = *(uint32_t *)(pArg1 + 92);  // pArg1+92〔pFxObjC(推断)〕
  if ( (unsigned int)(uint64_t)v26 != v29 )
  {
    v30 = *(void ***)(pArg1 + 4);  // pArg1+4〔pHostObj〕
    HIDWORD(v28) = *(uint32_t *)(pArg1 + 36);  // 调 取 64 位值高 32 位
    *(uint32_t *)(pArg1 + 92) = v28;  // pArg1+92〔pFxObjC(推断)〕
    v31 = v28 - v29;
    v82 = (char *)*v30;
    v32 = (*((int (/*thiscall*/ **)(void **, uint32_t, uint32_t))v82 + 184))(v30, 0, HIDWORD(v28));  // 虚函数调用 槽+184：动画对象 z 倾斜转状态码
    (*((void (/*thiscall*/ **)(void **, int))v82 + 182))(v30, v31 + v32);  // 虚函数调用 槽+182
  }
  v33 = *(uint32_t *)(pArg1 + 100);  // pArg1+100〔nEffMode〕
  if ( v33 == 1 )
  {
    v34 = *(uint32_t *)(pArg1 + 116);  // pArg1+116〔pNumAnim〕
    if ( v34 != 0 && *(int *)(v34 + 148) >= 4 && *(uint8_t *)(pArg1 + 120) == 0 )  // pArg1+120〔pAnimObj〕
    {
      pObj4 = dword_8F82B4;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F82B4 + 12))(dword_8F82B4, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      v36 = *(uint32_t *)pObj4;
      v37 = **(uint32_t **)(pArg1 + 4);  // pArg1+4〔pHostObj〕
      pObj6 = *(uint32_t *)(pArg1 + 4);  // pArg1+4〔pHostObj〕
      v38 = (*(int (**)(void))(v37 + 128))();  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      v39 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 124))(pObj6, v38 + 60);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      v40 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 120))(pObj6, v39);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      (*(void (/*thiscall*/ **)(int, int))(v36 + 40))(pObj4, v40);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj4 + 92))(pObj4, v76);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
      v41 = *(int **)(pArg1 + 4);  // pArg1+4〔pHostObj〕
      v42 = *v41;
      v85 = 0;
      v43 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v42 + 80))(v41, 2, 0, v76);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      sub_4600B0(v43, nArg3, nArg2, v75);  // 调 演播层注册(槽号)
      (*(void (/*thiscall*/ **)(uint32_t, const char *))(**(uint32_t **)(pArg1 + 4) + 212))(*(uint32_t *)(pArg1 + 4), "HP_RECOVERED");  // 字符串 “HP_RECOVERED”
      *(uint8_t *)(pArg1 + 120) = 1;  // pArg1+120〔pAnimObj〕
      v85 = -1;
      sub_5E5260(v76);  // 调 动画子对象清理临时缓冲
    }
  }
  else if ( v33 == 2 )
  {
    v44 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 120))(*(uint32_t *)(pArg1 + 4));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    v45 = *(int **)(pArg1 + 4);  // pArg1+4〔pHostObj〕
    v46 = *v45;
    pObj6 = v44;
    v47 = (char *)(*(int (/*thiscall*/ **)(int *))(v46 + 124))(v45);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    pObj3 = *(uint32_t *)(pArg1 + 4);  // pArg1+4〔pHostObj〕
    v82 = v47;
    v49 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 192))(pObj3) / 2;  // 虚函数调用 槽+192
    v50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 128))(pObj3) + v49;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v72 = (int)v82;
    pObj62 = pObj6;
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 124) + 40))(*(uint32_t *)(pArg1 + 124));  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(pArg1 + 124) + 92))(*(uint32_t *)(pArg1 + 124), v77);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    v51 = *(int **)(pArg1 + 4);  // pArg1+4〔pHostObj〕
    v52 = *v51;
    v85 = 1;
    v53 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v52 + 80))(v51, 2, 0, v77);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    sub_4600B0(v53, pObj62, v72, v50);  // 调 演播层注册(槽号)
    Block2 = Block;
    Block3 = Block;
    v82 = (char *)Block;
    if ( Block != v79 )
    {
      while ( 1 )  // 无限循环
      {
        v56 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block3 + 128))(*Block3);  // 结果 = 虚调用 vt+128
        pObj5 = *Block3;
        if ( v56 <= v50 )
        {
          v60 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 120))(pObj5);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
          v59 = v60 <= pObj6 ? 1.3 : -1.3;
        }
        else
        {
          v58 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 120))(pObj5);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
          v59 = v58 <= pObj6 ? 0.5 : -0.5;
        }
        i = v59;
        nRand = rand();  // 调 取伪随机数
        v71 = i + 0.5;
        v68 = i - 0.5;
        v62 = sub_4049C0(v68, v71, nRand % 100, 99);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        pObj8 = *Block3;
        v81 = v62;
        v64 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 96))(pObj8);  // 虚函数调用 槽+96：槽（4BE520 + 44E8D0）
        for ( i = 0.0; ; ++LODWORD(i) )  // 调 取 64 位值低 32 位
        {
          v65 = *(uint32_t *)(v64 + 44);
          if ( v65 != 0 )
            v65 = (*(uint32_t *)(v64 + 48) - v65) / 88;
          if ( SLODWORD(i) >= v65 )  // 调 取 64 位值低 32 位(带符号)
            break;
          v66 = sub_4924C0(LODWORD(i));  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
          *(float *)(v66 + 28) = v81;
        }
        v82 += 4;
        if ( v82 == v79 )
          break;
        Block3 = v82;
      }
      Block2 = Block;
    }
    v85 = -1;
    if ( Block2 != nullptr )  // 若 Block2 有效（非空）
      j__free(Block2);  // 调 堆释放
    Block = nullptr;
    v79 = nullptr;
    v80 = 0;
  }
  if ( *(uint32_t *)(pArg1 + 84) != -1  // pArg1+84〔nDurationMs〕
    && *(uint32_t *)(pArg1 + 92) == (uint64_t)*(float *)(pArg1 + 80)  // pArg1+80〔nHpDelta〕
    && (*(uint32_t *)(pArg1 + 100) != 1 || (v67 = *(uint32_t *)(pArg1 + 116)) == 0 || *(uint8_t *)(v67 + 170) != 0) )  // pArg1+100〔nEffMode〕
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 76))(pArg1, 0);  // 虚函数调用 槽+76：槽（542940 + 485020）
  }
}


// ------------------------------------------------------------
// 0x5FDC90 sub_5FDC90
// ------------------------------------------------------------
// 调: sub_5FDC90 sub_42AF90 sub_657740
int /*thiscall*/ sub_5FDC90(int this)  // 实现：调: sub_5FDC90 sub_42AF90 sub_657740
{
  int fld_74; // edi
  int result; // eax
  int (/*thiscall*/ ***pThis_7C)(uint32_t, int); // ecx

  fld_74 = *(uint32_t *)(this + 116);  // 读 fld_74 = this+116（观察者容器）
  if ( fld_74 != 0 )
  {
    sub_42AF90(*(void ***)(this + 116));  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_74, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_7C = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 124);  // this+124 第 2 组·+858/+1292 增量
  *(uint32_t *)(this + 116) = 0;  // 写 this+116 = 0（观察者容器）
  if ( pThis_7C != nullptr )  // 若 pThis_7C 有效（非空）
    result = (**pThis_7C)(pThis_7C, 1);  // 调 pThis_7C 的虚函数（vt+0）
  *(uint32_t *)(this + 124) = 0;  // 写 this+124 = 0（光环动画件）
  return result;
}



// ------------------------------------------------------------
// 0x5FDCE0 CNChangeHp__vmt1C
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/Heal.ani" | "Character/Swordman/Effect/Particle/DOTAreaDa"
// 调: sub_42FCB0 sub_431860 sub_4926A0 sub_428F30 sub_4924C0
void /*usercall*/ CNChangeHp__vmt1C(int pArg1@<ecx>, int nArg2@<edi>)  // 实现：调: sub_42FCB0 sub_431860 sub_4926A0 sub_428F30 sub_4924C0
{
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  uint32_t *pMem; // eax
  uint32_t *v9; // eax
  int pObj; // edi
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int pObj2; // esi
  int v20; // eax
  BOOL v22; // [esp-4h] [ebp-1Ch]
  void *Block; // [esp+8h] [ebp-10h]
  void *Blocka; // [esp+8h] [ebp-10h]

  v3 = *(uint32_t *)(pArg1 + 100);  // 读 v3 = pArg1+100（效果模式）
  *(uint32_t *)(pArg1 + 92) = 0;  // pArg1+92〔pFxObjC(推断)〕
  *(uint8_t *)(pArg1 + 104) = 1;  // pArg1+104〔nTimerEnd(推断)〕
  *(uint32_t *)(pArg1 + 108) = 0;  // pArg1+108〔nAdd108(推断)〕
  *(uint32_t *)(pArg1 + 112) = 0;  // 写 pArg1+112 = 0（宿主组件）
  if ( v3 == 1 && *(float *)(pArg1 + 80) <= 0.0 )  // 判定 “+80 HP 变更值”
    *(uint32_t *)(pArg1 + 100) = 0;  // 写 pArg1+100 = 0（效果模式）
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 && dword_8F7C04 != 0 )  // 全局 dword_8F7A24 = 登录/选区管理器
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 376))(*(uint32_t *)(pArg1 + 4));  // 涉及字段 “+4 宿主对象指针”
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) != v4 )  // 全局 dword_8F7C04 = 本机角色对象
    {
      if ( *(uint32_t *)(pArg1 + 100) == 1 )  // 判定 “+100 效果模式”
        *(uint32_t *)(pArg1 + 100) = 0;  // 写 pArg1+100 = 0（效果模式）
      if ( *(float *)(pArg1 + 80) > 0.0 )  // 判定 “+80 HP 变更值”
        *(uint8_t *)(pArg1 + 104) = 0;  // pArg1+104〔nTimerEnd(推断)〕
    }
  }
  v5 = *(uint32_t *)(pArg1 + 100);  // 读 v5 = pArg1+100（效果模式）
  if ( v5 == 1 )
  {
    if ( *(uint32_t *)(pArg1 + 116) == 0 )  // 判定 “+116 飘字动画件”
    {
      v6 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
      if ( v6 != 0 )
        v7 = sub_431860(v6, "Common/CommonEffect/Animation/Heal.ani", 1);  // 字符串 “Common/CommonEffect/Animation/Heal.ani”
      else
        v7 = 0;
      *(uint32_t *)(pArg1 + 116) = v7;  // 写 pArg1+116 = v7（飘字动画件）
    }
    sub_4926A0(*(uint32_t *)(pArg1 + 116));  // 帧游标复位（+44 帧数组；递归子链 +204）
    *(uint8_t *)(pArg1 + 120) = 0;  // 写 pArg1+120 = 0（动画对象）
  }
  else if ( v5 == 2 )
  {
    if ( *(uint32_t *)(pArg1 + 124) == 0 )  // 判定 “+124 光环动画件”
    {
      pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v9 = sub_428F30(pMem, (int)"Character/Swordman/Effect/Particle/DOTAreaDamage.ptl", 0);  // 字符串 “Character/Swordman/Effect/Particle/DOTAreaDa”
      else
        v9 = nullptr;
      *(uint32_t *)(pArg1 + 124) = v9;  // 写 pArg1+124 = v9（光环动画件）
    }
    pObj = *(uint32_t *)(pArg1 + 124);  // 读 pObj = pArg1+124（光环动画件）
    Block = (void *)(*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 192))(*(uint32_t *)(pArg1 + 4), nArg2);  // 涉及字段 “+4 宿主对象指针”
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 36))(pObj) + 20) = Block;  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
    v11 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 688))(*(uint32_t *)(pArg1 + 4));  // 涉及字段 “+4 宿主对象指针”
    if ( v11 != 0 )
    {
      v12 = *(uint32_t *)(v11 + 44);
      if ( v12 != 0 && (*(uint32_t *)(v11 + 48) - v12) / 88 > 0 )
      {
        v13 = sub_4924C0(0);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
        Blocka = (void *)sub_4918E0(v13, 1);  // 结果 = 动画盒四边界提取（研究 P29 族）
        v14 = sub_4924C0(0);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
        v22 = sub_4918E0(v14, 0) <= (int)Blocka;  // 结果 = 动画盒四边界提取（研究 P29 族）
        v15 = sub_4924C0(0);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
        v16 = 2 * sub_4918E0(v15, v22);  // 结果 = 动画盒四边界提取（研究 P29 族）
        *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 124) + 36))(*(uint32_t *)(pArg1 + 124)) + 12) = v16;  // 涉及字段 “+124 光环动画件”
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 124) + 12))(*(uint32_t *)(pArg1 + 124), 0);  // 涉及字段 “+124 光环动画件”
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 124) + 112))(*(uint32_t *)(pArg1 + 124), *(uint32_t *)(pArg1 + 4));  // 涉及字段 “+124 光环动画件；+4 宿主对象指针”
  }
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 && *(float *)(pArg1 + 80) > 0.0 )  // 全局 dword_8F7A24 = 登录/选区管理器
  {
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 64))(pArg1);  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
    v18 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v17 + 32) + 576))(*(uint32_t *)(v17 + 32));  // 虚函数调用 槽+576
    if ( __RTDynamicCast(v18, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0) == dword_8F7C04 )  // 全局 dword_8F7C04 = 本机角色对象
    {
      pObj2 = *(uint32_t *)(pArg1 + 4);  // 读 pObj2 = pArg1+4（宿主对象指针）
      if ( pObj2 != dword_8F7C04 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )  // 全局 dword_8F7C04 = 本机角色对象
      {
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 全局 dword_8F7C04 = 本机角色对象
        sub_496010((int)dword_99FD58, v20, 11, 1);  // 帧图像重载工厂（事件号 +48 → sub_495DC0 等）
      }
    }
  }
}



// ------------------------------------------------------------
// 0x5FDF60 CNMovementController__vmt4
// ------------------------------------------------------------
// 证: 叶子函数（32 行，无外调无字符串）
int /*thiscall*/ CNMovementController__vmt4(int this)  // 实现：证: 叶子函数（32 行，无外调无字符串）
{
  int result; // eax
  int fld_4; // eax  | +0x0004 → 宿主对象指针（0x5FDF60: vt+840 门、宿主 +6608/+6612 速度面、vt+876 应用）（CNMovementController；va=005FDF60）

  IRDAppendage__vmt4((int *)this);
  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4));  // 涉及字段 “+4 宿主对象指针”
  if ( result == 0 )
  {
    fld_4 = *(uint32_t *)(*(uint32_t *)(this + 4) + 6608);  // 涉及字段 “+4 宿主对象指针”
    if ( fld_4 > *(uint32_t *)(this + 92) || fld_4 < *(uint32_t *)(this + 88) )  // 判定 “+92 速度上限；+88 速度下限”
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 876))(  // this+4 宿主对象指针
        *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
        0,
        *(uint32_t *)(*(uint32_t *)(this + 4) + 6608),  // 涉及字段 “+4 宿主对象指针”
        *(uint32_t *)(*(uint32_t *)(this + 4) + 6608),  // 涉及字段 “+4 宿主对象指针”
        0,
        0,
        1);
    result = *(uint32_t *)(*(uint32_t *)(this + 4) + 6612);  // 涉及字段 “+4 宿主对象指针”
    if ( result > *(uint32_t *)(this + 92) || result < *(uint32_t *)(this + 88) )  // 判定 “+92 速度上限；+88 速度下限”
      return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 876))(  // this+4 宿主对象指针
               *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
               1,
               *(uint32_t *)(*(uint32_t *)(this + 4) + 6612),  // 涉及字段 “+4 宿主对象指针”
               *(uint32_t *)(*(uint32_t *)(this + 4) + 6612),  // 涉及字段 “+4 宿主对象指针”
               0,
               0,
               1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FDFE0 sub_5FDFE0
// ------------------------------------------------------------
// 调: sub_5FDFE0
int /*usercall*/ sub_5FDFE0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：调: sub_5FDFE0
{
  uint32_t *v3; // esi
  int v4; // eax
  int result; // eax
  int v6; // edx
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // edi
  int v12; // eax
  int v13; // ecx
  int v14; // ebx
  int v15; // eax

  v3 = (uint32_t *)__RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                   pDwArg1[1],
                   0,
                   &IRDActiveObject `RTTI Type Descriptor',
                   &IRDMonster `RTTI Type Descriptor',
                   0);
  pDwArg1[22] = 50 * v3[1652] / 100;
  pDwArg1[23] = 120 * v3[1652] / 100;
  v4 = v3[1652] / 3;
  pDwArg1[20] = v4;
  pDwArg1[21] = 2 * v4;
  result = v3[1787];
  if ( result != 4 && result != 13 && result != 1 )  // 若 result != 4 与/或 result != 13 与/或 result != 1
  {
    v6 = *v3;
    if ( result == 5 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 1032))(v3);  // 虚函数调用 槽+1032
      if ( *(uint32_t *)(result + 20) != 0 )
      {
        v7 = *v3;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v3 + 1032))(v3, nArg2);  // 结果 = 虚调用 vt+1032
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v7 + 156))(v3, *(uint32_t *)(v8 + 20));  // 虚函数调用 槽+156
        v10 = *v3;
        v11 = v9 + 1;
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 1032))(v3);  // 结果 = 虚调用 vt+1032
        v13 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v10 + 160))(v3, *(uint32_t *)(v12 + 20)) + 1;  // 虚函数调用 槽+160
        if ( v11 <= v13 )
        {
          v14 = 114;
          v15 = 114 * v11 / v13;
        }
        else
        {
          v14 = 143 * v13 / v11;
          v15 = 143;
        }
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t))(*v3 + 876))(v3, 0, v15, v15, 0, 0);  // 虚调用 vt+876
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, uint32_t, uint32_t, uint32_t))(*v3 + 876))(  // 虚调用 vt+876
                 v3,
                 1,
                 v14,
                 v14,
                 0,
                 0,
                 0);
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v6 + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        v3,
        0,
        v3[1652],
        v3[1652],
        0,
        0,
        0);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*v3 + 876))(  // 虚调用 vt+876
               v3,
               1,
               v3[1653],
               v3[1653],
               0,
               0,
               0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FE170 CNSpeedControl__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
int /*thiscall*/ CNSpeedControl__vmtC(int *this, int pArg2)  // 实现：调: sub_41A5E0 sub_41A590
{
  unsigned int v4; // edi
  int v5; // edx
  int v6; // edx
  float fld_e20; // [esp+Ch] [ebp-4h]
  float fld_e21; // [esp+Ch] [ebp-4h]
  int v10; // [esp+18h] [ebp+8h]
  int v11; // [esp+18h] [ebp+8h]

  v4 = pArg2 + 830;
  fld_e20 = (double)*(this + 20) * 0.001;  // this+20 频道页号
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pArg2 + 830)) + fld_e20;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v4, v5, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_e21 = (double)*(this + 21) * 0.001;  // this+21 【推断】霸体状态字节
  *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(pArg2 + 858)) + fld_e21;  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pArg2 + 858, v6, v11);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x5FE1F0 CNAuraBoss__vmt1C
// ------------------------------------------------------------
// 证: "Common/Etc/Animation/Aura/BossAuraMaster.ani"
int /*thiscall*/ CNAuraBoss__vmt1C(void *this)  // 实现：证: Common/Etc/Animation/Aura/BossAuraMaster.ani
{
  CNRDAuraMaster__vmt1C();
  return (*(int (/*thiscall*/ **)(void *, const char *))(*(uint32_t *)this + 128))(  // this+128 BOSS 攻击百分比
           this,
           "Common/Etc/Animation/Aura/BossAuraMaster.ani");  // 字符串 “Common/Etc/Animation/Aura/BossAuraMaster.ani”
}



// ------------------------------------------------------------
// 0x5FE210 CNAuraBoss__vmt78
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
int /*thiscall*/ CNAuraBoss__vmt78(int this, int nArg2)  // 实现：调: sub_41A5E0 sub_41A590
{
  unsigned int fld_4; // edi  | +0x0004 → 宿主对象指针（CNAuraBoss；va=0064A790）
  int v4; // edx
  int fld_42; // edi  | +0x0004 → 宿主对象指针（CNAuraBoss；va=0064A790）
  int v6; // ebx
  int64_t v7; // rax
  int *fld_43; // esi
  int v9; // edi
  int v10; // eax
  float fld_80; // [esp+Ch] [ebp-8h]  | +0x0080 → BOSS 攻击百分比（CNAuraBoss；va=005FE210）
  int v13; // [esp+Ch] [ebp-8h]

  fld_80 = *(float *)(this + 128) * 0.0099999998 - 1.0;  // this+128 BOSS 攻击百分比
  fld_4 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 18;  // 涉及字段 “+4 宿主对象指针”
  *(float *)&v13 = COERCE_FLOAT(sub_41A5E0(fld_4)) + fld_80;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(fld_4, v4, v13);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 676))(*(uint32_t *)(this + 4), 0);  // 涉及字段 “+4 宿主对象指针”
  fld_42 = *(uint32_t *)(this + 4);  // 读 fld_42 = this+4（宿主对象指针）
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_42 + 740))(fld_42);  // 虚函数调用 槽+740：属性块 +4 浮点壳（GetHP 族）
  v7 = ((int64_t (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)fld_42 + 684))(fld_42);  // 虚函数调用 槽+684：属性块基址（this+6132，HP 读处）
  sub_41A590(v7, SHIDWORD(v7), v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_43 = *(int **)(this + 4);  // this+4 宿主对象指针
  v9 = *fld_43;
  v10 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*fld_43 + 736))(fld_43, 1, 0);  // 结果 = 虚调用 vt+736
  return (*(int (/*thiscall*/ **)(int *, int))(v9 + 728))(fld_43, v10);  // 虚函数调用 槽+728：vec3 尾插 thunk（+1076 表）
}



// ------------------------------------------------------------
// 0x5FE2C0 sub_5FE2C0
// ------------------------------------------------------------
// 调: sub_5FE2C0 sub_5910D0
uint32_t */*thiscall*/ sub_5FE2C0(uint32_t *this, int nArg2)  // 实现：调: sub_5FE2C0 sub_5910D0
{
  sub_5910D0(0, 33, 500, 0);  // CNRDAuraMaster 构造函数
  *(this + 32) = nArg2;  // this+32 格子像素尺寸
  *this = &vftbl_CNAuraBoss;  // 构造装配 vftable：CNAuraBoss
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x5FE2F0 CNAuraBoss__vmt0
// ------------------------------------------------------------
// 调: sub_5FE320
void */*thiscall*/ CNAuraBoss__vmt0(void *Block, char pszArg2)  // 实现：调: sub_5FE320
{
  sub_5FE320();
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x5FE320 sub_5FE320
// ------------------------------------------------------------
// 调: sub_5FE320 sub_591190
int /*thiscall*/ sub_5FE320(uint32_t *this)  // 实现：调: sub_5FE320 sub_591190
{
  *this = &vftbl_CNAuraBoss;  // 构造装配 vftable：CNAuraBoss
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// ------------------------------------------------------------
// 0x5FE330 sub_5FE330
// ------------------------------------------------------------
// 调: sub_5FE330
int /*thiscall*/ sub_5FE330(int this)  // 函数定义: 基类 +
{
  *(uint32_t *)(this + 284) = 0;  // this+284 绑定/记录门字节
  *(uint32_t *)(this + 288) = 0;  // this+288 主人绑定对象
  *(uint32_t *)(this + 292) = 0;  // this+292 打开槽模式号
  *(uint32_t *)(this + 296) = 0;  // this+296 【推断】打开槽初始化字节
  *(uint8_t *)(this + 300) = 0;  // this+300 职业动画件 2
  *(uint32_t *)(this + 304) = 0;  // this+304 【推断】图层/子件槽
  *(uint32_t *)(this + 308) = 1000;  // this+1232〔pNameTagCtrl(推断)〕
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;  // this+324
  return 0;
}



// ------------------------------------------------------------
// 0x5FE380 sub_5FE380
// ------------------------------------------------------------
// 调: sub_5FE380
int /*thiscall*/ sub_5FE380(uint32_t *this)  // 实现：调: sub_5FE380
{
  int (/*thiscall*/ ***fld_e76)(uint32_t, int); // ecx
  int result; // eax

  fld_e76 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 76);  // this+76 纹章路径串
  if ( fld_e76 != nullptr )  // 若 fld_e76 有效（非空）
    result = (**fld_e76)(fld_e76, 1);  // 调 fld_e76 的虚函数（vt+0）
  *(this + 76) = 0;  // this+76 纹章路径串
  return result;
}



// ------------------------------------------------------------
// 0x5FE3A0 sub_5FE3A0
// ------------------------------------------------------------
// 证: "Monster/Common/Particle/MonsterDieSmoke.ptl"
// 调: sub_5FE3A0 sub_428F30 sub_4049C0
int /*userpurge*/ sub_5FE3A0@<eax>(int pArg1@<ecx>, double fArg2@<st0>, void *Block, int nArg4, int nArg5, int nArg6, int nArg7)  // 实现：调: sub_5FE3A0 sub_428F30 sub_4049C0
{
  int nArg42; // eax
  int pObj; // eax
  int fArg22; // edi

  *(uint32_t *)(pArg1 + 284) = Block;  // pArg1+284〔bBindGate284(推断)〕
  nArg42 = nArg4;
  if ( nArg4 <= 30000 )
  {
    nArg42 = 30000;
  }
  else if ( nArg4 >= 170000 )
  {
    nArg42 = 170000;
  }
  *(uint32_t *)(pArg1 + 288) = nArg42;  // pArg1+288〔pMaster288(推断)〕
  *(uint32_t *)(pArg1 + 292) = nArg5;  // pArg1+292〔nOpenMode292(推断)〕
  *(uint32_t *)(pArg1 + 296) = nArg6;  // pArg1+296〔bInitFlag296(推断)〕
  *(uint8_t *)(pArg1 + 300) = 0;  // pArg1+300〔pAnim300(推断)〕
  if ( operator new(0x12Cu) != nullptr )  // 堆分配 300 字节对象
    pObj = sub_428F30("Monster/Common/Particle/MonsterDieSmoke.ptl", 0);  // 字符串 “Monster/Common/Particle/MonsterDieSmoke.ptl”
  else
    pObj = 0;
  *(uint32_t *)(pArg1 + 304) = pObj;  // pArg1+304〔pLayer304(推断)〕
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj);  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
  fArg22 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 304) + 36))(*(uint32_t *)(pArg1 + 304));  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
  sub_4049C0(20.0, 60.0, *(uint32_t *)(pArg1 + 288) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(float *)fArg22 = fArg2;
  sub_4049C0(50.0, 150.0, *(uint32_t *)(pArg1 + 288) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(uint32_t *)(fArg22 + 12) = (uint64_t)fArg2;
  *(uint32_t *)(fArg22 + 20) = (uint64_t)fArg2;
  *(uint32_t *)(fArg22 + 16) = 2 * (uint64_t)fArg2;
  sub_4049C0(1000.0, 2000.0, *(uint32_t *)(pArg1 + 288) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(uint32_t *)(pArg1 + 308) = (uint64_t)fArg2;
  *(uint32_t *)(pArg1 + 320) = nArg7;
  return nArg7;
}



// ------------------------------------------------------------
// 0x5FE4F0 CNPieceDestroyEffect__vmt14C
// ------------------------------------------------------------
// 证: "Monster/Common/Animation/MonsterDieFlash.ani"
// 调: sub_699000 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E1F0
int /*thiscall*/ sub_5FE4F0(int *this)  // 【CNPieceDestroyEffect__vmt14C】
{
  char pThis_12C; // al
  int v3; // eax
  int v4; // edx
  int pObj2; // esi
  bool fld_50; // zf  | +0x0050 → 状态字节（CNPieceDestroyEffect；va=005FE4F0）
  int v7; // edi
  int pObj; // edi
  int fld_e29; // ecx
  uint32_t *v10; // edi
  uint64_t fld_e72; // rax
  int v12; // eax
  int v13; // eax
  uint64_t fld_e723; // rax
  int v15; // eax
  unsigned int v16; // eax
  int fld_e71; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  uint64_t fld_e724; // rax
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // esi
  int v28; // eax
  int v29; // edi
  int v30; // eax
  signed int nRand; // eax
  unsigned int v32; // eax
  int v33; // esi
  float fld_e7224; // ecx
  bool v35; // cc
  int pThis_10; // ecx
  int v37; // esi
  int v38; // eax
  void *fld_e292; // ecx
  unsigned int j; // esi
  int result; // eax
  int fld_e725; // [esp-28h] [ebp-180h]
  float fld_e7222; // [esp-4h] [ebp-15Ch]
  float fld_e7223; // [esp-4h] [ebp-15Ch]
  void *v45; // [esp+Ch] [ebp-14Ch] BYREF
  void *Block; // [esp+10h] [ebp-148h]
  int v47; // [esp+14h] [ebp-144h]
  int v48; // [esp+18h] [ebp-140h]
  int v49; // [esp+1Ch] [ebp-13Ch]
  char v50[4]; // [esp+20h] [ebp-138h] BYREF
  void *v51; // [esp+24h] [ebp-134h]
  void *v52; // [esp+28h] [ebp-130h]
  int v53; // [esp+2Ch] [ebp-12Ch]
  int v54; // [esp+30h] [ebp-128h]
  int v55; // [esp+34h] [ebp-124h]
  float fld_e722; // [esp+38h] [ebp-120h]
  int v57; // [esp+3Ch] [ebp-11Ch]
  int nRand2; // [esp+40h] [ebp-118h]
  int i; // [esp+44h] [ebp-114h]
  char Buffer[256]; // [esp+48h] [ebp-110h] BYREF
  int dword_796E502; // [esp+148h] [ebp-10h]
  int v62; // [esp+154h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  nullsub_3(this);
  pThis_12C = *((uint8_t *)this + 300);  // this+300 职业动画件 2
  v54 = 1;
  if ( pThis_12C != 0 || sub_699000((int)(this + 16)) < *(this + 74) )  // 【clock_now(clk)】
    goto LABEL_71;
  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
  v4 = *this;
  nRand2 = v3;
  v57 = (*(int (/*thiscall*/ **)(int *))(v4 + 124))(this);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  pObj2 = 0;
  v55 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
  v51 = nullptr;
  v52 = nullptr;
  v53 = 0;
  fld_50 = (*(uint8_t *)(this + 80) & 8) == 0;  // this+80 状态字节
  v62 = 0;
  if ( fld_50 )
    goto LABEL_15;
  LOBYTE(v62) = 1;  // 调 取 16 位值低 8 位
  v7 = sub_42FCB0(228) != 0 ? sub_431860((char)"Monster/Common/Animation/MonsterDieFlash.ani", 1) : 0;  // 字符串 “Monster/Common/Animation/MonsterDieFlash.ani”
  v49 = sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  LOBYTE(v62) = 2;  // 调 取 16 位值低 8 位
  pObj = v49 != 0 ? sub_44E1F0(v7, 1) : 0;  // 结果 = CNRDPooledObject 构造（虚表覆盖壳）
  fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
  LOBYTE(v62) = 0;  // 调 取 16 位值低 8 位
  sub_45FE80(fld_e29, pObj, 2, 0, pObj, (int)this, 0);  // 调 对象注册
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 112))(pObj, nRand2, v57, v55);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  if ( *(uint32_t *)(dword_8F7A24 + 244) == 1 )  // 全局 dword_8F7A24 = 登录/选区管理器
  {
LABEL_15:
    v10 = (uint32_t *)v54;
  }
  else
  {
    pObj2 = dword_8F82E0;
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F82E0 + 28))(dword_8F82E0);  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
    v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
    v10[1] = (uint64_t)sub_4049C0(10.0, 30.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    fld_e72 = (uint64_t)sub_4049C0(10.0, 30.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v10[3] = fld_e72;
    v10[4] = fld_e72;
    v10[5] = fld_e72;
    fld_e722 = sub_4049C0(1.0, 2.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    if ( *(this + 81) == 0 )  // this+324〔nRandPick324〕
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 40))(pObj2, nRand2, v57, v55);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      v12 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj2 + 92))(pObj2, &v45);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
      LOBYTE(v62) = 3;  // 调 取 16 位值低 8 位
      sub_4E77D0((int)v50, v12);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
      LOBYTE(v62) = 0;  // 调 取 16 位值低 8 位
      sub_5E5260(&v45);  // 调 动画子对象清理临时缓冲
      sub_4600B0((void *)*(this + 29), 2, 0, (int)v50);  // 调 演播层注册(槽号)
      for ( i = (int)v51; (void *)i != v52; i += 4 )
      {
        fld_e7222 = fld_e722;
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)i + 200))(*(uint32_t *)i);  // 虚函数调用 槽+200：取动画对象
        sub_4922F0(fld_e7222);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
      }
    }
  }
  if ( (*(uint8_t *)(this + 80) & 2) != 0 )  // 判定 “+80 状态字节”
  {
    v13 = *(uint32_t *)(dword_8F7A24 + 244);  // 全局 dword_8F7A24 = 登录/选区管理器
    if ( v13 != 2 )
    {
      pObj2 = dword_8F82CC[v13 != 1];
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 28))(pObj2);  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
      v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
      v10[1] = (uint64_t)sub_4049C0(15.0, 60.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      fld_e723 = (uint64_t)sub_4049C0(50.0, 150.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v10[3] = fld_e723;
      v10[4] = 2 * fld_e723;
      v10[5] = fld_e723;
      fld_e722 = sub_4049C0(1.0, 1.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 40))(pObj2, nRand2, v57, v55);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      v15 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj2 + 92))(pObj2, &v45);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
      LOBYTE(v62) = 4;  // 调 取 16 位值低 8 位
      sub_4E77D0((int)v50, v15);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
      LOBYTE(v62) = 0;  // 调 取 16 位值低 8 位
      sub_5E5260(&v45);  // 调 动画子对象清理临时缓冲
      sub_4600B0((void *)*(this + 29), 2, 0, (int)v50);  // 调 演播层注册(槽号)
      for ( i = (int)v51; (void *)i != v52; i += 4 )
      {
        fld_e7223 = fld_e722;
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)i + 200))(*(uint32_t *)i);  // 虚函数调用 槽+200：取动画对象
        sub_4922F0(fld_e7223);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
      }
    }
  }
  if ( (*(uint8_t *)(this + 80) & 1) != 0 && *(this + 73) != 0 )  // 判定 “+80 状态字节”
  {
    v16 = *(uint32_t *)(dword_8F7A24 + 244);  // 全局 dword_8F7A24 = 登录/选区管理器
    if ( v16 != 0 )
    {
      if ( v16 == 1 )
      {
        pObj2 = dword_8F82D4;
      }
      else if ( v16 == 2 )
      {
        pObj2 = dword_8F82DC;
      }
    }
    else
    {
      pObj2 = dword_8F82D8;
    }
    if ( v16 <= 1 )
    {
      i = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 28))(pObj2);  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
      v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
      fld_e71 = *(this + 71);  // this+71 移动类型
      switch ( fld_e71 )  // 按 fld_e71 分派
      {
        case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          v21 = i;
          *(uint32_t *)(i + 31) = 400;
          *(uint32_t *)(v21 + 35) = 400;
          *(uint32_t *)(v21 + 76) = 0;
          v19 = 100;
          break;
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        case 4:  // case 4 = ENUM_CMDPACKET_EXIT
          v20 = i;
          *(uint32_t *)(i + 31) = 700;
          *(uint32_t *)(v20 + 35) = 700;
          *(uint32_t *)(v20 + 76) = *(this + 71) != 3 ? -70 : 70;  // this+71 移动类型
          v19 = 40;
          break;
        case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
          v18 = i;
          *(uint32_t *)(i + 31) = 800;
          *(uint32_t *)(v18 + 35) = 800;
          *(uint32_t *)(v18 + 76) = 0;
          v19 = 10;
          break;
        default:
          goto LABEL_38;
      }
      v10[10] = v19;
      v10[11] = v19;
    }
LABEL_38:
    v10[1] = (uint64_t)sub_4049C0(10.0, 30.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    fld_e724 = (uint64_t)sub_4049C0(50.0, 150.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    fld_e725 = *(this + 72) - 30000;  // this+72 【推断】快照槽
    i = fld_e724;
    fld_e722 = sub_4049C0(0.5, 1.0, fld_e725, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )  // 全局 dword_8F7A24 = 登录/选区管理器
    {
      v10[1] = (uint64_t)sub_4049C0(20.0, 60.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      fld_e722 = sub_4049C0(2.0, 4.0, *(this + 72) - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v54 = 10;
    }
    v23 = i;
    v24 = 2 * i;
    v10[3] = i;
    v10[4] = v24;
    v10[5] = v23;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 40))(pObj2, nRand2, v57, v55);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    v25 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj2 + 92))(pObj2, &v45);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    LOBYTE(v62) = 5;  // 调 取 16 位值低 8 位
    sub_4E77D0((int)v50, v25);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
    LOBYTE(v62) = 0;  // 调 取 16 位值低 8 位
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
    sub_4600B0((void *)*(this + 29), 2, 0, (int)v50);  // 调 演播层注册(槽号)
    v26 = *(uint32_t *)(dword_8F7A24 + 244);  // 全局 dword_8F7A24 = 登录/选区管理器
    if ( v26 == 1 )
    {
      sprintf(Buffer, "Monster/Common/m%04d.img", *(this + 73));  // 字符串 “Monster/Common/m%04d.img”
    }
    else if ( v26 != 0 )
    {
      if ( v26 == 2 )
        strcpy(Buffer, "Monster/Common/MonsterDiePieceVeryYoung.img");  // 字符串 “Monster/Common/MonsterDiePieceVeryYoung.img”
    }
    else
    {
      strcpy(Buffer, "Monster/Common/MonsterDieYoung.img");  // 字符串 “Monster/Common/MonsterDieYoung.img”
    }
    v49 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, Buffer);  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
    i = (int)v51;
    if ( v51 != v52 )
    {
      while ( 1 )  // 无限循环
      {
        v27 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)i + 200))(*(uint32_t *)i);  // 虚函数调用 槽+200：取动画对象
        v28 = *(uint32_t *)(v27 + 44);
        v29 = 0;
        v55 = v27;
        v57 = v28 != 0 ? (*(uint32_t *)(v27 + 48) - v28) / 88 : 0;
        v30 = *(uint32_t *)(dword_8F7A24 + 244);  // 全局 dword_8F7A24 = 登录/选区管理器
        nRand2 = 0;
        if ( v30 == 1 )
          break;
        if ( v30 != 0 )
        {
          if ( v30 == 2 )
          {
            nRand = rand() & 0x80000001;  // 调 取伪随机数
            if ( nRand < 0 )
            {
              v32 = ((uint8_t)nRand - 1) | 0xFFFFFFFE;
LABEL_60:
              nRand = v32 + 1;
            }
LABEL_61:
            nRand2 = nRand;
          }
        }
        else
        {
          nRand2 = rand() % 3 + 1;  // 调 取伪随机数
        }
        if ( v57 > 0 )
        {
          do
          {
            v33 = sub_4924C0(v29);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
            *(uint32_t *)v33 = sub_418DD0(nRand2);  // 调 资源句柄 (101)
            fld_e7224 = fld_e722;
            *(float *)(v33 + 24) = fld_e722;
            v35 = ++v29 < v57;
            *(float *)(v33 + 20) = fld_e7224;
          }
          while ( v35 );
        }
        i += 4;
        if ( (void *)i == v52 )
          goto LABEL_65;
      }
      nRand = rand() & 0x80000003;  // 调 取伪随机数
      if ( nRand < 0 )
      {
        v32 = ((uint8_t)nRand - 1) | 0xFFFFFFFC;
        goto LABEL_60;
      }
      goto LABEL_61;
    }
  }
LABEL_65:
  if ( *(uint32_t *)(dword_8F7A24 + 244) != 1 )  // 全局 dword_8F7A24 = 登录/选区管理器
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "TEEN_MONSTER_DIE", -1, 0, 0);  // 字符串 “TEEN_MONSTER_DIE”
  if ( ++*(this + 81) >= v54 )  // this+324〔nRandPick324〕
  {
    *((uint8_t *)this + 300) = 1;  // this+300 职业动画件 2
    *(this + 81) = 0;  // this+324〔nRandPick324〕
  }
  v62 = -1;
  if ( v51 != nullptr )  // 若 v51 有效（非空）
    j__free(v51);  // 调 堆释放
LABEL_71:
  pThis_10 = (int)(this + 16);  // this+16 频道型选中索引
  if ( (*(uint8_t *)(this + 80) & 4) == 0 )  // 判定 “+80 状态字节”
  {
    result = sub_699000(pThis_10);  // 【clock_now(clk)】
    if ( result < *(this + 74) )  // this+74 【推断】复位字节 B
      return result;
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 84))(this, 0);  // 虚调用 vt+84
  }
  if ( sub_699000(pThis_10) >= *(this + 74) + 700 )  // 【clock_now(clk)】
  {
    v37 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
    v38 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 76) + 40))(*(this + 76), v37, v38, 30);  // this+76 纹章路径串
    (*(void (/*thiscall*/ **)(uint32_t, void **))(*(uint32_t *)*(this + 76) + 92))(*(this + 76), &v45);  // this+76 纹章路径串
    fld_e292 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v62 = 6;
    sub_4600B0(fld_e292, 2, 0, (int)&v45);  // 调 演播层注册(槽号)
    for ( j = 0; Block != nullptr && j < (v47 - (int)Block) >> 2; ++j )
    {
      (*(void (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + j) + 200))(*((uint32_t *)Block + j));  // 虚函数调用 槽+200：取动画对象
      *(uint32_t *)(sub_4924C0(0) + 48) = *(this + 77);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
    }
    v62 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
    Block = nullptr;
    v47 = 0;
    v48 = 0;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 76) + 68))(*(this + 76));  // this+76 纹章路径串
  if ( (uint8_t)result != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 84))(this, 0);  // 虚调用 vt+84
  return result;
}


// ------------------------------------------------------------
// 0x5FEEB0 sub_5FEEB0
// ------------------------------------------------------------
// 调: sub_5FEEB0
int /*thiscall*/ sub_5FEEB0(int this)  // 实现：调: sub_5FEEB0
{
  *(uint32_t *)(this + 80) = 0;  // this+80 关联角色对象
  *(uint32_t *)(this + 84) = 0;  // this+84 插值起点 X
  *(uint32_t *)(this + 88) = 0;  // this+88 插值起点 Y
  *(uint32_t *)(this + 92) = 4;  // this+92 插值起点 Z
  *(uint32_t *)(this + 96) = 0;  // this+96 插值终点 X / 落点偏移
  *(uint8_t *)(this + 100) = 0;  // this+100 插值终点 Y
  *(uint32_t *)(this + 104) = 0;  // this+104 插值终点 Z
  *(uint32_t *)(this + 108) = 0;  // this+108 第 1 组·宿主属性 +886 增量
  *(uint32_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  return 0;
}



// ------------------------------------------------------------
// 0x5FEEE0 sub_5FEEE0
// ------------------------------------------------------------
// 调: sub_5FEEE0 sub_699000 sub_4049C0 sub_47E720 sub_47EFD0
int /*thiscall*/ sub_5FEEE0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：调: sub_5FEEE0 sub_699000 sub_4049C0 sub_47E720 sub_47EFD0
{
  int pThis_2; // edi
  uint64_t v7; // rax
  char *v8; // edi

  *(this + 23) = nArg3;  // this+92〔pFxObjC(推断)〕
  *(this + 20) = nArg4;  // this+20 频道页号
  pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
  HIDWORD(v7) = rand() % 100;  // 调 取 64 位值高 32 位
  LODWORD(v7) = *(this + 20);  // this+20 频道页号
  *(this + 26) = HIDWORD(v7) + pThis_2;  // 调 取 64 位值高 32 位
  switch ( (int)v7 )  // 按 (int)v7 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      *(this + 11) = (uint64_t)sub_4049C0(10000.0, 10000.0, nArg2 - 1, 39);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from
      v7 = (uint64_t)sub_4049C0(10.0, 100.0, nArg2 - 1, 39);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      *(this + 22) = v7;  // this+88〔pFxObjB(推断)〕
      break;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      v8 = (char *)sub_47E720(1, 0x1Eu);  // 调 调 sub_47E720
      *(this + 21) = sub_47EFD0(v8, 0.0, nArg2, nArg5, nArg5, 0);  // this+21 【推断】霸体状态字节
      LODWORD(v7) = sub_47EF20(v8, 2u, nArg2, -1, -1, 11);  // 调 读攻击数据表
      *(this + 11) = v7;  // this+44〔nExpireMs(推断)〕
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      *(this + 23) = 4;  // this+92〔pFxObjC(推断)〕
      *(this + 21) = 0;  // this+21 【推断】霸体状态字节
      *(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
      *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
      *(this + 11) = 0;  // this+44〔nExpireMs(推断)〕
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      *(this + 11) = nArg2;  // this+44〔nExpireMs(推断)〕
      break;
    default:
      return v7;
  }
  return v7;
}



// ------------------------------------------------------------
// 0x5FEFE0 CNEnchantWeapon__vmt8
// ------------------------------------------------------------
// 证: 叶子函数（16 行，无外调无字符串）
char /*thiscall*/ CNEnchantWeapon__vmt8(int this, int pArg2)  // 实现：证: 叶子函数（16 行，无外调无字符串）
{
  char result; // al

  result = *(uint8_t *)(this + 100);  // 读 result = this+100（附魔完成标志）
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = pArg2;
    if ( *(uint8_t *)(pArg2 + 16) != 0 )  // pArg2+16〔nChannelTypeSel(推断)〕
    {
      *(uint32_t *)(pArg2 + 20) = *(uint32_t *)(this + 92);  // this+92 冰属性档位
      *(uint32_t *)(pArg2 + 8) += *(uint32_t *)(this + 88);  // this+88 火属性档位
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FF010 CNEnchantWeapon__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
int /*thiscall*/ CNEnchantWeapon__vmtC(uint32_t *this, int pArg2)  // 实现：调: sub_41A5E0 sub_41A590
{
  int fld_e21; // edi
  int v3; // eax
  int v4; // edx

  fld_e21 = *(this + 21);  // this+21 【推断】霸体状态字节
  v3 = sub_41A5E0(pArg2 + 1012);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pArg2 + 1012, v4, fld_e21 + v3);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x5FF040 sub_5FF040
// ------------------------------------------------------------
// 调: sub_5FF040 sub_699000 sub_42B420 sub_491690
char /*thiscall*/ sub_5FF040(uint32_t *this, int pArg2)  // 实现：调: sub_5FF040 sub_699000 sub_42B420 sub_491690
{
  int fld_e23; // eax
  int pThis_24; // eax
  uint8_t v4; // al
  int pThis_2; // eax
  uint8_t v6; // al
  int pThis_22; // eax
  uint8_t v8; // al
  int pThis_23; // eax
  uint8_t v10; // al

  LOBYTE(fld_e23) = *(uint8_t *)(pArg2 + 176);  // 调 取 16 位值低 8 位
  if ( (uint8_t)fld_e23 == 0 )
  {
    fld_e23 = *(this + 23);  // this+92〔pFxObjC(推断)〕
    if ( fld_e23 != 0 )
    {
      switch ( fld_e23 )  // 按 fld_e23 分派
      {
        case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
          pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
          v6 = sub_42B420(100, 220, pThis_2, 250);  // 结果 = 往返插值（三角波）
          LOBYTE(fld_e23) = sub_491690(1, 2, 1, -65536, (v6 << 24) | 0xFFFFFF, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
          break;
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
          pThis_22 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
          v8 = sub_42B420(100, 220, pThis_22, 250);  // 结果 = 往返插值（三角波）
          LOBYTE(fld_e23) = sub_491690(1, 2, 1, -1, (v8 << 24) | 0xFFFFFF, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
          break;
        case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          pThis_23 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
          v10 = sub_42B420(100, 220, pThis_23, 250);  // 结果 = 往返插值（三角波）
          LOBYTE(fld_e23) = sub_491690(1, 3, 1, -1, (v10 << 24) | 0xFFFFFF, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
          break;
        default:
          break;
      }
    }
    else
    {
      pThis_24 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
      v4 = sub_42B420(100, 220, pThis_24, 250);  // 结果 = 往返插值（三角波）
      LOBYTE(fld_e23) = sub_491690(1, 2, 1, -16776961, (v4 << 24) | 0xFFFFFF, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
    }
  }
  return fld_e23;
}



// ------------------------------------------------------------
// 0x5FF170 CNEnchantWeapon__vmt20
// ------------------------------------------------------------
// 证: "FROST_OFF" | "FLAME_OFF"
char /*thiscall*/ CNEnchantWeapon__vmt20(int this, char pszArg2)  // 函数定义: 设置坐标三元组 (this+100..112)
{
  int v2; // eax
  int fld_5C; // eax  | +0x005C → 冰属性档位（CNEnchantWeapon；va=005FF860）

  LOBYTE(v2) = pszArg2;  // 调 取 16 位值低 8 位
  if ( pszArg2 == 0 )
  {
    fld_5C = *(uint32_t *)(this + 92);  // 读 fld_5C = this+92（冰属性档位）
    if ( fld_5C != 0 )
    {
      v2 = fld_5C - 1;
      if ( v2 == 0 )
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(  // this+4 宿主对象指针
                       *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
                       "FROST_OFF",  // 字符串 “FROST_OFF”
                       -1,
                       0,
                       0);
    }
    else
    {
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(  // this+4 宿主对象指针
                     *(uint32_t *)(this + 4),  // 涉及字段 “+4 宿主对象指针”
                     "FLAME_OFF",  // 字符串 “FLAME_OFF”
                     -1,
                     0,
                     0);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5FF1C0 CNChangeWeaponElement__vmt8
// ------------------------------------------------------------
// 证: 叶子函数（12 行，无外调无字符串）
char /*thiscall*/ CNChangeWeaponElement__vmt8(int this, int pArg2)  // 实现：证: 叶子函数（12 行，无外调无字符串）
{
  int fld_5C; // eax  | +0x005C → 属性档位（0x5FF170: *(this+92) 0/1 定 FROST/FLAME）（CNChangeWeaponElement；va=005FF860）

  LOBYTE(fld_5C) = *(uint8_t *)(this + 100);  // this+100 附魔完成标志
  if ( (uint8_t)fld_5C != 0 )
  {
    fld_5C = *(uint32_t *)(this + 92);  // 读 fld_5C = this+92（属性档位）
    *(uint32_t *)(pArg2 + 20) = fld_5C;  // pArg2+20〔nPage(推断)〕
  }
  return fld_5C;  // | +0x005C → 属性档位（0x5FF170: *(this+92) 0/1 定 FROST/FLAME）（CNChangeWeaponElement；va=005FF860）
}



// ------------------------------------------------------------
// 0x5FF1E0 sub_5FF1E0
// ------------------------------------------------------------
// 调: sub_5FF1E0 sub_42AC90
void /*thiscall*/ sub_5FF1E0(int this)  // 实现：调: sub_5FF1E0 sub_42AC90
{
  int pThis; // ebx
  int v2; // esi
  int v3; // esi
  int pObj; // ecx
  int v5; // eax
  uint32_t *v6; // edx
  int v7; // ecx
  uint32_t *v8; // eax
  uint32_t *v9; // edi
  int v10; // ecx
  unsigned int v11; // edx
  uint32_t *v12; // eax
  int v13; // [esp+Ch] [ebp-18h]
  int v14; // [esp+10h] [ebp-14h]
  uint32_t *i; // [esp+14h] [ebp-10h]
  int v17; // [esp+1Ch] [ebp-8h]
  char v18; // [esp+23h] [ebp-1h]

  pThis = this;
  v18 = 0;
  if ( *(uint32_t *)(this + 108) != (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) )  // 判定 “+4 宿主对象指针”
  {
    v18 = 1;
    *(uint32_t *)(pThis + 108) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pThis + 4) + 200))(*(uint32_t *)(pThis + 4));  // this+108 第 1 组·宿主属性 +886 增量
  }
  v2 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pThis + 4) + 792))(*(uint32_t *)(pThis + 4), 8);  // this+4 宿主对象
  if ( v2 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pThis + 4) + 40))(*(uint32_t *)(pThis + 4), 273) != 0 )  // this+4 宿主对象
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pThis + 4) + 1084))(*(uint32_t *)(pThis + 4), 8);  // this+4 宿主对象
  }
  if ( *(uint32_t *)(pThis + 112) == v2 )  // this+112 第 1 组·宿主属性 +46 增量子倍率
  {
    if ( v18 == 0 )
      return;
  }
  else
  {
    *(uint32_t *)(pThis + 112) = v2;  // this+112 第 1 组·宿主属性 +46 增量子倍率
  }
  v3 = pThis + 116;  // this+116 观察者 vector 尾针
  if ( *(uint32_t *)(pThis + 120) != 0 )  // this+120 动画对象指针
    j__free(*(void **)(pThis + 120));  // this+120 动画对象指针
  *(uint32_t *)(pThis + 120) = 0;  // this+120 动画对象指针
  *(uint32_t *)(pThis + 124) = 0;  // this+124 第 2 组·+858/+1292 增量
  *(uint32_t *)(pThis + 128) = 0;  // this+128 第 2 组·+1208 增量子倍率
  if ( *(uint32_t *)(pThis + 108) != 0 )  // this+108 第 1 组·宿主属性 +886 增量
  {
    pObj = *(uint32_t *)(pThis + 112);  // this+112 第 1 组·宿主属性 +46 增量子倍率
    if ( pObj != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 248))(pObj);  // 虚函数调用 槽+248：区间长 = vt+244 - vt+240
      v6 = *(uint32_t **)(v5 + 4);
      v13 = v5;
      for ( i = v6; v6 != *(uint32_t **)(v13 + 8); i = v6 )
      {
        v7 = *(uint32_t *)(pThis + 108) + 200;  // this+108 第 1 组·宿主属性 +886 增量
        v14 = *v6;
        v8 = *(uint32_t **)(*(uint32_t *)(pThis + 108) + 204);  // this+108 第 1 组·宿主属性 +886 增量
        v9 = (uint32_t *)*v8;
        v17 = v7;
        if ( (uint32_t *)*v8 != v8 )
        {
          do
          {
            if ( v9[2] == v14 )
            {
              v10 = *(uint32_t *)(v3 + 4);
              if ( v10 != 0 )
                v11 = (*(uint32_t *)(v3 + 8) - v10) >> 2;  // 向量元素数 = (end−begin)/4
              else
                v11 = 0;
              if ( v10 != 0 && v11 < (*(uint32_t *)(v3 + 12) - v10) >> 2 )  // 向量元素数 = (end−begin)/4
              {
                v12 = *(uint32_t **)(v3 + 8);
                *v12 = v9[3];
                *(uint32_t *)(v3 + 8) = v12 + 1;
              }
              else
              {
                sub_42AC90(v3, *(char **)(v3 + 8), 1u, v9 + 3);  // 向量批量插入核心
              }
              v7 = v17;
              pThis = this;
            }
            v9 = (uint32_t *)*v9;
          }
          while ( v9 != *(uint32_t **)(v7 + 4) );
          v6 = i;
        }
        v6 += 31;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x5FF350 CNEnchantWeapon__vmt14
// ------------------------------------------------------------
// 调: sub_5FF1E0 sub_5FF040
void /*thiscall*/ CNEnchantWeapon__vmt14(int this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 实现：调: sub_5FF1E0 sub_5FF040
{
  int *i; // esi

  if ( pszArg2 == 0 && *(uint8_t *)(this + 100) != 0 )  // 判定 “+100 附魔完成标志”
  {
    sub_5FF1E0(this);
    for ( i = *(int **)(this + 120); i != *(int **)(this + 124); ++i )  // this+120 动画对象指针
      sub_5FF040((uint32_t *)this, *i);
  }
}



// ------------------------------------------------------------
// 0x5FF390 sub_5FF390
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/FlameWeapon.an" | "FLAME_ON"
// 调: sub_5FF390 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
int /*thiscall*/ sub_5FF390(int *this)  // 实现：调: sub_5FF390 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
{
  int v2; // eax
  int v3; // eax
  char *v4; // edi
  int v5; // eax
  int fld_e12; // esi
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int fld_e1; // [esp-8h] [ebp-28h]
  int v14; // [esp+0h] [ebp-20h]
  char *pObj; // [esp+10h] [ebp-10h]

  v2 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v2 != 0 )
    v3 = sub_431860(v2, "Common/CommonEffect/Animation/FlameWeapon.ani", 1);  // 字符串 “Common/CommonEffect/Animation/FlameWeapon.an”
  else
    v3 = 0;
  *(this + 24) = v3;  // this+24 页数上限
  v4 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  if ( v4 != nullptr )  // 若 v4 有效（非空）
  {
    sub_44E0D0(v4, *(this + 24), 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v4 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
  }
  else
  {
    v4 = nullptr;
  }
  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  pObj = v4;
  v5 = (*(int (**)(void))(*(uint32_t *)fld_e1 + 80))();  // 虚函数调用 槽+80：槽（参数写入 3 转发）
  sub_45FE80(v5, (int)v4, 2, 0, (int)v4, fld_e1, 0);  // 调 对象注册
  fld_e12 = *(this + 1);  // 读 fld_e12 = this+4（宿主对象指针）
  v7 = *(uint32_t *)v4;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 192))(fld_e12) / 2;  // 虚函数调用 槽+192
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 128))(fld_e12);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e12 + 124))(fld_e12, v9 + v8);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e12 + 120))(fld_e12, v10);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(pObj, v11);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj + 60))(pObj, *(this + 1));  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
  sub_4A06D0(v14);  // 调 绑定目标对象并记录相对偏移
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
           *(this + 1),  // this+4〔宿主对象〕
           "FLAME_ON",  // 字符串 “FLAME_ON”
           -1,
           0);
}



// ------------------------------------------------------------
// 0x5FF4C0 sub_5FF4C0
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/FrostWeapon.an" | "FROST_ON"
// 调: sub_5FF4C0 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
int /*thiscall*/ sub_5FF4C0(int *this)  // 实现：调: sub_5FF4C0 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
{
  int v2; // eax
  int v3; // eax
  char *v4; // edi
  int v5; // eax
  int fld_e12; // esi
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int fld_e1; // [esp-8h] [ebp-28h]
  int v14; // [esp+0h] [ebp-20h]
  char *pObj; // [esp+10h] [ebp-10h]

  v2 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v2 != 0 )
    v3 = sub_431860(v2, "Common/CommonEffect/Animation/FrostWeapon.ani", 1);  // 字符串 “Common/CommonEffect/Animation/FrostWeapon.an”
  else
    v3 = 0;
  *(this + 24) = v3;  // this+24 页数上限
  v4 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  if ( v4 != nullptr )  // 若 v4 有效（非空）
  {
    sub_44E0D0(v4, *(this + 24), 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v4 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
  }
  else
  {
    v4 = nullptr;
  }
  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  pObj = v4;
  v5 = (*(int (**)(void))(*(uint32_t *)fld_e1 + 80))();  // 虚函数调用 槽+80：槽（参数写入 3 转发）
  sub_45FE80(v5, (int)v4, 2, 0, (int)v4, fld_e1, 0);  // 调 对象注册
  fld_e12 = *(this + 1);  // 读 fld_e12 = this+4（宿主对象指针）
  v7 = *(uint32_t *)v4;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 192))(fld_e12) / 2;  // 虚函数调用 槽+192
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 128))(fld_e12);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e12 + 124))(fld_e12, v9 + v8);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e12 + 120))(fld_e12, v10);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(pObj, v11);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj + 60))(pObj, *(this + 1));  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
  sub_4A06D0(v14);  // 调 绑定目标对象并记录相对偏移
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t))(*(uint32_t *)*(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
           *(this + 1),  // this+4〔宿主对象〕
           "FROST_ON",  // 字符串 “FROST_ON”
           -1,
           0);
}



// ------------------------------------------------------------
// 0x5FF5F0 sub_5FF5F0
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/LightWeapon.an"
// 调: sub_5FF5F0 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
int /*thiscall*/ sub_5FF5F0(int *this)  // 实现：调: sub_5FF5F0 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
{
  int v2; // eax
  char *v3; // ebx
  int v4; // eax
  char *v5; // esi
  int v6; // eax
  int fld_e12; // esi
  int v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int fld_e1; // [esp-8h] [ebp-28h]
  int v14; // [esp-4h] [ebp-24h]
  char *pObj; // [esp+10h] [ebp-10h]

  v2 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  v3 = nullptr;
  if ( v2 != 0 )
    v4 = sub_431860(v2, "Common/CommonEffect/Animation/LightWeapon.ani", 1);  // 字符串 “Common/CommonEffect/Animation/LightWeapon.an”
  else
    v4 = 0;
  *(this + 24) = v4;  // this+24 页数上限
  v5 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  if ( v5 != nullptr )  // 若 v5 有效（非空）
  {
    sub_44E0D0(v5, *(this + 24), 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v5 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
    v3 = v5;
  }
  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  pObj = v3;
  v6 = (*(int (**)(void))(*(uint32_t *)fld_e1 + 80))();  // 虚函数调用 槽+80：槽（参数写入 3 转发）
  sub_45FE80(v6, (int)this, 2, 0, (int)v3, fld_e1, 0);  // 调 对象注册
  fld_e12 = *(this + 1);  // 读 fld_e12 = this+4（宿主对象指针）
  v8 = *(uint32_t *)v3;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 192))(fld_e12) / 2;  // 虚函数调用 槽+192
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 128))(fld_e12) + v9;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 124))(fld_e12);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e12 + 120))(fld_e12, v10);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
  (*(void (/*thiscall*/ **)(char *, int))(v8 + 112))(pObj, v11);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj + 60))(pObj, *(this + 1));  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
  return sub_4A06D0(v14);  // 调 绑定目标对象并记录相对偏移
}



// ------------------------------------------------------------
// 0x5FF700 sub_5FF700
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/DarkWeaponSpar" | "Common/CommonEffect/Animation/DarkWeaponSmok"
// 调: sub_5FF700 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
int /*thiscall*/ sub_5FF700(int *this)  // 实现：调: sub_5FF700 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
{
  int v2; // eax
  int v3; // eax
  char *v4; // edi
  int v5; // eax
  int fld_e12; // esi
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int fld_e1; // [esp-10h] [ebp-28h]
  int v15; // [esp-Ch] [ebp-24h]
  char *pObj; // [esp+8h] [ebp-10h]

  v2 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v2 != 0 )
    v3 = sub_431860(v2, "Common/CommonEffect/Animation/DarkWeaponSpark.ani", 1);  // 字符串 “Common/CommonEffect/Animation/DarkWeaponSpar”
  else
    v3 = 0;
  *(this + 24) = v3;  // this+24 页数上限
  v4 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  if ( v4 != nullptr )  // 若 v4 有效（非空）
  {
    sub_44E0D0(v4, *(this + 24), 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v4 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
  }
  else
  {
    v4 = nullptr;
  }
  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  pObj = v4;
  v5 = (*(int (**)(void))(*(uint32_t *)fld_e1 + 80))();  // 虚函数调用 槽+80：槽（参数写入 3 转发）
  sub_45FE80(v5, (int)v4, 2, 0, (int)v4, fld_e1, 0);  // 调 对象注册
  fld_e12 = *(this + 1);  // 读 fld_e12 = this+4（宿主对象指针）
  v7 = *(uint32_t *)v4;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 192))(fld_e12) / 2;  // 虚函数调用 槽+192
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 128))(fld_e12) + v8;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 124))(fld_e12);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e12 + 120))(fld_e12, v9);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(pObj, v10);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj + 60))(pObj, *(this + 1));  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
  sub_4A06D0(v15);  // 调 绑定目标对象并记录相对偏移
  v11 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v11 != 0 )
    v12 = sub_431860(v11, "Common/CommonEffect/Animation/DarkWeaponSmoke.ani", 1);  // 字符串 “Common/CommonEffect/Animation/DarkWeaponSmok”
  else
    v12 = 0;
  return (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
           pObj,
           100,
           v12,
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5FF860 CNEnchantWeapon__vmt4
// ------------------------------------------------------------
// 调: sub_699000 sub_5FF390 sub_5FF4C0 sub_5FF5F0 sub_5FF700
char /*thiscall*/ CNEnchantWeapon__vmt4(int this)  // 实现：调: sub_699000 sub_5FF390 sub_5FF4C0 sub_5FF5F0 sub_5FF700
{
  int pThis_8; // eax

  IRDAppendage__vmt4((int *)this);
  LOBYTE(pThis_8) = *(uint8_t *)(this + 100);  // this+100 附魔完成标志
  if ( (uint8_t)pThis_8 == 0 )
  {
    pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
    if ( *(uint32_t *)(this + 104) < pThis_8 )  // 判定 “+104 计时到期值”
    {
      pThis_8 = *(uint32_t *)(this + 80);  // 读 pThis_8 = this+80（附魔类型）
      if ( pThis_8 >= 0 )
      {
        if ( pThis_8 <= 1 )
        {
          pThis_8 = *(uint32_t *)(this + 92);  // 读 pThis_8 = this+92（冰属性档位）
          switch ( pThis_8 )  // 按 pThis_8 分派
          {
            case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
              LOBYTE(pThis_8) = sub_5FF390((int *)this);  // 调 取 16 位值低 8 位
              *(uint8_t *)(this + 100) = 1;  // 写 this+100 = 1（附魔完成标志）
              return pThis_8;
            case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
              LOBYTE(pThis_8) = sub_5FF4C0((int *)this);  // 调 取 16 位值低 8 位
              *(uint8_t *)(this + 100) = 1;  // 写 this+100 = 1（附魔完成标志）
              return pThis_8;
            case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
              LOBYTE(pThis_8) = sub_5FF5F0((int *)this);  // 调 取 16 位值低 8 位
              *(uint8_t *)(this + 100) = 1;  // 写 this+100 = 1（附魔完成标志）
              return pThis_8;
            default:
              break;
          }
        }
        if ( pThis_8 == 2 )
          LOBYTE(pThis_8) = sub_5FF700((int *)this);  // 调 取 16 位值低 8 位
      }
      *(uint8_t *)(this + 100) = 1;  // 写 this+100 = 1（附魔完成标志）
    }
  }
  return pThis_8;
}



// ------------------------------------------------------------
// 0x5FF8E0 sub_5FF8E0
// ------------------------------------------------------------
// 调: sub_5FF8E0
int /*thiscall*/ sub_5FF8E0(int this)  // 实现：调: sub_5FF8E0
{
  *(uint32_t *)(this + 96) = 33;  // this+96 插值终点 X / 落点偏移
  *(uint32_t *)(this + 676) = 0;  // this+676 重置标志
  *(uint32_t *)(this + 608) = 200;  // this+608 【推断】攻击盒/攻防门初值
  *(uint32_t *)(this + 876) = 0;
  *(uint32_t *)(this + 880) = 1;
  *(uint32_t *)(this + 884) = 0;
  *(uint32_t *)(this + 888) = 0;
  *(uint32_t *)(this + 892) = 0;
  *(uint32_t *)(this + 896) = 0;
  *(uint32_t *)(this + 900) = 0;
  *(uint32_t *)(this + 904) = 0;
  *(uint32_t *)(this + 908) = 0;
  *(uint32_t *)(this + 912) = 0;
  *(uint8_t *)(this + 944) = 0;  // 写 this+944 = 0（★名字已播出标志）
  *(uint8_t *)(this + 945) = 0;  // this+945 拆除完成位
  *(uint32_t *)(this + 948) = 3;
  *(uint32_t *)(this + 952) = 0;
  *(uint16_t *)(this + 946) = 255;
  *(uint32_t *)(this + 956) = 255;
  *(uint32_t *)(this + 964) = 0;  // 写 this+964 = 0（载荷缓冲字节数）
  *(uint32_t *)(this + 968) = 0;  // 写 this+968 = 0（载荷缓冲指针）
  return 0;
}



// ------------------------------------------------------------
// 0x5FF980 sub_5FF980
// ------------------------------------------------------------
// 调: sub_5FF980
void /*thiscall*/ sub_5FF980(uint32_t *this)  // 实现：调: sub_5FF980
{
  void (/*thiscall*/ ***fld_e219)(uint32_t, int); // ecx
  void *fld_e242; // eax

  fld_e219 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 219);
  if ( fld_e219 != nullptr )  // 若 fld_e219 有效（非空）
    (**fld_e219)(fld_e219, 1);  // 调 fld_e219 的虚函数（vt+0）
  fld_e242 = (void *)*(this + 242);  // this+968〔pBlobData〕
  *(this + 219) = 0;
  if ( fld_e242 != nullptr )  // 若 fld_e242 有效（非空）
    j__free(fld_e242);  // 调 堆释放
  *(this + 242) = 0;  // 写 this+968 = 0（载荷缓冲指针）
}



// ------------------------------------------------------------
// 0x5FF9C0 CNRDPassiveObject__vmt1F4
// ------------------------------------------------------------
// 调: sub_4E5740
int /*thiscall*/ CNRDPassiveObject__vmt1F4(int *this, uint32_t *uArg2, float *pArg3, char pszArg4)  // 实现：调: sub_4E5740
{
  int v5; // edi
  int v6; // eax

  v5 = IRDCollisionObject__vmt1F4(this, uArg2, pArg3, pszArg4);  // v5 = 调 IRDCollisionObject__vmt1F4
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);  // 结果 = 虚调用 vt+672
    if ( (uint8_t)sub_4E5740(*(uint32_t *)(v6 + 16), uArg2) == 0 )  // 概率判定（rand%10000 < 率×100；a3 为”抗性来源”）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312
  }
  return v5;
}



// ------------------------------------------------------------
// 0x5FFA20 CNRDPassiveObject__vmt130
// ------------------------------------------------------------
// 证: 叶子函数（16 行，无外调无字符串）
int /*thiscall*/ CNRDPassiveObject__vmt130(void *this)  // 实现：证: 叶子函数（16 行，无外调无字符串）
{
  int pThis_240; // eax
  int pObj; // esi

  pThis_240 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 576))(this);  // this+576 职业位移表值 A
  pObj = pThis_240;
  if ( pThis_240 == 0 )
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520);  // 虚函数调用 槽+144：槽（13 行）
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_240 + 40))(pThis_240, 273) != 0 )  // this+40 物品状态附属标志
    return pObj;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 304))(pObj);  // 虚函数调用 槽+304
  else
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520);  // 虚函数调用 槽+144：槽（13 行）
}



// ------------------------------------------------------------
// 0x5FFA80 CNRDPassiveObject__vmt2B8
// ------------------------------------------------------------
// 调: sub_4938F0 sub_4918E0
char /*thiscall*/ sub_5FFA80(int *this, int nArg2)  // 【CNRDPassiveObject__vmt2B8】
{
  int v5; // ebx
  int v6; // eax
  int v7; // ebx
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // ebx
  int v12; // eax
  int v13; // ebx
  int v14; // ebx
  int v15; // eax
  int v16; // ebx
  int v17; // ebx
  int v18; // ebx
  int fld_e30; // ebx  | +0x0078 → 动画对象指针（CNRDPassiveObject；va=00499020）
  int v20; // ebx
  int fld_e302; // ebx  | +0x0078 → 动画对象指针（CNRDPassiveObject；va=00499020）
  int v22; // ebx
  int v23; // eax
  int fld_e303; // ebx  | +0x0078 → 动画对象指针（CNRDPassiveObject；va=00499020）
  int v25; // ebx
  int v26; // eax
  int fld_e304; // ebx  | +0x0078 → 动画对象指针（CNRDPassiveObject；va=00499020）
  int v28; // ebx
  int v29; // eax
  int v30; // ecx
  int v31; // ebx
  bool v32; // cc
  int v33; // eax
  int *v34; // eax
  int v35; // ebx
  int v36; // eax
  int *v37; // eax
  unsigned int v38; // ebx
  int v39; // esi
  int v40; // [esp+8h] [ebp-18h]
  int v41; // [esp+Ch] [ebp-14h]
  int v42; // [esp+10h] [ebp-10h]
  int v43; // [esp+14h] [ebp-Ch]
  int v44; // [esp+14h] [ebp-Ch]
  int v45; // [esp+18h] [ebp-8h]
  int v46; // [esp+1Ch] [ebp-4h]
  int v47; // [esp+28h] [ebp+8h]

  if ( nArg2 == 0
    || (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) == 0  // 虚调用 vt+200
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2) == 0 )  // 虚函数调用 槽+200：取动画对象
  {
    return 0;
  }
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) >= v5 )  // 虚调用 vt+124
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);  // 虚函数调用 槽+200：取动画对象
    v7 = v6;
    if ( *(uint32_t *)(v6 + 148) == -1 )
      sub_4938F0(v6);  // 调 调 sub_4938F0
    v8 = sub_4918E0((int *)(v7 + 60), 0);  // 结果 = 动画盒四边界提取（研究 P29 族）
    v47 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2) - v8;  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);  // 虚函数调用 槽+200：取动画对象
    v10 = v9;
    if ( *(uint32_t *)(v9 + 148) == -1 )
      sub_4938F0(v9);  // 调 调 sub_4938F0
    v11 = sub_4918E0((int *)(v10 + 60), 1);  // 结果 = 动画盒四边界提取（研究 P29 族）
    v42 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2) + v11;  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);  // 虚函数调用 槽+200：取动画对象
    v13 = v12;
    if ( *(uint32_t *)(v12 + 148) == -1 )
      sub_4938F0(v12);  // 调 调 sub_4938F0
    v43 = sub_4918E0((int *)(v13 + 60), 2);  // 结果 = 动画盒四边界提取（研究 P29 族）
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) - v43;  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    v40 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2) + v14;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);  // 虚函数调用 槽+200：取动画对象
    v16 = v15;
    if ( *(uint32_t *)(v15 + 148) == -1 )
      sub_4938F0(v15);  // 调 调 sub_4938F0
    v17 = sub_4918E0((int *)(v16 + 60), 3);  // 结果 = 动画盒四边界提取（研究 P29 族）
    v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2) + v17;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v46 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) + v18;  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    fld_e30 = *(this + 30);  // 读 fld_e30 = this+120（动画对象指针）
    if ( *(uint32_t *)(fld_e30 + 148) == -1 )
      sub_4938F0(*(this + 30));  // 调 调 sub_4938F0
    v20 = 15 - sub_4918E0((int *)(fld_e30 + 60), 0);  // 结果 = 动画盒四边界提取（研究 P29 族）
    v41 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v20;  // 结果 = 虚调用 vt+120
    fld_e302 = *(this + 30);  // 读 fld_e302 = this+120（动画对象指针）
    if ( *(uint32_t *)(fld_e302 + 148) == -1 )
      sub_4938F0(*(this + 30));  // 调 调 sub_4938F0
    v22 = sub_4918E0((int *)(fld_e302 + 60), 1);  // 结果 = 动画盒四边界提取（研究 P29 族）
    v23 = v22 + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 15;  // 结果 = 虚调用 vt+120
    fld_e303 = *(this + 30);  // 读 fld_e303 = this+120（动画对象指针）
    v45 = v23;
    if ( *(uint32_t *)(fld_e303 + 148) == -1 )
      sub_4938F0(fld_e303);  // 调 调 sub_4938F0
    v25 = sub_4918E0((int *)(fld_e303 + 60), 2);  // 结果 = 动画盒四边界提取（研究 P29 族）
    v26 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - v25;  // 结果 = 虚调用 vt+124
    fld_e304 = *(this + 30);  // 读 fld_e304 = this+120（动画对象指针）
    v44 = v26;
    if ( *(uint32_t *)(fld_e304 + 148) == -1 )
      sub_4938F0(fld_e304);  // 调 调 sub_4938F0
    v28 = sub_4918E0((int *)(fld_e304 + 60), 3);  // 结果 = 动画盒四边界提取（研究 P29 族）
    v29 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
    v30 = v47;
    v31 = v29 + v28;
    if ( v47 < v41 )
    {
      if ( v42 > v45 && v40 < v44 && v46 > v31 )  // 若 v42 > v45 与/或 v40 < v44 与/或 v46 > v31
        return 1;  // 返回 1(成功)
      v30 = v47;
    }
    if ( v46 > v44 && v46 < v31 )  // 若 v46 > v44 与/或 v46 < v31
    {
      if ( v42 <= v41 || v42 >= v45 )  // 若 v42 <= v41 与/或 v42 >= v45
      {
        v32 = v30 < v41;
        if ( v30 <= v41 )
        {
LABEL_35:
          if ( !v32 || v42 <= v45 )
            return 0;
          goto LABEL_37;
        }
        if ( v30 >= v45 )
        {
          v32 = v30 < v41;
          goto LABEL_35;
        }
      }
LABEL_37:
      v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);  // 虚函数调用 槽+200：取动画对象
      v34 = (int *)sub_42F220(v33);  // 结果 = 取动画帧对象
      v35 = sub_4918E0(v34, 3);  // 结果 = 动画盒四边界提取（研究 P29 族）
      v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);  // 虚函数调用 槽+200：取动画对象
      v37 = (int *)sub_42F220(v36);  // 结果 = 取动画帧对象
      v38 = abs32(sub_4918E0(v37, 2) - v35);  // 结果 = 动画盒四边界提取（研究 P29 族）
      v39 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) + v38 + 15;  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      if ( v39 > (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) )  // 虚调用 vt+124
        return 1;  // 返回 1(成功)
    }
  }
  return 0;
}


// ------------------------------------------------------------
// 0x5FFD50 CNRDPassiveObject__vmt2A8
// ------------------------------------------------------------
// 证: 叶子函数（18 行，无外调无字符串）
void /*thiscall*/ CNRDPassiveObject__vmt2A8(uint32_t *this, int nArg2)  // 实现：证: 叶子函数（18 行，无外调无字符串）
{
  *(this + 173) = nArg2;  // 写 this+692 = nArg2（表现/名字快照[3]）
  if ( nArg2 != 0 )
  {
    *(this + 152) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // this+152 第 4 组·+886 增量
    *(this + 220) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 388))(nArg2);  // this+220 己方就绪标签控件
    *(this + 221) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 392))(nArg2);  // 虚函数调用 槽+392：HP 类属性读取（属性块 +60 防篡读 × 浮点壳 +74）
    *(this + 222) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 396))(nArg2);  // 虚函数调用 槽+396：MP 类属性读取（+1012 × 浮点壳 +1026）
    *(this + 223) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 400))(nArg2);  // 虚函数调用 槽+400：整数属性读取（+1306）
    *(this + 224) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 404))(nArg2);  // this+224 对方就绪标签控件
    *(this + 225) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 408))(nArg2);  // 虚函数调用 槽+408：装备槽解绑
    *(this + 226) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 412))(nArg2);  // 虚函数调用 槽+412：朝向与移动状态机
    *(this + 227) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 416))(nArg2);  // 虚函数调用 槽+416：[RTTI: IRDActiveObject__vmt1A0…
    *(this + 228) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 420))(nArg2);  // this+228 快照副本 C
  }
}



// ------------------------------------------------------------
// 0x5FFE10 CNRDPassiveObject__vmt2C0
// ------------------------------------------------------------
// 证: 叶子函数（23 行，无外调无字符串）
int /*thiscall*/ CNRDPassiveObject__vmt2C0(int *this)  // 实现：证: 叶子函数（23 行，无外调无字符串）
{
  uint64_t v1; // rax
  uint32_t v3[4]; // [esp+4h] [ebp-14h]
  int fld_e171; // [esp+14h] [ebp-4h]  | +0x02AC → 表现/名字快照[1]（4E1FE0）（证据 va=004E1FE0）（CNRDPassiveObject；va=004E1FE0）

  fld_e171 = *(this + 171);  // 读 fld_e171 = this+684（表现/名字快照[1]）
  LODWORD(v1) = fld_e171;  // 调 取 64 位值低 32 位
  if ( fld_e171 > 0 )
  {
    v3[0] = 1065353216;  // 常量 1.0f
    v3[1] = 0x40000000;
    v3[2] = 1077936128;  // 浮点常量 3.0f
    v3[3] = 1082130432;  // 常量 4.0f
    v1 = (uint64_t)((double)fld_e171 * *(float *)&v3[dword_99FB8C]);
    if ( (int)v1 > 0 )
    {
      *(this + 171) = v1;  // 写 this+684 = v1（表现/名字快照[1]）
      *(this + 170) = v1;  // 写 this+680 = v1（表现/名字快照[0]）
    }
  }
  return v1;
}



// ------------------------------------------------------------
// 0x5FFE70 CNRDPassiveObject__vmt140
// ------------------------------------------------------------
// 证: 叶子函数（10 行，无外调无字符串）
char /*thiscall*/ CNRDPassiveObject__vmt140(uint8_t *this)  // 实现：证: 叶子函数（10 行，无外调无字符串）
{
  char result; // al

  CNRDObject__vmt140(this);
  result = *(this + 276);  // this+276 地图条目指针
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 704))(this);  // this+704 表现/名字快照[24]
  return result;
}


