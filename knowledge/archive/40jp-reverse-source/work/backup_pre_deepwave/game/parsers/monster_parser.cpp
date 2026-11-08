// ============================================================
// 【40JP逆向源代码工程】parsers/monster_parser.cpp
// 模块: 怪物/NPC/PassiveObject 定义解析器族
// 来源: work/dump_parsers.txt  区块: 0x4FC000-0x50C000
//       （深度校验用 work/dump_full_0/1/2.txt —— [tag] 词汇表按全量版提取）
// 层级: L2 转写层 → L1 精修层（会话 4 精修：标签族头注 + attackinfo 字段表映射 + 分区）
// 函数数: 207
//
// ★ 本文件全部解析器都是 [tag] 字符串驱动：sub_442A10 打开文件 → sub_443430 逐行读 →
//   sub_40BF00/sub_423300 前缀/全串比对标签 → sub_4423D0(整型)/sub_442480(浮点)/
//   sub_443370(字符串)取参数。未识别标签一律走 off_77F3FC("SCRIPT TAG ERROR! [%s] %s")。
//
// ★ 关键锚点（研究 20 定案）：
//   - sub_503BA0 = 怪物/PO 攻击定义解析器（attackinfo 结构填充，全标签词汇表见研究 20 §1.3）
//   - sub_502F00 = 玩家技能定义解析器（[shake screen]/[command] 等，研究 20 §13/§30）
//   - sub_509C90 = 怪物数据文件解析器（[hit recovery]+396/+400、[stuckbonus on damage]+428..440
//     四档 —— 研究 20 §12 的"固定字段对"主体）
//   - sub_50B400 / sub_50B840 = PassiveObject / 技能 PO 解析器（[recovery time]/[skill recovery time]）
//
// 分区（按 VA 升序）：
//   §A 0x4FC000-0x4FD000  全局配置族（经验/掉率增益表、地图表、任务/场景资源）
//   §B 0x4FD000-0x4FE000  地图(场景)定义 + 副本定义族
//   §C 0x4FE000-0x4FF800  场地/NPC 定义族（field/npc 资源与商店角色）
//   §D 0x4FF800-0x504000  任务(quest)定义族 + 对象创建(sub_500B30) + 技能定义解析器 sub_502F00
//   §E 0x504000-0x504600  掉落/奖励类别标签（[monster]/[trap]/[item]/[quest]）
//   §F 0x504600-0x507690  容器辅助族（list/vector 模板实例）
//   §G 0x507690-0x50AF40  瓦片地图/副本地图/怪物定义族 + ★ 攻击定义 sub_503BA0
//   §H 0x50AF40-0x50C000  PassiveObject / 地图物件 / 技能 PO 定义族（sub_50AF40/50B400/50B840）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// §A 0x4FC000-0x4FD000 全局配置族
// ============================================================

// ------------------------------------------------------------
// 0x4FC0F0 sub_4FC0F0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4FC0F0(int this, unsigned int uArg2, int Block, int nArg4, int nArg5, int nArg6, int nArg7)
{
  int fld_4; // ecx
  unsigned int result; // eax
  int fld_82; // eax
  uint32_t *fld_8; // edi

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 8) - fld_4) / 20;
  else
    result = 0;
  if ( result >= uArg2 )
  {
    if ( fld_4 != 0 )
    {
      fld_8 = *(uint32_t **)(this + 8);
      result = ((int)fld_8 - fld_4) / 20;
      if ( uArg2 < result )
      {
        result = fld_4 + 20 * uArg2;
        if ( (uint32_t *)result != fld_8 )
        {
          result = (unsigned int)sub_4FBD40(fld_8, fld_8, (uint32_t *)result);
          *(uint32_t *)(this + 8) = result;
        }
      }
    }
  }
  else
  {
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) / 20;
    else
      fld_82 = 0;
    return sub_4FBE30((int *)this, *(char **)(this + 8), uArg2 - fld_82, &Block);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FC1A0 sub_4FC1A0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4FC1A0(void *this, unsigned int uArg2)
{
  return sub_4FC0F0((int)this, uArg2, 0, 0, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x4FC1E0 sub_4FC1E0 —— 全局战斗/成长配置解析器（[nation code]/[version]/经验与掉率增益表族）
//   [nation code]/[version] 区码与版本；经验增益 3 表（队伍人数×4 / 副本难度×4 / 结算评级×5）
//   + 掉率增益 4 表（难度/队伍/怪物种类） + 奖励概率 + 物品与稀有度判定基数 + 公会成本。
//   [drop prob number]/[drop prob]、[result reward prob number]/[result reward prob] 成对出现：
//   先报条数再逐条读（研究 20 §12 的"固定字段对"同型）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FC1E0(int pArg1, const char *ArgList)
{
  char result; // al
  int pArg12; // ebx
  int i2; // esi
  float *v5; // esi
  int i; // edi
  float *v7; // esi
  int j; // edi
  float *v9; // esi
  int k; // edi
  int v11; // eax
  int v12; // edi
  int *v13; // esi
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  void ***v18; // edx
  float *v19; // esi
  int m; // edi
  float *v21; // esi
  int n; // edi
  float *v23; // esi
  int ii; // edi
  int v25; // edi
  int v26; // ebx
  int *v27; // esi
  int v28; // eax
  int v29; // eax
  float *v30; // esi
  int jj; // edi
  float *v32; // esi
  int kk; // edi
  int *v34; // esi
  int mm; // edi
  int *v36; // esi
  int nn; // edi
  const char *p_Block; // eax
  void **v39[3]; // [esp-1Ch] [ebp-5Ch] BYREF
  uint8_t *v40; // [esp-10h] [ebp-50h]
  uint8_t *v41; // [esp-Ch] [ebp-4Ch]
  uint8_t *v42; // [esp-8h] [ebp-48h]
  unsigned int v43; // [esp-4h] [ebp-44h]
  void ***i1; // [esp+Ch] [ebp-34h] BYREF
  char v45; // [esp+13h] [ebp-2Dh] BYREF
  int v46; // [esp+14h] [ebp-2Ch] BYREF
  void *Block; // [esp+18h] [ebp-28h] BYREF
  int v48; // [esp+28h] [ebp-18h]
  unsigned int v49; // [esp+2Ch] [ebp-14h]
  int dword_796E502; // [esp+30h] [ebp-10h]
  int v51; // [esp+3Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)szPassword, (int)ArgList);
  if ( result != 0 )
  {
    pArg12 = pArg1;
    sub_433EF0(pArg1);
    v49 = 15;
    v48 = 0;
    LOBYTE(Block) = 0;
    v51 = 0;
    v45 = 0;
    while ( (uint8_t)sub_443430(&v46) != 0 )
    {
      sub_442B20(&v46);
      if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[nation code]", 0xDu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[version]", 9u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[clear exp bonusrate]", 0x15u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[monster exp bonusrate]", 0x17u) != 0 )
            {
              if ( (uint8_t)sub_423300(&v46, "[party user number exp bonusrate]") != 0 )
              {
                v5 = (float *)(pArg12 + 12);
                for ( i = 4; i != 0; --i )
                  *v5++ = sub_442480(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v46, "[dungeon difficulty exp bonusrate]") != 0 )
              {
                v7 = (float *)(pArg12 + 28);
                for ( j = 4; j != 0; --j )
                  *v7++ = sub_442480(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v46, "[clear rank exp bonusrate]") != 0 )
              {
                v9 = (float *)(pArg12 + 44);
                for ( k = 5; k != 0; --k )
                  *v9++ = sub_442480(nullptr);
              }
              else
              {
                if ( (uint8_t)sub_423300(&v46, "[drop prob number]") == 0 )
                {
                  if ( (uint8_t)sub_423300(&v46, "[drop prob]") != 0 )
                  {
                    v12 = 0;
                    if ( sub_45E580(pArg12 + 64) > 0 )
                    {
                      i1 = nullptr;
                      do
                      {
                        v13 = (int *)((char *)i1 + *(uint32_t *)(pArg12 + 68));
                        v14 = sub_4423D0(nullptr);
                        v42 = nullptr;
                        *v13 = v14;
                        v15 = sub_4423D0(v42);
                        v41 = nullptr;
                        v13[1] = v15;
                        v16 = sub_4423D0(v41);
                        v40 = nullptr;
                        v13[2] = v16;
                        v17 = sub_4423D0(v40);
                        v18 = i1 + 5;
                        v13[3] = v17;
                        v13[4] = 1000;
                        ++v12;
                        i1 = v18;
                      }
                      while ( v12 < sub_45E580(pArg12 + 64) );
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(&v46, "[dungeon difficulty drop bonusrate]") != 0 )
                  {
                    v19 = (float *)(pArg12 + 80);
                    for ( m = 4; m != 0; --m )
                      *v19++ = sub_442480(nullptr);
                    continue;
                  }
                  if ( (uint8_t)sub_423300(&v46, "[party user number drop bonusrate]") != 0 )
                  {
                    v21 = (float *)(pArg12 + 96);
                    for ( n = 4; n != 0; --n )
                      *v21++ = sub_442480(nullptr);
                    continue;
                  }
                  if ( (uint8_t)sub_423300(&v46, "[drop bonusrate of monster kind]") != 0 )
                  {
                    v23 = (float *)(pArg12 + 112);
                    for ( ii = 4; ii != 0; --ii )
                      *v23++ = sub_442480(nullptr);
                    continue;
                  }
                  if ( (uint8_t)sub_423300(&v46, "[result reward prob number]") == 0 )
                  {
                    if ( (uint8_t)sub_423300(&v46, "[result reward prob]") != 0 )
                    {
                      v25 = 0;
                      if ( sub_45E580(pArg12 + 128) > 0 )
                      {
                        v26 = 0;
                        do
                        {
                          v27 = (int *)(v26 + *(uint32_t *)(pArg1 + 132));
                          v28 = sub_4423D0(nullptr);
                          v42 = nullptr;
                          *v27 = v28;
                          v29 = sub_4423D0(v42);
                          v41 = nullptr;
                          v27[1] = v29;
                          v27[2] = 0;
                          v27[3] = sub_4423D0(v41);
                          v27[4] = 1000;
                          ++v25;
                          v26 += 20;
                        }
                        while ( v25 < sub_45E580(pArg1 + 128) );
                        pArg12 = pArg1;
                      }
                    }
                    else if ( (uint8_t)sub_423300(&v46, "[dungeon difficulty reward bonusrate]") != 0 )
                    {
                      v30 = (float *)(pArg12 + 144);
                      for ( jj = 4; jj != 0; --jj )
                        *v30++ = sub_442480(nullptr);
                    }
                    else if ( (uint8_t)sub_423300(&v46, "[party user number reward bonusrate]") != 0 )
                    {
                      v32 = (float *)(pArg12 + 160);
                      for ( kk = 4; kk != 0; --kk )
                        *v32++ = sub_442480(nullptr);
                    }
                    else if ( (uint8_t)sub_423300(&v46, "[basis of item dicision]") != 0 )
                    {
                      *(uint32_t *)(pArg12 + 176) = sub_4423D0(nullptr);
                    }
                    else if ( (uint8_t)sub_423300(&v46, "[basis of equipment rarity dicision]") != 0 )
                    {
                      v34 = (int *)(pArg12 + 180);
                      for ( mm = 4; mm != 0; --mm )
                        *v34++ = sub_4423D0(nullptr);
                    }
                    else if ( (uint8_t)sub_423300(&v46, "[basis of stackable rarity dicision]") != 0 )
                    {
                      v36 = (int *)(pArg12 + 196);
                      for ( nn = 4; nn != 0; --nn )
                        *v36++ = sub_4423D0(nullptr);
                    }
                    else if ( (uint8_t)sub_423300(&v46, "[stamina recovery cost]") != 0 )
                    {
                      sub_5E5260((void **)(pArg12 + 212));
                      for ( i1 = (void ***)sub_4423D0(&v45); v45 != 0; i1 = (void ***)sub_4423D0(&v45) )
                        sub_431230(pArg12 + 212, &i1);
                    }
                    else if ( (uint8_t)sub_423300(&v46, "[guild create cost]") != 0 )
                    {
                      *(uint32_t *)(pArg12 + 228) = sub_4423D0(nullptr);
                    }
                    else if ( (uint8_t)sub_423300(&v46, "[guild levelup cost]") != 0 )
                    {
                      *(uint32_t *)(pArg12 + 232) = sub_4423D0(nullptr);
                    }
                    else if ( (uint8_t)sub_423300(&v46, "[guild point acquirement ratio]") != 0 )
                    {
                      *(uint32_t *)(pArg12 + 236) = sub_4423D0(nullptr);
                    }
                    else
                    {
                      i1 = v39;
                      sub_401690(&v46);
                      if ( sub_442C80((char)v39[0], v39[1], (int)v39[2], (int)v40, (int)v41, (int)v42, v43) == 0 )
                      {
                        p_Block = (const char *)Block;
                        if ( v49 < 0x10 )
                          p_Block = (const char *)&Block;
                        off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, p_Block);
                      }
                    }
                    continue;
                  }
                }
                v11 = sub_4423D0(nullptr);
                sub_4FC1A0(v11);
              }
            }
            else
            {
              *(float *)(pArg12 + 8) = sub_442480(nullptr);
            }
          }
          else
          {
            *(float *)(pArg12 + 4) = sub_442480(nullptr);
          }
        }
        else
        {
          for ( i2 = 0; i2 < 4; ++i2 )
            *(uint8_t *)(i2 + pArg12) = sub_4423D0(nullptr);
        }
      }
      else
      {
        dword_78FF38 = sub_4423D0(nullptr);
        if ( dword_78FF38 == 1 )
          dword_9B0AB0 = (int)&dword_9B0C08;
        else
          dword_9B0AB0 = (int)&dword_9B0BC8;
      }
    }
    if ( v49 >= 0x10 )
      j__free(Block);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FC840 sub_4FC840
// ------------------------------------------------------------
bool /*cdecl*/ sub_4FC840(const char *pArg1, int nArg2)
{
  strcpy(byte_9B6C78, pArg1);
  if ( byte_9B6C77[strlen(byte_9B6C78)] != 92 && byte_9B6C77[strlen(byte_9B6C78)] != 47 )
    *(uint16_t *)&byte_9B6C78[strlen(byte_9B6C78)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B6D78, (char)byte_9B6C78, nArg2) != 0;
}



// ------------------------------------------------------------
// 0x4FC8D0 sub_4FC8D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4FC8D0(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 69) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 69) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 69) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 69) == 0 );
        if ( *(uint8_t *)(result + 69) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 69) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FC930 sub_4FC930
// ------------------------------------------------------------
void /*thiscall*/ sub_4FC930(void *this)
{
  *(uint32_t *)this = -1;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 8) = 0;
  if ( *((uint32_t *)this + 10) != 0 )
    j__free(*((void **)this + 10));
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
}



// ------------------------------------------------------------
// 0x4FC970 sub_4FC970
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FC970(uint32_t *this, uint32_t *pArg2)
{
  uint32_t *pThis_1; // ecx

  pThis_1 = this + 1;
  *this = *pArg2;
  pThis_1[6] = 15;
  pThis_1[5] = 0;
  *((uint8_t *)pThis_1 + 4) = 0;
  sub_4014D0((std::_String_base *)pThis_1, pArg2 + 1, 0, -1);
  *(this + 8) = pArg2[8];
  sub_435020(pArg2 + 9);
  return this;
}



// ------------------------------------------------------------
// 0x4FC9F0 sub_4FC9F0
// ------------------------------------------------------------
char */*thiscall*/ sub_4FC9F0(char *this)
{
  char *pThis_4; // ecx

  pThis_4 = this + 4;
  *((uint32_t *)pThis_4 + 6) = 15;
  *((uint32_t *)pThis_4 + 5) = 0;
  pThis_4[4] = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *(uint32_t *)this = -1;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 8) = 0;
  if ( *((uint32_t *)this + 10) != 0 )
    j__free(*((void **)this + 10));
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4FCA80 sub_4FCA80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FCA80(uint32_t *this, uint32_t *pArg2)
{
  *this = *pArg2;
  sub_4014D0((std::_String_base *)(this + 1), pArg2 + 1, 0, -1);
  *(this + 8) = pArg2[8];
  sub_4ED3F0((int)(this + 9), (int)(pArg2 + 9));
  return this;
}



// ------------------------------------------------------------
// 0x4FCAC0 sub_4FCAC0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4FCAC0(int nArg1, int nArg2, int nArg3, uint32_t *pArg4, char pszArg5)
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  pMem = operator new(0x48u);
  pMem2 = pMem;
  v8[4] = pMem;
  v8[8] = (void *)1;
  v8[3] = pMem;
  if ( pMem != nullptr )
  {
    *pMem = nArg1;
    pMem[1] = nArg2;
    pMem[2] = nArg3;
    pMem[3] = *pArg4;
    sub_4FC970(pMem + 4, pArg4 + 1);
    *((uint8_t *)pMem2 + 68) = pszArg5;
    *((uint8_t *)pMem2 + 69) = 0;
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x4FCB60 sub_4FCB60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FCB60(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
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

  if ( *(this + 2) >= 0x4924923u )
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_4FCAC0(*(this + 1), pArg4, *(this + 1), nArg5, 0);
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
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 68) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 68) != 0 )
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_4CE650(*v10);
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 68) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 68) = 0;
          sub_4CE6B0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 68) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4CE6B0(*v10);
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 68) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 68) = 0;
        sub_4CE650(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 68) = 1;
      *(uint8_t *)(v14 + 68) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 68) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 68) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 68) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4FCD10 sub_4FCD10
// ------------------------------------------------------------
int /*thiscall*/ sub_4FCD10(int *this, int pArg2, uint32_t *uArg3)
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
  if ( *((uint8_t *)v6 + 69) == 0 )
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
    while ( *((uint8_t *)v6 + 69) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_4FCB60(this, &uArg3, 1, fld_e1, uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4FC8D0(&uArg3);
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
    v12 = *sub_4FCB60(this, &uArg3, v13, fld_e1, uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4FCDD0 sub_4FCDD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FCDD0(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_4FCB60((int *)this, uArg2, 1, *(uint32_t **)(this + 4), pArg4);
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4FCB60((int *)this, uArg2, 1, pArg3, pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )
  {
    v8 = (uint32_t *)fld_4[2];
    if ( v8[3] < *pArg4 )
    {
      sub_4FCB60((int *)this, uArg2, 0, v8, pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4FC8D0(&pArg4), pArg4[3] >= *pArg42) )
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_4CE5F0(&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4FCD10((int *)this, (int)v10, pArg42);
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 69) != 0 )
      sub_4FCB60((int *)this, uArg2, 0, pArg3, pArg42);
    else
      sub_4FCB60((int *)this, uArg2, 1, pArg4, pArg42);
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 69) != 0 )
      sub_4FCB60((int *)this, uArg2, 0, pArg4, pArg42);
    else
      sub_4FCB60((int *)this, uArg2, 1, pArg3, pArg42);
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4FCF30 sub_4FCF30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FCF30(uint32_t *this, int *pDwArg2)
{
  int *pDwArg22; // ebx
  uint32_t *fld_e1; // esi
  int *v5; // eax
  char *v6; // eax
  int v8; // [esp+Ch] [ebp-78h] BYREF
  int v9; // [esp+10h] [ebp-74h] BYREF
  void *v10; // [esp+18h] [ebp-6Ch]
  int v11; // [esp+28h] [ebp-5Ch]
  unsigned int v12; // [esp+2Ch] [ebp-58h]
  void *Block; // [esp+38h] [ebp-4Ch]
  int v14; // [esp+3Ch] [ebp-48h]
  int v15; // [esp+40h] [ebp-44h]
  char v16[8]; // [esp+44h] [ebp-40h] BYREF
  void *v17; // [esp+4Ch] [ebp-38h]
  unsigned int v18; // [esp+60h] [ebp-24h]
  void *v19; // [esp+6Ch] [ebp-18h]
  int v20; // [esp+70h] [ebp-14h]
  int v21; // [esp+74h] [ebp-10h]
  int v22; // [esp+80h] [ebp-4h]

  pDwArg22 = pDwArg2;
  fld_e1 = (uint32_t *)*(this + 1);
  v5 = (int *)fld_e1[1];
  while ( *((uint8_t *)v5 + 69) == 0 )
  {
    if ( v5[3] >= *pDwArg2 )
    {
      fld_e1 = v5;
      v5 = (int *)*v5;
    }
    else
    {
      v5 = (int *)v5[2];
    }
  }
  if ( fld_e1 == (uint32_t *)*(this + 1) || *pDwArg2 < fld_e1[3] )
  {
    v6 = sub_4FC9F0(v16);
    v8 = *pDwArg22;
    v22 = 0;
    sub_4FC970(&v9, v6);
    LOBYTE(v22) = 1;
    fld_e1 = (uint32_t *)*sub_4FCDD0((int)this, &pDwArg2, fld_e1, &v8);
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v14 = 0;
    v15 = 0;
    if ( v12 >= 0x10 )
      j__free(v10);
    v12 = 15;
    v11 = 0;
    LOBYTE(v10) = 0;
    if ( v19 != nullptr )
      j__free(v19);
    v19 = nullptr;
    v20 = 0;
    v21 = 0;
    if ( v18 >= 0x10 )
      j__free(v17);
  }
  return fld_e1 + 4;
}



// ============================================================
// §B 0x4FD000-0x4FE000 地图(场景)定义 + 副本定义族
// ============================================================

// ------------------------------------------------------------
// 0x4FD040 sub_4FD040 —— 副本(dungeon)定义解析器
//   标签族：[name]/[entering title]/[cutscene image]/[dungeon what must be cleared]/[area]
//   + 入口类型枚举 [normal]=?/[gate]/[fishing place]/[pub]/[dungeon gate]。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FD040(int *pDwArg1, const char *ArgList)
{
  const char *v2; // edi
  char result; // al
  int *pDwArg12; // ebx
  int v5; // ecx
  void **v6; // esi
  int nCmp; // eax
  int v8; // eax
  char *v9; // esi
  void **v10; // eax
  char v11; // [esp-1Ch] [ebp-ACh] BYREF
  void *v12; // [esp-18h] [ebp-A8h]
  int v13; // [esp-14h] [ebp-A4h]
  int v14; // [esp-10h] [ebp-A0h]
  char *v15; // [esp-Ch] [ebp-9Ch]
  char *v16; // [esp-8h] [ebp-98h]
  int *v17; // [esp-4h] [ebp-94h]
  int i; // [esp+Ch] [ebp-84h] BYREF
  char v19; // [esp+13h] [ebp-7Dh] BYREF
  int v20; // [esp+14h] [ebp-7Ch] BYREF
  char v21; // [esp+18h] [ebp-78h] BYREF
  void *v22; // [esp+1Ch] [ebp-74h]
  int v23; // [esp+2Ch] [ebp-64h]
  unsigned int v24; // [esp+30h] [ebp-60h]
  int v25; // [esp+34h] [ebp-5Ch]
  void *Block; // [esp+3Ch] [ebp-54h]
  void *Src; // [esp+40h] [ebp-50h]
  int v28; // [esp+44h] [ebp-4Ch]
  char v29[4]; // [esp+48h] [ebp-48h] BYREF
  void *v30; // [esp+4Ch] [ebp-44h]
  unsigned int v31; // [esp+5Ch] [ebp-34h]
  unsigned int v32; // [esp+60h] [ebp-30h]
  size_t v33; // [esp+64h] [ebp-2Ch] BYREF
  void *v34[4]; // [esp+68h] [ebp-28h] BYREF
  int v35; // [esp+78h] [ebp-18h]
  unsigned int v36; // [esp+7Ch] [ebp-14h]
  int dword_796E502; // [esp+80h] [ebp-10h]
  int v38; // [esp+8Ch] [ebp-4h]

  v2 = ArgList;
  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B6C78, (int)ArgList);
  if ( result == 0 )
    return result;
  pDwArg12 = pDwArg1;
  sub_4D1020(pDwArg1);
  sub_443300((int)(pDwArg1 + 27), "%s%s", (char)&unk_9B6C78);
  v36 = 15;
  v35 = 0;
  LOBYTE(v34[0]) = 0;
  v38 = 1;
  v32 = 15;
  v31 = 0;
  LOBYTE(v30) = 0;
  v19 = 0;
  sub_4FC9F0(&v20);
  LOBYTE(v38) = 2;
  if ( (uint8_t)sub_443430(&v33) == 0 )
    goto LABEL_43;
  do
  {
    sub_442B20(&v33);
    if ( v35 != 0 )
    {
      v5 = v35;
      if ( (unsigned int)v35 >= 6 )
        v5 = 6;
      v6 = (void **)v34[0];
      if ( v36 < 0x10 )
        v6 = v34;
      nCmp = memcmp((const char *)v6, "[name]", v5);
      if ( nCmp == 0 && (unsigned int)v35 >= 6 )
      {
        LOBYTE(nCmp) = v35 != 6;
        if ( nCmp == 0 )
        {
          pDwArg12 = pDwArg1;
          v17 = pDwArg1 + 1;
          sub_443370();
          continue;
        }
      }
      pDwArg12 = pDwArg1;
    }
    if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[entering title]", 0x10u) != 0 )
    {
      if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[cutscene image]", 0x10u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[dungeon what must be cleared]", 0x1Eu) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[area]", 6u) != 0 )
          {
            i = (int)&v11;
            v17 = (int *)15;
            v16 = nullptr;
            LOBYTE(v12) = 0;
            sub_4014D0((size_t *)&v11, &v33, 0, 0xFFFFFFFF);
            if ( (uint8_t)sub_442C80(v11, v12, v13, v14, (int)v15, (int)v16, (int)v17) == 0 )
            {
              v10 = (void **)v34[0];
              if ( v36 < 0x10 )
                v10 = v34;
              off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)v10);
            }
          }
          else
          {
            sub_4FC930(&v20);
            v20 = sub_4423D0(nullptr);
            v16 = &v21;
            sub_443370();
            v15 = v29;
            sub_443370();
            if ( sub_40BF00((std::_String_base *)v29, 0, v31, "[normal]", 8u) != 0 )
            {
              if ( (uint8_t)sub_423300(v29, "[gate]") != 0 )
              {
                v25 = 1;
              }
              else if ( (uint8_t)sub_423300(v29, "[fishing place]") != 0 )
              {
                v25 = 2;
              }
              else if ( (uint8_t)sub_423300(v29, "[pub]") != 0 )
              {
                v25 = 3;
              }
              else if ( (uint8_t)sub_423300(v29, "[dungeon gate]") != 0 )
              {
                v25 = 4;
              }
            }
            else
            {
              v25 = 0;
            }
            v8 = sub_4423D0(&v19);
            for ( i = v8; v19 != 0; i = v8 )
            {
              v9 = (char *)Src;
              if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v28 - (int)Block) >> 2) )
              {
                *(uint32_t *)Src = v8;
                Src = v9 + 4;
              }
              else
              {
                sub_430C80(Src, 1, (int)&i);
              }
              v8 = sub_4423D0(&v19);
            }
            v17 = &v20;
            sub_4FCF30(&v20);
            sub_4FCA80(v17);
          }
        }
        else
        {
          pDwArg12[23] = sub_4423D0(nullptr);
        }
      }
      else
      {
        v17 = pDwArg12 + 15;
        sub_443370();
        pDwArg12[22] = sub_4423D0(nullptr);
      }
    }
    else
    {
      v17 = pDwArg12 + 8;
      sub_443370();
    }
  }
  while ( (uint8_t)sub_443430(&v33) != 0 );
  v2 = ArgList;
LABEL_43:
  *pDwArg12 = sub_4A2F80(&dword_9B6D78, v2);
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  Src = nullptr;
  v28 = 0;
  if ( v24 >= 0x10 )
    j__free(v22);
  v24 = 15;
  v23 = 0;
  LOBYTE(v22) = 0;
  if ( v32 >= 0x10 )
    j__free(v30);
  v32 = 15;
  v31 = 0;
  LOBYTE(v30) = 0;
  if ( v36 >= 0x10 )
    j__free(v34[0]);
  return 1;
}


// ------------------------------------------------------------
// 0x4FD430 sub_4FD430
// ------------------------------------------------------------
bool /*cdecl*/ sub_4FD430(const char *pArg1, int nArg2)
{
  strcpy(byte_9B6D88, pArg1);
  if ( byte_9B6D87[strlen(byte_9B6D88)] != 92 && byte_9B6D87[strlen(byte_9B6D88)] != 47 )
    *(uint16_t *)&byte_9B6D88[strlen(byte_9B6D88)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B6E88, (char)byte_9B6D88, nArg2) != 0;
}



// ------------------------------------------------------------
// 0x4FD4C0 sub_4FD4C0 —— 地图(map)定义解析器
//   标签族：[name]/[map image]/[dungeon]；未识别标签打印 "SCRIPT TAG ERROR! [%s] %s"
//   （off_77F3FC —— 研究 20 §1.3 所述引擎错误输出口）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FD4C0(int pArg1, const char *ArgList)
{
  char result; // al
  uint32_t *v3; // esi
  unsigned int v4; // edx
  int v5; // ecx
  void **Block2; // esi
  int nCmp; // eax
  int i; // eax
  int v9; // eax
  int v10; // edx
  unsigned int v11; // ecx
  int v12; // esi
  void **Block3; // eax
  char v14; // [esp-1Ch] [ebp-64h] BYREF
  void **v15; // [esp-18h] [ebp-60h]
  int v16; // [esp-14h] [ebp-5Ch]
  int v17; // [esp-10h] [ebp-58h]
  int v18; // [esp-Ch] [ebp-54h]
  CHAR *v19; // [esp-8h] [ebp-50h]
  unsigned int v20; // [esp-4h] [ebp-4Ch]
  uint32_t v21[2]; // [esp+Ch] [ebp-3Ch] BYREF
  char *v22; // [esp+14h] [ebp-34h]
  char v23; // [esp+1Bh] [ebp-2Dh] BYREF
  uint8_t v24[4]; // [esp+1Ch] [ebp-2Ch] BYREF
  void *Block[4]; // [esp+20h] [ebp-28h] BYREF
  int v26; // [esp+30h] [ebp-18h]
  unsigned int v27; // [esp+34h] [ebp-14h]
  int dword_796E502; // [esp+38h] [ebp-10h]
  int v29; // [esp+44h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B6D88, (int)ArgList);
  if ( result != 0 )
  {
    v3 = (uint32_t *)pArg1;
    v20 = 0;
    v19 = (CHAR *)szPassword;
    *(uint32_t *)pArg1 = 0;
    sub_4015C0(v19, v20);  // 【std::string构造赋值】
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    *(uint32_t *)(pArg1 + 60) = 0;
    if ( *(uint32_t *)(pArg1 + 68) != 0 )
      j__free(*(void **)(pArg1 + 68));
    *(uint32_t *)(pArg1 + 68) = 0;
    *(uint32_t *)(pArg1 + 72) = 0;
    *(uint32_t *)(pArg1 + 76) = 0;
    v27 = 15;
    v26 = 0;
    LOBYTE(Block[0]) = 0;
    v29 = 0;
    v23 = 0;
    if ( (uint8_t)sub_443430(v24) != 0 )
    {
      while ( 1 )
      {
        sub_442B20(v24);
        v4 = v26;
        if ( v26 == 0 )
          goto LABEL_15;
        v5 = v26;
        if ( (unsigned int)v26 >= 6 )
          v5 = 6;
        Block2 = (void **)Block[0];
        if ( v27 < 0x10 )
          Block2 = Block;
        nCmp = memcmp((const char *)Block2, "[name]", v5);
        if ( nCmp != 0 )
          break;
        if ( (unsigned int)v26 < 6 )
          break;
        LOBYTE(nCmp) = v26 != 6;
        if ( nCmp != 0 )
          break;
        v20 = pArg1 + 4;
        sub_443370();
LABEL_34:
        if ( (uint8_t)sub_443430(v24) == 0 )
        {
          v3 = (uint32_t *)pArg1;
          goto LABEL_36;
        }
      }
      v4 = v26;
LABEL_15:
      if ( sub_40BF00((std::_String_base *)v24, 0, v4, "[map image]", 0xBu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v24, 0, v26, "[dungeon]", 9u) != 0 )
        {
          v22 = &v14;
          v20 = 15;
          v19 = nullptr;
          LOBYTE(v15) = 0;
          sub_4014D0((std::_String_base *)&v14, v24, 0, -1);
          if ( sub_442C80(v14, v15, v16, v17, v18, (int)v19, v20) == 0 )
          {
            Block3 = (void **)Block[0];
            if ( v27 < 0x10 )
              Block3 = Block;
            off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)Block3);
          }
        }
        else
        {
          if ( *(uint32_t *)(pArg1 + 68) != 0 )
            j__free(*(void **)(pArg1 + 68));
          v20 = (unsigned int)&v23;
          *(uint32_t *)(pArg1 + 68) = 0;
          *(uint32_t *)(pArg1 + 72) = 0;
          *(uint32_t *)(pArg1 + 76) = 0;
          for ( i = sub_4423D0((uint8_t *)v20); v23 != 0; i = sub_4423D0(&v23) )
          {
            v21[0] = i;
            v9 = sub_4423D0(nullptr);
            v10 = *(uint32_t *)(pArg1 + 68);
            v21[1] = v9;
            if ( v10 != 0 )
              v11 = (*(uint32_t *)(pArg1 + 72) - v10) >> 3;
            else
              v11 = 0;
            if ( v10 != 0 && v11 < (*(uint32_t *)(pArg1 + 76) - v10) >> 3 )
            {
              v12 = *(uint32_t *)(pArg1 + 72);
              v20 = (unsigned int)v22;
              v19 = (CHAR *)(pArg1 + 64);
              sub_63A7C0(v12, 1, v21);
              *(uint32_t *)(pArg1 + 72) = v12 + 8;
            }
            else
            {
              sub_473A80(pArg1 + 64, *(uint32_t *)(pArg1 + 72), 1u, (int)v21);
            }
          }
        }
      }
      else
      {
        v20 = pArg1 + 32;
        sub_443370();
        *(uint32_t *)(pArg1 + 60) = sub_4423D0(nullptr);
      }
      goto LABEL_34;
    }
LABEL_36:
    *v3 = sub_4A2F80(ArgList);
    if ( v27 >= 0x10 )
      j__free(Block[0]);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FD770 sub_4FD770
// ------------------------------------------------------------
bool /*cdecl*/ sub_4FD770(const char *pArg1, int nArg2)
{
  strcpy(byte_9B6E98, pArg1);
  if ( byte_9B6E97[strlen(byte_9B6E98)] != 92 && byte_9B6E97[strlen(byte_9B6E98)] != 47 )
    *(uint16_t *)&byte_9B6E98[strlen(byte_9B6E98)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B6F98, (char)byte_9B6E98, nArg2) != 0;
}



// ------------------------------------------------------------
// 0x4FD800 sub_4FD800
// ------------------------------------------------------------
int /*cdecl*/ sub_4FD800(int pArg1)
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 101) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x4FD820 sub_4FD820
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FD820(uint32_t *pArg1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 101) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 101) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FD840 sub_4FD840
// ------------------------------------------------------------
int /*thiscall*/ sub_4FD840(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 101) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 101) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 101) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 101) == 0 );
        if ( *(uint8_t *)(result + 101) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 101) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FD8A0 sub_4FD8A0
