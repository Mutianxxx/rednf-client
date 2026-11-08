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
// 0x50C140 sub_50C140
// ------------------------------------------------------------
void /*thiscall*/ sub_50C140(int *this, unsigned int a2, char a3, void *Block, int a5, int a6)
{
  int v6; // esi
  unsigned int v7; // edx
  int v8; // edx

  v6 = *(this + 1);
  if ( v6 != 0 )
    v7 = (*(this + 2) - v6) >> 4;
  else
    v7 = 0;
  if ( v7 >= a2 )
  {
    if ( v6 != 0 && a2 < (*(this + 2) - v6) >> 4 )
      sub_50BE50(this, (int *)&a2, v6 + 16 * a2, *(this + 2));
  }
  else
  {
    if ( v6 != 0 )
      v8 = (*(this + 2) - v6) >> 4;
    else
      v8 = 0;
    sub_50BEA0((int)this, *(this + 2), a2 - v8, (int)&a3);
  }
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x50C1F0 sub_50C1F0
// ------------------------------------------------------------
int /*thiscall*/ sub_50C1F0(uint32_t *this, int a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi
  int result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) >> 4;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) >> 4 )
    return sub_4C3DC0(*(this + 2), 1, a2);
  v5 = *(this + 2);
  result = sub_4C2BA0(v5, 1, a2);
  *(this + 2) = v5 + 16;
  return result;
}



// ------------------------------------------------------------
// 0x50C260 sub_50C260
// ------------------------------------------------------------
void /*thiscall*/ sub_50C260(int *this, unsigned int a2)
{
  char v2; // [esp+0h] [ebp-14h] BYREF
  char *v3; // [esp+10h] [ebp-4h]

  v3 = &v2;
  sub_50C140(this, a2, v2, nullptr, 0, 0);
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
char /*cdecl*/ sub_50C290(int a1, int a2)
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
  char **v13; // esi
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
  int v50; // [esp+5Ch] [ebp-10h]
  int v51; // [esp+68h] [ebp-4h]

  v50 = dword_796E50;
  result = sub_442A10((char)&unk_9B7730, a2);
  if ( result == 0 )
    return result;
  sub_4D1EA0(a1);
  sub_443300(a1 + 1640, "%s%s", (char)&unk_9B7730);
  v49 = 15;
  v48 = 0;
  LOBYTE(Block) = 0;
  v51 = 0;
  v45 = nullptr;
  sub_41BFE0(&v45, szPassword);
  v40 = (void *)(a1 + 628);
  v3 = a1 + 152;
  LOBYTE(v51) = 1;
  v44 = 0;
  v42 = a1 + 152;
  v41 = (void *)(a1 + 724);
  if ( (uint8_t)sub_443430(v46) != 0 )
  {
    while ( 1 )
    {
      sub_442B20(v46);
      if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[job]", 5u) == 0 )
      {
        sub_442E10();
        v4 = sub_41ACF0(&v45);
        *(uint32_t *)a1 = sub_4426A0(v4);
        goto LABEL_161;
      }
      if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[growtype name]", 0xFu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[width]", 7u) == 0 )
        {
          *(uint32_t *)(a1 + 144) = sub_4423D0(nullptr);
          *(uint32_t *)(a1 + 148) = sub_4423D0(nullptr);
          goto LABEL_161;
        }
        if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[jump speed]", 0xCu) == 0 )
        {
          *(uint32_t *)(a1 + 820) = sub_4423D0(nullptr);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[initial value]") != 0 )
        {
          v42 = a1 + 152;
          v40 = (void *)(a1 + 628);
          v41 = (void *)(a1 + 724);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 1]") != 0 )
        {
          v42 = a1 + 231;
          v40 = (void *)(a1 + 644);
          v41 = (void *)(a1 + 740);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 2]") != 0 )
        {
          v42 = a1 + 310;
          v40 = (void *)(a1 + 660);
          v41 = (void *)(a1 + 756);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 3]") != 0 )
        {
          v42 = a1 + 389;
          v40 = (void *)(a1 + 676);
          v41 = (void *)(a1 + 772);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 4]") != 0 )
        {
          v42 = a1 + 468;
          v40 = (void *)(a1 + 692);
          v41 = (void *)(a1 + 788);
          goto LABEL_161;
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 5]") != 0 )
        {
          v42 = a1 + 547;
          v40 = (void *)(a1 + 708);
          v41 = (void *)(a1 + 804);
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
          if ( sub_442E10() != 0 )
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
            while ( sub_442E10() != 0 );
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
            sub_4017E0(a1 + 1440);
            while ( sub_442E10() != 0 )
              sub_420BB0(&v45);
          }
          else if ( (uint8_t)sub_423300(v46, "[etc motion]") != 0 )
          {
            sub_4017E0(a1 + 1456);
            while ( sub_442E10() != 0 )
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
              sub_4017E0(a1 + 1528);
              while ( sub_442E10() != 0 )
                sub_420BB0(&v45);
            }
            else if ( (uint8_t)sub_423300(v46, "[etc attack info]") != 0 )
            {
              sub_4017E0(a1 + 1544);
              while ( sub_442E10() != 0 )
                sub_420BB0(&v45);
            }
            else if ( (uint8_t)sub_423300(v46, "[weapon wav]") != 0 )
            {
              v11 = nullptr;
              v37 = nullptr;
              v38 = nullptr;
              v39 = 0;
              LOBYTE(v51) = 2;
              if ( sub_442E10() != 0 )
              {
                do
                  sub_420BB0(&v45);
                while ( sub_442E10() != 0 );
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
                sub_5E5260((void **)(a1 + 1576));
                sub_5E5260((void **)(a1 + 1592));
                sub_5E5260((void **)(a1 + 1608));
                sub_5E5260((void **)(a1 + 1624));
                if ( sub_442E10() == 0 )
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
                    sub_431230(a1 + 1576, &v43);
                  }
                  else if ( sub_43BCF0(&v45, "[burn]") )
                  {
                    v43 = 2;
                    sub_431230(a1 + 1576, &v43);
                  }
                  else if ( sub_43BCF0(&v45, "[etc]") )
                  {
                    v43 = 3;
LABEL_150:
                    sub_431230(a1 + 1576, &v43);
                  }
                  sub_442E10();
                  if ( sub_43BCF0(&v45, "[no blood]") )
                  {
                    *(float *)&v43 = 0.0;
                    sub_431230(a1 + 1592, &v43);
                  }
                  else if ( sub_43BCF0(&v45, "[blood]") )
                  {
                    v43 = 1;
                    sub_431230(a1 + 1592, &v43);
                  }
                  *(float *)&v43 = COERCE_FLOAT(sub_4423D0(nullptr));
                  sub_431230(a1 + 1608, &v43);
                  *(float *)&v43 = sub_442480(nullptr);
                  sub_5020D0(&v43);
                  if ( sub_442E10() == 0 )
                    goto LABEL_161;
                  continue;
                }
              }
              v13 = off_791FD8;
              v14 = (uint16_t *)(v42 + 24);
              do
              {
                if ( (uint8_t)sub_423300(v46, *v13) != 0 )
                {
                  v34 = sub_442480(nullptr) * 10.0;
                  *v14 = sub_432F40(v34);
                }
                ++v13;
                ++v14;
              }
              while ( (int)v13 < (int)off_792018 );
            }
          }
        }
      }
      else
      {
        v5 = a1 + 4;
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
char /*cdecl*/ sub_50D260(char *a1, int a2)
{
  char *v2; // eax
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
  int v15[11]; // [esp+Ch] [ebp-68h] BYREF
  uint32_t Block[11]; // [esp+38h] [ebp-3Ch] BYREF
  char **v17; // [esp+64h] [ebp-10h]
  int v18; // [esp+68h] [ebp-Ch]
  unsigned int v19; // [esp+6Ch] [ebp-8h]
  int v20; // [esp+70h] [ebp-4h]

  v2 = a1;
  v3 = byte_9B7830 - a1;
  do
  {
    v4 = *v2;
    v2[v3] = *v2;
    ++v2;
  }
  while ( v4 != 0 );
  if ( byte_9B782F[strlen(byte_9B7830)] != 92 && byte_9B782F[strlen(byte_9B7830)] != 47 )
    *(uint16_t *)&byte_9B7830[strlen(byte_9B7830)] = 92;
  if ( (uint8_t)sub_443C40((int)&unk_9B7C30, (char)byte_9B7830, a2) != 0 )
  {
    sub_50C260(3);
    v5 = (int *)off_792018;
    v20 = 0;
    v17 = off_792018;
    while ( (uint8_t)sub_442A10((char)byte_9B7830, *v5) != 0 )
    {
      v6 = 0;
      HIBYTE(a1) = 0;
      memset(Block, 0, sizeof(Block));
      v19 = 0;
      v7 = sub_4423D0((uint8_t *)&a1 + 3);
      if ( HIBYTE(a1) != 0 )
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
              memset(v15, 0, sizeof(v15));
              sub_509890(
                v19 + 1,
                v15[0],
                v15[1],
                v15[2],
                v15[3],
                v15[4],
                v15[5],
                v15[6],
                v15[7],
                v15[8],
                v15[9],
                v15[10]);
            }
            qmemcpy((void *)(v18 + *(uint32_t *)((char *)dword_9B7C64 + v20 + 4)), Block, 44);
            v6 = v19;
          }
          v19 = ++v6;
          v18 += 44;
          v7 = sub_4423D0((uint8_t *)&a1 + 3);
        }
        while ( HIBYTE(a1) != 0 );
        v5 = (int *)v17;
      }
      v17 = (char **)++v5;
      v20 += 16;
      if ( (int)v5 >= (int)&dword_792024 )
        return 1;
    }
  }
  return 0;
}


