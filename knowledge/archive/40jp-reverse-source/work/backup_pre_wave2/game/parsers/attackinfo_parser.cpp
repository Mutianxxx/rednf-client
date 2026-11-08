// ============================================================
// 【40JP逆向源代码工程】parsers/attackinfo_parser.cpp
// 模块: 职业(growtype)数据解析 / 仓储窗口 / 表情系统 / 堆叠物类族 + 脚本后端
// 来源: work/dump_parsers.txt  区块: 0x50C000-0x510000
//       （深度校验用 work/dump_full_0.txt —— [tag] 词汇表按全量版提取）
// 层级: L2 转写层 → L1 精修层（会话 4 精修：标签族头注 + 分区；逻辑未改）
// 函数数: 80
//
// ★ 范围说明：本文件虽名为 attackinfo_parser，但 0x50C000-0x510000 区块实际包含：
//   - 职业(growtype/技能树)数据解析器 sub_50C290（67 标签）—— 全文件唯一大 [tag] 解析器
//   - 仓储窗口 CNRDStorageWindow 族（0x50D4E0-0x50E650）
//   - 表情(emoticon)系统 0x50E7E0-0x50EAA0
//   - 堆叠物族 CNChangeMp/CNActiveStatusStackable/CNCoinOfFortune/CNTouchOfRemy/
//     CNRateHpMp/CNCallStorageBird/CNOmozzaOfWorld/CNUsableStackable
//   ★ attackinfo 字段表解析器本体是 monster_parser.cpp 的 sub_503BA0（研究 20 §1.3）——
//     本文件不含 attackinfo 字段写入；研究 20 §1.3 偏移表已在该函数头注释逐项映射。
//
// ★ 研究 20 相关锚点：
//   - CNTouchOfRemy / CNRateHpMp = 恢复类堆叠物（瞬时/回复率），与 sub_4D6810（CNChangeHp 构造，
//     研究 20 §2 ⑦ 延滞伤同型类）配对；[MP regen speed rate] 乘 0.0099999998 = ×0.01。
//   - sub_50D660 = 时间比较器（|差值|×0.001 秒经 sub_44E8D0 type 0x1B 上屏）。
//
// 分区（按 VA 升序）：
//   §A 0x50C140-0x50C290  仓储容器模板辅助（vector/list 实例化）
//   §B 0x50C290-0x50D260  ★ 职业(growtype)数据解析器 + 技能树加载
//   §C 0x50D260-0x50E7E0  仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取）
//   §D 0x50E7E0-0x50EB40  表情(emoticon)系统（$END 表 + EmoBalloonS.ani）
//   §E 0x50EB40-0x50F1C0  UI 文本气泡与 CNText 族
//   §F 0x50F270-0x50FFD0  堆叠物(stackable)与恢复类物品族（CNChangeMp 等）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// §A 0x50C140-0x50C290 仓储容器模板辅助
// ============================================================

// ------------------------------------------------------------
// 0x50C140 sub_50C140 —— 16 字节元素向量 resize（截尾/追加双路）
//   元素数不足经 ·sub_50BEA0 追加、富余经 ·sub_50BE50 截尾；末对 Block 调 j__free；
//   配套仓储槽位表追加原语 ·0x50C1F0。
// ------------------------------------------------------------
void /*thiscall*/ sub_50C140(int *this, unsigned int uArg2, char pszArg3, void *Block, int nArg5, int nArg6)
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int fld_e22; // edx

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 4;
  else
    fld_e2 = 0;
  if ( fld_e2 >= uArg2 )
  {
    if ( fld_e1 != 0 && uArg2 < (*(this + 2) - fld_e1) >> 4 )
      sub_50BE50(this, (int *)&uArg2, fld_e1 + 16 * uArg2, *(this + 2));
  }
  else
  {
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) >> 4;
    else
      fld_e22 = 0;
    sub_50BEA0((int)this, *(this + 2), uArg2 - fld_e22, (int)&pszArg3);
  }
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x50C1F0 sub_50C1F0 —— 16 字节元素向量尾部追加（满则扩容）
//   有富余 → ·sub_4C2BA0 就地按 nArg2 复制构造并 +16 递增；否则 ·sub_4C3DC0 扩容追加。
// ------------------------------------------------------------
int /*thiscall*/ sub_50C1F0(uint32_t *this, int nArg2)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  int result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 4;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 4 )
    return sub_4C3DC0(*(this + 2), 1, nArg2);
  fld_e22 = *(this + 2);
  result = sub_4C2BA0(fld_e22, 1, nArg2);
  *(this + 2) = fld_e22 + 16;
  return result;
}



// ------------------------------------------------------------
// 0x50C260 sub_50C260 —— 16 字节元素向量 resize 缺省值封装
//   栈临时默认值经 ·sub_50C140（Block=null）转发。
// ------------------------------------------------------------
void /*thiscall*/ sub_50C260(int *this, unsigned int uArg2)
{
  char v2; // [esp+0h] [ebp-14h] BYREF
  char *v3; // [esp+10h] [ebp-4h]

  v3 = &v2;
  sub_50C140(this, uArg2, v2, nullptr, 0, 0);
}



// ============================================================
// §B 0x50C290-0x50D260 ★ 职业(growtype)数据解析器 + 技能树加载
// ============================================================