// ------------------------------------------------------------
int */*thiscall*/ sub_4FD8A0(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 101) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 101) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 101) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 101) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 101) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FD900 sub_4FD900
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FD900(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;
  if ( *(uint8_t *)(*result + 101) == 0 )
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
// 0x4FD960 sub_4FD960
// ------------------------------------------------------------
int /*thiscall*/ sub_4FD960(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 101) == 0 )
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
// 0x4FD9C0 sub_4FD9C0
// ------------------------------------------------------------
char /*stdcall*/ sub_4FD9C0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4FD9C0(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FDA00 sub_4FDA00
// ------------------------------------------------------------
void /*thiscall*/ sub_4FDA00(int this)
{
  if ( *(uint32_t *)(this + 72) != 0 )
    j__free(*(void **)(this + 72));
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  if ( *(uint32_t *)(this + 64) >= 0x10u )
    j__free(*(void **)(this + 44));
  *(uint32_t *)(this + 64) = 15;
  *(uint32_t *)(this + 60) = 0;
  *(uint8_t *)(this + 44) = 0;
  if ( *(uint32_t *)(this + 36) >= 0x10u )
    j__free(*(void **)(this + 16));
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 15;
  *(uint8_t *)(this + 16) = 0;
}



// ------------------------------------------------------------
// 0x4FDA60 sub_4FDA60
// ------------------------------------------------------------
void /*thiscall*/ sub_4FDA60(void *this)
{
  sub_4FDA00((int)this + 4);
}



// ------------------------------------------------------------
// 0x4FDA80 sub_4FDA80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FDA80(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
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
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
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
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);
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
// 0x4FDC30 sub_4FDC30
// ------------------------------------------------------------
int /*thiscall*/ sub_4FDC30(uint32_t *this, int pArg2, uint32_t *uArg3)
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
      v10 = *sub_4FDA80(this, &uArg3, 1, fld_e1, (int)uArg32);
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
    v12 = *sub_4FDA80(this, &uArg3, v13, fld_e1, (int)uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4FDCF0 sub_4FDCF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FDCF0(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_4FDA80((uint32_t *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4FDA80((uint32_t *)this, uArg2, 1, pArg3, (int)pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )
  {
    v8 = (uint32_t *)fld_4[2];
    if ( v8[3] < *pArg4 )
    {
      sub_4FDA80((uint32_t *)this, uArg2, 0, v8, (int)pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4A3B30(&pArg4), pArg4[3] >= *pArg42) )
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C5E0(&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4FDC30((uint32_t *)this, (int)v10, pArg42);
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 21) != 0 )
      sub_4FDA80((uint32_t *)this, uArg2, 0, pArg3, (int)pArg42);
    else
      sub_4FDA80((uint32_t *)this, uArg2, 1, pArg4, (int)pArg42);
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 21) != 0 )
      sub_4FDA80((uint32_t *)this, uArg2, 0, pArg4, (int)pArg42);
    else
      sub_4FDA80((uint32_t *)this, uArg2, 1, pArg3, (int)pArg42);
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4FDE50 sub_4FDE50
// ------------------------------------------------------------
char /*stdcall*/ sub_4FDE50(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 101);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4FDE50(i[2]);
    i = (void **)*i;
    sub_4FDA70(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 101);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FDEA0 sub_4FDEA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FDEA0(uint32_t *this, uint32_t *pArg2)
{
  char *pThis_3; // ecx

  *this = *pArg2;
  *(this + 1) = pArg2[1];
  pThis_3 = (char *)(this + 3);
  *(this + 2) = pArg2[2];
  *((uint32_t *)pThis_3 + 6) = 15;
  *((uint32_t *)pThis_3 + 5) = 0;
  pThis_3[4] = 0;
  sub_4014D0((std::_String_base *)pThis_3, pArg2 + 3, 0, -1);
  *(this + 16) = 15;
  *(this + 15) = 0;
  *((uint8_t *)this + 44) = 0;
  sub_4014D0((std::_String_base *)(this + 10), pArg2 + 10, 0, -1);
  sub_435020(pArg2 + 17);
  return this;
}



// ------------------------------------------------------------
// 0x4FDF40 sub_4FDF40
// ------------------------------------------------------------
char */*thiscall*/ sub_4FDF40(char *this)
{
  char *pThis_C; // ecx

  pThis_C = this + 12;
  *((uint32_t *)pThis_C + 6) = 15;
  *((uint32_t *)pThis_C + 5) = 0;
  pThis_C[4] = 0;
  *((uint32_t *)this + 16) = 15;
  *((uint32_t *)this + 15) = 0;
  *(this + 44) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 0;
  *((uint32_t *)this + 2) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  if ( *((uint32_t *)this + 18) != 0 )
    j__free(*((void **)this + 18));
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4FDFE0 sub_4FDFE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FDFE0(uint32_t *this, uint32_t *pArg2)
{
  *this = *pArg2;
  *(this + 1) = pArg2[1];
  *(this + 2) = pArg2[2];
  sub_4014D0((std::_String_base *)(this + 3), pArg2 + 3, 0, -1);
  sub_4014D0((std::_String_base *)(this + 10), pArg2 + 10, 0, -1);
  sub_4ED3F0((int)(this + 17), (int)(pArg2 + 17));
  return this;
}



// ------------------------------------------------------------
// 0x4FE030 sub_4FE030
// ------------------------------------------------------------
int /*thiscall*/ sub_4FE030(uint32_t *this, uint32_t *uArg2)
{
  uint32_t *fld_e1; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);
  v3 = (int *)fld_e1[1];
  while ( *((uint8_t *)v3 + 21) == 0 )
  {
    if ( v3[3] >= *uArg2 )
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
  return *sub_4FDCF0((int)this, &uArg2, fld_e1, v5) + 16;
}



// ------------------------------------------------------------
// 0x4FE0B0 sub_4FE0B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4FE0B0(uint32_t *this)
{
  char *pThis_35; // edi
  int i; // ebx
  uint32_t *fld_e70; // ebx
  uint32_t *fld_e702; // eax
  char *pThis_50; // edi
  uint32_t *fld_e100; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-4h]
  int Blocka; // [esp+Ch] [ebp-4h]

  *this = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 22) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 30) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 38) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_35 = (char *)(this + 53);
  for ( i = 2; i != 0; --i )
  {
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pThis_35 += 28;
  }
  *((uint8_t *)this + 268) = 1;
  fld_e70 = *(uint32_t **)(*(this + 70) + 4);
  for ( Block = fld_e70; *((uint8_t *)fld_e70 + 21) == 0; Block = fld_e70 )
  {
    sub_4FD9C0((void **)fld_e70[2]);
    fld_e70 = (uint32_t *)*fld_e70;
    j__free(Block);
  }
  *(uint32_t *)(*(this + 70) + 4) = *(this + 70);
  fld_e702 = (uint32_t *)*(this + 70);
  *(this + 71) = 0;
  *fld_e702 = fld_e702;
  *(uint32_t *)(*(this + 70) + 8) = *(this + 70);
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_50 = (char *)(this + 80);
  for ( Blocka = 5; Blocka != 0; --Blocka )
  {
    if ( *(uint32_t *)pThis_50 != 0 )
      j__free(*(void **)pThis_50);
    *(uint32_t *)pThis_50 = 0;
    *((uint32_t *)pThis_50 + 1) = 0;
    *((uint32_t *)pThis_50 + 2) = 0;
    pThis_50 += 16;
  }
  sub_4FDE50(*(void ***)(*(this + 100) + 4));
  *(uint32_t *)(*(this + 100) + 4) = *(this + 100);
  fld_e100 = (uint32_t *)*(this + 100);
  *(this + 101) = 0;
  *fld_e100 = fld_e100;
  *(uint32_t *)(*(this + 100) + 8) = *(this + 100);
  result = sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 68) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x4FE240 sub_4FE240
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4FE240(int nArg1, int nArg2, int nArg3, uint32_t *pArg4, char pszArg5)
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  pMem = operator new(0x68u);
  pMem2 = pMem;
  v8[4] = pMem;
  v8[8] = (void *)1;
  v8[3] = pMem;
  if ( pMem != nullptr )
  {
    *pMem = nArg1;
    pMem[1] = nArg2;
    pMem[2] = nArg3;
    pMem[3] = *pArg4;
    sub_4FDEA0(pMem + 4, pArg4 + 1);
    *((uint8_t *)pMem2 + 100) = pszArg5;
    *((uint8_t *)pMem2 + 101) = 0;
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x4FE2E0 sub_4FE2E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FE2E0(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
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
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  int fld_e15; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x2E8BA2Du )
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_4FE240(*(this + 1), pArg4, *(this + 1), nArg5, 0);
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
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 100) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 100) != 0 )
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_4FD900(*v10);
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 100) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 100) = 0;
          sub_4FD960(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 100) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4FD960(*v10);
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 100) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 100) = 0;
        sub_4FD900(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 100) = 1;
      *(uint8_t *)(v14 + 100) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 100) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 100) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 100) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4FE490 sub_4FE490
// ------------------------------------------------------------
int /*thiscall*/ sub_4FE490(int *this, int pArg2, uint32_t *uArg3)
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
  if ( *((uint8_t *)v6 + 101) == 0 )
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
    while ( *((uint8_t *)v6 + 101) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_4FE2E0(this, &uArg3, 1, fld_e1, uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4FD840(&uArg3);
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
    v12 = *sub_4FE2E0(this, &uArg3, v13, fld_e1, uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4FE550 sub_4FE550
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FE550(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_4FE2E0((int *)this, uArg2, 1, *(uint32_t **)(this + 4), pArg4);
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4FE2E0((int *)this, uArg2, 1, pArg3, pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )
  {
    v8 = (uint32_t *)fld_4[2];
    if ( v8[3] < *pArg4 )
    {
      sub_4FE2E0((int *)this, uArg2, 0, v8, pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4FD840(&pArg4), pArg4[3] >= *pArg42) )
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_4FD8A0((int *)&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4FE490((int *)this, (int)v10, pArg42);
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 101) != 0 )
      sub_4FE2E0((int *)this, uArg2, 0, pArg3, pArg42);
    else
      sub_4FE2E0((int *)this, uArg2, 1, pArg4, pArg42);
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 101) != 0 )
      sub_4FE2E0((int *)this, uArg2, 0, pArg4, pArg42);
    else
      sub_4FE2E0((int *)this, uArg2, 1, pArg3, pArg42);
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4FE6B0 sub_4FE6B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FE6B0(uint32_t *this, int *pDwArg2)
{
  int *pDwArg22; // ebx
  uint32_t *fld_e1; // ecx
  int *v5; // eax
  uint32_t *fld_e12; // esi
  char *v7; // eax
  char v9[84]; // [esp+Ch] [ebp-B8h] BYREF
  int v10; // [esp+60h] [ebp-64h] BYREF
  uint32_t v11[21]; // [esp+64h] [ebp-60h] BYREF
  int v12; // [esp+C0h] [ebp-4h]

  pDwArg22 = pDwArg2;
  fld_e1 = (uint32_t *)*(this + 1);
  v5 = (int *)fld_e1[1];
  fld_e12 = fld_e1;
  while ( *((uint8_t *)v5 + 101) == 0 )
  {
    if ( v5[3] >= *pDwArg2 )
    {
      fld_e12 = v5;
      v5 = (int *)*v5;
    }
    else
    {
      v5 = (int *)v5[2];
    }
  }
  if ( fld_e12 == (uint32_t *)*(this + 1) || *pDwArg2 < fld_e12[3] )
  {
    v7 = sub_4FDF40(v9);
    v10 = *pDwArg22;
    v12 = 0;
    sub_4FDEA0(v11, v7);
    LOBYTE(v12) = 1;
    fld_e12 = (uint32_t *)*sub_4FE550((int)this, &pDwArg2, fld_e12, &v10);
    sub_4FDA00((int)v11);
    sub_4FDA00((int)v9);
  }
  return fld_e12 + 4;
}



// ============================================================
// §C 0x4FE000-0x4FF800 场地/NPC 定义族
// ============================================================

// ------------------------------------------------------------
// 0x4FE770 sub_4FE770 —— NPC(场地角色)定义解析器
//   标签族：资源 [name]/[field name]/[small face]/[big face]/[popup face]/[field animation]/
//   [field wav]/[popup wav]；行为开关 [look around]；角色职能枚举（[role] 子串：
//   [item shop]=0/[recover stamina]=1/[sera shop]=2/[guild]=3/[upgrade item]=4/[disjoint item]=5/
//   [product item]=6/[item storage]=7/[post box]=8）；[quest speech]/[skill]/[speech] 资源列表；
//   队伍枚举 [chaos team]/[red team]=0/[blue team]=1/[neutral team]=200（+272）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FE770(int pArg1, const char *ArgList)
{
  char result; // al
  int pArg12; // edi
  int v4; // ecx
  void **v5; // esi
  int nCmp; // eax
  int *v7; // esi
  int v8; // eax
  int v9; // eax
  void *p_Block; // eax
  void **v11; // esi
  void **v12; // eax
  void **v13[2]; // [esp-1Ch] [ebp-CCh] BYREF
  char *v14; // [esp-14h] [ebp-C4h]
  char *v15; // [esp-10h] [ebp-C0h]
  int v16; // [esp-Ch] [ebp-BCh]
  uint8_t *v17; // [esp-8h] [ebp-B8h]
  int *i; // [esp-4h] [ebp-B4h]
  int j; // [esp+Ch] [ebp-A4h] BYREF
  char v20; // [esp+13h] [ebp-9Dh] BYREF
  int v21[3]; // [esp+14h] [ebp-9Ch] BYREF
  char v22; // [esp+20h] [ebp-90h] BYREF
  char v23; // [esp+3Ch] [ebp-74h] BYREF
  void *v24[4]; // [esp+58h] [ebp-58h] BYREF
  uint8_t v25[4]; // [esp+68h] [ebp-48h] BYREF
  void *Block; // [esp+6Ch] [ebp-44h] BYREF
  int v27; // [esp+7Ch] [ebp-34h]
  unsigned int v28; // [esp+80h] [ebp-30h]
  int v29; // [esp+84h] [ebp-2Ch] BYREF
  void *v30[4]; // [esp+88h] [ebp-28h] BYREF
  int v31; // [esp+98h] [ebp-18h]
  unsigned int v32; // [esp+9Ch] [ebp-14h]
  int dword_796E502; // [esp+A0h] [ebp-10h]
  int v34; // [esp+ACh] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B6E98, (int)ArgList);
  if ( result != 0 )
  {
    pArg12 = pArg1;
    sub_4FE0B0(pArg1);
    i = (int *)ArgList;
    sub_443300(pArg1 + 408, "%s%s", (char)&unk_9B6E98);
    v32 = 15;
    v31 = 0;
    LOBYTE(v30[0]) = 0;
    v34 = 1;
    v28 = 15;
    v27 = 0;
    LOBYTE(Block) = 0;
    v20 = 0;
    if ( (uint8_t)sub_443430(&v29) != 0 )
    {
      while ( 1 )
      {
        sub_442B20(&v29);
        if ( v31 == 0 )
          goto LABEL_13;
        v4 = v31;
        if ( (unsigned int)v31 >= 6 )
          v4 = 6;
        v5 = (void **)v30[0];
        if ( v32 < 0x10 )
          v5 = v30;
        nCmp = memcmp((const char *)v5, "[name]", v4);
        if ( nCmp != 0 )
          break;
        if ( (unsigned int)v31 < 6 )
          break;
        LOBYTE(nCmp) = v31 != 6;
        if ( nCmp != 0 )
          break;
        pArg12 = pArg1;
        i = (int *)(pArg1 + 4);
        sub_443370();
LABEL_77:
        if ( (uint8_t)sub_443430(&v29) == 0 )
          goto LABEL_78;
      }
      pArg12 = pArg1;
LABEL_13:
      if ( sub_40BF00((std::_String_base *)&v29, 0, v31, "[field name]", 0xCu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)&v29, 0, v31, "[small face]", 0xCu) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)&v29, 0, v31, "[big face]", 0xAu) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)&v29, 0, v31, "[popup face]", 0xCu) != 0 )
            {
              if ( sub_40BF00((std::_String_base *)&v29, 0, v31, "[field animation]", 0x11u) != 0 )
              {
                if ( (uint8_t)sub_423300(&v29, "[field wav]") != 0 )
                {
                  i = (int *)(pArg12 + 184);
                  sub_443370();
                }
                else if ( (uint8_t)sub_423300(&v29, "[popup wav]") != 0 )
                {
                  i = (int *)(pArg12 + 212);
                  sub_443370();
                  v17 = (uint8_t *)(pArg12 + 240);
                  sub_443370();
                }
                else if ( (uint8_t)sub_423300(&v29, "[look around]") != 0 )
                {
                  *(uint8_t *)(pArg12 + 268) = sub_4423D0(nullptr) != 0;
                }
                else if ( (uint8_t)sub_423300(&v29, "[role]") != 0 )
                {
                  for ( i = (int *)v25; sub_443370() != 0; *v7 = v8 )
                  {
                    j = 0;
                    if ( (uint8_t)sub_423300(v25, "[item shop]") != 0 )
                    {
                      j = 0;
                    }
                    else if ( (uint8_t)sub_423300(v25, "[recover stamina]") != 0 )
                    {
                      j = 1;
                    }
                    else if ( (uint8_t)sub_423300(v25, "[sera shop]") != 0 )
                    {
                      j = 2;
                    }
                    else if ( (uint8_t)sub_423300(v25, "[guild]") != 0 )
                    {
                      j = 3;
                    }
                    else if ( (uint8_t)sub_423300(v25, "[upgrade item]") != 0 )
                    {
                      j = 4;
                    }
                    else if ( (uint8_t)sub_423300(v25, "[disjoint item]") != 0 )
                    {
                      j = 5;
                    }
                    else if ( (uint8_t)sub_423300(v25, "[product item]") != 0 )
                    {
                      j = 6;
                    }
                    else if ( (uint8_t)sub_423300(v25, "[item storage]") != 0 )
                    {
                      j = 7;
                    }
                    else if ( (uint8_t)sub_423300(v25, "[post box]") != 0 )
                    {
                      j = 8;
                    }
                    v7 = (int *)sub_4FE030(&j);
                    v8 = sub_4423D0(nullptr);
                    v17 = v25;
                  }
                }
                else if ( (uint8_t)sub_423300(&v29, "[quest speech]") != 0 )
                {
                  i = (int *)(pArg12 + 288);
                  sub_443370();
                }
                else if ( (uint8_t)sub_423300(&v29, "[skill]") != 0 )
                {
                  i = (int *)v25;
                  sub_443370();
                  if ( (uint8_t)sub_423300(v25, "[common]") != 0 )
                  {
                    v9 = 4;
                  }
                  else
                  {
                    p_Block = Block;
                    if ( v28 < 0x10 )
                      p_Block = &Block;
                    v9 = sub_4426A0(p_Block);  // 【职业标签→索引（[swordman]/[fighter]/[gunner]/[mag…】
                  }
                  v11 = (void **)(16 * v9 + pArg12 + 316);
                  sub_5E5260(v11);
                  for ( j = sub_4423D0(&v20); v20 != 0; j = sub_4423D0(&v20) )
                    sub_431230((int)v11, &j);
                }
                else if ( (uint8_t)sub_423300(&v29, "[speech]") != 0 )
                {
                  sub_4FDF40((char *)v21);
                  LOBYTE(v34) = 2;
                  v21[0] = sub_4423D0(nullptr);
                  v21[1] = sub_4423D0(nullptr);
                  v21[2] = sub_4423D0(nullptr);
                  v15 = &v22;
                  sub_443370();
                  v14 = &v23;
                  sub_443370();
                  sub_5E5260(v24);
                  for ( j = sub_4423D0(&v20); v20 != 0; j = sub_4423D0(&v20) )
                    sub_431230((int)v24, &j);
                  i = v21;
                  sub_4FE6B0((int **)(pArg12 + 396), v21);
                  sub_4FDFE0(i);
                  LOBYTE(v34) = 1;
                  sub_4FDA00(v21);
                }
                else if ( (uint8_t)sub_423300(&v29, "[chaos team]") != 0 )
                {
                  i = (int *)v25;
                  sub_443370();
                  if ( (uint8_t)sub_423300(v25, "[red team]") != 0 )
                  {
                    *(uint32_t *)(pArg12 + 272) = 0;
                  }
                  else if ( (uint8_t)sub_423300(v25, "[blue team]") != 0 )
                  {
                    *(uint32_t *)(pArg12 + 272) = 1;
                  }
                  else if ( (uint8_t)sub_423300(v25, "[neutral team]") != 0 )
                  {
                    *(uint32_t *)(pArg12 + 272) = 200;
                  }
                }
                else
                {
                  j = (int)v13;
                  sub_401690(&v29);
                  if ( sub_442C80((char)v13[0], v13[1], (int)v14, (int)v15, v16, (int)v17, (unsigned int)i) == 0 )
                  {
                    v12 = (void **)v30[0];
                    if ( v32 < 0x10 )
                      v12 = v30;
                    off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)v12);
                  }
                }
              }
              else
              {
                i = (int *)(pArg12 + 156);
                sub_443370();
              }
            }
            else
            {
              i = (int *)(pArg12 + 124);
              sub_443370();
              *(uint32_t *)(pArg12 + 152) = sub_4423D0(nullptr);
            }
          }
          else
          {
            i = (int *)(pArg12 + 92);
            sub_443370();
            *(uint32_t *)(pArg12 + 120) = sub_4423D0(nullptr);
          }
        }
        else
        {
          i = (int *)(pArg12 + 60);
          sub_443370();
          *(uint32_t *)(pArg12 + 88) = sub_4423D0(nullptr);
        }
      }
      else
      {
        i = (int *)(pArg12 + 32);
        sub_443370();
      }
      goto LABEL_77;
    }
LABEL_78:
    *(uint32_t *)pArg12 = sub_4A2F80(ArgList);
    if ( v28 >= 0x10 )
      j__free(Block);
    v28 = 15;
    v27 = 0;
    LOBYTE(Block) = 0;
    if ( v32 >= 0x10 )
      j__free(v30[0]);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FEEA0 sub_4FEEA0
// ------------------------------------------------------------
bool /*cdecl*/ sub_4FEEA0(const char *pArg1, int nArg2)
{
  strcpy(byte_9B6FA8, pArg1);
  if ( byte_9B6FA7[strlen(byte_9B6FA8)] != 92 && byte_9B6FA7[strlen(byte_9B6FA8)] != 47 )
    *(uint16_t *)&byte_9B6FA8[strlen(byte_9B6FA8)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B70A8, (char)byte_9B6FA8, nArg2) != 0;
}



// ------------------------------------------------------------
// 0x4FEF30 sub_4FEF30
// ------------------------------------------------------------
int /*thiscall*/ sub_4FEF30(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 24;
  return result;
}



// ------------------------------------------------------------
// 0x4FEF50 sub_4FEF50
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FEF50(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *v4; // edi

  for ( result = uArg1; result != uArg2; v4[5] = pArg3[5] )
  {
    v4 = result;
    *result = *pArg3;
    result[1] = pArg3[1];
    result[2] = pArg3[2];
    result[3] = pArg3[3];
    result[4] = pArg3[4];
    result += 6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FEFA0 sub_4FEFA0
// ------------------------------------------------------------
char */*cdecl*/ sub_4FEFA0(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  void *v4; // edi

  for ( result = pszArg1; result != pszArg2; result += 28 )
  {
    v4 = result;
    qmemcpy(v4, pArg3, 0x1Cu);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FEFD0 sub_4FEFD0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FEFD0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg22; // ecx
  uint32_t *result; // eax

  uArg22 = uArg2;
  for ( result = uArg3; uArg22 != uArg1; result[5] = uArg22[5] )
  {
    uArg22 -= 6;
    result -= 6;
    *result = *uArg22;
    result[1] = uArg22[1];
    result[2] = uArg22[2];
    result[3] = uArg22[3];
    result[4] = uArg22[4];
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FF020 sub_4FF020
// ------------------------------------------------------------
char */*cdecl*/ sub_4FF020(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg22; // edx
  char *result; // eax

  pszArg22 = pszArg2;
  result = pszArg3;
  while ( pszArg22 != pszArg1 )
  {
    pszArg22 -= 28;
    result -= 28;
    qmemcpy(result, pszArg22, 0x1Cu);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FF050 sub_4FF050
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FF050(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; result += 6 )
  {
    if ( result != nullptr )
    {
      *result = *uArg12;
      result[1] = uArg12[1];
      result[2] = uArg12[2];
      result[3] = uArg12[3];
      result[4] = uArg12[4];
      result[5] = uArg12[5];
    }
    uArg12 += 6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FF0A0 sub_4FF0A0
// ------------------------------------------------------------
char */*cdecl*/ sub_4FF0A0(char *pszArg1, char *pszArg2, const void *pArg3)
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
        qmemcpy(result, pArg3, 0x1Cu);
      result += 28;
      --pszArg22;
    }
    while ( pszArg22 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FF0D0 sub_4FF0D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4FF0D0(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)
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
      sub_4CEAB0(this);
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
// 0x4FF3A0 sub_4FF3A0
// ------------------------------------------------------------
void /*thiscall*/ sub_4FF3A0(int *this, char *pszArg2, unsigned int uArg3, void *Block)
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
  char *fld_e23; // ecx
  int fld_e26; // edx
  int fld_e12; // [esp-18h] [ebp-50h]
  int fld_e25; // [esp-Ch] [ebp-44h]
  unsigned int fld_e24; // [esp-8h] [ebp-40h]
  int v21; // [esp+0h] [ebp-38h] BYREF
  uint32_t v22[8]; // [esp+Ch] [ebp-2Ch] BYREF
  int v23; // [esp+34h] [ebp-4h]
  char *v24; // [esp+40h] [ebp+8h]
  char *v25; // [esp+44h] [ebp+Ch]
  char *Blocka; // [esp+48h] [ebp+10h]
  char *Blockb; // [esp+48h] [ebp+10h]

  qmemcpy(v22, Block, 0x1Cu);
  fld_e1 = *(this + 1);
  v22[7] = &v21;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 28;
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - *(this + 1)) / 28;
    else
      fld_e2 = 0;
    if ( 153391689 - fld_e2 < uArg3 )
      sub_4CEAB0(this);
    if ( *(this + 1) != 0 )
      fld_e22 = (*(this + 2) - *(this + 1)) / 28;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (char *)*(this + 2);
      Blockb = fld_e23;
      if ( (fld_e23 - pszArg2) / 28 >= uArg3 )
      {
        v24 = &fld_e23[-28 * uArg3];
        *(this + 2) = sub_472DB0(v24, fld_e23, fld_e23);
        sub_4FF020(pszArg2, v24, Blockb);
        sub_4FEFA0(pszArg2, &pszArg2[28 * uArg3], v22);
      }
      else
      {
        sub_472DB0(pszArg2, fld_e23, &pszArg2[28 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 28;
        fld_e25 = *(this + 2);
        v23 = 2;
        sub_488E00(fld_e25, fld_e24, v22);
        fld_e26 = 28 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        sub_4FEFA0(pszArg2, (char *)(fld_e26 - 28 * uArg3), v22);
      }
    }
    else
    {
      if ( 153391689 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        fld_e27 = (*(this + 2) - *(this + 1)) / 28;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_52AEF0(this);
      v12 = 28 * v10;
      Blocka = (char *)operator new(28 * v10);
      fld_e12 = *(this + 1);
      v23 = 0;
      v25 = (char *)sub_472DB0(fld_e12, pszArg2, Blocka);
      sub_4FF0A0(v25, (char *)uArg3, v22);
      sub_472DB0(pszArg2, *(this + 2), &v25[28 * uArg3]);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 28;
      v14 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v12];
      *(this + 2) = (int)&Blocka[28 * v14];
      *(this + 1) = (int)Blocka;
    }
  }
}



// ------------------------------------------------------------
// 0x4FF670 sub_4FF670
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FF670(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 24;
  else
    v6 = 0;
  sub_4FF0D0(this, pszArg3, 1u, Block);
  *uArg2 = *(this + 1) + 24 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4FF6E0 sub_4FF6E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FF6E0(int *this, uint32_t *uArg2, char *pszArg3, void *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 28 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 28;
  else
    v6 = 0;
  sub_4FF3A0(this, pszArg3, 1u, Block);
  *uArg2 = *(this + 1) + 28 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4FF750 sub_4FF750
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FF750(int this, uint32_t *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  int fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 24;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 24 )
    return sub_4FF670((int *)this, &Block, *(char **)(this + 8), Block);
  fld_82 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_5044B0(fld_82, 1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 24;
  return result;
}



// ------------------------------------------------------------
// 0x4FF7E0 sub_4FF7E0
// ------------------------------------------------------------
char */*thiscall*/ sub_4FF7E0(int this, void *Block)
{
  int fld_4; // ebx
  unsigned int fld_8; // esi
  char *fld_82; // esi
  char *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 28;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 28 )
    return (char *)sub_4FF6E0((int *)this, &Block, *(char **)(this + 8), Block);
  fld_82 = *(char **)(this + 8);
  result = sub_4FF0A0(fld_82, (char *)1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 28;
  return result;
}



// ============================================================
// §D 0x4FF800-0x504000 任务(quest)定义族 + 对象创建定义(sub_500B30) + 技能定义解析器(sub_502F00)
// ============================================================

// ------------------------------------------------------------
// 0x4FF870 sub_4FF870 —— 任务(quest)定义解析器
//   标签族：文本 [name]/[depend message]/[condition message]/[solve message]/[grade]；
//   前置 [job change quest]/[pre required quest]/[collision quest]/[relation quest]；
//   条件 [level]/[job]/[grow type]/[exceptional grow type]/[PVP RANK]/[pvp rank]；
//   报酬 [clear reward item]/[monster reward item]/[depend give item]/[reward int data]/
//   [reward type]（子枚举 [item]=0/[grow type]=1）；目标完成方式 [type]/[seeking] 枚举
//   [condition under clear]=0/[hunt monster]=1/[clear map]=2/[meet npc]=3/[pvp rank]=4；
//   稀有度 [normaly repeat]/[common unique]=1/[epic]=2（a1[29]）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FF870(int *pDwArg1, const char *ArgList)
{
  char result; // al
  unsigned int v3; // edx
  int v4; // ecx
  void **v5; // esi
  int nCmp; // eax
  void *p_Block; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int j; // eax
  void **v13; // eax
  void *v14[3]; // [esp-1Ch] [ebp-C4h] BYREF
  uint8_t *v15; // [esp-10h] [ebp-B8h]
  uint8_t *v16; // [esp-Ch] [ebp-B4h]
  uint8_t *v17; // [esp-8h] [ebp-B0h]
  const char *v18; // [esp-4h] [ebp-ACh]
  uint32_t v19[2]; // [esp+Ch] [ebp-9Ch] BYREF
  void *pBuf[4]; // [esp+14h] [ebp-94h] BYREF
  int v21; // [esp+24h] [ebp-84h] BYREF
  int v22; // [esp+28h] [ebp-80h]
  int v23; // [esp+2Ch] [ebp-7Ch]
  int v24; // [esp+30h] [ebp-78h]
  int v25; // [esp+34h] [ebp-74h]
  int v26; // [esp+38h] [ebp-70h]
  int v27; // [esp+3Ch] [ebp-6Ch]
  int v28; // [esp+40h] [ebp-68h] BYREF
  int v29; // [esp+44h] [ebp-64h]
  int v30; // [esp+48h] [ebp-60h]
  int v31; // [esp+4Ch] [ebp-5Ch]
  int v32; // [esp+50h] [ebp-58h]
  int v33; // [esp+54h] [ebp-54h]
  void **i; // [esp+58h] [ebp-50h] BYREF
  char v35; // [esp+5Fh] [ebp-49h] BYREF
  uint8_t v36[4]; // [esp+60h] [ebp-48h] BYREF
  void *Block; // [esp+64h] [ebp-44h] BYREF
  unsigned int v38; // [esp+74h] [ebp-34h]
  unsigned int v39; // [esp+78h] [ebp-30h]
  int v40; // [esp+7Ch] [ebp-2Ch] BYREF
  void *v41[4]; // [esp+80h] [ebp-28h] BYREF
  int v42; // [esp+90h] [ebp-18h]
  unsigned int v43; // [esp+94h] [ebp-14h]
  int dword_796E502; // [esp+98h] [ebp-10h]
  int v45; // [esp+A4h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B6FA8, (int)ArgList);
  if ( result != 0 )
  {
    sub_4D0D00(pDwArg1);
    v43 = 15;
    v42 = 0;
    LOBYTE(v41[0]) = 0;
    v45 = 1;
    v39 = 15;
    v38 = 0;
    LOBYTE(Block) = 0;
    v35 = 0;
    if ( (uint8_t)sub_443430(&v40) != 0 )
    {
      while ( 1 )
      {
        sub_442B20(&v40);
        v3 = v42;
        if ( v42 == 0 )
          goto LABEL_13;
        v4 = v42;
        if ( (unsigned int)v42 >= 6 )
          v4 = 6;
        v5 = (void **)v41[0];
        if ( v43 < 0x10 )
          v5 = v41;
        nCmp = memcmp((const char *)v5, "[name]", v4);
        if ( nCmp != 0 )
          break;
        if ( (unsigned int)v42 < 6 )
          break;
        LOBYTE(nCmp) = v42 != 6;
        if ( nCmp != 0 )
          break;
        v18 = (const char *)(pDwArg1 + 1);
        sub_443370();
LABEL_108:
        if ( (uint8_t)sub_443430(&v40) == 0 )
          goto LABEL_109;
      }
      v3 = v42;
LABEL_13:
      if ( sub_40BF00((std::_String_base *)&v40, 0, v3, "[depend message]", 0x10u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)&v40, 0, v42, "[condition message]", 0x13u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)&v40, 0, v42, "[solve message]", 0xFu) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)&v40, 0, v42, "[grade]", 7u) != 0 )
            {
              if ( sub_40BF00((std::_String_base *)&v40, 0, v42, "[job change quest]", 0x12u) != 0 )
              {
                if ( (uint8_t)sub_423300(&v40, "[npc index]") != 0 )
                {
                  pDwArg1[31] = sub_4423D0(nullptr);
                }
                else if ( (uint8_t)sub_423300(&v40, "[complete npc index]") != 0 )
                {
                  pDwArg1[32] = sub_4423D0(nullptr);
                }
                else if ( (uint8_t)sub_423300(&v40, "[job]") != 0 )
                {
                  v18 = v36;
                  sub_443370();
                  p_Block = Block;
                  if ( v39 < 0x10 )
                    p_Block = &Block;
                  pDwArg1[33] = sub_4426A0(p_Block);  // 【职业标签→索引（[swordman]/[fighter]/[gunner]/[mag…】
                }
                else if ( (uint8_t)sub_423300(&v40, "[grow type]") != 0 )
                {
                  pDwArg1[34] = sub_4423D0(nullptr);
                }
                else if ( (uint8_t)sub_423300(&v40, "[exceptional grow type]") != 0 )
                {
                  sub_5E5260((void **)pDwArg1 + 35);
                  for ( i = (void **)sub_4423D0(&v35); v35 != 0; i = (void **)sub_4423D0(&v35) )
                    sub_431230((int)(pDwArg1 + 35), &i);
                }
                else if ( (uint8_t)sub_423300(&v40, "[level]") != 0 )
                {
                  v8 = sub_4423D0(nullptr);
                  v17 = nullptr;
                  pDwArg1[39] = v8;
                  pDwArg1[40] = sub_4423D0(v17);
                }
                else if ( (uint8_t)sub_423300(&v40, "[pre required quest]") != 0 )
                {
                  memset(&pBuf[1], 0, 12);
                  LOBYTE(v45) = 2;
                  for ( i = (void **)sub_4423D0(&v35); v35 != 0; i = (void **)sub_4423D0(&v35) )
                    sub_431230((int)pBuf, &i);
                  if ( !sub_484F10(pBuf) )
                    sub_475190((int)(pDwArg1 + 41), pBuf);
                  LOBYTE(v45) = 1;
                  sub_5E5260(pBuf);
                }
                else if ( (uint8_t)sub_423300(&v40, "[collision quest]") != 0 )
                {
                  sub_5E5260((void **)pDwArg1 + 45);
                  for ( i = (void **)sub_4423D0(&v35); v35 != 0; i = (void **)sub_4423D0(&v35) )
                    sub_431230((int)(pDwArg1 + 45), &i);
                }
                else if ( (uint8_t)sub_423300(&v40, "[PVP RANK]") != 0 )
                {
                  pDwArg1[49] = sub_4423D0(nullptr);
                }
                else if ( (uint8_t)sub_423300(&v40, "[effect after clear quest]") != 0 )
                {
                  *((uint8_t *)pDwArg1 + 200) = sub_4423D0(nullptr) != 0;
                }
                else if ( (uint8_t)sub_423300(&v40, "[delete npc index]") != 0 )
                {
                  pDwArg1[51] = sub_4423D0(nullptr);
                }
                else if ( (uint8_t)sub_423300(&v40, "[clear reward item]") != 0 )
                {
                  sub_5E5260((void **)pDwArg1 + 52);
                  while ( 1 )
                  {
                    v29 = -1;
                    v30 = 0;
                    v31 = 0;
                    v32 = 0;
                    v33 = -1;
                    v28 = sub_4423D0(&v35);
                    if ( v35 == 0 )
                      break;
                    v29 = sub_4423D0(nullptr);
                    v30 = sub_4423D0(nullptr);
                    v31 = sub_4423D0(nullptr);
                    v32 = sub_4423D0(nullptr);
                    v33 = sub_4423D0(nullptr);
                    sub_4FF750(&v28);
                  }
                }
                else if ( (uint8_t)sub_423300(&v40, "[monster reward item]") != 0 )
                {
                  sub_5E5260((void **)pDwArg1 + 56);
                  while ( 1 )
                  {
                    v22 = -1;
                    v23 = -1;
                    v24 = 0;
                    v25 = 0;
                    v26 = 0;
                    v27 = -1;
                    v21 = sub_4423D0(&v35);
                    if ( v35 == 0 )
                      break;
                    v22 = sub_4423D0(nullptr);
                    v23 = sub_4423D0(nullptr);
                    v24 = sub_4423D0(nullptr);
                    v25 = sub_4423D0(nullptr);
                    v26 = sub_4423D0(nullptr);
                    v27 = sub_4423D0(nullptr);
                    sub_4FF7E0(&v21);
                  }
                }
                else if ( (uint8_t)sub_423300(&v40, "[appear map]") != 0 )
                {
                  v9 = sub_4423D0(nullptr);
                  v17 = nullptr;
                  pDwArg1[60] = v9;
                  v10 = sub_4423D0(v17);
                  v16 = nullptr;
                  pDwArg1[61] = v10;
                  v11 = sub_4423D0(v16);
                  v15 = nullptr;
                  pDwArg1[62] = v11;
                  pDwArg1[63] = sub_4423D0(v15);
                }
                else if ( (uint8_t)sub_423300(&v40, "[depend give item]") != 0 )
                {
                  sub_5E5260((void **)pDwArg1 + 64);
                  for ( j = sub_4423D0(&v35); v35 != 0; j = sub_4423D0(&v35) )
                  {
                    v19[0] = j;
                    v19[1] = sub_4423D0(nullptr);
                    sub_474950(v19);
                  }
                }
                else if ( (uint8_t)sub_423300(&v40, "[type]") != 0 )
                {
                  v18 = v36;
                  sub_443370();
                  if ( (uint8_t)sub_423300(v36, "[seeking]") != 0 )
                  {
                    pDwArg1[68] = 0;
                  }
                  else if ( (uint8_t)sub_423300(v36, "[condition under clear]") != 0 )
                  {
                    pDwArg1[68] = 1;
                  }
                  else if ( (uint8_t)sub_423300(v36, "[hunt monster]") != 0 )
                  {
                    pDwArg1[68] = 2;
                  }
                  else if ( (uint8_t)sub_423300(v36, "[clear map]") != 0 )
                  {
                    pDwArg1[68] = 3;
                  }
                  else if ( (uint8_t)sub_423300(v36, "[meet npc]") != 0 )
                  {
                    pDwArg1[68] = 4;
                  }
                  else if ( (uint8_t)sub_423300(v36, "[pvp rank]") != 0 )
                  {
                    pDwArg1[68] = 5;
                  }
                }
                else if ( (uint8_t)sub_423300(&v40, "[sub type]") != 0 )
                {
                  pDwArg1[69] = sub_4423D0(nullptr);
                }
                else if ( (uint8_t)sub_423300(&v40, "[int data]") != 0 )
                {
                  sub_5E5260((void **)pDwArg1 + 70);
                  for ( i = (void **)sub_4423D0(&v35); v35 != 0; i = (void **)sub_4423D0(&v35) )
                    sub_431230((int)(pDwArg1 + 70), &i);
                }
                else if ( (uint8_t)sub_423300(&v40, "[reward type]") != 0 )
                {
                  v18 = v36;
                  sub_443370();
                  if ( (uint8_t)sub_423300(v36, "[item]") != 0 )
                  {
                    pDwArg1[74] = 0;
                  }
                  else if ( (uint8_t)sub_423300(v36, "[grow type]") != 0 )
                  {
                    pDwArg1[74] = 1;
                  }
                }
                else if ( (uint8_t)sub_423300(&v40, "[reward int data]") != 0 )
                {
                  sub_5E5260((void **)pDwArg1 + 75);
                  for ( i = (void **)sub_4423D0(&v35); v35 != 0; i = (void **)sub_4423D0(&v35) )
                    sub_431230((int)(pDwArg1 + 75), &i);
                }
                else if ( (uint8_t)sub_423300(&v40, "[relation quest]") != 0 )
                {
                  pDwArg1[79] = sub_4423D0(nullptr);
                }
                else
                {
                  i = v14;
                  sub_401690((int)v14, (size_t *)&v40);
                  if ( (uint8_t)sub_442C80(
                                          (char)v14[0],
                                          v14[1],
                                          (int)v14[2],
                                          (int)v15,
                                          (int)v16,
                                          (int)v17,
                                          (int)v18) == 0 )
                  {
                    v13 = (void **)v41[0];
                    if ( v43 < 0x10 )
                      v13 = v41;
                    off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)v13);
                  }
                }
              }
              else
              {
                *((uint8_t *)pDwArg1 + 120) = sub_4423D0(nullptr) != 0;
              }
            }
            else
            {
              v18 = v36;
              sub_443370();
              if ( sub_40BF00((std::_String_base *)v36, 0, v38, "[normaly repeat]", 0x10u) != 0 )
              {
                if ( (uint8_t)sub_423300(v36, "[common unique]") != 0 )
                {
                  pDwArg1[29] = 1;
                }
                else if ( (uint8_t)sub_423300(v36, "[epic]") != 0 )
                {
                  pDwArg1[29] = 2;
                }
              }
              else
              {
                pDwArg1[29] = 0;
              }
            }
          }
          else
          {
            v18 = (const char *)(pDwArg1 + 22);
            sub_443370();
          }
        }
        else
        {
          v18 = (const char *)(pDwArg1 + 15);
          sub_443370();
        }
      }
      else
      {
        v18 = (const char *)(pDwArg1 + 8);
        sub_443370();
      }
      goto LABEL_108;
    }
LABEL_109:
    v18 = ArgList;
    pDwArg1[40] = 99;
    *pDwArg1 = sub_4A2F80(dword_9B70A8, v18);
    if ( pDwArg1[32] == -1 )
      pDwArg1[32] = pDwArg1[31];
    if ( v39 >= 0x10 )
      j__free(Block);
    v39 = 15;
    v38 = 0;
    LOBYTE(Block) = 0;
    if ( v43 >= 0x10 )
      j__free(v41[0]);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5002A0 sub_5002A0
// ------------------------------------------------------------
bool /*cdecl*/ sub_5002A0(const char *pArg1, int nArg2)
{
  strcpy(byte_9B70B8, pArg1);
  if ( byte_9B70B7[strlen(byte_9B70B8)] != 92 && byte_9B70B7[strlen(byte_9B70B8)] != 47 )
    *(uint16_t *)&byte_9B70B8[strlen(byte_9B70B8)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B71B8, (char)byte_9B70B8, nArg2) != 0;
}



// ------------------------------------------------------------
// 0x500330 sub_500330 —— NPC 商店(npc shop)定义解析器
//   标签族：[NPC]/[message]/[type]（商店枚举子串 [etc shop]/[weapon shop]/[disjoint shop]）
//   /[only buy]/[sell item]。
// ------------------------------------------------------------
char /*cdecl*/ sub_500330(int pArg1, const char *ArgList)
{
  char result; // al
  int pArg12; // esi
  unsigned int v4; // edx
  int v5; // ecx
  void **v6; // esi
  int nCmp; // eax
  int v8; // eax
  int v9; // esi
  unsigned int v10; // edx
  int *v11; // ecx
  void **v12; // eax
  char v13; // [esp-1Ch] [ebp-78h] BYREF
  void **v14; // [esp-18h] [ebp-74h]
  int v15; // [esp-14h] [ebp-70h]
  int v16; // [esp-10h] [ebp-6Ch]
  int v17; // [esp-Ch] [ebp-68h]
  CHAR *v18; // [esp-8h] [ebp-64h]
  unsigned int v19; // [esp-4h] [ebp-60h]
  int v20; // [esp+Ch] [ebp-50h] BYREF
  char v21; // [esp+13h] [ebp-49h] BYREF
  uint8_t v22[4]; // [esp+14h] [ebp-48h] BYREF
  void *Block; // [esp+18h] [ebp-44h]
  unsigned int v24; // [esp+28h] [ebp-34h]
  unsigned int v25; // [esp+2Ch] [ebp-30h]
  uint8_t v26[4]; // [esp+30h] [ebp-2Ch] BYREF
  void *v27[4]; // [esp+34h] [ebp-28h] BYREF
  int v28; // [esp+44h] [ebp-18h]
  unsigned int v29; // [esp+48h] [ebp-14h]
  int dword_796E502; // [esp+4Ch] [ebp-10h]
  int v31; // [esp+58h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B70B8, (int)ArgList);
  if ( result != 0 )
  {
    pArg12 = pArg1;
    v19 = 0;
    v18 = (CHAR *)szPassword;
    *(uint32_t *)pArg1 = 0;
    *(uint32_t *)(pArg1 + 4) = 0;
    *(uint32_t *)(pArg1 + 8) = 0;
    *(uint8_t *)(pArg1 + 12) = 0;
    sub_4015C0(v18, v19);  // 【std::string构造赋值】
    if ( *(uint32_t *)(pArg1 + 48) != 0 )
      j__free(*(void **)(pArg1 + 48));
    *(uint32_t *)(pArg1 + 48) = 0;
    *(uint32_t *)(pArg1 + 52) = 0;
    *(uint32_t *)(pArg1 + 56) = 0;
    v29 = 15;
    v28 = 0;
    LOBYTE(v27[0]) = 0;
    v31 = 1;
    v25 = 15;
    v24 = 0;
    LOBYTE(Block) = 0;
    v21 = 0;
    if ( (uint8_t)sub_443430(v26) != 0 )
    {
      while ( 1 )
      {
        sub_442B20(v26);
        v4 = v28;
        if ( v28 == 0 )
          goto LABEL_15;
        v5 = v28;
        if ( (unsigned int)v28 >= 5 )
          v5 = 5;
        v6 = (void **)v27[0];
        if ( v29 < 0x10 )
          v6 = v27;
        nCmp = memcmp((const char *)v6, "[NPC]", v5);
        if ( nCmp != 0 )
          break;
        if ( (unsigned int)v28 < 5 )
          break;
        LOBYTE(nCmp) = v28 != 5;
        if ( nCmp != 0 )
          break;
        *(uint32_t *)(pArg1 + 8) = sub_4423D0(nullptr);
        pArg12 = pArg1;
LABEL_43:
        if ( (uint8_t)sub_443430(v26) == 0 )
          goto LABEL_44;
      }
      v4 = v28;
      pArg12 = pArg1;
LABEL_15:
      if ( sub_40BF00((std::_String_base *)v26, 0, v4, "[message]", 9u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v26, 0, v28, "[type]", 6u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v26, 0, v28, "[only buy]", 0xAu) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v26, 0, v28, "[sell item]", 0xBu) != 0 )
            {
              v20 = (int)&v13;
              v19 = 15;
              v18 = nullptr;
              LOBYTE(v14) = 0;
              sub_4014D0((std::_String_base *)&v13, v26, 0, -1);
              if ( sub_442C80(v13, v14, v15, v16, v17, (int)v18, v19) == 0 )
              {
                v12 = (void **)v27[0];
                if ( v29 < 0x10 )
                  v12 = v27;
                off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)v12);
              }
            }
            else
            {
              if ( *(uint32_t *)(pArg1 + 48) != 0 )
                j__free(*(void **)(pArg1 + 48));
              v19 = (unsigned int)&v21;
              *(uint32_t *)(pArg1 + 48) = 0;
              *(uint32_t *)(pArg1 + 52) = 0;
              *(uint32_t *)(pArg1 + 56) = 0;
              v8 = sub_4423D0((uint8_t *)v19);
              v20 = v8;
              if ( v21 != 0 )
              {
                do
                {
                  v9 = *(uint32_t *)(pArg1 + 48);
                  if ( v9 != 0 )
                    v10 = (*(uint32_t *)(pArg1 + 52) - v9) >> 2;
                  else
                    v10 = 0;
                  if ( v9 != 0 && v10 < (*(uint32_t *)(pArg1 + 56) - v9) >> 2 )
                  {
                    v11 = *(int **)(pArg1 + 52);
                    *v11 = v8;
                    *(uint32_t *)(pArg1 + 52) = v11 + 1;
                  }
                  else
                  {
                    sub_430C80(*(void **)(pArg1 + 52), 1, (int)&v20);
                  }
                  v8 = sub_4423D0(&v21);
                  v20 = v8;
                }
                while ( v21 != 0 );
                pArg12 = pArg1;
              }
            }
          }
          else
          {
            *(uint8_t *)(pArg12 + 12) = sub_4423D0(nullptr) != 0;
          }
        }
        else
        {
          v19 = (unsigned int)v22;
          sub_443370();
          if ( sub_40BF00((std::_String_base *)v22, 0, v24, "[etc shop]", 0xAu) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v22, 0, v24, "[weapon shop]", 0xDu) != 0 )
            {
              if ( sub_40BF00((std::_String_base *)v22, 0, v24, "[disjoint shop]", 0xFu) == 0 )
                *(uint32_t *)(pArg12 + 4) = 2;
            }
            else
            {
              *(uint32_t *)(pArg12 + 4) = 1;
            }
          }
          else
          {
            *(uint32_t *)(pArg12 + 4) = 0;
          }
        }
      }
      else
      {
        v19 = pArg12 + 16;
        sub_443370();
      }
      goto LABEL_43;
    }