// ------------------------------------------------------------
// 0x50D4E0 sub_50D4E0
// ------------------------------------------------------------
int /*thiscall*/ sub_50D4E0(uint32_t *this)
{
  *this = &vftbl_IRDPopupWindow;
  return sub_5542F0();
}



// ------------------------------------------------------------
// 0x50D4F0 IRDPopupWindow__vmt4
// ------------------------------------------------------------
uint32_t */*thiscall*/ IRDPopupWindow__vmt4(uint32_t *Block, char a2)
{
  *Block = &vftbl_IRDPopupWindow;
  sub_5542F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50D520 sub_50D520
// ------------------------------------------------------------
void /*thiscall*/ sub_50D520(char *this)
{
  sub_41A580(this + 14);
  sub_41A580(this);
}



// ------------------------------------------------------------
// 0x50D570 sub_50D570
// ------------------------------------------------------------
int /*thiscall*/ sub_50D570(uint32_t *this)
{
  int i; // esi
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void *v4; // eax
  int result; // eax

  for ( i = 0; i < 264; i += 132 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)(*(this + 11) + i) + 8))(*(this + 11) + i);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( v3 != nullptr )
  {
    if ( *(v3 - 1) != nullptr )
      (**v3)(v3, 3);
    else
      j_j__free(v3 - 1);
  }
  v4 = (void *)*(this + 9);
  *(this + 11) = 0;
  if ( v4 != nullptr )
    j_j__free(v4);
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
// 0x50D610 CNRDStorageWindow__vmt10
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
// 0x50D660 sub_50D660
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_50D660(int a1, char a2)
{
  int v2; // eax
  int v3; // esi
  const char *v4; // eax
  char Buffer[1024]; // [esp+Ch] [ebp-404h] BYREF
  int v7; // [esp+40Ch] [ebp-4h]

  v7 = dword_796E50;
  v2 = sub_41A5E0((unsigned int)&unk_9B7D10);
  v3 = sub_41A5E0((unsigned int)&dword_9B7C9E[8 * v2]) - *((uint32_t *)dword_8F8530 + 1) - a1;
  if ( v3 < 0 && a2 != 0 )
  {
    v4 = (const char *)sub_422E70(1164);
    sprintf(Buffer, v4, (double)(int)abs32(v3) * 0.001);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);
  }
  return v3 < 0;
}



