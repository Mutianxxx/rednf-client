// ============================================================
// 【40JP逆向源代码工程】src/game/bigfunc_4ABE10_sub_4ABE10.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x4ABE10）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x4ABE10 sub_4ABE10  size=10050
// ------------------------------------------------------------
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

  if ( Block <= 200 )
  {
    if ( Block != 200 )
    {
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
    if ( operator new(0x21CCu) != nullptr )
      return sub_4A8D60(200, (int)a2);
    return 0;
  }
  if ( Block <= 904 )
  {
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
      if ( Block == 406 )
      {
        v10 = operator new(0x21ECu);
        if ( v10 != nullptr )
          return sub_58E1D0((int)v10, 150, (int)a2, 1);
        return 0;
      }
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
  if ( Block <= 50007 )
  {
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
  if ( Block > 50023 )
  {
    if ( Block > 50068 )
    {
      if ( Block > 60005 )
      {
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