// ------------------------------------------------------------
// 0x50C290 sub_50C290 —— ★★ 职业(growtype/角色成长)定义解析器（67 标签，本文件唯一大 [tag] 解析器）
//   a1 = 职业数据对象（sub_4D2D60 对象工厂 switch(this+72) **case 0**：operator new(0x684) +
//   sub_4D2320 构造 → 本函数；失败路径 sub_4D26E0 释放），a2 = 文件路径。
//   加载入口：先 sub_442A10 检查文件 → sub_4D1EA0 复位 → sub_443300 记录路径（a1+1640）。
//
//   标签族（67 个，按类）：
//   职业框架 [job]（查表 sub_4426A0 → *a1 职业码）/[growtype name]/[width]/[jump speed]（a1+820）/
//   [initial value]/[growtype 1..5]（五转分支，基址 a1+152/231/310/389/468，每组 79 字节；
//   配套指针 a1+628/644/660/676/692 与 a1+724/740/756/772/788）
//   基础属性 [HP MAX]/[MP MAX]/[physical attack]/[physical defense]/[magical attack]/
//   [magical defense]（×10 缩放后 sub_432F40 写入半字 a1+8..+22）/[fire/water/dark/light resistance]
//   [inventory limit]/[HP regen speed]/[MP regen speed]/[move speed]/[attack speed]/[cast speed]/
//   [hit recovery]/[jump power]/[weight]（走 sub_4F6790 属性解析器 —— 与装备/怪物共表）
//   技能 [skill]（技能表 a1+24 起 + a1+16 计数）/ [category]
//   动作表（同 sub_4F7C60 装备表，全 23 项）[waiting motion]/[move motion]/[sit motion]/
//   [damage motion 1-2]/[down motion]/[overturn motion]/[jump motion]/[jumpattack motion]/
//   [rest motion]/[throw motion 1-1..4-2]（8）/[dash motion]/[dashattack motion]/[getitem motion]/
//   [buff motion]/[attack motion]/[etc motion]
//   攻击数据引用 [jumpattack info]/[dashattack info]/[attack info]/[etc attack info]
//   音效与命中 [weapon wav]（经 sub_50C1F0 写入字符串表）/[weapon hit info]（4 类子枚举
//   [blow]/[cut]/[burn]/[etc] + [no blood]/[blood] + 整型 + 浮点，写 a1+1576/1592/1608/1624 四表）
//   ★ 与 研究 20 §1.3 的 attackinfo 字段表同源：[hit info] 四值枚举（[blow]=0/[cut]=1/[burn]=2/
//     [etc]=3）与 [no blood]/[blood] 刃钝标志在职业武器的 "weapon hit info" 表中重复出现
//     （同一枚举在三处解析器共用：sub_503BA0 / sub_50C290 / 装备武器区）。
// ------------------------------------------------------------
char /*cdecl*/ sub_50C290(int pArg1, int nArg2)
{
  char result; // al
  int v3; // esi
  int v4; // eax
  int v5; // esi
  int k; // ebx
  int i; // esi
  int v8; // eax
  void *v9; // ebx
  float v10; // esi
  void **v11; // ebx
  void **j; // esi
  char **off_791FD82; // esi
  uint16_t *v14; // ebx
  float v15; // [esp+0h] [ebp-6Ch]
  float v16; // [esp+0h] [ebp-6Ch]
  float v17; // [esp+0h] [ebp-6Ch]
  float v18; // [esp+0h] [ebp-6Ch]
  float v19; // [esp+0h] [ebp-6Ch]
  float v20; // [esp+0h] [ebp-6Ch]
  float v21; // [esp+0h] [ebp-6Ch]
  float v22; // [esp+0h] [ebp-6Ch]
  float v23; // [esp+0h] [ebp-6Ch]
  float v24; // [esp+0h] [ebp-6Ch]
  float v25; // [esp+0h] [ebp-6Ch]
  float v26; // [esp+0h] [ebp-6Ch]
  float v27; // [esp+0h] [ebp-6Ch]
  float v28; // [esp+0h] [ebp-6Ch]
  float v29; // [esp+0h] [ebp-6Ch]
  float v30; // [esp+0h] [ebp-6Ch]
  float v31; // [esp+0h] [ebp-6Ch]
  float v32; // [esp+0h] [ebp-6Ch]
  float v33; // [esp+0h] [ebp-6Ch]
  float v34; // [esp+0h] [ebp-6Ch]
  uint32_t v35[2]; // [esp+10h] [ebp-5Ch] BYREF
  char v36[4]; // [esp+18h] [ebp-54h] BYREF
  void **v37; // [esp+1Ch] [ebp-50h]
  void **v38; // [esp+20h] [ebp-4Ch]
  int v39; // [esp+24h] [ebp-48h]
  void *v40; // [esp+28h] [ebp-44h]
  void *v41; // [esp+2Ch] [ebp-40h]
  int v42; // [esp+30h] [ebp-3Ch]
  int v43; // [esp+34h] [ebp-38h] BYREF
  char v44; // [esp+3Bh] [ebp-31h] BYREF
  void *v45; // [esp+3Ch] [ebp-30h] BYREF
  char v46[4]; // [esp+40h] [ebp-2Ch] BYREF
  void *Block; // [esp+44h] [ebp-28h]
  unsigned int v48; // [esp+54h] [ebp-18h]
  unsigned int v49; // [esp+58h] [ebp-14h]
  int dword_796E502; // [esp+5Ch] [ebp-10h]
  int v51; // [esp+68h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)&unk_9B7730, nArg2);
  if ( result == 0 )
    return result;
  sub_4D1EA0(pArg1);
  sub_443300(pArg1 + 1640, "%s%s", (char)&unk_9B7730);
  v49 = 15;
  v48 = 0;
  LOBYTE(Block) = 0;
  v51 = 0;
  v45 = nullptr;
  sub_41BFE0(&v45, szPassword);
  v40 = (void *)(pArg1 + 628);
  v3 = pArg1 + 152;
  LOBYTE(v51) = 1;
  v44 = 0;
  v42 = pArg1 + 152;
  v41 = (void *)(pArg1 + 724);
  if ( (uint8_t)sub_443430(v46) != 0 )
  {
    while ( 1 )
    {
      sub_442B20(v46);
      if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[job]", 5u) == 0 )
      {
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        v4 = sub_41ACF0(&v45);
        *(uint32_t *)pArg1 = sub_4426A0(v4);
        goto LABEL_161;
      }
      if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[growtype name]", 0xFu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[width]", 7u) == 0 )
        {
          *(uint32_t *)(pArg1 + 144) = sub_4423D0(nullptr);
          *(uint32_t *)(pArg1 + 148) = sub_4423D0(nullptr);
          goto LABEL_161;
        }
        if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[jump speed]", 0xCu) == 0 )
        {
          *(uint32_t *)(pArg1 + 820) = sub_4423D0(nullptr);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[initial value]") != 0 )
        {
          v42 = pArg1 + 152;
          v40 = (void *)(pArg1 + 628);
          v41 = (void *)(pArg1 + 724);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 1]") != 0 )
        {
          v42 = pArg1 + 231;
          v40 = (void *)(pArg1 + 644);
          v41 = (void *)(pArg1 + 740);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 2]") != 0 )
        {
          v42 = pArg1 + 310;
          v40 = (void *)(pArg1 + 660);
          v41 = (void *)(pArg1 + 756);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 3]") != 0 )
        {
          v42 = pArg1 + 389;
          v40 = (void *)(pArg1 + 676);
          v41 = (void *)(pArg1 + 772);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 4]") != 0 )
        {
          v42 = pArg1 + 468;
          v40 = (void *)(pArg1 + 692);
          v41 = (void *)(pArg1 + 788);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 5]") != 0 )
        {
          v42 = pArg1 + 547;
          v40 = (void *)(pArg1 + 708);
          v41 = (void *)(pArg1 + 804);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[HP MAX]") != 0 )
        {
          v15 = sub_442480(nullptr) * 10.0;
          *(uint32_t *)v3 = sub_432F40(v15);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[MP MAX]") != 0 )
        {
          v16 = sub_442480(nullptr) * 10.0;
          *(uint32_t *)(v3 + 4) = sub_432F40(v16);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[physical attack]") != 0 )
        {
          v17 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 8) = sub_432F40(v17);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[physical defense]") != 0 )
        {
          v18 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 10) = sub_432F40(v18);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[magical attack]") != 0 )
        {
          v19 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 12) = sub_432F40(v19);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[magical defense]") != 0 )
        {
          v20 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 14) = sub_432F40(v20);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[fire resistance]") != 0 )
        {
          v21 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 16) = sub_432F40(v21);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[water resistance]") != 0 )
        {
          v22 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 18) = sub_432F40(v22);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[dark resistance]") != 0 )
        {
          v23 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 20) = sub_432F40(v23);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[light resistance]") != 0 )
        {
          v24 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 22) = sub_432F40(v24);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[inventory limit]") != 0 )
        {
          v25 = sub_442480(nullptr) * 10.0;
          *(uint32_t *)(v3 + 56) = sub_432F40(v25);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[HP regen speed]") != 0 )
        {
          v26 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 60) = sub_432F40(v26);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[MP regen speed]") != 0 )
        {
          v27 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 62) = sub_432F40(v27);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[move speed]") != 0 )
        {
          v28 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 64) = sub_432F40(v28);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[attack speed]") != 0 )
        {
          v29 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 66) = sub_432F40(v29);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[cast speed]") != 0 )
        {
          v30 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 68) = sub_432F40(v30);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[hit recovery]") != 0 )
        {
          v31 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 70) = sub_432F40(v31);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[jump power]") != 0 )
        {
          v32 = sub_442480(nullptr) * 10.0;
          *(uint16_t *)(v3 + 72) = sub_432F40(v32);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[weight]") != 0 )
        {
          v33 = sub_442480(nullptr) * 10.0;
          *(uint32_t *)(v3 + 74) = sub_432F40(v33);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[skill]") != 0 )
        {
          sub_5E5260((void **)v40);
          for ( i = sub_4423D0(&v44); v44 != 0; i = sub_4423D0(&v44) )
          {
            v8 = sub_4423D0(nullptr);
            v35[0] = i;
            v35[1] = v8;
            sub_474950(v35);
          }
        }
        else if ( (uint8_t)sub_423300(v46, "[category]") != 0 )
        {
          sub_5E5260((void **)v41);
          if ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
          {
            v9 = v41;
            do
            {
              v10 = 0.0;
              *(float *)&v43 = 0.0;
              while ( !sub_43BCF0(&v45, off_791F80[LODWORD(v10)]) )
              {
                ++LODWORD(v10);
                if ( SLODWORD(v10) >= 22 )
                {
                  *(float *)&v43 = v10;
                  goto LABEL_77;
                }
              }
              *(float *)&v43 = v10;
              sub_431230((int)v9, &v43);
LABEL_77:
              ;
            }
            while ( sub_442E10() != 0 );  // 【RDARScriptStringManager 入口（::ERROR::input…】
          }
        }
        else
        {
          if ( (uint8_t)sub_423300(v46, "[waiting motion]") != 0
            || (uint8_t)sub_423300(v46, "[move motion]") != 0
            || (uint8_t)sub_423300(v46, "[sit motion]") != 0
            || (uint8_t)sub_423300(v46, "[damage motion 1]") != 0
            || (uint8_t)sub_423300(v46, "[damage motion 2]") != 0
            || (uint8_t)sub_423300(v46, "[down motion]") != 0
            || (uint8_t)sub_423300(v46, "[overturn motion]") != 0
            || (uint8_t)sub_423300(v46, "[jump motion]") != 0
            || (uint8_t)sub_423300(v46, "[jumpattack motion]") != 0
            || (uint8_t)sub_423300(v46, "[rest motion]") != 0
            || (uint8_t)sub_423300(v46, "[throw motion 1-1]") != 0
            || (uint8_t)sub_423300(v46, "[throw motion 1-2]") != 0
            || (uint8_t)sub_423300(v46, "[throw motion 2-1]") != 0
            || (uint8_t)sub_423300(v46, "[throw motion 2-2]") != 0
            || (uint8_t)sub_423300(v46, "[throw motion 3-1]") != 0
            || (uint8_t)sub_423300(v46, "[throw motion 3-2]") != 0
            || (uint8_t)sub_423300(v46, "[throw motion 4-1]") != 0
            || (uint8_t)sub_423300(v46, "[throw motion 4-2]") != 0
            || (uint8_t)sub_423300(v46, "[dash motion]") != 0
            || (uint8_t)sub_423300(v46, "[dashattack motion]") != 0
            || (uint8_t)sub_423300(v46, "[getitem motion]") != 0
            || (uint8_t)sub_423300(v46, "[buff motion]") != 0 )
          {
LABEL_122:
            sub_443370();
            goto LABEL_161;
          }
          if ( (uint8_t)sub_423300(v46, "[attack motion]") != 0 )
          {
            sub_4017E0(pArg1 + 1440);
            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              sub_420BB0(&v45);
          }
          else if ( (uint8_t)sub_423300(v46, "[etc motion]") != 0 )
          {
            sub_4017E0(pArg1 + 1456);
            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              sub_420BB0(&v45);
          }
          else
          {
            if ( (uint8_t)sub_423300(v46, "[jumpattack info]") != 0
              || (uint8_t)sub_423300(v46, "[dashattack info]") != 0 )
            {
              goto LABEL_122;
            }
            if ( (uint8_t)sub_423300(v46, "[attack info]") != 0 )
            {
              sub_4017E0(pArg1 + 1528);
              while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                sub_420BB0(&v45);
            }
            else if ( (uint8_t)sub_423300(v46, "[etc attack info]") != 0 )
            {
              sub_4017E0(pArg1 + 1544);
              while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                sub_420BB0(&v45);
            }
            else if ( (uint8_t)sub_423300(v46, "[weapon wav]") != 0 )
            {
              v11 = nullptr;
              v37 = nullptr;
              v38 = nullptr;
              v39 = 0;
              LOBYTE(v51) = 2;
              if ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              {
                do
                  sub_420BB0(&v45);
                while ( sub_442E10() != 0 );  // 【RDARScriptStringManager 入口（::ERROR::input…】
                v11 = v37;
              }
              sub_50C1F0(v36);
              LOBYTE(v51) = 1;
              if ( v11 != nullptr )
              {
                for ( j = v11; j != v38; ++j )
                  sub_41B010(j);
                j__free(v11);
              }
              v37 = nullptr;
              v38 = nullptr;
              v39 = 0;
            }
            else
            {
              if ( (uint8_t)sub_423300(v46, "[weapon hit info]") != 0 )
              {
                sub_5E5260((void **)(pArg1 + 1576));
                sub_5E5260((void **)(pArg1 + 1592));
                sub_5E5260((void **)(pArg1 + 1608));
                sub_5E5260((void **)(pArg1 + 1624));
                if ( sub_442E10() == 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                  goto LABEL_161;
                while ( 2 )
                {
                  if ( sub_43BCF0(&v45, "[blow]") )
                  {
                    *(float *)&v43 = 0.0;
                    goto LABEL_150;
                  }
                  if ( sub_43BCF0(&v45, "[cut]") )
                  {
                    v43 = 1;
                    sub_431230(pArg1 + 1576, &v43);
                  }
                  else if ( sub_43BCF0(&v45, "[burn]") )
                  {
                    v43 = 2;
                    sub_431230(pArg1 + 1576, &v43);
                  }
                  else if ( sub_43BCF0(&v45, "[etc]") )
                  {
                    v43 = 3;
LABEL_150:
                    sub_431230(pArg1 + 1576, &v43);
                  }
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                  if ( sub_43BCF0(&v45, "[no blood]") )
                  {
                    *(float *)&v43 = 0.0;
                    sub_431230(pArg1 + 1592, &v43);
                  }
                  else if ( sub_43BCF0(&v45, "[blood]") )
                  {
                    v43 = 1;
                    sub_431230(pArg1 + 1592, &v43);
                  }
                  *(float *)&v43 = COERCE_FLOAT(sub_4423D0(nullptr));
                  sub_431230(pArg1 + 1608, &v43);
                  *(float *)&v43 = sub_442480(nullptr);
                  sub_5020D0(&v43);
                  if ( sub_442E10() == 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    goto LABEL_161;
                  continue;
                }
              }
              off_791FD82 = off_791FD8;
              v14 = (uint16_t *)(v42 + 24);
              do
              {
                if ( (uint8_t)sub_423300(v46, *off_791FD82) != 0 )
                {
                  v34 = sub_442480(nullptr) * 10.0;
                  *v14 = sub_432F40(v34);
                }
                ++off_791FD82;
                ++v14;
              }
              while ( (int)off_791FD82 < (int)off_792018 );
            }
          }
        }
      }
      else
      {
        v5 = pArg1 + 4;
        for ( k = 5; k != 0; --k )
        {
          sub_443370();
          v5 += 28;
        }
      }
LABEL_161:
      if ( (uint8_t)sub_443430(v46) == 0 )
        break;
      v3 = v42;
    }
  }
  LOBYTE(v51) = 0;
  sub_41B010(&v45);
  if ( v49 >= 0x10 )
    j__free(Block);
  return 1;
}


// ============================================================
// §C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取）
// ============================================================

// ------------------------------------------------------------
// 0x50D260 sub_50D260 —— 仓储物品表加载器（[item] 表：每行 44 字节 = 11 个描述符；
//   按索引追加 sub_509B70 / 越界补齐 sub_509890）
// ------------------------------------------------------------
char /*cdecl*/ sub_50D260(char *pszArg1, int nArg2)
{
  char *pszArg12; // eax
  int v3; // edx
  char v4; // cl
  int *v5; // ebx
  unsigned int v6; // edi
  int v7; // eax
  int v8; // eax
  char *v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  unsigned int v13; // eax
  int pBuf[11]; // [esp+Ch] [ebp-68h] BYREF
  uint32_t Block[11]; // [esp+38h] [ebp-3Ch] BYREF
  char **off_7920182; // [esp+64h] [ebp-10h]
  int v18; // [esp+68h] [ebp-Ch]
  unsigned int v19; // [esp+6Ch] [ebp-8h]
  int v20; // [esp+70h] [ebp-4h]

  pszArg12 = pszArg1;
  v3 = byte_9B7830 - pszArg1;
  do
  {
    v4 = *pszArg12;
    pszArg12[v3] = *pszArg12;
    ++pszArg12;
  }
  while ( v4 != 0 );
  if ( byte_9B782F[strlen(byte_9B7830)] != 92 && byte_9B782F[strlen(byte_9B7830)] != 47 )
    *(uint16_t *)&byte_9B7830[strlen(byte_9B7830)] = 92;
  if ( (uint8_t)sub_443C40((int)&unk_9B7C30, (char)byte_9B7830, nArg2) != 0 )
  {
    sub_50C260(3);
    v5 = (int *)off_792018;
    v20 = 0;
    off_7920182 = off_792018;
    while ( (uint8_t)sub_442A10((char)byte_9B7830, *v5) != 0 )
    {
      v6 = 0;
      HIBYTE(pszArg1) = 0;
      memset(Block, 0, sizeof(Block));
      v19 = 0;
      v7 = sub_4423D0((uint8_t *)&pszArg1 + 3);
      if ( HIBYTE(pszArg1) != 0 )
      {
        v18 = 0;
        do
        {
          Block[0] = v7;
          Block[3] = sub_4423D0(nullptr);
          Block[4] = sub_4423D0(nullptr);
          Block[5] = sub_4423D0(nullptr);
          Block[6] = sub_4423D0(nullptr);
          Block[1] = sub_4423D0(nullptr);
          Block[2] = sub_4423D0(nullptr);
          Block[7] = sub_4423D0(nullptr);
          Block[8] = sub_4423D0(nullptr);
          Block[9] = sub_4423D0(nullptr);
          v8 = sub_4423D0(nullptr);
          v9 = (char *)dword_9B7C64 + v20;
          Block[10] = v8;
          v10 = *(uint32_t *)((char *)dword_9B7C64 + v20 + 4);
          if ( v10 != 0 )
            v11 = (*((uint32_t *)v9 + 2) - v10) / 44;
          else
            v11 = 0;
          if ( v6 == v11 )
          {
            sub_509B70(Block);
          }
          else
          {
            v12 = *((uint32_t *)v9 + 1);
            if ( v12 != 0 )
              v13 = (*((uint32_t *)v9 + 2) - v12) / 44;
            else
              v13 = 0;
            if ( v6 > v13 )
            {
              memset(pBuf, 0, sizeof(pBuf));
              sub_509890(
                v19 + 1,
                pBuf[0],
                pBuf[1],
                pBuf[2],
                pBuf[3],
                pBuf[4],
                pBuf[5],
                pBuf[6],
                pBuf[7],
                pBuf[8],
                pBuf[9],
                pBuf[10]);
            }
            qmemcpy((void *)(v18 + *(uint32_t *)((char *)dword_9B7C64 + v20 + 4)), Block, 44);
            v6 = v19;
          }
          v19 = ++v6;
          v18 += 44;
          v7 = sub_4423D0((uint8_t *)&pszArg1 + 3);
        }
        while ( HIBYTE(pszArg1) != 0 );
        v5 = (int *)off_7920182;
      }
      off_7920182 = (char **)++v5;
      v20 += 16;
      if ( (int)v5 >= (int)&dword_792024 )
        return 1;
    }
  }
  return 0;
}


// ------------------------------------------------------------
// 0x50D4E0 sub_50D4E0 —— IRDPopupWindow 析构核心（基类清理 5542F0）
//   挂回 vftbl_IRDPopupWindow 后转 ·sub_5542F0；配 ·0x50D4F0 带释放标志的 vmt4 变体。
// ------------------------------------------------------------
int /*thiscall*/ sub_50D4E0(uint32_t *this)
{
  *this = &vftbl_IRDPopupWindow;
  return sub_5542F0();
}



// ------------------------------------------------------------
// 0x50D4F0 IRDPopupWindow__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50D4E0 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
uint32_t */*thiscall*/ IRDPopupWindow__vmt4(uint32_t *Block, char pszArg2)
{
  *Block = &vftbl_IRDPopupWindow;
  sub_5542F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50D520 sub_50D520 —— 双串槽析构（+14 与 +0）
//   两处串槽经 ·sub_41A580 释放（+14 先于 +0）。
// ------------------------------------------------------------
void /*thiscall*/ sub_50D520(char *this)
{
  sub_41A580(this + 14);
  sub_41A580(this);
}



// ------------------------------------------------------------
// 0x50D570 sub_50D570 —— 仓储窗口按钮组释放与槽位游标复位
//   this+44 起 2 个 132 字节按钮经 vt+8 析构、eh 数组（flag 3）随后回收，this+36 数组 free；
//   清零 +36..+52（游标 +48 → -1）；全局窗口态 dword_9B7C8C 为 0 时置 5 并清 dword_9B7C80/84。
// ------------------------------------------------------------
int /*thiscall*/ sub_50D570(uint32_t *this)
{
  int i; // esi
  void (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  void *fld_e9; // eax
  int result; // eax

  for ( i = 0; i < 264; i += 132 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)(*(this + 11) + i) + 8))(*(this + 11) + i);
  fld_e11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( fld_e11 != nullptr )
  {
    if ( *(fld_e11 - 1) != nullptr )
      (**fld_e11)(fld_e11, 3);
    else
      j_j__free(fld_e11 - 1);
  }
  fld_e9 = (void *)*(this + 9);
  *(this + 11) = 0;
  if ( fld_e9 != nullptr )
    j_j__free(fld_e9);
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 13) = 0;
  *(this + 12) = -1;
  result = dword_9B7C8C;
  if ( dword_9B7C8C == 0 )
  {
    dword_9B7C80 = 0;
    dword_9B7C84 = 0;
    dword_9B7C8C = 5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x50D610 CNRDStorageWindow__vmt10 —— 仓储窗口关闭（SAFE_CLOSE 音效）
//   游戏态 dword_795378==6 且 dword_9B88D0 非零时经 ·sub_44E850 回收 26 号池活动对象；
//   dword_9B7C88 非零时 ·sub_601D40 状态装配并清位；末播 SAFE_CLOSE 音效（·sub_432EA0）。
// ------------------------------------------------------------
void */*thiscall*/ CNRDStorageWindow__vmt10(uint32_t **this)
{
  if ( dword_9B88D0 != 0 && dword_795378 == 6 )
    sub_44E850(*(this + 4), 26);
  if ( dword_9B7C88 != 0 )
  {
    sub_601D40();
    dword_9B7C88 = 0;
  }
  return sub_432EA0("SAFE_CLOSE", -1, 0, 0);
}



// ------------------------------------------------------------
// 0x50D660 sub_50D660 —— 冷却时间比较器（剩余毫秒 ×0.001 秒上屏）
//   v3 = 目标时刻 − dword_8F8530 时间基 − nArg1；v3<0 且 pszArg2 非零时取 1164 号文案 sprintf 后经
//   ·sub_44E8D0 type 0x1B 上屏（|v3|×0.001 秒）；返回 v3<0。
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_50D660(int nArg1, char pszArg2)
{
  int v2; // eax
  int v3; // esi
  const char *v4; // eax
  char Buffer[1024]; // [esp+Ch] [ebp-404h] BYREF
  int dword_796E502; // [esp+40Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  v2 = sub_41A5E0((unsigned int)&unk_9B7D10);
  v3 = sub_41A5E0((unsigned int)&dword_9B7C9E[8 * v2]) - *((uint32_t *)dword_8F8530 + 1) - nArg1;
  if ( v3 < 0 && pszArg2 != 0 )
  {
    v4 = (const char *)sub_422E70(1164);
    sprintf(Buffer, v4, (double)(int)abs32(v3) * 0.001);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);
  }
  return v3 < 0;
}



// ------------------------------------------------------------
// 0x50D710 sub_50D710 —— 仓储窗口 process_move 落点判定与移动分派
//   move 2：·sub_486820 拒绝提示；3/4：槽内对象校验（vt+20/+132）→ 等级 6 提示 1165、堆叠 >1 走
//   ·sub_540DE0 摊位流程、冷却经 ·sub_50D660 后 ·sub_4866D0 请求 op 19；8：·sub_486530 双槽交换；
//   未知码 → 抛 CNRDStorageWindow::process_move() - Unsupported move 文案。
// ------------------------------------------------------------
int /*thiscall*/ sub_50D710(int *this, int *pDwArg2)
{
  int result; // eax
  int pObj; // esi
  uint32_t *v5; // eax
  int v6; // edi
  int v7; // ecx
  int pObj2; // esi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  void *dword_8F85302; // [esp-8h] [ebp-14h]
  int fld_e12; // [esp-4h] [ebp-10h]

  result = *pDwArg2;
  if ( *pDwArg2 == 2 )
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, pDwArg2[2]);
    pObj = result;
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 16))(result);
      if ( *(uint32_t *)(result + 4) == pDwArg2[1] )
      {
        v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);
        return sub_486820(*(this + 12), *v5, 1);
      }
    }
  }
  else
  {
    switch ( result )
    {
      case 3:
      case 4:
        result = pDwArg2[2];
        if ( result < *((uint32_t *)dword_8F852C + 2) )
        {
          v7 = *((uint32_t *)dword_8F852C + 3);
          pObj2 = *(uint32_t *)(v7 + 4 * result);
          if ( pObj2 != 0 )
          {
            result = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj2 + 16))(*(uint32_t *)(v7 + 4 * result)) + 4);
            if ( result == pDwArg2[1] )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 20))(pObj2, 1) != 0
                && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 132))(pObj2) == 6 )
              {
                v9 = sub_422E70(1165);
                return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v9, 0);
              }
              else if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 20))(pObj2, 1) != 0
                     && (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2) > 1 )
              {
                return sub_540DE0(1, 0, pDwArg2[2], 2, *(this + 12), 0, 0);
              }
              else
              {
                v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2);
                result = sub_50D660(v10, 1);
                if ( (uint8_t)result == 0 )
                {
                  fld_e12 = *(this + 12);
                  dword_8F85302 = dword_8F8530;
                  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2);
                  return sub_4866D0(pDwArg2[2], v11, dword_8F85302, fld_e12);
                }
              }
            }
          }
        }
        break;
      case 9:
        break;
      case 8:
        result = sub_44A980(pDwArg2[2]);
        if ( result != 0 )
        {
          result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 16))(result) + 4);
          if ( result == pDwArg2[1] )
          {
            result = *(this + 12);
            v6 = pDwArg2[2];
            if ( result != v6 )
              return sub_486530(result, v6, 1);
          }
        }
        break;
      case 7:
        break;
      default:
        return off_77F3FC("CNRDStorageWindow::process_move() - Unsupported move");
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x50D8F0 sub_50D8F0 —— 当前档位冷却表取值
//   按 dword_9B7D10 当前档位索引 dword_9B7CAC 表首字段。
// ------------------------------------------------------------
int sub_50D8F0()
{
  return dword_9B7CAC[8 * sub_41A5E0((unsigned int)&unk_9B7D10)];
}



