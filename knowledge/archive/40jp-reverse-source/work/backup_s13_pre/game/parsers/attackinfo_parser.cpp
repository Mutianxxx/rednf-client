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
void /*thiscall*/ sub_50C140(int *this, unsigned int uArg2, char pszArg3, void *Block, int nArg5, int nArg6)  // sub_50C140 —— 16 字节元素向量 resize（截尾/追加双路）
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int fld_e22; // edx

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 4;  // fld_e1=this+4 宿主对象
  else
    fld_e2 = 0;
  if ( fld_e2 >= uArg2 )
  {
    if ( fld_e1 != 0 && uArg2 < (*(this + 2) - fld_e1) >> 4 )  // fld_e1=this+4 宿主对象
      sub_50BE50(this, (int *)&uArg2, fld_e1 + 16 * uArg2, *(this + 2));  // 调 sub_50BE50
  }
  else
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) >> 4;  // fld_e1=this+4 宿主对象
    else
      fld_e22 = 0;
    sub_50BEA0((int)this, *(this + 2), uArg2 - fld_e22, (int)&pszArg3);  // 调 sub_50BEA0
  }
  if ( Block != nullptr )
    j__free(Block);  // 释放堆块
}



// ------------------------------------------------------------
// 0x50C1F0 sub_50C1F0 —— 16 字节元素向量尾部追加（满则扩容）
//   有富余 → ·sub_4C2BA0 就地按 nArg2 复制构造并 +16 递增；否则 ·sub_4C3DC0 扩容追加。
// ------------------------------------------------------------
int /*thiscall*/ sub_50C1F0(uint32_t *this, int nArg2)  // sub_50C1F0 —— 16 字节元素向量尾部追加（满则扩容）
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  int result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 4;  // fld_e1=this+4 宿主对象
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 4 )  // fld_e1=this+4 宿主对象
    return sub_4C3DC0(*(this + 2), 1, nArg2);  // 调 sub_4C3DC0
  fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
  result = sub_4C2BA0(fld_e22, 1, nArg2);  // 调 sub_4C2BA0
  *(this + 2) = fld_e22 + 16;  // 写字段 this+2 ← fld_e22 + 16
  return result;
}



// ------------------------------------------------------------
// 0x50C260 sub_50C260 —— 16 字节元素向量 resize 缺省值封装
//   栈临时默认值经 ·sub_50C140（Block=null）转发。
// ------------------------------------------------------------
void /*thiscall*/ sub_50C260(int *this, unsigned int uArg2)  // sub_50C260 —— 16 字节元素向量 resize 缺省值封装
{
  char v2; // [esp+0h] [ebp-14h] BYREF
  char *v3; // [esp+10h] [ebp-4h]

  v3 = &v2;
  sub_50C140(this, uArg2, v2, nullptr, 0, 0);  // sub_50C140 —— 16 字节元素向量 resize（截尾/追加双路）
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
char /*cdecl*/ sub_50C290(int pArg1, int nArg2)  // sub_50C290 —— ★★ 职业(growtype/角色成长)定义解析器（67 标签，本文件唯一大 [tag] 解析器）
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_442A10((char)&unk_9B7730, nArg2);  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result == 0 )
    return result;
  sub_4D1EA0(pArg1);  // 调 sub_4D1EA0
  sub_443300(pArg1 + 1640, "%s%s", (char)&unk_9B7730);  // 调 格式化串取目录前缀
  v49 = 15;
  v48 = 0;
  LOBYTE(Block) = 0;
  v51 = 0;
  v45 = nullptr;  // v45 = nullptr 空指针
  sub_41BFE0(&v45, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  v40 = (void *)(pArg1 + 628);
  v3 = pArg1 + 152;  // 计算 v3 = pArg1 + 152
  LOBYTE(v51) = 1;
  v44 = 0;
  v42 = pArg1 + 152;  // 计算 v42 = pArg1 + 152
  v41 = (void *)(pArg1 + 724);
  if ( (uint8_t)sub_443430(v46) != 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
  {
    while ( 1 )  // 当 1 循环
    {
      sub_442B20(v46);  // sub_442B20 —— 国家码标签配对校验（void）
      if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[job]", 5u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        v4 = sub_41ACF0(&v45);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        *(uint32_t *)pArg1 = sub_4426A0(v4);  // 调 ：→索引（[swordman]/[fighter]/[gunner]/[mage]）
        goto LABEL_161;  // 跳转 LABEL_161
      }
      if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[growtype name]", 0xFu) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[width]", 7u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          *(uint32_t *)(pArg1 + 144) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          *(uint32_t *)(pArg1 + 148) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( sub_40BF00((std::_String_base *)v46, 0, v48, "[jump speed]", 0xCu) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          *(uint32_t *)(pArg1 + 820) = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[initial value]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v42 = pArg1 + 152;  // 计算 v42 = pArg1 + 152
          v40 = (void *)(pArg1 + 628);
          v41 = (void *)(pArg1 + 724);
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 1]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v42 = pArg1 + 231;  // 计算 v42 = pArg1 + 231
          v40 = (void *)(pArg1 + 644);
          v41 = (void *)(pArg1 + 740);
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 2]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v42 = pArg1 + 310;  // 计算 v42 = pArg1 + 310
          v40 = (void *)(pArg1 + 660);
          v41 = (void *)(pArg1 + 756);
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 3]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v42 = pArg1 + 389;  // 计算 v42 = pArg1 + 389
          v40 = (void *)(pArg1 + 676);
          v41 = (void *)(pArg1 + 772);
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 4]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v42 = pArg1 + 468;  // 计算 v42 = pArg1 + 468
          v40 = (void *)(pArg1 + 692);
          v41 = (void *)(pArg1 + 788);
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[growtype 5]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v42 = pArg1 + 547;  // 计算 v42 = pArg1 + 547
          v40 = (void *)(pArg1 + 708);
          v41 = (void *)(pArg1 + 804);
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[HP MAX]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v15 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint32_t *)v3 = sub_432F40(v15);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[MP MAX]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v16 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint32_t *)(v3 + 4) = sub_432F40(v16);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[physical attack]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v17 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 8) = sub_432F40(v17);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[physical defense]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v18 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 10) = sub_432F40(v18);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[magical attack]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v19 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 12) = sub_432F40(v19);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[magical defense]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v20 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 14) = sub_432F40(v20);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[fire resistance]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v21 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 16) = sub_432F40(v21);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[water resistance]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v22 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 18) = sub_432F40(v22);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[dark resistance]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v23 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 20) = sub_432F40(v23);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[light resistance]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v24 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 22) = sub_432F40(v24);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[inventory limit]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v25 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint32_t *)(v3 + 56) = sub_432F40(v25);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[HP regen speed]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v26 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 60) = sub_432F40(v26);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[MP regen speed]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v27 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 62) = sub_432F40(v27);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[move speed]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v28 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 64) = sub_432F40(v28);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[attack speed]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v29 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 66) = sub_432F40(v29);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[cast speed]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v30 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 68) = sub_432F40(v30);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[hit recovery]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v31 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 70) = sub_432F40(v31);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[jump power]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v32 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint16_t *)(v3 + 72) = sub_432F40(v32);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[weight]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          v33 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
          *(uint32_t *)(v3 + 74) = sub_432F40(v33);  // sub_432F40 —— 结果 = 舍入取整（float → int）
          goto LABEL_161;  // 跳转 LABEL_161
        }
        if ( (uint8_t)sub_423300(v46, "[skill]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          sub_5E5260((void **)v40);  // 调 sub_5E5260
          for ( i = sub_4423D0(&v44); v44 != 0; i = sub_4423D0(&v44) )  // sub_4423D0 —— [LOOP] → 动画对象+160；sub_4423D0 —— [LOOP] → 动画对象+160
          {
            v8 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
            v35[0] = i;
            v35[1] = v8;
            sub_474950(v35);  // sub_474950 —— 调用 sub_474950
          }
        }
        else if ( (uint8_t)sub_423300(v46, "[category]") != 0 )  // sub_423300 —— [end] → 解析结束
        {
          sub_5E5260((void **)v41);  // 调 sub_5E5260
          if ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
          {
            v9 = v41;
            do
            {
              v10 = 0.0;  // 浮点常量 v10 ← 0.0
              *(float *)&v43 = 0.0;
              while ( !sub_43BCF0(&v45, off_791F80[LODWORD(v10)]) )  // sub_43BCF0 —— 字符串 “[free]”
              {
                ++LODWORD(v10);
                if ( SLODWORD(v10) >= 22 )  // 若 SLODWORD(v10) >= 22
                {
                  *(float *)&v43 = v10;
                  goto LABEL_77;  // 跳转 LABEL_77
                }
              }
              *(float *)&v43 = v10;
              sub_431230((int)v9, &v43);  // sub_431230 —— uint32 vector push_back
LABEL_77:
              ;
            }
            while ( sub_442E10() != 0 );  // 【RDARScriptStringManager 入口（::ERROR::input…】
          }
        }
        else
        {
          if ( (uint8_t)sub_423300(v46, "[waiting motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[move motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[sit motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[damage motion 1]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[damage motion 2]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[down motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[overturn motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[jump motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[jumpattack motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[rest motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[throw motion 1-1]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[throw motion 1-2]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[throw motion 2-1]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[throw motion 2-2]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[throw motion 3-1]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[throw motion 3-2]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[throw motion 4-1]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[throw motion 4-2]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[dash motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[dashattack motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[getitem motion]") != 0  // sub_423300 —— [end] → 解析结束
            || (uint8_t)sub_423300(v46, "[buff motion]") != 0 )  // sub_423300 —— [end] → 解析结束
          {
LABEL_122:
            sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
            goto LABEL_161;  // 跳转 LABEL_161
          }
          if ( (uint8_t)sub_423300(v46, "[attack motion]") != 0 )  // sub_423300 —— [end] → 解析结束
          {
            sub_4017E0(pArg1 + 1440);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              sub_420BB0(&v45);  // sub_420BB0 —— vector push_back（4 字节元素）
          }
          else if ( (uint8_t)sub_423300(v46, "[etc motion]") != 0 )  // sub_423300 —— [end] → 解析结束
          {
            sub_4017E0(pArg1 + 1456);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
            while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              sub_420BB0(&v45);  // sub_420BB0 —— vector push_back（4 字节元素）
          }
          else
          {
            if ( (uint8_t)sub_423300(v46, "[jumpattack info]") != 0  // sub_423300 —— [end] → 解析结束
              || (uint8_t)sub_423300(v46, "[dashattack info]") != 0 )  // sub_423300 —— [end] → 解析结束
            {
              goto LABEL_122;  // 跳转 LABEL_122
            }
            if ( (uint8_t)sub_423300(v46, "[attack info]") != 0 )  // sub_423300 —— [end] → 解析结束
            {
              sub_4017E0(pArg1 + 1528);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
              while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                sub_420BB0(&v45);  // sub_420BB0 —— vector push_back（4 字节元素）
            }
            else if ( (uint8_t)sub_423300(v46, "[etc attack info]") != 0 )  // sub_423300 —— [end] → 解析结束
            {
              sub_4017E0(pArg1 + 1544);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
              while ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                sub_420BB0(&v45);  // sub_420BB0 —— vector push_back（4 字节元素）
            }
            else if ( (uint8_t)sub_423300(v46, "[weapon wav]") != 0 )  // sub_423300 —— [end] → 解析结束
            {
              v11 = nullptr;  // v11 = nullptr 空指针
              v37 = nullptr;  // v37 = nullptr 空指针
              v38 = nullptr;  // v38 = nullptr 空指针
              v39 = 0;
              LOBYTE(v51) = 2;
              if ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              {
                do
                  sub_420BB0(&v45);  // sub_420BB0 —— vector push_back（4 字节元素）
                while ( sub_442E10() != 0 );  // 【RDARScriptStringManager 入口（::ERROR::input…】
                v11 = v37;
              }
              sub_50C1F0(v36);  // sub_50C1F0 —— 16 字节元素向量尾部追加（满则扩容）
              LOBYTE(v51) = 1;
              if ( v11 != nullptr )
              {
                for ( j = v11; j != v38; ++j )  // 遍历计次循环（j != v38）
                  sub_41B010(j);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
                j__free(v11);  // 释放堆块
              }
              v37 = nullptr;  // v37 = nullptr 空指针
              v38 = nullptr;  // v38 = nullptr 空指针
              v39 = 0;
            }
            else
            {
              if ( (uint8_t)sub_423300(v46, "[weapon hit info]") != 0 )  // sub_423300 —— [end] → 解析结束
              {
                sub_5E5260((void **)(pArg1 + 1576));  // 调 sub_5E5260
                sub_5E5260((void **)(pArg1 + 1592));  // 调 sub_5E5260
                sub_5E5260((void **)(pArg1 + 1608));  // 调 sub_5E5260
                sub_5E5260((void **)(pArg1 + 1624));  // 调 sub_5E5260
                if ( sub_442E10() == 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                  goto LABEL_161;  // 跳转 LABEL_161
                while ( 2 )  // 当 2 循环
                {
                  if ( sub_43BCF0(&v45, "[blow]") )  // sub_43BCF0 —— 字符串 “[free]”
                  {
                    *(float *)&v43 = 0.0;
                    goto LABEL_150;  // 跳转 LABEL_150
                  }
                  if ( sub_43BCF0(&v45, "[cut]") )  // sub_43BCF0 —— 字符串 “[free]”
                  {
                    v43 = 1;
                    sub_431230(pArg1 + 1576, &v43);  // sub_431230 —— uint32 vector push_back
                  }
                  else if ( sub_43BCF0(&v45, "[burn]") )  // sub_43BCF0 —— 字符串 “[free]”
                  {
                    v43 = 2;
                    sub_431230(pArg1 + 1576, &v43);  // sub_431230 —— uint32 vector push_back
                  }
                  else if ( sub_43BCF0(&v45, "[etc]") )  // sub_43BCF0 —— 字符串 “[free]”
                  {
                    v43 = 3;
LABEL_150:
                    sub_431230(pArg1 + 1576, &v43);  // sub_431230 —— uint32 vector push_back
                  }
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                  if ( sub_43BCF0(&v45, "[no blood]") )  // sub_43BCF0 —— 字符串 “[free]”
                  {
                    *(float *)&v43 = 0.0;
                    sub_431230(pArg1 + 1592, &v43);  // sub_431230 —— uint32 vector push_back
                  }
                  else if ( sub_43BCF0(&v45, "[blood]") )  // sub_43BCF0 —— 字符串 “[free]”
                  {
                    v43 = 1;
                    sub_431230(pArg1 + 1592, &v43);  // sub_431230 —— uint32 vector push_back
                  }
                  *(float *)&v43 = COERCE_FLOAT(sub_4423D0(nullptr));  // sub_4423D0 —— [LOOP] → 动画对象+160
                  sub_431230(pArg1 + 1608, &v43);  // sub_431230 —— uint32 vector push_back
                  *(float *)&v43 = sub_442480(nullptr);  // sub_442480 —— 脚本 token 数值解析（double 版）
                  sub_5020D0(&v43);  // 调 sub_5020D0
                  if ( sub_442E10() == 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    goto LABEL_161;  // 跳转 LABEL_161
                  continue;
                }
              }
              off_791FD82 = off_791FD8;
              v14 = (uint16_t *)(v42 + 24);
              do
              {
                if ( (uint8_t)sub_423300(v46, *off_791FD82) != 0 )  // sub_423300 —— [end] → 解析结束
                {
                  v34 = sub_442480(nullptr) * 10.0;  // sub_442480 —— 脚本 token 数值解析（double 版）
                  *v14 = sub_432F40(v34);  // sub_432F40 —— 结果 = 舍入取整（float → int）
                }
                ++off_791FD82;  // 计数自增 off_791FD82
                ++v14;  // 计数自增 v14
              }
              while ( (int)off_791FD82 < (int)off_792018 );  // 当 (int)off_791FD82 < (int)off_792018 循环
            }
          }
        }
      }
      else
      {
        v5 = pArg1 + 4;  // 计算 v5 = pArg1 + 4
        for ( k = 5; k != 0; --k )  // 遍历计次循环（k != 0）
        {
          sub_443370();  // sub_443370 —— [name] → 对象+0x04 名称串
          v5 += 28;
        }
      }
LABEL_161:
      if ( (uint8_t)sub_443430(v46) == 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
        break;
      v3 = v42;
    }
  }
  LOBYTE(v51) = 0;
  sub_41B010(&v45);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  if ( v49 >= 0x10 )
    j__free(Block);  // 释放堆块
  return 1;
}


