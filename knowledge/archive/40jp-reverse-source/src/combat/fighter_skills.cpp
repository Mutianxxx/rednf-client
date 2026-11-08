// ============================================================
// 【40JP逆向源代码工程】src/combat/fighter_skills.cpp
// 模块: 0x5E0000-0x5F0000
// 来源: work/dump 素材  区块: 0x5E0090-0x5EFBD1 §A 技能基础与投技
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: 71
// ============================================================


#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============================================================
// §A 技能基础与投技
// ============================================================
// 0x5E0090 CNMage__vmt514
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_4B3C90 sub_47EF20
void /*thiscall*/ sub_5E0090(int **this, void *pArg2, void *pArg3)  // 【CNMage__vmt514】
{
  void *pArg32; // ebx
  int v5; // eax
  int *v6; // eax
  int v7; // edx
  int *fld_e20582; // edi
  int *v9; // eax
  int v10; // edx
  int v11; // ebx
  int fld_e2062; // ecx
  int fld_16C; // ecx  | +0x016C → ★ 场景动画池指针（CNMage；va=005DE690）
  void *v14; // eax
  void *pObj; // ebx
  int fld_e29; // ecx  | +0x0074 → 0x5DE690 读取槽（fld_74）（CNMage；va=005DE690）
  int v17; // eax
  int v18; // eax
  int *v19; // eax
  int v20; // edx
  int *fld_e20622; // edi
  int v22; // ebx
  uint32_t *pThis_815; // eax
  int v24; // edi
  uint32_t *pThis_8152; // ebx
  int pThis_6C; // eax
  bool v27; // cc
  int i; // edi
  int v29; // ebx
  void *v30; // eax
  const char *pThis_5B; // ecx
  int v32; // eax
  void *v33; // eax
  const char *pThis_5B2; // ecx
  int v35; // eax
  void *v36; // eax
  const char *pThis_5B3; // ecx
  int v38; // eax
  int *pThis_822; // esi
  int j; // edi
  void *pMem3; // eax
  int *v42; // eax
  int v43; // edx
  int v44; // edi
  int *nAddVal_; // edi
  int v46; // ebx
  void *Block2; // ebx
  void **v48; // edi
  uint32_t *pMem4; // eax
  int *v50; // eax
  int v51; // edx
  int v52; // ebx
  int fld_e20952; // ebx
  void *pMem5; // eax
  int *v55; // eax
  int v56; // edx
  int v57; // edi
  int v58; // [esp+0h] [ebp-138h]
  int v59; // [esp+4h] [ebp-134h]
  float v60; // [esp+Ch] [ebp-12Ch]
  float v61; // [esp+Ch] [ebp-12Ch]
  char v62[4]; // [esp+10h] [ebp-128h] BYREF
  void *Block; // [esp+14h] [ebp-124h]
  void **v64; // [esp+18h] [ebp-120h]
  int v65; // [esp+1Ch] [ebp-11Ch]
  void *pMem2; // [esp+20h] [ebp-118h]
  void *pMem; // [esp+24h] [ebp-114h]
  char Buffer[256]; // [esp+28h] [ebp-110h] BYREF
  int dword_796E502; // [esp+128h] [ebp-10h]
  int v70; // [esp+134h] [ebp-4h]
  void **fld_e2058; // [esp+140h] [ebp+8h]
  void **fld_e2059; // [esp+140h] [ebp+8h]
  void (/*thiscall*/ **v73)(void *, int); // [esp+140h] [ebp+8h]
  BOOL v74; // [esp+140h] [ebp+8h]
  void *fld_e2095; // [esp+140h] [ebp+8h]
  void *fld_e20953; // [esp+140h] [ebp+8h]
  char *v77; // [esp+144h] [ebp+Ch]
  int v78; // [esp+144h] [ebp+Ch]
  void *nAddVal; // [esp+144h] [ebp+Ch]
  void *fld_e2060; // [esp+144h] [ebp+Ch]

  pArg32 = pArg3;
  dword_796E502 = dword_796E50;  // 帧时刻快照源
  sub_4B4170(pArg2, pArg3);  // Buff 图标条装配
  v5 = sub_41A5E0((unsigned int)pArg2 + 4);  // crypt4byte 解密校验（·0x41A590 逆运算）
  switch ( v5 )  // 按 v5 分派
  {
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      if ( *(this + 2058) == nullptr )  // this+8232〔nGrabTable〕
      {
        pMem = operator new(0x7Cu);  // new(124 字节) 分配对象
        v70 = 0;
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          v6 = (int *)sub_4B3C90(0, 4);  // CNChangeStatus 构造（双参）
        else  // 否则分支
          v6 = nullptr;  // v6 = 空指针
        *(this + 2058) = v6;  // this+8232〔nGrabTable〕
        v7 = *v6;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v7 + 64))(v6) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      }
      (*(void (/*thiscall*/ **)(uint32_t))(**(this + 2058) + 124))(*(this + 2058));  // this+8232〔nGrabTable〕
      (*(this + 2058))[11] = sub_47EF20(0, pArg3, -1, -1, 11);  // this+8232〔nGrabTable〕
      fld_e2058 = (void **)*(this + 2058);  // this+8232〔nGrabTable〕
      pMem = *fld_e2058;
      v60 = (float)(int)sub_47EF20(2, pArg3, -1, -1, 11);  // 调 读攻击数据表
      (*((void (/*thiscall*/ **)(void **, int, uint32_t, uint32_t))pMem + 30))(fld_e2058, 9, 0, LODWORD(v60));
      fld_e20582 = *(this + 2058);  // this+8232〔nGrabTable〕
      v59 = 34;
LABEL_15:  // 标签 LABEL_15（跳转合流点）
      v11 = *fld_e20582;
      (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        dword_8F84B8,  // 全局 攻击判定管理器
        "Common/CommonEffect/BuffIcon.img");  // 贴图 Common/CommonEffect/BuffIcon.img
LABEL_96:  // 标签 LABEL_96（跳转合流点）
      sub_418DD0(v59);  // 调 资源句柄 (101)
      (*(void (/*thiscall*/ **)(int *, int **, int **, int))(v11 + 56))(fld_e20582, this, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      return;
    case 41:  // case 41 = ENUM_CMDPACKET_FINISH_LOADING
      if ( *(this + 2059) == nullptr )  // this+8236〔nReflectCnt〕
      {
        pMem = operator new(0x7Cu);  // new(124 字节) 分配对象
        v70 = 1;
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          v9 = (int *)sub_4B3C90(0, 3);  // CNChangeStatus 构造（双参）
        else  // 否则分支
          v9 = nullptr;  // v9 = 空指针
        *(this + 2059) = v9;  // this+8236〔nReflectCnt〕
        v10 = *v9;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v10 + 64))(v9) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      }
      (*(void (/*thiscall*/ **)(uint32_t))(**(this + 2059) + 124))(*(this + 2059));  // this+8236〔nReflectCnt〕
      (*(this + 2059))[11] = sub_47EF20(0, pArg3, -1, -1, 11);  // this+8236〔nReflectCnt〕
      fld_e2059 = (void **)*(this + 2059);  // this+8236〔nReflectCnt〕
      pMem = *fld_e2059;
      v61 = (float)(int)sub_47EF20(1, pArg3, -1, -1, 11);  // 调 读攻击数据表
      (*((void (/*thiscall*/ **)(void **, int, uint32_t, uint32_t))pMem + 30))(fld_e2059, 23, 0, LODWORD(v61));
      fld_e20582 = *(this + 2059);  // this+8236〔nReflectCnt〕
      v59 = 29;
      goto LABEL_15;
    case 29:  // case 29 = ENUM_CMDPACKET_DISJOINT_ITEM
      fld_e2062 = (int)*(this + 2062);  // this+8248〔nVariantVal〕
      if ( fld_e2062 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2062 + 80))(fld_e2062) == 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      {
        *(this + 2063) = (int *)4;  // this+8252〔nParam2〕
        *(this + 2065) = (int *)-1;  // this+8260〔nPhaseA〕
        *(this + 2066) = (int *)-1;  // this+8264〔nPhaseB(推断)〕
        *(this + 2067) = (int *)-1;  // this+8268〔nParamArr(推断)〕
        *(this + 2068) = (int *)-1;  // this+8272〔pAnimPool2〕
        *(this + 2064) = nullptr;  // this+8256〔nParam3〕
        pMem = (void *)sub_42FCB0(228);  // CRT 一次性初始化
        v70 = 2;
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
        {
          if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimPoolCap〕
            LOBYTE(fld_16C) = (uint8_t)this + 108;  // this+108 第 1 组·宿主属性 +886 增量
          else  // 否则分支
            fld_16C = (int)*(this + 91);  // this+364〔pAnimPool〕
          pMem = (void *)sub_431920(fld_16C, (char)"Effect/Animation/ElementalChain/Start.ani", 1);  // 动画件构造（文件名版）
        }
        else  // 否则分支
        {
          pMem = nullptr;  // pMem = 空指针
        }
        v14 = (void *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
        pObj = v14;
        pMem2 = v14;
        v70 = 3;
        if ( v14 != nullptr )  // 若 v14 有效（非空）
        {
          sub_44E0D0((char *)v14, (int)pMem, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
          *(uint32_t *)pObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
        }
        else  // 否则分支
        {
          pObj = nullptr;  // pObj = 空指针
        }
        fld_e29 = (int)*(this + 29);  // this+116〔f_0074〕
        pMem = pObj;
        v70 = -1;
        sub_45FE80(fld_e29, (int)pArg2, 2, 0, (int)pObj, (int)this, 0);  // 调 实体对象注册到演播层
        v73 = *(void (/*thiscall*/ ***)(void *, int))pObj;
        v58 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this) + 25;
        v17 = ((int (/*thiscall*/ *)(int **))(*this)[31])(this);
        v18 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v17);
        v73[28](pObj, v18);
        (*(void (/*thiscall*/ **)(void *, int **))(*(uint32_t *)pObj + 60))(pObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        sub_4A06D0(v58);  // 调 绑定目标对象并记录相对偏移
        pArg32 = pArg3;
      }
      if ( *(this + 2062) == nullptr )  // this+8248〔nVariantVal〕
      {
        pMem2 = operator new(0x7Cu);  // new(124 字节) 分配对象
        v70 = 4;
        if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
          v19 = (int *)sub_4B3C90(0, 0);  // CNChangeStatus 构造（双参）
        else  // 否则分支
          v19 = nullptr;  // v19 = 空指针
        *(this + 2062) = v19;  // this+8248〔nVariantVal〕
        v20 = *v19;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v20 + 64))(v19) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      }
      (*(this + 2062))[11] = sub_47EF20(0, pArg32, -1, -1, 11);  // this+8248〔nVariantVal〕
      (*(void (/*thiscall*/ **)(uint32_t))(**(this + 2062) + 124))(*(this + 2062));  // this+8248〔nVariantVal〕
      fld_e20622 = *(this + 2062);  // this+8248〔nVariantVal〕
      v22 = *fld_e20622;
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        dword_8F84B8,  // 全局 攻击判定管理器
        "Common/CommonEffect/BuffIcon.img",  // 贴图 Common/CommonEffect/BuffIcon.img
        28,
        0,
        -1);
      sub_418DD0(v59);  // 调 资源句柄 (101)
      (*(void (/*thiscall*/ **)(int *, int **, int **, int))(v22 + 56))(fld_e20622, this, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      pThis_815 = this + 2069;
      if ( *(this + 2069) == nullptr )  // this+8276〔f_2054〕
      {
        v77 = nullptr;  // v77 = 空指针
        do  // do-while 循环体起点
        {
          v24 = 0;
          pThis_8152 = pThis_815;
          do  // do-while 循环体起点
          {
            sprintf(Buffer, "Effect/Animation/ElementalChain/LastElement%d%d.ani", v77, v24);  // 拼字符串（模板 Effect/Animation/ElementalChai…）
            pMem2 = (void *)sub_42FCB0(228);  // CRT 一次性初始化
            v70 = 5;
            if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
            {
              if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimPoolCap〕
                pThis_6C = sub_431920((uint8_t)this + 108, (char)Buffer, 1);  // 动画件构造（文件名版）
              else  // 否则分支
                pThis_6C = sub_431920((char)*(this + 91), (char)Buffer, 1);  // 动画件构造（文件名版）
            }
            else  // 否则分支
            {
              pThis_6C = 0;
            }
            *pThis_8152 = pThis_6C;
            ++v24;
            ++pThis_8152;
            v70 = -1;
          }
          while ( v24 < 2 );  // 条件循环
          v27 = (int)++v77 < 4;
          pThis_815 = pThis_8152;
        }
        while ( v27 );  // 条件循环
        for ( i = 0; i < 5; ++i )  // 循环：i 从 0 递增到 5
        {
          v78 = 2;
          if ( i != 4 )  // 若 i != 4
            v78 = i;
          v74 = i == 4;
          v29 = v74 + 1;
          sprintf(Buffer, "Effect/Animation/ElementalChain/MarkAppear%d.ani", v74 + 1);  // 拼字符串（模板 Effect/Animation/ElementalChai…）
          v30 = (void *)sub_42FCB0(228);  // CRT 一次性初始化
          pMem2 = v30;
          v70 = 6;
          if ( v30 != nullptr )  // 若 v30 有效（非空）
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimPoolCap〕
              pThis_5B = (const char *)(this + 91);  // this+364〔pAnimPool〕
            else  // 否则分支
              pThis_5B = (const char *)*(this + 91);  // this+364〔pAnimPool〕
            v32 = sub_4319E0((int)v30, v78, v74, pThis_5B, Buffer, 1);  // 动画件构造（文件名与参数版）
          }
          else  // 否则分支
          {
            v32 = 0;
          }
          *(this + i + 2077) = (int *)v32;
          v70 = -1;
          sprintf(Buffer, "Effect/Animation/ElementalChain/MarkStay%d.ani", v29);  // 拼字符串（模板 Effect/Animation/ElementalChai…）
          v33 = (void *)sub_42FCB0(228);  // CRT 一次性初始化
          pMem2 = v33;
          v70 = 7;
          if ( v33 != nullptr )  // 若 v33 有效（非空）
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimPoolCap〕
              pThis_5B2 = (const char *)(this + 91);  // this+364〔pAnimPool〕
            else  // 否则分支
              pThis_5B2 = (const char *)*(this + 91);  // this+364〔pAnimPool〕
            v35 = sub_4319E0((int)v33, v78, v74, pThis_5B2, Buffer, 1);  // 动画件构造（文件名与参数版）
          }
          else  // 否则分支
          {
            v35 = 0;
          }
          *(this + i + 2082) = (int *)v35;
          v70 = -1;
          sprintf(Buffer, "Effect/Animation/ElementalChain/MarkActivate%d.ani", v29);  // 拼字符串（模板 Effect/Animation/ElementalChai…）
          v36 = (void *)sub_42FCB0(228);  // CRT 一次性初始化
          pMem2 = v36;
          v70 = 8;
          if ( v36 != nullptr )  // 若 v36 有效（非空）
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimPoolCap〕
              pThis_5B3 = (const char *)(this + 91);  // this+364〔pAnimPool〕
            else  // 否则分支
              pThis_5B3 = (const char *)*(this + 91);  // this+364〔pAnimPool〕
            v38 = sub_4319E0((int)v36, v78, v74, pThis_5B3, Buffer, 1);  // 动画件构造（文件名与参数版）
          }
          else  // 否则分支
          {
            v38 = 0;
          }
          *(this + i + 2087) = (int *)v38;
          v70 = -1;
        }
      }
      pThis_822 = (int *)(this + 2082);  // this+2082〔pCaster〕
      for ( j = 5; j != 0; --j )  // 循环：j 从 5 递减到 0
      {
        sub_4926A0(*(pThis_822 - 5));  // 帧游标复位（+44 帧数组；递归子链 +204）
        sub_4926A0(*pThis_822++);  // 帧游标复位（+44 帧数组；递归子链 +204）
      }
      break;  // 跳出循环/分支
    case 30:  // case 30 = ENUM_CMDPACKET_USE_LOTTERY_ITEM
      if ( *((uint8_t *)this + 8368) != 0 )  // this+8368〔nCoordB〕
      {
        if ( sub_5DA1C0(this) )  // 存活查询（this+2093 对象非空且其 vt+80 判定为真）
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 2093) + 76))(*(this + 2093), 0);  // this+8372〔nAddVal〕
      }
      else  // 否则分支
      {
        if ( *(this + 2093) == nullptr )  // this+8372〔nAddVal〕
        {
          pMem3 = operator new(0x50u);  // new(80 字节) 分配对象
          pMem2 = pMem3;
          v70 = 9;
          if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
            v42 = (int *)sub_4B1030(pMem3);  // IRDAppendage 基类构造
          else  // 否则分支
            v42 = nullptr;  // v42 = 空指针
          *(this + 2093) = v42;  // this+8372〔nAddVal〕
          v43 = *v42;
          v70 = -1;
          *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v43 + 64))(v42) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
        }
        nAddVal = *(this + 2093);  // this+8372〔nAddVal〕
        v44 = sub_47EF20(0, pArg32, -1, -1, 11);  // v44 = 调 sub_47EF20 返回值
        *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)nAddVal + 64))(nAddVal) + 40) = v44;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
        nAddVal_ = *(this + 2093);  // this+8372〔nAddVal〕
        v46 = *nAddVal_;
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
          dword_8F84B8,  // 全局 攻击判定管理器
          "Common/CommonEffect/BuffIcon.img",  // 贴图 Common/CommonEffect/BuffIcon.img
          31,
          0,
          -1);
        sub_418DD0(v59);  // 调 资源句柄 (101)
        (*(void (/*thiscall*/ **)(int *, int **, int **, int))(v46 + 56))(nAddVal_, this, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
        Block = nullptr;  // Block = 空指针
        v64 = nullptr;  // v64 = 空指针
        v65 = 0;
        v70 = 10;
        sub_5DD040(this, 0xFFFF, (int)v62, 1);  // 召唤物/弹体筛选收集（this 碰撞表）：先按 pArg3 清空出口表，nArg2 命中 dword_738020..738030
        Block2 = Block;
        v48 = (void **)Block;
        if ( Block != v64 )  // 若 Block != v64
        {
          do  // do-while 循环体起点
            sub_5DB260(this, *v48++);  // 召集标实例化：new(0x7C) 后取 vt+1140(this,30) 参数交·sub_5DB090 构造 CNFollowMe
          while ( v48 != v64 );  // 条件循环
        }
        if ( Block2 != nullptr )  // 若 Block2 有效（非空）
          j__free(Block2);
      }
      break;  // 跳出循环/分支
    case 37:  // case 37 = ENUM_CMDPACKET_FINISH_QUEST
      if ( *(this + 2095) == nullptr )  // this+8380〔pAnimC〕
      {
        pMem4 = operator new(0x70u);  // new(112 字节) 分配对象
        pMem2 = pMem4;
        v70 = 11;
        if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
          v50 = sub_5DB180(pMem4);  // CNAuraShield 构造（光环护盾）：基类·sub_4B1030 → 置 CNAuraShield vftable
        else  // 否则分支
          v50 = nullptr;  // v50 = 空指针
        *(this + 2095) = v50;  // this+8380〔pAnimC〕
        v51 = *v50;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v51 + 64))(v50) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      }
      fld_e2095 = *(this + 2095);  // this+8380〔pAnimC〕
      v52 = sub_47EF20(0, pArg3, -1, -1, 11);  // v52 = 调 sub_47EF20 返回值
      *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)fld_e2095 + 64))(fld_e2095) + 40) = v52;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
      fld_e20952 = **(this + 2095);  // this+8380〔pAnimC〕
      fld_e20953 = *(this + 2095);  // this+8380〔pAnimC〕
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        dword_8F84B8,  // 全局 攻击判定管理器
        "Common/CommonEffect/BuffIcon.img",  // 贴图 Common/CommonEffect/BuffIcon.img
        32,
        0,
        -1);
      sub_418DD0(v59);  // 调 资源句柄 (101)
      (*(void (/*thiscall*/ **)(void *, int **, int **, int))(fld_e20952 + 56))(fld_e20953, this, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      *(this + 2096) = (int *)sub_47EF20(1, pArg3, -1, -1, 11);  // this+8384〔f_20C0〕
      *((float *)this + 2097) = (double)(int)sub_47EF20(2, pArg3, -1, -1, 11) * 0.0099999998;  // this+8388〔pAnimD〕
      *((float *)this + 2097) = *((float *)this + 2097) / sub_433F60((int)this, 2);  // this+8388〔pAnimD〕
      break;  // 跳出循环/分支
    case 40:  // case 40 = ENUM_CMDPACKET_FISHING
      if ( *(this + 2060) == nullptr )  // this+8240〔nParamCnt〕
      {
        pMem5 = operator new(0x50u);  // new(80 字节) 分配对象
        pMem2 = pMem5;
        v70 = 12;
        if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
          v55 = (int *)sub_4B1030(pMem5);  // IRDAppendage 基类构造
        else  // 否则分支
          v55 = nullptr;  // v55 = 空指针
        *(this + 2060) = v55;  // this+8240〔nParamCnt〕
        v56 = *v55;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v56 + 64))(v55) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      }
      fld_e2060 = *(this + 2060);  // this+8240〔nParamCnt〕
      v57 = sub_47EF20(0, pArg32, -1, -1, 11);  // v57 = 调 sub_47EF20 返回值
      *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)fld_e2060 + 64))(fld_e2060) + 40) = v57;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
      fld_e20582 = *(this + 2060);  // this+8240〔nParamCnt〕
      v11 = *fld_e20582;
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        dword_8F84B8,  // 全局 攻击判定管理器
        "Common/CommonEffect/BuffIcon.img",  // 贴图 Common/CommonEffect/BuffIcon.img
        33,
        0,
        -1);
      goto LABEL_96;  // 跳转合流点 LABEL_96
    default:  // 默认分支
      return;
  }
}