LABEL_44:
    *(uint32_t *)pArg12 = sub_4A2F80(ArgList);
    if ( v25 >= 0x10 )
      j__free(Block);
    v25 = 15;
    v24 = 0;
    LOBYTE(Block) = 0;
    if ( v29 >= 0x10 )
      j__free(v27[0]);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5006B0 sub_5006B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5006B0(int this)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 28) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x500710 sub_500710
// ------------------------------------------------------------
int /*cdecl*/ sub_500710(int nArg1, int nArg2, int pArg3)
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
      *(uint32_t *)(nArg12 + 24) = 15;
      *(uint32_t *)(nArg12 + 20) = 0;
      *(uint8_t *)(nArg12 + 4) = 0;
      sub_4014D0((std::_String_base *)nArg12, pArg3, 0, -1);
      result = *(uint32_t *)(pArg3 + 28);
      *(uint32_t *)(nArg12 + 28) = result;
    }
    nArg12 += 32;
    LOBYTE(v6) = 0;
    --nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5007D0 sub_5007D0
// ------------------------------------------------------------
int /*stdcall*/ sub_5007D0(int nArg1, int nArg2, int nArg3)
{
  sub_500710(nArg1, nArg2, nArg3);
  return nArg1 + 32 * nArg2;
}



// ------------------------------------------------------------
// 0x500800 sub_500800
// ------------------------------------------------------------
void /*thiscall*/ sub_500800(int this, int pArg2, unsigned int uArg3, int pArg4)
{
  int fld_4; // ecx
  unsigned int fld_C; // eax
  int fld_8; // edx
  int fld_82; // edx
  unsigned int v10; // eax
  int fld_87; // edx
  int fld_88; // eax
  char *pMem; // ebx
  void *fld_43; // ecx
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
  char v29[4]; // [esp+18h] [ebp-34h] BYREF
  void *v30; // [esp+1Ch] [ebp-30h]
  int v31; // [esp+2Ch] [ebp-20h]
  unsigned int v32; // [esp+30h] [ebp-1Ch]
  int v33; // [esp+34h] [ebp-18h]
  int dword_796E502; // [esp+38h] [ebp-14h]
  uint32_t *v35; // [esp+3Ch] [ebp-10h]
  int v36; // [esp+48h] [ebp-4h]
  int v37; // [esp+58h] [ebp+Ch]

  v35 = v26;
  dword_796E502 = dword_796E50;
  v26[3] = this;
  v32 = 15;
  v31 = 0;
  LOBYTE(v30) = 0;
  sub_4014D0((std::_String_base *)v29, pArg4, 0, -1);
  v33 = *(uint32_t *)(pArg4 + 28);
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
      sub_427E20(this);
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
        v20 = sub_4981F0(v19, fld_83, fld_83);
        Block2 = Block;
        *(uint32_t *)(this + 8) = v20;
        sub_492DA0(pArg2, v19, Block2);
        sub_492D60(pArg2, pArg2 + 32 * uArg3, v29);
      }
      else
      {
        sub_4981F0(pArg2, fld_83, pArg2 + 32 * uArg3);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 5);
        fld_85 = *(uint32_t *)(this + 8);
        LOBYTE(v36) = 3;
        sub_5007D0(fld_85, fld_84, v29);
        fld_86 = 32 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        v36 = 0;
        sub_492D60(pArg2, fld_86 - 32 * uArg3, v29);
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
      pMem2 = (char *)sub_4981F0(fld_42, pArg2, pMem);
      sub_500710(pMem2, uArg3, v29);
      fld_89 = *(uint32_t *)(this + 8);
      pMem2 += 32 * uArg3;
      sub_4981F0(pArg2, fld_89, pMem2);
      fld_43 = *(void **)(this + 4);
      if ( fld_43 != nullptr )
        fld_810 = (*(uint32_t *)(this + 8) - (int)fld_43) >> 5;
      else
        fld_810 = 0;
      v16 = fld_810 + uArg3;
      if ( fld_43 != nullptr )
      {
        sub_493260(fld_43, *(uint32_t *)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &pMem[v37];
      *(uint32_t *)(this + 8) = &pMem[32 * v16];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
  if ( v32 >= 0x10 )
    j__free(v30);
}


// ------------------------------------------------------------
// 0x500AC0 sub_500AC0
// ------------------------------------------------------------
void /*thiscall*/ sub_500AC0(int *this, int nArg2)
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
    sub_500710(fld_e22, 1, nArg2);
    *(this + 2) = fld_e22 + 32;
  }
  else
  {
    sub_500800((int)this, *(this + 2), 1u, nArg2);
  }
}