// ------------------------------------------------------------
// 0x50D910 sub_50D910 —— 当前档位号读取
//   返回 dword_9B7D10 当前值（·0x50D8F0/·0x50D980 的索引基）。
// ------------------------------------------------------------
int sub_50D910()
{
  return sub_41A5E0((unsigned int)&unk_9B7D10);
}



// ------------------------------------------------------------
// 0x50D920 sub_50D920 —— 仓储栏类型设置（非法档位报错）
//   遍历档位表（步长 8）比对 nArg1，命中且仍在 [dword_9B7C90, dword_9B7D10) 区内时写回 dword_9B7D10；
//   否则按 CNRDStorageWindow::set_storage_type - Abnormal storage type 文案报错。
// ------------------------------------------------------------
int /*cdecl*/ sub_50D920(int nArg1)
{
  int v1; // edi
  int *dword_9B7C902; // esi
  int result; // eax
  int v4; // edx

  v1 = 0;
  dword_9B7C902 = dword_9B7C90;
  do
  {
    result = sub_41A5E0((unsigned int)dword_9B7C902);
    if ( result == nArg1 )
    {
      if ( (int)dword_9B7C902 < (int)dword_9B7C90 || (int)dword_9B7C902 >= (int)dword_9B7D10 )
        result = off_77F3FC("CNRDStorageWindow::set_storage_type - Abnormal storage type %d", v1);
      else
        result = sub_41A590((unsigned int)dword_9B7D10, v4, v1);
    }
    dword_9B7C902 += 8;
    ++v1;
  }
  while ( (int)dword_9B7C902 < (int)dword_9B7D10 );
  return result;
}



// ------------------------------------------------------------
// 0x50D980 sub_50D980 —— 当前档位行数读取
//   返回 dword_9B7C90[8×当前档位]（每档 8 双字记录）。
// ------------------------------------------------------------
int sub_50D980()
{
  int v0; // eax

  v0 = sub_41A5E0((unsigned int)dword_9B7D10);
  return sub_41A5E0((unsigned int)&dword_9B7C90[8 * v0]);
}