// ------------------------------------------------------------
// 0x5E09B0 sub_5E09B0
// ------------------------------------------------------------
// 调: sub_5E09B0 sub_47E9D0 sub_5DD040 sub_47EF20 sub_422E70
void /*thiscall*/ sub_5E09B0(int *this, uint32_t *uArg2, int nArg3)  // 实现：调: sub_5E09B0 sub_47E9D0 sub_5DD040 sub_47EF20 sub_422E70
{
  int v5; // eax
  int v6; // ebx
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  unsigned int v11; // ebx
  int v12; // eax
  int *v13; // ecx
  uint32_t *v14; // ecx
  char v15; // al
  uint32_t *v16; // esi
  int v17; // eax
  uint32_t *v18; // esi
  int v19; // eax
  int i; // ebx
  int v21; // eax
  int v22; // ebx
  int v23; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // ebx
  int v29; // edi
  int v30; // eax
  uint32_t *Block2; // ecx
  unsigned int v32; // eax
  int v33; // ebx
  int v34; // edi
  int v35; // eax
  int v36; // eax
  int v37; // eax
  unsigned int v38; // ebx
  int pObj; // edi
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int fld_e91; // ecx
  uint32_t *v46; // ebx
  char *v47; // eax
  char *v48; // edi
  int v49; // edx
  int v50; // ebx
  int v51; // eax
  int v52; // ebx
  int v53; // eax
  int v54; // eax
  int v55; // eax
  void *v56[4]; // [esp+Ch] [ebp-14Ch] BYREF
  unsigned int v57; // [esp+1Ch] [ebp-13Ch]
  int v58; // [esp+20h] [ebp-138h]
  char *v59; // [esp+24h] [ebp-134h]
  int v60; // [esp+28h] [ebp-130h]
  int v61; // [esp+2Ch] [ebp-12Ch]
  char v62[4]; // [esp+30h] [ebp-128h] BYREF
  void *Block; // [esp+34h] [ebp-124h]
  int v64; // [esp+38h] [ebp-120h]
  int v65; // [esp+3Ch] [ebp-11Ch]
  bool v66; // [esp+40h] [ebp-118h] BYREF
  char v67; // [esp+41h] [ebp-117h]
  char nArg32; // [esp+42h] [ebp-116h]
  int v69; // [esp+43h] [ebp-115h]
  char Buffer[256]; // [esp+48h] [ebp-110h] BYREF
  int dword_796E502; // [esp+148h] [ebp-10h]
  int v72; // [esp+154h] [ebp-4h]
  int v73; // [esp+160h] [ebp+8h]
  float v74; // [esp+160h] [ebp+8h]

  dword_796E502 = dword_796E50;  // 帧时刻快照源
  v5 = sub_47E9D0(uArg2, 2u);  // v5 = 调 sub_47E9D0 返回值
  v6 = sub_5DD040(this, v5, 0, 1);  // 召唤物/弹体筛选收集（this 碰撞表）：先按 pArg3 清空出口表，nArg2 命中 dword_738020..738030
  v7 = sub_47EF20(2, nArg3, -1, -1, 11) - v6;  // v7 = 调 sub_47EF20 返回值
  if ( sub_47EF20(1, nArg3, -1, -1, 11) >= v7 )  // 若调用结果为真
  {
    v9 = sub_47E9D0(uArg2, 2u);  // v9 = 调 sub_47E9D0 返回值
    v10 = sub_5DD040(this, v9, 0, 1);  // 召唤物/弹体筛选收集（this 碰撞表）：先按 pArg3 清空出口表，nArg2 命中 dword_738020..738030
    v8 = sub_47EF20(2, nArg3, -1, -1, 11) - v10;  // v8 = 调 sub_47EF20 返回值
  }
  else  // 否则分支
  {
    v8 = sub_47EF20(1, nArg3, -1, -1, 11);  // v8 = 调 sub_47EF20 返回值
  }
  v11 = 0;
  v73 = v8;
  if ( v8 > 0 )  // 若 v8 > 0
  {
    if ( sub_47E9D0(uArg2, 7u) > 0 )  // 若调用结果为真
    {
      Block = nullptr;  // Block = 空指针
      v64 = 0;
      v65 = 0;
      v72 = 0;
      sub_5DD040(this, 60006, (int)v62, 1);  // 召唤物/弹体筛选收集（this 碰撞表）：先按 pArg3 清空出口表，nArg2 命中 dword_738020..738030
      if ( Block != nullptr )  // 若 Block 有效（非空）
        v11 = (v64 - (int)Block) >> 2;
      if ( v11 < sub_47E9D0(uArg2, 7u) )  // 若调用结果为真
      {
        v18 = *((uint32_t **)dword_8F8528 + 7);  // 主管理器(消息/弹窗)
        v19 = sub_422E70(2104);  // v19 = 调 sub_422E70 返回值
        sub_43BEE0(v18, v19, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
        goto LABEL_58;
      }
      for ( i = 0; i < sub_47E9D0(uArg2, 7u); ++i )  // 遍历循环
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, int))(**((uint32_t **)Block + i) + 560))(  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
          *((uint32_t *)Block + i),
          13,
          0,
          2,
          1);
      v72 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
    }
    v60 = sub_47E9D0(uArg2, 2u);  // v60 = 调 sub_47E9D0 返回值
    v58 = sub_47EF20(0, nArg3, -1, -1, 11);  // v58 = 调 sub_47EF20 返回值
    v66 = false;
    v67 = 0;
    nArg32 = 0;
    v69 = 0;
    v66 = sub_47E9D0(uArg2, 6u) == 1;  // v66 = 调 sub_47E9D0 返回值
    v67 = 2;
    nArg32 = nArg3;
    v69 = sub_47EF20(3, nArg3, -1, -1, 11);  // v69 = 调 sub_47EF20 返回值
    v21 = sub_47E9D0(uArg2, 0);  // v21 = 调 sub_47E9D0 返回值
    if ( v21 < 0 )  // 若 v21 < 0
      return;
    if ( v21 > 1 )  // 若 v21 > 1
    {
      if ( v21 == 2 )  // 若 v21 == 2
      {
        v22 = sub_47E9D0(uArg2, 5u);  // v22 = 调 sub_47E9D0 返回值
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )  // 调虚槽 +152：效果通道 3
          v23 = v22 + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
        else  // 否则分支
          v23 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v22;  // 调虚槽 +120：动画对象
        v24 = *this;
        v25 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, bool *, uint32_t))(*this + 152))(  // 调虚槽 +152：效果通道 3
                this,
                2,
                0,
                0,
                0xFFFF,
                0,
                0,
                &v66,
                0);
        v26 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v25);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v27 = (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 376))(this, v58, v23, v26);  // 调虚槽 +376：坐标同步包（type 37）
        (*(void (/*thiscall*/ **)(int *, int, int))(v24 + 592))(this, v60, v27);
      }
      return;
    }
    v28 = sub_47E9D0(uArg2, 5u);  // v28 = 调 sub_47E9D0 返回值
    v61 = v28;
    HIBYTE(nArg3) = 0;
    Block = nullptr;  // Block = 空指针
    v64 = 0;
    v65 = 0;
    v72 = 1;
    if ( sub_47E9D0(uArg2, 0) != 0 )  // 若调用结果为真
      goto LABEL_38;
    v29 = sub_47E9D0(uArg2, 1u);  // v29 = 调 sub_47E9D0 返回值
    v30 = sub_5DC330(v56, v28, v29);  // 目标筛选与登记（this 碰撞表遍历）：按 vt+40(obj,33) 类型门 + vt+348(obj) 档位 +20 == nArg4 匹配
    LOBYTE(v72) = 2;
    sub_4E77D0((int)v62, v30);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
    LOBYTE(v72) = 1;
    sub_5E5260(v56);  // 调 动画子对象清理临时缓冲
    switch ( v29 )  // 按 v29 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        HIBYTE(nArg3) = 1;
        break;  // 跳出循环/分支
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        HIBYTE(nArg3) = 2;
        break;  // 跳出循环/分支
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        HIBYTE(nArg3) = 3;
        break;  // 跳出循环/分支
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        HIBYTE(nArg3) = 4;
        break;  // 跳出循环/分支
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
    Block2 = Block;
    if ( Block != nullptr && (v32 = (v64 - (int)Block) >> 2, v57 = v32, v32 != 0) )  // 若 Block != nullptr
    {
      v38 = 0;
      if ( v73 > 0 )  // 若 v73 > 0
      {
        while ( v38 < v32 )  // 条件循环
        {
          pObj = Block2[v38];  // pObj = 取 Block2[v38]
          v59 = (char *)*this;
          v40 = (*((int (/*thiscall*/ **)(int *, int, char *, int, int, uint32_t, uint32_t, bool *, uint32_t))v59 + 38))(
                  this,
                  2,
                  (char *)&nArg3 + 3,
                  1,
                  0xFFFF,
                  0,
                  0,
                  &v66,
                  0);
          v41 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, 0, v40);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          v42 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v41);  // 调虚槽 +120：动画对象
          v43 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 376))(this, v58, v42);  // 调虚槽 +376：坐标同步包（type 37）
          (*((void (/*thiscall*/ **)(int *, int, int))v59 + 148))(this, v60, v43);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
          if ( (int)++v38 >= v73 )
            break;  // 跳出循环/分支
          v32 = v57;
          Block2 = Block;
        }
      }
    }
    else  // 否则分支
    {
LABEL_38:  // 标签 LABEL_38（跳转合流点）
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )  // 调虚槽 +152：效果通道 3
        v33 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 100;  // 调虚槽 +120：动画对象
      else  // 否则分支
        v33 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 100;  // 调虚槽 +120：动画对象
      v34 = *this;
      v35 = (*(int (/*thiscall*/ **)(int *, int, char *, int, int, uint32_t, uint32_t, bool *, uint32_t))(*this + 152))(  // 调虚槽 +152：效果通道 3
              this,
              2,
              (char *)&nArg3 + 3,
              1,
              0xFFFF,
              0,
              0,
              &v66,
              0);
      v36 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v35);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v37 = (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 376))(this, v58, v33, v36);  // 调虚槽 +376：坐标同步包（type 37）
      (*(void (/*thiscall*/ **)(int *, int, int))(v34 + 592))(this, v60, v37);
    }
    v44 = 0;
    v74 = (double)v61 * 0.0018867925;
    do  // do-while 循环体起点
    {
      v61 = v44 + 1;
      sprintf(Buffer, "Effect/Animation/SummonSpirit%d.ani", v44 + 1);  // 拼字符串（模板 Effect/Animation/SummonSpirit%…）
      v59 = (char *)sub_42FCB0(228);  // CRT 一次性初始化
      LOBYTE(v72) = 3;
      if ( v59 != nullptr )  // 若 v59 有效（非空）
      {
        if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimNameCap(推断)〕
          LOBYTE(fld_e91) = (uint8_t)this + 108;
        else  // 否则分支
          fld_e91 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
        v46 = (uint32_t *)sub_431920(fld_e91, (char)Buffer, 1);  // 动画件构造（文件名版）
      }
      else  // 否则分支
      {
        v46 = nullptr;  // v46 = 空指针
      }
      LOBYTE(v72) = 1;
      sub_4922F0(v46, v74);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
      v47 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      v48 = v47;
      v59 = v47;
      LOBYTE(v72) = 4;
      if ( v47 != nullptr )  // 若 v47 有效（非空）
      {
        sub_44E0D0(v47, (int)v46, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)v48 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
      }
      else  // 否则分支
      {
        v48 = nullptr;  // v48 = 空指针
      }
      v49 = *(uint32_t *)v48;
      LOBYTE(v72) = 1;
      *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(v49 + 36))(v48) + 8) = 2;  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/60584…
      sub_45FE80(*(this + 29), (int)v48, 2, 0, (int)v48, 0, 0);  // 调 实体对象注册到演播层
      v50 = *(uint32_t *)v48;
      v51 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
      (*(void (/*thiscall*/ **)(char *, int))(v50 + 148))(v48, v51);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      v52 = *(uint32_t *)v48;
      v53 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      v54 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v53);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v55 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v54);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(char *, int))(v52 + 112))(v48, v55);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      v44 = v61;
    }
    while ( v61 < 4 );  // 条件循环
LABEL_58:  // 标签 LABEL_58（跳转合流点）
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
    return;
  }
  v12 = sub_47E9D0(uArg2, 2u);  // v12 = 调 sub_47E9D0 返回值
  v13 = &dword_738020;  // 区间表内返回 1）
  while ( v12 != *v13 )  // 条件循环
  {
    if ( (int)++v13 >= (int)&dword_738030 )
    {
      v14 = &unk_738040;
      while ( v12 != *v14 )  // 条件循环
      {
        if ( (int)++v14 >= (int)&dword_738044 )
        {
          v15 = 0;
          goto LABEL_12;
        }
      }
      break;  // 跳出循环/分支
    }
  }
  v15 = 1;
LABEL_12:  // 标签 LABEL_12（跳转合流点）
  v16 = *((uint32_t **)dword_8F8528 + 7);  // 主管理器(消息/弹窗)
  v17 = sub_422E70(v15 != 0 ? 2103 : 1);  // v17 = 调 sub_422E70 返回值
  sub_43BEE0(v16, v17, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
}


// ------------------------------------------------------------
// ============================================================
// §B 抓爆/吼 stun
// ============================================================
// 0x5E44C0 sub_5E44C0
// ------------------------------------------------------------
// 调: sub_5E44C0
int /*thiscall*/ sub_5E44C0(int this)  // 实现：调: sub_5E44C0
{
  *(uint32_t *)(this + 8216) = -1;  // this+8216〔nAtkActionType〕
  *(uint32_t *)(this + 8220) = -1;  // this+8220〔nGrabTargetSel(推断)〕
  *(uint32_t *)(this + 8224) = 0;  // this+8224〔f_2020〕
  *(uint8_t *)(this + 8228) = 0;  // this+8228〔bGrabFlag(推断)〕
  *(uint32_t *)(this + 8232) = 0;  // this+8232〔nGrabTable〕
  *(uint32_t *)(this + 8240) = 0;  // this+8240〔nParamCnt〕
  *(uint32_t *)(this + 8244) = 0;  // this+8244〔nVariantSel〕
  *(uint32_t *)(this + 8248) = 0;  // this+8248〔nVariantVal〕
  *(uint32_t *)(this + 8252) = 0;  // this+8252〔nParam2〕
  *(uint32_t *)(this + 8256) = 0;  // this+8256〔nParam3〕
  *(uint32_t *)(this + 8260) = 0;  // this+8260〔nPhaseA〕
  *(uint32_t *)(this + 8264) = 1000;  // this+8264〔nPhaseB(推断)〕
  *(uint32_t *)(this + 8268) = 0;  // this+8268〔nParamArr(推断)〕
  *(uint32_t *)(this + 8272) = 0;  // this+8272〔pAnimPool2〕
  *(uint8_t *)(this + 8276) = 0;  // this+8276〔f_2054〕
  *(uint32_t *)(this + 8280) = 0;  // this+8280〔pStatusObj〕
  *(uint32_t *)(this + 8284) = 0;  // this+8284〔nGrabSkillNo〕
  *(uint8_t *)(this + 8292) = 0;  // this+8292〔bModeFlag(推断)〕
  *(uint32_t *)(this + 8296) = 0;  // this+8296〔nOffsetVal(推断)〕
  *(uint32_t *)(this + 8300) = 0;  // this+8300〔pHoldObj(推断)〕
  *(uint32_t *)(this + 8304) = 0;  // this+8304〔nHoldPosX(推断)〕
  *(uint32_t *)(this + 8308) = 0;  // this+8308〔nHoldPosY(推断)〕
  *(uint32_t *)(this + 8312) = 0;  // this+8312〔nHoldPosZ(推断)〕
  *(uint32_t *)(this + 8316) = 4;  // this+8316〔nHoldSrc(推断)〕
  *(uint32_t *)(this + 8320) = 0;  // this+8320〔pHoldHost(推断)〕
  *(uint8_t *)(this + 8324) = 0;  // this+8324〔bHoldMode(推断)〕
  *(uint8_t *)(this + 8325) = 0;  // this+8325〔bSubMode〕
  *(uint8_t *)(this + 8326) = 0;  // this+8326〔f_2086〕
  *(uint32_t *)(this + 8328) = 0;  // this+8328〔f_2088〕
  *(uint8_t *)(this + 8332) = 0;  // this+8332〔f_208C〕
  *(uint8_t *)(this + 8333) = 0;  // this+8333〔f_208D〕
  *(uint8_t *)(this + 8334) = 0;  // this+8334〔bPairOk〕
  *(uint32_t *)(this + 8336) = 0;  // this+8336〔pVtStack〕
  *(uint32_t *)(this + 8340) = 0;  // this+8340〔pAnimA(推断)〕
  *(uint32_t *)(this + 8344) = 0;  // this+8344〔nRideMode(推断)〕
  *(uint32_t *)(this + 8348) = 0;  // this+8348〔nPhaseParity(推断)〕
  *(uint32_t *)(this + 8352) = 0;  // this+8352〔nRideHost8352〕
  *(uint32_t *)(this + 8356) = 0;  // this+8356〔uPick8356(推断)〕
  *(uint8_t *)(this + 8360) = 0;  // this+8360〔pPickInfo8360(推断)〕
  *(uint32_t *)(this + 8364) = 0;  // this+8364〔pFrameObject(推断)〕
  *(uint32_t *)(this + 8368) = 0;  // this+8368〔nCoordB〕
  *(uint32_t *)(this + 8372) = 0;  // this+8372〔nDiffVal(推断)〕
  *(uint8_t *)(this + 8376) = 0;  // this+8376〔pFxObjB(推断)〕
  *(uint8_t *)(this + 8377) = 0;  // this+8377〔f_20B9〕
  *(uint32_t *)(this + 8380) = 0;  // this+8380〔pAnimC〕
  *(uint8_t *)(this + 8384) = 0;  // this+8384〔f_20C0〕
  *(uint32_t *)(this + 8388) = 0;  // this+8388〔pAnimD〕
  *(uint8_t *)(this + 8392) = 0;  // this+8392〔f_20C8〕
  *(uint32_t *)(this + 8396) = 0;  // this+8396〔nNameLookup(推断)〕
  *(uint32_t *)(this + 8400) = 0;  // this+8400〔pAppendage〕
  *(uint32_t *)(this + 8404) = 0;  // this+8404〔pFxObjD(推断)〕
  *(uint32_t *)(this + 8412) = 0;  // this+8412〔pAnimE(推断)〕
  *(uint32_t *)(this + 8432) = 0;  // this+8432〔pBuffObjA(推断)〕
  *(uint8_t *)(this + 8436) = 0;  // this+8436〔pBuffObjB(推断)〕
  *(uint8_t *)(this + 8437) = 0;  // this+8437〔f_20F5〕
  *(uint32_t *)(this + 8444) = 0;  // this+8444〔nSkillGate(推断)〕
  *(uint32_t *)(this + 8448) = 0;  // this+8448〔nFinishVal〕
  *(uint32_t *)(this + 8452) = 0;
  *(uint32_t *)(this + 8456) = 0;  // this+8456〔pAtkRateObj〕
  *(uint32_t *)(this + 8460) = 1065353216;  // this+8460〔f_AtkRate〕
  *(uint32_t *)(this + 8464) = 0;
  *(uint32_t *)(this + 8468) = 0;  // this+8468〔pSkillObj〕
  *(uint32_t *)(this + 8408) = 0;  // this+8408〔pRoplingObj〕
  *(uint32_t *)(this + 8472) = 0;  // this+8472〔nFinishFlag(推断)〕
  *(uint32_t *)(this + 8480) = 0;  // this+8480〔pAtkObj〕
  *(uint8_t *)(this + 8476) = 0;  // this+8476〔bFinishFlag(推断)〕
  *(uint8_t *)(this + 8477) = 0;  // this+8477〔f_211D〕
  *(uint32_t *)(this + 8484) = 0;
  *(uint32_t *)(this + 8488) = 0;
  *(uint32_t *)(this + 8492) = 0;
  *(uint32_t *)(this + 8496) = 0;  // this+8496〔nChargeState〕
  *(uint32_t *)(this + 8500) = 0;  // this+8500〔nChargeTime〕
  *(uint32_t *)(this + 8504) = 0;  // this+8504〔f_2138〕
  *(uint32_t *)(this + 8508) = 0;
  *(uint32_t *)(this + 8512) = 0;  // this+8512〔pAnimF(推断)〕
  *(uint32_t *)(this + 8516) = 0;
  *(uint32_t *)(this + 8520) = 0;  // this+8520〔bUseCtx(推断)〕
  *(uint32_t *)(this + 8524) = 0;  // this+8524〔bMonCfgFlag〕
  *(uint32_t *)(this + 8528) = 0;
  *(uint32_t *)(this + 8532) = 0;  // this+8532〔nPhaseValB〕
  *(uint32_t *)(this + 8536) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5E46C0 CNFighter__vmt1F8
// ------------------------------------------------------------
// 调: sub_47DCD0
int /*thiscall*/ CNFighter__vmt1F8(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：调: sub_47DCD0
{
  int pObj; // eax
  int *v6; // eax

  if ( *(this + 1639) == 16  // this+6556〔nBigState〕
    && *(this + 2060) == 4  // this+8240〔nParamCnt〕
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (uint32_t *)dword_8F7C04 == this  // 本地玩家对象
    && (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 776))(nArg2, 0) != 0 )  // 调虚槽 +776：异常状态查询
  {
    pObj = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 772))(nArg2, 0);  // 调虚槽 +772：17 状态槽数组访问（+6228+4*a2）
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj) < 200 )  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
    {
      v6 = (int *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 4);  // 调虚槽 +1160
      sub_47DCD0(v6, (int)this, -1);  // 调 震动/资源档位设置
    }
  }
  return IRDActiveObject__vmt1F8(this, nArg2, nArg3, nArg4);  // 返回 调 IRDActiveObject__vmt1F8
}



// ------------------------------------------------------------
// 0x5E4750 CNFighter__vmt200
// ------------------------------------------------------------
// 证: 叶子函数（5 行，无外调无字符串）
int /*stdcall*/ CNFighter__vmt200(int nArg1, int nArg2, int nArg3)  // 实现：证: 叶子函数（5 行，无外调无字符串）
{
  return IRDCharacter__vmt200(nArg1, nArg2, nArg3);  // 返回 调 IRDCharacter__vmt200
}



// ------------------------------------------------------------
// 0x5E47A0 CNFighter__vmt158
// ------------------------------------------------------------
// 证: 叶子函数（15 行，无外调无字符串）
int /*thiscall*/ CNFighter__vmt158(int this, int nArg2)  // 实现：证: 叶子函数（15 行，无外调无字符串）
{
  int result; // eax
  int pAtkRateObj; // ecx  | +0x2108 → ★ 攻击倍率组件（CNFighter；va=005E47A0）

  result = IRDCharacter__vmt158(this, nArg2);  // result = 调 IRDCharacter__vmt158
  pAtkRateObj = *(uint32_t *)(this + 8456);  // this+8456〔pAtkRateObj〕
  if ( pAtkRateObj != 0 )  // 若 fld_2108 非 0
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAtkRateObj + 80))(pAtkRateObj);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    if ( (uint8_t)result != 0 )
      *(float *)(this + 524) = *(float *)(this + 8460) * *(float *)(this + 524);  // this+524〔f_DmgScale〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x5E4DC0 sub_5E4DC0
// ------------------------------------------------------------
// 调: sub_5E4DC0 sub_4B1030 sub_64FC40 sub_650D30
uint32_t */*thiscall*/ sub_5E4DC0(uint32_t *this, int nArg2)  // 实现：调: sub_5E4DC0 sub_4B1030 sub_64FC40 sub_650D30
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNSuplexed;  // 构造装配 vftable：CNSuplexed
  sub_64FC40(this);  // 18 行小函数
  sub_650D30(nArg2);  // 参数化设置（+80 状态码）
  return this;
}



// ------------------------------------------------------------
// 0x5E4E20 CNSuplexed__vmt78
// ------------------------------------------------------------
// 证: 叶子函数（6 行，无外调无字符串）
char /*thiscall*/ CNSuplexed__vmt78(uint8_t *this, char pszArg2)  // 实现：证: 叶子函数（6 行，无外调无字符串）
{
  *(this + 84) = pszArg2;  // 字段 this+84〔起的树/有序容器定位〕
  return pszArg2;
}



// ------------------------------------------------------------
// 0x5E4E40 CNSuplexed__vmt0
// ------------------------------------------------------------
// 调: sub_5E4E70
void */*thiscall*/ CNSuplexed__vmt0(void *Block, char pszArg2)  // 实现：调: sub_5E4E70
{
  sub_5E4E70();
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5E4E70 sub_5E4E70
// ------------------------------------------------------------
// 调: sub_5E4E70 sub_5F6640
int /*thiscall*/ sub_5E4E70(uint32_t *this)  // 实现：调: sub_5E4E70 sub_5F6640
{
  int result; // eax

  *this = &vftbl_CNSuplexed;  // 构造装配 vftable：CNSuplexed
  nullsub_3();
  *this = &vftbl_IRDAppendage;  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // result = 调 sub_5F6640 返回值
  *(this + 2) = &vftbl_nengine__IObject;  // 构造装配 vftable：nengine__IObject
  *((uint8_t *)this + 12) = 0;  // this[12] = 0
  return result;
}



// ------------------------------------------------------------
// 0x5E4ED0 sub_5E4ED0
// ------------------------------------------------------------
// 调: sub_5E4ED0 sub_4B1030 sub_6500E0 sub_650D30
uint32_t */*thiscall*/ sub_5E4ED0(uint32_t *this, int nArg2)  // 实现：调: sub_5E4ED0 sub_4B1030 sub_6500E0 sub_650D30
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNGrabbedExplosion;  // 构造装配 vftable：CNGrabbedExplosion
  sub_6500E0(this);  // 状态块复位（+80..+96，+84 置 -1）
  sub_650D30(nArg2);  // 参数化设置（+80 状态码）
  return this;
}



// ------------------------------------------------------------
// 0x5E4F30 CNGrabbedExplosion__vmt0
// ------------------------------------------------------------
// 调: sub_5E4F60
void */*thiscall*/ CNGrabbedExplosion__vmt0(void *Block, char pszArg2)  // 实现：调: sub_5E4F60
{
  sub_5E4F60();
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5E4F60 sub_5E4F60
// ------------------------------------------------------------
// 调: sub_5E4F60 sub_5F6640
int /*thiscall*/ sub_5E4F60(uint32_t *this)  // 实现：调: sub_5E4F60 sub_5F6640
{
  int result; // eax

  *this = &vftbl_CNGrabbedExplosion;  // 构造装配 vftable：CNGrabbedExplosion
  nullsub_3();
  *this = &vftbl_IRDAppendage;  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // result = 调 sub_5F6640 返回值
  *(this + 2) = &vftbl_nengine__IObject;  // 构造装配 vftable：nengine__IObject
  *((uint8_t *)this + 12) = 0;  // this[12] = 0
  return result;
}



// ------------------------------------------------------------
// 0x5E4FC0 sub_5E4FC0
// ------------------------------------------------------------
// 调: sub_5E4FC0 sub_4B1030 sub_650340 sub_650D30
uint32_t */*thiscall*/ sub_5E4FC0(uint32_t *this, int nArg2)  // 实现：调: sub_5E4FC0 sub_4B1030 sub_650340 sub_650D30
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNThrownEnemy;  // 构造装配 vftable：CNThrownEnemy
  sub_650340(this);  // 与 ·sub_6500E0 同构（差异：+88 亦置 -1、共六字段）
  sub_650D30(nArg2);  // 参数化设置（+80 状态码）
  return this;
}



