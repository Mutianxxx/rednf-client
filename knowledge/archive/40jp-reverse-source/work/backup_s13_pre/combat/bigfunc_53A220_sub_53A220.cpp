// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_53A220_sub_53A220.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x53A220）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 1907 行；字符串证据 0 条；外调 6 个
//   调: sub_53A220 sub_534660 sub_533300 sub_5333E0 sub_5334C0 sub_5337D0
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x53A220 sub_53A220  size=17574
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_53A220(int Block, void *pArg2)  // 【巨函数（size=17574）→ src/combat/bigfunc_53A220…】
{
  uint32_t *result; // eax
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // edi

  // ── [段 1] ★ 本函数 = PassiveObject 工厂（Block=PO ID → new + 专属构造），整体是一棵二分阈值 if/switch 树 ──
  //   每 case 骨架同构：operator new(N) 申请对象内存（N 即该 PO 类大小）→ 调类构造器 → 返回对象指针
  //   参数：Block=PO 类型 ID，pArg2=构造参数包（多被强转 int/float 传递）；返回值=新对象或 nullptr
  //   命名依据：全部被调构造器在 missing_misc_b.cpp / gunner_skills.cpp 中已有 RTTI 虚表名直证（CNxxx 构造器）
  //   分派阈值带：>23007 → >30003 → … → <=250（0x51 区地图机关/技能弹体、PO 派生类全表）
  //   注：案例 ID 段与 docs/24 协议包类型无关——这些是 PO 资源 ID（地图机关/技能弹体），非网络包类型
  if ( Block > 23007 )  // 按 PO ID 阈值 > 23007 收窄分支
  {
    if ( Block <= 30003 )  // 按 PO ID 阈值 <= 30003 收窄分支
    {
      // ── [段 2] 30003 特例：CNHunterSpittle（猎手唾液）—— 0x3D0 字节 ──
      if ( Block == 30003 )  // 按 PO ID 阈值 == 30003 收窄分支
      {
        if ( operator new(0x3D0u) != nullptr )  // 申请 976 字节（0x3D0）→ CNHunterSpittle 猎手唾液
          return (uint32_t *)sub_534660(30003, pArg2);  // 返回 CNHunterSpittle 猎手唾液（构造参数包）
        return nullptr;  // 返回空指针（构造失败/未命中）
      }
      // ── [段 3] 23008-23019 段：法师/元素系大型 PO（0x3CC-0x3F4 字节） ──
      //   23008 CNLaunchJOL / 23009 CNLaunchFrostHead / 23010 LAUNCH_FLUORESCENT 荧光发射 / 23011 CNLaunchBlackCat
      switch ( Block )  // 按 PO ID 分派到具体构造
      {
        //   23012 CNVoid / 23013 CNHalloweenBuster / 23014 CNHalloweenBusterSub / 23015 SUN_BURST 阳光爆发 / 23016 CNFireExplosion
        //   23017 QUICK_TURN / 23018 CNTargetItBall / 23019 CNThunderBolt（三参 3 = 雷电形态）
        case 23008:  // PO 23008 → CNLaunchJOL 发射弹
          if ( operator new(0x3E8u) == nullptr )  // 申请 1000 字节（0x3E8）→ CNLaunchJOL 发射弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_533300(Block, pArg2);  // 构造 CNLaunchJOL 发射弹（构造参数包）
          break;
        case 23009:  // PO 23009 → CNLaunchFrostHead 霜首
          if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNLaunchFrostHead 霜首
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_5333E0(Block, pArg2);  // 构造 CNLaunchFrostHead 霜首（构造参数包）
          break;
        case 23010:  // PO 23010 → 荧光发射机关（LAUNCH_FLUORESCENT）
          if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ 荧光发射机关（LAUNCH_FLUORESCENT）
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_5334C0(Block, pArg2);  // 构造 荧光发射机关（LAUNCH_FLUORESCENT）（构造参数包）
          break;
        case 23011:  // PO 23011 → CNLaunchBlackCat 黑猫发射
          if ( operator new(0x3F4u) == nullptr )  // 申请 1012 字节（0x3F4）→ CNLaunchBlackCat 黑猫发射
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_5337D0(Block, pArg2);  // 构造 CNLaunchBlackCat 黑猫发射（构造参数包）
          break;
        case 23012:  // PO 23012 → CNVoid 虚空（VOID）
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNVoid 虚空（VOID）
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_5338B0(Block, pArg2);  // 构造 CNVoid 虚空（VOID）（构造参数包）
          break;
        case 23013:  // PO 23013 → CNHalloweenBuster 万圣节爆破
          if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNHalloweenBuster 万圣节爆破
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_533C10(Block, pArg2);  // 构造 CNHalloweenBuster 万圣节爆破（构造参数包）
          break;
        case 23014:  // PO 23014 → CNHalloweenBusterSub 万圣节爆破子体
          if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNHalloweenBusterSub 万圣节爆破子体
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_533CF0(Block, pArg2);  // 构造 CNHalloweenBusterSub 万圣节爆破子体（构造参数包）
          break;
        case 23015:  // PO 23015 → 阳光爆发（SUN_BURST）
          if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ 阳光爆发（SUN_BURST）
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_533DD0(Block, pArg2);  // 构造 阳光爆发（SUN_BURST）（构造参数包）
          break;
        case 23016:  // PO 23016 → CNFireExplosion 火焰爆炸
          if ( operator new(0x3E4u) != nullptr )  // 申请 996 字节（0x3E4）→ CNFireExplosion 火焰爆炸
            return (uint32_t *)sub_52F2C0(Block, pArg2);  // 返回 CNFireExplosion 火焰爆炸（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 23017:  // PO 23017 → 快速转身（QUICK_TURN）
          if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ 快速转身（QUICK_TURN）
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_5340A0(Block, pArg2);  // 构造 快速转身（QUICK_TURN）（构造参数包）
          break;
        case 23018:  // PO 23018 → CNTargetItBall 标记球
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNTargetItBall 标记球
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_534580(Block, pArg2);  // 构造 CNTargetItBall 标记球（构造参数包）
          break;
        case 23019:  // PO 23019 → CNThunderBolt 雷电
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNThunderBolt 雷电
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_52F4D0(Block, pArg2, 3);  // 构造 CNThunderBolt 雷电(pArg2, 3)
          break;
        //   上表未命中（default）→ goto LABEL_494 通用兜底（CNRDPooledPassiveObject 构造）
        default:
          goto LABEL_494;  // 转到公共出口 LABEL_494
      }
      return result;  // 返回已构造对象
    }
    // ── [段 4] 30004-30100 段：技能弹体主区（分段分支极密，每型一 new+构造） ──
    if ( Block <= 30100 )  // 按 PO ID 阈值 <= 30100 收窄分支
    {
      if ( Block == 30100 )  // 按 PO ID 阈值 == 30100 收窄分支
      {
        if ( operator new(0x3D0u) != nullptr )  // 申请 976 字节（0x3D0）→ CNCobWeb 蛛网
          return (uint32_t *)sub_535600(30100, pArg2);  // 返回 CNCobWeb 蛛网（构造参数包）
        return nullptr;  // 返回空指针（构造失败/未命中）
      }
      switch ( Block )  // 按 PO ID 分派到具体构造
      {
        //   30004 CNZombieEye / 30005 CNZombieEyeExplode / 30006 CNKagelBomb（内部转 30008）/ 30008 CNKagelBombSub
        case 30004:  // PO 30004 → CNZombieEye 僵尸眼
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNZombieEye 僵尸眼
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534700(Block, pArg2);  // 返回 CNZombieEye 僵尸眼（构造参数包）
        case 30005:  // PO 30005 → CNZombieEyeExplode 僵尸眼爆炸
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNZombieEyeExplode 僵尸眼爆炸
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_5347A0(Block, pArg2);  // 返回 CNZombieEyeExplode 僵尸眼爆炸（构造参数包）
        case 30006:  // PO 30006 → CNKagelBomb 卡格尔炸弹
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNKagelBomb 卡格尔炸弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534840(Block, 30008);  // 返回 CNKagelBomb 卡格尔炸弹(30008)
        case 30008:  // PO 30008 → CNKagelBombSub 卡格尔炸弹子体
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNKagelBombSub 卡格尔炸弹子体
            return (uint32_t *)sub_5348A0(Block, pArg2);  // 返回 CNKagelBombSub 卡格尔炸弹子体（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        //   30009 CNBronzeGolemBullets / 30010-30011 CNTreadShootSub / 30012 CNAshenForkSub / 30013 CNSpaceFishBug
        case 30009:  // PO 30009 → CNBronzeGolemBullets 青铜魔像弹
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNBronzeGolemBullets 青铜魔像弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534BC0(Block, pArg2);  // 返回 CNBronzeGolemBullets 青铜魔像弹（构造参数包）
        case 30010:  // PO 30010（无专属构造器）
        case 30011:  // PO 30011 → 补漏小构造
          if ( operator new(0x3F8u) == nullptr )  // 申请 1016 字节（0x3F8）→ 补漏小构造
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534A90(Block, pArg2);  // 返回 补漏小构造（构造参数包）
        case 30012:  // PO 30012 → 补漏小构造
          if ( operator new(0x3F8u) == nullptr )  // 申请 1016 字节（0x3F8）→ 补漏小构造
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534AF0(Block, pArg2);  // 返回 补漏小构造（构造参数包）
        case 30013:  // PO 30013 → CNSpaceFishBug 空鱼虫
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNSpaceFishBug 空鱼虫
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534990(Block, pArg2);  // 返回 CNSpaceFishBug 空鱼虫（构造参数包）
        //   30015/30036 → LABEL_527（CNLOLLaser）；30016/30017+30003 同族 CNHunterSpittle；30018 CNZepplinBullet
        case 30015:  // PO 30015（无专属构造器）
        case 30036:  // PO 30036 与同组 ID 共用出口 LABEL_527
          goto LABEL_527;  // 转到公共出口 LABEL_527
        case 30016:  // PO 30016（无专属构造器）
        case 30017:  // PO 30017 → CNHunterSpittle 猎手唾液
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNHunterSpittle 猎手唾液
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534660(Block, pArg2);  // 返回 CNHunterSpittle 猎手唾液（构造参数包）
        //   30019 CNKagelBomb(30020) / 30020 CNKagelBombSub / 30021 CNCreateOnDestroyObject / 30023 CNKagelBomb(30024)
        case 30018:  // PO 30018 → CNZepplinBullet 飞艇弹
          if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNZepplinBullet 飞艇弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534FA0(Block, pArg2);  // 返回 CNZepplinBullet 飞艇弹（构造参数包）
        case 30019:  // PO 30019 → CNKagelBomb 卡格尔炸弹
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNKagelBomb 卡格尔炸弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534840(Block, 30020);  // 返回 CNKagelBomb 卡格尔炸弹(30020)
        case 30020:  // PO 30020 → CNKagelBombSub 卡格尔炸弹子体
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNKagelBombSub 卡格尔炸弹子体
            return (uint32_t *)sub_5348A0(Block, pArg2);  // 返回 CNKagelBombSub 卡格尔炸弹子体（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30021:  // PO 30021 → CNCreateOnDestroyObject 销毁生成物
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNCreateOnDestroyObject 销毁生成物
            return (uint32_t *)sub_530040(Block, pArg2);  // 返回 CNCreateOnDestroyObject 销毁生成物（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30022:  // PO 30022 与同组 ID 共用出口 LABEL_346
          if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）→ CNKagelBomb 卡格尔炸弹
            goto LABEL_346;  // 转到公共出口 LABEL_346
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30023:  // PO 30023 → CNKagelBomb 卡格尔炸弹
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNKagelBomb 卡格尔炸弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534840(Block, 30024);  // 返回 CNKagelBomb 卡格尔炸弹(30024)
        //   30024/30032/30035/30064/30078 CNKagelBombSub 复用 / 30025+30380 CNIceWaveUp / 30026 CNStoneBlade …
        case 30024:  // PO 30024 → CNKagelBombSub 卡格尔炸弹子体
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNKagelBombSub 卡格尔炸弹子体
            return (uint32_t *)sub_5348A0(Block, pArg2);  // 返回 CNKagelBombSub 卡格尔炸弹子体（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30025:  // PO 30025 → CNIceWaveUp 上向冰波
          if ( operator new(0x3D0u) != nullptr )  // 申请 976 字节（0x3D0）→ CNIceWaveUp 上向冰波
            return (uint32_t *)sub_534C60(Block, pArg2);  // 返回 CNIceWaveUp 上向冰波（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30026:  // PO 30026 → CNStoneBlade 石刃
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNStoneBlade 石刃
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534D40(Block, pArg2);  // 返回 CNStoneBlade 石刃（构造参数包）
        //   30028 CNGrabbingLegOfLotus（巨型黑章鱼抓腿）/ 30029 CNPierceHeadLegOfLotus / 30030-30031 CNZepplinBullet
        case 30028:  // PO 30028 → CNGrabbingLegOfLotus 莲抓取腿
          if ( operator new(0x400u) == nullptr )  // 申请 1024 字节（0x400）→ CNGrabbingLegOfLotus 莲抓取腿
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534F40(Block, pArg2);  // 返回 CNGrabbingLegOfLotus 莲抓取腿（构造参数包）
        case 30029:  // PO 30029 → CNPierceHeadLegOfLotus 莲穿刺头腿
          if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNPierceHeadLegOfLotus 莲穿刺头腿
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534EB0(Block, pArg2);  // 返回 CNPierceHeadLegOfLotus 莲穿刺头腿（构造参数包）
        case 30030:  // PO 30030（无专属构造器）
        case 30031:  // PO 30031 → CNDendroidSeed 树状种子
          if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNDendroidSeed 树状种子
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_535010(Block, pArg2);  // 返回 CNDendroidSeed 树状种子（构造参数包）
        //   30033 CNRDTrap 基座直构（走通用底座 0x52EA60，非派生专属构造）/ 30034+30037 CNKagelBombSub(30335/30046) 双档
        case 30032:  // PO 30032 → CNKagelBombSub 卡格尔炸弹子体
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNKagelBombSub 卡格尔炸弹子体
            return (uint32_t *)sub_5348A0(Block, pArg2);  // 返回 CNKagelBombSub 卡格尔炸弹子体（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30033:  // PO 30033 → CNRDTrap 基座构造
          pMem = operator new(0x3CCu);
          if ( pMem == nullptr )
            return nullptr;  // 返回空指针（构造失败/未命中）
          return sub_52EA60(pMem, Block, (int)pArg2);
        case 30034:  // PO 30034 → CNOntoLandMakePassiveObject 落地生成物
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNOntoLandMakePassiveObject 落地生成物
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_5352D0(Block, pArg2, 30035, 0);  // 返回 CNOntoLandMakePassiveObject 落地生成物(pArg2, 30035, 0)
        case 30035:  // PO 30035 → CNKagelBombSub 卡格尔炸弹子体
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNKagelBombSub 卡格尔炸弹子体
            return (uint32_t *)sub_5348A0(Block, pArg2);  // 返回 CNKagelBombSub 卡格尔炸弹子体（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30037:  // PO 30037 → CNOntoLandMakePassiveObject 落地生成物
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNOntoLandMakePassiveObject 落地生成物
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_5352D0(Block, pArg2, 30046, 5);  // 返回 CNOntoLandMakePassiveObject 落地生成物(pArg2, 30046, 5)
        //   30038-30040 CNGunnerLaser（三 ID 同型）…
        case 30038:  // PO 30038（无专属构造器）
        case 30039:  // PO 30039（无专属构造器）
        case 30040:  // PO 30040 → CNDendroidNeedle 树状针
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNDendroidNeedle 树状针
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_5351F0(Block, pArg2);  // 返回 CNDendroidNeedle 树状针（构造参数包）
        // ── [段 5] 30043-30094 段：CNCreateOnDestroyObject / CNFireMissile / CNIceMissile / CNShootingStar 族 ──
        case 30043:  // PO 30043 与同组 ID 共用出口 LABEL_370
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNFireExplosion 火焰爆炸
            goto LABEL_370;  // 转到公共出口 LABEL_370
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30044:  // PO 30044 → CNFireExplosion 火焰爆炸
          if ( operator new(0x3E4u) != nullptr )  // 申请 996 字节（0x3E4）→ CNFireExplosion 火焰爆炸
            return (uint32_t *)sub_52F2C0(Block, pArg2);  // 返回 CNFireExplosion 火焰爆炸（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30045:  // PO 30045 → CNFireExplosion 火焰爆炸
          if ( operator new(0x3E4u) != nullptr )  // 申请 996 字节（0x3E4）→ CNFireExplosion 火焰爆炸
            return (uint32_t *)sub_52F2C0(Block, pArg2);  // 返回 CNFireExplosion 火焰爆炸（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        //   30046 → LABEL_503 与 40006 共用 sub_52FAD0(500,1,1)；30047/30049 CNTagetItBall…
        case 30046:  // PO 30046 与同组 ID 共用出口 LABEL_503
          goto LABEL_503;  // 转到公共出口 LABEL_503
        case 30047:  // PO 30047（无专属构造器）
        case 30049:  // PO 30049 → CNFireMissile 火焰飞弹
          if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNFireMissile 火焰飞弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_52F1E0(Block, pArg2);  // 返回 CNFireMissile 火焰飞弹（构造参数包）
        case 30048:  // PO 30048（无专属构造器）
        case 30050:  // PO 30050 与同组 ID 共用出口 LABEL_378
          if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）对象
            return nullptr;  // 返回空指针（构造失败/未命中）
          goto LABEL_378;  // 转到公共出口 LABEL_378
        //   30051/30052+40006 走 sub_52FAD0 四/五参（500,1, flag）
        case 30051:  // PO 30051 与同组 ID 共用出口 LABEL_378
          if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）对象
            return nullptr;  // 返回空指针（构造失败/未命中）
          goto LABEL_378;  // 转到公共出口 LABEL_378
        case 30052:  // PO 30052 与同组 ID 共用出口 LABEL_382
          if ( operator new(0x3F0u) != nullptr )  // 申请 1008 字节（0x3F0）对象
            goto LABEL_382;  // 转到公共出口 LABEL_382
          return nullptr;  // 返回空指针（构造失败/未命中）
        //   30053-30056：CNFireExplosion 爆炸族（0x3E0-0x3E4）
        case 30053:  // PO 30053（无专属构造器）
        case 30054:  // PO 30054 与同组 ID 共用出口 LABEL_384
          if ( operator new(0x3E0u) != nullptr )  // 申请 992 字节（0x3E0）→ CNFireExplosion 火焰爆炸
            goto LABEL_384;  // 转到公共出口 LABEL_384
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30055:  // PO 30055（无专属构造器）
        case 30056:  // PO 30056 → CNFireExplosion 火焰爆炸
          if ( operator new(0x3E4u) != nullptr )  // 申请 996 字节（0x3E4）→ CNFireExplosion 火焰爆炸
            return (uint32_t *)sub_52F2C0(Block, pArg2);  // 返回 CNFireExplosion 火焰爆炸（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        //   30057-30063：CNIceMissile 族（0x3D4）+ CNIceWave/CNIceNiddle（0x3CC）—— 30060..30063 与 30085..30088 同构
        case 30057:  // PO 30057（无专属构造器）
        case 30058:  // PO 30058 → CNIceMissile 冰飞弹
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNIceMissile 冰飞弹
            return (uint32_t *)sub_52F3F0(Block, pArg2);  // 返回 CNIceMissile 冰飞弹（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30059:  // PO 30059 与同组 ID 共用出口 LABEL_537
          if ( operator new(0x3E8u) != nullptr )  // 申请 1000 字节（0x3E8）对象
            goto LABEL_537;  // 转到公共出口 LABEL_537
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30060:  // PO 30060（无专属构造器）
        case 30061:  // PO 30061（无专属构造器）
        case 30062:  // PO 30062（无专属构造器）
        case 30063:  // PO 30063 → CNIceNiddle 冰针
          if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）→ CNIceNiddle 冰针
            return (uint32_t *)sub_52FA30(Block, pArg2);  // 返回 CNIceNiddle 冰针（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30064:  // PO 30064 → CNKagelBombSub 卡格尔炸弹子体
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNKagelBombSub 卡格尔炸弹子体
            return (uint32_t *)sub_5348A0(Block, pArg2);  // 返回 CNKagelBombSub 卡格尔炸弹子体（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        //   30065 → LABEL_506 sub_530270=CNRedRock；30066 → LABEL_568 sub_52FBC0=CNShootingStar
        case 30065:  // PO 30065 与同组 ID 共用出口 LABEL_506
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）对象
            goto LABEL_506;  // 转到公共出口 LABEL_506
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30066:  // PO 30066 与同组 ID 共用出口 LABEL_568
          if ( operator new(0x3D8u) != nullptr )  // 申请 984 字节（0x3D8）对象
            goto LABEL_568;  // 转到公共出口 LABEL_568
          return nullptr;  // 返回空指针（构造失败/未命中）
        //   30067 → LABEL_569 sub_52FCA0=CNShootingStarExp(0)
        case 30067:  // PO 30067 与同组 ID 共用出口 LABEL_569
          goto LABEL_569;  // 转到公共出口 LABEL_569
        //   30068-30069 CNSunkenRock / 30070-30074 CNThunderBolt(0) 五连 / 30077 CNKagelBomb(30078)
        case 30068:  // PO 30068（无专属构造器）
        case 30069:  // PO 30069 → CNSunkenRock 沉岩
          if ( operator new(0x3D0u) != nullptr )  // 申请 976 字节（0x3D0）→ CNSunkenRock 沉岩
            return (uint32_t *)sub_5301D0(Block, pArg2);  // 返回 CNSunkenRock 沉岩（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30070:  // PO 30070（无专属构造器）
        case 30071:  // PO 30071（无专属构造器）
        case 30072:  // PO 30072（无专属构造器）
        case 30073:  // PO 30073（无专属构造器）
        case 30074:  // PO 30074 → CNThunderBolt 雷电
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNThunderBolt 雷电
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_52F4D0(Block, pArg2, 0);  // 返回 CNThunderBolt 雷电(pArg2, 0)
        case 30077:  // PO 30077 → CNKagelBomb 卡格尔炸弹
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNKagelBomb 卡格尔炸弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_534840(Block, 30078);  // 返回 CNKagelBomb 卡格尔炸弹(30078)
        case 30078:  // PO 30078 → CNKagelBombSub 卡格尔炸弹子体
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNKagelBombSub 卡格尔炸弹子体
            return (uint32_t *)sub_5348A0(Block, pArg2);  // 返回 CNKagelBombSub 卡格尔炸弹子体（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        //   30080 CNToothKurokuta / 30081 … / 30084 与 30059 同型（CNShootingStarExp）
        case 30080:  // PO 30080 → CNRisingShuriken 上升手里剑
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNRisingShuriken 上升手里剑
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_5353D0(Block, pArg2);  // 返回 CNRisingShuriken 上升手里剑（构造参数包）
        case 30081:  // PO 30081 → CNFallingShuriken 下落手里剑
          if ( operator new(0x3ECu) == nullptr )  // 申请 1004 字节（0x3EC）→ CNFallingShuriken 下落手里剑
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_535450(Block, pArg2);  // 返回 CNFallingShuriken 下落手里剑（构造参数包）
        case 30084:  // PO 30084 与同组 ID 共用出口 LABEL_537
          if ( operator new(0x3E8u) != nullptr )  // 申请 1000 字节（0x3E8）对象
            goto LABEL_537;  // 转到公共出口 LABEL_537
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30085:  // PO 30085（无专属构造器）
        case 30086:  // PO 30086（无专属构造器）
        case 30087:  // PO 30087（无专属构造器）
        case 30088:  // PO 30088 → CNIceNiddle 冰针
          if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）→ CNIceNiddle 冰针
            return (uint32_t *)sub_52FA30(Block, pArg2);  // 返回 CNIceNiddle 冰针（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 30089:  // PO 30089（无专属构造器）
        case 30095:  // PO 30095 → CNGhoulSkull 食尸鬼头颅
          if ( operator new(0x434u) == nullptr )  // 申请 1076 字节（0x434）→ CNGhoulSkull 食尸鬼头颅
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_535520(Block, pArg2);  // 返回 CNGhoulSkull 食尸鬼头颅（构造参数包）
        //   30089+30095 同型（0x434 大对象）/ 30090 / 30091-30092-30093 与 40007 共享类
        case 30090:  // PO 30090 → CNGhoulSkullBomb 食尸鬼头颅弹
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNGhoulSkullBomb 食尸鬼头颅弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_535560(Block, pArg2);  // 返回 CNGhoulSkullBomb 食尸鬼头颅弹（构造参数包）
        case 30091:  // PO 30091 → CNEarthFire 地火
          if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNEarthFire 地火
            return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_378:
          result = (uint32_t *)sub_52FAD0(Block, pArg2, 500, 1, 0);  // 构造 CNEarthFire 地火(pArg2, 500, 1, 0)
          break;
        //   30092-30093 → sub_61E4C0=头骨子体 CNGhoulSkullSub 构造（0x5E 区之外）
        case 30092:  // PO 30092（无专属构造器）
        case 30093:  // PO 30093 → 头骨子体构造
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ 头骨子体构造
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_61E4C0(Block, pArg2);  // 构造 头骨子体构造（构造参数包）
          break;
        //   30094 → LABEL_490 = CNIceWaveUp
        case 30094:  // PO 30094 与同组 ID 共用出口 LABEL_490
          goto LABEL_490;  // 转到公共出口 LABEL_490
        default:
          goto LABEL_494;  // 转到公共出口 LABEL_494
      }
      return result;  // 返回已构造对象
    }
    // ── [段 6] Block 处于 (30100, 48008]：地图机关/技能弹体第二主区 ──
    if ( Block <= 48008 )  // 按 PO ID 阈值 <= 48008 收窄分支
    {
      // ── [段 7] 48005-48008 段：全走 sub_52FA30=CNIceNiddle（0x3CC 窄对象） ──
      if ( Block >= 48005 )  // 按 PO ID 阈值 >= 48005 收窄分支
      {
        if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）对象
          return nullptr;  // 返回空指针（构造失败/未命中）
      }
      else
      {
        // ── [段 8] Block 处于 (30368, 48005)：按 42002/46003 二分 ──
        if ( Block > 30368 )  // 按 PO ID 阈值 > 30368 收窄分支
        {
          if ( Block > 42002 )  // 按 PO ID 阈值 > 42002 收窄分支
          {
            if ( Block > 46003 )  // 按 PO ID 阈值 > 46003 收窄分支
            {
              switch ( Block )  // 按 PO ID 分派到具体构造
              {
                // ── [段 9] 48001-48004：CNBlast 爆炸族 ──
                //   48001 CNBlast / 48002 CNEarthQuake / 48003+48004 CNDangerousGas（48004 → LABEL_537 CNIceNiddleGroup）
                case 48001:  // PO 48001 → CNBlast 爆风
                  if ( operator new(0x3E0u) == nullptr )  // 申请 992 字节（0x3E0）→ CNBlast 爆风
                    return nullptr;  // 返回空指针（构造失败/未命中）
                  result = (uint32_t *)sub_52F6A0(Block, pArg2);  // 构造 CNBlast 爆风（构造参数包）
                  break;
                case 48002:  // PO 48002 → CNEarthQuake 地震
                  if ( operator new(0x3E0u) == nullptr )  // 申请 992 字节（0x3E0）→ CNEarthQuake 地震
                    return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_384:
                  result = (uint32_t *)sub_52F780(Block, pArg2);  // 构造 CNEarthQuake 地震（构造参数包）
                  break;
                case 48003:  // PO 48003 → CNDangerousGas 毒气
                  if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNDangerousGas 毒气
                    return nullptr;  // 返回空指针（构造失败/未命中）
                  result = (uint32_t *)sub_52F860(Block, pArg2, 0);  // 构造 CNDangerousGas 毒气(pArg2, 0)
                  break;
                case 48004:  // PO 48004 → CNIceNiddleGroup 冰针群
                  if ( operator new(0x3E8u) == nullptr )  // 申请 1000 字节（0x3E8）→ CNIceNiddleGroup 冰针群
                    return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_537:
                  result = (uint32_t *)sub_52F950(Block, pArg2);  // 构造 CNIceNiddleGroup 冰针群（构造参数包）
                  break;
                default:
                  goto LABEL_494;  // 转到公共出口 LABEL_494
              }
              return result;  // 返回已构造对象
            }
            // ── [段 10] 46003 → LABEL_527（CNLOLLaser）；46001 CNThunderBolt(0)、46002 CNTemporaryHit ──
            if ( Block == 46003 )  // 按 PO ID 阈值 == 46003 收窄分支
            {
LABEL_527:
              if ( operator new(0x3D8u) != nullptr )  // 申请 984 字节（0x3D8）→ CNLOLLaser 洛尔激光
                return (uint32_t *)sub_534B20(Block, pArg2);  // 返回 CNLOLLaser 洛尔激光（构造参数包）
              return nullptr;  // 返回空指针（构造失败/未命中）
            }
            if ( Block > 44001 )  // 按 PO ID 阈值 > 44001 收窄分支
            {
              if ( Block == 46001 )  // 按 PO ID 阈值 == 46001 收窄分支
              {
                if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNThunderBolt 雷电
                  return (uint32_t *)sub_52F4D0(46001, pArg2, 0);  // 返回 CNThunderBolt 雷电(pArg2, 0)
                return nullptr;  // 返回空指针（构造失败/未命中）
              }
              if ( Block == 46002 )  // 按 PO ID 阈值 == 46002 收窄分支
              {
                if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）→ CNTemporaryHit 临时命中
                  return (uint32_t *)sub_530500(46002, pArg2);  // 返回 CNTemporaryHit 临时命中（构造参数包）
                return nullptr;  // 返回空指针（构造失败/未命中）
              }
              goto LABEL_494;  // 转到公共出口 LABEL_494
            }
            if ( Block != 44001 )  // 按 PO ID 阈值 != 44001 收窄分支
            {
              if ( Block <= 42006 )  // 按 PO ID 阈值 <= 42006 收窄分支
              {
// ── [段 11] 42001-42007 段：CNIceMissile(42001) / ≤42006+48011… 走 LABEL_545=CNTemporaryHit / 42007 CNSingleIceWave ──
LABEL_545:
                if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）→ CNTemporaryHit 临时命中
                  return (uint32_t *)sub_530500(Block, pArg2);  // 返回 CNTemporaryHit 临时命中（构造参数包）
                return nullptr;  // 返回空指针（构造失败/未命中）
              }
              if ( Block == 42007 )  // 按 PO ID 阈值 == 42007 收窄分支
              {
                if ( operator new(0x3FCu) != nullptr )  // 申请 1020 字节（0x3FC）→ CNSingleIceWave 单冰波
                  return (uint32_t *)sub_531060(42007, pArg2);  // 返回 CNSingleIceWave 单冰波（构造参数包）
                return nullptr;  // 返回空指针（构造失败/未命中）
              }
              goto LABEL_494;  // 转到公共出口 LABEL_494
            }
          }
          else
          {
            // ── [段 12] 40001-40008 段：40004(CNLaser) 40005 40006 40007 40008 ──
            //   40001/40002 CNSpaceFishBug 族（0x3D8）/ 40003 CNEarthFire / 40006 CNEarthFire(1) / 40008 CNShootingStarExp(1)
            if ( Block >= 42001 )  // 按 PO ID 阈值 >= 42001 收窄分支
            {
              if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNIceMissile 冰飞弹
                return (uint32_t *)sub_52F3F0(Block, pArg2);  // 返回 CNIceMissile 冰飞弹（构造参数包）
              return nullptr;  // 返回空指针（构造失败/未命中）
            }
            if ( Block > 40003 )  // 按 PO ID 阈值 > 40003 收窄分支
            {
              switch ( Block )  // 按 PO ID 分派到具体构造
              {
                case 40004:  // PO 40004 与同组 ID 共用出口 LABEL_568
                  if ( operator new(0x3D8u) != nullptr )  // 申请 984 字节（0x3D8）对象
                    goto LABEL_568;  // 转到公共出口 LABEL_568
                  return nullptr;  // 返回空指针（构造失败/未命中）
                case 40005:  // PO 40005 与同组 ID 共用出口 LABEL_569
                  goto LABEL_569;  // 转到公共出口 LABEL_569
                case 40006:  // PO 40006 → CNEarthFire 地火
LABEL_503:
                  if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNEarthFire 地火
                    return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_382:
                  result = (uint32_t *)sub_52FAD0(Block, pArg2, 500, 1, 1);  // 构造 CNEarthFire 地火(pArg2, 500, 1, 1)
                  break;
                case 40007:  // PO 40007 → CNRedRock 红岩
                  if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNRedRock 红岩
                    return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_506:
                  result = (uint32_t *)sub_530270(Block, pArg2);  // 构造 CNRedRock 红岩（构造参数包）
                  break;
                case 40008:  // PO 40008 → CNShootingStarExp 流星爆
                  if ( operator new(0x3E8u) == nullptr )  // 申请 1000 字节（0x3E8）→ CNShootingStarExp 流星爆
                    return nullptr;  // 返回空指针（构造失败/未命中）
                  result = (uint32_t *)sub_52FCA0(Block, pArg2, 1);  // 构造 CNShootingStarExp 流星爆(pArg2, 1)
                  break;
                default:
                  goto LABEL_494;  // 转到公共出口 LABEL_494
              }
              return result;  // 返回已构造对象
            }
            if ( Block == 40003 )  // 按 PO ID 阈值 == 40003 收窄分支
            {
              if ( operator new(0x3F0u) != nullptr )  // 申请 1008 字节（0x3F0）→ CNEarthFire 地火
                return (uint32_t *)sub_52FAD0(40003, pArg2, 500, 1, 0);  // 返回 CNEarthFire 地火(pArg2, 500, 1, 0)
              return nullptr;  // 返回空指针（构造失败/未命中）
            }
            // ── [段 13] 30370-30380 段：30370+30371 CNKagelBomb 双 ID 同型 / 30380 CNIceWaveUp ──
            if ( Block <= 30380 )  // 按 PO ID 阈值 <= 30380 收窄分支
            {
              switch ( Block )  // 按 PO ID 分派到具体构造
              {
                case 30380:  // PO 30380 → CNIceWaveUp 上向冰波
LABEL_490:
                  if ( operator new(0x3D0u) != nullptr )  // 申请 976 字节（0x3D0）→ CNIceWaveUp 上向冰波
                    return (uint32_t *)sub_534C60(Block, pArg2);  // 返回 CNIceWaveUp 上向冰波（构造参数包）
                  return nullptr;  // 返回空指针（构造失败/未命中）
                case 30370:  // PO 30370 → CNKagelBomb 卡格尔炸弹
                  if ( operator new(0x3D0u) != nullptr )  // 申请 976 字节（0x3D0）→ CNKagelBomb 卡格尔炸弹
                    return (uint32_t *)sub_534840(30370, 30371);  // 返回 CNKagelBomb 卡格尔炸弹(30371)
                  return nullptr;  // 返回空指针（构造失败/未命中）
                case 30371:  // PO 30371 → CNKagelBombSub 卡格尔炸弹子体
                  if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNKagelBombSub 卡格尔炸弹子体
                    return (uint32_t *)sub_5348A0(30371, pArg2);  // 返回 CNKagelBombSub 卡格尔炸弹子体（构造参数包）
                  return nullptr;  // 返回空指针（构造失败/未命中）
                default:
                  break;
              }
              goto LABEL_494;  // 转到公共出口 LABEL_494
            }
            if ( Block == 40001 )  // 按 PO ID 阈值 == 40001 收窄分支
            {
              if ( operator new(0x3D8u) != nullptr )  // 申请 984 字节（0x3D8）→ CNFireMissile 火焰飞弹
                return (uint32_t *)sub_52F1E0(40001, pArg2);  // 返回 CNFireMissile 火焰飞弹（构造参数包）
              return nullptr;  // 返回空指针（构造失败/未命中）
            }
            if ( Block != 40002 )  // 按 PO ID 阈值 != 40002 收窄分支
              goto LABEL_494;  // 转到公共出口 LABEL_494
          }
// ── [段 14] LABEL_519：sub_52F2C0=CNFireExplosion 共通构造 ──
LABEL_519:
          if ( operator new(0x3E4u) != nullptr )  // 申请 996 字节（0x3E4）→ CNFireExplosion 火焰爆炸
            return (uint32_t *)sub_52F2C0(Block, pArg2);  // 返回 CNFireExplosion 火焰爆炸（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        }
        // ── [段 15] Block < 30365：30302-30310 大段（头骨/邪眼/巨型黑章鱼/CNTrackingIceWave 等） ──
        if ( Block < 30365 )  // 按 PO ID 阈值 < 30365 收窄分支
        {
          switch ( Block )  // 按 PO ID 分派到具体构造
          {
            //   30200 CNGrabbingLegOfLotus(0x3F8) / 30201 CNPierceHeadLegOfLotus / 30202 → LABEL_563=CNBodyHit
            case 30200:  // PO 30200 → 蜘蛛 BOSS 导弹烟雾
              if ( operator new(0x3F8u) == nullptr )  // 申请 1016 字节（0x3F8）→ 蜘蛛 BOSS 导弹烟雾
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_535670(Block, pArg2);  // 构造 蜘蛛 BOSS 导弹烟雾（构造参数包）
              break;
            case 30201:  // PO 30201 → CNAraclothoSpark 阿拉克托火花
              if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNAraclothoSpark 阿拉克托火花
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_535850(Block, pArg2);  // 构造 CNAraclothoSpark 阿拉克托火花（构造参数包）
              break;
            case 30202:  // PO 30202 与同组 ID 共用出口 LABEL_563
              goto LABEL_563;  // 转到公共出口 LABEL_563
            //   30300 CNSpiralNen(0x3F4) / 30301-30305 CNTargetItBall 四型（0x3CC-0x3D8）
            case 30300:  // PO 30300 → CNSpectressBat 幽女蝠
              if ( operator new(0x3F4u) == nullptr )  // 申请 1012 字节（0x3F4）→ CNSpectressBat 幽女蝠
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_5358C0(Block, pArg2);  // 构造 CNSpectressBat 幽女蝠（构造参数包）
              break;
            case 30301:  // PO 30301 → 邪眼大激光构造
              if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ 邪眼大激光构造
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_61F7D0(Block, pArg2);  // 构造 邪眼大激光构造（构造参数包）
              break;
            case 30302:  // PO 30302 → 邪眼飞弹构造
              if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ 邪眼飞弹构造
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_61F8B0(Block, pArg2);  // 构造 邪眼飞弹构造（构造参数包）
              break;
            case 30303:  // PO 30303 → 邪眼小激光构造
              if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ 邪眼小激光构造
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_61F9F0(Block, pArg2);  // 构造 邪眼小激光构造（构造参数包）
              break;
            case 30304:  // PO 30304 → CNEvilEyeSmallLOLLaser 邪眼小激光
              if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNEvilEyeSmallLOLLaser 邪眼小激光
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_5359F0(Block, pArg2);  // 构造 CNEvilEyeSmallLOLLaser 邪眼小激光（构造参数包）
              break;
            case 30305:  // PO 30305 → 邪眼震地构造
              if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ 邪眼震地构造
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_61FAD0(Block, pArg2);  // 构造 邪眼震地构造（构造参数包）
              break;
            //   30310 CNTrackingIceWave(0x460) / 30311 CNThunderBolt(2) / 30312 CNTemporaryHit …
            case 30310:  // PO 30310 → CNTrackingIceWave 追踪冰波
              if ( operator new(0x460u) == nullptr )  // 申请 1120 字节（0x460）→ CNTrackingIceWave 追踪冰波
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_530E30(Block, pArg2);  // 构造 CNTrackingIceWave 追踪冰波（构造参数包）
              break;
            case 30311:  // PO 30311 → CNThunderBolt 雷电
              if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNThunderBolt 雷电
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_52F4D0(Block, pArg2, 2);  // 构造 CNThunderBolt 雷电(pArg2, 2)
              break;
            case 30312:  // PO 30312 → CNTemporaryHit 临时命中
              if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）→ CNTemporaryHit 临时命中
                return (uint32_t *)sub_530500(Block, pArg2);  // 返回 CNTemporaryHit 临时命中（构造参数包）
              return nullptr;  // 返回空指针（构造失败/未命中）
            //   30320 CNFireExplosion / 30321 → LABEL_506 CNRedRock / 30322 CNSummonMonsterWithEffect
            case 30320:  // PO 30320 → CNFireExplosion 火焰爆炸
              if ( operator new(0x3E4u) != nullptr )  // 申请 996 字节（0x3E4）→ CNFireExplosion 火焰爆炸
                return (uint32_t *)sub_52F2C0(Block, pArg2);  // 返回 CNFireExplosion 火焰爆炸（构造参数包）
              return nullptr;  // 返回空指针（构造失败/未命中）
            case 30321:  // PO 30321 与同组 ID 共用出口 LABEL_506
              if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNOlreksExplosiveOil 欧雷克爆油
                goto LABEL_506;  // 转到公共出口 LABEL_506
              return nullptr;  // 返回空指针（构造失败/未命中）
            case 30322:  // PO 30322 → CNOlreksExplosiveOil 欧雷克爆油
              if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNOlreksExplosiveOil 欧雷克爆油
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_53A1B0(Block, pArg2);  // 构造 CNOlreksExplosiveOil 欧雷克爆油（构造参数包）
              break;
            //   30323 CNCreateOnDestroyObject / 30350 CNBlastBlood…（0x3EC）/ 30351 …
            case 30323:  // PO 30323 → CNCreateOnDestroyObject 销毁生成物
              if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNCreateOnDestroyObject 销毁生成物
                return (uint32_t *)sub_530040(Block, pArg2);  // 返回 CNCreateOnDestroyObject 销毁生成物（构造参数包）
              return nullptr;  // 返回空指针（构造失败/未命中）
            case 30350:  // PO 30350 → CNPoisonBug 毒虫
              if ( operator new(0x3ECu) == nullptr )  // 申请 1004 字节（0x3EC）→ CNPoisonBug 毒虫
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_539520(Block, pArg2);  // 构造 CNPoisonBug 毒虫（构造参数包）
              break;
            case 30351:  // PO 30351 → CNAuxoRoot 定身根
              if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNAuxoRoot 定身根
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_539650(Block, pArg2);  // 构造 CNAuxoRoot 定身根（构造参数包）
              break;
            //   30360 CNSpecificEnemy…（强制 float 参数）/ 30361 CNFireExplosion / 30362-30364 同 40004-40008 段
            case 30360:  // PO 30360 → CNFireBallCommon 通用火球
              if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNFireBallCommon 通用火球
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_5397C0(Block, *(float *)&pArg2);  // 构造 CNFireBallCommon 通用火球(*(float *)&pArg2)
              break;
            case 30361:  // PO 30361 → CNFireExplosion 火焰爆炸
              if ( operator new(0x3E4u) != nullptr )  // 申请 996 字节（0x3E4）→ CNFireExplosion 火焰爆炸
                return (uint32_t *)sub_52F2C0(Block, pArg2);  // 返回 CNFireExplosion 火焰爆炸（构造参数包）
              return nullptr;  // 返回空指针（构造失败/未命中）
            case 30362:  // PO 30362 与同组 ID 共用出口 LABEL_568
              if ( operator new(0x3D8u) != nullptr )  // 申请 984 字节（0x3D8）对象
                goto LABEL_568;  // 转到公共出口 LABEL_568
              return nullptr;  // 返回空指针（构造失败/未命中）
            case 30363:  // PO 30363 与同组 ID 共用出口 LABEL_569
              goto LABEL_569;  // 转到公共出口 LABEL_569
            case 30364:  // PO 30364 与同组 ID 共用出口 LABEL_537
              if ( operator new(0x3E8u) != nullptr )  // 申请 1000 字节（0x3E8）对象
                goto LABEL_537;  // 转到公共出口 LABEL_537
              return nullptr;  // 返回空指针（构造失败/未命中）
            default:
              goto LABEL_494;  // 转到公共出口 LABEL_494
          }
          return result;  // 返回已构造对象
        }
        // ── [段 16] Block 处于 [30365, 30368] 的四值：全走 sub_52FA30=CNIceNiddle ──
        if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNIceNiddle 冰针
          return nullptr;  // 返回空指针（构造失败/未命中）
      }
      return (uint32_t *)sub_52FA30(Block, pArg2);  // 返回 CNIceNiddle 冰针（构造参数包）
    }
    // ── [段 17] Block 处于 (48008, 48043] 段：48043-48042 大段（弹药/激光/诅咒炸弹族） ──
    if ( Block <= 48043 )  // 按 PO ID 阈值 <= 48043 收窄分支
    {
      //   48043 sub_5390B0(2)… / 48009 CNCreateOnDestroyObject
      if ( Block == 48043 )  // 按 PO ID 阈值 == 48043 收窄分支
      {
        if ( operator new(0x3D8u) != nullptr )  // 申请 984 字节（0x3D8）→ CNCircleAppendageDISENCHANT 解魔光环
          return (uint32_t *)sub_5390B0(48043, pArg2, 2);  // 返回 CNCircleAppendageDISENCHANT 解魔光环(pArg2, 2)
        return nullptr;  // 返回空指针（构造失败/未命中）
      }
      switch ( Block )  // 按 PO ID 分派到具体构造
      {
        //   48010+48014 CNDollMasterBubble（人形师气泡）/ 48011+48033..48042 → LABEL_545 CNTemporaryHit 十一连
        case 48009:  // PO 48009 → CNSunkenRock 沉岩
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNSunkenRock 沉岩
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_5301D0(Block, pArg2);  // 返回 CNSunkenRock 沉岩（构造参数包）
        case 48010:  // PO 48010（无专属构造器）
        case 48014:  // PO 48014 → CNDollMasterBubble 傀儡师气泡
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNDollMasterBubble 傀儡师气泡
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_530350(Block, pArg2);  // 返回 CNDollMasterBubble 傀儡师气泡（构造参数包）
        case 48011:  // PO 48011（无专属构造器）
        case 48033:  // PO 48033（无专属构造器）
        case 48034:  // PO 48034（无专属构造器）
        case 48035:  // PO 48035（无专属构造器）
        case 48036:  // PO 48036（无专属构造器）
        case 48037:  // PO 48037（无专属构造器）
        case 48038:  // PO 48038（无专属构造器）
        case 48039:  // PO 48039（无专属构造器）
        case 48040:  // PO 48040（无专属构造器）
        case 48041:  // PO 48041（无专属构造器）
        case 48042:  // PO 48042 与同组 ID 共用出口 LABEL_545
          goto LABEL_545;  // 转到公共出口 LABEL_545
        //   48012 CNMagicTargetWarning（0x444）/ 48013 CNForceField / 48015 CNCircleAppendageMaker
        case 48012:  // PO 48012 → CNMagicTargetWarning 魔法目标警示
          if ( operator new(0x444u) == nullptr )  // 申请 1092 字节（0x444）→ CNMagicTargetWarning 魔法目标警示
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_530430(Block, pArg2);  // 返回 CNMagicTargetWarning 魔法目标警示（构造参数包）
        case 48013:  // PO 48013 → CNForceField 力场
          if ( operator new(0x3FCu) == nullptr )  // 申请 1020 字节（0x3FC）→ CNForceField 力场
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_5305E0(Block, pArg2);  // 返回 CNForceField 力场（构造参数包）
        case 48015:  // PO 48015 → CNCircleAppendageMaker 光环生成器
          if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNCircleAppendageMaker 光环生成器
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_530710(Block, pArg2, 0);  // 返回 CNCircleAppendageMaker 光环生成器(pArg2, 0)
        //   48016 sub_538D90(1) / 48017 sub_538F70(1) / 48018 sub_538EB0(1)（三型带标志 1）
        case 48016:  // PO 48016 → CNCircleAppendageENCHANTWEAPON 附魔武器光环
          if ( operator new(0x3E4u) == nullptr )  // 申请 996 字节（0x3E4）→ CNCircleAppendageENCHANTWEAPON 附魔武器光环
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_538D90(Block, pArg2, 1);  // 返回 CNCircleAppendageENCHANTWEAPON 附魔武器光环(pArg2, 1)
        case 48017:  // PO 48017 → CNCircleAppendageCHANGESTATE 状态光环
          if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNCircleAppendageCHANGESTATE 状态光环
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_538F70(Block, pArg2, 1);  // 返回 CNCircleAppendageCHANGESTATE 状态光环(pArg2, 1)
        case 48018:  // PO 48018 → CNCircleAppendageCHANGE_WEAPON_ELEMENT 武器属性光环
          if ( operator new(0x3E4u) == nullptr )  // 申请 996 字节（0x3E4）→ CNCircleAppendageCHANGE_WEAPON_ELEMENT 武器属性光环
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_538EB0(Block, pArg2, 1);  // 返回 CNCircleAppendageCHANGE_WEAPON_ELEMENT 武器属性光环(pArg2, 1)
        //   48019-48023 CNDangerousGas(1..5) 五连（同一构造不同档）/ 48024 CNSummonMonsterWithEffect
        case 48019:  // PO 48019 → CNDangerousGas 毒气
          if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNDangerousGas 毒气
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_52F860(Block, pArg2, 1);  // 返回 CNDangerousGas 毒气(pArg2, 1)
        case 48020:  // PO 48020 → CNDangerousGas 毒气
          if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNDangerousGas 毒气
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_52F860(Block, pArg2, 2);  // 返回 CNDangerousGas 毒气(pArg2, 2)
        case 48021:  // PO 48021 → CNDangerousGas 毒气
          if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNDangerousGas 毒气
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_52F860(Block, pArg2, 3);  // 返回 CNDangerousGas 毒气(pArg2, 3)
        case 48022:  // PO 48022 → CNDangerousGas 毒气
          if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNDangerousGas 毒气
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_52F860(Block, pArg2, 4);  // 返回 CNDangerousGas 毒气(pArg2, 4)
        case 48023:  // PO 48023 与同组 ID 共用出口 LABEL_556
          if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNSummonMonsterWithEffect 带特效召唤
            return nullptr;  // 返回空指针（构造失败/未命中）
          goto LABEL_556;  // 转到公共出口 LABEL_556
        case 48024:  // PO 48024 → CNSummonMonsterWithEffect 带特效召唤
          if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNSummonMonsterWithEffect 带特效召唤
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_530C40(Block, pArg2);  // 返回 CNSummonMonsterWithEffect 带特效召唤（构造参数包）
        //   48025 同 48023（第 5 档）/ 48026 sub_539480 / 48027 sub_5393E0 / 48028 → LABEL_563 CNBodyHit
        case 48025:  // PO 48025 → CNDangerousGas 毒气
          if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNDangerousGas 毒气
            return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_556:
          result = (uint32_t *)sub_52F860(Block, pArg2, 5);  // 构造 CNDangerousGas 毒气(pArg2, 5)
          break;
        case 48026:  // PO 48026 → CNEPLPCampFire 营火
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNEPLPCampFire 营火
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_539480(Block, pArg2);  // 构造 CNEPLPCampFire 营火（构造参数包）
          break;
        case 48027:  // PO 48027 → CNStorageSub 仓库子体
          if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNStorageSub 仓库子体
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_5393E0(Block, pArg2);  // 构造 CNStorageSub 仓库子体（构造参数包）
          break;
        case 48028:  // PO 48028 → CNBodyHit 体碰
LABEL_563:
          if ( operator new(0x3F4u) == nullptr )  // 申请 1012 字节（0x3F4）→ CNBodyHit 体碰
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_530D50(Block, pArg2);  // 构造 CNBodyHit 体碰（构造参数包）
          break;
        //   48029 CNLOLLaser / 48030 → LABEL_568 CNShootingStar / 48031 → LABEL_569 CNShootingStarExp(0) / 48032 CNIceWaveUp
        case 48029:  // PO 48029 → CNLOLLaser 洛尔激光
          if ( operator new(0x3D8u) != nullptr )  // 申请 984 字节（0x3D8）→ CNLOLLaser 洛尔激光
            return (uint32_t *)sub_534B20(Block, pArg2);  // 返回 CNLOLLaser 洛尔激光（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 48030:  // PO 48030 → CNShootingStar 流星
          if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNShootingStar 流星
            return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_568:
          result = (uint32_t *)sub_52FBC0(Block, pArg2);  // 构造 CNShootingStar 流星（构造参数包）
          break;
        case 48031:  // PO 48031 → CNShootingStarExp 流星爆
LABEL_569:
          if ( operator new(0x3E8u) == nullptr )  // 申请 1000 字节（0x3E8）→ CNShootingStarExp 流星爆
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_52FCA0(Block, pArg2, 0);  // 构造 CNShootingStarExp 流星爆(pArg2, 0)
          break;
        case 48032:  // PO 48032 → CNIceWaveUp 上向冰波
          if ( operator new(0x3D0u) != nullptr )  // 申请 976 字节（0x3D0）→ CNIceWaveUp 上向冰波
            return (uint32_t *)sub_534C60(Block, pArg2);  // 返回 CNIceWaveUp 上向冰波（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        default:
          goto LABEL_494;  // 转到公共出口 LABEL_494
      }
      return result;  // 返回已构造对象
    }
    // ── [段 18] Block > 50704 区：50000-51201 段（地图传送门/Gate 与飞行弹体） ──
    if ( Block > 50704 )  // 按 PO ID 阈值 > 50704 收窄分支
    {
      if ( Block > 50950 )  // 按 PO ID 阈值 > 50950 收窄分支
      {
        switch ( Block )  // 按 PO ID 分派到具体构造
        {
          //   51000 sub_610960(51100) 转派（诅咒炸弹 CNCurseBomb）/ 51100 CNCurseBombSub / 51200+51201 CNZepplinBullet 两型
          case 51000:  // PO 51000 → CNCurseBomb 诅咒弹
            if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNCurseBomb 诅咒弹
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_610960(Block, 51100);  // 构造 CNCurseBomb 诅咒弹(51100)
            break;
          case 51100:  // PO 51100 → CNCurseBombSub 诅咒弹子体
            if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNCurseBombSub 诅咒弹子体
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_530B50(Block, pArg2);  // 构造 CNCurseBombSub 诅咒弹子体（构造参数包）
            break;
          case 51200:  // PO 51200 → CNStorageBird 仓储鸟
            if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNStorageBird 仓储鸟
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_539220(Block, pArg2);  // 构造 CNStorageBird 仓储鸟（构造参数包）
            break;
          case 51201:  // PO 51201 → CNFallingStorage 落箱
            if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNFallingStorage 落箱
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_539300(Block, pArg2);  // 构造 CNFallingStorage 落箱（构造参数包）
            break;
          default:
            goto LABEL_494;  // 转到公共出口 LABEL_494
        }
      }
      else
      {
        //   50950 CNToothKurokuta / 50750-50754 sub_5362F0 五连 / 50800-50805 → LABEL_629 sub_52FD90
        if ( Block == 50950 )  // 按 PO ID 阈值 == 50950 收窄分支
        {
          if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）→ CNToothKurokuta 巨齿
            return (uint32_t *)sub_530A60(50950, pArg2);  // 返回 CNToothKurokuta 巨齿（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        }
        switch ( Block )  // 按 PO ID 分派到具体构造
        {
          case 50750:  // PO 50750（无专属构造器）
          case 50751:  // PO 50751（无专属构造器）
          case 50752:  // PO 50752（无专属构造器）
          case 50753:  // PO 50753（无专属构造器）
          case 50754:  // PO 50754 → CNExplosiveOil 爆炸油
            if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNExplosiveOil 爆炸油
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_5362F0(Block, pArg2);  // 构造 CNExplosiveOil 爆炸油（构造参数包）
            break;
          case 50800:  // PO 50800（无专属构造器）
          case 50801:  // PO 50801（无专属构造器）
          case 50802:  // PO 50802（无专属构造器）
          case 50803:  // PO 50803（无专属构造器）
          case 50804:  // PO 50804（无专属构造器）
          case 50805:  // PO 50805 → CNThrowItemDestroyable 可破坏投掷物
            if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNThrowItemDestroyable 可破坏投掷物
              return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_629:
            result = (uint32_t *)sub_52FD90(Block, pArg2);  // 构造 CNThrowItemDestroyable 可破坏投掷物（构造参数包）
            break;
          //   50806-50810 sub_530010 五连 / 50900 CNToothSFish
          case 50806:  // PO 50806（无专属构造器）
          case 50807:  // PO 50807（无专属构造器）
          case 50808:  // PO 50808（无专属构造器）
          case 50809:  // PO 50809（无专属构造器）
          case 50810:  // PO 50810 → 补漏小构造
            if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ 补漏小构造
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_530010(Block, pArg2);  // 构造 补漏小构造（构造参数包）
            break;
          case 50900:  // PO 50900 → CNToothSFish 锯齿鱼
            if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNToothSFish 锯齿鱼
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_530970(Block, pArg2);  // 构造 CNToothSFish 锯齿鱼（构造参数包）
            break;
          default:
            goto LABEL_494;  // 转到公共出口 LABEL_494
        }
      }
      return result;  // 返回已构造对象
    }
    //   50700-50704 CNCreateOnDestroyObject
    if ( Block >= 50700 )  // 按 PO ID 阈值 >= 50700 收窄分支
    {
      if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNCreateOnDestroyObject 销毁生成物
        return (uint32_t *)sub_530040(Block, pArg2);  // 返回 CNCreateOnDestroyObject 销毁生成物（构造参数包）
      return nullptr;  // 返回空指针（构造失败/未命中）
    }
    // ── [段 19] Block 处于 (50404, 50700)：50500-50605 段 ──
    //   50500-50503 → LABEL_629 sub_52FD90=CNThrowItemDestroyable / 50580-50605（含 50590 → LABEL_346 sub_530130）
    if ( Block > 50404 )  // 按 PO ID 阈值 > 50404 收窄分支
    {
      switch ( Block )  // 按 PO ID 分派到具体构造
      {
        case 50500:  // PO 50500（无专属构造器）
        case 50501:  // PO 50501（无专属构造器）
        case 50502:  // PO 50502（无专属构造器）
        case 50503:  // PO 50503 与同组 ID 共用出口 LABEL_629
          if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）→ CNCreateOnDestroyObject 销毁生成物
            goto LABEL_629;  // 转到公共出口 LABEL_629
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 50580:  // PO 50580（无专属构造器）
        case 50581:  // PO 50581 → CNCreateOnDestroyObject 销毁生成物
          if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNCreateOnDestroyObject 销毁生成物
            return (uint32_t *)sub_530040(Block, pArg2);  // 返回 CNCreateOnDestroyObject 销毁生成物（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        case 50590:  // PO 50590 → CNFlyBombSub 飞行炸弹子体
          if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNFlyBombSub 飞行炸弹子体
            return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_346:
          result = (uint32_t *)sub_530130(Block, pArg2);  // 构造 CNFlyBombSub 飞行炸弹子体（构造参数包）
          break;
        case 50600:  // PO 50600（无专属构造器）
        case 50601:  // PO 50601（无专属构造器）
        case 50602:  // PO 50602（无专属构造器）
        case 50603:  // PO 50603（无专属构造器）
        case 50604:  // PO 50604（无专属构造器）
        case 50605:  // PO 50605 与同组 ID 共用出口 LABEL_629
          if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）对象
            goto LABEL_629;  // 转到公共出口 LABEL_629
          return nullptr;  // 返回空指针（构造失败/未命中）
        default:
          goto LABEL_494;  // 转到公共出口 LABEL_494
      }
      return result;  // 返回已构造对象
    }
    //   50400-50403 sub_52FF20=CNBouncer（弹跳球体）
    if ( Block >= 50400 )  // 按 PO ID 阈值 >= 50400 收窄分支
    {
      if ( operator new(0x3D8u) != nullptr )  // 申请 984 字节（0x3D8）→ CNBouncer 弹跳物
        return (uint32_t *)sub_52FF20(Block, pArg2);  // 返回 CNBouncer 弹跳物（构造参数包）
      return nullptr;  // 返回空指针（构造失败/未命中）
    }
    // ── [段 20] Block 处于 [50001, 50404)：50001-50104 段 ──
    //   50001-50004 → LABEL_370 sub_530800 / 50100-50104 CNKagelBomb(Block+100)
    if ( Block <= 50204 )  // 按 PO ID 阈值 <= 50204 收窄分支
    {
      if ( Block >= 50200 )  // 按 PO ID 阈值 >= 50200 收窄分支
      {
        if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNKagelBombSub 卡格尔炸弹子体
          return (uint32_t *)sub_5348A0(Block, pArg2);  // 返回 CNKagelBombSub 卡格尔炸弹子体（构造参数包）
        return nullptr;  // 返回空指针（构造失败/未命中）
      }
      switch ( Block )  // 按 PO ID 分派到具体构造
      {
        case 50001:  // PO 50001（无专属构造器）
        case 50002:  // PO 50002（无专属构造器）
        case 50003:  // PO 50003（无专属构造器）
        case 50004:  // PO 50004 → 补漏小构造
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ 补漏小构造
            return nullptr;  // 返回空指针（构造失败/未命中）
LABEL_370:
          result = (uint32_t *)sub_530800(Block, pArg2);  // 构造 补漏小构造（构造参数包）
          break;
        case 50100:  // PO 50100（无专属构造器）
        case 50101:  // PO 50101（无专属构造器）
        case 50102:  // PO 50102（无专属构造器）
        case 50103:  // PO 50103（无专属构造器）
        case 50104:  // PO 50104 → CNKagelBomb 卡格尔炸弹
          if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNKagelBomb 卡格尔炸弹
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_534840(Block, Block + 100);  // 构造 CNKagelBomb 卡格尔炸弹(Block + 100)
          break;
        default:
          goto LABEL_494;  // 转到公共出口 LABEL_494
      }
      return result;  // 返回已构造对象
    }
    //   50200-50204 CNKagelBombSub / 50300-50305 sub_52FE30 六连
    if ( Block >= 50300 && Block <= 50305 )  // PO ID 落在 [50300>=, 50305<=] 区间
    {
      if ( operator new(0x3D8u) != nullptr )  // 申请 984 字节（0x3D8）→ 补漏小构造
        return (uint32_t *)sub_52FE30(Block, pArg2);  // 返回 补漏小构造（构造参数包）
      return nullptr;  // 返回空指针（构造失败/未命中）
    }
// ── [段 21] ★ LABEL_494 通用兜底：未知 ID 一律 new(972=0x3CC) + sub_52EA60(CNRDTrap 底座) ──
//   随后覆盖虚表为 CNRDPooledPassiveObject::vftable（对象池版），返回对象（永不 nullptr，除非内存不足）
LABEL_494:
    v4 = (uint32_t *)sub_52E320(972);  // 构造 对象池借出（172 字节 PO 底座）
    v5 = v4;  // 保留底座指针
    if ( v4 != nullptr )  // 池化底座非空
    {
      sub_52EA60(v4, Block, (int)pArg2);  // CNRDTrap 基座构造（挂 PO ID / 参数包）
      *v5 = &CNRDPooledPassiveObject::`vftable';  // 挂虚表 CNRDPooledPassiveObject
      return v5;
    }
    return nullptr;  // 返回空指针（构造失败/未命中）
  }
  // ── [段 22] Block == 23007：CNMagicMissile（魔法飞弹）—— >23007 段的唯一小值 ──
  if ( Block == 23007 )  // 按 PO ID 阈值 == 23007 收窄分支
  {
    if ( operator new(0x3D4u) != nullptr )  // 申请 980 字节（0x3D4）→ CNMagicMissile 魔法飞弹
      return (uint32_t *)sub_533220(23007, pArg2);  // 返回 CNMagicMissile 魔法飞弹（构造参数包）
    return nullptr;  // 返回空指针（构造失败/未命中）
  }
  // ── [段 23] Block 处于 (1041, 23007)：20001-23006 段（召唤/格斗/枪手大型 PO） ──
  if ( Block > 1041 )  // 按 PO ID 阈值 > 1041 收窄分支
  {
    if ( Block <= 2002 )  // 按 PO ID 阈值 <= 2002 收窄分支
    {
      // ── [段 24] Block < 2000：1042-1056 段（鬼剑士/格斗家技能弹体，0x3D0-0x478 大对象） ──
      //   1042 sub_537400 / 1043 sub_5374E0 / 1044 CNGhost / 1045 sub_5375C0 / 1046 sub_5376C0 / 1047 sub_537730
      if ( Block < 2000 )  // 按 PO ID 阈值 < 2000 收窄分支
      {
        switch ( Block )  // 按 PO ID 分派到具体构造
        {
          case 1042:  // PO 1042 → CNDragonHeadSideNentan 侧龙头年弹
LABEL_136:
            if ( operator new(0x460u) == nullptr )  // 申请 1120 字节（0x460）→ CNDragonHeadSideNentan 侧龙头年弹
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_537400(Block, pArg2);  // 返回 CNDragonHeadSideNentan 侧龙头年弹（构造参数包）
          case 1043:  // PO 1043 → CNDragonHeadSideGas 侧龙头毒气
LABEL_138:
            if ( operator new(0x46Cu) == nullptr )  // 申请 1132 字节（0x46C）→ CNDragonHeadSideGas 侧龙头毒气
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_5374E0(Block, pArg2);  // 返回 CNDragonHeadSideGas 侧龙头毒气（构造参数包）
          case 1044:  // PO 1044 → CNDragonHeadSide 侧龙头
LABEL_134:
            if ( operator new(0x458u) == nullptr )  // 申请 1112 字节（0x458）→ CNDragonHeadSide 侧龙头
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_5371E0(Block, pArg2);  // 返回 CNDragonHeadSide 侧龙头（构造参数包）
          case 1045:  // PO 1045 → CNDragonHeadFrontFlame 正龙头火焰
            if ( operator new(0x46Cu) == nullptr )  // 申请 1132 字节（0x46C）→ CNDragonHeadFrontFlame 正龙头火焰
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_5375C0(Block, pArg2);  // 返回 CNDragonHeadFrontFlame 正龙头火焰（构造参数包）
          case 1046:  // PO 1046 → CNDragonHeadFrontNentan 正龙头年弹
            if ( operator new(0x464u) == nullptr )  // 申请 1124 字节（0x464）→ CNDragonHeadFrontNentan 正龙头年弹
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_5376C0(Block, pArg2);  // 返回 CNDragonHeadFrontNentan 正龙头年弹（构造参数包）
          case 1047:  // PO 1047 → CNDragonHeadFrontGas 正龙头毒气
            if ( operator new(0x46Cu) == nullptr )  // 申请 1132 字节（0x46C）→ CNDragonHeadFrontGas 正龙头毒气
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_537730(Block, pArg2);  // 返回 CNDragonHeadFrontGas 正龙头毒气（构造参数包）
          //   1049 → LABEL_132 sub_536430(2,3) / 1050-1051 双型 / 1053 sub_537A00 / 1054 → LABEL_16/17
          case 1049:  // PO 1049 → CNSwamp 沼泽
LABEL_132:
            if ( operator new(0x478u) == nullptr )  // 申请 1144 字节（0x478）→ CNSwamp 沼泽
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_536430(Block, pArg2, 2, 3);  // 返回 CNSwamp 沼泽(pArg2, 2, 3)
          case 1050:  // PO 1050 → CNEyeofObserver 观察者之眼
            if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNEyeofObserver 观察者之眼
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_537840(Block, pArg2);  // 返回 CNEyeofObserver 观察者之眼（构造参数包）
          case 1051:  // PO 1051 → CNActiveObserver 活动观察者
            if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNActiveObserver 活动观察者
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_537920(Block, pArg2);  // 返回 CNActiveObserver 活动观察者（构造参数包）
          case 1053:  // PO 1053 → CNLightBulb 灯泡
            if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNLightBulb 灯泡
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_537A00(Block, pArg2);  // 返回 CNLightBulb 灯泡（构造参数包）
          case 1054:  // PO 1054 → CN2StoryBox 双层箱
            if ( operator new(0x454u) == nullptr )  // 申请 1108 字节（0x454）→ CN2StoryBox 双层箱
              goto LABEL_16;  // 转到公共出口 LABEL_16
            result = (uint32_t *)sub_537FD0(Block, pArg2);  // 构造 CN2StoryBox 双层箱（构造参数包）
            goto LABEL_17;  // 转到公共出口 LABEL_17
          //   1055 sub_5380B0 / 1056 sub_536510(9,8)（大对象 0x478）
          case 1055:  // PO 1055 → CNGrenselosBunker 掩体
            if ( operator new(0x46Cu) == nullptr )  // 申请 1132 字节（0x46C）→ CNGrenselosBunker 掩体
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_5380B0(Block, pArg2);  // 返回 CNGrenselosBunker 掩体（构造参数包）
          case 1056:  // PO 1056 → CNMagmaSwamp 岩浆沼
            if ( operator new(0x478u) == nullptr )  // 申请 1144 字节（0x478）→ CNMagmaSwamp 岩浆沼
              return nullptr;  // 返回空指针（构造失败/未命中）
            return (uint32_t *)sub_536510(Block, pArg2, 9, 8);  // 返回 CNMagmaSwamp 岩浆沼(pArg2, 9, 8)
          default:
            goto LABEL_494;  // 转到公共出口 LABEL_494
        }
      }
// ── [段 25] LABEL_167：sub_5384F0（0x470 对象）—— 2001-2012 与 2010-2012 共用 ──
LABEL_167:
      if ( operator new(0x470u) != nullptr )  // 申请 1136 字节（0x470）→ CNHPFairy HP 精灵
        return (uint32_t *)sub_5384F0(Block, pArg2);  // 返回 CNHPFairy HP 精灵（构造参数包）
      return nullptr;  // 返回空指针（构造失败/未命中）
    }
    // ── [段 26] Block > 20013：21001-23006 段（召唤师/枪手/邪眼机关系） ──
    if ( Block > 20013 )  // 按 PO ID 阈值 > 20013 收窄分支
    {
      if ( Block > 21001 )  // 按 PO ID 阈值 > 21001 收窄分支
      {
        if ( Block > 22015 )  // 按 PO ID 阈值 > 22015 收窄分支
        {
          if ( Block > 22210 )  // 按 PO ID 阈值 > 22210 收窄分支
          {
            switch ( Block )  // 按 PO ID 分派到具体构造
            {
              // ── [段 27] 23001-23006：CNDecoy 替身族 —— 23001 单型、23002-23006 走 sub_533130(4/0/1/2/3) 六档 ──
              case 23001:  // PO 23001 → CNDecoy 诱饵
                if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNDecoy 诱饵
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_533050(Block, pArg2);  // 构造 CNDecoy 诱饵（构造参数包）
                break;
              case 23002:  // PO 23002 → CNChaser 追踪者
                if ( operator new(0x418u) == nullptr )  // 申请 1048 字节（0x418）→ CNChaser 追踪者
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_533130(Block, pArg2, 4);  // 构造 CNChaser 追踪者(pArg2, 4)
                break;
              case 23003:  // PO 23003 → CNChaser 追踪者
                if ( operator new(0x418u) == nullptr )  // 申请 1048 字节（0x418）→ CNChaser 追踪者
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_533130(Block, pArg2, 0);  // 构造 CNChaser 追踪者(pArg2, 0)
                break;
              case 23004:  // PO 23004 → CNChaser 追踪者
                if ( operator new(0x418u) == nullptr )  // 申请 1048 字节（0x418）→ CNChaser 追踪者
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_533130(Block, pArg2, 1);  // 构造 CNChaser 追踪者(pArg2, 1)
                break;
              case 23005:  // PO 23005 → CNChaser 追踪者
                if ( operator new(0x418u) == nullptr )  // 申请 1048 字节（0x418）→ CNChaser 追踪者
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_533130(Block, pArg2, 2);  // 构造 CNChaser 追踪者(pArg2, 2)
                break;
              case 23006:  // PO 23006 → CNChaser 追踪者
                if ( operator new(0x418u) == nullptr )  // 申请 1048 字节（0x418）→ CNChaser 追踪者
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_533130(Block, pArg2, 3);  // 构造 CNChaser 追踪者(pArg2, 3)
                break;
              default:
                goto LABEL_494;  // 转到公共出口 LABEL_494
            }
          }
          else
          {
            // ── [段 28] 22210+22200-22209 段：CNFireExplosion(22210) / sub_532330(5 连) / sub_532AC0(2) / sub_532BA0
            if ( Block == 22210 )  // 按 PO ID 阈值 == 22210 收窄分支
            {
              if ( operator new(0x3E4u) != nullptr )  // 申请 996 字节（0x3E4）→ CNFireExplosion 火焰爆炸
                return (uint32_t *)sub_52F2C0(22210, pArg2);  // 返回 CNFireExplosion 火焰爆炸（构造参数包）
              return nullptr;  // 返回空指针（构造失败/未命中）
            }
            switch ( Block )  // 按 PO ID 分派到具体构造
            {
              case 22016:  // PO 22016 → CNExsViperBullet 毒蛇弹
                if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNExsViperBullet 毒蛇弹
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_532440(Block, pArg2);  // 构造 CNExsViperBullet 毒蛇弹（构造参数包）
                break;
              case 22017:  // PO 22017 → CNGunnerLaser 枪手激光
                if ( operator new(0x3E0u) == nullptr )  // 申请 992 字节（0x3E0）→ CNGunnerLaser 枪手激光
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_5326C0(Block, pArg2);  // 构造 CNGunnerLaser 枪手激光（构造参数包）
                break;
              case 22200:  // PO 22200（无专属构造器）
              case 22201:  // PO 22201（无专属构造器）
              case 22202:  // PO 22202（无专属构造器）
              case 22203:  // PO 22203（无专属构造器）
              case 22204:  // PO 22204 → 惰性初始化表
                if ( sub_52E440(1012) == 0 )  // 若对象池不可用（惰性初始化表=0）
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_532330(Block, pArg2);  // 构造 CNGunnerSubWeaponBullet 副武器子弹（构造参数包）
                break;
              case 22205:  // PO 22205（无专属构造器）
              case 22206:  // PO 22206 → CNDropBomb 落弹
                if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNDropBomb 落弹
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_532AC0(Block, pArg2);  // 构造 CNDropBomb 落弹（构造参数包）
                break;
              case 22207:  // PO 22207 → CNTreadShootSub 履带射击子体
                if ( operator new(0x3ECu) == nullptr )  // 申请 1004 字节（0x3EC）→ CNTreadShootSub 履带射击子体
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_532BA0(Block, pArg2);  // 构造 CNTreadShootSub 履带射击子体（构造参数包）
                break;
              case 22208:  // PO 22208 与同组 ID 共用出口 LABEL_519
                goto LABEL_519;  // 转到公共出口 LABEL_519
              //   22208 → LABEL_519 CNFireExplosion / 22209 CNNapalmBomb(0x42C)
              case 22209:  // PO 22209 → CNNapalmBomb 凝固汽油弹
                if ( operator new(0x42Cu) == nullptr )  // 申请 1068 字节（0x42C）→ CNNapalmBomb 凝固汽油弹
                  return nullptr;  // 返回空指针（构造失败/未命中）
                result = (uint32_t *)sub_5343B0(Block, pArg2);  // 构造 CNNapalmBomb 凝固汽油弹（构造参数包）
                break;
              default:
                goto LABEL_494;  // 转到公共出口 LABEL_494
            }
          }
        }
        else
        {
          // ── [段 29] 22001-22016 段：CNGunnerBullet（22001-22015 经惰性表 sub_52E3B0(1040) 门）… / 22016 CNExsViperBullet
          if ( Block >= 22001 )  // 按 PO ID 阈值 >= 22001 收窄分支
          {
            if ( sub_52E3B0(1040) != 0 )  // 若对象池可用（对象池归还≠0）
              return (uint32_t *)sub_532250(Block, pArg2);  // 返回 CNGunnerBullet 枪手子弹（构造参数包）
            return nullptr;  // 返回空指针（构造失败/未命中）
          }
          //   21002-21015 段：CNEnergyBall(21002 吃 float)/CNEnergyBallSub/CNThrowSand/CNRoarStun/CNEnergyField…
          switch ( Block )  // 按 PO ID 分派到具体构造
          {
            case 21002:  // PO 21002 → CNEnergyBall 能量球
              if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNEnergyBall 能量球
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_5315E0(Block, *(float *)&pArg2);  // 构造 CNEnergyBall 能量球(*(float *)&pArg2)
              break;
            case 21003:  // PO 21003 → CNEnergyBallSub 能量球子体
              if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNEnergyBallSub 能量球子体
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_5316C0(Block, pArg2);  // 构造 CNEnergyBallSub 能量球子体（构造参数包）
              break;
            case 21004:  // PO 21004 → CNThrowSand 扬沙
              if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNThrowSand 扬沙
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_531810(Block, pArg2);  // 构造 CNThrowSand 扬沙（构造参数包）
              break;
            case 21005:  // PO 21005 → CNRoarStun 咆哮眩晕
              if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNRoarStun 咆哮眩晕
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_5318F0(Block, pArg2);  // 构造 CNRoarStun 咆哮眩晕（构造参数包）
              break;
            case 21006:  // PO 21006 → CNEnergyField 能量场
              if ( operator new(0x3E4u) == nullptr )  // 申请 996 字节（0x3E4）→ CNEnergyField 能量场
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_531A80(Block, pArg2);  // 构造 CNEnergyField 能量场（构造参数包）
              break;
            case 21007:  // PO 21007 → CNSpiralNen 螺旋念气
              if ( operator new(0x3ECu) == nullptr )  // 申请 1004 字节（0x3EC）→ CNSpiralNen 螺旋念气
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_532010(Block, pArg2);  // 构造 CNSpiralNen 螺旋念气（构造参数包）
              break;
            //   21008 → LABEL_229 sub_531500=CNSuplexSub；21010/21011 走 float 参数构造
            case 21008:  // PO 21008 与同组 ID 共用出口 LABEL_229
              goto LABEL_229;  // 转到公共出口 LABEL_229
            case 21009:  // PO 21009 → CNClosePunchSub 近拳子体
              if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNClosePunchSub 近拳子体
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_532120(Block, pArg2);  // 构造 CNClosePunchSub 近拳子体（构造参数包）
              break;
            case 21010:  // PO 21010 → CNNenGuard 念气护壁
              if ( operator new(0x3FCu) == nullptr )  // 申请 1020 字节（0x3FC）→ CNNenGuard 念气护壁
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_532760(Block, *(float *)&pArg2);  // 构造 CNNenGuard 念气护壁(*(float *)&pArg2)
              break;
            case 21011:  // PO 21011 → CNThunderBolt 雷电
              if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNThunderBolt 雷电
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_52F4D0(Block, pArg2, 1);  // 构造 CNThunderBolt 雷电(pArg2, 1)
              break;
            case 21014:  // PO 21014 → CNFireExplosion 火焰爆炸
              if ( operator new(0x3E4u) != nullptr )  // 申请 996 字节（0x3E4）→ CNFireExplosion 火焰爆炸
                return (uint32_t *)sub_52F2C0(Block, pArg2);  // 返回 CNFireExplosion 火焰爆炸（构造参数包）
              return nullptr;  // 返回空指针（构造失败/未命中）
            case 21015:  // PO 21015 → CNThrowWeb 撒网
              if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNThrowWeb 撒网
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_5336C0(Block, pArg2);  // 构造 CNThrowWeb 撒网（构造参数包）
              break;
            default:
              goto LABEL_494;  // 转到公共出口 LABEL_494
          }
        }
      }
      else
      {
        // ── [段 30] 21001：LABEL_229 sub_531500=CNSuplexSub ──
        if ( Block == 21001 )  // 按 PO ID 阈值 == 21001 收窄分支
        {
LABEL_229:
          if ( operator new(0x3DCu) != nullptr )  // 申请 988 字节（0x3DC）→ CNSuplexSub 双向子体
            return (uint32_t *)sub_531500(Block, pArg2);  // 返回 CNSuplexSub 双向子体（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        }
        // ── [段 31] Block 处于 (20013, 21001)：20014-20019 六型 ──
        //   20014 CNTombStoneRain / 20015 CNTombStone / 20016+20019 走 float / 20017 CNGrabBlastBlood / 20018 WAVE_CANCLE
        switch ( Block )  // 按 PO ID 分派到具体构造
        {
          case 20014:  // PO 20014 → CNTombStoneRain 墓石雨
            if ( operator new(0x3E0u) == nullptr )  // 申请 992 字节（0x3E0）→ CNTombStoneRain 墓石雨
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_532900(Block, pArg2);  // 构造 CNTombStoneRain 墓石雨（构造参数包）
            break;
          case 20015:  // PO 20015 → CNTombStone 墓石
            if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNTombStone 墓石
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_5329E0(Block, pArg2);  // 构造 CNTombStone 墓石（构造参数包）
            break;
          case 20016:  // PO 20016 → CNAshenForkSub 灰叉子体
            if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNAshenForkSub 灰叉子体
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_532CD0(Block, *(float *)&pArg2);  // 构造 CNAshenForkSub 灰叉子体(*(float *)&pArg2)
            break;
          case 20017:  // PO 20017 → CNGrabBlastBlood 抓取血爆
            if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNGrabBlastBlood 抓取血爆
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_532DB0(Block, pArg2);  // 构造 CNGrabBlastBlood 抓取血爆（构造参数包）
            break;
          case 20018:  // PO 20018 → 波/机关取消（播 WAVE_CANCLE）
            if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ 波/机关取消（播 WAVE_CANCLE）
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_532E90(Block, pArg2);  // 构造 波/机关取消（播 WAVE_CANCLE）（构造参数包）
            break;
          case 20019:  // PO 20019 → CNGrandWave 大波
            if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNGrandWave 大波
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_532F70(Block, *(float *)&pArg2);  // 构造 CNGrandWave 大波(*(float *)&pArg2)
            break;
          default:
            goto LABEL_494;  // 转到公共出口 LABEL_494
        }
      }
      return result;  // 返回已构造对象
    }
    // ── [段 32] Block == 20013：sub_531DB0(41) = CNGhost(41)（鬼魂 PO，41 为分型） ──
    if ( Block == 20013 )  // 按 PO ID 阈值 == 20013 收窄分支
    {
      if ( operator new(0x41Cu) != nullptr )  // 申请 1052 字节（0x41C）→ CNGhost 幽灵
        return (uint32_t *)sub_531DB0(20013, pArg2, 41);  // 返回 CNGhost 幽灵(pArg2, 41)
      return nullptr;  // 返回空指针（构造失败/未命中）
    }
    // ── [段 33] Block 处于 (4202, 20013)：4613 以上/4610/4412/4410 四层阈值分派 ──
    if ( Block > 4202 )  // 按 PO ID 阈值 > 4202 收窄分支
    {
      if ( Block > 4613 )  // 按 PO ID 阈值 > 4613 收窄分支
      {
        // ── [段 34] 20001-20012 段：20001 WAVE_CREATE 音效型 / 20002-20007 CNIceWave(6 连，吃 float) ──
        //   20008 CNFireWave / 20009 CNBlastBlood / 20010 CNBlastBloodSub / 20011 CNGhost(25) / 20012 CNGhost(36)
        switch ( Block )  // 按 PO ID 分派到具体构造
        {
          case 20001:  // PO 20001 → 机关/技能 PO 触发（播 WAVE_CREATE）
            if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ 机关/技能 PO 触发（播 WAVE_CREATE）
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_5312C0(Block, pArg2);  // 构造 机关/技能 PO 触发（播 WAVE_CREATE）（构造参数包）
            break;
          case 20002:  // PO 20002（无专属构造器）
          case 20003:  // PO 20003（无专属构造器）
          case 20004:  // PO 20004（无专属构造器）
          case 20005:  // PO 20005（无专属构造器）
          case 20006:  // PO 20006（无专属构造器）
          case 20007:  // PO 20007 → CNIceWave 冰波
            if ( operator new(0x3E0u) == nullptr )  // 申请 992 字节（0x3E0）→ CNIceWave 冰波
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_531420(Block, *(float *)&pArg2);  // 构造 CNIceWave 冰波(*(float *)&pArg2)
            break;
          case 20008:  // PO 20008 → CNFireWave 火波
            if ( operator new(0x3E8u) == nullptr )  // 申请 1000 字节（0x3E8）→ CNFireWave 火波
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_531F30(Block, pArg2);  // 构造 CNFireWave 火波（构造参数包）
            break;
          case 20009:  // PO 20009 → CNBlastBlood 血爆
            if ( operator new(0x3E8u) == nullptr )  // 申请 1000 字节（0x3E8）→ CNBlastBlood 血爆
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_531B90(Block, pArg2);  // 构造 CNBlastBlood 血爆（构造参数包）
            break;
          case 20010:  // PO 20010 → CNBlastBloodSub 血爆子体
            if ( operator new(0x3E0u) == nullptr )  // 申请 992 字节（0x3E0）→ CNBlastBloodSub 血爆子体
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_531CA0(Block, pArg2);  // 构造 CNBlastBloodSub 血爆子体（构造参数包）
            break;
          case 20011:  // PO 20011 → CNGhost 幽灵
            if ( operator new(0x41Cu) == nullptr )  // 申请 1052 字节（0x41C）→ CNGhost 幽灵
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_531DB0(Block, pArg2, 25);  // 构造 CNGhost 幽灵(pArg2, 25)
            break;
          case 20012:  // PO 20012 → CNGhost 幽灵
            if ( operator new(0x41Cu) == nullptr )  // 申请 1052 字节（0x41C）→ CNGhost 幽灵
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_531DB0(Block, pArg2, 36);  // 构造 CNGhost 幽灵(pArg2, 36)
            break;
          default:
            goto LABEL_494;  // 转到公共出口 LABEL_494
        }
        return result;  // 返回已构造对象
      }
      if ( Block < 4610 )  // 按 PO ID 阈值 < 4610 收窄分支
      {
        if ( Block > 4412 )  // 按 PO ID 阈值 > 4412 收窄分支
        {
          // ── [段 35] 4500-4602 九连 → LABEL_192 sub_5389C0（同一构造 9 个 ID） ──
          switch ( Block )  // 按 PO ID 分派到具体构造
          {
            case 4500:  // PO 4500（无专属构造器）
            case 4501:  // PO 4501（无专属构造器）
            case 4502:  // PO 4502（无专属构造器）
            case 4510:  // PO 4510（无专属构造器）
            case 4511:  // PO 4511（无专属构造器）
            case 4512:  // PO 4512（无专属构造器）
            case 4600:  // PO 4600（无专属构造器）
            case 4601:  // PO 4601（无专属构造器）
            case 4602:  // PO 4602 与同组 ID 共用出口 LABEL_192
              goto LABEL_192;  // 转到公共出口 LABEL_192
            default:
              goto LABEL_494;  // 转到公共出口 LABEL_494
          }
        }
        if ( Block < 4410 )  // 按 PO ID 阈值 < 4410 收窄分支
        {
          // ── [段 36] 4210-4402 九连：break 穿透（无专属构造，落到段 35 的 LABEL_192） ──
          switch ( Block )  // 按 PO ID 分派到具体构造
          {
            case 4210:  // PO 4210（无专属构造器）
            case 4211:  // PO 4211（无专属构造器）
            case 4212:  // PO 4212（无专属构造器）
            case 4300:  // PO 4300（无专属构造器）
            case 4301:  // PO 4301（无专属构造器）
            case 4302:  // PO 4302（无专属构造器）
            case 4310:  // PO 4310（无专属构造器）
            case 4311:  // PO 4311（无专属构造器）
            case 4312:  // PO 4312（无专属构造器）
            case 4400:  // PO 4400（无专属构造器）
            case 4401:  // PO 4401（无专属构造器）
            case 4402:  // PO 4402（无专属构造器）
              break;
            default:
              goto LABEL_494;  // 转到公共出口 LABEL_494
          }
        }
      }
    }
    else if ( Block < 4200 )  // 按 PO ID 阈值 < 4200 收窄分支
    {
      // ── [段 37] 2400-2412 → LABEL_176 sub_538910（0x470） ──
      if ( Block <= 2412 )  // 按 PO ID 阈值 <= 2412 收窄分支
      {
        if ( Block >= 2410 )  // 按 PO ID 阈值 >= 2410 收窄分支
        {
LABEL_176:
          if ( operator new(0x470u) != nullptr )  // 申请 1136 字节（0x470）→ CNInvinsibleFairy 无敌精灵
            return (uint32_t *)sub_538910(Block, pArg2);  // 返回 CNInvinsibleFairy 无敌精灵（构造参数包）
          return nullptr;  // 返回空指针（构造失败/未命中）
        }
        // ── [段 38] 2300-2312 sub_538700 / 2400-2402 → LABEL_176 ──
        if ( Block > 2212 )  // 按 PO ID 阈值 > 2212 收窄分支
        {
          switch ( Block )  // 按 PO ID 分派到具体构造
          {
            case 2300:  // PO 2300（无专属构造器）
            case 2301:  // PO 2301（无专属构造器）
            case 2302:  // PO 2302（无专属构造器）
            case 2310:  // PO 2310（无专属构造器）
            case 2311:  // PO 2311（无专属构造器）
            case 2312:  // PO 2312 → CNSuperArmorFairy 霸体精灵
              if ( operator new(0x470u) == nullptr )  // 申请 1136 字节（0x470）→ CNSuperArmorFairy 霸体精灵
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_538700(Block, pArg2);  // 构造 CNSuperArmorFairy 霸体精灵（构造参数包）
              break;
            case 2400:  // PO 2400（无专属构造器）
            case 2401:  // PO 2401（无专属构造器）
            case 2402:  // PO 2402 与同组 ID 共用出口 LABEL_176
              goto LABEL_176;  // 转到公共出口 LABEL_176
            default:
              goto LABEL_494;  // 转到公共出口 LABEL_494
          }
        }
        else
        {
          // ── [段 39] 2210-2212 → LABEL_171 sub_538650 ──
          if ( Block >= 2210 )  // 按 PO ID 阈值 >= 2210 收窄分支
          {
LABEL_171:
            if ( operator new(0x470u) != nullptr )  // 申请 1136 字节（0x470）→ CNHPMPFairy HP+MP 精灵
              return (uint32_t *)sub_538650(Block, pArg2);  // 返回 CNHPMPFairy HP+MP 精灵（构造参数包）
            return nullptr;  // 返回空指针（构造失败/未命中）
          }
          // ── [段 40] 2010-2012 → LABEL_167 / 2100-2112 sub_5385A0 / 2200-2202 → LABEL_171 ──
          switch ( Block )  // 按 PO ID 分派到具体构造
          {
            case 2010:  // PO 2010（无专属构造器）
            case 2011:  // PO 2011（无专属构造器）
            case 2012:  // PO 2012 与同组 ID 共用出口 LABEL_167
              goto LABEL_167;  // 转到公共出口 LABEL_167
            case 2100:  // PO 2100（无专属构造器）
            case 2101:  // PO 2101（无专属构造器）
            case 2102:  // PO 2102（无专属构造器）
            case 2110:  // PO 2110（无专属构造器）
            case 2111:  // PO 2111（无专属构造器）
            case 2112:  // PO 2112 → CNMPFairy MP 精灵
              if ( operator new(0x470u) == nullptr )  // 申请 1136 字节（0x470）→ CNMPFairy MP 精灵
                return nullptr;  // 返回空指针（构造失败/未命中）
              result = (uint32_t *)sub_5385A0(Block, pArg2);  // 构造 CNMPFairy MP 精灵（构造参数包）
              break;
            case 2200:  // PO 2200（无专属构造器）
            case 2201:  // PO 2201（无专属构造器）
            case 2202:  // PO 2202 与同组 ID 共用出口 LABEL_171
              goto LABEL_171;  // 转到公共出口 LABEL_171
            default:
              goto LABEL_494;  // 转到公共出口 LABEL_494
          }
        }
        return result;  // 返回已构造对象
      }
      // ── [段 41] 4010-4112 九连 → LABEL_192 ──
      if ( Block > 4002 )  // 按 PO ID 阈值 > 4002 收窄分支
      {
        switch ( Block )  // 按 PO ID 分派到具体构造
        {
          case 4010:  // PO 4010（无专属构造器）
          case 4011:  // PO 4011（无专属构造器）
          case 4012:  // PO 4012（无专属构造器）
          case 4100:  // PO 4100（无专属构造器）
          case 4101:  // PO 4101（无专属构造器）
          case 4102:  // PO 4102（无专属构造器）
          case 4110:  // PO 4110（无专属构造器）
          case 4111:  // PO 4111（无专属构造器）
          case 4112:  // PO 4112 与同组 ID 共用出口 LABEL_192
            goto LABEL_192;  // 转到公共出口 LABEL_192
          default:
            goto LABEL_494;  // 转到公共出口 LABEL_494
        }
      }
      // ── [段 42] 2500-2612 十二连：2500-2512 sub_538860 / 2600-2612 sub_5387B0 ──
      if ( Block < 4000 )  // 按 PO ID 阈值 < 4000 收窄分支
      {
        switch ( Block )  // 按 PO ID 分派到具体构造
        {
          case 2500:  // PO 2500（无专属构造器）
          case 2501:  // PO 2501（无专属构造器）
          case 2502:  // PO 2502（无专属构造器）
          case 2510:  // PO 2510（无专属构造器）
          case 2511:  // PO 2511（无专属构造器）
          case 2512:  // PO 2512 → CNBlessFairy 祝福精灵
            if ( operator new(0x470u) == nullptr )  // 申请 1136 字节（0x470）→ CNBlessFairy 祝福精灵
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_538860(Block, pArg2);  // 构造 CNBlessFairy 祝福精灵（构造参数包）
            break;
          case 2600:  // PO 2600（无专属构造器）
          case 2601:  // PO 2601（无专属构造器）
          case 2602:  // PO 2602（无专属构造器）
          case 2610:  // PO 2610（无专属构造器）
          case 2611:  // PO 2611（无专属构造器）
          case 2612:  // PO 2612 → CNHasteFairy 加速精灵
            if ( operator new(0x470u) == nullptr )  // 申请 1136 字节（0x470）→ CNHasteFairy 加速精灵
              return nullptr;  // 返回空指针（构造失败/未命中）
            result = (uint32_t *)sub_5387B0(Block, pArg2);  // 构造 CNHasteFairy 加速精灵（构造参数包）
            break;
          default:
            goto LABEL_494;  // 转到公共出口 LABEL_494
        }
        return result;  // 返回已构造对象
      }
    }
// ── [段 43] LABEL_192：sub_5389C0（0x3DC）—— 4210-4602 / 4010-4112 / 2500？多组合共用 ──
LABEL_192:
    if ( operator new(0x3DCu) != nullptr )  // 申请 988 字节（0x3DC）→ CNFairyFactory 精灵工厂
      return (uint32_t *)sub_5389C0(Block, pArg2);  // 返回 CNFairyFactory 精灵工厂（构造参数包）
    return nullptr;  // 返回空指针（构造失败/未命中）
  }
  // ── [段 44] Block == 1041：LABEL_127 sub_5372C0（0x46C） ──
  if ( Block == 1041 )  // 按 PO ID 阈值 == 1041 收窄分支
  {
LABEL_127:
    if ( operator new(0x46Cu) != nullptr )  // 申请 1132 字节（0x46C）→ CNDragonHeadSideFlame 侧龙头火焰
      return (uint32_t *)sub_5372C0(Block, pArg2);  // 返回 CNDragonHeadSideFlame 侧龙头火焰（构造参数包）
    return nullptr;  // 返回空指针（构造失败/未命中）
  }
  // ── [段 45] Block > 815：816-1040 段（大技能弹体，0x3CC-0x478） ──
  if ( Block > 815 )  // 按 PO ID 阈值 > 815 收窄分支
  {
    switch ( Block )  // 按 PO ID 分派到具体构造
    {
      //   816+831 CNUrn（罐）/ 817-819 三型（0x468-0x46C）
      case 816:  // PO 816（无专属构造器）
      case 831:  // PO 831 → CNBlueBallBox 蓝球箱
        if ( operator new(0x44Cu) == nullptr )  // 申请 1100 字节（0x44C）→ CNBlueBallBox 蓝球箱
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_52EF90(Block, pArg2);  // 返回 CNBlueBallBox 蓝球箱（构造参数包）
      case 817:  // PO 817 → CNFreezingLuna 冻结月
        if ( operator new(0x46Cu) == nullptr )  // 申请 1132 字节（0x46C）→ CNFreezingLuna 冻结月
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_537BC0(Block, pArg2);  // 返回 CNFreezingLuna 冻结月（构造参数包）
      case 818:  // PO 818 → CNSkeletonPile 骷髅堆
        if ( operator new(0x450u) == nullptr )  // 申请 1104 字节（0x450）→ CNSkeletonPile 骷髅堆
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_537E10(Block, pArg2);  // 返回 CNSkeletonPile 骷髅堆（构造参数包）
      case 819:  // PO 819 → CNSpiderSpawn 蜘蛛巢
        if ( operator new(0x468u) == nullptr )  // 申请 1128 字节（0x468）→ CNSpiderSpawn 蜘蛛巢
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_537EF0(Block, pArg2);  // 返回 CNSpiderSpawn 蜘蛛巢（构造参数包）
      //   820-823 → LABEL_125 sub_52EB00=CNRDPooledPassiveObject / 826+834-836+1021 → LABEL_73 sub_52ED60
      case 820:  // PO 820（无专属构造器）
      case 821:  // PO 821（无专属构造器）
      case 822:  // PO 822（无专属构造器）
      case 823:  // PO 823 与同组 ID 共用出口 LABEL_125
        goto LABEL_125;  // 转到公共出口 LABEL_125
      case 826:  // PO 826（无专属构造器）
      case 834:  // PO 834（无专属构造器）
      case 835:  // PO 835（无专属构造器）
      case 836:  // PO 836（无专属构造器）
      case 1021:  // PO 1021 → CNPassiveObject/CNMapObject 基座构造
LABEL_73:
        if ( operator new(0x44Cu) == nullptr )  // 申请 1100 字节（0x44C）→ CNPassiveObject/CNMapObject 基座构造
          goto LABEL_16;  // 转到公共出口 LABEL_16
        result = (uint32_t *)sub_52ED60(Block, pArg2);  // 构造 CNPassiveObject/CNMapObject 基座构造（构造参数包）
        goto LABEL_17;  // 转到公共出口 LABEL_17
      //   827-828 CNPathGate 传送门两型 / 830 → LABEL_63 sub_52EF60=CNTreasureBox 宝箱 / 832-833 CNEventBarrier 屏障两型
      case 827:  // PO 827（无专属构造器）
      case 828:  // PO 828 → CNUrn 瓮
        if ( operator new(0x44Cu) == nullptr )  // 申请 1100 字节（0x44C）→ CNUrn 瓮
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_52F040(Block, pArg2);  // 返回 CNUrn 瓮（构造参数包）
      case 830:  // PO 830 与同组 ID 共用出口 LABEL_63
        goto LABEL_63;  // 转到公共出口 LABEL_63
      case 832:  // PO 832 → CNEventBarrier 事件结界
        if ( operator new(0x478u) == nullptr )  // 申请 1144 字节（0x478）→ CNEventBarrier 事件结界
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_531190(Block, pArg2);  // 返回 CNEventBarrier 事件结界（构造参数包）
      case 833:  // PO 833 → CNEventBarrier 事件结界
        if ( operator new(0x478u) == nullptr )  // 申请 1144 字节（0x478）→ CNEventBarrier 事件结界
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_531190(Block, pArg2);  // 返回 CNEventBarrier 事件结界（构造参数包）
      //   1000 → sub_5361D0 / 1001-1005 CNUsableStackable… sub_538B90(0, Block-1001)
      case 1000:  // PO 1000 → CNSpaceFishLair 空鱼巢
        if ( operator new(0x468u) == nullptr )  // 申请 1128 字节（0x468）→ CNSpaceFishLair 空鱼巢
          goto LABEL_16;  // 转到公共出口 LABEL_16
        result = (uint32_t *)sub_5361D0(Block, pArg2);  // 构造 CNSpaceFishLair 空鱼巢（构造参数包）
        goto LABEL_17;  // 转到公共出口 LABEL_17
      case 1001:  // PO 1001（无专属构造器）
      case 1002:  // PO 1002（无专属构造器）
      case 1003:  // PO 1003（无专属构造器）
      case 1004:  // PO 1004（无专属构造器）
      case 1005:  // PO 1005 → CNSoundFloor 音板
        if ( operator new(0x454u) == nullptr )  // 申请 1108 字节（0x454）→ CNSoundFloor 音板
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_538B90(Block, 0, Block - 1001);  // 返回 CNSoundFloor 音板(0, Block - 1001)
      //   1006-1007 CNIceNiddle(CNIceWave) 两型 / 1008-1010 sub_536430(17,2) 三连 / 1011-1013 → LABEL_132
      case 1006:  // PO 1006（无专属构造器）
      case 1007:  // PO 1007 → CNHallucinationFlower 幻花
        if ( operator new(0x3E0u) == nullptr )  // 申请 992 字节（0x3E0）→ CNHallucinationFlower 幻花
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536350(Block, pArg2);  // 返回 CNHallucinationFlower 幻花（构造参数包）
      case 1008:  // PO 1008（无专属构造器）
      case 1009:  // PO 1009（无专属构造器）
      case 1010:  // PO 1010 → CNSwamp 沼泽
        if ( operator new(0x478u) == nullptr )  // 申请 1144 字节（0x478）→ CNSwamp 沼泽
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536430(Block, pArg2, 17, 2);  // 返回 CNSwamp 沼泽(pArg2, 17, 2)
      case 1011:  // PO 1011（无专属构造器）
      case 1012:  // PO 1012（无专属构造器）
      case 1013:  // PO 1013 与同组 ID 共用出口 LABEL_132
        goto LABEL_132;  // 转到公共出口 LABEL_132
      //   1014-1036 段：逐 ID 一构造（sub_536590…sub_5377A0）—— 密集区每 ID 5-12 行
      case 1014:  // PO 1014 → CNFloorNiddle 地刺
        if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNFloorNiddle 地刺
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536590(Block, pArg2);  // 返回 CNFloorNiddle 地刺（构造参数包）
      case 1015:  // PO 1015 → CNGoblinBunker 哥布林掩体
        if ( operator new(0x46Cu) == nullptr )  // 申请 1132 字节（0x46C）→ CNGoblinBunker 哥布林掩体
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536630(Block, pArg2);  // 返回 CNGoblinBunker 哥布林掩体（构造参数包）
      case 1016:  // PO 1016 → CNTwistFootHold 扭足台
        if ( operator new(0x3E8u) == nullptr )  // 申请 1000 字节（0x3E8）→ CNTwistFootHold 扭足台
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536770(Block, pArg2);  // 返回 CNTwistFootHold 扭足台（构造参数包）
      case 1017:  // PO 1017（无专属构造器）
      case 1018:  // PO 1018（无专属构造器）
      case 1019:  // PO 1019 → CNRollingStone 滚石
LABEL_121:
        if ( operator new(0x3F4u) == nullptr )  // 申请 1012 字节（0x3F4）→ CNRollingStone 滚石
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_535C50(Block, pArg2);  // 返回 CNRollingStone 滚石（构造参数包）
      case 1020:  // PO 1020 → CNWindShaker 风震
LABEL_123:
        if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNWindShaker 风震
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_535FC0(Block, pArg2);  // 返回 CNWindShaker 风震（构造参数包）
      case 1023:  // PO 1023 → CNEntangleVineTrigger 缠藤触发器
        if ( operator new(0x404u) == nullptr )  // 申请 1028 字节（0x404）→ CNEntangleVineTrigger 缠藤触发器
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536930(Block, pArg2);  // 返回 CNEntangleVineTrigger 缠藤触发器（构造参数包）
      case 1024:  // PO 1024 → CNStarfishEgg 海星卵
        if ( operator new(0x3ECu) == nullptr )  // 申请 1004 字节（0x3EC）→ CNStarfishEgg 海星卵
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536B40(Block, pArg2);  // 返回 CNStarfishEgg 海星卵（构造参数包）
      case 1025:  // PO 1025 → CNSweepingLegOfLotus 莲扫腿
        if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNSweepingLegOfLotus 莲扫腿
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536C30(Block, pArg2);  // 返回 CNSweepingLegOfLotus 莲扫腿（构造参数包）
      case 1026:  // PO 1026 → CNBellForZealots 狂徒钟
        if ( operator new(0x458u) == nullptr )  // 申请 1112 字节（0x458）→ CNBellForZealots 狂徒钟
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536D60(Block, pArg2);  // 返回 CNBellForZealots 狂徒钟（构造参数包）
      case 1027:  // PO 1027 → CNGravityChanger 重力变换
        if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNGravityChanger 重力变换
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536E00(Block, pArg2);  // 返回 CNGravityChanger 重力变换（构造参数包）
      case 1028:  // PO 1028 → CNDroppingRockTrigger 落石触发器
        if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNDroppingRockTrigger 落石触发器
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536EE0(Block, pArg2);  // 返回 CNDroppingRockTrigger 落石触发器（构造参数包）
      case 1029:  // PO 1029 → CNDroppingRock 落石
        if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNDroppingRock 落石
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536F80(Block, pArg2);  // 返回 CNDroppingRock 落石（构造参数包）
      case 1030:  // PO 1030 → CNEntangleVine 缠藤
        if ( operator new(0x3E4u) == nullptr )  // 申请 996 字节（0x3E4）→ CNEntangleVine 缠藤
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536A60(Block, pArg2);  // 返回 CNEntangleVine 缠藤（构造参数包）
      case 1031:  // PO 1031 → CNStarFishEggRequid 海星卵液
        if ( operator new(0x478u) == nullptr )  // 申请 1144 字节（0x478）→ CNStarFishEggRequid 海星卵液
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_5364E0(Block, pArg2);  // 返回 CNStarFishEggRequid 海星卵液（构造参数包）
      case 1032:  // PO 1032 → CNPassiveObjectTrigger 被动物触发器
        if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNPassiveObjectTrigger 被动物触发器
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536CC0(Block, pArg2);  // 返回 CNPassiveObjectTrigger 被动物触发器（构造参数包）
      case 1033:  // PO 1033 → CNFlappingBanner 飘旗
        if ( operator new(0x3DCu) == nullptr )  // 申请 988 字节（0x3DC）→ CNFlappingBanner 飘旗
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_537020(Block, pArg2);  // 返回 CNFlappingBanner 飘旗（构造参数包）
      case 1034:  // PO 1034 → CNPassiveObjectTrigger 被动物触发器
        if ( operator new(0x3D0u) == nullptr )  // 申请 976 字节（0x3D0）→ CNPassiveObjectTrigger 被动物触发器
          return nullptr;  // 返回空指针（构造失败/未命中）
        return (uint32_t *)sub_536CC0(Block, pArg2);  // 返回 CNPassiveObjectTrigger 被动物触发器（构造参数包）
      case 1035:  // PO 1035 → CNCystalPillar 水晶柱
        if ( operator new(0x44Cu) == nullptr )  // 申请 1100 字节（0x44C）→ CNCystalPillar 水晶柱
          goto LABEL_16;  // 转到公共出口 LABEL_16
        result = (uint32_t *)sub_5377A0(Block, pArg2);  // 构造 CNCystalPillar 水晶柱（构造参数包）
        goto LABEL_17;  // 转到公共出口 LABEL_17
      //   1036+1040 → LABEL_134 / 1037 → LABEL_127 / 1038 → LABEL_136 / 1039 → LABEL_138
      case 1036:  // PO 1036（无专属构造器）
      case 1040:  // PO 1040 与同组 ID 共用出口 LABEL_134
        goto LABEL_134;  // 转到公共出口 LABEL_134
      case 1037:  // PO 1037 与同组 ID 共用出口 LABEL_127
        goto LABEL_127;  // 转到公共出口 LABEL_127
      case 1038:  // PO 1038 与同组 ID 共用出口 LABEL_136
        goto LABEL_136;  // 转到公共出口 LABEL_136
      case 1039:  // PO 1039 与同组 ID 共用出口 LABEL_138
        goto LABEL_138;  // 转到公共出口 LABEL_138
      default:
        goto LABEL_494;  // 转到公共出口 LABEL_494
    }
  }
  // ── [段 46] Block == 815：LABEL_63 sub_52EF60=CNTreasureBox ──
  if ( Block == 815 )  // 按 PO ID 阈值 == 815 收窄分支
  {
LABEL_63:
    if ( operator new(0x44Cu) != nullptr )  // 申请 1100 字节（0x44C）→ CNTreasureBox 宝箱
      return (uint32_t *)sub_52EF60(Block, pArg2);  // 返回 CNTreasureBox 宝箱（构造参数包）
    return nullptr;  // 返回空指针（构造失败/未命中）
  }
  // ── [段 47] Block > 286：735-814 段 ──
  //   735-813 → LABEL_125 CNRDPooledPassiveObject / 770-809 → LABEL_73 CNPassiveObject 底座
  if ( Block > 286 )  // 按 PO ID 阈值 > 286 收窄分支
  {
    if ( Block > 721 )  // 按 PO ID 阈值 > 721 收窄分支
    {
      switch ( Block )  // 按 PO ID 分派到具体构造
      {
        case 735:  // PO 735（无专属构造器）
        case 736:  // PO 736（无专属构造器）
        case 737:  // PO 737（无专属构造器）
        case 801:  // PO 801（无专属构造器）
        case 810:  // PO 810（无专属构造器）
        case 811:  // PO 811（无专属构造器）
        case 812:  // PO 812（无专属构造器）
        case 813:  // PO 813 与同组 ID 共用出口 LABEL_125
          goto LABEL_125;  // 转到公共出口 LABEL_125
        case 770:  // PO 770（无专属构造器）
        case 771:  // PO 771（无专属构造器）
        case 772:  // PO 772（无专属构造器）
        case 773:  // PO 773（无专属构造器）
        case 774:  // PO 774（无专属构造器）
        case 775:  // PO 775（无专属构造器）
        case 776:  // PO 776（无专属构造器）
        case 777:  // PO 777（无专属构造器）
        case 778:  // PO 778（无专属构造器）
        case 779:  // PO 779（无专属构造器）
        case 780:  // PO 780（无专属构造器）
        case 781:  // PO 781（无专属构造器）
        case 800:  // PO 800（无专属构造器）
        case 802:  // PO 802（无专属构造器）
        case 803:  // PO 803（无专属构造器）
        case 806:  // PO 806（无专属构造器）
        case 807:  // PO 807（无专属构造器）
        case 808:  // PO 808（无专属构造器）
        case 809:  // PO 809 与同组 ID 共用出口 LABEL_73
          goto LABEL_73;  // 转到公共出口 LABEL_73
        //   804-805 sub_537D30（0x3CC）/ 814 sub_537AE0
        case 804:  // PO 804（无专属构造器）
        case 805:  // PO 805 → CNTreeCross 树十字
          if ( operator new(0x3CCu) == nullptr )  // 申请 972 字节（0x3CC）→ CNTreeCross 树十字
            goto LABEL_16;  // 转到公共出口 LABEL_16
          result = (uint32_t *)sub_537D30(Block, pArg2);  // 构造 CNTreeCross 树十字（构造参数包）
          goto LABEL_17;  // 转到公共出口 LABEL_17
        case 814:  // PO 814 → CNWaterDrop 水滴
          if ( operator new(0x3D4u) == nullptr )  // 申请 980 字节（0x3D4）→ CNWaterDrop 水滴
            return nullptr;  // 返回空指针（构造失败/未命中）
          return (uint32_t *)sub_537AE0(Block, pArg2);  // 返回 CNWaterDrop 水滴（构造参数包）
        default:
          goto LABEL_494;  // 转到公共出口 LABEL_494
      }
    }
    // ── [段 48] Block == 721：sub_537130（0x3CC）──
    if ( Block == 721 )  // 按 PO ID 阈值 == 721 收窄分支
    {
      if ( operator new(0x3CCu) != nullptr )  // 申请 972 字节（0x3CC）→ CNBehemothHelipad 巨兽停机坪
        return (uint32_t *)sub_537130(721, pArg2);  // 返回 CNBehemothHelipad 巨兽停机坪（构造参数包）
      return nullptr;  // 返回空指针（构造失败/未命中）
    }
    // ── [段 49] 291-337 段：291-316 CNRDPooledPassiveObject 二十六连 / 300 → LABEL_73 / 319-330 break 到 53
    if ( Block <= 337 )  // 按 PO ID 阈值 <= 337 收窄分支
    {
      if ( Block < 333 )  // 按 PO ID 阈值 < 333 收窄分支
      {
        switch ( Block )  // 按 PO ID 分派到具体构造
        {
          case 291:  // PO 291（无专属构造器）
          case 292:  // PO 292（无专属构造器）
          case 293:  // PO 293（无专属构造器）
          case 294:  // PO 294（无专属构造器）
          case 295:  // PO 295（无专属构造器）
          case 296:  // PO 296（无专属构造器）
          case 301:  // PO 301（无专属构造器）
          case 302:  // PO 302（无专属构造器）
          case 303:  // PO 303（无专属构造器）
          case 304:  // PO 304（无专属构造器）
          case 305:  // PO 305（无专属构造器）
          case 306:  // PO 306（无专属构造器）
          case 307:  // PO 307（无专属构造器）
          case 308:  // PO 308（无专属构造器）
          case 309:  // PO 309（无专属构造器）
          case 310:  // PO 310（无专属构造器）
          case 311:  // PO 311（无专属构造器）
          case 312:  // PO 312（无专属构造器）
          case 313:  // PO 313（无专属构造器）
          case 314:  // PO 314（无专属构造器）
          case 315:  // PO 315（无专属构造器）
          case 316:  // PO 316 与同组 ID 共用出口 LABEL_125
            goto LABEL_125;  // 转到公共出口 LABEL_125
          case 300:  // PO 300 与同组 ID 共用出口 LABEL_73
            goto LABEL_73;  // 转到公共出口 LABEL_73
          case 319:  // PO 319（无专属构造器）
          case 320:  // PO 320（无专属构造器）
          case 321:  // PO 321（无专属构造器）
          case 322:  // PO 322（无专属构造器）
          case 323:  // PO 323（无专属构造器）
          case 326:  // PO 326（无专属构造器）
          case 327:  // PO 327（无专属构造器）
          case 328:  // PO 328（无专属构造器）
          case 329:  // PO 329（无专属构造器）
          case 330:  // PO 330（无专属构造器）
            break;
          default:
            goto LABEL_494;  // 转到公共出口 LABEL_494
        }
      }
// ── [段 50] LABEL_53：sub_539140（0x3E8）—— 333-337 / 709-716 / 361-490 多组共用 ──
LABEL_53:
      if ( operator new(0x3E8u) != nullptr )  // 申请 1000 字节（0x3E8）→ CNGravityChangeBack 重力还原
        return (uint32_t *)sub_539140(Block, pArg2);  // 返回 CNGravityChangeBack 重力还原（构造参数包）
      return nullptr;  // 返回空指针（构造失败/未命中）
    }
    // ── [段 51] 702-716 段：702-716 → LABEL_53；716+ → LABEL_53 ──
    if ( Block > 713 )  // 按 PO ID 阈值 > 713 收窄分支
    {
      if ( Block >= 716 )  // 按 PO ID 阈值 >= 716 收窄分支
        goto LABEL_53;  // 转到公共出口 LABEL_53
    }
    else
    {
      if ( Block >= 709 )  // 按 PO ID 阈值 >= 709 收窄分支
        goto LABEL_53;  // 转到公共出口 LABEL_53
      if ( Block <= 706 )  // 按 PO ID 阈值 <= 706 收窄分支
      {
        if ( Block >= 702 )  // 按 PO ID 阈值 >= 702 收窄分支
          goto LABEL_53;  // 转到公共出口 LABEL_53
        // ── [段 52] 361-490 段：sub_52F0B0=CNPathGate + 回写 +945=1（强制置有效位） ──
        if ( Block >= 361 && Block <= 490 )  // PO ID 落在 [361>=, 490<=] 区间
        {
          if ( operator new(0x3ECu) != nullptr )  // 申请 1004 字节（0x3EC）→ CNPathGate 通道门
          {
            result = (uint32_t *)sub_52F0B0(Block, pArg2);  // 构造 CNPathGate 通道门（构造参数包）
            goto LABEL_17;  // 转到公共出口 LABEL_17
          }
LABEL_16:
          result = nullptr;  // 结果置空
LABEL_17:
          *((uint8_t *)result + 945) = 1;  // 对象 +945 打标记 1
          return result;  // 返回已构造对象
        }
      }
    }
    goto LABEL_494;  // 转到公共出口 LABEL_494
  }
  // ── [段 53] Block >= 281：LABEL_125 池化对象路径 —— 先 sub_52E320(972) 惰性池申请再 sub_52EB00 构造 ──
  if ( Block >= 281 )  // 按 PO ID 阈值 >= 281 收窄分支
  {
LABEL_125:
    if ( sub_52E320(972) != 0 )  // 若对象池可用（对象池借出（172 字节 PO 底座）≠0）
    {
      result = (uint32_t *)sub_52EB00(Block, pArg2);  // 构造 CNRDPooledPassiveObject 构造（构造参数包）
      goto LABEL_17;  // 转到公共出口 LABEL_17
    }
    goto LABEL_16;  // 转到公共出口 LABEL_16
  }
  // ── [段 54] Block <= 250：1-20 基础 PO 段 ──
  if ( Block <= 250 )  // 按 PO ID 阈值 <= 250 收窄分支
  {
    if ( Block < 241 )  // 按 PO ID 阈值 < 241 收窄分支
    {
      switch ( Block )  // 按 PO ID 分派到具体构造
      {
        // ── [段 55] 1-20 段：sub_52F5C0=CNParticleFactory（粒子工厂 PO，0x3D8）—— 1-9/13-20 共 17 个 ID ──
        case 1:  // PO 1（无专属构造器）
        case 2:  // PO 2（无专属构造器）
        case 3:  // PO 3（无专属构造器）
        case 4:  // PO 4（无专属构造器）
        case 5:  // PO 5（无专属构造器）
        case 6:  // PO 6（无专属构造器）
        case 7:  // PO 7（无专属构造器）
        case 8:  // PO 8（无专属构造器）
        case 9:  // PO 9（无专属构造器）
        case 13:  // PO 13（无专属构造器）
        case 14:  // PO 14（无专属构造器）
        case 15:  // PO 15（无专属构造器）
        case 16:  // PO 16（无专属构造器）
        case 17:  // PO 17（无专属构造器）
        case 18:  // PO 18（无专属构造器）
        case 19:  // PO 19（无专属构造器）
        case 20:  // PO 20 → CNParticleFactory 粒子工厂
          if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNParticleFactory 粒子工厂
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_52F5C0(Block, pArg2);  // 构造 CNParticleFactory 粒子工厂（构造参数包）
          break;
        //   221-239 → LABEL_73 / 222 → LABEL_63 / 223-230 sub_538AA0 + 回写 +945=1（八连）
        case 221:  // PO 221（无专属构造器）
        case 231:  // PO 231（无专属构造器）
        case 235:  // PO 235（无专属构造器）
        case 238:  // PO 238（无专属构造器）
        case 239:  // PO 239 与同组 ID 共用出口 LABEL_73
          goto LABEL_73;  // 转到公共出口 LABEL_73
        case 222:  // PO 222 与同组 ID 共用出口 LABEL_63
          goto LABEL_63;  // 转到公共出口 LABEL_63
        case 223:  // PO 223（无专属构造器）
        case 224:  // PO 224（无专属构造器）
        case 225:  // PO 225（无专属构造器）
        case 226:  // PO 226（无专属构造器）
        case 227:  // PO 227（无专属构造器）
        case 228:  // PO 228（无专属构造器）
        case 229:  // PO 229（无专属构造器）
        case 230:  // PO 230 → CNActionTree 行动树
          if ( operator new(0x44Cu) == nullptr )  // 申请 1100 字节（0x44C）→ CNActionTree 行动树
            goto LABEL_16;  // 转到公共出口 LABEL_16
          result = (uint32_t *)sub_538AA0(Block, pArg2);  // 构造 CNActionTree 行动树（构造参数包）
          *((uint8_t *)result + 945) = 1;  // 对象 +945 打标记 1
          break;
        //   236-237 sub_5381D0 / 240 sub_538CA0
        case 236:  // PO 236（无专属构造器）
        case 237:  // PO 237 → CNQuestCage 任务笼
          if ( operator new(0x454u) == nullptr )  // 申请 1108 字节（0x454）→ CNQuestCage 任务笼
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_5381D0(Block, pArg2);  // 构造 CNQuestCage 任务笼（构造参数包）
          break;
        case 240:  // PO 240 → CNFountain 喷泉
          if ( operator new(0x450u) == nullptr )  // 申请 1104 字节（0x450）→ CNFountain 喷泉
            return nullptr;  // 返回空指针（构造失败/未命中）
          result = (uint32_t *)sub_538CA0(Block, pArg2);  // 构造 CNFountain 喷泉（构造参数包）
          break;
        default:
          goto LABEL_494;  // 转到公共出口 LABEL_494
      }
      return result;  // 返回已构造对象
    // ── [段 56] Block 处于 [241, 250]：sub_52EBF0=CNCutableGrass（可砍草丛 PO，0x40C） ──
    }
    if ( operator new(0x40Cu) != nullptr )  // 申请 1036 字节（0x40C）→ CNCutableGrass 可砍草丛
      return (uint32_t *)sub_52EBF0(Block, pArg2);  // 返回 CNCutableGrass 可砍草丛（构造参数包）
    return nullptr;  // 返回空指针（构造失败/未命中）
  }
  // ── [段 57] Block 处于 (250, 281)：258-276 段（小 PO 收尾） ──
  //   258 sub_536850 / 261 CNToothKurokuta / 262-264 → LABEL_121 / 265-266 CNEarthFire 两型（1500ms）」
  switch ( Block )  // 按 PO ID 分派到具体构造
  {
    case 258:  // PO 258 → CNSeaGrass 海草
      if ( operator new(0x3D8u) == nullptr )  // 申请 984 字节（0x3D8）→ CNSeaGrass 海草
        return nullptr;  // 返回空指针（构造失败/未命中）
      result = (uint32_t *)sub_536850(Block, pArg2);  // 构造 CNSeaGrass 海草（构造参数包）
      break;
    case 261:  // PO 261 → CNMineTrap 地雷陷阱
      if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNMineTrap 地雷陷阱
        return nullptr;  // 返回空指针（构造失败/未命中）
      result = (uint32_t *)sub_535AD0(Block, pArg2);  // 构造 CNMineTrap 地雷陷阱（构造参数包）
      break;
    case 262:  // PO 262（无专属构造器）
    case 263:  // PO 263（无专属构造器）
    case 264:  // PO 264 与同组 ID 共用出口 LABEL_121
      goto LABEL_121;  // 转到公共出口 LABEL_121
    case 265:  // PO 265 → CNEarthFire 地火
      if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNEarthFire 地火
        return nullptr;  // 返回空指针（构造失败/未命中）
      result = (uint32_t *)sub_52FAD0(Block, 3, 1500, 0, 0);  // 构造 CNEarthFire 地火(3, 1500, 0, 0)
      break;
    //   267-268 双型 / 269 → LABEL_123 / 270 sub_5360F0 / 271-276 → LABEL_125 池化
    case 266:  // PO 266 → CNEarthFire 地火
      if ( operator new(0x3F0u) == nullptr )  // 申请 1008 字节（0x3F0）→ CNEarthFire 地火
        return nullptr;  // 返回空指针（构造失败/未命中）
      result = (uint32_t *)sub_52FAD0(Block, 5, 1500, 0, 1);  // 构造 CNEarthFire 地火(5, 1500, 0, 1)
      break;
    case 267:  // PO 267 → CNTrapCage 陷阱笼
      if ( operator new(0x3E0u) == nullptr )  // 申请 992 字节（0x3E0）→ CNTrapCage 陷阱笼
        return nullptr;  // 返回空指针（构造失败/未命中）
      result = (uint32_t *)sub_535DB0(Block, pArg2);  // 构造 CNTrapCage 陷阱笼（构造参数包）
      break;
    case 268:  // PO 268 → CNChandelier 吊灯
      if ( operator new(0x3E4u) == nullptr )  // 申请 996 字节（0x3E4）→ CNChandelier 吊灯
        return nullptr;  // 返回空指针（构造失败/未命中）
      result = (uint32_t *)sub_535E90(Block, pArg2);  // 构造 CNChandelier 吊灯（构造参数包）
      break;
    case 269:  // PO 269 与同组 ID 共用出口 LABEL_123
      goto LABEL_123;  // 转到公共出口 LABEL_123
    case 270:  // PO 270 → CNSpiner 旋刺
      if ( operator new(0x3E8u) == nullptr )  // 申请 1000 字节（0x3E8）→ CNSpiner 旋刺
        return nullptr;  // 返回空指针（构造失败/未命中）
      result = (uint32_t *)sub_5360F0(Block, pArg2);  // 构造 CNSpiner 旋刺（构造参数包）
      break;
    case 271:  // PO 271（无专属构造器）
    case 272:  // PO 272（无专属构造器）
    case 273:  // PO 273（无专属构造器）
    case 274:  // PO 274（无专属构造器）
    case 275:  // PO 275（无专属构造器）
    case 276:  // PO 276 与同组 ID 共用出口 LABEL_125
      goto LABEL_125;  // 转到公共出口 LABEL_125
    default:
      goto LABEL_494;  // 转到公共出口 LABEL_494
  }
  return result;  // 返回已构造对象
}