// ------------------------------------------------------------
// 0x500B30 sub_500B30 —— 对象创建/运动定义解析器（PassiveObject 生成器，[creation pos] 族）
//   标签族：创建位置 [creation pos]/[x axis]/[y axis]/[z axis]；运动 [move type] 子枚举
//   [stop]=0/[straight line]=1/[sin]=2/[cos]=3 + [move variable 1]/[move variable 2]；
//   变值模式 [changing term]/[changing type] 子枚举 [keep changing]=0/[keep last value]=1/[ping pong]=2；
//   [gravity]/[rotation angle]/[life time]；落点 [landing type] 子枚举 [pierce]/[slide]/[vanish]；
//   表现 [transparent value]；子对象生成 [creation frequency]/[maximum create number]/[maximum create time]/
//   [create area size]/[create area rotation angle]；区域形状 [rotation angle range type] 子枚举
//   [rectangle]/[circle]；[rotation angle variable]/[random range]/[display effect rate]/[create pos correct]；
//   对象 [object type] 子枚举 [animation]/[passive object]；[how to create object] 子枚举 [randomize]/[in order]；
//   [object]/[layer]。
// ------------------------------------------------------------
char /*cdecl*/ sub_500B30(int pArg1, char *ArgList)
{
  char result; // al
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int *v16; // edi
  int i; // ebx
  void *p_Block; // eax
  const char *v19; // eax
  void *v20[4]; // [esp-1Ch] [ebp-98h] BYREF
  uint8_t *v21; // [esp-Ch] [ebp-88h]
  uint8_t *v22; // [esp-8h] [ebp-84h]
  uint8_t *j; // [esp-4h] [ebp-80h]
  char v24; // [esp+0h] [ebp-7Ch]
  void **v25; // [esp+Ch] [ebp-70h]
  int v26; // [esp+10h] [ebp-6Ch]
  uint8_t v27[28]; // [esp+14h] [ebp-68h] BYREF
  int v28; // [esp+30h] [ebp-4Ch]
  uint8_t v29[4]; // [esp+34h] [ebp-48h] BYREF
  void *Block; // [esp+38h] [ebp-44h] BYREF
  int v31; // [esp+48h] [ebp-34h]
  unsigned int v32; // [esp+4Ch] [ebp-30h]
  int v33; // [esp+50h] [ebp-2Ch] BYREF
  void *v34; // [esp+54h] [ebp-28h] BYREF
  int v35; // [esp+64h] [ebp-18h]
  unsigned int v36; // [esp+68h] [ebp-14h]
  int dword_796E502; // [esp+6Ch] [ebp-10h]
  int v38; // [esp+78h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)szPassword, (int)ArgList);
  if ( result != 0 )
  {
    sub_443300(pArg1 + 196, ArgList, v24);
    sub_4D0B90(pArg1);
    sub_443300(pArg1 + 196, ArgList, v24);
    v3 = 0;
    v36 = 15;
    v35 = 0;
    LOBYTE(v34) = 0;
    v38 = 1;
    v32 = 15;
    v31 = 0;
    LOBYTE(Block) = 0;
    v26 = 0;
    while ( (uint8_t)sub_443430(&v33) != 0 )
    {
      sub_442B20(&v33);
      if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[creation pos]", 0xEu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[x axis]", 8u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[y axis]", 8u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[z axis]", 8u) != 0 )
            {
              if ( (uint8_t)sub_423300(&v33, "[move type]") != 0 )
              {
                j = v29;
                sub_443370();
                if ( (uint8_t)sub_423300(v29, "[stop]") != 0 )
                {
                  *(uint8_t *)(v3 + pArg1 + 12) = 0;
                }
                else if ( (uint8_t)sub_423300(v29, "[straight line]") != 0 )
                {
                  *(uint8_t *)(v3 + pArg1 + 12) = 1;
                }
                else if ( (uint8_t)sub_423300(v29, "[sin]") != 0 )
                {
                  *(uint8_t *)(v3 + pArg1 + 12) = 2;
                }
                else if ( (uint8_t)sub_423300(v29, "[cos]") != 0 )
                {
                  *(uint8_t *)(v3 + pArg1 + 12) = 3;
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[move variable 1]") != 0 )
              {
                v6 = sub_4423D0(nullptr);
                v22 = nullptr;
                *(uint32_t *)(pArg1 + 8 * v3 + 15) = v6;
                *(uint32_t *)(pArg1 + 8 * v3 + 19) = sub_4423D0(v22);
              }
              else if ( (uint8_t)sub_423300(&v33, "[move variable 2]") != 0 )
              {
                v7 = sub_4423D0(nullptr);
                v22 = nullptr;
                *(uint32_t *)(pArg1 + 8 * v3 + 39) = v7;
                *(uint32_t *)(pArg1 + 8 * v3 + 43) = sub_4423D0(v22);
              }
              else if ( (uint8_t)sub_423300(&v33, "[changing term]") != 0 )
              {
                *(uint32_t *)(pArg1 + 63) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v33, "[changing type]") != 0 )
              {
                j = v29;
                sub_443370();
                if ( (uint8_t)sub_423300(v29, "[keep changing]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 67) = 0;
                }
                else if ( (uint8_t)sub_423300(v29, "[keep last value]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 67) = 1;
                }
                else if ( (uint8_t)sub_423300(v29, "[ping pong]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 67) = 2;
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[gravity]") != 0 )
              {
                *(uint32_t *)(pArg1 + 68) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v33, "[rotation angle]") != 0 )
              {
                v8 = sub_4423D0(nullptr);
                v22 = nullptr;
                *(uint32_t *)(pArg1 + 72) = v8;
                v9 = sub_4423D0(v22);
                v21 = nullptr;
                *(uint32_t *)(pArg1 + 76) = v9;
                *(uint32_t *)(pArg1 + 80) = sub_4423D0(v21);
              }
              else if ( (uint8_t)sub_423300(&v33, "[life time]") != 0 )
              {
                *(uint32_t *)(pArg1 + 85) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v33, "[landing type]") != 0 )
              {
                j = v29;
                sub_443370();
                if ( (uint8_t)sub_423300(v29, "[pierce]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 89) = 0;
                }
                else if ( (uint8_t)sub_423300(v29, "[slide]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 89) = 1;
                }
                else if ( (uint8_t)sub_423300(v29, "[stop]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 89) = 2;
                }
                else if ( (uint8_t)sub_423300(v29, "[vanish]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 89) = 3;
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[transparent value]") != 0 )
              {
                v10 = sub_4423D0(nullptr);
                v22 = nullptr;
                *(uint32_t *)(pArg1 + 90) = v10;
                *(uint32_t *)(pArg1 + 94) = sub_4423D0(v22);
              }
              else if ( (uint8_t)sub_423300(&v33, "[creation frequency]") != 0 )
              {
                *(float *)(pArg1 + 100) = sub_442480(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v33, "[maximum create number]") != 0 )
              {
                *(uint32_t *)(pArg1 + 104) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v33, "[maximum create time]") != 0 )
              {
                *(uint32_t *)(pArg1 + 108) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v33, "[create area size]") != 0 )
              {
                v11 = sub_4423D0(nullptr);
                v22 = nullptr;
                *(uint32_t *)(pArg1 + 112) = v11;
                v12 = sub_4423D0(v22);
                v21 = nullptr;
                *(uint32_t *)(pArg1 + 116) = v12;
                *(uint32_t *)(pArg1 + 120) = sub_4423D0(v21);
              }
              else if ( (uint8_t)sub_423300(&v33, "[create area rotation angle]") != 0 )
              {
                v13 = sub_4423D0(nullptr);
                v22 = nullptr;
                *(uint32_t *)(pArg1 + 124) = v13;
                v14 = sub_4423D0(v22);
                v21 = nullptr;
                *(uint32_t *)(pArg1 + 128) = v14;
                *(uint32_t *)(pArg1 + 132) = sub_4423D0(v21);
              }
              else if ( (uint8_t)sub_423300(&v33, "[rotation angle range type]") != 0 )
              {
                j = v29;
                sub_443370();
                if ( (uint8_t)sub_423300(v29, "[rectangle]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 136) = 0;
                }
                else if ( (uint8_t)sub_423300(v29, "[circle]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 136) = 1;
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[rotation angle variable]") != 0 )
              {
                v15 = sub_4423D0(nullptr);
                v22 = nullptr;
                *(uint32_t *)(pArg1 + 140) = v15;
                *(uint32_t *)(pArg1 + 144) = sub_4423D0(v22);
              }
              else if ( (uint8_t)sub_423300(&v33, "[random range]") != 0 )
              {
                *(uint32_t *)(pArg1 + 148) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v33, "[display effect rate]") != 0 )
              {
                v16 = (int *)(pArg1 + 156);
                for ( i = 3; i != 0; --i )
                  *v16++ = sub_4423D0(nullptr);
                v3 = v26;
              }
              else if ( (uint8_t)sub_423300(&v33, "[create pos correct]") != 0 )
              {
                *(uint8_t *)(pArg1 + 152) = sub_4423D0(nullptr) != 0;
              }
              else if ( (uint8_t)sub_423300(&v33, "[object type]") != 0 )
              {
                j = v29;
                sub_443370();
                if ( (uint8_t)sub_423300(v29, "[animation]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 172) = 2;
                }
                else if ( (uint8_t)sub_423300(v29, "[passive object]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 172) = 33;
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[how to create object]") != 0 )
              {
                j = v29;
                sub_443370();
                if ( (uint8_t)sub_423300(v29, "[randomize]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 168) = 1;
                }
                else if ( (uint8_t)sub_423300(v29, "[in order]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 168) = 0;
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[object]") != 0 )
              {
                sub_428480(pArg1 + 180);
                for ( j = v29; sub_443370() != 0; j = v29 )
                {
                  sub_5006B0(v27);
                  LOBYTE(v38) = 2;
                  sub_4014D0((std::_String_base *)v27, v29, 0, -1);
                  v28 = sub_4423D0(nullptr);
                  sub_500AC0(v27);
                  LOBYTE(v38) = 1;
                  sub_501490(v27);
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[layer]") != 0 )
              {
                j = v29;
                sub_443370();
                p_Block = Block;
                if ( v32 < 0x10 )
                  p_Block = &Block;
                *(uint32_t *)(pArg1 + 176) = sub_4425F0(p_Block);
              }
              else
              {
                v25 = v20;
                sub_401690(&v33);
                if ( (uint8_t)sub_442C80(
                                        (char)v20[0],
                                        v20[1],
                                        (int)v20[2],
                                        (int)v20[3],
                                        (int)v21,
                                        (int)v22,
                                        (int)j) == 0 )
                {
                  v19 = (const char *)v34;
                  if ( v36 < 0x10 )
                    v19 = (const char *)&v34;
                  off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, v19);
                }
              }
            }
            else
            {
              v3 = 2;
              v26 = 2;
            }
          }
          else
          {
            v3 = 1;
            v26 = 1;
          }
        }
        else
        {
          v3 = 0;
          v26 = 0;
        }
      }
      else
      {
        v4 = sub_4423D0(nullptr);
        v22 = nullptr;
        *(uint32_t *)pArg1 = v4;
        v5 = sub_4423D0(v22);
        v21 = nullptr;
        *(uint32_t *)(pArg1 + 4) = v5;
        *(uint32_t *)(pArg1 + 8) = sub_4423D0(v21);
      }
    }
    if ( v32 >= 0x10 )
      j__free(Block);
    v32 = 15;
    v31 = 0;
    LOBYTE(Block) = 0;
    if ( v36 >= 0x10 )
      j__free(v34);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5013F0 sub_5013F0
// ------------------------------------------------------------
uint64_t /*cdecl*/ sub_5013F0(int nArg1, int nArg2)
{
  double v2; // st7

  v2 = (double)nArg2 * 0.0099999998 * (double)nArg1;
  if ( v2 < 1.0 )
    return (uint64_t)1.0;
  return (uint64_t)v2;
}



// ------------------------------------------------------------
// 0x501420 sub_501420
// ------------------------------------------------------------
int /*cdecl*/ sub_501420(int nArg1, int nArg2)
{
  return nArg1 + nArg2;
}



// ------------------------------------------------------------
// 0x501430 sub_501430
// ------------------------------------------------------------
int /*thiscall*/ sub_501430(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 45) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 45) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 45) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 45) == 0 );
        if ( *(uint8_t *)(result + 45) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 45) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x501490 sub_501490
// ------------------------------------------------------------
void /*thiscall*/ sub_501490(void **this)
{
  if ( (unsigned int)*(this + 6) >= 0x10 )
    j__free(*(this + 1));
  *(this + 6) = (void *)15;
  *(this + 5) = nullptr;
  *((uint8_t *)this + 4) = 0;
}



// ------------------------------------------------------------
// 0x5014C0 sub_5014C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5014C0(void **this)
{
  if ( (unsigned int)*(this + 9) >= 0x10 )
    j__free(*(this + 4));
  *(this + 9) = (void *)15;
  *(this + 8) = nullptr;
  *((uint8_t *)this + 16) = 0;
}



// ------------------------------------------------------------
// 0x5014F0 sub_5014F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5014F0(uint32_t *this, uint32_t *uArg2, unsigned int *pDwArg3)
{
  uint32_t *v5; // eax
  unsigned int v6; // ecx
  const char *v7; // eax
  uint32_t *v9; // [esp+18h] [ebp+Ch]

  v5 = (uint32_t *)sub_65DCE0(pDwArg3);
  v9 = v5;
  if ( v5 == (uint32_t *)*(this + 1)
    || ((v6 = v5[8], v5[9] < 0x10u) ? (v7 = (const char *)(v5 + 4)) : (v7 = (const char *)v5[4]),
        sub_40BF00((std::_String_base *)pDwArg3, 0, pDwArg3[5], v7, v6) < 0) )
  {
    *uArg2 = *(this + 1);
    return uArg2;
  }
  else
  {
    *uArg2 = v9;
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x501560 sub_501560
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_501560(int this, int Src, unsigned int uArg3, int *pDwArg4)
{
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_85; // ecx
  int fld_86; // eax
  char *fld_42; // eax
  uint32_t *v15; // eax
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
      sub_47F990(this);
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
        sub_523700(*(uint32_t **)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);
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
      v15 = sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);
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
// 0x501740 sub_501740
// ------------------------------------------------------------
int /*thiscall*/ sub_501740(int *this, char *pszArg2, unsigned int uArg3, int *Block)
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
  uint32_t *fld_e23; // ecx
  int fld_e26; // edi
  uint32_t *fld_e12; // [esp-18h] [ebp-40h]
  int fld_e25; // [esp-Ch] [ebp-34h]
  unsigned int fld_e24; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  uint32_t *v27; // [esp+30h] [ebp+8h]
  uint32_t *v28; // [esp+34h] [ebp+Ch]
  uint32_t *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];
  fld_e1 = *(this + 1);
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 12;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_47F990(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (uint32_t *)*(this + 2);
      Blockb = fld_e23;
      if ( ((char *)fld_e23 - pszArg2) / 12 >= uArg3 )
      {
        v27 = &fld_e23[-3 * uArg3];
        *(this + 2) = (int)sub_59EE30(v27, fld_e23, fld_e23);
        sub_504450(pszArg2, v27, Blockb);
        return sub_5043B0(pszArg2, &pszArg2[12 * uArg3], v25);
      }
      else
      {
        sub_59EE30(pszArg2, fld_e23, &pszArg2[12 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 12;
        fld_e25 = *(this + 2);
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return sub_5043B0(pszArg2, fld_e26 - 12 * uArg3, v25);
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 12;
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);
      v15 = 3 * v13;
      Blocka = operator new(12 * v13);
      fld_e12 = (uint32_t *)*(this + 1);
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pszArg2, Blocka);
      sub_623C10(v28, uArg3, v25);
      sub_59EE30(pszArg2, (uint32_t *)*(this + 2), &v28[3 * uArg3]);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 12;
      v17 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v15];
      *(this + 2) = (int)&Blocka[3 * v17];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5019F0 sub_5019F0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_5019F0(uint32_t *this, int ***uArg2, int **pDwArg3)
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
  uint32_t *v17; // eax
  uint32_t *Block2; // eax
  int v19; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v22; // [esp+34h] [ebp-34h] BYREF
  char v23; // [esp+38h] [ebp-30h]
  int v24; // [esp+48h] [ebp-20h]
  int v25; // [esp+4Ch] [ebp-1Ch]
  int v26; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v29; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 45) != 0 )
  {
    v25 = 15;
    v24 = 0;
    v23 = 0;
    sub_4015C0(&v22, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v29 = 0;
    sub_401740(pExceptionObject, &v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_40BEA0((int *)&pDwArg3);
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
        v9 = (int *)sub_6600D0(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v26 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 45) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v26 + 8) = sub_4429F0(v4);
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
        v17 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v17 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v17 + 44) == 0 )
          {
            *((uint8_t *)v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_442AC0(v6);
            v17 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v17 + 44) != 1 || *(uint8_t *)(v17[2] + 44) != 1 )
          {
            if ( *(uint8_t *)(v17[2] + 44) == 1 )
            {
              *(uint8_t *)(*v17 + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;
              sub_433290(v17);
              v17 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(v17[2] + 44) = 1;
            sub_442AC0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v17 + 44) == 0 )
          {
            *((uint8_t *)v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_433290(v6);
            v17 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v17[2] + 44) != 1 || *(uint8_t *)(*v17 + 44) != 1 )
          {
            if ( *(uint8_t *)(*v17 + 44) == 1 )
            {
              *(uint8_t *)(v17[2] + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;
              sub_442AC0(v17);
              v17 = (uint32_t *)*v6;
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(*v17 + 44) = 1;
            sub_433290(v6);
            break;
          }
        }
        *((uint8_t *)v17 + 44) = 0;
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
// 0x501CD0 sub_501CD0
// ------------------------------------------------------------
void */*stdcall*/ sub_501CD0(int nArg1, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  void *pMem; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  pMem = operator new(0x30u);
  v7[4] = pMem;
  v7[8] = (void *)1;
  v7[3] = pMem;
  if ( pMem != nullptr )
    sub_40C300(nArg1, nArg2, nArg3, nArg4, pszArg5);
  return pMem;
}



// ------------------------------------------------------------
// 0x501D60 sub_501D60
// ------------------------------------------------------------
char /*stdcall*/ sub_501D60(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 45);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_501D60(i[2]);
    i = (void **)*i;
    sub_5014C0(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 45);
  }
  return result;
}



// ------------------------------------------------------------
// 0x501DB0 sub_501DB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_501DB0(int *this, uint32_t *uArg2, int nArg3, int *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )
    v6 = (nArg3 - fld_e1) / 12;
  else
    v6 = 0;
  sub_501740(this, nArg3, 1u, Block);
  *uArg2 = *(this + 1) + 12 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x501E20 sub_501E20
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_501E20(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
{
  uint32_t *fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  uint32_t *fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
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
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(pExceptionObject, (int)v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_501CD0(*(this + 1), (int)pArg4, *(this + 1), nArg5, 0);
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
  fld_e16 = fld_e1;
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
          if ( fld_e16 == (uint32_t *)v12[2] )
          {
            fld_e16 = (uint32_t *)*v10;
            sub_442AC0(*v10);
          }
          *(uint8_t *)(fld_e16[1] + 44) = 1;
          *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
          sub_433290(*(uint32_t *)(fld_e16[1] + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 44) != 0 )
      {
        if ( fld_e16 == (uint32_t *)*v12 )
        {
          fld_e16 = (uint32_t *)*v10;
          sub_433290(*v10);
        }
        *(uint8_t *)(fld_e16[1] + 44) = 1;
        *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
        sub_442AC0(*(uint32_t *)(fld_e16[1] + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 44) = 1;
      *(uint8_t *)(v14 + 44) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 44) = 0;
      fld_e16 = *(uint32_t **)(*v10 + 4);
LABEL_21:
      v10 = fld_e16 + 1;
      if ( *(uint8_t *)(fld_e16[1] + 44) != 0 )
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
// 0x501FD0 sub_501FD0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_501FD0(int nArg1, int nArg2, uint32_t *uArg3)
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
    v5 = *(uint32_t *)(nArg22 - 44);
    nArg22 -= 44;
    uArg32 -= 11;
    *uArg32 = v5;
    uArg32[1] = *(uint32_t *)(nArg22 + 4);
    sub_41B0D0(nArg22 + 8);
    sub_4800C0(nArg22 + 12);
    sub_480210(nArg22 + 28);
  }
  while ( nArg22 != nArg1 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x502030 sub_502030
// ------------------------------------------------------------
char */*thiscall*/ sub_502030(char *this)
{
  void **pThis_8; // ebx

  pThis_8 = (void **)(this + 8);
  *((uint32_t *)this + 2) = 0;
  sub_41BFE0((void **)this + 2, szPassword);
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 0;
  sub_41B010(pThis_8);
  if ( *((uint32_t *)this + 4) != 0 )
    j__free(*((void **)this + 4));
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  if ( *((uint32_t *)this + 8) != 0 )
    j__free(*((void **)this + 8));
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x5020D0 sub_5020D0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5020D0(int *this, int *pDwArg2)
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
    return sub_501560((int)this, *(this + 2), 1u, pDwArg2);
  fld_e22 = (int *)*(this + 2);
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x502120 sub_502120
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_502120(int *this, int *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 12;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 12 )
    return sub_501DB0(this, &Block, *(this + 2), Block);
  fld_e22 = *(this + 2);
  result = (uint32_t *)sub_623C10(fld_e22, 1, Block);
  *(this + 2) = fld_e22 + 12;
  return result;
}



// ------------------------------------------------------------
// 0x5021A0 sub_5021A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5021A0(int *this, int pArg2, uint32_t *pArg3)
{
  int fld_e1; // ebx
  uint32_t *fld_e12; // esi
  char v5; // al
  uint32_t *pArg32; // edi
  unsigned int i; // esi
  unsigned int v8; // ecx
  const char *v9; // eax
  unsigned int v10; // edx
  const char *v11; // esi
  int nCmp; // eax
  bool v13; // sf
  unsigned int v14; // esi
  int v15; // eax
  uint32_t *fld_e122; // ebx
  const char *v18; // eax
  uint32_t *v19; // [esp+Ch] [ebp-14h]
  int *pThis; // [esp+18h] [ebp-8h]
  char v21; // [esp+1Ch] [ebp-4h]

  fld_e1 = *(uint32_t *)(*(this + 1) + 4);
  fld_e12 = (uint32_t *)*(this + 1);
  v5 = 1;
  pArg32 = pArg3;
  pThis = this;
  v21 = 1;
  if ( *(uint8_t *)(fld_e1 + 45) == 0 )
  {
    for ( i = pArg3[5]; ; i = pArg3[5] )
    {
      v8 = *(uint32_t *)(fld_e1 + 32);
      v19 = (uint32_t *)fld_e1;
      if ( *(uint32_t *)(fld_e1 + 36) < 0x10u )
        v9 = (const char *)(fld_e1 + 16);
      else
        v9 = *(const char **)(fld_e1 + 16);
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )
        goto LABEL_16;
      if ( v10 < v8 )
        v8 = v10;
      v11 = pArg32[6] < 0x10u ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];
      nCmp = memcmp(v11, v9, v8);
      v13 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )
      {
LABEL_16:
        v14 = *(uint32_t *)(fld_e1 + 32);
        if ( v10 >= v14 )
          v15 = v10 != v14;
        else
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      fld_e1 = v13 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);
      if ( *(uint8_t *)(fld_e1 + 45) != 0 )
        break;
    }
    fld_e12 = v19;
    this = pThis;
  }
  fld_e122 = fld_e12;
  pArg3 = fld_e12;
  if ( v5 != 0 )
  {
    if ( fld_e12 == *(uint32_t **)*(this + 1) )
    {
      *(uint32_t *)pArg2 = *sub_501E20(this, &pArg3, 1, fld_e12, (int)pArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      return pArg2;
    }
    sub_501430(&pArg3);
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10u )
    v18 = (const char *)(pArg32 + 1);
  else
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )
  {
    *(uint32_t *)pArg2 = fld_e122;
    *(uint8_t *)(pArg2 + 4) = 0;
  }
  else
  {
    *(uint32_t *)pArg2 = *sub_501E20(pThis, &pArg3, v21, fld_e12, (int)pArg32);
    *(uint8_t *)(pArg2 + 4) = 1;
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x502300 sub_502300
// ------------------------------------------------------------
int **/*thiscall*/ sub_502300(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
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
    sub_501D60(*(void ***)(fld_e1 + 4));
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
        if ( *((uint8_t *)pDwArg32 + 45) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 45) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 45) == 0; i = (int *)i[1] )
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
            for ( j = *v11; *((uint8_t *)j + 45) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_5019F0(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x5023C0 sub_5023C0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_5023C0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 11 )
  {
    *i = *pArg3;
    i[1] = pArg3[1];
    sub_41B0D0(pArg3 + 2);
    sub_4800C0(pArg3 + 3);
    sub_480210(pArg3 + 7);
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x502410 sub_502410
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_502410(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_501FD0(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x502430 sub_502430
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_502430(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // edi
  uint32_t *pArg43; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_501E20((int *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( (uint8_t)sub_40C160(pArg4, pArg3 + 3) != 0 )
    {
      sub_501E20((int *)this, uArg2, 1, pArg3, (int)pArg42);
      return uArg2;
    }
    goto LABEL_23;
  }
  if ( pArg3 == fld_4 )
  {
    if ( (uint8_t)sub_40C160(fld_4[2] + 12, pArg4) != 0 )
    {
      sub_501E20((int *)this, uArg2, 0, *(uint32_t **)(*(uint32_t *)(this + 4) + 8), (int)pArg42);
      return uArg2;
    }
    goto LABEL_23;
  }
  if ( (uint8_t)sub_40C160(pArg4, pArg3 + 3) != 0 )
  {
    pArg4 = pArg3;
    sub_501430(&pArg4);
    if ( (uint8_t)sub_40C160(pArg4 + 3, pArg42) != 0 )
    {
      if ( *(uint8_t *)(pArg4[2] + 45) != 0 )
        sub_501E20((int *)this, uArg2, 0, pArg4, (int)pArg42);
      else
        sub_501E20((int *)this, uArg2, 1, pArg3, (int)pArg42);
      return uArg2;
    }
  }
  if ( (uint8_t)sub_40C160(pArg3 + 3, pArg42) == 0 )
    goto LABEL_23;
  pArg4 = pArg3;
  sub_40BEA0(&pArg4);
  pArg43 = pArg4;
  if ( pArg4 != *(uint32_t **)(this + 4) )
  {
    if ( (uint8_t)sub_40C160(pArg42, pArg4 + 3) != 0 )
    {
      pArg43 = pArg4;
      goto LABEL_19;
    }
LABEL_23:
    v9 = *(uint32_t *)sub_5021A0((int *)this, (int)v10, pArg42);
    *uArg2 = v9;
    return uArg2;
  }
LABEL_19:
  if ( *(uint8_t *)(pArg3[2] + 45) != 0 )
    sub_501E20((int *)this, uArg2, 0, pArg3, (int)pArg42);
  else
    sub_501E20((int *)this, uArg2, 1, pArg43, (int)pArg42);
  return uArg2;
}



// ------------------------------------------------------------
// 0x5025D0 sub_5025D0
// ------------------------------------------------------------
void /*cdecl*/ sub_5025D0(int nArg1, int nArg2, int nArg3)
{
  int nArg12; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  nArg12 = nArg1;
  v5[4] = v5;
  v5[3] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v6) = 1;
    if ( nArg12 != 0 )
      sub_480A90(nArg3);
    --nArg2;
    nArg12 += 44;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x5026A0 sub_5026A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5026A0(uint32_t *this, unsigned int *pDwArg2)
{
  unsigned int *pDwArg22; // ebx
  uint32_t *v4; // esi
  const char *v5; // eax
  int v7; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h]
  int v9; // [esp+20h] [ebp-18h]
  unsigned int v10; // [esp+24h] [ebp-14h]
  int v11; // [esp+28h] [ebp-10h]
  int v12; // [esp+34h] [ebp-4h]

  pDwArg22 = pDwArg2;
  v4 = (uint32_t *)sub_65DCE0(pDwArg2);
  if ( v4 == (uint32_t *)*(this + 1)
    || (v4[9] < 0x10u ? (v5 = (const char *)(v4 + 4)) : (v5 = (const char *)v4[4]),
        sub_40BF00((std::_String_base *)pDwArg22, 0, pDwArg22[5], v5, v4[8]) < 0) )
  {
    v10 = 15;
    v9 = 0;
    LOBYTE(Block) = 0;
    sub_4014D0((std::_String_base *)&v7, pDwArg22, 0, -1);
    v11 = 0;
    v12 = 0;
    v4 = (uint32_t *)*sub_502430((int)this, &pDwArg2, v4, &v7);
    if ( v10 >= 0x10 )
      j__free(Block);
  }
  return v4 + 10;
}



// ------------------------------------------------------------
// 0x5027A0 sub_5027A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5027A0(uint32_t *this)
{
  int v2; // eax

  v2 = sub_433B80();
  *(this + 1) = v2;
  *(uint8_t *)(v2 + 45) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x5027D0 sub_5027D0
// ------------------------------------------------------------
int /*stdcall*/ sub_5027D0(int nArg1, int nArg2, int nArg3)
{
  sub_5025D0(nArg1, nArg2, nArg3);
  return nArg1 + 44 * nArg2;
}



// ------------------------------------------------------------
// 0x502800 sub_502800
// ------------------------------------------------------------
void /*thiscall*/ sub_502800(int *this, int pArg2, unsigned int uArg3, int nArg4)
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
  int fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-68h]
  int fld_e25; // [esp-Ch] [ebp-5Ch]
  unsigned int fld_e24; // [esp-8h] [ebp-58h]
  int v22; // [esp+0h] [ebp-50h] BYREF
  uint8_t v23[8]; // [esp+Ch] [ebp-44h] BYREF
  void *v24; // [esp+14h] [ebp-3Ch] BYREF
  void *v25; // [esp+1Ch] [ebp-34h]
  int v26; // [esp+20h] [ebp-30h]
  int v27; // [esp+24h] [ebp-2Ch]
  void *v28; // [esp+2Ch] [ebp-24h]
  int v29; // [esp+30h] [ebp-20h]
  int v30; // [esp+34h] [ebp-1Ch]
  void *Block; // [esp+38h] [ebp-18h]
  int *pThis; // [esp+3Ch] [ebp-14h]
  int *v33; // [esp+40h] [ebp-10h]
  int v34; // [esp+4Ch] [ebp-4h]
  int v35; // [esp+58h] [ebp+8h]
  int v36; // [esp+5Ch] [ebp+Ch]
  int v37; // [esp+60h] [ebp+10h]
  int fld_e232; // [esp+60h] [ebp+10h]

  v33 = &v22;
  pThis = this;
  sub_480A90(nArg4);
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v34 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 44;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 44;
    else
      fld_e2 = 0;
    if ( 97612893 - fld_e2 < uArg3 )
      sub_47F990(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 44;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = *(this + 2);
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 44 >= uArg3 )
      {
        v35 = fld_e23 - 44 * uArg3;
        *(this + 2) = sub_480E70(v35, fld_e23, fld_e23);
        sub_502410(pArg2, v35, fld_e232);
        sub_5023C0(pArg2, pArg2 + 44 * uArg3, v23);
      }
      else
      {
        sub_480E70(pArg2, fld_e23, pArg2 + 44 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 44;
        fld_e25 = *(this + 2);
        LOBYTE(v34) = 3;
        sub_5027D0(fld_e25, fld_e24, v23);
        fld_e26 = 44 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v34 = 0;
        sub_5023C0(pArg2, fld_e26 - 44 * uArg3, v23);
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
      v37 = 44 * v10;
      pMem = (char *)operator new(44 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      LOBYTE(v34) = 1;
      v36 = sub_480E70(fld_e12, pArg2, pMem);
      sub_5025D0(v36, uArg3, v23);
      sub_480E70(pArg2, *(this + 2), 44 * uArg3 + v36);
      fld_e13 = *(this + 1);
      v34 = 0;
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 44;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_480F40(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v37];
      *(this + 2) = (int)&pMem[44 * v14];
      *(this + 1) = (int)pMem;
    }
  }
  v34 = -1;
  if ( v28 != nullptr )
    j__free(v28);
  v28 = nullptr;
  v29 = 0;
  v30 = 0;
  if ( v25 != nullptr )
    j__free(v25);
  v25 = nullptr;
  v26 = 0;
  v27 = 0;
  sub_41B010(&v24);
}


// ------------------------------------------------------------
// 0x502B30 sub_502B30
// ------------------------------------------------------------
char /*cdecl*/ sub_502B30(char *i, int nArg2)
{
  char *v2; // eax
  int v3; // edx
  char v4; // cl
  char *v5; // eax
  int v6; // ecx
  char *v7; // ecx
  int v9; // edi
  int j; // eax
  char *v11; // ecx
  unsigned int v12; // [esp+8h] [ebp-34h] BYREF
  void *v13; // [esp+Ch] [ebp-30h]
  int v14; // [esp+1Ch] [ebp-20h]
  unsigned int v15; // [esp+20h] [ebp-1Ch]
  int v16; // [esp+24h] [ebp-18h] BYREF
  void *Block; // [esp+28h] [ebp-14h]
  int v18; // [esp+38h] [ebp-4h]

  v2 = i;
  v3 = byte_9B71C8 - i;
  do
  {
    v4 = *v2;
    v2[v3] = *v2;
    ++v2;
  }
  while ( v4 != 0 );
  if ( byte_9B71C7[strlen(byte_9B71C8)] != 92 && byte_9B71C7[strlen(byte_9B71C8)] != 47 )
    *(uint16_t *)&byte_9B71C8[strlen(byte_9B71C8)] = 92;
  sub_444150(&v16);
  v18 = 0;
  if ( (uint8_t)sub_443C40((int)&v16, (char)byte_9B71C8, nArg2) == 0 )
    goto LABEL_14;
  v5 = *(char **)Block;
  for ( i = *(char **)Block; i != Block; v5 = i )
  {
    v6 = *((uint32_t *)v5 + 10) < 0x10u ? (int)(v5 + 20) : *((uint32_t *)v5 + 5);
    if ( (uint8_t)sub_443C40(12 * *((uint32_t *)v5 + 3) + 10187476, (char)byte_9B71C8, v6) == 0 )
      goto LABEL_14;
    sub_40BEA0(&i);
  }
  if ( (uint8_t)sub_442A10((char)byte_9B71C8, (int)"RDARKeyIndex.dat") == 0 )
  {
LABEL_14:
    v7 = *(char **)Block;
    v18 = -1;
    sub_443810(&i, v7, Block);
    j__free(Block);
    return 0;
  }
  v9 = 0;
  for ( j = sub_65BE30(&unk_9789A0); j != 0; j = sub_65BE30(&unk_9789A0) )
  {
    if ( j == 2 )
    {
      v9 = j__atol(dword_9789A4);
    }
    else if ( j == 6 )
    {
      v15 = 15;
      v14 = 0;
      LOBYTE(v13) = 0;
      sub_4015C0(dword_9789A4, strlen(dword_9789A4));  // 【std::string构造赋值】
      LOBYTE(v18) = 1;
      *sub_5026A0(&dword_9B72C8, &v12) = v9;
      LOBYTE(v18) = 0;
      if ( v15 >= 0x10 )
        j__free(v13);
      v15 = 15;
      v14 = 0;
      LOBYTE(v13) = 0;
    }
  }
  v11 = *(char **)Block;
  v18 = -1;
  sub_443810(&i, v11, Block);
  j__free(Block);
  return 1;
}



// ------------------------------------------------------------
// 0x502DA0 sub_502DA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_502DA0(uint32_t *this, uint32_t *uArg2, int pArg3)
{
  int fld_e2; // edi
  int v5; // esi

  sub_480BC0(pArg3 + 44, *(this + 2), pArg3);
  fld_e2 = *(this + 2);
  v5 = fld_e2 - 44;
  do
  {
    sub_47FA00(v5);
    v5 += 44;
  }
  while ( v5 != fld_e2 );
  *(this + 2) -= 44;
  *uArg2 = pArg3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x502E00 sub_502E00
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_502E00(int *this, uint32_t *uArg2, char *pszArg3, int nArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 44 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 44;
  else
    v6 = 0;
  sub_502800(this, pszArg3, 1u, nArg4);
  *uArg2 = *(this + 1) + 44 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x502E70 sub_502E70
// ------------------------------------------------------------
void /*thiscall*/ sub_502E70(int *this, int nArg2)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 44;
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) / 44 )
  {
    fld_e22 = *(this + 2);
    sub_5025D0(fld_e22, 1, nArg2);
    *(this + 2) = fld_e22 + 44;
  }
  else
  {
    sub_502E00(this, &nArg2, (char *)*(this + 2), nArg2);
  }
}



// ------------------------------------------------------------
// 0x502F00 sub_502F00 —— ★ 玩家技能定义解析器（.skl 文件；研究 20 §13 定位为 [shake screen] 解析器，
//   研究 20 §30 定位为 [command] 技能指令语法解析器）。a1 = 技能对象（0x4A3520 构造），
//   a3 = 技能来源类别（4 时置 *a1 = -1，否则 sub_4A2F80 查技能 ID）。
//   标签族（29 个，按文件顺序）：
//   基础 [name]/[name2]/[explain]/[maximum level]/[purchase cost]/[required level]/
//   [required level range]/[pre required skill]/[steel learning skill]/[type]/
//   [active]=0/[passive]（+76 类型码）/[skill class]/[growtype fitness]/
//   [casting time]/[growtype maximum level]/[skill fitness growtype]/[consume MP]/
//   [consume item]/[cool time]/[skill under cooltime effect]/[auto cooltime apply]/[icon]/
//   [command key explain]/[command]（§30 键序语法：键名→键码，模式 DOWN/DOWN ONCE/UP/UP ONCE，
//   节奏符 '!'=150ms/','=300ms/'~'=1000ms）/[static data]/[level info]/[level property]/
//   [shake screen]（研究 20 §13：写技能+296/+300，最终传入镜头震动入口 sub_424120）。
// ------------------------------------------------------------
char /*cdecl*/ sub_502F00(int pArg1, const char *ArgList, int nArg3)
{
  char result; // al
  int v4; // eax
  int v5; // eax
  int v6; // eax
  uint32_t *v7; // edi
  int j; // ebx
  uint32_t *v9; // edi
  int k; // ebx
  uint32_t *v11; // edi
  int m; // ebx
  int v13; // edi
  int n; // ebx
  uint32_t *v15; // edi
  int jj; // ebx
  int v17; // eax
  int kk; // eax
  char v19; // al
  int v20; // ebx
  int v21; // edi
  int v22; // edi
  int mm; // edi
  int v24; // eax
  uint32_t *v25; // eax
  int v26; // eax
  const char *v27; // eax
  uint32_t *v28; // edi
  int nn; // ebx
  int v30; // ecx
  int v31; // eax
  int v32; // ecx
  unsigned int v33; // ebx
  uint32_t *v34; // eax
  void *v35[3]; // [esp-1Ch] [ebp-110h] BYREF
  int v36; // [esp-10h] [ebp-104h]
  int v37; // [esp-Ch] [ebp-100h]
  int v38; // [esp-8h] [ebp-FCh]
  int v39; // [esp-4h] [ebp-F8h]
  uint8_t v40[28]; // [esp+Ch] [ebp-E8h] BYREF
  int v41; // [esp+28h] [ebp-CCh] BYREF
  int v42; // [esp+2Ch] [ebp-C8h]
  uint8_t v43[4]; // [esp+30h] [ebp-C4h] BYREF
  uint8_t v44[4]; // [esp+54h] [ebp-A0h] BYREF
  uint32_t v45[2]; // [esp+58h] [ebp-9Ch] BYREF
  int v46; // [esp+60h] [ebp-94h] BYREF
  int ii; // [esp+64h] [ebp-90h] BYREF
  int v48; // [esp+68h] [ebp-8Ch]
  int v49; // [esp+6Ch] [ebp-88h]
  uint8_t v50[4]; // [esp+70h] [ebp-84h] BYREF
  int v51; // [esp+74h] [ebp-80h]
  int v52; // [esp+78h] [ebp-7Ch]
  int v53; // [esp+7Ch] [ebp-78h]
  int v54; // [esp+80h] [ebp-74h]
  int v55; // [esp+84h] [ebp-70h]
  float i; // [esp+88h] [ebp-6Ch] BYREF
  char v57; // [esp+8Fh] [ebp-65h] BYREF
  uint8_t v58[28]; // [esp+90h] [ebp-64h] BYREF
  uint8_t v59[4]; // [esp+ACh] [ebp-48h] BYREF
  void *Block; // [esp+B0h] [ebp-44h]
  int v61; // [esp+C0h] [ebp-34h]
  unsigned int v62; // [esp+C4h] [ebp-30h]
  int v63; // [esp+C8h] [ebp-2Ch] BYREF
  void *v64; // [esp+CCh] [ebp-28h] BYREF
  int v65; // [esp+DCh] [ebp-18h]
  unsigned int v66; // [esp+E0h] [ebp-14h]
  int dword_796E502; // [esp+E4h] [ebp-10h]
  int v68; // [esp+F0h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B71C8, (int)ArgList);
  if ( result != 0 )
  {
    sub_481420(pArg1);
    v66 = 15;
    v65 = 0;
    LOBYTE(v64) = 0;
    v68 = 1;
    v62 = 15;
    v61 = 0;
    LOBYTE(Block) = 0;
    v57 = 0;
    while ( (uint8_t)sub_443430(&v63) != 0 )
    {
      sub_442B20(&v63);
      if ( sub_40BF00(0, v65, "[name]", 6) != 0 )
      {
        if ( sub_40BF00(0, v65, "[name2]", 7) != 0 )
        {
          if ( sub_40BF00(0, v65, "[explain]", 9) != 0 )
          {
            if ( sub_40BF00(0, v65, "[maximum level]", 15) != 0 )
            {
              if ( (uint8_t)sub_423300(&v63, "[purchase cost]") != 0 )
              {
                sub_5E5260((void *)(pArg1 + 20));
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )
                  sub_431230(&i);
              }
              else if ( (uint8_t)sub_423300(&v63, "[required level]") != 0 )
              {
                *(uint32_t *)(pArg1 + 36) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(&v63, "[required level range]") != 0 )
              {
                *(uint32_t *)(pArg1 + 40) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(&v63, "[pre required skill]") != 0 )
              {
                sub_5E5260((void *)(pArg1 + 44));
                sub_5E5260((void *)(pArg1 + 60));
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )
                {
                  sub_431230(&i);
                  i = COERCE_FLOAT(sub_4423D0(0));
                  sub_431230(&i);
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[steel learning skill]") != 0 )
              {
                v4 = sub_4423D0(0);
                v38 = 0;
                *(uint8_t *)(pArg1 + 320) = v4 == 1;
                v5 = sub_4423D0(v38);
                v37 = 0;
                *(uint32_t *)(pArg1 + 324) = v5;
                v6 = sub_4423D0(v37);
                v36 = 0;
                *(uint32_t *)(pArg1 + 328) = v6;
                *(uint32_t *)(pArg1 + 332) = sub_4423D0(v36);
              }
              else if ( (uint8_t)sub_423300(&v63, "[type]") != 0 )
              {
                sub_443370(v59);
                if ( (uint8_t)sub_423300(v59, "[active]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 76) = 0;
                }
                else if ( (uint8_t)sub_423300(v59, "[passive]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 76) = 1;
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[skill class]") != 0 )
              {
                *(uint32_t *)(pArg1 + 80) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(&v63, "[growtype fitness]") != 0 )
              {
                v7 = (uint32_t *)(pArg1 + 84);
                for ( j = 5; j != 0; --j )
                  *v7++ = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(&v63, "[casting time]") != 0 )
              {
                v9 = (uint32_t *)(pArg1 + 132);
                for ( k = 2; k != 0; --k )
                  *v9++ = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(&v63, "[growtype maximum level]") != 0 )
              {
                v11 = (uint32_t *)(pArg1 + 104);
                for ( m = 5; m != 0; --m )
                  *v11++ = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(&v63, "[skill fitness growtype]") != 0 )
              {
                sub_5E5260((void *)(pArg1 + 304));
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )
                  sub_431230(&i);
              }
              else if ( (uint8_t)sub_423300(&v63, "[consume MP]") != 0 )
              {
                v13 = pArg1 + 124;
                for ( n = 2; n != 0; --n )
                {
                  v13 += 4;
                  *(float *)(v13 - 4) = sub_442480(0) * 0.89999998;
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[consume item]") != 0 )
              {
                v48 = 0;
                v49 = 0;
                sub_5E5260((void *)(pArg1 + 140));
                for ( ii = sub_4423D0(&v57); v57 != 0; ii = sub_4423D0(&v57) )
                {
                  v48 = sub_4423D0(0);
                  v49 = sub_4423D0(0);
                  sub_502120(&ii);
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[cool time]") != 0 )
              {
                v15 = (uint32_t *)(pArg1 + 156);
                for ( jj = 2; jj != 0; --jj )
                  *v15++ = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(&v63, "[skill under cooltime effect]") != 0 )
              {
                sub_5E5260((void *)(pArg1 + 164));
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )
                  sub_431230(&i);
              }
              else if ( (uint8_t)sub_423300(&v63, "[auto cooltime apply]") != 0 )
              {
                *(uint8_t *)(pArg1 + 180) = sub_4423D0(0) != 0;
              }
              else if ( (uint8_t)sub_423300(&v63, "[icon]") != 0 )
              {
                sub_442E10(pArg1 + 184);  // 【RDARScriptStringManager 入口（::ERROR::input…】
                v17 = sub_4423D0(0);
                v37 = pArg1 + 188;
                *(uint32_t *)(pArg1 + 192) = v17;
                sub_442E10(v37);  // 【RDARScriptStringManager 入口（::ERROR::input…】
                *(uint32_t *)(pArg1 + 196) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(&v63, "[command key explain]") != 0 )
              {
                sub_442E10(pArg1 + 244);  // 【RDARScriptStringManager 入口（::ERROR::input…】
              }
              else if ( (uint8_t)sub_423300(&v63, "[command]") != 0 )
              {
                v51 = 0;
                v52 = 0;
                v53 = 0;
                v54 = 0;
                v55 = 300;
                LOBYTE(v68) = 2;
                sub_435850(pArg1 + 200);
                for ( kk = sub_65BE30(&unk_9789A0); kk != 0; kk = sub_65BE30(&unk_9789A0) )
                {
                  if ( kk == 5 )
                    break;
                  switch ( kk )
                  {
                    case 6:
                      sub_401710(dword_9789A4);
                      LOBYTE(v68) = 3;
                      sub_5014F0(&v46, v40);
                      LOBYTE(v68) = 2;
                      sub_501490(v40);
                      if ( v46 != dword_9B72CC )
                        sub_431230(v46 + 40);
                      break;
                    case 2:
                      v54 = j__atol(dword_9789A4);
                      break;
                    case 7:
                      sub_401710(byte_979DF8);
                      LOBYTE(v68) = 4;
                      if ( (uint8_t)sub_423300(v58, "DOWN") != 0 )
                      {
                        *(uint32_t *)(pArg1 + 232) = 0;
                        LOBYTE(v68) = 2;
                        sub_501490(v58);
                      }
                      else if ( (uint8_t)sub_423300(v58, "DOWN ONCE") != 0 )
                      {
                        *(uint32_t *)(pArg1 + 232) = 1;
                        LOBYTE(v68) = 2;
                        sub_501490(v58);
                      }
                      else if ( (uint8_t)sub_423300(v58, "UP") != 0 )
                      {
                        *(uint32_t *)(pArg1 + 232) = 2;
                        LOBYTE(v68) = 2;
                        sub_501490(v58);
                      }
                      else
                      {
                        if ( (uint8_t)sub_423300(v58, "UP ONCE") != 0 )
                          *(uint32_t *)(pArg1 + 232) = 3;
                        LOBYTE(v68) = 2;
                        sub_501490(v58);
                      }
                      break;
                    case 8:
                      v19 = *dword_9789A4;
                      if ( *dword_9789A4 == 38 )
                      {
                        if ( (uint8_t)sub_484F10(v50) == 0 )
                          sub_4ED3F0(v50);
                      }
                      else
                      {
                        switch ( v19 )
                        {
                          case '!':
                            v55 = 150;
                            break;
                          case ',':
                            v55 = 300;
                            break;
                          case '~':
                            v55 = 1000;
                            break;
                          default:
                            break;
                        }
                        if ( (uint8_t)sub_484F10(v50) == 0 )
                          sub_4B5910(v50);
                      }
                      sub_4B1C10(v50);
                      break;
                    default:
                      break;
                  }
                }
                if ( (uint8_t)sub_484F10(v50) == 0 )
                  sub_4B5910(v50);
                LOBYTE(v68) = 1;
                sub_5E5260(v50);
              }
              else if ( (uint8_t)sub_423300(&v63, "[static data]") != 0 )
              {
                sub_5E5260((void *)(pArg1 + 248));
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )
                  sub_431230(&i);
              }
              else if ( (uint8_t)sub_423300(&v63, "[level info]") != 0 )
              {
                sub_42D540(pArg1 + 264);
                v20 = sub_4423D0(0);
                sub_4897D0(v20);
                v21 = 0;
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )
                {
                  sub_431230(&i);
                  ++v21;
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[level property]") != 0 )
              {
                v22 = sub_4423D0(&v57);
                if ( v57 == 0 )
                  break;
                sub_502030(&v41);
                LOBYTE(v68) = 5;
                v41 = v22;
                v42 = sub_4423D0(0);
                sub_442E10(v43);  // 【RDARScriptStringManager 入口（::ERROR::input…】
                for ( mm = sub_4423D0(&v57); v57 != 0; mm = sub_4423D0(&v57) )
                {
                  v24 = sub_4423D0(0);
                  v45[0] = mm;
                  v45[1] = v24;
                  sub_474950(v45);
                  i = sub_442480(0);
                  sub_5020D0(&i);
                }
                v25 = *(uint32_t **)(pArg1 + 284);
                while ( v25 != *(uint32_t **)(pArg1 + 288) )
                {
                  if ( v25[1] < v41 || *v25 > v42 )
                    v25 += 11;
                  else
                    v25 = *(uint32_t **)sub_502DA0(v44, v25);
                }
                sub_502E70(&v41);
                LOBYTE(v68) = 1;
                sub_47FA00(&v41);
              }
              else if ( (uint8_t)sub_423300(&v63, "[shake screen]") != 0 )
              {
                v26 = sub_4423D0(0);
                v38 = 0;
                *(uint32_t *)(pArg1 + 296) = v26;
                *(uint32_t *)(pArg1 + 300) = sub_4423D0(v38);
              }
              else
              {
                i = COERCE_FLOAT(v35);
                sub_401690(&v63);
                if ( (uint8_t)sub_442C80((char)v35[0], v35[1], (int)v35[2], v36, v37, v38, v39) == 0 )
                {
                  v27 = (const char *)v64;
                  if ( v66 < 0x10 )
                    v27 = (const char *)&v64;
                  off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, v27);
                }
              }
            }
            else
            {
              *(uint32_t *)(pArg1 + 16) = sub_4423D0(0);
            }
          }
          else
          {
            sub_442E10(pArg1 + 12);  // 【RDARScriptStringManager 入口（::ERROR::input…】
          }
        }
        else
        {
          sub_442E10(pArg1 + 8);  // 【RDARScriptStringManager 入口（::ERROR::input…】
        }
      }
      else
      {
        sub_442E10(pArg1 + 4);  // 【RDARScriptStringManager 入口（::ERROR::input…】
      }
    }
    v28 = (uint32_t *)(pArg1 + 104);
    for ( nn = 5; nn != 0; --nn )
    {
      if ( *v28 > *(uint32_t *)(pArg1 + 16) )
      {
        off_77F3FC(aSkillError, ArgList);
        *(uint32_t *)(pArg1 + 16) = *v28;
      }
      ++v28;
    }
    while ( 1 )
    {
      v30 = *(uint32_t *)(pArg1 + 24);
      v31 = v30 != 0 ? (*(uint32_t *)(pArg1 + 28) - v30) >> 2 : 0;
      if ( v31 >= *(uint32_t *)(pArg1 + 16) )
        break;
      v32 = *(uint32_t *)(pArg1 + 24);
      if ( v32 != 0 )
        v33 = (*(uint32_t *)(pArg1 + 28) - v32) >> 2;
      else
        v33 = 0;
      if ( v32 != 0 && v33 < (*(uint32_t *)(pArg1 + 32) - v32) >> 2 )
      {
        v34 = *(uint32_t **)(pArg1 + 28);
        *v34 = *(v34 - 1);
        *(uint32_t *)(pArg1 + 28) = v34 + 1;
      }
      else
      {
        sub_430C80(*(void **)(pArg1 + 28), 1, *(uint32_t *)(pArg1 + 28) - 4);
      }
    }
    if ( nArg3 == 4 )
      *(uint32_t *)pArg1 = -1;
    else
      *(uint32_t *)pArg1 = sub_4A2F80(ArgList);
    if ( v62 >= 0x10 )
      j__free(Block);
    v62 = 15;
    v61 = 0;
    LOBYTE(Block) = 0;
    if ( v66 >= 0x10 )
      j__free(v64);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x503BA0 sub_503BA0 —— ★★ 怪物/PassiveObject 攻击定义解析器（attackinfo 结构填充）
//   【研究 20 §1.3 全词汇表定案函数；研究 20 §12 "攻击定义" 解析器】。
//   a1 = attackinfo 结构基址（0x98 字节，由 sub_4A3520 构造 → sub_4A3450 置默认值）。
//   调用者：sub_4D2D60 对象工厂 case 8（operator new(0x98) + sub_4A3520 → 本函数）。
//   迭代：sub_443430 逐行 → sub_442B20 取行 → 标签比对 → 参数读取
//   （sub_4423D0 整型 / sub_442480 浮点 / sub_443370 字符串）。
//
//   ── attackinfo 字段表（本函数写入点，与 研究 20 §1.3 逐项对照）──
//   +0    float   [damage]                伤害门（>0 才出特效/结算；float 版）
//   +4    int     [absolute damage]       绝对伤害值
//   +8    int     [damage bonus]          伤害加成
//   +12   int     [attack type] 子枚举 [physic]=0/[magic]=1/[ignore defense]=2  伤害大类
//                                          （==1 时受击动作速度 ×0.7，研究 20 §2 ⑧）
//   +16   bool    [weapon damage apply]   武器伤害适用
//   +17   bool    [attack myself]         友敌开关 1/3（= 本地扫掠 sub_4E82B0 的 +405 门镜像）
//   +18   bool    [attack friend]         友敌开关 2/3（+406）
//   +19   bool    [attack enemy]          友敌开关 3/3（+407）
//   +20   int     [elemental property]    属性攻击（子串名查表 sub_442710）
//   +24   int[2]  [active status]         携带异常状态 id（0..17，off_791F38 表 18 项；
//                                          17 = 无；第二槽位经 v3 索引 → +28）
//   +36   float[2] [active status] 强度    与 +24/+28 平行数组
//   +48   int[2]  [active status] 概率     与 +24/+28 平行数组
//   +60   int     [damage reaction] 子枚举 [none]=0/[damage]=1/[down]=2  反应类型
//   +64   int     [push aside]            击退距离（阈值 150 分档，研究 20 §2 ⑧ state 4）
//   +68   int     [lift up]               浮空值（阈值 400 分档）
//   +72   float   [critical hit]          暴击率
//   +76   float   [stuck]                 硬直强度/概率
//   +80   bool    [stuck prob increase]   三开关之一
//   +81   bool    [knuck back]            三开关之二（原文拼写如此）
//   +82   bool    [ignore defense]        三开关之三
//   +84   float   [human damage rate]     对人型倍率（>100% 出标记特效，研究 20 §5.2）
//   +88   float   [fort damage rate]      对城械倍率（同上）
//   +92   string  [hit wav]               自定义命中音效（VC6 std::string，研究 20 §5.5）
//   +120  int     [attack direction] 子枚举 [hit lift up]=0/[hit horizon]=1/[hit down]=2
//                                          受击方向类型（决定反应动画选型）
//   +124  int     [hit info] 主参数 子枚举 [blow]=0/[cut]=1/[burn]=2/[etc]=3
//                                          伤害类（钝击 Knock / 斩击 Slash 火花；burn=延滞伤）
//   +128  bool    [hit info] 第二参数 子枚举 [no blood]=0/[blood]=1  血溅/刃钝标志
//   +132  int     [hit info] 第三参数    ★ 受击硬直（stuck）时长 ms —— hit stop 时长（研究 20 §3）
//   +136  float   [hit info] 第四参数    受击动作速度倍率（-1 → 1.0，研究 20 §2 ⑧）
//   +140  bool    [HP drain]              吸血
//   +141  bool    [MP drain]              吸魔
//   ── 本函数写入范围止于 +141（+124 附近穿插写 +128/+132/+136）──
//   +144 / +148 本函数【不写】：二者由 sub_4A3450 置默认（+144=0 / +148=100.0f），
//     运行时再由伤害流水线写入（研究 20 §1.3 第 14 轮：+144=背击暴击加成、+148=本次攻击倍率%，
//     终段公式 ×(+148×0.01)×技能参数×0.01；研究 20 §16 P38 速率链同型换算）。
//
//   未识别标签 → off_77F3FC("SCRIPT TAG ERROR! [%s] %s")（研究 20 §1.3 所述的引擎错误输出）。
//   标签总数 38（含子枚举）。
// ------------------------------------------------------------
char /*cdecl*/ sub_503BA0(int pArg1, const char *ArgList)
{
  char result; // al
  int v3; // ebx
  void *p_Block; // eax
  int v5; // edi
  int v6; // eax
  const char *v7; // eax
  void *v8[5]; // [esp-1Ch] [ebp-74h] BYREF
  int v9; // [esp-8h] [ebp-60h]
  int v10; // [esp-4h] [ebp-5Ch]
  void **v11; // [esp+Ch] [ebp-4Ch]
  uint8_t v12[4]; // [esp+10h] [ebp-48h] BYREF
  void *Block; // [esp+14h] [ebp-44h] BYREF
  int v14; // [esp+24h] [ebp-34h]
  unsigned int v15; // [esp+28h] [ebp-30h]
  int v16; // [esp+2Ch] [ebp-2Ch] BYREF
  void *v17; // [esp+30h] [ebp-28h] BYREF
  int v18; // [esp+40h] [ebp-18h]
  unsigned int v19; // [esp+44h] [ebp-14h]
  int dword_796E502; // [esp+48h] [ebp-10h]
  int v21; // [esp+54h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)szPassword, (int)ArgList);
  if ( result != 0 )
  {
    sub_4A3450(pArg1);   // attackinfo 默认值（sub_4A3450 @0x4A3450，由 sub_4A3520 构造函数先行调用）：
                      //   +0/+4/+8/+12=0；+16/+17/+18=0 但 +19=1（默认只打敌人）；
                      //   +20=4（属性=无）；+24/+28/+32=17（三槽异常状态 id 全 none=17）；
                      //   +36..+56=0（状态强度/概率平行数组）；+60=1（默认 damage 反应）；
                      //   +64/+68/+72/+76=0；+80..+82=0；
                      //   +84/+88=100.0f(0x42C80000)；+92=空串；+120=1（hit horizon）；+124=4（[hit info] 哨兵）；
                      //   +128=0；+132=-1（stuck 时长哨兵）；+136=-1.0f（速度倍率哨兵）；
                      //   +140/+141=0；+144=0；+148=100.0f
    v3 = 0;
    v19 = 15;
    v18 = 0;
    LOBYTE(v17) = 0;
    v21 = 1;
    v15 = 15;
    v14 = 0;
    LOBYTE(Block) = 0;
    while ( (uint8_t)sub_443430(&v16) != 0 )
    {
      sub_442B20(&v16);
      if ( sub_40BF00(0, v18, "[damage]", 8) != 0 )
      {
        if ( sub_40BF00(0, v18, "[absolute damage]", 17) != 0 )
        {
          if ( sub_40BF00(0, v18, "[damage bonus]", 14) != 0 )
          {
            if ( sub_40BF00(0, v18, "[attack type]", 13) != 0 )
            {
              if ( (uint8_t)sub_423300(&v16, "[weapon damage apply]") != 0 )
              {
                *(uint8_t *)(pArg1 + 16) = sub_4423D0(0) != 0;   // +16 [weapon damage apply] 武器伤害适用
              }
              else if ( (uint8_t)sub_423300(&v16, "[attack myself]") != 0 )
              {
                *(uint8_t *)(pArg1 + 17) = sub_4423D0(0) != 0;   // +17 [attack myself]  友敌开关 1/3（本地扫掠 +405 门镜像）
              }
              else if ( (uint8_t)sub_423300(&v16, "[attack friend]") != 0 )
              {
                *(uint8_t *)(pArg1 + 18) = sub_4423D0(0) != 0;   // +18 [attack friend]  友敌开关 2/3（+406）
              }
              else if ( (uint8_t)sub_423300(&v16, "[attack enemy]") != 0 )
              {
                *(uint8_t *)(pArg1 + 19) = sub_4423D0(0) != 0;   // +19 [attack enemy]   友敌开关 3/3（+407）
              }
              else if ( (uint8_t)sub_423300(&v16, "[elemental property]") != 0 )
              {
                sub_443370(v12);
                p_Block = Block;
                if ( v15 < 0x10 )
                  p_Block = &Block;
                *(uint32_t *)(pArg1 + 20) = sub_442710(p_Block);  // +20 [elemental property] 属性攻击（名字查表）
              }
              else if ( (uint8_t)sub_423300(&v16, "[active status]") != 0 )
              {
                sub_443370(v12);
                if ( *(uint32_t *)(pArg1 + 24) != 17 )            // 首槽非 17(=none) → 第二槽 v3=1
                  v3 = 1;
                v5 = 0;
                while ( (uint8_t)sub_423300(v12, off_791F38[v5]) == 0 )
                {
                  if ( ++v5 >= 18 )                             // 18 项状态名表（含 [none]=17）
                    goto LABEL_36;
                }
                *(uint32_t *)(pArg1 + 4 * v3 + 24) = v5;          // +24/+28 [active status] 状态 id
LABEL_36:
                *(float *)(pArg1 + 4 * v3 + 36) = sub_442480(0);  // +36/+40 状态强度（float 平行数组）
                *(uint32_t *)(pArg1 + 4 * v3 + 48) = sub_4423D0(0);// +48/+52 状态概率（int 平行数组）
                v3 = 0;
              }
              else if ( (uint8_t)sub_423300(&v16, "[damage reaction]") != 0 )
              {
                sub_443370(v12);
                if ( (uint8_t)sub_423300(v12, "[none]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 60) = 0;                   // +60 [damage reaction] [none] 反应类型=无
                }
                else if ( (uint8_t)sub_423300(v12, "[damage]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 60) = 1;                   // +60 [damage] 走受击反应（state 3/4/5 选型门）
                }
                else if ( (uint8_t)sub_423300(v12, "[down]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 60) = 2;                   // +60 [down] 击倒
                }
              }
              else if ( (uint8_t)sub_423300(&v16, "[push aside]") != 0 )
              {
                *(uint32_t *)(pArg1 + 64) = sub_4423D0(0);         // +64 [push aside] 击退距离（<150 分档，研究 20 §2 ⑧）
              }
              else if ( (uint8_t)sub_423300(&v16, "[lift up]") != 0 )
              {
                *(uint32_t *)(pArg1 + 68) = sub_4423D0(0);         // +68 [lift up] 浮空值（<400 分档 + 暴击加成 250/50）
              }
              else if ( (uint8_t)sub_423300(&v16, "[critical hit]") != 0 )
              {
                *(float *)(pArg1 + 72) = sub_442480(0);            // +72 [critical hit] 暴击率（伤害终段 +3.0 加成）
              }
              else if ( (uint8_t)sub_423300(&v16, "[stuck]") != 0 )
              {
                *(float *)(pArg1 + 76) = sub_442480(0);            // +76 [stuck] 硬直强度/概率（float 属性路径）
              }
              else if ( (uint8_t)sub_423300(&v16, "[stuck prob increase]") != 0 )
              {
                *(uint8_t *)(pArg1 + 80) = sub_4423D0(0) != 0;     // +80 [stuck prob increase] 三开关之一
              }
              else if ( (uint8_t)sub_423300(&v16, "[knuck back]") != 0 )
              {
                *(uint8_t *)(pArg1 + 81) = sub_4423D0(0) != 0;     // +81 [knuck back] 三开关之二（原文拼写）
              }
              else if ( (uint8_t)sub_423300(&v16, "[ignore defense]") != 0 )
              {
                *(uint8_t *)(pArg1 + 82) = sub_4423D0(0) != 0;     // +82 [ignore defense] 三开关之三
              }
              else if ( (uint8_t)sub_423300(&v16, "[human damage rate]") != 0 )
              {
                *(float *)(pArg1 + 84) = sub_442480(0);            // +84 [human damage rate] 对人型倍率（>100% 标记特效）
              }
              else if ( (uint8_t)sub_423300(&v16, "[fort damage rate]") != 0 )
              {
                *(float *)(pArg1 + 88) = sub_442480(0);            // +88 [fort damage rate] 对城械倍率
              }
              else if ( (uint8_t)sub_423300(&v16, "[HP drain]") != 0 )
              {
                *(uint8_t *)(pArg1 + 140) = sub_4423D0(0) != 0;    // +140 [HP drain] 吸血
              }
              else if ( (uint8_t)sub_423300(&v16, "[MP drain]") != 0 )
              {
                *(uint8_t *)(pArg1 + 141) = sub_4423D0(0) != 0;    // +141 [MP drain] 吸魔
              }
              else if ( (uint8_t)sub_423300(&v16, "[hit wav]") != 0 )
              {
                sub_443370(pArg1 + 92);                            // +92 [hit wav] 自定义命中音效（VC6 std::string）
              }
              else if ( (uint8_t)sub_423300(&v16, "[attack direction]") != 0 )
              {
                sub_443370(v12);
                if ( (uint8_t)sub_423300(v12, "[hit lift up]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 120) = 0;                  // +120 [attack direction] 0=上挑
                }
                else if ( (uint8_t)sub_423300(v12, "[hit horizon]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 120) = 1;                  // +120 1=平推
                }
                else if ( (uint8_t)sub_423300(v12, "[hit down]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 120) = 2;                  // +120 2=下压（决定反应动画选型）
                }
              }
              else if ( (uint8_t)sub_423300(&v16, "[hit info]") != 0 )
              {
                sub_443370(v12);
                if ( (uint8_t)sub_423300(v12, "[blow]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 124) = 0;                  // +124 [hit info] 0=[blow] 钝击 → Knock 火花
                }
                else if ( (uint8_t)sub_423300(v12, "[cut]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 124) = 1;                  // +124 1=[cut] 斩击 → Slash 火花
                }
                else if ( (uint8_t)sub_423300(v12, "[burn]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 124) = 2;                  // +124 2=[burn] 延滞伤（CNChangeHp 1000ms）
                }
                else if ( (uint8_t)sub_423300(v12, "[etc]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 124) = 3;                  // +124 3=[etc] 自定义路径（攻方 vt+652）
                }
                sub_443370(v12);
                if ( (uint8_t)sub_423300(v12, "[no blood]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 128) = 0;                   // +128 [no blood] 无血溅
                }
                else if ( (uint8_t)sub_423300(v12, "[blood]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 128) = 1;                   // +128 [blood] 有血溅（SplashBlood 族）
                }
                v6 = sub_4423D0(0);
                v9 = 0;
                *(uint32_t *)(pArg1 + 132) = v6;                   // +132 ★ 受击硬直(stuck)时长 ms = hit stop 时长
                                                                //   （研究 20 §3 表现壳 sub_4E5DC0 读此处，
                                                                //    经 vt+228(this,1,时长,0) 施加主状态 1）
                *(float *)(pArg1 + 136) = sub_442480(v9);          // +136 受击动作速度倍率（-1 → 1.0；+12==1 时 ×0.7）
              }
              else
              {
                v11 = v8;
                sub_401690(&v16);
                if ( (uint8_t)sub_442C80((char)v8[0], v8[1], (int)v8[2], (int)v8[3], (int)v8[4], v9, v10) == 0 )
                {
                  v7 = (const char *)v17;
                  if ( v19 < 0x10 )
                    v7 = (const char *)&v17;
                  off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, v7);  // 未知标签 = 引擎错误输出（研究 20 §1.3）
                }
              }
            }
            else
            {
              sub_443370(v12);
              if ( (uint8_t)sub_423300(v12, "[physic]") != 0 )
              {
                *(uint32_t *)(pArg1 + 12) = 0;                     // +12 [attack type] 0=物理
              }
              else if ( (uint8_t)sub_423300(v12, "[magic]") != 0 )
              {
                *(uint32_t *)(pArg1 + 12) = 1;                     // +12 1=魔法（受击动作速度 ×0.7 —— 研究 20 §2 ⑧）
              }
              else if ( (uint8_t)sub_423300(v12, "[ignore defense]") != 0 )
              {
                *(uint32_t *)(pArg1 + 12) = 2;                     // +12 2=无视防御
              }
            }
          }
          else
          {
            *(uint32_t *)(pArg1 + 8) = sub_4423D0(0);              // +8  [damage bonus] 伤害加成
          }
        }
        else
        {
          *(uint32_t *)(pArg1 + 4) = sub_4423D0(0);                // +4  [absolute damage] 绝对伤害
        }
      }
      else
      {
        *(float *)pArg1 = sub_442480(0);                           // +0  float [damage] 伤害门（>0 才出特效/结算）
      }
    }
    if ( v15 >= 0x10 )
      j__free(Block);
    v15 = 15;
    v14 = 0;
    LOBYTE(Block) = 0;
    if ( v19 >= 0x10 )
      j__free(v17);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x504300 sub_504300
// ------------------------------------------------------------
bool /*cdecl*/ sub_504300(const char *pArg1, int nArg2)
{
  strcpy(byte_9B7308, pArg1);
  if ( byte_9B7307[strlen(byte_9B7308)] != 92 && byte_9B7307[strlen(byte_9B7308)] != 47 )
    *(uint16_t *)&byte_9B7308[strlen(byte_9B7308)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B7408, (char)byte_9B7308, nArg2) != 0;
}



// ------------------------------------------------------------
// 0x504390 sub_504390
// ------------------------------------------------------------
int /*thiscall*/ sub_504390(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 36;
  return result;
}



// ------------------------------------------------------------
// 0x5043B0 sub_5043B0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_5043B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *v4; // edi

  for ( result = uArg1; result != uArg2; v4[2] = pArg3[2] )
  {
    v4 = result;
    *result = *pArg3;
    result[1] = pArg3[1];
    result += 3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5043F0 sub_5043F0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_5043F0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg22; // ecx
  uint32_t *result; // eax

  uArg22 = uArg2;
  for ( result = uArg3; uArg22 != uArg1; result[3] = uArg22[3] )
  {
    uArg22 -= 4;
    result -= 4;
    *result = *uArg22;
    result[1] = uArg22[1];
    result[2] = uArg22[2];
  }
  return result;
}



// ------------------------------------------------------------
// 0x504430 sub_504430
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_504430(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  return sub_4FEFD0(uArg1, uArg2, uArg3);
}



// ------------------------------------------------------------
// 0x504450 sub_504450
// ------------------------------------------------------------
int /*cdecl*/ sub_504450(int nArg1, int nArg2, int nArg3)
{
  return sub_623BD0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x504470 sub_504470
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_504470(int nArg1, int nArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax

  result = operator new(0x18u);
  if ( result != nullptr )
  {
    *result = nArg1;
    result[1] = nArg2;
    result[2] = *pArg3;
    result[3] = pArg3[1];
    result[4] = pArg3[2];
    result[5] = pArg3[3];
  }
  return result;
}



// ------------------------------------------------------------
// 0x5044B0 sub_5044B0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_5044B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *uArg22; // ecx

  result = uArg2;
  if ( uArg2 != nullptr )
  {
    uArg22 = uArg2;
    result = uArg1;
    do
    {
      if ( result != nullptr )
      {
        *result = *pArg3;
        result[1] = pArg3[1];
        result[2] = pArg3[2];
        result[3] = pArg3[3];
        result[4] = pArg3[4];
        result[5] = pArg3[5];
      }
      result += 6;
      uArg22 = (uint32_t *)((char *)uArg22 - 1);
    }
    while ( uArg22 != nullptr );
  }
  return result;
}



// ============================================================
// §E 0x504000-0x504600 掉落/奖励类别标签（sub_504500）、容器辅助族
// ============================================================

// ------------------------------------------------------------
// 0x504500 sub_504500 —— 掉落/奖励对象类别码解析器
//   标签族：[monster]=0/[trap]=1/[item]=2/[quest]=3（写 *a1；其余 5 项 sub_4423D0 数值）。
// ------------------------------------------------------------
void /*cdecl*/ sub_504500(uint32_t *uArg1)
{
  int i; // edi
  uint8_t v2[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  unsigned int v4; // [esp+1Ch] [ebp-18h]
  unsigned int v5; // [esp+20h] [ebp-14h]
  int dword_796E502; // [esp+24h] [ebp-10h]
  int v7; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v5 = 15;
  v4 = 0;
  LOBYTE(Block) = 0;
  v7 = 0;
  for ( i = 0; i < 6; ++i )
  {
    if ( i != 0 )
    {
      uArg1[i] = sub_4423D0(nullptr);
    }
    else if ( sub_443370() != 0 )
    {
      if ( sub_40BF00((std::_String_base *)v2, 0, v4, "[monster]", 9u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v2, 0, v4, "[trap]", 6u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v2, 0, v4, "[item]", 6u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v2, 0, v4, "[quest]", 7u) == 0 )
              *uArg1 = 3;
          }
          else
          {
            *uArg1 = 2;
          }
        }
        else
        {
          *uArg1 = 1;
        }
      }
      else
      {
        *uArg1 = 0;
      }
    }
  }
  if ( v5 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 容器模板实例族（0x504620~0x507690 区间；list<T>/vector<CnMonsterTemp> 等辅助函数；
//   其中 sub_5046D0/4760/47F0/48F0 为 std::list 容量检查（"list<T> too long"），
//   sub_508F60 为 "vector<T> too long"，属 CRT/STL 实例化，非游戏语义）
// ------------------------------------------------------------

// ------------------------------------------------------------
// 0x504620 sub_504620
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_504620(uint32_t *pArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  sub_5044B0(pArg1, uArg2, uArg3);
  return &pArg1[6 * (uint32_t)uArg2];
}



// ------------------------------------------------------------
// 0x504650 sub_504650
// ------------------------------------------------------------
int /*stdcall*/ sub_504650(int nArg1, int nArg2, int nArg3)
{
  sub_4BF340(nArg1, nArg2, nArg3);
  return nArg1 + 16 * nArg2;
}



// ------------------------------------------------------------
// 0x504680 sub_504680
// ------------------------------------------------------------
void /*thiscall*/ sub_504680(void *this)
{
  *(uint32_t *)this = -1;
  *((uint8_t *)this + 4) = 1;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 7) = 1;
  *((uint32_t *)this + 6) = 1;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  if ( *((uint32_t *)this + 11) != 0 )
    j__free(*((void **)this + 11));
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
}



// ------------------------------------------------------------
// 0x5046D0 sub_5046D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5046D0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 97612893 - fld_e2 < uArg2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
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
// 0x504760 sub_504760
// ------------------------------------------------------------
int /*thiscall*/ sub_504760(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 0xFFFFFFF - fld_e2 < uArg2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
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
// 0x5047F0 sub_5047F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5047F0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 82595524 - fld_e2 < uArg2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
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
// 0x504880 sub_504880
// ------------------------------------------------------------
void /*noreturn*/ sub_504880()
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
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x5048F0 sub_5048F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5048F0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 0x7FFFFFF - fld_e2 < uArg2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
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
// 0x504980 sub_504980
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_504980(uint32_t *this, int nArg2, int nArg3, uint32_t *pArg4)
{
  *this = nArg2;
  *(this + 1) = nArg3;
  *(this + 8) = 15;
  *(this + 7) = 0;
  *((uint8_t *)this + 12) = 0;
  sub_4014D0((std::_String_base *)(this + 2), pArg4, 0, -1);
  *(this + 9) = pArg4[7];
  *(this + 10) = pArg4[8];
  *(this + 11) = pArg4[9];
  *(this + 12) = pArg4[10];
  return this;
}



// ------------------------------------------------------------
// 0x5049E0 sub_5049E0
// ------------------------------------------------------------
int /*cdecl*/ sub_5049E0(int nArg1, int nArg2, int nArg3)
{
  int nArg22; // esi
  int nArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    nArg22 -= 36;
    nArg32 -= 36;
    sub_4014D0((std::_String_base *)nArg32, nArg22, 0, -1);
    *(uint32_t *)(nArg32 + 28) = *(uint32_t *)(nArg22 + 28);
    *(uint8_t *)(nArg32 + 32) = *(uint8_t *)(nArg22 + 32);
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x504A30 sub_504A30
// ------------------------------------------------------------
int /*cdecl*/ sub_504A30(int pArg1, int nArg2, int nArg3)
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != nArg2 )
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)(nArg32 + 24) = 15;
      *(uint32_t *)(nArg32 + 20) = 0;
      *(uint8_t *)(nArg32 + 4) = 0;
      sub_4014D0((std::_String_base *)nArg32, pArg1, 0, -1);
      *(uint32_t *)(nArg32 + 28) = *(uint32_t *)(pArg1 + 28);
      *(uint8_t *)(nArg32 + 32) = *(uint8_t *)(pArg1 + 32);
    }
    nArg32 += 36;
    LOBYTE(v7) = 0;
    pArg1 += 36;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x504AF0 sub_504AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_504AF0(int this)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 28) = 1;
  return this;
}



// ------------------------------------------------------------
// 0x504B50 sub_504B50
// ------------------------------------------------------------
void /*thiscall*/ sub_504B50(void *this)
{
  *(uint32_t *)this = -1;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 1) = 0;
  if ( *((uint32_t *)this + 5) != 0 )
    j__free(*((void **)this + 5));
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
}



// ------------------------------------------------------------
// 0x504B90 sub_504B90
// ------------------------------------------------------------
int /*thiscall*/ sub_504B90(int this)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(uint8_t *)(this + 32) = 0;
  *(uint32_t *)(this + 28) = 1;
  return this;
}



// ------------------------------------------------------------
// 0x504BF0 sub_504BF0
// ------------------------------------------------------------
char /*thiscall*/ sub_504BF0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x1FFFFFFF )
    sub_504880(this);
  pMem = (char *)operator new(8 * uArg2);
  *(this + 3) = &pMem[8 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x504C50 sub_504C50
// ------------------------------------------------------------
char /*thiscall*/ sub_504C50(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xAAAAAAA )
    sub_504880(this);
  pMem = (char *)operator new(24 * uArg2);
  *(this + 3) = &pMem[24 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x504CA0 sub_504CA0
// ------------------------------------------------------------
int /*thiscall*/ sub_504CA0(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)
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
      sub_42CB90(this);
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
// 0x504F70 sub_504F70
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_504F70(int this, int pArg2, unsigned int uArg3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ecx
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v12; // eax
  int fld_87; // ecx
  int fld_88; // eax
  uint32_t *v15; // ebx
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v18; // edi
  void *fld_83; // eax
  int fld_86; // edi
  int v21; // edi
  int fld_42; // [esp-18h] [ebp-44h]
  int fld_85; // [esp-Ch] [ebp-38h]
  unsigned int fld_84; // [esp-8h] [ebp-34h]
  int v25; // [esp+0h] [ebp-2Ch] BYREF
  uint32_t v26[5]; // [esp+Ch] [ebp-20h] BYREF
  int v27; // [esp+28h] [ebp-4h]
  int v28; // [esp+38h] [ebp+Ch]
  char *Blocka; // [esp+3Ch] [ebp+10h]
  void *Blockb; // [esp+3Ch] [ebp+10h]

  v5 = Block[1];
  v26[0] = *Block;
  v6 = Block[2];
  v26[1] = v5;
  v26[3] = Block[3];
  fld_4 = *(uint32_t *)(this + 4);
  v26[4] = &v25;
  v26[2] = v6;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 4;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    else
      fld_8 = 0;
    if ( 0xFFFFFFF - fld_8 < uArg3 )
      sub_42CB90(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(void **)(this + 8);
      Blockb = fld_83;
      if ( ((int)fld_83 - pArg2) >> 4 >= uArg3 )
      {
        v21 = (int)fld_83 - 16 * uArg3;
        *(uint32_t *)(this + 8) = sub_602460(v21, fld_83, fld_83);
        sub_4BF320(pArg2, v21, (int)Blockb);
        return sub_453C20(pArg2, pArg2 + 16 * uArg3, v26);
      }
      else
      {
        sub_602460(pArg2, fld_83, pArg2 + 16 * uArg3);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 4);
        fld_85 = *(uint32_t *)(this + 8);
        v27 = 2;
        sub_504650(fld_85, fld_84, v26);
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        return sub_453C20(pArg2, fld_86 - 16 * uArg3, v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )
        v12 = (result >> 1) + result;
      else
        v12 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
      else
        fld_87 = 0;
      if ( v12 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
        else
          fld_88 = 0;
        v12 = uArg3 + fld_88;
      }
      v28 = 16 * v12;
      Blocka = (char *)operator new(16 * v12);
      fld_42 = *(uint32_t *)(this + 4);
      v27 = 0;
      v15 = (uint32_t *)sub_602460(fld_42, pArg2, Blocka);
      sub_4BF340(v15, (uint32_t *)uArg3, v26);
      sub_602460(pArg2, *(uint32_t *)(this + 8), &v15[4 * uArg3]);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;
      else
        fld_89 = 0;
      v18 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v28];
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];
      *(uint32_t *)(this + 4) = Blocka;
      return (unsigned int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5051D0 sub_5051D0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_5051D0(int nArg1, int nArg2, uint32_t *uArg3)
{
  uint32_t *pMem; // esi
  void *v5[9]; // [esp+0h] [ebp-24h] BYREF

  v5[5] = v5;
  pMem = operator new(0x34u);
  v5[4] = pMem;
  v5[8] = (void *)1;
  v5[3] = pMem;
  if ( pMem != nullptr )
    sub_504980(pMem, nArg1, nArg2, uArg3);
  return pMem;
}



// ------------------------------------------------------------
// 0x505250 sub_505250
// ------------------------------------------------------------
void /*thiscall*/ sub_505250(int this, int nArg2, unsigned int uArg3, int pArg4)
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
      sub_504880(this);
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
// 0x5054A0 sub_5054A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5054A0(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)
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
      sub_504880(this);
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
// 0x505770 sub_505770
// ------------------------------------------------------------
int /*thiscall*/ sub_505770(int *this, uint32_t *pArg2, unsigned int uArg3, uint32_t *Block)
{
  int v5; // edx
  int fld_e1; // ebx
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
  uint32_t *v29; // [esp+3Ch] [ebp+Ch]
  char *Blocka; // [esp+40h] [ebp+10h]
  void *Blockb; // [esp+40h] [ebp+10h]

  v5 = Block[1];
  fld_e1 = *(this + 1);
  v26[0] = *Block;
  v7 = Block[2];
  v26[1] = v5;
  v8 = Block[3];
  result = Block[4];
  v26[5] = &v25;
  v26[2] = v7;
  v26[3] = v8;
  v26[4] = result;
  if ( fld_e1 != 0 )
  {
    result = 1717986919 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 20;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e2 = 0;
    if ( 214748364 - fld_e2 < uArg3 )
      sub_4CEAB0(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((uint8_t *)fld_e23 - (uint8_t *)pArg2) / 20 >= uArg3 )
      {
        v28 = (int)fld_e23 - 20 * uArg3;
        *(this + 2) = sub_4FBDE0(v28, fld_e23, fld_e23);
        sub_57A4A0(pArg2, v28, Blockb);
        return (int)sub_655A00(pArg2, &pArg2[5 * uArg3], v26);
      }
      else
      {
        sub_4FBDE0(pArg2, fld_e23, &pArg2[5 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pArg2) / 20;
        fld_e25 = *(this + 2);
        v27 = 2;
        sub_57A4C0(fld_e25, fld_e24, v26);
        fld_e26 = 20 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return (int)sub_655A00(pArg2, (uint32_t *)(fld_e26 - 20 * uArg3), v26);
      }
    }
    else
    {
      if ( 214748364 - (fld_e3 >> 1) >= fld_e3 )
        v14 = (fld_e3 >> 1) + fld_e3;
      else
        v14 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 20;
      else
        fld_e27 = 0;
      if ( v14 < uArg3 + fld_e27 )
        v14 = uArg3 + sub_45E580(this);
      v16 = 20 * v14;
      Blocka = (char *)operator new(20 * v14);
      fld_e12 = *(this + 1);
      v27 = 0;
      v29 = (uint32_t *)sub_4FBDE0(fld_e12, pArg2, Blocka);
      sub_655A40(v29, (uint32_t *)uArg3, v26);
      sub_4FBDE0(pArg2, *(this + 2), &v29[5 * uArg3]);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 20;
      v18 = fld_e13 + uArg3;
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
// 0x505A30 sub_505A30
// ------------------------------------------------------------
int /*thiscall*/ sub_505A30(int *this, int pArg2, unsigned int uArg3, int *Block)
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
  fld_e1 = *(this + 1);
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 12;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_4CEAB0(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 12 >= uArg3 )
      {
        v27 = (int)fld_e23 - 12 * uArg3;
        *(this + 2) = sub_59EE30(v27, fld_e23, fld_e23);
        sub_504450(pArg2, v27, Blockb);
        return sub_5043B0(pArg2, pArg2 + 12 * uArg3, v25);
      }
      else
      {
        sub_59EE30(pArg2, fld_e23, pArg2 + 12 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 12;
        fld_e25 = *(this + 2);
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return sub_5043B0(pArg2, fld_e26 - 12 * uArg3, v25);
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 12;
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);
      v15 = 12 * v13;
      Blocka = (char *)operator new(12 * v13);
      fld_e12 = *(this + 1);
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pArg2, Blocka);
      sub_623C10(v28, uArg3, v25);
      sub_59EE30(pArg2, *(this + 2), v28 + 12 * uArg3);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 12;
      v17 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v15];
      *(this + 2) = (int)&Blocka[12 * v17];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x505CE0 sub_505CE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_505CE0(uint32_t *this, int pArg2)
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
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( sub_504BF0(this, v4) != 0 )
  {
    fld_e1 = *(this + 1);
    v7 = *(uint32_t *)(pArg2 + 8);
    v6 = *(uint32_t *)(pArg2 + 4);
    v12 = 0;
    *(this + 2) = sub_44BD30(v6, v7, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x505D80 sub_505D80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_505D80(uint32_t *this, int pArg2)
{
  unsigned int v2; // eax
  uint32_t *v5; // [esp-14h] [ebp-34h]
  uint32_t *v6; // [esp-10h] [ebp-30h]
  uint32_t *fld_e1; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(pArg2 + 4);
  v10 = &v8;
  pThis = this;
  if ( v2 != 0 )
    v2 = (int)(*(uint32_t *)(pArg2 + 8) - v2) / 24;
  if ( sub_504C50(this, v2) != 0 )
  {
    fld_e1 = (uint32_t *)*(this + 1);
    v6 = *(uint32_t **)(pArg2 + 8);
    v5 = *(uint32_t **)(pArg2 + 4);
    v11 = 0;
    *(this + 2) = sub_4FF050(v5, v6, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x505E20 sub_505E20
// ------------------------------------------------------------
int /*cdecl*/ sub_505E20(int nArg1, int nArg2, int pArg3)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 36 )
  {
    sub_4014D0((std::_String_base *)i, pArg3, 0, -1);
    result = *(uint32_t *)(pArg3 + 28);
    *(uint32_t *)(i + 28) = result;
    *(uint8_t *)(i + 32) = *(uint8_t *)(pArg3 + 32);
  }
  return result;
}



// ------------------------------------------------------------
// 0x505E60 sub_505E60
// ------------------------------------------------------------
int /*cdecl*/ sub_505E60(int nArg1, int nArg2, int nArg3)
{
  return sub_5049E0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x505E80 sub_505E80
// ------------------------------------------------------------
int /*cdecl*/ sub_505E80(int nArg1, int nArg2, int pArg3)
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
      *(uint32_t *)(nArg12 + 24) = 15;
      *(uint32_t *)(nArg12 + 20) = 0;
      *(uint8_t *)(nArg12 + 4) = 0;
      sub_4014D0((std::_String_base *)nArg12, pArg3, 0, -1);
      result = *(uint32_t *)(pArg3 + 28);
      *(uint32_t *)(nArg12 + 28) = result;
      *(uint8_t *)(nArg12 + 32) = *(uint8_t *)(pArg3 + 32);
    }
    nArg12 += 36;
    LOBYTE(v6) = 0;
    --nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x505F40 sub_505F40
// ------------------------------------------------------------
int /*thiscall*/ sub_505F40(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_504470(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);
  result = sub_504760(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x505F80 sub_505F80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_505F80(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 24;
  else
    v6 = 0;
  sub_504CA0(this, pszArg3, 1u, Block);
  *uArg2 = *(this + 1) + 24 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x505FF0 sub_505FF0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_505FF0(unsigned int *this, unsigned int uArg2, int nArg3)
{
  int fld_e1; // edx
  unsigned int result; // eax
  int fld_e2; // eax
  void *v7; // edx

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    result = (int)(*(this + 2) - fld_e1) >> 2;
  else
    result = 0;
  if ( result >= uArg2 )
  {
    if ( fld_e1 != 0 )
    {
      result = *(this + 2);
      if ( uArg2 < (int)(result - fld_e1) >> 2 )
      {
        v7 = (void *)(fld_e1 + 4 * uArg2);
        if ( v7 != (void *)result )
        {
          result = (unsigned int)memcpy_0(v7, (const void *)result, 0);
          *(this + 2) = result;
        }
      }
    }
  }
  else
  {
    if ( fld_e1 != 0 )
      fld_e2 = (int)(*(this + 2) - fld_e1) >> 2;
    else
      fld_e2 = 0;
    return sub_430C80((void *)*(this + 2), uArg2 - fld_e2, (int)&nArg3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x506080 sub_506080
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506080(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 24;
  else
    v6 = 0;
  sub_5054A0(this, pszArg3, 1u, Block);
  *uArg2 = *(this + 1) + 24 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x5060F0 sub_5060F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5060F0(int *this, uint32_t *uArg2, uint32_t *uArg3, int *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )
    v6 = ((int)uArg3 - fld_e1) / 12;
  else
    v6 = 0;
  sub_505A30(this, uArg3, 1u, Block);
  *uArg2 = *(this + 1) + 12 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x506160 sub_506160
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506160(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 20 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 20;
  else
    v6 = 0;
  sub_505770(this, pszArg3, 1u, Block);
  *uArg2 = *(this + 1) + 20 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x5061D0 sub_5061D0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5061D0(uint8_t *this, int pArg2)
{
  *(uint32_t *)this = *(uint32_t *)pArg2;
  *(this + 4) = *(uint8_t *)(pArg2 + 4);
  *((uint32_t *)this + 2) = *(uint32_t *)(pArg2 + 8);
  *((uint32_t *)this + 3) = *(uint32_t *)(pArg2 + 12);
  *((uint32_t *)this + 4) = *(uint32_t *)(pArg2 + 16);
  *((uint32_t *)this + 5) = *(uint32_t *)(pArg2 + 20);
  *((uint32_t *)this + 6) = *(uint32_t *)(pArg2 + 24);
  *((uint32_t *)this + 7) = *(uint32_t *)(pArg2 + 28);
  *((uint32_t *)this + 8) = *(uint32_t *)(pArg2 + 32);
  *((uint32_t *)this + 9) = *(uint32_t *)(pArg2 + 36);
  sub_435020((void *)(pArg2 + 40));
  return this;
}



// ------------------------------------------------------------
// 0x506230 sub_506230
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506230(uint32_t *this, uint32_t *pArg2)
{
  *this = *pArg2;
  *(this + 1) = pArg2[1];
  *(this + 2) = pArg2[2];
  *(this + 3) = pArg2[3];
  *(this + 4) = pArg2[4];
  *(this + 5) = pArg2[5];
  *(this + 6) = pArg2[6];
  *(this + 7) = pArg2[7];
  *(this + 8) = pArg2[8];
  sub_505CE0(this + 9, (int)(pArg2 + 9));
  return this;
}



// ------------------------------------------------------------
// 0x506280 sub_506280
// ------------------------------------------------------------
int /*cdecl*/ sub_506280(int nArg1, int nArg2, int nArg3)
{
  int nArg22; // esi
  int nArg32; // edi
  int v5; // eax

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    v5 = *(uint32_t *)(nArg22 - 56);
    nArg22 -= 56;
    nArg32 -= 56;
    *(uint32_t *)nArg32 = v5;
    *(uint8_t *)(nArg32 + 4) = *(uint8_t *)(nArg22 + 4);
    *(uint32_t *)(nArg32 + 8) = *(uint32_t *)(nArg22 + 8);
    *(uint32_t *)(nArg32 + 12) = *(uint32_t *)(nArg22 + 12);
    *(uint32_t *)(nArg32 + 16) = *(uint32_t *)(nArg22 + 16);
    *(uint32_t *)(nArg32 + 20) = *(uint32_t *)(nArg22 + 20);
    *(uint32_t *)(nArg32 + 24) = *(uint32_t *)(nArg22 + 24);
    *(uint32_t *)(nArg32 + 28) = *(uint32_t *)(nArg22 + 28);
    *(uint32_t *)(nArg32 + 32) = *(uint32_t *)(nArg22 + 32);
    *(uint32_t *)(nArg32 + 36) = *(uint32_t *)(nArg22 + 36);
    sub_4ED3F0(nArg32 + 40, nArg22 + 40);
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x506300 sub_506300
// ------------------------------------------------------------
void */*thiscall*/ sub_506300(void *this)
{
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *(uint32_t *)this = -1;
  *((uint8_t *)this + 4) = 1;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 7) = 1;
  *((uint32_t *)this + 6) = 1;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  if ( *((uint32_t *)this + 11) != 0 )
    j__free(*((void **)this + 11));
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x506360 sub_506360
// ------------------------------------------------------------
void */*thiscall*/ sub_506360(void *this)
{
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 2) = 1;
  *((uint32_t *)this + 1) = 1;
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = -1;
  *((uint32_t *)this + 8) = -1;
  *((uint32_t *)this + 7) = -1;
  if ( *((uint32_t *)this + 10) != 0 )
    j__free(*((void **)this + 10));
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x5063B0 sub_5063B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5063B0(int this, uint32_t *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 24;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 24 )
    return sub_505F80((int *)this, &Block, *(char **)(this + 8), Block);
  fld_82 = *(uint32_t **)(this + 8);
  result = sub_5044B0(fld_82, (uint32_t *)1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 6;
  return result;
}



// ------------------------------------------------------------
// 0x506440 sub_506440
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_506440(int *this, uint32_t *Block)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  unsigned int result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 4;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 4 )
    return sub_504F70((int)this, *(this + 2), 1u, Block);
  fld_e22 = *(this + 2);
  result = sub_4BF340(fld_e22, 1, Block);
  *(this + 2) = fld_e22 + 16;
  return result;
}



// ------------------------------------------------------------
// 0x5064B0 sub_5064B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5064B0(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_5051D0(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);
  result = sub_5046D0(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x5064F0 sub_5064F0
// ------------------------------------------------------------
void /*thiscall*/ sub_5064F0(int *this, int nArg2)
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
    sub_505250((int)this, *(this + 2), 1u, nArg2);
  }
}



// ------------------------------------------------------------
// 0x506560 sub_506560
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506560(int this, uint32_t *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 24;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 24 )
    return sub_506080((int *)this, &Block, *(char **)(this + 8), Block);
  fld_82 = *(uint32_t **)(this + 8);
  result = sub_5044B0(fld_82, (uint32_t *)1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 6;
  return result;
}



// ------------------------------------------------------------
// 0x5065F0 sub_5065F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5065F0(int this, uint32_t *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  int fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 20;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 20 )
    return sub_506160((int *)this, &Block, *(char **)(this + 8), Block);
  fld_82 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_655A40(fld_82, 1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 20;
  return result;
}



// ------------------------------------------------------------
// 0x506680 sub_506680
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506680(int *this, int *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 12;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 12 )
    return sub_5060F0(this, &Block, (uint32_t *)*(this + 2), Block);
  fld_e22 = *(this + 2);
  result = (uint32_t *)sub_623C10(fld_e22, 1, Block);
  *(this + 2) = fld_e22 + 12;
  return result;
}



// ------------------------------------------------------------
// 0x506700 sub_506700
// ------------------------------------------------------------
int /*stdcall*/ sub_506700(int nArg1, int nArg2, int nArg3)
{
  sub_505E80(nArg1, nArg2, nArg3);
  return nArg1 + 36 * nArg2;
}



// ------------------------------------------------------------
// 0x506730 sub_506730
// ------------------------------------------------------------
void /*thiscall*/ sub_506730(int *this, int pArg2, unsigned int uArg3, int pArg4)
{
  char v5; // cl
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v11; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e28; // ecx
  int fld_e13; // eax
  unsigned int v16; // edi
  void *fld_e14; // eax
  int fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-68h]
  int fld_e25; // [esp-Ch] [ebp-5Ch]
  unsigned int fld_e24; // [esp-8h] [ebp-58h]
  int v24; // [esp+0h] [ebp-50h] BYREF
  void *Block; // [esp+Ch] [ebp-44h]
  int *pThis; // [esp+10h] [ebp-40h]
  char *pMem2; // [esp+14h] [ebp-3Ch]
  char v28[4]; // [esp+18h] [ebp-38h] BYREF
  void *v29; // [esp+1Ch] [ebp-34h]
  int v30; // [esp+2Ch] [ebp-24h]
  unsigned int v31; // [esp+30h] [ebp-20h]
  int v32; // [esp+34h] [ebp-1Ch]
  char v33; // [esp+38h] [ebp-18h]
  int dword_796E502; // [esp+3Ch] [ebp-14h]
  int *v35; // [esp+40h] [ebp-10h]
  int v36; // [esp+4Ch] [ebp-4h]
  int v37; // [esp+58h] [ebp+8h]
  int v38; // [esp+5Ch] [ebp+Ch]
  int fld_e232; // [esp+60h] [ebp+10h]

  v35 = &v24;
  dword_796E502 = dword_796E50;
  pThis = this;
  v31 = 15;
  v30 = 0;
  LOBYTE(v29) = 0;
  sub_4014D0((std::_String_base *)v28, pArg4, 0, -1);
  v5 = *(uint8_t *)(pArg4 + 32);
  v32 = *(uint32_t *)(pArg4 + 28);
  v33 = v5;
  fld_e1 = *(this + 1);
  v36 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 36;
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 36;
    else
      fld_e2 = 0;
    if ( 119304647 - fld_e2 < uArg3 )
      sub_4CEAB0(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 36;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = *(this + 2);
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 36 >= uArg3 )
      {
        v37 = fld_e23 - 36 * uArg3;
        *(this + 2) = sub_504A30(v37, fld_e23, fld_e23);
        sub_505E60(pArg2, v37, fld_e232);
        sub_505E20(pArg2, pArg2 + 36 * uArg3, v28);
      }
      else
      {
        sub_504A30(pArg2, fld_e23, pArg2 + 36 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 36;
        fld_e25 = *(this + 2);
        LOBYTE(v36) = 3;
        sub_506700(fld_e25, fld_e24, v28);
        fld_e26 = 36 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v36 = 0;
        sub_505E20(pArg2, fld_e26 - 36 * uArg3, v28);
      }
    }
    else
    {
      if ( 119304647 - (fld_e3 >> 1) >= fld_e3 )
        v11 = (fld_e3 >> 1) + fld_e3;
      else
        v11 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 36;
      else
        fld_e27 = 0;
      if ( v11 < uArg3 + fld_e27 )
        v11 = uArg3 + sub_504390(this);
      v38 = 36 * v11;
      pMem = (char *)operator new(36 * v11);
      fld_e12 = *(this + 1);
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;
      pMem2 = (char *)sub_504A30(fld_e12, pArg2, pMem);
      sub_505E80(pMem2, uArg3, v28);
      fld_e28 = *(this + 2);
      pMem2 += 36 * uArg3;
      sub_504A30(pArg2, fld_e28, pMem2);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 36;
      v16 = fld_e13 + uArg3;
      fld_e14 = (void *)*(this + 1);
      if ( fld_e14 != nullptr )
      {
        sub_4D0970(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v38];
      *(this + 2) = (int)&pMem[36 * v16];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v31 >= 0x10 )
    j__free(v29);
}


// ------------------------------------------------------------
// 0x506A60 sub_506A60
// ------------------------------------------------------------
int /*cdecl*/ sub_506A60(int nArg1, int nArg2, int pArg3)
{
  int result; // eax
  int i; // esi

  result = nArg2;
  for ( i = nArg1; i != nArg2; i += 56 )
  {
    *(uint32_t *)i = *(uint32_t *)pArg3;
    *(uint8_t *)(i + 4) = *(uint8_t *)(pArg3 + 4);
    *(uint32_t *)(i + 8) = *(uint32_t *)(pArg3 + 8);
    *(uint32_t *)(i + 12) = *(uint32_t *)(pArg3 + 12);
    *(uint32_t *)(i + 16) = *(uint32_t *)(pArg3 + 16);
    *(uint32_t *)(i + 20) = *(uint32_t *)(pArg3 + 20);
    *(uint32_t *)(i + 24) = *(uint32_t *)(pArg3 + 24);
    *(uint32_t *)(i + 28) = *(uint32_t *)(pArg3 + 28);
    *(uint32_t *)(i + 32) = *(uint32_t *)(pArg3 + 32);
    *(uint32_t *)(i + 36) = *(uint32_t *)(pArg3 + 36);
    sub_4ED3F0(i + 40, pArg3 + 40);
    result = nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x506AD0 sub_506AD0
// ------------------------------------------------------------
int /*cdecl*/ sub_506AD0(int nArg1, int nArg2, int nArg3)
{
  return sub_506280(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x506AF0 sub_506AF0
// ------------------------------------------------------------
int /*cdecl*/ sub_506AF0(int pArg1, int nArg2, int nArg3)
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != nArg2 )
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)nArg32 = *(uint32_t *)pArg1;
      *(uint8_t *)(nArg32 + 4) = *(uint8_t *)(pArg1 + 4);
      *(uint32_t *)(nArg32 + 8) = *(uint32_t *)(pArg1 + 8);
      *(uint32_t *)(nArg32 + 12) = *(uint32_t *)(pArg1 + 12);
      *(uint32_t *)(nArg32 + 16) = *(uint32_t *)(pArg1 + 16);
      *(uint32_t *)(nArg32 + 20) = *(uint32_t *)(pArg1 + 20);
      *(uint32_t *)(nArg32 + 24) = *(uint32_t *)(pArg1 + 24);
      *(uint32_t *)(nArg32 + 28) = *(uint32_t *)(pArg1 + 28);
      *(uint32_t *)(nArg32 + 32) = *(uint32_t *)(pArg1 + 32);
      *(uint32_t *)(nArg32 + 36) = *(uint32_t *)(pArg1 + 36);
      sub_435020((void *)(pArg1 + 40));
    }
    nArg32 += 56;
    LOBYTE(v7) = 0;
    pArg1 += 56;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x506BE0 sub_506BE0
// ------------------------------------------------------------
void /*cdecl*/ sub_506BE0(int nArg1, int pArg2)
{
  int nArg12; // esi
  const char *psz; // edi
  unsigned int nLen; // eax
  int nLen2; // ecx
  const char *p_Block; // esi
  int nCmp; // edx
  int v8; // edx
  int v9; // edi
  int v10; // ecx
  unsigned int v11; // esi
  int *v12; // eax
  int i; // [esp+0h] [ebp-30h]
  void *Block; // [esp+8h] [ebp-28h] BYREF
  unsigned int v15; // [esp+18h] [ebp-18h]
  unsigned int v16; // [esp+1Ch] [ebp-14h]
  int dword_796E502; // [esp+20h] [ebp-10h]
  int v18; // [esp+2Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  v16 = 15;
  v15 = 0;
  LOBYTE(Block) = 0;
  v18 = 0;
  if ( nArg1 > 0 )
  {
    for ( i = nArg1; i != 0; --i )
    {
      sub_443370();
      nArg12 = 0;
      nArg1 = 0;
      while ( 1 )
      {
        psz = off_795AC0[(uint8_t)dword_6FC398[nArg12]];
        nLen = strlen(psz);
        if ( v15 == 0 )
          goto LABEL_11;
        nLen2 = v15;
        if ( v15 >= nLen )
          nLen2 = nLen;
        p_Block = (const char *)Block;
        if ( v16 < 0x10 )
          p_Block = (const char *)&Block;
        nCmp = memcmp(p_Block, psz, nLen2);
        nArg12 = nArg1;
        if ( nCmp == 0 )
        {
LABEL_11:
          if ( v15 >= nLen && v15 == nLen )
            break;
        }
        nArg1 = ++nArg12;
        if ( nArg12 >= 27 )
          goto LABEL_21;
      }
      v8 = *(uint32_t *)(pArg2 + 44);
      v9 = dword_6FC398[nArg12];
      v10 = pArg2 + 40;
      nArg1 = v9;
      if ( v8 != 0 )
        v11 = (*(uint32_t *)(pArg2 + 48) - v8) >> 2;
      else
        v11 = 0;
      if ( v8 != 0 && v11 < (*(uint32_t *)(pArg2 + 52) - v8) >> 2 )
      {
        v12 = *(int **)(pArg2 + 48);
        *v12 = v9;
        *(uint32_t *)(v10 + 8) = v12 + 1;
      }
      else
      {
        sub_430C80(*(void **)(pArg2 + 48), 1, (int)&nArg1);
      }
LABEL_21:
      ;
    }
    if ( v16 >= 0x10 )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x506D30 sub_506D30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506D30(int *this, uint32_t *uArg2, int nArg3, int nArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 36 != 0 )
    v6 = (nArg3 - fld_e1) / 36;
  else
    v6 = 0;
  sub_506730(this, nArg3, 1u, nArg4);
  *uArg2 = *(this + 1) + 36 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x506DA0 sub_506DA0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_506DA0(int nArg1, int nArg2, uint32_t *uArg3)
{
  uint32_t *pMem; // esi
  void *v5[9]; // [esp+0h] [ebp-24h] BYREF

  v5[5] = v5;
  pMem = operator new(0x3Cu);
  v5[4] = pMem;
  v5[8] = (void *)1;
  v5[3] = pMem;
  if ( pMem != nullptr )
  {
    pMem[1] = nArg2;
    *pMem = nArg1;
    sub_506230(pMem + 2, uArg3);
  }
  return pMem;
}



// ------------------------------------------------------------
// 0x506E30 sub_506E30
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_506E30(int nArg1, int nArg2, uint32_t *pArg3)
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v6[9]; // [esp+0h] [ebp-24h] BYREF

  v6[5] = v6;
  pMem = operator new(0x28u);
  pMem2 = pMem;
  v6[4] = pMem;
  v6[8] = (void *)1;
  v6[3] = pMem;
  if ( pMem != nullptr )
  {
    *pMem = nArg1;
    pMem[1] = nArg2;
    pMem[2] = *pArg3;
    pMem[3] = pArg3[1];
    pMem[4] = pArg3[2];
    pMem[5] = pArg3[3];
    sub_505D80(pMem + 6, (int)(pArg3 + 4));
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x506ED0 sub_506ED0
// ------------------------------------------------------------
void /*cdecl*/ sub_506ED0(int nArg1, int nArg2, int pArg3)
{
  int nArg12; // esi
  uint32_t v4[6]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v4[5] = v4;
  v4[4] = nArg1;
  v5 = 0;
  while ( nArg2 != 0 )
  {
    v4[3] = nArg12;
    LOBYTE(v5) = 1;
    if ( nArg12 != 0 )
    {
      *(uint32_t *)nArg12 = *(uint32_t *)pArg3;
      *(uint8_t *)(nArg12 + 4) = *(uint8_t *)(pArg3 + 4);
      *(uint32_t *)(nArg12 + 8) = *(uint32_t *)(pArg3 + 8);
      *(uint32_t *)(nArg12 + 12) = *(uint32_t *)(pArg3 + 12);
      *(uint32_t *)(nArg12 + 16) = *(uint32_t *)(pArg3 + 16);
      *(uint32_t *)(nArg12 + 20) = *(uint32_t *)(pArg3 + 20);
      *(uint32_t *)(nArg12 + 24) = *(uint32_t *)(pArg3 + 24);
      *(uint32_t *)(nArg12 + 28) = *(uint32_t *)(pArg3 + 28);
      *(uint32_t *)(nArg12 + 32) = *(uint32_t *)(pArg3 + 32);
      *(uint32_t *)(nArg12 + 36) = *(uint32_t *)(pArg3 + 36);
      sub_435020((void *)(pArg3 + 40));
    }
    nArg12 += 56;
    LOBYTE(v5) = 0;
    --nArg2;
  }
}



// ------------------------------------------------------------
// 0x506FC0 sub_506FC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506FC0(int this, uint32_t *uArg2, uint32_t **Block)
{
  uint32_t *v3; // ebx

  v3 = *Block;
  if ( Block != *(uint32_t ***)(this + 4) )
  {
    *Block[1] = *Block;
    (*Block)[1] = Block[1];
    sub_4CFE40(Block);
    j__free(Block);
    --*(uint32_t *)(this + 8);
  }
  *uArg2 = v3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x507010 sub_507010
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_507010(int *this, int nArg2)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 36;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 36 )
    return sub_506D30(this, &nArg2, *(this + 2), nArg2);
  fld_e22 = *(this + 2);
  result = (uint32_t *)sub_505E80(fld_e22, 1, nArg2);
  *(this + 2) = fld_e22 + 36;
  return result;
}



// ------------------------------------------------------------
// 0x5070A0 sub_5070A0
// ------------------------------------------------------------
void /*thiscall*/ sub_5070A0(uint32_t *this, int pArg2, int nArg3, uint32_t *uArg4, int nArg5)
{
  uint32_t *v5; // esi
  uint32_t *v6; // edi
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  uint32_t *pThis; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  v5 = (uint32_t *)nArg3;
  v9 = v7;
  pThis = this;
  v7[3] = nArg3;
  v10 = 0;
  while ( v5 != uArg4 )
  {
    v6 = sub_506DA0(pArg2, *(uint32_t *)(pArg2 + 4), v5 + 2);
    sub_5047F0(pThis, 1u);
    *(uint32_t *)(pArg2 + 4) = v6;
    *(uint32_t *)v6[1] = v6;
    v5 = (uint32_t *)*v5;
  }
}



// ------------------------------------------------------------
// 0x507150 sub_507150
// ------------------------------------------------------------
int /*thiscall*/ sub_507150(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_506DA0(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);
  result = sub_5047F0(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x507190 sub_507190
// ------------------------------------------------------------
int /*thiscall*/ sub_507190(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_506E30(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);
  result = sub_5048F0(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x5071D0 sub_5071D0
// ------------------------------------------------------------
int /*stdcall*/ sub_5071D0(int nArg1, int nArg2, int nArg3)
{
  sub_506ED0(nArg1, nArg2, nArg3);
  return nArg1 + 56 * nArg2;
}



// ------------------------------------------------------------
// 0x507200 sub_507200
// ------------------------------------------------------------
void /*thiscall*/ sub_507200(int *this, int pArg2, unsigned int uArg3, int nArg4)
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
  int fld_e12; // [esp-18h] [ebp-74h]
  int fld_e25; // [esp-Ch] [ebp-68h]
  unsigned int fld_e24; // [esp-8h] [ebp-64h]
  int v22; // [esp+0h] [ebp-5Ch] BYREF
  uint8_t v23[44]; // [esp+Ch] [ebp-50h] BYREF
  void *v24; // [esp+38h] [ebp-24h]
  void *Block; // [esp+44h] [ebp-18h]
  int *pThis; // [esp+48h] [ebp-14h]
  int *v27; // [esp+4Ch] [ebp-10h]
  int v28; // [esp+58h] [ebp-4h]
  char *v29; // [esp+64h] [ebp+8h]
  int v30; // [esp+68h] [ebp+Ch]
  int v31; // [esp+6Ch] [ebp+10h]

  v27 = &v22;
  pThis = this;
  sub_5061D0(nArg4);
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v28 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 56;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - *(this + 1)) / 56;
    else
      fld_e2 = 0;
    if ( 76695844 - fld_e2 < uArg3 )
      sub_4CEAB0(this);
    if ( *(this + 1) != 0 )
      fld_e22 = (*(this + 2) - *(this + 1)) / 56;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (char *)*(this + 2);
      Block = fld_e23;
      if ( (int)&fld_e23[-pArg2] / 56 >= uArg3 )
      {
        v29 = &fld_e23[-56 * uArg3];
        *(this + 2) = sub_506AF0(v29, fld_e23, fld_e23);
        sub_506AD0(pArg2, v29, Block);
        sub_506A60(pArg2, pArg2 + 56 * uArg3, v23);
      }
      else
      {
        sub_506AF0(pArg2, fld_e23, pArg2 + 56 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 56;
        fld_e25 = *(this + 2);
        LOBYTE(v28) = 3;
        sub_5071D0(fld_e25, fld_e24, v23);
        fld_e26 = 56 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v28 = 0;
        sub_506A60(pArg2, fld_e26 - 56 * uArg3, v23);
      }
    }
    else
    {
      if ( 76695844 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        fld_e27 = (*(this + 2) - *(this + 1)) / 56;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_488DD0(this);
      v31 = 56 * v10;
      pMem = (char *)operator new(56 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      LOBYTE(v28) = 1;
      v30 = sub_506AF0(fld_e12, pArg2, pMem);
      sub_506ED0(v30, uArg3, v23);
      sub_506AF0(pArg2, *(this + 2), 56 * uArg3 + v30);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 56;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_4D0940(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v31];
      *(this + 2) = (int)&pMem[56 * v14];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v24 != nullptr )
    j__free(v24);
}


// ------------------------------------------------------------
// 0x507510 sub_507510
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_507510(uint32_t *this, int pArg2)
{
  int *v3; // eax
  int v5; // [esp-10h] [ebp-30h]
  int v6; // [esp-Ch] [ebp-2Ch]
  int *v7; // [esp-8h] [ebp-28h]
  uint32_t v8[8]; // [esp+0h] [ebp-20h] BYREF

  v8[4] = v8;
  v8[3] = this;
  v3 = (int *)sub_4CE750();
  *(this + 1) = v3;
  *(this + 2) = 0;
  v7 = *(int **)(pArg2 + 4);
  v6 = *v7;
  v5 = *v3;
  v8[7] = 0;
  sub_5070A0(this, v5, v6, v7, pArg2);
  return this;
}



// ------------------------------------------------------------
// 0x507590 sub_507590
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_507590(int *this, uint32_t *uArg2, int nArg3, int nArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 56 != 0 )
    v6 = (nArg3 - fld_e1) / 56;
  else
    v6 = 0;
  sub_507200(this, nArg3, 1u, nArg4);
  *uArg2 = *(this + 1) + 56 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x507600 sub_507600
// ------------------------------------------------------------
void /*thiscall*/ sub_507600(int *this, int nArg2)
{
  int fld_e1; // ebx
  unsigned int fld_e2; // esi
  int fld_e22; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 56;
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) / 56 )
  {
    fld_e22 = *(this + 2);
    sub_506ED0(fld_e22, 1, nArg2);
    *(this + 2) = fld_e22 + 56;
  }
  else
  {
    sub_507590(this, &nArg2, *(this + 2), nArg2);
  }
}



// ============================================================
// §F 0x504600-0x507690 容器辅助族（list/vector/map 模板实例 + 怪物基础参数表）
// ============================================================
// ============================================================
// §G 0x507690-0x50AF40 瓦片地图/副本地图/怪物定义族 + ★ 攻击定义 sub_503BA0
// ============================================================

// ------------------------------------------------------------
// 0x507690 sub_507690 —— 瓦片(tile)定义解析器
//   标签族：[IMAGE]/[tile type]（子枚举 [basic]/[extended]）/子枚举 [pass type]；
//   加载失败打印 "TILE LOAD FAIL! [%s]"。
// ------------------------------------------------------------
char /*cdecl*/ sub_507690(int nArg1, const char *ArgList)
{
  int nArg12; // esi
  int v4; // ebx
  int v5; // edi
  int j; // edi
  int *v7; // esi
  char v8; // [esp-10h] [ebp-68h] BYREF
  uint8_t *v9; // [esp-4h] [ebp-5Ch]
  char *i; // [esp+Ch] [ebp-4Ch]
  uint8_t v11[4]; // [esp+10h] [ebp-48h] BYREF
  void *Block; // [esp+14h] [ebp-44h]
  unsigned int v13; // [esp+24h] [ebp-34h]
  unsigned int v14; // [esp+28h] [ebp-30h]
  uint8_t v15[4]; // [esp+2Ch] [ebp-2Ch] BYREF
  void *v16; // [esp+30h] [ebp-28h]
  void *v17; // [esp+40h] [ebp-18h]
  unsigned int v18; // [esp+44h] [ebp-14h]
  int dword_796E502; // [esp+48h] [ebp-10h]
  int v20; // [esp+54h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)ArgList) != 0 )
  {
    nArg12 = nArg1;
    sub_4D0AE0(nArg1);
    v4 = 0;
    v18 = 15;
    v17 = nullptr;
    LOBYTE(v16) = 0;
    v20 = 1;
    v14 = 15;
    v13 = 0;
    LOBYTE(Block) = 0;
    while ( (uint8_t)sub_443430(v15) != 0 )
    {
      sub_442B20(v15);
      if ( sub_40BF00((std::_String_base *)v15, 0, (unsigned int)v17, "[IMAGE]", 7u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v15, 0, (unsigned int)v17, "[tile type]", 0xBu) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v15, 0, (unsigned int)v17, "[pass type]", 0xBu) == 0 )
          {
            v5 = *(uint8_t *)(nArg12 + 32) != 0 ? 10 : 30;
            i = &v8;
            sub_489720(v5, v8, nullptr, 0, 0);
            for ( i = (char *)v5; i != nullptr; --i )
            {
              sub_505FF0((unsigned int *)(v4 + *(uint32_t *)(nArg12 + 40)), 0xEu, 0);
              for ( j = 0; j < 56; j += 4 )
              {
                v7 = (int *)(j + *(uint32_t *)(*(uint32_t *)(nArg12 + 40) + v4 + 4));
                *v7 = sub_4423D0(nullptr);
                nArg12 = nArg1;
              }
              v4 += 16;
            }
            v4 = 0;
          }
        }
        else
        {
          v9 = v11;
          sub_443370();
          if ( sub_40BF00((std::_String_base *)v11, 0, v13, "[basic]", 7u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v11, 0, v13, "[extended]", 0xAu) == 0 )
              *(uint8_t *)(nArg12 + 32) = 1;
          }
          else
          {
            *(uint8_t *)(nArg12 + 32) = 0;
          }
        }
      }
      else
      {
        v9 = (uint8_t *)nArg12;
        sub_443370();
        *(uint32_t *)(nArg12 + 28) = sub_4423D0(nullptr);
      }
    }
    if ( v14 >= 0x10 )
      j__free(Block);
    v14 = 15;
    v13 = 0;
    LOBYTE(Block) = 0;
    if ( v18 >= 0x10 )
      j__free(v16);
    return 1;
  }
  else
  {
    off_77F3FC("TILE LOAD FAIL! [%s]", ArgList);
    return 0;
  }
}



// ------------------------------------------------------------
// 0x5078C0 sub_5078C0 —— 副本地图(dungeon map)定义解析器（0x1D8 字节对象，sub_4D1680 构造）
//   标签族：地图 [map name]/[player number]/[pvp start area]；阴影 [shadow type] 子枚举
//   [mirror]/[more darker]；[dungeon] 子枚举 [type]/[normal]/[boss]/[greed]；瓦片 [tile]/[extended tile]；
//   [elemental property]；视野 [far sight scroll]/[middle sight scroll]/[near sight scroll]；
//   [background animation] 子枚举 [below]；可行区域 [town movable area]/[virtual movable area]；
//   [pathgate pos]/[dungeon start area]；资源 [sound]/[animation]/[passive object]；
//   生成表 [monster]/[champion]/[super champion]/[special passive object]/[NPC]/[item]；
//   [monster spawn pos]/[chaos zone]（子枚举 [left]/[right]）；数量模式 [fixed]/[half]/[ratio]。
//   标签总数 39。调用者：sub_4D2D60 工厂 case 7。未识别标签 → off_77F3FC。
// ------------------------------------------------------------
char /*cdecl*/ sub_5078C0(int pArg1, int ArgList)
{
  const char *v2; // ebx
  int pArg12; // edi
  int v4; // eax
  int *v5; // esi
  int i; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // esi
  int v12; // edi
  uint32_t *v13; // eax
  int v14; // eax
  int v15; // eax
  uint8_t *v16; // eax
  uint8_t *v17; // eax
  uint8_t *v18; // eax
  int i6; // edx
  uint8_t *v20; // ecx
  uint8_t *v21; // eax
  uint32_t *v22; // esi
  int v23; // eax
  int v24; // eax
  void *v25; // eax
  int v26; // eax
  int v27; // eax
  int k; // eax
  int m; // eax
  int *v30; // esi
  int n; // edi
  int ii; // ebx
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int jj; // eax
  int i5; // esi
  int v39; // eax
  int kk; // esi
  int v41; // eax
  int mm; // esi
  int nn; // esi
  int v44; // eax
  int i1; // esi
  int i2; // eax
  int v47; // eax
  int i3; // ebx
  int i4; // eax
  const char *v50; // eax
  int v51; // eax
  void *v53[3]; // [esp-1Ch] [ebp-20Ch] BYREF
  uint8_t *v54; // [esp-10h] [ebp-200h]
  uint8_t *v55; // [esp-Ch] [ebp-1FCh]
  void **v56; // [esp-8h] [ebp-1F8h]
  int j; // [esp-4h] [ebp-1F4h]
  char v58[12]; // [esp+Ch] [ebp-1E4h] BYREF
  uint32_t v59[9]; // [esp+18h] [ebp-1D8h] BYREF
  uint32_t v60[6]; // [esp+4Ch] [ebp-1A4h] BYREF
  uint32_t v61[5]; // [esp+64h] [ebp-18Ch] BYREF
  uint32_t v62[4]; // [esp+78h] [ebp-178h] BYREF
  uint32_t pBuf[6]; // [esp+88h] [ebp-168h] BYREF
  uint32_t v64[2]; // [esp+A0h] [ebp-150h] BYREF
  uint32_t v65[2]; // [esp+A8h] [ebp-148h] BYREF
  int v66; // [esp+B0h] [ebp-140h] BYREF
  bool v67; // [esp+B4h] [ebp-13Ch]
  int v68; // [esp+B8h] [ebp-138h]
  int v69; // [esp+BCh] [ebp-134h]
  int v70; // [esp+C0h] [ebp-130h]
  int v71; // [esp+C4h] [ebp-12Ch]
  int v72; // [esp+C8h] [ebp-128h]
  int v73; // [esp+CCh] [ebp-124h]
  int v74; // [esp+D0h] [ebp-120h]
  int v75; // [esp+D4h] [ebp-11Ch]
  void *v76; // [esp+D8h] [ebp-118h] BYREF
  void *v77; // [esp+DCh] [ebp-114h]
  int v78; // [esp+E8h] [ebp-108h] BYREF
  int v79; // [esp+ECh] [ebp-104h]
  int v80; // [esp+F0h] [ebp-100h]
  int v81; // [esp+F4h] [ebp-FCh]
  void *Block; // [esp+FCh] [ebp-F4h]
  int v83; // [esp+100h] [ebp-F0h]
  int v84; // [esp+104h] [ebp-ECh]
  int v85; // [esp+108h] [ebp-E8h]
  int v86; // [esp+10Ch] [ebp-E4h] BYREF
  int v87; // [esp+110h] [ebp-E0h]
  int v88; // [esp+114h] [ebp-DCh]
  int v89; // [esp+118h] [ebp-D8h]
  int v90; // [esp+11Ch] [ebp-D4h] BYREF
  int v91; // [esp+120h] [ebp-D0h]
  int v92; // [esp+124h] [ebp-CCh]
  int v93; // [esp+128h] [ebp-C8h] BYREF
  int v94; // [esp+12Ch] [ebp-C4h]
  int v95; // [esp+130h] [ebp-C0h]
  int v96; // [esp+134h] [ebp-BCh]
  int v97; // [esp+138h] [ebp-B8h]
  void **v98; // [esp+13Ch] [ebp-B4h]
  int v99; // [esp+140h] [ebp-B0h]
  int v100; // [esp+144h] [ebp-ACh] BYREF
  int v101; // [esp+148h] [ebp-A8h]
  char v102; // [esp+14Fh] [ebp-A1h] BYREF
  uint32_t *v103; // [esp+150h] [ebp-A0h] BYREF
  char v104; // [esp+157h] [ebp-99h] BYREF
  uint8_t v105[28]; // [esp+158h] [ebp-98h] BYREF
  int v106; // [esp+174h] [ebp-7Ch]
  bool v107; // [esp+178h] [ebp-78h]
  char v108[4]; // [esp+17Ch] [ebp-74h] BYREF
  void *v109; // [esp+180h] [ebp-70h]
  int v110; // [esp+190h] [ebp-60h]
  unsigned int v111; // [esp+194h] [ebp-5Ch]
  int v112; // [esp+198h] [ebp-58h]
  int v113; // [esp+19Ch] [ebp-54h]
  int v114; // [esp+1A0h] [ebp-50h]
  int v115; // [esp+1A4h] [ebp-4Ch]
  char v116[4]; // [esp+1A8h] [ebp-48h] BYREF
  uint32_t v117[5]; // [esp+1ACh] [ebp-44h] BYREF
  unsigned int v118; // [esp+1C0h] [ebp-30h]
  int v119; // [esp+1C4h] [ebp-2Ch] BYREF
  void *v120; // [esp+1C8h] [ebp-28h] BYREF
  int v121; // [esp+1D8h] [ebp-18h]
  unsigned int v122; // [esp+1DCh] [ebp-14h]
  int dword_796E502; // [esp+1E0h] [ebp-10h]
  int v124; // [esp+1ECh] [ebp-4h]

  v2 = (const char *)ArgList;
  dword_796E502 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)&unk_9B7308, ArgList) == 0 )
    return 0;
  pArg12 = pArg1;
  sub_4D13A0(pArg1);
  sub_443300(pArg1 + 280, "%s%s", (char)&unk_9B7308);
  v122 = 15;
  v121 = 0;
  LOBYTE(v120) = 0;
  v124 = 0;
  v103 = nullptr;
  sub_41BFE0((void **)&v103, szPassword);
  LOBYTE(v124) = 1;
  v104 = 0;
  sub_504AF0(v108);
  LOBYTE(v124) = 2;
  v86 = -1;
  v87 = 0;
  v88 = 0;
  v89 = 0;
  sub_506300(&v66);
  v78 = -1;
  v81 = 0;
  v80 = 0;
  v79 = 0;
  Block = nullptr;
  v83 = 0;
  v84 = 0;
  LOBYTE(v124) = 4;
  v93 = 0;
  v94 = 0;
  v95 = 0;
  v96 = 0;
  v97 = 0;
  if ( (uint8_t)sub_443430(&v119) == 0 )
    goto LABEL_165;
  while ( 1 )
  {
    sub_442B20(&v119);
    if ( sub_40BF00((std::_String_base *)&v119, 0, v121, "[map name]", 0xAu) == 0 )
    {
      j = *(uint32_t *)(pArg12 + 424);
      sub_443370();
      goto LABEL_164;
    }
    if ( sub_40BF00((std::_String_base *)&v119, 0, v121, "[player number]", 0xFu) == 0 )
    {
      v4 = sub_4423D0(nullptr);
      v56 = nullptr;
      *(uint32_t *)(pArg12 + 336) = v4;
      *(uint32_t *)(pArg12 + 340) = sub_4423D0(v56);
      goto LABEL_164;
    }
    if ( sub_40BF00((std::_String_base *)&v119, 0, v121, "[pvp start area]", 0x10u) == 0 )
    {
      v5 = (int *)(pArg12 + 348);
      for ( i = 3; i != 0; --i )
      {
        v7 = sub_4423D0(nullptr);
        v56 = nullptr;
        *(v5 - 1) = v7;
        v8 = sub_4423D0(v56);
        v55 = nullptr;
        *v5 = v8;
        v9 = sub_4423D0(v55);
        v54 = nullptr;
        v5[1] = v9;
        v5[2] = sub_4423D0(v54);
        v5 += 4;
      }
      goto LABEL_164;
    }
    if ( sub_40BF00((std::_String_base *)&v119, 0, v121, "[shadow type]", 0xDu) == 0 )
    {
      j = (int)&v103;
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v103, "[mirror]") )
      {
        *(uint32_t *)(pArg12 + 392) = 1;
      }
      else if ( sub_43BCF0(&v103, "[more darker]") )
      {
        *(uint32_t *)(pArg12 + 392) = 2;
      }
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[dungeon]") != 0 )
    {
      v10 = pArg12 + 4;
      sub_6569D0(pArg12 + 4);
      v100 = sub_4423D0(&v104);
      if ( v104 != 0 )
      {
        do
        {
          v11 = *(uint32_t *)(v10 + 4);
          v12 = sub_40C0F0(v11, *(uint32_t *)(v11 + 4), &v100);
          sub_437320(1);
          *(uint32_t *)(v11 + 4) = v12;
          v13 = *(uint32_t **)(v12 + 4);
          j = (int)&v104;
          *v13 = v12;
          v100 = sub_4423D0((uint8_t *)j);
        }
        while ( v104 != 0 );
        pArg12 = pArg1;
      }
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[type]") != 0 )
    {
      j = (int)&v103;
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v103, "[normal]") )
      {
        *(uint32_t *)(pArg12 + 16) = 0;
      }
      else if ( sub_43BCF0(&v103, "[boss]") )
      {
        *(uint32_t *)(pArg12 + 16) = 1;
      }
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[greed]") != 0 )
      break;
    if ( (uint8_t)sub_423300(&v119, "[tile]") != 0 )
    {
      sub_4017E0(pArg12 + 124);
      for ( j = (int)&v103; sub_442E10() != 0; j = (int)&v103 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v103);
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[extended tile]") != 0 )
    {
      sub_4017E0(pArg12 + 140);
      for ( j = (int)&v103; sub_442E10() != 0; j = (int)&v103 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v103);
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[elemental property]") != 0 )
    {
      j = (int)&v103;
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      v24 = sub_41ACF0(&v103);
      *(uint32_t *)(pArg12 + 120) = sub_442710(v24);
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[far sight scroll]") != 0 )
    {
      *(uint32_t *)(pArg12 + 156) = sub_4423D0(nullptr);
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[middle sight scroll]") != 0 )
    {
      *(uint32_t *)(pArg12 + 160) = sub_4423D0(nullptr);
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[near sight scroll]") != 0 )
    {
      *(uint32_t *)(pArg12 + 164) = sub_4423D0(nullptr);
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[background animation]") != 0 )
    {
      sub_4D09E0(pArg12 + 168);
      sub_504B90(v105);
      j = (int)&v103;
      for ( LOBYTE(v124) = 6; sub_442E10() != 0; j = (int)&v103 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
      {
        v25 = (void *)sub_41ACF0(&v103);
        sub_406D60(v25);
        j = (int)&v103;
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        v26 = sub_41ACF0(&v103);
        v27 = sub_4425F0(v26);
        v56 = (void **)&v103;
        v106 = v27;
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        v107 = !sub_43BCF0(&v103, "[below]");
        sub_507010(v105);
      }
      LOBYTE(v124) = 4;
      sub_501490(v105);
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[town movable area]") != 0 )
    {
      sub_5E5260((void **)(pArg12 + 184));
      for ( k = sub_4423D0(&v104); v104 != 0; k = sub_4423D0(&v104) )
      {
        v60[0] = k;
        v60[1] = sub_4423D0(nullptr);
        v60[2] = sub_4423D0(nullptr);
        v60[3] = sub_4423D0(nullptr);
        v60[4] = sub_4423D0(nullptr);
        v60[5] = sub_4423D0(nullptr);
        sub_5063B0(v60);
      }
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[virtual movable area]") != 0 )
    {
      sub_5E5260((void **)(pArg12 + 200));
      for ( m = sub_4423D0(&v104); v104 != 0; m = sub_4423D0(&v104) )
      {
        v62[0] = m;
        v62[1] = sub_4423D0(nullptr);
        v62[2] = sub_4423D0(nullptr);
        v62[3] = sub_4423D0(nullptr);
        sub_506440(v62);
      }
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[pathgate pos]") != 0 )
    {
      v30 = (int *)(pArg1 + 216);
      for ( n = 4; n != 0; --n )
      {
        for ( ii = 2; ii != 0; --ii )
          *v30++ = sub_4423D0(nullptr);
      }
      pArg12 = pArg1;
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[dungeon start area]") != 0 )
    {
      v33 = sub_4423D0(nullptr);
      v56 = nullptr;
      *(uint32_t *)(pArg12 + 248) = v33;
      v34 = sub_4423D0(v56);
      v55 = nullptr;
      *(uint32_t *)(pArg12 + 252) = v34;
      v35 = sub_4423D0(v55);
      v54 = nullptr;
      *(uint32_t *)(pArg12 + 256) = v35;
      *(uint32_t *)(pArg12 + 260) = sub_4423D0(v54);
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[sound]") != 0 )
    {
      sub_4017E0(pArg12 + 264);
      for ( j = (int)&v103; sub_442E10() != 0; j = (int)&v103 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v103);
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[animation]") != 0 )
    {
      sub_4CFEA0(pArg12 + 36);
      for ( j = (int)v108; sub_443370() != 0; j = (int)v108 )
      {
        j = (int)&v103;
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        v36 = sub_41ACF0(&v103);
        v112 = sub_4425F0(v36);
        v113 = sub_4423D0(nullptr);
        v114 = sub_4423D0(nullptr);
        v115 = sub_4423D0(nullptr);
        sub_5064B0(v108);
      }
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[passive object]") != 0 )
    {
      sub_6569D0(pArg12 + 48);
      for ( jj = sub_4423D0(&v104); v104 != 0; jj = sub_4423D0(&v104) )
      {
        v86 = jj;
        v87 = sub_4423D0(nullptr);
        v88 = sub_4423D0(nullptr);
        v89 = sub_4423D0(nullptr);
        sub_505F40(&v86);
      }
      goto LABEL_164;
    }
    if ( (uint8_t)sub_423300(&v119, "[monster]") == 0 )
    {
      if ( (uint8_t)sub_423300(&v119, "[champion]") != 0 )
      {
        *(uint32_t *)(pArg12 + 76) = sub_4423D0(nullptr);
      }
      else if ( (uint8_t)sub_423300(&v119, "[item]") != 0 )
      {
        sub_4D1310(pArg12 + 80);
        for ( kk = sub_4423D0(&v104); v104 != 0; kk = sub_4423D0(&v104) )
        {
          sub_506360(v59);
          LOBYTE(v124) = 7;
          v59[0] = kk;
          v59[2] = sub_4423D0(nullptr);
          v59[1] = sub_4423D0(nullptr);
          v59[3] = sub_4423D0(nullptr);
          v59[4] = sub_4423D0(nullptr);
          v59[5] = sub_4423D0(nullptr);
          v59[6] = sub_4423D0(nullptr);
          v59[7] = sub_4423D0(nullptr);
          v59[8] = sub_4423D0(nullptr);
          v41 = sub_4423D0(nullptr);
          if ( v41 > 0 )
          {
            for ( mm = v41; mm != 0; --mm )
            {
              v65[0] = sub_4423D0(nullptr);
              v65[1] = sub_4423D0(nullptr);
              sub_5064F0(v65);
            }
          }
          sub_507150(v59);
          LOBYTE(v124) = 4;
          sub_4CEB20(v59);
        }
      }
      else if ( (uint8_t)sub_423300(&v119, "[special passive object]") != 0 )
      {
        sub_507510(pArg12 + 80);
        LOBYTE(v124) = 8;
        sub_4D1350(pArg12 + 92);
        for ( nn = sub_4423D0(&v104); v104 != 0; nn = sub_4423D0(&v104) )
        {
          sub_504B50(&v78);
          v78 = nn;
          v79 = sub_4423D0(nullptr);
          v80 = sub_4423D0(nullptr);
          v81 = sub_4423D0(nullptr);
          v44 = sub_4423D0(nullptr);
          if ( v44 > 0 )
          {
            for ( i1 = v44; i1 != 0; --i1 )
            {
              memset(pBuf, 255, sizeof(pBuf));
              sub_504500(pBuf);
              sub_506560(pBuf);
            }
          }
          sub_507190(&v78);
        }
        LOBYTE(v124) = 4;
        sub_4D1640(v58);
      }
      else if ( (uint8_t)sub_423300(&v119, "[NPC]") != 0 )
      {
        sub_5E5260((void **)(pArg12 + 104));
        for ( i2 = sub_4423D0(&v104); v104 != 0; i2 = sub_4423D0(&v104) )
        {
          v93 = i2;
          j = (int)&v103;
          sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
          if ( sub_43BCF0(&v103, "[left]") )
          {
            v94 = 0;
          }
          else if ( sub_43BCF0(&v103, "[right]") )
          {
            v94 = 1;
          }
          v95 = sub_4423D0(nullptr);
          v96 = sub_4423D0(nullptr);
          v97 = sub_4423D0(nullptr);
          sub_5065F0(&v93);
        }
      }
      else if ( (uint8_t)sub_423300(&v119, "[monster spawn pos]") != 0 )
      {
        sub_5E5260((void **)(pArg12 + 440));
        v47 = sub_4423D0(nullptr);
        v90 = 0;
        v91 = 0;
        v92 = 0;
        if ( v47 > 0 )
        {
          for ( i3 = v47; i3 != 0; --i3 )
          {
            v90 = sub_4423D0(nullptr);
            v91 = sub_4423D0(nullptr);
            v92 = sub_4423D0(nullptr);
            sub_506680(&v90);
          }
        }
      }
      else if ( (uint8_t)sub_423300(&v119, "[chaos zone]") != 0 )
      {
        sub_5E5260((void **)(pArg12 + 456));
        v102 = 0;
        for ( i4 = sub_4423D0(&v102); v102 != 0; i4 = sub_4423D0(&v102) )
        {
          v61[0] = i4;
          v61[1] = sub_4423D0(nullptr);
          v61[2] = sub_4423D0(nullptr);
          v61[3] = sub_4423D0(nullptr);
          v61[4] = sub_4423D0(nullptr);
          sub_5065F0(v61);
        }
      }
      else
      {
        v98 = v53;
        sub_401690(&v119);
        if ( (uint8_t)sub_442C80((char)v53[0], v53[1], (int)v53[2], (int)v54, (int)v55, (int)v56, j) == 0 )
        {
          v50 = (const char *)v120;
          if ( v122 < 0x10 )
            v50 = (const char *)&v120;
          off_77F3FC("SCRIPT TAG ERROR! [%s] %s", v2, v50);
        }
      }
      goto LABEL_164;
    }
    sub_4D09A0(pArg12 + 60);
    for ( i5 = sub_4423D0(&v104); v104 != 0; i5 = sub_4423D0(&v104) )
    {
      sub_504680(&v66);
      v66 = i5;
      v67 = sub_4423D0(nullptr) != 0;
      v68 = sub_4423D0(nullptr);
      v69 = sub_4423D0(nullptr);
      v70 = sub_4423D0(nullptr);
      v71 = sub_4423D0(nullptr);
      v72 = sub_4423D0(nullptr);
      v73 = sub_4423D0(nullptr);
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v103, "[fixed]") )
      {
        v74 = 0;
      }
      else if ( sub_43BCF0(&v103, "[half]") )
      {
        v74 = 1;
      }
      else if ( sub_43BCF0(&v103, "[ratio]") )
      {
        v74 = 2;
      }
      j = (int)&v103;
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v103, "[normal]") )
      {
        v75 = 0;
      }
      else
      {
        if ( sub_43BCF0(&v103, "[champion]") )
        {
          v75 = 1;
          v39 = sub_4423D0(nullptr);
          if ( v39 <= 0 )
            goto LABEL_119;
        }
        else
        {
          if ( !sub_43BCF0(&v103, "[super champion]") )
          {
            if ( sub_43BCF0(&v103, "[boss]") )
              v75 = 3;
            goto LABEL_125;
          }
          v75 = 2;
          v39 = sub_4423D0(nullptr);
          if ( v39 <= 0 )
          {
LABEL_119:
            sub_5E5260(&v76);
            goto LABEL_125;
          }
        }
        sub_506BE0(v39, &v66);
      }
LABEL_125:
      sub_507600(&v66);
    }
LABEL_164:
    v2 = (const char *)ArgList;
    if ( (uint8_t)sub_443430(&v119) == 0 )
    {
LABEL_165:
      *(uint32_t *)pArg12 = sub_4A2F80(v2);
      v51 = *(uint32_t *)(pArg12 + 4 * dword_78FF38 + 424);
      j = -1;
      v56 = nullptr;
      if ( v51 == 0 )
        v51 = *(uint32_t *)(pArg12 + 424);
      sub_4014D0((std::_String_base *)(pArg12 + 308), v51, v56, j);
      if ( Block != nullptr )
        j__free(Block);
      if ( v77 != nullptr )
        j__free(v77);
      if ( v111 >= 0x10 )
        j__free(v109);
      v111 = 15;
      v110 = 0;
      LOBYTE(v109) = 0;
      LOBYTE(v124) = 0;
      sub_41B010((void **)&v103);
      if ( v122 >= 0x10 )
        j__free(v120);
      return 1;
    }
  }
  v85 = pArg12 + 20;
  sub_5E5260((void **)(pArg12 + 20));
  j = (int)&v103;
  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
  if ( v103 != nullptr )
    v14 = v103[1];
  else
    v14 = 0;
  v100 = 0;
  v99 = -1;
  v101 = 0;
  v98 = (void **)(v14 - 1);
  if ( v14 - 1 <= 0 )
    goto LABEL_164;
  do
  {
    v118 = 15;
    v117[4] = 0;
    LOBYTE(v117[0]) = 0;
    j = 2;
    LOBYTE(v124) = 5;
    v15 = sub_41ACF0(&v103);
    sub_4022F0((std::_String_base *)v116, v101 + v15, j);
    v16 = (uint8_t *)v117[0];
    if ( v118 < 0x10 )
      v16 = v117;
    if ( *v16 == 13 )
      goto LABEL_53;
    v17 = (uint8_t *)v117[0];
    if ( v118 < 0x10 )
      v17 = v117;
    if ( *v17 == 10 )
      goto LABEL_53;
    v18 = (uint8_t *)v117[0];
    if ( v118 < 0x10 )
      v18 = v117;
    if ( *v18 == 32 )
    {
LABEL_53:
      v23 = v101 + 1;
    }
    else
    {
      for ( i6 = 0; i6 < 16; ++i6 )
      {
        v20 = (uint8_t *)v117[0];
        if ( v118 < 0x10 )
          v20 = v117;
        v21 = *(uint8_t **)(dword_9B0AB0 + 4 * i6);
        if ( *v20 == *v21 )
        {
          v22 = (uint32_t *)v117[0];
          if ( v118 < 0x10 )
            v22 = v117;
          if ( *((uint8_t *)v22 + 1) == v21[1] )
            break;
        }
      }
      if ( i6 == 16 )
      {
        ++v101;
        ++v100;
        goto LABEL_55;
      }
      if ( v99 == -1 )
      {
        v99 = i6;
      }
      else
      {
        v64[1] = i6;
        v64[0] = v99;
        sub_474950(v64);
        v99 = -1;
      }
      v23 = v101 + 2;
    }
    v101 = v23;
LABEL_55:
    LOBYTE(v124) = 4;
    sub_501490(v116);
  }
  while ( v101 < (int)v98 );
  if ( v100 == 0 )
  {
    pArg12 = pArg1;
    goto LABEL_164;
  }
  sub_4CEB50(&v78);
  sub_4CE820(&v66);
  sub_501490(v108);
  LOBYTE(v124) = 0;
  sub_41B010((void **)&v103);
  sub_501490(&v119);
  return 0;
}


// ------------------------------------------------------------
// 0x508C30 sub_508C30
// ------------------------------------------------------------
char /*cdecl*/ sub_508C30(const char *pArg1, int nArg2, int nArg3, int nArg4)
{
  char result; // al
  int *v5; // esi
  int *dword_9B75A02; // esi

  strcpy(byte_9B7730, pArg1);
  if ( byte_9B772F[strlen(byte_9B7730)] != 92 && byte_9B772F[strlen(byte_9B7730)] != 47 )
    *(uint16_t *)&byte_9B7730[strlen(byte_9B7730)] = 92;
  if ( (uint8_t)sub_443C40((int)&unk_9B7C3C, (char)byte_9B7730, nArg2) == 0 )
    return 0;
  memset(&unk_9B7418, 0, 0x188u);
  if ( (uint8_t)sub_442A10((char)byte_9B7730, nArg3) == 0 )
    return 0;
  v5 = (int *)&unk_9B7418;
  do
    *v5++ = sub_4423D0(nullptr);
  while ( (int)v5 < (int)dword_9B75A0 );
  if ( nArg4 != 0 )
  {
    memset(dword_9B75A0, 0, sizeof(dword_9B75A0));
    result = sub_442A10((char)byte_9B7730, nArg4);
    if ( result == 0 )
      return result;
    dword_9B75A02 = dword_9B75A0;
    do
      *dword_9B75A02++ = sub_4423D0(nullptr);
    while ( (int)dword_9B75A02 < (int)&unk_9B772C );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x508D50 sub_508D50
// ------------------------------------------------------------
bool /*cdecl*/ sub_508D50(const char *pArg1, int nArg2)
{
  strcpy(byte_9B7930, pArg1);
  if ( byte_9B792F[strlen(byte_9B7930)] != 92 && byte_9B792F[strlen(byte_9B7930)] != 47 )
    *(uint16_t *)&byte_9B7930[strlen(byte_9B7930)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B7C48, (char)byte_9B7930, nArg2) != 0;
}



// ------------------------------------------------------------
// 0x508DE0 sub_508DE0
// ------------------------------------------------------------
bool /*cdecl*/ sub_508DE0(const char *pArg1, int nArg2)
{
  strcpy(byte_9B7A30, pArg1);
  if ( byte_9B7A2F[strlen(byte_9B7A30)] != 92 && byte_9B7A2F[strlen(byte_9B7A30)] != 47 )
    *(uint16_t *)&byte_9B7A30[strlen(byte_9B7A30)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B7C70, (char)byte_9B7A30, nArg2) != 0;
}



// ------------------------------------------------------------
// 0x508E70 sub_508E70
// ------------------------------------------------------------
char */*cdecl*/ sub_508E70(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  void *v4; // edi

  for ( result = pszArg1; result != pszArg2; result += 44 )
  {
    v4 = result;
    qmemcpy(v4, pArg3, 0x2Cu);
  }
  return result;
}



// ------------------------------------------------------------
// 0x508EA0 sub_508EA0
// ------------------------------------------------------------
char */*cdecl*/ sub_508EA0(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg12; // edx
  char *result; // eax

  pszArg12 = pszArg1;
  for ( result = pszArg3; pszArg12 != pszArg2; result += 44 )
  {
    if ( result != nullptr )
      qmemcpy(result, pszArg12, 0x2Cu);
    pszArg12 += 44;
  }
  return result;
}



// ------------------------------------------------------------
// 0x508EE0 sub_508EE0
// ------------------------------------------------------------
char */*stdcall*/ sub_508EE0(char *pszArg1, char *pszArg2, const void *pArg3)
{
  sub_4F8DF0(pszArg1, pszArg2, pArg3);
  return &pszArg1[44 * (uint32_t)pszArg2];
}



// ------------------------------------------------------------
// 0x508F10 sub_508F10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_508F10(char **this, uint32_t *uArg2, char *pszArg3, char *pszArg4)
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
        pszArg42 += 44;
        pszArg33 += 44;
        qmemcpy(pszArg332, pszArg422, 0x2Cu);
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
// 0x508F60 sub_508F60
// ------------------------------------------------------------
void /*noreturn*/ sub_508F60()
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
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x508FD0 sub_508FD0
// ------------------------------------------------------------
int /*thiscall*/ sub_508FD0(int *this, char *pszArg2, unsigned int uArg3, int *Block)
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
  uint32_t *fld_e23; // ecx
  int fld_e26; // edi
  uint32_t *fld_e12; // [esp-18h] [ebp-40h]
  int fld_e25; // [esp-Ch] [ebp-34h]
  unsigned int fld_e24; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  uint32_t *v27; // [esp+30h] [ebp+8h]
  uint32_t *v28; // [esp+34h] [ebp+Ch]
  uint32_t *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];
  fld_e1 = *(this + 1);
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 12;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_4A30C0(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (uint32_t *)*(this + 2);
      Blockb = fld_e23;
      if ( ((char *)fld_e23 - pszArg2) / 12 >= uArg3 )
      {
        v27 = &fld_e23[-3 * uArg3];
        *(this + 2) = (int)sub_59EE30(v27, fld_e23, fld_e23);
        sub_504450(pszArg2, v27, Blockb);
        return sub_5043B0(pszArg2, &pszArg2[12 * uArg3], v25);
      }
      else
      {
        sub_59EE30(pszArg2, fld_e23, &pszArg2[12 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 12;
        fld_e25 = *(this + 2);
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return sub_5043B0(pszArg2, fld_e26 - 12 * uArg3, v25);
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 12;
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);
      v15 = 3 * v13;
      Blocka = operator new(12 * v13);
      fld_e12 = (uint32_t *)*(this + 1);
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pszArg2, Blocka);
      sub_623C10(v28, uArg3, v25);
      sub_59EE30(pszArg2, (uint32_t *)*(this + 2), &v28[3 * uArg3]);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 12;
      v17 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v15];
      *(this + 2) = (int)&Blocka[3 * v17];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x509280 sub_509280
// ------------------------------------------------------------
char /*thiscall*/ sub_509280(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x5D1745D )
    sub_508F60(this);
  pMem = (char *)operator new(44 * uArg2);
  *(this + 3) = &pMem[44 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x5092D0 sub_5092D0
// ------------------------------------------------------------
void /*thiscall*/ sub_5092D0(int this, char *pszArg2, unsigned int uArg3, void *Block)
{
  int fld_4; // edi
  unsigned int fld_C; // ecx
  int fld_8; // eax
  int fld_82; // eax
  unsigned int v10; // ecx
  int fld_87; // eax
  int v12; // edi
  int fld_43; // eax
  unsigned int v14; // esi
  char *fld_83; // ecx
  int fld_86; // esi
  char *fld_42; // [esp-18h] [ebp-60h]
  char *fld_85; // [esp-Ch] [ebp-54h]
  char *fld_84; // [esp-8h] [ebp-50h]
  int v21; // [esp+0h] [ebp-48h] BYREF
  uint32_t v22[12]; // [esp+Ch] [ebp-3Ch] BYREF
  int v23; // [esp+44h] [ebp-4h]
  char *v24; // [esp+50h] [ebp+8h]
  char *v25; // [esp+54h] [ebp+Ch]
  char *Blocka; // [esp+58h] [ebp+10h]
  char *Blockb; // [esp+58h] [ebp+10h]

  qmemcpy(v22, Block, 0x2Cu);
  fld_4 = *(uint32_t *)(this + 4);
  v22[11] = &v21;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) / 44;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 44;
    else
      fld_8 = 0;
    if ( 97612893 - fld_8 < uArg3 )
      sub_508F60(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) / 44;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(char **)(this + 8);
      Blockb = fld_83;
      if ( (fld_83 - pszArg2) / 44 >= uArg3 )
      {
        v24 = &fld_83[-44 * uArg3];
        *(uint32_t *)(this + 8) = sub_508EA0(v24, fld_83, fld_83);
        sub_4F8D90(pszArg2, v24, Blockb);
        sub_508E70(pszArg2, &pszArg2[44 * uArg3], v22);
      }
      else
      {
        sub_508EA0(pszArg2, fld_83, &pszArg2[44 * uArg3]);
        fld_84 = (char *)(uArg3 - (*(uint32_t *)(this + 8) - (int)pszArg2) / 44);
        fld_85 = *(char **)(this + 8);
        v23 = 2;
        sub_508EE0(fld_85, fld_84, v22);
        fld_86 = 44 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        sub_508E70(pszArg2, (char *)(fld_86 - 44 * uArg3), v22);
      }
    }
    else
    {
      if ( 97612893 - (fld_C >> 1) >= fld_C )
        v10 = (fld_C >> 1) + fld_C;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) / 44;
      else
        fld_87 = 0;
      if ( v10 < uArg3 + fld_87 )
        v10 = uArg3 + sub_527B90(this);
      v12 = 44 * v10;
      Blocka = (char *)operator new(44 * v10);
      fld_42 = *(char **)(this + 4);
      v23 = 0;
      v25 = sub_508EA0(fld_42, pszArg2, Blocka);
      sub_4F8DF0(v25, (char *)uArg3, v22);
      sub_508EA0(pszArg2, *(char **)(this + 8), &v25[44 * uArg3]);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_43 = (*(uint32_t *)(this + 8) - fld_43) / 44;
      v14 = fld_43 + uArg3;
      if ( *(uint32_t *)(this + 4) != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v12];
      *(uint32_t *)(this + 8) = &Blocka[44 * v14];
      *(uint32_t *)(this + 4) = Blocka;
    }
  }
}



// ------------------------------------------------------------
// 0x509580 sub_509580
// ------------------------------------------------------------
char **/*thiscall*/ sub_509580(char **this, int pArg2)
{
  unsigned int v2; // eax
  char *v5; // [esp-14h] [ebp-34h]
  char *v6; // [esp-10h] [ebp-30h]
  char *fld_e1; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(pArg2 + 4);
  v10 = &v8;
  pThis = this;
  if ( v2 != 0 )
    v2 = (int)(*(uint32_t *)(pArg2 + 8) - v2) / 44;
  if ( sub_509280(this, v2) != 0 )
  {
    fld_e1 = *(this + 1);
    v6 = *(char **)(pArg2 + 8);
    v5 = *(char **)(pArg2 + 4);
    v11 = 0;
    *(this + 2) = sub_508EA0(v5, v6, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x509620 sub_509620
// ------------------------------------------------------------
int /*thiscall*/ sub_509620(int this, int pArg2)
{
  int v3; // eax
  unsigned int v4; // ecx
  char *fld_4; // ebx
  unsigned int fld_8; // eax
  int v8; // eax
  unsigned int fld_C; // eax
  char *v10; // edi
  unsigned int v11; // eax

  if ( this == pArg2 )
    return this;
  v3 = *(uint32_t *)(pArg2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) / 44) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  fld_4 = *(char **)(this + 4);
  if ( fld_4 != nullptr )
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 44;
  else
    fld_8 = 0;
  if ( v4 > fld_8 )
  {
    if ( fld_4 != nullptr )
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 44;
    else
      fld_C = 0;
    if ( v4 <= fld_C )
    {
      v10 = (char *)(*(uint32_t *)(pArg2 + 4) + 44 * sub_527B90(this));
      sub_4F8DC0(*(char **)(pArg2 + 4), v10, fld_4);
      *(uint32_t *)(this + 8) = sub_508EA0(v10, *(char **)(pArg2 + 8), *(char **)(this + 8));
      return this;
    }
    if ( fld_4 != nullptr )
      j__free(*(void **)(this + 4));
    v11 = sub_527B90(pArg2);
    if ( sub_509280((uint32_t *)this, v11) != 0 )
      *(uint32_t *)(this + 8) = sub_433CF0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  sub_4F8DC0(*(char **)(pArg2 + 4), *(char **)(pArg2 + 8), *(char **)(this + 4));
  v8 = *(uint32_t *)(pArg2 + 4);
  if ( v8 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 44 * ((*(uint32_t *)(pArg2 + 8) - v8) / 44);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x5097A0 sub_5097A0
// ------------------------------------------------------------
int /*cdecl*/ sub_5097A0(int nArg1, int nArg2, int nArg3)
{
  int nArg12; // esi
  int nArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    sub_509620(nArg32, nArg12);
    nArg12 += 16;
    nArg32 += 16;
  }
  while ( nArg12 != nArg2 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x5097E0 sub_5097E0
// ------------------------------------------------------------
int /*cdecl*/ sub_5097E0(int nArg1, int nArg2, int nArg3)
{
  int nArg22; // esi
  int nArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    nArg22 -= 16;
    nArg32 -= 16;
    sub_509620(nArg32, nArg22);
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x509820 sub_509820
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_509820(int *this, uint32_t *uArg2, uint32_t *uArg3, int *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )
    v6 = ((int)uArg3 - fld_e1) / 12;
  else
    v6 = 0;
  sub_508FD0(this, uArg3, 1u, Block);
  *uArg2 = *(this + 1) + 12 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x509890 sub_509890
// ------------------------------------------------------------
void /*thiscall*/ sub_509890(
        int this,
        unsigned int a2,
        char Block,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13)
{
  int v13; // edi
  unsigned int v14; // eax
  int v15; // eax

  v13 = *(uint32_t *)(this + 4);
  if ( v13 != 0 )
    v14 = (*(uint32_t *)(this + 8) - v13) / 44;
  else
    v14 = 0;
  if ( v14 >= a2 )
  {
    if ( v13 != 0 && a2 < (*(uint32_t *)(this + 8) - v13) / 44 )
      sub_508F10((char **)this, &a2, (char *)(v13 + 44 * a2), *(char **)(this + 8));
  }
  else
  {
    if ( v13 != 0 )
      v15 = (*(uint32_t *)(this + 8) - v13) / 44;
    else
      v15 = 0;
    sub_5092D0(this, *(char **)(this + 8), a2 - v15, &Block);
  }
}



// ------------------------------------------------------------
// 0x509930 sub_509930
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_509930(uint32_t *this, uint32_t *uArg2, char *pszArg3, void *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 44 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 44;
  else
    v6 = 0;
  sub_5092D0((int)this, pszArg3, 1u, Block);
  *uArg2 = *(this + 1) + 44 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x5099A0 sub_5099A0
// ------------------------------------------------------------
int /*cdecl*/ sub_5099A0(int nArg1, int nArg2, int nArg3)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 16 )
    result = sub_509620(i, nArg3);
  return result;
}



// ------------------------------------------------------------
// 0x5099D0 sub_5099D0
// ------------------------------------------------------------
int /*cdecl*/ sub_5099D0(int nArg1, int nArg2, int nArg3)
{
  return sub_5097E0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x5099F0 sub_5099F0
// ------------------------------------------------------------
char **/*cdecl*/ sub_5099F0(int nArg1, int nArg2, char **pszArg3)
{
  char **pszArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pszArg32 = pszArg3;
  v6[4] = v6;
  v6[3] = pszArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )
  {
    LOBYTE(v7) = 1;
    if ( pszArg32 != nullptr )
      sub_509580(pszArg32, nArg1);
    pszArg32 += 4;
    LOBYTE(v7) = 0;
    nArg1 += 16;
  }
  return pszArg32;
}



// ------------------------------------------------------------
// 0x509A80 sub_509A80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_509A80(int *this, int *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 12;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 12 )
    return sub_509820(this, &Block, (uint32_t *)*(this + 2), Block);
  fld_e22 = *(this + 2);
  result = (uint32_t *)sub_623C10(fld_e22, 1, Block);
  *(this + 2) = fld_e22 + 12;
  return result;
}



// ------------------------------------------------------------
// 0x509B00 sub_509B00
// ------------------------------------------------------------
int /*thiscall*/ sub_509B00(int *this, void *Block)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  int result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 5;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 5 )
    return sub_4DE980(*(this + 2), 1, Block);
  fld_e22 = *(this + 2);
  result = sub_4DAB30(fld_e22, 1, Block);
  *(this + 2) = fld_e22 + 32;
  return result;
}



// ------------------------------------------------------------
// 0x509B70 sub_509B70
// ------------------------------------------------------------
char */*thiscall*/ sub_509B70(int this, void *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  char *fld_82; // edi
  char *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 44;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 44 )
    return (char *)sub_509930((uint32_t *)this, &Block, *(char **)(this + 8), Block);
  fld_82 = *(char **)(this + 8);
  result = sub_4F8DF0(fld_82, (char *)1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 44;
  return result;
}



// ------------------------------------------------------------
// 0x509C00 sub_509C00
// ------------------------------------------------------------
char **/*cdecl*/ sub_509C00(char **pszArg1, int nArg2, int nArg3)
{
  char **pszArg12; // esi
  char **result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pszArg12 = pszArg1;
  v6[4] = v6;
  v6[3] = pszArg1;
  v7 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( pszArg12 != nullptr )
      result = sub_509580(pszArg12, nArg3);
    --nArg2;
    pszArg12 += 4;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x509C90 sub_509C90 —— ★★ 怪物数据文件解析器（MonsterBaseParameter.tbl 族；技能/属性块通用）
//   【研究 20 §12 定位：技能/属性块通用解析器，"固定字段对"（基础/加成 双格）的主体】。
//   a1 = 数据对象（每数据文件一份，sub_4D2D60 工厂 case 1 的 0x5A0 对象），a2 = 文件路径。
//
//   ── 关键字段对（研究 20 §12 字段表对照；全库唯一写入点）──
//   a1+380/+384  [attack speed]          攻速（基础/加成）—— 攻速聚合 base×(1+stat×0.01) 的源头
//   a1+388/+392  [cast speed]            施放速度
//   a1+396/+400  [hit recovery]          受方硬直恢复 ★（研究 20 §12；§14#2 定案：
//                                        客户端仅解析不消费，表现壳原样施加 attackinfo+132，
//                                        权威时长在服务端）
//   a1+404/+408  [jump power]            跳跃力
//   a1+412/+416  [jump speed]            跳跃速度
//   a1+420/+424  [weight]                重量（研究 20 §19 更正："全 PE 无 [weight] 标签"系误——
//                                        该标签实际存在于本解析器，见报告）
//   a1+428/432/436/440  [stuckbonus on damage]  攻方按伤害类四档的硬直加成 ★
//                                        （研究 20 §12；生效点读者 0x47EF20/0x47F310/0x482A90 待追）
//   a1+492 / +496  [warlike] / [attack delay]
//   a1+772       [elemental property]     属性（名字查表）
//   a1+776       [active status]          状态槽（17 槽枚举：none=17/slow=0..hold=16 —— 研究 20 §10）
//   a1+850       [ignore defense]         无视防御开关
//   a1+879/+880  [HP drain]/[MP drain]    吸血/吸魔开关
//   a1+884       [skill levelup]          升级技能表（子枚举 [common]=4 = 通用）
//   a1+916       [avatar select ability]  时装能力选择
//
//   其它标签族：几何 [name]/[width]/[floating height]/[layer]；能力 [category]（22 项名表 off_791F80）/
//   [ability category]（13 项 off_795B2C，符号 "+"=0/"*"=1）/ [ability table] /
//   [summon skill status up rate]（10 个 float）；抗性 [fire/water/dark/light resistance]、
//   [HP/MP regen speed]；AI [superarmor on attack]/[sight]/[targeting time term] 与 14 项
//   [targeting ...] 选敌策略；演出 [die effect]/[face image] 与动作表（[waiting motion]...）；
//   [speech on situation] 情境语音（子枚举 [on attack]/[on damage]/[on die]/[on revenge]/[on etc]/
//   [on appear]/[on disappear]/[on go to help]/[on stand]）；[spawn prob] 出现概率；
//   [jumpattack info]/[attack info]/[etc attack info] 攻击数据引用（经 sub_420BB0 打包）。
//   标签总数 75。
// ------------------------------------------------------------
char /*cdecl*/ sub_509C90(int pArg1, int nArg2)
{
  char result; // al
  int v3; // eax
  int v4; // esi
  int v5; // esi
  float *v6; // esi
  int i; // ebx
  int j; // esi
  int v9; // eax
  int k; // esi
  int v11; // eax
  int v12; // esi
  const char *v13; // eax
  int n; // esi
  int v15; // eax
  int v16; // esi
  int jj; // ebx
  char **off_791FD82; // esi
  uint32_t *v19; // ebx
  uint32_t v20[2]; // [esp+4h] [ebp-84h] BYREF
  uint32_t v21[2]; // [esp+Ch] [ebp-7Ch] BYREF
  uint32_t v22[2]; // [esp+14h] [ebp-74h] BYREF
  bool v23[4]; // [esp+1Ch] [ebp-6Ch] BYREF
  float v24; // [esp+20h] [ebp-68h]
  float v25; // [esp+24h] [ebp-64h]
  float v26; // [esp+28h] [ebp-60h]
  int v27; // [esp+2Ch] [ebp-5Ch]
  int v28; // [esp+30h] [ebp-58h]
  int v29; // [esp+34h] [ebp-54h]
  int v30; // [esp+38h] [ebp-50h]
  int v31; // [esp+3Ch] [ebp-4Ch] BYREF
  char v32; // [esp+40h] [ebp-48h]
  int v33; // [esp+44h] [ebp-44h]
  void *v34; // [esp+48h] [ebp-40h] BYREF
  char v35; // [esp+4Fh] [ebp-39h] BYREF
  int ii; // [esp+50h] [ebp-38h] BYREF
  void *v37; // [esp+54h] [ebp-34h] BYREF
  char m; // [esp+5Bh] [ebp-2Dh] BYREF
  uint8_t v39[4]; // [esp+5Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+60h] [ebp-28h]
  unsigned int v41; // [esp+70h] [ebp-18h]
  unsigned int v42; // [esp+74h] [ebp-14h]
  int dword_796E502; // [esp+78h] [ebp-10h]
  int v44; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B7830, nArg2);
  if ( result != 0 )
  {
    sub_4CEB80(pArg1);
    sub_443300(pArg1 + 928, "%s%s", (char)&unk_9B7830);
    v42 = 15;
    v41 = 0;
    LOBYTE(Block) = 0;
    v44 = 0;
    v37 = nullptr;
    sub_41BFE0(&v37, szPassword);
    LOBYTE(v44) = 1;
    m = 0;
    while ( (uint8_t)sub_443430(v39) != 0 )
    {
      sub_442B20(v39);
      if ( sub_40BF00((std::_String_base *)v39, 0, v41, "[name]", 6u) == 0 )
        goto LABEL_162;
      if ( sub_40BF00((std::_String_base *)v39, 0, v41, "[width]", 7u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v39, 0, v41, "[floating height]", 0x11u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v39, 0, v41, "[layer]", 7u) != 0 )
          {
            if ( (uint8_t)sub_423300(v39, "[category]") != 0 )
            {
              sub_5E5260((void *)(pArg1 + 48));
              while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              {
                v4 = 0;
                ii = 0;
                while ( !sub_43BCF0(&v37, off_791F80[v4]) )
                {
                  if ( ++v4 >= 22 )
                  {
                    ii = v4;
                    goto LABEL_18;
                  }
                }
                ii = v4;
                sub_431230(&ii);
LABEL_18:
                ;
              }
              continue;
            }
            if ( (uint8_t)sub_423300(v39, "[ability category]") != 0 )
            {
              v33 = 0;
              v31 = 13;
              v32 = 0;
              sub_5E5260((void *)(pArg1 + 128));
              while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              {
                v5 = 0;
                while ( !sub_43BCF0(&v37, off_795B2C[v5]) )
                {
                  if ( ++v5 >= 13 )
                    goto LABEL_31;
                }
                v31 = v5;
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                if ( sub_43BCF0(&v37, "+") )
                {
                  v32 = 0;
                }
                else if ( sub_43BCF0(&v37, "*") )
                {
                  v32 = 1;
                }
                v33 = sub_4423D0(0);
LABEL_31:
                sub_509A80(&v31);
              }
              continue;
            }
            if ( (uint8_t)sub_423300(v39, "[ability table]") != 0 )
            {
              *(uint32_t *)(pArg1 + 144) = sub_4423D0(0);
            }
            else
            {
              if ( (uint8_t)sub_423300(v39, "[summon skill status up rate]") != 0 )
              {
                v6 = (float *)(pArg1 + 148);
                for ( i = 10; i != 0; --i )
                  *v6++ = sub_442480(0);
                continue;
              }
              if ( (uint8_t)sub_423300(v39, "[level]") != 0 )
              {
                *(uint32_t *)(pArg1 + 188) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 192) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[fire resistance]") != 0 )
              {
                *(uint32_t *)(pArg1 + 196) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 200) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[water resistance]") != 0 )
              {
                *(uint32_t *)(pArg1 + 204) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 208) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[dark resistance]") != 0 )
              {
                *(uint32_t *)(pArg1 + 212) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 216) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[light resistance]") != 0 )
              {
                *(uint32_t *)(pArg1 + 220) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 224) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[HP regen speed]") != 0 )
              {
                *(uint32_t *)(pArg1 + 356) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 360) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[MP regen speed]") != 0 )
              {
                *(uint32_t *)(pArg1 + 364) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 368) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[move speed]") != 0 )
              {
                *(uint32_t *)(pArg1 + 372) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 376) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[attack speed]") != 0 )
              {
                *(uint32_t *)(pArg1 + 380) = sub_4423D0(0);   // +380 [attack speed] 基础（+384 加成）
                *(uint32_t *)(pArg1 + 384) = sub_4423D0(0);   //   攻速聚合 base×(1+stat×0.01) 的源头（研究 20 §16）
              }
              else if ( (uint8_t)sub_423300(v39, "[cast speed]") != 0 )
              {
                *(uint32_t *)(pArg1 + 388) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 392) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[hit recovery]") != 0 )
              {
                *(uint32_t *)(pArg1 + 396) = sub_4423D0(0);   // +396 [hit recovery] 基础（基础/加成 双格）
                *(uint32_t *)(pArg1 + 400) = sub_4423D0(0);   // +400 [hit recovery] 加成（研究 20 §12：
                                                           //   客户端仅解析不消费，权威时长在服务端）
              }
              else if ( (uint8_t)sub_423300(v39, "[jump power]") != 0 )
              {
                *(uint32_t *)(pArg1 + 404) = sub_4423D0(0);   // +404 [jump power] 基础（+408 加成）
                *(uint32_t *)(pArg1 + 408) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[jump speed]") != 0 )
              {
                *(uint32_t *)(pArg1 + 412) = sub_4423D0(0);
                *(uint32_t *)(pArg1 + 416) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[weight]") != 0 )
              {
                *(uint32_t *)(pArg1 + 420) = sub_4423D0(0);   // +420 [weight] 基础（+424 加成）
                *(uint32_t *)(pArg1 + 424) = sub_4423D0(0);   //   ★ 更正研究 20 §19 "全 PE 无 [weight] 标签"之误
              }
              else if ( (uint8_t)sub_423300(v39, "[superarmor on attack]") != 0 )
              {
                *(uint8_t *)(pArg1 + 500) = sub_4423D0(0) != 0;
                *(uint32_t *)(pArg1 + 504) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[sight]") != 0 )
              {
                *(uint32_t *)(pArg1 + 444) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[targeting time term]") != 0 )
              {
                *(uint32_t *)(pArg1 + 448) = sub_4423D0(0);
              }
              else if ( (uint8_t)sub_423300(v39, "[targeting on attack]") != 0 )
              {
                *(uint8_t *)(pArg1 + 452) = sub_4423D0(0) != 0;
              }
              else if ( (uint8_t)sub_423300(v39, "[targeting on damage]") != 0 )
              {
                *(uint8_t *)(pArg1 + 453) = sub_4423D0(0) != 0;
              }
              else
              {
                if ( (uint8_t)sub_423300(v39, "[targeting high level]") != 0 )
                {
                  if ( sub_4423D0(0) != 0 )
                    *(uint32_t *)(pArg1 + 456) = 2;
                  continue;
                }
                if ( (uint8_t)sub_423300(v39, "[targeting low level]") != 0 )
                {
                  if ( sub_4423D0(0) != 0 )
                    *(uint32_t *)(pArg1 + 456) = 1;
                  continue;
                }
                if ( (uint8_t)sub_423300(v39, "[targeting high HP]") != 0 )
                {
                  if ( sub_4423D0(0) != 0 )
                    *(uint32_t *)(pArg1 + 460) = 2;
                  continue;
                }
                if ( (uint8_t)sub_423300(v39, "[targeting low HP]") != 0 )
                {
                  if ( sub_4423D0(0) != 0 )
                    *(uint32_t *)(pArg1 + 460) = 1;
                  continue;
                }
                if ( (uint8_t)sub_423300(v39, "[targeting nearest]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 468) = sub_4423D0(0) != 0;
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting attacker]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 469) = sub_4423D0(0) != 0;
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting from direction]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 470) = sub_4423D0(0) != 0;
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting low physical attack]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 472) = sub_4423D0(0) != 0;
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting low physical defense]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 476) = sub_4423D0(0) != 0;
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting low magical attack]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 480) = sub_4423D0(0) != 0;
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting low magical defense]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 484) = sub_4423D0(0) != 0;
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting downed]") != 0 )
                {
                  *(uint8_t *)(pArg1 + 488) = sub_4423D0(0) != 0;
                }
                else if ( (uint8_t)sub_423300(v39, "[warlike]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 492) = sub_4423D0(0);
                }
                else if ( (uint8_t)sub_423300(v39, "[attack delay]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 496) = sub_4423D0(0);
                }
                else if ( (uint8_t)sub_423300(v39, "[stuckbonus on damage]") != 0 )
                {
                  *(uint32_t *)(pArg1 + 428) = sub_4423D0(0);  // +428 [stuckbonus on damage] 档 1/4（攻方硬直加成）
                  *(uint32_t *)(pArg1 + 432) = sub_4423D0(0);  // +432 档 2/4
                  *(uint32_t *)(pArg1 + 436) = sub_4423D0(0);  // +436 档 3/4
                  *(uint32_t *)(pArg1 + 440) = sub_4423D0(0);  // +440 档 4/4（按伤害类四档 —— 研究 20 §12）
                }
                else
                {
                  if ( (uint8_t)sub_423300(v39, "[item]") != 0 )
                  {
                    sub_5E5260((void *)(pArg1 + 64));
                    for ( j = sub_4423D0(&m); m != 0; j = sub_4423D0(&m) )
                    {
                      v9 = sub_4423D0(0);
                      v22[0] = j;
                      v22[1] = v9;
                      sub_474950(v22);
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[common champion drop item]") != 0 )
                  {
                    sub_5E5260((void *)(pArg1 + 80));
                    for ( k = sub_4423D0(&m); m != 0; k = sub_4423D0(&m) )
                    {
                      v11 = sub_4423D0(0);
                      v20[0] = k;
                      v20[1] = v11;
                      sub_474950(v20);
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[common champion elemental property]") != 0 )
                  {
                    sub_5E5260((void *)(pArg1 + 1420));
                    for ( m = sub_442E10(); m != 0; m = sub_442E10() )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    {
                      v12 = 0;
                      ii = 0;
                      while ( 1 )
                      {
                        v13 = (const char *)sub_442780(v12);  // 【当前元素标签 setter（全局 dword_97B384）】
                        if ( sub_43BCF0(&v37, v13) )
                          break;
                        if ( ++v12 >= 5 )
                        {
                          ii = v12;
                          goto LABEL_126;
                        }
                      }
                      ii = v12;
                      sub_431230(&ii);
LABEL_126:
                      ;
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[super champion drop item]") != 0 )
                  {
                    sub_5E5260((void *)(pArg1 + 96));
                    for ( n = sub_4423D0(&m); m != 0; n = sub_4423D0(&m) )
                    {
                      v15 = sub_4423D0(0);
                      v21[0] = n;
                      v21[1] = v15;
                      sub_474950(v21);
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[attack kind]") != 0 )
                  {
                    sub_5E5260((void *)(pArg1 + 900));
                    while ( 1 )
                    {
                      v23[0] = false;
                      v27 = 0;
                      v28 = 0;
                      v29 = 0;
                      v30 = 0;
                      v25 = 0.0;
                      v26 = 0.0;
                      v24 = sub_442480(&v35);
                      if ( v35 == 0 )
                        break;
                      v25 = sub_442480(0);
                      v26 = sub_442480(0);
                      v23[0] = sub_4423D0(0) != 0;
                      v27 = sub_4423D0(0);
                      v28 = sub_4423D0(0);
                      v29 = sub_4423D0(0);
                      v30 = sub_4423D0(0);
                      sub_509B00(v23);
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[die effect]") != 0 )
                  {
                    *(uint32_t *)(pArg1 + 916) = sub_4423D0(0);
                    *(uint32_t *)(pArg1 + 920) = sub_4423D0(0);
                    *(uint32_t *)(pArg1 + 924) = sub_4423D0(0);
                  }
                  else
                  {
                    if ( (uint8_t)sub_423300(v39, "[face image]") == 0 )
                    {
                      if ( (uint8_t)sub_423300(v39, "[waiting motion]") == 0
                        && (uint8_t)sub_423300(v39, "[move motion]") == 0
                        && (uint8_t)sub_423300(v39, "[sit motion]") == 0
                        && (uint8_t)sub_423300(v39, "[damage motion 1]") == 0
                        && (uint8_t)sub_423300(v39, "[damage motion 2]") == 0
                        && (uint8_t)sub_423300(v39, "[down motion]") == 0
                        && (uint8_t)sub_423300(v39, "[overturn motion]") == 0
                        && (uint8_t)sub_423300(v39, "[jump motion]") == 0
                        && (uint8_t)sub_423300(v39, "[jumpattack motion]") == 0 )
                      {
                        if ( (uint8_t)sub_423300(v39, "[attack motion]") != 0 )
                        {
                          sub_4017E0(pArg1 + 792);
                          while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                            sub_420BB0(&v37);
                          continue;
                        }
                        if ( (uint8_t)sub_423300(v39, "[etc motion]") != 0 )
                        {
                          sub_4017E0(pArg1 + 808);
                          while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                            sub_420BB0(&v37);
                          continue;
                        }
                        if ( (uint8_t)sub_423300(v39, "[jumpattack info]") == 0 )
                        {
                          if ( (uint8_t)sub_423300(v39, "[attack info]") != 0 )
                          {
                            sub_4017E0(pArg1 + 852);
                            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                              sub_420BB0(&v37);
                          }
                          else if ( (uint8_t)sub_423300(v39, "[etc attack info]") != 0 )
                          {
                            sub_4017E0(pArg1 + 868);
                            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                              sub_420BB0(&v37);
                          }
                          else if ( (uint8_t)sub_423300(v39, "[int data]") != 0 )
                          {
                            sub_5E5260((void *)(pArg1 + 884));
                            for ( ii = sub_4423D0(&m); m != 0; ii = sub_4423D0(&m) )
                              sub_431230(&ii);
                          }
                          else if ( (uint8_t)sub_423300(v39, "[speech on situation]") != 0 )
                          {
                            sub_432D20(&v34);
                            LOBYTE(v44) = 2;
                            v16 = pArg1 + 956;
                            for ( jj = 29; jj != 0; --jj )
                            {
                              sub_4017E0(v16);
                              v16 += 16;
                            }
                            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                            {
                              sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                              sub_4423D0(0);
                              if ( !sub_43BCF0(&v37, "[on attack]")
                                && !sub_43BCF0(&v37, "[on damage]")
                                && !sub_43BCF0(&v37, "[on die]")
                                && !sub_43BCF0(&v37, "[on revenge]")
                                && !sub_43BCF0(&v37, "[on etc]")
                                && !sub_43BCF0(&v37, "[on appear]")
                                && !sub_43BCF0(&v37, "[on disappear]")
                                && !sub_43BCF0(&v37, "[on go to help]") )
                              {
                                sub_43BCF0(&v37, "[on stand]");
                              }
                              sub_420BB0(&v34);
                            }
                            LOBYTE(v44) = 1;
                            sub_41B010(&v34);
                          }
                          else if ( (uint8_t)sub_423300(v39, "[spawn prob]") != 0 )
                          {
                            *(uint32_t *)(pArg1 + 1436) = sub_4423D0(0);
                          }
                          else
                          {
                            off_791FD82 = off_791FD8;
                            v19 = (uint32_t *)(pArg1 + 232);
                            do
                            {
                              if ( (uint8_t)sub_423300(v39, *off_791FD82) != 0 )
                              {
                                *(v19 - 1) = sub_4423D0(0);
                                *v19 = sub_4423D0(0);
                              }
                              ++off_791FD82;
                              v19 += 2;
                            }
                            while ( (int)off_791FD82 < (int)off_792018 );
                          }
                          continue;
                        }
                      }
LABEL_162:
                      sub_443370();
                      continue;
                    }
                    sub_443370();
                    *(uint32_t *)(pArg1 + 536) = sub_4423D0(0);
                  }
                }
              }
            }
          }
          else
          {
            sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
            v3 = sub_41ACF0(&v37);
            *(uint32_t *)(pArg1 + 44) = sub_4425F0(v3);
          }
        }
        else
        {
          *(uint32_t *)(pArg1 + 40) = sub_4423D0(0);
        }
      }
      else
      {
        *(uint32_t *)(pArg1 + 32) = sub_4423D0(0);
        *(uint32_t *)(pArg1 + 36) = sub_4423D0(0);
      }
    }
    *(uint32_t *)pArg1 = sub_4A2F80(nArg2);
    LOBYTE(v44) = 0;
    sub_41B010(&v37);
    if ( v42 >= 0x10 )
      j__free(Block);
    return 1;
  }
  return result;
}


// ============================================================
// §H 0x50AF40-0x50C000 PassiveObject / 地图物件 / 技能 PO 定义族
// ============================================================

// ------------------------------------------------------------
// 0x50AF40 sub_50AF40 —— 地图物件(map object)定义解析器
//   标签族：几何 [name]/[width]/[floating height]/[layer]；通行 [pass type] 子枚举
//   [pass all]=0/[pass only float type]/[do not pass]；[piercing power] 穿透力；
//   [category]；动作 [basic motion]/[etc motion]；[destroy particle] 破坏粒子；
//   攻击数据引用 [attack info]/[etc attack info]；[int data]/[string data] 通用袋。
//   标签总数 17。调用者：sub_4D2D60 工厂（地图物件类）。
// ------------------------------------------------------------
char /*cdecl*/ sub_50AF40(int pArg1, int nArg2)
{
  int nArg22; // esi
  char result; // al
  int v4; // eax
  int v5; // esi
  int i; // [esp+4h] [ebp-38h] BYREF
  char v7; // [esp+Bh] [ebp-31h] BYREF
  void *v8; // [esp+Ch] [ebp-30h] BYREF
  uint8_t v9[4]; // [esp+10h] [ebp-2Ch] BYREF
  void *Block; // [esp+14h] [ebp-28h]
  unsigned int v11; // [esp+24h] [ebp-18h]
  unsigned int v12; // [esp+28h] [ebp-14h]
  int dword_796E502; // [esp+2Ch] [ebp-10h]
  int v14; // [esp+38h] [ebp-4h]

  nArg22 = nArg2;
  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B7930, nArg2);
  if ( result == 0 )
    return result;
  sub_4CF050(pArg1);
  sub_443300(pArg1 + 220, "%s%s", (char)&unk_9B7930);
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;
  v14 = 0;
  v8 = nullptr;
  sub_41BFE0(&v8, szPassword);
  LOBYTE(v14) = 1;
  v7 = 0;
  if ( (uint8_t)sub_443430(v9) == 0 )
    goto LABEL_50;
  do
  {
    sub_442B20(v9);
    if ( sub_40BF00((std::_String_base *)v9, 0, v11, "[name]", 6u) == 0 )
    {
LABEL_36:
      sub_443370();
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v9, 0, v11, "[width]", 7u) == 0 )
    {
      *(uint32_t *)(pArg1 + 32) = sub_4423D0(nullptr);
      *(uint32_t *)(pArg1 + 36) = sub_4423D0(nullptr);
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v9, 0, v11, "[floating height]", 0x11u) == 0 )
    {
      *(uint32_t *)(pArg1 + 40) = sub_4423D0(nullptr);
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v9, 0, v11, "[layer]", 7u) == 0 )
    {
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      v4 = sub_41ACF0(&v8);
      *(uint32_t *)(pArg1 + 44) = sub_4425F0(v4);
      continue;
    }
    if ( (uint8_t)sub_423300(v9, "[pass type]") != 0 )
    {
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v8, "[pass all]") )
      {
        *(uint32_t *)(pArg1 + 48) = 0;
      }
      else if ( sub_43BCF0(&v8, "[pass only float type]") )
      {
        *(uint32_t *)(pArg1 + 48) = 1;
      }
      else if ( sub_43BCF0(&v8, "[do not pass]") )
      {
        *(uint32_t *)(pArg1 + 48) = 2;
      }
    }
    else
    {
      if ( (uint8_t)sub_423300(v9, "[piercing power]") != 0 )
      {
        *(uint32_t *)(pArg1 + 52) = sub_4423D0(nullptr);
        continue;
      }
      if ( (uint8_t)sub_423300(v9, "[category]") != 0 )
      {
        sub_5E5260((void **)(pArg1 + 56));
        while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        {
          v5 = 0;
          i = 0;
          while ( !sub_43BCF0(&v8, off_791F80[v5]) )
          {
            if ( ++v5 >= 22 )
            {
              i = v5;
              goto LABEL_27;
            }
          }
          i = v5;
          sub_431230(pArg1 + 56, &i);
LABEL_27:
          ;
        }
      }
      else
      {
        if ( (uint8_t)sub_423300(v9, "[basic motion]") != 0 )
          goto LABEL_36;
        if ( (uint8_t)sub_423300(v9, "[etc motion]") != 0 )
        {
          sub_4017E0(pArg1 + 100);
          while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
            sub_420BB0(&v8);
        }
        else
        {
          if ( (uint8_t)sub_423300(v9, "[destroy particle]") != 0
            || (uint8_t)sub_423300(v9, "[attack info]") != 0 )
          {
            goto LABEL_36;
          }
          if ( (uint8_t)sub_423300(v9, "[etc attack info]") != 0 )
          {
            sub_4017E0(pArg1 + 172);
            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              sub_420BB0(&v8);
          }
          else if ( (uint8_t)sub_423300(v9, "[int data]") != 0 )
          {
            sub_5E5260((void **)(pArg1 + 188));
            for ( i = sub_4423D0(&v7); v7 != 0; i = sub_4423D0(&v7) )
              sub_431230(pArg1 + 188, &i);
          }
          else if ( (uint8_t)sub_423300(v9, "[string data]") != 0 )
          {
            sub_4017E0(pArg1 + 204);
            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              sub_420BB0(&v8);
          }
        }
      }
    }
  }
  while ( (uint8_t)sub_443430(v9) != 0 );
  nArg22 = nArg2;
LABEL_50:
  *(uint32_t *)pArg1 = sub_4A2F80(nArg22);
  LOBYTE(v14) = 0;
  sub_41B010(&v8);
  if ( v12 >= 0x10 )
    j__free(Block);
  return 1;
}


// ------------------------------------------------------------
// 0x50B400 sub_50B400 —— PassiveObject(PO)定义解析器（普通物件，非技能 PO）
//   标签族：几何 [name]/[width]/[floating height]/[layer]；时序 [recovery time] 恢复时间；
//   运动 [direction correct]/[move speed]/[gravity]；动作 [basic motion]/[etc motion]；
//   攻击数据引用 [attack info]（经 sub_420BB0 打包）；[int data]/[string data] 通用袋。
//   标签总数 13。调用者：sub_4D2D60 工厂（PO 类）。
// ------------------------------------------------------------
char /*cdecl*/ sub_50B400(int pArg1, int nArg2)
{
  int nArg22; // esi
  char result; // al
  unsigned int v4; // edx
  int v5; // ecx
  const char *p_Block; // esi
  int nCmp; // eax
  int v8; // eax
  int i; // [esp+4h] [ebp-38h] BYREF
  void *v10; // [esp+8h] [ebp-34h] BYREF
  char v11; // [esp+Fh] [ebp-2Dh] BYREF
  uint8_t v12[4]; // [esp+10h] [ebp-2Ch] BYREF
  void *Block; // [esp+14h] [ebp-28h] BYREF
  unsigned int v14; // [esp+24h] [ebp-18h]
  unsigned int v15; // [esp+28h] [ebp-14h]
  int dword_796E502; // [esp+2Ch] [ebp-10h]
  int v17; // [esp+38h] [ebp-4h]

  nArg22 = nArg2;
  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B7A30, nArg2);
  if ( result == 0 )
    return result;
  sub_4CF120(pArg1);
  sub_443300(pArg1 + 172, "%s%s", (char)&unk_9B7A30);
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;
  v17 = 0;
  v10 = nullptr;
  sub_41BFE0(&v10, szPassword);
  LOBYTE(v17) = 1;
  v11 = 0;
  if ( (uint8_t)sub_443430(v12) == 0 )
    goto LABEL_45;
  do
  {
    sub_442B20(v12);
    v4 = v14;
    if ( v14 != 0 )
    {
      v5 = v14;
      if ( v14 >= 6 )
        v5 = 6;
      p_Block = (const char *)Block;
      if ( v15 < 0x10 )
        p_Block = (const char *)&Block;
      nCmp = memcmp(p_Block, "[name]", v5);
      if ( nCmp == 0 && v14 >= 6 )
      {
        LOBYTE(nCmp) = v14 != 6;
        if ( nCmp == 0 )
        {
LABEL_11:
          sub_443370();
          continue;
        }
      }
      v4 = v14;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v4, "[width]", 7u) != 0 )
    {
      if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[floating height]", 0x11u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[layer]", 7u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[recovery time]", 0xFu) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[direction correct]", 0x13u) != 0 )
            {
              if ( (uint8_t)sub_423300(v12, "[move speed]") != 0 )
              {
                *(uint32_t *)(pArg1 + 56) = sub_4423D0(nullptr);
                *(uint32_t *)(pArg1 + 60) = sub_4423D0(nullptr);
                *(uint32_t *)(pArg1 + 64) = sub_4423D0(nullptr);
                *(uint32_t *)(pArg1 + 68) = sub_4423D0(nullptr);
                *(uint32_t *)(pArg1 + 72) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(v12, "[gravity]") != 0 )
              {
                *(uint32_t *)(pArg1 + 76) = sub_4423D0(nullptr);
              }
              else
              {
                if ( (uint8_t)sub_423300(v12, "[basic motion]") != 0 )
                  goto LABEL_11;
                if ( (uint8_t)sub_423300(v12, "[etc motion]") != 0 )
                {
                  sub_4017E0(pArg1 + 108);
                  while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v10);
                }
                else if ( (uint8_t)sub_423300(v12, "[attack info]") != 0 )
                {
                  sub_4017E0(pArg1 + 124);
                  while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v10);
                }
                else if ( (uint8_t)sub_423300(v12, "[int data]") != 0 )
                {
                  sub_5E5260((void **)(pArg1 + 140));
                  for ( i = sub_4423D0(&v11); v11 != 0; i = sub_4423D0(&v11) )
                    sub_431230(pArg1 + 140, &i);
                }
                else if ( (uint8_t)sub_423300(v12, "[string data]") != 0 )
                {
                  sub_4017E0(pArg1 + 156);
                  while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v10);
                }
              }
            }
            else
            {
              *(uint8_t *)(pArg1 + 52) = sub_4423D0(nullptr) != 0;
            }
          }
          else
          {
            *(uint32_t *)(pArg1 + 48) = sub_4423D0(nullptr);
          }
        }
        else
        {
          sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
          v8 = sub_41ACF0(&v10);
          *(uint32_t *)(pArg1 + 44) = sub_4425F0(v8);
        }
      }
      else
      {
        *(uint32_t *)(pArg1 + 40) = sub_4423D0(nullptr);
      }
    }
    else
    {
      *(uint32_t *)(pArg1 + 32) = sub_4423D0(nullptr);
      *(uint32_t *)(pArg1 + 36) = sub_4423D0(nullptr);
    }
  }
  while ( (uint8_t)sub_443430(v12) != 0 );
  nArg22 = nArg2;
LABEL_45:
  *(uint32_t *)pArg1 = sub_4A2F80(nArg22);
  LOBYTE(v17) = 0;
  sub_41B010(&v10);
  if ( v15 >= 0x10 )
    j__free(Block);
  return 1;
}


// ------------------------------------------------------------
// 0x50B840 sub_50B840 —— 技能 PassiveObject / 觉醒(overskill)定义解析器
//   标签族：几何 [name]/[width]/[floating height]/[layer]；时序 [skill recovery time]/
//   [over skill recovery time]（普通技能/觉醒技能 双恢复时间 —— 与 sub_50B400 [recovery time] 对照）；
//   运动 [direction correct]/[move speed]/[gravity]；成长 [start level]/[permission level]/
//   [artifact slot]/[learn overskill level]；动作表 [basic motion]/[walk motion]/[run motion]/
//   [skill motion]/[over skill motion]/[response motion]/[etc motion]；
//   攻击数据引用 [attack info]；[int data]/[string data]。标签总数 23。
// ------------------------------------------------------------
char /*cdecl*/ sub_50B840(int pArg1, int nArg2)
{
  const char *v2; // esi
  char result; // al
  unsigned int v4; // edx
  int v5; // ecx
  const char *p_Block; // esi
  int nCmp; // eax
  const CHAR *v8; // eax
  int i; // [esp+4h] [ebp-38h] BYREF
  unsigned int *v10; // [esp+8h] [ebp-34h] BYREF
  char v11; // [esp+Fh] [ebp-2Dh] BYREF
  uint8_t v12[4]; // [esp+10h] [ebp-2Ch] BYREF
  void *Block; // [esp+14h] [ebp-28h] BYREF
  unsigned int v14; // [esp+24h] [ebp-18h]
  unsigned int v15; // [esp+28h] [ebp-14h]
  int dword_796E502; // [esp+2Ch] [ebp-10h]
  int v17; // [esp+38h] [ebp-4h]

  v2 = (const char *)nArg2;
  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B7B30, nArg2);
  if ( result == 0 )
    return result;
  sub_4CF290((char *)pArg1);
  sub_443300(pArg1 + 332, "%s%s", (char)&unk_9B7B30);
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;
  v17 = 0;
  v10 = nullptr;
  sub_41BFE0((void **)&v10, szPassword);
  LOBYTE(v17) = 1;
  v11 = 0;
  if ( (uint8_t)sub_443430(v12) == 0 )
    goto LABEL_63;
  do
  {
    sub_442B20(v12);
    v4 = v14;
    if ( v14 != 0 )
    {
      v5 = v14;
      if ( v14 >= 6 )
        v5 = 6;
      p_Block = (const char *)Block;
      if ( v15 < 0x10 )
        p_Block = (const char *)&Block;
      nCmp = memcmp(p_Block, "[name]", v5);
      if ( nCmp == 0 && v14 >= 6 )
      {
        LOBYTE(nCmp) = v14 != 6;
        if ( nCmp == 0 )
          goto LABEL_45;
      }
      v4 = v14;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v4, "[width]", 7u) == 0 )
    {
      *(uint32_t *)(pArg1 + 32) = sub_4423D0(nullptr);
      *(uint32_t *)(pArg1 + 36) = sub_4423D0(nullptr);
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[floating height]", 0x11u) == 0 )
    {
      *(uint32_t *)(pArg1 + 40) = sub_4423D0(nullptr);
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[layer]", 7u) == 0 )
    {
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      v8 = sub_41ACF0(&v10);
      *(uint32_t *)(pArg1 + 44) = sub_4425F0(v8);
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[skill recovery time]", 0x15u) == 0 )
    {
      *(uint32_t *)(pArg1 + 48) = sub_4423D0(nullptr);
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[over skill recovery time]", 0x1Au) == 0 )
    {
      *(uint32_t *)(pArg1 + 52) = sub_4423D0(nullptr);
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[direction correct]") != 0 )
    {
      *(uint8_t *)(pArg1 + 56) = sub_4423D0(nullptr) != 0;
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[move speed]") != 0 )
    {
      *(uint32_t *)(pArg1 + 60) = sub_4423D0(nullptr);
      *(uint32_t *)(pArg1 + 64) = sub_4423D0(nullptr);
      *(uint32_t *)(pArg1 + 68) = sub_4423D0(nullptr);
      *(uint32_t *)(pArg1 + 72) = sub_4423D0(nullptr);
      *(uint32_t *)(pArg1 + 76) = sub_4423D0(nullptr);
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[gravity]") != 0 )
    {
      *(uint32_t *)(pArg1 + 80) = sub_4423D0(nullptr);
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[start level]") != 0 )
    {
      *(uint32_t *)(pArg1 + 84) = sub_4423D0(nullptr);
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[permission level]") != 0 )
    {
      *(uint32_t *)(pArg1 + 88) = sub_4423D0(nullptr);
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[artifact slot]") != 0 )
    {
      *(uint32_t *)(pArg1 + 92) = sub_4423D0(nullptr);
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[learn overskill level]") != 0 )
    {
      *(uint32_t *)(pArg1 + 96) = sub_4423D0(nullptr);
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[basic motion]") != 0
      || (uint8_t)sub_423300(v12, "[walk motion]") != 0
      || (uint8_t)sub_423300(v12, "[run motion]") != 0
      || (uint8_t)sub_423300(v12, "[skill motion]") != 0
      || (uint8_t)sub_423300(v12, "[over skill motion]") != 0
      || (uint8_t)sub_423300(v12, "[response motion]") != 0 )
    {
LABEL_45:
      sub_443370();
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[etc motion]") != 0 )
    {
      sub_4017E0(pArg1 + 268);
      while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v10);
    }
    else if ( (uint8_t)sub_423300(v12, "[attack info]") != 0 )
    {
      sub_4017E0(pArg1 + 284);
      while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v10);
    }
    else if ( (uint8_t)sub_423300(v12, "[int data]") != 0 )
    {
      sub_5E5260((void **)(pArg1 + 300));
      for ( i = sub_4423D0(&v11); v11 != 0; i = sub_4423D0(&v11) )
        sub_431230(pArg1 + 300, &i);
    }
    else if ( (uint8_t)sub_423300(v12, "[string data]") != 0 )
    {
      sub_4017E0(pArg1 + 316);
      while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v10);
    }
  }
  while ( (uint8_t)sub_443430(v12) != 0 );
  v2 = (const char *)nArg2;
LABEL_63:
  *(uint32_t *)pArg1 = sub_4A2F80(dword_9B7C54, v2);
  LOBYTE(v17) = 0;
  sub_41B010((void **)&v10);
  if ( v15 >= 0x10 )
    j__free(Block);
  return 1;
}


// ------------------------------------------------------------
// 0x50BE20 sub_50BE20
// ------------------------------------------------------------
char **/*stdcall*/ sub_50BE20(char **pszArg1, int nArg2, int nArg3)
{
  sub_509C00(pszArg1, nArg2, nArg3);
  return &pszArg1[4 * nArg2];
}



// ------------------------------------------------------------
// 0x50BE50 sub_50BE50
// ------------------------------------------------------------
int */*thiscall*/ sub_50BE50(int *this, int *pDwArg2, int nArg3, int nArg4)
{
  int fld_e2; // edi

  if ( nArg3 != nArg4 )
  {
    fld_e2 = sub_5097A0(nArg4, *(this + 2), nArg3);
    sub_42CC00(fld_e2, *(this + 2));
    *(this + 2) = fld_e2;
  }
  *pDwArg2 = nArg3;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x50BEA0 sub_50BEA0
// ------------------------------------------------------------
void /*thiscall*/ sub_50BEA0(int *this, int pArg2, unsigned int uArg3, int nArg4)
{
  int fld_e1; // edx
  int fld_e2; // ecx
  unsigned int fld_e3; // eax
  int fld_e22; // ecx
  unsigned int v10; // eax
  int fld_e27; // ecx
  int fld_e28; // eax
  char *pMem; // ebx
  int fld_e13; // ecx
  int fld_e29; // eax
  unsigned int v16; // edi
  uint32_t *fld_e23; // eax
  int fld_e26; // edi
  int v19; // edi
  uint32_t *v20; // eax
  int fld_e12; // [esp-18h] [ebp-4Ch]
  void *Block2; // [esp-18h] [ebp-4Ch]
  int fld_e25; // [esp-Ch] [ebp-40h]
  unsigned int fld_e24; // [esp-8h] [ebp-3Ch]
  int v25; // [esp+0h] [ebp-34h] BYREF
  int v26; // [esp+Ch] [ebp-28h] BYREF
  void *v27; // [esp+10h] [ebp-24h]
  void *Block; // [esp+1Ch] [ebp-18h]
  int *pThis; // [esp+20h] [ebp-14h]
  int *v30; // [esp+24h] [ebp-10h]
  int v31; // [esp+30h] [ebp-4h]
  uint32_t *v32; // [esp+40h] [ebp+Ch]
  int v33; // [esp+44h] [ebp+10h]

  v30 = &v25;
  pThis = this;
  sub_509580(&v26, nArg4);
  fld_e1 = *(this + 1);
  fld_e2 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) >> 4;
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) >> 4;
    if ( 0xFFFFFFF - fld_e2 < uArg3 )
      sub_508F60(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) >> 4;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (uint32_t *)*(this + 2);
      Block = fld_e23;
      if ( ((int)fld_e23 - pArg2) >> 4 >= uArg3 )
      {
        v19 = (int)&fld_e23[-4 * uArg3];
        v20 = sub_5099F0(v19, (int)fld_e23, fld_e23);
        Block2 = Block;
        *(this + 2) = (int)v20;
        sub_5099D0(pArg2, v19, Block2);
        sub_5099A0(pArg2, pArg2 + 16 * uArg3, &v26);
      }
      else
      {
        sub_5099F0(pArg2, (int)fld_e23, (uint32_t *)(pArg2 + 16 * uArg3));
        fld_e24 = uArg3 - ((*(this + 2) - pArg2) >> 4);
        fld_e25 = *(this + 2);
        LOBYTE(v31) = 3;
        sub_50BE20(fld_e25, fld_e24, &v26);
        fld_e26 = 16 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v31 = 0;
        sub_5099A0(pArg2, fld_e26 - 16 * uArg3, &v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) >> 4;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
      {
        if ( fld_e1 != 0 )
          fld_e28 = (*(this + 2) - fld_e1) >> 4;
        else
          fld_e28 = 0;
        v10 = uArg3 + fld_e28;
      }
      v33 = 16 * v10;
      pMem = (char *)operator new(16 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      LOBYTE(v31) = 1;
      v32 = sub_5099F0(fld_e12, pArg2, pMem);
      sub_509C00(v32, uArg3, (int)&v26);
      sub_5099F0(pArg2, *(this + 2), &v32[4 * uArg3]);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e29 = (*(this + 2) - fld_e13) >> 4;
      else
        fld_e29 = 0;
      v16 = fld_e29 + uArg3;
      if ( fld_e13 != 0 )
      {
        sub_42CC00(fld_e13, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v33];
      *(this + 2) = (int)&pMem[16 * v16];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v27 != nullptr )
    j__free(v27);
}