// ============================================================
// §C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取）
// ============================================================

// ------------------------------------------------------------
// 0x50D260 sub_50D260 —— 仓储物品表加载器（[item] 表：每行 44 字节 = 11 个描述符；
//   按索引追加 sub_509B70 / 越界补齐 sub_509890）
// ------------------------------------------------------------
char /*cdecl*/ sub_50D260(char *pszArg1, int nArg2)  // 函数: 仓储物品表加载器（[item] 表：每行 44 字节 = 11 个描述符；
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
  v3 = byte_9B7830 - pszArg1;  // 计算 v3 = byte_9B7830 - pszArg1
  do
  {
    v4 = *pszArg12;
    pszArg12[v3] = *pszArg12;  // pszArg12[v3] 写入 *pszArg12
    ++pszArg12;  // 计数自增 pszArg12
  }
  while ( v4 != 0 );  // 循环直到 v4 != 0
  if ( byte_9B782F[strlen(byte_9B7830)] != 92 && byte_9B782F[strlen(byte_9B7830)] != 47 )  // 若 byte_9B782F[strlen(byte_9B7830)] != 92 && byte_9B782F[strlen(b..
    *(uint16_t *)&byte_9B7830[strlen(byte_9B7830)] = 92;  // 调 strlen（求串长）
  if ( (uint8_t)sub_443C40((int)&unk_9B7C30, (char)byte_9B7830, nArg2) != 0 )  // sub_443C40 —— 脚本文件列表装表
  {
    sub_50C260(3);  // sub_50C260 —— 16 字节元素向量 resize 缺省值封装
    v5 = (int *)off_792018;
    v20 = 0;
    off_7920182 = off_792018;  // off_7920182 —— [esp+64h] [ebp-10h]
    while ( (uint8_t)sub_442A10((char)byte_9B7830, *v5) != 0 )  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
    {
      v6 = 0;
      HIBYTE(pszArg1) = 0;
      memset(Block, 0, sizeof(Block));  // 调 memset 按字节填充
      v19 = 0;
      v7 = sub_4423D0((uint8_t *)&pszArg1 + 3);  // sub_4423D0 —— [LOOP] → 动画对象+160
      if ( HIBYTE(pszArg1) != 0 )  // 若 HIBYTE(pszArg1) != 0
      {
        v18 = 0;
        do
        {
          Block[0] = v7;
          Block[3] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          Block[4] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          Block[5] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          Block[6] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          Block[1] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          Block[2] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          Block[7] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          Block[8] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          Block[9] = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v8 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
          v9 = (char *)dword_9B7C64 + v20;
          Block[10] = v8;
          v10 = *(uint32_t *)((char *)dword_9B7C64 + v20 + 4);
          if ( v10 != 0 )
            v11 = (*((uint32_t *)v9 + 2) - v10) / 44;
          else
            v11 = 0;
          if ( v6 == v11 )
          {
            sub_509B70(Block);  // 调 sub_509B70
          }
          else
          {
            v12 = *((uint32_t *)v9 + 1);  // 读字段 v12 = v9[1]
            if ( v12 != 0 )
              v13 = (*((uint32_t *)v9 + 2) - v12) / 44;
            else
              v13 = 0;
            if ( v6 > v13 )
            {
              memset(pBuf, 0, sizeof(pBuf));  // 调 memset 按字节填充
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
            qmemcpy((void *)(v18 + *(uint32_t *)((char *)dword_9B7C64 + v20 + 4)), Block, 44);  // 调 qmemcpy 内联块拷贝
            v6 = v19;
          }
          v19 = ++v6;
          v18 += 44;
          v7 = sub_4423D0((uint8_t *)&pszArg1 + 3);  // sub_4423D0 —— [LOOP] → 动画对象+160
        }
        while ( HIBYTE(pszArg1) != 0 );  // 当 HIBYTE(pszArg1) != 0 循环
        v5 = (int *)off_7920182;  // off_7920182 —— [esp+64h] [ebp-10h]
      }
      off_7920182 = (char **)++v5;  // off_7920182 —— [esp+64h] [ebp-10h]
      v20 += 16;
      if ( (int)v5 >= (int)&dword_792024 )  // 若 (int)v5 >= (int)&dword_792024
        return 1;
    }
  }
  return 0;
}


// ------------------------------------------------------------
// 0x50D4E0 sub_50D4E0 —— IRDPopupWindow 析构核心（基类清理 5542F0）
//   挂回 vftbl_IRDPopupWindow 后转 ·sub_5542F0；配 ·0x50D4F0 带释放标志的 vmt4 变体。
// ------------------------------------------------------------
int /*thiscall*/ sub_50D4E0(uint32_t *this)  // sub_50D4E0 —— IRDPopupWindow 析构核心（基类清理 5542F0）
{
  *this = &vftbl_IRDPopupWindow;  // 装虚表/取地址：← vftbl_IRDPopupWindow
  return sub_5542F0();  // sub_5542F0 —— 窗口页数据 2（22 行）
}



// ------------------------------------------------------------
// 0x50D4F0 IRDPopupWindow__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50D4E0 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
uint32_t */*thiscall*/ IRDPopupWindow__vmt4(uint32_t *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  *Block = &vftbl_IRDPopupWindow;  // 装虚表/取地址：← vftbl_IRDPopupWindow
  sub_5542F0();  // sub_5542F0 —— 窗口页数据 2（22 行）
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50D520 sub_50D520 —— 双串槽析构（+14 与 +0）
//   两处串槽经 ·sub_41A580 释放（+14 先于 +0）。
// ------------------------------------------------------------
void /*thiscall*/ sub_50D520(char *this)  // sub_50D520 —— 双串槽析构（+14 与 +0）
{
  sub_41A580(this + 14);  // sub_41A580 —— crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this);  // sub_41A580 —— crypt4byte 析构（vftable 复位 + 实例计数递减）
}



// ------------------------------------------------------------
// 0x50D570 sub_50D570 —— 仓储窗口按钮组释放与槽位游标复位
//   this+44 起 2 个 132 字节按钮经 vt+8 析构、eh 数组（flag 3）随后回收，this+36 数组 free；
//   清零 +36..+52（游标 +48 → -1）；全局窗口态 dword_9B7C8C 为 0 时置 5 并清 dword_9B7C80/84。
// ------------------------------------------------------------
int /*thiscall*/ sub_50D570(uint32_t *this)  // sub_50D570 —— 仓储窗口按钮组释放与槽位游标复位
{
  int i; // esi
  void (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  void *fld_e9; // eax
  int result; // eax

  for ( i = 0; i < 264; i += 132 )  // 循环：i = 0; i < 264; i += 132
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)(*(this + 11) + i) + 8))(*(this + 11) + i);  // 调用虚函数槽 +8
  fld_e11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( fld_e11 != nullptr )
  {
    if ( *(fld_e11 - 1) != nullptr )  // 若 *(fld_e11 - 1) != nullptr
      (**fld_e11)(fld_e11, 3);
    else
      j_j__free(fld_e11 - 1);  // 调 j__free
  }
  fld_e9 = (void *)*(this + 9);
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  if ( fld_e9 != nullptr )
    j_j__free(fld_e9);  // 调 j__free
  *(this + 9) = 0;  // 写字段 this+9 ← 0
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  *(this + 12) = -1;  // 写字段 this+12（nSkillRec12） ← -1
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
void */*thiscall*/ CNRDStorageWindow__vmt10(uint32_t **this)  // 仓储窗口关闭（SAFE_CLOSE 音效）
{
  if ( dword_9B88D0 != 0 && dword_795378 == 6 )  // 判定 dword_9B88D0 != 0 且 dword_795378 == 6
    sub_44E850(*(this + 4), 26);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
  if ( dword_9B7C88 != 0 )
  {
    sub_601D40();  // sub_601D40 —— 状态 3 装配
    dword_9B7C88 = 0;
  }
  return sub_432EA0("SAFE_CLOSE", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
}



// ------------------------------------------------------------
// 0x50D660 sub_50D660 —— 冷却时间比较器（剩余毫秒 ×0.001 秒上屏）
//   v3 = 目标时刻 − dword_8F8530 时间基 − nArg1；v3<0 且 pszArg2 非零时取 1164 号文案 sprintf 后经
//   ·sub_44E8D0 type 0x1B 上屏（|v3|×0.001 秒）；返回 v3<0。
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_50D660(int nArg1, char pszArg2)  // sub_50D660 —— 结果 = 冷却时间比较器（剩余毫秒 ×0.001 秒上屏）
{
  int v2; // eax
  int v3; // esi
  const char *v4; // eax
  char Buffer[1024]; // [esp+Ch] [ebp-404h] BYREF
  int dword_796E502; // [esp+40Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v2 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v3 = sub_41A5E0((unsigned int)&dword_9B7C9E[8 * v2]) - *((uint32_t *)dword_8F8530 + 1) - nArg1;  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  if ( v3 < 0 && pszArg2 != 0 )
  {
    v4 = (const char *)sub_422E70(1164);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v4, (double)(int)abs32(v3) * 0.001);  // 调 sprintf 格式化
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
  }
  return v3 < 0;
}



// ------------------------------------------------------------
// 0x50D710 sub_50D710 —— 仓储窗口 process_move 落点判定与移动分派
//   move 2：·sub_486820 拒绝提示；3/4：槽内对象校验（vt+20/+132）→ 等级 6 提示 1165、堆叠 >1 走
//   ·sub_540DE0 摊位流程、冷却经 ·sub_50D660 后 ·sub_4866D0 请求 op 19；8：·sub_486530 双槽交换；
//   未知码 → 抛 CNRDStorageWindow::process_move() - Unsupported move 文案。
// ------------------------------------------------------------
int /*thiscall*/ sub_50D710(int *this, int *pDwArg2)  // sub_50D710 —— 仓储窗口 process_move 落点判定与移动分派
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
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, pDwArg2[2]);  // 虚调用 vt+792（dword_8F7C04）角色槽物品取
    pObj = result;
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 16))(result);  // 虚调用 vt+16（result 虚表槽）
      if ( *(uint32_t *)(result + 4) == pDwArg2[1] )  // 若 *(uint32_t *)(result + 4) == pDwArg2[1]
      {
        v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);  // 虚调用 vt+172（pObj 虚表槽）
        return sub_486820(*(this + 12), *v5, 1);  // sub_486820 —— 施放拒绝提示（ALERT_1 音效 + sub_485510）
      }
    }
  }
  else
  {
    switch ( result )  // 分支：按 result 分派
    {
      case 3:  // case 3 分派（§C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取））
      case 4:  // case 4 分派（§C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取））
        result = pDwArg2[2];
        if ( result < *((uint32_t *)dword_8F852C + 2) )  // 若 result < *((uint32_t *)dword_8F852C + 2)
        {
          v7 = *((uint32_t *)dword_8F852C + 3);  // 读字段 v7 = dword_8F852C[3]
          pObj2 = *(uint32_t *)(v7 + 4 * result);
          if ( pObj2 != 0 )
          {
            result = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj2 + 16))(*(uint32_t *)(v7 + 4 * result)) + 4);  // 虚调用 vt+16（pObj2 虚表槽）
            if ( result == pDwArg2[1] )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 20))(pObj2, 1) != 0  // 虚调用 vt+20（pObj2）条件位掩码测试(273受击/17有血/65机械)
                && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 132))(pObj2) == 6 )  // 虚调用 vt+132（pObj2 虚表槽）
              {
                v9 = sub_422E70(1165);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
                return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v9, 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
              }
              else if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 20))(pObj2, 1) != 0  // 虚调用 vt+20（pObj2）条件位掩码测试(273受击/17有血/65机械)
                     && (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2) > 1 )  // 虚调用 vt+44（pObj2 虚表槽）
              {
                return sub_540DE0(1, 0, pDwArg2[2], 2, *(this + 12), 0, 0);  // sub_540DE0 —— 摊位列表构建（203 行：540A10/62EE70/540A50/541A30/542AB0 + 484FA0/48FCA0/48FD70 窗口件）
              }
              else
              {
                v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2);  // 虚调用 vt+36（pObj2 虚表槽）
                result = sub_50D660(v10, 1);  // sub_50D660 —— 结果 = 冷却时间比较器（剩余毫秒 ×0.001 秒上屏）
                if ( (uint8_t)result == 0 )
                {
                  fld_e12 = *(this + 12);  // 读字段 fld_e12 = this+12（nSkillRec12）
                  dword_8F85302 = dword_8F8530;  // dword_8F85302 —— [esp-8h] [ebp-14h]
                  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2);  // 虚调用 vt+44（pObj2 虚表槽）
                  return sub_4866D0(pDwArg2[2], v11, dword_8F85302, fld_e12);  // sub_4866D0 —— 请求 op 19 带来源对象（等级 + 来源容器）
                }
              }
            }
          }
        }
        break;
      case 9:  // case 9 分派（§C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取））
        break;
      case 8:  // case 8 分派（§C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取））
        result = sub_44A980(pDwArg2[2]);  // sub_44A980 —— 结果 = 带界索引 getter
        if ( result != 0 )
        {
          result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 16))(result) + 4);  // 虚调用 vt+16（result 虚表槽）
          if ( result == pDwArg2[1] )
          {
            result = *(this + 12);  // 读字段 result = this+12（nSkillRec12）
            v6 = pDwArg2[2];
            if ( result != v6 )  // result=this+12 nSkillRec12
              return sub_486530(result, v6, 1);  // sub_486530 —— 请求 op 19：两槽交换
          }
        }
        break;
      case 7:  // case 7 分派（§C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取））
        break;
      default:
        return off_77F3FC("CNRDStorageWindow::process_move() - Unsupported move");  // off_77F3FC —— 日志打印（printf 风格）
    }
  }
  return result;  // result=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x50D8F0 sub_50D8F0 —— 当前档位冷却表取值
