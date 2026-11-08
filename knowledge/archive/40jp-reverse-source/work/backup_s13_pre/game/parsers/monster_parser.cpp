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
//   std::vector<T>::resize 本体（元素 20 字节，如 [drop prob] 概率条目）：
//   目标条数 ≤ 现有条数时截尾销毁多余元素；不足时转 sub_4FBE30 重分配并补构造新元素。
//   返回值 = 调整后的 end 指针。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4FC0F0(int this, unsigned int uArg2, int Block, int nArg4, int nArg5, int nArg6, int nArg7)
{
  int fld_4; // ecx
  unsigned int result; // eax
  int fld_82; // eax
  uint32_t *fld_8; // edi

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 8) - fld_4) / 20;  // this+8 物品 id
  else
    result = 0;  // result=this+8 物品 id
  if ( result >= uArg2 )  // result=this+8 物品 id
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    {
      fld_8 = *(uint32_t **)(this + 8);  // this+8 物品 id
      result = ((int)fld_8 - fld_4) / 20;  // result=this+8 物品 id
      if ( uArg2 < result )  // result=this+8 物品 id
      {
        result = fld_4 + 20 * uArg2;  // result=this+8 物品 id
        if ( (uint32_t *)result != fld_8 )  // result=this+8 物品 id
        {
          result = (unsigned int)sub_4FBD40(fld_8, fld_8, (uint32_t *)result);  // sub_4FBD40 —— 20 字节元素正向搬移（5 双字直拷）
          *(uint32_t *)(this + 8) = result;  // 写字段 this+8（nSkillRec8） ← result
        }
      }
    }
  }
  else
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) / 20;  // this+8 物品 id
    else
      fld_82 = 0;  // fld_82=this+8 物品 id
    return sub_4FBE30((int *)this, *(char **)(this + 8), uArg2 - fld_82, &Block);  // sub_4FBE30 —— 20 字节元素向量插入（三路分支 + 1.5 倍扩容）
  }
  return result;  // result=this+8 物品 id
}



// ------------------------------------------------------------
// 0x4FC1A0 sub_4FC1A0
//   std::vector<T>::resize(n) 外壳：清掉尾部占位参数后转调 sub_4FC0F0。
//   sub_4FC1E0 解析 [drop prob number] 报条数后即调它扩表（this=pCfg+64 经寄存器传入）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4FC1A0(void *this, unsigned int uArg2)  // sub_4FC1A0 —— vector::resize（this=pCfg+64 经寄存器传入）
{
  return sub_4FC0F0((int)this, uArg2, 0, 0, 0, 0, 0);  // 调 sub_4FC0F0
}



// ------------------------------------------------------------
// 0x4FC1E0 sub_4FC1E0 —— 全局战斗/成长配置解析器（[nation code]/[version]/经验与掉率增益表族）
//   [nation code]/[version] 区码与版本；经验增益 3 表（队伍人数×4 / 副本难度×4 / 结算评级×5）
//   + 掉率增益 4 表（难度/队伍/怪物种类） + 奖励概率 + 物品与稀有度判定基数 + 公会成本。
//   [drop prob number]/[drop prob]、[result reward prob number]/[result reward prob] 成对出现：
//   先报条数再逐条读（研究 20 §12 的"固定字段对"同型）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FC1E0(int pArg1, const char *ArgList)  // sub_4FC1E0 —— 全局战斗/成长配置解析器（[nation code]/[version]/经验与掉率增益表族）
{
  char result; // al
  int pCfg; // ebx  全局战斗/成长配置对象（=pArg1，字段偏移见各标签分支）
  int i2; // esi
  float *pfPartyExp; // esi  [party user number exp bonusrate] → +12 float[4] 写入游标
  int i; // edi
  float *pfDiffExp; // esi  [dungeon difficulty exp bonusrate] → +28 float[4]
  int j; // edi
  float *pfRankExp; // esi  [clear rank exp bonusrate] → +44 float[5]
  int k; // edi
  int nTableSize; // eax  [drop prob number] 报出的条数
  int nDropIdx; // edi  [drop prob] 已填条目计数
  int *piDropEntry; // esi  掉落概率条目写入游标（每条 20 字节）
  int nDropVal1; // eax
  int nDropVal2; // eax
  int nDropVal3; // eax
  int nDropVal4; // eax
  void ***pFillOffNext; // edx  下一条目偏移暂存（void*** 算术，+5 即 +20 字节/条）
  float *pfDiffDrop; // esi  [dungeon difficulty drop bonusrate] → +80 float[4]
  int m; // edi
  float *pfPartyDrop; // esi  [party user number drop bonusrate] → +96 float[4]
  int n; // edi
  float *pfKindDrop; // esi  [drop bonusrate of monster kind] → +112 float[4]
  int ii; // edi
  int nRewardIdx; // edi  [result reward prob] 已填条目计数
  int nRewardOff; // ebx  已填字节偏移（步进 20）
  int *piRewardEntry; // esi  结算奖励条目写入游标
  int nRewardVal1; // eax
  int nRewardVal2; // eax
  float *pfDiffReward; // esi  [dungeon difficulty reward bonusrate] → +144 float[4]
  int jj; // edi
  float *pfPartyReward; // esi  [party user number reward bonusrate] → +160 float[4]
  int kk; // edi
  int *piEquipRarity; // esi  [basis of equipment rarity dicision] → +180 int[4]
  int mm; // edi
  int *piStackRarity; // esi  [basis of stackable rarity dicision] → +196 int[4]
  int nn; // edi
  const char *pszTagData; // eax  未识别标签报错时取行文本指针
  void **tmpTagBuf[3]; // [esp-1Ch] [ebp-5Ch] BYREF  临时行拷贝（未识别标签检查用）
  uint8_t *okDummy1; // [esp-10h] [ebp-50h]  sub_4423D0 可解析标志占位（不检查）
  uint8_t *okDummy2; // [esp-Ch] [ebp-4Ch]
  uint8_t *okDummy3; // [esp-8h] [ebp-48h]
  unsigned int tmpTagCap; // [esp-4h] [ebp-44h]  临时行拷贝容量
  void ***tmpVal; // [esp+Ch] [ebp-34h] BYREF  多用途临时（掉落条目偏移游标 / stamina 表值 / 拷贝 this 占位）
  char bTokOk; // [esp+13h] [ebp-2Dh] BYREF  token 可解析标志
  int strLine; // [esp+14h] [ebp-2Ch] BYREF  行字符串对象头（&strLine=std::string 基址）
  void *strLineBuf; // [esp+18h] [ebp-28h] BYREF  行字符串 SSO 缓冲/堆指针
  int strLineLen; // [esp+28h] [ebp-18h]
  unsigned int strLineCap; // [esp+2Ch] [ebp-14h]
  int dword_796E502; // [esp+30h] [ebp-10h]
  int v51; // [esp+3Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)szPassword, (int)ArgList);  // 打开 PVF 脚本文件（szPassword=脚本读入上下文全局）
  if ( result != 0 )
  {
    pCfg = pArg1;
    sub_433EF0(pArg1);  // 清零/重置配置对象
    strLineCap = 15;    // 空 std::string 初始化（容量 15）
    strLineLen = 0;
    LOBYTE(strLineBuf) = 0;  // 调 取 16 位值低 8 位
    v51 = 0;
    bTokOk = 0;
    while ( (uint8_t)sub_443430(&strLine) != 0 )  // 逐行读入脚本
    {
      sub_442B20(&strLine);  // 行首非 '[' 的行喂给词法器
      if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[nation code]", 0xDu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[version]", 9u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[clear exp bonusrate]", 0x15u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[monster exp bonusrate]", 0x17u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              if ( (uint8_t)sub_423300(&strLine, "[party user number exp bonusrate]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                pfPartyExp = (float *)(pCfg + 12);  // → 对象+0x0C float[4]（按队伍人数）
                for ( i = 4; i != 0; --i )  // 遍历计次循环（i != 0）
                  *pfPartyExp++ = sub_442480(nullptr);  // 取下一 token 浮点值
              }
              else if ( (uint8_t)sub_423300(&strLine, "[dungeon difficulty exp bonusrate]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                pfDiffExp = (float *)(pCfg + 28);  // → 对象+0x1C float[4]（按副本难度）
                for ( j = 4; j != 0; --j )  // 遍历计次循环（j != 0）
                  *pfDiffExp++ = sub_442480(nullptr);  // sub_442480 —— 脚本 token 数值解析（double 版）
              }
              else if ( (uint8_t)sub_423300(&strLine, "[clear rank exp bonusrate]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                pfRankExp = (float *)(pCfg + 44);  // → 对象+0x2C float[5]（按结算评级）
                for ( k = 5; k != 0; --k )  // 遍历计次循环（k != 0）
                  *pfRankExp++ = sub_442480(nullptr);  // sub_442480 —— 脚本 token 数值解析（double 版）
              }
              else
              {
                if ( (uint8_t)sub_423300(&strLine, "[drop prob number]") == 0 )  // sub_423300 —— [end] → 解析结束
                {
                  if ( (uint8_t)sub_423300(&strLine, "[drop prob]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    nDropIdx = 0;
                    if ( sub_45E580(pCfg + 64) > 0 )  // vector::size（+64 掉落概率表）
                    {
                      tmpVal = nullptr;  // tmpVal = nullptr 空指针
                      do
                      {
                        piDropEntry = (int *)((char *)tmpVal + *(uint32_t *)(pCfg + 68));  // +68=数据指针
                        nDropVal1 = sub_4423D0(nullptr);  // 取下一 token 整型值
                        okDummy3 = nullptr;  // okDummy3 = nullptr 空指针
                        *piDropEntry = nDropVal1;  // *piDropEntry 写入 nDropVal1
                        nDropVal2 = sub_4423D0(okDummy3);  // sub_4423D0 —— [LOOP] → 动画对象+160
                        okDummy2 = nullptr;  // okDummy2 = nullptr 空指针
                        piDropEntry[1] = nDropVal2;
                        nDropVal3 = sub_4423D0(okDummy2);  // sub_4423D0 —— [LOOP] → 动画对象+160
                        okDummy1 = nullptr;  // okDummy1 = nullptr 空指针
                        piDropEntry[2] = nDropVal3;
                        nDropVal4 = sub_4423D0(okDummy1);  // sub_4423D0 —— [LOOP] → 动画对象+160
                        pFillOffNext = tmpVal + 5;  // +5 个 void*** = 下一条目（20 字节）
                        piDropEntry[3] = nDropVal4;
                        piDropEntry[4] = 1000;  // 默认权重 1000（千分比基数）
                        ++nDropIdx;  // 计数自增 nDropIdx
                        tmpVal = pFillOffNext;
                      }
                      while ( nDropIdx < sub_45E580(pCfg + 64) );  // sub_45E580 —— vector::size（+64 掉落概率表）
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(&strLine, "[dungeon difficulty drop bonusrate]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pfDiffDrop = (float *)(pCfg + 80);  // → 对象+0x50 float[4]
                    for ( m = 4; m != 0; --m )  // 遍历计次循环（m != 0）
                      *pfDiffDrop++ = sub_442480(nullptr);  // sub_442480 —— 脚本 token 数值解析（double 版）
                    continue;
                  }
                  if ( (uint8_t)sub_423300(&strLine, "[party user number drop bonusrate]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pfPartyDrop = (float *)(pCfg + 96);  // → 对象+0x60 float[4]
                    for ( n = 4; n != 0; --n )  // 遍历计次循环（n != 0）
                      *pfPartyDrop++ = sub_442480(nullptr);  // sub_442480 —— 脚本 token 数值解析（double 版）
                    continue;
                  }
                  if ( (uint8_t)sub_423300(&strLine, "[drop bonusrate of monster kind]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pfKindDrop = (float *)(pCfg + 112);  // → 对象+0x70 float[4]
                    for ( ii = 4; ii != 0; --ii )  // 遍历计次循环（ii != 0）
                      *pfKindDrop++ = sub_442480(nullptr);  // sub_442480 —— 脚本 token 数值解析（double 版）
                    continue;
                  }
                  if ( (uint8_t)sub_423300(&strLine, "[result reward prob number]") == 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    if ( (uint8_t)sub_423300(&strLine, "[result reward prob]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      nRewardIdx = 0;
                      if ( sub_45E580(pCfg + 128) > 0 )  // +128 结算奖励概率表 vector
                      {
                        nRewardOff = 0;
                        do
                        {
                          piRewardEntry = (int *)(nRewardOff + *(uint32_t *)(pArg1 + 132));  // +132=数据指针
                          nRewardVal1 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                          okDummy3 = nullptr;  // okDummy3 = nullptr 空指针
                          *piRewardEntry = nRewardVal1;  // *piRewardEntry 写入 nRewardVal1
                          nRewardVal2 = sub_4423D0(okDummy3);  // sub_4423D0 —— [LOOP] → 动画对象+160
                          okDummy2 = nullptr;  // okDummy2 = nullptr 空指针
                          piRewardEntry[1] = nRewardVal2;
                          piRewardEntry[2] = 0;
                          piRewardEntry[3] = sub_4423D0(okDummy2);  // sub_4423D0 —— [LOOP] → 动画对象+160
                          piRewardEntry[4] = 1000;  // 默认权重 1000
                          ++nRewardIdx;  // 计数自增 nRewardIdx
                          nRewardOff += 20;
                        }
                        while ( nRewardIdx < sub_45E580(pArg1 + 128) );  // sub_45E580 —— vector::size（+64 掉落概率表）
                        pCfg = pArg1;
                      }
                    }
                    else if ( (uint8_t)sub_423300(&strLine, "[dungeon difficulty reward bonusrate]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      pfDiffReward = (float *)(pCfg + 144);  // → 对象+0x90 float[4]
                      for ( jj = 4; jj != 0; --jj )  // 遍历计次循环（jj != 0）
                        *pfDiffReward++ = sub_442480(nullptr);  // sub_442480 —— 脚本 token 数值解析（double 版）
                    }
                    else if ( (uint8_t)sub_423300(&strLine, "[party user number reward bonusrate]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      pfPartyReward = (float *)(pCfg + 160);  // → 对象+0xA0 float[4]
                      for ( kk = 4; kk != 0; --kk )  // 遍历计次循环（kk != 0）
                        *pfPartyReward++ = sub_442480(nullptr);  // sub_442480 —— 脚本 token 数值解析（double 版）
                    }
                    else if ( (uint8_t)sub_423300(&strLine, "[basis of item dicision]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      *(uint32_t *)(pCfg + 176) = sub_4423D0(nullptr);  // → 对象+0xB0 物品判定基数
                    }
                    else if ( (uint8_t)sub_423300(&strLine, "[basis of equipment rarity dicision]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      piEquipRarity = (int *)(pCfg + 180);  // → 对象+0xB4 int[4]（装备稀有度分档基数）
                      for ( mm = 4; mm != 0; --mm )  // 遍历计次循环（mm != 0）
                        *piEquipRarity++ = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    }
                    else if ( (uint8_t)sub_423300(&strLine, "[basis of stackable rarity dicision]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      piStackRarity = (int *)(pCfg + 196);  // → 对象+0xC4 int[4]（可堆叠稀有度分档基数）
                      for ( nn = 4; nn != 0; --nn )  // 遍历计次循环（nn != 0）
                        *piStackRarity++ = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    }
                    else if ( (uint8_t)sub_423300(&strLine, "[stamina recovery cost]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      sub_5E5260((void **)(pCfg + 212));  // 清空 +0xD4 容器
                      for ( tmpVal = (void ***)sub_4423D0(&bTokOk); bTokOk != 0; tmpVal = (void ***)sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                        sub_431230(pCfg + 212, &tmpVal);  // 逐个 push_back 疲劳恢复费用
                    }
                    else if ( (uint8_t)sub_423300(&strLine, "[guild create cost]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      *(uint32_t *)(pCfg + 228) = sub_4423D0(nullptr);  // → 对象+0xE4
                    }
                    else if ( (uint8_t)sub_423300(&strLine, "[guild levelup cost]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      *(uint32_t *)(pCfg + 232) = sub_4423D0(nullptr);  // → 对象+0xE8
                    }
                    else if ( (uint8_t)sub_423300(&strLine, "[guild point acquirement ratio]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      *(uint32_t *)(pCfg + 236) = sub_4423D0(nullptr);  // → 对象+0xEC
                    }
                    else
                    {
                      tmpVal = tmpTagBuf;  // 拷贝构造目标（this 经寄存器传给 sub_401690）
                      sub_401690(&strLine);  // 拷贝当前行到临时串
                      if ( sub_442C80((char)tmpTagBuf[0], tmpTagBuf[1], (int)tmpTagBuf[2], (int)okDummy1, (int)okDummy2, (int)okDummy3, tmpTagCap) == 0 )  // 行首是 '[' 仍没匹配上
                      {
                        pszTagData = (const char *)strLineBuf;
                        if ( strLineCap < 0x10 )
                          pszTagData = (const char *)&strLineBuf;  // SSO：短串直接取缓冲
                        off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, pszTagData);  // off_77F3FC —— 日志打印（printf 风格）
                      }
                    }
                    continue;
                  }
                }
                nTableSize = sub_4423D0(nullptr);  // [drop prob number] 条数
                sub_4FC1A0(nTableSize);  // vector::resize（this=pCfg+64 经寄存器传入）
              }
            }
            else
            {
              *(float *)(pCfg + 8) = sub_442480(nullptr);  // [monster exp bonusrate] → +0x08
            }
          }
          else
          {
            *(float *)(pCfg + 4) = sub_442480(nullptr);  // [clear exp bonusrate] → +0x04
          }
        }
        else
        {
          for ( i2 = 0; i2 < 4; ++i2 )  // 遍历计次循环（i2 < 4）
            *(uint8_t *)(i2 + pCfg) = sub_4423D0(nullptr);  // [version] → 对象+0x00 起 4 字节
        }
      }
      else
      {
        dword_78FF38 = sub_4423D0(nullptr);  // [nation code] → 全局单字节模式标志（sub_442B20 依赖）
        if ( dword_78FF38 == 1 )  // dword_78FF38 —— [nation code] → 全局单字节模式标志（sub_442B20 依赖）
          dword_9B0AB0 = (int)&dword_9B0C08;  // 区码 1 → 切换字符串表
        else
          dword_9B0AB0 = (int)&dword_9B0BC8;  // dword_9B0AB0 —— 区码 1 → 切换字符串表
      }
    }
    if ( strLineCap >= 0x10 )
      j__free(strLineBuf);  // 长串释放堆缓冲
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FC840 sub_4FC840
//   设定脚本根目录（byte_9B6C78，补 '\' 或 '/' 结尾）后在目录下加载文件表，
//   成功与否经 sub_443C40 返回（未知标签/文件探测用）。
// ------------------------------------------------------------
bool /*cdecl*/ sub_4FC840(const char *pArg1, int nArg2)  // 全局战斗/成长配置解析器（[nation code]/[version]/经验与掉率增益表族）
{
  strcpy(byte_9B6C78, pArg1);  // byte_9B6C78 —— 非 \ 且非 /
  if ( byte_9B6C77[strlen(byte_9B6C78)] != 92 && byte_9B6C77[strlen(byte_9B6C78)] != 47 )  // 非 '\' 且非 '/'
    *(uint16_t *)&byte_9B6C78[strlen(byte_9B6C78)] = 92;  // 补 '\' 结尾
  return (uint8_t)sub_443C40((int)&unk_9B6D78, (char)byte_9B6C78, nArg2) != 0;  // sub_443C40 —— 脚本文件列表装表
}



// ------------------------------------------------------------
// 0x4FC8D0 sub_4FC8D0
//   std::map/set 迭代器 _Dec()：把迭代器移到前驱（右子树存在则取右子树最左，
//   否则沿 +4 父指针上行）。节点 +0x45 为 _Isnil 标志。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FC8D0(void *this)  // sub_4FC8D0 —— 迭代器后退一格取前驱
{
  uint32_t *pNode; // eax
  int result; // eax
  int pDescend; // edx

  pNode = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 69) != 0 )  // 当前是 nil 哨兵
  {
    result = pNode[2];
    *(uint32_t *)this = result;
  }
  else
  {
    pDescend = *pNode;
    if ( *(uint8_t *)(*pNode + 69) != 0 )  // 若 *(uint8_t *)(*pNode + 69) != 0
    {
      result = pNode[1];
      if ( *(uint8_t *)(result + 69) == 0 )  // 若 *(uint8_t *)(result + 69) == 0
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )  // 若 *(uint32_t *)this != *(uint32_t *)result
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);  // 读字段 result = result+4（pHostObj）
        }
        while ( *(uint8_t *)(result + 69) == 0 );  // 写字段 result+69 ← = 0 )
        if ( *(uint8_t *)(result + 69) == 0 )  // 若 *(uint8_t *)(result + 69) == 0
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(pDescend + 8); *(uint8_t *)(result + 69) == 0; result = *(uint32_t *)(result + 8) )  // 读字段 result = pDescend+8（nSkillRec8）
        pDescend = result;
      *(uint32_t *)this = pDescend;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FC930 sub_4FC930
//   副本入口区域条目清空（[area] 域内复用）：id=-1，+0x04 字符串清空，+0x28 与
//   +0x28..0x30 三指针容器释放归零（sub_4FD040 的 [area] 处理中调用）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4FC930(void *this)  // sub_4FC930 —— 清空区域条目
{
  *(uint32_t *)this = -1;  // 区域 id = -1
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】清空 this+4 处字符串（this 经寄存器）
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  if ( *((uint32_t *)this + 10) != 0 )  // 若 *((uint32_t *)this + 10) != 0
    j__free(*((void **)this + 10));  // 释放堆块
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
}



// ------------------------------------------------------------
// 0x4FC970 sub_4FC970
//   区域条目拷贝构造：id ← +0、名称串 ← +4（sub_4014D0 串拷贝）、+0x20 附加值、
//   +0x24 起的链表经 sub_435020 重建。sub_4FCAC0 建新节点时调用。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FC970(uint32_t *this, uint32_t *pArg2)  // sub_4FC970 —— 拷贝名称串与链表
{
  uint32_t *pThis_1; // ecx

  pThis_1 = this + 1;
  *this = *pArg2;  // *this 写入 *pArg2
  pThis_1[6] = 15;
  pThis_1[5] = 0;
  *((uint8_t *)pThis_1 + 4) = 0;  // 写字段 pThis_1+4（pHostObj）
  sub_4014D0((std::_String_base *)pThis_1, pArg2 + 1, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(this + 8) = pArg2[8];  // 写字段 this+8（nSkillRec8） ← pArg2[8]
  sub_435020(pArg2 + 9);  // sub_435020 —— uint32 向量整体赋值
  return this;
}



// ------------------------------------------------------------
// 0x4FC9F0 sub_4FC9F0
//   区域条目默认构造（[area] 处理开头调用）：id=-1、+0x04 空串、+0x28/+0x28..0x30
//   容器三指针清零。
// ------------------------------------------------------------
char */*thiscall*/ sub_4FC9F0(char *this)  // sub_4FC9F0 —— 栈上默认构造条目
{
  char *pThis_4; // ecx  = this+0x04 处的名称字符串

  pThis_4 = this + 4;  // this+4 宿主对象
  *((uint32_t *)pThis_4 + 6) = 15;  // 空串：容量 15
  *((uint32_t *)pThis_4 + 5) = 0;   // 长度 0
  pThis_4[4] = 0;                   // 首字节 NUL
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *(uint32_t *)this = -1;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  if ( *((uint32_t *)this + 10) != 0 )  // 若 *((uint32_t *)this + 10) != 0
    j__free(*((void **)this + 10));  // 释放堆块
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  return this;
}



// ------------------------------------------------------------
// 0x4FCA80 sub_4FCA80
//   区域条目赋值：id、名称串、+0x20 值逐域拷贝，+0x24 链表经 sub_4ED3F0 深拷贝
//   （[area] 收尾时把临时条目搬入所属容器）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FCA80(uint32_t *this, uint32_t *pArg2)  // sub_4FCA80 —— 把条目赋值进槽位
{
  *this = *pArg2;  // *this 写入 *pArg2
  sub_4014D0((std::_String_base *)(this + 1), pArg2 + 1, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(this + 8) = pArg2[8];  // 写字段 this+8（nSkillRec8） ← pArg2[8]
  sub_4ED3F0((int)(this + 9), (int)(pArg2 + 9));  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
  return this;
}



// ------------------------------------------------------------
// 0x4FCAC0 sub_4FCAC0
//   堆上构造区域条目节点（0x48 字节）：{id1,id2,id3, 名称串(4FC970 拷贝),
//   +68 标志字节 pszArg5, +69=0}，供 [area] 列表 push 用。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4FCAC0(int nArg1, int nArg2, int nArg3, uint32_t *pArg4, char pszArg5)  // 函数定义: 建新节点时调用
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  pMem = operator new(0x48u);  // 堆分配
  pMem2 = pMem;
  v8[4] = pMem;
  v8[8] = (void *)1;  // v8[8] 写入 (void *)1
  v8[3] = pMem;
  if ( pMem != nullptr )
  {
    *pMem = nArg1;  // *pMem 写入 nArg1
    pMem[1] = nArg2;
    pMem[2] = nArg3;
    pMem[3] = *pArg4;  // pMem[3] 写入 *pArg4
    sub_4FC970(pMem + 4, pArg4 + 1);  // 拷贝名称串与链表
    *((uint8_t *)pMem2 + 68) = pszArg5;  // 写字段 pMem2+68（nCharCount）
    *((uint8_t *)pMem2 + 69) = 0;  // 写字段 pMem2[69]（宽1字节）
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x4FCB60 sub_4FCB60
//   std::map 红黑树插入：sub_4FCAC0 在堆上建节点后挂入树并做回平衡
//   （节点 +68 = 红黑色标志，sub_4CE650/4CE6B0 = 左旋/右旋）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FCB60(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)  // 函数定义: 插入并返回 {新节点
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

  if ( *(this + 2) >= 0x4924923u )  // 若 *(this + 2) >= 0x4924923u
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_4FCAC0(*(this + 1), pArg4, *(this + 1), nArg5, 0);  // 调 sub_4FCAC0
  fld_e12 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8 = 技能槽记录首字
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4 = pHostObj
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;  // *pArg4 写入 fld_e1
    fld_e13 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
    if ( pArg4 == (uint32_t *)*fld_e13 )  // 若 pArg4 == (uint32_t *)*fld_e13
      *fld_e13 = fld_e1;  // *fld_e13 写入 fld_e1
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // 若 pArg4 == *(uint32_t **)(fld_e14 + 8)
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
  }
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 68) == 0 )  // 若 *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 68) == 0
  {
    while ( 1 )  // 当 1 循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )  // 若 *v10 == *v13
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 68) != 0 )  // 若 *(uint8_t *)(v14 + 68) != 0
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_4CE650(*v10);  // 调 sub_4CE650
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 68) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 68) = 0;
          sub_4CE6B0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 调 sub_4CE6B0
          goto LABEL_21;  // 跳转 LABEL_21
        }
      }
      else if ( *(uint8_t *)(v14 + 68) != 0 )  // 否则若 *(uint8_t *)(v14 + 68) != 0
      {
        if ( fld_e16 == *v12 )  // 若 fld_e16 == *v12
        {
          fld_e16 = *v10;
          sub_4CE6B0(*v10);  // 调 sub_4CE6B0
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 68) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 68) = 0;
        sub_4CE650(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 调 sub_4CE650
        goto LABEL_21;  // 跳转 LABEL_21
      }
      *(uint8_t *)(*v10 + 68) = 1;
      *(uint8_t *)(v14 + 68) = 1;  // 写字段 v14+68（nCharCount） ← 1
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 68) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 68) != 0 )  // 若 *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 68) != 0
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 68) = 1;  // this+4 = pHostObj
  *uArg2 = fld_e1;  // *uArg2 写入 fld_e1
  return uArg2;
}


// ------------------------------------------------------------
// 0x4FCD10 sub_4FCD10
//   std::map::insert（唯一 key 版）：按 key（节点 +0x0C，即区域 id）下行比较，
//   已存在 → 返回 {已有节点, 0}；否则经 sub_4FCB60 插入并返回 {新节点, 1}。
//   uArg3 迭代器兼作下行游标（插入提示 hint）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FCD10(int *this, int pArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // ebx
  uint32_t *pNode; // esi  下行停留节点
  int *pWalk; // eax  下行游标
  bool bLess; // cl
  int nKey; // edx
  uint32_t *pFound; // edx
  int nNewNode; // edx
  int v12; // ecx
  char bHintLess; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  pNode = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  pWalk = (int *)pNode[1];
  bLess = true;
  bHintLess = 1;
  if ( *((uint8_t *)pWalk + 69) == 0 )  // 若 *((uint8_t *)pWalk + 69) == 0
  {
    nKey = *uArg3;
    do
    {
      bLess = nKey < pWalk[3];
      pNode = pWalk;
      bHintLess = bLess;
      if ( nKey >= pWalk[3] )
        pWalk = (int *)pWalk[2];  // key >= 节点 key → 右子树
      else
        pWalk = (int *)*pWalk;    // key <  节点 key → 左子树
    }
    while ( *((uint8_t *)pWalk + 69) == 0 );  // 当 *((uint8_t *)pWalk + 69) == 0 循环
  }
  pFound = pNode;
  uArg3 = pNode;
  if ( bLess )  // 若 bLess
  {
    if ( pNode == *(uint32_t **)*(this + 1) )  // 若 pNode == *(uint32_t **)*(this + 1)
    {
      nNewNode = *sub_4FCB60(this, &uArg3, 1, pNode, uArg32);  // 调 插入并返回 {新节点
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      *(uint32_t *)pArg2 = nNewNode;
      return pArg2;
    }
    sub_4FC8D0(&uArg3);  // 迭代器后退一格取前驱
    pFound = uArg3;
  }
  if ( pFound[3] >= *uArg32 )  // 已有相同 key
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
    *(uint32_t *)pArg2 = pFound;
    return pArg2;
  }
  else
  {
    v12 = *sub_4FCB60(this, &uArg3, bHintLess, pNode, uArg32);  // 调 插入并返回 {新节点
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4FCDD0 sub_4FCDD0
//   std::map::insert(hint 版)：先用提示迭代器 pArg3 与前后邻居比较确定插入点，
//   不确定则回退 sub_4FCD10 重查（LABEL_22）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FCDD0(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // 若 *(uint32_t *)(this + 8) == 0
  {
    sub_4FCB60((int *)this, uArg2, 1, *(uint32_t **)(this + 4), pArg4);  // 调 sub_4FCB60
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+4 宿主对象
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )  // 若 pArg3 == (uint32_t *)*fld_4
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4FCB60((int *)this, uArg2, 1, pArg3, pArg4);  // 调 sub_4FCB60
      return uArg2;
    }
    goto LABEL_22;  // 跳转 LABEL_22
  }
  if ( pArg3 == fld_4 )  // fld_4=this+4 宿主对象
  {
    v8 = (uint32_t *)fld_4[2];  // fld_4=this+4 宿主对象
    if ( v8[3] < *pArg4 )  // 若 v8[3] < *pArg4
    {
      sub_4FCB60((int *)this, uArg2, 0, v8, pArg4);  // 调 sub_4FCB60
      return uArg2;
    }
    goto LABEL_22;  // 跳转 LABEL_22
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4FC8D0(&pArg4), pArg4[3] >= *pArg42) )  // sub_4FC8D0 —— 迭代器后退一格取前驱
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_4CE5F0(&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )  // sub_4CE5F0 —— 调用 sub_4CE5F0
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4FCD10((int *)this, (int)v10, pArg42);
      *uArg2 = v9;  // *uArg2 写入 v9
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 69) != 0 )  // 若 *(uint8_t *)(pArg3[2] + 69) != 0
      sub_4FCB60((int *)this, uArg2, 0, pArg3, pArg42);  // 调 sub_4FCB60
    else
      sub_4FCB60((int *)this, uArg2, 1, pArg4, pArg42);  // 调 sub_4FCB60
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 69) != 0 )  // 若 *(uint8_t *)(pArg4[2] + 69) != 0
      sub_4FCB60((int *)this, uArg2, 0, pArg4, pArg42);  // 调 sub_4FCB60
    else
      sub_4FCB60((int *)this, uArg2, 1, pArg3, pArg42);  // 调 sub_4FCB60
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4FCF30 sub_4FCF30
//   map<区域id, 区域条目>::operator[]（sub_4FD040 [area] 收尾用）：按 *pDwArg2
//   下行查找；没有则栈上默认构造条目（4FC9F0→4FC970 拷贝）再经 4FCDD0 插入。
//   返回条目数据指针（节点+4）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FCF30(uint32_t *this, int *pDwArg2)  // sub_4FCF30 —— map<id,条目> 取/建槽位（this 经寄存器）
{
  int *pDwArg22; // ebx  区域 id 指针副本
  uint32_t *pNode; // esi  下行停留节点（= 插入提示）
  int *pWalk; // eax  下行游标
  char *pNewEntry; // eax  栈上默认构造的条目
  int nKey; // [esp+Ch] [ebp-78h] BYREF
  int tmpEntry; // [esp+10h] [ebp-74h] BYREF  条目拷贝目标
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
  pNode = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  pWalk = (int *)pNode[1];
  while ( *((uint8_t *)pWalk + 69) == 0 )  // 沿树下行（+0x45=_Isnil）
  {
    if ( pWalk[3] >= *pDwArg2 )  // 节点 key(+0x0C) >= 目标 id → 左
    {
      pNode = pWalk;
      pWalk = (int *)*pWalk;
    }
    else
    {
      pWalk = (int *)pWalk[2];  // 否则右
    }
  }
  if ( pNode == (uint32_t *)*(this + 1) || *pDwArg2 < pNode[3] )  // 没找到 → 插入
  {
    pNewEntry = sub_4FC9F0(v16);  // 栈上默认构造条目
    nKey = *pDwArg22;
    v22 = 0;
    sub_4FC970(&tmpEntry, pNewEntry);  // 拷贝条目
    LOBYTE(v22) = 1;  // 调 取 16 位值低 8 位
    pNode = (uint32_t *)*sub_4FCDD0((int)this, &pDwArg2, pNode, &nKey);
    // ↓ 析构两个临时条目里的 std::string（SSO/堆两种形态）
    if ( Block != nullptr )
      j__free(Block);  // 释放堆块
    Block = nullptr;  // Block = nullptr 空指针
    v14 = 0;
    v15 = 0;
    if ( v12 >= 0x10 )
      j__free(v10);  // 释放堆块
    v12 = 15;
    v11 = 0;
    LOBYTE(v10) = 0;  // 调 取 16 位值低 8 位
    if ( v19 != nullptr )
      j__free(v19);  // 释放堆块
    v19 = nullptr;  // v19 = nullptr 空指针
    v20 = 0;
    v21 = 0;
    if ( v18 >= 0x10 )
      j__free(v17);  // 释放堆块
  }
  return pNode + 4;  // 节点 +4 = 条目数据
}



// ============================================================
// §B 0x4FD000-0x4FE000 地图(场景)定义 + 副本定义族
// ============================================================

// ------------------------------------------------------------
// 0x4FD040 sub_4FD040 —— 副本(dungeon)定义解析器
//   标签族：[name]/[entering title]/[cutscene image]/[dungeon what must be cleared]/[area]
//   + 入口类型枚举 [normal]=?/[gate]/[fishing place]/[pub]/[dungeon gate]。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FD040(int *pDwArg1, const char *ArgList)  // sub_4FD040 —— 副本(dungeon)定义解析器
{
  const char *pszFileNameBak; // edi  文件名副本（结尾按名查 ID 用）
  char result; // al
  int *pDungeon; // ebx  副本定义对象（=pDwArg1，偏移：+0x00 ID/+0x04 名/+0x20 进图标题/+0x3C 过场图/+0x58/+0x5C/+0x6C 路径）
  int nCmpLen; // ecx
  void **pszLineData; // esi  行文本数据指针（容量<0x10 取 SSO 缓冲）
  int nCmp; // eax
  int nEntryInt; // eax  [area] 逐个读入的整数
  char *pVecWrite; // esi  vector<int> 写入游标
  void **pszLineDataB; // eax
  char v11; // [esp-1Ch] [ebp-ACh] BYREF  未知标签检查：行拷贝串头（寄存器传参拆散）
  void *v12; // [esp-18h] [ebp-A8h]
  int v13; // [esp-14h] [ebp-A4h]
  int v14; // [esp-10h] [ebp-A0h]
  char *miscArgA; // [esp-Ch] [ebp-9Ch]  [area] 中复用为 sub_443370 的目标串槽位
  char *miscArgB; // [esp-8h] [ebp-98h]
  int *miscArg; // [esp-4h] [ebp-94h]  多用途（sub_443370 目标串 / 串容量实参 / 条目赋值目标）
  int i; // [esp+Ch] [ebp-84h] BYREF  vector 推入暂存
  char bTokOk; // [esp+13h] [ebp-7Dh] BYREF  token 可解析标志
  int areaEntryId; // [esp+14h] [ebp-7Ch] BYREF  区域条目对象基址：+0x00 id
  char entryNameHead; // [esp+18h] [ebp-78h] BYREF  条目 +0x04 字符串头
  void *entryNameBuf; // [esp+1Ch] [ebp-74h]
  int entryNameLen; // [esp+2Ch] [ebp-64h]
  unsigned int entryNameCap; // [esp+30h] [ebp-60h]
  int entryType; // [esp+34h] [ebp-5Ch]  条目 +0x20 类型枚举
  void *entryListBegin; // [esp+3Ch] [ebp-54h]  条目 +0x28 起 vector<int>
  void *entryListEnd; // [esp+40h] [ebp-50h]
  int entryListCapEnd; // [esp+44h] [ebp-4Ch]
  char typeStrHead[4]; // [esp+48h] [ebp-48h] BYREF  入口类型字符串对象头
  void *typeStrBuf; // [esp+4Ch] [ebp-44h]
  unsigned int typeStrLen; // [esp+5Ch] [ebp-34h]
  unsigned int typeStrCap; // [esp+60h] [ebp-30h]
  size_t strLine; // [esp+64h] [ebp-2Ch] BYREF  行字符串对象头（&strLine=std::string 基址）
  void *strLineBuf[4]; // [esp+68h] [ebp-28h] BYREF
  int strLineLen; // [esp+78h] [ebp-18h]
  unsigned int strLineCap; // [esp+7Ch] [ebp-14h]
  int dword_796E502; // [esp+80h] [ebp-10h]
  int v38; // [esp+8Ch] [ebp-4h]

  pszFileNameBak = ArgList;
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B6C78, (int)ArgList);  // 打开副本定义脚本
  if ( result == 0 )
    return result;
  pDungeon = pDwArg1;
  sub_4D1020(pDwArg1);  // 重置副本定义对象
  sub_443300((int)(pDwArg1 + 27), "%s%s", (char)&unk_9B6C78);  // +0x6C ← 根目录+文件名完整路径
  strLineCap = 15;  // 行字符串 = 空串
  strLineLen = 0;
  LOBYTE(strLineBuf[0]) = 0;  // 调 取 16 位值低 8 位
  v38 = 1;
  typeStrCap = 15;  // 类型字符串 = 空串
  typeStrLen = 0;
  LOBYTE(typeStrBuf) = 0;  // 调 取 16 位值低 8 位
  bTokOk = 0;
  sub_4FC9F0(&areaEntryId);  // 区域条目默认构造
  LOBYTE(v38) = 2;  // 调 取 16 位值低 8 位
  if ( (uint8_t)sub_443430(&strLine) == 0 )  // 读第一行
    goto LABEL_43;  // 跳转 LABEL_43
  do
  {
    sub_442B20(&strLine);  // 行预处理
    if ( strLineLen != 0 )
    {
      nCmpLen = strLineLen;
      if ( (unsigned int)strLineLen >= 6 )
        nCmpLen = 6;  // "[name]" 长度
      pszLineData = (void **)strLineBuf[0];
      if ( strLineCap < 0x10 )
        pszLineData = strLineBuf;
      nCmp = memcmp((const char *)pszLineData, "[name]", nCmpLen);  // 调 memcmp 内存比较
      if ( nCmp == 0 && (unsigned int)strLineLen >= 6 )
      {
        LOBYTE(nCmp) = strLineLen != 6;  // 调 取 16 位值低 8 位
        if ( nCmp == 0 )  // [name] 全串匹配
        {
          pDungeon = pDwArg1;
          miscArg = pDwArg1 + 1;
          sub_443370();  // [name] → 对象+0x04 名称串
          continue;
        }
      }
      pDungeon = pDwArg1;
    }
    if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[entering title]", 0x10u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[cutscene image]", 0x10u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[dungeon what must be cleared]", 0x1Eu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[area]", 6u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            // 未识别标签：拷贝整行，行首是 '[' 才报错
            i = (int)&v11;
            miscArg = (int *)15;
            miscArgB = nullptr;  // miscArgB = nullptr 空指针
            LOBYTE(v12) = 0;  // 调 取 16 位值低 8 位
            sub_4014D0((size_t *)&v11, &strLine, 0, 0xFFFFFFFF);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
            if ( (uint8_t)sub_442C80(v11, v12, v13, v14, (int)miscArgA, (int)miscArgB, (int)miscArg) == 0 )  // sub_442C80 —— 行首是 [ 仍未匹配
            {
              pszLineDataB = (void **)strLineBuf[0];
              if ( strLineCap < 0x10 )
                pszLineDataB = strLineBuf;
              off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)pszLineDataB);  // off_77F3FC —— 日志打印（printf 风格）
            }
          }
          else
          {
            sub_4FC930(&areaEntryId);  // 清空区域条目
            areaEntryId = sub_4423D0(nullptr);  // 条目 id
            miscArgB = &entryNameHead;
            sub_443370();  // 条目名称 → 条目+0x04 串
            miscArgA = typeStrHead;
            sub_443370();  // 入口类型字符串 → typeStr
            if ( sub_40BF00((std::_String_base *)typeStrHead, 0, typeStrLen, "[normal]", 8u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              if ( (uint8_t)sub_423300(typeStrHead, "[gate]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                entryType = 1;
              }
              else if ( (uint8_t)sub_423300(typeStrHead, "[fishing place]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                entryType = 2;
              }
              else if ( (uint8_t)sub_423300(typeStrHead, "[pub]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                entryType = 3;
              }
              else if ( (uint8_t)sub_423300(typeStrHead, "[dungeon gate]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                entryType = 4;
              }
            }
            else
            {
              entryType = 0;  // [normal]
            }
            nEntryInt = sub_4423D0(&bTokOk);  // 逐个读整数直到 token 耗尽
            for ( i = nEntryInt; bTokOk != 0; i = nEntryInt )  // 循环：i = nEntryInt; bTokOk != 0; i = nEntryInt
            {
              pVecWrite = (char *)entryListEnd;
              if ( entryListBegin != nullptr && ((uint8_t *)entryListEnd - (uint8_t *)entryListBegin) >> 2 < (unsigned int)((entryListCapEnd - (int)entryListBegin) >> 2) )
              {
                *(uint32_t *)entryListEnd = nEntryInt;  // 有富余容量 → 直写
                entryListEnd = pVecWrite + 4;
              }
              else
              {
                sub_430C80(entryListEnd, 1, (int)&i);  // vector push_back 兜底
              }
              nEntryInt = sub_4423D0(&bTokOk);  // sub_4423D0 —— [LOOP] → 动画对象+160
            }
            miscArg = &areaEntryId;
            sub_4FCF30(&areaEntryId);  // map<id,条目> 取/建槽位（this 经寄存器）
            sub_4FCA80(miscArg);  // 把条目赋值进槽位
          }
        }
        else
        {
          pDungeon[23] = sub_4423D0(nullptr);  // [dungeon what must be cleared] → 对象+0x5C
        }
      }
      else
      {
        miscArg = pDungeon + 15;
        sub_443370();  // [cutscene image] → 对象+0x3C 过场图串
        pDungeon[22] = sub_4423D0(nullptr);  // 随后一个整数 → 对象+0x58
      }
    }
    else
    {
      miscArg = pDungeon + 8;
      sub_443370();  // [entering title] → 对象+0x20 进图标题串
    }
  }
  while ( (uint8_t)sub_443430(&strLine) != 0 );  // sub_443430 —— 读 token 到 string + 国家码标记
  pszFileNameBak = ArgList;
LABEL_43:
  *pDungeon = sub_4A2F80(&dword_9B6D78, pszFileNameBak);  // +0x00 ← 按文件名查全局副本 ID 表（未登记 = -1）
  if ( entryListBegin != nullptr )
    j__free(entryListBegin);  // 析构临时区域条目
  entryListBegin = nullptr;  // entryListBegin = nullptr 空指针
  entryListEnd = nullptr;  // entryListEnd = nullptr 空指针
  entryListCapEnd = 0;
  if ( entryNameCap >= 0x10 )
    j__free(entryNameBuf);  // 释放堆块
  entryNameCap = 15;
  entryNameLen = 0;
  LOBYTE(entryNameBuf) = 0;  // 调 取 16 位值低 8 位
  if ( typeStrCap >= 0x10 )
    j__free(typeStrBuf);  // 释放堆块
  typeStrCap = 15;
  typeStrLen = 0;
  LOBYTE(typeStrBuf) = 0;  // 调 取 16 位值低 8 位
  if ( strLineCap >= 0x10 )
    j__free(strLineBuf[0]);  // 释放堆块
  return 1;
}


// ------------------------------------------------------------
// 0x4FD430 sub_4FD430
//   设定地图脚本根目录（全局 byte_9B6D88，补 '\' 或 '/' 结尾）后加载文件表到
//   unk_9B6E88（sub_443C40）。sub_4FD4C0 地图解析器经 &unk_9B6D88 使用该目录。
// ------------------------------------------------------------
bool /*cdecl*/ sub_4FD430(const char *pArg1, int nArg2)  // 副本(dungeon)定义解析器
{
  strcpy(byte_9B6D88, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B6D87[strlen(byte_9B6D88)] != 92 && byte_9B6D87[strlen(byte_9B6D88)] != 47 )  // 若 byte_9B6D87[strlen(byte_9B6D88)] != 92 && byte_9B6D87[strlen(b..
    *(uint16_t *)&byte_9B6D88[strlen(byte_9B6D88)] = 92;  // 调 求串长
  return (uint8_t)sub_443C40((int)&unk_9B6E88, (char)byte_9B6D88, nArg2) != 0;  // sub_443C40 —— 脚本文件列表装表
}



// ------------------------------------------------------------
// 0x4FD4C0 sub_4FD4C0 —— 地图(map)定义解析器
//   标签族：[name]/[map image]/[dungeon]；未识别标签打印 "SCRIPT TAG ERROR! [%s] %s"
//   （off_77F3FC —— 研究 20 §1.3 所述引擎错误输出口）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FD4C0(int pArg1, const char *ArgList)  // sub_4FD4C0 —— 地图(map)定义解析器
{
  char result; // al
  uint32_t *pMapObj; // esi  地图定义对象（偏移：+0x00 ID/+0x04 名/+0x20 图/+0x3C int/+0x40 vector 对）
  unsigned int nTagLen; // edx
  int nCmpLen; // ecx
  void **pszLineData; // esi  行文本数据指针（容量<0x10 取 SSO 缓冲）
  int nCmp; // eax
  int nPairVal1; // eax  [dungeon] 每对第一个 int
  int nPairVal2; // eax  每对第二个 int
  int pVecBegin; // edx  对象+0x40 vector 起始
  unsigned int nCount; // ecx
  int pEndTmp; // esi
  void **pszLineDataB; // eax
  char v14; // [esp-1Ch] [ebp-64h] BYREF  未知标签检查：行拷贝串头（寄存器传参拆散）
  void **v15; // [esp-18h] [ebp-60h]
  int v16; // [esp-14h] [ebp-5Ch]
  int v17; // [esp-10h] [ebp-58h]
  int v18; // [esp-Ch] [ebp-54h]
  CHAR *v19; // [esp-8h] [ebp-50h]
  unsigned int v20; // [esp-4h] [ebp-4Ch]
  uint32_t entryPair[2]; // [esp+Ch] [ebp-3Ch] BYREF  [dungeon] 读入的 (int,int) 对
  char *pTmpHead; // [esp+14h] [ebp-34h]
  char bTokOk; // [esp+1Bh] [ebp-2Dh] BYREF  token 可解析标志
  uint8_t strLine[4]; // [esp+1Ch] [ebp-2Ch] BYREF  行字符串对象头
  void *strLineBuf[4]; // [esp+20h] [ebp-28h] BYREF
  int strLineLen; // [esp+30h] [ebp-18h]
  unsigned int strLineCap; // [esp+34h] [ebp-14h]
  int dword_796E502; // [esp+38h] [ebp-10h]
  int v29; // [esp+44h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B6D88, (int)ArgList);  // 打开地图定义脚本
  if ( result != 0 )
  {
    pMapObj = (uint32_t *)pArg1;
    v20 = 0;
    v19 = (CHAR *)szPassword;
    *(uint32_t *)pArg1 = 0;
    sub_4015C0(v19, v20);  // 【std::string构造赋值】置空对象+0x04 名称串（this 经寄存器）
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】置空对象+0x20 图串
    *(uint32_t *)(pArg1 + 60) = 0;  // 写字段 pArg1+60（nFadeValue60） ← 0
    if ( *(uint32_t *)(pArg1 + 68) != 0 )  // 若 *(uint32_t *)(pArg1 + 68) != 0
      j__free(*(void **)(pArg1 + 68));  // 释放堆块
    *(uint32_t *)(pArg1 + 68) = 0;   // +0x40 vector 起始
    *(uint32_t *)(pArg1 + 72) = 0;   // 结束
    *(uint32_t *)(pArg1 + 76) = 0;   // 容量尾
    strLineCap = 15;
    strLineLen = 0;
    LOBYTE(strLineBuf[0]) = 0;  // 调 取 16 位值低 8 位
    v29 = 0;
    bTokOk = 0;
    if ( (uint8_t)sub_443430(strLine) != 0 )  // 读第一行
    {
      while ( 1 )  // 当 1 循环
      {
        sub_442B20(strLine);  // sub_442B20 —— 国家码标签配对校验（void）
        nTagLen = strLineLen;
        if ( strLineLen == 0 )
          goto LABEL_15;  // 跳转 LABEL_15
        nCmpLen = strLineLen;
        if ( (unsigned int)strLineLen >= 6 )
          nCmpLen = 6;
        pszLineData = (void **)strLineBuf[0];
        if ( strLineCap < 0x10 )
          pszLineData = strLineBuf;
        nCmp = memcmp((const char *)pszLineData, "[name]", nCmpLen);  // 调 memcmp 内存比较
        if ( nCmp != 0 )
          break;
        if ( (unsigned int)strLineLen < 6 )
          break;
        LOBYTE(nCmp) = strLineLen != 6;  // 调 取 16 位值低 8 位
        if ( nCmp != 0 )
          break;
        v20 = pArg1 + 4;  // 计算 v20 = pArg1 + 4
        sub_443370();  // [name] → 对象+0x04 名称串
LABEL_34:
        if ( (uint8_t)sub_443430(strLine) == 0 )  // 读下一行
        {
          pMapObj = (uint32_t *)pArg1;
          goto LABEL_36;  // 跳转 LABEL_36
        }
      }
      nTagLen = strLineLen;
LABEL_15:
      if ( sub_40BF00((std::_String_base *)strLine, 0, nTagLen, "[map image]", 0xBu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)strLine, 0, strLineLen, "[dungeon]", 9u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          pTmpHead = &v14;
          v20 = 15;
          v19 = nullptr;  // v19 = nullptr 空指针
          LOBYTE(v15) = 0;  // 调 取 16 位值低 8 位
          sub_4014D0((std::_String_base *)&v14, strLine, 0, -1);  // 拷贝整行
          if ( sub_442C80(v14, v15, v16, v17, v18, (int)v19, v20) == 0 )  // 行首是 '[' 仍未匹配
          {
            pszLineDataB = (void **)strLineBuf[0];
            if ( strLineCap < 0x10 )
              pszLineDataB = strLineBuf;
            off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)pszLineDataB);  // off_77F3FC —— 日志打印（printf 风格）
          }
        }
        else
        {
          // [dungeon] → 对象+0x40 vector：逐对读 (int,int) 推入（8 字节/对）
          if ( *(uint32_t *)(pArg1 + 68) != 0 )  // 若 *(uint32_t *)(pArg1 + 68) != 0
            j__free(*(void **)(pArg1 + 68));  // 释放堆块
          v20 = (unsigned int)&bTokOk;
          *(uint32_t *)(pArg1 + 68) = 0;  // 写字段 pArg1+68（nCharCount） ← 0
          *(uint32_t *)(pArg1 + 72) = 0;  // 写字段 pArg1+72（nSnapshot72） ← 0
          *(uint32_t *)(pArg1 + 76) = 0;  // 写字段 pArg1+76（szEmblemPath） ← 0
          for ( nPairVal1 = sub_4423D0((uint8_t *)v20); bTokOk != 0; nPairVal1 = sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
          {
            entryPair[0] = nPairVal1;
            nPairVal2 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
            pVecBegin = *(uint32_t *)(pArg1 + 68);  // 读字段 pVecBegin = pArg1+68（nCharCount）
            entryPair[1] = nPairVal2;
            if ( pVecBegin != 0 )
              nCount = (*(uint32_t *)(pArg1 + 72) - pVecBegin) >> 3;
            else
              nCount = 0;
            if ( pVecBegin != 0 && nCount < (*(uint32_t *)(pArg1 + 76) - pVecBegin) >> 3 )
            {
              pEndTmp = *(uint32_t *)(pArg1 + 72);  // 读字段 pEndTmp = pArg1+72（nSnapshot72）
              v20 = (unsigned int)pTmpHead;
              v19 = (CHAR *)(pArg1 + 64);
              sub_63A7C0(pEndTmp, 1, entryPair);  // 有富余容量 → 直写
              *(uint32_t *)(pArg1 + 72) = pEndTmp + 8;  // 写字段 pArg1+72（nSnapshot72） ← pEndTmp + 8
            }
            else
            {
              sub_473A80(pArg1 + 64, *(uint32_t *)(pArg1 + 72), 1u, (int)entryPair);  // push_back 兜底
            }
          }
        }
      }
      else
      {
        v20 = pArg1 + 32;  // 计算 v20 = pArg1 + 32
        sub_443370();  // [map image] → 对象+0x20 小地图图串
        *(uint32_t *)(pArg1 + 60) = sub_4423D0(nullptr);  // 随后一个整数 → 对象+0x3C
      }
      goto LABEL_34;  // 跳转 LABEL_34
    }
LABEL_36:
    *pMapObj = sub_4A2F80(ArgList);  // +0x00 ← 按文件名查全局 ID 表（未登记 = -1）
    if ( strLineCap >= 0x10 )
      j__free(strLineBuf[0]);  // 释放堆块
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FD770 sub_4FD770
//   设定另一脚本根目录（byte_9B6E98，补 \ 结尾）并经 sub_443C40 探测加载（同 4FC840 的第二份）。
// ------------------------------------------------------------
bool /*cdecl*/ sub_4FD770(const char *pArg1, int nArg2)  // 地图(map)定义解析器
{
  strcpy(byte_9B6E98, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B6E97[strlen(byte_9B6E98)] != 92 && byte_9B6E97[strlen(byte_9B6E98)] != 47 )  // 若 byte_9B6E97[strlen(byte_9B6E98)] != 92 && byte_9B6E97[strlen(b..
    *(uint16_t *)&byte_9B6E98[strlen(byte_9B6E98)] = 92;  // 调 求串长
  return (uint8_t)sub_443C40((int)&unk_9B6F98, (char)byte_9B6E98, nArg2) != 0;  // sub_443C40 —— 脚本文件列表装表
}



// ------------------------------------------------------------
// 0x4FD800 sub_4FD800
//   std::_Tree 节点 _Max()：沿 +8（右子）下行到最右非空节点（+0x65=_Isnil）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4FD800(int pArg1)
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 101) == 0; i = *(uint32_t *)(i + 8) )  // 读字段 i = pArg1+8（nSkillRec8）
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x4FD820 sub_4FD820
//   std::_Tree 节点 _Min()：沿 +0（左子）下行到最左非空节点。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FD820(uint32_t *pArg1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 101) == 0 )  // 若 *(uint8_t *)(*pArg1 + 101) == 0
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 101) == 0 );  // 当 *((uint8_t *)v2 + 101) == 0 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FD840 sub_4FD840
//   std::map 迭代器 _Dec()（本树实例，_Isnil=+0x65）：移动到前驱（右子树最左/沿父上行）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FD840(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 101) != 0 )  // 若 *(uint8_t *)(*(uint32_t *)this + 101) != 0
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 101) != 0 )  // 若 *(uint8_t *)(*v1 + 101) != 0
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 101) == 0 )  // 若 *(uint8_t *)(result + 101) == 0
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )  // 若 *(uint32_t *)this != *(uint32_t *)result
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);  // 读字段 result = result+4（pHostObj）
        }
        while ( *(uint8_t *)(result + 101) == 0 );  // 写字段 result+101（bFired101） ← = 0 )
        if ( *(uint8_t *)(result + 101) == 0 )  // 若 *(uint8_t *)(result + 101) == 0
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 101) == 0; result = *(uint32_t *)(result + 8) )  // 读字段 result = v3+8（nSkillRec8）
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FD8A0 sub_4FD8A0
//   std::map 迭代器 _Inc()：移动到后继（右子树最左，否则沿 +4 父指针上行）。
// ------------------------------------------------------------
int */*thiscall*/ sub_4FD8A0(int *this)  // this+4 宿主对象
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 101) == 0 )  // 若 *(uint8_t *)(*this + 101) == 0
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 101) != 0 )  // 若 *((uint8_t *)v2 + 101) != 0
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 101) == 0; result = (int *)result[1] )  // 循环：result = (int *)result[1]; *((uint8_t *)result + 101) == 0; 
      {
        if ( *this != result[2] )
          break;
        *this = (int)result;  // *this 写入 (int)result
      }
      *this = (int)result;  // *this 写入 (int)result
    }
    else
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 101) == 0 )  // 若 *(uint8_t *)(*v2 + 101) == 0
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 101) == 0 );  // 当 *((uint8_t *)result + 101) == 0 循环
      }
      *this = (int)v2;  // *this 写入 (int)v2
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FD900 sub_4FD900
//   std::_Tree 旋转子例程之一（绕 pArg2 转动其 +8 孩子，维护 +4 父指针与根回接）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FD900(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;  // 写字段 pArg2+8（nSkillRec8） ← *result
  if ( *(uint8_t *)(*result + 101) == 0 )  // 若 *(uint8_t *)(*result + 101) == 0
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);  // result[1] 写入 *(uint32_t *)(pArg2 + 4)
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )  // 若 pArg2 == *(uint32_t *)(fld_e1 + 4)
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // 写字段 fld_e1+4（pHostObj） ← result
    *result = pArg2;  // *result 写入 pArg2
    *(uint32_t *)(pArg2 + 4) = result;  // 写字段 pArg2+4（pHostObj） ← result
  }
  else
  {
    v4 = *(uint32_t **)(pArg2 + 4);
    if ( pArg2 == *v4 )  // 若 pArg2 == *v4
      *v4 = result;  // *v4 写入 result
    else
      v4[2] = result;
    *result = pArg2;  // *result 写入 pArg2
    *(uint32_t *)(pArg2 + 4) = result;  // 写字段 pArg2+4（pHostObj） ← result
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FD960 sub_4FD960
//   std::_Tree 旋转子例程之二（与 4FD900 镜像，绕 pArg2 转动另一侧孩子）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FD960(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);  // *pArg2 写入 *(uint32_t *)(*pArg2 + 8)
  v3 = *(uint32_t *)(result + 8);  // 读字段 v3 = result+8（nSkillRec8）
  if ( *(uint8_t *)(v3 + 101) == 0 )  // 若 *(uint8_t *)(v3 + 101) == 0
    *(uint32_t *)(v3 + 4) = pArg2;  // 写字段 v3+4（pHostObj） ← pArg2
  *(uint32_t *)(result + 4) = pArg2[1];  // 写字段 result+4（pHostObj） ← pArg2[1]
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )  // 若 pArg2 == *(uint32_t **)(fld_e1 + 4)
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // 写字段 fld_e1+4（pHostObj） ← result
    *(uint32_t *)(result + 8) = pArg2;  // 写字段 result+8（nSkillRec8） ← pArg2
    pArg2[1] = result;
  }
  else
  {
    v5 = (uint32_t *)pArg2[1];
    if ( pArg2 == (uint32_t *)v5[2] )  // 若 pArg2 == (uint32_t *)v5[2]
      v5[2] = result;
    else
      *v5 = result;  // *v5 写入 result
    *(uint32_t *)(result + 8) = pArg2;  // 写字段 result+8（nSkillRec8） ← pArg2
    pArg2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FD9C0 sub_4FD9C0
//   递归深度释放节点链（+0x15 为哨兵标志；先释放 i[2] 分支再沿 *i 前进）。
// ------------------------------------------------------------
char /*stdcall*/ sub_4FD9C0(void **Block)  // 函数: 释放后返回
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);  // 读字段 result = Block+21（bArmorState）
  for ( i = Block; result == 0; Block2 = i )  // 循环：i = Block; result == 0; Block2 = i
  {
    sub_4FD9C0(i[2]);  // 调 sub_4FD9C0
    i = (void **)*i;
    j__free(Block2);  // 释放堆块
    result = *((uint8_t *)i + 21);  // 读字段 result = i+21（bArmorState）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FDA00 sub_4FDA00
//   NPC 对话/语音条目值类型清空：释放 +72 vector（三指针），再析构 +16 与 +44
//   两处 std::string（容量 ≥0x10 时释放堆缓冲并复位 SSO）。
//   NPC 定义解析器 sub_4FE240 析构临时条目时调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_4FDA00(int this)  // sub_4FDA00 —— 转调 sub_4FDA00（传 this+16 子对象）
{
  if ( *(uint32_t *)(this + 72) != 0 )  // 若 *(uint32_t *)(this + 72) != 0
    j__free(*(void **)(this + 72));  // 释放堆块
  *(uint32_t *)(this + 72) = 0;  // 写字段 this+72（nSnapshot72） ← 0
  *(uint32_t *)(this + 76) = 0;  // 写字段 this+76（szEmblemPath） ← 0
  *(uint32_t *)(this + 80) = 0;  // 写字段 this+80（nAuraStage） ← 0
  if ( *(uint32_t *)(this + 64) >= 0x10u )  // 若 *(uint32_t *)(this + 64) >= 0x10u
    j__free(*(void **)(this + 44));  // 释放堆块
  *(uint32_t *)(this + 64) = 15;  // 写字段 this+64（apServerTabBtn） ← 15
  *(uint32_t *)(this + 60) = 0;  // 写字段 this+60（nFadeValue60） ← 0
  *(uint8_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  if ( *(uint32_t *)(this + 36) >= 0x10u )  // 若 *(uint32_t *)(this + 36) >= 0x10u
    j__free(*(void **)(this + 16));  // 释放堆块
  *(uint32_t *)(this + 32) = 0;  // 写字段 this+32（nHeight） ← 0
  *(uint32_t *)(this + 36) = 15;  // 写字段 this+36（nStateWord36） ← 15
  *(uint8_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
}



// ------------------------------------------------------------
// 0x4FDA60 sub_4FDA60
//   值类型析构包装：对 this+4 转调 sub_4FDA00（map 节点里值部分从 +4 起）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4FDA60(void *this)  // 函数: 转发 ·sub_4FDA00
{
  sub_4FDA00((int)this + 4);  // sub_4FDA00 —— 转调 sub_4FDA00（传 this+16 子对象）
}



// ------------------------------------------------------------
// 0x4FDA80 sub_4FDA80
//   std::map::insert 本体（NPC 对话树，红黑标志 @节点+0x14）：sub_5648C0 堆上建值
//   → 挂树（左/右孩子挂接）→ 回平衡（sub_433130 / sub_4296E0 = 双向旋转），返回新节点。
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

  if ( *(this + 2) >= 0x1FFFFFFEu )  // 若 *(this + 2) >= 0x1FFFFFFEu
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);  // sub_5648C0 —— 商店文本（23 行）
  fld_e12 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8 = 技能槽记录首字
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4 = pHostObj
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;  // *pArg4 写入 fld_e1
    fld_e13 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
    if ( pArg4 == (uint32_t *)*fld_e13 )  // 若 pArg4 == (uint32_t *)*fld_e13
      *fld_e13 = fld_e1;  // *fld_e13 写入 fld_e1
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // 若 pArg4 == *(uint32_t **)(fld_e14 + 8)
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
  }
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0 )  // 若 *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0
  {
    while ( 1 )  // 当 1 循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )  // 若 *v10 == *v13
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 20) != 0 )  // 若 *(uint8_t *)(v14 + 20) != 0
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_433130(*v10);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_4296E0 —— STL 内联红黑树节点摘除重连
          goto LABEL_21;  // 跳转 LABEL_21
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )  // 否则若 *(uint8_t *)(v14 + 20) != 0
      {
        if ( fld_e16 == *v12 )  // 若 fld_e16 == *v12
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_433130 —— 红黑树左旋（节点 0x18 版）
        goto LABEL_21;  // 跳转 LABEL_21
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;  // 写字段 v14+20（nPage） ← 1
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )  // 若 *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;  // this+4 = pHostObj
  *uArg2 = fld_e1;  // *uArg2 写入 fld_e1
  return uArg2;
}


// ------------------------------------------------------------
// 0x4FDC30 sub_4FDC30
//   std::map::insert(unique) 前半（NPC 对话树，_Isnil @节点+0x15）：按 key
//   （节点+0x0C 的整数）下行查找；已存在 → {已有节点,false}；否则转 sub_4FDA80 插入。
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
  fld_e1 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  v6 = (int *)fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )  // 若 *((uint8_t *)v6 + 21) == 0
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
    while ( *((uint8_t *)v6 + 21) == 0 );  // 当 *((uint8_t *)v6 + 21) == 0 循环
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )  // 若 v7
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // 若 fld_e1 == *(uint32_t **)*(this + 1)
    {
      v10 = *sub_4FDA80(this, &uArg3, 1, fld_e1, (int)uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&uArg3);  // 调 sub_4A3B30
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )  // 若 fld_e12[3] >= *uArg32
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_4FDA80(this, &uArg3, v13, fld_e1, (int)uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4FDCF0 sub_4FDCF0
//   std::map::insert(hint)（NPC 对话树）：先用提示迭代器与前后邻居比较定位插入点，
//   邻居检查失败则回退 sub_4FDC30 重查（LABEL_22）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FDCF0(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)  // 函数定义: 插入后返回新值槽
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // 若 *(uint32_t *)(this + 8) == 0
  {
    sub_4FDA80((uint32_t *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);  // 调 sub_4FDA80
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+4 宿主对象
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )  // 若 pArg3 == (uint32_t *)*fld_4
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4FDA80((uint32_t *)this, uArg2, 1, pArg3, (int)pArg4);  // 调 sub_4FDA80
      return uArg2;
    }
    goto LABEL_22;  // 跳转 LABEL_22
  }
  if ( pArg3 == fld_4 )  // fld_4=this+4 宿主对象
  {
    v8 = (uint32_t *)fld_4[2];  // fld_4=this+4 宿主对象
    if ( v8[3] < *pArg4 )  // 若 v8[3] < *pArg4
    {
      sub_4FDA80((uint32_t *)this, uArg2, 0, v8, (int)pArg4);  // 调 sub_4FDA80
      return uArg2;
    }
    goto LABEL_22;  // 跳转 LABEL_22
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4A3B30(&pArg4), pArg4[3] >= *pArg42) )  // 调 取后继再插
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C5E0(&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4FDC30((uint32_t *)this, (int)v10, pArg42);
      *uArg2 = v9;  // *uArg2 写入 v9
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 21) != 0 )  // 若 *(uint8_t *)(pArg3[2] + 21) != 0
      sub_4FDA80((uint32_t *)this, uArg2, 0, pArg3, (int)pArg42);  // 调 sub_4FDA80
    else
      sub_4FDA80((uint32_t *)this, uArg2, 1, pArg4, (int)pArg42);  // 调 sub_4FDA80
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 21) != 0 )  // 若 *(uint8_t *)(pArg4[2] + 21) != 0
      sub_4FDA80((uint32_t *)this, uArg2, 0, pArg4, (int)pArg42);  // 调 sub_4FDA80
    else
      sub_4FDA80((uint32_t *)this, uArg2, 1, pArg3, (int)pArg42);  // 调 sub_4FDA80
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4FDE50 sub_4FDE50
//   递归释放整棵 NPC 对话树（_Isnil @+0x65）：先递归右子树，再析构节点值
//   （sub_4FDA70）并 free 节点本体。
// ------------------------------------------------------------
char /*stdcall*/ sub_4FDE50(void **Block)  // 函数: 释放后返回
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 101);  // 读字段 result = Block+101（bFired101）
  for ( i = Block; result == 0; Block2 = i )  // 循环：i = Block; result == 0; Block2 = i
  {
    sub_4FDE50(i[2]);  // 调 sub_4FDE50
    i = (void **)*i;
    sub_4FDA70(Block2);  // 调 sub_4FDA70
    j__free(Block2);  // 释放堆块
    result = *((uint8_t *)i + 101);  // 读字段 result = i+101（bFired101）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FDEA0 sub_4FDEA0
//   NPC 对话条目值类型拷贝构造：+0x00..+0x08 三整数逐个拷贝，+0x10 与 +0x2C
//   两处 std::string 深拷贝（sub_4014D0），+0x44 处成员经 sub_435020 拷贝。
//   sub_4FE240 建树节点时调用。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FDEA0(uint32_t *this, uint32_t *pArg2)
{
  char *pThis_3; // ecx

  *this = *pArg2;  // *this 写入 *pArg2
  *(this + 1) = pArg2[1];  // 写字段 this+1 ← pArg2[1]
  pThis_3 = (char *)(this + 3);  // this+12 = 技能槽记录次字
  *(this + 2) = pArg2[2];  // 写字段 this+2 ← pArg2[2]
  *((uint32_t *)pThis_3 + 6) = 15;  // 写字段 pThis_3[6]（宽4字节）
  *((uint32_t *)pThis_3 + 5) = 0;  // 写字段 pThis_3[5]（宽4字节）
  pThis_3[4] = 0;
  sub_4014D0((std::_String_base *)pThis_3, pArg2 + 3, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(this + 16) = 15;  // 写字段 this+16（nChannelTypeSel） ← 15
  *(this + 15) = 0;  // 写字段 this+15 ← 0
  *((uint8_t *)this + 44) = 0;  // 写字段 this+44（nExpireMs）
  sub_4014D0((std::_String_base *)(this + 10), pArg2 + 10, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  sub_435020(pArg2 + 17);  // sub_435020 —— uint32 向量整体赋值
  return this;
}



// ------------------------------------------------------------
// 0x4FDF40 sub_4FDF40
//   NPC 对话条目值类型默认构造：+0x00..+0x08 三整数清零，+0x10 与 +0x2C 两处
//   std::string 空串初始化，+0x48 vector 清零并释放旧缓冲。
// ------------------------------------------------------------
char */*thiscall*/ sub_4FDF40(char *this)
{
  char *pThis_C; // ecx

  pThis_C = this + 12;  // this+12 物品类型号
  *((uint32_t *)pThis_C + 6) = 15;  // 写字段 pThis_C[6]（宽4字节）
  *((uint32_t *)pThis_C + 5) = 0;  // 写字段 pThis_C[5]（宽4字节）
  pThis_C[4] = 0;  // pThis_C=this+12 物品类型号
  *((uint32_t *)this + 16) = 15;  // 写字段 this+16（nChannelTypeSel）
  *((uint32_t *)this + 15) = 0;  // 写字段 this[15]（宽4字节）
  *(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  *((uint32_t *)this + 18) = 0;  // 写字段 this+18（bDragChild）
  *((uint32_t *)this + 19) = 0;  // 写字段 this[19]（宽4字节）
  *((uint32_t *)this + 20) = 0;  // 写字段 this+20（nPage）
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 0;  // 写字段 this[1]（宽4字节）
  *((uint32_t *)this + 2) = 0;  // 写字段 this[2]（宽4字节）
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  if ( *((uint32_t *)this + 18) != 0 )  // 若 *((uint32_t *)this + 18) != 0
    j__free(*((void **)this + 18));  // 释放堆块
  *((uint32_t *)this + 18) = 0;  // 写字段 this+18（bDragChild）
  *((uint32_t *)this + 19) = 0;  // 写字段 this[19]（宽4字节）
  *((uint32_t *)this + 20) = 0;  // 写字段 this+20（nPage）
  return this;
}



// ------------------------------------------------------------
// 0x4FDFE0 sub_4FDFE0
//   NPC 对话条目值类型拷贝赋值：+0x00..+0x08 三整数、+0x0C 与 +0x28 两字符串
//   （sub_4014D0 深拷贝）、+0x44 链表（sub_4ED3F0 深拷贝）逐域复制。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FDFE0(uint32_t *this, uint32_t *pArg2)
{
  *this = *pArg2;  // *this 写入 *pArg2
  *(this + 1) = pArg2[1];  // 写字段 this+1 ← pArg2[1]
  *(this + 2) = pArg2[2];  // 写字段 this+2 ← pArg2[2]
  sub_4014D0((std::_String_base *)(this + 3), pArg2 + 3, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  sub_4014D0((std::_String_base *)(this + 10), pArg2 + 10, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  sub_4ED3F0((int)(this + 17), (int)(pArg2 + 17));  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
  return this;
}



// ------------------------------------------------------------
// 0x4FE030 sub_4FE030
//   map<职能id, 条目>::operator[]（NPC 定义解析器按枚举建条目用）：树中找到 →
//   返回值指针；没有 → 栈上配好 {key,0} 经 sub_4FDCF0 插入后返回新值槽。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FE030(uint32_t *this, uint32_t *uArg2)  // sub_4FE030 —— 建职能条目（枚举）并返回值槽
{
  uint32_t *fld_e1; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  v3 = (int *)fld_e1[1];
  while ( *((uint8_t *)v3 + 21) == 0 )  // 当 *((uint8_t *)v3 + 21) == 0 循环
  {
    if ( v3[3] >= *uArg2 )  // 若 v3[3] >= *uArg2
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
  v5[0] = *uArg2;  // v5[0] 写入 *uArg2
  v5[1] = 0;
  return *sub_4FDCF0((int)this, &uArg2, fld_e1, v5) + 16;  // 调 插入后返回新值槽
}



// ------------------------------------------------------------
// 0x4FE0B0 sub_4FE0B0
//   NPC 定义对象重置（sub_4FE550 NPC 解析器开头调用）：全部内嵌 std::string 置空、
//   +268 标志字节 =1（默认开）、+280/+400 两棵 map 树整树释放（4FD9C0/4FDE50 逐节点）、
//   +320 起 5 个 16 字节容器清空、+272 哨兵 = -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FE0B0(uint32_t *this)  // sub_4FE0B0 —— 重置 NPC 定义对象
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

  *this = 0;  // *this 写入 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 22) = 0;  // 写字段 this+22 ← 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 30) = 0;  // 写字段 this+30 ← 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 38) = 0;  // 写字段 this+38（bFadeFlag38） ← 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_35 = (char *)(this + 53);
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pThis_35 += 28;
  }
  *((uint8_t *)this + 268) = 1;  // 写字段 this[268]（宽1字节）
  fld_e70 = *(uint32_t **)(*(this + 70) + 4);
  for ( Block = fld_e70; *((uint8_t *)fld_e70 + 21) == 0; Block = fld_e70 )  // 循环：Block = fld_e70; *((uint8_t *)fld_e70 + 21) == 0; Block = fl
  {
    sub_4FD9C0((void **)fld_e70[2]);  // 调 sub_4FD9C0
    fld_e70 = (uint32_t *)*fld_e70;
    j__free(Block);  // 释放堆块
  }
  *(uint32_t *)(*(this + 70) + 4) = *(this + 70);
  fld_e702 = (uint32_t *)*(this + 70);
  *(this + 71) = 0;  // 写字段 this+71（bMoveType） ← 0
  *fld_e702 = fld_e702;  // *fld_e702 写入 fld_e702
  *(uint32_t *)(*(this + 70) + 8) = *(this + 70);
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_50 = (char *)(this + 80);  // this+80 关联角色对象
  for ( Blocka = 5; Blocka != 0; --Blocka )  // 遍历计次循环（Blocka != 0）
  {
    if ( *(uint32_t *)pThis_50 != 0 )  // pThis_50=this+80 关联角色对象
      j__free(*(void **)pThis_50);  // 释放堆块
    *(uint32_t *)pThis_50 = 0;  // pThis_50=this+80 关联角色对象
    *((uint32_t *)pThis_50 + 1) = 0;  // 写字段 pThis_50[1]（宽4字节）
    *((uint32_t *)pThis_50 + 2) = 0;  // 写字段 pThis_50[2]（宽4字节）
    pThis_50 += 16;  // pThis_50=this+80 关联角色对象
  }
  sub_4FDE50(*(void ***)(*(this + 100) + 4));  // 调 sub_4FDE50
  *(uint32_t *)(*(this + 100) + 4) = *(this + 100);  // this+100 插值终点 Y
  fld_e100 = (uint32_t *)*(this + 100);  // this+100 插值终点 Y
  *(this + 101) = 0;  // 写字段 this+101（bFired101） ← 0
  *fld_e100 = fld_e100;  // *fld_e100 写入 fld_e100
  *(uint32_t *)(*(this + 100) + 8) = *(this + 100);  // this+100 插值终点 Y
  result = sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 68) = -1;  // 写字段 this+68（nCharCount） ← -1
  return result;
}



// ------------------------------------------------------------
// 0x4FE240 sub_4FE240
//   std::map 树节点堆构造（0x68 字节）：前 3 个整数 + 值（sub_4FDEA0 拷贝构造），
//   +100 = 红黑标志字节 pszArg5（恒 0），供 4FE2E0 插入用。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4FE240(int nArg1, int nArg2, int nArg3, uint32_t *pArg4, char pszArg5)  // 函数定义: 析构临时条目时调用
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  pMem = operator new(0x68u);  // 堆分配
  pMem2 = pMem;
  v8[4] = pMem;
  v8[8] = (void *)1;  // v8[8] 写入 (void *)1
  v8[3] = pMem;
  if ( pMem != nullptr )
  {
    *pMem = nArg1;  // *pMem 写入 nArg1
    pMem[1] = nArg2;
    pMem[2] = nArg3;
    pMem[3] = *pArg4;  // pMem[3] 写入 *pArg4
    sub_4FDEA0(pMem + 4, pArg4 + 1);  // 调 sub_4FDEA0
    *((uint8_t *)pMem2 + 100) = pszArg5;  // 写字段 pMem2+100（bEnchantDone）
    *((uint8_t *)pMem2 + 101) = 0;  // 写字段 pMem2+101（bFired101）
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x4FE2E0 sub_4FE2E0
//   std::map::insert 本体（第三棵树实例，红黑标志 @节点+0x64）：sub_4FE240 建节点
//   → 挂树 → 回平衡（sub_4FD960 / sub_4FD900 = 双向旋转），返回新节点。
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

  if ( *(this + 2) >= 0x2E8BA2Du )  // 若 *(this + 2) >= 0x2E8BA2Du
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_4FE240(*(this + 1), pArg4, *(this + 1), nArg5, 0);  // 调 sub_4FE240
  fld_e12 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8 = 技能槽记录首字
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4 = pHostObj
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;  // *pArg4 写入 fld_e1
    fld_e13 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
    if ( pArg4 == (uint32_t *)*fld_e13 )  // 若 pArg4 == (uint32_t *)*fld_e13
      *fld_e13 = fld_e1;  // *fld_e13 写入 fld_e1
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // 若 pArg4 == *(uint32_t **)(fld_e14 + 8)
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
  }
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 100) == 0 )  // 若 *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 100) == 0
  {
    while ( 1 )  // 当 1 循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )  // 若 *v10 == *v13
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 100) != 0 )  // 若 *(uint8_t *)(v14 + 100) != 0
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_4FD900(*v10);  // 调 sub_4FD900
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 100) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 100) = 0;
          sub_4FD960(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 调 sub_4FD960
          goto LABEL_21;  // 跳转 LABEL_21
        }
      }
      else if ( *(uint8_t *)(v14 + 100) != 0 )  // 否则若 *(uint8_t *)(v14 + 100) != 0
      {
        if ( fld_e16 == *v12 )  // 若 fld_e16 == *v12
        {
          fld_e16 = *v10;
          sub_4FD960(*v10);  // 调 sub_4FD960
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 100) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 100) = 0;
        sub_4FD900(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 调 sub_4FD900
        goto LABEL_21;  // 跳转 LABEL_21
      }
      *(uint8_t *)(*v10 + 100) = 1;
      *(uint8_t *)(v14 + 100) = 1;  // 写字段 v14+100（bEnchantDone） ← 1
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 100) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 100) != 0 )  // 若 *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 100) != 0
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 100) = 1;  // this+4 = pHostObj
  *uArg2 = fld_e1;  // *uArg2 写入 fld_e1
  return uArg2;
}


// ------------------------------------------------------------
// 0x4FE490 sub_4FE490
//   std::map::insert(unique)（第三棵树，_Isnil @+0x65）：按 key（节点+0x0C）下行
//   查找；已存在 → {已有节点,false}；否则转 sub_4FE2E0 插入。
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
  fld_e1 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  v6 = (int *)fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 101) == 0 )  // 若 *((uint8_t *)v6 + 101) == 0
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
    while ( *((uint8_t *)v6 + 101) == 0 );  // 当 *((uint8_t *)v6 + 101) == 0 循环
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )  // 若 v7
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // 若 fld_e1 == *(uint32_t **)*(this + 1)
    {
      v10 = *sub_4FE2E0(this, &uArg3, 1, fld_e1, uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4FD840(&uArg3);  // 调 sub_4FD840
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )  // 若 fld_e12[3] >= *uArg32
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_4FE2E0(this, &uArg3, v13, fld_e1, uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4FE550 sub_4FE550
//   std::map::insert(hint)（第三棵树）：先用提示迭代器与前后邻居比较定位插入点，
//   邻居检查失败则回退 sub_4FE490 重查（LABEL_22）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FE550(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // 若 *(uint32_t *)(this + 8) == 0
  {
    sub_4FE2E0((int *)this, uArg2, 1, *(uint32_t **)(this + 4), pArg4);  // 调 sub_4FE2E0
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+4 宿主对象
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )  // 若 pArg3 == (uint32_t *)*fld_4
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4FE2E0((int *)this, uArg2, 1, pArg3, pArg4);  // 调 sub_4FE2E0
      return uArg2;
    }
    goto LABEL_22;  // 跳转 LABEL_22
  }
  if ( pArg3 == fld_4 )  // fld_4=this+4 宿主对象
  {
    v8 = (uint32_t *)fld_4[2];  // fld_4=this+4 宿主对象
    if ( v8[3] < *pArg4 )  // 若 v8[3] < *pArg4
    {
      sub_4FE2E0((int *)this, uArg2, 0, v8, pArg4);  // 调 sub_4FE2E0
      return uArg2;
    }
    goto LABEL_22;  // 跳转 LABEL_22
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4FD840(&pArg4), pArg4[3] >= *pArg42) )
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_4FD8A0((int *)&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )  // this+4 宿主对象
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4FE490((int *)this, (int)v10, pArg42);
      *uArg2 = v9;  // *uArg2 写入 v9
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 101) != 0 )  // 若 *(uint8_t *)(pArg3[2] + 101) != 0
      sub_4FE2E0((int *)this, uArg2, 0, pArg3, pArg42);  // 调 sub_4FE2E0
    else
      sub_4FE2E0((int *)this, uArg2, 1, pArg4, pArg42);  // 调 sub_4FE2E0
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 101) != 0 )  // 若 *(uint8_t *)(pArg4[2] + 101) != 0
      sub_4FE2E0((int *)this, uArg2, 0, pArg4, pArg42);  // 调 sub_4FE2E0
    else
      sub_4FE2E0((int *)this, uArg2, 1, pArg3, pArg42);  // 调 sub_4FE2E0
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4FE6B0 sub_4FE6B0
//   map<职能id, 对话条目>::operator[]（NPC 解析器 [role]/[speech] 用）：树中找到 →
//   返回值指针；没有 → 栈上默认构造条目（4FDF40→4FDEA0 拷贝）插入后返回（再析构临时）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FE6B0(uint32_t *this, int *pDwArg2)  // sub_4FE6B0 —— 拷入台词列表
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
  fld_e1 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  v5 = (int *)fld_e1[1];
  fld_e12 = fld_e1;
  while ( *((uint8_t *)v5 + 101) == 0 )  // 当 *((uint8_t *)v5 + 101) == 0 循环
  {
    if ( v5[3] >= *pDwArg2 )  // 若 v5[3] >= *pDwArg2
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
    v7 = sub_4FDF40(v9);  // 调 sub_4FDF40
    v10 = *pDwArg22;
    v12 = 0;
    sub_4FDEA0(v11, v7);  // 调 sub_4FDEA0
    LOBYTE(v12) = 1;  // 调 取 16 位值低 8 位
    fld_e12 = (uint32_t *)*sub_4FE550((int)this, &pDwArg2, fld_e12, &v10);
    sub_4FDA00((int)v11);  // sub_4FDA00 —— 转调 sub_4FDA00（传 this+16 子对象）
    sub_4FDA00((int)v9);  // sub_4FDA00 —— 转调 sub_4FDA00（传 this+16 子对象）
  }
  return fld_e12 + 4;  // 返回内嵌子对象/缓冲指针（fld_e12+4）
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
char /*cdecl*/ sub_4FE770(int pArg1, const char *ArgList)  // sub_4FE770 —— NPC(场地角色)定义解析器
{
  char result; // al
  int pNpc; // edi  NPC 定义对象（偏移：+0x00 ID/+0x04 名/+0x20 场景名/+0x3C 小头像/+0x5C 大头像/
             //        +0x7C 弹出头/+0x9C 场景动画/+0xB8 场景音/+0xD4 弹出音/+0x10C 环顾/+0x110 队伍/
             //        +0x120 任务台词/+0x13C 起按职业技能表/+0x18C 台词列表/+0x198 完整路径）
  int nCmpLen; // ecx
  void **pszLineData; // esi  行文本数据指针（容量<0x10 取 SSO 缓冲）
  int nCmp; // eax
  int *pRoleValSlot; // esi  sub_4FE030 建条目后返回的值槽
  int nRoleVal; // eax  职能条目附加值
  int nJobIdx; // eax  职业/通用 索引
  void *pszJobTag; // eax  职业标签数据指针
  void **pJobSkillList; // esi  该职业的技能 id vector（对象+0x13C+16*职业）
  void **pszLineDataB; // eax
  void **tmpTagBuf[2]; // [esp-1Ch] [ebp-CCh] BYREF  未知标签检查：行拷贝（寄存器传参拆散）
  char *v14; // [esp-14h] [ebp-C4h]
  char *v15; // [esp-10h] [ebp-C0h]
  int v16; // [esp-Ch] [ebp-BCh]
  uint8_t *v17; // [esp-8h] [ebp-B8h]
  int *pDestStr; // [esp-4h] [ebp-B4h]  目标串槽位（this 经寄存器传给 sub_443370/443300 等）
  int tmpInt; // [esp+Ch] [ebp-A4h] BYREF  职能枚举/技能 id/台词列表值
  char bTokOk; // [esp+13h] [ebp-9Dh] BYREF  token 可解析标志
  int speechEntry[3]; // [esp+14h] [ebp-9Ch] BYREF  台词条目基址：+0x00 起 3 个整数
  char speechStr1Head; // [esp+20h] [ebp-90h] BYREF  台词条目 +0x0C 字符串
  char speechStr2Head; // [esp+3Ch] [ebp-74h] BYREF  台词条目 +0x28 字符串
  void *speechIdList[4]; // [esp+58h] [ebp-58h] BYREF  台词条目 +0x44 vector<int>
  uint8_t tagStr[4]; // [esp+68h] [ebp-48h] BYREF  职业/队伍标签字符串对象头
  void *tagStrBuf; // [esp+6Ch] [ebp-44h] BYREF
  int tagStrLen; // [esp+7Ch] [ebp-34h]
  unsigned int tagStrCap; // [esp+80h] [ebp-30h]
  int strLine; // [esp+84h] [ebp-2Ch] BYREF  行字符串对象头
  void *strLineBuf[4]; // [esp+88h] [ebp-28h] BYREF
  int strLineLen; // [esp+98h] [ebp-18h]
  unsigned int strLineCap; // [esp+9Ch] [ebp-14h]
  int dword_796E502; // [esp+A0h] [ebp-10h]
  int v34; // [esp+ACh] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B6E98, (int)ArgList);  // 打开 NPC 定义脚本
  if ( result != 0 )
  {
    pNpc = pArg1;
    sub_4FE0B0(pArg1);  // 重置 NPC 定义对象
    pDestStr = (int *)ArgList;
    sub_443300(pArg1 + 408, "%s%s", (char)&unk_9B6E98);  // +0x198 ← 根目录+文件名完整路径
    strLineCap = 15;
    strLineLen = 0;
    LOBYTE(strLineBuf[0]) = 0;  // 调 取 16 位值低 8 位
    v34 = 1;
    tagStrCap = 15;
    tagStrLen = 0;
    LOBYTE(tagStrBuf) = 0;  // 调 取 16 位值低 8 位
    bTokOk = 0;
    if ( (uint8_t)sub_443430(&strLine) != 0 )  // 读第一行
    {
      while ( 1 )  // 当 1 循环
      {
        sub_442B20(&strLine);  // sub_442B20 —— 国家码标签配对校验（void）
        if ( strLineLen == 0 )
          goto LABEL_13;  // 跳转 LABEL_13
        nCmpLen = strLineLen;
        if ( (unsigned int)strLineLen >= 6 )
          nCmpLen = 6;
        pszLineData = (void **)strLineBuf[0];
        if ( strLineCap < 0x10 )
          pszLineData = strLineBuf;
        nCmp = memcmp((const char *)pszLineData, "[name]", nCmpLen);  // 调 memcmp 内存比较
        if ( nCmp != 0 )
          break;
        if ( (unsigned int)strLineLen < 6 )
          break;
        LOBYTE(nCmp) = strLineLen != 6;  // 调 取 16 位值低 8 位
        if ( nCmp != 0 )
          break;
        pNpc = pArg1;
        pDestStr = (int *)(pArg1 + 4);
        sub_443370();  // [name] → 对象+0x04
LABEL_77:
        if ( (uint8_t)sub_443430(&strLine) == 0 )  // 读下一行
          goto LABEL_78;  // 跳转 LABEL_78
      }
      pNpc = pArg1;
LABEL_13:
      if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[field name]", 0xCu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[small face]", 0xCu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[big face]", 0xAu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[popup face]", 0xCu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[field animation]", 0x11u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
              {
                if ( (uint8_t)sub_423300(&strLine, "[field wav]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDestStr = (int *)(pNpc + 184);
                  sub_443370();  // [field wav] → 对象+0xB8
                }
                else if ( (uint8_t)sub_423300(&strLine, "[popup wav]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDestStr = (int *)(pNpc + 212);
                  sub_443370();  // [popup wav] → 对象+0xD4
                  v17 = (uint8_t *)(pNpc + 240);
                  sub_443370();  // 随后一个字符串 → 对象+0xF0
                }
                else if ( (uint8_t)sub_423300(&strLine, "[look around]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pNpc + 268) = sub_4423D0(nullptr) != 0;  // [look around] → 对象+0x10C 布尔
                }
                else if ( (uint8_t)sub_423300(&strLine, "[role]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  // [role]：逐个读职能标签映射为枚举（0-8），sub_4FE030 建条目并写入附加值
                  for ( pDestStr = (int *)tagStr; sub_443370() != 0; *pRoleValSlot = nRoleVal )  // sub_443370 —— [name] → 对象+0x04 名称串
                  {
                    tmpInt = 0;
                    if ( (uint8_t)sub_423300(tagStr, "[item shop]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      tmpInt = 0;
                    }
                    else if ( (uint8_t)sub_423300(tagStr, "[recover stamina]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      tmpInt = 1;
                    }
                    else if ( (uint8_t)sub_423300(tagStr, "[sera shop]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      tmpInt = 2;
                    }
                    else if ( (uint8_t)sub_423300(tagStr, "[guild]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      tmpInt = 3;
                    }
                    else if ( (uint8_t)sub_423300(tagStr, "[upgrade item]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      tmpInt = 4;
                    }
                    else if ( (uint8_t)sub_423300(tagStr, "[disjoint item]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      tmpInt = 5;
                    }
                    else if ( (uint8_t)sub_423300(tagStr, "[product item]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      tmpInt = 6;
                    }
                    else if ( (uint8_t)sub_423300(tagStr, "[item storage]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      tmpInt = 7;
                    }
                    else if ( (uint8_t)sub_423300(tagStr, "[post box]") != 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      tmpInt = 8;
                    }
                    pRoleValSlot = (int *)sub_4FE030(&tmpInt);  // 建职能条目（枚举）并返回值槽
                    nRoleVal = sub_4423D0(nullptr);  // 随后一个整数（条目参数）
                    v17 = tagStr;
                  }
                }
                else if ( (uint8_t)sub_423300(&strLine, "[quest speech]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDestStr = (int *)(pNpc + 288);
                  sub_443370();  // [quest speech] → 对象+0x120
                }
                else if ( (uint8_t)sub_423300(&strLine, "[skill]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  // [skill]：职业标签（[common]=4 或经 sub_4426A0 查表）→ 清空该职业技能表后逐个推入
                  pDestStr = (int *)tagStr;
                  sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                  if ( (uint8_t)sub_423300(tagStr, "[common]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    nJobIdx = 4;  // [common] = 通用技能组
                  }
                  else
                  {
                    pszJobTag = tagStrBuf;
                    if ( tagStrCap < 0x10 )
                      pszJobTag = &tagStrBuf;
                    nJobIdx = sub_4426A0(pszJobTag);  // 【职业标签→索引（[swordman]/[fighter]/[gunner]/[mag…】
                  }
                  pJobSkillList = (void **)(16 * nJobIdx + pNpc + 316);
                  sub_5E5260(pJobSkillList);  // 清空该职业槽
                  for ( tmpInt = sub_4423D0(&bTokOk); bTokOk != 0; tmpInt = sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_431230((int)pJobSkillList, &tmpInt);  // 逐个 push_back 技能 id
                }
                else if ( (uint8_t)sub_423300(&strLine, "[speech]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  // [speech]：条目 {3 整数, 2 字符串, 整数 vector}，填完推入对象+0x18C 列表
                  sub_4FDF40((char *)speechEntry);  // 调 sub_4FDF40
                  LOBYTE(v34) = 2;  // 调 取 16 位值低 8 位
                  speechEntry[0] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  speechEntry[1] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  speechEntry[2] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  v15 = &speechStr1Head;
                  sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                  v14 = &speechStr2Head;
                  sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                  sub_5E5260(speechIdList);  // 调 sub_5E5260
                  for ( tmpInt = sub_4423D0(&bTokOk); bTokOk != 0; tmpInt = sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_431230((int)speechIdList, &tmpInt);  // sub_431230 —— uint32 vector push_back
                  pDestStr = speechEntry;
                  sub_4FE6B0((int **)(pNpc + 396), speechEntry);  // 拷入台词列表
                  sub_4FDFE0(pDestStr);  // 调 sub_4FDFE0
                  LOBYTE(v34) = 1;  // 调 取 16 位值低 8 位
                  sub_4FDA00(speechEntry);  // 析构临时条目
                }
                else if ( (uint8_t)sub_423300(&strLine, "[chaos team]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDestStr = (int *)tagStr;
                  sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                  if ( (uint8_t)sub_423300(tagStr, "[red team]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    *(uint32_t *)(pNpc + 272) = 0;  // [red team] → 对象+0x110 = 0
                  }
                  else if ( (uint8_t)sub_423300(tagStr, "[blue team]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    *(uint32_t *)(pNpc + 272) = 1;  // 写字段 pNpc+272 ← 1
                  }
                  else if ( (uint8_t)sub_423300(tagStr, "[neutral team]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    *(uint32_t *)(pNpc + 272) = 200;  // [neutral team] = 200
                  }
                }
                else
                {
                  // 未识别标签：行首是 '[' 才报错
                  tmpInt = (int)tmpTagBuf;
                  sub_401690(&strLine);  // sub_401690 —— std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全量赋值）
                  if ( sub_442C80((char)tmpTagBuf[0], tmpTagBuf[1], (int)v14, (int)v15, v16, (int)v17, (unsigned int)pDestStr) == 0 )  // sub_442C80 —— 行首是 [ 仍未匹配
                  {
                    pszLineDataB = (void **)strLineBuf[0];
                    if ( strLineCap < 0x10 )
                      pszLineDataB = strLineBuf;
                    off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)pszLineDataB);  // off_77F3FC —— 日志打印（printf 风格）
                  }
                }
              }
              else
              {
                pDestStr = (int *)(pNpc + 156);
                sub_443370();  // [field animation] → 对象+0x9C
              }
            }
            else
            {
              pDestStr = (int *)(pNpc + 124);
              sub_443370();  // [popup face] → 对象+0x7C
              *(uint32_t *)(pNpc + 152) = sub_4423D0(nullptr);  // 随后整数 → 对象+0x98
            }
          }
          else
          {
            pDestStr = (int *)(pNpc + 92);
            sub_443370();  // [big face] → 对象+0x5C
            *(uint32_t *)(pNpc + 120) = sub_4423D0(nullptr);  // 随后整数 → 对象+0x78
          }
        }
        else
        {
          pDestStr = (int *)(pNpc + 60);
          sub_443370();  // [small face] → 对象+0x3C
          *(uint32_t *)(pNpc + 88) = sub_4423D0(nullptr);  // 随后整数 → 对象+0x58
        }
      }
      else
      {
        pDestStr = (int *)(pNpc + 32);
        sub_443370();  // [field name] → 对象+0x20 场景名
      }
      goto LABEL_77;  // 跳转 LABEL_77
    }
LABEL_78:
    *(uint32_t *)pNpc = sub_4A2F80(ArgList);  // +0x00 ← 按文件名查全局 ID 表（未登记 = -1）
    if ( tagStrCap >= 0x10 )
      j__free(tagStrBuf);  // 释放堆块
    tagStrCap = 15;
    tagStrLen = 0;
    LOBYTE(tagStrBuf) = 0;  // 调 取 16 位值低 8 位
    if ( strLineCap >= 0x10 )
      j__free(strLineBuf[0]);  // 释放堆块
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FEEA0 sub_4FEEA0
//   设定又一脚本根目录（全局 byte_9B6FA8，补 '\' 或 '/' 结尾）后加载文件表到
//   unk_9B70A8（sub_443C40）。同 4FC840/4FD430/4FD770 族的第四份（本文件内
//   解析器未直接引用该目录，供其他翻译单元使用）。
// ------------------------------------------------------------
bool /*cdecl*/ sub_4FEEA0(const char *pArg1, int nArg2)  // NPC(场地角色)定义解析器
{
  strcpy(byte_9B6FA8, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B6FA7[strlen(byte_9B6FA8)] != 92 && byte_9B6FA7[strlen(byte_9B6FA8)] != 47 )  // 若 byte_9B6FA7[strlen(byte_9B6FA8)] != 92 && byte_9B6FA7[strlen(b..
    *(uint16_t *)&byte_9B6FA8[strlen(byte_9B6FA8)] = 92;  // 调 求串长
  return (uint8_t)sub_443C40((int)&unk_9B70A8, (char)byte_9B6FA8, nArg2) != 0;  // sub_443C40 —— 脚本文件列表装表
}



// ------------------------------------------------------------
// 0x4FEF30 sub_4FEF30
//   std::vector<24字节元素>::size()：(end-begin)/24。24 字节元素 = 任务
//   [clear reward item] 报酬条目（6 int，见 sub_5006B0 解析器）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FEF30(int *this)  // pArg2+4〔宿主对象〕
{
  int result; // eax

  result = *(this + 1);  // 读字段 result = this+1
  if ( result != 0 )  // result=this+4 宿主对象
    return (*(this + 2) - result) / 24;  // this+8 = 技能槽记录首字
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x4FEF50 sub_4FEF50
//   std::_Fill/fill_n（24 字节元素版）：把 [uArg1,uArg2) 区间逐元素用 pArg3 的
//   6 个 dword 覆盖（vector::insert 的元素搬运子例程）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FEF50(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *v4; // edi

  for ( result = uArg1; result != uArg2; v4[5] = pArg3[5] )  // 循环：result = uArg1; result != uArg2; v4[5] = pArg3[5]
  {
    v4 = result;
    *result = *pArg3;  // *result 写入 *pArg3
    result[1] = pArg3[1];  // result[1] 写入 pArg3[1]
    result[2] = pArg3[2];  // result[2] 写入 pArg3[2]
    result[3] = pArg3[3];  // result[3] 写入 pArg3[3]
    result[4] = pArg3[4];  // result[4] 写入 pArg3[4]
    result += 6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FEFA0 sub_4FEFA0
//   std::fill_n（28 字节元素版）：从 pszArg1 起把 pszArg2 个元素用 pArg3 的
//   0x1C 字节整块覆盖（vector::insert 元素搬运子例程）。
// ------------------------------------------------------------
char */*cdecl*/ sub_4FEFA0(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  void *v4; // edi

  for ( result = pszArg1; result != pszArg2; result += 28 )  // 循环：result = pszArg1; result != pszArg2; result += 28
  {
    v4 = result;
    qmemcpy(v4, pArg3, 0x1Cu);  // 调 qmemcpy 内联块拷贝
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FEFD0 sub_4FEFD0
//   std::copy_backward（24 字节元素版）：把 [uArg1,uArg2) 从尾往头搬到 uArg3
//   结尾处（vector::insert 腾位子例程）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FEFD0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg22; // ecx
  uint32_t *result; // eax

  uArg22 = uArg2;
  for ( result = uArg3; uArg22 != uArg1; result[5] = uArg22[5] )  // 循环：result = uArg3; uArg22 != uArg1; result[5] = uArg22[5]
  {
    uArg22 -= 6;
    result -= 6;
    *result = *uArg22;  // *result 写入 *uArg22
    result[1] = uArg22[1];  // result[1] 写入 uArg22[1]
    result[2] = uArg22[2];  // result[2] 写入 uArg22[2]
    result[3] = uArg22[3];  // result[3] 写入 uArg22[3]
    result[4] = uArg22[4];  // result[4] 写入 uArg22[4]
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FF020 sub_4FF020
//   std::copy_backward（28 字节元素版）：[pszArg1,pszArg2) 从尾往头搬到 pszArg3
//   结尾处（vector::insert 腾位子例程）。
// ------------------------------------------------------------
char */*cdecl*/ sub_4FF020(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg22; // edx
  char *result; // eax

  pszArg22 = pszArg2;
  result = pszArg3;
  while ( pszArg22 != pszArg1 )  // 循环直到 pszArg22 != pszArg1
  {
    pszArg22 -= 28;
    result -= 28;
    qmemcpy(result, pszArg22, 0x1Cu);  // 调 qmemcpy 内联块拷贝
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FF050 sub_4FF050
//   std::copy（24 字节元素版，正向逐 6 dword）：[uArg1,uArg2) → uArg3。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FF050(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; result += 6 )  // 循环：result = uArg3; uArg12 != uArg2; result += 6
  {
    if ( result != nullptr )
    {
      *result = *uArg12;  // *result 写入 *uArg12
      result[1] = uArg12[1];  // result[1] 写入 uArg12[1]
      result[2] = uArg12[2];  // result[2] 写入 uArg12[2]
      result[3] = uArg12[3];  // result[3] 写入 uArg12[3]
      result[4] = uArg12[4];  // result[4] 写入 uArg12[4]
      result[5] = uArg12[5];  // result[5] 写入 uArg12[5]
    }
    uArg12 += 6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FF0A0 sub_4FF0A0
//   按计数填充（28 字节元素版）：从 pszArg1 起连续 pszArg2 个元素用 pArg3 的
//   0x1C 字节覆盖（vector::insert 新元素区初始化子例程）。
// ------------------------------------------------------------
char */*cdecl*/ sub_4FF0A0(char *pszArg1, char *pszArg2, const void *pArg3)  // 函数定义: 构造记录并返回其地址
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
        qmemcpy(result, pArg3, 0x1Cu);  // 调 qmemcpy 内联块拷贝
      result += 28;
      --pszArg22;  // 计数自减 pszArg22
    }
    while ( pszArg22 != nullptr );  // 循环直到 pszArg22 != nullptr
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FF0D0 sub_4FF0D0
//   std::vector<24字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量足够 → 尾部腾位搬移（4FF050/504430/504620/4FEF50）；不足 → 扩容
//   （new 一段，三段拷贝）重建。容量上限检查失败走 sub_4CEAB0（length_error）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FF0D0(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)  // 函数: 释放后返回
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v28[0] = *Block;  // v28[0] 写入 *Block
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
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    result = 715827883 * (*(this + 3) - fld_e1);  // this+12 = 技能槽记录次字
    fld_e3 = (*(this + 3) - fld_e1) / 24;  // this+12 = 技能槽记录次字
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 24;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 178956970 - fld_e2 < uArg3 )
      sub_4CEAB0(this);  // 调 sub_4CEAB0
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 24;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);  // this+8 = 技能槽记录首字
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 24 >= uArg3 )
      {
        v30 = (int)fld_e23 - 24 * uArg3;
        *(this + 2) = sub_4FF050(v30, fld_e23, fld_e23);  // 写字段 this+2 ← sub_4FF050(v30, fld_e23, fld_e23)
        sub_504430(pArg2, v30, Blockb);  // 调 sub_504430
        return sub_4FEF50(pArg2, pArg2 + 24 * uArg3, v28);  // 调 sub_4FEF50
      }
      else
      {
        sub_4FF050(pArg2, fld_e23, pArg2 + 24 * uArg3);  // 调 sub_4FF050
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 24;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        v29 = 2;
        sub_504620(fld_e25, fld_e24, v28);  // 调 sub_504620
        fld_e26 = 24 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        return sub_4FEF50(pArg2, fld_e26 - 24 * uArg3, v28);  // 调 sub_4FEF50
      }
    }
    else
    {
      if ( 178956970 - (fld_e3 >> 1) >= fld_e3 )  // 若 178956970 - (fld_e3 >> 1) >= fld_e3
        v16 = (fld_e3 >> 1) + fld_e3;
      else
        v16 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 24;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v16 < uArg3 + fld_e27 )
        v16 = uArg3 + sub_4FEF30(this);  // 调 pArg2+4〔宿主对象〕
      v18 = 24 * v16;  // 计算 v18 = 24 * v16
      Blocka = (char *)operator new(24 * v16);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      v29 = 0;
      v31 = sub_4FF050(fld_e12, pArg2, Blocka);  // 调 sub_4FF050
      sub_5044B0(v31, uArg3, v28);  // 调 sub_5044B0
      sub_4FF050(pArg2, *(this + 2), v31 + 24 * uArg3);  // 调 sub_4FF050
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 24;  // this+8 = 技能槽记录首字
      v20 = fld_e13 + uArg3;  // 计算 v20 = fld_e13 + uArg3
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 释放堆块
      *(this + 3) = (int)&Blocka[v18];  // 写字段 this+3 ← (int)&Blocka[v18]
      *(this + 2) = (int)&Blocka[24 * v20];  // 写字段 this+2 ← (int)&Blocka[24 * v20]
      *(this + 1) = (int)Blocka;  // 写字段 this+1 ← (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FF3A0 sub_4FF3A0
//   std::vector<28字节元素>::insert(pos, n, val)（任务 [monster reward item]
//   掉落条目 7 int）：逻辑同 4FF0D0 的 28 字节版（472DB0/488E00/4FF020/4FEFA0 搬运）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4FF3A0(int *this, char *pszArg2, unsigned int uArg3, void *Block)  // 函数: 释放后返回
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

  qmemcpy(v22, Block, 0x1Cu);  // 调 qmemcpy 内联块拷贝
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v22[7] = &v21;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - fld_e1) / 28;  // this+12 = 技能槽记录次字
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - *(this + 1)) / 28;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 153391689 - fld_e2 < uArg3 )
      sub_4CEAB0(this);  // 调 sub_4CEAB0
    if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
      fld_e22 = (*(this + 2) - *(this + 1)) / 28;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (char *)*(this + 2);  // this+8 = 技能槽记录首字
      Blockb = fld_e23;
      if ( (fld_e23 - pszArg2) / 28 >= uArg3 )
      {
        v24 = &fld_e23[-28 * uArg3];
        *(this + 2) = sub_472DB0(v24, fld_e23, fld_e23);  // 写字段 this+2 ← sub_472DB0(v24, fld_e23, fld_e23)
        sub_4FF020(pszArg2, v24, Blockb);  // 调 sub_4FF020
        sub_4FEFA0(pszArg2, &pszArg2[28 * uArg3], v22);  // 调 sub_4FEFA0
      }
      else
      {
        sub_472DB0(pszArg2, fld_e23, &pszArg2[28 * uArg3]);  // 调 sub_472DB0
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 28;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        v23 = 2;
        sub_488E00(fld_e25, fld_e24, v22);  // sub_488E00 —— 28 字节元素原位构造
        fld_e26 = 28 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        sub_4FEFA0(pszArg2, (char *)(fld_e26 - 28 * uArg3), v22);  // 调 sub_4FEFA0
      }
    }
    else
    {
      if ( 153391689 - (fld_e3 >> 1) >= fld_e3 )  // 若 153391689 - (fld_e3 >> 1) >= fld_e3
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        fld_e27 = (*(this + 2) - *(this + 1)) / 28;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_52AEF0(this);  // sub_52AEF0 —— v10 = 插入数 + sub_52AEF0
      v12 = 28 * v10;  // 计算 v12 = 28 * v10
      Blocka = (char *)operator new(28 * v10);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      v23 = 0;
      v25 = (char *)sub_472DB0(fld_e12, pszArg2, Blocka);  // 调 pszArg3，返回新游标
      sub_4FF0A0(v25, (char *)uArg3, v22);  // 调 sub_4FF0A0
      sub_472DB0(pszArg2, *(this + 2), &v25[28 * uArg3]);  // 调 sub_472DB0
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 28;  // this+8 = 技能槽记录首字
      v14 = fld_e13 + uArg3;  // 计算 v14 = fld_e13 + uArg3
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 释放堆块
      *(this + 3) = (int)&Blocka[v12];  // 写字段 this+3 ← (int)&Blocka[v12]
      *(this + 2) = (int)&Blocka[28 * v14];  // 写字段 this+2 ← (int)&Blocka[28 * v14]
      *(this + 1) = (int)Blocka;  // 写字段 this+1 ← (int)Blocka
    }
  }
}



// ------------------------------------------------------------
// 0x4FF670 sub_4FF670
//   std::vector<24字节元素>::insert(iterator pos, 1, val) 外壳：先算出 pos 的
//   元素下标（防插入导致迭代器失效），转调 sub_4FF0D0 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FF670(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *Block)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (int)&pszArg3[-fld_e1] / 24;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_4FF0D0(this, pszArg3, 1u, Block);  // 调 sub_4FF0D0
  *uArg2 = *(this + 1) + 24 * v6;  // *uArg2 写入 *(this + 1) + 24 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x4FF6E0 sub_4FF6E0
//   std::vector<28字节元素>::insert(pos, 1, val) 外壳：同 4FF670 的 28 字节版
//   （转调 sub_4FF3A0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FF6E0(int *this, uint32_t *uArg2, char *pszArg3, void *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 28 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (int)&pszArg3[-fld_e1] / 28;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_4FF3A0(this, pszArg3, 1u, Block);  // 调 sub_4FF3A0
  *uArg2 = *(this + 1) + 28 * v6;  // *uArg2 写入 *(this + 1) + 28 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x4FF750 sub_4FF750
//   std::vector<24字节元素>::push_back：容量够 → 在 +8 end 直写 1 个元素；
//   不够 → 走 sub_4FF670 插入路径扩容。任务 [clear reward item] 报酬条目入表用。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FF750(int this, uint32_t *Block)  // sub_4FF750 —— 推入对象+0xD0 列表
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  int fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 24;  // this+8 物品 id
  else
    fld_8 = 0;  // fld_8=this+8 物品 id
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 24 )  // this+12 物品类型号
    return sub_4FF670((int *)this, &Block, *(char **)(this + 8), Block);  // 调 sub_4FF670
  fld_82 = *(uint32_t *)(this + 8);  // 读字段 fld_82 = this+8（nSkillRec8）
  result = (uint32_t *)sub_5044B0(fld_82, 1, Block);  // 调 后返回 &pArg1[6*uArg2] 尾地址
  *(uint32_t *)(this + 8) = fld_82 + 24;  // 写字段 this+8（nSkillRec8） ← fld_82 + 24
  return result;
}



// ------------------------------------------------------------
// 0x4FF7E0 sub_4FF7E0
//   std::vector<28字节元素>::push_back：同 4FF750 的 28 字节版。任务
//   [monster reward item] 怪物掉落条目入表用。
// ------------------------------------------------------------
char */*thiscall*/ sub_4FF7E0(int this, void *Block)  // sub_4FF7E0 —— 推入对象+0xE0 列表
{
  int fld_4; // ebx
  unsigned int fld_8; // esi
  char *fld_82; // esi
  char *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 28;  // this+8 物品 id
  else
    fld_8 = 0;  // fld_8=this+8 物品 id
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 28 )  // this+12 物品类型号
    return (char *)sub_4FF6E0((int *)this, &Block, *(char **)(this + 8), Block);  // this+8 物品 id
  fld_82 = *(char **)(this + 8);  // this+8 物品 id
  result = sub_4FF0A0(fld_82, (char *)1, Block);  // 调 sub_4FF0A0
  *(uint32_t *)(this + 8) = fld_82 + 28;  // 写字段 this+8（nSkillRec8） ← fld_82 + 28
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
char /*cdecl*/ sub_4FF870(int *pDwArg1, const char *ArgList)  // sub_4FF870 —— 任务(quest)定义解析器
{
  char result; // al
  unsigned int nTagLen; // edx
  int nCmpLen; // ecx
  void **pszLineData; // esi  行文本数据指针（容量<0x10 取 SSO 缓冲）
  int nCmp; // eax
  void *pszJobTag; // eax  职业标签数据指针
  int nLevelMin; // eax  [level] 第一个值
  int nAppear1; // eax  [appear map] 依次 4 个值
  int nAppear2; // eax
  int nAppear3; // eax
  int nGiveItemId; // eax  [depend give item] 每对第一个 int
  void **pszLineDataB; // eax
  void *tmpTagBuf[3]; // [esp-1Ch] [ebp-C4h] BYREF  未知标签检查：行拷贝（寄存器传参拆散）
  uint8_t *tmpSlot1; // [esp-10h] [ebp-B8h]
  uint8_t *tmpSlot2; // [esp-Ch] [ebp-B4h]
  uint8_t *tmpSlot3; // [esp-8h] [ebp-B0h]  兼作 sub_4423D0 的可解析标志占位（传 nullptr）
  const char *miscArg; // [esp-4h] [ebp-ACh]  目标串槽位 / sub_442C80 容量实参
  uint32_t givePair[2]; // [esp+Ch] [ebp-9Ch] BYREF  [depend give item] (int,int) 对
  void *preReqList[4]; // [esp+14h] [ebp-94h] BYREF  [pre required quest] 临时 list
  int monRwEntry; // [esp+24h] [ebp-84h] BYREF  [monster reward item] 临时条目（7 int）
  int monRwVal1; // [esp+28h] [ebp-80h]  默认 -1
  int monRwVal2; // [esp+2Ch] [ebp-7Ch]  默认 -1
  int monRwVal3; // [esp+30h] [ebp-78h]  默认 0
  int monRwVal4; // [esp+34h] [ebp-74h]  默认 0
  int monRwVal5; // [esp+38h] [ebp-70h]  默认 0
  int monRwVal6; // [esp+3Ch] [ebp-6Ch]  默认 -1
  int clrRwEntry; // [esp+40h] [ebp-68h] BYREF  [clear reward item] 临时条目（6 int）
  int clrRwVal1; // [esp+44h] [ebp-64h]  默认 -1
  int clrRwVal2; // [esp+48h] [ebp-60h]  默认 0
  int clrRwVal3; // [esp+4Ch] [ebp-5Ch]  默认 0
  int clrRwVal4; // [esp+50h] [ebp-58h]  默认 0
  int clrRwVal5; // [esp+54h] [ebp-54h]  默认 -1
  void **listTmp; // [esp+58h] [ebp-50h] BYREF  各 list/vector push 的值暂存
  char bTokOk; // [esp+5Fh] [ebp-49h] BYREF  token 可解析标志
  uint8_t tagStr[4]; // [esp+60h] [ebp-48h] BYREF  职业/类型/报酬类型 标签字符串对象头
  void *tagStrBuf; // [esp+64h] [ebp-44h] BYREF
  unsigned int tagStrLen; // [esp+74h] [ebp-34h]
  unsigned int tagStrCap; // [esp+78h] [ebp-30h]
  int strLine; // [esp+7Ch] [ebp-2Ch] BYREF  行字符串对象头
  void *strLineBuf[4]; // [esp+80h] [ebp-28h] BYREF
  int strLineLen; // [esp+90h] [ebp-18h]
  unsigned int strLineCap; // [esp+94h] [ebp-14h]
  int dword_796E502; // [esp+98h] [ebp-10h]
  int v45; // [esp+A4h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B6FA8, (int)ArgList);  // 打开任务定义脚本
  if ( result != 0 )
  {
    sub_4D0D00(pDwArg1);  // 重置任务定义对象
    strLineCap = 15;
    strLineLen = 0;
    LOBYTE(strLineBuf[0]) = 0;  // 调 取 16 位值低 8 位
    v45 = 1;
    tagStrCap = 15;
    tagStrLen = 0;
    LOBYTE(tagStrBuf) = 0;  // 调 取 16 位值低 8 位
    bTokOk = 0;
    if ( (uint8_t)sub_443430(&strLine) != 0 )  // 读第一行
    {
      while ( 1 )  // 当 1 循环
      {
        sub_442B20(&strLine);  // sub_442B20 —— 国家码标签配对校验（void）
        nTagLen = strLineLen;
        if ( strLineLen == 0 )
          goto LABEL_13;  // 跳转 LABEL_13
        nCmpLen = strLineLen;
        if ( (unsigned int)strLineLen >= 6 )
          nCmpLen = 6;
        pszLineData = (void **)strLineBuf[0];
        if ( strLineCap < 0x10 )
          pszLineData = strLineBuf;
        nCmp = memcmp((const char *)pszLineData, "[name]", nCmpLen);  // 调 memcmp 内存比较
        if ( nCmp != 0 )
          break;
        if ( (unsigned int)strLineLen < 6 )
          break;
        LOBYTE(nCmp) = strLineLen != 6;  // 调 取 16 位值低 8 位
        if ( nCmp != 0 )
          break;
        miscArg = (const char *)(pDwArg1 + 1);
        sub_443370();  // [name] → 对象+0x04
LABEL_108:
        if ( (uint8_t)sub_443430(&strLine) == 0 )  // 读下一行
          goto LABEL_109;  // 跳转 LABEL_109
      }
      nTagLen = strLineLen;
LABEL_13:
      if ( sub_40BF00((std::_String_base *)&strLine, 0, nTagLen, "[depend message]", 0x10u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[condition message]", 0x13u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[solve message]", 0xFu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[grade]", 7u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              if ( sub_40BF00((std::_String_base *)&strLine, 0, strLineLen, "[job change quest]", 0x12u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
              {
                if ( (uint8_t)sub_423300(&strLine, "[npc index]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDwArg1[31] = sub_4423D0(nullptr);  // → 对象+0x7C 接任务 NPC
                }
                else if ( (uint8_t)sub_423300(&strLine, "[complete npc index]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDwArg1[32] = sub_4423D0(nullptr);  // → 对象+0x80 交付 NPC
                }
                else if ( (uint8_t)sub_423300(&strLine, "[job]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  miscArg = tagStr;
                  sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                  pszJobTag = tagStrBuf;
                  if ( tagStrCap < 0x10 )
                    pszJobTag = &tagStrBuf;
                  pDwArg1[33] = sub_4426A0(pszJobTag);  // 【职业标签→索引（[swordman]/[fighter]/[gunner]/[mag…】→ 对象+0x84
                }
                else if ( (uint8_t)sub_423300(&strLine, "[grow type]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDwArg1[34] = sub_4423D0(nullptr);  // → 对象+0x88
                }
                else if ( (uint8_t)sub_423300(&strLine, "[exceptional grow type]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_5E5260((void **)pDwArg1 + 35);  // 清空对象+0x8C list
                  for ( listTmp = (void **)sub_4423D0(&bTokOk); bTokOk != 0; listTmp = (void **)sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_431230((int)(pDwArg1 + 35), &listTmp);  // 例外成长类型逐个推入
                }
                else if ( (uint8_t)sub_423300(&strLine, "[level]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  nLevelMin = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  tmpSlot3 = nullptr;  // tmpSlot3 = nullptr 空指针
                  pDwArg1[39] = nLevelMin;  // → 对象+0x9C 最低等级
                  pDwArg1[40] = sub_4423D0(tmpSlot3);  // → 对象+0xA0（收尾会被覆盖为 99）
                }
                else if ( (uint8_t)sub_423300(&strLine, "[pre required quest]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  memset(&preReqList[1], 0, 12);  // 调 memset 按字节填充
                  LOBYTE(v45) = 2;  // 调 取 16 位值低 8 位
                  for ( listTmp = (void **)sub_4423D0(&bTokOk); bTokOk != 0; listTmp = (void **)sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_431230((int)preReqList, &listTmp);  // 前置任务 id 逐个收集
                  if ( !sub_484F10(preReqList) )  // 非空才合并
                    sub_475190((int)(pDwArg1 + 41), preReqList);  // → 对象+0xA4 前置任务 list
                  LOBYTE(v45) = 1;  // 调 取 16 位值低 8 位
                  sub_5E5260(preReqList);  // 调 sub_5E5260
                }
                else if ( (uint8_t)sub_423300(&strLine, "[collision quest]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_5E5260((void **)pDwArg1 + 45);  // 清空对象+0xB4
                  for ( listTmp = (void **)sub_4423D0(&bTokOk); bTokOk != 0; listTmp = (void **)sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_431230((int)(pDwArg1 + 45), &listTmp);  // 互斥任务 id 逐个推入
                }
                else if ( (uint8_t)sub_423300(&strLine, "[PVP RANK]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDwArg1[49] = sub_4423D0(nullptr);  // → 对象+0xC4
                }
                else if ( (uint8_t)sub_423300(&strLine, "[effect after clear quest]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *((uint8_t *)pDwArg1 + 200) = sub_4423D0(nullptr) != 0;  // → 对象+0xC8 布尔
                }
                else if ( (uint8_t)sub_423300(&strLine, "[delete npc index]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDwArg1[51] = sub_4423D0(nullptr);  // → 对象+0xCC
                }
                else if ( (uint8_t)sub_423300(&strLine, "[clear reward item]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_5E5260((void **)pDwArg1 + 52);  // 清空对象+0xD0 报酬列表
                  while ( 1 )  // 当 1 循环
                  {
                    clrRwVal1 = -1;  // 条目默认值
                    clrRwVal2 = 0;
                    clrRwVal3 = 0;
                    clrRwVal4 = 0;
                    clrRwVal5 = -1;
                    clrRwEntry = sub_4423D0(&bTokOk);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    if ( bTokOk == 0 )
                      break;
                    clrRwVal1 = sub_4423D0(nullptr);  // 逐个读满 6 int 条目
                    clrRwVal2 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    clrRwVal3 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    clrRwVal4 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    clrRwVal5 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_4FF750(&clrRwEntry);  // 推入对象+0xD0 列表
                  }
                }
                else if ( (uint8_t)sub_423300(&strLine, "[monster reward item]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_5E5260((void **)pDwArg1 + 56);  // 清空对象+0xE0 怪物掉落列表
                  while ( 1 )  // 当 1 循环
                  {
                    monRwVal1 = -1;  // 条目默认值
                    monRwVal2 = -1;
                    monRwVal3 = 0;
                    monRwVal4 = 0;
                    monRwVal5 = 0;
                    monRwVal6 = -1;
                    monRwEntry = sub_4423D0(&bTokOk);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    if ( bTokOk == 0 )
                      break;
                    monRwVal1 = sub_4423D0(nullptr);  // 逐个读满 7 int 条目
                    monRwVal2 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    monRwVal3 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    monRwVal4 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    monRwVal5 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    monRwVal6 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_4FF7E0(&monRwEntry);  // 推入对象+0xE0 列表
                  }
                }
                else if ( (uint8_t)sub_423300(&strLine, "[appear map]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  nAppear1 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  tmpSlot3 = nullptr;  // tmpSlot3 = nullptr 空指针
                  pDwArg1[60] = nAppear1;  // → 对象+0xF0
                  nAppear2 = sub_4423D0(tmpSlot3);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  tmpSlot2 = nullptr;  // tmpSlot2 = nullptr 空指针
                  pDwArg1[61] = nAppear2;  // → 对象+0xF4
                  nAppear3 = sub_4423D0(tmpSlot2);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  tmpSlot1 = nullptr;  // tmpSlot1 = nullptr 空指针
                  pDwArg1[62] = nAppear3;  // → 对象+0xF8
                  pDwArg1[63] = sub_4423D0(tmpSlot1);  // → 对象+0xFC
                }
                else if ( (uint8_t)sub_423300(&strLine, "[depend give item]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_5E5260((void **)pDwArg1 + 64);  // 清空对象+0x100
                  for ( nGiveItemId = sub_4423D0(&bTokOk); bTokOk != 0; nGiveItemId = sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                  {
                    givePair[0] = nGiveItemId;
                    givePair[1] = sub_4423D0(nullptr);  // (物品id, 数量) 对
                    sub_474950(givePair);  // 推入对象+0x100 列表
                  }
                }
                else if ( (uint8_t)sub_423300(&strLine, "[type]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  miscArg = tagStr;
                  sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                  if ( (uint8_t)sub_423300(tagStr, "[seeking]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pDwArg1[68] = 0;  // 完成方式枚举 → 对象+0x110
                  }
                  else if ( (uint8_t)sub_423300(tagStr, "[condition under clear]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pDwArg1[68] = 1;
                  }
                  else if ( (uint8_t)sub_423300(tagStr, "[hunt monster]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pDwArg1[68] = 2;
                  }
                  else if ( (uint8_t)sub_423300(tagStr, "[clear map]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pDwArg1[68] = 3;
                  }
                  else if ( (uint8_t)sub_423300(tagStr, "[meet npc]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pDwArg1[68] = 4;
                  }
                  else if ( (uint8_t)sub_423300(tagStr, "[pvp rank]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pDwArg1[68] = 5;
                  }
                }
                else if ( (uint8_t)sub_423300(&strLine, "[sub type]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDwArg1[69] = sub_4423D0(nullptr);  // → 对象+0x114
                }
                else if ( (uint8_t)sub_423300(&strLine, "[int data]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_5E5260((void **)pDwArg1 + 70);  // 清空对象+0x118
                  for ( listTmp = (void **)sub_4423D0(&bTokOk); bTokOk != 0; listTmp = (void **)sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_431230((int)(pDwArg1 + 70), &listTmp);  // 条件用整数数据逐个推入
                }
                else if ( (uint8_t)sub_423300(&strLine, "[reward type]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  miscArg = tagStr;
                  sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                  if ( (uint8_t)sub_423300(tagStr, "[item]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pDwArg1[74] = 0;  // 报酬类型枚举 → 对象+0x128
                  }
                  else if ( (uint8_t)sub_423300(tagStr, "[grow type]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    pDwArg1[74] = 1;
                  }
                }
                else if ( (uint8_t)sub_423300(&strLine, "[reward int data]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_5E5260((void **)pDwArg1 + 75);  // 清空对象+0x12C
                  for ( listTmp = (void **)sub_4423D0(&bTokOk); bTokOk != 0; listTmp = (void **)sub_4423D0(&bTokOk) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_431230((int)(pDwArg1 + 75), &listTmp);  // 报酬整数数据逐个推入
                }
                else if ( (uint8_t)sub_423300(&strLine, "[relation quest]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDwArg1[79] = sub_4423D0(nullptr);  // → 对象+0x13C 关联任务
                }
                else
                {
                  listTmp = tmpTagBuf;  // 拷贝构造目标（this 经寄存器传给 sub_401690）
                  sub_401690((int)tmpTagBuf, (size_t *)&strLine);  // 拷贝整行
                  if ( (uint8_t)sub_442C80(  // sub_442C80 —— 行首是 [ 仍未匹配
                                          (char)tmpTagBuf[0],
                                          tmpTagBuf[1],
                                          (int)tmpTagBuf[2],
                                          (int)tmpSlot1,
                                          (int)tmpSlot2,
                                          (int)tmpSlot3,
                                          (int)miscArg) == 0 )  // 行首是 '[' 仍未匹配
                  {
                    pszLineDataB = (void **)strLineBuf[0];
                    if ( strLineCap < 0x10 )
                      pszLineDataB = strLineBuf;
                    off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)pszLineDataB);  // off_77F3FC —— 日志打印（printf 风格）
                  }
                }
              }
              else
              {
                *((uint8_t *)pDwArg1 + 120) = sub_4423D0(nullptr) != 0;  // [job change quest] → 对象+0x78 布尔
              }
            }
            else
            {
              miscArg = tagStr;
              sub_443370();  // [grade] 子标签 → tagStr
              if ( sub_40BF00((std::_String_base *)tagStr, 0, tagStrLen, "[normaly repeat]", 0x10u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
              {
                if ( (uint8_t)sub_423300(tagStr, "[common unique]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDwArg1[29] = 1;  // → 对象+0x74
                }
                else if ( (uint8_t)sub_423300(tagStr, "[epic]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  pDwArg1[29] = 2;
                }
              }
              else
              {
                pDwArg1[29] = 0;  // [normaly repeat]
              }
            }
          }
          else
          {
            miscArg = (const char *)(pDwArg1 + 22);
            sub_443370();  // [solve message] → 对象+0x58
          }
        }
        else
        {
          miscArg = (const char *)(pDwArg1 + 15);
          sub_443370();  // [condition message] → 对象+0x3C
        }
      }
      else
      {
        miscArg = (const char *)(pDwArg1 + 8);
        sub_443370();  // [depend message] → 对象+0x20
      }
      goto LABEL_108;  // 跳转 LABEL_108
    }
LABEL_109:
    miscArg = ArgList;
    pDwArg1[40] = 99;  // +0xA0 ← 99（在 [level] 之后执行，原样覆盖第二值）
    *pDwArg1 = sub_4A2F80(dword_9B70A8, miscArg);  // +0x00 ← 按文件名查全局任务 ID 表
    if ( pDwArg1[32] == -1 )  // 若 pDwArg1[32] == -1
      pDwArg1[32] = pDwArg1[31];  // 未给交付 NPC → 复用接任务 NPC
    if ( tagStrCap >= 0x10 )
      j__free(tagStrBuf);  // 释放堆块
    tagStrCap = 15;
    tagStrLen = 0;
    LOBYTE(tagStrBuf) = 0;  // 调 取 16 位值低 8 位
    if ( strLineCap >= 0x10 )
      j__free(strLineBuf[0]);  // 释放堆块
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5002A0 sub_5002A0
//   设定 NPC 商店脚本根目录（全局 byte_9B70B8，补 '\' 或 '/' 结尾）后加载文件表到
//   unk_9B71B8（sub_443C40）。sub_500330 商店解析器经 &unk_9B70B8 使用该目录。
// ------------------------------------------------------------
bool /*cdecl*/ sub_5002A0(const char *pArg1, int nArg2)  // 任务(quest)定义解析器
{
  strcpy(byte_9B70B8, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B70B7[strlen(byte_9B70B8)] != 92 && byte_9B70B7[strlen(byte_9B70B8)] != 47 )  // 若 byte_9B70B7[strlen(byte_9B70B8)] != 92 && byte_9B70B7[strlen(b..
    *(uint16_t *)&byte_9B70B8[strlen(byte_9B70B8)] = 92;  // 调 求串长
  return (uint8_t)sub_443C40((int)&unk_9B71B8, (char)byte_9B70B8, nArg2) != 0;  // sub_443C40 —— 脚本文件列表装表
}



// ------------------------------------------------------------
// 0x500330 sub_500330 —— NPC 商店(npc shop)定义解析器
//   标签族：[NPC]/[message]/[type]（商店枚举子串 [etc shop]/[weapon shop]/[disjoint shop]）
//   /[only buy]/[sell item]。
// ------------------------------------------------------------
char /*cdecl*/ sub_500330(int pArg1, const char *ArgList)  // sub_500330 —— NPC 商店(npc shop)定义解析器
{
  char result; // al
  int pShop; // esi  商店定义对象（偏移：+0x00 ID/+0x04 类型/+0x08 NPC 索引/+0x0C 仅收购/
             //        +0x10 台词串/+0x30 起商品 id vector）
  unsigned int nTagLen; // edx
  int nCmpLen; // ecx
  void **pszLineData; // esi  行文本数据指针（容量<0x10 取 SSO 缓冲）
  int nCmp; // eax
  int nSellItemId; // eax  [sell item] 当前商品 id
  int pVecBegin; // esi  对象+0x30 vector 起始
  unsigned int nCount; // edx
  int *pVecEnd; // ecx
  void **pszLineDataB; // eax
  char v13; // [esp-1Ch] [ebp-78h] BYREF  未知标签检查：行拷贝串头（寄存器传参拆散）
  void **v14; // [esp-18h] [ebp-74h]
  int v15; // [esp-14h] [ebp-70h]
  int v16; // [esp-10h] [ebp-6Ch]
  int v17; // [esp-Ch] [ebp-68h]
  CHAR *v18; // [esp-8h] [ebp-64h]
  unsigned int miscArg; // [esp-4h] [ebp-60h]  多用途槽位（容量实参/标志指针/目标串）
  int nSellItemVal; // [esp+Ch] [ebp-50h] BYREF  push 暂存
  char bTokOk; // [esp+13h] [ebp-49h] BYREF  token 可解析标志
  uint8_t typeStr[4]; // [esp+14h] [ebp-48h] BYREF  [type] 子标签字符串对象头
  void *typeStrBuf; // [esp+18h] [ebp-44h]
  unsigned int typeStrLen; // [esp+28h] [ebp-34h]
  unsigned int typeStrCap; // [esp+2Ch] [ebp-30h]
  uint8_t strLine[4]; // [esp+30h] [ebp-2Ch] BYREF  行字符串对象头
  void *strLineBuf[4]; // [esp+34h] [ebp-28h] BYREF
  int strLineLen; // [esp+44h] [ebp-18h]
  unsigned int strLineCap; // [esp+48h] [ebp-14h]
  int dword_796E502; // [esp+4Ch] [ebp-10h]
  int v31; // [esp+58h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B70B8, (int)ArgList);  // 打开商店定义脚本
  if ( result != 0 )
  {
    pShop = pArg1;
    miscArg = 0;
    v18 = (CHAR *)szPassword;
    *(uint32_t *)pArg1 = 0;
    *(uint32_t *)(pArg1 + 4) = 0;  // 写字段 pArg1+4（pHostObj） ← 0
    *(uint32_t *)(pArg1 + 8) = 0;  // 写字段 pArg1+8（nSkillRec8） ← 0
    *(uint8_t *)(pArg1 + 12) = 0;  // 写字段 pArg1+12（nSkillRec12） ← 0
    sub_4015C0(v18, miscArg);  // 【std::string构造赋值】置空对象+0x10 台词串（this 经寄存器）
    if ( *(uint32_t *)(pArg1 + 48) != 0 )  // 若 *(uint32_t *)(pArg1 + 48) != 0
      j__free(*(void **)(pArg1 + 48));  // 释放堆块
    *(uint32_t *)(pArg1 + 48) = 0;   // +0x30 vector 起始
    *(uint32_t *)(pArg1 + 52) = 0;   // 结束
    *(uint32_t *)(pArg1 + 56) = 0;   // 容量尾
    strLineCap = 15;
    strLineLen = 0;
    LOBYTE(strLineBuf[0]) = 0;  // 调 取 16 位值低 8 位
    v31 = 1;
    typeStrCap = 15;
    typeStrLen = 0;
    LOBYTE(typeStrBuf) = 0;  // 调 取 16 位值低 8 位
    bTokOk = 0;
    if ( (uint8_t)sub_443430(strLine) != 0 )  // 读第一行
    {
      while ( 1 )  // 当 1 循环
      {
        sub_442B20(strLine);  // sub_442B20 —— 国家码标签配对校验（void）
        nTagLen = strLineLen;
        if ( strLineLen == 0 )
          goto LABEL_15;  // 跳转 LABEL_15
        nCmpLen = strLineLen;
        if ( (unsigned int)strLineLen >= 5 )
          nCmpLen = 5;  // "[NPC]" 长度
        pszLineData = (void **)strLineBuf[0];
        if ( strLineCap < 0x10 )
          pszLineData = strLineBuf;
        nCmp = memcmp((const char *)pszLineData, "[NPC]", nCmpLen);  // 调 memcmp 内存比较
        if ( nCmp != 0 )
          break;
        if ( (unsigned int)strLineLen < 5 )
          break;
        LOBYTE(nCmp) = strLineLen != 5;  // 调 取 16 位值低 8 位
        if ( nCmp != 0 )
          break;
        *(uint32_t *)(pArg1 + 8) = sub_4423D0(nullptr);  // [NPC] → 对象+0x08
        pShop = pArg1;
LABEL_43:
        if ( (uint8_t)sub_443430(strLine) == 0 )  // 读下一行
          goto LABEL_44;  // 跳转 LABEL_44
      }
      nTagLen = strLineLen;
      pShop = pArg1;
LABEL_15:
      if ( sub_40BF00((std::_String_base *)strLine, 0, nTagLen, "[message]", 9u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)strLine, 0, strLineLen, "[type]", 6u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)strLine, 0, strLineLen, "[only buy]", 0xAu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)strLine, 0, strLineLen, "[sell item]", 0xBu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              nSellItemVal = (int)&v13;
              miscArg = 15;
              v18 = nullptr;  // v18 = nullptr 空指针
              LOBYTE(v14) = 0;  // 调 取 16 位值低 8 位
              sub_4014D0((std::_String_base *)&v13, strLine, 0, -1);  // 拷贝整行
              if ( sub_442C80(v13, v14, v15, v16, v17, (int)v18, miscArg) == 0 )  // 行首是 '[' 仍未匹配
              {
                pszLineDataB = (void **)strLineBuf[0];
                if ( strLineCap < 0x10 )
                  pszLineDataB = strLineBuf;
                off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, (const char *)pszLineDataB);  // off_77F3FC —— 日志打印（printf 风格）
              }
            }
            else
            {
              // [sell item] → 对象+0x30 vector<int>：逐个读商品 id 推入
              if ( *(uint32_t *)(pArg1 + 48) != 0 )  // 若 *(uint32_t *)(pArg1 + 48) != 0
                j__free(*(void **)(pArg1 + 48));  // 释放堆块
              miscArg = (unsigned int)&bTokOk;
              *(uint32_t *)(pArg1 + 48) = 0;  // 写字段 pArg1+48（pCmdVecBegin48） ← 0
              *(uint32_t *)(pArg1 + 52) = 0;  // 写字段 pArg1+52（bAuraState） ← 0
              *(uint32_t *)(pArg1 + 56) = 0;  // 写字段 pArg1+56（pCmdVecCap56） ← 0
              nSellItemId = sub_4423D0((uint8_t *)miscArg);  // sub_4423D0 —— [LOOP] → 动画对象+160
              nSellItemVal = nSellItemId;
              if ( bTokOk != 0 )
              {
                do
                {
                  pVecBegin = *(uint32_t *)(pArg1 + 48);  // 读字段 pVecBegin = pArg1+48（pCmdVecBegin48）
                  if ( pVecBegin != 0 )
                    nCount = (*(uint32_t *)(pArg1 + 52) - pVecBegin) >> 2;
                  else
                    nCount = 0;
                  if ( pVecBegin != 0 && nCount < (*(uint32_t *)(pArg1 + 56) - pVecBegin) >> 2 )
                  {
                    pVecEnd = *(int **)(pArg1 + 52);
                    *pVecEnd = nSellItemId;  // 有富余容量 → 直写
                    *(uint32_t *)(pArg1 + 52) = pVecEnd + 1;  // 写字段 pArg1+52（bAuraState） ← pVecEnd + 1
                  }
                  else
                  {
                    sub_430C80(*(void **)(pArg1 + 52), 1, (int)&nSellItemVal);  // push_back 兜底
                  }
                  nSellItemId = sub_4423D0(&bTokOk);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  nSellItemVal = nSellItemId;
                }
                while ( bTokOk != 0 );  // 循环直到 bTokOk != 0
                pShop = pArg1;
              }
            }
          }
          else
          {
            *(uint8_t *)(pShop + 12) = sub_4423D0(nullptr) != 0;  // [only buy] → 对象+0x0C 布尔
          }
        }
        else
        {
          miscArg = (unsigned int)typeStr;
          sub_443370();  // [type] 子标签 → typeStr
          if ( sub_40BF00((std::_String_base *)typeStr, 0, typeStrLen, "[etc shop]", 0xAu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)typeStr, 0, typeStrLen, "[weapon shop]", 0xDu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              if ( sub_40BF00((std::_String_base *)typeStr, 0, typeStrLen, "[disjoint shop]", 0xFu) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
                *(uint32_t *)(pShop + 4) = 2;  // [disjoint shop] = 2
            }
            else
            {
              *(uint32_t *)(pShop + 4) = 1;  // [weapon shop] = 1
            }
          }
          else
          {
            *(uint32_t *)(pShop + 4) = 0;  // [etc shop] = 0
          }
        }
      }
      else
      {
        miscArg = pShop + 16;
        sub_443370();  // [message] → 对象+0x10 台词串
      }
      goto LABEL_43;  // 跳转 LABEL_43
    }
LABEL_44:
    *(uint32_t *)pShop = sub_4A2F80(ArgList);  // +0x00 ← 按文件名查全局 ID 表（未登记 = -1）
    if ( typeStrCap >= 0x10 )
      j__free(typeStrBuf);  // 释放堆块
    typeStrCap = 15;
    typeStrLen = 0;
    LOBYTE(typeStrBuf) = 0;  // 调 取 16 位值低 8 位
    if ( strLineCap >= 0x10 )
      j__free(strLineBuf[0]);  // 释放堆块
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5006B0 sub_5006B0
//   32 字节条目默认构造：+0x04 字符串空串初始化（数据@+4/长度@+20/容量@+24）、
//   +0x1C 整数清零。quest/PO 解析器 [object] 标签的条目 {名称串, 参数 int}。
// ------------------------------------------------------------
int /*thiscall*/ sub_5006B0(int this)  // NPC 商店(npc shop)定义解析器
{
  *(uint32_t *)(this + 24) = 15;  // 写字段 this+24（nPageMax） ← 15
  *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
  *(uint8_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
  return this;
}



// ------------------------------------------------------------
// 0x500710 sub_500710
//   按计数拷贝构造 32 字节条目（从 pArg3 复制 +0x04 字符串与 +0x1C 整数），
//   返回构造完成后的尾地址（未初始化填充子例程，步进 32 字节）。
// ------------------------------------------------------------
int /*cdecl*/ sub_500710(int nArg1, int nArg2, int pArg3)  // 函数定义: 后返回 nArg1+32*nArg2 尾地址
{
  int nArg12; // esi
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v5[5] = v5;
  v5[4] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    v5[3] = nArg12;
    LOBYTE(v6) = 1;  // 调 取 16 位值低 8 位
    if ( nArg12 != 0 )
    {
      *(uint32_t *)(nArg12 + 24) = 15;  // 写字段 nArg12+24（nPageMax） ← 15
      *(uint32_t *)(nArg12 + 20) = 0;  // 写字段 nArg12+20（nPage） ← 0
      *(uint8_t *)(nArg12 + 4) = 0;  // 写字段 nArg12+4（pHostObj） ← 0
      sub_4014D0((std::_String_base *)nArg12, pArg3, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      result = *(uint32_t *)(pArg3 + 28);  // 读字段 result = pArg3+28（pPanelVec）
      *(uint32_t *)(nArg12 + 28) = result;  // 写字段 nArg12+28（pPanelVec） ← result
    }
    nArg12 += 32;
    LOBYTE(v6) = 0;  // 调 取 16 位值低 8 位
    --nArg2;  // 计数自减 nArg2
  }
  return result;
}



// ------------------------------------------------------------
// 0x5007D0 sub_5007D0
//   std::_Fill_n（32 字节条目版）：转调 sub_500710 后返回 nArg1+32*nArg2 尾地址。
// ------------------------------------------------------------
int /*stdcall*/ sub_5007D0(int nArg1, int nArg2, int nArg3)
{
  sub_500710(nArg1, nArg2, nArg3);  // 调 sub_500710
  return nArg1 + 32 * nArg2;
}



// ------------------------------------------------------------
// 0x500800 sub_500800
//   std::vector<32字节条目>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（4981F0/492DA0/5007D0/492D60 搬运）；不足 → 扩容三段拷贝
//   重建（旧缓冲经 493260 析构 + free）。
// ------------------------------------------------------------
void /*thiscall*/ sub_500800(int this, int pArg2, unsigned int uArg3, int pArg4)  // 函数: 释放后返回
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
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v26[3] = this;
  v32 = 15;
  v31 = 0;
  LOBYTE(v30) = 0;  // 调 取 16 位值低 8 位
  sub_4014D0((std::_String_base *)v29, pArg4, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  v33 = *(uint32_t *)(pArg4 + 28);  // 读字段 v33 = pArg4+28（pPanelVec）
  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  v36 = 0;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 5;  // this+12 物品类型号
  else
    fld_C = 0;  // fld_C=this+12 物品类型号
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8 物品 id
    else
      fld_8 = 0;  // fld_8=this+8 物品 id
    if ( 0x7FFFFFF - fld_8 < uArg3 )  // fld_8=this+8 物品 id
      sub_427E20(this);  // sub_427E20 —— STL 内联 vector<T> too long
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8 物品 id
    else
      fld_82 = 0;  // fld_82=this+8 物品 id
    if ( fld_C >= uArg3 + fld_82 )  // fld_C=this+12 物品类型号
    {
      fld_83 = *(char **)(this + 8);  // this+8 物品 id
      Block = fld_83;  // fld_83=this+8 物品 id
      if ( (int)&fld_83[-pArg2] >> 5 >= uArg3 )  // fld_83=this+8 物品 id
      {
        v19 = &fld_83[-32 * uArg3];  // fld_83=this+8 物品 id
        v20 = sub_4981F0(v19, fld_83, fld_83);  // sub_4981F0 —— 32 字节元素区间构造拷贝（先置空串）
        Block2 = Block;
        *(uint32_t *)(this + 8) = v20;  // 写字段 this+8（nSkillRec8） ← v20
        sub_492DA0(pArg2, v19, Block2);  // sub_492DA0 —— 转发 ·0x492880（32 字节元素反向拷贝）
        sub_492D60(pArg2, pArg2 + 32 * uArg3, v29);  // sub_492D60 —— 32 字节元素容器正向区间拷贝（逐元素赋值，非构造版）
      }
      else
      {
        sub_4981F0(pArg2, fld_83, pArg2 + 32 * uArg3);  // sub_4981F0 —— 32 字节元素区间构造拷贝（先置空串）
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 5);  // this+8 物品 id
        fld_85 = *(uint32_t *)(this + 8);  // 读字段 fld_85 = this+8（nSkillRec8）
        LOBYTE(v36) = 3;  // 调 取 16 位值低 8 位
        sub_5007D0(fld_85, fld_84, v29);  // 调 sub_5007D0
        fld_86 = 32 * uArg3 + *(uint32_t *)(this + 8);  // this+8 物品 id
        *(uint32_t *)(this + 8) = fld_86;  // 写字段 this+8（nSkillRec8） ← fld_86
        v36 = 0;
        sub_492D60(pArg2, fld_86 - 32 * uArg3, v29);  // sub_492D60 —— 32 字节元素容器正向区间拷贝（逐元素赋值，非构造版）
      }
    }
    else
    {
      if ( 0x7FFFFFF - (fld_C >> 1) >= fld_C )  // 若 0x7FFFFFF - (fld_C >> 1) >= fld_C
        v10 = (fld_C >> 1) + fld_C;  // fld_C=this+12 物品类型号
      else
        v10 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8 物品 id
      else
        fld_87 = 0;  // fld_87=this+8 物品 id
      if ( v10 < uArg3 + fld_87 )  // fld_87=this+8 物品 id
      {
        if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8 物品 id
        else
          fld_88 = 0;  // fld_88=this+8 物品 id
        v10 = uArg3 + fld_88;  // 计算 v10 = uArg3 + fld_88
      }
      v37 = 32 * v10;  // 计算 v37 = 32 * v10
      pMem = (char *)operator new(32 * v10);  // 堆分配
      fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;  // 调 取 16 位值低 8 位
      pMem2 = (char *)sub_4981F0(fld_42, pArg2, pMem);  // sub_4981F0 —— 32 字节元素区间构造拷贝（先置空串）
      sub_500710(pMem2, uArg3, v29);  // 调 sub_500710
      fld_89 = *(uint32_t *)(this + 8);  // 读字段 fld_89 = this+8（nSkillRec8）
      pMem2 += 32 * uArg3;
      sub_4981F0(pArg2, fld_89, pMem2);  // sub_4981F0 —— 32 字节元素区间构造拷贝（先置空串）
      fld_43 = *(void **)(this + 4);  // this+4 宿主对象
      if ( fld_43 != nullptr )  // fld_43=this+4 宿主对象
        fld_810 = (*(uint32_t *)(this + 8) - (int)fld_43) >> 5;  // this+8 物品 id
      else
        fld_810 = 0;  // fld_810=this+8 物品 id
      v16 = fld_810 + uArg3;  // 计算 v16 = fld_810 + uArg3
      if ( fld_43 != nullptr )  // fld_43=this+4 宿主对象
      {
        sub_493260(fld_43, *(uint32_t *)(this + 8));  // sub_493260 —— 32 字节元素数组析构遍历（区间 [pszArg1,pszArg2)，步长 32）
        j__free(*(void **)(this + 4));  // 释放堆块
      }
      *(uint32_t *)(this + 12) = &pMem[v37];  // 写字段 this+12（nSkillRec12） ← &pMem[v37]
      *(uint32_t *)(this + 8) = &pMem[32 * v16];  // 写字段 this+8（nSkillRec8） ← &pMem[32 * v16]
      *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
    }
  }
  if ( v32 >= 0x10 )
    j__free(v30);  // 释放堆块
}


// ------------------------------------------------------------
// 0x500AC0 sub_500AC0
//   std::vector<32字节条目>::push_back：容量够 → 在 +8 end 直写 1 个条目
//   （sub_500710 构造）；不够 → 转调 sub_500800 插入路径扩容。
// ------------------------------------------------------------
void /*thiscall*/ sub_500AC0(int *this, int nArg2)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 5;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 5 )  // fld_e1=this+4 宿主对象
  {
    fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
    sub_500710(fld_e22, 1, nArg2);  // 调 sub_500710
    *(this + 2) = fld_e22 + 32;  // 写字段 this+2 ← fld_e22 + 32
  }
  else
  {
    sub_500800((int)this, *(this + 2), 1u, nArg2);  // 调 sub_500800
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
char /*cdecl*/ sub_500B30(int pArg1, char *ArgList)  // sub_500B30 —— 对象创建/运动定义解析器（PassiveObject 生成器，[creation pos] 族）
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)szPassword, (int)ArgList);  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )
  {
    sub_443300(pArg1 + 196, ArgList, v24);  // 调 格式化串取目录前缀
    sub_4D0B90(pArg1);  // 调 sub_4D0B90
    sub_443300(pArg1 + 196, ArgList, v24);  // 调 格式化串取目录前缀
    v3 = 0;
    v36 = 15;
    v35 = 0;
    LOBYTE(v34) = 0;  // 调 取 16 位值低 8 位
    v38 = 1;
    v32 = 15;
    v31 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    v26 = 0;
    while ( (uint8_t)sub_443430(&v33) != 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    {
      sub_442B20(&v33);  // sub_442B20 —— 国家码标签配对校验（void）
      if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[creation pos]", 0xEu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[x axis]", 8u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[y axis]", 8u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)&v33, 0, v35, "[z axis]", 8u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              if ( (uint8_t)sub_423300(&v33, "[move type]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                j = v29;
                sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v29, "[stop]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(v3 + pArg1 + 12) = 0;
                }
                else if ( (uint8_t)sub_423300(v29, "[straight line]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(v3 + pArg1 + 12) = 1;
                }
                else if ( (uint8_t)sub_423300(v29, "[sin]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(v3 + pArg1 + 12) = 2;
                }
                else if ( (uint8_t)sub_423300(v29, "[cos]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(v3 + pArg1 + 12) = 3;
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[move variable 1]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v6 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v22 = nullptr;  // v22 = nullptr 空指针
                *(uint32_t *)(pArg1 + 8 * v3 + 15) = v6;
                *(uint32_t *)(pArg1 + 8 * v3 + 19) = sub_4423D0(v22);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[move variable 2]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v7 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v22 = nullptr;  // v22 = nullptr 空指针
                *(uint32_t *)(pArg1 + 8 * v3 + 39) = v7;
                *(uint32_t *)(pArg1 + 8 * v3 + 43) = sub_4423D0(v22);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[changing term]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 63) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[changing type]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                j = v29;
                sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v29, "[keep changing]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 67) = 0;  // 写字段 pArg1+67（nPeriodMs） ← 0
                }
                else if ( (uint8_t)sub_423300(v29, "[keep last value]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 67) = 1;  // 写字段 pArg1+67（nPeriodMs） ← 1
                }
                else if ( (uint8_t)sub_423300(v29, "[ping pong]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 67) = 2;  // 写字段 pArg1+67（nPeriodMs） ← 2
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[gravity]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 68) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[rotation angle]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v8 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v22 = nullptr;  // v22 = nullptr 空指针
                *(uint32_t *)(pArg1 + 72) = v8;  // 写字段 pArg1+72（nSnapshot72） ← v8
                v9 = sub_4423D0(v22);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v21 = nullptr;  // v21 = nullptr 空指针
                *(uint32_t *)(pArg1 + 76) = v9;  // 写字段 pArg1+76（szEmblemPath） ← v9
                *(uint32_t *)(pArg1 + 80) = sub_4423D0(v21);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[life time]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 85) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[landing type]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                j = v29;
                sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v29, "[pierce]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 89) = 0;  // 写字段 pArg1+89（nLifetime） ← 0
                }
                else if ( (uint8_t)sub_423300(v29, "[slide]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 89) = 1;  // 写字段 pArg1+89（nLifetime） ← 1
                }
                else if ( (uint8_t)sub_423300(v29, "[stop]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 89) = 2;  // 写字段 pArg1+89（nLifetime） ← 2
                }
                else if ( (uint8_t)sub_423300(v29, "[vanish]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 89) = 3;  // 写字段 pArg1+89（nLifetime） ← 3
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[transparent value]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v10 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v22 = nullptr;  // v22 = nullptr 空指针
                *(uint32_t *)(pArg1 + 90) = v10;  // 写字段 pArg1+90 ← v10
                *(uint32_t *)(pArg1 + 94) = sub_4423D0(v22);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[creation frequency]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(float *)(pArg1 + 100) = sub_442480(nullptr);  // sub_442480 —— 脚本 token 数值解析（double 版）
              }
              else if ( (uint8_t)sub_423300(&v33, "[maximum create number]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 104) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[maximum create time]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 108) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[create area size]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v11 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v22 = nullptr;  // v22 = nullptr 空指针
                *(uint32_t *)(pArg1 + 112) = v11;  // 写字段 pArg1+112（pHostComp） ← v11
                v12 = sub_4423D0(v22);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v21 = nullptr;  // v21 = nullptr 空指针
                *(uint32_t *)(pArg1 + 116) = v12;  // 写字段 pArg1+116（pSessionCtx） ← v12
                *(uint32_t *)(pArg1 + 120) = sub_4423D0(v21);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[create area rotation angle]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v13 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v22 = nullptr;  // v22 = nullptr 空指针
                *(uint32_t *)(pArg1 + 124) = v13;  // 写字段 pArg1+124（pAuraAnim） ← v13
                v14 = sub_4423D0(v22);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v21 = nullptr;  // v21 = nullptr 空指针
                *(uint32_t *)(pArg1 + 128) = v14;  // 写字段 pArg1+128（szStatusKeyBuf） ← v14
                *(uint32_t *)(pArg1 + 132) = sub_4423D0(v21);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[rotation angle range type]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                j = v29;
                sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v29, "[rectangle]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 136) = 0;  // 写字段 pArg1+136（nCtx136） ← 0
                }
                else if ( (uint8_t)sub_423300(v29, "[circle]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 136) = 1;  // 写字段 pArg1+136（nCtx136） ← 1
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[rotation angle variable]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v15 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v22 = nullptr;  // v22 = nullptr 空指针
                *(uint32_t *)(pArg1 + 140) = v15;  // 写字段 pArg1+140（nAdd140） ← v15
                *(uint32_t *)(pArg1 + 144) = sub_4423D0(v22);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[random range]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 148) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[display effect rate]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v16 = (int *)(pArg1 + 156);
                for ( i = 3; i != 0; --i )  // 遍历计次循环（i != 0）
                  *v16++ = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v3 = v26;
              }
              else if ( (uint8_t)sub_423300(&v33, "[create pos correct]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 152) = sub_4423D0(nullptr) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v33, "[object type]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                j = v29;
                sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v29, "[animation]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 172) = 2;  // 写字段 pArg1+172（pAppendVecEnd） ← 2
                }
                else if ( (uint8_t)sub_423300(v29, "[passive object]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 172) = 33;  // 写字段 pArg1+172（pAppendVecEnd） ← 33
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[how to create object]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                j = v29;
                sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v29, "[randomize]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 168) = 1;  // 写字段 pArg1+168（pAppendVec） ← 1
                }
                else if ( (uint8_t)sub_423300(v29, "[in order]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 168) = 0;  // 写字段 pArg1+168（pAppendVec） ← 0
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[object]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_428480(pArg1 + 180);  // sub_428480 —— 32B 元素容器清空
                for ( j = v29; sub_443370() != 0; j = v29 )  // sub_443370 —— [name] → 对象+0x04 名称串
                {
                  sub_5006B0(v27);  // 调 sub_5006B0
                  LOBYTE(v38) = 2;  // 调 取 16 位值低 8 位
                  sub_4014D0((std::_String_base *)v27, v29, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
                  v28 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  sub_500AC0(v27);  // 调 sub_500AC0
                  LOBYTE(v38) = 1;  // 调 取 16 位值低 8 位
                  sub_501490(v27);  // 调 sub_501490
                }
              }
              else if ( (uint8_t)sub_423300(&v33, "[layer]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                j = v29;
                sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                p_Block = Block;
                if ( v32 < 0x10 )
                  p_Block = &Block;
                *(uint32_t *)(pArg1 + 176) = sub_4425F0(p_Block);  // sub_4425F0 —— 场景前景/背景档位标签→索引
              }
              else
              {
                v25 = v20;
                sub_401690(&v33);  // sub_401690 —— std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全量赋值）
                if ( (uint8_t)sub_442C80(  // sub_442C80 —— 行首是 [ 仍未匹配
                                        (char)v20[0],
                                        v20[1],
                                        (int)v20[2],
                                        (int)v20[3],
                                        (int)v21,
                                        (int)v22,
                                        (int)j) == 0 )  // 对象创建/运动定义解析器（PassiveObject 生成器，[creation pos] 族）
                {
                  v19 = (const char *)v34;
                  if ( v36 < 0x10 )
                    v19 = (const char *)&v34;
                  off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, v19);  // off_77F3FC —— 日志打印（printf 风格）
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
        v4 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v22 = nullptr;  // v22 = nullptr 空指针
        *(uint32_t *)pArg1 = v4;
        v5 = sub_4423D0(v22);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v21 = nullptr;  // v21 = nullptr 空指针
        *(uint32_t *)(pArg1 + 4) = v5;  // 写字段 pArg1+4（pHostObj） ← v5
        *(uint32_t *)(pArg1 + 8) = sub_4423D0(v21);  // sub_4423D0 —— [LOOP] → 动画对象+160
      }
    }
    if ( v32 >= 0x10 )
      j__free(Block);  // 释放堆块
    v32 = 15;
    v31 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    if ( v36 >= 0x10 )
      j__free(v34);  // 释放堆块
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5013F0 sub_5013F0
//   百分比计算：nArg2 * 0.01 * nArg1，向下clamp到最小 1（掉率/概率换算用），
//   返回值按 uint64 截断（Hex-Rays 把 int 返回值展示为 64 位）。
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
//   std::plus<int> 函数对象实例：返回 nArg1 + nArg2。
// ------------------------------------------------------------
int /*cdecl*/ sub_501420(int nArg1, int nArg2)
{
  return nArg1 + nArg2;
}



// ------------------------------------------------------------
// 0x501430 sub_501430
//   std::map 迭代器 _Dec()（quest/PO 侧 string 树，_Isnil @+0x2D）：移动到前驱。
// ------------------------------------------------------------
int /*thiscall*/ sub_501430(void *this)  // sub_501430 —— 调 sub_501430
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 45) != 0 )  // 若 *(uint8_t *)(*(uint32_t *)this + 45) != 0
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 45) != 0 )  // 若 *(uint8_t *)(*v1 + 45) != 0
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 45) == 0 )  // 若 *(uint8_t *)(result + 45) == 0
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )  // 若 *(uint32_t *)this != *(uint32_t *)result
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);  // 读字段 result = result+4（pHostObj）
        }
        while ( *(uint8_t *)(result + 45) == 0 );  // 写字段 result+45 ← = 0 )
        if ( *(uint8_t *)(result + 45) == 0 )  // 若 *(uint8_t *)(result + 45) == 0
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 45) == 0; result = *(uint32_t *)(result + 8) )  // 读字段 result = v3+8（nSkillRec8）
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x501490 sub_501490
//   std::string 析构（本条目串：数据@+4/长度@+20/容量@+24）：容量 ≥0x10 时
//   释放堆缓冲并复位 SSO 空串。
// ------------------------------------------------------------
void /*thiscall*/ sub_501490(void **this)  // 函数: 释放后返回
{
  if ( (unsigned int)*(this + 6) >= 0x10 )  // 若 (unsigned int)*(this + 6) >= 0x10
    j__free(*(this + 1));  // 释放堆块
  *(this + 6) = (void *)15;  // 写字段 this+6 ← (void *)15
  *(this + 5) = nullptr;  // 写字段 this+5 ← nullptr
  *((uint8_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
}



// ------------------------------------------------------------
// 0x5014C0 sub_5014C0
//   std::string 析构（另一槽位串：数据@+16/长度@+32/容量@+36）：同 501490。
// ------------------------------------------------------------
void /*thiscall*/ sub_5014C0(void **this)  // sub_5014C0 —— 调 sub_5014C0
{
  if ( (unsigned int)*(this + 9) >= 0x10 )  // 若 (unsigned int)*(this + 9) >= 0x10
    j__free(*(this + 4));  // 释放堆块
  *(this + 9) = (void *)15;  // 写字段 this+9 ← (void *)15
  *(this + 8) = nullptr;  // 写字段 this+8（nSkillRec8） ← nullptr
  *((uint8_t *)this + 16) = 0;  // 写字段 this+16（nChannelTypeSel）
}



// ------------------------------------------------------------
// 0x5014F0 sub_5014F0
//   std::map<std::string,...> 边界查找：sub_65DCE0 按 key（字符串，行数据）下行
//   到节点；节点为头或 key 大于给定串（sub_40BF00 比较）→ 返回树起始节点，
//   否则返回命中节点（upper_bound 语义【推断】）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5014F0(uint32_t *this, uint32_t *uArg2, unsigned int *pDwArg3)
{
  uint32_t *v5; // eax
  unsigned int v6; // ecx
  const char *v7; // eax
  uint32_t *v9; // [esp+18h] [ebp+Ch]

  v5 = (uint32_t *)sub_65DCE0(pDwArg3);  // sub_65DCE0 —— 字符串键在红黑树中定位（逐字节 memcmp，右侧插入语义）
  v9 = v5;
  if ( v5 == (uint32_t *)*(this + 1)  // 若 v5 == (uint32_t *)*(this + 1
    || ((v6 = v5[8], v5[9] < 0x10u) ? (v7 = (const char *)(v5 + 4)) : (v7 = (const char *)v5[4]),
        sub_40BF00((std::_String_base *)pDwArg3, 0, pDwArg3[5], v7, v6) < 0) )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    *uArg2 = *(this + 1);  // *uArg2 写入 *(this + 1)
    return uArg2;
  }
  else
  {
    *uArg2 = v9;  // *uArg2 写入 v9
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x501560 sub_501560
//   std::vector<int>::insert(pos, n, val*)（4 字节元素，+4 begin/+8 end/+12 capEnd）：
//   容量够 → 尾部腾位（55E7F0/5DAF70/523700/49A9D0）；不足 → 扩容三段拷贝重建。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_501560(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 函数: 释放后返回
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

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;  // this+12 物品类型号
  else
    result = 0;  // result=this+12 物品类型号
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
    else
      fld_8 = 0;  // fld_8=this+8 物品 id
    if ( 0x3FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 物品 id
      sub_47F990(this);  // 调 sub_47F990
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
    else
      fld_82 = 0;  // fld_82=this+8 物品 id
    if ( result >= uArg3 + fld_82 )  // result=this+12 物品类型号
    {
      fld_83 = *(uint8_t **)(this + 8);  // this+8 物品 id
      v21 = (int)&fld_83[-Src] >> 2;  // fld_83=this+8 物品 id
      v22 = 4 * uArg3;  // 计算 v22 = 4 * uArg3
      v29 = (int)fld_83;  // fld_83=this+8 物品 id
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];  // fld_83=this+8 物品 id
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // sub_55E7F0 —— 商城状态（10 行）
        sub_5DAF70((void *)Src, v24, v29);  // sub_5DAF70 —— 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // sub_49A9D0 —— 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // sub_55E7F0 —— 商城状态（10 行）
        sub_523700(*(uint32_t **)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // sub_523700 —— 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;  // 写字段 this+8（nSkillRec8） ← fld_84
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // sub_49A9D0 —— 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )  // 若 0x3FFFFFFF - (result >> 1) >= result
        v10 = (result >> 1) + result;  // result=this+12 物品类型号
      else
        v10 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
      else
        fld_85 = 0;  // fld_85=this+8 物品 id
      if ( v10 < uArg3 + fld_85 )  // fld_85=this+8 物品 id
      {
        if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
        else
          fld_86 = 0;  // fld_86=this+8 物品 id
        v10 = uArg3 + fld_86;  // 计算 v10 = uArg3 + fld_86
      }
      v28 = 4 * v10;  // 计算 v28 = 4 * v10
      pMem = (char *)operator new(4 * v10);  // 堆分配
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);  // this+4 宿主对象
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+4 宿主对象
      v15 = sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // sub_523700 —— 填充补足尾段
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // this+8 物品 id
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8 物品 id
      else
        fld_87 = 0;  // fld_87=this+8 物品 id
      v18 = fld_87 + uArg3;  // 计算 v18 = fld_87 + uArg3
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &pMem[v28];  // 写字段 this+12（nSkillRec12） ← &pMem[v28]
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // 写字段 this+8（nSkillRec8） ← &pMem[4 * v18]
      *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
      return (unsigned int)pMem;
    }
  }
  return result;  // result=this+12 物品类型号
}


// ------------------------------------------------------------
// 0x501740 sub_501740
//   std::vector<12字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（59EE30/504450/5E51C0/5043B0 搬运）；不足 → 扩容三段拷贝重建。
// ------------------------------------------------------------
int /*thiscall*/ sub_501740(int *this, char *pszArg2, unsigned int uArg3, int *Block)  // 函数: 释放后返回
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    result = 715827883 * (*(this + 3) - fld_e1);  // this+12 = 技能槽记录次字
    fld_e3 = (*(this + 3) - fld_e1) / 12;  // this+12 = 技能槽记录次字
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_47F990(this);  // 调 sub_47F990
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
      Blockb = fld_e23;
      if ( ((char *)fld_e23 - pszArg2) / 12 >= uArg3 )
      {
        v27 = &fld_e23[-3 * uArg3];
        *(this + 2) = (int)sub_59EE30(v27, fld_e23, fld_e23);  // sub_59EE30 —— 三元组块搬移辅助
        sub_504450(pszArg2, v27, Blockb);  // sub_504450 —— 搬移插入位后元素
        return sub_5043B0(pszArg2, &pszArg2[12 * uArg3], v25);  // sub_5043B0 —— 在插入位填 n 条
      }
      else
      {
        sub_59EE30(pszArg2, fld_e23, &pszArg2[12 * uArg3]);  // sub_59EE30 —— 三元组块搬移辅助
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 12;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);  // sub_5E51C0 —— 填充补足尾段
        fld_e26 = 12 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        return sub_5043B0(pszArg2, fld_e26 - 12 * uArg3, v25);  // sub_5043B0 —— 在插入位填 n 条
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )  // 若 357913941 - (fld_e3 >> 1) >= fld_e3
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);  // sub_4DA030 —— v13 = 插入数 + sub_4DA030（当前数）
      v15 = 3 * v13;  // 计算 v15 = 3 * v13
      Blocka = operator new(12 * v13);  // 堆分配
      fld_e12 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pszArg2, Blocka);  // sub_59EE30 —— 三元组块搬移辅助
      sub_623C10(v28, uArg3, v25);  // sub_623C10 —— 就地构造（拷贝构造 1 个）
      sub_59EE30(pszArg2, (uint32_t *)*(this + 2), &v28[3 * uArg3]);  // sub_59EE30 —— 三元组块搬移辅助
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 12;  // this+8 = 技能槽记录首字
      v17 = fld_e13 + uArg3;  // 计算 v17 = fld_e13 + uArg3
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 释放堆块
      *(this + 3) = (int)&Blocka[v15];  // 写字段 this+3 ← (int)&Blocka[v15]
      *(this + 2) = (int)&Blocka[3 * v17];  // 写字段 this+2 ← (int)&Blocka[3 * v17]
      *(this + 1) = (int)Blocka;  // 写字段 this+1 ← (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5019F0 sub_5019F0
//   std::map::erase(iterator) 本体：摘除节点并做红黑回平衡（红黑标志 @节点+0x2C、
//   _Isnil @+0x2D；旋转 sub_442AC0/sub_433290）。迭代器为 nil 时抛
//   "invalid map/set<T> iterator"（out_of_range）。
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
  if ( *((uint8_t *)pDwArg3 + 45) != 0 )  // 若 *((uint8_t *)pDwArg3 + 45) != 0
  {
    v25 = 15;
    v24 = 0;
    v23 = 0;
    sub_4015C0(&v22, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v29 = 0;
    sub_401740(pExceptionObject, &v22);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::out_of_range::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_40BEA0((int *)&pDwArg3);  // sub_40BEA0 —— 红黑树迭代器自增（后继；哨兵位 +45）
  if ( *((uint8_t *)*pDwArg32 + 45) != 0 )  // 若 *((uint8_t *)*pDwArg32 + 45) != 0
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 45) == 0 )  // 若 *((uint8_t *)v4 + 45) == 0
      v4[1] = (int)v6;  // v4[1] 写入 (int)v6
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )  // 若 *(int ***)(v8 + 4) == pDwArg32
    {
      *(uint32_t *)(v8 + 4) = v4;  // 写字段 v8+4（pHostObj） ← v4
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;  // *v6 写入 (int)v4
    }
    else
    {
      v6[2] = (int)v4;  // v6[2] 写入 (int)v4
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )  // 若 *(int ***)pThis2[1] == pDwArg32
    {
      if ( *((uint8_t *)v4 + 45) != 0 )  // 若 *((uint8_t *)v4 + 45) != 0
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_6600D0(v4);  // sub_6600D0 —— 红黑树最小结点（沿左子下行，哨兵位 +45）
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;  // 写字段 v10+8（nSkillRec8） ← = (uint32_t)pDwArg32
    v26 = v10;
    if ( v11 )  // 若 v11
    {
      if ( *((uint8_t *)v4 + 45) != 0 )  // 若 *((uint8_t *)v4 + 45) != 0
        *(uint32_t *)(v10 + 8) = v6;  // 写字段 v10+8（nSkillRec8） ← v6
      else
        *(uint32_t *)(v26 + 8) = sub_4429F0(v4);  // sub_4429F0 —— v25+8 = sub_4429F0(v4)
    }
    goto LABEL_35;  // 跳转 LABEL_35
  }
  if ( *((uint8_t *)pDwArg32[2] + 45) != 0 )  // 若 *((uint8_t *)pDwArg32[2] + 45) != 0
  {
    v4 = *pDwArg32;
    goto LABEL_8;  // 跳转 LABEL_8
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;  // 跳转 LABEL_8
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;  // *v5 写入 (int)*pDwArg32
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 45) == 0 )  // 若 *((uint8_t *)v4 + 45) == 0
      v4[1] = (int)v6;  // v4[1] 写入 (int)v6
    *v6 = (int)v4;  // *v6 写入 (int)v4
    v5[2] = (int)pDwArg32[2];  // v5[2] 写入 (int)pDwArg32[2]
    pDwArg32[2][1] = (int)v5;  // pDwArg32[2][1] 写入 (int)v5
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )  // 若 *(int ***)(v12 + 4) == pDwArg32
  {
    *(uint32_t *)(v12 + 4) = v5;  // 写字段 v12+4（pHostObj） ← v5
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )  // 若 *v13 == (int *)pDwArg32
      *v13 = v5;  // *v13 写入 v5
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];  // v5[1] 写入 (int)pDwArg32[1]
  v14 = *((uint8_t *)v5 + 44);  // 读字段 v14 = v5+44（nExpireMs）
  *((uint8_t *)v5 + 44) = *((uint8_t *)pDwArg32 + 44);  // 写字段 v5+44（nExpireMs）
  *((uint8_t *)pDwArg32 + 44) = v14;  // 写字段 pDwArg32+44（nExpireMs）
LABEL_35:
  v15 = (void **)Block;
  if ( *((uint8_t *)Block + 44) == 1 )  // 若 *((uint8_t *)Block + 44) == 1
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )  // 若 v4 != *(int **)(pThis[1] + 4)
    {
      do
      {
        if ( *((uint8_t *)v4 + 44) != 1 )  // 若 *((uint8_t *)v4 + 44) != 1
          break;
        v17 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )  // 若 v4 == (int *)*v6
        {
          v17 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v17 + 44) == 0 )  // 若 *((uint8_t *)v17 + 44) == 0
          {
            *((uint8_t *)v17 + 44) = 1;  // 写字段 v17+44（nExpireMs）
            *((uint8_t *)v6 + 44) = 0;  // 写字段 v6+44（nExpireMs）
            sub_442AC0(v6);  // sub_442AC0 —— 调 sub_442AC0
            v17 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )  // 若 *((uint8_t *)v17 + 45) != 0
            goto LABEL_53;  // 跳转 LABEL_53
          if ( *(uint8_t *)(*v17 + 44) != 1 || *(uint8_t *)(v17[2] + 44) != 1 )  // 若 *(uint8_t *)(*v17 + 44) != 1 || *(uint8_t *)(v17[2] + 44) != 1
          {
            if ( *(uint8_t *)(v17[2] + 44) == 1 )  // 若 *(uint8_t *)(v17[2] + 44) == 1
            {
              *(uint8_t *)(*v17 + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;  // 写字段 v17+44（nExpireMs）
              sub_433290(v17);  // sub_433290 —— 红黑树右旋（节点 0x30 版）
              v17 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);  // 写字段 v17+44（nExpireMs）
            *((uint8_t *)v6 + 44) = 1;  // 写字段 v6+44（nExpireMs）
            *(uint8_t *)(v17[2] + 44) = 1;
            sub_442AC0(v6);  // sub_442AC0 —— 调 sub_442AC0
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v17 + 44) == 0 )  // 若 *((uint8_t *)v17 + 44) == 0
          {
            *((uint8_t *)v17 + 44) = 1;  // 写字段 v17+44（nExpireMs）
            *((uint8_t *)v6 + 44) = 0;  // 写字段 v6+44（nExpireMs）
            sub_433290(v6);  // sub_433290 —— 红黑树右旋（节点 0x30 版）
            v17 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )  // 若 *((uint8_t *)v17 + 45) != 0
            goto LABEL_53;  // 跳转 LABEL_53
          if ( *(uint8_t *)(v17[2] + 44) != 1 || *(uint8_t *)(*v17 + 44) != 1 )  // 若 *(uint8_t *)(v17[2] + 44) != 1 || *(uint8_t *)(*v17 + 44) != 1
          {
            if ( *(uint8_t *)(*v17 + 44) == 1 )  // 若 *(uint8_t *)(*v17 + 44) == 1
            {
              *(uint8_t *)(v17[2] + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;  // 写字段 v17+44（nExpireMs）
              sub_442AC0(v17);  // sub_442AC0 —— 调 sub_442AC0
              v17 = (uint32_t *)*v6;
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);  // 写字段 v17+44（nExpireMs）
            *((uint8_t *)v6 + 44) = 1;  // 写字段 v6+44（nExpireMs）
            *(uint8_t *)(*v17 + 44) = 1;
            sub_433290(v6);  // sub_433290 —— 红黑树右旋（节点 0x30 版）
            break;
          }
        }
        *((uint8_t *)v17 + 44) = 0;  // 写字段 v17+44（nExpireMs）
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );  // 当 !v11 循环
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 44) = 1;  // 写字段 v4+44（nExpireMs）
  }
  if ( (unsigned int)v15[9] >= 0x10 )  // 若 (unsigned int)v15[9] >= 0x10
    j__free(v15[4]);  // 释放堆块
  Block2 = Block;
  *((uint32_t *)Block + 9) = 15;  // 写字段 Block[9]（宽4字节）
  Block2[8] = 0;
  *((uint8_t *)Block2 + 16) = 0;  // 写字段 Block2+16（nChannelTypeSel）
  j__free(Block2);  // 释放堆块
  v19 = pThis[2];
  if ( v19 != 0 )
    pThis[2] = v19 - 1;  // pThis[2] 写入 v19 - 1
  *uArg2 = pDwArg3;  // *uArg2 写入 pDwArg3
  return uArg2;
}


// ------------------------------------------------------------
// 0x501CD0 sub_501CD0
//   std::map 树节点堆构造（0x30 字节，值构造转 sub_40C300），供 501E20 插入用
//   （+0x2C = 红黑标志字节 pszArg5，恒 0）。
// ------------------------------------------------------------
void */*stdcall*/ sub_501CD0(int nArg1, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  void *pMem; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  pMem = operator new(0x30u);  // 堆分配
  v7[4] = pMem;
  v7[8] = (void *)1;  // v7[8] 写入 (void *)1
  v7[3] = pMem;
  if ( pMem != nullptr )
    sub_40C300(nArg1, nArg2, nArg3, nArg4, pszArg5);  // sub_40C300 —— 树结点值构造（键串 + 坐标三元 + 颜色标记）
  return pMem;
}



// ------------------------------------------------------------
// 0x501D60 sub_501D60
//   递归释放整棵 map 树（_Isnil @+0x2D）：先递归右子树，再析构节点内字符串
//   （sub_5014C0）并 free 节点。
// ------------------------------------------------------------
char /*stdcall*/ sub_501D60(void **Block)  // 函数: 释放后返回
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 45);  // 读字段 result = Block[45]
  for ( i = Block; result == 0; Block2 = i )  // 循环：i = Block; result == 0; Block2 = i
  {
    sub_501D60(i[2]);  // 调 sub_501D60
    i = (void **)*i;
    sub_5014C0(Block2);  // sub_5014C0 —— 调 sub_5014C0
    j__free(Block2);  // 释放堆块
    result = *((uint8_t *)i + 45);  // 读字段 result = i[45]
  }
  return result;
}



// ------------------------------------------------------------
// 0x501DB0 sub_501DB0
//   std::vector<12字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_501740 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_501DB0(int *this, uint32_t *uArg2, int nArg3, int *Block)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (nArg3 - fld_e1) / 12;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_501740(this, nArg3, 1u, Block);  // 调 sub_501740
  *uArg2 = *(this + 1) + 12 * v6;  // *uArg2 写入 *(this + 1) + 12 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x501E20 sub_501E20
//   std::map::insert 本体（string key 树，红黑标志 @节点+0x2C）：sub_501CD0 建节点
//   → 挂树 → 回平衡（sub_442AC0/sub_433290 旋转）。
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

  if ( (unsigned int)*(this + 2) >= 0x7FFFFFE )  // 若 (unsigned int)*(this + 2) >= 0x7FFFFFE
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(pExceptionObject, (int)v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_501CD0(*(this + 1), (int)pArg4, *(this + 1), nArg5, 0);  // 调 sub_501CD0
  fld_e12 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8 = 技能槽记录首字
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4 = pHostObj
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;  // *pArg4 写入 fld_e1
    fld_e13 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
    if ( pArg4 == (uint32_t *)*fld_e13 )  // 若 pArg4 == (uint32_t *)*fld_e13
      *fld_e13 = fld_e1;  // *fld_e13 写入 fld_e1
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // 若 pArg4 == *(uint32_t **)(fld_e14 + 8)
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
  }
  v10 = fld_e1 + 1;  // 计算 v10 = fld_e1 + 1
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 44) == 0 )  // 若 *(uint8_t *)(fld_e1[1] + 44) == 0
  {
    while ( 1 )  // 当 1 循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )  // 若 *v10 == *v13
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 44) != 0 )  // 若 *(uint8_t *)(v14 + 44) != 0
        {
          if ( fld_e16 == (uint32_t *)v12[2] )  // 若 fld_e16 == (uint32_t *)v12[2]
          {
            fld_e16 = (uint32_t *)*v10;
            sub_442AC0(*v10);  // sub_442AC0 —— 调 sub_442AC0
          }
          *(uint8_t *)(fld_e16[1] + 44) = 1;
          *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
          sub_433290(*(uint32_t *)(fld_e16[1] + 4));  // sub_433290 —— 红黑树右旋（节点 0x30 版）
          goto LABEL_21;  // 跳转 LABEL_21
        }
      }
      else if ( *(uint8_t *)(v14 + 44) != 0 )  // 否则若 *(uint8_t *)(v14 + 44) != 0
      {
        if ( fld_e16 == (uint32_t *)*v12 )  // 若 fld_e16 == (uint32_t *)*v12
        {
          fld_e16 = (uint32_t *)*v10;
          sub_433290(*v10);  // sub_433290 —— 红黑树右旋（节点 0x30 版）
        }
        *(uint8_t *)(fld_e16[1] + 44) = 1;
        *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
        sub_442AC0(*(uint32_t *)(fld_e16[1] + 4));  // sub_442AC0 —— 调 sub_442AC0
        goto LABEL_21;  // 跳转 LABEL_21
      }
      *(uint8_t *)(*v10 + 44) = 1;
      *(uint8_t *)(v14 + 44) = 1;  // 写字段 v14+44（nExpireMs） ← 1
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 44) = 0;
      fld_e16 = *(uint32_t **)(*v10 + 4);
LABEL_21:
      v10 = fld_e16 + 1;  // 计算 v10 = fld_e16 + 1
      if ( *(uint8_t *)(fld_e16[1] + 44) != 0 )  // 若 *(uint8_t *)(fld_e16[1] + 44) != 0
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 44) = 1;  // this+4 = pHostObj
  *uArg2 = fld_e1;  // *uArg2 写入 fld_e1
  return uArg2;
}


// ------------------------------------------------------------
// 0x501FD0 sub_501FD0
//   std::copy_backward（44 字节元素版，元素 = {int, 3 个 std::string@+8/+12/+28}）：
//   从尾往头逐 0x2C 字节搬移，字符串经 41B0D0/4800C0/480210 拷贝构造
//   （任务/掉落名称条目的腾位子例程【推断】）。
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
    *uArg32 = v5;  // *uArg32 写入 v5
    uArg32[1] = *(uint32_t *)(nArg22 + 4);  // uArg32[1] 写入 *(uint32_t *)(nArg22 + 4)
    sub_41B0D0(nArg22 + 8);  // sub_41B0D0 —— 驻留句柄赋值（旧引用释放 + 新引用 ++）
    sub_4800C0(nArg22 + 12);  // sub_4800C0 —— 8 字节元素容器区间赋值（三分支容量策略）
    sub_480210(nArg22 + 28);  // sub_480210 —— 4 字节元素容器区间赋值（与 ·0x4800C0 同构）
  }
  while ( nArg22 != nArg1 );  // 循环直到 nArg22 != nArg1
  return uArg32;
}



// ------------------------------------------------------------
// 0x502030 sub_502030
//   定义对象重置：+0x08 字符串置空（41BFE0）、+0x10/+0x20 两个容器清空释放、
//   +0x00/+0x04 计数清零、+0x10 串经 41B010 析构。
// ------------------------------------------------------------
char */*thiscall*/ sub_502030(char *this)
{
  void **pThis_8; // ebx

  pThis_8 = (void **)(this + 8);  // this+8 物品 id
  *((uint32_t *)this + 2) = 0;  // 写字段 this[2]（宽4字节）
  sub_41BFE0((void **)this + 2, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 5) = 0;  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 6) = 0;  // 写字段 this[6]（宽4字节）
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 0;  // 写字段 this[1]（宽4字节）
  sub_41B010(pThis_8);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  if ( *((uint32_t *)this + 4) != 0 )  // 若 *((uint32_t *)this + 4) != 0
    j__free(*((void **)this + 4));  // 释放堆块
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 5) = 0;  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 6) = 0;  // 写字段 this[6]（宽4字节）
  if ( *((uint32_t *)this + 8) != 0 )  // 若 *((uint32_t *)this + 8) != 0
    j__free(*((void **)this + 8));  // 释放堆块
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  return this;
}



// ------------------------------------------------------------
// 0x5020D0 sub_5020D0
//   std::vector<int>::push_back（4 字节元素）：容量够 → 在 +8 end 直写；
//   不够 → 转调 sub_501560 插入路径扩容。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5020D0(int *this, int *pDwArg2)
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 2;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2 )  // fld_e1=this+4 宿主对象
    return sub_501560((int)this, *(this + 2), 1u, pDwArg2);  // 调 sub_501560
  fld_e22 = (int *)*(this + 2);  // this+8 = 技能槽记录首字
  *fld_e22 = *pDwArg2;  // *fld_e22 写入 *pDwArg2
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;  // 写字段 this+2 ← result
  return result;
}



// ------------------------------------------------------------
// 0x502120 sub_502120
//   std::vector<12字节元素>::push_back：容量够 → 在 +8 end 直写（623C10 构造）；
//   不够 → 转调 sub_501DB0 插入路径扩容。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_502120(int *this, int *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 12 )  // fld_e1=this+4 宿主对象
    return sub_501DB0(this, &Block, *(this + 2), Block);  // 调 sub_501DB0
  fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
  result = (uint32_t *)sub_623C10(fld_e22, 1, Block);  // sub_623C10 —— 就地构造（拷贝构造 1 个）
  *(this + 2) = fld_e22 + 12;  // 写字段 this+2 ← fld_e22 + 12
  return result;
}



// ------------------------------------------------------------
// 0x5021A0 sub_5021A0
//   std::map<std::string,...>::insert(unique) 前半：沿树按字符串 key 下行
//   （memcmp 语义，节点 key 串 @节点+16/长度@+32），已存在 → {已有,false}；
//   否则转 sub_501E20 插入。
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

  fld_e1 = *(uint32_t *)(*(this + 1) + 4);  // this+4 = pHostObj
  fld_e12 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  v5 = 1;
  pArg32 = pArg3;
  pThis = this;
  v21 = 1;
  if ( *(uint8_t *)(fld_e1 + 45) == 0 )  // 若 *(uint8_t *)(fld_e1 + 45) == 0
  {
    for ( i = pArg3[5]; ; i = pArg3[5] )  // 循环：i = pArg3[5]; ; i = pArg3[5]
    {
      v8 = *(uint32_t *)(fld_e1 + 32);  // 读字段 v8 = fld_e1+32（nHeight）
      v19 = (uint32_t *)fld_e1;
      if ( *(uint32_t *)(fld_e1 + 36) < 0x10u )  // 若 *(uint32_t *)(fld_e1 + 36) < 0x10u
        v9 = (const char *)(fld_e1 + 16);
      else
        v9 = *(const char **)(fld_e1 + 16);
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )
        goto LABEL_16;  // 跳转 LABEL_16
      if ( v10 < v8 )
        v8 = v10;
      v11 = pArg32[6] < 0x10u ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];  // v11 = pArg32[6] < 0x10u ? (const char]
      nCmp = memcmp(v11, v9, v8);  // 调 memcmp 内存比较
      v13 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )
      {
LABEL_16:
        v14 = *(uint32_t *)(fld_e1 + 32);  // 读字段 v14 = fld_e1+32（nHeight）
        if ( v10 >= v14 )
          v15 = v10 != v14;
        else
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      fld_e1 = v13 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);
      if ( *(uint8_t *)(fld_e1 + 45) != 0 )  // 若 *(uint8_t *)(fld_e1 + 45) != 0
        break;
    }
    fld_e12 = v19;
    this = pThis;
  }
  fld_e122 = fld_e12;
  pArg3 = fld_e12;
  if ( v5 != 0 )
  {
    if ( fld_e12 == *(uint32_t **)*(this + 1) )  // 若 fld_e12 == *(uint32_t **)*(this + 1)
    {
      *(uint32_t *)pArg2 = *sub_501E20(this, &pArg3, 1, fld_e12, (int)pArg32);
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      return pArg2;
    }
    sub_501430(&pArg3);  // sub_501430 —— 调 sub_501430
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10u )  // 若 pArg32[6] < 0x10u
    v18 = (const char *)(pArg32 + 1);
  else
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    *(uint32_t *)pArg2 = fld_e122;
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
  }
  else
  {
    *(uint32_t *)pArg2 = *sub_501E20(pThis, &pArg3, v21, fld_e12, (int)pArg32);
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x502300 sub_502300
//   std::map::erase(first, last)（string key 树）：first=begin 且 last=end 时整树
//   清空（sub_501D60 递归释放并复位哨兵）；否则逐节点转 sub_5019F0 擦除。
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
  fld_e1 = (int)*(this + 1);  // this+4 = pHostObj
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )  // 若 pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1
  {
    sub_501D60(*(void ***)(fld_e1 + 4));  // 调 sub_501D60
    (*(this + 1))[1] = (int *)*(this + 1);  // this+4 = pHostObj
    fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
    *(this + 2) = nullptr;  // 写字段 this+2 ← nullptr
    *fld_e12 = fld_e12;  // *fld_e12 写入 fld_e12
    (*(this + 1))[2] = (int *)*(this + 1);  // this+4 = pHostObj
    *pDwArg2 = **(this + 1);  // *pDwArg2 写入 **(this + 1)
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 45) == 0 )  // 若 *((uint8_t *)pDwArg32 + 45) == 0
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 45) != 0 )  // 若 *((uint8_t *)v11 + 45) != 0
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 45) == 0; i = (int *)i[1] )  // 循环：i = (int *)pDwArg32[1]; *((uint8_t *)i + 45) == 0; i = (int 
            {
              if ( pDwArg32 != (int *)i[2] )  // 若 pDwArg32 != (int *)i[2]
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 45) == 0; j = (int *)*j )  // 循环：j = *v11; *((uint8_t *)j + 45) == 0; j = (int *)*j
              pDwArg32 = j;
          }
        }
        sub_5019F0(this, (int ***)&pDwArg3, v10);  // 调 sub_5019F0
      }
      while ( pDwArg32 != pDwArg42 );  // 循环直到 pDwArg32 != pDwArg42
    }
    *pDwArg2 = pDwArg32;  // *pDwArg2 写入 pDwArg32
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x5023C0 sub_5023C0
//   std::copy（44 字节元素版，正向）：逐元素拷贝 int 与 3 个字符串
//   （41B0D0/4800C0/480210 拷贝构造）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_5023C0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 11 )  // 循环：i = uArg1; i != uArg2; i += 11
  {
    *i = *pArg3;  // *i 写入 *pArg3
    i[1] = pArg3[1];  // i[1] 写入 pArg3[1]
    sub_41B0D0(pArg3 + 2);  // sub_41B0D0 —— 驻留句柄赋值（旧引用释放 + 新引用 ++）
    sub_4800C0(pArg3 + 3);  // sub_4800C0 —— 8 字节元素容器区间赋值（三分支容量策略）
    sub_480210(pArg3 + 7);  // sub_480210 —— 4 字节元素容器区间赋值（与 ·0x4800C0 同构）
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x502410 sub_502410
//   std::copy_backward（44 字节元素版）：转调 sub_501FD0。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_502410(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_501FD0(nArg1, nArg2, uArg3);  // 调 sub_501FD0
}



// ------------------------------------------------------------
// 0x502430 sub_502430
//   std::map<std::string,...>::insert(hint)：用提示迭代器与前后邻居做串比较
//   （sub_40C160 = string less）定位插入点；邻居检查失败回退 sub_5021A0（LABEL_23）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_502430(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // edi
  uint32_t *pArg43; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // 若 *(uint32_t *)(this + 8) == 0
  {
    sub_501E20((int *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);  // 调 sub_501E20
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+4 宿主对象
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )  // 若 pArg3 == (uint32_t *)*fld_4
  {
    if ( (uint8_t)sub_40C160(pArg4, pArg3 + 3) != 0 )  // sub_40C160 —— map 键比较器（string < string，经 ·sub_40BF00）
    {
      sub_501E20((int *)this, uArg2, 1, pArg3, (int)pArg42);  // 调 sub_501E20
      return uArg2;
    }
    goto LABEL_23;  // 跳转 LABEL_23
  }
  if ( pArg3 == fld_4 )  // fld_4=this+4 宿主对象
  {
    if ( (uint8_t)sub_40C160(fld_4[2] + 12, pArg4) != 0 )  // sub_40C160 —— map 键比较器（string < string，经 ·sub_40BF00）
    {
      sub_501E20((int *)this, uArg2, 0, *(uint32_t **)(*(uint32_t *)(this + 4) + 8), (int)pArg42);  // 调 sub_501E20
      return uArg2;
    }
    goto LABEL_23;  // 跳转 LABEL_23
  }
  if ( (uint8_t)sub_40C160(pArg4, pArg3 + 3) != 0 )  // sub_40C160 —— map 键比较器（string < string，经 ·sub_40BF00）
  {
    pArg4 = pArg3;
    sub_501430(&pArg4);  // sub_501430 —— 调 sub_501430
    if ( (uint8_t)sub_40C160(pArg4 + 3, pArg42) != 0 )  // sub_40C160 —— map 键比较器（string < string，经 ·sub_40BF00）
    {
      if ( *(uint8_t *)(pArg4[2] + 45) != 0 )  // 若 *(uint8_t *)(pArg4[2] + 45) != 0
        sub_501E20((int *)this, uArg2, 0, pArg4, (int)pArg42);  // 调 sub_501E20
      else
        sub_501E20((int *)this, uArg2, 1, pArg3, (int)pArg42);  // 调 sub_501E20
      return uArg2;
    }
  }
  if ( (uint8_t)sub_40C160(pArg3 + 3, pArg42) == 0 )  // sub_40C160 —— map 键比较器（string < string，经 ·sub_40BF00）
    goto LABEL_23;  // 跳转 LABEL_23
  pArg4 = pArg3;
  sub_40BEA0(&pArg4);  // sub_40BEA0 —— 红黑树迭代器自增（后继；哨兵位 +45）
  pArg43 = pArg4;
  if ( pArg4 != *(uint32_t **)(this + 4) )  // 若 pArg4 != *(uint32_t **)(this + 4)
  {
    if ( (uint8_t)sub_40C160(pArg42, pArg4 + 3) != 0 )  // sub_40C160 —— map 键比较器（string < string，经 ·sub_40BF00）
    {
      pArg43 = pArg4;
      goto LABEL_19;  // 跳转 LABEL_19
    }
LABEL_23:
    v9 = *(uint32_t *)sub_5021A0((int *)this, (int)v10, pArg42);
    *uArg2 = v9;  // *uArg2 写入 v9
    return uArg2;
  }
LABEL_19:
  if ( *(uint8_t *)(pArg3[2] + 45) != 0 )  // 若 *(uint8_t *)(pArg3[2] + 45) != 0
    sub_501E20((int *)this, uArg2, 0, pArg3, (int)pArg42);  // 调 sub_501E20
  else
    sub_501E20((int *)this, uArg2, 1, pArg43, (int)pArg42);  // 调 sub_501E20
  return uArg2;
}



// ------------------------------------------------------------
// 0x5025D0 sub_5025D0
//   std::_Destroy（44 字节元素版）：对 [nArg1, nArg1+44*nArg2) 每个元素调
//   sub_480A90 析构（3 个字符串的析构）。
// ------------------------------------------------------------
void /*cdecl*/ sub_5025D0(int nArg1, int nArg2, int nArg3)  // 函数定义: 后返回 nArg1+44*nArg2 尾地址
{
  int nArg12; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  nArg12 = nArg1;
  v5[4] = v5;
  v5[3] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    LOBYTE(v6) = 1;  // 调 取 16 位值低 8 位
    if ( nArg12 != 0 )
      sub_480A90(nArg3);  // sub_480A90 —— 44 字节技能槽条目拷贝构造（含两内嵌列表）
    --nArg2;  // 计数自减 nArg2
    nArg12 += 44;
    LOBYTE(v6) = 0;  // 调 取 16 位值低 8 位
  }
}



// ------------------------------------------------------------
// 0x5026A0 sub_5026A0
//   std::map<std::string,...>::operator[]：按 key 下行查找（sub_65DCE0）；
//   没有 → 栈上构造 {key 串, 0, 0} 插入（sub_502430）后返回新值槽（节点+0x28）。
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
  v4 = (uint32_t *)sub_65DCE0(pDwArg2);  // sub_65DCE0 —— 字符串键在红黑树中定位（逐字节 memcmp，右侧插入语义）
  if ( v4 == (uint32_t *)*(this + 1)  // 若 v4 == (uint32_t *)*(this + 1
    || (v4[9] < 0x10u ? (v5 = (const char *)(v4 + 4)) : (v5 = (const char *)v4[4]),
        sub_40BF00((std::_String_base *)pDwArg22, 0, pDwArg22[5], v5, v4[8]) < 0) )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v10 = 15;
    v9 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    sub_4014D0((std::_String_base *)&v7, pDwArg22, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    v11 = 0;
    v12 = 0;
    v4 = (uint32_t *)*sub_502430((int)this, &pDwArg2, v4, &v7);
    if ( v10 >= 0x10 )
      j__free(Block);  // 释放堆块
  }
  return v4 + 10;  // 返回内嵌子对象/缓冲指针（v4+10）
}



// ------------------------------------------------------------
// 0x5027A0 sub_5027A0
//   std::map 默认构造：分配头哨兵节点（sub_433B80，+0x2D=_Isnil=1），
//   左右/父指针全部回指自身，元素计数清零。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5027A0(uint32_t *this)
{
  int v2; // eax

  v2 = sub_433B80();  // sub_433B80 —— map 节点分配（0x30）
  *(this + 1) = v2;  // 写字段 this+1 ← v2
  *(uint8_t *)(v2 + 45) = 1;  // 写字段 v2+45 ← 1
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);  // this+4 = pHostObj
  *(uint32_t *)*(this + 1) = *(this + 1);  // 写字段 this+1 ← *(this + 1)
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);  // this+4 = pHostObj
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  return this;
}



// ------------------------------------------------------------
// 0x5027D0 sub_5027D0
//   std::_Fill_n（44 字节元素版）：转调 sub_5025D0 后返回 nArg1+44*nArg2 尾地址。
// ------------------------------------------------------------
int /*stdcall*/ sub_5027D0(int nArg1, int nArg2, int nArg3)
{
  sub_5025D0(nArg1, nArg2, nArg3);  // 调 sub_5025D0
  return nArg1 + 44 * nArg2;
}



// ------------------------------------------------------------
// 0x502800 sub_502800
//   std::vector<44字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（480E70/502410/5027D0/5023C0 搬运）；不足 → 扩容三段拷贝重建。
// ------------------------------------------------------------
void /*thiscall*/ sub_502800(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 函数: 释放后返回
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
  sub_480A90(nArg4);  // sub_480A90 —— 44 字节技能槽条目拷贝构造（含两内嵌列表）
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  fld_e3 = 0;
  v34 = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - fld_e1) / 44;  // this+12 = 技能槽记录次字
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 44;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 97612893 - fld_e2 < uArg3 )
      sub_47F990(this);  // 调 sub_47F990
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 44;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = *(this + 2);  // 读字段 fld_e23 = this+2
      fld_e232 = fld_e23;  // fld_e23=this+8 物品 id
      if ( (fld_e23 - pArg2) / 44 >= uArg3 )  // fld_e23=this+8 物品 id
      {
        v35 = fld_e23 - 44 * uArg3;  // fld_e23=this+8 物品 id
        *(this + 2) = sub_480E70(v35, fld_e23, fld_e23);  // sub_480E70 —— 44 字节条目区间构造到裸内存
        sub_502410(pArg2, v35, fld_e232);  // 调 sub_502410
        sub_5023C0(pArg2, pArg2 + 44 * uArg3, v23);  // 调 sub_5023C0
      }
      else
      {
        sub_480E70(pArg2, fld_e23, pArg2 + 44 * uArg3);  // sub_480E70 —— 44 字节条目区间构造到裸内存
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 44;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        LOBYTE(v34) = 3;  // 调 取 16 位值低 8 位
        sub_5027D0(fld_e25, fld_e24, v23);  // 调 sub_5027D0
        fld_e26 = 44 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        v34 = 0;
        sub_5023C0(pArg2, fld_e26 - 44 * uArg3, v23);  // 调 sub_5023C0
      }
    }
    else
    {
      if ( 97612893 - (fld_e3 >> 1) >= fld_e3 )  // 若 97612893 - (fld_e3 >> 1) >= fld_e3
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 44;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_527B90(this);  // 调 取 size
      v37 = 44 * v10;  // 计算 v37 = 44 * v10
      pMem = (char *)operator new(44 * v10);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      Block = pMem;
      LOBYTE(v34) = 1;  // 调 取 16 位值低 8 位
      v36 = sub_480E70(fld_e12, pArg2, pMem);  // sub_480E70 —— 44 字节条目区间构造到裸内存
      sub_5025D0(v36, uArg3, v23);  // 调 sub_5025D0
      sub_480E70(pArg2, *(this + 2), 44 * uArg3 + v36);  // sub_480E70 —— 44 字节条目区间构造到裸内存
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      v34 = 0;
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 44;  // this+8 = 技能槽记录首字
      v14 = fld_e13 + uArg3;  // 计算 v14 = fld_e13 + uArg3
      fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
      if ( fld_e14 != 0 )  // fld_e14=this+4 宿主对象
      {
        sub_480F40(fld_e14, *(this + 2));  // sub_480F40 —— 44 字节条目区间逐项析构（转 ·sub_47FA00）
        j__free((void *)*(this + 1));  // 释放堆块
      }
      *(this + 3) = (int)&pMem[v37];  // 写字段 this+3 ← (int)&pMem[v37]
      *(this + 2) = (int)&pMem[44 * v14];  // 写字段 this+2 ← (int)&pMem[44 * v14]
      *(this + 1) = (int)pMem;  // 写字段 this+1 ← (int)pMem
    }
  }
  v34 = -1;
  if ( v28 != nullptr )
    j__free(v28);  // 释放堆块
  v28 = nullptr;  // v28 = nullptr 空指针
  v29 = 0;
  v30 = 0;
  if ( v25 != nullptr )
    j__free(v25);  // 释放堆块
  v25 = nullptr;  // v25 = nullptr 空指针
  v26 = 0;
  v27 = 0;
  sub_41B010(&v24);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
}


// ------------------------------------------------------------
// 0x502B30 sub_502B30
//   RDARKeyIndex.dat 索引加载器：校验脚本根目录（byte_9B71C8）后打开该索引文件，
//   逐 token 读（type 6 = 指令名字符串 / type 2 = 键码 atol），以
//   "指令名 → 键码" 存入全局 map dword_9B72C8（sub_5026A0 建槽）。供
//   sub_502F00 技能 [command] 键序解析查表。
// ------------------------------------------------------------
char /*cdecl*/ sub_502B30(char *i, int nArg2)  // 函数: 释放后返回
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
  v3 = byte_9B71C8 - i;  // 计算 v3 = byte_9B71C8 - i
  do
  {
    v4 = *v2;
    v2[v3] = *v2;  // v2[v3] 写入 *v2
    ++v2;  // 计数自增 v2
  }
  while ( v4 != 0 );  // 循环直到 v4 != 0
  if ( byte_9B71C7[strlen(byte_9B71C8)] != 92 && byte_9B71C7[strlen(byte_9B71C8)] != 47 )  // 若 byte_9B71C7[strlen(byte_9B71C8)] != 92 && byte_9B71C7[strlen(b..
    *(uint16_t *)&byte_9B71C8[strlen(byte_9B71C8)] = 92;  // 调 求串长
  sub_444150(&v16);  // sub_444150 —— map 初始化（header 自环）
  v18 = 0;
  if ( (uint8_t)sub_443C40((int)&v16, (char)byte_9B71C8, nArg2) == 0 )  // sub_443C40 —— 脚本文件列表装表
    goto LABEL_14;  // 跳转 LABEL_14
  v5 = *(char **)Block;
  for ( i = *(char **)Block; i != Block; v5 = i )  // 循环：i = *(char **)Block; i != Block; v5 = i
  {
    v6 = *((uint32_t *)v5 + 10) < 0x10u ? (int)(v5 + 20) : *((uint32_t *)v5 + 5);
    if ( (uint8_t)sub_443C40(12 * *((uint32_t *)v5 + 3) + 10187476, (char)byte_9B71C8, v6) == 0 )  // sub_443C40 —— 脚本文件列表装表
      goto LABEL_14;  // 跳转 LABEL_14
    sub_40BEA0(&i);  // sub_40BEA0 —— 红黑树迭代器自增（后继；哨兵位 +45）
  }
  if ( (uint8_t)sub_442A10((char)byte_9B71C8, (int)"RDARKeyIndex.dat") == 0 )  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  {
LABEL_14:
    v7 = *(char **)Block;
    v18 = -1;
    sub_443810(&i, v7, Block);  // sub_443810 —— 红黑树区间删除
    j__free(Block);  // 释放堆块
    return 0;
  }
  v9 = 0;
  for ( j = sub_65BE30(&unk_9789A0); j != 0; j = sub_65BE30(&unk_9789A0) )  // sub_65BE30 —— flex 扫描主循环（yylex 内核）：DFA 状态表驱动的内联动作分派；sub_65BE30 —— flex 扫描主循环（yylex 内核）：DFA 状态表驱动的内联动作分派
  {
    if ( j == 2 )
    {
      v9 = j__atol(dword_9789A4);  // dword_9789A4 —— 【std::string构造赋值】
    }
    else if ( j == 6 )
    {
      v15 = 15;
      v14 = 0;
      LOBYTE(v13) = 0;  // 调 取 16 位值低 8 位
      sub_4015C0(dword_9789A4, strlen(dword_9789A4));  // 【std::string构造赋值】
      LOBYTE(v18) = 1;  // 调 取 16 位值低 8 位
      *sub_5026A0(&dword_9B72C8, &v12) = v9;
      LOBYTE(v18) = 0;  // 调 取 16 位值低 8 位
      if ( v15 >= 0x10 )
        j__free(v13);  // 释放堆块
      v15 = 15;
      v14 = 0;
      LOBYTE(v13) = 0;  // 调 取 16 位值低 8 位
    }
  }
  v11 = *(char **)Block;
  v18 = -1;
  sub_443810(&i, v11, Block);  // sub_443810 —— 红黑树区间删除
  j__free(Block);  // 释放堆块
  return 1;
}



// ------------------------------------------------------------
// 0x502DA0 sub_502DA0
//   std::vector<44字节元素>::erase(尾部)：先把元素搬移（sub_480BC0），再从后往
//   前逐个析构（sub_47FA00），end 回退 44 字节。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_502DA0(uint32_t *this, uint32_t *uArg2, int pArg3)
{
  int fld_e2; // edi
  int v5; // esi

  sub_480BC0(pArg3 + 44, *(this + 2), pArg3);  // sub_480BC0 —— 44 字节技能槽条目区间逐个拷贝构造
  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  v5 = fld_e2 - 44;  // 计算 v5 = fld_e2 - 44
  do
  {
    sub_47FA00(v5);  // 调 sub_47FA00
    v5 += 44;
  }
  while ( v5 != fld_e2 );  // 循环直到 v5 != fld_e2
  *(this + 2) -= 44;  // this+8 = 技能槽记录首字
  *uArg2 = pArg3;  // *uArg2 写入 pArg3
  return uArg2;
}



// ------------------------------------------------------------
// 0x502E00 sub_502E00
//   std::vector<44字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_502800 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_502E00(int *this, uint32_t *uArg2, char *pszArg3, int nArg4)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 44 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (int)&pszArg3[-fld_e1] / 44;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_502800(this, pszArg3, 1u, nArg4);  // 调 sub_502800
  *uArg2 = *(this + 1) + 44 * v6;  // *uArg2 写入 *(this + 1) + 44 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x502E70 sub_502E70
//   std::vector<44字节元素>::push_back：容量够 → 在 +8 end 构造（sub_5025D0 析构
//   占位后再写）；不够 → 转调 sub_502E00 插入路径扩容。
// ------------------------------------------------------------
void /*thiscall*/ sub_502E70(int *this, int nArg2)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) / 44;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) / 44 )  // fld_e1=this+4 宿主对象
  {
    fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
    sub_5025D0(fld_e22, 1, nArg2);  // 调 sub_5025D0
    *(this + 2) = fld_e22 + 44;  // 写字段 this+2 ← fld_e22 + 44
  }
  else
  {
    sub_502E00(this, &nArg2, (char *)*(this + 2), nArg2);  // 调 sub_502E00
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
char /*cdecl*/ sub_502F00(int pArg1, const char *ArgList, int nArg3)  // 函数: 释放后返回
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B71C8, (int)ArgList);  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )
  {
    sub_481420(pArg1);  // sub_481420 —— 节点字段组清零（+42..59）+ sub_5E5260 容器析构
    v66 = 15;
    v65 = 0;
    LOBYTE(v64) = 0;  // 调 取 16 位值低 8 位
    v68 = 1;
    v62 = 15;
    v61 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    v57 = 0;
    while ( (uint8_t)sub_443430(&v63) != 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    {
      sub_442B20(&v63);  // sub_442B20 —— 国家码标签配对校验（void）
      if ( sub_40BF00(0, v65, "[name]", 6) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00(0, v65, "[name2]", 7) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00(0, v65, "[explain]", 9) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00(0, v65, "[maximum level]", 15) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              if ( (uint8_t)sub_423300(&v63, "[purchase cost]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_5E5260((void *)(pArg1 + 20));  // 调 sub_5E5260
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                  sub_431230(&i);  // sub_431230 —— uint32 vector push_back
              }
              else if ( (uint8_t)sub_423300(&v63, "[required level]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 36) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[required level range]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 40) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[pre required skill]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_5E5260((void *)(pArg1 + 44));  // 调 sub_5E5260
                sub_5E5260((void *)(pArg1 + 60));  // 调 sub_5E5260
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                {
                  sub_431230(&i);  // sub_431230 —— uint32 vector push_back
                  i = COERCE_FLOAT(sub_4423D0(0));  // sub_4423D0 —— [LOOP] → 动画对象+160
                  sub_431230(&i);  // sub_431230 —— uint32 vector push_back
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[steel learning skill]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v4 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v38 = 0;
                *(uint8_t *)(pArg1 + 320) = v4 == 1;  // 写字段 pArg1+320 ← v4 == 1
                v5 = sub_4423D0(v38);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v37 = 0;
                *(uint32_t *)(pArg1 + 324) = v5;  // 写字段 pArg1+324（nAnchor324） ← v5
                v6 = sub_4423D0(v37);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v36 = 0;
                *(uint32_t *)(pArg1 + 328) = v6;  // 写字段 pArg1+328 ← v6
                *(uint32_t *)(pArg1 + 332) = sub_4423D0(v36);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[type]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_443370(v59);  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v59, "[active]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 76) = 0;  // 写字段 pArg1+76（szEmblemPath） ← 0
                }
                else if ( (uint8_t)sub_423300(v59, "[passive]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 76) = 1;  // 写字段 pArg1+76（szEmblemPath） ← 1
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[skill class]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 80) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[growtype fitness]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v7 = (uint32_t *)(pArg1 + 84);
                for ( j = 5; j != 0; --j )  // 遍历计次循环（j != 0）
                  *v7++ = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[casting time]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v9 = (uint32_t *)(pArg1 + 132);
                for ( k = 2; k != 0; --k )  // 遍历计次循环（k != 0）
                  *v9++ = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[growtype maximum level]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v11 = (uint32_t *)(pArg1 + 104);
                for ( m = 5; m != 0; --m )  // 遍历计次循环（m != 0）
                  *v11++ = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[skill fitness growtype]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_5E5260((void *)(pArg1 + 304));  // 调 sub_5E5260
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                  sub_431230(&i);  // sub_431230 —— uint32 vector push_back
              }
              else if ( (uint8_t)sub_423300(&v63, "[consume MP]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v13 = pArg1 + 124;  // 计算 v13 = pArg1 + 124
                for ( n = 2; n != 0; --n )  // 遍历计次循环（n != 0）
                {
                  v13 += 4;
                  *(float *)(v13 - 4) = sub_442480(0) * 0.89999998;  // sub_442480 —— 脚本 token 数值解析（double 版）
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[consume item]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v48 = 0;
                v49 = 0;
                sub_5E5260((void *)(pArg1 + 140));  // 调 sub_5E5260
                for ( ii = sub_4423D0(&v57); v57 != 0; ii = sub_4423D0(&v57) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                {
                  v48 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  v49 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  sub_502120(&ii);  // 调 sub_502120
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[cool time]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v15 = (uint32_t *)(pArg1 + 156);
                for ( jj = 2; jj != 0; --jj )  // 遍历计次循环（jj != 0）
                  *v15++ = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[skill under cooltime effect]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_5E5260((void *)(pArg1 + 164));  // 调 sub_5E5260
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                  sub_431230(&i);  // sub_431230 —— uint32 vector push_back
              }
              else if ( (uint8_t)sub_423300(&v63, "[auto cooltime apply]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 180) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[icon]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_442E10(pArg1 + 184);  // 【RDARScriptStringManager 入口（::ERROR::input…】
                v17 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v37 = pArg1 + 188;  // 计算 v37 = pArg1 + 188
                *(uint32_t *)(pArg1 + 192) = v17;  // 写字段 pArg1+192（nDlgId） ← v17
                sub_442E10(v37);  // 【RDARScriptStringManager 入口（::ERROR::input…】
                *(uint32_t *)(pArg1 + 196) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(&v63, "[command key explain]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_442E10(pArg1 + 244);  // 【RDARScriptStringManager 入口（::ERROR::input…】
              }
              else if ( (uint8_t)sub_423300(&v63, "[command]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v51 = 0;
                v52 = 0;
                v53 = 0;
                v54 = 0;
                v55 = 300;
                LOBYTE(v68) = 2;  // 调 取 16 位值低 8 位
                sub_435850(pArg1 + 200);  // sub_435850 —— 24 字节条目向量销毁
                for ( kk = sub_65BE30(&unk_9789A0); kk != 0; kk = sub_65BE30(&unk_9789A0) )  // sub_65BE30 —— flex 扫描主循环（yylex 内核）：DFA 状态表驱动的内联动作分派；sub_65BE30 —— flex 扫描主循环（yylex 内核）：DFA 状态表驱动的内联动作分派
                {
                  if ( kk == 5 )
                    break;
                  switch ( kk )  // 分支：按 kk 分派
                  {
                    case 6:  // case 6 分派（§D 0x4FF800-0x504000 任务(quest)定义族 + 对象创建定义(sub_500B30) + 技能定）
                      sub_401710(dword_9789A4);  // sub_401710 —— std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
                      LOBYTE(v68) = 3;  // 调 取 16 位值低 8 位
                      sub_5014F0(&v46, v40);  // 调 sub_5014F0
                      LOBYTE(v68) = 2;  // 调 取 16 位值低 8 位
                      sub_501490(v40);  // 调 sub_501490
                      if ( v46 != dword_9B72CC )
                        sub_431230(v46 + 40);  // sub_431230 —— uint32 vector push_back
                      break;
                    case 2:  // case 2 分派（§D 0x4FF800-0x504000 任务(quest)定义族 + 对象创建定义(sub_500B30) + 技能定）
                      v54 = j__atol(dword_9789A4);  // dword_9789A4 —— 【std::string构造赋值】
                      break;
                    case 7:  // case 7 分派（§D 0x4FF800-0x504000 任务(quest)定义族 + 对象创建定义(sub_500B30) + 技能定）
                      sub_401710(byte_979DF8);  // sub_401710 —— std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
                      LOBYTE(v68) = 4;  // 调 取 16 位值低 8 位
                      if ( (uint8_t)sub_423300(v58, "DOWN") != 0 )  // sub_423300 —— [end] → 解析结束
                      {
                        *(uint32_t *)(pArg1 + 232) = 0;  // 写字段 pArg1+232（bSyncSwitch） ← 0
                        LOBYTE(v68) = 2;  // 调 取 16 位值低 8 位
                        sub_501490(v58);  // 调 sub_501490
                      }
                      else if ( (uint8_t)sub_423300(v58, "DOWN ONCE") != 0 )  // sub_423300 —— [end] → 解析结束
                      {
                        *(uint32_t *)(pArg1 + 232) = 1;  // 写字段 pArg1+232（bSyncSwitch） ← 1
                        LOBYTE(v68) = 2;  // 调 取 16 位值低 8 位
                        sub_501490(v58);  // 调 sub_501490
                      }
                      else if ( (uint8_t)sub_423300(v58, "UP") != 0 )  // sub_423300 —— [end] → 解析结束
                      {
                        *(uint32_t *)(pArg1 + 232) = 2;  // 写字段 pArg1+232（bSyncSwitch） ← 2
                        LOBYTE(v68) = 2;  // 调 取 16 位值低 8 位
                        sub_501490(v58);  // 调 sub_501490
                      }
                      else
                      {
                        if ( (uint8_t)sub_423300(v58, "UP ONCE") != 0 )  // sub_423300 —— [end] → 解析结束
                          *(uint32_t *)(pArg1 + 232) = 3;  // 写字段 pArg1+232（bSyncSwitch） ← 3
                        LOBYTE(v68) = 2;  // 调 取 16 位值低 8 位
                        sub_501490(v58);  // 调 sub_501490
                      }
                      break;
                    case 8:  // case 8 分派（§D 0x4FF800-0x504000 任务(quest)定义族 + 对象创建定义(sub_500B30) + 技能定）
                      v19 = *dword_9789A4;  // dword_9789A4 —— 【std::string构造赋值】
                      if ( *dword_9789A4 == 38 )  // dword_9789A4 —— 【std::string构造赋值】
                      {
                        if ( (uint8_t)sub_484F10(v50) == 0 )  // sub_484F10 —— 32 字节对象列表空判定（+4 为 0 或元素数 0）
                          sub_4ED3F0(v50);  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
                      }
                      else
                      {
                        switch ( v19 )  // 分支：按 v19 分派
                        {
                          case '!':  // case 字符 ! (0x21)
                            v55 = 150;
                            break;
                          case ',':  // case 字符 , (0x2C)
                            v55 = 300;
                            break;
                          case '~':  // case 字符 ~ (0x7E)
                            v55 = 1000;
                            break;
                          default:
                            break;
                        }
                        if ( (uint8_t)sub_484F10(v50) == 0 )  // sub_484F10 —— 32 字节对象列表空判定（+4 为 0 或元素数 0）
                          sub_4B5910(v50);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
                      }
                      sub_4B1C10(v50);  // sub_4B1C10 —— 容器释放复位（缺省 300）
                      break;
                    default:
                      break;
                  }
                }
                if ( (uint8_t)sub_484F10(v50) == 0 )  // sub_484F10 —— 32 字节对象列表空判定（+4 为 0 或元素数 0）
                  sub_4B5910(v50);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
                LOBYTE(v68) = 1;  // 调 取 16 位值低 8 位
                sub_5E5260(v50);  // 调 sub_5E5260
              }
              else if ( (uint8_t)sub_423300(&v63, "[static data]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_5E5260((void *)(pArg1 + 248));  // 调 sub_5E5260
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                  sub_431230(&i);  // sub_431230 —— uint32 vector push_back
              }
              else if ( (uint8_t)sub_423300(&v63, "[level info]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_42D540(pArg1 + 264);  // sub_42D540 —— 释放 +4 缓冲（16B 条目）
                v20 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                sub_4897D0(v20);  // sub_4897D0 —— 容器重设长度·薄包装
                v21 = 0;
                for ( i = COERCE_FLOAT(sub_4423D0(&v57)); v57 != 0; i = COERCE_FLOAT(sub_4423D0(&v57)) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                {
                  sub_431230(&i);  // sub_431230 —— uint32 vector push_back
                  ++v21;  // 计数自增 v21
                }
              }
              else if ( (uint8_t)sub_423300(&v63, "[level property]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v22 = sub_4423D0(&v57);  // sub_4423D0 —— [LOOP] → 动画对象+160
                if ( v57 == 0 )
                  break;
                sub_502030(&v41);  // 调 sub_502030
                LOBYTE(v68) = 5;  // 调 取 16 位值低 8 位
                v41 = v22;
                v42 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                sub_442E10(v43);  // 【RDARScriptStringManager 入口（::ERROR::input…】
                for ( mm = sub_4423D0(&v57); v57 != 0; mm = sub_4423D0(&v57) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                {
                  v24 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  v45[0] = mm;
                  v45[1] = v24;
                  sub_474950(v45);  // sub_474950 —— 调用 sub_474950
                  i = sub_442480(0);  // sub_442480 —— 脚本 token 数值解析（double 版）
                  sub_5020D0(&i);  // 调 sub_5020D0
                }
                v25 = *(uint32_t **)(pArg1 + 284);
                while ( v25 != *(uint32_t **)(pArg1 + 288) )  // 当 v25 != *(uint32_t **)(pArg1 + 288) 循环
                {
                  if ( v25[1] < v41 || *v25 > v42 )
                    v25 += 11;
                  else
                    v25 = *(uint32_t **)sub_502DA0(v44, v25);
                }
                sub_502E70(&v41);  // 调 sub_502E70
                LOBYTE(v68) = 1;  // 调 取 16 位值低 8 位
                sub_47FA00(&v41);  // 调 sub_47FA00
              }
              else if ( (uint8_t)sub_423300(&v63, "[shake screen]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v26 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                v38 = 0;
                *(uint32_t *)(pArg1 + 296) = v26;  // 写字段 pArg1+296（bInitFlag296） ← v26
                *(uint32_t *)(pArg1 + 300) = sub_4423D0(v38);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else
              {
                i = COERCE_FLOAT(v35);
                sub_401690(&v63);  // sub_401690 —— std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全量赋值）
                if ( (uint8_t)sub_442C80((char)v35[0], v35[1], (int)v35[2], v36, v37, v38, v39) == 0 )  // sub_442C80 —— 行首是 [ 仍未匹配
                {
                  v27 = (const char *)v64;
                  if ( v66 < 0x10 )
                    v27 = (const char *)&v64;
                  off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, v27);  // off_77F3FC —— 日志打印（printf 风格）
                }
              }
            }
            else
            {
              *(uint32_t *)(pArg1 + 16) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
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
    for ( nn = 5; nn != 0; --nn )  // 遍历计次循环（nn != 0）
    {
      if ( *v28 > *(uint32_t *)(pArg1 + 16) )  // 若 *v28 > *(uint32_t *)(pArg1 + 16)
      {
        off_77F3FC(aSkillError, ArgList);  // off_77F3FC —— 日志打印（printf 风格）
        *(uint32_t *)(pArg1 + 16) = *v28;  // 写字段 pArg1+16（nChannelTypeSel） ← *v28
      }
      ++v28;  // 计数自增 v28
    }
    while ( 1 )  // 当 1 循环
    {
      v30 = *(uint32_t *)(pArg1 + 24);  // 读字段 v30 = pArg1+24（nPageMax）
      v31 = v30 != 0 ? (*(uint32_t *)(pArg1 + 28) - v30) >> 2 : 0;
      if ( v31 >= *(uint32_t *)(pArg1 + 16) )  // 若 v31 >= *(uint32_t *)(pArg1 + 16)
        break;
      v32 = *(uint32_t *)(pArg1 + 24);  // 读字段 v32 = pArg1+24（nPageMax）
      if ( v32 != 0 )
        v33 = (*(uint32_t *)(pArg1 + 28) - v32) >> 2;
      else
        v33 = 0;
      if ( v32 != 0 && v33 < (*(uint32_t *)(pArg1 + 32) - v32) >> 2 )
      {
        v34 = *(uint32_t **)(pArg1 + 28);
        *v34 = *(v34 - 1);  // *v34 写入 *(v34 - 1)
        *(uint32_t *)(pArg1 + 28) = v34 + 1;  // 写字段 pArg1+28（pPanelVec） ← v34 + 1
      }
      else
      {
        sub_430C80(*(void **)(pArg1 + 28), 1, *(uint32_t *)(pArg1 + 28) - 4);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
      }
    }
    if ( nArg3 == 4 )
      *(uint32_t *)pArg1 = -1;
    else
      *(uint32_t *)pArg1 = sub_4A2F80(ArgList);  // 调 +0x00 ← 按文件名查全局 ID 表（未登记 = -1）
    if ( v62 >= 0x10 )
      j__free(Block);  // 释放堆块
    v62 = 15;
    v61 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    if ( v66 >= 0x10 )
      j__free(v64);  // 释放堆块
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
char /*cdecl*/ sub_503BA0(int pArg1, const char *ArgList)  // sub_503BA0 —— ★★ 怪物/PassiveObject 攻击定义解析器（attackinfo 结构填充）
{
  char result; // al
  int nStatusSlot; // ebx  [active status] 槽位选择（首槽=17 时用第二槽）
  void *p_Block; // eax
  int nStatusIdx; // edi  off_791F38 状态名表索引
  int v6; // eax
  const char *v7; // eax
  void *tmpTagBuf[5]; // [esp-1Ch] [ebp-74h] BYREF  未知标签检查：行拷贝（寄存器传参拆散）
  int tmpFlagSlot; // [esp-8h] [ebp-60h]  sub_442480 可解析标志占位 / sub_442C80 实参
  int tmpCapSlot; // [esp-4h] [ebp-5Ch]
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)szPassword, (int)ArgList);  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
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
    nStatusSlot = 0;
    v19 = 15;
    v18 = 0;
    LOBYTE(v17) = 0;  // 调 取 16 位值低 8 位
    v21 = 1;
    v15 = 15;
    v14 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    while ( (uint8_t)sub_443430(&v16) != 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    {
      sub_442B20(&v16);  // sub_442B20 —— 国家码标签配对校验（void）
      if ( sub_40BF00(0, v18, "[damage]", 8) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00(0, v18, "[absolute damage]", 17) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00(0, v18, "[damage bonus]", 14) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00(0, v18, "[attack type]", 13) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              if ( (uint8_t)sub_423300(&v16, "[weapon damage apply]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 16) = sub_4423D0(0) != 0;   // +16 [weapon damage apply] 武器伤害适用
              }
              else if ( (uint8_t)sub_423300(&v16, "[attack myself]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 17) = sub_4423D0(0) != 0;   // +17 [attack myself]  友敌开关 1/3（本地扫掠 +405 门镜像）
              }
              else if ( (uint8_t)sub_423300(&v16, "[attack friend]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 18) = sub_4423D0(0) != 0;   // +18 [attack friend]  友敌开关 2/3（+406）
              }
              else if ( (uint8_t)sub_423300(&v16, "[attack enemy]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 19) = sub_4423D0(0) != 0;   // +19 [attack enemy]   友敌开关 3/3（+407）
              }
              else if ( (uint8_t)sub_423300(&v16, "[elemental property]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_443370(v12);  // sub_443370 —— [name] → 对象+0x04 名称串
                p_Block = Block;
                if ( v15 < 0x10 )
                  p_Block = &Block;
                *(uint32_t *)(pArg1 + 20) = sub_442710(p_Block);  // +20 [elemental property] 属性攻击（名字查表）
              }
              else if ( (uint8_t)sub_423300(&v16, "[active status]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_443370(v12);  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( *(uint32_t *)(pArg1 + 24) != 17 )            // 首槽非 17(=none) → 第二槽
                  nStatusSlot = 1;
                nStatusIdx = 0;
                while ( (uint8_t)sub_423300(v12, off_791F38[nStatusIdx]) == 0 )  // sub_423300 —— [end] → 解析结束
                {
                  if ( ++nStatusIdx >= 18 )                             // 18 项状态名表（含 [none]=17）
                    goto LABEL_36;  // 跳转 LABEL_36
                }
                *(uint32_t *)(pArg1 + 4 * nStatusSlot + 24) = nStatusIdx;          // +24/+28 [active status] 状态 id
LABEL_36:
                *(float *)(pArg1 + 4 * nStatusSlot + 36) = sub_442480(0);  // +36/+40 状态强度（float 平行数组）
                *(uint32_t *)(pArg1 + 4 * nStatusSlot + 48) = sub_4423D0(0);// +48/+52 状态概率（int 平行数组）
                nStatusSlot = 0;
              }
              else if ( (uint8_t)sub_423300(&v16, "[damage reaction]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_443370(v12);  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v12, "[none]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 60) = 0;                   // +60 [damage reaction] [none] 反应类型=无
                }
                else if ( (uint8_t)sub_423300(v12, "[damage]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 60) = 1;                   // +60 [damage] 走受击反应（state 3/4/5 选型门）
                }
                else if ( (uint8_t)sub_423300(v12, "[down]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 60) = 2;                   // +60 [down] 击倒
                }
              }
              else if ( (uint8_t)sub_423300(&v16, "[push aside]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 64) = sub_4423D0(0);         // +64 [push aside] 击退距离（<150 分档，研究 20 §2 ⑧）
              }
              else if ( (uint8_t)sub_423300(&v16, "[lift up]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 68) = sub_4423D0(0);         // +68 [lift up] 浮空值（<400 分档 + 暴击加成 250/50）
              }
              else if ( (uint8_t)sub_423300(&v16, "[critical hit]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(float *)(pArg1 + 72) = sub_442480(0);            // +72 [critical hit] 暴击率（伤害终段 +3.0 加成）
              }
              else if ( (uint8_t)sub_423300(&v16, "[stuck]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(float *)(pArg1 + 76) = sub_442480(0);            // +76 [stuck] 硬直强度/概率（float 属性路径）
              }
              else if ( (uint8_t)sub_423300(&v16, "[stuck prob increase]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 80) = sub_4423D0(0) != 0;     // +80 [stuck prob increase] 三开关之一
              }
              else if ( (uint8_t)sub_423300(&v16, "[knuck back]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 81) = sub_4423D0(0) != 0;     // +81 [knuck back] 三开关之二（原文拼写）
              }
              else if ( (uint8_t)sub_423300(&v16, "[ignore defense]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 82) = sub_4423D0(0) != 0;     // +82 [ignore defense] 三开关之三
              }
              else if ( (uint8_t)sub_423300(&v16, "[human damage rate]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(float *)(pArg1 + 84) = sub_442480(0);            // +84 [human damage rate] 对人型倍率（>100% 标记特效）
              }
              else if ( (uint8_t)sub_423300(&v16, "[fort damage rate]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(float *)(pArg1 + 88) = sub_442480(0);            // +88 [fort damage rate] 对城械倍率
              }
              else if ( (uint8_t)sub_423300(&v16, "[HP drain]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 140) = sub_4423D0(0) != 0;    // +140 [HP drain] 吸血
              }
              else if ( (uint8_t)sub_423300(&v16, "[MP drain]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 141) = sub_4423D0(0) != 0;    // +141 [MP drain] 吸魔
              }
              else if ( (uint8_t)sub_423300(&v16, "[hit wav]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_443370(pArg1 + 92);                            // +92 [hit wav] 自定义命中音效（VC6 std::string）
              }
              else if ( (uint8_t)sub_423300(&v16, "[attack direction]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_443370(v12);  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v12, "[hit lift up]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 120) = 0;                  // +120 [attack direction] 0=上挑
                }
                else if ( (uint8_t)sub_423300(v12, "[hit horizon]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 120) = 1;                  // +120 1=平推
                }
                else if ( (uint8_t)sub_423300(v12, "[hit down]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 120) = 2;                  // +120 2=下压（决定反应动画选型）
                }
              }
              else if ( (uint8_t)sub_423300(&v16, "[hit info]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_443370(v12);  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v12, "[blow]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 124) = 0;                  // +124 [hit info] 0=[blow] 钝击 → Knock 火花
                }
                else if ( (uint8_t)sub_423300(v12, "[cut]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 124) = 1;                  // +124 1=[cut] 斩击 → Slash 火花
                }
                else if ( (uint8_t)sub_423300(v12, "[burn]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 124) = 2;                  // +124 2=[burn] 延滞伤（CNChangeHp 1000ms）
                }
                else if ( (uint8_t)sub_423300(v12, "[etc]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 124) = 3;                  // +124 3=[etc] 自定义路径（攻方 vt+652）
                }
                sub_443370(v12);  // sub_443370 —— [name] → 对象+0x04 名称串
                if ( (uint8_t)sub_423300(v12, "[no blood]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 128) = 0;                   // +128 [no blood] 无血溅
                }
                else if ( (uint8_t)sub_423300(v12, "[blood]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 128) = 1;                   // +128 [blood] 有血溅（SplashBlood 族）
                }
                v6 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                tmpFlagSlot = 0;
                *(uint32_t *)(pArg1 + 132) = v6;                   // +132 ★ 受击硬直(stuck)时长 ms = hit stop 时长
                                                                //   （研究 20 §3 表现壳 sub_4E5DC0 读此处，
                                                                //    经 vt+228(this,1,时长,0) 施加主状态 1）
                *(float *)(pArg1 + 136) = sub_442480(tmpFlagSlot);          // +136 受击动作速度倍率（-1 → 1.0；+12==1 时 ×0.7）
              }
              else
              {
                v11 = tmpTagBuf;
                sub_401690(&v16);  // sub_401690 —— std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全量赋值）
                if ( (uint8_t)sub_442C80((char)tmpTagBuf[0], tmpTagBuf[1], (int)tmpTagBuf[2], (int)tmpTagBuf[3], (int)tmpTagBuf[4], tmpFlagSlot, tmpCapSlot) == 0 )  // sub_442C80 —— 行首是 [ 仍未匹配
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
              sub_443370(v12);  // sub_443370 —— [name] → 对象+0x04 名称串
              if ( (uint8_t)sub_423300(v12, "[physic]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 12) = 0;                     // +12 [attack type] 0=物理
              }
              else if ( (uint8_t)sub_423300(v12, "[magic]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 12) = 1;                     // +12 1=魔法（受击动作速度 ×0.7 —— 研究 20 §2 ⑧）
              }
              else if ( (uint8_t)sub_423300(v12, "[ignore defense]") != 0 )  // sub_423300 —— [end] → 解析结束
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
      j__free(Block);  // 释放堆块
    v15 = 15;
    v14 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    if ( v19 >= 0x10 )
      j__free(v17);  // 释放堆块
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x504300 sub_504300
//   设定副本地图脚本根目录（全局 byte_9B7308，补 '\' 或 '/' 结尾）后加载文件表到
//   unk_9B7408（sub_443C40）。sub_5078C0 副本地图解析器经 &unk_9B7308 使用该目录。
// ------------------------------------------------------------
bool /*cdecl*/ sub_504300(const char *pArg1, int nArg2)  // ★★ 怪物/PassiveObject 攻击定义解析器（attackinfo 结构填充）
{
  strcpy(byte_9B7308, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B7307[strlen(byte_9B7308)] != 92 && byte_9B7307[strlen(byte_9B7308)] != 47 )  // 若 byte_9B7307[strlen(byte_9B7308)] != 92 && byte_9B7307[strlen(b..
    *(uint16_t *)&byte_9B7308[strlen(byte_9B7308)] = 92;  // 调 求串长
  return (uint8_t)sub_443C40((int)&unk_9B7408, (char)byte_9B7308, nArg2) != 0;  // sub_443C40 —— 脚本文件列表装表
}



// ------------------------------------------------------------
// 0x504390 sub_504390
//   std::vector<36字节元素>::size()：(end-begin)/36。
// ------------------------------------------------------------
int /*thiscall*/ sub_504390(int *this)
{
  int result; // eax

  result = *(this + 1);  // 读字段 result = this+1
  if ( result != 0 )  // result=this+4 宿主对象
    return (*(this + 2) - result) / 36;  // this+8 = 技能槽记录首字
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x5043B0 sub_5043B0
//   std::copy（12 字节元素版，正向逐 3 dword）：[uArg1,uArg2) → uArg3。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_5043B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // sub_5043B0 —— 在插入位填 n 条
{
  uint32_t *result; // eax
  uint32_t *v4; // edi

  for ( result = uArg1; result != uArg2; v4[2] = pArg3[2] )  // 循环：result = uArg1; result != uArg2; v4[2] = pArg3[2]
  {
    v4 = result;
    *result = *pArg3;  // *result 写入 *pArg3
    result[1] = pArg3[1];  // result[1] 写入 pArg3[1]
    result += 3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5043F0 sub_5043F0
//   std::copy_backward（16 字节元素版）：[uArg1,uArg2) 从尾往头搬到 uArg3 结尾处。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_5043F0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg22; // ecx
  uint32_t *result; // eax

  uArg22 = uArg2;
  for ( result = uArg3; uArg22 != uArg1; result[3] = uArg22[3] )  // 循环：result = uArg3; uArg22 != uArg1; result[3] = uArg22[3]
  {
    uArg22 -= 4;
    result -= 4;
    *result = *uArg22;  // *result 写入 *uArg22
    result[1] = uArg22[1];  // result[1] 写入 uArg22[1]
    result[2] = uArg22[2];  // result[2] 写入 uArg22[2]
  }
  return result;
}



// ------------------------------------------------------------
// 0x504430 sub_504430
//   std::copy_backward（24 字节元素版）：转调 sub_4FEFD0。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_504430(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  return sub_4FEFD0(uArg1, uArg2, uArg3);  // 调 sub_4FEFD0
}



// ------------------------------------------------------------
// 0x504450 sub_504450
//   std::_Fill_n（12 字节元素版）：转调 sub_623BD0（逐元素拷贝构造）。
// ------------------------------------------------------------
int /*cdecl*/ sub_504450(int nArg1, int nArg2, int nArg3)  // sub_504450 —— 搬移插入位后元素
{
  return sub_623BD0(nArg1, nArg2, nArg3);  // sub_623BD0 —— 12 字节元素反向搬移
}



// ------------------------------------------------------------
// 0x504470 sub_504470
//   std::map 树节点堆构造（0x18 字节）：{int key1, int key2, 16 字节值(4 dword)}，
//   供怪物临时条目 map 插入用【推断】。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_504470(int nArg1, int nArg2, uint32_t *pArg3)  // 函数定义: 建节点插到哨兵后
{
  uint32_t *result; // eax

  result = operator new(0x18u);  // 堆分配
  if ( result != nullptr )
  {
    *result = nArg1;  // *result 写入 nArg1
    result[1] = nArg2;
    result[2] = *pArg3;  // result[2] 写入 *pArg3
    result[3] = pArg3[1];  // result[3] 写入 pArg3[1]
    result[4] = pArg3[2];  // result[4] 写入 pArg3[2]
    result[5] = pArg3[3];  // result[5] 写入 pArg3[3]
  }
  return result;
}



// ------------------------------------------------------------
// 0x5044B0 sub_5044B0
//   std::fill_n / 未初始化填充（24 字节元素版）：从 uArg1 起连续 uArg2 个元素
//   用 pArg3 的 6 个 dword 覆盖。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_5044B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // 函数定义: 后返回 &pArg1[6*uArg2] 尾地址
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
        *result = *pArg3;  // *result 写入 *pArg3
        result[1] = pArg3[1];  // result[1] 写入 pArg3[1]
        result[2] = pArg3[2];  // result[2] 写入 pArg3[2]
        result[3] = pArg3[3];  // result[3] 写入 pArg3[3]
        result[4] = pArg3[4];  // result[4] 写入 pArg3[4]
        result[5] = pArg3[5];  // result[5] 写入 pArg3[5]
      }
      result += 6;
      uArg22 = (uint32_t *)((char *)uArg22 - 1);
    }
    while ( uArg22 != nullptr );  // 循环直到 uArg22 != nullptr
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
void /*cdecl*/ sub_504500(uint32_t *uArg1)  // sub_504500 —— 掉落/奖励对象类别码解析器
{
  int i; // edi
  uint8_t v2[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  unsigned int v4; // [esp+1Ch] [ebp-18h]
  unsigned int v5; // [esp+20h] [ebp-14h]
  int dword_796E502; // [esp+24h] [ebp-10h]
  int v7; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v5 = 15;
  v4 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  v7 = 0;
  for ( i = 0; i < 6; ++i )  // 遍历计次循环（i < 6）
  {
    if ( i != 0 )
    {
      uArg1[i] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
    }
    else if ( sub_443370() != 0 )  // sub_443370 —— [name] → 对象+0x04 名称串
    {
      if ( sub_40BF00((std::_String_base *)v2, 0, v4, "[monster]", 9u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)v2, 0, v4, "[trap]", 6u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)v2, 0, v4, "[item]", 6u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)v2, 0, v4, "[quest]", 7u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
              *uArg1 = 3;  // *uArg1 写入 3
          }
          else
          {
            *uArg1 = 2;  // *uArg1 写入 2
          }
        }
        else
        {
          *uArg1 = 1;  // *uArg1 写入 1
        }
      }
      else
      {
        *uArg1 = 0;  // *uArg1 写入 0
      }
    }
  }
  if ( v5 >= 0x10 )
    j__free(Block);  // 释放堆块
}



// ------------------------------------------------------------
// 容器模板实例族（0x504620~0x507690 区间；list<T>/vector<CnMonsterTemp> 等辅助函数；
//   其中 sub_5046D0/4760/47F0/48F0 为 std::list 容量检查（"list<T> too long"），
//   sub_508F60 为 "vector<T> too long"，属 CRT/STL 实例化，非游戏语义）
// ------------------------------------------------------------

// ------------------------------------------------------------
// 0x504620 sub_504620
//   std::_Fill_n（24 字节元素版）：转调 sub_5044B0 后返回 &pArg1[6*uArg2] 尾地址。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_504620(uint32_t *pArg1, uint32_t *uArg2, uint32_t *uArg3)  // 掉落/奖励对象类别码解析器
{
  sub_5044B0(pArg1, uArg2, uArg3);  // 调 sub_5044B0
  return &pArg1[6 * (uint32_t)uArg2];
}



// ------------------------------------------------------------
// 0x504650 sub_504650
//   std::_Fill_n（16 字节元素版）：转调 sub_4BF340 后返回 nArg1+16*nArg2 尾地址。
// ------------------------------------------------------------
int /*stdcall*/ sub_504650(int nArg1, int nArg2, int nArg3)
{
  sub_4BF340(nArg1, nArg2, nArg3);  // sub_4BF340 —— 16 字节元素填充
  return nArg1 + 16 * nArg2;
}



// ------------------------------------------------------------
// 0x504680 sub_504680
//   怪物/PO 临时条目重置：id=-1、+0x04 标志=1、+0x0C/+0x10 清零、+0x18/+0x1C
//   计数=1、+0x20 清零、+0x2C 起三指针容器释放归零（条目复用前的清场）。
// ------------------------------------------------------------
void /*thiscall*/ sub_504680(void *this)  // 函数: 释放后返回
{
  *(uint32_t *)this = -1;
  *((uint8_t *)this + 4) = 1;  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 2) = 0;  // 写字段 this[2]（宽4字节）
  *((uint32_t *)this + 3) = 0;  // 写字段 this[3]（宽4字节）
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 5) = 0;  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 7) = 1;  // 写字段 this+7（uPathTerm）
  *((uint32_t *)this + 6) = 1;  // 写字段 this[6]（宽4字节）
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  if ( *((uint32_t *)this + 11) != 0 )  // 若 *((uint32_t *)this + 11) != 0
    j__free(*((void **)this + 11));  // 释放堆块
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *((uint32_t *)this + 13) = 0;  // 写字段 this[13]（宽4字节）
}



// ------------------------------------------------------------
// 0x5046D0 sub_5046D0
//   std::list 容量记账（this+8 = 元素计数）：计数 + uArg2 前先查上限
//   97612893，超限抛 "list<T> too long"（length_error）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5046D0(uint32_t *this, unsigned int uArg2)  // 函数: 条件抛异常
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  if ( 97612893 - fld_e2 < uArg2 )  // fld_e2=this+8 物品 id
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(v5);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  result = uArg2 + fld_e2;  // fld_e2=this+8 物品 id
  *(this + 2) = result;  // 写字段 this+2 ← result
  return result;
}



// ------------------------------------------------------------
// 0x504760 sub_504760
//   std::list 容量记账（另一实例）：同 5046D0，上限 0xFFFFFFF。
// ------------------------------------------------------------
int /*thiscall*/ sub_504760(uint32_t *this, unsigned int uArg2)  // 函数: 条件抛异常
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  if ( 0xFFFFFFF - fld_e2 < uArg2 )  // fld_e2=this+8 物品 id
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(v5);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  result = uArg2 + fld_e2;  // fld_e2=this+8 物品 id
  *(this + 2) = result;  // 写字段 this+2 ← result
  return result;
}



// ------------------------------------------------------------
// 0x5047F0 sub_5047F0
//   std::list 容量记账（第四实例）：同 5046D0（this+8 元素计数 + 上限检查）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5047F0(uint32_t *this, unsigned int uArg2)  // 函数: 条件抛异常
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  if ( 82595524 - fld_e2 < uArg2 )  // fld_e2=this+8 物品 id
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(v5);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  result = uArg2 + fld_e2;  // fld_e2=this+8 物品 id
  *(this + 2) = result;  // 写字段 this+2 ← result
  return result;
}



// ------------------------------------------------------------
// 0x504880 sub_504880
//   "vector<T> too long" 异常抛出（length_error），永不返回（vector 容量上限检查失败路径）。
// ------------------------------------------------------------
void /*noreturn*/ sub_504880()  // 函数: 条件抛异常
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
  sub_401740(v1);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x5048F0 sub_5048F0
//   std::list 容量记账（第三实例）：同 5046D0，上限 0x7FFFFFF。
// ------------------------------------------------------------
int /*thiscall*/ sub_5048F0(uint32_t *this, unsigned int uArg2)  // 函数: 条件抛异常
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  if ( 0x7FFFFFF - fld_e2 < uArg2 )  // fld_e2=this+8 物品 id
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(v5);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  result = uArg2 + fld_e2;  // fld_e2=this+8 物品 id
  *(this + 2) = result;  // 写字段 this+2 ← result
  return result;
}



// ------------------------------------------------------------
// 0x504980 sub_504980
//   48 字节节点逐域拷贝构造：{int@+0, int@+4, string@+0x0C, int[4]@+0x24}，
//   字符串经 sub_4014D0 深拷贝【推断：怪物生成/掉落条目节点】。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_504980(uint32_t *this, int nArg2, int nArg3, uint32_t *pArg4)
{
  *this = nArg2;  // *this 写入 nArg2
  *(this + 1) = nArg3;  // 写字段 this+1 ← nArg3
  *(this + 8) = 15;  // 写字段 this+8（nSkillRec8） ← 15
  *(this + 7) = 0;  // 写字段 this+7（uPathTerm） ← 0
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  sub_4014D0((std::_String_base *)(this + 2), pArg4, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(this + 9) = pArg4[7];  // 写字段 this+9 ← pArg4[7]
  *(this + 10) = pArg4[8];  // 写字段 this+10 ← pArg4[8]
  *(this + 11) = pArg4[9];  // 写字段 this+11 ← pArg4[9]
  *(this + 12) = pArg4[10];  // 写字段 this+12（nSkillRec12） ← pArg4[10]
  return this;
}



// ------------------------------------------------------------
// 0x5049E0 sub_5049E0
//   std::copy_backward（36 字节元素版，元素 = {string@+0x04, int@+0x1C, byte@+0x20}）：
//   从尾往头逐 0x24 字节搬移（字符串经 4014D0 深拷贝）。
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
    sub_4014D0((std::_String_base *)nArg32, nArg22, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    *(uint32_t *)(nArg32 + 28) = *(uint32_t *)(nArg22 + 28);  // 写字段 nArg32+28（pPanelVec） ← *(uint32_t *)(nArg22 + 28)
    *(uint8_t *)(nArg32 + 32) = *(uint8_t *)(nArg22 + 32);  // 写字段 nArg32+32（nHeight） ← *(uint8_t *)(nArg22 + 32)
  }
  while ( nArg22 != nArg1 );  // 循环直到 nArg22 != nArg1
  return nArg32;
}



// ------------------------------------------------------------
// 0x504A30 sub_504A30
//   std::_Copy/未初始化填充（36 字节元素版）：[pArg1, nArg2) 逐元素拷贝构造到
//   nArg3 起（sub_4014D0 串拷贝），返回尾地址。
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
  while ( pArg1 != nArg2 )  // 循环直到 pArg1 != nArg2
  {
    LOBYTE(v7) = 1;  // 调 取 16 位值低 8 位
    if ( nArg32 != 0 )
    {
      *(uint32_t *)(nArg32 + 24) = 15;  // 写字段 nArg32+24（nPageMax） ← 15
      *(uint32_t *)(nArg32 + 20) = 0;  // 写字段 nArg32+20（nPage） ← 0
      *(uint8_t *)(nArg32 + 4) = 0;  // 写字段 nArg32+4（pHostObj） ← 0
      sub_4014D0((std::_String_base *)nArg32, pArg1, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      *(uint32_t *)(nArg32 + 28) = *(uint32_t *)(pArg1 + 28);  // 写字段 nArg32+28（pPanelVec） ← *(uint32_t *)(pArg1 + 28)
      *(uint8_t *)(nArg32 + 32) = *(uint8_t *)(pArg1 + 32);  // 写字段 nArg32+32（nHeight） ← *(uint8_t *)(pArg1 + 32)
    }
    nArg32 += 36;
    LOBYTE(v7) = 0;  // 调 取 16 位值低 8 位
    pArg1 += 36;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x504AF0 sub_504AF0
//   36 字节条目默认构造：+0x04 字符串空串、+0x1C = 1（数量默认 1）、
//   +0x20 = 0、+0x24..+0x2C 清零（副本地图 [monster]/[NPC] 生成条目临时构造，
//   sub_5078C0 调用）。
// ------------------------------------------------------------
int /*thiscall*/ sub_504AF0(int this)
{
  *(uint32_t *)(this + 24) = 15;  // 写字段 this+24（nPageMax） ← 15
  *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
  *(uint8_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 32) = 0;  // 写字段 this+32（nHeight） ← 0
  *(uint32_t *)(this + 36) = 0;  // 写字段 this+36（nStateWord36） ← 0
  *(uint32_t *)(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  *(uint32_t *)(this + 28) = 1;  // 写字段 this+28（pPanelVec） ← 1
  return this;
}



// ------------------------------------------------------------
// 0x504B50 sub_504B50
//   28 字节条目重置：id=-1、+0x04/+0x08/+0x0C 清零、+0x14 起三指针容器
//   释放归零（副本地图 [dungeon] 条目等复用前清场，sub_5078C0 调用）。
// ------------------------------------------------------------
void /*thiscall*/ sub_504B50(void *this)  // 函数: 释放后返回
{
  *(uint32_t *)this = -1;
  *((uint32_t *)this + 3) = 0;  // 写字段 this[3]（宽4字节）
  *((uint32_t *)this + 2) = 0;  // 写字段 this[2]（宽4字节）
  *((uint32_t *)this + 1) = 0;  // 写字段 this[1]（宽4字节）
  if ( *((uint32_t *)this + 5) != 0 )  // 若 *((uint32_t *)this + 5) != 0
    j__free(*((void **)this + 5));  // 释放堆块
  *((uint32_t *)this + 5) = 0;  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 6) = 0;  // 写字段 this[6]（宽4字节）
  *((uint32_t *)this + 7) = 0;  // 写字段 this+7（uPathTerm）
}



// ------------------------------------------------------------
// 0x504B90 sub_504B90
//   36 字节条目默认构造（变体）：+0x04 字符串空串、+0x1C = 1、+0x20 = 0
//   （副本地图生成条目【推断：怪物 [monster]/[champion] 槽】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_504B90(int this)
{
  *(uint32_t *)(this + 24) = 15;  // 写字段 this+24（nPageMax） ← 15
  *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
  *(uint8_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(uint8_t *)(this + 32) = 0;  // 写字段 this+32（nHeight） ← 0
  *(uint32_t *)(this + 28) = 1;  // 写字段 this+28（pPanelVec） ← 1
  return this;
}



// ------------------------------------------------------------
// 0x504BF0 sub_504BF0
//   std::vector<8字节元素>::reserve/分配：+4 begin/+8 end/+12 capEnd，
//   超上限 0x1FFFFFFF 抛错（sub_504880）。返回是否分配成功。
// ------------------------------------------------------------
char /*thiscall*/ sub_504BF0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  *(this + 3) = 0;  // 写字段 this+3 ← 0
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x1FFFFFFF )
    sub_504880(this);  // 调 sub_504880
  pMem = (char *)operator new(8 * uArg2);  // 堆分配
  *(this + 3) = &pMem[8 * uArg2];  // 写字段 this+3 ← &pMem[8 * uArg2]
  *(this + 1) = pMem;  // 写字段 this+1 ← pMem
  *(this + 2) = pMem;  // 写字段 this+2 ← pMem
  return 1;
}



// ------------------------------------------------------------
// 0x504C50 sub_504C50
//   std::vector<24字节元素>::reserve/分配：同 504BF0 的 24 字节版（上限 0xAAAAAAA）。
// ------------------------------------------------------------
char /*thiscall*/ sub_504C50(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  *(this + 3) = 0;  // 写字段 this+3 ← 0
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xAAAAAAA )
    sub_504880(this);  // 调 sub_504880
  pMem = (char *)operator new(24 * uArg2);  // 堆分配
  *(this + 3) = &pMem[24 * uArg2];  // 写字段 this+3 ← &pMem[24 * uArg2]
  *(this + 1) = pMem;  // 写字段 this+1 ← pMem
  *(this + 2) = pMem;  // 写字段 this+2 ← pMem
  return 1;
}



// ------------------------------------------------------------
// 0x504CA0 sub_504CA0
//   std::vector<24字节元素>::insert(pos, n, val)（另一实例，同 4FF0D0 逻辑）：
//   容量够 → 尾部腾位；不足 → 扩容三段拷贝重建。
// ------------------------------------------------------------
int /*thiscall*/ sub_504CA0(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)  // 函数: 释放后返回
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v28[0] = *Block;  // v28[0] 写入 *Block
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
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    result = 715827883 * (*(this + 3) - fld_e1);  // this+12 = 技能槽记录次字
    fld_e3 = (*(this + 3) - fld_e1) / 24;  // this+12 = 技能槽记录次字
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 24;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 178956970 - fld_e2 < uArg3 )
      sub_42CB90(this);  // sub_42CB90 —— CRT 桩（vector 长度异常）
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 24;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);  // this+8 = 技能槽记录首字
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 24 >= uArg3 )
      {
        v30 = (int)fld_e23 - 24 * uArg3;
        *(this + 2) = sub_4FF050(v30, fld_e23, fld_e23);  // 写字段 this+2 ← sub_4FF050(v30, fld_e23, fld_e23)
        sub_504430(pArg2, v30, Blockb);  // 调 sub_504430
        return sub_4FEF50(pArg2, pArg2 + 24 * uArg3, v28);  // 调 sub_4FEF50
      }
      else
      {
        sub_4FF050(pArg2, fld_e23, pArg2 + 24 * uArg3);  // 调 sub_4FF050
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 24;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        v29 = 2;
        sub_504620(fld_e25, fld_e24, v28);  // 调 sub_504620
        fld_e26 = 24 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        return sub_4FEF50(pArg2, fld_e26 - 24 * uArg3, v28);  // 调 sub_4FEF50
      }
    }
    else
    {
      if ( 178956970 - (fld_e3 >> 1) >= fld_e3 )  // 若 178956970 - (fld_e3 >> 1) >= fld_e3
        v16 = (fld_e3 >> 1) + fld_e3;
      else
        v16 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 24;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v16 < uArg3 + fld_e27 )
        v16 = uArg3 + sub_4FEF30(this);  // 调 pArg2+4〔宿主对象〕
      v18 = 24 * v16;  // 计算 v18 = 24 * v16
      Blocka = (char *)operator new(24 * v16);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      v29 = 0;
      v31 = sub_4FF050(fld_e12, pArg2, Blocka);  // 调 sub_4FF050
      sub_5044B0(v31, uArg3, v28);  // 调 sub_5044B0
      sub_4FF050(pArg2, *(this + 2), v31 + 24 * uArg3);  // 调 sub_4FF050
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 24;  // this+8 = 技能槽记录首字
      v20 = fld_e13 + uArg3;  // 计算 v20 = fld_e13 + uArg3
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 释放堆块
      *(this + 3) = (int)&Blocka[v18];  // 写字段 this+3 ← (int)&Blocka[v18]
      *(this + 2) = (int)&Blocka[24 * v20];  // 写字段 this+2 ← (int)&Blocka[24 * v20]
      *(this + 1) = (int)Blocka;  // 写字段 this+1 ← (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x504F70 sub_504F70
//   std::vector<16字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（602460/4BF320/453C20/504650）；不足 → 扩容三段拷贝重建。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_504F70(int this, int pArg2, unsigned int uArg3, uint32_t *Block)  // 函数: 释放后返回
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
  v26[0] = *Block;  // v26[0] 写入 *Block
  v6 = Block[2];
  v26[1] = v5;
  v26[3] = Block[3];  // v26[3] 写入 Block[3]
  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  v26[4] = &v25;
  v26[2] = v6;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 12) - fld_4) >> 4;  // this+12 物品类型号
  else
    result = 0;  // result=this+12 物品类型号
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8 物品 id
    else
      fld_8 = 0;  // fld_8=this+8 物品 id
    if ( 0xFFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 物品 id
      sub_42CB90(this);  // sub_42CB90 —— CRT 桩（vector 长度异常）
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8 物品 id
    else
      fld_82 = 0;  // fld_82=this+8 物品 id
    if ( result >= uArg3 + fld_82 )  // result=this+12 物品类型号
    {
      fld_83 = *(void **)(this + 8);  // this+8 物品 id
      Blockb = fld_83;  // fld_83=this+8 物品 id
      if ( ((int)fld_83 - pArg2) >> 4 >= uArg3 )  // fld_83=this+8 物品 id
      {
        v21 = (int)fld_83 - 16 * uArg3;  // fld_83=this+8 物品 id
        *(uint32_t *)(this + 8) = sub_602460(v21, fld_83, fld_83);  // sub_602460 —— 16 字节批量拷贝
        sub_4BF320(pArg2, v21, (int)Blockb);  // sub_4BF320 —— 转发壳
        return sub_453C20(pArg2, pArg2 + 16 * uArg3, v26);  // sub_453C20 —— 16 字节元素区间填充
      }
      else
      {
        sub_602460(pArg2, fld_83, pArg2 + 16 * uArg3);  // sub_602460 —— 16 字节批量拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 4);  // this+8 物品 id
        fld_85 = *(uint32_t *)(this + 8);  // 读字段 fld_85 = this+8（nSkillRec8）
        v27 = 2;
        sub_504650(fld_85, fld_84, v26);  // 调 sub_504650
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);  // this+8 物品 id
        *(uint32_t *)(this + 8) = fld_86;  // 写字段 this+8（nSkillRec8） ← fld_86
        return sub_453C20(pArg2, fld_86 - 16 * uArg3, v26);  // sub_453C20 —— 16 字节元素区间填充
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )  // 若 0xFFFFFFF - (result >> 1) >= result
        v12 = (result >> 1) + result;  // result=this+12 物品类型号
      else
        v12 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8 物品 id
      else
        fld_87 = 0;  // fld_87=this+8 物品 id
      if ( v12 < uArg3 + fld_87 )  // fld_87=this+8 物品 id
      {
        if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8 物品 id
        else
          fld_88 = 0;  // fld_88=this+8 物品 id
        v12 = uArg3 + fld_88;  // 计算 v12 = uArg3 + fld_88
      }
      v28 = 16 * v12;  // 计算 v28 = 16 * v12
      Blocka = (char *)operator new(16 * v12);  // 堆分配
      fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
      v27 = 0;
      v15 = (uint32_t *)sub_602460(fld_42, pArg2, Blocka);  // sub_602460 —— 16 字节批量拷贝
      sub_4BF340(v15, (uint32_t *)uArg3, v26);  // sub_4BF340 —— 16 字节元素填充
      sub_602460(pArg2, *(uint32_t *)(this + 8), &v15[4 * uArg3]);  // sub_602460 —— 16 字节批量拷贝
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;  // this+8 物品 id
      else
        fld_89 = 0;  // fld_89=this+8 物品 id
      v18 = fld_89 + uArg3;  // 计算 v18 = fld_89 + uArg3
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &Blocka[v28];  // 写字段 this+12（nSkillRec12） ← &Blocka[v28]
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];  // 写字段 this+8（nSkillRec8） ← &Blocka[16 * v18]
      *(uint32_t *)(this + 4) = Blocka;  // 写字段 this+4（pHostObj） ← Blocka
      return (unsigned int)Blocka;
    }
  }
  return result;  // result=this+12 物品类型号
}


// ------------------------------------------------------------
// 0x5051D0 sub_5051D0
//   std::list 树/链节点堆构造（0x34 字节）：值部分（48 字节）经 sub_504980
//   逐域拷贝（{int,int,string,int[4]}）。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_5051D0(int nArg1, int nArg2, uint32_t *uArg3)  // 函数定义: 建节点插到哨兵后
{
  uint32_t *pMem; // esi
  void *v5[9]; // [esp+0h] [ebp-24h] BYREF

  v5[5] = v5;
  pMem = operator new(0x34u);  // 堆分配
  v5[4] = pMem;
  v5[8] = (void *)1;  // v5[8] 写入 (void *)1
  v5[3] = pMem;
  if ( pMem != nullptr )
    sub_504980(pMem, nArg1, nArg2, uArg3);  // 调 sub_504980
  return pMem;
}



// ------------------------------------------------------------
// 0x505250 sub_505250
//   std::vector<8字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（44BD30/44BD00/5E51F0/41FEB0）；不足 → 扩容三段拷贝重建。
// ------------------------------------------------------------
void /*thiscall*/ sub_505250(int this, int nArg2, unsigned int uArg3, int pArg4)  // 函数: 释放后返回
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
  v28[0] = *(void **)pArg4;  // v28[0] 写入 *(void **)pArg4
  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;  // this+12 物品类型号
  else
    fld_C = 0;  // fld_C=this+12 物品类型号
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
    else
      fld_8 = 0;  // fld_8=this+8 物品 id
    if ( 0x1FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 物品 id
      sub_504880(this);  // 调 sub_504880
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
    else
      fld_82 = 0;  // fld_82=this+8 物品 id
    if ( fld_C >= uArg3 + fld_82 )  // fld_C=this+12 物品类型号
    {
      fld_83 = *(uint32_t *)(this + 8);  // 读字段 fld_83 = this+8（nSkillRec8）
      v20 = (fld_83 - nArg2) >> 3 < uArg3;  // fld_83=this+8 nSkillRec8
      v21 = 8 * uArg3;  // 计算 v21 = 8 * uArg3
      v30 = 8 * uArg3;  // 计算 v30 = 8 * uArg3
      fld_832 = fld_83;  // fld_83=this+8 nSkillRec8
      if ( v20 )  // 若 v20
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);  // sub_44BD30 —— 8 字节元素正向拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);  // this+8 物品 id
        fld_85 = *(uint32_t *)(this + 8);  // 读字段 fld_85 = this+8（nSkillRec8）
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);  // sub_5E51F0 —— 填充补足尾段
        fld_86 = v30 + *(uint32_t *)(this + 8);  // this+8 物品 id
        *(uint32_t *)(this + 8) = fld_86;  // 写字段 this+8（nSkillRec8） ← fld_86
        sub_41FEB0(nArg2, fld_86 - v30, v28);  // sub_41FEB0 —— 8B 元素区间拷贝
      }
      else
      {
        v23 = fld_83 - v21;  // 计算 v23 = fld_83 - v21
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);  // sub_44BD30 —— 8 字节元素正向拷贝
        sub_44BD00(nArg2, v23, fld_832);  // sub_44BD00 —— 8 字节元素反向拷贝
        sub_41FEB0(nArg2, nArg2 + v30, v28);  // sub_41FEB0 —— 8B 元素区间拷贝
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )  // 若 0x1FFFFFFF - (fld_C >> 1) >= fld_C
        v11 = (fld_C >> 1) + fld_C;  // fld_C=this+12 物品类型号
      else
        v11 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
      else
        fld_87 = 0;  // fld_87=this+8 物品 id
      if ( v11 < uArg3 + fld_87 )  // fld_87=this+8 物品 id
      {
        if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
        else
          fld_88 = 0;  // fld_88=this+8 物品 id
        v11 = uArg3 + fld_88;  // 计算 v11 = uArg3 + fld_88
      }
      v31 = 8 * v11;  // 计算 v31 = 8 * v11
      pMem = (char *)operator new(8 * v11);  // 堆分配
      fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);  // sub_44BD30 —— 8 字节元素正向拷贝
      sub_63A7C0(v32, uArg3, v28);  // sub_63A7C0 —— 强化结果公共件（30 行）
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);  // sub_44BD30 —— 8 字节元素正向拷贝
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;  // this+8 物品 id
      else
        fld_89 = 0;  // fld_89=this+8 物品 id
      v17 = fld_89 + uArg3;  // 计算 v17 = fld_89 + uArg3
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &pMem[v31];  // 写字段 this+12（nSkillRec12） ← &pMem[v31]
      *(uint32_t *)(this + 8) = &pMem[8 * v17];  // 写字段 this+8（nSkillRec8） ← &pMem[8 * v17]
      *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
    }
  }
}


// ------------------------------------------------------------
// 0x5054A0 sub_5054A0
//   std::vector<24字节元素>::insert(pos, n, val)：同 504CA0 的另一实例
//   （上限检查走 sub_504880；搬运 4FF050/504430/4FEF50/504620）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5054A0(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)  // 函数: 释放后返回
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v28[0] = *Block;  // v28[0] 写入 *Block
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
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    result = 715827883 * (*(this + 3) - fld_e1);  // this+12 = 技能槽记录次字
    fld_e3 = (*(this + 3) - fld_e1) / 24;  // this+12 = 技能槽记录次字
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 24;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 178956970 - fld_e2 < uArg3 )
      sub_504880(this);  // 调 sub_504880
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 24;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);  // this+8 = 技能槽记录首字
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 24 >= uArg3 )
      {
        v30 = (int)fld_e23 - 24 * uArg3;
        *(this + 2) = sub_4FF050(v30, fld_e23, fld_e23);  // 写字段 this+2 ← sub_4FF050(v30, fld_e23, fld_e23)
        sub_504430(pArg2, v30, Blockb);  // 调 sub_504430
        return sub_4FEF50(pArg2, pArg2 + 24 * uArg3, v28);  // 调 sub_4FEF50
      }
      else
      {
        sub_4FF050(pArg2, fld_e23, pArg2 + 24 * uArg3);  // 调 sub_4FF050
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 24;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        v29 = 2;
        sub_504620(fld_e25, fld_e24, v28);  // 调 sub_504620
        fld_e26 = 24 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        return sub_4FEF50(pArg2, fld_e26 - 24 * uArg3, v28);  // 调 sub_4FEF50
      }
    }
    else
    {
      if ( 178956970 - (fld_e3 >> 1) >= fld_e3 )  // 若 178956970 - (fld_e3 >> 1) >= fld_e3
        v16 = (fld_e3 >> 1) + fld_e3;
      else
        v16 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 24;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v16 < uArg3 + fld_e27 )
        v16 = uArg3 + sub_4FEF30(this);  // 调 pArg2+4〔宿主对象〕
      v18 = 24 * v16;  // 计算 v18 = 24 * v16
      Blocka = (char *)operator new(24 * v16);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      v29 = 0;
      v31 = sub_4FF050(fld_e12, pArg2, Blocka);  // 调 sub_4FF050
      sub_5044B0(v31, uArg3, v28);  // 调 sub_5044B0
      sub_4FF050(pArg2, *(this + 2), v31 + 24 * uArg3);  // 调 sub_4FF050
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 24;  // this+8 = 技能槽记录首字
      v20 = fld_e13 + uArg3;  // 计算 v20 = fld_e13 + uArg3
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 释放堆块
      *(this + 3) = (int)&Blocka[v18];  // 写字段 this+3 ← (int)&Blocka[v18]
      *(this + 2) = (int)&Blocka[24 * v20];  // 写字段 this+2 ← (int)&Blocka[24 * v20]
      *(this + 1) = (int)Blocka;  // 写字段 this+1 ← (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x505770 sub_505770
//   std::vector<20字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位；不足 → 扩容三段拷贝重建（上限检查 sub_4CEAB0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_505770(int *this, uint32_t *pArg2, unsigned int uArg3, uint32_t *Block)  // 函数: 释放后返回
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v26[0] = *Block;  // v26[0] 写入 *Block
  v7 = Block[2];
  v26[1] = v5;
  v8 = Block[3];
  result = Block[4];
  v26[5] = &v25;
  v26[2] = v7;
  v26[3] = v8;
  v26[4] = result;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    result = 1717986919 * (*(this + 3) - fld_e1);  // this+12 = 技能槽记录次字
    fld_e3 = (*(this + 3) - fld_e1) / 20;  // this+12 = 技能槽记录次字
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 20;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 214748364 - fld_e2 < uArg3 )
      sub_4CEAB0(this);  // 调 sub_4CEAB0
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 20;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);  // this+8 = 技能槽记录首字
      Blockb = fld_e23;
      if ( ((uint8_t *)fld_e23 - (uint8_t *)pArg2) / 20 >= uArg3 )
      {
        v28 = (int)fld_e23 - 20 * uArg3;
        *(this + 2) = sub_4FBDE0(v28, fld_e23, fld_e23);  // sub_4FBDE0 —— 20 字节元素正向区间拷贝（逐槽空目标防御）
        sub_57A4A0(pArg2, v28, Blockb);  // sub_57A4A0 —— 调 sub_57A4A0
        return (int)sub_655A00(pArg2, &pArg2[5 * uArg3], v26);  // sub_655A00 —— 20 字节记录正向区间拷贝
      }
      else
      {
        sub_4FBDE0(pArg2, fld_e23, &pArg2[5 * uArg3]);  // sub_4FBDE0 —— 20 字节元素正向区间拷贝（逐槽空目标防御）
        fld_e24 = uArg3 - (*(this + 2) - (int)pArg2) / 20;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        v27 = 2;
        sub_57A4C0(fld_e25, fld_e24, v26);  // sub_57A4C0 —— 调 sub_57A4C0
        fld_e26 = 20 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        return (int)sub_655A00(pArg2, (uint32_t *)(fld_e26 - 20 * uArg3), v26);  // sub_655A00 —— 20 字节记录正向区间拷贝
      }
    }
    else
    {
      if ( 214748364 - (fld_e3 >> 1) >= fld_e3 )  // 若 214748364 - (fld_e3 >> 1) >= fld_e3
        v14 = (fld_e3 >> 1) + fld_e3;
      else
        v14 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 20;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v14 < uArg3 + fld_e27 )
        v14 = uArg3 + sub_45E580(this);  // sub_45E580 —— vector::size（+64 掉落概率表）
      v16 = 20 * v14;  // 计算 v16 = 20 * v14
      Blocka = (char *)operator new(20 * v14);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      v27 = 0;
      v29 = (uint32_t *)sub_4FBDE0(fld_e12, pArg2, Blocka);  // sub_4FBDE0 —— 20 字节元素正向区间拷贝（逐槽空目标防御）
      sub_655A40(v29, (uint32_t *)uArg3, v26);  // sub_655A40 —— 20 字节记录逐元素填充
      sub_4FBDE0(pArg2, *(this + 2), &v29[5 * uArg3]);  // sub_4FBDE0 —— 20 字节元素正向区间拷贝（逐槽空目标防御）
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 20;  // this+8 = 技能槽记录首字
      v18 = fld_e13 + uArg3;  // 计算 v18 = fld_e13 + uArg3
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 释放堆块
      *(this + 3) = (int)&Blocka[v16];  // 写字段 this+3 ← (int)&Blocka[v16]
      *(this + 2) = (int)&Blocka[20 * v18];  // 写字段 this+2 ← (int)&Blocka[20 * v18]
      *(this + 1) = (int)Blocka;  // 写字段 this+1 ← (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x505A30 sub_505A30
//   std::vector<12字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（59EE30/504450/5043B0/5E51C0）；不足 → 扩容三段拷贝重建。
// ------------------------------------------------------------
int /*thiscall*/ sub_505A30(int *this, int pArg2, unsigned int uArg3, int *Block)  // 函数: 释放后返回
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    result = 715827883 * (*(this + 3) - fld_e1);  // this+12 = 技能槽记录次字
    fld_e3 = (*(this + 3) - fld_e1) / 12;  // this+12 = 技能槽记录次字
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_4CEAB0(this);  // 调 sub_4CEAB0
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);  // this+8 = 技能槽记录首字
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 12 >= uArg3 )
      {
        v27 = (int)fld_e23 - 12 * uArg3;
        *(this + 2) = sub_59EE30(v27, fld_e23, fld_e23);  // sub_59EE30 —— 三元组块搬移辅助
        sub_504450(pArg2, v27, Blockb);  // sub_504450 —— 搬移插入位后元素
        return sub_5043B0(pArg2, pArg2 + 12 * uArg3, v25);  // sub_5043B0 —— 在插入位填 n 条
      }
      else
      {
        sub_59EE30(pArg2, fld_e23, pArg2 + 12 * uArg3);  // sub_59EE30 —— 三元组块搬移辅助
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 12;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);  // sub_5E51C0 —— 填充补足尾段
        fld_e26 = 12 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        return sub_5043B0(pArg2, fld_e26 - 12 * uArg3, v25);  // sub_5043B0 —— 在插入位填 n 条
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )  // 若 357913941 - (fld_e3 >> 1) >= fld_e3
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);  // sub_4DA030 —— v13 = 插入数 + sub_4DA030（当前数）
      v15 = 12 * v13;  // 计算 v15 = 12 * v13
      Blocka = (char *)operator new(12 * v13);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pArg2, Blocka);  // sub_59EE30 —— 三元组块搬移辅助
      sub_623C10(v28, uArg3, v25);  // sub_623C10 —— 就地构造（拷贝构造 1 个）
      sub_59EE30(pArg2, *(this + 2), v28 + 12 * uArg3);  // sub_59EE30 —— 三元组块搬移辅助
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 12;  // this+8 = 技能槽记录首字
      v17 = fld_e13 + uArg3;  // 计算 v17 = fld_e13 + uArg3
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 释放堆块
      *(this + 3) = (int)&Blocka[v15];  // 写字段 this+3 ← (int)&Blocka[v15]
      *(this + 2) = (int)&Blocka[12 * v17];  // 写字段 this+2 ← (int)&Blocka[12 * v17]
      *(this + 1) = (int)Blocka;  // 写字段 this+1 ← (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x505CE0 sub_505CE0
//   std::vector<8字节元素> 复制构造辅助：按源 vector（pArg2+4/+8）大小
//   reserve（sub_504BF0）后整段 copy（sub_44BD30）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_505CE0(uint32_t *this, int pArg2)  // 函数定义: 整段复制
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

  v3 = *(uint32_t *)(pArg2 + 4);  // 读字段 v3 = pArg2+4（pHostObj）
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( sub_504BF0(this, v4) != 0 )  // 若 sub_504BF0(this, v4) != 0
  {
    fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
    v7 = *(uint32_t *)(pArg2 + 8);  // 读字段 v7 = pArg2+8（nSkillRec8）
    v6 = *(uint32_t *)(pArg2 + 4);  // 读字段 v6 = pArg2+4（pHostObj）
    v12 = 0;
    *(this + 2) = sub_44BD30(v6, v7, fld_e1);  // sub_44BD30 —— 8 字节元素正向拷贝
  }
  return this;
}



// ------------------------------------------------------------
// 0x505D80 sub_505D80
//   std::vector<24字节元素> 复制构造辅助：按源 vector（pArg2+4/+8）大小
//   reserve（sub_504C50）后整段 copy（sub_4FF050）。
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

  v2 = *(uint32_t *)(pArg2 + 4);  // 读字段 v2 = pArg2+4（pHostObj）
  v10 = &v8;
  pThis = this;
  if ( v2 != 0 )
    v2 = (int)(*(uint32_t *)(pArg2 + 8) - v2) / 24;
  if ( sub_504C50(this, v2) != 0 )  // 若 sub_504C50(this, v2) != 0
  {
    fld_e1 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
    v6 = *(uint32_t **)(pArg2 + 8);
    v5 = *(uint32_t **)(pArg2 + 4);
    v11 = 0;
    *(this + 2) = sub_4FF050(v5, v6, fld_e1);  // 写字段 this+2 ← sub_4FF050(v5, v6, fld_e1)
  }
  return this;
}



// ------------------------------------------------------------
// 0x505E20 sub_505E20
//   std::fill（36 字节元素版）：[nArg1,nArg2) 区间逐元素从 pArg3 拷贝
//   {string@+0x04, int@+0x1C, byte@+0x20}（已有元素的赋值式填充）。
// ------------------------------------------------------------
int /*cdecl*/ sub_505E20(int nArg1, int nArg2, int pArg3)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 36 )  // 循环：i = nArg1; i != nArg2; i += 36
  {
    sub_4014D0((std::_String_base *)i, pArg3, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    result = *(uint32_t *)(pArg3 + 28);  // 读字段 result = pArg3+28（pPanelVec）
    *(uint32_t *)(i + 28) = result;  // 写字段 i+28（pPanelVec） ← result
    *(uint8_t *)(i + 32) = *(uint8_t *)(pArg3 + 32);  // 写字段 i+32（nHeight） ← *(uint8_t *)(pArg3 + 32)
  }
  return result;
}



// ------------------------------------------------------------
// 0x505E60 sub_505E60
//   std::copy_backward（36 字节元素版）：转调 sub_5049E0。
// ------------------------------------------------------------
int /*cdecl*/ sub_505E60(int nArg1, int nArg2, int nArg3)  // 函数: 转发 ·sub_5049E0
{
  return sub_5049E0(nArg1, nArg2, nArg3);  // 调 sub_5049E0
}



// ------------------------------------------------------------
// 0x505E80 sub_505E80
//   std::_Fill_n 未初始化构造（36 字节元素版）：从 nArg1 起连续 nArg2 个元素
//   从 pArg3 拷贝构造（{string@+0x04, int@+0x1C, byte@+0x20}）。
// ------------------------------------------------------------
int /*cdecl*/ sub_505E80(int nArg1, int nArg2, int pArg3)  // 函数定义: 后返回 nArg1+36*nArg2 尾地址
{
  int nArg12; // esi
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v5[5] = v5;
  v5[4] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    v5[3] = nArg12;
    LOBYTE(v6) = 1;  // 调 取 16 位值低 8 位
    if ( nArg12 != 0 )
    {
      *(uint32_t *)(nArg12 + 24) = 15;  // 写字段 nArg12+24（nPageMax） ← 15
      *(uint32_t *)(nArg12 + 20) = 0;  // 写字段 nArg12+20（nPage） ← 0
      *(uint8_t *)(nArg12 + 4) = 0;  // 写字段 nArg12+4（pHostObj） ← 0
      sub_4014D0((std::_String_base *)nArg12, pArg3, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      result = *(uint32_t *)(pArg3 + 28);  // 读字段 result = pArg3+28（pPanelVec）
      *(uint32_t *)(nArg12 + 28) = result;  // 写字段 nArg12+28（pPanelVec） ← result
      *(uint8_t *)(nArg12 + 32) = *(uint8_t *)(pArg3 + 32);  // 写字段 nArg12+32（nHeight） ← *(uint8_t *)(pArg3 + 32)
    }
    nArg12 += 36;
    LOBYTE(v6) = 0;  // 调 取 16 位值低 8 位
    --nArg2;  // 计数自减 nArg2
  }
  return result;
}



// ------------------------------------------------------------
// 0x505F40 sub_505F40
//   std::list::push_front（16 字节值）：sub_504470 建节点插到哨兵后，
//   元素计数 +1（sub_504760 容量检查）。
// ------------------------------------------------------------
int /*thiscall*/ sub_505F40(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v4 = sub_504470(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);  // 调 sub_504470
  result = sub_504760(this, 1u);  // 调 sub_504760
  *(uint32_t *)(fld_e1 + 4) = v4;  // 写字段 fld_e1+4（pHostObj） ← v4
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x505F80 sub_505F80
//   std::vector<24字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_504CA0 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_505F80(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *Block)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (int)&pszArg3[-fld_e1] / 24;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_504CA0(this, pszArg3, 1u, Block);  // 调 sub_504CA0
  *uArg2 = *(this + 1) + 24 * v6;  // *uArg2 写入 *(this + 1) + 24 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x505FF0 sub_505FF0
//   std::vector<int>::resize(n)（4 字节元素）：目标条数 ≤ 现有 → 截尾；
//   不足 → sub_430C80 扩容并补构造。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_505FF0(unsigned int *this, unsigned int uArg2, int nArg3)
{
  int fld_e1; // edx
  unsigned int result; // eax
  int fld_e2; // eax
  void *v7; // edx

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    result = (int)(*(this + 2) - fld_e1) >> 2;  // this+8 = 技能槽记录首字
  else
    result = 0;
  if ( result >= uArg2 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    {
      result = *(this + 2);  // 读字段 result = this+2
      if ( uArg2 < (int)(result - fld_e1) >> 2 )  // 若 uArg2 < (int)(result - fld_e1) >> 2
      {
        v7 = (void *)(fld_e1 + 4 * uArg2);  // fld_e1=this+4 宿主对象
        if ( v7 != (void *)result )  // 若 v7 != (void *)result
        {
          result = (unsigned int)memcpy_0(v7, (const void *)result, 0);  // result=this+8 物品 id
          *(this + 2) = result;  // 写字段 this+2 ← result
        }
      }
    }
  }
  else
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (int)(*(this + 2) - fld_e1) >> 2;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    return sub_430C80((void *)*(this + 2), uArg2 - fld_e2, (int)&nArg3);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
  }
  return result;  // result=this+8 物品 id
}



// ------------------------------------------------------------
// 0x506080 sub_506080
//   std::vector<24字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_5054A0 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506080(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *Block)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (int)&pszArg3[-fld_e1] / 24;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_5054A0(this, pszArg3, 1u, Block);  // 调 sub_5054A0
  *uArg2 = *(this + 1) + 24 * v6;  // *uArg2 写入 *(this + 1) + 24 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x5060F0 sub_5060F0
//   std::vector<12字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_505A30 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5060F0(int *this, uint32_t *uArg2, uint32_t *uArg3, int *Block)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )  // fld_e1=this+4 宿主对象
    v6 = ((int)uArg3 - fld_e1) / 12;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_505A30(this, uArg3, 1u, Block);  // 调 sub_505A30
  *uArg2 = *(this + 1) + 12 * v6;  // *uArg2 写入 *(this + 1) + 12 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x506160 sub_506160
//   std::vector<20字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_505770 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506160(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *Block)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 20 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (int)&pszArg3[-fld_e1] / 20;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_505770(this, pszArg3, 1u, Block);  // 调 sub_505770
  *uArg2 = *(this + 1) + 20 * v6;  // *uArg2 写入 *(this + 1) + 20 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x5061D0 sub_5061D0
//   56 字节元素拷贝构造：{int@0, byte@4, int[8]@+8..+0x24, +0x28 处成员
//   经 sub_435020 拷贝}（副本地图 [monster] 生成条目等【推断】）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5061D0(uint8_t *this, int pArg2)
{
  *(uint32_t *)this = *(uint32_t *)pArg2;
  *(this + 4) = *(uint8_t *)(pArg2 + 4);  // 写字段 this+4（pHostObj） ← *(uint8_t *)(pArg2 + 4)
  *((uint32_t *)this + 2) = *(uint32_t *)(pArg2 + 8);  // 写字段 this[2]（宽4字节）
  *((uint32_t *)this + 3) = *(uint32_t *)(pArg2 + 12);  // 写字段 this[3]（宽4字节）
  *((uint32_t *)this + 4) = *(uint32_t *)(pArg2 + 16);  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 5) = *(uint32_t *)(pArg2 + 20);  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 6) = *(uint32_t *)(pArg2 + 24);  // 写字段 this[6]（宽4字节）
  *((uint32_t *)this + 7) = *(uint32_t *)(pArg2 + 28);  // 写字段 this+7（uPathTerm）
  *((uint32_t *)this + 8) = *(uint32_t *)(pArg2 + 32);  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = *(uint32_t *)(pArg2 + 36);  // 写字段 this[9]（宽4字节）
  sub_435020((void *)(pArg2 + 40));  // sub_435020 —— uint32 向量整体赋值
  return this;
}



// ------------------------------------------------------------
// 0x506230 sub_506230
//   52 字节块拷贝构造：9 个 dword 逐个拷贝 + +0x24 起的 vector<8字节>
//   经 sub_505CE0 整段复制。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506230(uint32_t *this, uint32_t *pArg2)
{
  *this = *pArg2;  // *this 写入 *pArg2
  *(this + 1) = pArg2[1];  // 写字段 this+1 ← pArg2[1]
  *(this + 2) = pArg2[2];  // 写字段 this+2 ← pArg2[2]
  *(this + 3) = pArg2[3];  // 写字段 this+3 ← pArg2[3]
  *(this + 4) = pArg2[4];  // 写字段 this+4（pHostObj） ← pArg2[4]
  *(this + 5) = pArg2[5];  // 写字段 this+5 ← pArg2[5]
  *(this + 6) = pArg2[6];  // 写字段 this+6 ← pArg2[6]
  *(this + 7) = pArg2[7];  // 写字段 this+7（uPathTerm） ← pArg2[7]
  *(this + 8) = pArg2[8];  // 写字段 this+8（nSkillRec8） ← pArg2[8]
  sub_505CE0(this + 9, (int)(pArg2 + 9));  // 调 sub_505CE0
  return this;
}



// ------------------------------------------------------------
// 0x506280 sub_506280
//   std::copy_backward（56 字节元素版）：从尾往头逐 0x38 字节搬移，
//   +0x28 处容器经 sub_4ED3F0 深拷贝。
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
    *(uint8_t *)(nArg32 + 4) = *(uint8_t *)(nArg22 + 4);  // 写字段 nArg32+4（pHostObj） ← *(uint8_t *)(nArg22 + 4)
    *(uint32_t *)(nArg32 + 8) = *(uint32_t *)(nArg22 + 8);  // 写字段 nArg32+8（nSkillRec8） ← *(uint32_t *)(nArg22 + 8)
    *(uint32_t *)(nArg32 + 12) = *(uint32_t *)(nArg22 + 12);  // 写字段 nArg32+12（nSkillRec12） ← *(uint32_t *)(nArg22 + 12)
    *(uint32_t *)(nArg32 + 16) = *(uint32_t *)(nArg22 + 16);  // 写字段 nArg32+16（nChannelTypeSel） ← *(uint32_t *)(nArg22 + 16)
    *(uint32_t *)(nArg32 + 20) = *(uint32_t *)(nArg22 + 20);  // 写字段 nArg32+20（nPage） ← *(uint32_t *)(nArg22 + 20)
    *(uint32_t *)(nArg32 + 24) = *(uint32_t *)(nArg22 + 24);  // 写字段 nArg32+24（nPageMax） ← *(uint32_t *)(nArg22 + 24)
    *(uint32_t *)(nArg32 + 28) = *(uint32_t *)(nArg22 + 28);  // 写字段 nArg32+28（pPanelVec） ← *(uint32_t *)(nArg22 + 28)
    *(uint32_t *)(nArg32 + 32) = *(uint32_t *)(nArg22 + 32);  // 写字段 nArg32+32（nHeight） ← *(uint32_t *)(nArg22 + 32)
    *(uint32_t *)(nArg32 + 36) = *(uint32_t *)(nArg22 + 36);  // 写字段 nArg32+36（nStateWord36） ← *(uint32_t *)(nArg22 + 36)
    sub_4ED3F0(nArg32 + 40, nArg22 + 40);  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
  }
  while ( nArg22 != nArg1 );  // 循环直到 nArg22 != nArg1
  return nArg32;
}



// ------------------------------------------------------------
// 0x506300 sub_506300
//   生成/掉落条目重置（48 字节布局）：id=-1、+0x04 标志=1、+0x18/+0x1C 计数=1、
//   +0x20 清零、+0x2C 三指针容器释放归零（sub_5078C0 副本地图解析器用）。
// ------------------------------------------------------------
void */*thiscall*/ sub_506300(void *this)
{
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *((uint32_t *)this + 13) = 0;  // 写字段 this[13]（宽4字节）
  *(uint32_t *)this = -1;
  *((uint8_t *)this + 4) = 1;  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 2) = 0;  // 写字段 this[2]（宽4字节）
  *((uint32_t *)this + 3) = 0;  // 写字段 this[3]（宽4字节）
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 5) = 0;  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 7) = 1;  // 写字段 this+7（uPathTerm）
  *((uint32_t *)this + 6) = 1;  // 写字段 this[6]（宽4字节）
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  if ( *((uint32_t *)this + 11) != 0 )  // 若 *((uint32_t *)this + 11) != 0
    j__free(*((void **)this + 11));  // 释放堆块
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *((uint32_t *)this + 13) = 0;  // 写字段 this[13]（宽4字节）
  return this;
}



// ------------------------------------------------------------
// 0x506360 sub_506360
//   生成/掉落条目重置（变体）：+0x00=0、+0x04/+0x08=1、+0x18/+0x1C/+0x20=-1、
//   +0x28 三指针容器释放归零。
// ------------------------------------------------------------
void */*thiscall*/ sub_506360(void *this)
{
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *((uint32_t *)this + 2) = 1;  // 写字段 this[2]（宽4字节）
  *((uint32_t *)this + 1) = 1;  // 写字段 this[1]（宽4字节）
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 3) = 0;  // 写字段 this[3]（宽4字节）
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 5) = 0;  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 6) = -1;  // 写字段 this[6]（宽4字节）
  *((uint32_t *)this + 8) = -1;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 7) = -1;  // 写字段 this+7（uPathTerm）
  if ( *((uint32_t *)this + 10) != 0 )  // 若 *((uint32_t *)this + 10) != 0
    j__free(*((void **)this + 10));  // 释放堆块
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  return this;
}



// ------------------------------------------------------------
// 0x5063B0 sub_5063B0
//   std::vector<24字节元素>::push_back：容量够 → 在 +8 end 直写（sub_5044B0）；
//   不够 → 转调 sub_505F80 插入路径扩容。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5063B0(int this, uint32_t *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 24;  // this+8 物品 id
  else
    fld_8 = 0;  // fld_8=this+8 物品 id
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 24 )  // this+12 物品类型号
    return sub_505F80((int *)this, &Block, *(char **)(this + 8), Block);  // 调 sub_505F80
  fld_82 = *(uint32_t **)(this + 8);  // this+8 物品 id
  result = sub_5044B0(fld_82, (uint32_t *)1, Block);  // 调 sub_5044B0
  *(uint32_t *)(this + 8) = fld_82 + 6;  // 写字段 this+8（nSkillRec8） ← fld_82 + 6
  return result;
}



// ------------------------------------------------------------
// 0x506440 sub_506440
//   std::vector<16字节元素>::push_back：容量够 → 在 end 直写（sub_4BF340）；
//   不够 → 转调 sub_504F70 插入路径扩容。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_506440(int *this, uint32_t *Block)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  unsigned int result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 4;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 4 )  // fld_e1=this+4 宿主对象
    return sub_504F70((int)this, *(this + 2), 1u, Block);  // 调 sub_504F70
  fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
  result = sub_4BF340(fld_e22, 1, Block);  // sub_4BF340 —— 16 字节元素填充
  *(this + 2) = fld_e22 + 16;  // 写字段 this+2 ← fld_e22 + 16
  return result;
}



// ------------------------------------------------------------
// 0x5064B0 sub_5064B0
//   std::list::push_front（48 字节值）：sub_5051D0 建节点插到哨兵后，
//   元素计数 +1（sub_5046D0 容量检查）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5064B0(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v4 = sub_5051D0(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);  // 调 sub_5051D0
  result = sub_5046D0(this, 1u);  // 调 sub_5046D0
  *(uint32_t *)(fld_e1 + 4) = v4;  // 写字段 fld_e1+4（pHostObj） ← v4
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x5064F0 sub_5064F0
//   std::vector<8字节元素>::push_back：容量够 → 在 end 直写（sub_63A7C0）；
//   不够 → 转调 sub_505250 插入路径扩容。
// ------------------------------------------------------------
void /*thiscall*/ sub_5064F0(int *this, int nArg2)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 3;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 3 )  // fld_e1=this+4 宿主对象
  {
    fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
    sub_63A7C0(fld_e22, 1, nArg2);  // sub_63A7C0 —— 强化结果公共件（30 行）
    *(this + 2) = fld_e22 + 8;  // 写字段 this+2 ← fld_e22 + 8
  }
  else
  {
    sub_505250((int)this, *(this + 2), 1u, nArg2);  // 调 sub_505250
  }
}



// ------------------------------------------------------------
// 0x506560 sub_506560
//   std::vector<24字节元素>::push_back：容量够 → 在 end 直写（sub_5044B0）；
//   不够 → 转调 sub_506080 插入路径扩容。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506560(int this, uint32_t *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 24;  // this+8 物品 id
  else
    fld_8 = 0;  // fld_8=this+8 物品 id
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 24 )  // this+12 物品类型号
    return sub_506080((int *)this, &Block, *(char **)(this + 8), Block);  // 调 sub_506080
  fld_82 = *(uint32_t **)(this + 8);  // this+8 物品 id
  result = sub_5044B0(fld_82, (uint32_t *)1, Block);  // 调 sub_5044B0
  *(uint32_t *)(this + 8) = fld_82 + 6;  // 写字段 this+8（nSkillRec8） ← fld_82 + 6
  return result;
}



// ------------------------------------------------------------
// 0x5065F0 sub_5065F0
//   std::vector<20字节元素>::push_back：容量够 → 在 end 直写（sub_655A40）；
//   不够 → 转调 sub_506160 插入路径扩容。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5065F0(int this, uint32_t *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  int fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 20;  // this+8 物品 id
  else
    fld_8 = 0;  // fld_8=this+8 物品 id
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 20 )  // this+12 物品类型号
    return sub_506160((int *)this, &Block, *(char **)(this + 8), Block);  // 调 sub_506160
  fld_82 = *(uint32_t *)(this + 8);  // 读字段 fld_82 = this+8（nSkillRec8）
  result = (uint32_t *)sub_655A40(fld_82, 1, Block);  // sub_655A40 —— 20 字节记录逐元素填充
  *(uint32_t *)(this + 8) = fld_82 + 20;  // 写字段 this+8（nSkillRec8） ← fld_82 + 20
  return result;
}



// ------------------------------------------------------------
// 0x506680 sub_506680
//   std::vector<12字节元素>::push_back：容量够 → 在 end 直写（sub_623C10）；
//   不够 → 转调 sub_5060F0 插入路径扩容。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506680(int *this, int *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 12 )  // fld_e1=this+4 宿主对象
    return sub_5060F0(this, &Block, (uint32_t *)*(this + 2), Block);  // 调 sub_5060F0
  fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
  result = (uint32_t *)sub_623C10(fld_e22, 1, Block);  // sub_623C10 —— 就地构造（拷贝构造 1 个）
  *(this + 2) = fld_e22 + 12;  // 写字段 this+2 ← fld_e22 + 12
  return result;
}



// ------------------------------------------------------------
// 0x506700 sub_506700
//   std::_Fill_n（36 字节元素版）：转调 sub_505E80 后返回 nArg1+36*nArg2 尾地址。
// ------------------------------------------------------------
int /*stdcall*/ sub_506700(int nArg1, int nArg2, int nArg3)
{
  sub_505E80(nArg1, nArg2, nArg3);  // 调 sub_505E80
  return nArg1 + 36 * nArg2;
}



// ------------------------------------------------------------
// 0x506730 sub_506730
//   std::vector<36字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（504A30/505E60/505E20/506700 搬运）；不足 →
//   扩容三段拷贝重建（上限检查 sub_4CEAB0）。
// ------------------------------------------------------------
void /*thiscall*/ sub_506730(int *this, int pArg2, unsigned int uArg3, int pArg4)  // 函数: 释放后返回
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
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  pThis = this;
  v31 = 15;
  v30 = 0;
  LOBYTE(v29) = 0;  // 调 取 16 位值低 8 位
  sub_4014D0((std::_String_base *)v28, pArg4, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  v5 = *(uint8_t *)(pArg4 + 32);  // 读字段 v5 = pArg4+32（nHeight）
  v32 = *(uint32_t *)(pArg4 + 28);  // 读字段 v32 = pArg4+28（pPanelVec）
  v33 = v5;
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v36 = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - fld_e1) / 36;  // this+12 = 技能槽记录次字
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 36;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 119304647 - fld_e2 < uArg3 )
      sub_4CEAB0(this);  // 调 sub_4CEAB0
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 36;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = *(this + 2);  // 读字段 fld_e23 = this+2
      fld_e232 = fld_e23;  // fld_e23=this+8 物品 id
      if ( (fld_e23 - pArg2) / 36 >= uArg3 )  // fld_e23=this+8 物品 id
      {
        v37 = fld_e23 - 36 * uArg3;  // fld_e23=this+8 物品 id
        *(this + 2) = sub_504A30(v37, fld_e23, fld_e23);  // 写字段 this+2 ← sub_504A30(v37, fld_e23, fld_e23)
        sub_505E60(pArg2, v37, fld_e232);  // 调 sub_505E60
        sub_505E20(pArg2, pArg2 + 36 * uArg3, v28);  // 调 sub_505E20
      }
      else
      {
        sub_504A30(pArg2, fld_e23, pArg2 + 36 * uArg3);  // 调 sub_504A30
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 36;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        LOBYTE(v36) = 3;  // 调 取 16 位值低 8 位
        sub_506700(fld_e25, fld_e24, v28);  // 调 sub_506700
        fld_e26 = 36 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        v36 = 0;
        sub_505E20(pArg2, fld_e26 - 36 * uArg3, v28);  // 调 sub_505E20
      }
    }
    else
    {
      if ( 119304647 - (fld_e3 >> 1) >= fld_e3 )  // 若 119304647 - (fld_e3 >> 1) >= fld_e3
        v11 = (fld_e3 >> 1) + fld_e3;
      else
        v11 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 36;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v11 < uArg3 + fld_e27 )
        v11 = uArg3 + sub_504390(this);
      v38 = 36 * v11;  // 计算 v38 = 36 * v11
      pMem = (char *)operator new(36 * v11);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;  // 调 取 16 位值低 8 位
      pMem2 = (char *)sub_504A30(fld_e12, pArg2, pMem);  // fld_e12=this+4 宿主对象
      sub_505E80(pMem2, uArg3, v28);  // 调 sub_505E80
      fld_e28 = *(this + 2);  // 读字段 fld_e28 = this+2
      pMem2 += 36 * uArg3;
      sub_504A30(pArg2, fld_e28, pMem2);  // 调 sub_504A30
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 36;  // this+8 = 技能槽记录首字
      v16 = fld_e13 + uArg3;  // 计算 v16 = fld_e13 + uArg3
      fld_e14 = (void *)*(this + 1);  // this+4 = pHostObj
      if ( fld_e14 != nullptr )
      {
        sub_4D0970(fld_e14, *(this + 2));  // 调 sub_4D0970
        j__free((void *)*(this + 1));  // 释放堆块
      }
      *(this + 3) = (int)&pMem[v38];  // 写字段 this+3 ← (int)&pMem[v38]
      *(this + 2) = (int)&pMem[36 * v16];  // 写字段 this+2 ← (int)&pMem[36 * v16]
      *(this + 1) = (int)pMem;  // 写字段 this+1 ← (int)pMem
    }
  }
  if ( v31 >= 0x10 )
    j__free(v29);  // 释放堆块
}


// ------------------------------------------------------------
// 0x506A60 sub_506A60
//   std::copy（56 字节元素版，正向）：+0x28 处容器经 sub_4ED3F0 深拷贝。
// ------------------------------------------------------------
int /*cdecl*/ sub_506A60(int nArg1, int nArg2, int pArg3)
{
  int result; // eax
  int i; // esi

  result = nArg2;
  for ( i = nArg1; i != nArg2; i += 56 )  // 循环：i = nArg1; i != nArg2; i += 56
  {
    *(uint32_t *)i = *(uint32_t *)pArg3;
    *(uint8_t *)(i + 4) = *(uint8_t *)(pArg3 + 4);  // 写字段 i+4（pHostObj） ← *(uint8_t *)(pArg3 + 4)
    *(uint32_t *)(i + 8) = *(uint32_t *)(pArg3 + 8);  // 写字段 i+8（nSkillRec8） ← *(uint32_t *)(pArg3 + 8)
    *(uint32_t *)(i + 12) = *(uint32_t *)(pArg3 + 12);  // 写字段 i+12（nSkillRec12） ← *(uint32_t *)(pArg3 + 12)
    *(uint32_t *)(i + 16) = *(uint32_t *)(pArg3 + 16);  // 写字段 i+16（nChannelTypeSel） ← *(uint32_t *)(pArg3 + 16)
    *(uint32_t *)(i + 20) = *(uint32_t *)(pArg3 + 20);  // 写字段 i+20（nPage） ← *(uint32_t *)(pArg3 + 20)
    *(uint32_t *)(i + 24) = *(uint32_t *)(pArg3 + 24);  // 写字段 i+24（nPageMax） ← *(uint32_t *)(pArg3 + 24)
    *(uint32_t *)(i + 28) = *(uint32_t *)(pArg3 + 28);  // 写字段 i+28（pPanelVec） ← *(uint32_t *)(pArg3 + 28)
    *(uint32_t *)(i + 32) = *(uint32_t *)(pArg3 + 32);  // 写字段 i+32（nHeight） ← *(uint32_t *)(pArg3 + 32)
    *(uint32_t *)(i + 36) = *(uint32_t *)(pArg3 + 36);  // 写字段 i+36（nStateWord36） ← *(uint32_t *)(pArg3 + 36)
    sub_4ED3F0(i + 40, pArg3 + 40);  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
    result = nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x506AD0 sub_506AD0
//   std::copy_backward（56 字节元素版）：转调 sub_506280。
// ------------------------------------------------------------
int /*cdecl*/ sub_506AD0(int nArg1, int nArg2, int nArg3)  // 函数: 转发 ·sub_506280
{
  return sub_506280(nArg1, nArg2, nArg3);  // 调 sub_506280
}



// ------------------------------------------------------------
// 0x506AF0 sub_506AF0
//   std::copy/未初始化填充（56 字节元素版，正向）：逐元素拷贝，
//   +0x28 成员经 sub_435020 复制。
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
  while ( pArg1 != nArg2 )  // 循环直到 pArg1 != nArg2
  {
    LOBYTE(v7) = 1;  // 调 取 16 位值低 8 位
    if ( nArg32 != 0 )
    {
      *(uint32_t *)nArg32 = *(uint32_t *)pArg1;
      *(uint8_t *)(nArg32 + 4) = *(uint8_t *)(pArg1 + 4);  // 写字段 nArg32+4（pHostObj） ← *(uint8_t *)(pArg1 + 4)
      *(uint32_t *)(nArg32 + 8) = *(uint32_t *)(pArg1 + 8);  // 写字段 nArg32+8（nSkillRec8） ← *(uint32_t *)(pArg1 + 8)
      *(uint32_t *)(nArg32 + 12) = *(uint32_t *)(pArg1 + 12);  // 写字段 nArg32+12（nSkillRec12） ← *(uint32_t *)(pArg1 + 12)
      *(uint32_t *)(nArg32 + 16) = *(uint32_t *)(pArg1 + 16);  // 写字段 nArg32+16（nChannelTypeSel） ← *(uint32_t *)(pArg1 + 16)
      *(uint32_t *)(nArg32 + 20) = *(uint32_t *)(pArg1 + 20);  // 写字段 nArg32+20（nPage） ← *(uint32_t *)(pArg1 + 20)
      *(uint32_t *)(nArg32 + 24) = *(uint32_t *)(pArg1 + 24);  // 写字段 nArg32+24（nPageMax） ← *(uint32_t *)(pArg1 + 24)
      *(uint32_t *)(nArg32 + 28) = *(uint32_t *)(pArg1 + 28);  // 写字段 nArg32+28（pPanelVec） ← *(uint32_t *)(pArg1 + 28)
      *(uint32_t *)(nArg32 + 32) = *(uint32_t *)(pArg1 + 32);  // 写字段 nArg32+32（nHeight） ← *(uint32_t *)(pArg1 + 32)
      *(uint32_t *)(nArg32 + 36) = *(uint32_t *)(pArg1 + 36);  // 写字段 nArg32+36（nStateWord36） ← *(uint32_t *)(pArg1 + 36)
      sub_435020((void *)(pArg1 + 40));  // sub_435020 —— uint32 向量整体赋值
    }
    nArg32 += 56;
    LOBYTE(v7) = 0;  // 调 取 16 位值低 8 位
    pArg1 += 56;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x506BE0 sub_506BE0
//   名称→代码匹配助手（读 nArg1 个 token）：每个 token 读为字符串（sub_443370）
//   后在 27 项静态名字表 off_795AC0[dword_6FC398[i]] 中查全等，命中则把代码
//   dword_6FC398[i] 推入 pArg2+0x28 的 vector<int>（sub_502F00 技能 [static data]
//   的名称串→内部代码转换【推断】）。
// ------------------------------------------------------------
void /*cdecl*/ sub_506BE0(int nArg1, int pArg2)  // 函数: 释放后返回
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v16 = 15;
  v15 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  v18 = 0;
  if ( nArg1 > 0 )
  {
    for ( i = nArg1; i != 0; --i )  // 遍历计次循环（i != 0）
    {
      sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
      nArg12 = 0;
      nArg1 = 0;
      while ( 1 )  // 当 1 循环
      {
        psz = off_795AC0[(uint8_t)dword_6FC398[nArg12]];  // psz = off_795AC0[(uint8_t)dword_6FC398[nA]
        nLen = strlen(psz);  // 调 _strlen 取字符串长度
        if ( v15 == 0 )
          goto LABEL_11;  // 跳转 LABEL_11
        nLen2 = v15;
        if ( v15 >= nLen )
          nLen2 = nLen;
        p_Block = (const char *)Block;
        if ( v16 < 0x10 )
          p_Block = (const char *)&Block;
        nCmp = memcmp(p_Block, psz, nLen2);  // 调 memcmp 内存比较
        nArg12 = nArg1;
        if ( nCmp == 0 )
        {
LABEL_11:
          if ( v15 >= nLen && v15 == nLen )
            break;
        }
        nArg1 = ++nArg12;
        if ( nArg12 >= 27 )
          goto LABEL_21;  // 跳转 LABEL_21
      }
      v8 = *(uint32_t *)(pArg2 + 44);  // 读字段 v8 = pArg2+44（nExpireMs）
      v9 = dword_6FC398[nArg12];
      v10 = pArg2 + 40;  // 计算 v10 = pArg2 + 40
      nArg1 = v9;
      if ( v8 != 0 )
        v11 = (*(uint32_t *)(pArg2 + 48) - v8) >> 2;
      else
        v11 = 0;
      if ( v8 != 0 && v11 < (*(uint32_t *)(pArg2 + 52) - v8) >> 2 )
      {
        v12 = *(int **)(pArg2 + 48);
        *v12 = v9;  // *v12 写入 v9
        *(uint32_t *)(v10 + 8) = v12 + 1;  // 写字段 v10+8（nSkillRec8） ← v12 + 1
      }
      else
      {
        sub_430C80(*(void **)(pArg2 + 48), 1, (int)&nArg1);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
      }
LABEL_21:
      ;
    }
    if ( v16 >= 0x10 )
      j__free(Block);  // 释放堆块
  }
}



// ------------------------------------------------------------
// 0x506D30 sub_506D30
//   std::vector<36字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_506730 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506D30(int *this, uint32_t *uArg2, int nArg3, int nArg4)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 36 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (nArg3 - fld_e1) / 36;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_506730(this, nArg3, 1u, nArg4);  // 调 sub_506730
  *uArg2 = *(this + 1) + 36 * v6;  // *uArg2 写入 *(this + 1) + 36 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x506DA0 sub_506DA0
//   std::list 节点堆构造（0x3C 字节）：{next, prev, 9 dword 块（sub_506230 拷贝）,
//   +0x2C vector<8字节> 复制}。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_506DA0(int nArg1, int nArg2, uint32_t *uArg3)  // 函数定义: 建节点插到哨兵后
{
  uint32_t *pMem; // esi
  void *v5[9]; // [esp+0h] [ebp-24h] BYREF

  v5[5] = v5;
  pMem = operator new(0x3Cu);  // 堆分配
  v5[4] = pMem;
  v5[8] = (void *)1;  // v5[8] 写入 (void *)1
  v5[3] = pMem;
  if ( pMem != nullptr )
  {
    pMem[1] = nArg2;
    *pMem = nArg1;  // *pMem 写入 nArg1
    sub_506230(pMem + 2, uArg3);  // 调 sub_506230
  }
  return pMem;
}



// ------------------------------------------------------------
// 0x506E30 sub_506E30
//   std::list 节点堆构造（0x28 字节）：{next, prev, 4 dword 值,
//   +0x18 vector<24字节> 整段复制（sub_505D80）}。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_506E30(int nArg1, int nArg2, uint32_t *pArg3)  // 函数定义: 建节点插到哨兵后
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v6[9]; // [esp+0h] [ebp-24h] BYREF

  v6[5] = v6;
  pMem = operator new(0x28u);  // 堆分配
  pMem2 = pMem;
  v6[4] = pMem;
  v6[8] = (void *)1;  // v6[8] 写入 (void *)1
  v6[3] = pMem;
  if ( pMem != nullptr )
  {
    *pMem = nArg1;  // *pMem 写入 nArg1
    pMem[1] = nArg2;
    pMem[2] = *pArg3;  // pMem[2] 写入 *pArg3
    pMem[3] = pArg3[1];  // pMem[3] 写入 pArg3[1]
    pMem[4] = pArg3[2];  // pMem[4] 写入 pArg3[2]
    pMem[5] = pArg3[3];  // pMem[5] 写入 pArg3[3]
    sub_505D80(pMem + 6, (int)(pArg3 + 4));  // 调 sub_505D80
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x506ED0 sub_506ED0
//   std::_Fill_n 未初始化构造（56 字节元素版）：从 nArg1 起连续 nArg2 个元素
//   从 pArg3 拷贝构造（+0x28 成员经 sub_435020）。
// ------------------------------------------------------------
void /*cdecl*/ sub_506ED0(int nArg1, int nArg2, int pArg3)  // 函数定义: 后返回 nArg1+56*nArg2 尾地址
{
  int nArg12; // esi
  uint32_t v4[6]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v4[5] = v4;
  v4[4] = nArg1;
  v5 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    v4[3] = nArg12;
    LOBYTE(v5) = 1;  // 调 取 16 位值低 8 位
    if ( nArg12 != 0 )
    {
      *(uint32_t *)nArg12 = *(uint32_t *)pArg3;
      *(uint8_t *)(nArg12 + 4) = *(uint8_t *)(pArg3 + 4);  // 写字段 nArg12+4（pHostObj） ← *(uint8_t *)(pArg3 + 4)
      *(uint32_t *)(nArg12 + 8) = *(uint32_t *)(pArg3 + 8);  // 写字段 nArg12+8（nSkillRec8） ← *(uint32_t *)(pArg3 + 8)
      *(uint32_t *)(nArg12 + 12) = *(uint32_t *)(pArg3 + 12);  // 写字段 nArg12+12（nSkillRec12） ← *(uint32_t *)(pArg3 + 12)
      *(uint32_t *)(nArg12 + 16) = *(uint32_t *)(pArg3 + 16);  // 写字段 nArg12+16（nChannelTypeSel） ← *(uint32_t *)(pArg3 + 16)
      *(uint32_t *)(nArg12 + 20) = *(uint32_t *)(pArg3 + 20);  // 写字段 nArg12+20（nPage） ← *(uint32_t *)(pArg3 + 20)
      *(uint32_t *)(nArg12 + 24) = *(uint32_t *)(pArg3 + 24);  // 写字段 nArg12+24（nPageMax） ← *(uint32_t *)(pArg3 + 24)
      *(uint32_t *)(nArg12 + 28) = *(uint32_t *)(pArg3 + 28);  // 写字段 nArg12+28（pPanelVec） ← *(uint32_t *)(pArg3 + 28)
      *(uint32_t *)(nArg12 + 32) = *(uint32_t *)(pArg3 + 32);  // 写字段 nArg12+32（nHeight） ← *(uint32_t *)(pArg3 + 32)
      *(uint32_t *)(nArg12 + 36) = *(uint32_t *)(pArg3 + 36);  // 写字段 nArg12+36（nStateWord36） ← *(uint32_t *)(pArg3 + 36)
      sub_435020((void *)(pArg3 + 40));  // sub_435020 —— uint32 向量整体赋值
    }
    nArg12 += 56;
    LOBYTE(v5) = 0;  // 调 取 16 位值低 8 位
    --nArg2;  // 计数自减 nArg2
  }
}



// ------------------------------------------------------------
// 0x506FC0 sub_506FC0
//   std::list::erase(iterator)：把节点从链摘下（邻居互指），经 sub_4CFE40 析构
//   值并 free 节点，元素计数 -1；返回后继节点。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_506FC0(int this, uint32_t *uArg2, uint32_t **Block)
{
  uint32_t *v3; // ebx

  v3 = *Block;
  if ( Block != *(uint32_t ***)(this + 4) )  // 若 Block != *(uint32_t ***)(this + 4)
  {
    *Block[1] = *Block;
    (*Block)[1] = Block[1];
    sub_4CFE40(Block);  // 调 sub_4CFE40
    j__free(Block);  // 释放堆块
    --*(uint32_t *)(this + 8);  // this+8 物品 id
  }
  *uArg2 = v3;  // *uArg2 写入 v3
  return uArg2;
}



// ------------------------------------------------------------
// 0x507010 sub_507010
//   std::vector<36字节元素>::push_back：容量够 → 在 end 构造（sub_505E80）；
//   不够 → 转调 sub_506D30 插入路径扩容。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_507010(int *this, int nArg2)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) / 36;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 36 )  // fld_e1=this+4 宿主对象
    return sub_506D30(this, &nArg2, *(this + 2), nArg2);  // 调 sub_506D30
  fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
  result = (uint32_t *)sub_505E80(fld_e22, 1, nArg2);  // 调 后返回 nArg1+36*nArg2 尾地址
  *(this + 2) = fld_e22 + 36;  // 写字段 this+2 ← fld_e22 + 36
  return result;
}



// ------------------------------------------------------------
// 0x5070A0 sub_5070A0
//   std::list 范围插入：把 [nArg3, uArg4) 的源链逐节点（sub_506DA0）插到
//   本链哨兵后（push_front 语义），计数走 sub_5047F0。
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
  while ( v5 != uArg4 )  // 循环直到 v5 != uArg4
  {
    v6 = sub_506DA0(pArg2, *(uint32_t *)(pArg2 + 4), v5 + 2);  // 调 sub_506DA0
    sub_5047F0(pThis, 1u);  // 调 sub_5047F0
    *(uint32_t *)(pArg2 + 4) = v6;  // 写字段 pArg2+4（pHostObj） ← v6
    *(uint32_t *)v6[1] = v6;
    v5 = (uint32_t *)*v5;
  }
}



// ------------------------------------------------------------
// 0x507150 sub_507150
//   std::list::push_front（0x3C 字节节点版）：sub_506DA0 建节点插到哨兵后，
//   计数 +1（sub_5047F0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_507150(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v4 = sub_506DA0(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);  // 调 sub_506DA0
  result = sub_5047F0(this, 1u);  // 调 sub_5047F0
  *(uint32_t *)(fld_e1 + 4) = v4;  // 写字段 fld_e1+4（pHostObj） ← v4
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x507190 sub_507190
//   std::list::push_front（0x28 字节节点版）：sub_506E30 建节点插到哨兵后，
//   计数 +1（sub_5048F0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_507190(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v4 = sub_506E30(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);  // 调 sub_506E30
  result = sub_5048F0(this, 1u);  // 调 sub_5048F0
  *(uint32_t *)(fld_e1 + 4) = v4;  // 写字段 fld_e1+4（pHostObj） ← v4
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x5071D0 sub_5071D0
//   std::_Fill_n（56 字节元素版）：转调 sub_506ED0 后返回 nArg1+56*nArg2 尾地址。
// ------------------------------------------------------------
int /*stdcall*/ sub_5071D0(int nArg1, int nArg2, int nArg3)
{
  sub_506ED0(nArg1, nArg2, nArg3);  // 调 sub_506ED0
  return nArg1 + 56 * nArg2;
}



// ------------------------------------------------------------
// 0x507200 sub_507200
//   std::vector<56字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（5061D0/506AF0/506AD0/506A60/5071D0 搬运）；不足 →
//   扩容三段拷贝重建（旧缓冲经 4D0940 析构 + free）。
// ------------------------------------------------------------
void /*thiscall*/ sub_507200(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 函数: 释放后返回
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
  sub_5061D0(nArg4);  // 调 sub_5061D0
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  fld_e3 = 0;
  v28 = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - fld_e1) / 56;  // this+12 = 技能槽记录次字
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - *(this + 1)) / 56;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 76695844 - fld_e2 < uArg3 )
      sub_4CEAB0(this);  // 调 sub_4CEAB0
    if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
      fld_e22 = (*(this + 2) - *(this + 1)) / 56;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (char *)*(this + 2);  // this+8 = 技能槽记录首字
      Block = fld_e23;
      if ( (int)&fld_e23[-pArg2] / 56 >= uArg3 )
      {
        v29 = &fld_e23[-56 * uArg3];
        *(this + 2) = sub_506AF0(v29, fld_e23, fld_e23);  // 写字段 this+2 ← sub_506AF0(v29, fld_e23, fld_e23)
        sub_506AD0(pArg2, v29, Block);  // 调 sub_506AD0
        sub_506A60(pArg2, pArg2 + 56 * uArg3, v23);  // 调 sub_506A60
      }
      else
      {
        sub_506AF0(pArg2, fld_e23, pArg2 + 56 * uArg3);  // 调 sub_506AF0
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 56;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        LOBYTE(v28) = 3;  // 调 取 16 位值低 8 位
        sub_5071D0(fld_e25, fld_e24, v23);  // 调 sub_5071D0
        fld_e26 = 56 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        v28 = 0;
        sub_506A60(pArg2, fld_e26 - 56 * uArg3, v23);  // 调 sub_506A60
      }
    }
    else
    {
      if ( 76695844 - (fld_e3 >> 1) >= fld_e3 )  // 若 76695844 - (fld_e3 >> 1) >= fld_e3
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        fld_e27 = (*(this + 2) - *(this + 1)) / 56;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_488DD0(this);  // sub_488DD0 —— 结果 = 56 字节元素数组长度
      v31 = 56 * v10;  // 计算 v31 = 56 * v10
      pMem = (char *)operator new(56 * v10);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      Block = pMem;
      LOBYTE(v28) = 1;  // 调 取 16 位值低 8 位
      v30 = sub_506AF0(fld_e12, pArg2, pMem);  // 调 sub_506AF0
      sub_506ED0(v30, uArg3, v23);  // 调 sub_506ED0
      sub_506AF0(pArg2, *(this + 2), 56 * uArg3 + v30);  // 调 sub_506AF0
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 56;  // this+8 = 技能槽记录首字
      v14 = fld_e13 + uArg3;  // 计算 v14 = fld_e13 + uArg3
      fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
      if ( fld_e14 != 0 )  // fld_e14=this+4 宿主对象
      {
        sub_4D0940(fld_e14, *(this + 2));  // 调 sub_4D0940
        j__free((void *)*(this + 1));  // 释放堆块
      }
      *(this + 3) = (int)&pMem[v31];  // 写字段 this+3 ← (int)&pMem[v31]
      *(this + 2) = (int)&pMem[56 * v14];  // 写字段 this+2 ← (int)&pMem[56 * v14]
      *(this + 1) = (int)pMem;  // 写字段 this+1 ← (int)pMem
    }
  }
  if ( v24 != nullptr )
    j__free(v24);  // 释放堆块
}


// ------------------------------------------------------------
// 0x507510 sub_507510
//   std::list 拷贝构造：分配哨兵（sub_4CE750）后把源链 [源哨兵后..末尾]
//   逐节点复制插入（sub_5070A0）。
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
  *(this + 1) = v3;  // 写字段 this+1 ← v3
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  v7 = *(int **)(pArg2 + 4);
  v6 = *v7;
  v5 = *v3;
  v8[7] = 0;
  sub_5070A0(this, v5, v6, v7, pArg2);  // 调 sub_5070A0
  return this;
}



// ------------------------------------------------------------
// 0x507590 sub_507590
//   std::vector<56字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_507200 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_507590(int *this, uint32_t *uArg2, int nArg3, int nArg4)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 56 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (nArg3 - fld_e1) / 56;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_507200(this, nArg3, 1u, nArg4);  // 调 sub_507200
  *uArg2 = *(this + 1) + 56 * v6;  // *uArg2 写入 *(this + 1) + 56 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x507600 sub_507600
//   std::vector<56字节元素>::push_back：容量够 → 在 end 构造（sub_506ED0）；
//   不够 → 转调 sub_507590 插入路径扩容。
// ------------------------------------------------------------
void /*thiscall*/ sub_507600(int *this, int nArg2)
{
  int fld_e1; // ebx
  unsigned int fld_e2; // esi
  int fld_e22; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) / 56;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) / 56 )  // fld_e1=this+4 宿主对象
  {
    fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
    sub_506ED0(fld_e22, 1, nArg2);  // 调 sub_506ED0
    *(this + 2) = fld_e22 + 56;  // 写字段 this+2 ← fld_e22 + 56
  }
  else
  {
    sub_507590(this, &nArg2, *(this + 2), nArg2);  // 调 sub_507590
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
char /*cdecl*/ sub_507690(int nArg1, const char *ArgList)  // sub_507690 —— 瓦片(tile)定义解析器
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( (uint8_t)sub_442A10((char)szPassword, (int)ArgList) != 0 )  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  {
    nArg12 = nArg1;
    sub_4D0AE0(nArg1);  // 调 sub_4D0AE0
    v4 = 0;
    v18 = 15;
    v17 = nullptr;  // v17 = nullptr 空指针
    LOBYTE(v16) = 0;  // 调 取 16 位值低 8 位
    v20 = 1;
    v14 = 15;
    v13 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    while ( (uint8_t)sub_443430(v15) != 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    {
      sub_442B20(v15);  // sub_442B20 —— 国家码标签配对校验（void）
      if ( sub_40BF00((std::_String_base *)v15, 0, (unsigned int)v17, "[IMAGE]", 7u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)v15, 0, (unsigned int)v17, "[tile type]", 0xBu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)v15, 0, (unsigned int)v17, "[pass type]", 0xBu) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            v5 = *(uint8_t *)(nArg12 + 32) != 0 ? 10 : 30;
            i = &v8;
            sub_489720(v5, v8, nullptr, 0, 0);  // sub_489720 —— 16 字节元素容器重设长度（缩删/伸补）
            for ( i = (char *)v5; i != nullptr; --i )  // 循环：i = (char *)v5; i != nullptr; --i
            {
              sub_505FF0((unsigned int *)(v4 + *(uint32_t *)(nArg12 + 40)), 0xEu, 0);  // 调 sub_505FF0
              for ( j = 0; j < 56; j += 4 )  // 循环：j = 0; j < 56; j += 4
              {
                v7 = (int *)(j + *(uint32_t *)(*(uint32_t *)(nArg12 + 40) + v4 + 4));
                *v7 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
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
          sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
          if ( sub_40BF00((std::_String_base *)v11, 0, v13, "[basic]", 7u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)v11, 0, v13, "[extended]", 0xAu) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
              *(uint8_t *)(nArg12 + 32) = 1;  // 写字段 nArg12+32（nHeight） ← 1
          }
          else
          {
            *(uint8_t *)(nArg12 + 32) = 0;  // 写字段 nArg12+32（nHeight） ← 0
          }
        }
      }
      else
      {
        v9 = (uint8_t *)nArg12;
        sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
        *(uint32_t *)(nArg12 + 28) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      }
    }
    if ( v14 >= 0x10 )
      j__free(Block);  // 释放堆块
    v14 = 15;
    v13 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    if ( v18 >= 0x10 )
      j__free(v16);  // 释放堆块
    return 1;
  }
  else
  {
    off_77F3FC("TILE LOAD FAIL! [%s]", ArgList);  // off_77F3FC —— 日志打印（printf 风格）
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
char /*cdecl*/ sub_5078C0(int pArg1, int ArgList)  // sub_5078C0 —— 副本地图(dungeon map)定义解析器（0x1D8 字节对象，sub_4D1680 构造）
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
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( (uint8_t)sub_442A10((char)&unk_9B7308, ArgList) == 0 )  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
    return 0;
  pArg12 = pArg1;
  sub_4D13A0(pArg1);  // 调 sub_4D13A0
  sub_443300(pArg1 + 280, "%s%s", (char)&unk_9B7308);  // 调 格式化串取目录前缀
  v122 = 15;
  v121 = 0;
  LOBYTE(v120) = 0;  // 调 取 16 位值低 8 位
  v124 = 0;
  v103 = nullptr;  // v103 = nullptr 空指针
  sub_41BFE0((void **)&v103, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  LOBYTE(v124) = 1;  // 调 取 16 位值低 8 位
  v104 = 0;
  sub_504AF0(v108);  // 调 sub_504AF0
  LOBYTE(v124) = 2;  // 调 取 16 位值低 8 位
  v86 = -1;
  v87 = 0;
  v88 = 0;
  v89 = 0;
  sub_506300(&v66);  // 调 sub_506300
  v78 = -1;
  v81 = 0;
  v80 = 0;
  v79 = 0;
  Block = nullptr;  // Block = nullptr 空指针
  v83 = 0;
  v84 = 0;
  LOBYTE(v124) = 4;  // 调 取 16 位值低 8 位
  v93 = 0;
  v94 = 0;
  v95 = 0;
  v96 = 0;
  v97 = 0;
  if ( (uint8_t)sub_443430(&v119) == 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    goto LABEL_165;  // 跳转 LABEL_165
  while ( 1 )  // 当 1 循环
  {
    sub_442B20(&v119);  // sub_442B20 —— 国家码标签配对校验（void）
    if ( sub_40BF00((std::_String_base *)&v119, 0, v121, "[map name]", 0xAu) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      j = *(uint32_t *)(pArg12 + 424);  // 读字段 j = pArg12+424（f_AtkRateX10）
      sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( sub_40BF00((std::_String_base *)&v119, 0, v121, "[player number]", 0xFu) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      v4 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      v56 = nullptr;  // v56 = nullptr 空指针
      *(uint32_t *)(pArg12 + 336) = v4;  // 写字段 pArg12+336 ← v4
      *(uint32_t *)(pArg12 + 340) = sub_4423D0(v56);  // sub_4423D0 —— [LOOP] → 动画对象+160
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( sub_40BF00((std::_String_base *)&v119, 0, v121, "[pvp start area]", 0x10u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      v5 = (int *)(pArg12 + 348);
      for ( i = 3; i != 0; --i )  // 遍历计次循环（i != 0）
      {
        v7 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v56 = nullptr;  // v56 = nullptr 空指针
        *(v5 - 1) = v7;
        v8 = sub_4423D0(v56);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v55 = nullptr;  // v55 = nullptr 空指针
        *v5 = v8;  // *v5 写入 v8
        v9 = sub_4423D0(v55);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v54 = nullptr;  // v54 = nullptr 空指针
        v5[1] = v9;
        v5[2] = sub_4423D0(v54);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v5 += 4;
      }
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( sub_40BF00((std::_String_base *)&v119, 0, v121, "[shadow type]", 0xDu) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      j = (int)&v103;
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v103, "[mirror]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        *(uint32_t *)(pArg12 + 392) = 1;  // 写字段 pArg12+392 ← 1
      }
      else if ( sub_43BCF0(&v103, "[more darker]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        *(uint32_t *)(pArg12 + 392) = 2;  // 写字段 pArg12+392 ← 2
      }
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[dungeon]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      v10 = pArg12 + 4;  // 计算 v10 = pArg12 + 4
      sub_6569D0(pArg12 + 4);  // sub_6569D0 —— (this+4)
      v100 = sub_4423D0(&v104);  // sub_4423D0 —— [LOOP] → 动画对象+160
      if ( v104 != 0 )
      {
        do
        {
          v11 = *(uint32_t *)(v10 + 4);  // 读字段 v11 = v10+4（pHostObj）
          v12 = sub_40C0F0(v11, *(uint32_t *)(v11 + 4), &v100);  // sub_40C0F0 —— list 结点分配（12B：前驱/后继/数据）
          sub_437320(1);  // sub_437320 —— 链表计数累加
          *(uint32_t *)(v11 + 4) = v12;  // 写字段 v11+4（pHostObj） ← v12
          v13 = *(uint32_t **)(v12 + 4);
          j = (int)&v104;
          *v13 = v12;  // *v13 写入 v12
          v100 = sub_4423D0((uint8_t *)j);  // sub_4423D0 —— [LOOP] → 动画对象+160
        }
        while ( v104 != 0 );  // 循环直到 v104 != 0
        pArg12 = pArg1;
      }
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[type]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      j = (int)&v103;
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v103, "[normal]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        *(uint32_t *)(pArg12 + 16) = 0;  // 写字段 pArg12+16（nChannelTypeSel） ← 0
      }
      else if ( sub_43BCF0(&v103, "[boss]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        *(uint32_t *)(pArg12 + 16) = 1;  // 写字段 pArg12+16（nChannelTypeSel） ← 1
      }
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[greed]") != 0 )  // sub_423300 —— [end] → 解析结束
      break;
    if ( (uint8_t)sub_423300(&v119, "[tile]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_4017E0(pArg12 + 124);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
      for ( j = (int)&v103; sub_442E10() != 0; j = (int)&v103 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v103);  // sub_420BB0 —— vector push_back（4 字节元素）
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[extended tile]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_4017E0(pArg12 + 140);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
      for ( j = (int)&v103; sub_442E10() != 0; j = (int)&v103 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v103);  // sub_420BB0 —— vector push_back（4 字节元素）
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[elemental property]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      j = (int)&v103;
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      v24 = sub_41ACF0(&v103);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      *(uint32_t *)(pArg12 + 120) = sub_442710(v24);  // sub_442710 —— 【元素标签→索引（[fire/water/dark/light element]）】
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[far sight scroll]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint32_t *)(pArg12 + 156) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[middle sight scroll]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint32_t *)(pArg12 + 160) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[near sight scroll]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint32_t *)(pArg12 + 164) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[background animation]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_4D09E0(pArg12 + 168);  // 调 sub_4D09E0
      sub_504B90(v105);  // 调 sub_504B90
      j = (int)&v103;
      for ( LOBYTE(v124) = 6; sub_442E10() != 0; j = (int)&v103 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
      {
        v25 = (void *)sub_41ACF0(&v103);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        sub_406D60(v25);  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        j = (int)&v103;
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        v26 = sub_41ACF0(&v103);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        v27 = sub_4425F0(v26);  // sub_4425F0 —— 场景前景/背景档位标签→索引
        v56 = (void **)&v103;
        v106 = v27;
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        v107 = !sub_43BCF0(&v103, "[below]");  // sub_43BCF0 —— 字符串 “[free]”
        sub_507010(v105);  // 调 sub_507010
      }
      LOBYTE(v124) = 4;  // 调 取 16 位值低 8 位
      sub_501490(v105);  // 调 sub_501490
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[town movable area]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_5E5260((void **)(pArg12 + 184));  // 调 sub_5E5260
      for ( k = sub_4423D0(&v104); v104 != 0; k = sub_4423D0(&v104) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
      {
        v60[0] = k;
        v60[1] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v60[2] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v60[3] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v60[4] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v60[5] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        sub_5063B0(v60);  // 调 sub_5063B0
      }
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[virtual movable area]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_5E5260((void **)(pArg12 + 200));  // 调 sub_5E5260
      for ( m = sub_4423D0(&v104); v104 != 0; m = sub_4423D0(&v104) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
      {
        v62[0] = m;
        v62[1] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v62[2] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v62[3] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        sub_506440(v62);  // 调 sub_506440
      }
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[pathgate pos]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      v30 = (int *)(pArg1 + 216);
      for ( n = 4; n != 0; --n )  // 遍历计次循环（n != 0）
      {
        for ( ii = 2; ii != 0; --ii )  // 遍历计次循环（ii != 0）
          *v30++ = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      }
      pArg12 = pArg1;
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[dungeon start area]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      v33 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      v56 = nullptr;  // v56 = nullptr 空指针
      *(uint32_t *)(pArg12 + 248) = v33;  // 写字段 pArg12+248（bParamSlotA） ← v33
      v34 = sub_4423D0(v56);  // sub_4423D0 —— [LOOP] → 动画对象+160
      v55 = nullptr;  // v55 = nullptr 空指针
      *(uint32_t *)(pArg12 + 252) = v34;  // 写字段 pArg12+252（nParamSlotB） ← v34
      v35 = sub_4423D0(v55);  // sub_4423D0 —— [LOOP] → 动画对象+160
      v54 = nullptr;  // v54 = nullptr 空指针
      *(uint32_t *)(pArg12 + 256) = v35;  // 写字段 pArg12+256（bParamSlotC） ← v35
      *(uint32_t *)(pArg12 + 260) = sub_4423D0(v54);  // sub_4423D0 —— [LOOP] → 动画对象+160
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[sound]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_4017E0(pArg12 + 264);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
      for ( j = (int)&v103; sub_442E10() != 0; j = (int)&v103 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v103);  // sub_420BB0 —— vector push_back（4 字节元素）
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[animation]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_4CFEA0(pArg12 + 36);  // 调 sub_4CFEA0
      for ( j = (int)v108; sub_443370() != 0; j = (int)v108 )  // sub_443370 —— [name] → 对象+0x04 名称串
      {
        j = (int)&v103;
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        v36 = sub_41ACF0(&v103);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        v112 = sub_4425F0(v36);  // sub_4425F0 —— 场景前景/背景档位标签→索引
        v113 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v114 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v115 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        sub_5064B0(v108);  // 调 sub_5064B0
      }
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[passive object]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_6569D0(pArg12 + 48);  // sub_6569D0 —— (this+4)
      for ( jj = sub_4423D0(&v104); v104 != 0; jj = sub_4423D0(&v104) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
      {
        v86 = jj;
        v87 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v88 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v89 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        sub_505F40(&v86);  // 调 sub_505F40
      }
      goto LABEL_164;  // 跳转 LABEL_164
    }
    if ( (uint8_t)sub_423300(&v119, "[monster]") == 0 )  // sub_423300 —— [end] → 解析结束
    {
      if ( (uint8_t)sub_423300(&v119, "[champion]") != 0 )  // sub_423300 —— [end] → 解析结束
      {
        *(uint32_t *)(pArg12 + 76) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      }
      else if ( (uint8_t)sub_423300(&v119, "[item]") != 0 )  // sub_423300 —— [end] → 解析结束
      {
        sub_4D1310(pArg12 + 80);  // 调 sub_4D1310
        for ( kk = sub_4423D0(&v104); v104 != 0; kk = sub_4423D0(&v104) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
        {
          sub_506360(v59);  // 调 sub_506360
          LOBYTE(v124) = 7;  // 调 取 16 位值低 8 位
          v59[0] = kk;
          v59[2] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v59[1] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v59[3] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v59[4] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v59[5] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v59[6] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v59[7] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v59[8] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v41 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          if ( v41 > 0 )
          {
            for ( mm = v41; mm != 0; --mm )  // 遍历计次循环（mm != 0）
            {
              v65[0] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              v65[1] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              sub_5064F0(v65);  // 调 sub_5064F0
            }
          }
          sub_507150(v59);  // 调 sub_507150
          LOBYTE(v124) = 4;  // 调 取 16 位值低 8 位
          sub_4CEB20(v59);  // 调 sub_4CEB20
        }
      }
      else if ( (uint8_t)sub_423300(&v119, "[special passive object]") != 0 )  // sub_423300 —— [end] → 解析结束
      {
        sub_507510(pArg12 + 80);  // 调 sub_507510
        LOBYTE(v124) = 8;  // 调 取 16 位值低 8 位
        sub_4D1350(pArg12 + 92);  // 调 sub_4D1350
        for ( nn = sub_4423D0(&v104); v104 != 0; nn = sub_4423D0(&v104) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
        {
          sub_504B50(&v78);  // 调 sub_504B50
          v78 = nn;
          v79 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v80 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v81 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v44 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          if ( v44 > 0 )
          {
            for ( i1 = v44; i1 != 0; --i1 )  // 遍历计次循环（i1 != 0）
            {
              memset(pBuf, 255, sizeof(pBuf));  // 调 memset 按字节填充
              sub_504500(pBuf);  // sub_504500 —— 掉落/奖励对象类别码解析器
              sub_506560(pBuf);  // 调 sub_506560
            }
          }
          sub_507190(&v78);  // 调 sub_507190
        }
        LOBYTE(v124) = 4;  // 调 取 16 位值低 8 位
        sub_4D1640(v58);  // 调 sub_4D1640
      }
      else if ( (uint8_t)sub_423300(&v119, "[NPC]") != 0 )  // sub_423300 —— [end] → 解析结束
      {
        sub_5E5260((void **)(pArg12 + 104));  // 调 sub_5E5260
        for ( i2 = sub_4423D0(&v104); v104 != 0; i2 = sub_4423D0(&v104) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
        {
          v93 = i2;
          j = (int)&v103;
          sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
          if ( sub_43BCF0(&v103, "[left]") )  // sub_43BCF0 —— 字符串 “[free]”
          {
            v94 = 0;
          }
          else if ( sub_43BCF0(&v103, "[right]") )  // sub_43BCF0 —— 字符串 “[free]”
          {
            v94 = 1;
          }
          v95 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v96 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v97 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          sub_5065F0(&v93);  // 调 sub_5065F0
        }
      }
      else if ( (uint8_t)sub_423300(&v119, "[monster spawn pos]") != 0 )  // sub_423300 —— [end] → 解析结束
      {
        sub_5E5260((void **)(pArg12 + 440));  // 调 sub_5E5260
        v47 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v90 = 0;
        v91 = 0;
        v92 = 0;
        if ( v47 > 0 )
        {
          for ( i3 = v47; i3 != 0; --i3 )  // 遍历计次循环（i3 != 0）
          {
            v90 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
            v91 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
            v92 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
            sub_506680(&v90);  // 调 sub_506680
          }
        }
      }
      else if ( (uint8_t)sub_423300(&v119, "[chaos zone]") != 0 )  // sub_423300 —— [end] → 解析结束
      {
        sub_5E5260((void **)(pArg12 + 456));  // 调 sub_5E5260
        v102 = 0;
        for ( i4 = sub_4423D0(&v102); v102 != 0; i4 = sub_4423D0(&v102) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
        {
          v61[0] = i4;
          v61[1] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v61[2] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v61[3] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v61[4] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          sub_5065F0(v61);  // 调 sub_5065F0
        }
      }
      else
      {
        v98 = v53;
        sub_401690(&v119);  // sub_401690 —— std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全量赋值）
        if ( (uint8_t)sub_442C80((char)v53[0], v53[1], (int)v53[2], (int)v54, (int)v55, (int)v56, j) == 0 )  // sub_442C80 —— 行首是 [ 仍未匹配
        {
          v50 = (const char *)v120;
          if ( v122 < 0x10 )
            v50 = (const char *)&v120;
          off_77F3FC("SCRIPT TAG ERROR! [%s] %s", v2, v50);  // off_77F3FC —— 日志打印（printf 风格）
        }
      }
      goto LABEL_164;  // 跳转 LABEL_164
    }
    sub_4D09A0(pArg12 + 60);  // 调 sub_4D09A0
    for ( i5 = sub_4423D0(&v104); v104 != 0; i5 = sub_4423D0(&v104) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
    {
      sub_504680(&v66);  // 调 sub_504680
      v66 = i5;
      v67 = sub_4423D0(nullptr) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
      v68 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      v69 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      v70 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      v71 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      v72 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      v73 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v103, "[fixed]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        v74 = 0;
      }
      else if ( sub_43BCF0(&v103, "[half]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        v74 = 1;
      }
      else if ( sub_43BCF0(&v103, "[ratio]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        v74 = 2;
      }
      j = (int)&v103;
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v103, "[normal]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        v75 = 0;
      }
      else
      {
        if ( sub_43BCF0(&v103, "[champion]") )  // sub_43BCF0 —— 字符串 “[free]”
        {
          v75 = 1;
          v39 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          if ( v39 <= 0 )
            goto LABEL_119;  // 跳转 LABEL_119
        }
        else
        {
          if ( !sub_43BCF0(&v103, "[super champion]") )  // sub_43BCF0 —— 字符串 “[free]”
          {
            if ( sub_43BCF0(&v103, "[boss]") )  // sub_43BCF0 —— 字符串 “[free]”
              v75 = 3;
            goto LABEL_125;  // 跳转 LABEL_125
          }
          v75 = 2;
          v39 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          if ( v39 <= 0 )
          {
LABEL_119:
            sub_5E5260(&v76);  // 调 sub_5E5260
            goto LABEL_125;  // 跳转 LABEL_125
          }
        }
        sub_506BE0(v39, &v66);  // 调 sub_506BE0
      }
LABEL_125:
      sub_507600(&v66);  // 调 sub_507600
    }
LABEL_164:
    v2 = (const char *)ArgList;
    if ( (uint8_t)sub_443430(&v119) == 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    {
LABEL_165:
      *(uint32_t *)pArg12 = sub_4A2F80(v2);  // 调 +0x00 ← 按文件名查全局 ID 表（未登记 = -1）
      v51 = *(uint32_t *)(pArg12 + 4 * dword_78FF38 + 424);  // dword_78FF38 —— [nation code] → 全局单字节模式标志（sub_442B20 依赖）
      j = -1;
      v56 = nullptr;  // v56 = nullptr 空指针
      if ( v51 == 0 )
        v51 = *(uint32_t *)(pArg12 + 424);  // 读字段 v51 = pArg12+424（f_AtkRateX10）
      sub_4014D0((std::_String_base *)(pArg12 + 308), v51, v56, j);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      if ( Block != nullptr )
        j__free(Block);  // 释放堆块
      if ( v77 != nullptr )
        j__free(v77);  // 释放堆块
      if ( v111 >= 0x10 )
        j__free(v109);  // 释放堆块
      v111 = 15;
      v110 = 0;
      LOBYTE(v109) = 0;  // 调 取 16 位值低 8 位
      LOBYTE(v124) = 0;  // 调 取 16 位值低 8 位
      sub_41B010((void **)&v103);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
      if ( v122 >= 0x10 )
        j__free(v120);  // 释放堆块
      return 1;
    }
  }
  v85 = pArg12 + 20;  // 计算 v85 = pArg12 + 20
  sub_5E5260((void **)(pArg12 + 20));  // 调 sub_5E5260
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
    goto LABEL_164;  // 跳转 LABEL_164
  do
  {
    v118 = 15;
    v117[4] = 0;
    LOBYTE(v117[0]) = 0;  // 调 取 16 位值低 8 位
    j = 2;
    LOBYTE(v124) = 5;  // 调 取 16 位值低 8 位
    v15 = sub_41ACF0(&v103);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    sub_4022F0((std::_String_base *)v116, v101 + v15, j);  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
    v16 = (uint8_t *)v117[0];
    if ( v118 < 0x10 )
      v16 = v117;
    if ( *v16 == 13 )
      goto LABEL_53;  // 跳转 LABEL_53
    v17 = (uint8_t *)v117[0];
    if ( v118 < 0x10 )
      v17 = v117;
    if ( *v17 == 10 )
      goto LABEL_53;  // 跳转 LABEL_53
    v18 = (uint8_t *)v117[0];
    if ( v118 < 0x10 )
      v18 = v117;
    if ( *v18 == 32 )
    {
LABEL_53:
      v23 = v101 + 1;  // 计算 v23 = v101 + 1
    }
    else
    {
      for ( i6 = 0; i6 < 16; ++i6 )  // 遍历计次循环（i6 < 16）
      {
        v20 = (uint8_t *)v117[0];
        if ( v118 < 0x10 )
          v20 = v117;
        v21 = *(uint8_t **)(dword_9B0AB0 + 4 * i6);  // dword_9B0AB0 —— 区码 1 → 切换字符串表
        if ( *v20 == *v21 )  // 若 *v20 == *v21
        {
          v22 = (uint32_t *)v117[0];
          if ( v118 < 0x10 )
            v22 = v117;
          if ( *((uint8_t *)v22 + 1) == v21[1] )  // 若 *((uint8_t *)v22 + 1) == v21[1]
            break;
        }
      }
      if ( i6 == 16 )
      {
        ++v101;  // 计数自增 v101
        ++v100;  // 计数自增 v100
        goto LABEL_55;  // 跳转 LABEL_55
      }
      if ( v99 == -1 )
      {
        v99 = i6;
      }
      else
      {
        v64[1] = i6;
        v64[0] = v99;
        sub_474950(v64);  // sub_474950 —— 调用 sub_474950
        v99 = -1;
      }
      v23 = v101 + 2;  // 计算 v23 = v101 + 2
    }
    v101 = v23;
LABEL_55:
    LOBYTE(v124) = 4;  // 调 取 16 位值低 8 位
    sub_501490(v116);  // 调 sub_501490
  }
  while ( v101 < (int)v98 );  // 当 v101 < (int)v98 循环
  if ( v100 == 0 )
  {
    pArg12 = pArg1;
    goto LABEL_164;  // 跳转 LABEL_164
  }
  sub_4CEB50(&v78);  // sub_4CEB50 —— 成员清理
  sub_4CE820(&v66);  // 调 sub_4CE820
  sub_501490(v108);  // 调 sub_501490
  LOBYTE(v124) = 0;  // 调 取 16 位值低 8 位
  sub_41B010((void **)&v103);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_501490(&v119);  // 调 sub_501490
  return 0;
}


// ------------------------------------------------------------
// 0x508C30 sub_508C30
//   全局数值表加载器：设定根目录 byte_9B7730 并加载文件表（unk_9B7C3C）后，
//   从打开的文件按序读整型填入 unk_9B7418 起 0x188 字节全局表；
//   nArg4 非空时再读第二张表填 dword_9B75A0 区（表用途未在标签层体现，
//   【推断：等级/成长类全局表】）。
// ------------------------------------------------------------
char /*cdecl*/ sub_508C30(const char *pArg1, int nArg2, int nArg3, int nArg4)  // 函数: 清零缓冲
{
  char result; // al
  int *v5; // esi
  int *dword_9B75A02; // esi

  strcpy(byte_9B7730, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B772F[strlen(byte_9B7730)] != 92 && byte_9B772F[strlen(byte_9B7730)] != 47 )  // 若 byte_9B772F[strlen(byte_9B7730)] != 92 && byte_9B772F[strlen(b..
    *(uint16_t *)&byte_9B7730[strlen(byte_9B7730)] = 92;  // 调 求串长
  if ( (uint8_t)sub_443C40((int)&unk_9B7C3C, (char)byte_9B7730, nArg2) == 0 )  // sub_443C40 —— 脚本文件列表装表
    return 0;
  memset(&unk_9B7418, 0, 0x188u);  // 调 memset 按字节填充
  if ( (uint8_t)sub_442A10((char)byte_9B7730, nArg3) == 0 )  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
    return 0;
  v5 = (int *)&unk_9B7418;
  do
    *v5++ = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
  while ( (int)v5 < (int)dword_9B75A0 );  // 当 (int)v5 < (int)dword_9B75A0 循环
  if ( nArg4 != 0 )
  {
    memset(dword_9B75A0, 0, sizeof(dword_9B75A0));  // 调 memset 按字节填充
    result = sub_442A10((char)byte_9B7730, nArg4);  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
    if ( result == 0 )
      return result;
    dword_9B75A02 = dword_9B75A0;
    do
      *dword_9B75A02++ = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
    while ( (int)dword_9B75A02 < (int)&unk_9B772C );  // 当 (int)dword_9B75A02 < (int)&unk_9B772C 循环
  }
  return 1;
}



// ------------------------------------------------------------
// 0x508D50 sub_508D50
//   设定又一脚本根目录（byte_9B7930，补 '\' 或 '/' 结尾）并加载文件表到
//   unk_9B7C48（sub_443C40）。同 4FC840 族。
// ------------------------------------------------------------
bool /*cdecl*/ sub_508D50(const char *pArg1, int nArg2)  // 副本地图(dungeon map)定义解析器（0x1D8 字节对象，sub_4D1680 构造）
{
  strcpy(byte_9B7930, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B792F[strlen(byte_9B7930)] != 92 && byte_9B792F[strlen(byte_9B7930)] != 47 )  // 若 byte_9B792F[strlen(byte_9B7930)] != 92 && byte_9B792F[strlen(b..
    *(uint16_t *)&byte_9B7930[strlen(byte_9B7930)] = 92;  // 调 求串长
  return (uint8_t)sub_443C40((int)&unk_9B7C48, (char)byte_9B7930, nArg2) != 0;  // sub_443C40 —— 脚本文件列表装表
}



// ------------------------------------------------------------
// 0x508DE0 sub_508DE0
//   设定又一脚本根目录（byte_9B7A30，补 '\' 或 '/' 结尾）并加载文件表到
//   unk_9B7C70（sub_443C40）。同 4FC840 族。
// ------------------------------------------------------------
bool /*cdecl*/ sub_508DE0(const char *pArg1, int nArg2)
{
  strcpy(byte_9B7A30, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B7A2F[strlen(byte_9B7A30)] != 92 && byte_9B7A2F[strlen(byte_9B7A30)] != 47 )  // 若 byte_9B7A2F[strlen(byte_9B7A30)] != 92 && byte_9B7A2F[strlen(b..
    *(uint16_t *)&byte_9B7A30[strlen(byte_9B7A30)] = 92;  // 调 求串长
  return (uint8_t)sub_443C40((int)&unk_9B7C70, (char)byte_9B7A30, nArg2) != 0;  // sub_443C40 —— 脚本文件列表装表
}



// ------------------------------------------------------------
// 0x508E70 sub_508E70
//   std::fill_n（44 字节 POD 元素版）：从 pszArg1 起把到 pszArg2 的每个元素
//   用 pArg3 的 0x2C 字节整块覆盖。
// ------------------------------------------------------------
char */*cdecl*/ sub_508E70(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  void *v4; // edi

  for ( result = pszArg1; result != pszArg2; result += 44 )  // 循环：result = pszArg1; result != pszArg2; result += 44
  {
    v4 = result;
    qmemcpy(v4, pArg3, 0x2Cu);  // 调 qmemcpy 内联块拷贝
  }
  return result;
}



// ------------------------------------------------------------
// 0x508EA0 sub_508EA0
//   std::copy（44 字节 POD 元素版，正向）：[pszArg1,pszArg2) 逐元素
//   qmemcpy 0x2C 字节到 pszArg3 起。
// ------------------------------------------------------------
char */*cdecl*/ sub_508EA0(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg12; // edx
  char *result; // eax

  pszArg12 = pszArg1;
  for ( result = pszArg3; pszArg12 != pszArg2; result += 44 )  // 循环：result = pszArg3; pszArg12 != pszArg2; result += 44
  {
    if ( result != nullptr )
      qmemcpy(result, pszArg12, 0x2Cu);  // 调 qmemcpy 内联块拷贝
    pszArg12 += 44;
  }
  return result;
}



// ------------------------------------------------------------
// 0x508EE0 sub_508EE0
//   std::_Fill_n 未初始化构造（44 字节 POD 元素版）：转调 sub_4F8DF0 后返回
//   pszArg1+44*nArg2 尾地址。
// ------------------------------------------------------------
char */*stdcall*/ sub_508EE0(char *pszArg1, char *pszArg2, const void *pArg3)
{
  sub_4F8DF0(pszArg1, pszArg2, pArg3);  // sub_4F8DF0 —— 44 字节元素填充拷贝（nArg2 个副本自 pArg3）
  return &pszArg1[44 * (uint32_t)pszArg2];
}



// ------------------------------------------------------------
// 0x508F10 sub_508F10
//   std::vector<44字节元素>::erase 尾部（pop_back 的截断）：把 pszArg3 之后的
//   元素搬到 [pszArg3..] 收缩区（qmemcpy 0x2C），end 回退；*uArg2 返回新 end。
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
    fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
    pszArg33 = pszArg3;
    if ( pszArg4 != fld_e2 )  // fld_e2=this+8 物品 id
    {
      do
      {
        pszArg422 = pszArg42;
        pszArg332 = pszArg33;
        pszArg42 += 44;
        pszArg33 += 44;
        qmemcpy(pszArg332, pszArg422, 0x2Cu);  // 调 qmemcpy 内联块拷贝
      }
      while ( pszArg42 != fld_e2 );  // 循环直到 pszArg42 != fld_e2
      pszArg32 = pszArg3;
    }
    *(this + 2) = pszArg33;  // 写字段 this+2 ← pszArg33
  }
  *uArg2 = pszArg32;  // *uArg2 写入 pszArg32
  return uArg2;
}



// ------------------------------------------------------------
// 0x508F60 sub_508F60
//   "vector<T> too long" 异常抛出（length_error），永不返回。
// ------------------------------------------------------------
void /*noreturn*/ sub_508F60()  // 函数: 条件抛异常
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
  sub_401740(v1);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x508FD0 sub_508FD0
//   std::vector<12字节元素>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（59EE30/504450/5043B0/5E51C0）；不足 → 扩容三段拷贝重建。
// ------------------------------------------------------------
int /*thiscall*/ sub_508FD0(int *this, char *pszArg2, unsigned int uArg3, int *Block)  // 函数: 释放后返回
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    result = 715827883 * (*(this + 3) - fld_e1);  // this+12 = 技能槽记录次字
    fld_e3 = (*(this + 3) - fld_e1) / 12;  // this+12 = 技能槽记录次字
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_4A30C0(this);  // 调 sub_4A30C0
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
      Blockb = fld_e23;
      if ( ((char *)fld_e23 - pszArg2) / 12 >= uArg3 )
      {
        v27 = &fld_e23[-3 * uArg3];
        *(this + 2) = (int)sub_59EE30(v27, fld_e23, fld_e23);  // sub_59EE30 —— 三元组块搬移辅助
        sub_504450(pszArg2, v27, Blockb);  // sub_504450 —— 搬移插入位后元素
        return sub_5043B0(pszArg2, &pszArg2[12 * uArg3], v25);  // sub_5043B0 —— 在插入位填 n 条
      }
      else
      {
        sub_59EE30(pszArg2, fld_e23, &pszArg2[12 * uArg3]);  // sub_59EE30 —— 三元组块搬移辅助
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 12;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);  // sub_5E51C0 —— 填充补足尾段
        fld_e26 = 12 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        return sub_5043B0(pszArg2, fld_e26 - 12 * uArg3, v25);  // sub_5043B0 —— 在插入位填 n 条
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )  // 若 357913941 - (fld_e3 >> 1) >= fld_e3
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);  // sub_4DA030 —— v13 = 插入数 + sub_4DA030（当前数）
      v15 = 3 * v13;  // 计算 v15 = 3 * v13
      Blocka = operator new(12 * v13);  // 堆分配
      fld_e12 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pszArg2, Blocka);  // sub_59EE30 —— 三元组块搬移辅助
      sub_623C10(v28, uArg3, v25);  // sub_623C10 —— 就地构造（拷贝构造 1 个）
      sub_59EE30(pszArg2, (uint32_t *)*(this + 2), &v28[3 * uArg3]);  // sub_59EE30 —— 三元组块搬移辅助
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 12;  // this+8 = 技能槽记录首字
      v17 = fld_e13 + uArg3;  // 计算 v17 = fld_e13 + uArg3
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 释放堆块
      *(this + 3) = (int)&Blocka[v15];  // 写字段 this+3 ← (int)&Blocka[v15]
      *(this + 2) = (int)&Blocka[3 * v17];  // 写字段 this+2 ← (int)&Blocka[3 * v17]
      *(this + 1) = (int)Blocka;  // 写字段 this+1 ← (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x509280 sub_509280
//   std::vector<44字节元素>::reserve/分配：+4 begin/+8 end/+12 capEnd，
//   超上限 0x5D1745D 抛错（sub_508F60）。
// ------------------------------------------------------------
char /*thiscall*/ sub_509280(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  *(this + 3) = 0;  // 写字段 this+3 ← 0
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x5D1745D )
    sub_508F60(this);  // 调 sub_508F60
  pMem = (char *)operator new(44 * uArg2);  // 堆分配
  *(this + 3) = &pMem[44 * uArg2];  // 写字段 this+3 ← &pMem[44 * uArg2]
  *(this + 1) = pMem;  // 写字段 this+1 ← pMem
  *(this + 2) = pMem;  // 写字段 this+2 ← pMem
  return 1;
}



// ------------------------------------------------------------
// 0x5092D0 sub_5092D0
//   std::vector<44字节元素>::insert(pos, n, val)：容量够 → 尾部腾位
//   （508EA0/4F8D90/508E70/508EE0）；不足 → 扩容三段拷贝重建（上限检查 sub_508F60）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5092D0(int this, char *pszArg2, unsigned int uArg3, void *Block)  // 函数: 释放后返回
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

  qmemcpy(v22, Block, 0x2Cu);  // 调 qmemcpy 内联块拷贝
  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  v22[11] = &v21;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_C = (*(uint32_t *)(this + 12) - fld_4) / 44;  // this+12 物品类型号
  else
    fld_C = 0;  // fld_C=this+12 物品类型号
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 44;  // this+8 物品 id
    else
      fld_8 = 0;  // fld_8=this+8 物品 id
    if ( 97612893 - fld_8 < uArg3 )  // fld_8=this+8 物品 id
      sub_508F60(this);  // 调 sub_508F60
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) / 44;  // this+8 物品 id
    else
      fld_82 = 0;  // fld_82=this+8 物品 id
    if ( fld_C >= uArg3 + fld_82 )  // fld_C=this+12 物品类型号
    {
      fld_83 = *(char **)(this + 8);  // this+8 物品 id
      Blockb = fld_83;  // fld_83=this+8 物品 id
      if ( (fld_83 - pszArg2) / 44 >= uArg3 )  // fld_83=this+8 物品 id
      {
        v24 = &fld_83[-44 * uArg3];  // fld_83=this+8 物品 id
        *(uint32_t *)(this + 8) = sub_508EA0(v24, fld_83, fld_83);  // 写字段 this+8（nSkillRec8） ← sub_508EA0(v24, fld_83, fld_83)
        sub_4F8D90(pszArg2, v24, Blockb);  // sub_4F8D90 —— 44 字节元素反向搬移（qmemcpy 0x2C 每步）
        sub_508E70(pszArg2, &pszArg2[44 * uArg3], v22);  // 调 sub_508E70
      }
      else
      {
        sub_508EA0(pszArg2, fld_83, &pszArg2[44 * uArg3]);  // 调 sub_508EA0
        fld_84 = (char *)(uArg3 - (*(uint32_t *)(this + 8) - (int)pszArg2) / 44);  // this+8 物品 id
        fld_85 = *(char **)(this + 8);  // this+8 物品 id
        v23 = 2;
        sub_508EE0(fld_85, fld_84, v22);  // 调 sub_508EE0
        fld_86 = 44 * uArg3 + *(uint32_t *)(this + 8);  // this+8 物品 id
        *(uint32_t *)(this + 8) = fld_86;  // 写字段 this+8（nSkillRec8） ← fld_86
        sub_508E70(pszArg2, (char *)(fld_86 - 44 * uArg3), v22);  // 调 sub_508E70
      }
    }
    else
    {
      if ( 97612893 - (fld_C >> 1) >= fld_C )  // 若 97612893 - (fld_C >> 1) >= fld_C
        v10 = (fld_C >> 1) + fld_C;  // fld_C=this+12 物品类型号
      else
        v10 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) / 44;  // this+8 物品 id
      else
        fld_87 = 0;  // fld_87=this+8 物品 id
      if ( v10 < uArg3 + fld_87 )  // fld_87=this+8 物品 id
        v10 = uArg3 + sub_527B90(this);  // 调 取 size
      v12 = 44 * v10;  // 计算 v12 = 44 * v10
      Blocka = (char *)operator new(44 * v10);  // 堆分配
      fld_42 = *(char **)(this + 4);  // this+4 宿主对象
      v23 = 0;
      v25 = sub_508EA0(fld_42, pszArg2, Blocka);  // 调 sub_508EA0
      sub_4F8DF0(v25, (char *)uArg3, v22);  // sub_4F8DF0 —— 44 字节元素填充拷贝（nArg2 个副本自 pArg3）
      sub_508EA0(pszArg2, *(char **)(this + 8), &v25[44 * uArg3]);  // 调 sub_508EA0
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_43 = (*(uint32_t *)(this + 8) - fld_43) / 44;  // this+8 物品 id
      v14 = fld_43 + uArg3;  // 计算 v14 = fld_43 + uArg3
      if ( *(uint32_t *)(this + 4) != 0 )  // 若 *(uint32_t *)(this + 4) != 0
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &Blocka[v12];  // 写字段 this+12（nSkillRec12） ← &Blocka[v12]
      *(uint32_t *)(this + 8) = &Blocka[44 * v14];  // 写字段 this+8（nSkillRec8） ← &Blocka[44 * v14]
      *(uint32_t *)(this + 4) = Blocka;  // 写字段 this+4（pHostObj） ← Blocka
    }
  }
}



// ------------------------------------------------------------
// 0x509580 sub_509580
//   std::vector<44字节元素> 复制构造辅助：按源 vector 大小 reserve（sub_509280）
//   后整段 copy（sub_508EA0）。
// ------------------------------------------------------------
char **/*thiscall*/ sub_509580(char **this, int pArg2)  // 函数定义: 拷贝构造到 pszArg3 起
{
  unsigned int v2; // eax
  char *v5; // [esp-14h] [ebp-34h]
  char *v6; // [esp-10h] [ebp-30h]
  char *fld_e1; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(pArg2 + 4);  // 读字段 v2 = pArg2+4（pHostObj）
  v10 = &v8;
  pThis = this;
  if ( v2 != 0 )
    v2 = (int)(*(uint32_t *)(pArg2 + 8) - v2) / 44;
  if ( sub_509280(this, v2) != 0 )  // 若 sub_509280(this, v2) != 0
  {
    fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
    v6 = *(char **)(pArg2 + 8);
    v5 = *(char **)(pArg2 + 4);
    v11 = 0;
    *(this + 2) = sub_508EA0(v5, v6, fld_e1);  // 写字段 this+2 ← sub_508EA0(v5, v6, fld_e1)
  }
  return this;
}



// ------------------------------------------------------------
// 0x509620 sub_509620
//   std::vector<44字节元素>::operator=：按源大小收缩/扩容后整段覆盖
//   （多余容量销毁 4F8DC0；不够则重建 sub_509280+433CF0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_509620(int this, int pArg2)  // 函数: 释放后返回
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
  v3 = *(uint32_t *)(pArg2 + 4);  // 读字段 v3 = pArg2+4（pHostObj）
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) / 44) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // 若 *(uint32_t *)(this + 4) != 0
      j__free(*(void **)(this + 4));  // 释放堆块
    *(uint32_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
    *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
    *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
    return this;
  }
  fld_4 = *(char **)(this + 4);  // this+4 宿主对象
  if ( fld_4 != nullptr )  // fld_4=this+4 宿主对象
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 44;  // this+8 物品 id
  else
    fld_8 = 0;  // fld_8=this+8 物品 id
  if ( v4 > fld_8 )  // fld_8=this+8 物品 id
  {
    if ( fld_4 != nullptr )  // fld_4=this+4 宿主对象
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 44;  // this+12 物品类型号
    else
      fld_C = 0;  // fld_C=this+12 物品类型号
    if ( v4 <= fld_C )  // fld_C=this+12 物品类型号
    {
      v10 = (char *)(*(uint32_t *)(pArg2 + 4) + 44 * sub_527B90(this));  // 调 取 size
      sub_4F8DC0(*(char **)(pArg2 + 4), v10, fld_4);  // sub_4F8DC0 —— 44 字节元素正向搬移（qmemcpy 0x2C 每步）
      *(uint32_t *)(this + 8) = sub_508EA0(v10, *(char **)(pArg2 + 8), *(char **)(this + 8));  // 写字段 this+8（nSkillRec8） ← sub_508EA0(v10, *(char **)(pArg2 + 8), *(char **)(this + 8))
      return this;
    }
    if ( fld_4 != nullptr )  // fld_4=this+4 宿主对象
      j__free(*(void **)(this + 4));  // 释放堆块
    v11 = sub_527B90(pArg2);  // 调 sub_527B90
    if ( sub_509280((uint32_t *)this, v11) != 0 )  // 若 sub_509280((uint32_t *)this, v11) != 0
      *(uint32_t *)(this + 8) = sub_433CF0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));  // sub_433CF0 —— 44B 元素区间拷贝
    return this;
  }
  sub_4F8DC0(*(char **)(pArg2 + 4), *(char **)(pArg2 + 8), *(char **)(this + 4));  // sub_4F8DC0 —— 44 字节元素正向搬移（qmemcpy 0x2C 每步）
  v8 = *(uint32_t *)(pArg2 + 4);  // 读字段 v8 = pArg2+4（pHostObj）
  if ( v8 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 44 * ((*(uint32_t *)(pArg2 + 8) - v8) / 44);  // 写字段 this+8（nSkillRec8） ← *(uint32_t *)(this + 4) + 44 * ((*(uint32_t *)(pArg2 + 8) - v8) / 44)
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);  // 写字段 this+8（nSkillRec8） ← *(uint32_t *)(this + 4)
  return this;
}



// ------------------------------------------------------------
// 0x5097A0 sub_5097A0
//   std::vector<vector<44字节>>::assign 正向（16 字节内层 vector 逐个
//   operator= 赋值，sub_509620），步进 16 字节。
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
    sub_509620(nArg32, nArg12);  // 调 sub_509620
    nArg12 += 16;
    nArg32 += 16;
  }
  while ( nArg12 != nArg2 );  // 循环直到 nArg12 != nArg2
  return nArg32;
}



// ------------------------------------------------------------
// 0x5097E0 sub_5097E0
//   std::vector<vector<44字节>>::assign 反向（copy_backward 语义）：
//   从尾往头逐 16 字节内层 vector 赋值（sub_509620）。
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
    sub_509620(nArg32, nArg22);  // 调 sub_509620
  }
  while ( nArg22 != nArg1 );  // 循环直到 nArg22 != nArg1
  return nArg32;
}



// ------------------------------------------------------------
// 0x509820 sub_509820
//   std::vector<12字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_508FD0 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_509820(int *this, uint32_t *uArg2, uint32_t *uArg3, int *Block)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )  // fld_e1=this+4 宿主对象
    v6 = ((int)uArg3 - fld_e1) / 12;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_508FD0(this, uArg3, 1u, Block);  // 调 sub_508FD0
  *uArg2 = *(this + 1) + 12 * v6;  // *uArg2 写入 *(this + 1) + 12 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x509890 sub_509890
//   std::vector<44字节元素>::resize(n)：n ≤ 现有 → 尾部截断（sub_508F10）；
//   n > 现有 → 从 end 补构造 a2-现有 个元素（sub_5092D0，值 = 栈上 Block）。
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

  v13 = *(uint32_t *)(this + 4);  // 读字段 v13 = this+4（pHostObj）
  if ( v13 != 0 )  // v13=this+4 pHostObj
    v14 = (*(uint32_t *)(this + 8) - v13) / 44;  // this+8 物品 id
  else
    v14 = 0;  // v14=this+8 物品 id
  if ( v14 >= a2 )  // v14=this+8 物品 id
  {
    if ( v13 != 0 && a2 < (*(uint32_t *)(this + 8) - v13) / 44 )  // this+8 物品 id
      sub_508F10((char **)this, &a2, (char *)(v13 + 44 * a2), *(char **)(this + 8));  // 调 sub_508F10
  }
  else
  {
    if ( v13 != 0 )  // v13=this+4 pHostObj
      v15 = (*(uint32_t *)(this + 8) - v13) / 44;  // this+8 物品 id
    else
      v15 = 0;  // v15=this+8 物品 id
    sub_5092D0(this, *(char **)(this + 8), a2 - v15, &Block);  // 调 sub_5092D0
  }
}



// ------------------------------------------------------------
// 0x509930 sub_509930
//   std::vector<44字节元素>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_5092D0 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_509930(uint32_t *this, uint32_t *uArg2, char *pszArg3, void *Block)  // 函数定义: 插入路径扩容
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 44 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (int)&pszArg3[-fld_e1] / 44;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_5092D0((int)this, pszArg3, 1u, Block);  // 调 sub_5092D0
  *uArg2 = *(this + 1) + 44 * v6;  // *uArg2 写入 *(this + 1) + 44 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x5099A0 sub_5099A0
//   std::fill（16 字节内层 vector<44B> 元素版）：[nArg1,nArg2) 逐 16 字节
//   用 nArg3 模板赋值（sub_509620）。
// ------------------------------------------------------------
int /*cdecl*/ sub_5099A0(int nArg1, int nArg2, int nArg3)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 16 )  // 循环：i = nArg1; i != nArg2; i += 16
    result = sub_509620(i, nArg3);  // 调 sub_509620
  return result;
}



// ------------------------------------------------------------
// 0x5099D0 sub_5099D0
//   std::copy_backward（16 字节内层 vector<44B> 元素版）：转调 sub_5097E0。
// ------------------------------------------------------------
int /*cdecl*/ sub_5099D0(int nArg1, int nArg2, int nArg3)  // 函数: 转发 ·sub_5097E0
{
  return sub_5097E0(nArg1, nArg2, nArg3);  // 调 sub_5097E0
}



// ------------------------------------------------------------
// 0x5099F0 sub_5099F0
//   std::copy（16 字节内层 vector<44B> 元素版，正向）：[nArg1,nArg2) 逐元素
//   经 sub_509580 拷贝构造到 pszArg3 起，返回尾地址。
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
  while ( nArg1 != nArg2 )  // 循环直到 nArg1 != nArg2
  {
    LOBYTE(v7) = 1;  // 调 取 16 位值低 8 位
    if ( pszArg32 != nullptr )
      sub_509580(pszArg32, nArg1);  // 调 sub_509580
    pszArg32 += 4;
    LOBYTE(v7) = 0;  // 调 取 16 位值低 8 位
    nArg1 += 16;
  }
  return pszArg32;
}



// ------------------------------------------------------------
// 0x509A80 sub_509A80
//   std::vector<12字节元素>::push_back：容量够 → 在 end 直写（sub_623C10）；
//   不够 → 转调 sub_509820 插入路径扩容。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_509A80(int *this, int *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 12 )  // fld_e1=this+4 宿主对象
    return sub_509820(this, &Block, (uint32_t *)*(this + 2), Block);  // 调 sub_509820
  fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
  result = (uint32_t *)sub_623C10(fld_e22, 1, Block);  // sub_623C10 —— 就地构造（拷贝构造 1 个）
  *(this + 2) = fld_e22 + 12;  // 写字段 this+2 ← fld_e22 + 12
  return result;
}



// ------------------------------------------------------------
// 0x509B00 sub_509B00
//   std::vector<32字节元素>::push_back：容量够 → 在 end 直写（sub_4DAB30）；
//   不够 → sub_4DE980 插入路径扩容。
// ------------------------------------------------------------
int /*thiscall*/ sub_509B00(int *this, void *Block)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  int result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 5;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 5 )  // fld_e1=this+4 宿主对象
    return sub_4DE980(*(this + 2), 1, Block);  // sub_4DE980 —— vector<32B>::_Insert_n（在 pszArg2 位置填充插入 uArg3 个值）
  fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
  result = sub_4DAB30(fld_e22, 1, Block);  // sub_4DAB30 —— 定长块批量填充（cdecl）
  *(this + 2) = fld_e22 + 32;  // 写字段 this+2 ← fld_e22 + 32
  return result;
}



// ------------------------------------------------------------
// 0x509B70 sub_509B70
//   std::vector<44字节元素>::push_back：容量够 → 在 end 直写（sub_4F8DF0）；
//   不够 → 转调 sub_509930 插入路径扩容。
// ------------------------------------------------------------
char */*thiscall*/ sub_509B70(int this, void *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  char *fld_82; // edi
  char *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 44;  // this+8 物品 id
  else
    fld_8 = 0;  // fld_8=this+8 物品 id
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 44 )  // this+12 物品类型号
    return (char *)sub_509930((uint32_t *)this, &Block, *(char **)(this + 8), Block);  // 调 插入路径扩容
  fld_82 = *(char **)(this + 8);  // this+8 物品 id
  result = sub_4F8DF0(fld_82, (char *)1, Block);  // sub_4F8DF0 —— 44 字节元素填充拷贝（nArg2 个副本自 pArg3）
  *(uint32_t *)(this + 8) = fld_82 + 44;  // 写字段 this+8（nSkillRec8） ← fld_82 + 44
  return result;
}



// ------------------------------------------------------------
// 0x509C00 sub_509C00
//   std::copy（16 字节内层 vector<44B> 元素版，正向）：[pszArg1, nArg2) 逐元素
//   经 sub_509580 拷贝构造到 nArg3 起。
// ------------------------------------------------------------
char **/*cdecl*/ sub_509C00(char **pszArg1, int nArg2, int nArg3)  // 函数定义: 后返回尾地址
{
  char **pszArg12; // esi
  char **result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pszArg12 = pszArg1;
  v6[4] = v6;
  v6[3] = pszArg1;
  v7 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    LOBYTE(v7) = 1;  // 调 取 16 位值低 8 位
    if ( pszArg12 != nullptr )
      result = sub_509580(pszArg12, nArg3);  // 调 sub_509580
    --nArg2;  // 计数自减 nArg2
    pszArg12 += 4;
    LOBYTE(v7) = 0;  // 调 取 16 位值低 8 位
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
char /*cdecl*/ sub_509C90(int pArg1, int nArg2)  // sub_509C90 —— ★★ 怪物数据文件解析器（MonsterBaseParameter.tbl 族；技能/属性块通用）
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B7830, nArg2);  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )
  {
    sub_4CEB80(pArg1);  // 调 sub_4CEB80
    sub_443300(pArg1 + 928, "%s%s", (char)&unk_9B7830);  // 调 格式化串取目录前缀
    v42 = 15;
    v41 = 0;
    LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
    v44 = 0;
    v37 = nullptr;  // v37 = nullptr 空指针
    sub_41BFE0(&v37, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
    LOBYTE(v44) = 1;  // 调 取 16 位值低 8 位
    m = 0;
    while ( (uint8_t)sub_443430(v39) != 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    {
      sub_442B20(v39);  // sub_442B20 —— 国家码标签配对校验（void）
      if ( sub_40BF00((std::_String_base *)v39, 0, v41, "[name]", 6u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        goto LABEL_162;  // 跳转 LABEL_162
      if ( sub_40BF00((std::_String_base *)v39, 0, v41, "[width]", 7u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)v39, 0, v41, "[floating height]", 0x11u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)v39, 0, v41, "[layer]", 7u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( (uint8_t)sub_423300(v39, "[category]") != 0 )  // sub_423300 —— [end] → 解析结束
            {
              sub_5E5260((void *)(pArg1 + 48));  // 调 sub_5E5260
              while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              {
                v4 = 0;
                ii = 0;
                while ( !sub_43BCF0(&v37, off_791F80[v4]) )  // sub_43BCF0 —— 字符串 “[free]”
                {
                  if ( ++v4 >= 22 )
                  {
                    ii = v4;
                    goto LABEL_18;  // 跳转 LABEL_18
                  }
                }
                ii = v4;
                sub_431230(&ii);  // sub_431230 —— uint32 vector push_back
LABEL_18:
                ;
              }
              continue;
            }
            if ( (uint8_t)sub_423300(v39, "[ability category]") != 0 )  // sub_423300 —— [end] → 解析结束
            {
              v33 = 0;
              v31 = 13;
              v32 = 0;
              sub_5E5260((void *)(pArg1 + 128));  // 调 sub_5E5260
              while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              {
                v5 = 0;
                while ( !sub_43BCF0(&v37, off_795B2C[v5]) )  // sub_43BCF0 —— 字符串 “[free]”
                {
                  if ( ++v5 >= 13 )
                    goto LABEL_31;  // 跳转 LABEL_31
                }
                v31 = v5;
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                if ( sub_43BCF0(&v37, "+") )  // sub_43BCF0 —— 字符串 “[free]”
                {
                  v32 = 0;
                }
                else if ( sub_43BCF0(&v37, "*") )  // sub_43BCF0 —— 字符串 “[free]”
                {
                  v32 = 1;
                }
                v33 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
LABEL_31:
                sub_509A80(&v31);  // 调 sub_509A80
              }
              continue;
            }
            if ( (uint8_t)sub_423300(v39, "[ability table]") != 0 )  // sub_423300 —— [end] → 解析结束
            {
              *(uint32_t *)(pArg1 + 144) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
            }
            else
            {
              if ( (uint8_t)sub_423300(v39, "[summon skill status up rate]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                v6 = (float *)(pArg1 + 148);
                for ( i = 10; i != 0; --i )  // 遍历计次循环（i != 0）
                  *v6++ = sub_442480(0);  // sub_442480 —— 脚本 token 数值解析（double 版）
                continue;
              }
              if ( (uint8_t)sub_423300(v39, "[level]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 188) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 192) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[fire resistance]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 196) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 200) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[water resistance]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 204) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 208) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[dark resistance]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 212) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 216) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[light resistance]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 220) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 224) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[HP regen speed]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 356) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 360) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[MP regen speed]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 364) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 368) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[move speed]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 372) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 376) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[attack speed]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 380) = sub_4423D0(0);   // +380 [attack speed] 基础（+384 加成）
                *(uint32_t *)(pArg1 + 384) = sub_4423D0(0);   //   攻速聚合 base×(1+stat×0.01) 的源头（研究 20 §16）
              }
              else if ( (uint8_t)sub_423300(v39, "[cast speed]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 388) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 392) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[hit recovery]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 396) = sub_4423D0(0);   // +396 [hit recovery] 基础（基础/加成 双格）
                *(uint32_t *)(pArg1 + 400) = sub_4423D0(0);   // +400 [hit recovery] 加成（研究 20 §12：
                                                           //   客户端仅解析不消费，权威时长在服务端）
              }
              else if ( (uint8_t)sub_423300(v39, "[jump power]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 404) = sub_4423D0(0);   // +404 [jump power] 基础（+408 加成）
                *(uint32_t *)(pArg1 + 408) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[jump speed]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 412) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 416) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[weight]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 420) = sub_4423D0(0);   // +420 [weight] 基础（+424 加成）
                *(uint32_t *)(pArg1 + 424) = sub_4423D0(0);   //   ★ 更正研究 20 §19 "全 PE 无 [weight] 标签"之误
              }
              else if ( (uint8_t)sub_423300(v39, "[superarmor on attack]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 500) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 504) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[sight]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 444) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[targeting time term]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 448) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[targeting on attack]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 452) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v39, "[targeting on damage]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint8_t *)(pArg1 + 453) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else
              {
                if ( (uint8_t)sub_423300(v39, "[targeting high level]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  if ( sub_4423D0(0) != 0 )  // sub_4423D0 —— [LOOP] → 动画对象+160
                    *(uint32_t *)(pArg1 + 456) = 2;  // 写字段 pArg1+456（pKeyVecEnd） ← 2
                  continue;
                }
                if ( (uint8_t)sub_423300(v39, "[targeting low level]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  if ( sub_4423D0(0) != 0 )  // sub_4423D0 —— [LOOP] → 动画对象+160
                    *(uint32_t *)(pArg1 + 456) = 1;  // 写字段 pArg1+456（pKeyVecEnd） ← 1
                  continue;
                }
                if ( (uint8_t)sub_423300(v39, "[targeting high HP]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  if ( sub_4423D0(0) != 0 )  // sub_4423D0 —— [LOOP] → 动画对象+160
                    *(uint32_t *)(pArg1 + 460) = 2;  // 写字段 pArg1+460（bSpiritFlag） ← 2
                  continue;
                }
                if ( (uint8_t)sub_423300(v39, "[targeting low HP]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  if ( sub_4423D0(0) != 0 )  // sub_4423D0 —— [LOOP] → 动画对象+160
                    *(uint32_t *)(pArg1 + 460) = 1;  // 写字段 pArg1+460（bSpiritFlag） ← 1
                  continue;
                }
                if ( (uint8_t)sub_423300(v39, "[targeting nearest]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 468) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting attacker]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 469) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting from direction]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 470) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting low physical attack]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 472) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting low physical defense]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 476) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting low magical attack]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 480) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting low magical defense]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 484) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[targeting downed]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint8_t *)(pArg1 + 488) = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[warlike]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 492) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[attack delay]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 496) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                }
                else if ( (uint8_t)sub_423300(v39, "[stuckbonus on damage]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  *(uint32_t *)(pArg1 + 428) = sub_4423D0(0);  // +428 [stuckbonus on damage] 档 1/4（攻方硬直加成）
                  *(uint32_t *)(pArg1 + 432) = sub_4423D0(0);  // +432 档 2/4
                  *(uint32_t *)(pArg1 + 436) = sub_4423D0(0);  // +436 档 3/4
                  *(uint32_t *)(pArg1 + 440) = sub_4423D0(0);  // +440 档 4/4（按伤害类四档 —— 研究 20 §12）
                }
                else
                {
                  if ( (uint8_t)sub_423300(v39, "[item]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    sub_5E5260((void *)(pArg1 + 64));  // 调 sub_5E5260
                    for ( j = sub_4423D0(&m); m != 0; j = sub_4423D0(&m) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    {
                      v9 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                      v22[0] = j;
                      v22[1] = v9;
                      sub_474950(v22);  // sub_474950 —— 调用 sub_474950
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[common champion drop item]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    sub_5E5260((void *)(pArg1 + 80));  // 调 sub_5E5260
                    for ( k = sub_4423D0(&m); m != 0; k = sub_4423D0(&m) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    {
                      v11 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                      v20[0] = k;
                      v20[1] = v11;
                      sub_474950(v20);  // sub_474950 —— 调用 sub_474950
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[common champion elemental property]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    sub_5E5260((void *)(pArg1 + 1420));  // 调 sub_5E5260
                    for ( m = sub_442E10(); m != 0; m = sub_442E10() )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    {
                      v12 = 0;
                      ii = 0;
                      while ( 1 )  // 当 1 循环
                      {
                        v13 = (const char *)sub_442780(v12);  // 【当前元素标签 setter（全局 dword_97B384）】
                        if ( sub_43BCF0(&v37, v13) )  // sub_43BCF0 —— 字符串 “[free]”
                          break;
                        if ( ++v12 >= 5 )
                        {
                          ii = v12;
                          goto LABEL_126;  // 跳转 LABEL_126
                        }
                      }
                      ii = v12;
                      sub_431230(&ii);  // sub_431230 —— uint32 vector push_back
LABEL_126:
                      ;
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[super champion drop item]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    sub_5E5260((void *)(pArg1 + 96));  // 调 sub_5E5260
                    for ( n = sub_4423D0(&m); m != 0; n = sub_4423D0(&m) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    {
                      v15 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                      v21[0] = n;
                      v21[1] = v15;
                      sub_474950(v21);  // sub_474950 —— 调用 sub_474950
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[attack kind]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    sub_5E5260((void *)(pArg1 + 900));  // 调 sub_5E5260
                    while ( 1 )  // 当 1 循环
                    {
                      v23[0] = false;
                      v27 = 0;
                      v28 = 0;
                      v29 = 0;
                      v30 = 0;
                      v25 = 0.0;  // 浮点常量 v25 ← 0.0
                      v26 = 0.0;  // 浮点常量 v26 ← 0.0
                      v24 = sub_442480(&v35);  // sub_442480 —— 脚本 token 数值解析（double 版）
                      if ( v35 == 0 )
                        break;
                      v25 = sub_442480(0);  // sub_442480 —— 脚本 token 数值解析（double 版）
                      v26 = sub_442480(0);  // sub_442480 —— 脚本 token 数值解析（double 版）
                      v23[0] = sub_4423D0(0) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
                      v27 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                      v28 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                      v29 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                      v30 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                      sub_509B00(v23);  // 调 sub_509B00
                    }
                    continue;
                  }
                  if ( (uint8_t)sub_423300(v39, "[die effect]") != 0 )  // sub_423300 —— [end] → 解析结束
                  {
                    *(uint32_t *)(pArg1 + 916) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    *(uint32_t *)(pArg1 + 920) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                    *(uint32_t *)(pArg1 + 924) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  }
                  else
                  {
                    if ( (uint8_t)sub_423300(v39, "[face image]") == 0 )  // sub_423300 —— [end] → 解析结束
                    {
                      if ( (uint8_t)sub_423300(v39, "[waiting motion]") == 0  // sub_423300 —— [end] → 解析结束
                        && (uint8_t)sub_423300(v39, "[move motion]") == 0  // sub_423300 —— [end] → 解析结束
                        && (uint8_t)sub_423300(v39, "[sit motion]") == 0  // sub_423300 —— [end] → 解析结束
                        && (uint8_t)sub_423300(v39, "[damage motion 1]") == 0  // sub_423300 —— [end] → 解析结束
                        && (uint8_t)sub_423300(v39, "[damage motion 2]") == 0  // sub_423300 —— [end] → 解析结束
                        && (uint8_t)sub_423300(v39, "[down motion]") == 0  // sub_423300 —— [end] → 解析结束
                        && (uint8_t)sub_423300(v39, "[overturn motion]") == 0  // sub_423300 —— [end] → 解析结束
                        && (uint8_t)sub_423300(v39, "[jump motion]") == 0  // sub_423300 —— [end] → 解析结束
                        && (uint8_t)sub_423300(v39, "[jumpattack motion]") == 0 )  // sub_423300 —— [end] → 解析结束
                      {
                        if ( (uint8_t)sub_423300(v39, "[attack motion]") != 0 )  // sub_423300 —— [end] → 解析结束
                        {
                          sub_4017E0(pArg1 + 792);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                          while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                            sub_420BB0(&v37);  // sub_420BB0 —— vector push_back（4 字节元素）
                          continue;
                        }
                        if ( (uint8_t)sub_423300(v39, "[etc motion]") != 0 )  // sub_423300 —— [end] → 解析结束
                        {
                          sub_4017E0(pArg1 + 808);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                          while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                            sub_420BB0(&v37);  // sub_420BB0 —— vector push_back（4 字节元素）
                          continue;
                        }
                        if ( (uint8_t)sub_423300(v39, "[jumpattack info]") == 0 )  // sub_423300 —— [end] → 解析结束
                        {
                          if ( (uint8_t)sub_423300(v39, "[attack info]") != 0 )  // sub_423300 —— [end] → 解析结束
                          {
                            sub_4017E0(pArg1 + 852);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                              sub_420BB0(&v37);  // sub_420BB0 —— vector push_back（4 字节元素）
                          }
                          else if ( (uint8_t)sub_423300(v39, "[etc attack info]") != 0 )  // sub_423300 —— [end] → 解析结束
                          {
                            sub_4017E0(pArg1 + 868);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                              sub_420BB0(&v37);  // sub_420BB0 —— vector push_back（4 字节元素）
                          }
                          else if ( (uint8_t)sub_423300(v39, "[int data]") != 0 )  // sub_423300 —— [end] → 解析结束
                          {
                            sub_5E5260((void *)(pArg1 + 884));  // 调 sub_5E5260
                            for ( ii = sub_4423D0(&m); m != 0; ii = sub_4423D0(&m) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                              sub_431230(&ii);  // sub_431230 —— uint32 vector push_back
                          }
                          else if ( (uint8_t)sub_423300(v39, "[speech on situation]") != 0 )  // sub_423300 —— [end] → 解析结束
                          {
                            sub_432D20(&v34);  // sub_432D20 —— 共享串槽初始化（空串）
                            LOBYTE(v44) = 2;  // 调 取 16 位值低 8 位
                            v16 = pArg1 + 956;  // 计算 v16 = pArg1 + 956
                            for ( jj = 29; jj != 0; --jj )  // 遍历计次循环（jj != 0）
                            {
                              sub_4017E0(v16);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                              v16 += 16;
                            }
                            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                            {
                              sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                              sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                              if ( !sub_43BCF0(&v37, "[on attack]")  // sub_43BCF0 —— 字符串 “[free]”
                                && !sub_43BCF0(&v37, "[on damage]")  // sub_43BCF0 —— 字符串 “[free]”
                                && !sub_43BCF0(&v37, "[on die]")  // sub_43BCF0 —— 字符串 “[free]”
                                && !sub_43BCF0(&v37, "[on revenge]")  // sub_43BCF0 —— 字符串 “[free]”
                                && !sub_43BCF0(&v37, "[on etc]")  // sub_43BCF0 —— 字符串 “[free]”
                                && !sub_43BCF0(&v37, "[on appear]")  // sub_43BCF0 —— 字符串 “[free]”
                                && !sub_43BCF0(&v37, "[on disappear]")  // sub_43BCF0 —— 字符串 “[free]”
                                && !sub_43BCF0(&v37, "[on go to help]") )  // sub_43BCF0 —— 字符串 “[free]”
                              {
                                sub_43BCF0(&v37, "[on stand]");  // sub_43BCF0 —— 字符串 “[free]”
                              }
                              sub_420BB0(&v34);  // sub_420BB0 —— vector push_back（4 字节元素）
                            }
                            LOBYTE(v44) = 1;  // 调 取 16 位值低 8 位
                            sub_41B010(&v34);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
                          }
                          else if ( (uint8_t)sub_423300(v39, "[spawn prob]") != 0 )  // sub_423300 —— [end] → 解析结束
                          {
                            *(uint32_t *)(pArg1 + 1436) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                          }
                          else
                          {
                            off_791FD82 = off_791FD8;
                            v19 = (uint32_t *)(pArg1 + 232);
                            do
                            {
                              if ( (uint8_t)sub_423300(v39, *off_791FD82) != 0 )  // sub_423300 —— [end] → 解析结束
                              {
                                *(v19 - 1) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                                *v19 = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                              }
                              ++off_791FD82;  // 计数自增 off_791FD82
                              v19 += 2;
                            }
                            while ( (int)off_791FD82 < (int)off_792018 );  // 当 (int)off_791FD82 < (int)off_792018 循环
                          }
                          continue;
                        }
                      }
LABEL_162:
                      sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                      continue;
                    }
                    sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
                    *(uint32_t *)(pArg1 + 536) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
                  }
                }
              }
            }
          }
          else
          {
            sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
            v3 = sub_41ACF0(&v37);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
            *(uint32_t *)(pArg1 + 44) = sub_4425F0(v3);  // sub_4425F0 —— 场景前景/背景档位标签→索引
          }
        }
        else
        {
          *(uint32_t *)(pArg1 + 40) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
        }
      }
      else
      {
        *(uint32_t *)(pArg1 + 32) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
        *(uint32_t *)(pArg1 + 36) = sub_4423D0(0);  // sub_4423D0 —— [LOOP] → 动画对象+160
      }
    }
    *(uint32_t *)pArg1 = sub_4A2F80(nArg2);  // 调 +0x00 ← 按文件名查全局 ID 表（未登记 = -1）
    LOBYTE(v44) = 0;  // 调 取 16 位值低 8 位
    sub_41B010(&v37);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    if ( v42 >= 0x10 )
      j__free(Block);  // 释放堆块
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
char /*cdecl*/ sub_50AF40(int pArg1, int nArg2)  // sub_50AF40 —— 地图物件(map object)定义解析器
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
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B7930, nArg2);  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result == 0 )
    return result;
  sub_4CF050(pArg1);  // 调 sub_4CF050
  sub_443300(pArg1 + 220, "%s%s", (char)&unk_9B7930);  // 调 格式化串取目录前缀
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  v14 = 0;
  v8 = nullptr;  // v8 = nullptr 空指针
  sub_41BFE0(&v8, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  LOBYTE(v14) = 1;  // 调 取 16 位值低 8 位
  v7 = 0;
  if ( (uint8_t)sub_443430(v9) == 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    goto LABEL_50;  // 跳转 LABEL_50
  do
  {
    sub_442B20(v9);  // sub_442B20 —— 国家码标签配对校验（void）
    if ( sub_40BF00((std::_String_base *)v9, 0, v11, "[name]", 6u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
LABEL_36:
      sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v9, 0, v11, "[width]", 7u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      *(uint32_t *)(pArg1 + 32) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      *(uint32_t *)(pArg1 + 36) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v9, 0, v11, "[floating height]", 0x11u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      *(uint32_t *)(pArg1 + 40) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v9, 0, v11, "[layer]", 7u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      v4 = sub_41ACF0(&v8);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      *(uint32_t *)(pArg1 + 44) = sub_4425F0(v4);  // sub_4425F0 —— 场景前景/背景档位标签→索引
      continue;
    }
    if ( (uint8_t)sub_423300(v9, "[pass type]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      if ( sub_43BCF0(&v8, "[pass all]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        *(uint32_t *)(pArg1 + 48) = 0;  // 写字段 pArg1+48（pCmdVecBegin48） ← 0
      }
      else if ( sub_43BCF0(&v8, "[pass only float type]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        *(uint32_t *)(pArg1 + 48) = 1;  // 写字段 pArg1+48（pCmdVecBegin48） ← 1
      }
      else if ( sub_43BCF0(&v8, "[do not pass]") )  // sub_43BCF0 —— 字符串 “[free]”
      {
        *(uint32_t *)(pArg1 + 48) = 2;  // 写字段 pArg1+48（pCmdVecBegin48） ← 2
      }
    }
    else
    {
      if ( (uint8_t)sub_423300(v9, "[piercing power]") != 0 )  // sub_423300 —— [end] → 解析结束
      {
        *(uint32_t *)(pArg1 + 52) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        continue;
      }
      if ( (uint8_t)sub_423300(v9, "[category]") != 0 )  // sub_423300 —— [end] → 解析结束
      {
        sub_5E5260((void **)(pArg1 + 56));  // 调 sub_5E5260
        while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        {
          v5 = 0;
          i = 0;
          while ( !sub_43BCF0(&v8, off_791F80[v5]) )  // sub_43BCF0 —— 字符串 “[free]”
          {
            if ( ++v5 >= 22 )
            {
              i = v5;
              goto LABEL_27;  // 跳转 LABEL_27
            }
          }
          i = v5;
          sub_431230(pArg1 + 56, &i);  // sub_431230 —— uint32 vector push_back
LABEL_27:
          ;
        }
      }
      else
      {
        if ( (uint8_t)sub_423300(v9, "[basic motion]") != 0 )  // sub_423300 —— [end] → 解析结束
          goto LABEL_36;  // 跳转 LABEL_36
        if ( (uint8_t)sub_423300(v9, "[etc motion]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          sub_4017E0(pArg1 + 100);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
          while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
            sub_420BB0(&v8);  // sub_420BB0 —— vector push_back（4 字节元素）
        }
        else
        {
          if ( (uint8_t)sub_423300(v9, "[destroy particle]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v9, "[attack info]") != 0 )  // sub_423300 —— [end] → 解析结束
          {
            goto LABEL_36;  // 跳转 LABEL_36
          }
          if ( (uint8_t)sub_423300(v9, "[etc attack info]") != 0 )  // sub_423300 —— [end] → 解析结束
          {
            sub_4017E0(pArg1 + 172);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              sub_420BB0(&v8);  // sub_420BB0 —— vector push_back（4 字节元素）
          }
          else if ( (uint8_t)sub_423300(v9, "[int data]") != 0 )  // sub_423300 —— [end] → 解析结束
          {
            sub_5E5260((void **)(pArg1 + 188));  // 调 sub_5E5260
            for ( i = sub_4423D0(&v7); v7 != 0; i = sub_4423D0(&v7) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
              sub_431230(pArg1 + 188, &i);  // sub_431230 —— uint32 vector push_back
          }
          else if ( (uint8_t)sub_423300(v9, "[string data]") != 0 )  // sub_423300 —— [end] → 解析结束
          {
            sub_4017E0(pArg1 + 204);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              sub_420BB0(&v8);  // sub_420BB0 —— vector push_back（4 字节元素）
          }
        }
      }
    }
  }
  while ( (uint8_t)sub_443430(v9) != 0 );  // sub_443430 —— 读 token 到 string + 国家码标记
  nArg22 = nArg2;
LABEL_50:
  *(uint32_t *)pArg1 = sub_4A2F80(nArg22);  // 调 +0x00 ← 按文件名查全局 ID 表（未登记 = -1）
  LOBYTE(v14) = 0;  // 调 取 16 位值低 8 位
  sub_41B010(&v8);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  if ( v12 >= 0x10 )
    j__free(Block);  // 释放堆块
  return 1;
}


// ------------------------------------------------------------
// 0x50B400 sub_50B400 —— PassiveObject(PO)定义解析器（普通物件，非技能 PO）
//   标签族：几何 [name]/[width]/[floating height]/[layer]；时序 [recovery time] 恢复时间；
//   运动 [direction correct]/[move speed]/[gravity]；动作 [basic motion]/[etc motion]；
//   攻击数据引用 [attack info]（经 sub_420BB0 打包）；[int data]/[string data] 通用袋。
//   标签总数 13。调用者：sub_4D2D60 工厂（PO 类）。
// ------------------------------------------------------------
char /*cdecl*/ sub_50B400(int pArg1, int nArg2)  // sub_50B400 —— PassiveObject(PO)定义解析器（普通物件，非技能 PO）
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
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B7A30, nArg2);  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result == 0 )
    return result;
  sub_4CF120(pArg1);  // 调 sub_4CF120
  sub_443300(pArg1 + 172, "%s%s", (char)&unk_9B7A30);  // 调 格式化串取目录前缀
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  v17 = 0;
  v10 = nullptr;  // v10 = nullptr 空指针
  sub_41BFE0(&v10, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  LOBYTE(v17) = 1;  // 调 取 16 位值低 8 位
  v11 = 0;
  if ( (uint8_t)sub_443430(v12) == 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    goto LABEL_45;  // 跳转 LABEL_45
  do
  {
    sub_442B20(v12);  // sub_442B20 —— 国家码标签配对校验（void）
    v4 = v14;
    if ( v14 != 0 )
    {
      v5 = v14;
      if ( v14 >= 6 )
        v5 = 6;
      p_Block = (const char *)Block;
      if ( v15 < 0x10 )
        p_Block = (const char *)&Block;
      nCmp = memcmp(p_Block, "[name]", v5);  // 调 memcmp 内存比较
      if ( nCmp == 0 && v14 >= 6 )
      {
        LOBYTE(nCmp) = v14 != 6;  // 调 取 16 位值低 8 位
        if ( nCmp == 0 )
        {
LABEL_11:
          sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
          continue;
        }
      }
      v4 = v14;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v4, "[width]", 7u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[floating height]", 0x11u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[layer]", 7u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[recovery time]", 0xFu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[direction correct]", 0x13u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              if ( (uint8_t)sub_423300(v12, "[move speed]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 56) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 60) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 64) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 68) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
                *(uint32_t *)(pArg1 + 72) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v12, "[gravity]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                *(uint32_t *)(pArg1 + 76) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
              }
              else
              {
                if ( (uint8_t)sub_423300(v12, "[basic motion]") != 0 )  // sub_423300 —— [end] → 解析结束
                  goto LABEL_11;  // 跳转 LABEL_11
                if ( (uint8_t)sub_423300(v12, "[etc motion]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_4017E0(pArg1 + 108);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                  while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v10);  // sub_420BB0 —— vector push_back（4 字节元素）
                }
                else if ( (uint8_t)sub_423300(v12, "[attack info]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_4017E0(pArg1 + 124);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                  while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v10);  // sub_420BB0 —— vector push_back（4 字节元素）
                }
                else if ( (uint8_t)sub_423300(v12, "[int data]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_5E5260((void **)(pArg1 + 140));  // 调 sub_5E5260
                  for ( i = sub_4423D0(&v11); v11 != 0; i = sub_4423D0(&v11) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
                    sub_431230(pArg1 + 140, &i);  // sub_431230 —— uint32 vector push_back
                }
                else if ( (uint8_t)sub_423300(v12, "[string data]") != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  sub_4017E0(pArg1 + 156);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                  while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v10);  // sub_420BB0 —— vector push_back（4 字节元素）
                }
              }
            }
            else
            {
              *(uint8_t *)(pArg1 + 52) = sub_4423D0(nullptr) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
            }
          }
          else
          {
            *(uint32_t *)(pArg1 + 48) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          }
        }
        else
        {
          sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
          v8 = sub_41ACF0(&v10);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
          *(uint32_t *)(pArg1 + 44) = sub_4425F0(v8);  // sub_4425F0 —— 场景前景/背景档位标签→索引
        }
      }
      else
      {
        *(uint32_t *)(pArg1 + 40) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      }
    }
    else
    {
      *(uint32_t *)(pArg1 + 32) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      *(uint32_t *)(pArg1 + 36) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
    }
  }
  while ( (uint8_t)sub_443430(v12) != 0 );  // sub_443430 —— 读 token 到 string + 国家码标记
  nArg22 = nArg2;
LABEL_45:
  *(uint32_t *)pArg1 = sub_4A2F80(nArg22);  // 调 +0x00 ← 按文件名查全局 ID 表（未登记 = -1）
  LOBYTE(v17) = 0;  // 调 取 16 位值低 8 位
  sub_41B010(&v10);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  if ( v15 >= 0x10 )
    j__free(Block);  // 释放堆块
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
char /*cdecl*/ sub_50B840(int pArg1, int nArg2)  // sub_50B840 —— 技能 PassiveObject / 觉醒(overskill)定义解析器
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
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B7B30, nArg2);  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result == 0 )
    return result;
  sub_4CF290((char *)pArg1);  // 调 sub_4CF290
  sub_443300(pArg1 + 332, "%s%s", (char)&unk_9B7B30);  // 调 格式化串取目录前缀
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  v17 = 0;
  v10 = nullptr;  // v10 = nullptr 空指针
  sub_41BFE0((void **)&v10, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  LOBYTE(v17) = 1;  // 调 取 16 位值低 8 位
  v11 = 0;
  if ( (uint8_t)sub_443430(v12) == 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    goto LABEL_63;  // 跳转 LABEL_63
  do
  {
    sub_442B20(v12);  // sub_442B20 —— 国家码标签配对校验（void）
    v4 = v14;
    if ( v14 != 0 )
    {
      v5 = v14;
      if ( v14 >= 6 )
        v5 = 6;
      p_Block = (const char *)Block;
      if ( v15 < 0x10 )
        p_Block = (const char *)&Block;
      nCmp = memcmp(p_Block, "[name]", v5);  // 调 memcmp 内存比较
      if ( nCmp == 0 && v14 >= 6 )
      {
        LOBYTE(nCmp) = v14 != 6;  // 调 取 16 位值低 8 位
        if ( nCmp == 0 )
          goto LABEL_45;  // 跳转 LABEL_45
      }
      v4 = v14;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v4, "[width]", 7u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      *(uint32_t *)(pArg1 + 32) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      *(uint32_t *)(pArg1 + 36) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[floating height]", 0x11u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      *(uint32_t *)(pArg1 + 40) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[layer]", 7u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      v8 = sub_41ACF0(&v10);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      *(uint32_t *)(pArg1 + 44) = sub_4425F0(v8);  // sub_4425F0 —— 场景前景/背景档位标签→索引
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[skill recovery time]", 0x15u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      *(uint32_t *)(pArg1 + 48) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( sub_40BF00((std::_String_base *)v12, 0, v14, "[over skill recovery time]", 0x1Au) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      *(uint32_t *)(pArg1 + 52) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[direction correct]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint8_t *)(pArg1 + 56) = sub_4423D0(nullptr) != 0;  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[move speed]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint32_t *)(pArg1 + 60) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      *(uint32_t *)(pArg1 + 64) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      *(uint32_t *)(pArg1 + 68) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      *(uint32_t *)(pArg1 + 72) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      *(uint32_t *)(pArg1 + 76) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[gravity]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint32_t *)(pArg1 + 80) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[start level]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint32_t *)(pArg1 + 84) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[permission level]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint32_t *)(pArg1 + 88) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[artifact slot]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint32_t *)(pArg1 + 92) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[learn overskill level]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      *(uint32_t *)(pArg1 + 96) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[basic motion]") != 0  // sub_423300 —— [end] → 解析结束
      || (uint8_t)sub_423300(v12, "[walk motion]") != 0  // sub_423300 —— [end] → 解析结束
      || (uint8_t)sub_423300(v12, "[run motion]") != 0  // sub_423300 —— [end] → 解析结束
      || (uint8_t)sub_423300(v12, "[skill motion]") != 0  // sub_423300 —— [end] → 解析结束
      || (uint8_t)sub_423300(v12, "[over skill motion]") != 0  // sub_423300 —— [end] → 解析结束
      || (uint8_t)sub_423300(v12, "[response motion]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
LABEL_45:
      sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
      continue;
    }
    if ( (uint8_t)sub_423300(v12, "[etc motion]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_4017E0(pArg1 + 268);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
      while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v10);  // sub_420BB0 —— vector push_back（4 字节元素）
    }
    else if ( (uint8_t)sub_423300(v12, "[attack info]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_4017E0(pArg1 + 284);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
      while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v10);  // sub_420BB0 —— vector push_back（4 字节元素）
    }
    else if ( (uint8_t)sub_423300(v12, "[int data]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_5E5260((void **)(pArg1 + 300));  // 调 sub_5E5260
      for ( i = sub_4423D0(&v11); v11 != 0; i = sub_4423D0(&v11) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
        sub_431230(pArg1 + 300, &i);  // sub_431230 —— uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(v12, "[string data]") != 0 )  // sub_423300 —— [end] → 解析结束
    {
      sub_4017E0(pArg1 + 316);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
      while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
        sub_420BB0(&v10);  // sub_420BB0 —— vector push_back（4 字节元素）
    }
  }
  while ( (uint8_t)sub_443430(v12) != 0 );  // sub_443430 —— 读 token 到 string + 国家码标记
  v2 = (const char *)nArg2;
LABEL_63:
  *(uint32_t *)pArg1 = sub_4A2F80(dword_9B7C54, v2);  // 调 +0x00 ← 按文件名查全局 ID 表（未登记 = -1）
  LOBYTE(v17) = 0;  // 调 取 16 位值低 8 位
  sub_41B010((void **)&v10);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  if ( v15 >= 0x10 )
    j__free(Block);  // 释放堆块
  return 1;
}


// ------------------------------------------------------------
// 0x50BE20 sub_50BE20
//   std::_Fill_n（16 字节内层 vector<44B> 元素版）：转调 sub_509C00 后返回尾地址。
// ------------------------------------------------------------
char **/*stdcall*/ sub_50BE20(char **pszArg1, int nArg2, int nArg3)  // 技能 PassiveObject / 觉醒(overskill)定义解析器
{
  sub_509C00(pszArg1, nArg2, nArg3);  // 调 sub_509C00
  return &pszArg1[4 * nArg2];
}



// ------------------------------------------------------------
// 0x50BE50 sub_50BE50
//   std::vector<vector<44B>>::erase(first, last)（16 字节内层元素）：
//   把 [nArg4, end) 前移（sub_5097A0 赋值）后收缩 end（sub_42CC00 析构余量）。
// ------------------------------------------------------------
int */*thiscall*/ sub_50BE50(int *this, int *pDwArg2, int nArg3, int nArg4)
{
  int fld_e2; // edi

  if ( nArg3 != nArg4 )
  {
    fld_e2 = sub_5097A0(nArg4, *(this + 2), nArg3);  // 调 sub_5097A0
    sub_42CC00(fld_e2, *(this + 2));  // sub_42CC00 —— 16 字节槽组释放
    *(this + 2) = fld_e2;  // 写字段 this+2 ← fld_e2
  }
  *pDwArg2 = nArg3;  // *pDwArg2 写入 nArg3
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x50BEA0 sub_50BEA0
//   std::vector<vector<44字节>>::insert(pos, n, val)（16 字节内层元素）：
//   先把模板 nArg4 复制到栈上临时（sub_509580），容量够 → 尾部腾位
//   （5099F0/5099D0/50BE20/5099A0）；不足 → 扩容三段拷贝重建。
// ------------------------------------------------------------
void /*thiscall*/ sub_50BEA0(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 函数: 释放后返回
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
  sub_509580(&v26, nArg4);  // 调 sub_509580
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  fld_e2 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - fld_e1) >> 4;  // this+12 = 技能槽记录次字
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) >> 4;  // this+8 = 技能槽记录首字
    if ( 0xFFFFFFF - fld_e2 < uArg3 )
      sub_508F60(this);  // 调 sub_508F60
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) >> 4;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
      Block = fld_e23;
      if ( ((int)fld_e23 - pArg2) >> 4 >= uArg3 )
      {
        v19 = (int)&fld_e23[-4 * uArg3];
        v20 = sub_5099F0(v19, (int)fld_e23, fld_e23);  // 调 sub_5099F0
        Block2 = Block;
        *(this + 2) = (int)v20;  // 写字段 this+2 ← (int)v20
        sub_5099D0(pArg2, v19, Block2);  // 调 sub_5099D0
        sub_5099A0(pArg2, pArg2 + 16 * uArg3, &v26);  // 调 sub_5099A0
      }
      else
      {
        sub_5099F0(pArg2, (int)fld_e23, (uint32_t *)(pArg2 + 16 * uArg3));  // 调 sub_5099F0
        fld_e24 = uArg3 - ((*(this + 2) - pArg2) >> 4);  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        LOBYTE(v31) = 3;  // 调 取 16 位值低 8 位
        sub_50BE20(fld_e25, fld_e24, &v26);  // 调 sub_50BE20
        fld_e26 = 16 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        v31 = 0;
        sub_5099A0(pArg2, fld_e26 - 16 * uArg3, &v26);  // 调 sub_5099A0
      }
    }
    else
    {
      if ( 0xFFFFFFF - (fld_e3 >> 1) >= fld_e3 )  // 若 0xFFFFFFF - (fld_e3 >> 1) >= fld_e3
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) >> 4;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
      {
        if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
          fld_e28 = (*(this + 2) - fld_e1) >> 4;  // this+8 = 技能槽记录首字
        else
          fld_e28 = 0;
        v10 = uArg3 + fld_e28;  // 计算 v10 = uArg3 + fld_e28
      }
      v33 = 16 * v10;  // 计算 v33 = 16 * v10
      pMem = (char *)operator new(16 * v10);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      Block = pMem;
      LOBYTE(v31) = 1;  // 调 取 16 位值低 8 位
      v32 = sub_5099F0(fld_e12, pArg2, pMem);  // 调 sub_5099F0
      sub_509C00(v32, uArg3, (int)&v26);  // 调 sub_509C00
      sub_5099F0(pArg2, *(this + 2), &v32[4 * uArg3]);  // 调 sub_5099F0
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e29 = (*(this + 2) - fld_e13) >> 4;  // this+8 = 技能槽记录首字
      else
        fld_e29 = 0;
      v16 = fld_e29 + uArg3;  // 计算 v16 = fld_e29 + uArg3
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
      {
        sub_42CC00(fld_e13, *(this + 2));  // sub_42CC00 —— 16 字节槽组释放
        j__free((void *)*(this + 1));  // 释放堆块
      }
      *(this + 3) = (int)&pMem[v33];  // 写字段 this+3 ← (int)&pMem[v33]
      *(this + 2) = (int)&pMem[16 * v16];  // 写字段 this+2 ← (int)&pMem[16 * v16]
      *(this + 1) = (int)pMem;  // 写字段 this+1 ← (int)pMem
    }
  }
  if ( v27 != nullptr )
    j__free(v27);  // 释放堆块
}