// ------------------------------------------------------------
// 0x50D9A0 CNRDStorageWindow__vmt0 —— 仓储窗口绘制主例程（背景/行/槽位/时间提示）
//   背景/行/底边（dword_792024/028/02C 精灵）与滚动条（vmt24）绘制；行数上限 8（超限报 Too many lines）；
//   逐槽 16B 布局经对象 vt+8 绘制、空槽补 16 号精灵，选中槽 ·sub_4F2E40 高亮；光标落时间区
//   （Rect 75,11-183,20）时按 1166 文案显示剩余/总时间（×0.001 秒）。
// ------------------------------------------------------------
int /*thiscall*/ sub_50D9A0(int *this, int nArg2)  // 【CNRDStorageWindow__vmt0】
{
  int result; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // eax
  int pObj3; // eax
  int v8; // eax
  unsigned int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int pObj6; // eax
  int v15; // eax
  int v16; // eax
  int pObj; // eax
  int v18; // eax
  int v19; // eax
  uint64_t v20; // rax
  uint32_t *v21; // ecx
  int pObj5; // eax
  int fld_e13; // ecx
  int v24; // eax
  uint32_t *dword_8F85302; // edx
  int pObj2; // ecx
  bool fld_e132; // cf
  int v28; // eax
  unsigned int v29; // eax
  int v30; // ebx
  int pObj4; // eax
  bool v32; // zf
  int v33; // eax
  char *v34; // eax
  double v35; // [esp+54h] [ebp-CCh]
  float v36; // [esp+58h] [ebp-C8h]
  LONG y; // [esp+70h] [ebp-B0h]
  struct tagRECT rc; // [esp+78h] [ebp-A8h] BYREF
  POINT pt; // [esp+88h] [ebp-98h]
  LONG i; // [esp+90h] [ebp-90h]
  int v41; // [esp+94h] [ebp-8Ch]
  unsigned int v42; // [esp+98h] [ebp-88h]
  char Buffer[128]; // [esp+9Ch] [ebp-84h] BYREF
  int dword_796E502; // [esp+11Ch] [ebp-4h]
  int v45; // [esp+128h] [ebp+8h]
  int v46; // [esp+128h] [ebp+8h]

  dword_796E502 = dword_796E50;
  result = *(this + 2);
  if ( nArg2 == result )
  {
    v4 = *(uint32_t *)(result + 24);
    v5 = *(uint32_t *)(result + 20);
    y = ::pt.y;
    v45 = v4;
    pt.x = ::pt.x;
    v6 = sub_41A5E0((unsigned int)&unk_9B7D10);
    pObj3 = sub_418DD0(dword_792024[3 * v6]);
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v5, v4, dword_79C0B0);
    v8 = sub_41A5E0((unsigned int)&unk_9B7D10);
    v9 = (unsigned int)sub_41A5E0((unsigned int)&dword_9B7C90[8 * v8]) >> 3;
    pt.y = v9;
    v10 = sub_41A5E0((unsigned int)&unk_9B7D10);
    if ( (sub_41A5E0((unsigned int)&dword_9B7C90[8 * v10]) & 7) != 0 )
      pt.y = ++v9;
    if ( v9 > 8 )
    {
      off_77F3FC("CNRDStorageWindow::Proc - Too many lines %d", v9);
      pt.y = 8;
    }
    v11 = sub_41A5E0((unsigned int)&unk_9B7D10);
    v12 = v45 + *(uint32_t *)(sub_418DD0(dword_792024[3 * v11]) + 24);
    i = v12;
    if ( pt.y > 0 )
    {
      for ( i = pt.y; i != 0; --i )
      {
        v13 = sub_41A5E0((unsigned int)&unk_9B7D10);
        pObj6 = sub_418DD0(dword_792028[3 * v13]);
        if ( pObj6 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v5, v12, dword_79C0B0);
        v15 = sub_41A5E0((unsigned int)&unk_9B7D10);
        v12 += *(uint32_t *)(sub_418DD0(dword_792028[3 * v15]) + 24);
      }
      i = v12;
    }
    v16 = sub_41A5E0((unsigned int)&unk_9B7D10);
    pObj = sub_418DD0(dword_79202C[3 * v16]);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v5, v12, dword_79C0B0);
    v18 = sub_418DD0(13);
    (*(void (/*thiscall*/ **)(int *, int, unsigned int))(*this + 24))(
      this,
      21,
      (*(uint32_t *)(v18 + 24) - v45 + v12 - 12) / 0xDu);
    sub_69A5F0((uint32_t *)(*(this + 11) + 132), v5 + 192, v12 + 6);
    result = dword_9B7C84;
    if ( dword_9B7C84 != 0 )
    {
      v19 = sub_41A5E0((unsigned int)&unk_9B7D10);
      v42 = sub_41A5E0((unsigned int)&dword_9B7C9E[8 * v19]);
      v41 = *((uint32_t *)dword_8F8530 + 1);
      v36 = (float)*(int *)(sub_418DD0(6) + 20);
      v20 = (uint64_t)sub_4049C0(0.0, v36, v41, v42);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v21 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = 0;
      v21[13] = 0;
      v21[14] = v20 + v5 + 75;
      v21[15] = 480;
      pObj5 = sub_418DD0(6);
      if ( pObj5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v5 + 75, v12 + 11, dword_79C0B0);
      sub_488670(dword_79C0B0);
      fld_e13 = *(this + 13);
      v24 = 0;
      v42 = 0;
      if ( fld_e13 != 0 )
      {
        dword_8F85302 = dword_8F8530;
        v41 = 0;
        do
        {
          if ( v24 < dword_8F85302[2] )
          {
            pObj2 = *(uint32_t *)(dword_8F85302[3] + 4 * v24);
            if ( pObj2 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 8))(
                pObj2,
                v5 + *(uint32_t *)(*(this + 9) + v41),
                v45 + *(uint32_t *)(v41 + *(this + 9) + 4),
                0,
                0);
              dword_8F85302 = dword_8F8530;
              v24 = v42;
              v12 = i;
            }
          }
          ++v24;
          v41 += 16;
          fld_e132 = v24 < (unsigned int)*(this + 13);
          v42 = v24;
        }
        while ( fld_e132 );
      }
      v28 = sub_41A5E0((unsigned int)&unk_9B7D10);
      v29 = sub_41A5E0((unsigned int)&dword_9B7C90[8 * v28]);
      if ( v29 < 8 * pt.y )
      {
        v30 = 16 * v29;
        v42 = 16 * v29;
        v41 = 8 * pt.y - v29;
        do
        {
          pObj4 = sub_418DD0(16);
          if ( pObj4 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(
              pObj4,
              v5 + *(uint32_t *)(v30 + *(this + 9)),
              v45 + *(uint32_t *)(v30 + *(this + 9) + 4),
              dword_79C0B0);
            v30 = v42;
          }
          v30 += 16;
          v32 = v41 == 1;
          v42 = v30;
          --v41;
        }
        while ( !v32 );
        v12 = i;
      }
      if ( *(this + 12) != -1 )
        sub_4F2E40(
          v5 + *(uint32_t *)(16 * *(this + 12) + *(this + 9)),
          v45 + *(uint32_t *)(16 * *(this + 12) + *(this + 9) + 4));
      rc.top = 11;
      rc.left = 75;
      rc.right = 183;
      rc.bottom = 20;
      OffsetRect(&rc, v5, v12);
      result = PtInRect(&rc, (POINT)__PAIR64__(y, pt.x));
      if ( result == 1 )
      {
        v33 = sub_41A5E0((unsigned int)&unk_9B7D10);
        v46 = sub_41A5E0((unsigned int)&dword_9B7C9E[8 * v33]);
        pt.x = *((uint32_t *)dword_8F8530 + 1);
        v35 = (double)pt.x * 0.001;
        v34 = sub_422E70(1166);
        sprintf(Buffer, v34, v35, (double)v46 * 0.001);
        return sub_4649B0(rc.left + (rc.right - rc.left) / 2, rc.top - 2, -1, -16777216, 2, Buffer, 0, 0, 1600, 0);
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x50DED0 sub_50DED0 —— CNRDStorageWindow 析构核心（双层虚表链）
//   先挂 vftbl_CNRDStorageWindow 调 ·sub_50D570 清理，再挂 vftbl_IRDPopupWindow 转 ·sub_5542F0。
// ------------------------------------------------------------
int /*thiscall*/ sub_50DED0(uint32_t *this)
{
  *this = &vftbl_CNRDStorageWindow;
  sub_50D570(this);
  *this = &vftbl_IRDPopupWindow;
  return sub_5542F0(this);
}



// ------------------------------------------------------------
// 0x50DF30 CNRDStorageWindow__vmtC —— 仓储窗口打开回调
//   置 dword_9B7C84=1 与 dword_9B7C8C=1，播 SAFE_OPEN 音效后返回 1。
// ------------------------------------------------------------
char /*stdcall*/ CNRDStorageWindow__vmtC(int nArg1, int nArg2)
{
  dword_9B7C84 = 1;
  sub_432EA0("SAFE_OPEN", -1, 0, 0);
  dword_9B7C8C = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x50DF60 sub_50DF60 —— 鼠标拾取槽位（get_mouse_over_slot）
//   父窗口可见（+17）且激活件（+12）属三活动态之一时遍历 this+36 槽位矩形（16B，扩展 2px）做 PtInRect；
//   槽数上限 0x40（超限报 slot_limit is too big），未命中返回 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_50DF60(unsigned int *this)
{
  int fld_e2; // ecx
  int v3; // edi
  int result; // eax
  int fld_e22; // eax
  int v6; // edi
  int v7; // ebx
  int fld_e13; // ecx
  int fld_e9; // eax
  int v10; // edx
  uint32_t *v11; // eax
  bool v12; // zf
  unsigned int fld_e132; // ecx
  RECT rc; // [esp+8h] [ebp-20h] BYREF
  POINT pt; // [esp+18h] [ebp-10h]
  unsigned int v16; // [esp+20h] [ebp-8h]
  int v17; // [esp+24h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( *(uint8_t *)(fld_e2 + 17) == 0 )
    return -1;
  v3 = *(uint32_t *)(fld_e2 + 12);
  if ( dword_79BE3C != v3 && dword_79BE34 != v3 && dword_79BE38 != v3 )
    return -1;
  if ( *(this + 13) > 0x40 )
  {
    off_77F3FC("CNRDStorageWindow::get_mouse_over_slot - slot_limit is too big. (%d)", *(this + 13));
    *(this + 13) = 64;
  }
  fld_e22 = *(this + 2);
  v6 = *(uint32_t *)(fld_e22 + 20);
  v7 = *(uint32_t *)(fld_e22 + 24);
  pt.x = ::pt.x;
  fld_e13 = *(this + 13);
  pt.y = ::pt.y;
  v16 = 0;
  if ( fld_e13 == 0 )
    return -1;
  v17 = 0;
  while ( 1 )
  {
    fld_e9 = *(this + 9);
    v10 = *(uint32_t *)(fld_e9 + v17);
    v11 = (uint32_t *)(v17 + fld_e9);
    rc.left = v10 + v6 - 2;
    rc.top = v11[1] + v7 - 2;
    rc.right = v11[2] + v6 + 2;
    rc.bottom = v11[3] + v7 + 2;
    v12 = !PtInRect(&rc, pt);
    result = v16;
    if ( !v12 )
      break;
    fld_e132 = *(this + 13);
    ++v16;
    v17 += 16;
    if ( v16 >= fld_e132 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x50E060 CNRDStorageWindow__vmt8 —— 仓储窗口交互处理（点击/悬停/状态机）
//   取槽位上限与鼠标槽；命中按钮区（+12/+161 判定）播 CLICK_BUTTON2；悬停槽经 ·sub_44E8D0 type 0x1A 拖拽预览；
//   状态机 dword_9B7C8C：1→2、2/3 按钮点击进 5、3 依悬停/拖拽走 ·sub_486C40/·sub_44BC30/·sub_50D710 分支、4→3。
// ------------------------------------------------------------
int /*thiscall*/ sub_50E060(void *this)  // 【CNRDStorageWindow__vmt8】
{
  int v2; // ebx
  int v3; // eax
  int pThis_B; // eax
  int pThis_B2; // eax
  char v6; // cl
  int v7; // eax
  uint32_t *dword_8F85302; // ecx
  int v9; // edx
  int v10; // eax
  int pThis_C; // eax
  int pThis_4; // eax
  bool v13; // zf
  int pThis_C2; // eax
  BOOL v15; // edi
  int v16; // eax
  int pThis_42; // eax
  int pThis_9; // edx
  int pThis_C3; // ecx
  int result; // eax
  int v21; // edx
  int v22; // eax
  int pThis_C5; // [esp-Ch] [ebp-30h]
  int v24; // [esp-8h] [ebp-2Ch]
  int pThis_C4; // [esp-4h] [ebp-28h]
  int v26; // [esp+10h] [ebp-14h]
  int v27; // [esp+14h] [ebp-10h]
  int v28; // [esp+18h] [ebp-Ch]
  int v29; // [esp+1Ch] [ebp-8h]

  v2 = 0;
  v29 = 0;
  v28 = 0;
  v27 = 0;
  v26 = 0;
  v3 = sub_41A5E0((unsigned int)&unk_9B7D10);
  *((uint32_t *)this + 13) = sub_41A5E0((unsigned int)&dword_9B7C90[8 * v3]);
  *((uint32_t *)this + 12) = sub_50DF60(this);
  pThis_B = *((uint32_t *)this + 11);
  if ( *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_B + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v2 = 1;
    v29 = 1;
  }
  pThis_B2 = *((uint32_t *)this + 11);
  v6 = *(uint8_t *)(pThis_B2 + 149);
  v7 = pThis_B2 + 132;
  if ( v6 != 0 && dword_79BE34 == *(uint32_t *)(v7 + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v28 = 1;
  }
  if ( *(uint32_t *)(*((uint32_t *)this + 4) + 2504) == 2 )
  {
    if ( *((uint32_t *)this + 12) != -1 && (uint8_t)sub_69A500(*((uint32_t *)this + 2)) == 1 )
      v26 = 1;
    goto LABEL_11;
  }
  sub_69A650(*((uint32_t *)this + 2));
  if ( (uint8_t)sub_69A4D0(*((uint32_t *)this + 2)) != 1 || (pThis_C = *((uint32_t *)this + 12)) == -1 )
  {
LABEL_11:
    dword_8F85302 = dword_8F8530;
    goto LABEL_12;
  }
  dword_8F85302 = dword_8F8530;
  if ( pThis_C < *((uint32_t *)dword_8F8530 + 2) && *(uint32_t *)(*((uint32_t *)dword_8F8530 + 3) + 4 * pThis_C) != 0 )
  {
    pThis_4 = *(uint32_t *)(*((uint32_t *)this + 4) + 2504);
    if ( pThis_4 != 5 && pThis_4 != 6 )
      v27 = 1;
  }
LABEL_12:
  v9 = dword_8F85302[5];
  if ( v9 != 0 )
    v10 = (dword_8F85302[6] - v9) >> 2;
  else
    v10 = 0;
  v13 = v10 == 0;
  pThis_C2 = *((uint32_t *)this + 12);
  v15 = !v13;
  if ( pThis_C2 == -1 )
  {
    if ( dword_9B88D0 == 0 || dword_795378 != 6 )
      goto LABEL_34;
    sub_44E850(*((uint32_t **)this + 4), 26);
  }
  else
  {
    if ( pThis_C2 >= dword_8F85302[2] )
      v16 = 0;
    else
      v16 = *(uint32_t *)(dword_8F85302[3] + 4 * pThis_C2);
    if ( dword_9B88D0 == v16 && dword_795378 == 6 )
      goto LABEL_34;
    pThis_42 = sub_44E8D0(*((char **)this + 4), (void *)0x1A, v16, 6);
    if ( pThis_42 != 0 )
    {
      pThis_9 = *((uint32_t *)this + 9);
      pThis_C3 = 16 * *((uint32_t *)this + 12);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pThis_42 + 48))(
        pThis_42,
        *(uint32_t *)(pThis_C3 + pThis_9) + *(uint32_t *)(*((uint32_t *)this + 2) + 20),
        *(uint32_t *)(pThis_9 + pThis_C3 + 4) + *(uint32_t *)(*((uint32_t *)this + 2) + 24),
        *(uint32_t *)(pThis_C3 + pThis_9 + 8) - *(uint32_t *)(pThis_C3 + pThis_9),
        *(uint32_t *)(pThis_C3 + pThis_9 + 12) - *(uint32_t *)(pThis_9 + pThis_C3 + 4));
      v2 = v29;
    }
  }
  dword_8F85302 = dword_8F8530;
LABEL_34:
  result = dword_9B7C8C - 1;
  v21 = 3;
  switch ( dword_9B7C8C )
  {
    case 1:
      result = 1;
      if ( dword_9B7C84 == 1 )
        goto LABEL_51;
      dword_9B7C8C = 2;
      if ( dword_9B7C80 == 0 )
        dword_9B7C80 = 1;
      return result;
    case 2:
      if ( v2 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
        dword_9B7C8C = 5;
      }
      return result;
    case 3:
      if ( v2 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
        dword_8F85302 = dword_8F8530;
        dword_9B7C8C = 5;
      }
      if ( v15 )
        goto LABEL_45;
      if ( v28 != 0 )
      {
        result = sub_486C40(dword_8F85302, v21);
LABEL_45:
        dword_9B7C8C = 4;
        return result;
      }
      if ( v27 != 0 )
      {
        pThis_C4 = sub_44A980(*((uint32_t *)this + 12));
        v24 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_C4 + 16))(pThis_C4) + 68);
        pThis_C5 = *((uint32_t *)this + 12);
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_C4 + 16))(pThis_C4);
        return sub_44BC30(2, 8, *(uint32_t *)(v22 + 4), pThis_C5, v24, pThis_C4);
      }
      else
      {
        result = v26;
        if ( v26 != 0 )
        {
          result = sub_50D710(this, *((uint32_t *)this + 4) + 2508);
          dword_9B7C8C = 4;
        }
      }
      return result;
    case 4:
      if ( !v15 )
LABEL_51:
        dword_9B7C8C = 3;
      return result;
    default:
      return result;
  }
}