// ------------------------------------------------------------
// 0x5E5020 CNThrownEnemy__vmt0
// ------------------------------------------------------------
// 调: sub_5E5050
void */*thiscall*/ CNThrownEnemy__vmt0(void *Block, char pszArg2)  // 实现：调: sub_5E5050
{
  sub_5E5050();
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5E5050 sub_5E5050
// ------------------------------------------------------------
// 调: sub_5E5050 sub_5F6640
int /*thiscall*/ sub_5E5050(uint32_t *this)  // 实现：调: sub_5E5050 sub_5F6640
{
  int result; // eax

  *this = &vftbl_CNThrownEnemy;  // 构造装配 vftable：CNThrownEnemy
  nullsub_3();
  *this = &vftbl_IRDAppendage;  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // result = 调 sub_5F6640 返回值
  *(this + 2) = &vftbl_nengine__IObject;  // 构造装配 vftable：nengine__IObject
  *((uint8_t *)this + 12) = 0;  // this[12] = 0
  return result;
}



// ------------------------------------------------------------
// 0x5E50B0 sub_5E50B0
// ------------------------------------------------------------
// 调: sub_5E50B0 sub_47E720 sub_47E9D0
int sub_5E50B0()  // 实现：调: sub_5E50B0 sub_47E720 sub_47E9D0
{
  uint32_t *v0; // eax
  uint32_t *v1; // eax
  uint32_t *v2; // eax
  int result; // eax

  v0 = (uint32_t *)sub_47E720(1, 1u);  // v0 = 调 sub_47E720 返回值
  dword_795948 = sub_47E9D0(v0, 0);  // dword_795948 = 调 sub_47E9D0 返回值
  v1 = (uint32_t *)sub_47E720(1, 1u);  // v1 = 调 sub_47E720 返回值
  dword_79594C = sub_47E9D0(v1, 1u);  // dword_79594C = 调 sub_47E9D0 返回值
  v2 = (uint32_t *)sub_47E720(1, 0x36u);  // v2 = 调 sub_47E720 返回值
  result = sub_47E9D0(v2, 0);  // result = 调 sub_47E9D0 返回值
  dword_9B9348 = result;
  return result;
}



// ------------------------------------------------------------
// 0x5E51C0 sub_5E51C0
// ------------------------------------------------------------
// 调: sub_5E51C0 sub_623C10
int /*stdcall*/ sub_5E51C0(int nArg1, int nArg2, int nArg3)  // 实现：调: sub_5E51C0 sub_623C10
{
  sub_623C10(nArg1, nArg2, nArg3);  // 12 字节元素区间填充
  return nArg1 + 12 * nArg2;
}



// ------------------------------------------------------------
// 0x5E51F0 sub_5E51F0
// ------------------------------------------------------------
// 调: sub_5E51F0 sub_63A7C0
int /*stdcall*/ sub_5E51F0(int nArg1, int nArg2, int nArg3)  // 实现：调: sub_5E51F0 sub_63A7C0
{
  sub_63A7C0(nArg1, nArg2, nArg3);  // 强化结果公共件（30 行）
  return nArg1 + 8 * nArg2;
}



// ------------------------------------------------------------
// 0x5E5220 sub_5E5220
// ------------------------------------------------------------
// 调: sub_5E5220
uint32_t */*thiscall*/ sub_5E5220(uint32_t *this, uint32_t *uArg2, uint32_t *pArg3)  // 实现：调: sub_5E5220
{
  uint32_t *fld_e2; // esi
  uint32_t *v4; // eax
  uint32_t *pArg32; // edx

  fld_e2 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  v4 = pArg3 + 2;
  if ( pArg3 + 2 != fld_e2 )
  {
    pArg32 = pArg3;
    do  // do-while 循环体起点
    {
      *pArg32 = *v4;
      pArg32[1] = v4[1];  // pArg32[1] = 取 v4[1]
      v4 += 2;
      pArg32 += 2;
    }
    while ( v4 != fld_e2 );  // 条件循环
  }
  *(this + 2) -= 8;  // this+8〔nSkillRec8(推断)〕
  *uArg2 = pArg3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x5E5260 sub_5E5260
// ------------------------------------------------------------
// 调: sub_5E5260
void /*thiscall*/ sub_5E5260(void **this)  // 实现：调: sub_5E5260
{
  if ( *(this + 1) != nullptr )  // 空指针判定
    j__free(*(this + 1));  // this+4〔宿主对象〕
  *(this + 1) = nullptr;  // this+4〔宿主对象〕
  *(this + 2) = nullptr;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = nullptr;  // this+12〔nSkillRec12(推断)〕
}



// ------------------------------------------------------------
// 0x5E5290 CNFighter__vmt12C
// ------------------------------------------------------------
// 证: 叶子函数（47 行，无外调无字符串）
uint32_t */*thiscall*/ CNFighter__vmt12C(uint32_t *this, uint32_t *uArg2)  // 实现：证: 叶子函数（47 行，无外调无字符串）
{
  uint32_t *result; // eax
  uint32_t *v4; // ecx
  uint32_t *pVecEnd; // edx
  uint32_t *v6; // ecx

  IRDCharacter__vmt12C(uArg2);
  if ( (uint32_t *)*(this + 2075) == uArg2 )  // this+8300〔pHoldObj〕
    *(this + 2075) = 0;  // this+8300〔pHoldObj〕
  if ( (uint32_t *)*(this + 2089) == uArg2 )  // this+8356〔pHoldTarget〕
    *(this + 2089) = 0;  // this+8356〔pHoldTarget〕
  result = (uint32_t *)*(this + 2105);  // this+8420〔pVecBegin〕
  if ( result != (uint32_t *)*(this + 2106) )  // this+8424〔pVecEnd〕
  {
    while ( 1 )  // 条件循环
    {
      v4 = (uint32_t *)*result;
      result += 2;
      if ( v4 == uArg2 )  // 若 v4 == uArg2
        break;  // 跳出循环/分支
      if ( result == (uint32_t *)*(this + 2106) )  // this+8424〔pVecEnd〕
        goto LABEL_13;
    }
    pVecEnd = (uint32_t *)*(this + 2106);  // this+8424〔pVecEnd〕
    if ( result != pVecEnd )  // 若 result != fld_e2106
    {
      v6 = result - 2;
      do  // do-while 循环体起点
      {
        *v6 = *result;
        v6[1] = result[1];  // v6[1] = 取 result[1]
        result += 2;
        v6 += 2;
      }
      while ( result != pVecEnd );  // 条件循环
    }
    *(this + 2106) -= 8;  // this+8424〔pVecEnd〕
  }
LABEL_13:  // 标签 LABEL_13（跳转合流点）
  if ( uArg2 == this )  // 若 uArg2 == this
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 12);  // 调虚槽 +216：音效 TAG 查询
    return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 13);  // 调虚槽 +216：音效 TAG 查询
  }
  return result;
}



// ------------------------------------------------------------
// 0x5E5330 sub_5E5330
// ------------------------------------------------------------
// 调: sub_5E5330
void /*thiscall*/ sub_5E5330(int this)  // 实现：调: sub_5E5330
{
  if ( *(uint32_t *)(this + 84) != 0 )  // this+84〔pFxObjA(推断)〕
    j__free(*(void **)(this + 84));  // 释放 this+84〔pFxObjA(推断)〕堆块
  *(uint32_t *)(this + 84) = 0;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  *(uint32_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
}



// ------------------------------------------------------------
// 0x5E5360 sub_5E5360
// ------------------------------------------------------------
// 调: sub_5E5360 sub_579200 sub_44BD30 sub_5E51F0 sub_41FEB0
void /*thiscall*/ sub_5E5360(int this, int nArg2, unsigned int uArg3, int pArg4)  // 实现：调: sub_5E5360 sub_579200 sub_44BD30 sub_5E51F0 sub_41FEB0
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
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else  // 否则分支
    fld_C = 0;
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )
      sub_579200(this);  // 角色构造前置（4015C0/401740）
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);  // fld_83 = 读 this+8
      v20 = (fld_83 - nArg2) >> 3 < uArg3;
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;
      if ( v20 )
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);  // 8 字节元素正向拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t *)(this + 8);  // fld_85 = 读 this+8
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);  // 调 填充补足尾段
        fld_86 = v30 + *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_86;  // this+8〔nSkillRec8(推断)〕等 2 字段
        sub_41FEB0(nArg2, fld_86 - v30, v28);  // 8B 元素区间拷贝
      }
      else  // 否则分支
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);  // 8 字节元素正向拷贝
        sub_44BD00(nArg2, v23, fld_832);  // 8 字节元素反向拷贝
        sub_41FEB0(nArg2, nArg2 + v30, v28);  // 8B 元素区间拷贝
      }
    }
    else  // 否则分支
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else  // 否则分支
        v11 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 非 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )  // 若 fld_4 非 0
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else  // 否则分支
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = 读 this+4
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);  // 8 字节元素正向拷贝
      sub_63A7C0(v32, uArg3, v28);  // 强化结果公共件（30 行）
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);  // 8 字节元素正向拷贝
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = 读 this+4
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pMem[v31];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[8 * v17];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
    }
  }
}


// ------------------------------------------------------------
// 0x5E55B0 sub_5E55B0
// ------------------------------------------------------------
// 调: sub_5E55B0 sub_50F360 sub_59EE30 sub_504450 sub_5043B0
int /*thiscall*/ sub_5E55B0(int *this, int pArg2, unsigned int uArg3, int *Block)  // 实现：调: sub_5E55B0 sub_50F360 sub_59EE30 sub_504450 sub_5043B0
{
  int v5; // ecx
  int v6; // edx
  int pVecEnd_14; // ebx
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
  v6 = Block[1];  // v6 = 取 Block[1]
  pVecEnd_14 = *(this + 1);  // this+4〔宿主对象〕
  result = Block[2];  // result = 取 Block[2]
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
  {
    result = 715827883 * (*(this + 3) - pVecEnd_14);
    fld_e3 = (*(this + 3) - pVecEnd_14) / 12;  // this+12〔nSkillRec12(推断)〕
  }
  else  // 否则分支
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
      fld_e2 = (*(this + 2) - pVecEnd_14) / 12;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_50F360(this);  // vector 超长异常（length_error，不返回）
    if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
      fld_e22 = (*(this + 2) - pVecEnd_14) / 12;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
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
        return sub_5043B0(pArg2, pArg2 + 12 * uArg3, v25);  // 返回 调 sub_5043B0 返回值
      }
      else  // 否则分支
      {
        sub_59EE30(pArg2, fld_e23, pArg2 + 12 * uArg3);  // 三元组块搬移辅助
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 12;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);  // 调 填充补足尾段
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        return sub_5043B0(pArg2, fld_e26 - 12 * uArg3, v25);  // 返回 调 sub_5043B0 返回值
      }
    }
    else  // 否则分支
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else  // 否则分支
        v13 = 0;
      if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
        fld_e27 = (*(this + 2) - pVecEnd_14) / 12;  // this+8〔nSkillRec8(推断)〕
      else  // 否则分支
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);  // sub_4DA030 —— v13 = 插入数 + sub_4DA030（当前数）
      v15 = 12 * v13;
      Blocka = (char *)operator new(12 * v13);
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pArg2, Blocka);  // 三元组块搬移辅助
      sub_623C10(v28, uArg3, v25);  // 12 字节元素区间填充
      sub_59EE30(pArg2, *(this + 2), v28 + 12 * uArg3);  // 三元组块搬移辅助
      fld_e13 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e13 != 0 )  // 若 fld_e13 非 0
        fld_e13 = (*(this + 2) - fld_e13) / 12;  // this+8〔nSkillRec8(推断)〕
      v17 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )  // this+4〔宿主对象〕
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      *(this + 3) = (int)&Blocka[v15];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&Blocka[12 * v17];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)Blocka;  // this+4〔宿主对象〕
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5E5860 sub_5E5860
// ------------------------------------------------------------
// 调: sub_5E5860 sub_50F360 sub_44BD30 sub_5E51F0 sub_41FEB0
void /*thiscall*/ sub_5E5860(int this, int nArg2, unsigned int uArg3, int pArg4)  // 实现：调: sub_5E5860 sub_50F360 sub_44BD30 sub_5E51F0 sub_41FEB0
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
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else  // 否则分支
    fld_C = 0;
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )
      sub_50F360(this);  // vector 超长异常（length_error，不返回）
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);  // fld_83 = 读 this+8
      v20 = (fld_83 - nArg2) >> 3 < uArg3;
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;
      if ( v20 )
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);  // 8 字节元素正向拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t *)(this + 8);  // fld_85 = 读 this+8
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);  // 调 填充补足尾段
        fld_86 = v30 + *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_86;  // this+8〔nSkillRec8(推断)〕等 2 字段
        sub_41FEB0(nArg2, fld_86 - v30, v28);  // 8B 元素区间拷贝
      }
      else  // 否则分支
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);  // 8 字节元素正向拷贝
        sub_44BD00(nArg2, v23, fld_832);  // 8 字节元素反向拷贝
        sub_41FEB0(nArg2, nArg2 + v30, v28);  // 8B 元素区间拷贝
      }
    }
    else  // 否则分支
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else  // 否则分支
        v11 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 非 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )  // 若 fld_4 非 0
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else  // 否则分支
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = 读 this+4
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);  // 8 字节元素正向拷贝
      sub_63A7C0(v32, uArg3, v28);  // 强化结果公共件（30 行）
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);  // 8 字节元素正向拷贝
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = 读 this+4
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pMem[v31];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[8 * v17];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
    }
  }
}


// ------------------------------------------------------------
// 0x5E5AB0 sub_5E5AB0
// ------------------------------------------------------------
// 调: sub_5E5AB0 sub_5E55B0
uint32_t */*thiscall*/ sub_5E5AB0(int *this, uint32_t *uArg2, int nArg3, int *Block)  // 实现：调: sub_5E5AB0 sub_5E55B0
{
  int pVecEnd_5; // esi
  int v6; // esi

  pVecEnd_5 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_5 != 0 && (*(this + 2) - pVecEnd_5) / 12 != 0 )  // 若 pVecEnd_5 != 0
    v6 = (nArg3 - pVecEnd_5) / 12;
  else  // 否则分支
    v6 = 0;
  sub_5E55B0(this, nArg3, 1u, Block);
  *uArg2 = *(this + 1) + 12 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x5E5B20 sub_5E5B20
// ------------------------------------------------------------
// 调: sub_5E5B20 sub_4B1030 sub_603900 sub_603A50
uint32_t */*thiscall*/ sub_5E5B20(uint32_t *this, int nArg2, char pszArg3, void *Src)  // 实现：调: sub_5E5B20 sub_4B1030 sub_603900 sub_603A50
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNChangeElementTolerance;  // 构造装配 vftable：CNChangeElementTolerance
  *(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  *(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *(this + 24) = 0;  // this+96〔nStatusMode(推断)〕
  *(this + 32) = 15;  // this+128〔szStatusKeyBuf(推断)〕
  *(this + 31) = 0;  // this+124〔pAuraAnim(推断)〕
  *((uint8_t *)this + 108) = 0;  // this[108] = 0
  sub_603900(this);
  sub_603A50(nArg2, pszArg3, Src);  // 三元配置写入
  return this;
}



// ------------------------------------------------------------
// 0x5E5BA0 sub_5E5BA0
// ------------------------------------------------------------
// 调: sub_5E5BA0 sub_4B1030 sub_6037B0
uint32_t */*thiscall*/ sub_5E5BA0(uint32_t *this, int nArg2)  // 实现：调: sub_5E5BA0 sub_4B1030 sub_6037B0
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNChangeActiveProperty;  // 构造装配 vftable：CNChangeActiveProperty
  *(this + 21) = 0;  // this+84〔pFxObjA(推断)〕
  *(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  *(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  nullsub_3();
  sub_6037B0(nArg2);  // 目标句柄 setter
  return this;
}



// ------------------------------------------------------------
// 0x5E5C10 sub_5E5C10
// ------------------------------------------------------------
// 调: sub_5E5C10 sub_4B1030 sub_650540 sub_650560
uint32_t */*thiscall*/ sub_5E5C10(uint32_t *this, int nArg2, float fArg3, int nArg4, int nArg5, int nArg6, int nArg7)  // 实现：调: sub_5E5C10 sub_4B1030 sub_650540 sub_650560
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNEnchantActiveStatus;  // 构造装配 vftable：CNEnchantActiveStatus
  *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *(this + 28) = 0;  // this+112〔pHostComp112〕
  *(this + 29) = 0;  // this+116〔会话上下文〕
  sub_650540(this);  // 状态块初始化（+80=17 默认态、+93 使能）
  sub_650560(nArg2, fArg3, nArg4, nArg5, nArg6, nArg7);  // 宿主表现转发（float 拆双栈参走 vt+120）
  return this;
}



// ------------------------------------------------------------
// 0x5E5C90 CNEnchantActiveStatus__vmt78
// ------------------------------------------------------------
// 证: 叶子函数（11 行，无外调无字符串）
char /*thiscall*/ CNEnchantActiveStatus__vmt78(int this, int nArg2, int nArg3, int nArg4, char pszArg5, int nArg6, char pszArg7)  // 实现：证: 叶子函数（11 行，无外调无字符串）
{
  *(uint32_t *)(this + 80) = nArg2;  // this+80〔nStatusId〕
  *(float *)(this + 84) = (float)nArg3;  // this+84〔fStatusValue〕
  *(uint32_t *)(this + 88) = nArg4;  // this+88〔nStatusDur〕
  *(uint8_t *)(this + 92) = pszArg5;  // this+92〔bStatusFlag〕
  *(uint32_t *)(this + 44) = nArg6;  // this+44〔nTimerParam〕
  *(uint8_t *)(this + 93) = pszArg7;  // this+93〔bEnableFlag〕
  return pszArg7;
}



// ------------------------------------------------------------
// 0x5E5CC0 CNEnchantActiveStatus__vmt0
// ------------------------------------------------------------
// 调: sub_5E5CF0
void */*thiscall*/ CNEnchantActiveStatus__vmt0(void *Block, char pszArg2)  // 实现：调: sub_5E5CF0
{
  sub_5E5CF0();
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5E5CF0 sub_5E5CF0
// ------------------------------------------------------------
// 调: sub_5E5CF0 sub_5F6640
int /*thiscall*/ sub_5E5CF0(void **this)  // 实现：调: sub_5E5CF0 sub_5F6640
{
  int result; // eax

  *this = &vftbl_CNEnchantActiveStatus;  // 构造装配 vftable：CNEnchantActiveStatus
  nullsub_3();
  if ( *(this + 27) != nullptr )  // 空指针判定
    j__free(*(this + 27));  // this+108〔nAdd108(推断)〕
  *(this + 27) = nullptr;  // this+108〔nAdd108(推断)〕
  *(this + 28) = nullptr;  // this+112〔pHostComp112〕
  *(this + 29) = nullptr;  // this+116〔会话上下文〕
  *this = &vftbl_IRDAppendage;  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // result = 调 sub_5F6640 返回值
  *((uint8_t *)this + 12) = 0;  // this[12] = 0
  *(this + 2) = &vftbl_nengine__IObject;  // 构造装配 vftable：nengine__IObject
  return result;
}



// ------------------------------------------------------------
// 0x5E5D70 sub_5E5D70
// ------------------------------------------------------------
// 调: sub_5E5D70 sub_63A7C0 sub_5E5360
void /*thiscall*/ sub_5E5D70(int this, int nArg2)  // 实现：调: sub_5E5D70 sub_63A7C0 sub_5E5360
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3 )  // 若 fld_4 != 0
  {
    fld_82 = *(uint32_t *)(this + 8);  // fld_82 = 读 this+8
    sub_63A7C0(fld_82, 1, nArg2);  // 强化结果公共件（30 行）
    *(uint32_t *)(this + 8) = fld_82 + 8;  // this+8〔nSkillRec8(推断)〕等 2 字段
  }
  else  // 否则分支
  {
    sub_5E5360(this, *(char **)(this + 8), 1u, nArg2);  // this+32〔nHeight(推断)〕
  }
}



// ------------------------------------------------------------
// 0x5E5DE0 sub_5E5DE0
// ------------------------------------------------------------
// 调: sub_5E5DE0 sub_5E5AB0 sub_623C10
uint32_t */*thiscall*/ sub_5E5DE0(int *this, int *Block)  // 实现：调: sub_5E5DE0 sub_5E5AB0 sub_623C10
{
  int pVecEnd_7; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  pVecEnd_7 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_7 != 0 )  // 若 fld_e1 非 0
    fld_e2 = (*(this + 2) - pVecEnd_7) / 12;  // this+8〔nSkillRec8(推断)〕
  else  // 否则分支
    fld_e2 = 0;
  if ( pVecEnd_7 == 0 || fld_e2 >= (*(this + 3) - pVecEnd_7) / 12 )  // 若 pVecEnd_7 == 0
    return sub_5E5AB0(this, &Block, *(this + 2), Block);  // 返回 调 sub_5E5AB0 返回值
  fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  result = (uint32_t *)sub_623C10(fld_e22, 1, Block);  // 12 字节元素区间填充
  *(this + 2) = fld_e22 + 12;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x5E5E60 sub_5E5E60
// ------------------------------------------------------------
// 调: sub_5E5E60 sub_63A7C0 sub_5E5860
void /*thiscall*/ sub_5E5E60(int this, int nArg2)  // 实现：调: sub_5E5E60 sub_63A7C0 sub_5E5860
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3 )  // 若 fld_4 != 0
  {
    fld_82 = *(uint32_t *)(this + 8);  // fld_82 = 读 this+8
    sub_63A7C0(fld_82, 1, nArg2);  // 强化结果公共件（30 行）
    *(uint32_t *)(this + 8) = fld_82 + 8;  // this+8〔nSkillRec8(推断)〕等 2 字段
  }
  else  // 否则分支
  {
    sub_5E5860(this, *(char **)(this + 8), 1u, nArg2);  // this+32〔nHeight(推断)〕
  }
}



// ------------------------------------------------------------
// 0x5E5ED0 sub_5E5ED0
// ------------------------------------------------------------
// 调: sub_5E5ED0 sub_5E5DE0
uint32_t */*thiscall*/ sub_5E5ED0(int *this, int nArg2, char pszArg3, int nArg4)  // 实现：调: sub_5E5ED0 sub_5E5DE0
{
  int Block; // [esp+0h] [ebp-Ch] BYREF
  char pszArg32; // [esp+4h] [ebp-8h]
  int nArg42; // [esp+8h] [ebp-4h]

  pszArg32 = pszArg3;
  Block = nArg2;
  nArg42 = nArg4;
  return sub_5E5DE0(this + 21, &Block);  // this+21〔bArmorState〕
}



// ------------------------------------------------------------
// 0x5E5F00 sub_5E5F00
// ------------------------------------------------------------
// 调: sub_5E5F00 sub_5E5E60
void /*thiscall*/ sub_5E5F00(void *this, int nArg2, int nArg3)  // 实现：调: sub_5E5F00 sub_5E5E60
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = nArg2;
  v3[1] = nArg3;
  sub_5E5E60((int)this + 80, (int)v3);
}