//   按 dword_9B7D10 当前档位索引 dword_9B7CAC 表首字段。
// ------------------------------------------------------------
int sub_50D8F0()  // sub_50D8F0 —— 结果 = 当前档位冷却表取值
{
  return dword_9B7CAC[8 * sub_41A5E0((unsigned int)&unk_9B7D10)];  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x50D910 sub_50D910 —— 当前档位号读取
//   返回 dword_9B7D10 当前值（·0x50D8F0/·0x50D980 的索引基）。
// ------------------------------------------------------------
int sub_50D910()  // sub_50D910 —— 结果 = 当前档位号读取
{
  return sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x50D920 sub_50D920 —— 仓储栏类型设置（非法档位报错）
//   遍历档位表（步长 8）比对 nArg1，命中且仍在 [dword_9B7C90, dword_9B7D10) 区内时写回 dword_9B7D10；
//   否则按 CNRDStorageWindow::set_storage_type - Abnormal storage type 文案报错。
// ------------------------------------------------------------
int /*cdecl*/ sub_50D920(int nArg1)  // sub_50D920 —— 仓储栏类型设置（非法档位报错）
{
  int v1; // edi
  int *dword_9B7C902; // esi
  int result; // eax
  int v4; // edx

  v1 = 0;
  dword_9B7C902 = dword_9B7C90;
  do
  {
    result = sub_41A5E0((unsigned int)dword_9B7C902);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == nArg1 )
    {
      if ( (int)dword_9B7C902 < (int)dword_9B7C90 || (int)dword_9B7C902 >= (int)dword_9B7D10 )  // 若 (int)dword_9B7C902 < (int)dword_9B7C90 || (int)dword_9B7C902 >..
        result = off_77F3FC("CNRDStorageWindow::set_storage_type - Abnormal storage type %d", v1);  // off_77F3FC —— 日志打印（printf 风格）
      else
        result = sub_41A590((unsigned int)dword_9B7D10, v4, v1);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
    dword_9B7C902 += 8;
    ++v1;  // 计数自增 v1
  }
  while ( (int)dword_9B7C902 < (int)dword_9B7D10 );  // 当 (int)dword_9B7C902 < (int)dword_9B7D10 循环
  return result;
}



// ------------------------------------------------------------
// 0x50D980 sub_50D980 —— 当前档位行数读取
//   返回 dword_9B7C90[8×当前档位]（每档 8 双字记录）。
// ------------------------------------------------------------
int sub_50D980()  // sub_50D980 —— 当前档位行数读取
{
  int v0; // eax

  v0 = sub_41A5E0((unsigned int)dword_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A5E0((unsigned int)&dword_9B7C90[8 * v0]);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = *(this + 2);  // 读字段 result = this+2
  if ( nArg2 == result )  // result=this+8 物品 id
  {
    v4 = *(uint32_t *)(result + 24);  // 读字段 v4 = result+24（nPageMax）
    v5 = *(uint32_t *)(result + 20);  // 读字段 v5 = result+20（nPage）
    y = ::pt.y;
    v45 = v4;
    pt.x = ::pt.x;
    v6 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pObj3 = sub_418DD0(dword_792024[3 * v6]);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v5, v4, dword_79C0B0);  // 虚调用 vt+152（pObj3）取值(参数)
    v8 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v9 = (unsigned int)sub_41A5E0((unsigned int)&dword_9B7C90[8 * v8]) >> 3;  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pt.y = v9;
    v10 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    if ( (sub_41A5E0((unsigned int)&dword_9B7C90[8 * v10]) & 7) != 0 )  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      pt.y = ++v9;
    if ( v9 > 8 )
    {
      off_77F3FC("CNRDStorageWindow::Proc - Too many lines %d", v9);  // off_77F3FC —— 日志打印（printf 风格）
      pt.y = 8;
    }
    v11 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v12 = v45 + *(uint32_t *)(sub_418DD0(dword_792024[3 * v11]) + 24);  // sub_418DD0 —— 资源句柄 (101)
    i = v12;
    if ( pt.y > 0 )
    {
      for ( i = pt.y; i != 0; --i )  // 循环：i = pt.y; i != 0; --i
      {
        v13 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        pObj6 = sub_418DD0(dword_792028[3 * v13]);  // sub_418DD0 —— 资源句柄 (101)
        if ( pObj6 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v5, v12, dword_79C0B0);  // 虚调用 vt+152（pObj6）取值(参数)
        v15 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        v12 += *(uint32_t *)(sub_418DD0(dword_792028[3 * v15]) + 24);  // sub_418DD0 —— 资源句柄 (101)
      }
      i = v12;
    }
    v16 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pObj = sub_418DD0(dword_79202C[3 * v16]);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v5, v12, dword_79C0B0);  // 虚调用 vt+152（pObj）取值(参数)
    v18 = sub_418DD0(13);  // sub_418DD0 —— 资源句柄 (101)
    (*(void (/*thiscall*/ **)(int *, int, unsigned int))(*this + 24))(  // 虚调用 vt+24（this）（析构，参 1）与 8（Release）释放后 GlobalFree 并 SetWindowLongA 摘除 —— 与 ·0x6528C0 挂载配对。
      this,
      21,
      (*(uint32_t *)(v18 + 24) - v45 + v12 - 12) / 0xDu);
    sub_69A5F0((uint32_t *)(*(this + 11) + 132), v5 + 192, v12 + 6);  // 调 sub_69A5F0
    result = dword_9B7C84;  // result=this+8 物品 id
    if ( dword_9B7C84 != 0 )
    {
      v19 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v42 = sub_41A5E0((unsigned int)&dword_9B7C9E[8 * v19]);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v41 = *((uint32_t *)dword_8F8530 + 1);  // dword_8F8530 —— 请求 op 19 带来源对象（等级 + 来源容器）
      v36 = (float)*(int *)(sub_418DD0(6) + 20);  // sub_418DD0 —— 资源句柄 (101)
      v20 = (uint64_t)sub_4049C0(0.0, v36, v41, v42);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v21 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      v21[13] = 0;
      v21[14] = v20 + v5 + 75;  // v21[14] 写入 v20 + v5 + 75
      v21[15] = 480;
      pObj5 = sub_418DD0(6);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v5 + 75, v12 + 11, dword_79C0B0);  // 虚调用 vt+152（pObj5）取值(参数)
      sub_488670(dword_79C0B0);  // sub_488670 —— 视口重置 640x480
      fld_e13 = *(this + 13);  // 读字段 fld_e13 = this+13
      v24 = 0;
      v42 = 0;
      if ( fld_e13 != 0 )  // fld_e13=this+52 光环状态字节
      {
        dword_8F85302 = dword_8F8530;  // dword_8F85302 —— [esp-8h] [ebp-14h]
        v41 = 0;
        do
        {
          if ( v24 < dword_8F85302[2] )  // dword_8F85302 —— [esp-8h] [ebp-14h]
          {
            pObj2 = *(uint32_t *)(dword_8F85302[3] + 4 * v24);  // dword_8F85302 —— [esp-8h] [ebp-14h]
            if ( pObj2 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 8))(  // 虚调用 vt+8（pObj2 虚表槽）
                pObj2,
                v5 + *(uint32_t *)(*(this + 9) + v41),
                v45 + *(uint32_t *)(v41 + *(this + 9) + 4),
                0,
                0);
              dword_8F85302 = dword_8F8530;  // dword_8F85302 —— [esp-8h] [ebp-14h]
              v24 = v42;
              v12 = i;
            }
          }
          ++v24;  // 计数自增 v24
          v41 += 16;
          fld_e132 = v24 < (unsigned int)*(this + 13);
          v42 = v24;
        }
        while ( fld_e132 );  // 当 fld_e132 循环
      }
      v28 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v29 = sub_41A5E0((unsigned int)&dword_9B7C90[8 * v28]);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      if ( v29 < 8 * pt.y )
      {
        v30 = 16 * v29;  // 计算 v30 = 16 * v29
        v42 = 16 * v29;  // 计算 v42 = 16 * v29
        v41 = 8 * pt.y - v29;
        do
        {
          pObj4 = sub_418DD0(16);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj4 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(  // 虚调用 vt+152（pObj4）取值(参数)
              pObj4,
              v5 + *(uint32_t *)(v30 + *(this + 9)),
              v45 + *(uint32_t *)(v30 + *(this + 9) + 4),
              dword_79C0B0);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            v30 = v42;
          }
          v30 += 16;
          v32 = v41 == 1;
          v42 = v30;
          --v41;  // 计数自减 v41
        }
        while ( !v32 );  // 当 !v32 循环
        v12 = i;
      }
      if ( *(this + 12) != -1 )  // 若 *(this + 12) != -1
        sub_4F2E40(
          v5 + *(uint32_t *)(16 * *(this + 12) + *(this + 9)),  // this+12 物品类型号
          v45 + *(uint32_t *)(16 * *(this + 12) + *(this + 9) + 4));  // this+12 物品类型号
      rc.top = 11;
      rc.left = 75;
      rc.right = 183;
      rc.bottom = 20;
      OffsetRect(&rc, v5, v12);
      result = PtInRect(&rc, (POINT)__PAIR64__(y, pt.x));  // result=this+8 物品 id
      if ( result == 1 )  // result=this+8 物品 id
      {
        v33 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        v46 = sub_41A5E0((unsigned int)&dword_9B7C9E[8 * v33]);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        pt.x = *((uint32_t *)dword_8F8530 + 1);  // dword_8F8530 —— 请求 op 19 带来源对象（等级 + 来源容器）
        v35 = (double)pt.x * 0.001;
        v34 = sub_422E70(1166);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v34, v35, (double)v46 * 0.001);  // 调 sprintf 格式化
        return sub_4649B0(rc.left + (rc.right - rc.left) / 2, rc.top - 2, -1, -16777216, 2, Buffer, 0, 0, 1600, 0);  // sub_4649B0 —— 带框文本上屏（静态一次性初始化）
      }
    }
  }
  return result;  // result=this+8 物品 id
}


// ------------------------------------------------------------
// 0x50DED0 sub_50DED0 —— CNRDStorageWindow 析构核心（双层虚表链）
//   先挂 vftbl_CNRDStorageWindow 调 ·sub_50D570 清理，再挂 vftbl_IRDPopupWindow 转 ·sub_5542F0。
// ------------------------------------------------------------
int /*thiscall*/ sub_50DED0(uint32_t *this)  // sub_50DED0 —— CNRDStorageWindow 析构核心（双层虚表链）
{
  *this = &vftbl_CNRDStorageWindow;  // 装虚表/取地址：← vftbl_CNRDStorageWindow
  sub_50D570(this);  // sub_50D570 —— 仓储窗口按钮组释放与槽位游标复位
  *this = &vftbl_IRDPopupWindow;  // 装虚表/取地址：← vftbl_IRDPopupWindow
  return sub_5542F0(this);  // sub_5542F0 —— 窗口页数据 2（22 行）
}



