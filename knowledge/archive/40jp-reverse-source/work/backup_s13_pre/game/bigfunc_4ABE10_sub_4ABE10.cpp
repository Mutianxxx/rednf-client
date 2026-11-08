// ============================================================
// 【40JP逆向源代码工程】src/game/bigfunc_4ABE10_sub_4ABE10.cpp
// 模块: ★怪物对象工厂 sub_4ABE10（IRDMonster 派生类 new+构造 分发器）
//   身份直证：各 case 尾调的 sub_4AXXXX 构造函数体最后写 &CNXxx::vftable
//   （CNGoblinGoblin/CNTauArmy/CNWraith/... 定义见 src/game/rtti_core.cpp）；
//   基类链 IRDActiveObject ← IRDMonster（rtti_core.cpp §0x4A4EA0）。
//   调用方：sub_4471E0 case 0x16 实体批量生成、login_channel、
//   broadcast_debug、dragonman(0x47)/missing_monster(0xBB8=3000) 等。
// 来源: work/dump_misc_a.txt  区块: 0x4A（单独反编译，size=10050 字节）
// 层级: L2 转写层 + L1 分段精修（函数体零改动，仅插注释）
// 函数数: 1（单文件单函数）
// ------------------------------------------------------------
// ★ 函数签名解读：
//   sub_4ABE10(Block, a2, a3)
//   Block —— 怪物生成 ID（switch 分发键；基础段 1-703、万位段 3000/5001-5005/
//             40001-60010 为"复合 ID"，多数重映射到旧 1-200 体系的规范 ID 再构造）
//   a2    —— 怪物索引参数【推断】：原样转传构造函数第 2 参（ArgList），基类链尾
//             sub_4DB410 以其为 key 查怪物数据表（查无则 "MONSTER CREATE FAIL! INDEX %d"）
//   a3    —— 附加参数【推断】：仅 case 60010（CNProvocationDoll 挑动人偶）转传
// ★ 统一模式：operator new(0x21xx~0x23xx)（对象 ~8.5-9KB，大小随派生类微差）
//   → 构造函数(Block 或 规范ID, a2[, a3])；new 失败一律 return 0
// ★ 未知 Block 一律 return -842150451（= 0xCDCDCDCD，MSVC 调试堆填充值作错误码）
// ★ 本文件无字符串/资源引用（纯工厂分发）；构造函数本体见 rtti_core.cpp 与
//   creature/*.cpp（0x5C 蜘蛛）、ui/char_server_info.cpp（0x58 Ghoul 系）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 961 行；字符串证据 0 条；外调 6 个
//   调: sub_4ABE10 sub_4A5F10 sub_4A5DC0 sub_4A69E0 sub_4A6850 sub_4A62A0
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x4ABE10 sub_4ABE10  size=10050
// ------------------------------------------------------------
// ★ 怪物对象工厂（IRDMonster 派生类 new+构造）。分发树按 Block 值域四分：
//   段A ≤200 基础怪 / 段B 201-904 中段怪 / 段C 3000-50007 万位复合ID / 段D >50023 高位段
// ★ 分段地图（行号为精修后行号，约值）：
//   段A @~55-245   基础怪 ID：1-15 哥布林族 / 21-22 拉尔 / 31-40 石偶傀儡 / 50-53
//                  塞利翁龙 / 60-63 投掷卡格尔 / 70-71 飞艇
//   段B @~247-590  201-904：201-202 猎手 / 210-212 僵尸 / 220-222 空骨鱼 / 250-253
//                  星鱼 / 260-266 传教士系 / 270-273 攻城器 / 280-281 飞艇 / 400-408
//                  尸鬼系 / 410-430 蜘蛛系 / 500-502 洛迪戈 / 600-603 精灵系 / 700-762
//                  驱逐者军团 / 800 蝙蝠 / 900-904 特殊
//   段C @~592-802  3000-50007：3000-3002 boss / 5001-5005 卢加鲁系 / 40001-41005 哥布林
//                  镜像重映射 / 42001-43003 猎手僵尸镜像 / 50000-50007 复合
//   段D @~804-999  50023-60010：50023-50034 亚特拉斯巨人 / 50062-50069 守卫塔 / 60001-60010
//                  机器人与幻影
int /*cdecl*/ sub_4ABE10(int Block, void *pArg2, int nArg3)
{
  int result; // eax
  uint8_t *pMem10; // eax
  void *pMem11; // eax
  void *pMem12; // eax
  uint8_t *pMem13; // eax
  void *pMem14; // eax
  void *pMem15; // eax
  void *pMem9; // eax
  uint32_t **pMem8; // eax
  uint32_t *pMem7; // eax
  uint8_t *pMem; // eax
  void *pMem2; // eax
  uint8_t *pMem3; // eax
  uint8_t *pMem4; // eax
  uint32_t *pMem5; // eax
  uint8_t *pMem6; // eax
  uint32_t *pMem16; // eax

  // ── [段 1] 段A 总闸：Block ≤ 200 基础怪工厂入口（Block==200 旁路到段 5）──
  //   Block=怪物生成 ID（switch 分发键）；统一模式 operator new(0x21xx~0x23xx) 后交构造函数；
  //   new 失败 return 0；未知 ID 一律 return -842150451（= 0xCDCDCDCD 调试堆填充值当错误码）
  // --- 段A（约行 55-245）Block ≤ 200：基础怪 ID 工厂 ---
  if ( Block <= 200 )  // 总闸：怪物 ID ≤ 200 走本段
  {
    if ( Block != 200 )  // Block == 200 是特例（见段 7），其余进段A-1 主 switch
    {
      // --- 段A-1 case 1-15：哥布林族（CNGoblinGoblin/Stoner/IslandGab/MountainGab/
      //     Kinol/Gero/Lupete/Sharedo/CowardGoblin 等，构造见 rtti_core.cpp §0x4A5xxx）---
      // ── [段 2] 段A-1：case 1-15 —— 哥布林族（1-10）与牛头族（11-15）──
      //   1 CNGoblinGoblin / 2 CNGoblinStoner / 3 CNGoblinIslandGab / 4 CNGoblinMountainGab / 5 CNGoblinKinol / 6 CNGoblinGero / 7 CNGoblinLupete / 8 CNGoblinSharedo / 9 CNLightningKinol（落雷凯诺）/ 10 CNCowardGoblin / 11 CNTauArmy / 12 CNTauBeast / 13 CNTauAssaulter / 14 CNTauGuard / 15 CNTauTangas（沙乌塔）
      //   对象体 0x219C-0x21E8（~8.5KB）；类名取自 rtti_core.cpp 各构造末尾写 &CNXxxvftable 的直证
      switch ( Block )  // 按怪物 ID（Block）分派构造
      {
        case 1:  // case 1 = 怪物 ID 1（段A-1 哥布林族）
          if ( operator new(0x21E8u) == nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A5F10(Block, (int)pArg2);  // CNGoblinGoblin 构造，结果存 result
          break;  // 跳出该分支
        case 2:  // case 2 = 怪物 ID 2（段A-1 哥布林族）
          if ( operator new(0x21D0u) == nullptr )  // operator new(8656 字节=0x21D0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A5DC0(Block, (int)pArg2);  // CNGoblinStoner 构造，结果存 result
          break;  // 跳出该分支
        case 3:  // case 3 = 怪物 ID 3（段A-1 哥布林族）
          if ( operator new(0x21D0u) == nullptr )  // operator new(8656 字节=0x21D0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A69E0(Block, (int)pArg2);  // CNGoblinIslandGab 构造，结果存 result
          break;  // 跳出该分支
        case 4:  // case 4 = 怪物 ID 4（段A-1 哥布林族）
          if ( operator new(0x21D0u) == nullptr )  // operator new(8656 字节=0x21D0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A6850(Block, (int)pArg2);  // CNGoblinMountainGab 构造，结果存 result
          break;  // 跳出该分支
        case 5:  // case 5 = 怪物 ID 5（段A-1 哥布林族）
          if ( operator new(0x21E8u) == nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A62A0(Block, (int)pArg2);  // CNGoblinKinol 构造，结果存 result
          break;  // 跳出该分支
        case 6:  // case 6 = 怪物 ID 6（段A-1 哥布林族）
          if ( operator new(0x21E0u) == nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A6620(Block, (int)pArg2);  // CNGoblinGero 构造，结果存 result
          break;  // 跳出该分支
        case 7:  // case 7 = 怪物 ID 7（段A-1 哥布林族）
          if ( operator new(0x21D8u) == nullptr )  // operator new(8664 字节=0x21D8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A6B70(Block, (int)pArg2);  // CNGoblinLupete 构造，结果存 result
          break;  // 跳出该分支
        case 8:  // case 8 = 怪物 ID 8（段A-1 哥布林族）
          if ( operator new(0x21B0u) == nullptr )  // operator new(8624 字节=0x21B0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A6EE0(Block, (int)pArg2);  // CNGoblinSharedo 构造，结果存 result
          break;  // 跳出该分支
        case 9:  // case 9 = 怪物 ID 9（段A-1 落雷凯诺）
          if ( operator new(0x21BCu) == nullptr )  // operator new(8636 字节=0x21BC) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7280(Block, (int)pArg2);  // CNLightningKinol 构造，结果存 result
          break;  // 跳出该分支
        case 10:  // case 10 = 怪物 ID 10（段A-1 胆小哥布林）
          if ( operator new(0x21C8u) == nullptr )  // operator new(8648 字节=0x21C8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A73D0(Block, (int)pArg2);  // CNCowardGoblin 构造，结果存 result
          break;  // 跳出该分支
        case 11:  // case 11 = 怪物 ID 11（段A-1 牛头族）
          if ( operator new(0x219Cu) == nullptr )  // operator new(8604 字节=0x219C) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7520(Block, (int)pArg2);  // CNTauArmy 构造，结果存 result
          break;  // 跳出该分支
        case 12:  // case 12 = 怪物 ID 12（段A-1 牛头族）
          if ( operator new(0x21A4u) == nullptr )  // operator new(8612 字节=0x21A4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7640(Block, (int)pArg2);  // CNTauBeast 构造，结果存 result
          break;  // 跳出该分支
        case 13:  // case 13 = 怪物 ID 13（段A-1 牛头族）
          if ( operator new(0x21A0u) == nullptr )  // operator new(8608 字节=0x21A0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7760(Block, (int)pArg2);  // CNTauAssaulter 构造，结果存 result
          break;  // 跳出该分支
        case 14:  // case 14 = 怪物 ID 14（段A-1 牛头族）
          if ( operator new(0x21A8u) == nullptr )  // operator new(8616 字节=0x21A8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7900(Block, (int)pArg2);  // CNTauGuard 构造，结果存 result
          break;  // 跳出该分支
        case 15:  // case 15 = 怪物 ID 15（段A-1 牛头族）
          if ( operator new(0x21A0u) == nullptr )  // operator new(8608 字节=0x21A0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7A20(Block, (int)pArg2);  // CNTauTangas 构造，结果存 result
          break;  // 跳出该分支
        // --- 段A-2 case 21/22 + case 31-40：园丁拉尔(CNGardener_Ral/CNVinoshu)与
        //     石偶傀儡系（CNGolemStone/Steel/Clay/Bronze/Gold/StoneMaster/SteelMaster/
        //     ClayMaster/MasterDogri，构造见 rtti_core.cpp §0x4A7Cxx-0x4A82xx）---
        // ── [段 3] 段A-2：case 21/22 + case 31-40 —— 园丁拉尔与石偶傀儡系 ──
        //   case 21 经 LABEL_32 与段D case 50024 共享 sub_4A5540（CNKeraha 克拉赫）；22 sub_4A5620（CNVinoshu 彼诺修）；
        //   31-35 石偶五型 CNDrakeStone/GolemStone/Steel/Clay/Bronze/Gold；37-40 大师级 StoneMaster/SteelMaster/ClayMaster/MasterDogri（人形师）
        case 21:  // case 21 = 怪物 ID 21（段A-2 克拉赫(与 50024 共享)）
          if ( operator new(0x21C8u) != nullptr )  // operator new(8648 字节=0x21C8) 分配怪物对象；成功则前往合流标签
            goto LABEL_32;  // 合流到 LABEL_32 = CNKeraha 构造（与 case 50024 共享）
          return 0;  // 分配失败 → 返回空指针 0
        case 22:  // case 22 = 怪物 ID 22（段A-2 彼诺修）
          if ( operator new(0x21D8u) == nullptr )  // operator new(8664 字节=0x21D8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A5620(Block, (int)pArg2);  // CNVinoshu 构造，结果存 result
          break;  // 跳出该分支
        case 31:  // case 31 = 怪物 ID 31（段A-2 石偶·石）
          if ( operator new(0x21E8u) == nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          // ── [段 4] 段A-2 之石偶五型清单：31 Stone / 32 Steel / 33 Clay / 34 Bronze / 35 Gold（构造体 0x21E4 齐平）──
          result = sub_4A7C90(Block, (int)pArg2);  // CNGolemStone 构造，结果存 result
          break;  // 跳出该分支
        case 32:  // case 32 = 怪物 ID 32（段A-2 石偶·钢）
          if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7D30(Block, (int)pArg2);  // CNGolemSteel 构造，结果存 result
          break;  // 跳出该分支
        case 33:  // case 33 = 怪物 ID 33（段A-2 石偶·黏土）
          if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7E30(Block, (int)pArg2);  // CNGolemClay 构造，结果存 result
          break;  // 跳出该分支
        case 34:  // case 34 = 怪物 ID 34（段A-2 石偶·青铜）
          if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7DD0(Block, (int)pArg2);  // CNGolemBronze 构造，结果存 result
          break;  // 跳出该分支
        case 35:  // case 35 = 怪物 ID 35（段A-2 石偶·金）
          if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7ED0(Block, (int)pArg2);  // CNGolemGold 构造，结果存 result
          break;  // 跳出该分支
        case 37:  // case 37 = 怪物 ID 37（段A-2 大师级·石）
          if ( operator new(0x21E0u) == nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          // ── [段 5] 段A-2 之大师级四型：37 StoneMaster / 38 SteelMaster / 39 ClayMaster / 40 MasterDogri（人形师）──
          result = sub_4A8120(Block, (int)pArg2);  // CNStoneMaster 构造，结果存 result
          break;  // 跳出该分支
        case 38:  // case 38 = 怪物 ID 38（段A-2 大师级·钢）
          if ( operator new(0x21E0u) == nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A8190(Block, (int)pArg2);  // CNSteelMaster 构造，结果存 result
          break;  // 跳出该分支
        case 39:  // case 39 = 怪物 ID 39（段A-2 大师级·黏土）
          if ( operator new(0x21E0u) == nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A8200(Block, (int)pArg2);  // CNClayMaster 构造，结果存 result
          break;  // 跳出该分支
        case 40:  // case 40 = 怪物 ID 40（段A-2 大师级·人形师）
          if ( operator new(0x21E0u) == nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A8270(Block, (int)pArg2);  // CNMasterDogri 构造，结果存 result
          break;  // 跳出该分支
        // --- 段A-3 case 50-53 + 60-63 + 70/71：塞利翁龙系（CNDrakeSerimalion/
        //     Loose/Harse/SelionTheFireBreather）、投掷卡格尔（CNGoblinBombKagel/
        //     SurikenKagel/BullsEye）、飞艇（CNNormalZepplin/CNCannonZepplin）---
        // ── [段 6] 段A-3：case 50-53 + 60/61/63 + 70/71 —— 塞利翁龙系 / 投掷卡格尔 / 龙人 ──
        //   case 50 走 LABEL_64（与段C case 50005 共享 sub_4A8680 CNDrakeSerimalion）；51 CNDrakeLooseSerimalion；
        //   52 CNDrakeHarseSerimalion；53 CNDrakeSelionTheFireBreather；60 CNGoblinBombKagel；61 CNGoblinSurikenKagel；
        //   63 CNGoblinAssaulter（与万位段 40001-41005 镜像同构造）；70 CNDracoMirkius；71 CNDracoLakius（鲁卡斯）
        case 50:  // case 50 = 怪物 ID 50（段A-3 塞利翁龙(与 50005 共享)）
          if ( operator new(0x226Cu) != nullptr )  // operator new(8812 字节=0x226C) 分配怪物对象；成功则前往合流标签
            goto LABEL_64;  // 合流到 LABEL_64 = CNDrakeSerimalion 构造（与 case 50005 共享）
          return 0;  // 分配失败 → 返回空指针 0
        case 51:  // case 51 = 怪物 ID 51（段A-3 塞利翁龙）
          if ( operator new(0x2280u) == nullptr )  // operator new(8832 字节=0x2280) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A87A0(Block, pArg2);  // CNDrakeLooseSerimalion 构造，结果存 result
          break;  // 跳出该分支
        case 52:  // case 52 = 怪物 ID 52（段A-3 塞利翁龙）
          if ( operator new(0x2250u) == nullptr )  // operator new(8784 字节=0x2250) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A8940(Block, (int)pArg2);  // CNDrakeHarseSerimalion 构造，结果存 result
          break;  // 跳出该分支
        case 53:  // case 53 = 怪物 ID 53（段A-3 塞利翁龙）
          if ( operator new(0x21C0u) == nullptr )  // operator new(8640 字节=0x21C0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A89C0(Block, (int)pArg2);  // CNDrakeSelionTheFireBreather 构造，结果存 result
          break;  // 跳出该分支
        case 60:  // case 60 = 怪物 ID 60（段A-3 投掷卡格尔·炸弹）
          if ( operator new(0x21E0u) == nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A6F60(Block, (int)pArg2);  // CNGoblinBombKagel 构造，结果存 result
          break;  // 跳出该分支
        case 61:  // case 61 = 怪物 ID 61（段A-3 投掷卡格尔·手里剑）
          if ( operator new(0x21E0u) == nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A7090(Block, (int)pArg2);  // CNGoblinSurikenKagel 构造，结果存 result
          break;  // 跳出该分支
        case 63:  // case 63 = 怪物 ID 63（段A-3 哥布林突击兵）
          if ( operator new(0x21E8u) == nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A60F0(Block, (int)pArg2);  // CNGoblinAssaulter 构造，结果存 result
          break;  // 跳出该分支
        case 70:  // case 70 = 怪物 ID 70（段A-3 龙人·米尔基乌斯）
          if ( operator new(0x21C0u) == nullptr )  // operator new(8640 字节=0x21C0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A9220(Block, (int)pArg2);  // CNDracoMirkius 构造，结果存 result
          break;  // 跳出该分支
        case 71:  // case 71 = 怪物 ID 71（段A-3 龙人·鲁卡斯）
          if ( operator new(0x21C0u) == nullptr )  // operator new(8640 字节=0x21C0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A9290(Block, (int)pArg2);  // CNDracoLakius 构造，结果存 result
          break;  // 跳出该分支
        default:  // 未列出的 ID → 落到 default
          return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
      }
      return result;  // 返回构造好的怪物对象指针
    }
    // ── [段 7] 段A-4 特例：Block == 200 走独立出口，规范 ID 200 直接构造（对象体 0x21CC）──
    // --- 段A-4 case 200：特例重映射 —— CNHunterHunter（规范 ID 200，构造 sub_4A8D60）---
    if ( operator new(0x21CCu) != nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；成功则前往合流标签
      return sub_4A8D60(200, (int)pArg2);  // CNHunterHunter 构造并把指针直接返回
    return 0;  // 分配失败 → 返回空指针 0
  }
  // ── [段 8] 段B 总闸：201 ≤ Block ≤ 904 中段怪工厂 ──
  //   内层两级阈值切分：先 904 特例，再按 406 / 700 分四支（>700 军团段、406<B≤700 支、B==406 特例、B<406 支）
  // --- 段B（约行 247-590）201 ≤ Block ≤ 904：中段怪 ID 工厂 ---
  if ( Block <= 904 )  // 总闸：怪物 ID ≤ 904 走本段
  {
    // ── [段 9] 段B-0 特例：Block == 904 重映射规范 ID 136 构造 CNSpikeKing（刺王，对象体 0x21FC）──
    // --- 段B-0 case 904：特例重映射 —— CNSpikeKing（规范 ID 136，构造 sub_4AB840）---
    if ( Block == 904 )  // 特例分支：怪物 ID == 904（见段注释）
    {
      if ( operator new(0x21FCu) != nullptr )  // operator new(8700 字节=0x21FC) 分配怪物对象；成功则前往合流标签
        return sub_4AB840(136, (int)pArg2);  // ? 构造并把指针直接返回
      return 0;  // 分配失败 → 返回空指针 0
    }
    if ( Block > 406 )  // 阈值切分：怪物 ID > 406
    {
      if ( Block > 700 )  // 阈值切分：怪物 ID > 700
      {
        // ── [段 10] 段B-4：Block 701-903 —— 驱逐者军团 + 蝙蝠 + 特殊怪（switch 12 case）──
        //   701 CNExpeller / 702 CNHeavenExpeller / 704 CNLegionExpeller / 705 CNAxionExpeller / 711 CNHammerKing / 750 CNEvilEye / 800 CNBat（对象体 0x2334 最大）；760/761/762 经 LABEL_183/185/187 与段D case 50030-50032 共享（CNAtlas/CNGoliath/CNTitan）；900 CNGoblinHodor / 902 CNLuis / 903 CNMonsterFlower
        // --- 段B-4 case 700：特例重映射 —— CNExpeller 驱逐者（规范 ID 188，构造
        //     sub_5D88C0，见 creature/expeller_guard.cpp）；701-762 驱逐者军团
        //     （Axe/Heaven/Legion/TinSwordMan/SandorExpeller/HammerKing/Axion/
        //     GuardLight/Goliath/Atlas/Titan 等）、800 蝙蝠 CNBat、900-904 特殊
        //     （GoblinHodor/Luis/MonsterFlower）---
        switch ( Block )  // 按怪物 ID（Block）分派构造
        {
          case 701:  // case 701 = 怪物 ID 701（段B-4 斧驱逐者）
            pMem = operator new(0x2274u);  // operator new(8820 字节=0x2274) 分配怪物对象并存入临时指针
            if ( pMem == nullptr )  // 分配失败则返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = (int)sub_5D7870(pMem, Block, (int)pArg2);  // CNAxeExpeller 构造，结果存 result
            break;  // 跳出该分支
          case 702:  // case 702 = 怪物 ID 702（段B-4 天界驱逐者）
            pMem2 = operator new(0x2288u);  // operator new(8840 字节=0x2288) 分配怪物对象并存入临时指针
            if ( pMem2 == nullptr )  // 分配失败则返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = (int)sub_5D7970(pMem2, Block, (int)pArg2);  // CNHeavenExpeller 构造，结果存 result
            break;  // 跳出该分支
          case 704:  // case 704 = 怪物 ID 704（段B-4 军团驱逐者）
            pMem3 = operator new(0x2284u);  // operator new(8836 字节=0x2284) 分配怪物对象并存入临时指针
            if ( pMem3 == nullptr )  // 分配失败则返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = (int)sub_5D7AE0(pMem3, Block, (int)pArg2, 1);  // CNLegionExpeller 构造，结果存 result
            break;  // 跳出该分支
          case 705:  // case 705 = 怪物 ID 705（段B-4 冲击驱逐者）
            pMem4 = operator new(0x2298u);  // operator new(8856 字节=0x2298) 分配怪物对象并存入临时指针
            if ( pMem4 == nullptr )  // 分配失败则返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = (int)sub_5D8A70(pMem4, Block, (int)pArg2, 1);  // CNTinSwordManExpeller 构造，结果存 result
            break;  // 跳出该分支
          case 711:  // case 711 = 怪物 ID 711（段B-4 锤王）
            if ( operator new(0x2334u) == nullptr )  // operator new(9012 字节=0x2334) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_5D7100(Block, (int)pArg2);  // CNHammerKing 构造，结果存 result
            break;  // 跳出该分支
          case 750:  // case 750 = 怪物 ID 750（段B-4 邪眼）
            if ( operator new(0x2218u) == nullptr )  // operator new(8728 字节=0x2218) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_5D9F50(Block, (int)pArg2);  // CNEvilEye 构造，结果存 result
            break;  // 跳出该分支
          case 760:  // case 760 = 怪物 ID 760（段B-4 亚特拉斯）
            if ( operator new(0x21FCu) != nullptr )  // operator new(8700 字节=0x21FC) 分配怪物对象；成功则前往合流标签
              goto LABEL_183;  // 合流到 LABEL_183 = CNAtlas 构造（与 case 760 共享）
            return 0;  // 分配失败 → 返回空指针 0
          case 761:  // case 761 = 怪物 ID 761（段B-4 歌利亚）
            if ( operator new(0x2210u) != nullptr )  // operator new(8720 字节=0x2210) 分配怪物对象；成功则前往合流标签
              goto LABEL_185;  // 合流到 LABEL_185 = CNGoliath 构造（与 case 761 共享）
            return 0;  // 分配失败 → 返回空指针 0
          case 762:  // case 762 = 怪物 ID 762（段B-4 泰坦）
            if ( operator new(0x21F8u) != nullptr )  // operator new(8696 字节=0x21F8) 分配怪物对象；成功则前往合流标签
              goto LABEL_187;  // 合流到 LABEL_187 = CNTitan 构造（与 case 762 共享）
            return 0;  // 分配失败 → 返回空指针 0
          case 800:  // case 800 = 怪物 ID 800（段B-4 蝙蝠）
            pMem5 = operator new(0x21B4u);  // operator new(8628 字节=0x21B4) 分配怪物对象并存入临时指针
            if ( pMem5 == nullptr )  // 分配失败则返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = (int)sub_5D8C80(pMem5, Block, (int)pArg2, 0);  // CNBat 构造，结果存 result
            break;  // 跳出该分支
          case 900:  // case 900 = 怪物 ID 900（段B-4 哥布林霍德尔）
            if ( operator new(0x221Cu) == nullptr )  // operator new(8732 字节=0x221C) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A6180(Block, (int)pArg2);  // CNGoblinHodor 构造，结果存 result
            break;  // 跳出该分支
          case 901:  // case 901 = 怪物 ID 901（段B-4 沙多驱逐者）
            pMem6 = operator new(0x2278u);  // operator new(8824 字节=0x2278) 分配怪物对象并存入临时指针
            if ( pMem6 == nullptr )  // 分配失败则返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = (int)sub_5D7C40(pMem6, Block, (int)pArg2, 1);  // CNSandorExpeller 构造，结果存 result
            break;  // 跳出该分支
          case 902:  // case 902 = 怪物 ID 902（段B-4 路易斯）
            if ( operator new(0x21A4u) == nullptr )  // operator new(8612 字节=0x21A4) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A5700(Block, (int)pArg2);  // CNLuis 构造，结果存 result
            break;  // 跳出该分支
          case 903:  // case 903 = 怪物 ID 903（段B-4 怪物花）
            if ( operator new(0x21A4u) == nullptr )  // operator new(8612 字节=0x21A4) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AB7B0(Block, (int)pArg2);  // CNMonsterFlower 构造，结果存 result
            break;  // 跳出该分支
          default:  // 未列出的 ID → 落到 default
            return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
        }
      }
      else
      {
        if ( Block == 700 )  // 特例分支：怪物 ID == 700（见段注释）
        {
          pMem7 = operator new(0x226Cu);  // operator new(8812 字节=0x226C) 分配怪物对象并存入临时指针
          if ( pMem7 != nullptr )  // 分配成功 → 直接构造并返回
            return (int)sub_5D88C0(pMem7, 188, (int)pArg2);  // CNExpeller 构造并把指针直接返回
          return 0;  // 分配失败 → 返回空指针 0
        }
        switch ( Block )  // 按怪物 ID（Block）分派构造
        {
          // ── [段 11] 段B-3（else 支 406 < Block ≤ 700）：岩浆尸鬼 / 蜘蛛系 / 洛迪戈 / 精灵 ──
          //   407/408 同一构造 sub_4A2330(Block, pArg2, 0/1) —— 第三参作变体开关（CNMagmaGhoul 双态）；
          //   410 CNWraith（怨灵）/ 411 CNWraithSpectress（女怨灵）/ 420 CNRollingSpider / 421 CNPoisonSpider / 422 CNAraclothoSpider / 430 CNYoungSpider（sub_5C1C00 单独 0x21C0）；500 CNDendroid / 501 CNGoliden / 502 CNRodinglo；
          //   600-603 经 LABEL_360/362/364/366 与段D case 60006-60009 共享（CNNaias/CNAdor/CNStalker/CNWisp 精灵系）
          // --- 段B-3 case 407/408 岩浆尸鬼 CNMagmaGhoul（nArg3 位作变体开关 0/1）、
        //     410-422 蜘蛛系（Wraith/WraithSpectress/RollingSpider/PoisonSpider/
        //     AraclothoSpider，构造见 creature/spider_trap.cpp）、430 幼蜘蛛
        //     CNYoungSpider（creature/）、500-502 洛迪戈（Goliden/Rodinglo）、
        //     600-603 → LABEL_360-366 精灵系（Naias/Ador/Stalker/Wisp）---
          case 407:  // case 407 = 怪物 ID 407（段B-3 岩浆尸鬼(变体0)）
            if ( operator new(0x21D4u) == nullptr )  // operator new(8660 字节=0x21D4) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A2330(Block, pArg2, 0);  // CNMagmaGhoul 构造，结果存 result
            break;  // 跳出该分支
          case 408:  // case 408 = 怪物 ID 408（段B-3 岩浆尸鬼(变体1)）
            if ( operator new(0x21D4u) == nullptr )  // operator new(8660 字节=0x21D4) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A2330(Block, pArg2, 1);  // CNMagmaGhoul 构造，结果存 result
            break;  // 跳出该分支
          case 410:  // case 410 = 怪物 ID 410（段B-3 怨灵）
            if ( operator new(0x21CCu) == nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AA4E0(Block, (int)pArg2);  // CNWraith 构造，结果存 result
            break;  // 跳出该分支
          case 411:  // case 411 = 怪物 ID 411（段B-3 女怨灵）
            if ( operator new(0x2200u) == nullptr )  // operator new(8704 字节=0x2200) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AA610(Block, (int)pArg2);  // CNWraithSpectress 构造，结果存 result
            break;  // 跳出该分支
          case 420:  // case 420 = 怪物 ID 420（段B-3 滚动蜘蛛）
            if ( operator new(0x21D0u) == nullptr )  // operator new(8656 字节=0x21D0) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AA7F0(Block, (int)pArg2);  // CNRollingSpider 构造，结果存 result
            break;  // 跳出该分支
          case 421:  // case 421 = 怪物 ID 421（段B-3 毒蜘蛛）
            if ( operator new(0x21B0u) == nullptr )  // operator new(8624 字节=0x21B0) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AA8E0(Block, (int)pArg2);  // CNPoisonSpider 构造，结果存 result
            break;  // 跳出该分支
          case 422:  // case 422 = 怪物 ID 422（段B-3 阿拉克洛蜘蛛）
            if ( operator new(0x2240u) == nullptr )  // operator new(8768 字节=0x2240) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AA970(Block, (int)pArg2);  // CNAraclothoSpider 构造，结果存 result
            break;  // 跳出该分支
          case 430:  // case 430 = 怪物 ID 430（段B-3 幼蜘蛛）
            pMem8 = (uint32_t **)operator new(0x21C0u);  // operator new(8640 字节=0x21C0) 分配怪物对象并存入临时指针
            if ( pMem8 == nullptr )  // 分配失败则返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = (int)sub_5C1C00(pMem8, Block, (int)pArg2, 0);  // CNYoungSpider 构造，结果存 result
            break;  // 跳出该分支
          case 500:  // case 500 = 怪物 ID 500（段B-3 登德洛伊德）
            if ( operator new(0x21F0u) == nullptr )  // operator new(8688 字节=0x21F0) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AAED0(Block, (int)pArg2);  // CNDendroid 构造，结果存 result
            break;  // 跳出该分支
          case 501:  // case 501 = 怪物 ID 501（段B-3 戈利登）
            if ( operator new(0x21F0u) == nullptr )  // operator new(8688 字节=0x21F0) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AAF70(Block, (int)pArg2);  // CNGoliden 构造，结果存 result
            break;  // 跳出该分支
          case 502:  // case 502 = 怪物 ID 502（段B-3 洛迪戈）
            if ( operator new(0x21F8u) == nullptr )  // operator new(8696 字节=0x21F8) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AB010(Block, (int)pArg2);  // CNRodinglo 构造，结果存 result
            break;  // 跳出该分支
          case 600:  // case 600 = 怪物 ID 600（段B-3 精灵·纳依亚斯）
            goto LABEL_360;  // 合流到 LABEL_360 = CNNaias 构造（与 case 60006 共享）
          case 601:  // case 601 = 怪物 ID 601（段B-3 精灵·阿多尔）
            goto LABEL_362;  // 合流到 LABEL_362 = CNAdor 构造（与 case 60007 共享）
          case 602:  // case 602 = 怪物 ID 602（段B-3 精灵·潜行者）
            goto LABEL_364;  // 合流到 LABEL_364 = CNStalker 构造（与 case 60008 共享）
          case 603:  // case 603 = 怪物 ID 603（段B-3 精灵·微光）
            goto LABEL_366;  // 合流到 LABEL_366 = CNWisp 构造（与 case 60009 共享）
          default:  // 未列出的 ID → 落到 default
            return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
        }
      }
    }
    else
    {
      // ── [段 12] 段B-1 特例：Block == 406 —— 规范 ID 150 交 sub_58E1D0（CNGhoul 派生，四参含形态位 1）──
      // --- 段B-1 case 406：特例重映射 —— CNGhoul 派生（规范 ID 150，构造 sub_58E1D0，
      //     部件标签 R_GHOUL* 注册见 ui/char_server_info.cpp §0x58E1D0）---
      if ( Block == 406 )  // 特例分支：怪物 ID == 406（见段注释）
      {
        pMem9 = operator new(0x21ECu);  // operator new(8684 字节=0x21EC) 分配怪物对象并存入临时指针
        if ( pMem9 != nullptr )  // 分配成功 → 直接构造并返回
          return sub_58E1D0((int)pMem9, 150, (int)pArg2, 1);  // CNGhoul派生(形态位) 构造并把指针直接返回
        return 0;  // 分配失败 → 返回空指针 0
      }
      // ── [段 13] 段B-2：Block 201-281 —— 猎手 / 僵尸 / 空骨鱼 / 星鱼 / 传教士 / 攻城器 / 飞艇（switch 主表）──
      //   201 CNHunterAlex / 202 CNHunterMaster（猎手阿尔克斯/大师）；210 CNZombieZombie / 211 CNZombieHollowEye / 212 CNZombieGhoulgwish（僵尸三型）；220 CNStarFishShort / 221 CNStarFishLong / 222 CNSpaceFishCrocuta（空骨鱼，官方名空骨鱼）；
      //   250 CNStarFish / 251 CNStarFishKing（巨空骨鱼）/ 252 CNStarFishRukuku / 253 CNStarFishDevourer（星鱼四型）；
      //   260 CNRaxy_A / 261·265 CNFather / 262·266 CNPope / 263 CNCraxy / 264 CNRaxy_B（传教士六型）；
      //   270 CNCatapult / 271 CNBattlIngram / 272 CNFlameCatapult / 273 CNLaserCatapult（攻城器）；280-281 飞艇（Normal/CannonZepplin）
      // --- 段B-2 case 201-281 + 400-405：猎手(HunterAlex/HunterHunter/HunterMaster)、
      //     僵尸(ZombieZombie/HollowEye/Ghoulgwish)、空骨鱼(SpaceFishShort/Long/Crocuta)、
      //     星鱼(StarFish/StarFishKing/Rukuku/Devourer)、传教士系(Raxy_A/Father/Pope/
      //     Craxy)、攻城器(Catapult/FlameCatapult/LaserCatapult/BattlIngram)、飞艇
      //     (NormalZepplin/CannonZepplin)、尸鬼系 400-405（CNGhoul 派生，构造
      //     sub_58DFE0/58E0E0/58E480/58E1D0 见 ui/char_server_info.cpp）---
      switch ( Block )  // 按怪物 ID（Block）分派构造
      {
        case 201:  // case 201 = 怪物 ID 201（段B-2 猎手·阿尔克斯）
          if ( operator new(0x21CCu) == nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A8CC0(Block, (int)pArg2);  // CNHunterAlex 构造，结果存 result
          break;  // 跳出该分支
        case 202:  // case 202 = 怪物 ID 202（段B-2 猎手·大师）
          if ( operator new(0x21D0u) == nullptr )  // operator new(8656 字节=0x21D0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A8C20(Block, (int)pArg2);  // CNHunterMaster 构造，结果存 result
          break;  // 跳出该分支
        case 210:  // case 210 = 怪物 ID 210（段B-2 僵尸·僵尸）
          if ( operator new(0x21CCu) == nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A8EE0(Block, (int)pArg2);  // CNZombieZombie 构造，结果存 result
          break;  // 跳出该分支
        case 211:  // case 211 = 怪物 ID 211（段B-2 僵尸·空洞眼）
          if ( operator new(0x21CCu) == nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A8F50(Block, (int)pArg2);  // CNZombieHollowEye 构造，结果存 result
          break;  // 跳出该分支
        case 212:  // case 212 = 怪物 ID 212（段B-2 僵尸·食尸鬼）
          if ( operator new(0x21CCu) == nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A8FC0(Block, (int)pArg2);  // CNZombieGhoulgwish 构造，结果存 result
          break;  // 跳出该分支
        case 220:  // case 220 = 怪物 ID 220（段B-2 空骨鱼·短）
          if ( operator new(0x21B0u) == nullptr )  // operator new(8624 字节=0x21B0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          // ── [段 14] 段B-2 之空骨鱼三型：220 Short / 221 Long / 222 Crocuta（官方名空骨鱼 / 克洛库）──
          result = sub_4A95F0(Block, (int)pArg2);  // CNSpaceFishShort 构造，结果存 result
          break;  // 跳出该分支
        case 221:  // case 221 = 怪物 ID 221（段B-2 空骨鱼·长）
          if ( operator new(0x21B0u) == nullptr )  // operator new(8624 字节=0x21B0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A9690(Block, (int)pArg2);  // CNSpaceFishLong 构造，结果存 result
          break;  // 跳出该分支
        case 222:  // case 222 = 怪物 ID 222（段B-2 空骨鱼·克洛库）
          if ( operator new(0x21B0u) == nullptr )  // operator new(8624 字节=0x21B0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A9730(Block, (int)pArg2);  // CNSpaceFishCrocuta 构造，结果存 result
          break;  // 跳出该分支
        case 250:  // case 250 = 怪物 ID 250（段B-2 星鱼·普通）
          if ( operator new(0x21D0u) == nullptr )  // operator new(8656 字节=0x21D0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          // ── [段 15] 段B-2 之星鱼四型：250 CNStarFish / 251 StarFishKing（巨空骨鱼）/ 252 Rukuku / 253 Devourer ──
          result = sub_4A97D0(Block, (int)pArg2);  // CNStarFish 构造，结果存 result
          break;  // 跳出该分支
        case 251:  // case 251 = 怪物 ID 251（段B-2 星鱼·巨空骨鱼）
          if ( operator new(0x21F0u) == nullptr )  // operator new(8688 字节=0x21F0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A99F0(Block, (int)pArg2);  // CNStarFishKing 构造，结果存 result
          break;  // 跳出该分支
        case 252:  // case 252 = 怪物 ID 252（段B-2 星鱼·鲁库库）
          if ( operator new(0x21D0u) == nullptr )  // operator new(8656 字节=0x21D0) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A98F0(Block, (int)pArg2);  // CNStarFishRukuku 构造，结果存 result
          break;  // 跳出该分支
        case 253:  // case 253 = 怪物 ID 253（段B-2 星鱼·吞噬者）
          if ( operator new(0x21D8u) == nullptr )  // operator new(8664 字节=0x21D8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A9970(Block, (int)pArg2);  // CNStarFishDevourer 构造，结果存 result
          break;  // 跳出该分支
        case 260:  // case 260 = 怪物 ID 260（段B-2 传教士·拉库西A）
          if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          // ── [段 16] 段B-2 之传教士六型：260 Raxy_A / 261·265 Father / 262·266 Pope / 263 Craxy / 264 Raxy_B ──
          result = sub_4A9C20(Block, (int)pArg2);  // CNRaxy_A 构造，结果存 result
          break;  // 跳出该分支
        case 261:  // case 261 = 怪物 ID 261（段B-2 传教士·神父）
        case 265:  // case 265 = 怪物 ID 265（段B-2 传教士·神父）
          if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A9D00(Block, (int)pArg2);  // CNFather 构造，结果存 result
          break;  // 跳出该分支
        case 262:  // case 262 = 怪物 ID 262（段B-2 传教士·教皇）
        case 266:  // case 266 = 怪物 ID 266（段B-2 传教士·教皇）
          if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A9D80(Block, (int)pArg2);  // CNPope 构造，结果存 result
          break;  // 跳出该分支
        case 263:  // case 263 = 怪物 ID 263（段B-2 传教士·疯狂）
          if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A9CD0(Block, (int)pArg2);  // CNCraxy 构造（传教士·疯狂），结果存 result
          break;  // 跳出该分支
        case 264:  // case 264 = 怪物 ID 264（段B-2 传教士·拉库西B）
          if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4A9C50(Block, (int)pArg2);  // CNRaxy_B 构造，结果存 result
          break;  // 跳出该分支
        case 270:  // case 270 = 怪物 ID 270（段B-2 攻城器·投石车）
          if ( operator new(0x21B4u) == nullptr )  // operator new(8628 字节=0x21B4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          // ── [段 17] 段B-2 之攻城器四型：270 Catapult / 271 BattlIngram / 272 FlameCatapult / 273 LaserCatapult ──
          result = sub_4AA080(Block, (int)pArg2);  // CNCatapult 构造，结果存 result
          break;  // 跳出该分支
        case 271:  // case 271 = 怪物 ID 271（段B-2 攻城器·英格拉姆）
          if ( operator new(0x21A8u) == nullptr )  // operator new(8616 字节=0x21A8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4AA1E0(Block, (int)pArg2);  // CNBattlIngram 构造，结果存 result
          break;  // 跳出该分支
        case 272:  // case 272 = 怪物 ID 272（段B-2 攻城器·火焰投石车）
          if ( operator new(0x21B4u) == nullptr )  // operator new(8628 字节=0x21B4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4AA150(Block, (int)pArg2);  // CNFlameCatapult 构造，结果存 result
          break;  // 跳出该分支
        case 273:  // case 273 = 怪物 ID 273（段B-2 攻城器·激光投石车）
          if ( operator new(0x21B4u) == nullptr )  // operator new(8628 字节=0x21B4) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4AA0F0(Block, (int)pArg2);  // CNLaserCatapult 构造，结果存 result
          break;  // 跳出该分支
        case 280:  // case 280 = 怪物 ID 280（段B-2 飞艇·普通）
          if ( operator new(0x21E8u) == nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          // ── [段 18] 段B-2 之飞艇两型：280 CNNormalZepplin / 281 CNCannonZepplin ──
          result = sub_4AA440(Block, (int)pArg2);  // CNNormalZepplin 构造，结果存 result
          break;  // 跳出该分支
        case 281:  // case 281 = 怪物 ID 281（段B-2 飞艇·火炮）
          if ( operator new(0x2214u) == nullptr )  // operator new(8724 字节=0x2214) 分配怪物对象；失败即分配失败返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_4AA3A0(Block, (int)pArg2);  // CNCannonZepplin 构造，结果存 result
          break;  // 跳出该分支
        // ── [段 19] 段B-2 尾：case 400-405 —— 尸鬼系（构造主体在 ui/char_server_info.cpp ·0x58DFE0 族）──
        //   400↔403 sub_58DFE0（第四参 0/1 形态位）、401↔404 sub_58E0E0、402 sub_58E480、405 sub_58E1D0（同上段 B-1 同函数）
        case 400:  // case 400 = 怪物 ID 400（段B-2 尸鬼系）
          pMem10 = operator new(0x21ACu);  // operator new(8620 字节=0x21AC) 分配怪物对象并存入临时指针
          if ( pMem10 == nullptr )  // 分配失败则返回 0
            return 0;  // 分配失败 → 返回空指针 0
          // ── [段 20] 段B-2 尾之尸鬼系（0x58 区构造）：400↔403 sub_58DFE0 / 401↔404 sub_58E0E0 / 402 sub_58E480 / 405 sub_58E1D0 ──
          result = (int)sub_58DFE0(pMem10, Block, (int)pArg2, 0);  // CNGhoul派生(形态0) 构造，结果存 result
          break;  // 跳出该分支
        case 401:  // case 401 = 怪物 ID 401（段B-2 尸鬼系）
          pMem11 = operator new(0x21B0u);  // operator new(8624 字节=0x21B0) 分配怪物对象并存入临时指针
          if ( pMem11 == nullptr )  // 分配失败则返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_58E0E0((int)pMem11, Block, (int)pArg2, 0);  // CNGhoul派生2(形态0) 构造，结果存 result
          break;  // 跳出该分支
        case 402:  // case 402 = 怪物 ID 402（段B-2 尸鬼系）
          pMem12 = operator new(0x21B4u);  // operator new(8628 字节=0x21B4) 分配怪物对象并存入临时指针
          if ( pMem12 == nullptr )  // 分配失败则返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_58E480((int)pMem12, Block, (int)pArg2);  // CNGhoul派生3 构造，结果存 result
          break;  // 跳出该分支
        case 403:  // case 403 = 怪物 ID 403（段B-2 尸鬼系）
          pMem13 = operator new(0x21ACu);  // operator new(8620 字节=0x21AC) 分配怪物对象并存入临时指针
          if ( pMem13 == nullptr )  // 分配失败则返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = (int)sub_58DFE0(pMem13, Block, (int)pArg2, 1);  // CNGhoul派生(形态0) 构造，结果存 result
          break;  // 跳出该分支
        case 404:  // case 404 = 怪物 ID 404（段B-2 尸鬼系）
          pMem14 = operator new(0x21B0u);  // operator new(8624 字节=0x21B0) 分配怪物对象并存入临时指针
          if ( pMem14 == nullptr )  // 分配失败则返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_58E0E0((int)pMem14, Block, (int)pArg2, 1);  // CNGhoul派生2(形态0) 构造，结果存 result
          break;  // 跳出该分支
        case 405:  // case 405 = 怪物 ID 405（段B-2 尸鬼系）
          pMem15 = operator new(0x21ECu);  // operator new(8684 字节=0x21EC) 分配怪物对象并存入临时指针
          if ( pMem15 == nullptr )  // 分配失败则返回 0
            return 0;  // 分配失败 → 返回空指针 0
          result = sub_58E1D0((int)pMem15, Block, (int)pArg2, 0);  // CNGhoul派生(形态位) 构造，结果存 result
          break;  // 跳出该分支
        default:  // 未列出的 ID → 落到 default
          return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
      }
    }
    return result;  // 返回构造好的怪物对象指针
  }
  // ── [段 21] 段C 总闸：904 < Block ≤ 50007 万位段（复合 ID，多数重映射回旧 1-200 规范 ID 再复用构造）──
  // --- 段C（约行 592-802）904 < Block ≤ 50007：万位段复合 ID 工厂（多数重映射旧 ID）---
  if ( Block <= 50007 )  // 总闸：怪物 ID ≤ 50007 走本段
  {
    // ── [段 22] 段C-0 特例：Block == 50007 —— 规范 ID 87 构造 CNAuraHunter_Sius（对象体 0x21C4）──
    // --- 段C-0 case 50007：特例重映射 —— CNAuraHunter_Sius（规范 ID 87，构造 sub_4A9330）---
    if ( Block == 50007 )  // 特例分支：怪物 ID == 50007（段C-0 猎手·西乌斯）
    {
      if ( operator new(0x21C4u) != nullptr )  // operator new(8644 字节=0x21C4) 分配怪物对象；成功则前往合流标签
        return sub_4A9330(87, (int)pArg2);  // CNAuraHunter_Sius 构造并把指针直接返回
      return 0;  // 分配失败 → 返回空指针 0
    }
    if ( Block > 41004 )  // 阈值切分：怪物 ID > 41004
    {
      if ( Block > 43003 )  // 阈值切分：怪物 ID > 43003
      {
        // ── [段 23] 段C-1：case 50000-50006 复合段 —— 高位 ID 直接取类构造 ──
        //   50000 CNGardener_Ral（园丁拉尔）/ 50001 CNKalkazak / 50002 CNRock_Moud / 50003 CNBunker_Woker / 50004 CNPrag / 50005 走 LABEL_64 与段A case 50 共享 CNDrakeSerimalion / 50006 CNIceDoll_Sharedo
        // --- 段C-1 case 50000-50007：复合段（Gardener_Ral/Kalkazak/Rock_Moud/
        //     Bunker_Woker/Prag/DrakeSerimalion/IceDoll_Sharedo）；50005 与段A case 50
        //     共享 LABEL_64（同构造 sub_4A8680，按各自 Block 传参）---
        switch ( Block )  // 按怪物 ID（Block）分派构造
        {
          case 50000:  // case 50000 = 怪物 ID 50000（段C-1 园丁拉尔）
            if ( operator new(0x21BCu) == nullptr )  // operator new(8636 字节=0x21BC) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            // ── [段 24] 段C-1 之 50000-50006 复合清单：Gardener_Ral / Kalkazak / Rock_Moud / Bunker_Woker / Prag / IceDoll_Sharedo ──
            result = sub_4A58C0(Block, (int)pArg2);  // CNGardener_Ral 构造，结果存 result
            break;  // 跳出该分支
          case 50001:  // case 50001 = 怪物 ID 50001（段C-1 卡尔卡扎克）
            if ( operator new(0x21D4u) == nullptr )  // operator new(8660 字节=0x21D4) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A9060(Block, (int)pArg2);  // CNKalkazak 构造，结果存 result
            break;  // 跳出该分支
          case 50002:  // case 50002 = 怪物 ID 50002（段C-1 洛克莫德）
            if ( operator new(0x21A0u) == nullptr )  // operator new(8608 字节=0x21A0) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A7880(Block, (int)pArg2);  // CNRock_Moud 构造，结果存 result
            break;  // 跳出该分支
          case 50003:  // case 50003 = 怪物 ID 50003（段C-1 地堡工兵）
            if ( operator new(0x21F0u) == nullptr )  // operator new(8688 字节=0x21F0) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A6480(Block, (int)pArg2);  // CNBunker_Woker 构造，结果存 result
            break;  // 跳出该分支
          case 50004:  // case 50004 = 怪物 ID 50004（段C-1 普拉格）
            if ( operator new(0x21E0u) == nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A67B0(Block, (int)pArg2);  // CNPrag 构造，结果存 result
            break;  // 跳出该分支
          case 50005:  // case 50005 = 怪物 ID 50005（段C-1 塞利翁龙(与 50 共享)）
            if ( operator new(0x226Cu) == nullptr )  // operator new(8812 字节=0x226C) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
LABEL_64:  // 标签 LABEL_64：多 case 合流点
            result = sub_4A8680(Block, (int)pArg2);  // CNDrakeSerimalion 构造，结果存 result
            break;  // 跳出该分支
          case 50006:  // case 50006 = 怪物 ID 50006（段C-1 冰偶）
            if ( operator new(0x21E0u) == nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A82E0(Block, (int)pArg2);  // CNIceDoll_Sharedo 构造，结果存 result
            break;  // 跳出该分支
          default:  // 未列出的 ID → 落到 default
            return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
        }
        return result;  // 返回构造好的怪物对象指针
      }
      // ── [段 25] 段C-2 镜像重映射：41001-43003 —— 万位 ID 翻译为 1-200 规范 ID 后复用同构造 ──
      //   43003→251、42004→20、43001→249、43002→250、42003→19、41005→45、42001→17、42002→18、41004→44、41001→41、41002→42、41003→43（精英哥布林族）—— 同怪不同编号段，构造对象体随目标类
      // --- 段C-2 case 43003/42001-43003/41001-41005：镜像重映射 —— 以旧 1-200 规范 ID
      //     构造同类怪（43003→251 猎手 / 42004→20 投石车 / 43001→249 / 43002→250
      //     KingGalok / 41005→45 投石车 / 42003→19 / 41001→41 / 41002→42 / 41003→43
      //     精英哥布林 / 42001→17 / 42002→18 / 41004→44 猎手）---
      if ( Block == 43003 )  // 特例分支：怪物 ID == 43003（段C-2 猎手镜像）
      {
        if ( operator new(0x21CCu) != nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；成功则前往合流标签
          return sub_4A8CC0(251, (int)pArg2);  // CNHunterAlex 构造并把指针直接返回
        return 0;  // 分配失败 → 返回空指针 0
      }
      if ( Block > 42003 )  // 阈值切分：怪物 ID > 42003
      {
        switch ( Block )  // 按怪物 ID（Block）分派构造
        {
          case 42004:  // case 42004 = 怪物 ID 42004（段C-2 投石车镜像）
            if ( operator new(0x21B4u) != nullptr )  // operator new(8628 字节=0x21B4) 分配怪物对象；成功则前往合流标签
              return sub_4AA080(20, (int)pArg2);  // CNCatapult 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          case 43001:  // case 43001 = 怪物 ID 43001（段C-2 镜像）
            if ( operator new(0x21BCu) != nullptr )  // operator new(8636 字节=0x21BC) 分配怪物对象；成功则前往合流标签
              return sub_4A7280(249, (int)pArg2);  // CNLightningKinol 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          case 43002:  // case 43002 = 怪物 ID 43002（段C-2 镜像）
            if ( operator new(0x21ECu) != nullptr )  // operator new(8684 字节=0x21EC) 分配怪物对象；成功则前往合流标签
              return sub_4A6580(250, (int)pArg2);  // CNKingGalok 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          default:  // 未列出的 ID → 落到 default
            break;  // 跳出该分支
        }
      }
      else
      {
        switch ( Block )  // 按怪物 ID（Block）分派构造
        {
          case 42003:  // case 42003 = 怪物 ID 42003（段C-2 猎手镜像）
            if ( operator new(0x21CCu) != nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；成功则前往合流标签
              return sub_4A8CC0(19, (int)pArg2);  // CNHunterAlex 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          case 41005:  // case 41005 = 怪物 ID 41005（段C-2 投石车镜像）
            if ( operator new(0x21B4u) != nullptr )  // operator new(8628 字节=0x21B4) 分配怪物对象；成功则前往合流标签
              return sub_4AA080(45, (int)pArg2);  // CNCatapult 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          case 42001:  // case 42001 = 怪物 ID 42001（段C-2 精英镜像）
            if ( operator new(0x21ECu) != nullptr )  // operator new(8684 字节=0x21EC) 分配怪物对象；成功则前往合流标签
              return sub_4A6540(17, (int)pArg2);  // CNEliteGoblin 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          case 42002:  // case 42002 = 怪物 ID 42002（段C-2 猎手镜像）
            if ( operator new(0x21CCu) != nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；成功则前往合流标签
              return sub_4A8D60(18, (int)pArg2);  // CNHunterHunter 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          default:  // 未列出的 ID → 落到 default
            break;  // 跳出该分支
        }
      }
    }
    else
    {
      // ── [段 26] 段C-3：case 3000-3002 / 5001-5005 / 40001-40004 —— boss 与卢加鲁系 ──
      //   3000→184 CNLordofLight（赛格哈特，光之城主）/ 3001→185 CNGolemPlatany / 3002→186 CNLotus（莲花）；
      //   5001-5005 → 137 CNLugaru / 138 CNBlackLugaru / 139 CNWhiteLugaru / 140 CNPenril / 141 CNBloodLugaru；
      //   40001-40004 为投掷卡格尔族重映射（40002 与段A case 5 同函数 sub_4A62A0，40003 与 case 6 同函数 sub_4A6620）
      // --- 段C-3 case 3000-3002 / 5001-5005 / 40001-40004：boss 与卢加鲁系
      //     （3000→184 LordofLight 光之主 / 3001→185 GolemPlatany / 3002→186 Lotus /
      //     5001→137 Lugaru / 5002→138 BlackLugaru / 5003→139 WhiteLugaru /
      //     5004→140 Penril / 5005→141 BloodLugaru / 40001→65 / 40002→66 /
      //     40003→67 / 40004→68 投掷卡格尔重映射）---
      if ( Block == 41004 )  // 特例分支：怪物 ID == 41004（段C-2 猎手镜像）
      {
        if ( operator new(0x21CCu) != nullptr )  // operator new(8652 字节=0x21CC) 分配怪物对象；成功则前往合流标签
          return sub_4A8D60(44, (int)pArg2);  // CNHunterHunter 构造并把指针直接返回
        return 0;  // 分配失败 → 返回空指针 0
      }
      if ( Block > 5005 )  // 阈值切分：怪物 ID > 5005
      {
        if ( Block > 40004 )  // 阈值切分：怪物 ID > 40004
        {
          switch ( Block )  // 按怪物 ID（Block）分派构造
          {
            case 41001:  // case 41001 = 怪物 ID 41001（段C-2 哥布林镜像）
              if ( operator new(0x21E8u) != nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；成功则前往合流标签
                return sub_4A60F0(41, (int)pArg2);  // CNGoblinAssaulter 构造并把指针直接返回
              return 0;  // 分配失败 → 返回空指针 0
            case 41002:  // case 41002 = 怪物 ID 41002（段C-2 哥布林镜像）
              if ( operator new(0x21E8u) != nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；成功则前往合流标签
                return sub_4A62A0(42, (int)pArg2);  // CNGoblinKinol 构造并把指针直接返回
              return 0;  // 分配失败 → 返回空指针 0
            case 41003:  // case 41003 = 怪物 ID 41003（段C-2 哥布林镜像）
              if ( operator new(0x21E0u) != nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；成功则前往合流标签
                return sub_4A6620(43, (int)pArg2);  // CNGoblinGero 构造并把指针直接返回
              return 0;  // 分配失败 → 返回空指针 0
            default:  // 未列出的 ID → 落到 default
              break;  // 跳出该分支
          }
        }
        else
        {
          switch ( Block )  // 按怪物 ID（Block）分派构造
          {
            case 40004:  // case 40004 = 怪物 ID 40004（段C-3 卡格尔重映射）
              if ( operator new(0x21E0u) != nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；成功则前往合流标签
                return sub_4A6F60(68, (int)pArg2);  // CNGoblinBombKagel 构造并把指针直接返回
              return 0;  // 分配失败 → 返回空指针 0
            case 40001:  // case 40001 = 怪物 ID 40001（段C-3 卡格尔重映射）
              if ( operator new(0x21E8u) != nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；成功则前往合流标签
                return sub_4A60F0(65, (int)pArg2);  // CNGoblinAssaulter 构造并把指针直接返回
              return 0;  // 分配失败 → 返回空指针 0
            case 40002:  // case 40002 = 怪物 ID 40002（段C-3 卡格尔重映射）
              if ( operator new(0x21E8u) != nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；成功则前往合流标签
                return sub_4A62A0(66, (int)pArg2);  // CNGoblinKinol 构造并把指针直接返回
              return 0;  // 分配失败 → 返回空指针 0
            case 40003:  // case 40003 = 怪物 ID 40003（段C-3 卡格尔重映射）
              if ( operator new(0x21E0u) != nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；成功则前往合流标签
                return sub_4A6620(67, (int)pArg2);  // CNGoblinGero 构造并把指针直接返回
              return 0;  // 分配失败 → 返回空指针 0
            default:  // 未列出的 ID → 落到 default
              break;  // 跳出该分支
          }
        }
      }
      else
      {
        if ( Block == 5005 )  // 特例分支：怪物 ID == 5005（段C-3 血卢加鲁）
        {
          if ( operator new(0x21ECu) != nullptr )  // operator new(8684 字节=0x21EC) 分配怪物对象；成功则前往合流标签
            return sub_4A5C90(141, (int)pArg2);  // CNBloodLugaru 构造并把指针直接返回
          return 0;  // 分配失败 → 返回空指针 0
        }
        if ( Block > 5001 )  // 阈值切分：怪物 ID > 5001
        {
          if ( Block == 5002 )  // 特例分支：怪物 ID == 5002（段C-3 黑卢加鲁）
          {
            if ( operator new(0x21BCu) != nullptr )  // operator new(8636 字节=0x21BC) 分配怪物对象；成功则前往合流标签
              return sub_4A59F0(138, (int)pArg2);  // CNBlackLugaru 构造并把指针直接返回
          }
          else if ( Block == 5003 )  // else-if 链：怪物 ID == 5003（段C-3 白卢加鲁）
          {
            if ( operator new(0x21C0u) != nullptr )  // operator new(8640 字节=0x21C0) 分配怪物对象；成功则前往合流标签
              return sub_4A5AD0(139, (int)pArg2);  // CNWhiteLugaru 构造并把指针直接返回
          }
          else if ( operator new(0x21BCu) != nullptr )  // else-if 链：再分配 8636 字节对象，成功则构造返回
          {
            return sub_4A5BB0(140, (int)pArg2);  // CNPenril 构造并把指针直接返回
          }
          return 0;  // 分配失败 → 返回空指针 0
        }
        switch ( Block )  // 按怪物 ID（Block）分派构造
        {
          case 5001:  // case 5001 = 怪物 ID 5001（段C-3 卢加鲁）
            if ( operator new(0x21B8u) != nullptr )  // operator new(8632 字节=0x21B8) 分配怪物对象；成功则前往合流标签
              return sub_4A57E0(137, (int)pArg2);  // CNLugaru 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          case 3000:  // case 3000 = 怪物 ID 3000（段C-3 光之城主）
            if ( operator new(0x21C8u) != nullptr )  // operator new(8648 字节=0x21C8) 分配怪物对象；成功则前往合流标签
              return sub_4A9470(184, (int)pArg2);  // CNLordofLight 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          case 3001:  // case 3001 = 怪物 ID 3001（段C-3 钢铁巨人）
            if ( operator new(0x21F4u) != nullptr )  // operator new(8692 字节=0x21F4) 分配怪物对象；成功则前往合流标签
              return sub_4A7F70(185, (int)pArg2);  // CNGolemPlatany 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          case 3002:  // case 3002 = 怪物 ID 3002（段C-3 莲花）
            if ( operator new(0x21E0u) != nullptr )  // operator new(8672 字节=0x21E0) 分配怪物对象；成功则前往合流标签
              return sub_4AB740(186, (int)pArg2);  // CNLotus 构造并把指针直接返回
            return 0;  // 分配失败 → 返回空指针 0
          default:  // 未列出的 ID → 落到 default
            break;  // 跳出该分支
        }
      }
    }
    return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
  }
  // ── [段 27] 段D 总闸：Block > 50023 高位段（守卫塔 / 机器人 / 精灵 / 巨人族）──
  // --- 段D（约行 804-999）Block > 50023：高位段（巨人/守卫塔/机器人/幻影）---
  if ( Block > 50023 )  // 阈值切分：怪物 ID > 50023
  {
    // ── [段 28] 段D-1：50069-60005 —— 高位特例与机器人段 ──
    //   50069→149 CNSoulEter；60001 sub_4A5380(97 CNFighterIllusion)、60002 sub_4AAB30(98 CNRobotRX78)、60003 sub_4AAC10(99 CNRobotEz8)、60004 sub_4AACF0(100 CNRobotExs)、60005 sub_4A60F0(101，同 case 63 构造)
    // --- 段D-1 case 50068/50069：特例重映射 —— CNGuardLight（规范 ID 148，构造
    //     sub_5D7290）/ CNSoulEter（规范 ID 149，构造 sub_4AB430）---
    if ( Block > 50068 )  // 阈值切分：怪物 ID > 50068
    {
      if ( Block > 60005 )  // 阈值切分：怪物 ID > 60005
      {
        // ── [段 29] 段D-2：case 60006-60010 —— 精灵系与幻影（LABEL_360/362/364/366 与段B case 600-603 共享）──
        //   60006 CNNaias / 60007 CNAdor / 60008 CNStalker / 60009 CNWisp（对象体 0x222C-0x2230）；
        //   60010 CNProvocationDoll —— 全函数唯一把 nArg3 透传给构造的分支（sub_4A5460 三参，挑动人偶）
        // --- 段D-2 case 60006-60010：精灵系与幻影（Naias/Ador/Stalker/Wisp/
        //     ProvocationDoll——60010 是唯一把 nArg3 传入构造的分支）；
        //     60006-60009 与段B case 600-603 共享 LABEL_360-366 ---
        switch ( Block )  // 按怪物 ID（Block）分派构造
        {
          case 60006:  // case 60006 = 怪物 ID 60006（段D-2 纳依亚斯）
LABEL_360:  // 标签 LABEL_360：多 case 合流点
            if ( operator new(0x222Cu) == nullptr )  // operator new(8748 字节=0x222C) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AB320(Block, (int)pArg2);  // CNNaias 构造，结果存 result
            break;  // 跳出该分支
          case 60007:  // case 60007 = 怪物 ID 60007（段D-2 阿多尔）
LABEL_362:  // 标签 LABEL_362：多 case 合流点
            if ( operator new(0x222Cu) == nullptr )  // operator new(8748 字节=0x222C) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AB3C0(Block, (int)pArg2);  // CNAdor 构造，结果存 result
            break;  // 跳出该分支
          case 60008:  // case 60008 = 怪物 ID 60008（段D-2 潜行者）
LABEL_364:  // 标签 LABEL_364：多 case 合流点
            if ( operator new(0x222Cu) == nullptr )  // operator new(8748 字节=0x222C) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AB4C0(Block, (int)pArg2);  // CNStalker 构造，结果存 result
            break;  // 跳出该分支
          case 60009:  // case 60009 = 怪物 ID 60009（段D-2 微光）
LABEL_366:  // 标签 LABEL_366：多 case 合流点
            if ( operator new(0x2230u) == nullptr )  // operator new(8752 字节=0x2230) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4AB560(Block, (int)pArg2);  // CNWisp 构造，结果存 result
            break;  // 跳出该分支
          case 60010:  // case 60010 = 怪物 ID 60010（段D-2 挑动人偶）
            if ( operator new(0x21A4u) == nullptr )  // operator new(8612 字节=0x21A4) 分配怪物对象；失败即分配失败返回 0
              return 0;  // 分配失败 → 返回空指针 0
            result = sub_4A5460(Block, (int)pArg2, nArg3);  // CNProvocationDoll 构造，结果存 result
            break;  // 跳出该分支
          default:  // 未列出的 ID → 落到 default
            return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
        }
        return result;  // 返回构造好的怪物对象指针
      }
      if ( Block == 60005 )  // 特例分支：怪物 ID == 60005（段D-1 哥布林突击兵(与 63 共享)）
      {
        if ( operator new(0x21E8u) != nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；成功则前往合流标签
          return sub_4A60F0(101, (int)pArg2);  // CNGoblinAssaulter 构造并把指针直接返回
        return 0;  // 分配失败 → 返回空指针 0
      }
      if ( Block > 60002 )  // 阈值切分：怪物 ID > 60002
      {
        if ( Block == 60003 )  // 特例分支：怪物 ID == 60003（段D-1 机器人Ez8）
        {
          if ( operator new(0x21B8u) != nullptr )  // operator new(8632 字节=0x21B8) 分配怪物对象；成功则前往合流标签
            return sub_4AAC10(99, (int)pArg2);  // CNRobotEz8 构造并把指针直接返回
        }
        else if ( operator new(0x21D4u) != nullptr )  // else-if 链：再分配 8660 字节对象，成功则构造返回
        {
          return sub_4AACF0(100, (int)pArg2);  // CNRobotExs 构造并把指针直接返回
        }
        return 0;  // 分配失败 → 返回空指针 0
      }
      switch ( Block )  // 按怪物 ID（Block）分派构造
      {
        case 60002:  // case 60002 = 怪物 ID 60002（段D-1 机器人RX78）
          if ( operator new(0x21ACu) != nullptr )  // operator new(8620 字节=0x21AC) 分配怪物对象；成功则前往合流标签
            return sub_4AAB30(98, (int)pArg2);  // CNRobotRX78 构造并把指针直接返回
          return 0;  // 分配失败 → 返回空指针 0
        case 50069:  // case 50069 = 怪物 ID 50069（段D-1 灵魂吞噬者）
          if ( operator new(0x2230u) != nullptr )  // operator new(8752 字节=0x2230) 分配怪物对象；成功则前往合流标签
            return sub_4AB430(149, (int)pArg2);  // CNSoulEter 构造并把指针直接返回
          return 0;  // 分配失败 → 返回空指针 0
        case 60001:  // case 60001 = 怪物 ID 60001（段D-1 格斗家幻影）
          if ( operator new(0x21A0u) != nullptr )  // operator new(8608 字节=0x21A0) 分配怪物对象；成功则前往合流标签
            return sub_4A5380(97, (int)pArg2);  // CNFighterIllusion 构造并把指针直接返回
          return 0;  // 分配失败 → 返回空指针 0
        default:  // 未列出的 ID → 落到 default
          break;  // 跳出该分支
      }
      return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
    }
    if ( Block == 50068 )  // 特例分支：怪物 ID == 50068（段D-1 光守卫）
    {
      if ( operator new(0x22E8u) != nullptr )  // operator new(8936 字节=0x22E8) 分配怪物对象；成功则前往合流标签
        return sub_5D7290(148, (int)pArg2);  // CNGuardLight 构造并把指针直接返回
      return 0;  // 分配失败 → 返回空指针 0
    }
    // ── [段 30] 段D 主体 switch：50024-50067 —— 亚特拉斯巨人族 / 守卫塔 / 油商奥雷克 ──
    //   50024 走 LABEL_32（与段A case 21 共享 sub_4A5540 CNKeraha）；50030/50031/50032 走 LABEL_183/185/187（与段B 760/761/762 共享 CNAtlas/CNGoliath/CNTitan）；50033 CNBurningHela、50034 CNGhoulOilSellerOlrek（油商奥雷克）；
    //   50062 CNGoblinBullsEye（投掷哥布林）、50063-50067 sub_5Dxxxx 系守卫塔（对象体 0x2204-0x235C 最大族）
    switch ( Block )  // 按怪物 ID（Block）分派构造
    {
      case 50024:  // case 50024 = 怪物 ID 50024（段D-3 克拉赫(与 21 共享)）
        if ( operator new(0x21C8u) == nullptr )  // operator new(8648 字节=0x21C8) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
LABEL_32:  // 标签 LABEL_32：多 case 合流点
        result = sub_4A5540(Block, (int)pArg2);  // CNKeraha 构造，结果存 result
        break;  // 跳出该分支
      case 50030:  // case 50030 = 怪物 ID 50030（段D 亚特拉斯(与 760 共享)）
        if ( operator new(0x21FCu) == nullptr )  // operator new(8700 字节=0x21FC) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
LABEL_183:  // 标签 LABEL_183：多 case 合流点
        result = sub_4ABC50(Block, (int)pArg2);  // CNAtlas 构造，结果存 result
        break;  // 跳出该分支
      case 50031:  // case 50031 = 怪物 ID 50031（段D 歌利亚(与 761 共享)）
        if ( operator new(0x2210u) == nullptr )  // operator new(8720 字节=0x2210) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
LABEL_185:  // 标签 LABEL_185：多 case 合流点
        result = sub_4ABB70(Block, (int)pArg2);  // CNGoliath 构造，结果存 result
        break;  // 跳出该分支
      case 50032:  // case 50032 = 怪物 ID 50032（段D 泰坦(与 762 共享)）
        if ( operator new(0x21F8u) == nullptr )  // operator new(8696 字节=0x21F8) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
LABEL_187:  // 标签 LABEL_187：多 case 合流点
        result = sub_4ABD30(Block, (int)pArg2);  // CNTitan 构造，结果存 result
        break;  // 跳出该分支
      case 50033:  // case 50033 = 怪物 ID 50033（段D 燃烧赫拉）
        if ( operator new(0x21D0u) == nullptr )  // operator new(8656 字节=0x21D0) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_4A90D0(Block, (int)pArg2);  // CNBurningHela 构造，结果存 result
        break;  // 跳出该分支
      case 50034:  // case 50034 = 怪物 ID 50034（段D 油商奥雷克）
        if ( operator new(0x21B0u) == nullptr )  // operator new(8624 字节=0x21B0) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_4A0CF0(Block, pArg2, 1);  // CNGhoulOilSellerOlrek 构造，结果存 result
        break;  // 跳出该分支
      case 50062:  // case 50062 = 怪物 ID 50062（段D 投掷哥布林）
        if ( operator new(0x2204u) == nullptr )  // operator new(8708 字节=0x2204) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_4A7100(Block, (int)pArg2);  // CNGoblinBullsEye 构造，结果存 result
        break;  // 跳出该分支
      case 50063:  // case 50063 = 怪物 ID 50063（段D 斧驱逐者(守卫塔)）
        pMem16 = operator new(0x226Cu);  // operator new(8812 字节=0x226C) 分配怪物对象并存入临时指针
        if ( pMem16 == nullptr )  // 分配失败则返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = (int)sub_5D89B0(pMem16, Block, (int)pArg2, 1);  // CNAxionExpeller 构造，结果存 result
        break;  // 跳出该分支
      case 50064:  // case 50064 = 怪物 ID 50064（段D 火守卫）
        if ( operator new(0x22ECu) == nullptr )  // operator new(8940 字节=0x22EC) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_5D7740(Block, (int)pArg2);  // CNGuardFire 构造，结果存 result
        break;  // 跳出该分支
      case 50065:  // case 50065 = 怪物 ID 50065（段D 风守卫）
        if ( operator new(0x235Cu) == nullptr )  // operator new(9052 字节=0x235C) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_5D7360(Block, (int)pArg2);  // CNGuardWind 构造，结果存 result
        break;  // 跳出该分支
      case 50066:  // case 50066 = 怪物 ID 50066（段D 重装守卫）
        if ( operator new(0x22CCu) == nullptr )  // operator new(8908 字节=0x22CC) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_5D76D0(Block, (int)pArg2);  // CNGuardBlock 构造，结果存 result
        break;  // 跳出该分支
      case 50067:  // case 50067 = 怪物 ID 50067（段D 冰守卫）
        if ( operator new(0x22BCu) == nullptr )  // operator new(8892 字节=0x22BC) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_5D75E0(Block, (int)pArg2);  // CNGuardIce 构造，结果存 result
        break;  // 跳出该分支
      default:  // 未列出的 ID → 落到 default
        return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
    }
  }
  else
  {
      // ── [段 31] 段D-3：Block ≤ 50023 —— Vinoshu 重映射 + 破晓/曙光/黄昏/暗黑四传道者 ──
      //   50023→103 经 sub_4A5620（CNVinoshu 复用，与段A case 22 同函数）；50008 CNStoneBlade_Razor；
      //   50009-50012 CNEvangelistOfDawn/Light/Twilight/Dark（对象体 0x21E4-0x21E8 同尺寸族）
      // --- 段D-3 case 50023-50034：亚特拉斯巨人族（Vinoshu→50023 重映射 / Atlas /
      //     Goliath / Titan / BurningHela / GhoulOilSellerOlrek 油商奥雷克）；
      //     50024 与段A case 21 共享 LABEL_32 ---
    if ( Block == 50023 )  // 特例分支：怪物 ID == 50023（段D-3 彼诺修重映射）
    {
      if ( operator new(0x21D8u) != nullptr )  // operator new(8664 字节=0x21D8) 分配怪物对象；成功则前往合流标签
        return sub_4A5620(103, (int)pArg2);  // CNVinoshu 构造并把指针直接返回
      return 0;  // 分配失败 → 返回空指针 0
    }
    switch ( Block )  // 按怪物 ID（Block）分派构造
    {
      case 50008:  // case 50008 = 怪物 ID 50008（段D-3 石刃·锐）
        if ( operator new(0x21ECu) == nullptr )  // operator new(8684 字节=0x21EC) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_4A8010(Block, (int)pArg2);  // CNStoneBlade_Razor 构造，结果存 result
        break;  // 跳出该分支
      case 50009:  // case 50009 = 怪物 ID 50009（段D-3 传道者·破晓）
        if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_4A9E00(Block, (int)pArg2);  // CNEvangelistOfDawn 构造，结果存 result
        break;  // 跳出该分支
      case 50010:  // case 50010 = 怪物 ID 50010（段D-3 传道者·曙光）
        if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_4A9E50(Block, (int)pArg2);  // CNEvangelistOfLight 构造，结果存 result
        break;  // 跳出该分支
      case 50011:  // case 50011 = 怪物 ID 50011（段D-3 传道者·黄昏）
        if ( operator new(0x21E8u) == nullptr )  // operator new(8680 字节=0x21E8) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_4A9E80(Block, (int)pArg2);  // CNEvangelistOfTwilight 构造，结果存 result
        break;  // 跳出该分支
      case 50012:  // case 50012 = 怪物 ID 50012（段D-3 传道者·暗黑）
        if ( operator new(0x21E4u) == nullptr )  // operator new(8676 字节=0x21E4) 分配怪物对象；失败即分配失败返回 0
          return 0;  // 分配失败 → 返回空指针 0
        result = sub_4A9F10(Block, (int)pArg2);  // CNEvangelistOfDark 构造，结果存 result
        break;  // 跳出该分支
      default:  // 未列出的 ID → 落到 default
        return -842150451;  // 未识别 ID → 返回 -842150451（0xCDCDCDCD 调试堆填充值当错误码）
    }
  }
  return result;  // 返回构造好的怪物对象指针
}