// ------------------------------------------------------------
// 0x5E5F30 sub_5E5F30
// ------------------------------------------------------------
// 证: "R_FT_KICK_JUMP" | "R_FT_DMG" | "R_FT_DIE" | "FT_JUMP"
// 调: sub_5E5F30 sub_430C80 sub_4015C0
int /*thiscall*/ sub_5E5F30(int this)  // 实现：调: sub_5E5F30 sub_430C80 sub_4015C0
{
  int pThis_1ED4; // edi
  int fld_1ED8; // eax
  unsigned int fld_1EDC; // edx
  uint32_t *fld_1EDC2; // eax
  int v6; // edx
  unsigned int v7; // ecx
  uint32_t *v8; // eax
  int v9; // edx
  unsigned int v10; // ecx
  uint32_t *v11; // eax
  int v12; // edx
  unsigned int v13; // ecx
  uint32_t *v14; // eax
  int v16; // [esp+Ch] [ebp-4h] BYREF

  pThis_1ED4 = this + 7892;
  *(uint32_t *)(this + 6792) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(uint32_t *)(this + 6796) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(uint32_t *)(this + 6800) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(uint32_t *)(this + 6804) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(uint32_t *)(this + 6808) = 4;  // this+6808〔nVoiceParam4(推断)〕
  *(uint32_t *)(this + 6864) = 1;
  *(uint32_t *)(this + 6868) = 7;
  *(uint32_t *)(this + 6872) = 13;
  fld_1ED8 = *(uint32_t *)(this + 7896);  // fld_1ED8 = 读 this+7896
  v16 = 1;
  if ( fld_1ED8 != 0 )  // 若 fld_1ED8 非 0
    fld_1EDC = (*(uint32_t *)(this + 7900) - fld_1ED8) >> 2;  // 向量元素数 = (end−begin)/4
  else  // 否则分支
    fld_1EDC = 0;
  if ( fld_1ED8 != 0 && fld_1EDC < (*(uint32_t *)(this + 7904) - fld_1ED8) >> 2 )  // 若 fld_1ED8 != 0
  {
    fld_1EDC2 = *(uint32_t **)(this + 7900);  // fld_1EDC2 = 读 this+7900
    *fld_1EDC2 = 1;
    *(uint32_t *)(this + 7900) = fld_1EDC2 + 1;
  }
  else  // 否则分支
  {
    sub_430C80(*(void **)(this + 7900), 1, (int)&v16);  // uint32 vector 区间插入（同值填充）
  }
  v6 = *(uint32_t *)(pThis_1ED4 + 4);  // pThis_1ED4+4〔宿主对象〕
  v16 = 1;
  if ( v6 != 0 )  // 若 v6 非 0
    v7 = (*(uint32_t *)(pThis_1ED4 + 8) - v6) >> 2;  // pThis_1ED4+8〔nSkillRec8(推断)〕
  else  // 否则分支
    v7 = 0;
  if ( v6 != 0 && v7 < (*(uint32_t *)(pThis_1ED4 + 12) - v6) >> 2 )  // 若 v6 != 0
  {
    v8 = *(uint32_t **)(pThis_1ED4 + 8);  // pThis_1ED4+8〔nSkillRec8(推断)〕
    *v8 = 1;
    *(uint32_t *)(pThis_1ED4 + 8) = v8 + 1;  // pThis_1ED4+8〔nSkillRec8(推断)〕
  }
  else  // 否则分支
  {
    sub_430C80(*(void **)(pThis_1ED4 + 8), 1, (int)&v16);  // uint32 vector 区间插入（同值填充）
  }
  v9 = *(uint32_t *)(pThis_1ED4 + 4);  // pThis_1ED4+4〔宿主对象〕
  v16 = 4;
  if ( v9 != 0 )  // 若 v9 非 0
    v10 = (*(uint32_t *)(pThis_1ED4 + 8) - v9) >> 2;  // pThis_1ED4+8〔nSkillRec8(推断)〕
  else  // 否则分支
    v10 = 0;
  if ( v9 != 0 && v10 < (*(uint32_t *)(pThis_1ED4 + 12) - v9) >> 2 )  // 若 v9 != 0
  {
    v11 = *(uint32_t **)(pThis_1ED4 + 8);  // pThis_1ED4+8〔nSkillRec8(推断)〕
    *v11 = 4;
    *(uint32_t *)(pThis_1ED4 + 8) = v11 + 1;  // pThis_1ED4+8〔nSkillRec8(推断)〕
  }
  else  // 否则分支
  {
    sub_430C80(*(void **)(pThis_1ED4 + 8), 1, (int)&v16);  // uint32 vector 区间插入（同值填充）
  }
  v12 = *(uint32_t *)(pThis_1ED4 + 4);  // pThis_1ED4+4〔宿主对象〕
  v16 = 3;
  if ( v12 != 0 )  // 若 v12 非 0
    v13 = (*(uint32_t *)(pThis_1ED4 + 8) - v12) >> 2;  // pThis_1ED4+8〔nSkillRec8(推断)〕
  else  // 否则分支
    v13 = 0;
  if ( v12 != 0 && v13 < (*(uint32_t *)(pThis_1ED4 + 12) - v12) >> 2 )  // 若 v12 != 0
  {
    v14 = *(uint32_t **)(pThis_1ED4 + 8);  // pThis_1ED4+8〔nSkillRec8(推断)〕
    *v14 = 3;
    *(uint32_t *)(pThis_1ED4 + 8) = v14 + 1;  // pThis_1ED4+8〔nSkillRec8(推断)〕
  }
  else  // 否则分支
  {
    sub_430C80(*(void **)(pThis_1ED4 + 8), 1, (int)&v16);  // uint32 vector 区间插入（同值填充）
  }
  *(uint32_t *)(this + 7908) = 600;
  *(uint32_t *)(this + 7912) = -10000;
  *(uint32_t *)(this + 7916) = 1200;
  *(uint32_t *)(this + 7920) = -10000;
  *(uint32_t *)(this + 7844) = 65;
  *(uint32_t *)(this + 7848) = 50;
  *(uint32_t *)(this + 7852) = 1;
  *(uint32_t *)(this + 7928) = 2;
  sub_4015C0("R_FT_KICK_JUMP", 0xEu);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0("R_FT_DMG", 8u);  // 【std::string构造赋值】
  sub_4015C0("R_FT_DIE", 8u);  // 【std::string构造赋值】
  sub_4015C0("FT_JUMP", 7u);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0("FT_BACKSTEP", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("R_FT_PAM_BREAST", 0xFu);  // 【std::string构造赋值】
  sub_4015C0("FT_NOMANA", 9u);  // 【std::string构造赋值】
  sub_4015C0("FT_COMMAND_PET", 0xEu);  // 【std::string构造赋值】
  return sub_4015C0("FT_THROW", 8u);  // 【std::string构造赋值】
}


// ------------------------------------------------------------
// 0x5E61C0 sub_5E61C0
// ------------------------------------------------------------
// 调: sub_5E61C0 sub_53FE50 sub_4B3C90 sub_47EF20 sub_5E5B20
void /*thiscall*/ sub_5E61C0(int *this, void *pArg2, void *Block)  // 实现：调: sub_5E61C0 sub_53FE50 sub_4B3C90 sub_47EF20 sub_5E5B20
{
  void *pMem; // eax
  int pObj4; // eax
  int fld_e2130; // ecx
  int pObj; // eax
  uint32_t *v8; // edi
  int v9; // eax
  int v10; // eax
  int fld_e2131; // ecx
  int pObj3; // eax
  uint32_t *v13; // eax
  int v14; // eax
  int fld_e2132; // ecx
  int pObj5; // eax
  uint32_t *v17; // eax
  int v18; // eax
  int fld_e2133; // ecx
  void *pMem2; // eax
  int pObj2; // eax
  int fld_e2134; // ecx
  float v23; // [esp+4h] [ebp-18h]
  unsigned int v24; // [esp+8h] [ebp-14h]
  void *Blocka; // [esp+28h] [ebp+Ch]

  sub_4B3E70(this, pArg2, (int)Block);  // Buff 图标/状态附加物增删
  if ( pArg2 == (void *)7 )
  {
    if ( (int)Block <= 0 )
    {
      fld_e2130 = *(this + 2130);  // this+8520〔bUseCtx(推断)〕
      if ( fld_e2130 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2130 + 80))(fld_e2130) != 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        sub_53FE50(*(this + 2130));  // this+8520〔bUseCtx(推断)〕
    }
    else  // 否则分支
    {
      if ( *(this + 2130) == 0 )  // this+8520〔bUseCtx(推断)〕
      {
        pMem = operator new(0x7Cu);  // new(124 字节) 分配对象
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          pObj4 = sub_4B3C90((int)pMem, 0, 0);  // CNChangeStatus 构造（双参）
        else  // 否则分支
          pObj4 = 0;
        *(this + 2130) = pObj4;  // this+8520〔bUseCtx(推断)〕
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 64))(pObj4) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
      }
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 7);  // 调虚槽 +1160
      Blocka = (void *)sub_47EF20(0, Block, -1, -1, 11);  // Blocka = 调 sub_47EF20 返回值
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2130) + 124))(*(this + 2130));  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      v23 = (float)(int)Blocka;
      (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)*(this + 2130) + 120))(5, 0, LODWORD(v23));  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2130) + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
        *(this + 2130),  // this+8520〔bUseCtx(推断)〕
        this,
        this,
        0,
        0,
        0,
        -1);
    }
  }
  else if ( pArg2 == (void *)29 )
  {
    if ( (int)Block <= 0 )
    {
      fld_e2131 = *(this + 2131);  // this+8524〔bMonCfgFlag〕
      if ( fld_e2131 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2131 + 80))(fld_e2131) != 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        sub_53FE50(*(this + 2131));  // this+8524〔bMonCfgFlag〕
    }
    else  // 否则分支
    {
      if ( *(this + 2131) == 0 )  // this+8524〔bMonCfgFlag〕
      {
        if ( operator new(0x84u) != nullptr )  // new(132 字节) 分配对象
          pObj = sub_5E5B20(0, 0, nullptr);  // pObj = 调 sub_5E5B20 返回值
        else  // 否则分支
          pObj = 0;
        *(this + 2131) = pObj;  // this+8524〔bMonCfgFlag〕
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
        v8 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 29);  // 调虚槽 +1160
        v9 = sub_47E9D0(v8, 0);  // v9 = 调 sub_47E9D0 返回值
        sub_5E5ED0(3, 0, v9);
        v10 = sub_47E9D0(v8, 1u);  // v10 = 调 sub_47E9D0 返回值
        sub_5E5ED0(2, 0, v10);
      }
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2131) + 56))(  // this+8524〔bMonCfgFlag〕
        *(this + 2131),  // this+8524〔bMonCfgFlag〕
        this,
        this,
        0,
        0,
        0,
        -1);
    }
  }
  else if ( pArg2 == (void *)32 )
  {
    if ( (int)Block <= 0 )
    {
      fld_e2132 = *(this + 2132);
      if ( fld_e2132 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2132 + 80))(fld_e2132) != 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        sub_53FE50(*(this + 2132));
    }
    else  // 否则分支
    {
      if ( *(this + 2132) == 0 )
      {
        if ( operator new(0x60u) != nullptr )  // new(96 字节) 分配对象
          pObj3 = sub_5E5BA0(0);  // pObj3 = 调 sub_5E5BA0 返回值
        else  // 否则分支
          pObj3 = 0;
        *(this + 2132) = pObj3;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 64))(pObj3) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
      }
      sub_5E5330(*(this + 2132));
      v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 1160))(this, 32, 0);  // 调虚槽 +1160
      v14 = sub_47E9D0(v13, v24);  // v14 = 调 sub_47E9D0 返回值
      sub_5E5F00(2, v14);
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2132) + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
        *(this + 2132),
        this,
        this,
        0,
        0,
        0);
    }
  }
  else if ( pArg2 == (void *)35 )
  {
    if ( (int)Block <= 0 )
    {
      fld_e2133 = *(this + 2133);  // this+8532〔nPhaseValB〕
      if ( fld_e2133 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2133 + 80))(fld_e2133) != 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        sub_53FE50(*(this + 2133));  // this+8532〔nPhaseValB〕
    }
    else  // 否则分支
    {
      if ( *(this + 2133) == 0 )  // this+8532〔nPhaseValB〕
      {
        if ( operator new(0x60u) != nullptr )  // new(96 字节) 分配对象
          pObj5 = sub_5E5BA0(0);  // pObj5 = 调 sub_5E5BA0 返回值
        else  // 否则分支
          pObj5 = 0;
        *(this + 2133) = pObj5;  // this+8532〔nPhaseValB〕
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 64))(pObj5) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
      }
      sub_5E5330(*(this + 2133));  // this+8532〔nPhaseValB〕
      v17 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 1160))(this, 35, 0);  // 调虚槽 +1160
      v18 = sub_47E9D0(v17, v24);  // v18 = 调 sub_47E9D0 返回值
      sub_5E5F00(5, v18);
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2133) + 56))(  // this+8532〔nPhaseValB〕
        *(this + 2133),  // this+8532〔nPhaseValB〕
        this,
        this,
        0,
        0,
        0);
    }
  }
  else if ( pArg2 == (void *)45 )
  {
    if ( (int)Block <= 0 )
    {
      fld_e2134 = *(this + 2134);
      if ( fld_e2134 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2134 + 80))(fld_e2134) != 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        sub_53FE50(*(this + 2134));
    }
    else  // 否则分支
    {
      if ( *(this + 2134) == 0 )
      {
        pMem2 = operator new(0x88u);  // new(136 字节) 分配对象
        if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
          pObj2 = sub_4C2820((int)pMem2, 1, 45);  // pObj2 = 调 sub_4C2820 返回值
        else  // 否则分支
          pObj2 = 0;
        *(this + 2134) = pObj2;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
      }
      sub_5F9DD0(Block);
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2134) + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
        *(this + 2134),
        this,
        this,
        0,
        0,
        0,
        -1);
    }
  }
}


// ------------------------------------------------------------
// 0x5E6640 sub_5E6640
// ------------------------------------------------------------
// 调: sub_5E6640 sub_430C80
void */*thiscall*/ sub_5E6640(uint32_t *this)  // 实现：调: sub_5E6640 sub_430C80
{
  uint32_t *pThis_849; // edi
  int i; // ebx
  void *result; // eax
  int fld_e2075; // ecx
  int fld_e20752; // eax
  int fld_e20753; // ecx
  int v8; // eax
  int fld_e20754; // ecx
  int v10; // edi
  bool fld_e20755; // zf
  int fld_e20756; // eax
  char v13; // al
  int fld_e20757; // edx
  int fld_e2120; // ecx
  uint8_t v16[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  void *Src; // [esp+14h] [ebp-20h]
  int v19; // [esp+18h] [ebp-1Ch]
  int v20; // [esp+1Ch] [ebp-18h] BYREF
  int fld_e207522; // [esp+20h] [ebp-14h] BYREF
  int v22; // [esp+24h] [ebp-10h] BYREF
  int v23; // [esp+30h] [ebp-4h]

  pThis_849 = this + 2121;
  for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
    result = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *pThis_849++);  // 调虚槽 +208：定时器移除
  fld_e2075 = *(this + 2075);  // this+8300〔pHoldObj(推断)〕
  if ( fld_e2075 != 0 )  // 若 fld_e2075 非 0
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2075 + 308))(fld_e2075) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      fld_e20752 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2075) + 120))(*(this + 2075));  // 调虚槽 +120：动画对象
      fld_e20753 = *(this + 2075);  // this+8300〔pHoldObj(推断)〕
      fld_e207522 = fld_e20752;
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e20753 + 124))(fld_e20753);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      fld_e20754 = *(this + 2075);  // this+8300〔pHoldObj(推断)〕
      v22 = v8;
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e20754 + 128))(fld_e20754);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 2075) + 136))(  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
             *(this + 2075),  // this+8300〔pHoldObj(推断)〕
             fld_e207522,
             v22,
             0) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2075) + 132))(*(this + 2075), v10) != 0 )  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2075) + 108))(*(this + 2075), fld_e207522, v22, v10);  // 调虚槽 +108：CNRDPrivateStoreWindow__vmt6C 槽（10 行）
      }
      else  // 否则分支
      {
        fld_e20755 = (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)*(this + 2075)  // this+8300〔pHoldObj(推断)〕
                                                                                               + 140))(
                *(this + 2075),  // this+8300〔pHoldObj(推断)〕
                &fld_e207522,
                &v22,
                fld_e207522,
                v22,
                100,
                1,
                1) == 0;
        fld_e20756 = *(uint32_t *)*(this + 2075);  // fld_e20756 = 读 this+2075
        if ( fld_e20755 )
        {
          v13 = (*(int (/*cdecl*/ **)(int))(fld_e20756 + 132))(v10);  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
          fld_e20757 = *(uint32_t *)*(this + 2075);  // fld_e20757 = 读 this+2075
          if ( v13 != 0 )  // 若 v13 非 0
            (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int))(fld_e20757 + 108))(*(this + 2076), *(this + 2077), v10);  // 调虚槽 +108：CNRDPrivateStoreWindow__vmt6C 槽（10 行）
          else  // 否则分支
            (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t))(fld_e20757 + 108))(*(this + 2076), *(this + 2077), *(this + 2078));  // 调虚槽 +108：CNRDPrivateStoreWindow__vmt6C 槽（10 行）
        }
        else  // 否则分支
        {
          (*(void (/*stdcall*/ **)(int, int))(fld_e20756 + 108))(fld_e207522, v22);  // 调虚槽 +108：CNRDPrivateStoreWindow__vmt6C 槽（10 行）
        }
      }
      Block = nullptr;  // Block = 空指针
      Src = nullptr;  // Src = 空指针
      v19 = 0;
      v23 = 0;
      v20 = 4;
      sub_430C80(nullptr, 1, (int)&v20);  // uint32 vector 区间插入（同值填充）
      v20 = 0;
      sub_430C80(nullptr, 1, (int)&v20);  // uint32 vector 区间插入（同值填充）
      v20 = 1;
      sub_430C80(nullptr, 1, (int)&v20);  // uint32 vector 区间插入（同值填充）
      v20 = 400;
      sub_430C80(nullptr, 1, (int)&v20);  // uint32 vector 区间插入（同值填充）
      v20 = 400;
      sub_430C80(nullptr, 1, (int)&v20);  // uint32 vector 区间插入（同值填充）
      (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int, uint32_t))(*(uint32_t *)*(this + 2075) + 560))(  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        *(this + 2075),  // this+8300〔pHoldObj(推断)〕
        4,
        v16,
        2,
        0);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2075) + 564))(*(this + 2075));  // this+8300〔pHoldObj(推断)〕
      v23 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
      Block = nullptr;  // Block = 空指针
      Src = nullptr;  // Src = 空指针
      v19 = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2075) + 596))(*(this + 2075), 1);  // 调虚槽 +596：[RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActive…
    fld_e2120 = *(this + 2120);  // this+8480〔pAtkObj〕
    *(this + 2075) = 0;  // this+8300〔pHoldObj(推断)〕
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e2120 + 76))(fld_e2120, 0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
    return sub_432EA0("TOMBTONE_STUCK", -1, 0, 0);  // 音效播放包装（非空判定）
  }
  return result;
}


// ------------------------------------------------------------
// 0x5E6920 sub_5E6920
// ------------------------------------------------------------
// 调: sub_5E6920 sub_431230 sub_47E9D0 sub_47EFD0
int /*usercall*/ sub_5E6920@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：调: sub_5E6920 sub_431230 sub_47E9D0 sub_47EFD0
{
  int result; // eax
  uint32_t *v5; // ecx
  char *v6; // edi
  int v7; // ebx
  int v8; // eax
  uint32_t *v9; // ecx
  int v10; // eax
  uint32_t *v11; // ecx
  uint32_t *v12; // eax
  char v13; // al
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  char v19; // al
  uint32_t *v20; // edi
  int v21; // eax
  int v22; // [esp-24h] [ebp-94h]
  int v23; // [esp-20h] [ebp-90h]
  int v24; // [esp-1Ch] [ebp-8Ch]
  int v25; // [esp-18h] [ebp-88h]
  uint8_t v26[4]; // [esp+4h] [ebp-6Ch] BYREF
  void *Block; // [esp+8h] [ebp-68h]
  int v28; // [esp+Ch] [ebp-64h]
  int v29; // [esp+10h] [ebp-60h]
  int v30; // [esp+14h] [ebp-5Ch] BYREF
  int v31; // [esp+18h] [ebp-58h] BYREF
  int v32; // [esp+1Ch] [ebp-54h] BYREF
  int v33; // [esp+20h] [ebp-50h] BYREF
  int16_t v34; // [esp+24h] [ebp-4Ch]
  int16_t v35; // [esp+26h] [ebp-4Ah]
  int16_t v36; // [esp+28h] [ebp-48h]
  int v37; // [esp+2Ah] [ebp-46h]
  int v38; // [esp+2Eh] [ebp-42h]
  int16_t v39; // [esp+32h] [ebp-3Eh]
  char v40; // [esp+34h] [ebp-3Ch]
  int dword_796E502; // [esp+60h] [ebp-10h]
  int v42; // [esp+6Ch] [ebp-4h]

  result = dword_796E50;  // 帧时刻快照源
  v5 = (uint32_t *)pDwArg1[2075];
  dword_796E502 = dword_796E50;  // 帧时刻快照源
  if ( v5 != nullptr )  // 若 v5 有效（非空）
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v5 + 308))(v5) == 0 )  // 调虚槽 +308：是否本地玩家
    {
LABEL_13:  // 标签 LABEL_13（跳转合流点）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2102] + 76))(pDwArg1[2102], 0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 485020）
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2075] + 596))(pDwArg1[2075], 1);  // 调虚槽 +596：[RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActive…
      pDwArg1[2075] = 0;
      return result;
    }
    v6 = (char *)(*(int (/*thiscall*/ **)(int *, int, int, int))(*pDwArg1 + 1160))(pDwArg1, 49, nArg3, nArg2);  // 调虚槽 +1160
    v7 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1140))(pDwArg1, 49);  // 调虚槽 +1140
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2075] + 120))(pDwArg1[2075]);  // 调虚槽 +120：动画对象
    v9 = (uint32_t *)pDwArg1[2075];
    v31 = v8;
    v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*v9 + 124))(v9);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    v11 = (uint32_t *)pDwArg1[2075];
    v30 = v10;
    v32 = (*(int (/*thiscall*/ **)(uint32_t *))(*v11 + 128))(v11);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    v31 += (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) != 0 ? 40 : -40;  // 调虚槽 +152：效果通道 3
    v32 -= 10;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2075] + 136))(pDwArg1[2075], v31, v30, 0) != 0  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2075] + 132))(pDwArg1[2075], v32) != 0 )  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
    {
      v12 = (uint32_t *)v31;
    }
    else  // 否则分支
    {
      v13 = (*(int (/*thiscall*/ **)(int, int *, int *, int, int, int, int, int))(*(uint32_t *)pDwArg1[2075] + 140))(  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
              pDwArg1[2075],
              &v31,
              &v30,
              v31,
              v30,
              100,
              1,
              1);
      v14 = *(uint32_t *)pDwArg1[2075];
      if ( v13 != 0 )  // 若 v13 非 0
      {
        v12 = (uint32_t *)v31;
LABEL_10:  // 标签 LABEL_10（跳转合流点）
        (*(void (/*stdcall*/ **)(uint32_t *))(v14 + 108))(v12);  // 调虚槽 +108：CNRDPrivateStoreWindow__vmt6C 槽（10 行）
        Block = nullptr;  // Block = 空指针
        v28 = 0;
        v29 = 0;
        v42 = 0;
        v32 = 4;
        sub_431230((int)v26, &v32);  // uint32 vector push_back
        v32 = 0;
        sub_431230((int)v26, &v32);  // uint32 vector push_back
        v32 = 1;
        sub_431230((int)v26, &v32);  // uint32 vector push_back
        v32 = sub_47E9D0(v6, 1u);  // v32 = 调 sub_47E9D0 返回值
        sub_431230((int)v26, &v32);  // uint32 vector push_back
        v32 = sub_47E9D0(v6, 2u);  // v32 = 调 sub_47E9D0 返回值
        sub_431230((int)v26, &v32);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, int, uint32_t))(*(uint32_t *)pDwArg1[2075] + 560))(pDwArg1[2075], 4, v26, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2075] + 564))(pDwArg1[2075]);
        v15 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 388))(pDwArg1);  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
        v33 = sub_47EFD0(v6, COERCE_FLOAT(2), v7, v15, v15, 0);  // v33 = 调 sub_47EFD0 返回值
        v34 = sub_47E9D0(v6, 4u);  // v34 = 调 sub_47E9D0 返回值
        v35 = sub_47E9D0(v6, 3u);  // v35 = 调 sub_47E9D0 返回值
        v16 = *pDwArg1;
        v36 = -1;
        v17 = (*(int (/*thiscall*/ **)(int *))(v16 + 388))(pDwArg1);  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
        v37 = sub_47EFD0(v6, 0.0, v7, v17, v17, 0);  // v37 = 调 sub_47EFD0 返回值
        v18 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 388))(pDwArg1);  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
        v38 = sub_47EFD0(v6, COERCE_FLOAT(1), v7, v18, v18, 0);  // v38 = 调 sub_47EFD0 返回值
        v39 = sub_47E9D0(v6, 5u);  // v39 = 调 sub_47E9D0 返回值
        v19 = sub_47E9D0(v6, 6u);  // v19 = 调 sub_47E9D0 返回值
        v20 = (uint32_t *)pDwArg1[2075];
        v40 = v19;
        v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 152))(v20);  // 调虚槽 +152：效果通道 3
        v24 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 128))(v20);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 124))(v20);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v22 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 120))(v20);  // 调虚槽 +120：动画对象
        v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 56))(v20);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
        sub_4E4A50(pDwArg1, 48028, v21, v22, v23, v24, v25, 0, 21, &v33);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
        v42 = -1;
        if ( Block != nullptr )  // 若 Block 有效（非空）
          j__free(Block);
        Block = nullptr;  // Block = 空指针
        v28 = 0;
        v29 = 0;
        goto LABEL_13;
      }
      (*(void (/*stdcall*/ **)(int))(v14 + 132))(v32);  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
      v12 = (uint32_t *)pDwArg1[2076];
    }
    v14 = *(uint32_t *)pDwArg1[2075];
    goto LABEL_10;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5E6C50 sub_5E6C50
// ------------------------------------------------------------
// 调: sub_5E6C50 sub_42AF90 sub_657740
int /*thiscall*/ sub_5E6C50(int this)  // 实现：调: sub_5E6C50 sub_42AF90 sub_657740
{
  void (/*thiscall*/ ***pThis_2080)(uint32_t, int); // ecx
  void ***pThis_204C; // edi
  void **v4; // ebx
  void ***pThis_2090; // edi
  void **v6; // ebx
  int fld_20BC; // edi
  void **fld_20C4; // edi
  void (/*thiscall*/ ***pThis_20D0)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_20D8)(uint32_t, int); // ecx
  void **fld_20DC; // edi
  void (/*thiscall*/ ***pThis_2104)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_2108)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_2110)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_2114)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_2120)(uint32_t, int); // ecx
  void ***pThis_2124; // edi
  void **v18; // ebx
  int result; // eax
  int fld_2140; // edi
  int (/*thiscall*/ ***pThis_2148)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_214C)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_2150)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_2154)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_2158)(uint32_t, int); // ecx
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]
  int v28; // [esp+Ch] [ebp-4h]

  pThis_2080 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8320);  // this+8320〔pHoldHost(推断)〕
  if ( pThis_2080 != nullptr )  // 若 pThis_2080 有效（非空）
    (**pThis_2080)(pThis_2080, 1);  // 调 pThis_2080 的虚函数（vt+0）
  *(uint32_t *)(this + 8320) = 0;  // this+8320〔pHoldHost(推断)〕
  pThis_204C = (void ***)(this + 8268);  // this+8268〔nParamArr(推断)〕
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
  {
    v4 = *pThis_204C;
    if ( *pThis_204C != nullptr )  // 空指针判定
    {
      sub_42AF90(*pThis_204C);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v4, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_204C++ = nullptr;
  }
  pThis_2090 = (void ***)(this + 8336);  // this+8336〔pVtStack〕
  for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
  {
    v6 = *pThis_2090;
    if ( *pThis_2090 != nullptr )  // 空指针判定
    {
      sub_42AF90(*pThis_2090);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v6, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_2090++ = nullptr;
  }
  fld_20BC = *(uint32_t *)(this + 8380);  // this+8380〔pAnimC〕
  if ( fld_20BC != 0 )  // 若 fld_20BC 非 0
  {
    sub_42AF90(*(void ***)(this + 8380));  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_20BC, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_20C4 = *(void ***)(this + 8388);  // this+8388〔pAnimD〕
  *(uint32_t *)(this + 8380) = 0;  // this+8380〔pAnimC〕
  if ( fld_20C4 != nullptr )  // 若 fld_20C4 有效（非空）
  {
    sub_42AF90(fld_20C4);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_20C4, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_20D0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8400);  // this+8400〔pAppendage〕
  *(uint32_t *)(this + 8388) = 0;  // this+8388〔pAnimD〕
  if ( pThis_20D0 != nullptr )  // 若 pThis_20D0 有效（非空）
    (**pThis_20D0)(pThis_20D0, 1);  // 调 pThis_20D0 的虚函数（vt+0）
  pThis_20D8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8408);  // this+8408〔pRoplingObj〕
  *(uint32_t *)(this + 8400) = 0;  // this+8400〔pAppendage〕
  if ( pThis_20D8 != nullptr )  // 若 pThis_20D8 有效（非空）
    (**pThis_20D8)(pThis_20D8, 1);  // 调 pThis_20D8 的虚函数（vt+0）
  fld_20DC = *(void ***)(this + 8412);  // this+8412〔pAnimE(推断)〕
  *(uint32_t *)(this + 8408) = 0;  // this+8408〔pRoplingObj〕
  if ( fld_20DC != nullptr )  // 若 fld_20DC 有效（非空）
  {
    sub_42AF90(fld_20DC);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_20DC, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_2104 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8452);
  *(uint32_t *)(this + 8412) = 0;  // this+8412〔pAnimE(推断)〕
  if ( pThis_2104 != nullptr )  // 若 pThis_2104 有效（非空）
    (**pThis_2104)(pThis_2104, 1);  // 调 pThis_2104 的虚函数（vt+0）
  pThis_2108 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8456);  // this+8456〔pAtkRateObj〕
  *(uint32_t *)(this + 8452) = 0;
  if ( pThis_2108 != nullptr )  // 若 pThis_2108 有效（非空）
    (**pThis_2108)(pThis_2108, 1);  // 调 pThis_2108 的虚函数（vt+0）
  pThis_2110 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8464);
  *(uint32_t *)(this + 8456) = 0;  // this+8456〔pAtkRateObj〕
  if ( pThis_2110 != nullptr )  // 若 pThis_2110 有效（非空）
    (**pThis_2110)(pThis_2110, 1);  // 调 pThis_2110 的虚函数（vt+0）
  pThis_2114 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8468);  // this+8468〔pSkillObj〕
  *(uint32_t *)(this + 8464) = 0;
  if ( pThis_2114 != nullptr )  // 若 pThis_2114 有效（非空）
    (**pThis_2114)(pThis_2114, 1);  // 调 pThis_2114 的虚函数（vt+0）
  pThis_2120 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8480);  // this+8480〔pAtkObj〕
  *(uint32_t *)(this + 8468) = 0;  // this+8468〔pSkillObj〕
  if ( pThis_2120 != nullptr )  // 若 pThis_2120 有效（非空）
    (**pThis_2120)(pThis_2120, 1);  // 调 pThis_2120 的虚函数（vt+0）
  *(uint32_t *)(this + 8480) = 0;  // this+8480〔pAtkObj〕
  pThis_2124 = (void ***)(this + 8484);
  v28 = 3;
  do  // do-while 循环体起点
  {
    v18 = *pThis_2124;
    if ( *pThis_2124 != nullptr )  // 空指针判定
    {
      sub_42AF90(*pThis_2124);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v18, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_2124++ = nullptr;
    result = v28 - 1;
    v28 = result;
  }
  while ( result != 0 );  // 条件循环
  fld_2140 = *(uint32_t *)(this + 8512);  // fld_2140 = 读 this+8512
  if ( fld_2140 != 0 )  // 若 fld_2140 非 0
  {
    sub_42AF90(*(void ***)(this + 8512));  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_2140, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_2148 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8520);  // this+8520〔bUseCtx(推断)〕
  *(uint32_t *)(this + 8512) = 0;  // this+8512〔pAnimF(推断)〕
  if ( pThis_2148 != nullptr )  // 若 pThis_2148 有效（非空）
    result = (**pThis_2148)(pThis_2148, 1);  // 调 pThis_2148 的虚函数（vt+0）
  pThis_214C = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8524);  // this+8524〔bMonCfgFlag〕
  *(uint32_t *)(this + 8520) = 0;  // this+8520〔bUseCtx(推断)〕
  if ( pThis_214C != nullptr )  // 若 pThis_214C 有效（非空）
    result = (**pThis_214C)(pThis_214C, 1);  // 调 pThis_214C 的虚函数（vt+0）
  pThis_2150 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8528);
  *(uint32_t *)(this + 8524) = 0;  // this+8524〔bMonCfgFlag〕
  if ( pThis_2150 != nullptr )  // 若 pThis_2150 有效（非空）
    result = (**pThis_2150)(pThis_2150, 1);  // 调 pThis_2150 的虚函数（vt+0）
  pThis_2154 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8532);  // this+8532〔nPhaseValB〕
  *(uint32_t *)(this + 8528) = 0;
  if ( pThis_2154 != nullptr )  // 若 pThis_2154 有效（非空）
    result = (**pThis_2154)(pThis_2154, 1);  // 调 pThis_2154 的虚函数（vt+0）
  pThis_2158 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8536);
  *(uint32_t *)(this + 8532) = 0;  // this+8532〔nPhaseValB〕
  if ( pThis_2158 != nullptr )  // 若 pThis_2158 有效（非空）
    result = (**pThis_2158)(pThis_2158, 1);  // 调 pThis_2158 的虚函数（vt+0）
  *(uint32_t *)(this + 8536) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x5E6EE0 CNFighter__vmt1F4
