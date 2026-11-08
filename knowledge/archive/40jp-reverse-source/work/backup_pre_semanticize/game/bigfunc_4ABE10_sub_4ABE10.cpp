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
//   段B @~247-590  201-904：201-202 猎手 / 210-212 僵尸 / 220-222 宇宙鱼 / 250-253
//                  星鱼 / 260-266 传教士系 / 270-273 攻城器 / 280-281 飞艇 / 400-408
//                  尸鬼系 / 410-430 蜘蛛系 / 500-502 洛迪戈 / 600-603 精灵系 / 700-762
//                  驱逐者军团 / 800 蝙蝠 / 900-904 特殊
//   段C @~592-802  3000-50007：3000-3002 boss / 5001-5005 卢加鲁系 / 40001-41005 哥布林
//                  镜像重映射 / 42001-43003 猎手僵尸镜像 / 50000-50007 复合
//   段D @~804-999  50023-60010：50023-50034 亚特拉斯巨人 / 50062-50069 守卫塔 / 60001-60010
//                  机器人与幻影
int /*cdecl*/ sub_4ABE10(int Block, void *a2, int a3)
{
  int result; // eax
  uint8_t *v4; // eax
  void *v5; // eax
  void *v6; // eax
  uint8_t *v7; // eax
  void *v8; // eax
  void *v9; // eax
  void *v10; // eax
  uint32_t **v11; // eax
  uint32_t *v12; // eax
  uint8_t *v13; // eax
  void *v14; // eax
  uint8_t *v15; // eax
  uint8_t *v16; // eax
  uint32_t *v17; // eax
  uint8_t *v18; // eax
  uint32_t *v19; // eax

  // --- 段A（约行 55-245）Block ≤ 200：基础怪 ID 工厂 ---
  if ( Block <= 200 )
  {
    if ( Block != 200 )
    {
      // --- 段A-1 case 1-15：哥布林族（CNGoblinGoblin/Stoner/IslandGab/MountainGab/
      //     Kinol/Gero/Lupete/Sharedo/CowardGoblin 等，构造见 rtti_core.cpp §0x4A5xxx）---
      switch ( Block )
      {
        case 1:
          if ( operator new(0x21E8u) == nullptr )
            return 0;
          result = sub_4A5F10(Block, (int)a2);
          break;
        case 2:
          if ( operator new(0x21D0u) == nullptr )
            return 0;
          result = sub_4A5DC0(Block, (int)a2);
          break;
        case 3:
          if ( operator new(0x21D0u) == nullptr )
            return 0;
          result = sub_4A69E0(Block, (int)a2);
          break;
        case 4:
          if ( operator new(0x21D0u) == nullptr )
            return 0;
          result = sub_4A6850(Block, (int)a2);
          break;
        case 5:
          if ( operator new(0x21E8u) == nullptr )
            return 0;
          result = sub_4A62A0(Block, (int)a2);
          break;
        case 6:
          if ( operator new(0x21E0u) == nullptr )
            return 0;
          result = sub_4A6620(Block, (int)a2);
          break;
        case 7:
          if ( operator new(0x21D8u) == nullptr )
            return 0;
          result = sub_4A6B70(Block, (int)a2);
          break;
        case 8:
          if ( operator new(0x21B0u) == nullptr )
            return 0;
          result = sub_4A6EE0(Block, (int)a2);
          break;
        case 9:
          if ( operator new(0x21BCu) == nullptr )
            return 0;
          result = sub_4A7280(Block, (int)a2);
          break;
        case 10:
          if ( operator new(0x21C8u) == nullptr )
            return 0;
          result = sub_4A73D0(Block, (int)a2);
          break;
        case 11:
          if ( operator new(0x219Cu) == nullptr )
            return 0;
          result = sub_4A7520(Block, (int)a2);
          break;
        case 12:
          if ( operator new(0x21A4u) == nullptr )
            return 0;
          result = sub_4A7640(Block, (int)a2);
          break;
        case 13:
          if ( operator new(0x21A0u) == nullptr )
            return 0;
          result = sub_4A7760(Block, (int)a2);
          break;
        case 14:
          if ( operator new(0x21A8u) == nullptr )
            return 0;
          result = sub_4A7900(Block, (int)a2);
          break;
        case 15:
          if ( operator new(0x21A0u) == nullptr )
            return 0;
          result = sub_4A7A20(Block, (int)a2);
          break;
        // --- 段A-2 case 21/22 + case 31-40：园丁拉尔(CNGardener_Ral/CNVinoshu)与
        //     石偶傀儡系（CNGolemStone/Steel/Clay/Bronze/Gold/StoneMaster/SteelMaster/
        //     ClayMaster/MasterDogri，构造见 rtti_core.cpp §0x4A7Cxx-0x4A82xx）---
        case 21:
          if ( operator new(0x21C8u) != nullptr )
            goto LABEL_32;
          return 0;
        case 22:
          if ( operator new(0x21D8u) == nullptr )
            return 0;
          result = sub_4A5620(Block, (int)a2);
          break;
        case 31:
          if ( operator new(0x21E8u) == nullptr )
            return 0;
          result = sub_4A7C90(Block, (int)a2);
          break;
        case 32:
          if ( operator new(0x21E4u) == nullptr )
            return 0;
          result = sub_4A7D30(Block, (int)a2);
          break;
        case 33:
          if ( operator new(0x21E4u) == nullptr )
            return 0;
          result = sub_4A7E30(Block, (int)a2);
          break;
        case 34:
          if ( operator new(0x21E4u) == nullptr )
            return 0;
          result = sub_4A7DD0(Block, (int)a2);
          break;
        case 35:
          if ( operator new(0x21E4u) == nullptr )
            return 0;
          result = sub_4A7ED0(Block, (int)a2);
          break;
        case 37:
          if ( operator new(0x21E0u) == nullptr )
            return 0;
          result = sub_4A8120(Block, (int)a2);
          break;
        case 38:
          if ( operator new(0x21E0u) == nullptr )
            return 0;
          result = sub_4A8190(Block, (int)a2);
          break;
        case 39:
          if ( operator new(0x21E0u) == nullptr )
            return 0;
          result = sub_4A8200(Block, (int)a2);
          break;
        case 40:
          if ( operator new(0x21E0u) == nullptr )
            return 0;
          result = sub_4A8270(Block, (int)a2);
          break;
        // --- 段A-3 case 50-53 + 60-63 + 70/71：塞利翁龙系（CNDrakeSerimalion/
        //     Loose/Harse/SelionTheFireBreather）、投掷卡格尔（CNGoblinBombKagel/
        //     SurikenKagel/BullsEye）、飞艇（CNNormalZepplin/CNCannonZepplin）---
        case 50:
          if ( operator new(0x226Cu) != nullptr )
            goto LABEL_64;
          return 0;
        case 51:
          if ( operator new(0x2280u) == nullptr )
            return 0;
          result = sub_4A87A0(Block, a2);
          break;
        case 52:
          if ( operator new(0x2250u) == nullptr )
            return 0;
          result = sub_4A8940(Block, (int)a2);
          break;
        case 53:
          if ( operator new(0x21C0u) == nullptr )
            return 0;
          result = sub_4A89C0(Block, (int)a2);
          break;
        case 60:
          if ( operator new(0x21E0u) == nullptr )
            return 0;
          result = sub_4A6F60(Block, (int)a2);
          break;
        case 61:
          if ( operator new(0x21E0u) == nullptr )
            return 0;
          result = sub_4A7090(Block, (int)a2);
          break;
        case 63:
          if ( operator new(0x21E8u) == nullptr )
            return 0;
          result = sub_4A60F0(Block, (int)a2);
          break;
        case 70:
          if ( operator new(0x21C0u) == nullptr )
            return 0;
          result = sub_4A9220(Block, (int)a2);
          break;
        case 71:
          if ( operator new(0x21C0u) == nullptr )
            return 0;
          result = sub_4A9290(Block, (int)a2);
          break;
        default:
          return -842150451;
      }
      return result;
    }
    // --- 段A-4 case 200：特例重映射 —— CNHunterHunter（规范 ID 200，构造 sub_4A8D60）---
    if ( operator new(0x21CCu) != nullptr )
      return sub_4A8D60(200, (int)a2);
    return 0;
  }
  // --- 段B（约行 247-590）201 ≤ Block ≤ 904：中段怪 ID 工厂 ---
  if ( Block <= 904 )
  {
    // --- 段B-0 case 904：特例重映射 —— CNSpikeKing（规范 ID 136，构造 sub_4AB840）---
    if ( Block == 904 )
    {
      if ( operator new(0x21FCu) != nullptr )
        return sub_4AB840(136, (int)a2);
      return 0;
    }
    if ( Block > 406 )
    {
      if ( Block > 700 )
      {
        // --- 段B-4 case 700：特例重映射 —— CNExpeller 驱逐者（规范 ID 188，构造
        //     sub_5D88C0，见 creature/expeller_guard.cpp）；701-762 驱逐者军团
        //     （Axe/Heaven/Legion/TinSwordMan/SandorExpeller/HammerKing/Axion/
        //     GuardLight/Goliath/Atlas/Titan 等）、800 蝙蝠 CNBat、900-904 特殊
        //     （GoblinHodor/Luis/MonsterFlower）---
        switch ( Block )
        {
          case 701:
            v13 = operator new(0x2274u);
            if ( v13 == nullptr )
              return 0;
            result = (int)sub_5D7870(v13, Block, (int)a2);
            break;
          case 702:
            v14 = operator new(0x2288u);
            if ( v14 == nullptr )
              return 0;
            result = (int)sub_5D7970(v14, Block, (int)a2);
            break;
          case 704:
            v15 = operator new(0x2284u);
            if ( v15 == nullptr )
              return 0;
            result = (int)sub_5D7AE0(v15, Block, (int)a2, 1);
            break;
          case 705:
            v16 = operator new(0x2298u);
            if ( v16 == nullptr )
              return 0;
            result = (int)sub_5D8A70(v16, Block, (int)a2, 1);
            break;
          case 711:
            if ( operator new(0x2334u) == nullptr )
              return 0;
            result = sub_5D7100(Block, (int)a2);
            break;
          case 750:
            if ( operator new(0x2218u) == nullptr )
              return 0;
            result = sub_5D9F50(Block, (int)a2);
            break;
          case 760:
            if ( operator new(0x21FCu) != nullptr )
              goto LABEL_183;
            return 0;
          case 761:
            if ( operator new(0x2210u) != nullptr )
              goto LABEL_185;
            return 0;
          case 762:
            if ( operator new(0x21F8u) != nullptr )
              goto LABEL_187;
            return 0;
          case 800:
            v17 = operator new(0x21B4u);
            if ( v17 == nullptr )
              return 0;
            result = (int)sub_5D8C80(v17, Block, (int)a2, 0);
            break;
          case 900:
            if ( operator new(0x221Cu) == nullptr )
              return 0;
            result = sub_4A6180(Block, (int)a2);
            break;
          case 901:
            v18 = operator new(0x2278u);
            if ( v18 == nullptr )
              return 0;
            result = (int)sub_5D7C40(v18, Block, (int)a2, 1);
            break;
          case 902:
            if ( operator new(0x21A4u) == nullptr )
              return 0;
            result = sub_4A5700(Block, (int)a2);
            break;
          case 903:
            if ( operator new(0x21A4u) == nullptr )
              return 0;
            result = sub_4AB7B0(Block, (int)a2);
            break;
          default:
            return -842150451;
        }
      }
      else
      {
        if ( Block == 700 )
        {
          v12 = operator new(0x226Cu);
          if ( v12 != nullptr )
            return (int)sub_5D88C0(v12, 188, (int)a2);
          return 0;
        }
        switch ( Block )
        {
          // --- 段B-3 case 407/408 岩浆尸鬼 CNMagmaGhoul（a3 位作变体开关 0/1）、
        //     410-422 蜘蛛系（Wraith/WraithSpectress/RollingSpider/PoisonSpider/
        //     AraclothoSpider，构造见 creature/spider_trap.cpp）、430 幼蜘蛛
        //     CNYoungSpider（creature/）、500-502 洛迪戈（Goliden/Rodinglo）、
        //     600-603 → LABEL_360-366 精灵系（Naias/Ador/Stalker/Wisp）---
          case 407:
            if ( operator new(0x21D4u) == nullptr )
              return 0;
            result = sub_4A2330(Block, a2, 0);
            break;
          case 408:
            if ( operator new(0x21D4u) == nullptr )
              return 0;
            result = sub_4A2330(Block, a2, 1);
            break;
          case 410:
            if ( operator new(0x21CCu) == nullptr )
              return 0;
            result = sub_4AA4E0(Block, (int)a2);
            break;
          case 411:
            if ( operator new(0x2200u) == nullptr )
              return 0;
            result = sub_4AA610(Block, (int)a2);
            break;
          case 420:
            if ( operator new(0x21D0u) == nullptr )
              return 0;
            result = sub_4AA7F0(Block, (int)a2);
            break;
          case 421:
            if ( operator new(0x21B0u) == nullptr )
              return 0;
            result = sub_4AA8E0(Block, (int)a2);
            break;
          case 422:
            if ( operator new(0x2240u) == nullptr )
              return 0;
            result = sub_4AA970(Block, (int)a2);
            break;
          case 430:
            v11 = (uint32_t **)operator new(0x21C0u);
            if ( v11 == nullptr )
              return 0;
            result = (int)sub_5C1C00(v11, Block, (int)a2, 0);
            break;
          case 500:
            if ( operator new(0x21F0u) == nullptr )
              return 0;
            result = sub_4AAED0(Block, (int)a2);
            break;
          case 501:
            if ( operator new(0x21F0u) == nullptr )
              return 0;
            result = sub_4AAF70(Block, (int)a2);
            break;
          case 502:
            if ( operator new(0x21F8u) == nullptr )
              return 0;
            result = sub_4AB010(Block, (int)a2);
            break;
          case 600:
            goto LABEL_360;
          case 601:
            goto LABEL_362;
          case 602:
            goto LABEL_364;
          case 603:
            goto LABEL_366;
          default:
            return -842150451;
        }
      }
    }
    else
    {
      // --- 段B-1 case 406：特例重映射 —— CNGhoul 派生（规范 ID 150，构造 sub_58E1D0，
      //     部件标签 R_GHOUL* 注册见 ui/char_server_info.cpp §0x58E1D0）---
      if ( Block == 406 )
      {
        v10 = operator new(0x21ECu);
        if ( v10 != nullptr )
          return sub_58E1D0((int)v10, 150, (int)a2, 1);
        return 0;
      }
      // --- 段B-2 case 201-281 + 400-405：猎手(HunterAlex/HunterHunter/HunterMaster)、
      //     僵尸(ZombieZombie/HollowEye/Ghoulgwish)、宇宙鱼(SpaceFishShort/Long/Crocuta)、
      //     星鱼(StarFish/StarFishKing/Rukuku/Devourer)、传教士系(Raxy_A/Father/Pope/
      //     Craxy)、攻城器(Catapult/FlameCatapult/LaserCatapult/BattlIngram)、飞艇
      //     (NormalZepplin/CannonZepplin)、尸鬼系 400-405（CNGhoul 派生，构造
      //     sub_58DFE0/58E0E0/58E480/58E1D0 见 ui/char_server_info.cpp）---
      switch ( Block )
      {
        case 201:
          if ( operator new(0x21CCu) == nullptr )
            return 0;
          result = sub_4A8CC0(Block, (int)a2);
          break;
        case 202:
          if ( operator new(0x21D0u) == nullptr )
            return 0;
          result = sub_4A8C20(Block, (int)a2);
          break;
        case 210:
          if ( operator new(0x21CCu) == nullptr )
            return 0;
          result = sub_4A8EE0(Block, (int)a2);
          break;
        case 211:
          if ( operator new(0x21CCu) == nullptr )
            return 0;
          result = sub_4A8F50(Block, (int)a2);
          break;
        case 212:
          if ( operator new(0x21CCu) == nullptr )
            return 0;
          result = sub_4A8FC0(Block, (int)a2);
          break;
        case 220:
          if ( operator new(0x21B0u) == nullptr )
            return 0;
          result = sub_4A95F0(Block, (int)a2);
          break;
        case 221:
          if ( operator new(0x21B0u) == nullptr )
            return 0;
          result = sub_4A9690(Block, (int)a2);
          break;
        case 222:
          if ( operator new(0x21B0u) == nullptr )
            return 0;
          result = sub_4A9730(Block, (int)a2);
          break;
        case 250:
          if ( operator new(0x21D0u) == nullptr )
            return 0;
          result = sub_4A97D0(Block, (int)a2);
          break;
        case 251:
          if ( operator new(0x21F0u) == nullptr )
            return 0;
          result = sub_4A99F0(Block, (int)a2);
          break;
        case 252:
          if ( operator new(0x21D0u) == nullptr )
            return 0;
          result = sub_4A98F0(Block, (int)a2);
          break;
        case 253:
          if ( operator new(0x21D8u) == nullptr )
            return 0;
          result = sub_4A9970(Block, (int)a2);
          break;
        case 260:
          if ( operator new(0x21E4u) == nullptr )
            return 0;
          result = sub_4A9C20(Block, (int)a2);
          break;
        case 261:
        case 265:
          if ( operator new(0x21E4u) == nullptr )
            return 0;
          result = sub_4A9D00(Block, (int)a2);
          break;
        case 262:
        case 266:
          if ( operator new(0x21E4u) == nullptr )
            return 0;
          result = sub_4A9D80(Block, (int)a2);
          break;
        case 263:
          if ( operator new(0x21E4u) == nullptr )
            return 0;
          result = sub_4A9CD0(Block, (int)a2);
          break;
        case 264:
          if ( operator new(0x21E4u) == nullptr )
            return 0;
          result = sub_4A9C50(Block, (int)a2);
          break;
        case 270:
          if ( operator new(0x21B4u) == nullptr )
            return 0;
          result = sub_4AA080(Block, (int)a2);
          break;
        case 271:
          if ( operator new(0x21A8u) == nullptr )
            return 0;
          result = sub_4AA1E0(Block, (int)a2);
          break;
        case 272:
          if ( operator new(0x21B4u) == nullptr )
            return 0;
          result = sub_4AA150(Block, (int)a2);
          break;
        case 273:
          if ( operator new(0x21B4u) == nullptr )
            return 0;
          result = sub_4AA0F0(Block, (int)a2);
          break;
        case 280:
          if ( operator new(0x21E8u) == nullptr )
            return 0;
          result = sub_4AA440(Block, (int)a2);
          break;
        case 281:
          if ( operator new(0x2214u) == nullptr )
            return 0;
          result = sub_4AA3A0(Block, (int)a2);
          break;
        case 400:
          v4 = operator new(0x21ACu);
          if ( v4 == nullptr )
            return 0;
          result = (int)sub_58DFE0(v4, Block, (int)a2, 0);
          break;
        case 401:
          v5 = operator new(0x21B0u);
          if ( v5 == nullptr )
            return 0;
          result = sub_58E0E0((int)v5, Block, (int)a2, 0);
          break;
        case 402:
          v6 = operator new(0x21B4u);
          if ( v6 == nullptr )
            return 0;
          result = sub_58E480((int)v6, Block, (int)a2);
          break;
        case 403:
          v7 = operator new(0x21ACu);
          if ( v7 == nullptr )
            return 0;
          result = (int)sub_58DFE0(v7, Block, (int)a2, 1);
          break;
        case 404:
          v8 = operator new(0x21B0u);
          if ( v8 == nullptr )
            return 0;
          result = sub_58E0E0((int)v8, Block, (int)a2, 1);
          break;
        case 405:
          v9 = operator new(0x21ECu);
          if ( v9 == nullptr )
            return 0;
          result = sub_58E1D0((int)v9, Block, (int)a2, 0);
          break;
        default:
          return -842150451;
      }
    }
    return result;
  }
  // --- 段C（约行 592-802）904 < Block ≤ 50007：万位段复合 ID 工厂（多数重映射旧 ID）---
  if ( Block <= 50007 )
  {
    // --- 段C-0 case 50007：特例重映射 —— CNAuraHunter_Sius（规范 ID 87，构造 sub_4A9330）---
    if ( Block == 50007 )
    {
      if ( operator new(0x21C4u) != nullptr )
        return sub_4A9330(87, (int)a2);
      return 0;
    }
    if ( Block > 41004 )
    {
      if ( Block > 43003 )
      {
        // --- 段C-1 case 50000-50007：复合段（Gardener_Ral/Kalkazak/Rock_Moud/
        //     Bunker_Woker/Prag/DrakeSerimalion/IceDoll_Sharedo）；50005 与段A case 50
        //     共享 LABEL_64（同构造 sub_4A8680，按各自 Block 传参）---
        switch ( Block )
        {
          case 50000:
            if ( operator new(0x21BCu) == nullptr )
              return 0;
            result = sub_4A58C0(Block, (int)a2);
            break;
          case 50001:
            if ( operator new(0x21D4u) == nullptr )
              return 0;
            result = sub_4A9060(Block, (int)a2);
            break;
          case 50002:
            if ( operator new(0x21A0u) == nullptr )
              return 0;
            result = sub_4A7880(Block, (int)a2);
            break;
          case 50003:
            if ( operator new(0x21F0u) == nullptr )
              return 0;
            result = sub_4A6480(Block, (int)a2);
            break;
          case 50004:
            if ( operator new(0x21E0u) == nullptr )
              return 0;
            result = sub_4A67B0(Block, (int)a2);
            break;
          case 50005:
            if ( operator new(0x226Cu) == nullptr )
              return 0;
LABEL_64:
            result = sub_4A8680(Block, (int)a2);
            break;
          case 50006:
            if ( operator new(0x21E0u) == nullptr )
              return 0;
            result = sub_4A82E0(Block, (int)a2);
            break;
          default:
            return -842150451;
        }
        return result;
      }
      // --- 段C-2 case 43003/42001-43003/41001-41005：镜像重映射 —— 以旧 1-200 规范 ID
      //     构造同类怪（43003→251 猎手 / 42004→20 投石车 / 43001→249 / 43002→250
      //     KingGalok / 41005→45 投石车 / 42003→19 / 41001→41 / 41002→42 / 41003→43
      //     精英哥布林 / 42001→17 / 42002→18 / 41004→44 猎手）---
      if ( Block == 43003 )
      {
        if ( operator new(0x21CCu) != nullptr )
          return sub_4A8CC0(251, (int)a2);
        return 0;
      }
      if ( Block > 42003 )
      {
        switch ( Block )
        {
          case 42004:
            if ( operator new(0x21B4u) != nullptr )
              return sub_4AA080(20, (int)a2);
            return 0;
          case 43001:
            if ( operator new(0x21BCu) != nullptr )
              return sub_4A7280(249, (int)a2);
            return 0;
          case 43002:
            if ( operator new(0x21ECu) != nullptr )
              return sub_4A6580(250, (int)a2);
            return 0;
          default:
            break;
        }
      }
      else
      {
        switch ( Block )
        {
          case 42003:
            if ( operator new(0x21CCu) != nullptr )
              return sub_4A8CC0(19, (int)a2);
            return 0;
          case 41005:
            if ( operator new(0x21B4u) != nullptr )
              return sub_4AA080(45, (int)a2);
            return 0;
          case 42001:
            if ( operator new(0x21ECu) != nullptr )
              return sub_4A6540(17, (int)a2);
            return 0;
          case 42002:
            if ( operator new(0x21CCu) != nullptr )
              return sub_4A8D60(18, (int)a2);
            return 0;
          default:
            break;
        }
      }
    }
    else
    {
      // --- 段C-3 case 3000-3002 / 5001-5005 / 40001-40004：boss 与卢加鲁系
      //     （3000→184 LordofLight 光之主 / 3001→185 GolemPlatany / 3002→186 Lotus /
      //     5001→137 Lugaru / 5002→138 BlackLugaru / 5003→139 WhiteLugaru /
      //     5004→140 Penril / 5005→141 BloodLugaru / 40001→65 / 40002→66 /
      //     40003→67 / 40004→68 投掷卡格尔重映射）---
      if ( Block == 41004 )
      {
        if ( operator new(0x21CCu) != nullptr )
          return sub_4A8D60(44, (int)a2);
        return 0;
      }
      if ( Block > 5005 )
      {
        if ( Block > 40004 )
        {
          switch ( Block )
          {
            case 41001:
              if ( operator new(0x21E8u) != nullptr )
                return sub_4A60F0(41, (int)a2);
              return 0;
            case 41002:
              if ( operator new(0x21E8u) != nullptr )
                return sub_4A62A0(42, (int)a2);
              return 0;
            case 41003:
              if ( operator new(0x21E0u) != nullptr )
                return sub_4A6620(43, (int)a2);
              return 0;
            default:
              break;
          }
        }
        else
        {
          switch ( Block )
          {
            case 40004:
              if ( operator new(0x21E0u) != nullptr )
                return sub_4A6F60(68, (int)a2);
              return 0;
            case 40001:
              if ( operator new(0x21E8u) != nullptr )
                return sub_4A60F0(65, (int)a2);
              return 0;
            case 40002:
              if ( operator new(0x21E8u) != nullptr )
                return sub_4A62A0(66, (int)a2);
              return 0;
            case 40003:
              if ( operator new(0x21E0u) != nullptr )
                return sub_4A6620(67, (int)a2);
              return 0;
            default:
              break;
          }
        }
      }
      else
      {
        if ( Block == 5005 )
        {
          if ( operator new(0x21ECu) != nullptr )
            return sub_4A5C90(141, (int)a2);
          return 0;
        }
        if ( Block > 5001 )
        {
          if ( Block == 5002 )
          {
            if ( operator new(0x21BCu) != nullptr )
              return sub_4A59F0(138, (int)a2);
          }
          else if ( Block == 5003 )
          {
            if ( operator new(0x21C0u) != nullptr )
              return sub_4A5AD0(139, (int)a2);
          }
          else if ( operator new(0x21BCu) != nullptr )
          {
            return sub_4A5BB0(140, (int)a2);
          }
          return 0;
        }
        switch ( Block )
        {
          case 5001:
            if ( operator new(0x21B8u) != nullptr )
              return sub_4A57E0(137, (int)a2);
            return 0;
          case 3000:
            if ( operator new(0x21C8u) != nullptr )
              return sub_4A9470(184, (int)a2);
            return 0;
          case 3001:
            if ( operator new(0x21F4u) != nullptr )
              return sub_4A7F70(185, (int)a2);
            return 0;
          case 3002:
            if ( operator new(0x21E0u) != nullptr )
              return sub_4AB740(186, (int)a2);
            return 0;
          default:
            break;
        }
      }
    }
    return -842150451;
  }
  // --- 段D（约行 804-999）Block > 50023：高位段（巨人/守卫塔/机器人/幻影）---
  if ( Block > 50023 )
  {
    // --- 段D-1 case 50068/50069：特例重映射 —— CNGuardLight（规范 ID 148，构造
    //     sub_5D7290）/ CNSoulEter（规范 ID 149，构造 sub_4AB430）---
    if ( Block > 50068 )
    {
      if ( Block > 60005 )
      {
        // --- 段D-2 case 60006-60010：精灵系与幻影（Naias/Ador/Stalker/Wisp/
        //     ProvocationDoll——60010 是唯一把 a3 传入构造的分支）；
        //     60006-60009 与段B case 600-603 共享 LABEL_360-366 ---
        switch ( Block )
        {
          case 60006:
LABEL_360:
            if ( operator new(0x222Cu) == nullptr )
              return 0;
            result = sub_4AB320(Block, (int)a2);
            break;
          case 60007:
LABEL_362:
            if ( operator new(0x222Cu) == nullptr )
              return 0;
            result = sub_4AB3C0(Block, (int)a2);
            break;
          case 60008:
LABEL_364:
            if ( operator new(0x222Cu) == nullptr )
              return 0;
            result = sub_4AB4C0(Block, (int)a2);
            break;
          case 60009:
LABEL_366:
            if ( operator new(0x2230u) == nullptr )
              return 0;
            result = sub_4AB560(Block, (int)a2);
            break;
          case 60010:
            if ( operator new(0x21A4u) == nullptr )
              return 0;
            result = sub_4A5460(Block, (int)a2, a3);
            break;
          default:
            return -842150451;
        }
        return result;
      }
      if ( Block == 60005 )
      {
        if ( operator new(0x21E8u) != nullptr )
          return sub_4A60F0(101, (int)a2);
        return 0;
      }
      if ( Block > 60002 )
      {
        if ( Block == 60003 )
        {
          if ( operator new(0x21B8u) != nullptr )
            return sub_4AAC10(99, (int)a2);
        }
        else if ( operator new(0x21D4u) != nullptr )
        {
          return sub_4AACF0(100, (int)a2);
        }
        return 0;
      }
      switch ( Block )
      {
        case 60002:
          if ( operator new(0x21ACu) != nullptr )
            return sub_4AAB30(98, (int)a2);
          return 0;
        case 50069:
          if ( operator new(0x2230u) != nullptr )
            return sub_4AB430(149, (int)a2);
          return 0;
        case 60001:
          if ( operator new(0x21A0u) != nullptr )
            return sub_4A5380(97, (int)a2);
          return 0;
        default:
          break;
      }
      return -842150451;
    }
    if ( Block == 50068 )
    {
      if ( operator new(0x22E8u) != nullptr )
        return sub_5D7290(148, (int)a2);
      return 0;
    }
    switch ( Block )
    {
      case 50024:
        if ( operator new(0x21C8u) == nullptr )
          return 0;
LABEL_32:
        result = sub_4A5540(Block, (int)a2);
        break;
      case 50030:
        if ( operator new(0x21FCu) == nullptr )
          return 0;
LABEL_183:
        result = sub_4ABC50(Block, (int)a2);
        break;
      case 50031:
        if ( operator new(0x2210u) == nullptr )
          return 0;
LABEL_185:
        result = sub_4ABB70(Block, (int)a2);
        break;
      case 50032:
        if ( operator new(0x21F8u) == nullptr )
          return 0;
LABEL_187:
        result = sub_4ABD30(Block, (int)a2);
        break;
      case 50033:
        if ( operator new(0x21D0u) == nullptr )
          return 0;
        result = sub_4A90D0(Block, (int)a2);
        break;
      case 50034:
        if ( operator new(0x21B0u) == nullptr )
          return 0;
        result = sub_4A0CF0(Block, a2, 1);
        break;
      case 50062:
        if ( operator new(0x2204u) == nullptr )
          return 0;
        result = sub_4A7100(Block, (int)a2);
        break;
      case 50063:
        v19 = operator new(0x226Cu);
        if ( v19 == nullptr )
          return 0;
        result = (int)sub_5D89B0(v19, Block, (int)a2, 1);
        break;
      case 50064:
        if ( operator new(0x22ECu) == nullptr )
          return 0;
        result = sub_5D7740(Block, (int)a2);
        break;
      case 50065:
        if ( operator new(0x235Cu) == nullptr )
          return 0;
        result = sub_5D7360(Block, (int)a2);
        break;
      case 50066:
        if ( operator new(0x22CCu) == nullptr )
          return 0;
        result = sub_5D76D0(Block, (int)a2);
        break;
      case 50067:
        if ( operator new(0x22BCu) == nullptr )
          return 0;
        result = sub_5D75E0(Block, (int)a2);
        break;
      default:
        return -842150451;
    }
  }
  else
  {
      // --- 段D-3 case 50023-50034：亚特拉斯巨人族（Vinoshu→50023 重映射 / Atlas /
      //     Goliath / Titan / BurningHela / GhoulOilSellerOlrek 油商奥雷克）；
      //     50024 与段A case 21 共享 LABEL_32 ---
    if ( Block == 50023 )
    {
      if ( operator new(0x21D8u) != nullptr )
        return sub_4A5620(103, (int)a2);
      return 0;
    }
    switch ( Block )
    {
      case 50008:
        if ( operator new(0x21ECu) == nullptr )
          return 0;
        result = sub_4A8010(Block, (int)a2);
        break;
      case 50009:
        if ( operator new(0x21E4u) == nullptr )
          return 0;
        result = sub_4A9E00(Block, (int)a2);
        break;
      case 50010:
        if ( operator new(0x21E4u) == nullptr )
          return 0;
        result = sub_4A9E50(Block, (int)a2);
        break;
      case 50011:
        if ( operator new(0x21E8u) == nullptr )
          return 0;
        result = sub_4A9E80(Block, (int)a2);
        break;
      case 50012:
        if ( operator new(0x21E4u) == nullptr )
          return 0;
        result = sub_4A9F10(Block, (int)a2);
        break;
      default:
        return -842150451;
    }
  }
  return result;
}