// ------------------------------------------------------------
// 0x50E380 CNRDStorageWindow__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50DED0 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDStorageWindow__vmt4(uint32_t *Block, char pszArg2)
{
  sub_50DED0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50E3B0 sub_50E3B0 —— 仓储窗口构建（按钮组 + 槽位表布局）
//   读按钮模板 dword_99FCC8，operator new(0x10C) eh 数组构造 2 个 CNButton（unk_6FCD5C/6FCD70 配置）；
//   this+36 槽位表按 128 步长排 8 列（15/47/79/111/143/175/207/239 起），行高取自 10/7 号精灵 +2。
// ------------------------------------------------------------
int /*thiscall*/ sub_50E3B0(uint32_t *this)
{
  uint32_t *pMem; // eax
  int v3; // ebx
  uint32_t *v4; // edi
  int *v5; // edi
  void *pMem2; // eax
  uint32_t *fld_e10; // ecx
  int result; // eax
  int v9; // edx
  unsigned int i; // ecx
  int fld_e9; // edi
  unsigned int v12; // ebx
  uint32_t *v13; // edi
  int fld_e92; // edi
  uint32_t *v15; // edi
  uint32_t *fld_e93; // edi
  uint32_t *fld_e94; // edi
  uint32_t *fld_e95; // edi
  uint32_t *fld_e96; // edi
  uint32_t *fld_e97; // edi
  uint32_t *fld_e98; // edi
  int *Block; // [esp+Ch] [ebp-10h]
  void *Blocka; // [esp+Ch] [ebp-10h]

  *(this + 10) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 188);
  pMem = operator new(0x10Cu);
  v3 = 0;
  if ( pMem != nullptr )
  {
    v4 = pMem + 1;
    *pMem = 2;
    `eh vector constructor iterator'(pMem + 1, 0x84u, 2, sub_46F750, sub_43C480);
  }
  else
  {
    v4 = nullptr;
  }
  *(this + 11) = v4;
  Block = (int *)&unk_6FCD70;
  v5 = (int *)&unk_6FCD5C;
  do
  {
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)(v3 + *(this + 11))
                                                                                     + 32))(
      v3 + *(this + 11),
      *(this + 10),
      *(v5 - 3),
      *(v5 - 2),
      *(v5 - 1),
      *v5 < 0 ? 0 : *v5,
      0,
      0);
    sub_69A5F0((uint32_t *)(v3 + *(this + 11)), *Block, Block[1]);
    sub_69A840(v3 + *(this + 11));
    v5 += 4;
    v3 += 132;
    Block += 2;
  }
  while ( (int)v5 < (int)&dword_6FCD7C );
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 1);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 21, 2);
  sub_69A5F0((uint32_t *)*(this + 2), 34, 34);
  pMem2 = operator new(0x400u);
  fld_e10 = (uint32_t *)*(this + 10);
  *(this + 9) = pMem2;
  Blocka = *(void **)(sub_418DD0(fld_e10, 0xAu) + 24);
  result = *(uint32_t *)(sub_418DD0((uint32_t *)*(this + 10), 7u) + 24) + 2;
  v9 = result + 28;
  for ( i = 48; i < 0x430; i += 128 )
  {
    fld_e9 = *(this + 9);
    v12 = i - 48;
    *(uint32_t *)(fld_e9 + v12 + 4) = result;
    *(uint32_t *)(fld_e9 + v12 + 12) = v9;
    v13 = (uint32_t *)(i - 48 + fld_e9);
    *v13 = 15;
    v13[2] = 43;
    fld_e92 = *(this + 9);
    *(uint32_t *)(fld_e92 + v12 + 20) = result;
    *(uint32_t *)(fld_e92 + v12 + 28) = v9;
    v15 = (uint32_t *)(fld_e92 + i - 48 + 16);
    *v15 = 47;
    v15[2] = 75;
    fld_e93 = (uint32_t *)(*(this + 9) + i - 16);
    fld_e93[1] = result;
    fld_e93[3] = v9;
    *fld_e93 = 79;
    fld_e93[2] = 107;
    fld_e94 = (uint32_t *)(i + *(this + 9));
    fld_e94[1] = result;
    fld_e94[3] = v9;
    *fld_e94 = 111;
    fld_e94[2] = 139;
    fld_e95 = (uint32_t *)(*(this + 9) + i + 16);
    fld_e95[1] = result;
    fld_e95[3] = v9;
    *fld_e95 = 143;
    fld_e95[2] = 171;
    fld_e96 = (uint32_t *)(*(this + 9) + i + 32);
    fld_e96[1] = result;
    fld_e96[3] = v9;
    *fld_e96 = 175;
    fld_e96[2] = 203;
    fld_e97 = (uint32_t *)(*(this + 9) + i + 48);
    fld_e97[1] = result;
    fld_e97[3] = v9;
    *fld_e97 = 207;
    fld_e97[2] = 235;
    fld_e98 = (uint32_t *)(*(this + 9) + i + 64);
    fld_e98[1] = result;
    fld_e98[3] = v9;
    *fld_e98 = 239;
    fld_e98[2] = 267;
    result += (int)Blocka;
    v9 += (int)Blocka;
  }
  return result;
}


// ------------------------------------------------------------
// 0x50E5F0 nengine__CNButton__vmt0 —— CNButton eh 数组析构（标志位 1 释放）
//   pszArg2&2 → eh 数组析构（0x84 步长、计数存 -4）；pszArg2&1 → 释放数组头（-4 偏移）。
// ------------------------------------------------------------
char */*thiscall*/ nengine__CNButton__vmt0(char *this, char pszArg2)
{
  if ( (pszArg2 & 2) != 0 )
  {
    `eh vector destructor iterator'(this, 0x84u, *((uint32_t *)this - 1), sub_43C480);
    if ( (pszArg2 & 1) != 0 )
      j_j__free(this - 4);
    return this - 4;
  }
  else
  {
    sub_43C480(this);
    if ( (pszArg2 & 1) != 0 )
      j__free(this);
    return this;
  }
}