// ------------------------------------------------------------
// 调: sub_4049C0 sub_4AED20
int /*thiscall*/ sub_5E6EE0(int *this, int pArg2, float *pArg3, int nArg4)  // 【CNFighter__vmt1F4】
{
  uint32_t *v5; // edi
  uint64_t pThis_61; // rax
  int pObj; // eax
  int nGrabSkillNo; // eax  | +0x205C → 0x5EA970 写入槽（v260）（CNFighter；va=005EA970）
  uint32_t *v9; // eax
  int v10; // ebx
  int v11; // eax
  int pObj3; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  uint64_t v17; // rax
  int v18; // eax
  double v19; // st7
  int v20; // eax
  int v21; // edx
  char *v22; // eax
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int pThis_2; // eax
  int pObj2; // ebx
  int v28; // eax
  int v29; // edx
  int v30; // eax
  int v31; // eax
  int v32; // edx
  int v33; // eax
  int v34; // eax
  int v35; // edx
  int v36; // eax
  int v37; // eax
  int nChargeTime; // eax  | +0x2134 → 0x5EA970: *(this+8500) >= dword_9B9348 门（CNFighter；va=005EA970）
  int v39; // edx
  int v40; // eax
  int fld_16C; // ecx  | +0x016C → ★ 场景动画池指针（CNFighter；va=005EA970）
  char *v42; // eax
  int *v43; // ebx
  int fld_e29; // ecx
  uint64_t v45; // rax
  int v46; // ebx
  int v47; // eax
  int v48; // eax
  int pAtkRateObj; // ecx  | +0x2108 → ★ 攻击倍率组件（CNFighter；va=005E47A0）
  float v51; // [esp+8h] [ebp-90h]
  int v52; // [esp+14h] [ebp-84h]
  int v53; // [esp+24h] [ebp-74h]
  unsigned int v54; // [esp+28h] [ebp-70h] BYREF
  int v55; // [esp+2Ch] [ebp-6Ch]
  int v56; // [esp+30h] [ebp-68h]
  void *v57; // [esp+34h] [ebp-64h] BYREF
  void *Block; // [esp+38h] [ebp-60h]
  uint32_t *v59; // [esp+3Ch] [ebp-5Ch] BYREF
  int pThis_22; // [esp+40h] [ebp-58h]
  int fld_e20712; // [esp+44h] [ebp-54h] BYREF  | +0x205C → 0x5EA970 写入槽（v260）（CNFighter；va=005EA970）
  uint32_t v62[17]; // [esp+48h] [ebp-50h] BYREF
  int v63; // [esp+94h] [ebp-4h]

  v62[16] = dword_796E50;  // 帧时刻快照源
  v5 = (uint32_t *)pArg2;
  if ( *(this + 1639) == 12 && *(this + 2055) == 1 )  // this+6556〔nBigState〕
  {
    pArg2 = *(this + 2056);  // this+8224〔f_2020〕
    if ( pArg2 != 0 )  // 若 pArg2 非 0
      *((float *)this + 97) = *((float *)this + 97) - (double)pArg2;  // this+388〔fAtkCtxVal〕
    pArg2 = (*(int (/*thiscall*/ **)(int *, uint32_t *, uint32_t))(*this + 8))(this, v5, 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    fld_e20712 = (uint64_t)(double)dword_79594C;
    v51 = (float)fld_e20712;
    pThis_61 = (uint64_t)((double)(int)(uint64_t)sub_4049C0(v51, 0.0, pArg2, dword_795948)  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
                          * *((float *)this + 97)  // this+388〔fAtkCtxVal〕
                          * 0.0099999998);  // ×0.01f（百分数转比例）
    pArg2 = pThis_61;
    *(this + 2056) = pThis_61;  // this+8224〔f_2020〕
    *((float *)this + 97) = (double)(int)pThis_61 + *((float *)this + 97);  // this+388〔fAtkCtxVal〕
  }
  if ( *(this + 1639) == 18  // this+6556〔nBigState〕
    && *(this + 154) == -1  // this+616〔nReactionState〕
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    pObj = __RTDynamicCast(
           (int)v5,
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &IRDActiveObject `RTTI Type Descriptor',
           0);
    if ( pObj != 0  // 若 pObj 非 0
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 824))(pObj) != 0  // 调虚槽 +824
      && (unsigned int)sub_4AED20((int)v5) <= 1 )
    {
      nGrabSkillNo = *(this + 2071);  // this+8284〔nGrabSkillNo〕
      if ( nGrabSkillNo == 9 || nGrabSkillNo == 18 )  // 若 fld_e2071 == 9 与/或 fld_e2071 == 18
      {
        HIBYTE(pArg2) = 0;
        if ( nGrabSkillNo == 9 && (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 10) > 0 )  // 调虚槽 +1140
        {
          v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 152))(v5);  // 调虚槽 +152：效果通道 3
          if ( v10 == (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) )  // 调虚槽 +152：效果通道 3
            HIBYTE(pArg2) = 1;
        }
        Block = nullptr;  // Block = 空指针
        v59 = nullptr;  // v59 = 空指针
        pThis_22 = 0;
        v11 = *v5;
        v63 = 0;
        *(float *)&fld_e20712 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(v11 + 48))(v5));  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
        sub_431230((int)&v57, &fld_e20712);  // uint32 vector push_back
        *(float *)&fld_e20712 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 52))(v5));  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        sub_431230((int)&v57, &fld_e20712);  // uint32 vector push_back
        fld_e20712 = *(this + 2071) == 18;  // this+8284〔nGrabSkillNo〕
        sub_431230((int)&v57, &fld_e20712);  // uint32 vector push_back
        pArg2 = HIBYTE(pArg2) != 0;  // pArg2 = 调 HIBYTE
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 19, &v57, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        goto LABEL_22;
      }
      if ( nGrabSkillNo == 49 )  // 若 fld_e2071 == 49
      {
        Block = nullptr;  // Block = 空指针
        v59 = nullptr;  // v59 = 空指针
        pThis_22 = 0;
        v63 = 1;
        pArg2 = 0;
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = 0;
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = 49;
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = 10000;
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 1160))(this, 49, 0);  // 调虚槽 +1160
        pArg2 = sub_47E9D0(v9, v54);  // pArg2 = 调 sub_47E9D0 返回值
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = 0;
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = 3;
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = 0;
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = 1000;
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, int))(*this + 900))(this, 3) * 0.8);  // 调虚槽 +900
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 48))(v5);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        pArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 52))(v5);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 10, &v57, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
LABEL_22:  // 标签 LABEL_22（跳转合流点）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v5 + 596))(v5, 0);  // 调虚槽 +596：[RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActi…
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
        v63 = -1;
        sub_5E5260(&v57);  // 调 动画子对象清理临时缓冲
      }
    }
  }
  if ( *(this + 1639) == 24  // this+6556〔nBigState〕
    && *(this + 2118) == 0  // this+8472〔nFinishFlag〕
    && *(this + 154) == -1  // this+616〔nReactionState〕
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    pObj3 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
            (int)v5,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDActiveObject `RTTI Type Descriptor',
            0);
    if ( pObj3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 824))(pObj3) != 0 )  // 调虚槽 +824
    {
      *(float *)&fld_e20712 = COERCE_FLOAT(sub_4AED20((int)v5));
      v13 = *v5;
      pArg2 = 100;
      v14 = (*(int (/*thiscall*/ **)(uint32_t *, int *, int *))(v13 + 648))(v5, &pArg2, this);  // 调虚槽 +648：写入 100（格挡/减伤基础值槽）
      if ( *(float *)&fld_e20712 == 0.0 && v14 == 0 )  // 若 v14 == 0
      {
        Block = nullptr;  // Block = 空指针
        v59 = nullptr;  // v59 = 空指针
        pThis_22 = 0;
        v63 = 2;
        fld_e20712 = 1;
        sub_431230((int)&v57, &fld_e20712);  // uint32 vector push_back
        *(float *)&fld_e20712 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 48))(v5));  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        sub_431230((int)&v57, &fld_e20712);  // uint32 vector push_back
        *(float *)&fld_e20712 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 52))(v5));  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        sub_431230((int)&v57, &fld_e20712);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 24, &v57, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v5 + 596))(v5, 0);  // 调虚槽 +596：[RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActi…
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
        v63 = -1;
        sub_5E5260(&v57);  // 调 动画子对象清理临时缓冲
      }
    }
  }
  if ( *(this + 1639) == 21 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    Block = nullptr;  // Block = 空指针
    v59 = nullptr;  // v59 = 空指针
    pThis_22 = 0;
    v63 = 3;
    pArg2 = 1;
    sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
    pArg2 = 0;
    sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
    *(float *)&fld_e20712 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 调虚槽 +672：自身 HP
    pArg2 = sub_41A5E0(fld_e20712 + 928);  // crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&fld_e20712 = COERCE_FLOAT(sub_41A5E0(fld_e20712 + 942));  // crypt4byte 解密校验（·0x41A590 逆运算）
    pArg2 = (int)(8 * (uint64_t)((double)pArg2 * *(float *)&fld_e20712)) / 10;
    sub_431230((int)&v57, &pArg2);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 6, &v57, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    v63 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
  }
  if ( *(this + 1639) == 22 )  // this+6556〔nBigState〕
  {
    v15 = *v5;
    pArg2 = 100;
    (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v15 + 648))(v5, &pArg2, this);  // 调虚槽 +648：写入 100（格挡/减伤基础值槽）
    if ( (uint8_t)nArg4 != 0 || pArg2 <= 0 || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v5 + 308))(v5) == 0 )  // 调虚槽 +308：是否本地玩家
    {
      v16 = (int)pArg3;
    }
    else  // 否则分支
    {
      v16 = (int)pArg3;
      v17 = (uint64_t)(pArg3[4] * 0.5 + *pArg3);
      pThis_22 = v17;
      v18 = (*(int (/*fastcall*/ **)(uint32_t *, uint32_t))(*v5 + 124))(v5, HIDWORD(v17));  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v19 = *(float *)(v16 + 20) * 0.5;
      v55 = v18;
      v53 = (uint64_t)(v19 + *(float *)(v16 + 8));
      *(float *)&fld_e20712 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*this + 388))(this));  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
      v20 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 19);  // 调虚槽 +1140
      v21 = *this;
      v56 = v20;
      v22 = (char *)(*(int (/*thiscall*/ **)(int *, int))(v21 + 1160))(this, 19);
      v23 = sub_47EFD0(v22, COERCE_FLOAT(2), v56, fld_e20712, fld_e20712, 0);  // v23 = 调 sub_47EFD0 返回值
      v24 = *this;
      v56 = v23;
      v25 = (*(int (/*thiscall*/ **)(int *))(v24 + 152))(this);  // 调虚槽 +152：效果通道 3
      sub_4E4A50(this, 21009, v56, pThis_22, v55, v53, v25, 0, 0, 0);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    }
    pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
    v59 = v5;
    pThis_22 = pThis_2;
    sub_5E5D70(&v59);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 19);  // 调虚槽 +1160
    sub_47DCD0(this, -1);  // 调 震动/资源档位设置
  }
  else  // 否则分支
  {
    v16 = (int)pArg3;
  }
  if ( *(this + 1639) == 26 && (uint8_t)nArg4 == 0 )  // this+6556〔nBigState〕
  {
    pObj2 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
            (int)v5,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDActiveObject `RTTI Type Descriptor',
            0);
    if ( pObj2 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 308))(pObj2) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      v28 = sub_4AED20((int)v5);  // v28 = 调 sub_4AED20 返回值
      v29 = *v5;
      pArg2 = v28;
      v54 = 100;
      v30 = (*(int (/*thiscall*/ **)(uint32_t *, unsigned int *, int *))(v29 + 648))(v5, &v54, this);  // 调虚槽 +648：写入 100（格挡/减伤基础值槽）
      if ( pArg2 == 0 && v30 == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 688))(pObj2) + 20) != 0 )  // 调虚槽 +688：附加块基址 this+6160
      {
        v31 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 54);  // 调虚槽 +1160
        v32 = *this;
        fld_e20712 = v31;
        pArg2 = (*(int (/*thiscall*/ **)(int *, int))(v32 + 1140))(this, 54);
        v33 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
        v34 = sub_47EFD0((char *)fld_e20712, COERCE_FLOAT(2), pArg2, v33, v33, 0);  // v34 = 调 sub_47EFD0 返回值
        v35 = *this;
        pThis_22 = v34;
        v36 = (*(int (/*thiscall*/ **)(int *))(v35 + 388))(this);  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
        v37 = sub_47EFD0((char *)fld_e20712, COERCE_FLOAT(3), pArg2, v36, v36, 0);  // v37 = 调 sub_47EFD0 返回值
        nChargeTime = sub_423A80(pThis_22, v37, *(this + 2125), dword_9B9348);  // 同上 int 版（FTOL 截断）
        v39 = *(uint32_t *)pObj2;
        v62[0] = nChargeTime;
        pArg2 = *this;
        v40 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t *))(v39 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
                pObj2,  // 续行：对象 pObj2
                0,
                0,
                0,
                0,
                0,
                4,
                0,
                4,
                v62);
        (*(void (/*thiscall*/ **)(int *, int, int))(pArg2 + 580))(this, 48028, v40);  // pArg2+580〔uOffset580(推断)〕
      }
    }
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 54);  // 调虚槽 +1160
    sub_47DCD0(this, -1);  // 调 震动/资源档位设置
    pThis_22 = sub_42FCB0(228);  // CRT 一次性初始化
    v63 = 4;
    if ( pThis_22 != 0 )  // 若 pThis_22 非 0
    {
      if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimPoolCap〕
        LOBYTE(fld_16C) = (uint8_t)this + 108;  // this+108 第 1 组·宿主属性 +886 增量
      else  // 否则分支
        fld_16C = *(this + 91);  // this+364〔pAnimPool〕
      *(float *)&fld_e20712 = COERCE_FLOAT(sub_431920(fld_16C, (char)"Effect/Animation/ShoulderTackleHit.ani", 1));  // 动画件构造（文件名版）
    }
    else  // 否则分支
    {
      *(float *)&fld_e20712 = 0.0;
    }
    v63 = -1;
    v42 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    v43 = (int *)v42;
    pThis_22 = (int)v42;
    v63 = 5;
    if ( v42 != nullptr )  // 若 v42 有效（非空）
    {
      sub_44E0D0(v42, fld_e20712, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *v43 = (int)&CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else  // 否则分支
    {
      v43 = nullptr;  // v43 = 空指针
    }
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    fld_e20712 = (int)v43;
    v63 = -1;
    sub_45FE80(fld_e29, (int)v5, 2, 0, (int)v43, (int)v5, 0);  // 调 实体对象注册到演播层
    pArg2 = *v43;
    v52 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*v5 + 124))(v5, (uint64_t)(pArg3[5] * 0.5 + pArg3[2]));  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    v45 = (uint64_t)(pArg3[3] * 0.5 + *pArg3);
    (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, int))(pArg2 + 112))(v43, HIDWORD(v45), v45, v52);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    v46 = *v43;
    v47 = (*(int (/*thiscall*/ **)(int *, uint32_t *))(*this + 660))(this, v5);  // 调虚槽 +660
    v48 = sub_432E50(v47);  // 关系码对调映射
    (*(void (/*thiscall*/ **)(int, int))(v46 + 148))(fld_e20712, v48);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 9);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 49);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 18);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
    }
    if ( *(this + 2129) >= 1 )  // this+8516〔f_2144〕
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
        this,
        "R_FT_PAM_BREAST",  // 标签 R_FT_PAM_BREAST
        -1,
        0,
        0);
    v16 = (int)pArg3;
    ++*(this + 2129);  // this+8516〔f_2144〕
  }
  pAtkRateObj = *(this + 2114);  // this+8456〔pAtkRateObj〕
  if ( pAtkRateObj != 0  // 若 fld_e2114 非 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pAtkRateObj + 80))(pAtkRateObj) != 0  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    && (*((uint8_t *)this + 404) != 0 || *((float *)this + 97) > 0.0)  // this+388〔fAtkCtxVal〕
    && (uint8_t)nArg4 == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 37);  // 调虚槽 +1160
    sub_47DCD0(this, -1);  // 调 震动/资源档位设置
  }
  return sub_4AFB30(this, v5, v16, nArg4);  // 返回 调 sub_4AFB30 返回值
}


// ------------------------------------------------------------
// ============================================================
// §C Launch 系召唤
// ============================================================
// 0x5ED470 sub_5ED470
// ------------------------------------------------------------
// 调: sub_5ED470 sub_41A5E0 sub_51A7D0
int /*thiscall*/ sub_5ED470(int this, uint32_t *pArg2, void *pArg3)  // 实现：调: sub_5ED470 sub_41A5E0 sub_51A7D0
{
  int result; // eax
  void *pMem; // eax
  int *v8; // eax
  int v9; // edx
  int v10; // edi
  double v11; // st7
  int fld_16C; // ecx
  uint32_t *v13; // ebx
  char *v14; // eax
  char *v15; // edi
  int v16; // edx
  int v17; // ebx
  int pThis_98; // eax
  int v19; // ebx
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  double v23; // st7
  int fld_16C2; // ecx
  uint32_t *v25; // ebx
  char *v26; // eax
  char *v27; // edi
  int v28; // edx
  int v29; // ebx
  int pThis_982; // eax
  int v31; // ebx
  int pThis_802; // eax
  int pThis_7C2; // eax
  int pThis_782; // eax
  int fld_74; // eax
  int v36; // ecx
  unsigned int v37; // ebx
  int fld_742; // ecx
  int v39; // edx
  int v40; // eax
  int pObj; // edi
  int v42; // ebx
  int *v43; // eax
  int v44; // ebx
  int v45; // eax
  uint32_t *v46; // eax
  double v47; // st7
  int fld_2108; // eax
  void *pMem2; // eax
  int *v50; // eax
  int v51; // edx
  int fld_21082; // edi
  uint32_t *v53; // eax
  int v54; // ebx
  int *v55; // eax
  int v56; // edx
  int fld_2110; // edi
  uint32_t *v58; // eax
  int v59; // ebx
  int *pMem3; // eax
  int *pMem32; // edi
  int *pMem322; // ecx
  int v63; // eax
  int fld_20D0; // edi
  uint32_t *v65; // eax
  int v66; // eax
  int fld_20D02; // ecx
  int v68; // ebx
  int *pMem4; // eax
  int *pMem42; // edi
  int *pMem422; // ecx
  int v72; // eax
  uint32_t *v73; // eax
  float v74; // [esp+44h] [ebp-22Ch]
  float v75; // [esp+44h] [ebp-22Ch]
  float v76; // [esp+44h] [ebp-22Ch]
  unsigned int v77; // [esp+48h] [ebp-228h]
  int v78; // [esp+54h] [ebp-21Ch]
  int v79; // [esp+54h] [ebp-21Ch]
  int *v80; // [esp+58h] [ebp-218h]
  void *Blockb; // [esp+5Ch] [ebp-214h]
  void *Blockc; // [esp+5Ch] [ebp-214h]
  void *Block; // [esp+5Ch] [ebp-214h]
  void *Blocka; // [esp+5Ch] [ebp-214h]
  char Buffer[256]; // [esp+60h] [ebp-210h] BYREF
  char v86[256]; // [esp+160h] [ebp-110h] BYREF
  int dword_796E502; // [esp+260h] [ebp-10h]
  int v88; // [esp+26Ch] [ebp-4h]
  int v89; // [esp+278h] [ebp+8h]
  int v90; // [esp+278h] [ebp+8h]
  void *v91; // [esp+278h] [ebp+8h]
  void *v92; // [esp+278h] [ebp+8h]
  float v93; // [esp+278h] [ebp+8h]
  void *v94; // [esp+27Ch] [ebp+Ch]
  void *fld_2104; // [esp+27Ch] [ebp+Ch]
  float v96; // [esp+27Ch] [ebp+Ch]
  float v97; // [esp+27Ch] [ebp+Ch]
  void *v98; // [esp+27Ch] [ebp+Ch]
  float v99; // [esp+27Ch] [ebp+Ch]
  void *v100; // [esp+27Ch] [ebp+Ch]

  dword_796E502 = dword_796E50;  // 帧时刻快照源
  sub_4B4170((float *)this, pArg2, pArg3);  // Buff 图标条装配
  result = sub_41A5E0((unsigned int)(pArg2 + 1));  // crypt4byte 解密校验（·0x41A590 逆运算）
  v94 = (void *)result;
  if ( result == 20 )  // 若 result == 20
  {
    if ( *(uint32_t *)(this + 8452) == 0 )
    {
      pMem = operator new(0x64u);  // new(100 字节) 分配对象
      v88 = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v8 = (int *)sub_51A7D0(pMem);  // v8 = 调 sub_51A7D0 返回值
      else  // 否则分支
        v8 = nullptr;  // v8 = 空指针
      *(uint32_t *)(this + 8452) = v8;
      v9 = *v8;
      v88 = -1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v9 + 64))(v8) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
    }
    fld_2104 = *(void **)(this + 8452);
    v10 = sub_47EF20(0, pArg3, -1, -1, 11);  // v10 = 调 sub_47EF20 返回值
    *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)fld_2104 + 64))(fld_2104) + 40) = v10;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, int, int))(**(uint32_t **)(this + 8452) + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      *(uint32_t *)(this + 8452),
      this,
      this,
      1,
      0,
      3,
      -1);
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
      this,
      "FT_SUPERARMOR",  // 标签 FT_SUPERARMOR
      -1,
      0,
      0);
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "BUFF_SUPERARMOR",  // 标签 BUFF_SUPERARMOR
             -1,
             0,
             0);
  }
  if ( result == 30 || result == 31 || result == 39 || result == 44 )  // 若 result == 30 与/或 result == 31 与/或 result == 39
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
      (*(void (/*thiscall*/ **)(int, int, void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
        this,
        48015,
        v94,
        0,
        0,
        0,
        0,
        0,
        4,
        0,
        0,
        0);
    if ( v94 == (void *)39 )
    {
      v11 = (double)(int)sub_47EF20(2, pArg3, -1, -1, 11);  // 调 读攻击数据表
      result = 0;
      do  // do-while 循环体起点
      {
        v89 = result + 1;
        sprintf(Buffer, "Effect/Animation/AimVitalPoint%d.ani", result + 1);  // 拼字符串（模板 Effect/Animation/AimVitalPoint…）
        Blockb = (void *)sub_42FCB0(228);  // CRT 一次性初始化
        v88 = 1;
        if ( Blockb != nullptr )  // 若 Blockb 有效（非空）
        {
          if ( *(uint32_t *)(this + 384) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
            LOBYTE(fld_16C) = this + 108;
          else  // 否则分支
            fld_16C = *(uint32_t *)(this + 364);  // fld_16C = 读 this+364
          v13 = (uint32_t *)sub_431920(fld_16C, (char)Buffer, 1);  // 动画件构造（文件名版）
        }
        else  // 否则分支
        {
          v13 = nullptr;  // v13 = 空指针
        }
        v88 = -1;
        v96 = v11 * 0.0018867925;
        sub_4922F0(v13, v96);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
        v14 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
        v15 = v14;
        v88 = 2;
        if ( v14 != nullptr )  // 若 v14 有效（非空）
        {
          sub_44E0D0(v14, (int)v13, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
          *(uint32_t *)v15 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
        }
        else  // 否则分支
        {
          v15 = nullptr;  // v15 = 空指针
        }
        v16 = *(uint32_t *)v15;
        v88 = -1;
        *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(v16 + 36))(v15) + 8) = 2;  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/60584…
        sub_45FE80(*(uint32_t *)(this + 116), (int)v15, 2, 0, (int)v15, 0, 0);  // 调 实体对象注册到演播层
        v17 = *(uint32_t *)v15;
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 调虚槽 +152：效果通道 3
        (*(void (/*thiscall*/ **)(char *, int))(v17 + 148))(v15, v18);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
        v19 = *(uint32_t *)v15;
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v20);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v21);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(char *, int))(v19 + 112))(v15, v22);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
        result = v89;
      }
      while ( v89 < 3 );  // 条件循环
      return result;
    }
    if ( v94 == (void *)44 )
    {
      v23 = (double)(int)sub_47EF20(1, a3, -1, -1, 11);  // 调 读攻击数据表
      result = 0;
      do  // do-while 循环体起点
      {
        v90 = result + 1;
        sprintf(v86, "Effect/Animation/Provocation%d.ani", result + 1);  // 拼字符串（模板 Effect/Animation/Provocation%d…）
        Blockc = (void *)sub_42FCB0(228);  // CRT 一次性初始化
        v88 = 3;
        if ( Blockc != nullptr )  // 若 Blockc 有效（非空）
        {
          if ( *(uint32_t *)(this + 384) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
            LOBYTE(v24) = this + 108;
          else  // 否则分支
            v24 = *(uint32_t *)(this + 364);  // v24 = 读 this+364
          v25 = (uint32_t *)sub_431920(v24, (char)v86, 1);  // 动画件构造（文件名版）
        }
        else  // 否则分支
        {
          v25 = nullptr;  // v25 = 空指针
        }
        v88 = -1;
        v97 = v23 * 0.0018867925;
        sub_4922F0(v25, v97);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
        v26 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
        v27 = v26;
        v88 = 4;
        if ( v26 != nullptr )  // 若 v26 有效（非空）
        {
          sub_44E0D0(v26, (int)v25, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
          *(uint32_t *)v27 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
        }
        else  // 否则分支
        {
          v27 = nullptr;  // v27 = 空指针
        }
        v28 = *(uint32_t *)v27;
        v88 = -1;
        *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(v28 + 36))(v27) + 8) = 2;  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/60584…
        sub_45FE80(*(uint32_t *)(this + 116), (int)v27, 2, 0, (int)v27, 0, 0);  // 调 实体对象注册到演播层
        v29 = *(uint32_t *)v27;
        pThis_982 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 调虚槽 +152：效果通道 3
        (*(void (/*thiscall*/ **)(char *, int))(v29 + 148))(v27, pThis_982);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
        v31 = *(uint32_t *)v27;
        pThis_802 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        pThis_7C2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_802);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        pThis_782 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C2);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(char *, int))(v31 + 112))(v27, pThis_782);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
        result = v90;
      }
      while ( v90 < 3 );  // 条件循环
      return result;
    }
    result = (int)v94;
  }
  if ( result == 36 )  // 若 result == 36
  {
    v78 = sub_47EF20(0, pArg3, -1, -1, 11);  // v78 = 调 sub_47EF20 返回值
    Block = (void *)sub_47EF20(1, pArg3, -1, -1, 11);  // Block = 调 sub_47EF20 返回值
    fld_74 = *(uint32_t *)(this + 116);  // fld_74 = 读 this+116
    v36 = *(uint32_t *)(fld_74 + 120);
    result = fld_74 + 116;
    v37 = 0;
    if ( v36 != 0 )  // 若 v36 非 0
    {
      result = (*(uint32_t *)(result + 8) - v36) >> 2;  // 向量元素数 = (end−begin)/4
      v91 = (void *)result;
    }
    else  // 否则分支
    {
      v91 = nullptr;  // v91 = 空指针
    }
    v98 = nullptr;  // v98 = 空指针
    if ( (int)v91 > 0 )
    {
      do  // do-while 循环体起点
      {
        fld_742 = *(uint32_t *)(this + 116);  // fld_742 = 读 this+116
        v39 = *(uint32_t *)(fld_742 + 120);
        if ( v39 != 0 && v37 < (*(uint32_t *)(fld_742 + 124) - v39) >> 2 )  // 若 v39 != 0
          v40 = *(uint32_t *)(v39 + 4 * v37);
        else  // 否则分支
          v40 = 0;
        pObj = __RTDynamicCast(
                v40,
                0,
                &IRDCollisionObject `RTTI Type Descriptor',
                &IRDActiveObject `RTTI Type Descriptor',
                0);
        if ( pObj != 0 )  // 若 pObj 非 0
        {
          v42 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调虚槽 +376：坐标同步包（type 37）
          if ( v42 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 376))(this) )  // 调虚槽 +376：坐标同步包（type 37）
          {
            v88 = 5;
            if ( operator new(0x84u) != nullptr )  // new(132 字节) 分配对象
              v43 = (int *)sub_510350(3, 0, Block, v78, 1, nullptr);  // v43 = 调 sub_510350 返回值
            else  // 否则分支
              v43 = nullptr;  // v43 = 空指针
            v44 = *v43;
            v80 = v43;
            v45 = *(uint32_t *)dword_8F84B8;  // 全局 攻击判定管理器
            v88 = -1;
            v46 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, int, int))(v45 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行…
                              dword_8F84B8,  // 全局 攻击判定管理器
                              "Common/CommonEffect/BuffIcon.img",  // 贴图 Common/CommonEffect/BuffIcon.img
                              11,
                              4,
                              -1);
            v77 = sub_418DD0(v46, v77);  // v77 = 调 sub_418DD0 返回值
            (*(void (/*thiscall*/ **)(int *, int, int, int))(v44 + 56))(v80, pObj, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
              pObj,
              "BUFF_SUNCURTAIN",  // 标签 BUFF_SUNCURTAIN
              -1,
              0,
              0);
          }
          v37 = (unsigned int)v98;
        }
        result = (int)v91;
        v98 = (void *)++v37;
      }
      while ( (int)v37 < (int)v91 );  // 条件循环
    }
  }
  else if ( result == 37 )
  {
    v79 = sub_47EF20(0, pArg3, -1, -1, 11);  // v79 = 调 sub_47EF20 返回值
    Blocka = (void *)sub_47EF20(1, pArg3, -1, -1, 11);  // Blocka = 调 sub_47EF20 返回值
    v92 = (void *)sub_47E9D0(pArg2, 0);  // v92 = 调 sub_47E9D0 返回值
    v47 = (double)sub_47E9D0(pArg2, 1u);  // v47 = 调 sub_47E9D0 返回值
    fld_2108 = *(uint32_t *)(this + 8456);  // this+8456〔pAtkRateObj〕
    *(float *)(this + 8460) = v47 * 0.0099999998;  // this+8460〔f_AtkRate〕
    if ( fld_2108 == 0 )  // 若 fld_2108 为 0
    {
      pMem2 = operator new(0x7Cu);  // new(124 字节) 分配对象
      v88 = 6;
      if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
        v50 = (int *)sub_4B3C90((int)pMem2, 0, 0);  // CNChangeStatus 构造（双参）
      else  // 否则分支
        v50 = nullptr;  // v50 = 空指针
      *(uint32_t *)(this + 8456) = v50;  // this+8456〔pAtkRateObj〕
      v51 = *v50;
      v88 = -1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v51 + 64))(v50) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
    }
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8456) + 124))(*(uint32_t *)(this + 8456));  // this+8456〔pAtkRateObj〕
    v99 = (float)(int)v92;
    v74 = -v99;
    (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(**(uint32_t **)(this + 8456) + 120))(7, 0, LODWORD(v74));  // this+8456〔pAtkRateObj〕
    v75 = (float)(int)Blocka;
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 8456) + 120))(0, 0, LODWORD(v75));  // this+8456〔pAtkRateObj〕
    v76 = v99 * -0.001;
    (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(**(uint32_t **)(this + 8456) + 120))(24, 0, LODWORD(v76));  // this+8456〔pAtkRateObj〕
    *(uint32_t *)(*(uint32_t *)(this + 8456) + 44) = v79;  // this+8456〔pAtkRateObj〕
    fld_21082 = **(uint32_t **)(this + 8456);  // this+8456〔pAtkRateObj〕
    v53 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, int, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
                      dword_8F84B8,  // 全局 攻击判定管理器
                      "Common/CommonEffect/BuffIcon.img",  // 贴图 Common/CommonEffect/BuffIcon.img
                      6,
                      5,
                      -1);
    sub_418DD0(v53, v77);  // 调 资源句柄 (101)
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(fld_21082 + 56))(*(uint32_t *)(this + 8456), this, this, 1);  // this+8456〔pAtkRateObj〕
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "BUFF_POWERFIST",  // 标签 BUFF_POWERFIST
             -1,
             0,
             0);
  }
  else if ( result == 38 )
  {
    v100 = (void *)sub_47EF20(0, pArg3, -1, -1, 11);  // v100 = 调 sub_47EF20 返回值
    v93 = (double)(int)sub_47EF20(1, pArg3, -1, -1, 11) * 0.1;  // 调 读攻击数据表
    v54 = sub_47EF20(2, pArg3, -1, -1, 11);  // v54 = 调 sub_47EF20 返回值
    if ( *(uint32_t *)(this + 8464) == 0 )
    {
      v88 = 7;
      if ( operator new(0x78u) != nullptr )  // new(120 字节) 分配对象
        v55 = (int *)sub_5E5C10(2, v93, v54, 1, (int)v100, 1);  // v55 = 调 sub_5E5C10 返回值
      else  // 否则分支
        v55 = nullptr;  // v55 = 空指针
      *(uint32_t *)(this + 8464) = v55;
      v56 = *v55;
      v88 = -1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v56 + 64))(v55) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
    }
    (*(void (/*fastcall*/ **)(uint32_t, uint32_t, int, uint32_t, int, int, void *, int))(**(uint32_t **)(this + 8464) + 120))(  // 调虚槽 +120：动画对象
      *(uint32_t *)(this + 8464),
      (uint64_t)v93 >> 32,
      2,
      (uint64_t)v93,
      v54,
      1,
      v100,
      1);
    fld_2110 = **(uint32_t **)(this + 8464);
    v58 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
                      dword_8F84B8,  // 全局 攻击判定管理器
                      "Common/CommonEffect/BuffIcon.img",  // 贴图 Common/CommonEffect/BuffIcon.img
                      8,
                      0,
                      -1);
    sub_418DD0(v58, v77);  // 调 资源句柄 (101)
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(fld_2110 + 56))(*(uint32_t *)(this + 8464), this, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "BUFF_POISON_SPREAD",  // 标签 BUFF_POISON_SPREAD
             -1,
             0,
             0);
  }
  else  // 否则分支
  {
    if ( result == 43 )  // 若 result == 43
    {
      v59 = sub_47EF20(0, pArg3, -1, -1, 11);  // v59 = 调 sub_47EF20 返回值
      if ( *(uint32_t *)(this + 8400) == 0 )  // this+8400〔pAppendage〕
      {
        pMem3 = (int *)operator new(0x50u);  // new(80 字节) 分配对象
        pMem32 = pMem3;
        v88 = 8;
        if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
        {
          *pMem3 = (int)&IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
          sub_4B0D60((uint8_t *)v60 + 4);  // 计时子对象初始化（时钟域 2）
          LOBYTE(v88) = 9;
          sub_5F6610(v61);
          sub_5F6750(v61);
          v62 = v61;
        }
        else  // 否则分支
        {
          v62 = nullptr;  // v62 = 空指针
        }
        *(uint32_t *)(this + 8400) = v62;  // this+8400〔pAppendage〕
        v63 = *v62;
        v88 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v63 + 64))(v62) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      }
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8400) + 64))(*(uint32_t *)(this + 8400)) + 40) = v59;  // this+8400〔pAppendage〕
      v64 = **(uint32_t **)(this + 8400);  // this+8400〔pAppendage〕
      v65 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      v66 = sub_418DD0(v65, (unsigned int)"Common/CommonEffect/BuffIcon.img");  // v66 = 调 sub_418DD0 返回值
      v67 = *(uint32_t *)(this + 8400);  // this+8400〔pAppendage〕
    }
    else  // 否则分支
    {
      if ( result != 50 )  // 若 result != 50
        return result;
      v68 = sub_47EF20(0, a3, -1, -1, 11);  // v68 = 调 sub_47EF20 返回值
      if ( *(uint32_t *)(this + 8468) == 0 )  // this+8468〔pSkillObj〕
      {
        v69 = (int *)operator new(0x50u);  // new(80 字节) 分配对象
        v70 = v69;
        v88 = 10;
        if ( v69 != nullptr )  // 若 v69 有效（非空）
        {
          *v69 = (int)&IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
          sub_4B0D60((uint8_t *)pMem4 + 4);  // 计时子对象初始化（时钟域 2）
          LOBYTE(v88) = 11;
          sub_5F6610(pMem42);
          sub_5F6750(pMem42);
          pMem422 = pMem42;
        }
        else  // 否则分支
        {
          pMem422 = nullptr;  // pMem422 = 空指针
        }
        *(uint32_t *)(this + 8468) = pMem422;  // this+8468〔pSkillObj〕
        v72 = *pMem422;
        v88 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v72 + 64))(pMem422) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      }
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8468) + 64))(*(uint32_t *)(this + 8468)) + 40) = v68;  // this+8468〔pSkillObj〕
      fld_20D0 = **(uint32_t **)(this + 8468);  // this+8468〔pSkillObj〕
      v73 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      v66 = sub_418DD0(v73, (unsigned int)"Common/CommonEffect/BuffIcon.img");  // v66 = 调 sub_418DD0 返回值
      fld_20D02 = *(uint32_t *)(this + 8468);  // this+8468〔pSkillObj〕
    }
    return (*(int (/*thiscall*/ **)(int, int, int, int, int))(fld_20D0 + 56))(fld_20D02, this, this, 1, v66);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
  }
  return result;
}


// ------------------------------------------------------------
// 0x5EDDC0 sub_5EDDC0
// ------------------------------------------------------------
// 调: sub_5EDDC0
int /*thiscall*/ sub_5EDDC0(int this)  // 实现：调: sub_5EDDC0
{
  *(uint32_t *)(this + 8264) = 100;  // this+8264〔nPhaseB(推断)〕
  *(uint32_t *)(this + 8216) = -1;  // this+8216〔nAtkActionType〕
  *(uint8_t *)(this + 8220) = 0;  // this+8220〔nGrabTargetSel(推断)〕
  *(uint32_t *)(this + 8224) = -1;  // this+8224〔f_2020〕
  *(uint32_t *)(this + 8228) = 0;  // this+8228〔bGrabFlag(推断)〕
  *(uint32_t *)(this + 8232) = 0;  // this+8232〔nGrabTable〕
  *(uint32_t *)(this + 8236) = 0;  // this+8236〔nReflectCnt〕
  *(uint32_t *)(this + 8240) = 0;  // this+8240〔nParamCnt〕
  *(uint32_t *)(this + 8244) = 0;  // this+8244〔nVariantSel〕
  *(uint32_t *)(this + 8248) = 0;  // this+8248〔nVariantVal〕
  *(uint32_t *)(this + 8252) = 0;  // this+8252〔nParam2〕
  *(uint8_t *)(this + 8256) = 0;  // this+8256〔nParam3〕
  *(uint32_t *)(this + 8260) = 0;  // this+8260〔nPhaseA〕
  *(uint8_t *)(this + 8268) = 0;  // this+8268〔nParamArr(推断)〕
  *(uint32_t *)(this + 8272) = 0;  // this+8272〔pAnimPool2〕
  *(uint8_t *)(this + 8276) = 0;  // this+8276〔f_2054〕
  *(uint32_t *)(this + 8280) = 0;  // this+8280〔pStatusObj〕
  *(uint8_t *)(this + 8284) = 0;  // this+8284〔nGrabSkillNo〕
  *(uint32_t *)(this + 8288) = 0;  // this+8288〔nGrabDataVal(推断)〕
  *(uint32_t *)(this + 8296) = 0;  // this+8296〔nOffsetVal(推断)〕
  *(uint32_t *)(this + 8292) = 0;  // this+8292〔bModeFlag(推断)〕
  *(uint32_t *)(this + 8300) = 0;  // this+8300〔pHoldObj(推断)〕
  *(uint8_t *)(this + 8304) = 0;  // this+8304〔nHoldPosX(推断)〕
  *(uint8_t *)(this + 8305) = 0;  // this+8305〔bImmune8305〕
  *(uint32_t *)(this + 8308) = 0;  // this+8308〔nHoldPosY(推断)〕
  *(uint32_t *)(this + 8312) = 0;  // this+8312〔nHoldPosZ(推断)〕
  *(uint32_t *)(this + 8316) = 0;  // this+8316〔nHoldSrc(推断)〕
  *(uint32_t *)(this + 8320) = 0;  // this+8320〔pHoldHost(推断)〕
  *(uint32_t *)(this + 8324) = 0;  // this+8324〔bHoldMode(推断)〕
  *(uint32_t *)(this + 8328) = 0;  // this+8328〔f_2088〕
  *(uint8_t *)(this + 8332) = 0;  // this+8332〔f_208C〕
  *(uint8_t *)(this + 8333) = 0;  // this+8333〔f_208D〕
  *(uint32_t *)(this + 8336) = 0;  // this+8336〔pVtStack〕
  *(uint32_t *)(this + 8340) = 0;  // this+8340〔pAnimA(推断)〕
  *(uint8_t *)(this + 8344) = 0;  // this+8344〔nRideMode(推断)〕
  *(uint32_t *)(this + 8348) = 0;  // this+8348〔nPhaseParity(推断)〕
  *(uint32_t *)(this + 8352) = 0;  // this+8352〔nRideHost8352〕
  *(uint32_t *)(this + 8356) = 0;  // this+8356〔uPick8356(推断)〕
  *(uint32_t *)(this + 8360) = 0;  // this+8360〔pPickInfo8360(推断)〕
  *(uint32_t *)(this + 8364) = 0;  // this+8364〔pFrameObject(推断)〕
  *(uint32_t *)(this + 8368) = 0;  // this+8368〔nCoordB〕
  *(uint32_t *)(this + 8372) = 0;  // this+8372〔nDiffVal(推断)〕
  *(uint32_t *)(this + 8376) = 0;  // this+8376〔pFxObjB(推断)〕
  *(uint32_t *)(this + 8380) = 0;  // this+8380〔pAnimC〕
  *(uint32_t *)(this + 8388) = 0;  // this+8388〔pAnimD〕
  *(uint32_t *)(this + 8384) = 0;  // this+8384〔f_20C0〕
  *(uint32_t *)(this + 8392) = 0;  // this+8392〔f_20C8〕
  *(uint32_t *)(this + 8396) = 0;  // this+8396〔nNameLookup(推断)〕
  *(uint32_t *)(this + 8400) = 0;  // this+8400〔pAppendage〕
  *(uint32_t *)(this + 8404) = 0;  // this+8404〔pFxObjD(推断)〕
  *(uint32_t *)(this + 8408) = 0;  // this+8408〔pRoplingObj〕
  *(uint8_t *)(this + 8412) = 0;  // this+8412〔pAnimE(推断)〕
  *(uint8_t *)(this + 8413) = 0;
  *(uint32_t *)(this + 8416) = 0;
  *(uint32_t *)(this + 8420) = 0;  // this+8420〔pVecBegin〕
  *(uint32_t *)(this + 8424) = 0;  // this+8424〔pVecEnd〕
  *(uint32_t *)(this + 8428) = 0;  // this+8428〔pVecCap(推断)〕
  *(uint32_t *)(this + 8432) = 0;  // this+8432〔pBuffObjA(推断)〕
  *(uint32_t *)(this + 8436) = 0;  // this+8436〔pBuffObjB(推断)〕
  *(uint8_t *)(this + 8440) = 0;
  *(uint8_t *)(this + 8441) = 0;  // this+8441〔bGhostStepFlag2〕
  *(uint32_t *)(this + 8444) = 0;  // this+8444〔nSkillGate(推断)〕
  *(uint32_t *)(this + 8448) = 0;  // this+8448〔nFinishVal〕
  *(uint32_t *)(this + 8452) = -1;
  *(uint32_t *)(this + 8456) = 0;  // this+8456〔pAtkRateObj〕
  *(uint32_t *)(this + 8460) = 0;  // this+8460〔f_AtkRate〕
  *(uint32_t *)(this + 8464) = 0;
  *(uint32_t *)(this + 8468) = 0;  // this+8468〔pSkillObj〕
  *(uint32_t *)(this + 8472) = 0;  // this+8472〔nFinishFlag(推断)〕
  *(uint32_t *)(this + 8476) = 0;  // this+8476〔bFinishFlag(推断)〕
  *(uint32_t *)(this + 8480) = 0;  // this+8480〔pAtkObj〕
  *(uint32_t *)(this + 8484) = 0;
  *(uint32_t *)(this + 8488) = 0;
  *(uint32_t *)(this + 8492) = 0;
  *(uint8_t *)(this + 8496) = 0;  // this+8496〔nChargeState〕
  *(uint32_t *)(this + 8500) = 0;  // this+8500〔nChargeTime〕
  *(uint32_t *)(this + 8504) = 0;  // this+8504〔f_2138〕
  *(uint32_t *)(this + 8508) = 0;
  *(uint32_t *)(this + 8512) = 0;  // this+8512〔pAnimF(推断)〕
  *(uint8_t *)(this + 8516) = 0;
  *(uint32_t *)(this + 8520) = 0;  // this+8520〔bUseCtx(推断)〕
  *(uint32_t *)(this + 8524) = 0;  // this+8524〔bMonCfgFlag〕
  *(uint32_t *)(this + 8528) = 0;
  *(uint32_t *)(this + 8532) = 0;  // this+8532〔nPhaseValB〕
  *(uint32_t *)(this + 8536) = 0;
  *(uint32_t *)(this + 8540) = 0;  // this+8540〔nPhaseStamp〕
  *(uint32_t *)(this + 8544) = 0;  // this+8544〔nFxCtx〕
  *(uint32_t *)(this + 8548) = 0;  // this+8548〔nPhaseEndB〕
  *(uint32_t *)(this + 8552) = 0;
  *(uint32_t *)(this + 8556) = 0;  // 字段 this+8556〔时钟设随机倒计时、sub_4DE5〕
  return 0;
}



// ------------------------------------------------------------
// 0x5EDFF0 CNSwordman__vmt3FC
// ------------------------------------------------------------
// 证: 叶子函数（9 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt3FC(int this)  // 实现：证: 叶子函数（9 行，无外调无字符串）
{
  IRDCharacter__vmt3FC();
  *(uint8_t *)(this + 8440) = 0;  // this+8440〔bGhostStepFlag〕
  *(uint8_t *)(this + 8441) = 0;  // this+8441〔bGhostStepFlag2〕
  *(uint32_t *)(this + 8520) = 0;  // this+8520〔pBuffCtx8520〕
  return 0;
}



// ------------------------------------------------------------
// 0x5EE010 CNSwordman__vmt204
// ------------------------------------------------------------
// 证: 叶子函数（9 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt204(int this, int nArg2, int nArg3, int nArg4)  // 实现：证: 叶子函数（9 行，无外调无字符串）
{
  *(uint32_t *)(this + 8264) = 100;  // this+8264〔nAbsorbCap〕
  *(uint8_t *)(this + 8268) = 0;  // this+8268〔bAbsorbOn〕
  *(uint8_t *)(this + 8305) = 0;  // this+8305〔bImmune8305〕
  *(uint8_t *)(this + 8412) = 0;  // this+8412〔bImmune8412〕
  return IRDCharacter__vmt204(nArg2, nArg3, nArg4);  // 返回 调 IRDCharacter__vmt204
}



// ------------------------------------------------------------
// 0x5EE040 CNSwordman__vmt388
// ------------------------------------------------------------
// 证: "SWD_REFLECT"
// 调: sub_699000 sub_47EFD0 sub_47E440
char /*thiscall*/ CNSwordman__vmt388(int this, int nArg2, int nArg3)  // 实现：调: sub_699000 sub_47EFD0 sub_47E440
{
  char result; // al
  int (/*thiscall*/ **v5)(int); // edx
  int v6; // edi
  int pThis_474; // ebx
  char *pThis_488; // eax
  int nReflectCnt; // edx  | +0x202C → 反射/连击计数（CNSwordman；va=005EE040）
  unsigned int *pThis_4882; // eax
  int pStealObj; // ecx  | +0x20FC → Buff 表现对象·夺取（CNSwordman；va=005F07A0）

  result = (uint8_t)IRDCharacter__vmt388((uint8_t **)this, nArg2, nArg3);
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               this,
               "SWD_REFLECT",  // 标签 SWD_REFLECT
               -1,
               0,
               0);
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);  // 调虚槽 +352：命中列表双链表清空
      *(uint32_t *)(this + 8228) = sub_699000(this + 6560);  // clock_now(clk)
      if ( *(uint32_t *)(this + 8236) == 0 )  // this+8236〔nReflectCnt〕
      {
        v5 = *(int (/*thiscall*/ ***)(int))this;
        *(uint32_t *)(this + 396) = 0;  // this+396〔uReflectCtx〕
        v6 = v5[97](this);
        pThis_474 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 11);  // 调虚槽 +1140
        pThis_488 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 11);  // 调虚槽 +1160
        *(float *)(this + 388) = (float)sub_47EFD0(pThis_488, 0.0, pThis_474, v6, v6, 0);  // this+388〔fAtkCtxVal〕
      }
      nReflectCnt = *(uint32_t *)(this + 8236) + 1;  // this+8236〔nReflectCnt〕
      *(uint32_t *)(this + 8236) = nReflectCnt;  // this+8236〔nReflectCnt〕
      result = nReflectCnt;
      if ( nReflectCnt == dword_7959FC )  // 若 fld_202C == dword_7959FC
        *(uint32_t *)(this + 448) = 2;  // this+448〔uReflectStage〕
      if ( dword_8F7C04 == this )  // 本地玩家对象
      {
        pThis_4882 = (unsigned int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 11);  // 调虚槽 +1160
        return sub_47E440(pThis_4882, 0);  // 返回 调 sub_47E440 返回值
      }
      break;  // 跳出循环/分支
    case 52:  // case 52 = ENUM_CMDPACKET_DECREASE_DURABILITY
      pStealObj = *(uint32_t *)(this + 8444);  // this+8444〔pStealObj〕
      if ( pStealObj != 0 )  // 若 fld_20FC 非 0
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pStealObj + 80))(pStealObj);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        if ( result != 0 )  // 若结果非 0（成功）
          return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8444) + 76))(*(uint32_t *)(this + 8444), 0);  // this+8444〔pStealObj〕
      }
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EE170 CNSwordman__vmt288
// ------------------------------------------------------------
// 证: 叶子函数（25 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt288(int this, int *pDwArg2, int nArg3)  // 实现：证: 叶子函数（25 行，无外调无字符串）
{
  int result; // eax
  int fld_20482; // eax
  int nAbsorbCap; // esi  | +0x2048 → 伤害吸收上限（CNSwordman；va=005EE170）

  result = IRDCharacter__vmt288(pDwArg2, nArg3);  // result = 调 IRDCharacter__vmt288
  if ( result != 3 )  // 若 result != 3
  {
    if ( *(uint8_t *)(this + 8268) != 0 )  // this+8268〔bAbsorbOn〕
    {
      fld_20482 = *pDwArg2;
      nAbsorbCap = *(uint32_t *)(this + 8264);  // this+8264〔nAbsorbCap〕
      if ( *pDwArg2 >= nAbsorbCap )
        fld_20482 = nAbsorbCap;
      *pDwArg2 = fld_20482;
      return 2;
    }
    else if ( *(uint8_t *)(this + 8305) != 0 || *(uint32_t *)(this + 616) == 17 || *(uint8_t *)(this + 8412) != 0 )  // this+8305〔bImmune8305〕
    {
      return 1;  // 返回 1(成功)
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EE1E0 CNSwordman__vmt530
// ------------------------------------------------------------
// 调: sub_47E440
char /*userpurge*/ CNSwordman__vmt530@<al>(uint8_t *pArg1@<ecx>, uint8_t uArg2@<bl>, char pszArg3)  // 实现：调: sub_47E440
{
  char result; // al
  char pszArg32; // bl
  int v6; // eax
  unsigned int *v7; // eax
  bool v8; // al
  unsigned int *v9; // eax
  bool v10; // al
  unsigned int *v11; // eax
  bool v12; // al
  unsigned int *v13; // eax
  bool v14; // al
  unsigned int *v15; // eax
  bool v16; // al
  unsigned int *v17; // eax
  unsigned int *v18; // eax
  bool v19; // al
  unsigned int *v20; // eax
  uint8_t v22; // [esp-4h] [ebp-8h]
  uint8_t v23; // [esp-4h] [ebp-8h]
  uint8_t v24; // [esp-4h] [ebp-8h]
  uint8_t v25; // [esp-4h] [ebp-8h]
  uint8_t v26; // [esp-4h] [ebp-8h]
  uint8_t v27; // [esp-4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( pArg1[7730] != 0 )
    {
      pszArg32 = pszArg3;
    }
    else  // 否则分支
    {
      pszArg32 = 0;
      pszArg3 = 0;
    }
    v6 = IRDCharacter__vmt530(pszArg3);  // v6 = 调 IRDCharacter__vmt530
    LOBYTE(v6) = pszArg32 != 0 && (v6 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 10)) > 0;  // 调虚槽 +1140
    v7 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 20, v6);  // 调虚槽 +1160
    sub_47E440(v7, uArg2);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
    v8 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 10) > 0;  // 调虚槽 +1140
    v22 = v8;
    v9 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 22);  // 调虚槽 +1160
    sub_47E440(v9, v22);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
    v10 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 10) > 0;  // 调虚槽 +1140
    v23 = v10;
    v11 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 21);  // 调虚槽 +1160
    sub_47E440(v11, v23);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
    v12 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 26) > 0;  // 调虚槽 +1140
    v24 = v12;
    v13 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 8);  // 调虚槽 +1160
    sub_47E440(v13, v24);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
    v14 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 28) > 0;  // 调虚槽 +1140
    v25 = v14;
    v15 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 5);  // 调虚槽 +1160
    sub_47E440(v15, v25);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
    v16 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 45) > 0;  // 调虚槽 +1140
    v26 = v16;
    v17 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 1);  // 调虚槽 +1160
    sub_47E440(v17, v26);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
    if ( pszArg32 != 0 )  // 若 pszArg32 非 0
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 48);  // 调虚槽 +1140
    v18 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 1160))(pArg1);  // 调虚槽 +1160
    sub_47E440(v18, 0x2Eu);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
    v19 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 54) > 0;  // 调虚槽 +1140
    v27 = v19;
    v20 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 31);  // 调虚槽 +1160
    return sub_47E440(v20, v27);  // 返回 调 sub_47E440 返回值
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EE390 CNSwordman__vmt524
// ------------------------------------------------------------
// 调: sub_47E440
char /*thiscall*/ sub_5EE390(uint8_t *this)  // 【CNSwordman__vmt524】
{
  int pThis_667; // eax

  LOBYTE(pThis_667) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)pThis_667 == 0 )
    return pThis_667;
  sub_4AFEC0(this);  // 【推断】★★ 全局 UI/表现标志同步器（仅当 this == dword_8F7C04
  LOBYTE(pThis_667) = *(this + 7730);
  if ( (uint8_t)pThis_667 == 0 )
    return pThis_667;
  pThis_667 = *((uint32_t *)this + 1639);  // this+6556〔大状态ID〕
  switch ( pThis_667 )  // 按 pThis_667 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
LABEL_6:  // 标签 LABEL_6（跳转合流点）
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 1);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 5);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 8);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 9);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 20);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 21);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 22);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 23);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 24);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 25);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 30);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 36);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 38);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 40);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 18);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 41);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 44);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 46);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 31);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 32);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 50);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 52);  // 调虚槽 +1160
      LOBYTE(pThis_667) = sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      return pThis_667;
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      if ( *((uint32_t *)this + 1723) != 1 )  // this+6892〔nSkillCtxVal〕
        return pThis_667;
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 16);  // 调虚槽 +1160
      sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      if ( *((int *)this + 1724) > 0 )  // this+6896〔nTickCount〕
      {
        if ( *(this + 6988) != 0 )
        {
LABEL_13:  // 标签 LABEL_13（跳转合流点）
          (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 49);  // 调虚槽 +1160
          LOBYTE(pThis_667) = sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
          return pThis_667;
        }
        (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 17);  // 调虚槽 +1160
        sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
      }
      LOBYTE(pThis_667) = *(this + 6988);
      if ( (uint8_t)pThis_667 == 0 )
        return pThis_667;
      goto LABEL_13;
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      goto LABEL_6;
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  return pThis_667;
}


// ------------------------------------------------------------
// 0x5EE610 CNSwordman__vmt490
// ------------------------------------------------------------
// 调: sub_47EF20
int /*thiscall*/ CNSwordman__vmt490(void *this, int nArg2, uint32_t *uArg3)  // 实现：调: sub_47EF20
{
  int64_t v4; // rax
  uint32_t *pThis_488; // eax
  int pThis_474; // [esp-10h] [ebp-14h]

  LODWORD(v4) = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1140))(this, 37);  // 调虚槽 +1140
  if ( (int)v4 > 0 )
  {
    LODWORD(v4) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 20))(nArg2, 2);  // 调虚槽 +20：CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认…
    if ( (uint8_t)v4 != 0 )
    {
      LODWORD(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 172))(nArg2);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
      if ( *(uint32_t *)v4 == 8 )
      {
        pThis_474 = (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1140))(this, 37, -1);  // 调虚槽 +1140
        pThis_488 = (uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1160))(this);  // 调虚槽 +1160
        v4 = 1374389535LL * sub_47EF20(pThis_488, 0x25u, 0, pThis_474, -1, 11) * *uArg3;  // 调 读攻击数据表
        *uArg3 = (SHIDWORD(v4) >> 5) + (HIDWORD(v4) >> 31);
      }
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x5EE690 CNSwordman__vmt454
// ------------------------------------------------------------
// 证: 叶子函数（11 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt454(uint32_t *this)  // 实现：证: 叶子函数（11 行，无外调无字符串）
{
  int pBuffOverdriveObj; // eax  | +0x20EC → Buff 表现对象·过载（CNSwordman；va=005F07A0）
  int pBuffCtx8520; // edi  | +0x2148 → Buff 上下文槽（CNSwordman；va=005F07A0）

  pBuffOverdriveObj = *(this + 2107);  // this+8428〔pBuffOverdriveObj〕
  pBuffCtx8520 = dword_9A0308;
  if ( pBuffOverdriveObj != 0 && (*(uint8_t (**)(void))(*(uint32_t *)pBuffOverdriveObj + 80))() != 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    pBuffCtx8520 = pBuffCtx8520 * *(this + 2130) / 100;  // this+8520〔pBuffCtx8520〕
  return pBuffCtx8520 * (100 - *(this + 2131)) / 100;  // this+8524〔bMonCfgFlag〕
}



// ------------------------------------------------------------
// 0x5EE6F0 CNSwordman__vmt12C
// ------------------------------------------------------------
// 证: 叶子函数（18 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt12C(uint32_t *this, uint32_t *uArg2)  // 实现：证: 叶子函数（18 行，无外调无字符串）
{
  int result; // eax

  result = IRDCharacter__vmt12C(uArg2);  // result = 调 IRDCharacter__vmt12C
  if ( (uint32_t *)*(this + 2114) == uArg2 )  // this+8456〔pAtkRateObj〕
    *(this + 2114) = 0;  // this+8456〔pAtkRateObj〕
  if ( uArg2 == this )  // 若 uArg2 == this
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);  // 调虚槽 +216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 12);  // 调虚槽 +216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 16);  // 调虚槽 +216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 13);  // 调虚槽 +216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 14);  // 调虚槽 +216：音效 TAG 查询
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 15);  // 调虚槽 +216：音效 TAG 查询
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EE770 sub_5EE770
// ------------------------------------------------------------
// 调: sub_5EE770 sub_4B1030 sub_650800
uint32_t */*thiscall*/ sub_5EE770(uint32_t *this)  // 实现：调: sub_5EE770 sub_4B1030 sub_650800
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNPinchPowerUp;  // 构造装配 vftable：CNPinchPowerUp
  sub_650800(this);  // 与 ·sub_6500E0 同构（差异：+84 亦清零）
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x5EE7C0 CNPinchPowerUp__vmt0
// ------------------------------------------------------------
// 调: sub_5EE7F0
void */*thiscall*/ CNPinchPowerUp__vmt0(void *Block, char pszArg2)  // 实现：调: sub_5EE7F0
{
  sub_5EE7F0();
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5EE7F0 sub_5EE7F0
// ------------------------------------------------------------
// 调: sub_5EE7F0 sub_5F6640
int /*thiscall*/ sub_5EE7F0(uint32_t *this)  // 实现：调: sub_5EE7F0 sub_5F6640
{
  int result; // eax

  *this = &vftbl_CNPinchPowerUp;  // 构造装配 vftable：CNPinchPowerUp
  nullsub_3();
  *this = &vftbl_IRDAppendage;  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // result = 调 sub_5F6640 返回值
  *(this + 2) = &vftbl_nengine__IObject;  // 构造装配 vftable：nengine__IObject
  *((uint8_t *)this + 12) = 0;  // this[12] = 0
  return result;
}



// ------------------------------------------------------------
// 0x5EE850 sub_5EE850
// ------------------------------------------------------------
// 调: sub_5EE850 sub_4B1030 sub_6509D0
uint32_t */*thiscall*/ sub_5EE850(uint32_t *this)  // 实现：调: sub_5EE850 sub_4B1030 sub_6509D0
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNReckless;  // 构造装配 vftable：CNReckless
  sub_6509D0(this);  // 与 ·sub_6500E0 同构（差异：+80..+108 八字段全清）
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x5EE8A0 CNReckless__vmt0
// ------------------------------------------------------------
// 调: sub_5EE8D0
void */*thiscall*/ CNReckless__vmt0(void *Block, char pszArg2)  // 实现：调: sub_5EE8D0
{
  sub_5EE8D0();
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5EE8D0 sub_5EE8D0
// ------------------------------------------------------------
// 调: sub_5EE8D0 sub_6509F0 sub_5F6640
int /*thiscall*/ sub_5EE8D0(uint32_t *this)  // 实现：调: sub_5EE8D0 sub_6509F0 sub_5F6640
{
  int result; // eax

  *this = &vftbl_CNReckless;  // 构造装配 vftable：CNReckless
  sub_6509F0();  // 释放 +108 挂接件（虚表首槽删除）
  *this = &vftbl_IRDAppendage;  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // result = 调 sub_5F6640 返回值
  *(this + 2) = &vftbl_nengine__IObject;  // 构造装配 vftable：nengine__IObject
  *((uint8_t *)this + 12) = 0;  // this[12] = 0
  return result;
}



// ------------------------------------------------------------
// 0x5EE930 sub_5EE930
// ------------------------------------------------------------
// 调: sub_5EE930 sub_4B1030 sub_650D20 sub_650D30
uint32_t */*thiscall*/ sub_5EE930(uint32_t *this, int nArg2)  // 实现：调: sub_5EE930 sub_4B1030 sub_650D20 sub_650D30
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNGrabbedBlastBlood;  // 构造装配 vftable：CNGrabbedBlastBlood
  sub_650D20(this);  // 与 ·sub_650800 同构（差异：仅 +80..+92）
  sub_650D30(nArg2);  // 参数化设置（+80 状态码）
  return this;
}



// ------------------------------------------------------------
// 0x5EE990 CNGrabbedBlastBlood__vmt0
// ------------------------------------------------------------
// 调: sub_5EE9C0
void */*thiscall*/ CNGrabbedBlastBlood__vmt0(void *Block, char pszArg2)  // 实现：调: sub_5EE9C0
{
  sub_5EE9C0();
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5EE9C0 sub_5EE9C0
// ------------------------------------------------------------
// 调: sub_5EE9C0 sub_5F6640
int /*thiscall*/ sub_5EE9C0(uint32_t *this)  // 实现：调: sub_5EE9C0 sub_5F6640
{
  int result; // eax

  *this = &vftbl_CNGrabbedBlastBlood;  // 构造装配 vftable：CNGrabbedBlastBlood
  nullsub_3();
  *this = &vftbl_IRDAppendage;  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // result = 调 sub_5F6640 返回值
  *(this + 2) = &vftbl_nengine__IObject;  // 构造装配 vftable：nengine__IObject
  *((uint8_t *)this + 12) = 0;  // this[12] = 0
  return result;
}



// ------------------------------------------------------------
// 0x5EEA20 sub_5EEA20
// ------------------------------------------------------------
// 调: sub_5EEA20 sub_47E720 sub_47E9D0
int sub_5EEA20()  // 实现：调: sub_5EEA20 sub_47E720 sub_47E9D0
{
  uint32_t *v0; // eax
  uint32_t *v1; // eax
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  int result; // eax

  v0 = (uint32_t *)sub_47E720(0, 6u);  // v0 = 调 sub_47E720 返回值
  dword_7959F8 = sub_47E9D0(v0, 1u);  // dword_7959F8 = 调 sub_47E9D0 返回值
  v1 = (uint32_t *)sub_47E720(0, 0x17u);  // v1 = 调 sub_47E720 返回值
  flt_9B934C = (double)sub_47E9D0(v1, 0) * 0.0099999998;  // flt_9B934C = 调 sub_47E9D0 返回值
  v2 = (uint32_t *)sub_47E720(0, 0xBu);  // v2 = 调 sub_47E720 返回值
  dword_7959FC = sub_47E9D0(v2, 1u);  // dword_7959FC = 调 sub_47E9D0 返回值
  v3 = (uint32_t *)sub_47E720(0, 0x10u);  // v3 = 调 sub_47E720 返回值
  dword_795A00 = sub_47E9D0(v3, 0);  // dword_795A00 = 调 sub_47E9D0 返回值
  v4 = (uint32_t *)sub_47E720(0, 0x10u);  // v4 = 调 sub_47E720 返回值
  flt_9B9350 = (double)sub_47E9D0(v4, 1u) * 0.0099999998;  // flt_9B9350 = 调 sub_47E9D0 返回值
  v5 = (uint32_t *)sub_47E720(0, 0x10u);  // v5 = 调 sub_47E720 返回值
  dword_795A04 = sub_47E9D0(v5, 2u);  // dword_795A04 = 调 sub_47E9D0 返回值
  v6 = (uint32_t *)sub_47E720(0, 0x22u);  // v6 = 调 sub_47E720 返回值
  dword_795A08 = sub_47E9D0(v6, 0);  // dword_795A08 = 调 sub_47E9D0 返回值
  v7 = (uint32_t *)sub_47E720(0, 0x33u);  // v7 = 调 sub_47E720 返回值
  result = sub_47E9D0(v7, 0);  // result = 调 sub_47E9D0 返回值
  dword_795A0C = result;
  return result;
}



// ------------------------------------------------------------
// 0x5EEB20 CNSwordman__vmt480
// ------------------------------------------------------------
// 调: sub_47E9D0 sub_4B1BA0 sub_47DCC0
int /*thiscall*/ CNSwordman__vmt480(uint32_t *this)  // 实现：调: sub_47E9D0 sub_4B1BA0 sub_47DCC0
{
  uint32_t *v2; // edi
  int v3; // eax
  int v4; // ebx
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int64_t v9; // rax
  uint32_t *v10; // edi
  int v11; // ebx
  uint32_t *v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  uint32_t *v17; // [esp+Ch] [ebp-10h] BYREF
  uint32_t *v18; // [esp+10h] [ebp-Ch] BYREF
  int v19; // [esp+14h] [ebp-8h] BYREF
  signed int v20; // [esp+18h] [ebp-4h]

  IRDCharacter__vmt480(this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 35) > 0 )  // 调虚槽 +1140
  {
    v2 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 35);  // 调虚槽 +1160
    v3 = v2[103];  // v3 = 取 v2[103]
    v18 = v2;
    v4 = v3 != 0 ? (v2[104] - v3) / 14 : 0;
    v20 = 0;
    if ( v4 > 0 )  // 若 v4 > 0
    {
      while ( 1 )  // 条件循环
      {
        v19 = sub_47E9D0(v2, v20);  // v19 = 调 sub_47E9D0 返回值
        sub_4B1BA0(&v17, &v19);  // map lower_bound（键在 +12）
        v5 = v17;
        if ( v17 != (uint32_t *)*(this + 1855) )  // this+7420〔map7416End〕
        {
          v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, v19);  // 调虚槽 +1160
          v7 = sub_47DCC0(v6);  // v7 = 调 sub_47DCC0 返回值
          v8 = v5[5];  // v8 = 取 v5[5]
          if ( v8 < v7 )  // 若 v8 < v7
            v5[5] = v8 + 1;
        }
        if ( ++v20 >= v4 )
          break;  // 跳出循环/分支
        v2 = v18;
      }
    }
  }
  LODWORD(v9) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 27);  // 调虚槽 +1140
  if ( (int)v9 > 0 )
  {
    v10 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 27);  // 调虚槽 +1160
    LODWORD(v9) = v10[103];
    v17 = v10;
    if ( (uint32_t)v9 != 0 )
    {
      v9 = 2454267027LL * (v10[104] - (int)v9);
      v11 = (SHIDWORD(v9) >> 3) + (HIDWORD(v9) >> 31);
    }
    else  // 否则分支
    {
      v11 = 0;
    }
    v20 = 0;
    if ( v11 > 0 )  // 若 v11 > 0
    {
      while ( 1 )  // 条件循环
      {
        v19 = sub_47E9D0(v10, v20);  // v19 = 调 sub_47E9D0 返回值
        sub_4B1BA0(&v18, &v19);  // map lower_bound（键在 +12）
        v12 = v18;
        if ( v18 != (uint32_t *)*(this + 1855) )  // this+7420〔map7416End〕
        {
          v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, v19);  // 调虚槽 +1160
          v14 = sub_47DCC0(v13);  // v14 = 调 sub_47DCC0 返回值
          v15 = v12[5];  // v15 = 取 v12[5]
          if ( v15 < v14 )  // 若 v15 < v14
            v12[5] = v15 + 1;
        }
        LODWORD(v9) = ++v20;
        if ( v20 >= v11 )  // 若 v20 >= v11
          break;  // 跳出循环/分支
        v10 = v17;
      }
    }
  }
  return v9;
}



// ------------------------------------------------------------
// 0x5EECB0 CNSwordman__vmt48C
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_47E9D0 sub_47DCC0 sub_41A590
int /*usercall*/ CNSwordman__vmt48C@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>)  // 实现：调: sub_41A5E0 sub_47E9D0 sub_47DCC0 sub_41A590
{
  int result; // eax
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // edx
  uint32_t *v11; // edi
  int v12; // ebx
  int v13; // eax
  int v14; // ebx
  int v15; // edi
  int v16; // edx
  uint32_t *v17; // [esp+8h] [ebp-Ch]
  uint32_t *v18; // [esp+8h] [ebp-Ch]
  int v19; // [esp+Ch] [ebp-8h]
  signed int v20; // [esp+Ch] [ebp-8h]
  unsigned int v21; // [esp+10h] [ebp-4h]
  int v22; // [esp+10h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 1160))(pDwArg1, 35, nArg2);  // 调虚槽 +1160
    v17 = v4;
    if ( sub_41A5E0((unsigned int)v4 + 510) > 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v5 = v4[103];  // v5 = 取 v4[103]
      v19 = v5 != 0 ? (v4[104] - v5) / 14 : 0;
      v21 = 0;
      if ( v19 > 0 )  // 若 v19 > 0
      {
        while ( 1 )  // 条件循环
        {
          v6 = *pDwArg1;
          v7 = sub_47E9D0(v4, v21);  // v7 = 调 sub_47E9D0 返回值
          v8 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 1160))(pDwArg1, v7);
          v9 = sub_41A5E0(v8 + 510);  // crypt4byte 解密校验（·0x41A590 逆运算）
          if ( v9 > 0 && v9 < sub_47DCC0(v8) )  // 若 v9 > 0 与/或 v9 < sub_47DCC0
            sub_41A590(v8 + 510, v10, v9 + 1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          if ( (int)++v21 >= v19 )
            break;  // 跳出循环/分支
          v4 = v17;
        }
      }
    }
    v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1160))(pDwArg1, 27);  // 调虚槽 +1160
    v18 = v11;
    result = sub_41A5E0((unsigned int)v11 + 510);  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result > 0 )  // 若 result > 0
    {
      result = v11[103];  // result = 取 v11[103]
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = (v11[104] - result) / 14;
        v22 = result;
      }
      else  // 否则分支
      {
        v22 = 0;
      }
      v20 = 0;
      if ( v22 > 0 )  // 若 v22 > 0
      {
        while ( 1 )  // 条件循环
        {
          v12 = *pDwArg1;
          v13 = sub_47E9D0(v11, v20);  // v13 = 调 sub_47E9D0 返回值
          v14 = (*(int (/*thiscall*/ **)(int *, int))(v12 + 1160))(pDwArg1, v13);
          v15 = sub_41A5E0(v14 + 510);  // crypt4byte 解密校验（·0x41A590 逆运算）
          if ( v15 > 0 && v15 < sub_47DCC0(v14) )  // 若 v15 > 0 与/或 v15 < sub_47DCC0
            sub_41A590(v14 + 510, v16, v15 + 1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          result = ++v20;
          if ( v20 >= v22 )  // 若 v20 >= v22
            break;  // 跳出循环/分支
          v11 = v18;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EEE40 sub_5EEE40
// ------------------------------------------------------------
// 证: "R_SM_JUMP_ATK" | "R_SM_ATK" | "R_SM_DMG" | "SM_DIE"
// 调: sub_5EEE40 sub_430C80 sub_4015C0
int /*thiscall*/ sub_5EEE40(uint32_t *this)  // 实现：调: sub_5EEE40 sub_430C80 sub_4015C0
{
  uint32_t *pThis_7B5; // edi
  int fld_e1974; // eax
  unsigned int fld_e1975; // edx
  uint32_t *fld_e19752; // eax
  int v6; // edx
  unsigned int v7; // ecx
  uint32_t *v8; // eax
  int v9; // edx
  unsigned int v10; // ecx
  uint32_t *v11; // eax
  int v13; // [esp+8h] [ebp-4h] BYREF

  pThis_7B5 = this + 1973;
  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  *(this + 1716) = 1;
  *(this + 1717) = 8;
  *(this + 1718) = 15;
  fld_e1974 = *(this + 1974);
  v13 = 5;
  if ( fld_e1974 != 0 )  // 若 fld_e1974 非 0
    fld_e1975 = (*(this + 1975) - fld_e1974) >> 2;  // 向量元素数 = (end−begin)/4
  else  // 否则分支
    fld_e1975 = 0;
  if ( fld_e1974 != 0 && fld_e1975 < (*(this + 1976) - fld_e1974) >> 2 )  // 若 fld_e1974 != 0
  {
    fld_e19752 = (uint32_t *)*(this + 1975);
    *fld_e19752 = 5;
    *(this + 1975) = fld_e19752 + 1;
  }
  else  // 否则分支
  {
    sub_430C80((int)(this + 1973), *(this + 1975), 1u, &v13);  // uint32 vector 区间插入（同值填充）
  }
  v6 = pThis_7B5[1];  // v6 = 取 pThis_7B5[1]
  v13 = 4;
  if ( v6 != 0 )  // 若 v6 非 0
    v7 = (pThis_7B5[2] - v6) >> 2;  // 向量元素数 = (end−begin)/4
  else  // 否则分支
    v7 = 0;
  if ( v6 != 0 && v7 < (pThis_7B5[3] - v6) >> 2 )  // 若 v6 != 0
  {
    v8 = (uint32_t *)pThis_7B5[2];
    *v8 = 4;
    pThis_7B5[2] = v8 + 1;
  }
  else  // 否则分支
  {
    sub_430C80((int)pThis_7B5, pThis_7B5[2], 1u, &v13);  // uint32 vector 区间插入（同值填充）
  }
  v9 = pThis_7B5[1];  // v9 = 取 pThis_7B5[1]
  v13 = 5;
  if ( v9 != 0 )  // 若 v9 非 0
    v10 = (pThis_7B5[2] - v9) >> 2;  // 向量元素数 = (end−begin)/4
  else  // 否则分支
    v10 = 0;
  if ( v9 != 0 && v10 < (pThis_7B5[3] - v9) >> 2 )  // 若 v9 != 0
  {
    v11 = (uint32_t *)pThis_7B5[2];
    *v11 = 5;
    pThis_7B5[2] = v11 + 1;
  }
  else  // 否则分支
  {
    sub_430C80((int)pThis_7B5, pThis_7B5[2], 1u, &v13);  // uint32 vector 区间插入（同值填充）
  }
  *(this + 1977) = 100;
  *(this + 1978) = -300;
  *(this + 1979) = 200;
  *(this + 1980) = -300;
  *(this + 1961) = 44;
  *(this + 1962) = 65;
  *(this + 1963) = 1;
  *(this + 1982) = 4;
  sub_4015C0("R_SM_JUMP_ATK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_SM_ATK", 8u);  // 【std::string构造赋值】
  sub_4015C0("R_SM_DMG", 8u);  // 【std::string构造赋值】
  sub_4015C0("SM_DIE", 6u);  // 【std::string构造赋值】
  sub_4015C0("SM_JUMP", 7u);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0("SM_BACKSTEP", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("SM_THRUST", 9u);  // 【std::string构造赋值】
  sub_4015C0("SM_NOMANA", 9u);  // 【std::string构造赋值】
  sub_4015C0("SM_COMMAND_PET", 0xEu);  // 【std::string构造赋值】
  return sub_4015C0("SM_THROW", 8u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x5EF0A0 CNSwordman__vmt1F4
// ------------------------------------------------------------
// 证: "SACRIFICE_CURED"
// 调: sub_47E9D0 sub_699000 sub_47E440 sub_47EFD0 sub_4D6810
int /*thiscall*/ sub_5EF0A0(int *this, int nArg2, int nArg3, int nArg4)  // 【CNSwordman__vmt1F4】
{
  uint32_t *v5; // eax
  int v6; // edi
  int pThis_668; // eax
  int v8; // edx
  double v9; // st7
  int fld_e2106; // edi
  int v11; // ebx
  int v12; // eax
  int v13; // edx
  char *v14; // eax
  int v15; // eax
  uint64_t v16; // rax
  uint32_t *v17; // edi
  int *v18; // eax
  int v19; // edx
  uint8_t *pObj; // eax
  float v22; // [esp+14h] [ebp-40h]
  void *pBuf[4]; // [esp+30h] [ebp-24h] BYREF
  void *Block; // [esp+40h] [ebp-14h]
  int fld_e2105; // [esp+44h] [ebp-10h]
  int v26; // [esp+50h] [ebp-4h]

  if ( *(this + 1639) == 18 && (int *)dword_8F7C04 == this && *(this + 2077) < 2 )  // this+6556〔大状态ID〕
  {
    v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 8);  // 调虚槽 +1160
    v6 = sub_47E9D0(v5, 4u);  // v6 = 调 sub_47E9D0 返回值
    pThis_668 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
    v8 = *this;
    *(this + 2078) = pThis_668 + v6;  // this+8312〔nHoldPosZ(推断)〕
    (*(void (/*thiscall*/ **)(int *, int))(v8 + 1160))(this, 8);
    sub_47E440(1);  // 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），
  }
  if ( *(this + 1639) == 21 )  // this+6556〔大状态ID〕
  {
    fld_e2105 = *(this + 2105);  // this+8420〔pVecBegin〕
    if ( fld_e2105 != 0 )  // 若 fld_e2105 非 0
    {
      v9 = (double)fld_e2105;
      *(this + 2105) = 0;  // this+8420〔pVecBegin〕
      *((float *)this + 97) = *((float *)this + 97) - v9;  // this+388〔fAtkCtxVal〕
    }
    fld_e2106 = *(this + 2106) - (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    if ( fld_e2106 >= dword_795A00 )  // 若 fld_e2106 >= dword_795A00
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
      v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 16);  // 调虚槽 +1140
      v13 = *this;
      fld_e2105 = v12;
      v14 = (char *)(*(int (/*thiscall*/ **)(int *, int))(v13 + 1160))(this, 16);
      v15 = sub_47EFD0(v14, 0.0, fld_e2105, v11, v11, 0);  // v15 = 调 sub_47EFD0 返回值
      fld_e2105 = fld_e2106 - dword_795A00;
      v16 = (uint64_t)((double)(fld_e2106 - dword_795A00) * (double)v15 * flt_9B9350 * 0.0099999998);  // ×0.01f（百分数转比例）
      Block = (void *)v16;
      *(this + 2105) = v16;  // this+8420〔pVecBegin〕
      *((float *)this + 97) = (double)(int)v16 + *((float *)this + 97);  // this+388〔fAtkCtxVal〕
    }
  }
  v17 = (uint32_t *)nArg2;
  if ( *(this + 1639) == 10  // this+6556〔大状态ID〕
    && *(this + 1953) == 0  // this+7812〔nSubStateA(推断)〕
    && *(this + 1954) == 23  // this+7816〔nSubStateB(推断)〕
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    nArg2 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(*this + 740))(this)  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
                          * *((float *)this + 2100)  // this+8400〔pAppendage〕
                          * flt_9B934C);
    Block = operator new(0x80u);  // new(128 字节) 分配对象
    v26 = 0;
    if ( Block != nullptr )  // 若 Block 有效（非空）
    {
      v22 = (float)nArg2;
      v18 = (int *)sub_4D6810(LODWORD(v22), 500, 1, 1);  // CNChangeHp 构造（研究 §2⑦ 的延滞伤分支）
    }
    else  // 否则分支
    {
      v18 = nullptr;  // v18 = 空指针
    }
    v19 = *v18;
    v26 = -1;
    (*(void (/*thiscall*/ **)(int *, uint32_t *, int *, uint32_t, uint32_t, uint32_t, int))(v19 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      v18,
      v17,
      this,
      0,
      0,
      0,
      -1);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*v17 + 212))(v17, "SACRIFICE_CURED", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  }
  if ( *(this + 1639) == 22  // this+6556〔大状态ID〕
    && *(this + 2112) == 0  // this+8448〔nFinishVal〕
    && *(this + 154) == -1  // this+616〔nReactionState〕
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    pObj = __RTDynamicCast(
            v17,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDActiveObject `RTTI Type Descriptor',
            0);
    if ( pObj != nullptr  // 若 pObj != nullptr
      && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 824))(pObj) != 0  // 调虚槽 +824
      && (unsigned int)sub_4AED20((int)v17) <= 1
      && *(this + 2113) == 31 )
    {
      memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
      v26 = 1;
      nArg2 = 1;
      sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
      sub_431230((int)pBuf, this + 2113);  // uint32 vector push_back
      nArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*v17 + 48))(v17);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
      nArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*v17 + 52))(v17);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 22, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v17 + 596))(v17, 0);  // 调虚槽 +596：[RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActi…
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
      v26 = -1;
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
    }
  }
  return sub_4AFB30(this, v17, nArg3, nArg4);  // 返回 调 sub_4AFB30 返回值
}