// ------------------------------------------------------------
// 0x50DF30 CNRDStorageWindow__vmtC —— 仓储窗口打开回调
//   置 dword_9B7C84=1 与 dword_9B7C8C=1，播 SAFE_OPEN 音效后返回 1。
// ------------------------------------------------------------
char /*stdcall*/ CNRDStorageWindow__vmtC(int nArg1, int nArg2)  // 函数: 仓储窗口打开回调
{
  dword_9B7C84 = 1;
  sub_432EA0("SAFE_OPEN", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  dword_9B7C8C = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x50DF60 sub_50DF60 —— 鼠标拾取槽位（get_mouse_over_slot）
//   父窗口可见（+17）且激活件（+12）属三活动态之一时遍历 this+36 槽位矩形（16B，扩展 2px）做 PtInRect；
//   槽数上限 0x40（超限报 slot_limit is too big），未命中返回 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_50DF60(unsigned int *this)  // sub_50DF60 —— 鼠标拾取槽位（get_mouse_over_slot）
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

  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  if ( *(uint8_t *)(fld_e2 + 17) == 0 )  // 若 *(uint8_t *)(fld_e2 + 17) == 0
    return -1;  // 返回 -1（0xFFFFFFFF）
  v3 = *(uint32_t *)(fld_e2 + 12);  // 读字段 v3 = fld_e2+12（nSkillRec12）
  if ( dword_79BE3C != v3 && dword_79BE34 != v3 && dword_79BE38 != v3 )  // 判定 dword_79BE3C != v3 且 dword_79BE34 != v3 且 dword_79BE38 != v3
    return -1;  // 返回 -1（0xFFFFFFFF）
  if ( *(this + 13) > 0x40 )  // 若 *(this + 13) > 0x40
  {
    off_77F3FC("CNRDStorageWindow::get_mouse_over_slot - slot_limit is too big. (%d)", *(this + 13));  // off_77F3FC —— 日志打印（printf 风格）
    *(this + 13) = 64;  // 写字段 this+13 ← 64
  }
  fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
  v6 = *(uint32_t *)(fld_e22 + 20);  // 读字段 v6 = fld_e22+20（nPage）
  v7 = *(uint32_t *)(fld_e22 + 24);  // 读字段 v7 = fld_e22+24（nPageMax）
  pt.x = ::pt.x;
  fld_e13 = *(this + 13);  // 读字段 fld_e13 = this+13
  pt.y = ::pt.y;
  v16 = 0;
  if ( fld_e13 == 0 )  // fld_e13=this+52 光环状态字节
    return -1;  // 返回 -1（0xFFFFFFFF）
  v17 = 0;
  while ( 1 )  // 当 1 循环
  {
    fld_e9 = *(this + 9);  // 读字段 fld_e9 = this+9
    v10 = *(uint32_t *)(fld_e9 + v17);  // v10 = fld_e9+v17
    v11 = (uint32_t *)(v17 + fld_e9);  // fld_e9=this+36 物品状态字
    rc.left = v10 + v6 - 2;
    rc.top = v11[1] + v7 - 2;
    rc.right = v11[2] + v6 + 2;
    rc.bottom = v11[3] + v7 + 2;
    v12 = !PtInRect(&rc, pt);
    result = v16;
    if ( !v12 )  // 若 !v12
      break;
    fld_e132 = *(this + 13);  // 读字段 fld_e132 = this+13
    ++v16;  // 计数自增 v16
    v17 += 16;
    if ( v16 >= fld_e132 )  // fld_e132=this+52 光环状态字节
      return -1;  // 返回 -1（0xFFFFFFFF）
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
  v3 = sub_41A5E0((unsigned int)&unk_9B7D10);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  *((uint32_t *)this + 13) = sub_41A5E0((unsigned int)&dword_9B7C90[8 * v3]);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  *((uint32_t *)this + 12) = sub_50DF60(this);  // sub_50DF60 —— 鼠标拾取槽位（get_mouse_over_slot）
  pThis_B = *((uint32_t *)this + 11);  // 读字段 pThis_B = this[11]
  if ( *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_B + 12) )  // 若 *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    v2 = 1;
    v29 = 1;
  }
  pThis_B2 = *((uint32_t *)this + 11);  // 读字段 pThis_B2 = this[11]
  v6 = *(uint8_t *)(pThis_B2 + 149);  // 读字段 v6 = pThis_B2+149
  v7 = pThis_B2 + 132;  // 计算 v7 = pThis_B2 + 132
  if ( v6 != 0 && dword_79BE34 == *(uint32_t *)(v7 + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    v28 = 1;
  }
  if ( *(uint32_t *)(*((uint32_t *)this + 4) + 2504) == 2 )  // 若 *(uint32_t *)(*((uint32_t *)this + 4) + 2504) == 2
  {
    if ( *((uint32_t *)this + 12) != -1 && (uint8_t)sub_69A500(*((uint32_t *)this + 2)) == 1 )  // 若 *((uint32_t *)this + 12) != -1 && (uint8_t)sub_69A500(*((uint3..
      v26 = 1;
    goto LABEL_11;  // 跳转 LABEL_11
  }
  sub_69A650(*((uint32_t *)this + 2));  // 调 sub_69A650
  if ( (uint8_t)sub_69A4D0(*((uint32_t *)this + 2)) != 1 || (pThis_C = *((uint32_t *)this + 12)) == -1 )  // 若 (uint8_t)sub_69A4D0(*((uint32_t *)this + 2)) != 1 || (pThis_C ..
  {
LABEL_11:
    dword_8F85302 = dword_8F8530;  // dword_8F85302 —— [esp-8h] [ebp-14h]
    goto LABEL_12;  // 跳转 LABEL_12
  }
  dword_8F85302 = dword_8F8530;  // dword_8F85302 —— [esp-8h] [ebp-14h]
  if ( pThis_C < *((uint32_t *)dword_8F8530 + 2) && *(uint32_t *)(*((uint32_t *)dword_8F8530 + 3) + 4 * pThis_C) != 0 )  // dword_8F8530 —— 请求 op 19 带来源对象（等级 + 来源容器）
  {
    pThis_4 = *(uint32_t *)(*((uint32_t *)this + 4) + 2504);  // this+4 宿主对象
    if ( pThis_4 != 5 && pThis_4 != 6 )
      v27 = 1;
  }
LABEL_12:
  v9 = dword_8F85302[5];  // dword_8F85302 —— [esp-8h] [ebp-14h]
  if ( v9 != 0 )
    v10 = (dword_8F85302[6] - v9) >> 2;  // dword_8F85302 —— [esp-8h] [ebp-14h]
  else
    v10 = 0;
  v13 = v10 == 0;
  pThis_C2 = *((uint32_t *)this + 12);  // 读字段 pThis_C2 = this+12（nSkillRec12）
  v15 = !v13;
  if ( pThis_C2 == -1 )  // pThis_C2=this+12 nSkillRec12
  {
    if ( dword_9B88D0 == 0 || dword_795378 != 6 )  // 判定 dword_9B88D0 == 0 或 dword_795378 != 6
      goto LABEL_34;  // 跳转 LABEL_34
    sub_44E850(*((uint32_t **)this + 4), 26);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
  }
  else
  {
    if ( pThis_C2 >= dword_8F85302[2] )  // dword_8F85302 —— [esp-8h] [ebp-14h]
      v16 = 0;
    else
      v16 = *(uint32_t *)(dword_8F85302[3] + 4 * pThis_C2);  // dword_8F85302 —— [esp-8h] [ebp-14h]
    if ( dword_9B88D0 == v16 && dword_795378 == 6 )  // 判定 dword_9B88D0 == v16 且 dword_795378 == 6
      goto LABEL_34;  // 跳转 LABEL_34
    pThis_42 = sub_44E8D0(*((char **)this + 4), (void *)0x1A, v16, 6);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
    if ( pThis_42 != 0 )
    {
      pThis_9 = *((uint32_t *)this + 9);  // 读字段 pThis_9 = this[9]
      pThis_C3 = 16 * *((uint32_t *)this + 12);  // this+12 物品类型号
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pThis_42 + 48))(  // 虚调用 vt+48（pThis_42）归属坐标x
        pThis_42,
        *(uint32_t *)(pThis_C3 + pThis_9) + *(uint32_t *)(*((uint32_t *)this + 2) + 20),  // pThis_9=this+36 物品状态字
        *(uint32_t *)(pThis_9 + pThis_C3 + 4) + *(uint32_t *)(*((uint32_t *)this + 2) + 24),  // pThis_9=this+36 物品状态字
        *(uint32_t *)(pThis_C3 + pThis_9 + 8) - *(uint32_t *)(pThis_C3 + pThis_9),  // pThis_9=this+36 物品状态字
        *(uint32_t *)(pThis_C3 + pThis_9 + 12) - *(uint32_t *)(pThis_9 + pThis_C3 + 4));  // pThis_9=this+36 物品状态字
      v2 = v29;
    }
  }
  dword_8F85302 = dword_8F8530;  // dword_8F85302 —— [esp-8h] [ebp-14h]
LABEL_34:
  result = dword_9B7C8C - 1;
  v21 = 3;
  switch ( dword_9B7C8C )  // 分支：按 dword_9B7C8C 分派
  {
    case 1:  // case 1 分派（§C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取））
      result = 1;
      if ( dword_9B7C84 == 1 )
        goto LABEL_51;  // 跳转 LABEL_51
      dword_9B7C8C = 2;
      if ( dword_9B7C80 == 0 )
        dword_9B7C80 = 1;
      return result;
    case 2:  // case 2 分派（§C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取））
      if ( v2 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 虚调用 vt+32（this 虚表槽）
        dword_9B7C8C = 5;
      }
      return result;
    case 3:  // case 3 分派（§C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取））
      if ( v2 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 虚调用 vt+32（this 虚表槽）
        dword_8F85302 = dword_8F8530;  // dword_8F85302 —— [esp-8h] [ebp-14h]
        dword_9B7C8C = 5;
      }
      if ( v15 )  // 若 v15
        goto LABEL_45;  // 跳转 LABEL_45
      if ( v28 != 0 )
      {
        result = sub_486C40(dword_8F85302, v21);  // sub_486C40 —— 请求 op 20（整栏技能重置）
LABEL_45:
        dword_9B7C8C = 4;
        return result;
      }
      if ( v27 != 0 )
      {
        pThis_C4 = sub_44A980(*((uint32_t *)this + 12));  // sub_44A980 —— 结果 = 带界索引 getter
        v24 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_C4 + 16))(pThis_C4) + 68);  // 虚调用 vt+16（pThis_C4 虚表槽）
        pThis_C5 = *((uint32_t *)this + 12);  // 读字段 pThis_C5 = this+12（nSkillRec12）
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_C4 + 16))(pThis_C4);  // 虚调用 vt+16（pThis_C4 虚表槽）
        return sub_44BC30(2, 8, *(uint32_t *)(v22 + 4), pThis_C5, v24, pThis_C4);  // sub_44BC30 —— 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
      }
      else
      {
        result = v26;
        if ( v26 != 0 )
        {
          result = sub_50D710(this, *((uint32_t *)this + 4) + 2508);  // sub_50D710 —— 仓储窗口 process_move 落点判定与移动分派
          dword_9B7C8C = 4;
        }
      }
      return result;
    case 4:  // case 4 分派（§C 0x50D260-0x50E7E0 仓储窗口 CNRDStorageWindow 族（弹窗/移动/交换/鼠标拾取））
      if ( !v15 )  // 若 !v15
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
uint32_t */*thiscall*/ CNRDStorageWindow__vmt4(uint32_t *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50DED0(Block);  // sub_50DED0 —— CNRDStorageWindow 析构核心（双层虚表链）
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50E3B0 sub_50E3B0 —— 仓储窗口构建（按钮组 + 槽位表布局）
//   读按钮模板 dword_99FCC8，operator new(0x10C) eh 数组构造 2 个 CNButton（unk_6FCD5C/6FCD70 配置）；
//   this+36 槽位表按 128 步长排 8 列（15/47/79/111/143/175/207/239 起），行高取自 10/7 号精灵 +2。
// ------------------------------------------------------------
int /*thiscall*/ sub_50E3B0(uint32_t *this)  // sub_50E3B0 —— 仓储窗口构建（按钮组 + 槽位表布局）
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

  *(this + 10) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 188);  // dword_99FCC8 —— nengine::CNSlider 构造
  pMem = operator new(0x10Cu);  // 堆分配
  v3 = 0;
  if ( pMem != nullptr )
  {
    v4 = pMem + 1;  // 计算 v4 = pMem + 1
    *pMem = 2;  // *pMem 写入 2
    `eh vector constructor iterator'(pMem + 1, 0x84u, 2, sub_46F750, sub_43C480);  // 调 nengine::CNButton 构造
  }
  else
  {
    v4 = nullptr;  // v4 = nullptr 空指针
  }
  *(this + 11) = v4;  // 写字段 this+11 ← v4
  Block = (int *)&unk_6FCD70;
  v5 = (int *)&unk_6FCD5C;
  do
  {
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)(v3 + *(this + 11))  // 仓储窗口构建（按钮组 + 槽位表布局）
                                                                                     + 32))(
      v3 + *(this + 11),
      *(this + 10),
      *(v5 - 3),
      *(v5 - 2),
      *(v5 - 1),
      *v5 < 0 ? 0 : *v5,
      0,
      0);
    sub_69A5F0((uint32_t *)(v3 + *(this + 11)), *Block, Block[1]);  // 调 sub_69A5F0
    sub_69A840(v3 + *(this + 11));  // 调 sub_69A840
    v5 += 4;
    v3 += 132;
    Block += 2;
  }
  while ( (int)v5 < (int)&dword_6FCD7C );  // 当 (int)v5 < (int)&dword_6FCD7C 循环
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 1);  // 虚调用 vt+28（this 虚表槽）
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 21, 2);  // 虚调用 vt+24（this）（析构，参 1）与 8（Release）释放后 GlobalFree 并 SetWindowLongA 摘除 —— 与 ·0x6528C0 挂载配对。
  sub_69A5F0((uint32_t *)*(this + 2), 34, 34);  // 调 sub_69A5F0
  pMem2 = operator new(0x400u);  // 堆分配
  fld_e10 = (uint32_t *)*(this + 10);
  *(this + 9) = pMem2;  // 写字段 this+9 ← pMem2
  Blocka = *(void **)(sub_418DD0(fld_e10, 0xAu) + 24);  // sub_418DD0 —— 资源句柄 (101)
  result = *(uint32_t *)(sub_418DD0((uint32_t *)*(this + 10), 7u) + 24) + 2;  // sub_418DD0 —— 资源句柄 (101)
  v9 = result + 28;  // 计算 v9 = result + 28
  for ( i = 48; i < 0x430; i += 128 )  // 循环：i = 48; i < 0x430; i += 128
  {
    fld_e9 = *(this + 9);  // 读字段 fld_e9 = this+9
    v12 = i - 48;  // 计算 v12 = i - 48
    *(uint32_t *)(fld_e9 + v12 + 4) = result;  // fld_e9=this+36 物品状态字
    *(uint32_t *)(fld_e9 + v12 + 12) = v9;  // fld_e9=this+36 物品状态字
    v13 = (uint32_t *)(i - 48 + fld_e9);  // fld_e9=this+36 物品状态字
    *v13 = 15;  // *v13 写入 15
    v13[2] = 43;
    fld_e92 = *(this + 9);  // 读字段 fld_e92 = this+9
    *(uint32_t *)(fld_e92 + v12 + 20) = result;  // fld_e92=this+36 物品状态字
    *(uint32_t *)(fld_e92 + v12 + 28) = v9;  // fld_e92=this+36 物品状态字
    v15 = (uint32_t *)(fld_e92 + i - 48 + 16);  // fld_e92=this+36 物品状态字
    *v15 = 47;  // *v15 写入 47
    v15[2] = 75;
    fld_e93 = (uint32_t *)(*(this + 9) + i - 16);
    fld_e93[1] = result;
    fld_e93[3] = v9;
    *fld_e93 = 79;  // *fld_e93 写入 79
    fld_e93[2] = 107;
    fld_e94 = (uint32_t *)(i + *(this + 9));
    fld_e94[1] = result;
    fld_e94[3] = v9;
    *fld_e94 = 111;  // *fld_e94 写入 111
    fld_e94[2] = 139;
    fld_e95 = (uint32_t *)(*(this + 9) + i + 16);
    fld_e95[1] = result;
    fld_e95[3] = v9;
    *fld_e95 = 143;  // *fld_e95 写入 143
    fld_e95[2] = 171;
    fld_e96 = (uint32_t *)(*(this + 9) + i + 32);
    fld_e96[1] = result;
    fld_e96[3] = v9;
    *fld_e96 = 175;  // *fld_e96 写入 175
    fld_e96[2] = 203;
    fld_e97 = (uint32_t *)(*(this + 9) + i + 48);
    fld_e97[1] = result;
    fld_e97[3] = v9;
    *fld_e97 = 207;  // *fld_e97 写入 207
    fld_e97[2] = 235;
    fld_e98 = (uint32_t *)(*(this + 9) + i + 64);
    fld_e98[1] = result;
    fld_e98[3] = v9;
    *fld_e98 = 239;  // *fld_e98 写入 239
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
char */*thiscall*/ nengine__CNButton__vmt0(char *this, char pszArg2)  // CNButton eh 数组析构（标志位 1 释放）
{
  if ( (pszArg2 & 2) != 0 )  // 判定位掩码：pszArg2 & 2
  {
    `eh vector destructor iterator'(this, 0x84u, *((uint32_t *)this - 1), sub_43C480);  // 调 nengine::CNButton 析构
    if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
      j_j__free(this - 4);  // 调 j__free
    return this - 4;
  }
  else
  {
    sub_43C480(this);  // sub_43C480 —— nengine::CNButton 析构
    if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
      j__free(this);  // 释放堆块
    return this;
  }
}