// ------------------------------------------------------------
// 0x50E650 sub_50E650 —— 仓储窗口构造（弹窗基类 + 文案表缓存）
//   弹窗基类 ·sub_5542C0/·sub_5548B0（op 15）后挂 vftbl_CNRDStorageWindow；四段静态文案
//   （1160..1163）惰性取入 dword_9B7CAC 段；槽位游标清零、全局态缺省 5；末 ·sub_50E3B0 建钮。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50E650(uint32_t *this, int nArg2)
{
  *this = &vftbl_IRDPopupWindow;
  sub_5542C0();
  sub_5548B0(nArg2, 15);
  *this = &vftbl_CNRDStorageWindow;
  if ( dword_9B7CAC[0] == 0 )
  {
    dword_9B7CAC[0] = sub_422E70(1160);
    dword_9B7CCC = sub_422E70(1161);
    dword_9B7CEC = sub_422E70(1162);
    dword_9B7D0C = sub_422E70(1163);
  }
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = -1;
  *(this + 13) = 0;
  if ( dword_9B7C8C == 0 )
  {
    dword_9B7C80 = 0;
    dword_9B7C84 = 0;
    dword_9B7C8C = 5;
  }
  sub_50E3B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x50E730 sub_50E730 —— 对象字段清零（三指针 + 两标志）
//   清零 +0/+4/+8 与 +12/+13 标志字节。
// ------------------------------------------------------------
int /*thiscall*/ sub_50E730(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *((uint8_t *)this + 12) = 0;
  *((uint8_t *)this + 13) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x50E750 sub_50E750 —— 表情气泡双图层播放推进
//   主/次两动画件（this+4 / this+8）依次：·sub_4938F0 播放、·sub_491D00 图层属性下发（y 经 vmt192 偏移）；
//   次层帧数 ≥1 时首帧经 ·sub_4926A0 复位（+13 标志）。
// ------------------------------------------------------------
char /*thiscall*/ sub_50E750(uint32_t *this, int nArg2, int nArg3)
{
  int fld_e1; // eax
  int v5; // eax
  int v6; // eax

  LOBYTE(fld_e1) = *((uint8_t *)this + 12);
  if ( (uint8_t)fld_e1 != 0 )
  {
    sub_4938F0(*(this + 1));
    v5 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*this + 192))(*this);
    sub_491D00(dword_79C0B0, nArg2, nArg3 - v5, 0.0);
    fld_e1 = *(this + 1);
    if ( *(int *)(fld_e1 + 148) >= 1 )
    {
      if ( *((uint8_t *)this + 13) == 0 )
      {
        sub_4926A0(*(this + 2));
        *((uint8_t *)this + 13) = 1;
      }
      sub_4938F0(*(this + 2));
      v6 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*this + 192))(*this);
      LOBYTE(fld_e1) = sub_491D00(dword_79C0B0, nArg2, nArg3 - v6, 0.0);
    }
  }
  return fld_e1;
}



// ============================================================
// §D 0x50E7E0-0x50EB40 表情(emoticon)系统
// ============================================================
// ------------------------------------------------------------

// 0x50E7E0 sub_50E7E0 —— 表情标签反查器（unk_9B7D24 表 23 项，$END 结尾；
//   倒序逐长匹配 → 返回索引，未命中返回 23）
// ------------------------------------------------------------
int /*cdecl*/ sub_50E7E0(const char *pArg1)
{
  int *v1; // ebx
  int v2; // ebx
  size_t *v3; // ecx
  size_t v4; // eax
  const char *psz; // eax
  size_t psz2; // [esp-10h] [ebp-20h]
  int v8; // [esp+4h] [ebp-Ch]
  int nLen; // [esp+8h] [ebp-8h]
  int *v10; // [esp+Ch] [ebp-4h]

  nLen = strlen(pArg1);
  if ( nLen >= 0 )
  {
    while ( 2 )
    {
      v1 = (int *)&unk_9B7D24;
      v8 = 0;
      v10 = (int *)&unk_9B7D24;
      do
      {
        if ( strcmp((const char *)sub_41ACF0(*v1), "$END") != 0 )
        {
          v2 = 0;
          while ( 1 )
          {
            v3 = (size_t *)(*v10 + v2);
            v4 = *v3;
            if ( *v3 != 0 )
              v4 = *(uint32_t *)(v4 + 4);
            psz2 = v4;
            psz = (const char *)sub_41ACF0(v3);
            if ( strncmp(psz, &pArg1[nLen], psz2) == 0 )
              return v8;
            v2 += 4;
            if ( strcmp((const char *)sub_41ACF0(v2 + *v10), "$END") == 0 )
            {
              v1 = v10;
              break;
            }
          }
        }
        v1 += 4;
        ++v8;
        v10 = v1;
      }
      while ( (int)v1 < (int)&dword_9B7E94 );
      if ( --nLen >= 0 )
        continue;
      break;
    }
  }
  return 23;
}



// ------------------------------------------------------------
// 0x50E8D0 sub_50E8D0 —— 表情气泡对象构造（EmoBalloonS.ani）
//   记类型 nArg2，sub_42FCB0(228) 实配后 ·sub_431860 载入 Common/Emoticon/EmoBalloonS.ani；
//   ·sub_4924C0(3) 取帧 3 并把 +48 置 3000（毫秒寿命）。
// ------------------------------------------------------------
int /*thiscall*/ sub_50E8D0(uint32_t *this, int nArg2)
{
  int v3; // eax
  int result; // eax

  *this = nArg2;
  if ( sub_42FCB0(228) != 0 )
    v3 = sub_431860((char)"Common/Emoticon/EmoBalloonS.ani", 1);
  else
    v3 = 0;
  *(this + 1) = v3;
  result = sub_4924C0(3);
  *(uint32_t *)(result + 48) = 3000;
  return result;
}



// ------------------------------------------------------------
// 0x50E950 sub_50E950 —— 表情气泡双动画件释放
//   this+4 / this+8 两动画件经 ·sub_42AF90 析构 + ·sub_657740(228) 释放并置空。
// ------------------------------------------------------------
int /*thiscall*/ sub_50E950(void ***this)
{
  int fld_e1; // edi
  int result; // eax
  void **fld_e2; // edi

  fld_e1 = (int)*(this + 1);
  if ( fld_e1 != 0 )
  {
    sub_42AF90(*(this + 1));
    result = sub_657740(fld_e1, 228);
  }
  fld_e2 = *(this + 2);
  *(this + 1) = nullptr;
  if ( fld_e2 != nullptr )
  {
    sub_42AF90(fld_e2);
    result = sub_657740(fld_e2, 228);
  }
  *(this + 2) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x50E9B0 sub_50E9B0 —— 表情气泡次层提前销毁（主层 +170 标志触发）
//   可见且主件 +170 置位时清 +12 标志并释放 +8 次动画件。
// ------------------------------------------------------------
char /*thiscall*/ sub_50E9B0(int this)
{
  int fld_4; // eax
  void **fld_8; // edi

  LOBYTE(fld_4) = *(uint8_t *)(this + 12);
  if ( (uint8_t)fld_4 != 0 )
  {
    fld_4 = *(uint32_t *)(this + 4);
    if ( *(uint8_t *)(fld_4 + 170) != 0 )
    {
      fld_8 = *(void ***)(this + 8);
      *(uint8_t *)(this + 12) = 0;
      if ( fld_8 != nullptr )
      {
        sub_42AF90(fld_8);
        LOBYTE(fld_4) = sub_657740(fld_8, 228);
      }
      *(uint32_t *)(this + 8) = 0;
    }
  }
  return fld_4;
}



// ------------------------------------------------------------
// 0x50EA00 sub_50EA00 —— 表情气泡换图（按索引 off_792078）
//   先释放旧次件（+12 清位）与 ·sub_4926A0 复位主件帧游标，再以 off_792078[nArg2] 建新件（228B），
//   置 +12=1/+13=0。
// ------------------------------------------------------------
int /*thiscall*/ sub_50EA00(int this, int nArg2)
{
  void **fld_8; // edi
  int result; // eax

  if ( *(uint8_t *)(this + 12) != 0 )
  {
    fld_8 = *(void ***)(this + 8);
    *(uint8_t *)(this + 12) = 0;
    if ( fld_8 != nullptr )
    {
      sub_42AF90(fld_8);
      sub_657740(fld_8, 228);
    }
    *(uint32_t *)(this + 8) = 0;
  }
  sub_4926A0(*(uint32_t *)(this + 4));
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)off_792078[nArg2], 1);
  else
    result = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint32_t *)(this + 8) = result;
  *(uint8_t *)(this + 12) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x50EAA0 sub_50EAA0 —— 表情名 → 气泡切换（含 vmt80 可用判定）
//   vmt80 非零时把 pArg2 经 ·sub_50E7E0 反查为索引，命中（≠23）转 ·sub_50EA00。
// ------------------------------------------------------------
int /*thiscall*/ sub_50EAA0(uint32_t *this, const char *pArg2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*this + 80))(*this);
  if ( result != 0 )
  {
    result = sub_50E7E0(pArg2);
    if ( result != 23 )
      return sub_50EA00((int)this, result);
  }
  return result;
}



// ------------------------------------------------------------
// 0x50EAD0 sub_50EAD0 —— 气泡对象定时/计数状态复位
//   清零 +0/+32/+40 与 +44..+64（含内嵌计时目标与计数）。
// ------------------------------------------------------------
int /*thiscall*/ sub_50EAD0(uint32_t *this)
{
  *this = 0;
  *(this + 8) = 0;
  *((uint8_t *)this + 40) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x50EAF0 sub_50EAF0 —— 释放内嵌对象（this+32）并置空
//   this+32 对象存在则经其虚表首项（flag 1）自毁，指针清零；返回该调用结果。
// ------------------------------------------------------------
int /*thiscall*/ sub_50EAF0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e8)(uint32_t, int); // ecx
  int result; // eax

  fld_e8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 8);
  if ( fld_e8 != nullptr )
    result = (**fld_e8)(fld_e8, 1);
  *(this + 8) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x50EB10 sub_50EB10 —— 气泡计时到期判定
//   标志（+40）置位时取 ·sub_699000(this+4) 与到期时刻 +28 比较，到点清 +40。
// ------------------------------------------------------------
char /*thiscall*/ sub_50EB10(int this)
{
  int pThis_4; // eax
  int fld_1C; // edi

  LOBYTE(pThis_4) = *(uint8_t *)(this + 40);
  if ( (uint8_t)pThis_4 != 0 )
  {
    fld_1C = *(uint32_t *)(this + 28);
    pThis_4 = sub_699000(this + 4);  // 【clock_now(clk)】
    if ( pThis_4 >= fld_1C )
      *(uint8_t *)(this + 40) = 0;
  }
  return pThis_4;
}



// ============================================================
// §E 0x50EB40-0x50F1C0 UI 文本气泡与 CNText 族
// ============================================================
// ------------------------------------------------------------