// ------------------------------------------------------------
// 0x5EF3F0 CNSwordman__vmt1FC
// ------------------------------------------------------------
// 调: sub_699000 sub_47DCD0 sub_4E5CA0 sub_4E4C10 sub_47EFD0
int /*fastcall*/ sub_5EF3F0(uint32_t *pArg1, int nArg2, int nArg3, int pArg4, int nArg5)  // 【CNSwordman__vmt1FC】
{
  uint32_t *v5; // edi
  float *v7; // eax
  int v8; // edx
  int v9; // ebx
  int *v10; // ebx
  int *v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // edi
  char *v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // edi
  int v20; // eax
  bool v22; // zf
  int v23; // ebx
  int v24; // eax
  int v25; // ebx
  int v26; // eax
  int v27; // ecx
  int v28; // ebx
  int v29; // ebx
  int v30; // ebx
  int v31; // eax
  int v32; // ebx
  int v33; // eax
  int v34; // eax
  int v35; // ebx
  int v36; // [esp-10h] [ebp-B8h]
  int v37; // [esp-Ch] [ebp-B4h]
  int v38; // [esp-Ch] [ebp-B4h]
  int v39; // [esp-Ch] [ebp-B4h]
  int v40; // [esp-8h] [ebp-B0h]
  int v41; // [esp-4h] [ebp-ACh]
  int v42; // [esp+0h] [ebp-A8h]
  void *pBuf[4]; // [esp+Ch] [ebp-9Ch] BYREF
  uint8_t v44[4]; // [esp+1Ch] [ebp-8Ch] BYREF
  void *Block; // [esp+20h] [ebp-88h]
  int v46; // [esp+24h] [ebp-84h]
  int v47; // [esp+28h] [ebp-80h]
  float *v48; // [esp+2Ch] [ebp-7Ch]
  float v49; // [esp+30h] [ebp-78h] BYREF
  uint8_t v50[100]; // [esp+34h] [ebp-74h] BYREF
  int dword_796E502; // [esp+98h] [ebp-10h]
  int v52; // [esp+A4h] [ebp-4h]

  v5 = (uint32_t *)nArg3;
  dword_796E502 = dword_796E50;  // 帧时刻快照源
  v7 = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3);  // 调虚槽 +348：取坐标对象
  v8 = *pArg1;
  v48 = v7;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v8 + 308))(pArg1) != 0  // 调虚槽 +308：是否本地玩家
    && (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1140))(pArg1, 2) > 0  // 调虚槽 +1140
    && pArg1[1639] == 15
    && pArg1[2063] != -1
    && sub_699000((int)(pArg1 + 16)) <= pArg1[2063]  // 【clock_now(clk)】
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v5 + 368))(v5) != 0  // 调虚槽 +368：位移预测写入
    && (v9 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v5 + 660))(v5, pArg1)) == (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1)  // 调虚槽 +660
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1312))(pArg1, 2) != 0 )  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t *))(*pArg1 + 1160))(pArg1, 2, pArg1);  // 调虚槽 +1160
    sub_47DCD0(-1, v42);  // 调 震动/资源档位设置
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*v5 + 312))(v5, 1);  // 调虚槽 +312：濒死/一击表现(LAST STRIKE)
    v10 = *(int **)((*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 60))(v5) + 104);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    v48 = sub_4E5CA0(v5) == 0 ? (float *)pArg1 : nullptr;  // 阵营号 200..204 判定（200 起逐个比较）
    v11 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 340))(v5);  // 调虚槽 +340：三元组基址（+284，vt+340）
    v12 = *v10;
    nArg5 = *v11;
    (*(void (/*thiscall*/ **)(int *, uint8_t *))(v12 + 20))(v10, v50);  // 调虚槽 +20：CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买…
    v13 = (*(int (/*thiscall*/ **)(int *))(*v10 + 44))(v10);  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
    v41 = v5[242];  // v41 = 取 v5[242]
    v40 = v5[241];  // v40 = 取 v5[241]
    v36 = v13;
    v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 672))(v5);  // 调虚槽 +672：自身 HP
    nArg3 = sub_4E4C10((int)v5, (int)v48, nArg5, *(uint32_t *)(v14 + 24), (int)v50, v36, 0, v40, v41);  // 与 ·0x4E4A50 同构（差异：上下文使能位固定 1 + 数据块打包）
    v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 388))(pArg1);  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
    nArg5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1140))(pArg1, 2);  // 调虚槽 +1140
    v16 = (char *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1160))(pArg1, 2);  // 调虚槽 +1160
    v17 = sub_47EFD0(v16, 0.0, nArg5, v15, v15, 0);  // v17 = 调 sub_47EFD0 返回值
    v18 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    nArg5 = v17;
    (*(void (/*thiscall*/ **)(int, int, int))(v18 + 8))(dword_8F8520, 16, 2);  // 会话/UDP 管理器
    v19 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);  // 调虚槽 +1220：IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
    (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);  // 会话/UDP 管理器
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg3);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg5);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
    v52 = 0;
    nArg5 = 1;
    sub_431230((int)pBuf, &nArg5);  // uint32 vector push_back
    nArg5 = (uint64_t)(*(float *)(pArg4 + 20) * 0.5 + *(float *)(pArg4 + 8));  // pArg4+8〔nSkillRec8(推断)〕
    sub_431230((int)pBuf, &nArg5);  // uint32 vector push_back
    nArg5 = 1;
    sub_431230((int)pBuf, &nArg5);  // uint32 vector push_back
    nArg5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调虚槽 +152：效果通道 3
    sub_431230((int)pBuf, &nArg5);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 8);  // 调虚槽 +1104
    *((uint8_t *)pArg1 + 8268) = 1;
    pArg1[2066] = 0;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
    return 0;
  }
  else  // 否则分支
  {
    v22 = pArg1[1639] == 15;
    HIBYTE(nArg3) = 0;
    if ( v22
      && (v23 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v5 + 660))(v5, pArg1)) == (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1)  // 调虚槽 +660
      && (*((uint8_t *)v48 + 16) != 0 || *v48 > 0.0 || *((uint32_t *)v48 + 15) != 0)
      && (uint8_t)nArg5 == 0 )
    {
      *((uint8_t *)pArg1 + 8268) = 1;
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1140))(pArg1, 3) > 0  // 调虚槽 +1140
           && (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1140))(pArg1, 1) > 0  // 调虚槽 +1140
           && (*((uint8_t *)v48 + 16) != 0 || *v48 > 0.0 || *((uint32_t *)v48 + 15) != 0)
           && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1) == 0 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    {
      v24 = pArg1[1639];  // v24 = 取 pArg1[1639]
      if ( v24 != 4 && v24 != 9 && (uint8_t)nArg5 == 0 )  // 若 v24 != 4 与/或 v24 != 9
      {
        v37 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 1140))(pArg1, 3, -1);  // 调虚槽 +1140
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1160))(pArg1);  // 调虚槽 +1160
        v25 = sub_47EF20(3, 0, v37, -1, 11);  // v25 = 调 sub_47EF20 返回值
        if ( sub_445870(21654682, 10000) < 100 * v25  // 槽表随机数
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1312))(pArg1, 1) != 0 )  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
        {
          *((uint8_t *)pArg1 + 8268) = 1;
          HIBYTE(nArg3) = 1;
          sub_5E5260((void **)pArg1 + 2029);  // 调 动画子对象清理临时缓冲
        }
      }
    }
    if ( *((uint8_t *)pArg1 + 8268) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1160))(pArg1, 1);  // 调虚槽 +1160
      v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1140))(pArg1, 1);  // 调虚槽 +1140
      v27 = *((uint32_t *)v48 + 3);
      if ( v27 == 1 )  // 若 v27 == 1
      {
        pArg1[2066] = 100 - sub_47EF20(3, v26, -1, -1, 11);  // 调 读攻击数据表
      }
      else if ( v27 != 0 )
      {
        if ( v27 == 2 )  // 若 v27 == 2
          pArg1[2066] = 100;
      }
      else  // 否则分支
      {
        pArg1[2066] = 100 - sub_47EF20(2, v26, -1, -1, 11);  // 调 读攻击数据表
      }
      if ( *((uint8_t *)pArg1 + 642) != 0 )
      {
        v28 = pArg1[161];  // v28 = 取 pArg1[161]
      }
      else  // 否则分支
      {
        v29 = pArg1[30];  // v29 = 取 pArg1[30]
        if ( v29 != 0 )  // 若 v29 非 0
        {
          if ( *(uint32_t *)(v29 + 148) == -1 )
            sub_4938F0(pArg1[30]);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
          v28 = *(uint32_t *)(v29 + 112);
        }
        else  // 否则分支
        {
          v28 = 0;
        }
      }
      if ( (HIBYTE(nArg3) != 0 || v28 == 0) && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )  // 调虚槽 +308：是否本地玩家
      {
        Block = nullptr;  // Block = 空指针
        v46 = 0;
        v47 = 0;
        v52 = 1;
        LODWORD(v49) = 1;
        sub_431230((int)v44, &v49);  // uint32 vector push_back
        LODWORD(v49) = (uint64_t)(*(float *)(pArg4 + 20) * 0.5 + *(float *)(pArg4 + 8));  // pArg4+8〔nSkillRec8(推断)〕
        sub_431230((int)v44, &v49);  // uint32 vector push_back
        v49 = 0.0;
        sub_431230((int)v44, &v49);  // uint32 vector push_back
        if ( HIBYTE(nArg3) == 0
          || (v30 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v5 + 660))(v5, pArg1)) == (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1) )  // 调虚槽 +660
        {
          nArg3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调虚槽 +152：效果通道 3
          sub_431230((int)v44, &nArg3);  // uint32 vector push_back
        }
        else  // 否则分支
        {
          v31 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调虚槽 +152：效果通道 3
          nArg3 = sub_432E50(v31);  // 关系码对调映射
          sub_431230((int)v44, &nArg3);  // uint32 vector push_back
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, v44, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        v52 = -1;
        if ( Block != nullptr )  // 若 Block 有效（非空）
          j__free(Block);
        Block = nullptr;  // Block = 空指针
        v46 = 0;
        v47 = 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 8);  // 调虚槽 +1104
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1140))(pArg1, 7) > 0 && *((uint8_t *)pArg1 + 8268) == 0 )  // 调虚槽 +1140
    {
      v32 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v5 + 660))(v5, pArg1);  // 调虚槽 +660
      if ( v32 != (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1)  // 调虚槽 +152：效果通道 3
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v5 + 40))(v5, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1) == 0 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      {
        v33 = pArg1[1639];  // v33 = 取 pArg1[1639]
        if ( v33 != 4 && v33 != 9 && sub_4AED00(v48) )  // 若 v33 != 4 与/或 v33 != 9
        {
          v38 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 1140))(pArg1, 7, -1);  // 调虚槽 +1140
          (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1160))(pArg1);  // 调虚槽 +1160
          nArg3 = sub_47EF20(7, 0, v38, -1, 11);  // nArg3 = 调 sub_47EF20 返回值
          v49 = (float)nArg3;
          nArg3 = sub_445870(&unk_85B384, 10000);  // 槽表随机数
          if ( v49 * 100.0 > (double)nArg3 && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1312))(pArg1, 7) != 0 )  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
            *((uint8_t *)pArg1 + 8305) = 1;
        }
      }
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1140))(pArg1, 47) > 0  // 调虚槽 +1140
      && *((uint8_t *)pArg1 + 8268) == 0
      && *((uint8_t *)pArg1 + 8305) == 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v5 + 40))(v5, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1) == 0 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    {
      v34 = pArg1[1639];  // v34 = 取 pArg1[1639]
      if ( v34 != 4 && v34 != 9 && sub_4AED00(v48) )  // 若 v34 != 4 与/或 v34 != 9
      {
        v39 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 1140))(pArg1, 47, -1);  // 调虚槽 +1140
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1160))(pArg1);  // 调虚槽 +1160
        v35 = sub_47EF20(47, 0, v39, -1, 11);  // v35 = 调 sub_47EF20 返回值
        if ( sub_445870(off_702C24, 10000) < 100 * v35  // 槽表随机数
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1312))(pArg1, 47) != 0 )  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
        {
          *((uint8_t *)pArg1 + 8412) = 1;
        }
      }
    }
    return sub_4AFB80(pArg1, (int)v5, pArg4, nArg5);  // 返回 调 sub_4AFB80 返回值
  }
}