// ------------------------------------------------------------
// 0x50E650 sub_50E650 —— 仓储窗口构造（弹窗基类 + 文案表缓存）
//   弹窗基类 ·sub_5542C0/·sub_5548B0（op 15）后挂 vftbl_CNRDStorageWindow；四段静态文案
//   （1160..1163）惰性取入 dword_9B7CAC 段；槽位游标清零、全局态缺省 5；末 ·sub_50E3B0 建钮。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50E650(uint32_t *this, int nArg2)  // sub_50E650 —— 仓储窗口构造（弹窗基类 + 文案表缓存）
{
  *this = &vftbl_IRDPopupWindow;  // 装虚表/取地址：← vftbl_IRDPopupWindow
  sub_5542C0();  // sub_5542C0 —— 窗口页数据（18 行）
  sub_5548B0(nArg2, 15);  // sub_5548B0 —— 弹窗关闭回调调用（5547D0，22 行——vmt4 三件套的公共尾）
  *this = &vftbl_CNRDStorageWindow;  // 装虚表/取地址：← vftbl_CNRDStorageWindow
  if ( dword_9B7CAC[0] == 0 )  // 若 dword_9B7CAC[0] == 0
  {
    dword_9B7CAC[0] = sub_422E70(1160);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    dword_9B7CCC = sub_422E70(1161);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    dword_9B7CEC = sub_422E70(1162);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    dword_9B7D0C = sub_422E70(1163);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  }
  *(this + 9) = 0;  // 写字段 this+9 ← 0
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  *(this + 12) = -1;  // 写字段 this+12（nSkillRec12） ← -1
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  if ( dword_9B7C8C == 0 )
  {
    dword_9B7C80 = 0;
    dword_9B7C84 = 0;
    dword_9B7C8C = 5;
  }
  sub_50E3B0(this);  // sub_50E3B0 —— 仓储窗口构建（按钮组 + 槽位表布局）
  return this;
}



// ------------------------------------------------------------
// 0x50E730 sub_50E730 —— 对象字段清零（三指针 + 两标志）
//   清零 +0/+4/+8 与 +12/+13 标志字节。
// ------------------------------------------------------------
int /*thiscall*/ sub_50E730(uint32_t *this)  // sub_50E730 —— 对象字段清零（三指针 + 两标志）
{
  *this = 0;  // *this 写入 0
  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *((uint8_t *)this + 13) = 0;  // 写字段 this[13]（宽1字节）
  return 0;
}



// ------------------------------------------------------------
// 0x50E750 sub_50E750 —— 表情气泡双图层播放推进
//   主/次两动画件（this+4 / this+8）依次：·sub_4938F0 播放、·sub_491D00 图层属性下发（y 经 vmt192 偏移）；
//   次层帧数 ≥1 时首帧经 ·sub_4926A0 复位（+13 标志）。
// ------------------------------------------------------------
char /*thiscall*/ sub_50E750(uint32_t *this, int nArg2, int nArg3)  // sub_50E750 —— 表情气泡双图层播放推进
{
  int fld_e1; // eax
  int v5; // eax
  int v6; // eax

  LOBYTE(fld_e1) = *((uint8_t *)this + 12);  // this+12 物品类型号
  if ( (uint8_t)fld_e1 != 0 )
  {
    sub_4938F0(*(this + 1));  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    v5 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*this + 192))(*this);  // 虚调用 vt+192（this）取尺寸/包围盒
    sub_491D00(dword_79C0B0, nArg2, nArg3 - v5, 0.0);  // sub_491D00 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
    if ( *(int *)(fld_e1 + 148) >= 1 )  // 若 *(int *)(fld_e1 + 148) >= 1
    {
      if ( *((uint8_t *)this + 13) == 0 )  // 若 *((uint8_t *)this + 13) == 0
      {
        sub_4926A0(*(this + 2));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
        *((uint8_t *)this + 13) = 1;  // 写字段 this[13]（宽1字节）
      }
      sub_4938F0(*(this + 2));  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      v6 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*this + 192))(*this);  // 虚调用 vt+192（this）取尺寸/包围盒
      LOBYTE(fld_e1) = sub_491D00(dword_79C0B0, nArg2, nArg3 - v6, 0.0);  // sub_491D00 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    }
  }
  return fld_e1;  // fld_e1=this+4 宿主对象
}



// ============================================================
// §D 0x50E7E0-0x50EB40 表情(emoticon)系统
// ============================================================
// ------------------------------------------------------------