// ------------------------------------------------------------
// 0x50D710 sub_50D710
// ------------------------------------------------------------
int /*thiscall*/ sub_50D710(int *this, int *a2)
{
  int result; // eax
  int v4; // esi
  uint32_t *v5; // eax
  int v6; // edi
  int v7; // ecx
  int v8; // esi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  void *v12; // [esp-8h] [ebp-14h]
  int v13; // [esp-4h] [ebp-10h]

  result = *a2;
  if ( *a2 == 2 )
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, a2[2]);
    v4 = result;
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 16))(result);
      if ( *(uint32_t *)(result + 4) == a2[1] )
      {
        v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 172))(v4);
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
        result = a2[2];
        if ( result < *((uint32_t *)dword_8F852C + 2) )
        {
          v7 = *((uint32_t *)dword_8F852C + 3);
          v8 = *(uint32_t *)(v7 + 4 * result);
          if ( v8 != 0 )
          {
            result = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v8 + 16))(*(uint32_t *)(v7 + 4 * result)) + 4);
            if ( result == a2[1] )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 20))(v8, 1) != 0
                && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 132))(v8) == 6 )
              {
                v9 = sub_422E70(1165);
                return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v9, 0);
              }
              else if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 20))(v8, 1) != 0
                     && (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 44))(v8) > 1 )
              {
                return sub_540DE0(1, 0, a2[2], 2, *(this + 12), 0, 0);
              }
              else
              {
                v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 36))(v8);
                result = sub_50D660(v10, 1);
                if ( (uint8_t)result == 0 )
                {
                  v13 = *(this + 12);
                  v12 = dword_8F8530;
                  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 44))(v8);
                  return sub_4866D0(a2[2], v11, v12, v13);
                }
              }
            }
          }
        }
        break;
      case 9:
        break;
      case 8:
        result = sub_44A980(a2[2]);
        if ( result != 0 )
        {
          result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 16))(result) + 4);
          if ( result == a2[1] )
          {
            result = *(this + 12);
            v6 = a2[2];
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
// 0x50D8F0 sub_50D8F0
// ------------------------------------------------------------
int sub_50D8F0()
{
  return dword_9B7CAC[8 * sub_41A5E0((unsigned int)&unk_9B7D10)];
}



// ------------------------------------------------------------
// 0x50D910 sub_50D910
// ------------------------------------------------------------
int sub_50D910()
{
  return sub_41A5E0((unsigned int)&unk_9B7D10);
}



// ------------------------------------------------------------
// 0x50D920 sub_50D920
// ------------------------------------------------------------
int /*cdecl*/ sub_50D920(int a1)
{
  int v1; // edi
  int *v2; // esi
  int result; // eax
  int v4; // edx

  v1 = 0;
  v2 = dword_9B7C90;
  do
  {
    result = sub_41A5E0((unsigned int)v2);
    if ( result == a1 )
    {
      if ( (int)v2 < (int)dword_9B7C90 || (int)v2 >= (int)dword_9B7D10 )
        result = off_77F3FC("CNRDStorageWindow::set_storage_type - Abnormal storage type %d", v1);
      else
        result = sub_41A590((unsigned int)dword_9B7D10, v4, v1);
    }
    v2 += 8;
    ++v1;
  }
  while ( (int)v2 < (int)dword_9B7D10 );
  return result;
}



// ------------------------------------------------------------
// 0x50D980 sub_50D980
// ------------------------------------------------------------
int sub_50D980()
{
  int v0; // eax

  v0 = sub_41A5E0((unsigned int)dword_9B7D10);
  return sub_41A5E0((unsigned int)&dword_9B7C90[8 * v0]);
}



// ------------------------------------------------------------
// 0x50D9A0 CNRDStorageWindow__vmt0
// ------------------------------------------------------------
int /*thiscall*/ sub_50D9A0(int *this, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  unsigned int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  uint64_t v20; // rax
  uint32_t *v21; // ecx
  int v22; // eax
  int v23; // ecx
  int v24; // eax
  uint32_t *v25; // edx
  int v26; // ecx
  bool v27; // cf
  int v28; // eax
  unsigned int v29; // eax
  int v30; // ebx
  int v31; // eax
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
  int v44; // [esp+11Ch] [ebp-4h]
  int v45; // [esp+128h] [ebp+8h]
  int v46; // [esp+128h] [ebp+8h]

  v44 = dword_796E50;
  result = *(this + 2);
  if ( a2 == result )
  {
    v4 = *(uint32_t *)(result + 24);
    v5 = *(uint32_t *)(result + 20);
    y = ::pt.y;
    v45 = v4;
    pt.x = ::pt.x;
    v6 = sub_41A5E0((unsigned int)&unk_9B7D10);
    v7 = sub_418DD0(dword_792024[3 * v6]);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5, v4, dword_79C0B0);
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
        v14 = sub_418DD0(dword_792028[3 * v13]);
        if ( v14 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v5, v12, dword_79C0B0);
        v15 = sub_41A5E0((unsigned int)&unk_9B7D10);
        v12 += *(uint32_t *)(sub_418DD0(dword_792028[3 * v15]) + 24);
      }
      i = v12;
    }
    v16 = sub_41A5E0((unsigned int)&unk_9B7D10);
    v17 = sub_418DD0(dword_79202C[3 * v16]);
    if ( v17 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v17 + 152))(v17, v5, v12, dword_79C0B0);
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
      v20 = (uint64_t)sub_4049C0(0.0, v36, v41, v42);
      v21 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = 0;
      v21[13] = 0;
      v21[14] = v20 + v5 + 75;
      v21[15] = 480;
      v22 = sub_418DD0(6);
      if ( v22 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v22 + 152))(v22, v5 + 75, v12 + 11, dword_79C0B0);
      sub_488670(dword_79C0B0);
      v23 = *(this + 13);
      v24 = 0;
      v42 = 0;
      if ( v23 != 0 )
      {
        v25 = dword_8F8530;
        v41 = 0;
        do
        {
          if ( v24 < v25[2] )
          {
            v26 = *(uint32_t *)(v25[3] + 4 * v24);
            if ( v26 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)v26 + 8))(
                v26,
                v5 + *(uint32_t *)(*(this + 9) + v41),
                v45 + *(uint32_t *)(v41 + *(this + 9) + 4),
                0,
                0);
              v25 = dword_8F8530;
              v24 = v42;
              v12 = i;
            }
          }
          ++v24;
          v41 += 16;
          v27 = v24 < (unsigned int)*(this + 13);
          v42 = v24;
        }
        while ( v27 );
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
          v31 = sub_418DD0(16);
          if ( v31 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v31 + 152))(
              v31,
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
// 0x50DED0 sub_50DED0
// ------------------------------------------------------------
int /*thiscall*/ sub_50DED0(uint32_t *this)
{
  *this = &vftbl_CNRDStorageWindow;
  sub_50D570(this);
  *this = &vftbl_IRDPopupWindow;
  return sub_5542F0(this);
}



// ------------------------------------------------------------
// 0x50DF30 CNRDStorageWindow__vmtC
// ------------------------------------------------------------
char /*stdcall*/ CNRDStorageWindow__vmtC(int a1, int a2)
{
  dword_9B7C84 = 1;
  sub_432EA0("SAFE_OPEN", -1, 0, 0);
  dword_9B7C8C = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x50DF60 sub_50DF60
// ------------------------------------------------------------
int /*thiscall*/ sub_50DF60(unsigned int *this)
{
  int v2; // ecx
  int v3; // edi
  int result; // eax
  int v5; // eax
  int v6; // edi
  int v7; // ebx
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  uint32_t *v11; // eax
  bool v12; // zf
  unsigned int v13; // ecx
  RECT rc; // [esp+8h] [ebp-20h] BYREF
  POINT pt; // [esp+18h] [ebp-10h]
  unsigned int v16; // [esp+20h] [ebp-8h]
  int v17; // [esp+24h] [ebp-4h]

  v2 = *(this + 2);
  if ( *(uint8_t *)(v2 + 17) == 0 )
    return -1;
  v3 = *(uint32_t *)(v2 + 12);
  if ( dword_79BE3C != v3 && dword_79BE34 != v3 && dword_79BE38 != v3 )
    return -1;
  if ( *(this + 13) > 0x40 )
  {
    off_77F3FC("CNRDStorageWindow::get_mouse_over_slot - slot_limit is too big. (%d)", *(this + 13));
    *(this + 13) = 64;
  }
  v5 = *(this + 2);
  v6 = *(uint32_t *)(v5 + 20);
  v7 = *(uint32_t *)(v5 + 24);
  pt.x = ::pt.x;
  v8 = *(this + 13);
  pt.y = ::pt.y;
  v16 = 0;
  if ( v8 == 0 )
    return -1;
  v17 = 0;
  while ( 1 )
  {
    v9 = *(this + 9);
    v10 = *(uint32_t *)(v9 + v17);
    v11 = (uint32_t *)(v17 + v9);
    rc.left = v10 + v6 - 2;
    rc.top = v11[1] + v7 - 2;
    rc.right = v11[2] + v6 + 2;
    rc.bottom = v11[3] + v7 + 2;
    v12 = !PtInRect(&rc, pt);
    result = v16;
    if ( !v12 )
      break;
    v13 = *(this + 13);
    ++v16;
    v17 += 16;
    if ( v16 >= v13 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x50E060 CNRDStorageWindow__vmt8
// ------------------------------------------------------------
int /*thiscall*/ sub_50E060(void *this)
{
  int v2; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  char v6; // cl
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  bool v13; // zf
  int v14; // eax
  BOOL v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // ecx
  int result; // eax
  int v21; // edx
  int v22; // eax
  int v23; // [esp-Ch] [ebp-30h]
  int v24; // [esp-8h] [ebp-2Ch]
  int v25; // [esp-4h] [ebp-28h]
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
  v4 = *((uint32_t *)this + 11);
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v2 = 1;
    v29 = 1;
  }
  v5 = *((uint32_t *)this + 11);
  v6 = *(uint8_t *)(v5 + 149);
  v7 = v5 + 132;
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
  if ( (uint8_t)sub_69A4D0(*((uint32_t *)this + 2)) != 1 || (v11 = *((uint32_t *)this + 12)) == -1 )
  {
LABEL_11:
    v8 = dword_8F8530;
    goto LABEL_12;
  }
  v8 = dword_8F8530;
  if ( v11 < *((uint32_t *)dword_8F8530 + 2) && *(uint32_t *)(*((uint32_t *)dword_8F8530 + 3) + 4 * v11) != 0 )
  {
    v12 = *(uint32_t *)(*((uint32_t *)this + 4) + 2504);
    if ( v12 != 5 && v12 != 6 )
      v27 = 1;
  }
LABEL_12:
  v9 = v8[5];
  if ( v9 != 0 )
    v10 = (v8[6] - v9) >> 2;
  else
    v10 = 0;
  v13 = v10 == 0;
  v14 = *((uint32_t *)this + 12);
  v15 = !v13;
  if ( v14 == -1 )
  {
    if ( dword_9B88D0 == 0 || dword_795378 != 6 )
      goto LABEL_34;
    sub_44E850(*((uint32_t **)this + 4), 26);
  }
  else
  {
    if ( v14 >= v8[2] )
      v16 = 0;
    else
      v16 = *(uint32_t *)(v8[3] + 4 * v14);
    if ( dword_9B88D0 == v16 && dword_795378 == 6 )
      goto LABEL_34;
    v17 = sub_44E8D0(*((char **)this + 4), (void *)0x1A, v16, 6);
    if ( v17 != 0 )
    {
      v18 = *((uint32_t *)this + 9);
      v19 = 16 * *((uint32_t *)this + 12);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v17 + 48))(
        v17,
        *(uint32_t *)(v19 + v18) + *(uint32_t *)(*((uint32_t *)this + 2) + 20),
        *(uint32_t *)(v18 + v19 + 4) + *(uint32_t *)(*((uint32_t *)this + 2) + 24),
        *(uint32_t *)(v19 + v18 + 8) - *(uint32_t *)(v19 + v18),
        *(uint32_t *)(v19 + v18 + 12) - *(uint32_t *)(v18 + v19 + 4));
      v2 = v29;
    }
  }
  v8 = dword_8F8530;
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
        v8 = dword_8F8530;
        dword_9B7C8C = 5;
      }
      if ( v15 )
        goto LABEL_45;
      if ( v28 != 0 )
      {
        result = sub_486C40(v8, v21);
LABEL_45:
        dword_9B7C8C = 4;
        return result;
      }
      if ( v27 != 0 )
      {
        v25 = sub_44A980(*((uint32_t *)this + 12));
        v24 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v25 + 16))(v25) + 68);
        v23 = *((uint32_t *)this + 12);
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v25 + 16))(v25);
        return sub_44BC30(2, 8, *(uint32_t *)(v22 + 4), v23, v24, v25);
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
// 0x50E380 CNRDStorageWindow__vmt4
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDStorageWindow__vmt4(uint32_t *Block, char a2)
{
  sub_50DED0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50E3B0 sub_50E3B0
// ------------------------------------------------------------
int /*thiscall*/ sub_50E3B0(uint32_t *this)
{
  uint32_t *v2; // eax
  int v3; // ebx
  uint32_t *v4; // edi
  int *v5; // edi
  void *v6; // eax
  uint32_t *v7; // ecx
  int result; // eax
  int v9; // edx
  unsigned int i; // ecx
  int v11; // edi
  unsigned int v12; // ebx
  uint32_t *v13; // edi
  int v14; // edi
  uint32_t *v15; // edi
  uint32_t *v16; // edi
  uint32_t *v17; // edi
  uint32_t *v18; // edi
  uint32_t *v19; // edi
  uint32_t *v20; // edi
  uint32_t *v21; // edi
  int *Block; // [esp+Ch] [ebp-10h]
  void *Blocka; // [esp+Ch] [ebp-10h]

  *(this + 10) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 188);
  v2 = operator new(0x10Cu);
  v3 = 0;
  if ( v2 != nullptr )
  {
    v4 = v2 + 1;
    *v2 = 2;
    `eh vector constructor iterator'(v2 + 1, 0x84u, 2, sub_46F750, sub_43C480);
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
  v6 = operator new(0x400u);
  v7 = (uint32_t *)*(this + 10);
  *(this + 9) = v6;
  Blocka = *(void **)(sub_418DD0(v7, 0xAu) + 24);
  result = *(uint32_t *)(sub_418DD0((uint32_t *)*(this + 10), 7u) + 24) + 2;
  v9 = result + 28;
  for ( i = 48; i < 0x430; i += 128 )
  {
    v11 = *(this + 9);
    v12 = i - 48;
    *(uint32_t *)(v11 + v12 + 4) = result;
    *(uint32_t *)(v11 + v12 + 12) = v9;
    v13 = (uint32_t *)(i - 48 + v11);
    *v13 = 15;
    v13[2] = 43;
    v14 = *(this + 9);
    *(uint32_t *)(v14 + v12 + 20) = result;
    *(uint32_t *)(v14 + v12 + 28) = v9;
    v15 = (uint32_t *)(v14 + i - 48 + 16);
    *v15 = 47;
    v15[2] = 75;
    v16 = (uint32_t *)(*(this + 9) + i - 16);
    v16[1] = result;
    v16[3] = v9;
    *v16 = 79;
    v16[2] = 107;
    v17 = (uint32_t *)(i + *(this + 9));
    v17[1] = result;
    v17[3] = v9;
    *v17 = 111;
    v17[2] = 139;
    v18 = (uint32_t *)(*(this + 9) + i + 16);
    v18[1] = result;
    v18[3] = v9;
    *v18 = 143;
    v18[2] = 171;
    v19 = (uint32_t *)(*(this + 9) + i + 32);
    v19[1] = result;
    v19[3] = v9;
    *v19 = 175;
    v19[2] = 203;
    v20 = (uint32_t *)(*(this + 9) + i + 48);
    v20[1] = result;
    v20[3] = v9;
    *v20 = 207;
    v20[2] = 235;
    v21 = (uint32_t *)(*(this + 9) + i + 64);
    v21[1] = result;
    v21[3] = v9;
    *v21 = 239;
    v21[2] = 267;
    result += (int)Blocka;
    v9 += (int)Blocka;
  }
  return result;
}


// ------------------------------------------------------------
// 0x50E5F0 nengine__CNButton__vmt0
// ------------------------------------------------------------
char */*thiscall*/ nengine__CNButton__vmt0(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(this, 0x84u, *((uint32_t *)this - 1), sub_43C480);
    if ( (a2 & 1) != 0 )
      j_j__free(this - 4);
    return this - 4;
  }
  else
  {
    sub_43C480(this);
    if ( (a2 & 1) != 0 )
      j__free(this);
    return this;
  }
}



// ------------------------------------------------------------
// 0x50E650 sub_50E650
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50E650(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  sub_5542C0();
  sub_5548B0(a2, 15);
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
// 0x50E730 sub_50E730
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
// 0x50E750 sub_50E750
// ------------------------------------------------------------
char /*thiscall*/ sub_50E750(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax

  LOBYTE(v4) = *((uint8_t *)this + 12);
  if ( (uint8_t)v4 != 0 )
  {
    sub_4938F0(*(this + 1));
    v5 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*this + 192))(*this);
    sub_491D00(dword_79C0B0, a2, a3 - v5, 0.0);
    v4 = *(this + 1);
    if ( *(int *)(v4 + 148) >= 1 )
    {
      if ( *((uint8_t *)this + 13) == 0 )
      {
        sub_4926A0(*(this + 2));
        *((uint8_t *)this + 13) = 1;
      }
      sub_4938F0(*(this + 2));
      v6 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*this + 192))(*this);
      LOBYTE(v4) = sub_491D00(dword_79C0B0, a2, a3 - v6, 0.0);
    }
  }
  return v4;
}



// ============================================================
// §D 0x50E7E0-0x50EB40 表情(emoticon)系统
// ============================================================
// ------------------------------------------------------------

// 0x50E7E0 sub_50E7E0 —— 表情标签反查器（unk_9B7D24 表 23 项，$END 结尾；
//   倒序逐长匹配 → 返回索引，未命中返回 23）
// ------------------------------------------------------------
int /*cdecl*/ sub_50E7E0(const char *a1)
{
  int *v1; // ebx
  int v2; // ebx
  size_t *v3; // ecx
  size_t v4; // eax
  const char *v5; // eax
  size_t v7; // [esp-10h] [ebp-20h]
  int v8; // [esp+4h] [ebp-Ch]
  int v9; // [esp+8h] [ebp-8h]
  int *v10; // [esp+Ch] [ebp-4h]

  v9 = strlen(a1);
  if ( v9 >= 0 )
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
            v7 = v4;
            v5 = (const char *)sub_41ACF0(v3);
            if ( strncmp(v5, &a1[v9], v7) == 0 )
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
      if ( --v9 >= 0 )
        continue;
      break;
    }
  }
  return 23;
}



// ------------------------------------------------------------
// 0x50E8D0 sub_50E8D0
// ------------------------------------------------------------
int /*thiscall*/ sub_50E8D0(uint32_t *this, int a2)
{
  int v3; // eax
  int result; // eax

  *this = a2;
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
// 0x50E950 sub_50E950
// ------------------------------------------------------------
int /*thiscall*/ sub_50E950(void ***this)
{
  int v2; // edi
  int result; // eax
  void **v4; // edi

  v2 = (int)*(this + 1);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 1));
    result = sub_657740(v2, 228);
  }
  v4 = *(this + 2);
  *(this + 1) = nullptr;
  if ( v4 != nullptr )
  {
    sub_42AF90(v4);
    result = sub_657740(v4, 228);
  }
  *(this + 2) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x50E9B0 sub_50E9B0
// ------------------------------------------------------------
char /*thiscall*/ sub_50E9B0(int this)
{
  int v2; // eax
  void **v3; // edi

  LOBYTE(v2) = *(uint8_t *)(this + 12);
  if ( (uint8_t)v2 != 0 )
  {
    v2 = *(uint32_t *)(this + 4);
    if ( *(uint8_t *)(v2 + 170) != 0 )
    {
      v3 = *(void ***)(this + 8);
      *(uint8_t *)(this + 12) = 0;
      if ( v3 != nullptr )
      {
        sub_42AF90(v3);
        LOBYTE(v2) = sub_657740(v3, 228);
      }
      *(uint32_t *)(this + 8) = 0;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x50EA00 sub_50EA00
// ------------------------------------------------------------
int /*thiscall*/ sub_50EA00(int this, int a2)
{
  void **v3; // edi
  int result; // eax

  if ( *(uint8_t *)(this + 12) != 0 )
  {
    v3 = *(void ***)(this + 8);
    *(uint8_t *)(this + 12) = 0;
    if ( v3 != nullptr )
    {
      sub_42AF90(v3);
      sub_657740(v3, 228);
    }
    *(uint32_t *)(this + 8) = 0;
  }
  sub_4926A0(*(uint32_t *)(this + 4));
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)off_792078[a2], 1);
  else
    result = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint32_t *)(this + 8) = result;
  *(uint8_t *)(this + 12) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x50EAA0 sub_50EAA0
// ------------------------------------------------------------
int /*thiscall*/ sub_50EAA0(uint32_t *this, const char *a2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*this + 80))(*this);
  if ( result != 0 )
  {
    result = sub_50E7E0(a2);
    if ( result != 23 )
      return sub_50EA00((int)this, result);
  }
  return result;
}



// ------------------------------------------------------------
// 0x50EAD0 sub_50EAD0
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
// 0x50EAF0 sub_50EAF0
// ------------------------------------------------------------
int /*thiscall*/ sub_50EAF0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 8);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 8) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x50EB10 sub_50EB10
// ------------------------------------------------------------
char /*thiscall*/ sub_50EB10(int this)
{
  int v2; // eax
  int v3; // edi

  LOBYTE(v2) = *(uint8_t *)(this + 40);
  if ( (uint8_t)v2 != 0 )
  {
    v3 = *(uint32_t *)(this + 28);
    v2 = sub_699000(this + 4);
    if ( v2 >= v3 )
      *(uint8_t *)(this + 40) = 0;
  }
  return v2;
}



// ============================================================
// §E 0x50EB40-0x50F1C0 UI 文本气泡与 CNText 族
// ============================================================
// ------------------------------------------------------------

// 0x50EB40 sub_50EB40 —— 表情气泡绘制（按行数拼 9-slice：id 63/64/65/66）
// ------------------------------------------------------------
void /*thiscall*/ sub_50EB40(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // ebx
  int v8; // esi
  int v9; // eax
  int v11; // eax
  bool v12; // cc
  int v13; // eax
  int v14; // esi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // [esp+4h] [ebp-4h]
  int v22; // [esp+10h] [ebp+8h]
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
    v5 = -10 - 12 * *(this + 13) + a2;
    v22 = v5;
    if ( *this != 0 )
    {
      v5 -= 14;
      v22 = v5;
    }
    v6 = *(this + 8);
    v7 = *(this + 14);
    *(uint32_t *)(v6 + 32) = v5 + 5;
    v8 = a3 - v7;
    v26 = v5 + 5;
    *(uint32_t *)(v6 + 36) = v8 + 6;
    v21 = v5;
    v9 = sub_418DD0(63);
    if ( v9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
        v9,
        v22,
        v8,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)a4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v23 = v26;
    v27 = 0;
    if ( (int)*(this + 11) > 0 )
    {
      do
      {
        v11 = sub_418DD0(64);
        if ( v11 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v11 + 128))(
            v11,
            v23,
            v8,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)a4 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        v12 = ++v27 < *(this + 11);
        v23 += 12;
      }
      while ( v12 );
    }
    v13 = sub_418DD0(65);
    if ( v13 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
        v13,
        v23,
        v8,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)a4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v14 = v8 + 5;
    for ( i = 0; i < *(this + 12); ++i )
    {
      v15 = sub_418DD0(66);
      if ( v15 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v15 + 128))(
          v15,
          v21,
          v14,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)a4 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v24 = v21 + 5;
      v28 = 0;
      if ( (int)*(this + 11) > 0 )
      {
        do
        {
          v16 = sub_418DD0(67);
          if ( v16 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v16 + 128))(
              v16,
              v24,
              v14,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)a4 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          v12 = ++v28 < *(this + 11);
          v24 += 12;
        }
        while ( v12 );
      }
      v17 = sub_418DD0(68);
      if ( v17 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v17 + 128))(
          v17,
          v24,
          v14,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)a4 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v14 += 13;
    }
    v18 = sub_418DD0(69);
    if ( v18 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v18 + 128))(
        v18,
        v21,
        v14,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)a4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v25 = v21 + 5;
    v29 = 0;
    if ( (int)*(this + 11) > 0 )
    {
      do
      {
        v19 = sub_418DD0(2 * (v29 == *(this + 13)) + 70);
        if ( v19 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v19 + 128))(
            v19,
            v25,
            v14,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)a4 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        v12 = ++v29 < *(this + 11);
        v25 += 12;
      }
      while ( v12 );
    }
    v20 = sub_418DD0(71);
    if ( v20 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v20 + 128))(
        v20,
        v25,
        v14,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)a4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    if ( a4 == 255 )
      sub_69D780(*(this + 8));
  }
}


// ------------------------------------------------------------
// 0x50EF20 sub_50EF20
// ------------------------------------------------------------
char /*thiscall*/ sub_50EF20(int *this, char *Format, int a3, int a4)
{
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // et2
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // edx
  bool v17; // zf
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  char result; // al
  char v22; // [esp+0h] [ebp-8h]

  sub_69D6C0(-1);
  sub_69DDB0(*(this + 8), Format, v22);
  v5 = *(this + 8);
  v6 = *(uint32_t *)(v5 + 16);
  v7 = v5 + 12;
  if ( v6 != 0 )
    v8 = (*(uint32_t *)(v7 + 8) - v6) >> 2;
  else
    v8 = 0;
  *(this + 12) = v8;
  if ( v8 != 1 || *(this + 16) != 0 )
    v9 = *(this + 15);
  else
    v9 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, Format);
  v11 = v9 % 12;
  v10 = v9 / 12;
  v12 = v11;
  if ( v11 != 0 )
    v12 = 1;
  v13 = v12 + v10;
  *(this + 11) = v13;
  if ( a3 != 0 || v13 < 5 )
    v14 = (v13 - 1) / 2;
  else
    v14 = 2;
  v15 = *this;
  v16 = 13 * *(this + 12) + 15;
  v17 = *this == 0;
  *(this + 13) = v14;
  *(this + 14) = v16;
  if ( !v17 )
  {
    *(this + 14) += (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 192))(v15) + 3;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*this + 40))(*this, 18) != 0 )
    {
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)*this + 360))(*this) == 0;
      v18 = *(this + 14);
      if ( v17 )
        v19 = v18 + 14;
      else
        v19 = v18 + 30;
      *(this + 14) = v19;
    }
  }
  v20 = (int)(this + 1);
  *((uint8_t *)this + 17) = 0;
  *((uint8_t *)this + 18) = 0;
  if ( a4 == -1 )
    result = sub_698F90(v20, 3000, 0);
  else
    result = sub_698F90(v20, a4, 0);
  *((uint8_t *)this + 40) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x50F040 sub_50F040
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
  sub_4015C0((void *)"vector<T> too long", 0x12u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x50F0B0 sub_50F0B0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_50F0B0(uint8_t *this, int a2, int a3, int a4)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNText;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  sub_69D4E0();
  sub_69D150(a2, a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x50F120 nengine__CNText__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNText__vmt0(void *Block, char a2)
{
  sub_50F150();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F150 sub_50F150
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
// 0x50F1C0 sub_50F1C0
// ------------------------------------------------------------
int /*thiscall*/ sub_50F1C0(uint32_t *this, void *Block, int a3, int a4)
{
  uint8_t *v5; // eax
  uint8_t *v6; // eax
  int v7; // eax
  int v8; // edx

  *this = Block;
  *(this + 15) = a3;
  v5 = operator new(0x60u);
  if ( v5 != nullptr )
    v6 = sub_50F0B0(v5, dword_79C0B0, 2048, a3);
  else
    v6 = nullptr;
  *(this + 8) = v6;
  *((uint32_t *)v6 + 14) = dword_99FCCC;
  *(uint32_t *)(*(this + 8) + 64) = 1;
  *(uint32_t *)(*(this + 8) + 80) = -1;
  *(uint32_t *)(*(this + 8) + 92) = a4;
  v7 = *(uint32_t *)(dword_99FCC8 + 20);
  v8 = *(uint32_t *)(v7 + 60);
  *(this + 16) = a4;
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
uint32_t */*thiscall*/ sub_50F270(uint32_t *this, int a2, int a3)
{
  sub_4B1030();
  *this = &vftbl_CNChangeMp;
  sub_602070(this);
  sub_602380(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x50F2D0 CNChangeMp__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNChangeMp__vmt0(void *Block, char a2)
{
  sub_50F300();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F300 sub_50F300
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
// 0x50F360 sub_50F360
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
  sub_4015C0((void *)"vector<T> too long", 0x12u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x50F3D0 sub_50F3D0
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
// 0x50F440 sub_50F440
// ------------------------------------------------------------
void /*thiscall*/ sub_50F440(int this, int a2, unsigned int a3, int a4)
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
      sub_50F360(this);
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v18 = *(uint32_t *)(this + 8);
      v20 = (v18 - a2) >> 3 < a3;
      v21 = 8 * a3;
      v30 = 8 * a3;
      v33 = v18;
      if ( v20 )
      {
        sub_44BD30(a2, v18, a2 + v21);
        v26 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 3);
        v25 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(v25, v26, v28);
        v22 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v22;
        sub_41FEB0(a2, v22 - v30, v28);
      }
      else
      {
        v23 = v18 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(v18 - v21, v18, v18);
        sub_44BD00(a2, v23, v33);
        sub_41FEB0(a2, a2 + v30, v28);
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
// 0x50F690 sub_50F690
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
// 0x50F710 CNActiveStatusStackable__vmt4
// ------------------------------------------------------------
void **/*thiscall*/ CNActiveStatusStackable__vmt4(void **Block, char a2)
{
  sub_50F690(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F740 sub_50F740
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
// 0x50F7C0 sub_50F7C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50F7C0(uint32_t *this, char a2)
{
  sub_50F740(this, a2);
  *this = &vftbl_CNIncreaseStatusStackable;
  return this;
}



// ------------------------------------------------------------
// 0x50F7F0 sub_50F7F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50F7F0(uint32_t *this, char a2)
{
  sub_50F740(this, a2);
  *this = &vftbl_CNItemScreamOfHysma;
  return this;
}



// ------------------------------------------------------------
// 0x50F810 CNItemScreamOfHysma__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNItemScreamOfHysma__vmt4(void *Block, char a2)
{
  sub_50F840();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F840 sub_50F840
// ------------------------------------------------------------
int /*thiscall*/ sub_50F840(uint32_t *this)
{
  *this = &vftbl_CNItemScreamOfHysma;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50F850 sub_50F850
// ------------------------------------------------------------
int /*thiscall*/ sub_50F850(int this, char a2, int a3, int a4)
{
  sub_50F740((uint32_t *)this, a2);
  *(uint32_t *)this = &vftbl_CNAppendageStackable;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint8_t *)(this + 192) = 1;
  *(uint32_t *)(this + 180) = 17;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  sub_602E40(this);
  sub_6032D0(a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x50F8E0 CNAppendageStackable__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNAppendageStackable__vmt4(void *Block, char a2)
{
  sub_50F910();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50F910 sub_50F910
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
// 0x50F990 sub_50F990
// ------------------------------------------------------------
int /*thiscall*/ sub_50F990(int this, char a2, int a3, int a4, int a5)
{
  sub_50F740((uint32_t *)this, a2);
  *(uint32_t *)this = &vftbl_CNAppendageStackable;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint8_t *)(this + 192) = 1;
  *(uint32_t *)(this + 180) = 17;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  sub_602E40(this);
  sub_603300(a3, a4, a5);
  return this;
}



// ------------------------------------------------------------
// 0x50FA30 sub_50FA30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FA30(uint32_t *this, char a2)
{
  sub_50F740(this, a2);
  *this = &vftbl_CNCoinOfFortune;
  return this;
}



// ------------------------------------------------------------
// 0x50FA50 CNCoinOfFortune__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNCoinOfFortune__vmt4(void *Block, char a2)
{
  sub_50FA80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FA80 sub_50FA80
// ------------------------------------------------------------
int /*thiscall*/ sub_50FA80(uint32_t *this)
{
  *this = &vftbl_CNCoinOfFortune;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FA90 sub_50FA90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FA90(uint32_t *this, char a2)
{
  sub_50F740(this, a2);
  *this = &vftbl_CNTouchOfRemy;
  return this;
}



// ------------------------------------------------------------
// 0x50FAB0 CNTouchOfRemy__vmt88
// ------------------------------------------------------------
int /*stdcall*/ CNTouchOfRemy__vmt88(int a1, int a2, void *Block)
{
  int result; // eax
  int v4; // edi
  int v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  float v8; // [esp+0h] [ebp-24h]
  int v9; // [esp+30h] [ebp+Ch]

  result = CNRDStackable__vmt88(a1, a2, Block);
  if ( a1 != 0 )
  {
    v9 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 740))(a1) * 0.30000001);
    v4 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 756))(a1) * 0.30000001);
    if ( operator new(0x80u) != nullptr )
    {
      v8 = (float)v9;
      v5 = sub_4D6810(LODWORD(v8), 1000, 0, 1);
    }
    else
    {
      v5 = 0;
    }
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v5 + 56))(v5, a1, a1, 0, 0, 0, -1);
    v6 = operator new(0x64u);
    if ( v6 != nullptr )
      v7 = sub_50F270(v6, v4, 1000);
    else
      v7 = nullptr;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*v7 + 56))(v7, a1, a1, 0, 0, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x50FBC0 CNTouchOfRemy__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNTouchOfRemy__vmt4(void *Block, char a2)
{
  sub_50FBF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FBF0 sub_50FBF0
// ------------------------------------------------------------
int /*thiscall*/ sub_50FBF0(uint32_t *this)
{
  *this = &vftbl_CNTouchOfRemy;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FC00 sub_50FC00
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FC00(uint32_t *this, char a2, int a3, int a4, int a5)
{
  sub_50F740(this, a2);
  *(this + 43) = a5;
  *this = &vftbl_CNRateHpMp;
  *(this + 41) = a3;
  *(this + 42) = a4;
  return this;
}



// ------------------------------------------------------------
// 0x50FC40 CNRateHpMp__vmt88
// ------------------------------------------------------------
int /*thiscall*/ CNRateHpMp__vmt88(int *this, int a2, void *Block, void *a4)
{
  int result; // eax
  uint32_t *v6; // eax
  int v7; // ebx
  uint32_t *v8; // eax
  int v9; // eax
  float v10; // [esp+0h] [ebp-28h]
  float v11; // [esp+0h] [ebp-28h]
  void *v12; // [esp+38h] [ebp+10h]
  void *v13; // [esp+38h] [ebp+10h]

  result = CNRDStackable__vmt88(a2, Block, a4);
  if ( a2 != 0 )
  {
    result = *(this + 41);
    if ( result != 0 )
    {
      if ( result == 1 )
      {
        v7 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2)
                              * ((double)*(this + 42)
                               * 0.0099999998));
        v8 = operator new(0x64u);
      }
      else
      {
        if ( result != 2 )
          return result;
        v13 = (void *)(uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2)
                                       * ((double)*(this + 42)
                                        * 0.0099999998));
        if ( operator new(0x80u) != nullptr )
        {
          v11 = (float)(int)v13;
          v9 = sub_4D6810(LODWORD(v11), *(this + 43), 0, 1);
        }
        else
        {
          v9 = 0;
        }
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v9 + 56))(
          v9,
          a2,
          a2,
          0,
          0,
          0,
          -1);
        v7 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2)
                              * ((double)*(this + 42)
                               * 0.0099999998));
        v8 = operator new(0x64u);
      }
      if ( v8 != nullptr )
      {
        v6 = sub_50F270(v8, v7, *(this + 43));
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*v6 + 56))(
                 v6,
                 a2,
                 a2,
                 0,
                 0,
                 0,
                 -1);
      }
    }
    else
    {
      v12 = (void *)(uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2)
                                     * ((double)*(this + 42)
                                      * 0.0099999998));
      if ( operator new(0x80u) != nullptr )
      {
        v10 = (float)(int)v12;
        v6 = (uint32_t *)sub_4D6810(LODWORD(v10), *(this + 43), 0, 1);
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*v6 + 56))(
                 v6,
                 a2,
                 a2,
                 0,
                 0,
                 0,
                 -1);
      }
    }
    v6 = nullptr;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*v6 + 56))(v6, a2, a2, 0, 0, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x50FE30 CNRateHpMp__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRateHpMp__vmt4(void *Block, char a2)
{
  sub_50FE60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FE60 sub_50FE60
// ------------------------------------------------------------
int /*thiscall*/ sub_50FE60(uint32_t *this)
{
  *this = &vftbl_CNRateHpMp;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FE70 sub_50FE70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FE70(uint32_t *this, char a2)
{
  sub_50F740(this, a2);
  *this = &vftbl_CNCallStorageBird;
  return this;
}



// ------------------------------------------------------------
// 0x50FE90 CNCallStorageBird__vmt88
// ------------------------------------------------------------
int /*stdcall*/ CNCallStorageBird__vmt88(int *a1, int a2, int a3)
{
  int result; // eax
  int v4; // edi
  int v5; // eax

  result = CNRDStackable__vmt88(a1, a2, a3);
  if ( a1 != nullptr && a1 == (int *)dword_8F7C04 )
  {
    v4 = *a1;
    v5 = sub_50D910();
    return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(
             a1,
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
// 0x50FEF0 CNCallStorageBird__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNCallStorageBird__vmt4(void *Block, char a2)
{
  sub_50FF20();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FF20 sub_50FF20
// ------------------------------------------------------------
int /*thiscall*/ sub_50FF20(uint32_t *this)
{
  *this = &vftbl_CNCallStorageBird;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FF30 sub_50FF30
// ------------------------------------------------------------
int /*thiscall*/ sub_50FF30(int this, char a2, int a3, int a4, char a5)
{
  sub_50F740((uint32_t *)this, a2);
  *(uint8_t *)(this + 172) = a5;
  *(uint32_t *)this = &vftbl_CNOmozzaOfWorld;
  *(uint32_t *)(this + 164) = a3;
  *(uint32_t *)(this + 168) = a4;
  return this;
}



// ------------------------------------------------------------
// 0x50FF70 CNOmozzaOfWorld__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNOmozzaOfWorld__vmt4(void *Block, char a2)
{
  sub_50FFA0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x50FFA0 sub_50FFA0
// ------------------------------------------------------------
int /*thiscall*/ sub_50FFA0(uint32_t *this)
{
  *this = &vftbl_CNOmozzaOfWorld;
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x50FFB0 sub_50FFB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FFB0(uint32_t *this, char a2)
{
  sub_50F740(this, a2);
  *this = &vftbl_CNUsableStackable;
  return this;
}



// ------------------------------------------------------------
// 0x50FFD0 CNIncreaseStatusStackable__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNIncreaseStatusStackable__vmt4(void *Block, char a2)
{
  sub_50F7E0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}