// 0x50EB40 sub_50EB40 —— 表情气泡绘制（按行数拼 9-slice：id 63/64/65/66）
// ------------------------------------------------------------
void /*thiscall*/ sub_50EB40(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int fld_e13; // ecx
  int fld_e8; // eax
  int fld_e14; // ebx
  int v8; // esi
  int pObj2; // eax
  int pObj7; // eax
  bool fld_e11; // cc
  int pObj3; // eax
  int v14; // esi
  int pObj5; // eax
  int pObj6; // eax
  int pObj; // eax
  int pObj4; // eax
  int fld_e132; // eax
  int pObj8; // eax
  int fld_e134; // [esp+4h] [ebp-4h]
  int fld_e133; // [esp+10h] [ebp+8h]
  int v23; // [esp+10h] [ebp+8h]
  int v24; // [esp+10h] [ebp+8h]
  int v25; // [esp+10h] [ebp+8h]
  int v26; // [esp+14h] [ebp+Ch]
  int v27; // [esp+14h] [ebp+Ch]
  int v28; // [esp+14h] [ebp+Ch]
  int v29; // [esp+14h] [ebp+Ch]
  int i; // [esp+18h] [ebp+10h]

  if ( *((uint8_t *)this + 40) != 0 && *(float *)&dword_77F6DC == 1.0 )
  {
    fld_e13 = -10 - 12 * *(this + 13) + nArg2;
    fld_e133 = fld_e13;
    if ( *this != 0 )
    {
      fld_e13 -= 14;
      fld_e133 = fld_e13;
    }
    fld_e8 = *(this + 8);
    fld_e14 = *(this + 14);
    *(uint32_t *)(fld_e8 + 32) = fld_e13 + 5;
    v8 = nArg3 - fld_e14;
    v26 = fld_e13 + 5;
    *(uint32_t *)(fld_e8 + 36) = v8 + 6;
    fld_e134 = fld_e13;
    pObj2 = sub_418DD0(63);
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(
        pObj2,
        fld_e133,
        v8,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v23 = v26;
    v27 = 0;
    if ( (int)*(this + 11) > 0 )
    {
      do
      {
        pObj7 = sub_418DD0(64);
        if ( pObj7 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj7 + 128))(
            pObj7,
            v23,
            v8,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)nArg4 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        fld_e11 = ++v27 < *(this + 11);
        v23 += 12;
      }
      while ( fld_e11 );
    }
    pObj3 = sub_418DD0(65);
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(
        pObj3,
        v23,
        v8,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v14 = v8 + 5;
    for ( i = 0; i < *(this + 12); ++i )
    {
      pObj5 = sub_418DD0(66);
      if ( pObj5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(
          pObj5,
          fld_e134,
          v14,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg4 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v24 = fld_e134 + 5;
      v28 = 0;
      if ( (int)*(this + 11) > 0 )
      {
        do
        {
          pObj6 = sub_418DD0(67);
          if ( pObj6 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(
              pObj6,
              v24,
              v14,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)nArg4 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          fld_e11 = ++v28 < *(this + 11);
          v24 += 12;
        }
        while ( fld_e11 );
      }
      pObj = sub_418DD0(68);
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(
          pObj,
          v24,
          v14,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg4 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v14 += 13;
    }
    pObj4 = sub_418DD0(69);
    if ( pObj4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(
        pObj4,
        fld_e134,
        v14,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v25 = fld_e134 + 5;
    v29 = 0;
    if ( (int)*(this + 11) > 0 )
    {
      do
      {
        fld_e132 = sub_418DD0(2 * (v29 == *(this + 13)) + 70);
        if ( fld_e132 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_e132 + 128))(
            fld_e132,
            v25,
            v14,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)nArg4 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        fld_e11 = ++v29 < *(this + 11);
        v25 += 12;
      }
      while ( fld_e11 );
    }
    pObj8 = sub_418DD0(71);
    if ( pObj8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(
        pObj8,
        v25,
        v14,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    if ( nArg4 == 255 )
      sub_69D780(*(this + 8));
  }
}


// ------------------------------------------------------------
// 0x50EF20 sub_50EF20 —— 气泡文本设置与量算（行数/半高/倒计时）
//   ·sub_69D6C0(-1) 复位文本对象后 ·sub_69DDB0 写入 Format，从其行数组（+16）得显示行数（+48）；
//   按 12 字/行 折算气泡行数（+44）与半高行（+52）；高度（+56）=13×行数+15，叠加对象 vmt192 与
//   vmt40(18) 分支；末 ·sub_698F90 起 nArg4 毫秒（-1→3000）倒计时并置可见（+40=1）。
// ------------------------------------------------------------
char /*thiscall*/ sub_50EF20(int *this, char *Format, int nArg3, int nArg4)
{
  int fld_e8; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int fld_e15; // eax
  int v10; // eax
  int v11; // et2
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int pObj; // ecx
  int fld_e12; // edx
  bool v17; // zf
  int fld_e14; // eax
  int v19; // eax
  int pThis_1; // ecx
  char result; // al
  char v22; // [esp+0h] [ebp-8h]

  sub_69D6C0(-1);
  sub_69DDB0(*(this + 8), Format, v22);
  fld_e8 = *(this + 8);
  v6 = *(uint32_t *)(fld_e8 + 16);
  v7 = fld_e8 + 12;
  if ( v6 != 0 )
    v8 = (*(uint32_t *)(v7 + 8) - v6) >> 2;
  else
    v8 = 0;
  *(this + 12) = v8;
  if ( v8 != 1 || *(this + 16) != 0 )
    fld_e15 = *(this + 15);
  else
    fld_e15 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, Format);
  v11 = fld_e15 % 12;
  v10 = fld_e15 / 12;
  v12 = v11;
  if ( v11 != 0 )
    v12 = 1;
  v13 = v12 + v10;
  *(this + 11) = v13;
  if ( nArg3 != 0 || v13 < 5 )
    v14 = (v13 - 1) / 2;
  else
    v14 = 2;
  pObj = *this;
  fld_e12 = 13 * *(this + 12) + 15;
  v17 = *this == 0;
  *(this + 13) = v14;
  *(this + 14) = fld_e12;
  if ( !v17 )
  {
    *(this + 14) += (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 192))(pObj) + 3;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*this + 40))(*this, 18) != 0 )
    {
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)*this + 360))(*this) == 0;
      fld_e14 = *(this + 14);
      if ( v17 )
        v19 = fld_e14 + 14;
      else
        v19 = fld_e14 + 30;
      *(this + 14) = v19;
    }
  }
  pThis_1 = (int)(this + 1);
  *((uint8_t *)this + 17) = 0;
  *((uint8_t *)this + 18) = 0;
  if ( nArg4 == -1 )
    result = sub_698F90(pThis_1, 3000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  else
    result = sub_698F90(pThis_1, nArg4, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint8_t *)this + 40) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x50F040 sub_50F040 —— vector 超长异常（length_error，不返回）
//   vector<T> too long 标准抛出，与 ·0x50F360 同构。
// ------------------------------------------------------------
void /*noreturn*/ sub_50F040()
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
// 0x50F0B0 sub_50F0B0 —— nengine::CNText 构造（挂 vftbl + 初始化）
//   挂 vftbl_nengine__CNText、+4..+24 清零后 ·sub_69D4E0/·sub_69D150(nArg2,nArg3,nArg4) 初始化文本字段。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_50F0B0(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNText;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  sub_69D4E0();
  sub_69D150(nArg2, nArg3, nArg4);
  return this;
}