// 0x50E7E0 sub_50E7E0 —— 表情标签反查器（unk_9B7D24 表 23 项，$END 结尾；
//   倒序逐长匹配 → 返回索引，未命中返回 23）
// ------------------------------------------------------------
int /*cdecl*/ sub_50E7E0(const char *pArg1)  // 函数: 表情标签反查器（unk_9B7D24 表 23 项，$END 结尾；
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

  nLen = strlen(pArg1);  // 调 _strlen 取字符串长度
  if ( nLen >= 0 )
  {
    while ( 2 )  // 当 2 循环
    {
      v1 = (int *)&unk_9B7D24;
      v8 = 0;
      v10 = (int *)&unk_9B7D24;
      do
      {
        if ( strcmp((const char *)sub_41ACF0(*v1), "$END") != 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        {
          v2 = 0;
          while ( 1 )  // 当 1 循环
          {
            v3 = (size_t *)(*v10 + v2);
            v4 = *v3;
            if ( *v3 != 0 )
              v4 = *(uint32_t *)(v4 + 4);  // 读字段 v4 = v4+4（pHostObj）
            psz2 = v4;
            psz = (const char *)sub_41ACF0(v3);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
            if ( strncmp(psz, &pArg1[nLen], psz2) == 0 )  // 若 strncmp(psz, &pArg1[nLen], psz2) == 0
              return v8;
            v2 += 4;
            if ( strcmp((const char *)sub_41ACF0(v2 + *v10), "$END") == 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
            {
              v1 = v10;
              break;
            }
          }
        }
        v1 += 4;
        ++v8;  // 计数自增 v8
        v10 = v1;
      }
      while ( (int)v1 < (int)&dword_9B7E94 );  // 当 (int)v1 < (int)&dword_9B7E94 循环
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
int /*thiscall*/ sub_50E8D0(uint32_t *this, int nArg2)  // sub_50E8D0 —— 表情气泡对象构造（EmoBalloonS.ani）
{
  int v3; // eax
  int result; // eax

  *this = nArg2;  // *this 写入 nArg2
  if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v3 = sub_431860((char)"Common/Emoticon/EmoBalloonS.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
  else
    v3 = 0;
  *(this + 1) = v3;  // 写字段 this+1 ← v3
  result = sub_4924C0(3);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
  *(uint32_t *)(result + 48) = 3000;  // 写字段 result+48（pCmdVecBegin48） ← 3000
  return result;
}



// ------------------------------------------------------------
// 0x50E950 sub_50E950 —— 表情气泡双动画件释放
//   this+4 / this+8 两动画件经 ·sub_42AF90 析构 + ·sub_657740(228) 释放并置空。
// ------------------------------------------------------------
int /*thiscall*/ sub_50E950(void ***this)  // sub_50E950 —— 表情气泡双动画件释放
{
  int fld_e1; // edi
  int result; // eax
  void **fld_e2; // edi

  fld_e1 = (int)*(this + 1);
  if ( fld_e1 != 0 )
  {
    sub_42AF90(*(this + 1));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e1, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  *(this + 1) = nullptr;  // 写字段 this+1 ← nullptr
  if ( fld_e2 != nullptr )  // fld_e2=this+8 物品 id
  {
    sub_42AF90(fld_e2);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e2, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 2) = nullptr;  // 写字段 this+2 ← nullptr
  return result;
}



// ------------------------------------------------------------
// 0x50E9B0 sub_50E9B0 —— 表情气泡次层提前销毁（主层 +170 标志触发）
//   可见且主件 +170 置位时清 +12 标志并释放 +8 次动画件。
// ------------------------------------------------------------
char /*thiscall*/ sub_50E9B0(int this)  // sub_50E9B0 —— 表情气泡次层提前销毁（主层 +170 标志触发）
{
  int fld_4; // eax
  void **fld_8; // edi

  LOBYTE(fld_4) = *(uint8_t *)(this + 12);  // this+12 物品类型号
  if ( (uint8_t)fld_4 != 0 )
  {
    fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
    if ( *(uint8_t *)(fld_4 + 170) != 0 )  // 若 *(uint8_t *)(fld_4 + 170) != 0
    {
      fld_8 = *(void ***)(this + 8);  // this+8 物品 id
      *(uint8_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
      if ( fld_8 != nullptr )  // fld_8=this+8 物品 id
      {
        sub_42AF90(fld_8);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
        LOBYTE(fld_4) = sub_657740(fld_8, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
      }
      *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
    }
  }
  return fld_4;  // fld_4=this+4 pHostObj
}



// ------------------------------------------------------------
// 0x50EA00 sub_50EA00 —— 表情气泡换图（按索引 off_792078）
//   先释放旧次件（+12 清位）与 ·sub_4926A0 复位主件帧游标，再以 off_792078[nArg2] 建新件（228B），
//   置 +12=1/+13=0。
// ------------------------------------------------------------
int /*thiscall*/ sub_50EA00(int this, int nArg2)  // sub_50EA00 —— 表情气泡换图（按索引 off_792078）
{
  void **fld_8; // edi
  int result; // eax

  if ( *(uint8_t *)(this + 12) != 0 )  // 若 *(uint8_t *)(this + 12) != 0
  {
    fld_8 = *(void ***)(this + 8);  // this+8 物品 id
    *(uint8_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
    if ( fld_8 != nullptr )  // fld_8=this+8 物品 id
    {
      sub_42AF90(fld_8);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(fld_8, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  }
  sub_4926A0(*(uint32_t *)(this + 4));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
  if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    result = sub_431860((char)off_792078[nArg2], 1);  // sub_431860 —— 动画件构造（资源 id 版）
  else
    result = 0;
  *(uint8_t *)(this + 13) = 0;  // 写字段 this+13 ← 0
  *(uint32_t *)(this + 8) = result;  // 写字段 this+8（nSkillRec8） ← result
  *(uint8_t *)(this + 12) = 1;  // 写字段 this+12（nSkillRec12） ← 1
  return result;
}



// ------------------------------------------------------------
// 0x50EAA0 sub_50EAA0 —— 表情名 → 气泡切换（含 vmt80 可用判定）
//   vmt80 非零时把 pArg2 经 ·sub_50E7E0 反查为索引，命中（≠23）转 ·sub_50EA00。
// ------------------------------------------------------------
int /*thiscall*/ sub_50EAA0(uint32_t *this, const char *pArg2)  // sub_50EAA0 —— 表情名 → 气泡切换（含 vmt80 可用判定）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*this + 80))(*this);  // 虚调用 vt+80（this）读 4 字节
  if ( result != 0 )
  {
    result = sub_50E7E0(pArg2);  // 调 表情标签反查器
    if ( result != 23 )
      return sub_50EA00((int)this, result);  // sub_50EA00 —— 表情气泡换图（按索引 off_792078）
  }
  return result;
}



// ------------------------------------------------------------
// 0x50EAD0 sub_50EAD0 —— 气泡对象定时/计数状态复位
//   清零 +0/+32/+40 与 +44..+64（含内嵌计时目标与计数）。
// ------------------------------------------------------------
int /*thiscall*/ sub_50EAD0(uint32_t *this)  // sub_50EAD0 —— 气泡对象定时/计数状态复位
{
  *this = 0;  // *this 写入 0
  *(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *((uint8_t *)this + 40) = 0;  // 写字段 this+40（bStateSub40）
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  *(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  *(this + 14) = 0;  // 写字段 this+14 ← 0
  *(this + 15) = 0;  // 写字段 this+15 ← 0
  *(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x50EAF0 sub_50EAF0 —— 释放内嵌对象（this+32）并置空
//   this+32 对象存在则经其虚表首项（flag 1）自毁，指针清零；返回该调用结果。
// ------------------------------------------------------------
int /*thiscall*/ sub_50EAF0(uint32_t *this)  // sub_50EAF0 —— 释放内嵌对象（this+32）并置空
{
  int (/*thiscall*/ ***fld_e8)(uint32_t, int); // ecx
  int result; // eax

  fld_e8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 8);  // this+8 物品 id
  if ( fld_e8 != nullptr )
    result = (**fld_e8)(fld_e8, 1);
  *(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  return result;
}



// ------------------------------------------------------------
// 0x50EB10 sub_50EB10 —— 气泡计时到期判定
//   标志（+40）置位时取 ·sub_699000(this+4) 与到期时刻 +28 比较，到点清 +40。
// ------------------------------------------------------------
char /*thiscall*/ sub_50EB10(int this)  // sub_50EB10 —— 附件 tick A
{
  int pThis_4; // eax
  int fld_1C; // edi

  LOBYTE(pThis_4) = *(uint8_t *)(this + 40);  // this+40 物品状态附属标志
  if ( (uint8_t)pThis_4 != 0 )
  {
    fld_1C = *(uint32_t *)(this + 28);  // 读字段 fld_1C = this+28（pPanelVec）
    pThis_4 = sub_699000(this + 4);  // 【clock_now(clk)】
    if ( pThis_4 >= fld_1C )  // fld_1C=this+28 pPanelVec
      *(uint8_t *)(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  }
  return pThis_4;
}



// ============================================================
// §E 0x50EB40-0x50F1C0 UI 文本气泡与 CNText 族
// ============================================================
// ------------------------------------------------------------

// 0x50EB40 sub_50EB40 —— 表情气泡绘制（按行数拼 9-slice：id 63/64/65/66）
// ------------------------------------------------------------
void /*thiscall*/ sub_50EB40(uint32_t *this, int nArg2, int nArg3, int nArg4)  // sub_50EB40 —— 表情气泡绘制（按行数拼 9-slice：id 63/64/65/66）
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

  if ( *((uint8_t *)this + 40) != 0 && *(float *)&dword_77F6DC == 1.0 )  // this+40 物品状态附属标志
  {
    fld_e13 = -10 - 12 * *(this + 13) + nArg2;
    fld_e133 = fld_e13;
    if ( *this != 0 )
    {
      fld_e13 -= 14;
      fld_e133 = fld_e13;
    }
    fld_e8 = *(this + 8);  // 读字段 fld_e8 = this+8（nSkillRec8）
    fld_e14 = *(this + 14);  // 读字段 fld_e14 = this+14
    *(uint32_t *)(fld_e8 + 32) = fld_e13 + 5;  // 写字段 fld_e8+32（nHeight） ← fld_e13 + 5
    v8 = nArg3 - fld_e14;  // 计算 v8 = nArg3 - fld_e14
    v26 = fld_e13 + 5;  // 计算 v26 = fld_e13 + 5
    *(uint32_t *)(fld_e8 + 36) = v8 + 6;  // 写字段 fld_e8+36（nStateWord36） ← v8 + 6
    fld_e134 = fld_e13;
    pObj2 = sub_418DD0(63);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
        pObj2,
        fld_e133,
        v8,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v23 = v26;
    v27 = 0;
    if ( (int)*(this + 11) > 0 )  // 若 (int)*(this + 11) > 0
    {
      do
      {
        pObj7 = sub_418DD0(64);  // sub_418DD0 —— 资源句柄 (101)
        if ( pObj7 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj7 + 128))(  // 虚调用 vt+128（pObj7）目标坐标y上界
            pObj7,
            v23,
            v8,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,
            1065353216,
            0,
            ((uint8_t)nArg4 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        fld_e11 = ++v27 < *(this + 11);
        v23 += 12;
      }
      while ( fld_e11 );  // 当 fld_e11 循环
    }
    pObj3 = sub_418DD0(65);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚调用 vt+128（pObj3）目标坐标y上界
        pObj3,
        v23,
        v8,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v14 = v8 + 5;  // 计算 v14 = v8 + 5
    for ( i = 0; i < *(this + 12); ++i )  // 循环：i = 0; i < *(this + 12); ++i
    {
      pObj5 = sub_418DD0(66);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 虚调用 vt+128（pObj5）目标坐标y上界
          pObj5,
          fld_e134,
          v14,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg4 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v24 = fld_e134 + 5;  // 计算 v24 = fld_e134 + 5
      v28 = 0;
      if ( (int)*(this + 11) > 0 )  // 若 (int)*(this + 11) > 0
      {
        do
        {
          pObj6 = sub_418DD0(67);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj6 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(  // 虚调用 vt+128（pObj6）目标坐标y上界
              pObj6,
              v24,
              v14,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              ((uint8_t)nArg4 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          fld_e11 = ++v28 < *(this + 11);
          v24 += 12;
        }
        while ( fld_e11 );  // 当 fld_e11 循环
      }
      pObj = sub_418DD0(68);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
          pObj,
          v24,
          v14,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg4 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v14 += 13;
    }
    pObj4 = sub_418DD0(69);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 虚调用 vt+128（pObj4）目标坐标y上界
        pObj4,
        fld_e134,
        v14,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v25 = fld_e134 + 5;  // 计算 v25 = fld_e134 + 5
    v29 = 0;
    if ( (int)*(this + 11) > 0 )  // 若 (int)*(this + 11) > 0
    {
      do
      {
        fld_e132 = sub_418DD0(2 * (v29 == *(this + 13)) + 70);  // sub_418DD0 —— 资源句柄 (101)
        if ( fld_e132 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_e132 + 128))(  // 虚调用 vt+128（fld_e132）目标坐标y上界
            fld_e132,
            v25,
            v14,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,
            1065353216,
            0,
            ((uint8_t)nArg4 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        fld_e11 = ++v29 < *(this + 11);
        v25 += 12;
      }
      while ( fld_e11 );  // 当 fld_e11 循环
    }
    pObj8 = sub_418DD0(71);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(  // 虚调用 vt+128（pObj8）目标坐标y上界
        pObj8,
        v25,
        v14,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    if ( nArg4 == 255 )
      sub_69D780(*(this + 8));  // 调 sub_69D780
  }
}


// ------------------------------------------------------------
// 0x50EF20 sub_50EF20 —— 气泡文本设置与量算（行数/半高/倒计时）
//   ·sub_69D6C0(-1) 复位文本对象后 ·sub_69DDB0 写入 Format，从其行数组（+16）得显示行数（+48）；
//   按 12 字/行 折算气泡行数（+44）与半高行（+52）；高度（+56）=13×行数+15，叠加对象 vmt192 与
//   vmt40(18) 分支；末 ·sub_698F90 起 nArg4 毫秒（-1→3000）倒计时并置可见（+40=1）。
// ------------------------------------------------------------
char /*thiscall*/ sub_50EF20(int *this, char *Format, int nArg3, int nArg4)  // 函数: 气泡文本设置与量算（行数/半高/倒计时）
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

  sub_69D6C0(-1);  // 调 sub_69D6C0
  sub_69DDB0(*(this + 8), Format, v22);  // 调 sub_69DDB0
  fld_e8 = *(this + 8);  // 读字段 fld_e8 = this+8（nSkillRec8）
  v6 = *(uint32_t *)(fld_e8 + 16);  // 读字段 v6 = fld_e8+16（nChannelTypeSel）
  v7 = fld_e8 + 12;  // 计算 v7 = fld_e8 + 12
  if ( v6 != 0 )
    v8 = (*(uint32_t *)(v7 + 8) - v6) >> 2;
  else
    v8 = 0;
  *(this + 12) = v8;  // 写字段 this+12（nSkillRec12） ← v8
  if ( v8 != 1 || *(this + 16) != 0 )  // this+16 频道型选中索引
    fld_e15 = *(this + 15);  // 读字段 fld_e15 = this+15
  else
    fld_e15 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, Format);  // 虚调用 vt+16（dword_99FCCC 虚表槽）
  v11 = fld_e15 % 12;  // fld_e15=this+60 fade 值
  v10 = fld_e15 / 12;  // 计算 v10 = fld_e15 / 12
  v12 = v11;
  if ( v11 != 0 )
    v12 = 1;
  v13 = v12 + v10;  // 计算 v13 = v12 + v10
  *(this + 11) = v13;  // 写字段 this+11 ← v13
  if ( nArg3 != 0 || v13 < 5 )
    v14 = (v13 - 1) / 2;
  else
    v14 = 2;
  pObj = *this;
  fld_e12 = 13 * *(this + 12) + 15;  // this+12 物品类型号
  v17 = *this == 0;
  *(this + 13) = v14;  // 写字段 this+13 ← v14
  *(this + 14) = fld_e12;  // 写字段 this+14 ← fld_e12
  if ( !v17 )  // 若 !v17
  {
    *(this + 14) += (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 192))(pObj) + 3;  // 虚调用 vt+192（pObj）取尺寸/包围盒
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*this + 40))(*this, 18) != 0 )  // 虚调用 vt+40（this）条件查询(273等)
    {
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)*this + 360))(*this) == 0;  // 虚调用 vt+360（this 虚表槽）
      fld_e14 = *(this + 14);  // 读字段 fld_e14 = this+14
      if ( v17 )  // 若 v17
        v19 = fld_e14 + 14;  // 计算 v19 = fld_e14 + 14
      else
        v19 = fld_e14 + 30;  // 计算 v19 = fld_e14 + 30
      *(this + 14) = v19;  // 写字段 this+14 ← v19
    }
  }
  pThis_1 = (int)(this + 1);
  *((uint8_t *)this + 17) = 0;  // 写字段 this+17（bEnable）
  *((uint8_t *)this + 18) = 0;  // 写字段 this+18（bDragChild）
  if ( nArg4 == -1 )
    result = sub_698F90(pThis_1, 3000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  else
    result = sub_698F90(pThis_1, nArg4, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint8_t *)this + 40) = 1;  // 写字段 this+40（bStateSub40）
  return result;
}



// ------------------------------------------------------------
// 0x50F040 sub_50F040 —— vector 超长异常（length_error，不返回）
//   vector<T> too long 标准抛出，与 ·0x50F360 同构。
// ------------------------------------------------------------
void /*noreturn*/ sub_50F040()  // sub_50F040 —— vector 超长异常（length_error，不返回）
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
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x50F0B0 sub_50F0B0 —— nengine::CNText 构造（挂 vftbl + 初始化）
//   挂 vftbl_nengine__CNText、+4..+24 清零后 ·sub_69D4E0/·sub_69D150(nArg2,nArg3,nArg4) 初始化文本字段。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_50F0B0(uint8_t *this, int nArg2, int nArg3, int nArg4)  // sub_50F0B0 —— nengine::CNText 构造（挂 vftbl + 初始化）
{
  *(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(uint32_t *)this = &vftbl_nengine__CNText;
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 5) = 0;  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 6) = 0;  // 写字段 this[6]（宽4字节）
  sub_69D4E0();  // 调 sub_69D4E0
  sub_69D150(nArg2, nArg3, nArg4);  // 调 sub_69D150
  return this;
}



// ------------------------------------------------------------
// 0x50F120 nengine__CNText__vmt0 —— CNText 析构（标志位 1 释放）
//   ·sub_50F150 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNText__vmt0(void *Block, char pszArg2)  // CNText 析构（标志位 1 释放）
{
  sub_50F150();  // sub_50F150 —— CNText 析构核心（释放缓冲并挂回基类）
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50F150 sub_50F150 —— CNText 析构核心（释放缓冲并挂回基类）
//   挂 vftbl_nengine__CNText、·sub_69D550 清理、free +16 并清零 +16/+20/+24，末挂 vftbl_nengine__IObject。
// ------------------------------------------------------------
void /*thiscall*/ sub_50F150(void **this)  // sub_50F150 —— CNText 析构核心（释放缓冲并挂回基类）
{
  *this = &vftbl_nengine__CNText;  // 装虚表/取地址：← vftbl_nengine__CNText
  sub_69D550();  // 调 sub_69D550
  if ( *(this + 4) != nullptr )  // 若 *(this + 4) != nullptr
    j__free(*(this + 4));  // 释放堆块
  *(this + 4) = nullptr;  // 写字段 this+4（pHostObj） ← nullptr
  *(this + 5) = nullptr;  // 写字段 this+5 ← nullptr
  *(this + 6) = nullptr;  // 写字段 this+6 ← nullptr
  *((uint8_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *this = &vftbl_nengine__IObject;  // 装虚表/取地址：← vftbl_nengine__IObject
}



// ------------------------------------------------------------
// 0x50F1C0 sub_50F1C0 —— 气泡文本宿主绑定（建 96B CNText + 取屏幕边界）
//   绑定宿主 *this=Block 与宽 this+60=nArg3；operator new(0x60) 建 CNText（dword_79C0B0, 2048, nArg3）并配
//   +56 上下文 dword_99FCCC、+64=1、+80=-1、+92=nArg4；this+64=nArg4、this+36=屏幕对象 +60 值。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F1C0(uint32_t *this, void *Block, int nArg3, int nArg4)  // sub_50F1C0 —— 结果 = 气泡文本宿主绑定（建 96B CNText + 取屏幕边界）
{
  uint8_t *pMem; // eax
  uint8_t *v6; // eax
  int v7; // eax
  int v8; // edx

  *this = Block;  // *this 写入 Block
  *(this + 15) = nArg3;  // 写字段 this+15 ← nArg3
  pMem = operator new(0x60u);  // 堆分配
  if ( pMem != nullptr )
    v6 = sub_50F0B0(pMem, dword_79C0B0, 2048, nArg3);  // sub_50F0B0 —— nengine::CNText 构造（挂 vftbl + 初始化）
  else
    v6 = nullptr;  // v6 = nullptr 空指针
  *(this + 8) = v6;  // 写字段 this+8（nSkillRec8） ← v6
  *((uint32_t *)v6 + 14) = dword_99FCCC;  // 写字段 v6[14]（宽4字节）
  *(uint32_t *)(*(this + 8) + 64) = 1;  // this+8 物品 id
  *(uint32_t *)(*(this + 8) + 80) = -1;  // this+8 物品 id
  *(uint32_t *)(*(this + 8) + 92) = nArg4;  // this+8 物品 id
  v7 = *(uint32_t *)(dword_99FCC8 + 20);  // dword_99FCC8 —— nengine::CNSlider 构造
  v8 = *(uint32_t *)(v7 + 60);  // 读字段 v8 = v7+60（nFadeValue60）
  *(this + 16) = nArg4;  // 写字段 this+16（nChannelTypeSel） ← nArg4
  *(this + 9) = v8;  // 写字段 this+9 ← v8
  return v7 + 60;  // 返回内嵌子对象/缓冲指针（v7+60）
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
uint32_t */*thiscall*/ sub_50F270(uint32_t *this, int nArg2, int nArg3)  // sub_50F270 —— CNChangeMp 构造（vftbl_CNChangeMp + sub_602070 基类 + sub_602380 初值）
{
  sub_4B1030();  // sub_4B1030 —— IRDAppendage 基类构造
  *this = &vftbl_CNChangeMp;  // 装虚表/取地址：← vftbl_CNChangeMp
  sub_602070(this);  // sub_602070 —— 精灵字段复位
  sub_602380(nArg2, nArg3);  // sub_602380 —— 出生装配（MpUp.ani）
  return this;
}



// ------------------------------------------------------------
// 0x50F2D0 CNChangeMp__vmt0 —— CNChangeMp 析构（标志位 1 释放）
//   ·sub_50F300 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNChangeMp__vmt0(void *Block, char pszArg2)  // CNChangeMp 析构（标志位 1 释放）
{
  sub_50F300();  // sub_50F300 —— CNChangeMp 析构核心（三层基类链）
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50F300 sub_50F300 —— CNChangeMp 析构核心（三层基类链）
//   挂 vftbl_CNChangeMp → ·sub_602400 清理 → 挂 vftbl_IRDAppendage 调 ·sub_5F6640 → +8 处挂 IObject 虚表。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F300(uint32_t *this)  // sub_50F300 —— CNChangeMp 析构核心（三层基类链）
{
  int result; // eax

  *this = &vftbl_CNChangeMp;  // 装虚表/取地址：← vftbl_CNChangeMp
  sub_602400();  // sub_602400 —— 动画件析构
  *this = &vftbl_IRDAppendage;  // 装虚表/取地址：← vftbl_IRDAppendage
  result = sub_5F6640(this);  // 调 sub_5F6640
  *(this + 2) = &vftbl_nengine__IObject;  // 写字段 this+2 ← &vftbl_nengine__IObject
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  return result;
}



// ------------------------------------------------------------
// 0x50F360 sub_50F360 —— vector 超长异常（length_error，不返回）
//   vector<T> too long 标准抛出，由 ·0x50F440 扩容路径消费。
// ------------------------------------------------------------
void /*noreturn*/ sub_50F360()  // sub_50F360 —— vector 超长异常（length_error，不返回）
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
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x50F3D0 sub_50F3D0 —— 对象大块字段复位（+1348..+1436）【推断：技能树/状态 UI】
//   清零 +1348/+1352、释放 +1360 段；+1372 起 15 个 int 置 -1（无效槽），三标志置 0、+1436=4；返回 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F3D0(int this)  // sub_50F3D0 —— 对象大块字段复位（+1348..+1436）【推断：技能树/状态 UI】
{
  *(uint32_t *)(this + 1348) = 0;  // 写字段 this+1348 ← 0
  *(uint32_t *)(this + 1352) = 0;  // 写字段 this+1352 ← 0
  if ( *(uint32_t *)(this + 1360) != 0 )  // 若 *(uint32_t *)(this + 1360) != 0
    j__free(*(void **)(this + 1360));  // 释放堆块
  *(uint32_t *)(this + 1360) = 0;  // 写字段 this+1360 ← 0
  *(uint32_t *)(this + 1364) = 0;  // 写字段 this+1364 ← 0
  *(uint32_t *)(this + 1368) = 0;  // 写字段 this+1368 ← 0
  memset((void *)(this + 1372), 0xFFu, 0x3Cu);  // 调 memset 按字节填充
  *(uint8_t *)(this + 1432) = 0;  // 写字段 this+1432（bTriggerLatch1432） ← 0
  *(uint8_t *)(this + 1433) = 0;  // 写字段 this+1433（bTriggerSub1433） ← 0
  *(uint8_t *)(this + 1434) = 0;  // 写字段 this+1434 ← 0
  *(uint32_t *)(this + 1436) = 4;  // 写字段 this+1436（nSceneType1436） ← 4
  return -1;  // 返回 -1（0xFFFFFFFF）
}



// ------------------------------------------------------------
// 0x50F440 sub_50F440 —— 8 字节元素向量插入（三路分支 + 1.5 倍扩容）
//   就地 ·sub_44BD30/·sub_44BD00 搬移 + ·sub_41FEB0 填充；重建 operator new 8×n + ·sub_63A7C0 填洞；
//   超限 ·sub_50F360。
// ------------------------------------------------------------
void /*thiscall*/ sub_50F440(int this, int nArg2, unsigned int uArg3, int pArg4)  // sub_50F440 —— 8 字节元素向量插入（三路分支 + 1.5 倍扩容）
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
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
    else
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )
      sub_50F360(this);  // sub_50F360 —— vector 超长异常（length_error，不返回）
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
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
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
        else
          fld_88 = 0;
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
        fld_89 = 0;
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
// 0x50F690 sub_50F690 —— CNActiveStatusStackable 析构核心
//   挂 vftbl_CNActiveStatusStackable、nullsub_3，释放 +168 段并清零 +168..+176，末 ·sub_485B50（CNRDStackable 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F690(void **this)  // sub_50F690 —— CNActiveStatusStackable 析构核心
{
  *this = &vftbl_CNActiveStatusStackable;  // 装虚表/取地址：← vftbl_CNActiveStatusStackable
  nullsub_3();  // 空桩函数（无操作）
  if ( *(this + 42) != nullptr )  // 若 *(this + 42) != nullptr
    j__free(*(this + 42));  // 释放堆块
  *(this + 42) = nullptr;  // 写字段 this+42 ← nullptr
  *(this + 43) = nullptr;  // 写字段 this+43 ← nullptr
  *(this + 44) = nullptr;  // 写字段 this+44（nExpireMs） ← nullptr
  return sub_485B50(this);  // sub_485B50 —— CNRDStackable 析构
}



// ------------------------------------------------------------
// 0x50F710 CNActiveStatusStackable__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50F690 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void **/*thiscall*/ CNActiveStatusStackable__vmt4(void **Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50F690(Block);  // sub_50F690 —— CNActiveStatusStackable 析构核心
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50F740 sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
//   ·sub_485CC0（IRDItem 核心构造）后挂 vftbl_CNRDStackable，+148=8/+152=-1 等槽初值，
//   ·sub_577FF0、·sub_578610(ArgList) 掉落物动画驱动。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50F740(uint32_t *this, char ArgList)  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
{
  sub_485CC0();  // sub_485CC0 —— IRDItem 核心构造（+132 转 clong 子对象）
  *this = &vftbl_CNRDStackable;  // 装虚表/取地址：← vftbl_CNRDStackable
  *(this + 37) = 8;  // 写字段 this+37（bFadeFlag37） ← 8
  *(this + 38) = -1;  // 写字段 this+38（bFadeFlag38） ← -1
  *(this + 39) = 0;  // 写字段 this+39 ← 0
  *((uint8_t *)this + 160) = 0;  // 写字段 this+160（fAdd160）
  sub_577FF0(this);  // sub_577FF0 —— 10 行小函数
  sub_578610(ArgList);  // sub_578610 —— 掉落物动画驱动（442D00 + 578340）
  return this;
}



// ------------------------------------------------------------
// 0x50F7C0 sub_50F7C0 —— CNIncreaseStatusStackable 构造
//   ·sub_50F740 基类后挂 vftbl_CNIncreaseStatusStackable。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50F7C0(uint32_t *this, char pszArg2)  // sub_50F7C0 —— 返回 CNIncreaseStatusStackable 构造(Block)
{
  sub_50F740(this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *this = &vftbl_CNIncreaseStatusStackable;  // 装虚表/取地址：← vftbl_CNIncreaseStatusStackable
  return this;
}



// ------------------------------------------------------------
// 0x50F7F0 sub_50F7F0 —— CNItemScreamOfHysma 构造
//   ·sub_50F740 基类后挂 vftbl_CNItemScreamOfHysma。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50F7F0(uint32_t *this, char pszArg2)  // sub_50F7F0 —— 返回 CNItemScreamOfHysma 构造(Block)
{
  sub_50F740(this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *this = &vftbl_CNItemScreamOfHysma;  // 装虚表/取地址：← vftbl_CNItemScreamOfHysma
  return this;
}



// ------------------------------------------------------------
// 0x50F810 CNItemScreamOfHysma__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50F840 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNItemScreamOfHysma__vmt4(void *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50F840();  // sub_50F840 —— CNItemScreamOfHysma 析构核心
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50F840 sub_50F840 —— CNItemScreamOfHysma 析构核心
//   挂 vftbl_CNItemScreamOfHysma 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F840(uint32_t *this)  // sub_50F840 —— CNItemScreamOfHysma 析构核心
{
  *this = &vftbl_CNItemScreamOfHysma;  // 装虚表/取地址：← vftbl_CNItemScreamOfHysma
  return sub_485B50(this);  // sub_485B50 —— CNRDStackable 析构
}



// ------------------------------------------------------------
// 0x50F850 sub_50F850 —— CNAppendageStackable 构造（记录追加初始化）
//   ·sub_50F740 后挂 vftbl_CNAppendageStackable，+168..+188 槽初值（+180=17 类型字、+192=1），
//   ·sub_602E40 释放旧段、·sub_6032D0(nArg3,nArg4) 追加记录。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F850(int this, char pszArg2, int nArg3, int nArg4)  // sub_50F850 —— 返回 CNAppendageStackable 记录追加构造(Block=6511, 效果对象=v98, 类型字=36)
{
  sub_50F740((uint32_t *)this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *(uint32_t *)this = &vftbl_CNAppendageStackable;
  *(uint32_t *)(this + 168) = 0;  // 写字段 this+168（pAppendVec） ← 0
  *(uint32_t *)(this + 172) = 0;  // 写字段 this+172（pAppendVecEnd） ← 0
  *(uint32_t *)(this + 176) = 0;  // 写字段 this+176（pAppendVecCap） ← 0
  *(uint8_t *)(this + 192) = 1;  // 写字段 this+192（nDlgId） ← 1
  *(uint32_t *)(this + 180) = 17;  // 写字段 this+180（nRadius） ← 17
  *(uint32_t *)(this + 184) = 0;  // 写字段 this+184（bSingleTarget） ← 0
  *(uint32_t *)(this + 188) = 0;  // 写字段 this+188（nStatusIdx） ← 0
  sub_602E40(this);  // sub_602E40 —— vector 底层数组释放
  sub_6032D0(nArg3, nArg4);  // sub_6032D0 —— 记录追加薄封装（8B）
  return this;
}



// ------------------------------------------------------------
// 0x50F8E0 CNAppendageStackable__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50F910 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNAppendageStackable__vmt4(void *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50F910();  // sub_50F910 —— CNAppendageStackable 析构核心
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50F910 sub_50F910 —— CNAppendageStackable 析构核心
//   挂 vftbl_CNAppendageStackable、·sub_602DE0 释放 8 字节槽表、free +168 段，末 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50F910(void **this)  // sub_50F910 —— CNAppendageStackable 析构核心
{
  *this = &vftbl_CNAppendageStackable;  // 装虚表/取地址：← vftbl_CNAppendageStackable
  sub_602DE0();  // sub_602DE0 —— 8 字节槽表释放
  if ( *(this + 42) != nullptr )  // 若 *(this + 42) != nullptr
    j__free(*(this + 42));  // 释放堆块
  *(this + 42) = nullptr;  // 写字段 this+42 ← nullptr
  *(this + 43) = nullptr;  // 写字段 this+43 ← nullptr
  *(this + 44) = nullptr;  // 写字段 this+44（nExpireMs） ← nullptr
  return sub_485B50(this);  // sub_485B50 —— CNRDStackable 析构
}



// ------------------------------------------------------------
// 0x50F990 sub_50F990 —— 与 ·0x50F850 同构（差异：末步 ·sub_603300 三参追加）
// ------------------------------------------------------------
int /*thiscall*/ sub_50F990(int this, char pszArg2, int nArg3, int nArg4, int nArg5)  // sub_50F990 —— 返回 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=2)
{
  sub_50F740((uint32_t *)this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *(uint32_t *)this = &vftbl_CNAppendageStackable;
  *(uint32_t *)(this + 168) = 0;  // 写字段 this+168（pAppendVec） ← 0
  *(uint32_t *)(this + 172) = 0;  // 写字段 this+172（pAppendVecEnd） ← 0
  *(uint32_t *)(this + 176) = 0;  // 写字段 this+176（pAppendVecCap） ← 0
  *(uint8_t *)(this + 192) = 1;  // 写字段 this+192（nDlgId） ← 1
  *(uint32_t *)(this + 180) = 17;  // 写字段 this+180（nRadius） ← 17
  *(uint32_t *)(this + 184) = 0;  // 写字段 this+184（bSingleTarget） ← 0
  *(uint32_t *)(this + 188) = 0;  // 写字段 this+188（nStatusIdx） ← 0
  sub_602E40(this);  // sub_602E40 —— vector 底层数组释放
  sub_603300(nArg3, nArg4, nArg5);  // 调 sub_603300
  return this;
}



// ------------------------------------------------------------
// 0x50FA30 sub_50FA30 —— CNCoinOfFortune 构造
//   ·sub_50F740 基类后挂 vftbl_CNCoinOfFortune。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FA30(uint32_t *this, char pszArg2)  // sub_50FA30 —— 返回 CNCoinOfFortune 幸运硬币(Block)
{
  sub_50F740(this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *this = &vftbl_CNCoinOfFortune;  // 装虚表/取地址：← vftbl_CNCoinOfFortune
  return this;
}



// ------------------------------------------------------------
// 0x50FA50 CNCoinOfFortune__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50FA80 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNCoinOfFortune__vmt4(void *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50FA80();  // sub_50FA80 —— CNCoinOfFortune 析构核心
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50FA80 sub_50FA80 —— CNCoinOfFortune 析构核心
//   挂 vftbl_CNCoinOfFortune 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FA80(uint32_t *this)  // sub_50FA80 —— CNCoinOfFortune 析构核心
{
  *this = &vftbl_CNCoinOfFortune;  // 装虚表/取地址：← vftbl_CNCoinOfFortune
  return sub_485B50(this);  // sub_485B50 —— CNRDStackable 析构
}



// ------------------------------------------------------------
// 0x50FA90 sub_50FA90 —— CNTouchOfRemy 构造
//   ·sub_50F740 基类后挂 vftbl_CNTouchOfRemy。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FA90(uint32_t *this, char pszArg2)  // sub_50FA90 —— CNTouchOfRemy 构造
{
  sub_50F740(this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *this = &vftbl_CNTouchOfRemy;  // 装虚表/取地址：← vftbl_CNTouchOfRemy
  return this;
}



// ------------------------------------------------------------
// 0x50FAB0 CNTouchOfRemy__vmt88 —— 雷米援助施放（HP/MP 双 30% 恢复）
//   基类 ·CNRDStackable__vmt88 后按 vmt740/vmt756（当前 HP/MP【推断】）×30%：HP → ·sub_4D6810（CNChangeHp，1000ms）、
//   MP → ·sub_50F270（CNChangeMp，1000ms）；各经 vt+56 施放。
// ------------------------------------------------------------
int /*stdcall*/ CNTouchOfRemy__vmt88(int nArg1, int nArg2, void *Block)  // 函数: 雷米援助施放（HP/MP 双 30% 恢复）
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
    v9 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 740))(nArg1) * 0.30000001);  // 虚调用 vt+740（nArg1 虚表槽）
    v4 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 756))(nArg1) * 0.30000001);  // 虚调用 vt+756（nArg1 虚表槽）
    if ( operator new(0x80u) != nullptr )  // 堆分配
    {
      v8 = (float)v9;
      pObj = sub_4D6810(LODWORD(v8), 1000, 0, 1);  // sub_4D6810 —— 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
    }
    else
    {
      pObj = 0;
    }
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(pObj, nArg1, nArg1, 0, 0, 0, -1);  // 虚调用 vt+56（pObj 虚表槽）
    pMem = operator new(0x64u);  // 堆分配
    if ( pMem != nullptr )
      v7 = sub_50F270(pMem, v4, 1000);  // sub_50F270 —— CNChangeMp 构造（vftbl_CNChangeMp + sub_602070 基类 + sub_602380 初值）
    else
      v7 = nullptr;  // v7 = nullptr 空指针
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*v7 + 56))(v7, nArg1, nArg1, 0, 0, 0, -1);  // 虚调用 vt+56（v7 虚表槽）
  }
  return result;
}



// ------------------------------------------------------------
// 0x50FBC0 CNTouchOfRemy__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50FBF0 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNTouchOfRemy__vmt4(void *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50FBF0();  // sub_50FBF0 —— CNTouchOfRemy 析构核心
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50FBF0 sub_50FBF0 —— CNTouchOfRemy 析构核心
//   挂 vftbl_CNTouchOfRemy 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FBF0(uint32_t *this)  // sub_50FBF0 —— CNTouchOfRemy 析构核心
{
  *this = &vftbl_CNTouchOfRemy;  // 装虚表/取地址：← vftbl_CNTouchOfRemy
  return sub_485B50(this);  // sub_485B50 —— CNRDStackable 析构
}



// ------------------------------------------------------------
// 0x50FC00 sub_50FC00 —— CNRateHpMp 构造（模式 + 回复率 + 时长）
//   ·sub_50F740 后挂 vftbl_CNRateHpMp；+164=nArg3（模式 0 HP/1 MP/2 双）、+168=nArg4（回复率）、+172=nArg5（时长）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FC00(uint32_t *this, char pszArg2, int nArg3, int nArg4, int nArg5)  // sub_50FC00 —— 返回 CNRateHpMp 回复率构造(模式=MP, 回复率=50, 时长=100)
{
  sub_50F740(this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *(this + 43) = nArg5;  // 写字段 this+43 ← nArg5
  *this = &vftbl_CNRateHpMp;  // 装虚表/取地址：← vftbl_CNRateHpMp
  *(this + 41) = nArg3;  // 写字段 this+41 ← nArg3
  *(this + 42) = nArg4;  // 写字段 this+42 ← nArg4
  return this;
}



// ------------------------------------------------------------
// 0x50FC40 CNRateHpMp__vmt88 —— HP/MP 比率回复施放（×0.01 换算）
//   基类后按模式（+164）：0 → vmt740×率×0.01 建 ·sub_4D6810；1 → vmt756×率×0.01 建 ·sub_50F270；
//   2 → 两者皆建；量值经 vt+56 施放（率标签 [MP regen speed rate] ×0.0099999998）。
// ------------------------------------------------------------
int /*thiscall*/ CNRateHpMp__vmt88(int *this, int nArg2, void *Block, void *pArg4)  // 函数: HP/MP 比率回复施放（×0.01 换算）
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
    result = *(this + 41);  // 读字段 result = this+41
    if ( result != 0 )  // result=this+164 第 5 组·+88 增量子倍率
    {
      if ( result == 1 )  // result=this+164 第 5 组·+88 增量子倍率
      {
        fld_e42 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2)  // 虚调用 vt+756（nArg2 虚表槽）
                              * ((double)*(this + 42)  // HP/MP 比率回复施放（×0.01 换算）
                               * 0.0099999998));
        pMem = operator new(0x64u);  // 堆分配
      }
      else
      {
        if ( result != 2 )  // result=this+164 第 5 组·+88 增量子倍率
          return result;  // result=this+164 第 5 组·+88 增量子倍率
        fld_e422 = (void *)(uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2)  // 虚调用 vt+740（nArg2 虚表槽）
                                       * ((double)*(this + 42)
                                        * 0.0099999998));
        if ( operator new(0x80u) != nullptr )  // 堆分配
        {
          v11 = (float)(int)fld_e422;
          fld_e43 = sub_4D6810(LODWORD(v11), *(this + 43), 0, 1);  // sub_4D6810 —— 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
        }
        else
        {
          fld_e43 = 0;
        }
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)fld_e43 + 56))(  // 虚调用 vt+56（fld_e43 虚表槽）
          fld_e43,
          nArg2,
          nArg2,
          0,
          0,
          0,
          -1);
        fld_e42 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2)  // 虚调用 vt+756（nArg2 虚表槽）
                              * ((double)*(this + 42)
                               * 0.0099999998));
        pMem = operator new(0x64u);  // 堆分配
      }
      if ( pMem != nullptr )
      {
        fld_e432 = sub_50F270(pMem, fld_e42, *(this + 43));  // sub_50F270 —— CNChangeMp 构造（vftbl_CNChangeMp + sub_602070 基类 + sub_602380 初值）
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*fld_e432 + 56))(  // 虚调用 vt+56（fld_e432 虚表槽）
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
      fld_e423 = (void *)(uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2)  // 虚调用 vt+740（nArg2 虚表槽）
                                     * ((double)*(this + 42)
                                      * 0.0099999998));
      if ( operator new(0x80u) != nullptr )  // 堆分配
      {
        v10 = (float)(int)fld_e423;
        fld_e432 = (uint32_t *)sub_4D6810(LODWORD(v10), *(this + 43), 0, 1);  // sub_4D6810 —— 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*fld_e432 + 56))(  // 虚调用 vt+56（fld_e432 虚表槽）
                 fld_e432,
                 nArg2,
                 nArg2,
                 0,
                 0,
                 0,
                 -1);
      }
    }
    fld_e432 = nullptr;  // fld_e432 = nullptr 空指针
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*fld_e432 + 56))(fld_e432, nArg2, nArg2, 0, 0, 0, -1);  // 虚调用 vt+56（fld_e432 虚表槽）
  }
  return result;  // result=this+164 第 5 组·+88 增量子倍率
}



