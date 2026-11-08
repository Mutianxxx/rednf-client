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
uint32_t */*cdecl*/ sub_53A220(int Block, void *a2)
{
  uint32_t *result; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // edi

  if ( Block > 23007 )
  {
    if ( Block <= 30003 )
    {
      if ( Block == 30003 )
      {
        if ( operator new(0x3D0u) != nullptr )
          return (uint32_t *)sub_534660(30003, a2);
        return nullptr;
      }
      switch ( Block )
      {
        case 23008:
          if ( operator new(0x3E8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_533300(Block, a2);
          break;
        case 23009:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5333E0(Block, a2);
          break;
        case 23010:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5334C0(Block, a2);
          break;
        case 23011:
          if ( operator new(0x3F4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5337D0(Block, a2);
          break;
        case 23012:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5338B0(Block, a2);
          break;
        case 23013:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_533C10(Block, a2);
          break;
        case 23014:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_533CF0(Block, a2);
          break;
        case 23015:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_533DD0(Block, a2);
          break;
        case 23016:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, a2);
          return nullptr;
        case 23017:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5340A0(Block, a2);
          break;
        case 23018:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_534580(Block, a2);
          break;
        case 23019:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_52F4D0(Block, a2, 3);
          break;
        default:
          goto LABEL_494;
      }
      return result;
    }
    if ( Block <= 30100 )
    {
      if ( Block == 30100 )
      {
        if ( operator new(0x3D0u) != nullptr )
          return (uint32_t *)sub_535600(30100, a2);
        return nullptr;
      }
      switch ( Block )
      {
        case 30004:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534700(Block, a2);
        case 30005:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5347A0(Block, a2);
        case 30006:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534840(Block, 30008);
        case 30008:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, a2);
          return nullptr;
        case 30009:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534BC0(Block, a2);
        case 30010:
        case 30011:
          if ( operator new(0x3F8u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534A90(Block, a2);
        case 30012:
          if ( operator new(0x3F8u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534AF0(Block, a2);
        case 30013:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534990(Block, a2);
        case 30015:
        case 30036:
          goto LABEL_527;
        case 30016:
        case 30017:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534660(Block, a2);
        case 30018:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534FA0(Block, a2);
        case 30019:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534840(Block, 30020);
        case 30020:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, a2);
          return nullptr;
        case 30021:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_530040(Block, a2);
          return nullptr;
        case 30022:
          if ( operator new(0x3CCu) != nullptr )
            goto LABEL_346;
          return nullptr;
        case 30023:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534840(Block, 30024);
        case 30024:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, a2);
          return nullptr;
        case 30025:
          if ( operator new(0x3D0u) != nullptr )
            return (uint32_t *)sub_534C60(Block, a2);
          return nullptr;
        case 30026:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534D40(Block, a2);
        case 30028:
          if ( operator new(0x400u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534F40(Block, a2);
        case 30029:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534EB0(Block, a2);
        case 30030:
        case 30031:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_535010(Block, a2);
        case 30032:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, a2);
          return nullptr;
        case 30033:
          v3 = operator new(0x3CCu);
          if ( v3 == nullptr )
            return nullptr;
          return sub_52EA60(v3, Block, (int)a2);
        case 30034:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5352D0(Block, a2, 30035, 0);
        case 30035:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, a2);
          return nullptr;
        case 30037:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5352D0(Block, a2, 30046, 5);
        case 30038:
        case 30039:
        case 30040:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5351F0(Block, a2);
        case 30043:
          if ( operator new(0x3D4u) != nullptr )
            goto LABEL_370;
          return nullptr;
        case 30044:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, a2);
          return nullptr;
        case 30045:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, a2);
          return nullptr;
        case 30046:
          goto LABEL_503;
        case 30047:
        case 30049:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F1E0(Block, a2);
        case 30048:
        case 30050:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
          goto LABEL_378;
        case 30051:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
          goto LABEL_378;
        case 30052:
          if ( operator new(0x3F0u) != nullptr )
            goto LABEL_382;
          return nullptr;
        case 30053:
        case 30054:
          if ( operator new(0x3E0u) != nullptr )
            goto LABEL_384;
          return nullptr;
        case 30055:
        case 30056:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, a2);
          return nullptr;
        case 30057:
        case 30058:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_52F3F0(Block, a2);
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
            return (uint32_t *)sub_52FA30(Block, a2);
          return nullptr;
        case 30064:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, a2);
          return nullptr;
        case 30065:
          if ( operator new(0x3D4u) != nullptr )
            goto LABEL_506;
          return nullptr;
        case 30066:
          if ( operator new(0x3D8u) != nullptr )
            goto LABEL_568;
          return nullptr;
        case 30067:
          goto LABEL_569;
        case 30068:
        case 30069:
          if ( operator new(0x3D0u) != nullptr )
            return (uint32_t *)sub_5301D0(Block, a2);
          return nullptr;
        case 30070:
        case 30071:
        case 30072:
        case 30073:
        case 30074:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F4D0(Block, a2, 0);
        case 30077:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_534840(Block, 30078);
        case 30078:
          if ( operator new(0x3D4u) != nullptr )
            return (uint32_t *)sub_5348A0(Block, a2);
          return nullptr;
        case 30080:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5353D0(Block, a2);
        case 30081:
          if ( operator new(0x3ECu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_535450(Block, a2);
        case 30084:
          if ( operator new(0x3E8u) != nullptr )
            goto LABEL_537;
          return nullptr;
        case 30085:
        case 30086:
        case 30087:
        case 30088:
          if ( operator new(0x3CCu) != nullptr )
            return (uint32_t *)sub_52FA30(Block, a2);
          return nullptr;
        case 30089:
        case 30095:
          if ( operator new(0x434u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_535520(Block, a2);
        case 30090:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_535560(Block, a2);
        case 30091:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
LABEL_378:
          result = (uint32_t *)sub_52FAD0(Block, a2, 500, 1, 0);
          break;
        case 30092:
        case 30093:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_61E4C0(Block, a2);
          break;
        case 30094:
          goto LABEL_490;
        default:
          goto LABEL_494;
      }
      return result;
    }
    if ( Block <= 48008 )
    {
      if ( Block >= 48005 )
      {
        if ( operator new(0x3CCu) == nullptr )
          return nullptr;
      }
      else
      {
        if ( Block > 30368 )
        {
          if ( Block > 42002 )
          {
            if ( Block > 46003 )
            {
              switch ( Block )
              {
                case 48001:
                  if ( operator new(0x3E0u) == nullptr )
                    return nullptr;
                  result = (uint32_t *)sub_52F6A0(Block, a2);
                  break;
                case 48002:
                  if ( operator new(0x3E0u) == nullptr )
                    return nullptr;
LABEL_384:
                  result = (uint32_t *)sub_52F780(Block, a2);
                  break;
                case 48003:
                  if ( operator new(0x3DCu) == nullptr )
                    return nullptr;
                  result = (uint32_t *)sub_52F860(Block, a2, 0);
                  break;
                case 48004:
                  if ( operator new(0x3E8u) == nullptr )
                    return nullptr;
LABEL_537:
                  result = (uint32_t *)sub_52F950(Block, a2);
                  break;
                default:
                  goto LABEL_494;
              }
              return result;
            }
            if ( Block == 46003 )
            {
LABEL_527:
              if ( operator new(0x3D8u) != nullptr )
                return (uint32_t *)sub_534B20(Block, a2);
              return nullptr;
            }
            if ( Block > 44001 )
            {
              if ( Block == 46001 )
              {
                if ( operator new(0x3D4u) != nullptr )
                  return (uint32_t *)sub_52F4D0(46001, a2, 0);
                return nullptr;
              }
              if ( Block == 46002 )
              {
                if ( operator new(0x3CCu) != nullptr )
                  return (uint32_t *)sub_530500(46002, a2);
                return nullptr;
              }
              goto LABEL_494;
            }
            if ( Block != 44001 )
            {
              if ( Block <= 42006 )
              {
LABEL_545:
                if ( operator new(0x3CCu) != nullptr )
                  return (uint32_t *)sub_530500(Block, a2);
                return nullptr;
              }
              if ( Block == 42007 )
              {
                if ( operator new(0x3FCu) != nullptr )
                  return (uint32_t *)sub_531060(42007, a2);
                return nullptr;
              }
              goto LABEL_494;
            }
          }
          else
          {
            if ( Block >= 42001 )
            {
              if ( operator new(0x3D4u) != nullptr )
                return (uint32_t *)sub_52F3F0(Block, a2);
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
                  result = (uint32_t *)sub_52FAD0(Block, a2, 500, 1, 1);
                  break;
                case 40007:
                  if ( operator new(0x3D4u) == nullptr )
                    return nullptr;
LABEL_506:
                  result = (uint32_t *)sub_530270(Block, a2);
                  break;
                case 40008:
                  if ( operator new(0x3E8u) == nullptr )
                    return nullptr;
                  result = (uint32_t *)sub_52FCA0(Block, a2, 1);
                  break;
                default:
                  goto LABEL_494;
              }
              return result;
            }
            if ( Block == 40003 )
            {
              if ( operator new(0x3F0u) != nullptr )
                return (uint32_t *)sub_52FAD0(40003, a2, 500, 1, 0);
              return nullptr;
            }
            if ( Block <= 30380 )
            {
              switch ( Block )
              {
                case 30380:
LABEL_490:
                  if ( operator new(0x3D0u) != nullptr )
                    return (uint32_t *)sub_534C60(Block, a2);
                  return nullptr;
                case 30370:
                  if ( operator new(0x3D0u) != nullptr )
                    return (uint32_t *)sub_534840(30370, 30371);
                  return nullptr;
                case 30371:
                  if ( operator new(0x3D4u) != nullptr )
                    return (uint32_t *)sub_5348A0(30371, a2);
                  return nullptr;
                default:
                  break;
              }
              goto LABEL_494;
            }
            if ( Block == 40001 )
            {
              if ( operator new(0x3D8u) != nullptr )
                return (uint32_t *)sub_52F1E0(40001, a2);
              return nullptr;
            }
            if ( Block != 40002 )
              goto LABEL_494;
          }
LABEL_519:
          if ( operator new(0x3E4u) != nullptr )
            return (uint32_t *)sub_52F2C0(Block, a2);
          return nullptr;
        }
        if ( Block < 30365 )
        {
          switch ( Block )
          {
            case 30200:
              if ( operator new(0x3F8u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_535670(Block, a2);
              break;
            case 30201:
              if ( operator new(0x3CCu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_535850(Block, a2);
              break;
            case 30202:
              goto LABEL_563;
            case 30300:
              if ( operator new(0x3F4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5358C0(Block, a2);
              break;
            case 30301:
              if ( operator new(0x3D8u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_61F7D0(Block, a2);
              break;
            case 30302:
              if ( operator new(0x3CCu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_61F8B0(Block, a2);
              break;
            case 30303:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_61F9F0(Block, a2);
              break;
            case 30304:
              if ( operator new(0x3D8u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5359F0(Block, a2);
              break;
            case 30305:
              if ( operator new(0x3D8u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_61FAD0(Block, a2);
              break;
            case 30310:
              if ( operator new(0x460u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_530E30(Block, a2);
              break;
            case 30311:
              if ( operator new(0x3D4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_52F4D0(Block, a2, 2);
              break;
            case 30312:
              if ( operator new(0x3CCu) != nullptr )
                return (uint32_t *)sub_530500(Block, a2);
              return nullptr;
            case 30320:
              if ( operator new(0x3E4u) != nullptr )
                return (uint32_t *)sub_52F2C0(Block, a2);
              return nullptr;
            case 30321:
              if ( operator new(0x3D4u) != nullptr )
                goto LABEL_506;
              return nullptr;
            case 30322:
              if ( operator new(0x3F0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_53A1B0(Block, a2);
              break;
            case 30323:
              if ( operator new(0x3D4u) != nullptr )
                return (uint32_t *)sub_530040(Block, a2);
              return nullptr;
            case 30350:
              if ( operator new(0x3ECu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_539520(Block, a2);
              break;
            case 30351:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_539650(Block, a2);
              break;
            case 30360:
              if ( operator new(0x3D4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5397C0(Block, *(float *)&a2);
              break;
            case 30361:
              if ( operator new(0x3E4u) != nullptr )
                return (uint32_t *)sub_52F2C0(Block, a2);
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
        if ( operator new(0x3CCu) == nullptr )
          return nullptr;
      }
      return (uint32_t *)sub_52FA30(Block, a2);
    }
    if ( Block <= 48043 )
    {
      if ( Block == 48043 )
      {
        if ( operator new(0x3D8u) != nullptr )
          return (uint32_t *)sub_5390B0(48043, a2, 2);
        return nullptr;
      }
      switch ( Block )
      {
        case 48009:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5301D0(Block, a2);
        case 48010:
        case 48014:
          if ( operator new(0x3D0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_530350(Block, a2);
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
        case 48012:
          if ( operator new(0x444u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_530430(Block, a2);
        case 48013:
          if ( operator new(0x3FCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_5305E0(Block, a2);
        case 48015:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_530710(Block, a2, 0);
        case 48016:
          if ( operator new(0x3E4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_538D90(Block, a2, 1);
        case 48017:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_538F70(Block, a2, 1);
        case 48018:
          if ( operator new(0x3E4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_538EB0(Block, a2, 1);
        case 48019:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F860(Block, a2, 1);
        case 48020:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F860(Block, a2, 2);
        case 48021:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F860(Block, a2, 3);
        case 48022:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          return (uint32_t *)sub_52F860(Block, a2, 4);
        case 48023:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
          goto LABEL_556;
        case 48024:
          if ( operator new(0x3F0u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_530C40(Block, a2);
        case 48025:
          if ( operator new(0x3DCu) == nullptr )
            return nullptr;
LABEL_556:
          result = (uint32_t *)sub_52F860(Block, a2, 5);
          break;
        case 48026:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_539480(Block, a2);
          break;
        case 48027:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5393E0(Block, a2);
          break;
        case 48028:
LABEL_563:
          if ( operator new(0x3F4u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_530D50(Block, a2);
          break;
        case 48029:
          if ( operator new(0x3D8u) != nullptr )
            return (uint32_t *)sub_534B20(Block, a2);
          return nullptr;
        case 48030:
          if ( operator new(0x3D8u) == nullptr )
            return nullptr;
LABEL_568:
          result = (uint32_t *)sub_52FBC0(Block, a2);
          break;
        case 48031:
LABEL_569:
          if ( operator new(0x3E8u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_52FCA0(Block, a2, 0);
          break;
        case 48032:
          if ( operator new(0x3D0u) != nullptr )
            return (uint32_t *)sub_534C60(Block, a2);
          return nullptr;
        default:
          goto LABEL_494;
      }
      return result;
    }
    if ( Block > 50704 )
    {
      if ( Block > 50950 )
      {
        switch ( Block )
        {
          case 51000:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_610960(Block, 51100);
            break;
          case 51100:
            if ( operator new(0x3D4u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_530B50(Block, a2);
            break;
          case 51200:
            if ( operator new(0x3D8u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_539220(Block, a2);
            break;
          case 51201:
            if ( operator new(0x3D4u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_539300(Block, a2);
            break;
          default:
            goto LABEL_494;
        }
      }
      else
      {
        if ( Block == 50950 )
        {
          if ( operator new(0x3CCu) != nullptr )
            return (uint32_t *)sub_530A60(50950, a2);
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
            result = (uint32_t *)sub_5362F0(Block, a2);
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
            result = (uint32_t *)sub_52FD90(Block, a2);
            break;
          case 50806:
          case 50807:
          case 50808:
          case 50809:
          case 50810:
            if ( operator new(0x3DCu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_530010(Block, a2);
            break;
          case 50900:
            if ( operator new(0x3CCu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_530970(Block, a2);
            break;
          default:
            goto LABEL_494;
        }
      }
      return result;
    }
    if ( Block >= 50700 )
    {
      if ( operator new(0x3D4u) != nullptr )
        return (uint32_t *)sub_530040(Block, a2);
      return nullptr;
    }
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
            return (uint32_t *)sub_530040(Block, a2);
          return nullptr;
        case 50590:
          if ( operator new(0x3CCu) == nullptr )
            return nullptr;
LABEL_346:
          result = (uint32_t *)sub_530130(Block, a2);
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
    if ( Block >= 50400 )
    {
      if ( operator new(0x3D8u) != nullptr )
        return (uint32_t *)sub_52FF20(Block, a2);
      return nullptr;
    }
    if ( Block <= 50204 )
    {
      if ( Block >= 50200 )
      {
        if ( operator new(0x3D4u) != nullptr )
          return (uint32_t *)sub_5348A0(Block, a2);
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
          result = (uint32_t *)sub_530800(Block, a2);
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
    if ( Block >= 50300 && Block <= 50305 )
    {
      if ( operator new(0x3D8u) != nullptr )
        return (uint32_t *)sub_52FE30(Block, a2);
      return nullptr;
    }
LABEL_494:
    v4 = (uint32_t *)sub_52E320(972);
    v5 = v4;
    if ( v4 != nullptr )
    {
      sub_52EA60(v4, Block, (int)a2);
      *v5 = &CNRDPooledPassiveObject::`vftable';
      return v5;
    }
    return nullptr;
  }
  if ( Block == 23007 )
  {
    if ( operator new(0x3D4u) != nullptr )
      return (uint32_t *)sub_533220(23007, a2);
    return nullptr;
  }
  if ( Block > 1041 )
  {
    if ( Block <= 2002 )
    {
      if ( Block < 2000 )
      {
        switch ( Block )
        {
          case 1042:
LABEL_136:
            if ( operator new(0x460u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537400(Block, a2);
          case 1043:
LABEL_138:
            if ( operator new(0x46Cu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5374E0(Block, a2);
          case 1044:
LABEL_134:
            if ( operator new(0x458u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5371E0(Block, a2);
          case 1045:
            if ( operator new(0x46Cu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5375C0(Block, a2);
          case 1046:
            if ( operator new(0x464u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5376C0(Block, a2);
          case 1047:
            if ( operator new(0x46Cu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537730(Block, a2);
          case 1049:
LABEL_132:
            if ( operator new(0x478u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_536430(Block, a2, 2, 3);
          case 1050:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537840(Block, a2);
          case 1051:
            if ( operator new(0x3DCu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537920(Block, a2);
          case 1053:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_537A00(Block, a2);
          case 1054:
            if ( operator new(0x454u) == nullptr )
              goto LABEL_16;
            result = (uint32_t *)sub_537FD0(Block, a2);
            goto LABEL_17;
          case 1055:
            if ( operator new(0x46Cu) == nullptr )
              return nullptr;
            return (uint32_t *)sub_5380B0(Block, a2);
          case 1056:
            if ( operator new(0x478u) == nullptr )
              return nullptr;
            return (uint32_t *)sub_536510(Block, a2, 9, 8);
          default:
            goto LABEL_494;
        }
      }
LABEL_167:
      if ( operator new(0x470u) != nullptr )
        return (uint32_t *)sub_5384F0(Block, a2);
      return nullptr;
    }
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
              case 23001:
                if ( operator new(0x3D8u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533050(Block, a2);
                break;
              case 23002:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, a2, 4);
                break;
              case 23003:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, a2, 0);
                break;
              case 23004:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, a2, 1);
                break;
              case 23005:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, a2, 2);
                break;
              case 23006:
                if ( operator new(0x418u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_533130(Block, a2, 3);
                break;
              default:
                goto LABEL_494;
            }
          }
          else
          {
            if ( Block == 22210 )
            {
              if ( operator new(0x3E4u) != nullptr )
                return (uint32_t *)sub_52F2C0(22210, a2);
              return nullptr;
            }
            switch ( Block )
            {
              case 22016:
                if ( operator new(0x3D0u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_532440(Block, a2);
                break;
              case 22017:
                if ( operator new(0x3E0u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_5326C0(Block, a2);
                break;
              case 22200:
              case 22201:
              case 22202:
              case 22203:
              case 22204:
                if ( sub_52E440(1012) == 0 )
                  return nullptr;
                result = (uint32_t *)sub_532330(Block, a2);
                break;
              case 22205:
              case 22206:
                if ( operator new(0x3D4u) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_532AC0(Block, a2);
                break;
              case 22207:
                if ( operator new(0x3ECu) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_532BA0(Block, a2);
                break;
              case 22208:
                goto LABEL_519;
              case 22209:
                if ( operator new(0x42Cu) == nullptr )
                  return nullptr;
                result = (uint32_t *)sub_5343B0(Block, a2);
                break;
              default:
                goto LABEL_494;
            }
          }
        }
        else
        {
          if ( Block >= 22001 )
          {
            if ( sub_52E3B0(1040) != 0 )
              return (uint32_t *)sub_532250(Block, a2);
            return nullptr;
          }
          switch ( Block )
          {
            case 21002:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5315E0(Block, *(float *)&a2);
              break;
            case 21003:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5316C0(Block, a2);
              break;
            case 21004:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_531810(Block, a2);
              break;
            case 21005:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5318F0(Block, a2);
              break;
            case 21006:
              if ( operator new(0x3E4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_531A80(Block, a2);
              break;
            case 21007:
              if ( operator new(0x3ECu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_532010(Block, a2);
              break;
            case 21008:
              goto LABEL_229;
            case 21009:
              if ( operator new(0x3DCu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_532120(Block, a2);
              break;
            case 21010:
              if ( operator new(0x3FCu) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_532760(Block, *(float *)&a2);
              break;
            case 21011:
              if ( operator new(0x3D4u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_52F4D0(Block, a2, 1);
              break;
            case 21014:
              if ( operator new(0x3E4u) != nullptr )
                return (uint32_t *)sub_52F2C0(Block, a2);
              return nullptr;
            case 21015:
              if ( operator new(0x3D0u) == nullptr )
                return nullptr;
              result = (uint32_t *)sub_5336C0(Block, a2);
              break;
            default:
              goto LABEL_494;
          }
        }
      }
      else
      {
        if ( Block == 21001 )
        {
LABEL_229:
          if ( operator new(0x3DCu) != nullptr )
            return (uint32_t *)sub_531500(Block, a2);
          return nullptr;
        }
        switch ( Block )
        {
          case 20014:
            if ( operator new(0x3E0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532900(Block, a2);
            break;
          case 20015:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_5329E0(Block, a2);
            break;
          case 20016:
            if ( operator new(0x3D4u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532CD0(Block, *(float *)&a2);
            break;
          case 20017:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532DB0(Block, a2);
            break;
          case 20018:
            if ( operator new(0x3CCu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532E90(Block, a2);
            break;
          case 20019:
            if ( operator new(0x3D8u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_532F70(Block, *(float *)&a2);
            break;
          default:
            goto LABEL_494;
        }
      }
      return result;
    }
    if ( Block == 20013 )
    {
      if ( operator new(0x41Cu) != nullptr )
        return (uint32_t *)sub_531DB0(20013, a2, 41);
      return nullptr;
    }
    if ( Block > 4202 )
    {
      if ( Block > 4613 )
      {
        switch ( Block )
        {
          case 20001:
            if ( operator new(0x3D0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_5312C0(Block, a2);
            break;
          case 20002:
          case 20003:
          case 20004:
          case 20005:
          case 20006:
          case 20007:
            if ( operator new(0x3E0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531420(Block, *(float *)&a2);
            break;
          case 20008:
            if ( operator new(0x3E8u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531F30(Block, a2);
            break;
          case 20009:
            if ( operator new(0x3E8u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531B90(Block, a2);
            break;
          case 20010:
            if ( operator new(0x3E0u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531CA0(Block, a2);
            break;
          case 20011:
            if ( operator new(0x41Cu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531DB0(Block, a2, 25);
            break;
          case 20012:
            if ( operator new(0x41Cu) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_531DB0(Block, a2, 36);
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
      if ( Block <= 2412 )
      {
        if ( Block >= 2410 )
        {
LABEL_176:
          if ( operator new(0x470u) != nullptr )
            return (uint32_t *)sub_538910(Block, a2);
          return nullptr;
        }
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
              result = (uint32_t *)sub_538700(Block, a2);
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
          if ( Block >= 2210 )
          {
LABEL_171:
            if ( operator new(0x470u) != nullptr )
              return (uint32_t *)sub_538650(Block, a2);
            return nullptr;
          }
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
              result = (uint32_t *)sub_5385A0(Block, a2);
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
            result = (uint32_t *)sub_538860(Block, a2);
            break;
          case 2600:
          case 2601:
          case 2602:
          case 2610:
          case 2611:
          case 2612:
            if ( operator new(0x470u) == nullptr )
              return nullptr;
            result = (uint32_t *)sub_5387B0(Block, a2);
            break;
          default:
            goto LABEL_494;
        }
        return result;
      }
    }
LABEL_192:
    if ( operator new(0x3DCu) != nullptr )
      return (uint32_t *)sub_5389C0(Block, a2);
    return nullptr;
  }
  if ( Block == 1041 )
  {
LABEL_127:
    if ( operator new(0x46Cu) != nullptr )
      return (uint32_t *)sub_5372C0(Block, a2);
    return nullptr;
  }
  if ( Block > 815 )
  {
    switch ( Block )
    {
      case 816:
      case 831:
        if ( operator new(0x44Cu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_52EF90(Block, a2);
      case 817:
        if ( operator new(0x46Cu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_537BC0(Block, a2);
      case 818:
        if ( operator new(0x450u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_537E10(Block, a2);
      case 819:
        if ( operator new(0x468u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_537EF0(Block, a2);
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
        result = (uint32_t *)sub_52ED60(Block, a2);
        goto LABEL_17;
      case 827:
      case 828:
        if ( operator new(0x44Cu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_52F040(Block, a2);
      case 830:
        goto LABEL_63;
      case 832:
        if ( operator new(0x478u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_531190(Block, a2);
      case 833:
        if ( operator new(0x478u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_531190(Block, a2);
      case 1000:
        if ( operator new(0x468u) == nullptr )
          goto LABEL_16;
        result = (uint32_t *)sub_5361D0(Block, a2);
        goto LABEL_17;
      case 1001:
      case 1002:
      case 1003:
      case 1004:
      case 1005:
        if ( operator new(0x454u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_538B90(Block, 0, Block - 1001);
      case 1006:
      case 1007:
        if ( operator new(0x3E0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536350(Block, a2);
      case 1008:
      case 1009:
      case 1010:
        if ( operator new(0x478u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536430(Block, a2, 17, 2);
      case 1011:
      case 1012:
      case 1013:
        goto LABEL_132;
      case 1014:
        if ( operator new(0x3CCu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536590(Block, a2);
      case 1015:
        if ( operator new(0x46Cu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536630(Block, a2);
      case 1016:
        if ( operator new(0x3E8u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536770(Block, a2);
      case 1017:
      case 1018:
      case 1019:
LABEL_121:
        if ( operator new(0x3F4u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_535C50(Block, a2);
      case 1020:
LABEL_123:
        if ( operator new(0x3F0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_535FC0(Block, a2);
      case 1023:
        if ( operator new(0x404u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536930(Block, a2);
      case 1024:
        if ( operator new(0x3ECu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536B40(Block, a2);
      case 1025:
        if ( operator new(0x3DCu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536C30(Block, a2);
      case 1026:
        if ( operator new(0x458u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536D60(Block, a2);
      case 1027:
        if ( operator new(0x3CCu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536E00(Block, a2);
      case 1028:
        if ( operator new(0x3D4u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536EE0(Block, a2);
      case 1029:
        if ( operator new(0x3D0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536F80(Block, a2);
      case 1030:
        if ( operator new(0x3E4u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536A60(Block, a2);
      case 1031:
        if ( operator new(0x478u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_5364E0(Block, a2);
      case 1032:
        if ( operator new(0x3D0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536CC0(Block, a2);
      case 1033:
        if ( operator new(0x3DCu) == nullptr )
          return nullptr;
        return (uint32_t *)sub_537020(Block, a2);
      case 1034:
        if ( operator new(0x3D0u) == nullptr )
          return nullptr;
        return (uint32_t *)sub_536CC0(Block, a2);
      case 1035:
        if ( operator new(0x44Cu) == nullptr )
          goto LABEL_16;
        result = (uint32_t *)sub_5377A0(Block, a2);
        goto LABEL_17;
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
  if ( Block == 815 )
  {
LABEL_63:
    if ( operator new(0x44Cu) != nullptr )
      return (uint32_t *)sub_52EF60(Block, a2);
    return nullptr;
  }
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
        case 804:
        case 805:
          if ( operator new(0x3CCu) == nullptr )
            goto LABEL_16;
          result = (uint32_t *)sub_537D30(Block, a2);
          goto LABEL_17;
        case 814:
          if ( operator new(0x3D4u) == nullptr )
            return nullptr;
          return (uint32_t *)sub_537AE0(Block, a2);
        default:
          goto LABEL_494;
      }
    }
    if ( Block == 721 )
    {
      if ( operator new(0x3CCu) != nullptr )
        return (uint32_t *)sub_537130(721, a2);
      return nullptr;
    }
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
LABEL_53:
      if ( operator new(0x3E8u) != nullptr )
        return (uint32_t *)sub_539140(Block, a2);
      return nullptr;
    }
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
        if ( Block >= 361 && Block <= 490 )
        {
          if ( operator new(0x3ECu) != nullptr )
          {
            result = (uint32_t *)sub_52F0B0(Block, a2);
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
  if ( Block >= 281 )
  {
LABEL_125:
    if ( sub_52E320(972) != 0 )
    {
      result = (uint32_t *)sub_52EB00(Block, a2);
      goto LABEL_17;
    }
    goto LABEL_16;
  }
  if ( Block <= 250 )
  {
    if ( Block < 241 )
    {
      switch ( Block )
      {
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
          result = (uint32_t *)sub_52F5C0(Block, a2);
          break;
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
          result = (uint32_t *)sub_538AA0(Block, a2);
          *((uint8_t *)result + 945) = 1;
          break;
        case 236:
        case 237:
          if ( operator new(0x454u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_5381D0(Block, a2);
          break;
        case 240:
          if ( operator new(0x450u) == nullptr )
            return nullptr;
          result = (uint32_t *)sub_538CA0(Block, a2);
          break;
        default:
          goto LABEL_494;
      }
      return result;
    }
    if ( operator new(0x40Cu) != nullptr )
      return (uint32_t *)sub_52EBF0(Block, a2);
    return nullptr;
  }
  switch ( Block )
  {
    case 258:
      if ( operator new(0x3D8u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_536850(Block, a2);
      break;
    case 261:
      if ( operator new(0x3F0u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_535AD0(Block, a2);
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
    case 266:
      if ( operator new(0x3F0u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_52FAD0(Block, 5, 1500, 0, 1);
      break;
    case 267:
      if ( operator new(0x3E0u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_535DB0(Block, a2);
      break;
    case 268:
      if ( operator new(0x3E4u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_535E90(Block, a2);
      break;
    case 269:
      goto LABEL_123;
    case 270:
      if ( operator new(0x3E8u) == nullptr )
        return nullptr;
      result = (uint32_t *)sub_5360F0(Block, a2);
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