// ------------------------------------------------------------
// 0x5EFBD0 CNSwordman__vmt200
// ------------------------------------------------------------
// 调: sub_4938F0 sub_432E50 sub_431230 sub_5E5260
int /*thiscall*/ sub_5EFBD0(int this, int pArg2, uint32_t *Block, int nArg4)  // 【CNSwordman__vmt200】
{
  float v4; // edi
  int nFrameOverride; // ecx  | +0x0284 → 基类帧时刻覆盖值（与 +0x282 成对；0x4E5C10 第四参）（证据: va=004E5C10）（CNSwordman；va=004E5C10）
  int pArg22; // ecx
  int nReactionState; // eax  | +0x0268 → 受击反应态（CNSwordman；va=005EFBD0）
  int v9; // ebx
  int pThis_30; // eax
  int v11; // ebx
  int pThis_34; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // ebx
  int v16; // eax
  unsigned int v17; // edx
  int v18; // eax
  int nReactionState_; // eax  | +0x0268 → 受击反应态（CNSwordman；va=005EFBD0）
  uint32_t *pThis_488; // eax
  int v21; // eax
  int v22; // edi
  uint32_t *pThis_4882; // edi
  void **v24; // eax
  uint32_t *v25; // eax
  int v26; // eax
  int v28; // [esp+74h] [ebp-44h]
  int v29; // [esp+78h] [ebp-40h]
  unsigned int v30; // [esp+80h] [ebp-38h]
  void *pBuf2[4]; // [esp+8Ch] [ebp-2Ch] BYREF
  void *pBuf[4]; // [esp+9Ch] [ebp-1Ch] BYREF
  int v33; // [esp+B4h] [ebp-4h]

  v4 = *(float *)&pArg2;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg2 + 348))(pArg2) + 60) == 0 )  // 调虚槽 +348：取坐标对象
    goto LABEL_11;
  if ( *(uint8_t *)(this + 642) != 0 )  // this+642〔bAttackEnable〕
  {
    nFrameOverride = *(uint32_t *)(this + 644);  // this+644〔nFrameOverride〕
    goto LABEL_8;
  }
  pArg2 = *(uint32_t *)(this + 120);  // this+120〔pAnimObj〕
  pArg22 = pArg2;
  if ( pArg2 != 0 )  // 若 pArg2 非 0
  {
    if ( *(uint32_t *)(pArg2 + 148) == -1 )  // pArg2+148〔fAdd148(推断)〕
    {
      sub_4938F0(pArg2);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      pArg22 = pArg2;
    }
    nFrameOverride = *(uint32_t *)(pArg22 + 112);  // pArg22+112〔pHostComp112〕
LABEL_8:  // 标签 LABEL_8（跳转合流点）
    if ( nFrameOverride != 0 )  // 若 fld_284 非 0
      goto LABEL_11;
  }
  if ( (uint8_t)nArg4 == 0 )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 13);  // 调虚槽 +216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 12);  // 调虚槽 +216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 11);  // 调虚槽 +216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 16);  // 调虚槽 +216：音效 TAG 查询
  }