// ------------------------------------------------------------
// 0x50FE30 CNRateHpMp__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50FE60 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNRateHpMp__vmt4(void *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50FE60();  // sub_50FE60 —— CNRateHpMp 析构核心
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50FE60 sub_50FE60 —— CNRateHpMp 析构核心
//   挂 vftbl_CNRateHpMp 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FE60(uint32_t *this)  // sub_50FE60 —— CNRateHpMp 析构核心
{
  *this = &vftbl_CNRateHpMp;  // 装虚表/取地址：← vftbl_CNRateHpMp
  return sub_485B50(this);  // sub_485B50 —— CNRDStackable 析构
}



// ------------------------------------------------------------
// 0x50FE70 sub_50FE70 —— CNCallStorageBird 构造
//   ·sub_50F740 基类后挂 vftbl_CNCallStorageBird。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FE70(uint32_t *this, char pszArg2)  // sub_50FE70 —— CNCallStorageBird 构造
{
  sub_50F740(this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *this = &vftbl_CNCallStorageBird;  // 装虚表/取地址：← vftbl_CNCallStorageBird
  return this;
}



// ------------------------------------------------------------
// 0x50FE90 CNCallStorageBird__vmt88 —— 仓库鸟拾取动画施放（本地玩家限定）
//   仅当 pDwArg1 == dword_8F7C04（本地玩家）时经 vt+580 播放 51200 号动画，参数含当前档位 ·sub_50D910。
// ------------------------------------------------------------
int /*stdcall*/ CNCallStorageBird__vmt88(int *pDwArg1, int nArg2, int nArg3)  // 函数: 仓库鸟拾取动画施放（本地玩家限定）
{
  int result; // eax
  int v4; // edi
  int v5; // eax

  result = CNRDStackable__vmt88(pDwArg1, nArg2, nArg3);
  if ( pDwArg1 != nullptr && pDwArg1 == (int *)dword_8F7C04 )  // dword_8F7C04（本地玩家对象）
  {
    v4 = *pDwArg1;
    v5 = sub_50D910();  // sub_50D910 —— 结果 = 当前档位号读取
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
void */*thiscall*/ CNCallStorageBird__vmt4(void *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50FF20();  // sub_50FF20 —— CNCallStorageBird 析构核心
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50FF20 sub_50FF20 —— CNCallStorageBird 析构核心
//   挂 vftbl_CNCallStorageBird 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FF20(uint32_t *this)  // sub_50FF20 —— CNCallStorageBird 析构核心
{
  *this = &vftbl_CNCallStorageBird;  // 装虚表/取地址：← vftbl_CNCallStorageBird
  return sub_485B50(this);  // sub_485B50 —— CNRDStackable 析构
}



// ------------------------------------------------------------
// 0x50FF30 sub_50FF30 —— CNOmozzaOfWorld 构造
//   ·sub_50F740 后挂 vftbl_CNOmozzaOfWorld；+164/+168 存两参、+172 存标志。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FF30(int this, char pszArg2, int nArg3, int nArg4, char pszArg5)  // sub_50FF30 —— 返回 CNOmozzaOfWorld 构造(Block, 0, 0, 0)
{
  sub_50F740((uint32_t *)this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *(uint8_t *)(this + 172) = pszArg5;  // 写字段 this+172（pAppendVecEnd） ← pszArg5
  *(uint32_t *)this = &vftbl_CNOmozzaOfWorld;
  *(uint32_t *)(this + 164) = nArg3;  // 写字段 this+164（fAdd164） ← nArg3
  *(uint32_t *)(this + 168) = nArg4;  // 写字段 this+168（pAppendVec） ← nArg4
  return this;
}



// ------------------------------------------------------------
// 0x50FF70 CNOmozzaOfWorld__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50FFA0 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNOmozzaOfWorld__vmt4(void *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50FFA0();  // sub_50FFA0 —— CNOmozzaOfWorld 析构核心
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x50FFA0 sub_50FFA0 —— CNOmozzaOfWorld 析构核心
//   挂 vftbl_CNOmozzaOfWorld 后转 ·sub_485B50。
// ------------------------------------------------------------
int /*thiscall*/ sub_50FFA0(uint32_t *this)  // sub_50FFA0 —— CNOmozzaOfWorld 析构核心
{
  *this = &vftbl_CNOmozzaOfWorld;  // 装虚表/取地址：← vftbl_CNOmozzaOfWorld
  return sub_485B50(this);  // sub_485B50 —— CNRDStackable 析构
}



// ------------------------------------------------------------
// 0x50FFB0 sub_50FFB0 —— CNUsableStackable 构造
//   ·sub_50F740 基类后挂 vftbl_CNUsableStackable。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_50FFB0(uint32_t *this, char pszArg2)  // sub_50FFB0 —— CNUsableStackable 构造
{
  sub_50F740(this, pszArg2);  // sub_50F740 —— CNRDStackable 基类构造（物品核心 + 掉落动画）
  *this = &vftbl_CNUsableStackable;  // 装虚表/取地址：← vftbl_CNUsableStackable
  return this;
}



// ------------------------------------------------------------
// 0x50FFD0 CNIncreaseStatusStackable__vmt4 —— 析构（标志位 1 释放自身）
//   ·sub_50F7E0 析构后按 pszArg2&1 释放 this。
// ------------------------------------------------------------
void */*thiscall*/ CNIncreaseStatusStackable__vmt4(void *Block, char pszArg2)  // 析构（标志位 1 释放自身）
{
  sub_50F7E0(Block);  // 调 sub_50F7E0
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}

