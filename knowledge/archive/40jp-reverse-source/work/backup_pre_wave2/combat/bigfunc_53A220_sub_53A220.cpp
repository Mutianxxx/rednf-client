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
  if ( Block > 23007 )
  {
    if ( Block <= 30003 )
    {
      // ── [段 2] 30003 特例：CNHunterSpittle（猎手唾液）—— 0x3D0 字节 ──
      if ( Block == 30003 )
      {
        if ( operator new(0x3D0u) != nullptr )
          return (uint32_t *)sub_534660(30003, pArg2);
        return nullptr;
      }
      // ── [段 3] 23008-23019 段：法师/元素系大型 PO（0x3CC-0x3F4 字节） ──
      //   23008 CNLaunchJOL / 23009 CNLaunchFrostHead / 23010 LAUNCH_FLUORESCENT 荧光发射 / 23011 CNLaunchBlackCat
      switch ( Block )
      {
        //   23012 CNVoid / 23013 CNHalloweenBuster / 23014 CNHalloweenBusterSub / 23015 SUN_BURST 阳光爆发 / 23016 CNFireExplosion
        //   23017 QUICK_TURN / 23018 CNTargetItBall / 23019 CNThunderBolt（三参 3 = 雷电形态）
        case 23008:
          if ( operator new(0x3E8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_533300(Block, pArg2);
          break;
        case 23009:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5333E0(Block, pArg2);
          break;
        case 23010:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5334C0(Block, pArg2);
          break;
        case 23011:
          if ( operator new(0x3F4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5337D0(Block, pArg2);
          break;
        case 23012:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5338B0(Block, pArg2);
          break;
        case 23013:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_533C10(Block, pArg2);
          break;
        case 23014:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_533CF0(Block, pArg2);
          break;
        case 23015:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_533DD0(Block, pArg2);
          break;
        case 23016:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, pArg2);
          return nullptr;
        case 23017:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5340A0(Block, pArg2);
          break;
        case 23018:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_534580(Block, pArg2);
          break;
        case 23019:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_52F4D0(Block, pArg2, 3);
          break;
        //   上表未命中（default）→ goto LABEL_494 通用兜底（CNRDPooledPassiveObject 构造）
        default:
          goto LABEL_494;
      }
      return result;
    }
    // ── [段 4] 30004-30100 段：技能弹体主区（分段分支极密，每型一 new+构造） ──
    if ( Block <= 30100 )
    {
      if ( Block == 30100 )
      {
        if ( operator new(0x3D0u) != nullptr )
          return (uint32_t *)sub_535600(30100, pArg2);
        return nullptr;
      }
      switch ( Block )
      {
        //   30004 CNZombieEye / 30005 CNZombieEyeExplode / 30006 CNKagelBomb（内部转 30008）/ 30008 CNKagelBombSub
        case 30004:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534700(Block, pArg2);
        case 30005:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5347A0(Block, pArg2);
        case 30006:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534840(Block, 30008);
        case 30008:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, pArg2);
          return nullptr;
        //   30009 CNBronzeGolemBullets / 30010-30011 CNTreadShootSub / 30012 CNAshenForkSub / 30013 CNSpaceFishBug
        case 30009:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534BC0(Block, pArg2);
        case 30010:
        case 30011:
          if ( operator new(0x3F8u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534A90(Block, pArg2);
        case 30012:
          if ( operator new(0x3F8u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534AF0(Block, pArg2);
        case 30013:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534990(Block, pArg2);
        //   30015/30036 → LABEL_527（CNLOLLaser）；30016/30017+30003 同族 CNHunterSpittle；30018 CNZepplinBullet
        case 30015:
        case 30036:
          goto LABEL_527;
        case 30016:
        case 30017:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534660(Block, pArg2);
        //   30019 CNKagelBomb(30020) / 30020 CNKagelBombSub / 30021 CNCreateOnDestroyObject / 30023 CNKagelBomb(30024)
        case 30018:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534FA0(Block, pArg2);
        case 30019:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534840(Block, 30020);
        case 30020:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, pArg2);
          return nullptr;
        case 30021:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_530040(Block, pArg2);
          return nullptr;
        case 30022:
          if ( operator new(0x3CCu) != nullptr )
            goto LABEL_346;
          return nullptr;
        case 30023:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534840(Block, 30024);
        //   30024/30032/30035/30064/30078 CNKagelBombSub 复用 / 30025+30380 CNIceWaveUp / 30026 CNStoneBlade …
        case 30024:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, pArg2);
          return nullptr;
        case 30025:
          if ( operator new(0x3D0u) != nullptr )
            return (uint32_t *)sub_534C60(Block, pArg2);
          return nullptr;
        case 30026:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534D40(Block, pArg2);
        //   30028 CNGrabbingLegOfLotus（巨型黑章鱼抓腿）/ 30029 CNPierceHeadLegOfLotus / 30030-30031 CNZepplinBullet
        case 30028:
          if ( operator new(0x400u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534F40(Block, pArg2);
        case 30029:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534EB0(Block, pArg2);
        case 30030:
        case 30031:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_535010(Block, pArg2);
        //   30033 CNRDTrap 基座直构（走通用底座 0x52EA60，非派生专属构造）/ 30034+30037 CNKagelBombSub(30335/30046) 双档
        case 30032:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, pArg2);
          return nullptr;
        case 30033:
          pMem = operator new(0x3CCu);
          if ( pMem == nullptr )
            return nullptr;
          return sub_52EA60(pMem, Block, (int)pArg2);
        case 30034:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5352D0(Block, pArg2, 30035, 0);
        case 30035:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, pArg2);
          return nullptr;
        case 30037:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5352D0(Block, pArg2, 30046, 5);
        //   30038-30040 CNGunnerLaser（三 ID 同型）…
        case 30038:
        case 30039:
        case 30040:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5351F0(Block, pArg2);
        // ── [段 5] 30043-30094 段：CNCreateOnDestroyObject / CNFireMissile / CNIceMissile / CNShootingStar 族 ──
        case 30043:
          if ( operator new(0x3D4u) != nullptr )
            goto LABEL_370;
          return nullptr;
        case 30044:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, pArg2);
          return nullptr;
        case 30045:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, pArg2);
          return nullptr;
        //   30046 → LABEL_503 与 40006 共用 sub_52FAD0(500,1,1)；30047/30049 CNTagetItBall…
        case 30046:
          goto LABEL_503;
        case 30047:
        case 30049:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F1E0(Block, pArg2);
        case 30048:
        case 30050:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
          goto LABEL_378;
        //   30051/30052+40006 走 sub_52FAD0 四/五参（500,1, flag）
        case 30051:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
          goto LABEL_378;
        case 30052:
          if ( operator new(0x3F0u) != nullptr )
            goto LABEL_382;
          return nullptr;
        //   30053-30056：CNFireExplosion 爆炸族（0x3E0-0x3E4）
        case 30053:
        case 30054:
          if ( operator new(0x3E0u) != nullptr )
            goto LABEL_384;
          return nullptr;
        case 30055:
        case 30056:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, pArg2);
          return nullptr;
        //   30057-30063：CNIceMissile 族（0x3D4）+ CNIceWave/CNIceNiddle（0x3CC）—— 30060..30063 与 30085..30088 同构
        case 30057:
        case 30058:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_52F3F0(Block, pArg2);
          return nullptr;
        case 30059:
          if ( operator new(0x3E8u) != nullptr )
            goto LABEL_537;
          return nullptr;
        case 30060:
        case 30061:
        case 30062:
        case 30063:
          if ( operator new(0x3CCu) != nullptr )
            return (uint32_t *)sub_52FA30(Block, pArg2);
          return nullptr;
        case 30064:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, pArg2);
          return nullptr;
        //   30065 → LABEL_506 sub_530270=CNRedRock；30066 → LABEL_568 sub_52FBC0=CNShootingStar
        case 30065:
          if ( operator new(0x3D4u) != nullptr )
            goto LABEL_506;
          return nullptr;
        case 30066:
          if ( operator new(0x3D8u) != nullptr )
            goto LABEL_568;
          return nullptr;
        //   30067 → LABEL_569 sub_52FCA0=CNShootingStarExp(0)
        case 30067:
          goto LABEL_569;
        //   30068-30069 CNSunkenRock / 30070-30074 CNThunderBolt(0) 五连 / 30077 CNKagelBomb(30078)
        case 30068:
        case 30069:
          if ( operator new(0x3D0u) != nullptr )
            return (uint32_t *)sub_5301D0(Block, pArg2);
          return nullptr;
        case 30070:
        case 30071:
        case 30072:
        case 30073:
        case 30074:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F4D0(Block, pArg2, 0);
        case 30077:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534840(Block, 30078);
        case 30078:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, pArg2);
          return nullptr;
        //   30080 CNToothKurokuta / 30081 … / 30084 与 30059 同型（CNShootingStarExp）
        case 30080:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5353D0(Block, pArg2);
        case 30081:
          if ( operator new(0x3ECu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_535450(Block, pArg2);
        case 30084:
          if ( operator new(0x3E8u) != nullptr )
            goto LABEL_537;
          return nullptr;
        case 30085:
        case 30086:
        case 30087:
        case 30088:
          if ( operator new(0x3CCu) != nullptr )
            return (uint32_t *)sub_52FA30(Block, pArg2);
          return nullptr;
        case 30089:
        case 30095:
          if ( operator new(0x434u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_535520(Block, pArg2);
        //   30089+30095 同型（0x434 大对象）/ 30090 / 30091-30092-30093 与 40007 共享类
        case 30090:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_535560(Block, pArg2);
        case 30091:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
LABEL_378:
          result = (uint32_t *)sub_52FAD0(Block, pArg2, 500, 1, 0);
          break;
        //   30092-30093 → sub_61E4C0=头骨子体 CNGhoulSkullSub 构造（0x5E 区之外）
        case 30092:
        case 30093:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_61E4C0(Block, pArg2);
          break;
        //   30094 → LABEL_490 = CNIceWaveUp
        case 30094:
          goto LABEL_490;
        default:
          goto LABEL_494;
      }
      return result;
    }
    // ── [段 6] Block 处于 (30100, 48008]：地图机关/技能弹体第二主区 ──
    if ( Block <= 48008 )
    {
      // ── [段 7] 48005-48008 段：全走 sub_52FA30=CNIceNiddle（0x3CC 窄对象） ──
      if ( Block >= 48005 )
      {
        if ( operator new(0x3CCu) == nullptr )
          return nullptr;
      }
      else
      {
        // ── [段 8] Block 处于 (30368, 48005)：按 42002/46003 二分 ──
        if ( Block > 30368 )
        {
          if ( Block > 42002 )
          {
            if ( Block > 46003 )
            {
              switch ( Block )
              {
                // ── [段 9] 48001-48004：CNBlast 爆炸族 ──
                //   48001 CNBlast / 48002 CNEarthQuake / 48003+48004 CNDangerousGas（48004 → LABEL_537 CNIceNiddleGroup）
                case 48001:
                  if ( operator new(0x3E0u) == nullptr )
                    return nullptr;
                  result = (uint32_t *)sub_52F6A0(Block, pArg2);
                  break;
                case 48002:
                  if ( operator new(0x3E0u) == nullptr )
                    return nullptr;
LABEL_384:
                  result = (uint32_t *)sub_52F780(Block, pArg2);
                  break;
                case 48003:
                  if ( operator new(0x3DCu) == nullptr )
                    return nullptr;
                  result = (uint32_t *)sub_52F860(Block, pArg2, 0);
                  break;
                case 48004:
                  if ( operator new(0x3E8u) == nullptr )
                    return nullptr;
LABEL_537:
                  result = (uint32_t *)sub_52F950(Block, pArg2);
                  break;
                default:
                  goto LABEL_494;
              }
              return result;
            }
            // ── [段 10] 46003 → LABEL_527（CNLOLLaser）；46001 CNThunderBolt(0)、46002 CNTemporaryHit ──
            if ( Block == 46003 )
            {
LABEL_527:
              if ( operator new(0x3D8u) != nullptr )
                return (uint32_t *)sub_534B20(Block, pArg2);
              return nullptr;
            }
            if ( Block > 44001 )
            {
              if ( Block == 46001 )
              {
                if ( operator new(0x3D4u) != nullptr )
                  return (uint32_t *)sub_52F4D0(46001, pArg2, 0);
                return nullptr;
              }
              if ( Block == 46002 )
              {
                if ( operator new(0x3CCu) != nullptr )
                  return (uint32_t *)sub_530500(46002, pArg2);
                return nullptr;
              }
              goto LABEL_494;
            }
            if ( Block != 44001 )
            {
              if ( Block <= 42006 )
              {
// ── [段 11] 42001-42007 段：CNIceMissile(42001) / ≤42006+48011… 走 LABEL_545=CNTemporaryHit / 42007 CNSingleIceWave ──
LABEL_545:
                if ( operator new(0x3CCu) != nullptr )
                  return (uint32_t *)sub_530500(Block, pArg2);
                return nullptr;
              }
              if ( Block == 42007 )
              {
                if ( operator new(0x3FCu) != nullptr )
                  return (uint32_t *)sub_531060(42007, pArg2);
                return nullptr;
              }
              goto LABEL_494;
            }
          }
          else
          {
            // ── [段 12] 40001-40008 段：40004(CNLaser) 40005 40006 40007 40008 ──
            //   40001/40002 CNSpaceFishBug 族（0x3D8）/ 40003 CNEarthFire / 40006 CNEarthFire(1) / 40008 CNShootingStarExp(1)
            if ( Block >= 42001 )
            {
              if ( operator new(0x3D4u) != nullptr )
                return (uint32_t *)sub_52F3F0(Block, pArg2);
              return nullptr;
            }
            if ( Block > 40003 )
            {
              switch ( Block )
              {
                case 40004:
                  if ( operator new(0x3D8u) != nullptr )
                    goto LABEL_568;
                  return nullptr;
                case 40005:
                  goto LABEL_569;
                case 40006:
LABEL_503:
                  if ( operator new(0x3F0u) == nullptr )
                    return nullptr;
LABEL_382:
                  result = (uint32_t *)sub_52FAD0(Block, pArg2, 500, 1, 1);
                  break;
                case 40007:
                  if ( operator new(0x3D4u) == nullptr )
                    return nullptr;
LABEL_506:
                  result = (uint32_t *)sub_530270(Block, pArg2);
                  break;
                case 40008:
                  if ( operator new(0x3E8u) == nullptr )
                    return nullptr;
                  result = (uint32_t *)sub_52FCA0(Block, pArg2, 1);
                  break;
                default:
                  goto LABEL_494;
              }
              return result;
            }
            if ( Block == 40003 )
            {
              if ( operator new(0x3F0u) != nullptr )
                return (uint32_t *)sub_52FAD0(40003, pArg2, 500, 1, 0);
              return nullptr;
            }
            // ── [段 13] 30370-30380 段：30370+30371 CNKagelBomb 双 ID 同型 / 30380 CNIceWaveUp ──
            if ( Block <= 30380 )
            {
              switch ( Block )
              {
                case 30380:
LABEL_490:
                  if ( operator new(0x3D0u) != nullptr )
                    return (uint32_t *)sub_534C60(Block, pArg2);
                  return nullptr;
                case 30370:
                  if ( operator new(0x3D0u) != nullptr )
                    return (uint32_t *)sub_534840(30370, 30371);
                  return nullptr;
                case 30371:
                  if ( operator new(0x3D4u) != nullptr )
                    return (uint32_t *)sub_5348A0(30371, pArg2);
                  return nullptr;
                default:
                  break;
              }
              goto LABEL_494;
            }
            if ( Block == 40001 )
            {
              if ( operator new(0x3D8u) != nullptr )
                return (uint32_t *)sub_52F1E0(40001, pArg2);
              return nullptr;
            }
            if ( Block != 40002 )
              goto LABEL_494;
          }
// ── [段 14] LABEL_519：sub_52F2C0=CNFireExplosion 共通构造 ──
LABEL_519:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, pArg2);
          return nullptr;
        }
        // ── [段 15] Block < 30365：30302-30310 大段（头骨/邪眼/巨型黑章鱼/CNTrackingIceWave 等） ──
        if ( Block < 30365 )
        {
          switch ( Block )
          {
            //   30200 CNGrabbingLegOfLotus(0x3F8) / 30201 CNPierceHeadLegOfLotus / 30202 → LABEL_563=CNBodyHit
            case 30200:
              if ( operator new(0x3F8u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_535670(Block, pArg2);
              break;
            case 30201:
              if ( operator new(0x3CCu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_535850(Block, pArg2);
              break;
            case 30202:
              goto LABEL_563;
            //   30300 CNSpiralNen(0x3F4) / 30301-30305 CNTargetItBall 四型（0x3CC-0x3D8）
            case 30300:
              if ( operator new(0x3F4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5358C0(Block, pArg2);
              break;
            case 30301:
              if ( operator new(0x3D8u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_61F7D0(Block, pArg2);
              break;
            case 30302:
              if ( operator new(0x3CCu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_61F8B0(Block, pArg2);
              break;
            case 30303:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_61F9F0(Block, pArg2);
              break;
            case 30304:
              if ( operator new(0x3D8u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5359F0(Block, pArg2);
              break;
            case 30305:
              if ( operator new(0x3D8u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_61FAD0(Block, pArg2);
              break;
            //   30310 CNTrackingIceWave(0x460) / 30311 CNThunderBolt(2) / 30312 CNTemporaryHit …
            case 30310:
              if ( operator new(0x460u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_530E30(Block, pArg2);
              break;
            case 30311:
              if ( operator new(0x3D4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_52F4D0(Block, pArg2, 2);
              break;
            case 30312:
              if ( operator new(0x3CCu) != nullptr )
                return (uint32_t *)sub_530500(Block, pArg2);
              return nullptr;
            //   30320 CNFireExplosion / 30321 → LABEL_506 CNRedRock / 30322 CNSummonMonsterWithEffect
            case 30320:
              if ( operator new(0x3E4u) != nullptr )
                return (uint32_t *)sub_52F2C0(Block, pArg2);
              return nullptr;
            case 30321:
              if ( operator new(0x3D4u) != nullptr )
                goto LABEL_506;
              return nullptr;
            case 30322:
              if ( operator new(0x3F0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_53A1B0(Block, pArg2);
              break;
            //   30323 CNCreateOnDestroyObject / 30350 CNBlastBlood…（0x3EC）/ 30351 …
            case 30323:
              if ( operator new(0x3D4u) != nullptr )
                return (uint32_t *)sub_530040(Block, pArg2);
              return nullptr;
            case 30350:
              if ( operator new(0x3ECu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_539520(Block, pArg2);
              break;
            case 30351:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_539650(Block, pArg2);
              break;
            //   30360 CNSpecificEnemy…（强制 float 参数）/ 30361 CNFireExplosion / 30362-30364 同 40004-40008 段
            case 30360:
              if ( operator new(0x3D4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5397C0(Block, *(float *)&pArg2);
              break;
            case 30361:
              if ( operator new(0x3E4u) != nullptr )
                return (uint32_t *)sub_52F2C0(Block, pArg2);
              return nullptr;
            case 30362:
              if ( operator new(0x3D8u) != nullptr )
                goto LABEL_568;
              return nullptr;
            case 30363:
              goto LABEL_569;
            case 30364:
              if ( operator new(0x3E8u) != nullptr )
                goto LABEL_537;
              return nullptr;
            default:
              goto LABEL_494;
          }
          return result;
        }
        // ── [段 16] Block 处于 [30365, 30368] 的四值：全走 sub_52FA30=CNIceNiddle ──
        if ( operator new(0x3CCu) == nullptr )
          return nullptr;
      }
      return (uint32_t *)sub_52FA30(Block, pArg2);
    }
    // ── [段 17] Block 处于 (48008, 48043] 段：48043-48042 大段（弹药/激光/诅咒炸弹族） ──
    if ( Block <= 48043 )
    {
      //   48043 sub_5390B0(2)… / 48009 CNCreateOnDestroyObject
      if ( Block == 48043 )
      {
        if ( operator new(0x3D8u) != nullptr )
          return (uint32_t *)sub_5390B0(48043, pArg2, 2);
        return nullptr;
      }
      switch ( Block )
      {
        //   48010+48014 CNDollMasterBubble（人形师气泡）/ 48011+48033..48042 → LABEL_545 CNTemporaryHit 十一连
        case 48009:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5301D0(Block, pArg2);
        case 48010:
        case 48014:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_530350(Block, pArg2);
        case 48011:
        case 48033:
        case 48034:
        case 48035:
        case 48036:
        case 48037:
        case 48038:
        case 48039:
        case 48040:
        case 48041:
        case 48042:
          goto LABEL_545;
        //   48012 CNMagicTargetWarning（0x444）/ 48013 CNForceField / 48015 CNCircleAppendageMaker
        case 48012:
          if ( operator new(0x444u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_530430(Block, pArg2);
        case 48013:
          if ( operator new(0x3FCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5305E0(Block, pArg2);
        case 48015:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_530710(Block, pArg2, 0);
        //   48016 sub_538D90(1) / 48017 sub_538F70(1) / 48018 sub_538EB0(1)（三型带标志 1）
        case 48016:
          if ( operator new(0x3E4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_538D90(Block, pArg2, 1);
        case 48017:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_538F70(Block, pArg2, 1);
        case 48018:
          if ( operator new(0x3E4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_538EB0(Block, pArg2, 1);
        //   48019-48023 CNDangerousGas(1..5) 五连（同一构造不同档）/ 48024 CNSummonMonsterWithEffect
        case 48019:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F860(Block, pArg2, 1);
        case 48020:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F860(Block, pArg2, 2);
        case 48021:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F860(Block, pArg2, 3);
        case 48022:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F860(Block, pArg2, 4);
        case 48023:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          goto LABEL_556;
        case 48024:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_530C40(Block, pArg2);
        //   48025 同 48023（第 5 档）/ 48026 sub_539480 / 48027 sub_5393E0 / 48028 → LABEL_563 CNBodyHit
        case 48025:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
LABEL_556:
          result = (uint32_t *)sub_52F860(Block, pArg2, 5);
          break;
        case 48026:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_539480(Block, pArg2);
          break;
        case 48027:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5393E0(Block, pArg2);
          break;
        case 48028:
LABEL_563:
          if ( operator new(0x3F4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_530D50(Block, pArg2);
          break;
        //   48029 CNLOLLaser / 48030 → LABEL_568 CNShootingStar / 48031 → LABEL_569 CNShootingStarExp(0) / 48032 CNIceWaveUp
        case 48029:
          if ( operator new(0x3D8u) != nullptr )
            return (uint32_t *)sub_534B20(Block, pArg2);
          return nullptr;
        case 48030:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
LABEL_568:
          result = (uint32_t *)sub_52FBC0(Block, pArg2);
          break;
        case 48031:
LABEL_569:
          if ( operator new(0x3E8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_52FCA0(Block, pArg2, 0);
          break;
        case 48032:
          if ( operator new(0x3D0u) != nullptr )
            return (uint32_t *)sub_534C60(Block, pArg2);
          return nullptr;
        default:
          goto LABEL_494;
      }
      return result;
    }
    // ── [段 18] Block > 50704 区：50000-51201 段（地图传送门/Gate 与飞行弹体） ──
    if ( Block > 50704 )
    {
      if ( Block > 50950 )
      {
        switch ( Block )
        {
          //   51000 sub_610960(51100) 转派（诅咒炸弹 CNCurseBomb）/ 51100 CNCurseBombSub / 51200+51201 CNZepplinBullet 两型
          case 51000:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_610960(Block, 51100);
            break;
          case 51100:
            if ( operator new(0x3D4u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_530B50(Block, pArg2);
            break;
          case 51200:
            if ( operator new(0x3D8u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_539220(Block, pArg2);
            break;
          case 51201:
            if ( operator new(0x3D4u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_539300(Block, pArg2);
            break;
          default:
            goto LABEL_494;
        }
      }
      else
      {
        //   50950 CNToothKurokuta / 50750-50754 sub_5362F0 五连 / 50800-50805 → LABEL_629 sub_52FD90
        if ( Block == 50950 )
        {
          if ( operator new(0x3CCu) != nullptr )
            return (uint32_t *)sub_530A60(50950, pArg2);
          return nullptr;
        }
        switch ( Block )
        {
          case 50750:
          case 50751:
          case 50752:
          case 50753:
          case 50754:
            if ( operator new(0x3F0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_5362F0(Block, pArg2);
            break;
          case 50800:
          case 50801:
          case 50802:
          case 50803:
          case 50804:
          case 50805:
            if ( operator new(0x3CCu) == nullptr )
              return nullptr;
LABEL_629:
            result = (uint32_t *)sub_52FD90(Block, pArg2);
            break;
          //   50806-50810 sub_530010 五连 / 50900 CNToothSFish
          case 50806:
          case 50807:
          case 50808:
          case 50809:
          case 50810:
            if ( operator new(0x3DCu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_530010(Block, pArg2);
            break;
          case 50900:
            if ( operator new(0x3CCu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_530970(Block, pArg2);
            break;
          default:
            goto LABEL_494;
        }
      }
      return result;
    }
    //   50700-50704 CNCreateOnDestroyObject
    if ( Block >= 50700 )
    {
      if ( operator new(0x3D4u) != nullptr )
        return (uint32_t *)sub_530040(Block, pArg2);
      return nullptr;
    }
    // ── [段 19] Block 处于 (50404, 50700)：50500-50605 段 ──
    //   50500-50503 → LABEL_629 sub_52FD90=CNThrowItemDestroyable / 50580-50605（含 50590 → LABEL_346 sub_530130）
    if ( Block > 50404 )
    {
      switch ( Block )
      {
        case 50500:
        case 50501:
        case 50502:
        case 50503:
          if ( operator new(0x3CCu) != nullptr )
            goto LABEL_629;
          return nullptr;
        case 50580:
        case 50581:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_530040(Block, pArg2);
          return nullptr;
        case 50590:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
LABEL_346:
          result = (uint32_t *)sub_530130(Block, pArg2);
          break;
        case 50600:
        case 50601:
        case 50602:
        case 50603:
        case 50604:
        case 50605:
          if ( operator new(0x3CCu) != nullptr )
            goto LABEL_629;
          return nullptr;
        default:
          goto LABEL_494;
      }
      return result;
    }
    //   50400-50403 sub_52FF20=CNBouncer（弹跳球体）
    if ( Block >= 50400 )
    {
      if ( operator new(0x3D8u) != nullptr )
        return (uint32_t *)sub_52FF20(Block, pArg2);
      return nullptr;
    }
    // ── [段 20] Block 处于 [50001, 50404)：50001-50104 段 ──
    //   50001-50004 → LABEL_370 sub_530800 / 50100-50104 CNKagelBomb(Block+100)
    if ( Block <= 50204 )
    {
      if ( Block >= 50200 )
      {
        if ( operator new(0x3D4u) != nullptr )
          return (uint32_t *)sub_5348A0(Block, pArg2);
        return nullptr;
      }
      switch ( Block )
      {
        case 50001:
        case 50002:
        case 50003:
        case 50004:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
LABEL_370:
          result = (uint32_t *)sub_530800(Block, pArg2);
          break;
        case 50100:
        case 50101:
        case 50102:
        case 50103:
        case 50104:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_534840(Block, Block + 100);
          break;
        default:
          goto LABEL_494;
      }
      return result;
    }
    //   50200-50204 CNKagelBombSub / 50300-50305 sub_52FE30 六连
    if ( Block >= 50300 && Block <= 50305 )
    {
      if ( operator new(0x3D8u) != nullptr )
        return (uint32_t *)sub_52FE30(Block, pArg2);
      return nullptr;
    }
// ── [段 21] ★ LABEL_494 通用兜底：未知 ID 一律 new(972=0x3CC) + sub_52EA60(CNRDTrap 底座) ──
//   随后覆盖虚表为 CNRDPooledPassiveObject::vftable（对象池版），返回对象（永不 nullptr，除非内存不足）
LABEL_494:
    v4 = (uint32_t *)sub_52E320(972);
    v5 = v4;
    if ( v4 != nullptr )
    {
      sub_52EA60(v4, Block, (int)pArg2);
      *v5 = &CNRDPooledPassiveObject::`vftable';
      return v5;
    }
    return nullptr;
  }
  // ── [段 22] Block == 23007：CNMagicMissile（魔法飞弹）—— >23007 段的唯一小值 ──
  if ( Block == 23007 )
  {
    if ( operator new(0x3D4u) != nullptr )
      return (uint32_t *)sub_533220(23007, pArg2);
    return nullptr;
  }
  // ── [段 23] Block 处于 (1041, 23007)：20001-23006 段（召唤/格斗/枪手大型 PO） ──
  if ( Block > 1041 )
  {
    if ( Block <= 2002 )
    {
      // ── [段 24] Block < 2000：1042-1056 段（鬼剑士/格斗家技能弹体，0x3D0-0x478 大对象） ──
      //   1042 sub_537400 / 1043 sub_5374E0 / 1044 CNGhost / 1045 sub_5375C0 / 1046 sub_5376C0 / 1047 sub_537730
      if ( Block < 2000 )
      {
        switch ( Block )
        {
          case 1042:
LABEL_136:
            if ( operator new(0x460u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537400(Block, pArg2);
          case 1043:
LABEL_138:
            if ( operator new(0x46Cu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5374E0(Block, pArg2);
          case 1044:
LABEL_134:
            if ( operator new(0x458u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5371E0(Block, pArg2);
          case 1045:
            if ( operator new(0x46Cu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5375C0(Block, pArg2);
          case 1046:
            if ( operator new(0x464u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5376C0(Block, pArg2);
          case 1047:
            if ( operator new(0x46Cu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537730(Block, pArg2);
          //   1049 → LABEL_132 sub_536430(2,3) / 1050-1051 双型 / 1053 sub_537A00 / 1054 → LABEL_16/17
          case 1049:
LABEL_132:
            if ( operator new(0x478u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_536430(Block, pArg2, 2, 3);
          case 1050:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537840(Block, pArg2);
          case 1051:
            if ( operator new(0x3DCu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537920(Block, pArg2);
          case 1053:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537A00(Block, pArg2);
          case 1054:
            if ( operator new(0x454u) == nullptr )
              goto LABEL_16;
            result = (uint32_t *)sub_537FD0(Block, pArg2);
            goto LABEL_17;
          //   1055 sub_5380B0 / 1056 sub_536510(9,8)（大对象 0x478）
          case 1055:
            if ( operator new(0x46Cu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5380B0(Block, pArg2);
          case 1056:
            if ( operator new(0x478u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_536510(Block, pArg2, 9, 8);
          default:
            goto LABEL_494;
        }
      }
// ── [段 25] LABEL_167：sub_5384F0（0x470 对象）—— 2001-2012 与 2010-2012 共用 ──
LABEL_167:
      if ( operator new(0x470u) != nullptr )
        return (uint32_t *)sub_5384F0(Block, pArg2);
      return nullptr;
    }
    // ── [段 26] Block > 20013：21001-23006 段（召唤师/枪手/邪眼机关系） ──
    if ( Block > 20013 )
    {
      if ( Block > 21001 )
      {
        if ( Block > 22015 )
        {
          if ( Block > 22210 )
          {
            switch ( Block )
            {
              // ── [段 27] 23001-23006：CNDecoy 替身族 —— 23001 单型、23002-23006 走 sub_533130(4/0/1/2/3) 六档 ──
              case 23001:
                if ( operator new(0x3D8u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533050(Block, pArg2);
                break;
              case 23002:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, pArg2, 4);
                break;
              case 23003:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, pArg2, 0);
                break;
              case 23004:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, pArg2, 1);
                break;
              case 23005:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, pArg2, 2);
                break;
              case 23006:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, pArg2, 3);
                break;
              default:
                goto LABEL_494;
            }
          }
          else
          {
            // ── [段 28] 22210+22200-22209 段：CNFireExplosion(22210) / sub_532330(5 连) / sub_532AC0(2) / sub_532BA0
            if ( Block == 22210 )
            {
              if ( operator new(0x3E4u) != nullptr )
                return (uint32_t *)sub_52F2C0(22210, pArg2);
              return nullptr;
            }
            switch ( Block )
            {
              case 22016:
                if ( operator new(0x3D0u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_532440(Block, pArg2);
                break;
              case 22017:
                if ( operator new(0x3E0u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_5326C0(Block, pArg2);
                break;
              case 22200:
              case 22201:
              case 22202:
              case 22203:
              case 22204:
                if ( sub_52E440(1012) == 0 )
                  return nullptr;
                result = (uint32_t *)sub_532330(Block, pArg2);
                break;
              case 22205:
              case 22206:
                if ( operator new(0x3D4u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_532AC0(Block, pArg2);
                break;
              case 22207:
                if ( operator new(0x3ECu) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_532BA0(Block, pArg2);
                break;
              case 22208:
                goto LABEL_519;
              //   22208 → LABEL_519 CNFireExplosion / 22209 CNNapalmBomb(0x42C)
              case 22209:
                if ( operator new(0x42Cu) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_5343B0(Block, pArg2);
                break;
              default:
                goto LABEL_494;
            }
          }
        }
        else
        {
          // ── [段 29] 22001-22016 段：CNGunnerBullet（22001-22015 经惰性表 sub_52E3B0(1040) 门）… / 22016 CNExsViperBullet
          if ( Block >= 22001 )
          {
            if ( sub_52E3B0(1040) != 0 )
              return (uint32_t *)sub_532250(Block, pArg2);
            return nullptr;
          }
          //   21002-21015 段：CNEnergyBall(21002 吃 float)/CNEnergyBallSub/CNThrowSand/CNRoarStun/CNEnergyField…
          switch ( Block )
          {
            case 21002:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5315E0(Block, *(float *)&pArg2);
              break;
            case 21003:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5316C0(Block, pArg2);
              break;
            case 21004:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_531810(Block, pArg2);
              break;
            case 21005:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5318F0(Block, pArg2);
              break;
            case 21006:
              if ( operator new(0x3E4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_531A80(Block, pArg2);
              break;
            case 21007:
              if ( operator new(0x3ECu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_532010(Block, pArg2);
              break;
            //   21008 → LABEL_229 sub_531500=CNSuplexSub；21010/21011 走 float 参数构造
            case 21008:
              goto LABEL_229;
            case 21009:
              if ( operator new(0x3DCu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_532120(Block, pArg2);
              break;
            case 21010:
              if ( operator new(0x3FCu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_532760(Block, *(float *)&pArg2);
              break;
            case 21011:
              if ( operator new(0x3D4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_52F4D0(Block, pArg2, 1);
              break;
            case 21014:
              if ( operator new(0x3E4u) != nullptr )
                return (uint32_t *)sub_52F2C0(Block, pArg2);
              return nullptr;
            case 21015:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5336C0(Block, pArg2);
              break;
            default:
              goto LABEL_494;
          }
        }
      }
      else
      {
        // ── [段 30] 21001：LABEL_229 sub_531500=CNSuplexSub ──
        if ( Block == 21001 )
        {
LABEL_229:
          if ( operator new(0x3DCu) != nullptr )
            return (uint32_t *)sub_531500(Block, pArg2);
          return nullptr;
        }
        // ── [段 31] Block 处于 (20013, 21001)：20014-20019 六型 ──
        //   20014 CNTombStoneRain / 20015 CNTombStone / 20016+20019 走 float / 20017 CNGrabBlastBlood / 20018 WAVE_CANCLE
        switch ( Block )
        {
          case 20014:
            if ( operator new(0x3E0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532900(Block, pArg2);
            break;
          case 20015:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_5329E0(Block, pArg2);
            break;
          case 20016:
            if ( operator new(0x3D4u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532CD0(Block, *(float *)&pArg2);
            break;
          case 20017:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532DB0(Block, pArg2);
            break;
          case 20018:
            if ( operator new(0x3CCu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532E90(Block, pArg2);
            break;
          case 20019:
            if ( operator new(0x3D8u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532F70(Block, *(float *)&pArg2);
            break;
          default:
            goto LABEL_494;
        }
      }
      return result;
    }
    // ── [段 32] Block == 20013：sub_531DB0(41) = CNGhost(41)（鬼魂 PO，41 为分型） ──
    if ( Block == 20013 )
    {
      if ( operator new(0x41Cu) != nullptr )
        return (uint32_t *)sub_531DB0(20013, pArg2, 41);
      return nullptr;
    }
    // ── [段 33] Block 处于 (4202, 20013)：4613 以上/4610/4412/4410 四层阈值分派 ──
    if ( Block > 4202 )
    {
      if ( Block > 4613 )
      {
        // ── [段 34] 20001-20012 段：20001 WAVE_CREATE 音效型 / 20002-20007 CNIceWave(6 连，吃 float) ──
        //   20008 CNFireWave / 20009 CNBlastBlood / 20010 CNBlastBloodSub / 20011 CNGhost(25) / 20012 CNGhost(36)
        switch ( Block )
        {
          case 20001:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_5312C0(Block, pArg2);
            break;
          case 20002:
          case 20003:
          case 20004:
          case 20005:
          case 20006:
          case 20007:
            if ( operator new(0x3E0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531420(Block, *(float *)&pArg2);
            break;
          case 20008:
            if ( operator new(0x3E8u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531F30(Block, pArg2);
            break;
          case 20009:
            if ( operator new(0x3E8u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531B90(Block, pArg2);
            break;
          case 20010:
            if ( operator new(0x3E0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531CA0(Block, pArg2);
            break;
          case 20011:
            if ( operator new(0x41Cu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531DB0(Block, pArg2, 25);
            break;
          case 20012:
            if ( operator new(0x41Cu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531DB0(Block, pArg2, 36);
            break;
          default:
            goto LABEL_494;
        }
        return result;
      }
      if ( Block < 4610 )
      {
        if ( Block > 4412 )
        {
          // ── [段 35] 4500-4602 九连 → LABEL_192 sub_5389C0（同一构造 9 个 ID） ──
          switch ( Block )
          {
            case 4500:
            case 4501:
            case 4502:
            case 4510:
            case 4511:
            case 4512:
            case 4600:
            case 4601:
            case 4602:
              goto LABEL_192;
            default:
              goto LABEL_494;
          }
        }
        if ( Block < 4410 )
        {
          // ── [段 36] 4210-4402 九连：break 穿透（无专属构造，落到段 35 的 LABEL_192） ──
          switch ( Block )
          {
            case 4210:
            case 4211:
            case 4212:
            case 4300:
            case 4301:
            case 4302:
            case 4310:
            case 4311:
            case 4312:
            case 4400:
            case 4401:
            case 4402:
              break;
            default:
              goto LABEL_494;
          }
        }
      }
    }
    else if ( Block < 4200 )
    {
      // ── [段 37] 2400-2412 → LABEL_176 sub_538910（0x470） ──
      if ( Block <= 2412 )
      {
        if ( Block >= 2410 )
        {
LABEL_176:
          if ( operator new(0x470u) != nullptr )
            return (uint32_t *)sub_538910(Block, pArg2);
          return nullptr;
        }
        // ── [段 38] 2300-2312 sub_538700 / 2400-2402 → LABEL_176 ──
        if ( Block > 2212 )
        {
          switch ( Block )
          {
            case 2300:
            case 2301:
            case 2302:
            case 2310:
            case 2311:
            case 2312:
              if ( operator new(0x470u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_538700(Block, pArg2);
              break;
            case 2400:
            case 2401:
            case 2402:
              goto LABEL_176;
            default:
              goto LABEL_494;
          }
        }
        else
        {
          // ── [段 39] 2210-2212 → LABEL_171 sub_538650 ──
          if ( Block >= 2210 )
          {
LABEL_171:
            if ( operator new(0x470u) != nullptr )
              return (uint32_t *)sub_538650(Block, pArg2);
            return nullptr;
          }
          // ── [段 40] 2010-2012 → LABEL_167 / 2100-2112 sub_5385A0 / 2200-2202 → LABEL_171 ──
          switch ( Block )
          {
            case 2010:
            case 2011:
            case 2012:
              goto LABEL_167;
            case 2100:
            case 2101:
            case 2102:
            case 2110:
            case 2111:
            case 2112:
              if ( operator new(0x470u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5385A0(Block, pArg2);
              break;
            case 2200:
            case 2201:
            case 2202:
              goto LABEL_171;
            default:
              goto LABEL_494;
          }
        }
        return result;
      }
      // ── [段 41] 4010-4112 九连 → LABEL_192 ──
      if ( Block > 4002 )
      {
        switch ( Block )
        {
          case 4010:
          case 4011:
          case 4012:
          case 4100:
          case 4101:
          case 4102:
          case 4110:
          case 4111:
          case 4112:
            goto LABEL_192;
          default:
            goto LABEL_494;
        }
      }
      // ── [段 42] 2500-2612 十二连：2500-2512 sub_538860 / 2600-2612 sub_5387B0 ──
      if ( Block < 4000 )
      {
        switch ( Block )
        {
          case 2500:
          case 2501:
          case 2502:
          case 2510:
          case 2511:
          case 2512:
            if ( operator new(0x470u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_538860(Block, pArg2);
            break;
          case 2600:
          case 2601:
          case 2602:
          case 2610:
          case 2611:
          case 2612:
            if ( operator new(0x470u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_5387B0(Block, pArg2);
            break;
          default:
            goto LABEL_494;
        }
        return result;
      }
    }
// ── [段 43] LABEL_192：sub_5389C0（0x3DC）—— 4210-4602 / 4010-4112 / 2500？多组合共用 ──
LABEL_192:
    if ( operator new(0x3DCu) != nullptr )
      return (uint32_t *)sub_5389C0(Block, pArg2);
    return nullptr;
  }
  // ── [段 44] Block == 1041：LABEL_127 sub_5372C0（0x46C） ──
  if ( Block == 1041 )
  {
LABEL_127:
    if ( operator new(0x46Cu) != nullptr )
      return (uint32_t *)sub_5372C0(Block, pArg2);
    return nullptr;
  }
  // ── [段 45] Block > 815：816-1040 段（大技能弹体，0x3CC-0x478） ──
  if ( Block > 815 )
  {
    switch ( Block )
    {
      //   816+831 CNUrn（罐）/ 817-819 三型（0x468-0x46C）
      case 816:
      case 831:
        if ( operator new(0x44Cu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_52EF90(Block, pArg2);
      case 817:
        if ( operator new(0x46Cu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_537BC0(Block, pArg2);
      case 818:
        if ( operator new(0x450u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_537E10(Block, pArg2);
      case 819:
        if ( operator new(0x468u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_537EF0(Block, pArg2);
      //   820-823 → LABEL_125 sub_52EB00=CNRDPooledPassiveObject / 826+834-836+1021 → LABEL_73 sub_52ED60
      case 820:
      case 821:
      case 822:
      case 823:
        goto LABEL_125;
      case 826:
      case 834:
      case 835:
      case 836:
      case 1021:
LABEL_73:
        if ( operator new(0x44Cu) == nullptr )
          goto LABEL_16;
        result = (uint32_t *)sub_52ED60(Block, pArg2);
        goto LABEL_17;
      //   827-828 CNPathGate 传送门两型 / 830 → LABEL_63 sub_52EF60=CNTreasureBox 宝箱 / 832-833 CNEventBarrier 屏障两型
      case 827:
      case 828:
        if ( operator new(0x44Cu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_52F040(Block, pArg2);
      case 830:
        goto LABEL_63;
      case 832:
        if ( operator new(0x478u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_531190(Block, pArg2);
      case 833:
        if ( operator new(0x478u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_531190(Block, pArg2);
      //   1000 → sub_5361D0 / 1001-1005 CNUsableStackable… sub_538B90(0, Block-1001)
      case 1000:
        if ( operator new(0x468u) == nullptr )
          goto LABEL_16;
        result = (uint32_t *)sub_5361D0(Block, pArg2);
        goto LABEL_17;
      case 1001:
      case 1002:
      case 1003:
      case 1004:
      case 1005:
        if ( operator new(0x454u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_538B90(Block, 0, Block - 1001);
      //   1006-1007 CNIceNiddle(CNIceWave) 两型 / 1008-1010 sub_536430(17,2) 三连 / 1011-1013 → LABEL_132
      case 1006:
      case 1007:
        if ( operator new(0x3E0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536350(Block, pArg2);
      case 1008:
      case 1009:
      case 1010:
        if ( operator new(0x478u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536430(Block, pArg2, 17, 2);
      case 1011:
      case 1012:
      case 1013:
        goto LABEL_132;
      //   1014-1036 段：逐 ID 一构造（sub_536590…sub_5377A0）—— 密集区每 ID 5-12 行
      case 1014:
        if ( operator new(0x3CCu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536590(Block, pArg2);
      case 1015:
        if ( operator new(0x46Cu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536630(Block, pArg2);
      case 1016:
        if ( operator new(0x3E8u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536770(Block, pArg2);
      case 1017:
      case 1018:
      case 1019:
LABEL_121:
        if ( operator new(0x3F4u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_535C50(Block, pArg2);
      case 1020:
LABEL_123:
        if ( operator new(0x3F0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_535FC0(Block, pArg2);
      case 1023:
        if ( operator new(0x404u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536930(Block, pArg2);
      case 1024:
        if ( operator new(0x3ECu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536B40(Block, pArg2);
      case 1025:
        if ( operator new(0x3DCu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536C30(Block, pArg2);
      case 1026:
        if ( operator new(0x458u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536D60(Block, pArg2);
      case 1027:
        if ( operator new(0x3CCu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536E00(Block, pArg2);
      case 1028:
        if ( operator new(0x3D4u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536EE0(Block, pArg2);
      case 1029:
        if ( operator new(0x3D0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536F80(Block, pArg2);
      case 1030:
        if ( operator new(0x3E4u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536A60(Block, pArg2);
      case 1031:
        if ( operator new(0x478u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_5364E0(Block, pArg2);
      case 1032:
        if ( operator new(0x3D0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536CC0(Block, pArg2);
      case 1033:
        if ( operator new(0x3DCu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_537020(Block, pArg2);
      case 1034:
        if ( operator new(0x3D0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536CC0(Block, pArg2);
      case 1035:
        if ( operator new(0x44Cu) == nullptr )
          goto LABEL_16;
        result = (uint32_t *)sub_5377A0(Block, pArg2);
        goto LABEL_17;
      //   1036+1040 → LABEL_134 / 1037 → LABEL_127 / 1038 → LABEL_136 / 1039 → LABEL_138
      case 1036:
      case 1040:
        goto LABEL_134;
      case 1037:
        goto LABEL_127;
      case 1038:
        goto LABEL_136;
      case 1039:
        goto LABEL_138;
      default:
        goto LABEL_494;
    }
  }
  // ── [段 46] Block == 815：LABEL_63 sub_52EF60=CNTreasureBox ──
  if ( Block == 815 )
  {
LABEL_63:
    if ( operator new(0x44Cu) != nullptr )
      return (uint32_t *)sub_52EF60(Block, pArg2);
    return nullptr;
  }
  // ── [段 47] Block > 286：735-814 段 ──
  //   735-813 → LABEL_125 CNRDPooledPassiveObject / 770-809 → LABEL_73 CNPassiveObject 底座
  if ( Block > 286 )
  {
    if ( Block > 721 )
    {
      switch ( Block )
      {
        case 735:
        case 736:
        case 737:
        case 801:
        case 810:
        case 811:
        case 812:
        case 813:
          goto LABEL_125;
        case 770:
        case 771:
        case 772:
        case 773:
        case 774:
        case 775:
        case 776:
        case 777:
        case 778:
        case 779:
        case 780:
        case 781:
        case 800:
        case 802:
        case 803:
        case 806:
        case 807:
        case 808:
        case 809:
          goto LABEL_73;
        //   804-805 sub_537D30（0x3CC）/ 814 sub_537AE0
        case 804:
        case 805:
          if ( operator new(0x3CCu) == nullptr )
            goto LABEL_16;
          result = (uint32_t *)sub_537D30(Block, pArg2);
          goto LABEL_17;
        case 814:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_537AE0(Block, pArg2);
        default:
          goto LABEL_494;
      }
    }
    // ── [段 48] Block == 721：sub_537130（0x3CC）──
    if ( Block == 721 )
    {
      if ( operator new(0x3CCu) != nullptr )
        return (uint32_t *)sub_537130(721, pArg2);
      return nullptr;
    }
    // ── [段 49] 291-337 段：291-316 CNRDPooledPassiveObject 二十六连 / 300 → LABEL_73 / 319-330 break 到 53
    if ( Block <= 337 )
    {
      if ( Block < 333 )
      {
        switch ( Block )
        {
          case 291:
          case 292:
          case 293:
          case 294:
          case 295:
          case 296:
          case 301:
          case 302:
          case 303:
          case 304:
          case 305:
          case 306:
          case 307:
          case 308:
          case 309:
          case 310:
          case 311:
          case 312:
          case 313:
          case 314:
          case 315:
          case 316:
            goto LABEL_125;
          case 300:
            goto LABEL_73;
          case 319:
          case 320:
          case 321:
          case 322:
          case 323:
          case 326:
          case 327:
          case 328:
          case 329:
          case 330:
            break;
          default:
            goto LABEL_494;
        }
      }
// ── [段 50] LABEL_53：sub_539140（0x3E8）—— 333-337 / 709-716 / 361-490 多组共用 ──
LABEL_53:
      if ( operator new(0x3E8u) != nullptr )
        return (uint32_t *)sub_539140(Block, pArg2);
      return nullptr;
    }
    // ── [段 51] 702-716 段：702-716 → LABEL_53；716+ → LABEL_53 ──
    if ( Block > 713 )
    {
      if ( Block >= 716 )
        goto LABEL_53;
    }
    else
    {
      if ( Block >= 709 )
        goto LABEL_53;
      if ( Block <= 706 )
      {
        if ( Block >= 702 )
          goto LABEL_53;
        // ── [段 52] 361-490 段：sub_52F0B0=CNPathGate + 回写 +945=1（强制置有效位） ──
        if ( Block >= 361 && Block <= 490 )
        {
          if ( operator new(0x3ECu) != nullptr )
          {
            result = (uint32_t *)sub_52F0B0(Block, pArg2);
            goto LABEL_17;
          }
LABEL_16:
          result = nullptr;
LABEL_17:
          *((uint8_t *)result + 945) = 1;
          return result;
        }
      }
    }
    goto LABEL_494;
  }
  // ── [段 53] Block >= 281：LABEL_125 池化对象路径 —— 先 sub_52E320(972) 惰性池申请再 sub_52EB00 构造 ──
  if ( Block >= 281 )
  {
LABEL_125:
    if ( sub_52E320(972) != 0 )
    {
      result = (uint32_t *)sub_52EB00(Block, pArg2);
      goto LABEL_17;
    }
    goto LABEL_16;
  }
  // ── [段 54] Block <= 250：1-20 基础 PO 段 ──
  if ( Block <= 250 )
  {
    if ( Block < 241 )
    {
      switch ( Block )
      {
        // ── [段 55] 1-20 段：sub_52F5C0=CNParticleFactory（粒子工厂 PO，0x3D8）—— 1-9/13-20 共 17 个 ID ──
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_52F5C0(Block, pArg2);
          break;
        //   221-239 → LABEL_73 / 222 → LABEL_63 / 223-230 sub_538AA0 + 回写 +945=1（八连）
        case 221:
        case 231:
        case 235:
        case 238:
        case 239:
          goto LABEL_73;
        case 222:
          goto LABEL_63;
        case 223:
        case 224:
        case 225:
        case 226:
        case 227:
        case 228:
        case 229:
        case 230:
          if ( operator new(0x44Cu) == nullptr )
            goto LABEL_16;
          result = (uint32_t *)sub_538AA0(Block, pArg2);
          *((uint8_t *)result + 945) = 1;
          break;
        //   236-237 sub_5381D0 / 240 sub_538CA0
        case 236:
        case 237:
          if ( operator new(0x454u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5381D0(Block, pArg2);
          break;
        case 240:
          if ( operator new(0x450u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_538CA0(Block, pArg2);
          break;
        default:
          goto LABEL_494;
      }
      return result;
    // ── [段 56] Block 处于 [241, 250]：sub_52EBF0=CNCutableGrass（可砍草丛 PO，0x40C） ──
    }
    if ( operator new(0x40Cu) != nullptr )
      return (uint32_t *)sub_52EBF0(Block, pArg2);
    return nullptr;
  }
  // ── [段 57] Block 处于 (250, 281)：258-276 段（小 PO 收尾） ──
  //   258 sub_536850 / 261 CNToothKurokuta / 262-264 → LABEL_121 / 265-266 CNEarthFire 两型（1500ms）」
  switch ( Block )
  {
    case 258:
      if ( operator new(0x3D8u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_536850(Block, pArg2);
      break;
    case 261:
      if ( operator new(0x3F0u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_535AD0(Block, pArg2);
      break;
    case 262:
    case 263:
    case 264:
      goto LABEL_121;
    case 265:
      if ( operator new(0x3F0u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_52FAD0(Block, 3, 1500, 0, 0);
      break;
    //   267-268 双型 / 269 → LABEL_123 / 270 sub_5360F0 / 271-276 → LABEL_125 池化
    case 266:
      if ( operator new(0x3F0u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_52FAD0(Block, 5, 1500, 0, 1);
      break;
    case 267:
      if ( operator new(0x3E0u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_535DB0(Block, pArg2);
      break;
    case 268:
      if ( operator new(0x3E4u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_535E90(Block, pArg2);
      break;
    case 269:
      goto LABEL_123;
    case 270:
      if ( operator new(0x3E8u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_5360F0(Block, pArg2);
      break;
    case 271:
    case 272:
    case 273:
    case 274:
    case 275:
    case 276:
      goto LABEL_125;
    default:
      goto LABEL_494;
  }
  return result;
}