LABEL_11:  // 标签 LABEL_11（跳转合流点）
  nArg4 = sub_4B9720((unsigned int *)this, v4, (int)Block, nArg4);  // 霸体特效（SuperArmorEffect.ani；sub_4920E0 全帧缩放；+40/+52 槽；调 sub_4D71B0 命中主处理器(待验证)）
  if ( *(uint8_t *)(this + 8305) != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    nReactionState = *(uint32_t *)(this + 616);  // this+616〔nReactionState〕
    if ( nReactionState != 3 && nReactionState != 4 && nReactionState != 5 )  // 若 fld_268 != 3 与/或 fld_268 != 4 与/或 fld_268 != 5
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 27, 2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 2);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      v9 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      pThis_30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 48))(this);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, pThis_30);  // 会话/UDP 管理器
      v11 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      pThis_34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, pThis_34);  // 会话/UDP 管理器
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 200);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      v13 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      v14 = (*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 48))(COERCE_FLOAT(LODWORD(v4)));  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
      (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);  // 会话/UDP 管理器
      v15 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      v16 = (*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 52))(COERCE_FLOAT(LODWORD(v4)));  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行…
      (*(void (/*thiscall*/ **)(int, int))(v15 + 36))(dword_8F8520, v16);  // 会话/UDP 管理器
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 200);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      memset(&pBuf2[1], 0, 12);  // 内存块填充 12 字节
      v17 = *(uint32_t *)this;
      v33 = 0;
      v18 = (*(int (/*thiscall*/ **)(int))(v17 + 152))(this);  // 调虚槽 +152：效果通道 3
      pArg2 = sub_432E50(v18);  // 关系码对调映射
      sub_431230((int)pBuf2, &pArg2);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, void **, int, uint32_t))(*(uint32_t *)this + 560))(this, 17, pBuf2, 1, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      v33 = -1;
      sub_5E5260(pBuf2);  // 调 动画子对象清理临时缓冲
    }
  }
  if ( *(uint8_t *)(this + 8412) != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    nReactionState_ = *(uint32_t *)(this + 616);  // this+616〔nReactionState〕
    if ( nReactionState_ != 3 && nReactionState_ != 4 && nReactionState_ != 5 )  // 若 fld_2682 != 3 与/或 fld_2682 != 4 与/或 fld_2682 != 5
    {
      memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
      v33 = 1;
      pArg2 = 0;
      sub_431230((int)pBuf, &pArg2);  // uint32 vector push_back
      pArg2 = 0;
      sub_431230((int)pBuf, &pArg2);  // uint32 vector push_back
      pArg2 = 32;
      sub_431230((int)pBuf, &pArg2);  // uint32 vector push_back
      pArg2 = 0;
      sub_431230((int)pBuf, &pArg2);  // uint32 vector push_back
      pThis_488 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)this + 1160))(this, 32, 0);  // 调虚槽 +1160
      pArg2 = sub_47E9D0(pThis_488, v30);  // pArg2 = 调 sub_47E9D0 返回值
      sub_431230((int)pBuf, &pArg2);  // uint32 vector push_back
      pArg2 = 1;
      sub_431230((int)pBuf, &pArg2);  // uint32 vector push_back
      pArg2 = 4;
      sub_431230((int)pBuf, &pArg2);  // uint32 vector push_back
      pArg2 = 4;
      sub_431230((int)pBuf, &pArg2);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, void **, uint32_t))(*(uint32_t *)this + 560))(this, 10, pBuf, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      v33 = -1;
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
    }
  }
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 53) > 0 && *(uint8_t *)(this + 8268) == 0 )  // 调虚槽 +1140
  {
    v21 = (*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 348))(COERCE_FLOAT(LODWORD(v4)));  // 调虚槽 +348：取坐标对象
    if ( *(uint8_t *)(v21 + 16) != 0
      || *(float *)v21 > 0.0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 348))(COERCE_FLOAT(LODWORD(v4))) + 60) != 0 )  // 调虚槽 +348：取坐标对象
    {
      v22 = (*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 376))(COERCE_FLOAT(LODWORD(v4)));  // 调虚槽 +376：坐标同步包（type 37）
      if ( v22 != (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 376))(this) )  // 调虚槽 +376：坐标同步包（type 37）
      {
        pThis_4882 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 53);  // 调虚槽 +1160
        pArg2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 53);  // 调虚槽 +1140
        Block = operator new(0x7Cu);  // new(124 字节) 分配对象
        v33 = 2;
        if ( Block != nullptr )  // 若 Block 有效（非空）
        {
          v29 = sub_47EF20(1, pArg2, -1, -1, 11);  // v29 = 调 sub_47EF20 返回值
          pArg2 = sub_47EF20(0, pArg2, -1, -1, 11);  // pArg2 = 调 sub_47EF20 返回值
          *(float *)&v28 = (float)pArg2;
          v24 = (void **)sub_4B3DF0(Block, 1, 0, v28, v29, 5);  // CNChangeStatus 构造（六参）
        }
        else  // 否则分支
        {
          v24 = nullptr;  // v24 = 空指针
        }
        pArg2 = (int)v24;
        v25 = *v24;
        v33 = -1;
        Block = v25;
        v26 = sub_47E9D0(pThis_4882, 0);  // v26 = 调 sub_47E9D0 返回值
        ((void (/*thiscall*/ *)(int, int, int, int, uint32_t, int, int))Block[14])(pArg2, this, this, 1, 0, 16, v26);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
          this,
          "HOOP_SHIELD",  // 标签 HOOP_SHIELD
          -1,
          0,
          0);
      }
    }
  }
  return nArg4;
}