// ------------------------------------------------------------
// 0x50F120 nengine__CNText__vmt0 —— CNText 析构（标志位 1 释放）
//   ·sub_50F150 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNText__vmt0(void *Block, char pszArg2)
{
  sub_50F150();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F150 sub_50F150 —— CNText 析构核心（释放缓冲并挂回基类）
//   挂 vftbl_nengine__CNText、·sub_69D550 清理、free +16 并清零 +16/+20/+24，末挂 vftbl_nengine__IObject。
// ------------------------------------------------------------
void /*thiscall*/ sub_50F150(void **this)
{
  *this = &vftbl_nengine__CNText;
  sub_69D550();
  if ( *(this + 4) != nullptr )
    j__free(*(this + 4));
  *(this + 4) = nullptr;
  *(this + 5) = nullptr;
  *(this + 6) = nullptr;
  *((uint8_t *)this + 4) = 0;
  *this = &vftbl_nengine__IObject;
}



// ------------------------------------------------------------
// 0x50F1C0 sub_50F1C0 —— 气泡文本宿主绑定（建 96B CNText + 取屏幕边界）
//   绑定宿主 *this=Block 与宽 this+60=nArg3；operator new(0x60) 建 CNText（dword_79C0B0, 2048, nArg3）并配
//   +56 上下文 dword_99FCCC、+64=1、+80=-1、+92=nArg4；this+64=nArg4、this+36=屏幕对象 +60 值。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F1C0(uint32_t *this, void *Block, int nArg3, int nArg4)
{
  uint8_t *pMem; // eax
  uint8_t *v6; // eax
  int v7; // eax
  int v8; // edx

  *this = Block;
  *(this + 15) = nArg3;
  pMem = operator new(0x60u);
  if ( pMem != nullptr )
    v6 = sub_50F0B0(pMem, dword_79C0B0, 2048, nArg3);
  else
    v6 = nullptr;
  *(this + 8) = v6;
  *((uint32_t *)v6 + 14) = dword_99FCCC;
  *(uint32_t *)(*(this + 8) + 64) = 1;
  *(uint32_t *)(*(this + 8) + 80) = -1;
  *(uint32_t *)(*(this + 8) + 92) = nArg4;
  v7 = *(uint32_t *)(dword_99FCC8 + 20);
  v8 = *(uint32_t *)(v7 + 60);
  *(this + 16) = nArg4;
  *(this + 9) = v8;
  return v7 + 60;
}



// ============================================================
// §F 0x50F270-0x50FFD0 堆叠物(stackable)与恢复类物品族
//   CNChangeMp（MP 立即变更）/ CNRateHpMp（HP/MP 比率回复）/ CNTouchOfRemy（雷米援助）等 ——
//   与 sub_4D6810（CNChangeHp 构造）同族的生命值操作对象；
//   回复率标签 [MP regen speed rate] 走 ×0.0099999998 (=×0.01) 换算（研究 20 §1.3 同型
//   的浮点换算风格）
// ============================================================
// ------------------------------------------------------------

// 0x50F270 sub_50F270 —— CNChangeMp 构造（vftbl_CNChangeMp + sub_602070 基类 + sub_602380 初值）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50F270(uint32_t *this, int nArg2, int nArg3)
{
  sub_4B1030();
  *this = &vftbl_CNChangeMp;
  sub_602070(this);
  sub_602380(nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x50F2D0 CNChangeMp__vmt0 —— CNChangeMp 析构（标志位 1 释放）
//   ·sub_50F300 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNChangeMp__vmt0(void *Block, char pszArg2)
{
  sub_50F300();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F300 sub_50F300 —— CNChangeMp 析构核心（三层基类链）
//   挂 vftbl_CNChangeMp → ·sub_602400 清理 → 挂 vftbl_IRDAppendage 调 ·sub_5F6640 → +8 处挂 IObject 虚表。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F300(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNChangeMp;
  sub_602400();
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x50F360 sub_50F360 —— vector 超长异常（length_error，不返回）
//   vector<T> too long 标准抛出，由 ·0x50F440 扩容路径消费。
// ------------------------------------------------------------
void /*noreturn*/ sub_50F360()
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
// 0x50F3D0 sub_50F3D0 —— 对象大块字段复位（+1348..+1436）【推断：技能树/状态 UI】
//   清零 +1348/+1352、释放 +1360 段；+1372 起 15 个 int 置 -1（无效槽），三标志置 0、+1436=4；返回 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F3D0(int this)
{
  *(uint32_t *)(this + 1348) = 0;
  *(uint32_t *)(this + 1352) = 0;
  if ( *(uint32_t *)(this + 1360) != 0 )
    j__free(*(void **)(this + 1360));
  *(uint32_t *)(this + 1360) = 0;
  *(uint32_t *)(this + 1364) = 0;
  *(uint32_t *)(this + 1368) = 0;
  memset((void *)(this + 1372), 0xFFu, 0x3Cu);
  *(uint8_t *)(this + 1432) = 0;
  *(uint8_t *)(this + 1433) = 0;
  *(uint8_t *)(this + 1434) = 0;
  *(uint32_t *)(this + 1436) = 4;
  return -1;
}



// ------------------------------------------------------------
// 0x50F440 sub_50F440 —— 8 字节元素向量插入（三路分支 + 1.5 倍扩容）
//   就地 ·sub_44BD30/·sub_44BD00 搬移 + ·sub_41FEB0 填充；重建 operator new 8×n + ·sub_63A7C0 填洞；
//   超限 ·sub_50F360。
// ------------------------------------------------------------
void /*thiscall*/ sub_50F440(int this, int nArg2, unsigned int uArg3, int pArg4)
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
      sub_50F360(this);
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
// 0x50F690 sub_50F690 —— CNActiveStatusStackable 析构核心
//   挂 vftbl_CNActiveStatusStackable、nullsub_3，释放 +168 段并清零 +168..+176，末 ·sub_485B50（CNRDStackable 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F690(void **this)
{
  *this = &vftbl_CNActiveStatusStackable;
  nullsub_3();
  if ( *(this + 42) != nullptr )
    j__free(*(this + 42));
  *(this + 42) = nullptr;
  *(this + 43) = nullptr;
  *(this + 44) = nullptr;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50F710 CNActiveStatusStackable__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50F690 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void **/*thiscall*/ CNActiveStatusStackable__vmt4(void **Block, char pszArg2)
{
  sub_50F690(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F740 sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
//   ·sub_485CC0（IRDItem 核心构造）后挂 vftbl_CNRDStackable，+148=8/+152=-1 等槽初值，
//   ·sub_577FF0、·sub_578610(ArgList) 掉落物动画驱动。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50F740(uint32_t *this, char ArgList)
{
  sub_485CC0();
  *this = &vftbl_CNRDStackable;
  *(this + 37) = 8;
  *(this + 38) = -1;
  *(this + 39) = 0;
  *((uint8_t *)this + 160) = 0;
  sub_577FF0(this);
  sub_578610(ArgList);
  return this;
}



// ------------------------------------------------------------
// 0x50F7C0 sub_50F7C0 —— CNIncreaseStatusStackable 构造
//   ·sub_50F740 基类后挂 vftbl_CNIncreaseStatusStackable。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50F7C0(uint32_t *this, char pszArg2)
{
  sub_50F740(this, pszArg2);
  *this = &vftbl_CNIncreaseStatusStackable;
  return this;
}



// ------------------------------------------------------------
// 0x50F7F0 sub_50F7F0 —— CNItemScreamOfHysma 构造
//   ·sub_50F740 基类后挂 vftbl_CNItemScreamOfHysma。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50F7F0(uint32_t *this, char pszArg2)
{
  sub_50F740(this, pszArg2);
  *this = &vftbl_CNItemScreamOfHysma;
  return this;
}



// ------------------------------------------------------------
// 0x50F810 CNItemScreamOfHysma__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50F840 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNItemScreamOfHysma__vmt4(void *Block, char pszArg2)
{
  sub_50F840();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F840 sub_50F840 —— CNItemScreamOfHysma 析构核心
//   挂 vftbl_CNItemScreamOfHysma 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F840(uint32_t *this)
{
  *this = &vftbl_CNItemScreamOfHysma;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50F850 sub_50F850 —— CNAppendageStackable 构造（记录追加初始化）
//   ·sub_50F740 后挂 vftbl_CNAppendageStackable，+168..+188 槽初值（+180=17 类型字、+192=1），
//   ·sub_602E40 释放旧段、·sub_6032D0(nArg3,nArg4) 追加记录。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F850(int this, char pszArg2, int nArg3, int nArg4)
{
  sub_50F740((uint32_t *)this, pszArg2);
  *(uint32_t *)this = &vftbl_CNAppendageStackable;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint8_t *)(this + 192) = 1;
  *(uint32_t *)(this + 180) = 17;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  sub_602E40(this);
  sub_6032D0(nArg3, nArg4);
  return this;
}



// ------------------------------------------------------------
// 0x50F8E0 CNAppendageStackable__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50F910 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNAppendageStackable__vmt4(void *Block, char pszArg2)
{
  sub_50F910();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F910 sub_50F910 —— CNAppendageStackable 析构核心
//   挂 vftbl_CNAppendageStackable、·sub_602DE0 释放 8 字节槽表、free +168 段，末 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F910(void **this)
{
  *this = &vftbl_CNAppendageStackable;
  sub_602DE0();
  if ( *(this + 42) != nullptr )
    j__free(*(this + 42));
  *(this + 42) = nullptr;
  *(this + 43) = nullptr;
  *(this + 44) = nullptr;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50F990 sub_50F990 —— 与 ·0x50F850 同构（差异：末步 ·sub_603300 三参追加）
// ------------------------------------------------------------
int /*thiscall*/ sub_50F990(int this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  sub_50F740((uint32_t *)this, pszArg2);
  *(uint32_t *)this = &vftbl_CNAppendageStackable;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint8_t *)(this + 192) = 1;
  *(uint32_t *)(this + 180) = 17;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  sub_602E40(this);
  sub_603300(nArg3, nArg4, nArg5);
  return this;
}



// ------------------------------------------------------------
// 0x50FA30 sub_50FA30 —— CNCoinOfFortune 构造
//   ·sub_50F740 基类后挂 vftbl_CNCoinOfFortune。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FA30(uint32_t *this, char pszArg2)
{
  sub_50F740(this, pszArg2);
  *this = &vftbl_CNCoinOfFortune;
  return this;
}



// ------------------------------------------------------------
// 0x50FA50 CNCoinOfFortune__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50FA80 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNCoinOfFortune__vmt4(void *Block, char pszArg2)
{
  sub_50FA80();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FA80 sub_50FA80 —— CNCoinOfFortune 析构核心
//   挂 vftbl_CNCoinOfFortune 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FA80(uint32_t *this)
{
  *this = &vftbl_CNCoinOfFortune;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FA90 sub_50FA90 —— CNTouchOfRemy 构造
//   ·sub_50F740 基类后挂 vftbl_CNTouchOfRemy。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FA90(uint32_t *this, char pszArg2)
{
  sub_50F740(this, pszArg2);
  *this = &vftbl_CNTouchOfRemy;
  return this;
}



// ------------------------------------------------------------
// 0x50FAB0 CNTouchOfRemy__vmt88 —— 雷米援助施放（HP/MP 双 30% 恢复）
//   基类 ·CNRDStackable__vmt88 后按 vmt740/vmt756（当前 HP/MP【推断】）×30%：HP → ·sub_4D6810（CNChangeHp，1000ms）、
//   MP → ·sub_50F270（CNChangeMp，1000ms）；各经 vt+56 施放。
// ------------------------------------------------------------
int /*stdcall*/ CNTouchOfRemy__vmt88(int nArg1, int nArg2, void *Block)
{
  int result; // eax
  int v4; // edi
  int pObj; // eax
  uint32_t *pMem; // eax
  uint32_t *v7; // eax
  float v8; // [esp+0h] [ebp-24h]
  int v9; // [esp+30h] [ebp+Ch]

  result = CNRDStackable__vmt88(nArg1, nArg2, Block);
  if ( nArg1 != 0 )
  {
    v9 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 740))(nArg1) * 0.30000001);
    v4 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 756))(nArg1) * 0.30000001);
    if ( operator new(0x80u) != nullptr )
    {
      v8 = (float)v9;
      pObj = sub_4D6810(LODWORD(v8), 1000, 0, 1);
    }
    else
    {
      pObj = 0;
    }
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(pObj, nArg1, nArg1, 0, 0, 0, -1);
    pMem = operator new(0x64u);
    if ( pMem != nullptr )
      v7 = sub_50F270(pMem, v4, 1000);
    else
      v7 = nullptr;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*v7 + 56))(v7, nArg1, nArg1, 0, 0, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x50FBC0 CNTouchOfRemy__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50FBF0 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNTouchOfRemy__vmt4(void *Block, char pszArg2)
{
  sub_50FBF0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FBF0 sub_50FBF0 —— CNTouchOfRemy 析构核心
//   挂 vftbl_CNTouchOfRemy 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FBF0(uint32_t *this)
{
  *this = &vftbl_CNTouchOfRemy;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FC00 sub_50FC00 —— CNRateHpMp 构造（模式 + 回复率 + 时长）
//   ·sub_50F740 后挂 vftbl_CNRateHpMp；+164=nArg3（模式 0 HP/1 MP/2 双）、+168=nArg4（回复率）、+172=nArg5（时长）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FC00(uint32_t *this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  sub_50F740(this, pszArg2);
  *(this + 43) = nArg5;
  *this = &vftbl_CNRateHpMp;
  *(this + 41) = nArg3;
  *(this + 42) = nArg4;
  return this;
}



// ------------------------------------------------------------
// 0x50FC40 CNRateHpMp__vmt88 —— HP/MP 比率回复施放（×0.01 换算）
//   基类后按模式（+164）：0 → vmt740×率×0.01 建 ·sub_4D6810；1 → vmt756×率×0.01 建 ·sub_50F270；
//   2 → 两者皆建；量值经 vt+56 施放（率标签 [MP regen speed rate] ×0.0099999998）。
// ------------------------------------------------------------
int /*thiscall*/ CNRateHpMp__vmt88(int *this, int nArg2, void *Block, void *pArg4)
{
  int result; // eax
  uint32_t *fld_e432; // eax
  int fld_e42; // ebx
  uint32_t *pMem; // eax
  int fld_e43; // eax
  float v10; // [esp+0h] [ebp-28h]
  float v11; // [esp+0h] [ebp-28h]
  void *fld_e423; // [esp+38h] [ebp+10h]
  void *fld_e422; // [esp+38h] [ebp+10h]

  result = CNRDStackable__vmt88(nArg2, Block, pArg4);
  if ( nArg2 != 0 )
  {
    result = *(this + 41);
    if ( result != 0 )
    {
      if ( result == 1 )
      {
        fld_e42 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2)
                              * ((double)*(this + 42)
                               * 0.0099999998));
        pMem = operator new(0x64u);
      }
      else
      {
        if ( result != 2 )
          return result;
        fld_e422 = (void *)(uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2)
                                       * ((double)*(this + 42)
                                        * 0.0099999998));
        if ( operator new(0x80u) != nullptr )
        {
          v11 = (float)(int)fld_e422;
          fld_e43 = sub_4D6810(LODWORD(v11), *(this + 43), 0, 1);
        }
        else
        {
          fld_e43 = 0;
        }
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)fld_e43 + 56))(
          fld_e43,
          nArg2,
          nArg2,
          0,
          0,
          0,
          -1);
        fld_e42 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2)
                              * ((double)*(this + 42)
                               * 0.0099999998));
        pMem = operator new(0x64u);
      }
      if ( pMem != nullptr )
      {
        fld_e432 = sub_50F270(pMem, fld_e42, *(this + 43));
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*fld_e432 + 56))(
                 fld_e432,
                 nArg2,
                 nArg2,
                 0,
                 0,
                 0,
                 -1);
      }
    }
    else
    {
      fld_e423 = (void *)(uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2)
                                     * ((double)*(this + 42)
                                      * 0.0099999998));
      if ( operator new(0x80u) != nullptr )
      {
        v10 = (float)(int)fld_e423;
        fld_e432 = (uint32_t *)sub_4D6810(LODWORD(v10), *(this + 43), 0, 1);
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*fld_e432 + 56))(
                 fld_e432,
                 nArg2,
                 nArg2,
                 0,
                 0,
                 0,
                 -1);
      }
    }
    fld_e432 = nullptr;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*fld_e432 + 56))(fld_e432, nArg2, nArg2, 0, 0, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x50FE30 CNRateHpMp__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50FE60 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNRateHpMp__vmt4(void *Block, char pszArg2)
{
  sub_50FE60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FE60 sub_50FE60 —— CNRateHpMp 析构核心
//   挂 vftbl_CNRateHpMp 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FE60(uint32_t *this)
{
  *this = &vftbl_CNRateHpMp;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FE70 sub_50FE70 —— CNCallStorageBird 构造
//   ·sub_50F740 基类后挂 vftbl_CNCallStorageBird。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FE70(uint32_t *this, char pszArg2)
{
  sub_50F740(this, pszArg2);
  *this = &vftbl_CNCallStorageBird;
  return this;
}



// ------------------------------------------------------------
// 0x50FE90 CNCallStorageBird__vmt88 —— 仓库鸟拾取动画施放（本地玩家限定）
//   仅当 pDwArg1 == dword_8F7C04（本地玩家）时经 vt+580 播放 51200 号动画，参数含当前档位 ·sub_50D910。
// ------------------------------------------------------------
int /*stdcall*/ CNCallStorageBird__vmt88(int *pDwArg1, int nArg2, int nArg3)
{
  int result; // eax
  int v4; // edi
  int v5; // eax

  result = CNRDStackable__vmt88(pDwArg1, nArg2, nArg3);
  if ( pDwArg1 != nullptr && pDwArg1 == (int *)dword_8F7C04 )
  {
    v4 = *pDwArg1;
    v5 = sub_50D910();
    return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(
             pDwArg1,
             51200,
             v5,
             0,
             0,
             70,
             0,
             700,
             4,
             0,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x50FEF0 CNCallStorageBird__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50FF20 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNCallStorageBird__vmt4(void *Block, char pszArg2)
{
  sub_50FF20();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FF20 sub_50FF20 —— CNCallStorageBird 析构核心
//   挂 vftbl_CNCallStorageBird 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FF20(uint32_t *this)
{
  *this = &vftbl_CNCallStorageBird;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FF30 sub_50FF30 —— CNOmozzaOfWorld 构造
//   ·sub_50F740 后挂 vftbl_CNOmozzaOfWorld；+164/+168 存两参、+172 存标志。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FF30(int this, char pszArg2, int nArg3, int nArg4, char pszArg5)
{
  sub_50F740((uint32_t *)this, pszArg2);
  *(uint8_t *)(this + 172) = pszArg5;
  *(uint32_t *)this = &vftbl_CNOmozzaOfWorld;
  *(uint32_t *)(this + 164) = nArg3;
  *(uint32_t *)(this + 168) = nArg4;
  return this;
}



// ------------------------------------------------------------
// 0x50FF70 CNOmozzaOfWorld__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50FFA0 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNOmozzaOfWorld__vmt4(void *Block, char pszArg2)
{
  sub_50FFA0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FFA0 sub_50FFA0 —— CNOmozzaOfWorld 析构核心
//   挂 vftbl_CNOmozzaOfWorld 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FFA0(uint32_t *this)
{
  *this = &vftbl_CNOmozzaOfWorld;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FFB0 sub_50FFB0 —— CNUsableStackable 构造
//   ·sub_50F740 基类后挂 vftbl_CNUsableStackable。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FFB0(uint32_t *this, char pszArg2)
{
  sub_50F740(this, pszArg2);
  *this = &vftbl_CNUsableStackable;
  return this;
}



// ------------------------------------------------------------
// 0x50FFD0 CNIncreaseStatusStackable__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50F7E0 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNIncreaseStatusStackable__vmt4(void *Block, char pszArg2)
{
  sub_50F7E0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}

