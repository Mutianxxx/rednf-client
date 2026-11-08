// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_583B90_sub_583B90.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x583B90）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 4518 行；字符串证据 5 条；外调 6 个
//   串: "Age %d isPCRoom %d channelType %d"
//   串: "Error %d"
//   串: "ClearQuestNumber %d"
//   串: "TownIndex %d"
//   串: "CHARACTER_CREATED"
//   调: sub_583B90 sub_404A90 sub_404AD0 sub_6567F0 sub_41D300 sub_45DA30
//   case 分支地图（共 120 处）:
//     L559  case 0x10:
//     L563  case 0x12:
//     L567  case 0x16:
//     L571  case 0x17:
//     L749  case 0x12:
//     L753  case 0x13:
//     L757  case 0x16:
//     L760  case 0x17:
//     L764  case 0x18:
//     L795  case 0x13:
//     L799  case 0x15:
//     L803  case 0x16:
//     L807  case 0x25:
//     L896  case 0x12:
//     L914  case 0x13:
//     L932  case 0x37:
//     L952  case 0x38:
//     L1020  case 0x12:
//     L1038  case 0x13:
//     L1114  case 0x13:
//     L1182  case 0x15:
//     L1186  case 0x13:
//     L1194  case 0xE:
//     L1197  case 0x11:
//     L1314  case 0x11:
//     L1318  case 0x13:
//     L1322  case 0x17:
//     L1469  case 0x11:
//     L1474  case 0x12:
//     L1477  case 0x13:
//     L1483  case 0xE:
//     L1486  case 0x17:
//     L1622  case 0xA:
//     L1626  case 0x11:
//     L1628  case 0x13:
//     L1630  case 0x37:
//     L1713  case 0xA:
//     L1717  case 0x11:
//     L1721  case 0x13:
//     L1788  case 0xA:
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x583B90 sub_583B90  size=27453
// ------------------------------------------------------------
int /*userpurge*/ sub_583B90@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>, unsigned int pArg4, int nArg5)  // （表达式/调用续行）
{
  int v5; // eax
  uint8_t v7; // al
  int *v8; // edx
  int v9; // esi
  int v10; // edi
  int v11; // eax
  bool v12; // bl
  int v13; // eax
  DWORD v14; // ecx
  char *v15; // eax
  char v16; // cl
  int v17; // eax
  int v18; // eax
  char *v19; // eax
  char v20; // cl
  char *v21; // eax
  char v22; // cl
  char *v23; // eax
  char v24; // cl
  int v25; // eax
  int v26; // eax
  char *v27; // eax
  char v28; // cl
  int v29; // eax
  char *v30; // eax
  char v31; // cl
  int v32; // eax
  int v33; // eax
  int v34; // esi
  int v35; // ebx
  int i; // edi
  int v37; // edi
  int v38; // eax
  int *v39; // esi
  int v40; // eax
  int *v41; // esi
  char *v42; // eax
  char v43; // cl
  uint32_t *v44; // esi
  int v45; // eax
  uint32_t *v46; // esi
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int dword_8F85382; // eax
  int v55; // eax
  int v56; // esi
  const char *v57; // eax
  char *v58; // eax
  char v59; // cl
  char *v60; // eax
  char v61; // cl
  char *v62; // eax
  char v63; // cl
  char *v64; // eax
  char v65; // cl
  char *v66; // eax
  char v67; // cl
  char *v68; // eax
  char v69; // cl
  int v70; // esi
  int v71; // esi
  const char *v72; // eax
  uint32_t *v73; // esi
  int v74; // eax
  char *v75; // eax
  char v76; // cl
  char *v77; // eax
  char v78; // cl
  char *v79; // eax
  char v80; // cl
  int v81; // eax
  int v82; // ebx
  uint32_t *v83; // eax
  uint32_t *v84; // esi
  int v85; // eax
  int v86; // ecx
  uint32_t *v87; // edx
  int v88; // ecx
  const char *v89; // eax
  char v90; // al
  int v91; // ecx
  int v92; // edi
  int pObj30; // eax
  int *v94; // eax
  char *v95; // eax
  char v96; // cl
  char v97; // cl
  char *v98; // eax
  char v99; // cl
  char *v100; // eax
  char v101; // cl
  uint32_t *v102; // eax
  uint32_t *v103; // eax
  char *v104; // eax
  char v105; // cl
  int *v106; // esi
  int *v107; // eax
  char *v108; // eax
  char v109; // cl
  int *v110; // eax
  int v111; // eax
  int pObj12; // esi
  int v113; // eax
  bool v114; // zf
  int *v115; // ecx
  char *v116; // eax
  char v117; // cl
  int j; // esi
  int *v119; // esi
  int *v120; // eax
  char *v121; // eax
  char v122; // cl
  int k; // esi
  char *v124; // eax
  char v125; // cl
  int v126; // eax
  uint32_t *v127; // esi
  uint32_t *v128; // edi
  uint32_t *v129; // eax
  char *v130; // eax
  char v131; // cl
  uint32_t *v132; // eax
  int pObj34; // esi
  char v134; // al
  int v135; // edx
  int v136; // eax
  void *v137; // eax
  int dword_99FF082; // esi
  int v139; // eax
  int v140; // eax
  int v141; // eax
  int v142; // edi
  int pObj41; // eax
  int pObj13; // esi
  void *v145; // eax
  int *v146; // eax
  int v147; // eax
  int v148; // eax
  int v149; // eax
  int pObj16; // eax
  int *v151; // esi
  int v152; // eax
  int v153; // edx
  int v154; // eax
  void *v155; // eax
  int pObj3; // eax
  int pObj24; // esi
  unsigned int v158; // edi
  int pObj4; // eax
  int v160; // eax
  int v161; // edi
  int pObj22; // ebx
  int pObj26; // esi
  int v164; // eax
  int v165; // eax
  int v166; // ebx
  int pObj15; // eax
  int pObj8; // esi
  int v169; // eax
  int v170; // edi
  int v171; // eax
  int v172; // eax
  int v173; // eax
  int pObj18; // eax
  int pObj28; // esi
  int v176; // eax
  int pObj31; // eax
  int v178; // eax
  int v179; // eax
  int v180; // eax
  int v181; // edi
  int pObj5; // esi
  int v183; // eax
  int v184; // eax
  int pObj20; // eax
  int v186; // eax
  int v187; // edi
  int pObj19; // esi
  char v189; // al
  int v190; // edx
  int v191; // eax
  int v192; // eax
  void *v193; // eax
  int v194; // eax
  int v195; // eax
  int v196; // eax
  int v197; // eax
  int v198; // eax
  int v199; // eax
  int v200; // eax
  int v201; // edi
  int pObj39; // esi
  char v203; // al
  int v204; // edx
  int v205; // eax
  int v206; // eax
  void *v207; // eax
  int v208; // eax
  int16_t pArg42; // di
  int pObj27; // esi
  int pObj21; // eax
  int pObj9; // esi
  char v213; // al
  int v214; // edx
  int v215; // eax
  void *v216; // eax
  int v217; // eax
  int v218; // eax
  int v219; // eax
  int v220; // eax
  char *v221; // eax
  char v222; // cl
  int v223; // esi
  int v224; // eax
  char v225; // al
  int v226; // eax
  const char *v227; // eax
  const char *v228; // eax
  int pObj; // esi
  uint32_t *v230; // eax
  int v231; // ebx
  int v232; // eax
  int v233; // ebx
  uint32_t *v234; // esi
  int v235; // eax
  const char *v236; // eax
  int pObj40; // ebx
  int v238; // esi
  const char *v239; // eax
  const char *v240; // eax
  const char *v241; // eax
  const char *v242; // eax
  const char *v243; // eax
  const char *v244; // eax
  const char *v245; // eax
  const char *v246; // eax
  int v247; // eax
  const char *v248; // eax
  int v249; // esi
  int v250; // eax
  int v251; // eax
  int v252; // eax
  int v253; // ebx
  int *v254; // esi
  char v255; // al
  int v256; // edx
  int v257; // eax
  int v258; // eax
  int v259; // esi
  const char *v260; // eax
  int v261; // eax
  int v262; // eax
  int v263; // eax
  int v264; // esi
  const char *v265; // eax
  int v266; // eax
  int v267; // ebx
  const char *v268; // eax
  int pObj37; // eax
  int pObj10; // esi
  int v271; // eax
  int pObj17; // eax
  int v273; // eax
  int v274; // ebx
  int v275; // edi
  int pObj14; // esi
  char v277; // al
  int v278; // edx
  int v279; // eax
  int v280; // eax
  void *v281; // eax
  int v282; // esi
  int v283; // eax
  int v284; // eax
  const char *v285; // eax
  int v286; // eax
  int pObj29; // eax
  uint32_t *v288; // esi
  int v289; // eax
  int v290; // ebx
  signed int v291; // edi
  uint8_t *pObj7; // esi
  uint32_t *v293; // esi
  int v294; // eax
  int v295; // esi
  int v296; // edi
  int v297; // ebx
  int v298; // eax
  int pObj23; // eax
  char v300; // cl
  uint32_t *v301; // esi
  int v302; // eax
  int pObj38; // esi
  int pObj2; // eax
  int v305; // eax
  bool v306; // bl
  int v307; // edi
  int v308; // eax
  int v309; // edi
  int v310; // eax
  int v311; // eax
  int v312; // esi
  int m; // esi
  int v314; // eax
  int v315; // esi
  int v316; // eax
  char *v317; // eax
  const char *v318; // eax
  int v319; // eax
  int v320; // eax
  int v321; // eax
  char *v322; // eax
  int v323; // eax
  int v324; // edx
  int v325; // eax
  char *v326; // eax
  uint8_t n; // bl
  char *v328; // eax
  char *v329; // eax
  int v330; // eax
  const char *v331; // edi
  const char *v332; // eax
  int v333; // esi
  int v334; // eax
  int v335; // eax
  int v336; // eax
  int v337; // eax
  int v338; // eax
  int v339; // eax
  uint8_t *v340; // eax
  uint8_t *v341; // esi
  char v342; // al
  int v343; // eax
  int v344; // eax
  int v345; // eax
  int v346; // eax
  int v347; // eax
  int v348; // eax
  char v349; // bl
  int ii; // esi
  int jj; // esi
  char *v352; // eax
  int v353; // eax
  const char *v354; // eax
  int v355; // eax
  int v356; // eax
  int v357; // eax
  int v358; // eax
  int v359; // esi
  char *v360; // eax
  int v361; // eax
  char *v362; // eax
  const char *v363; // eax
  int v364; // eax
  char *v365; // eax
  const char *v366; // eax
  char *v367; // eax
  int v368; // eax
  const char *v369; // eax
  char *v370; // edx
  int v371; // eax
  int v372; // eax
  int v373; // eax
  int v374; // eax
  int v375; // eax
  int v376; // eax
  const char *v377; // eax
  char *v378; // eax
  const char *v379; // eax
  const char *v380; // eax
  int v381; // esi
  int *v382; // ebx
  int v383; // edi
  int pObj36; // eax
  int v385; // eax
  int v386; // eax
  int v387; // eax
  int v388; // eax
  int v389; // eax
  int v390; // eax
  const char *v391; // eax
  int v392; // esi
  int *v393; // ebx
  int pObj11; // eax
  int pObj35; // eax
  int pObj25; // esi
  int v397; // eax
  uint32_t *v398; // eax
  int v399; // edx
  int v400; // edi
  int pObj33; // eax
  int pObj6; // esi
  int v403; // eax
  int v404; // eax
  int pObj32; // eax
  int v406; // ecx
  int v408; // [esp-18h] [ebp-384h]
  int v409; // [esp-18h] [ebp-384h]
  int v410; // [esp-18h] [ebp-384h]
  int v411; // [esp-14h] [ebp-380h]
  int v412; // [esp-10h] [ebp-37Ch]
  int v413; // [esp-10h] [ebp-37Ch]
  uint32_t *v414; // [esp-10h] [ebp-37Ch]
  int v415; // [esp-Ch] [ebp-378h]
  uint32_t *v416; // [esp-Ch] [ebp-378h]
  unsigned int pArg44; // [esp-Ch] [ebp-378h]
  unsigned int pArg43; // [esp-Ch] [ebp-378h]
  int v419; // [esp-Ch] [ebp-378h]
  unsigned int v420; // [esp-Ch] [ebp-378h]
  unsigned int v421; // [esp-Ch] [ebp-378h]
  unsigned int v422; // [esp-Ch] [ebp-378h]
  unsigned int v423; // [esp-Ch] [ebp-378h]
  unsigned int v424; // [esp-Ch] [ebp-378h]
  unsigned int v425; // [esp-Ch] [ebp-378h]
  unsigned int v426; // [esp-Ch] [ebp-378h]
  unsigned int v427; // [esp-Ch] [ebp-378h]
  uint32_t *v428; // [esp-Ch] [ebp-378h]
  uint32_t *v429; // [esp-Ch] [ebp-378h]
  uint32_t *v430; // [esp-Ch] [ebp-378h]
  int v431; // [esp-Ch] [ebp-378h]
  uint32_t *v432; // [esp-Ch] [ebp-378h]
  int v433; // [esp-Ch] [ebp-378h]
  int v434; // [esp-Ch] [ebp-378h]
  int v435; // [esp-Ch] [ebp-378h]
  int v436; // [esp-Ch] [ebp-378h]
  int nArg32; // [esp-8h] [ebp-374h]
  int v438; // [esp+4h] [ebp-368h] BYREF
  int *v439; // [esp+8h] [ebp-364h] BYREF
  char v440[4]; // [esp+Ch] [ebp-360h] BYREF
  unsigned int v441; // [esp+10h] [ebp-35Ch] BYREF
  uint8_t v442; // [esp+17h] [ebp-355h] BYREF
  char ArgList[4]; // [esp+18h] [ebp-354h] BYREF
  unsigned int v444; // [esp+1Ch] [ebp-350h] BYREF
  int v445; // [esp+20h] [ebp-34Ch] BYREF
  char dword_9B0BBC2[4]; // [esp+24h] [ebp-348h] BYREF
  int v447; // [esp+28h] [ebp-344h] BYREF
  char v448[256]; // [esp+2Ch] [ebp-340h] BYREF
  char v449[128]; // [esp+12Ch] [ebp-240h] BYREF
  char v450[128]; // [esp+1ACh] [ebp-1C0h] BYREF
  char Buffer[128]; // [esp+22Ch] [ebp-140h] BYREF
  char v452[64]; // [esp+2ACh] [ebp-C0h] BYREF
  char psz[61]; // [esp+2ECh] [ebp-80h] BYREF
  int16_t v454; // [esp+329h] [ebp-43h]
  char v455; // [esp+32Bh] [ebp-41h]
  char Destination[12]; // [esp+32Ch] [ebp-40h] BYREF
  void *pBuf[5]; // [esp+338h] [ebp-34h] BYREF
  char v458[4]; // [esp+34Ch] [ebp-20h] BYREF
  __time64_t Time; // [esp+350h] [ebp-1Ch] BYREF
  int dword_796E502; // [esp+35Ch] [ebp-10h]
  int v461; // [esp+368h] [ebp-4h]

  // ── [段 1] 入口：v5 = 包体第 2 字节 - 1 = ★ CMDPACKET 类型号 - 1（off_790928 枚举表索引） ──
  //   ★ 本函数 = 服务器对 客户端 CMDPACKET 的回报分发器；与 ·0x57A980（NOTIFY 包分发器）成对
  //   故 case N ↔ docs/24 §一 的 ENUM_CMDPACKET_(N+1)；已逐条对表验证（见各段括注）
  //   pArg1=主管理器、pArg2/pArg4=包体缓冲、nArg5=包长（低字节用作「成功/失败」标志位）
  dword_796E502 = dword_796E50;  // dword_796E502 = dword_796E50（转发）
  v5 = *(uint8_t *)(pArg4 + 1) - 1;  // 入口：包体第 2 字节 - 1 = CMDPACKET 类型号 - 1
  v439 = (int *)pArg1;  // 别名 pArg1 → v439（主管理器指针）
  nArg32 = nArg3;  // nArg32 = nArg3（转发）
  // ── [段 2] ★ case 0..100 主表：回报包全表（共 120 case 标签、~100 实际分支） ──
  switch ( v5 )  // 按包类型号（首字节-1）分派回报处理
  {
    // ── [段 3] case 0 = type 1 ENUM_CMDPACKET_LOGIN（登录回报）──
    //   HIBYTE(nArg5)!=0（登录成功）：读 Age/isPCRoom/channelType → 通道类型折叠到 0..4 写 v439[87]
    //   随后：isSkipCharacterSelect 判定（v9/v10/v11 三字段）+ 场景 5 复位，成功则 sub_45DA30 进选角
    case 0:  // case 0 = 类型 1 ENUM_CMDPACKET_LOGIN（登录回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(v445) = 0;  // 清 v445 高字节（即将读取）
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        sub_404A90((uint8_t *)&v445 + 3);  // 游标读 1 字节 → v445 高位（错误码字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        sub_6567F0(*(int *)dword_9B0BBC2);  // sub_6567F0 —— 会话频道号全局写入口
        off_77F3FC("Age %d isPCRoom %d channelType %d", HIBYTE(v445), HIBYTE(pArg4), HIBYTE(nArg5));  // 日志打印（printf 风格）
        v7 = HIBYTE(nArg5);
        if ( HIBYTE(nArg5) >= 4u )  // nArg5 >= 4u 则截断/分档
        {
          v7 = 4;  // 设文案编号 4，稍后弹窗
          HIBYTE(nArg5) = 4;  // nArg5 高字节置 4
        }
        v8 = v439;  // v8 = v439（转发）
        v439[87] = v7;  // 写数组 v439[87] = v7
        v9 = *(uint32_t *)(dword_8F7A24 + 284);  // 读字段 v9 = (uint32)dword_8F7A24+284
        v10 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12);  // dword_8F7A24＝登录/选区管理器
        v11 = *(uint32_t *)(dword_8F7A24 + 288);  // 读字段 v11 = (uint32)dword_8F7A24+288
        v12 = false;  // v12 = false（转发）
        *(uint32_t *)ArgList = v11;
        if ( v9 == v10 )  // 条件判定 v9 == v10
          v12 = v11 != -1;
        if ( *(uint32_t *)(dword_8F7B08 + 456) == 2 )  // 读全局对象字段并与常数比较
          v12 = false;  // v12 = false（转发）
        if ( v8[3] == 5 && !v12 )  // 条件判定
          sub_41D300((int *)dword_8F7A24, 0);  // sub_41D300 —— 模块切换 setter → 0x41CC80(onChangeModule) 转发
        *(uint8_t *)(v439[4] + 48) = 1;  // 字段赋值
        sub_45DA30((int)dword_8F8524);  // sub_45DA30 —— net_type 非 0 时重发识别回执
        //   失败支：不是跳过选角时发包 8（sub_423200(8) = GET_USERINFO）→ 写 0xFFFF + 类型 2 → sub_423380 提交
        if ( v12 )  // 条件判定
        {
          sub_46BCB0(*(uint32_t *)ArgList, 1);  // sub_46BCB0 —— 频道选定提交（发包与配置写入）
        }
        else  // 否则分支
        {
          sub_423200(dword_8F7B08, 8);  // 【发送网络包API】
          *(uint32_t *)v440 = 0xFFFF;
          sub_423290(v440, 2);  // 调用 sub_423290
          HIBYTE(v447) = 2;  // v447 高字节置 2
          sub_423290((char *)&v447 + 3, 1);  // 调用 sub_423290
          sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
        }
        off_77F3FC(  // 日志打印（printf 风格）
          "isSkipCharacterSelect %d, lastPlayedServer %d lastPlayedCharacterSlotIndex %d curServer %d",  // （上一调用/表达式的参数续行）
          v12,  // （上一调用/表达式的参数续行）
          v9,  // （上一调用/表达式的参数续行）
          *(uint32_t *)ArgList,  // （上一调用/表达式的参数续行）
          v10);  // （上一调用/表达式的参数续行）
        *((uint8_t *)v439 + 92) = 0;  // （表达式续行/复合语句）
      }
      //   失败支（else）：读错误码 → switch 2/4/5/6/7/0x10/0x12/0x16/0x17 → 写 dword_8F7B08+456（连接错误态 1..10）
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( *(uint32_t *)(pArg1 + 12) != 0 )  // 读全局对象字段并与常数比较
          sub_41D300((int *)dword_8F7A24, 0);  // sub_41D300 —— 模块切换 setter → 0x41CC80(onChangeModule) 转发
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
            *(uint32_t *)(dword_8F7B08 + 456) = 1;  // 写字段 (uint32)dword_8F7B08+456 = 1
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            *(uint32_t *)(dword_8F7B08 + 456) = 2;  // 写字段 (uint32)dword_8F7B08+456 = 2
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
          case 5:  // case 5 = 类型 6 ENUM_CMDPACKET_DELETE_CHARACTER（删角回报）
            *(uint32_t *)(dword_8F7B08 + 456) = 3;  // 写字段 (uint32)dword_8F7B08+456 = 3
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
          case 6:  // case 6 = 类型 7 ENUM_CMDPACKET_RETURN_SELECT_CHARACTER（返回选角）
            *(uint32_t *)(dword_8F7B08 + 456) = 4;  // 写字段 (uint32)dword_8F7B08+456 = 4
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
          case 7:  // case 7 = 类型 8 ENUM_CMDPACKET_GET_USERINFO
            *(uint32_t *)(dword_8F7B08 + 456) = 5;  // 写字段 (uint32)dword_8F7B08+456 = 5
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
          case 0x10:  // case 0x10 = 类型 17 ENUM_CMDPACKET_SEND_MESSAGE（发聊天消息回报）
            *(uint32_t *)(dword_8F7B08 + 456) = 6;  // 写字段 (uint32)dword_8F7B08+456 = 6
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            *(uint32_t *)(dword_8F7B08 + 456) = 7;  // 写字段 (uint32)dword_8F7B08+456 = 7
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
          case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
            *(uint32_t *)(dword_8F7B08 + 456) = 8;  // 写字段 (uint32)dword_8F7B08+456 = 8
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
          case 0x17:  // case 0x17 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
            *(uint32_t *)(dword_8F7B08 + 456) = 9;  // 写字段 (uint32)dword_8F7B08+456 = 9
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            *(uint32_t *)(dword_8F7B08 + 456) = 10;  // 写字段 (uint32)dword_8F7B08+456 = 10
            *(uint8_t *)(pArg1 + 92) = 0;  // 字段清零 pArg1 + 92
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 4] case 2 = type 3 EXIT（退出确认）—— 清 +466 发送锁；非 0 则 sub_6989F0 关闭 socket ──
    case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
      v114 = (uint8_t)nArg5 == 0;  // v114 = (包长低字节 == 0)（成败标志）
      *(uint8_t *)(dword_8F7B08 + 466) = 0;  // 字段清零 dword_8F7B08 + 466
      if ( !v114 )  // 上一步标志为假则处理
      {
        if ( *(uint32_t *)(pArg1 + 12) != 5 )  // 读全局对象字段并与常数比较
          sub_41C1E0();  // sub_41C1E0 —— 退出清理（__noreturn；PostQuitMessage + exit(0)）
        sub_6989F0(dword_8F7B08);  // 调用 sub_6989F0
        goto LABEL_32;  // 跳转合流点 LABEL_32
      }
      sub_41C860((uint32_t *)pArg1);  // sub_41C860 —— 断线/超时退出判定（重试上限 5）
      return 1;  // 处理完成，返回 1
    // ── [段 5] case 3 = type 4 SELECT_CHARACTER（选角回报）──
    //   失败支 switch(错误码)：21 → 串 694、8 → 串 2040 → 弹窗；否则清 +16 对象的 +96
    case 3:  // case 3 = 类型 4 ENUM_CMDPACKET_SELECT_CHARACTER（选角回报）
      v34 = 0;  // 设文案编号 0，稍后弹窗
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 21 )  // 错误码 == 21 分支
        {
          v42 = (char *)sub_422E70(694);  // 取本地化文案 694
        }
        else  // 否则分支
        {
          if ( HIBYTE(nArg5) != 8 )  // 错误码 != 8 分支
          {
LABEL_94:  // 标签 LABEL_94：合流点
            *(uint8_t *)(*(uint32_t *)(pArg1 + 16) + 96) = 0;  // 字段赋值
            return 1;  // 处理完成，返回 1
          }
          v42 = (char *)sub_422E70(2040);  // 取本地化文案 2040
        }
        off_77F3F8(v43, v42);  // 文本输出/弹窗提示
        goto LABEL_94;  // 跳转合流点 LABEL_94
      }
      //   成功支：读 v445/v441/v440 三字段 + v444 计数 → 循环读 premium 段（premiumType/premiumEndTime）
      HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
      HIBYTE(v444) = 0;  // 清 v444 高字节（即将读取）
      v445 = 0;  // 设文案编号 0，稍后弹窗
      v441 = 0;  // 设文案编号 0，稍后弹窗
      *(uint32_t *)v440 = 0;
      v447 = 0;  // 设文案编号 0，稍后弹窗
      *(uint32_t *)ArgList = 0;
      v438 = 0;  // 设文案编号 0，稍后弹窗
      sub_404AB0(&v445);  // 游标读 2 字节 → v445
      sub_404AB0(&v441);  // 游标读 2 字节 → v441
      sub_404AB0(v440);  // 游标读 2 字节 → v440
      sub_404A90((uint8_t *)&v444 + 3);  // 游标读 1 字节 → v444 高位（错误码字段）
      v35 = 0;  // 设文案编号 0，稍后弹窗
      if ( HIBYTE(v444) != 0 )  // 条件判定
      {
        do
        {
          sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
          sub_404AD0(&v438);  // 游标读 4 字节 → v438
          off_77F3FC("premium %d : premiumType %d, premiumEndTime %d", v35, HIBYTE(nArg5), v438);  // 日志打印（printf 风格）
          //   sub_41C470/sub_41C490 写 premium 记录；premiumType==5 时 sub_461180(1) 特殊处理
          sub_41C470((uint8_t *)pArg1, HIBYTE(nArg5), 1);  // sub_41C470 —— 字节数组 setter（this + pArg2 + 297 = pszArg3）
          sub_41C490((uint32_t *)pArg1, HIBYTE(nArg5), v438);  // sub_41C490 —— dword 数组 setter（this + pArg2 + 77 = nArg3）
          if ( HIBYTE(nArg5) == 5 )  // 错误码 == 5 分支
          {
            sub_461180(1);  // sub_461180 —— 与 ·sub_461170 同构（差异：偏移 +1241）
          }
          else if ( HIBYTE(nArg5) != 8 )  // 否则条件分支
          {
            sub_461170(1);  // sub_461170 —— 字节标志 setter（+1240）
          }
          ++v35;  // 自增 v35（循环计数）
        }
        while ( v35 < HIBYTE(v444) );  // 循环直到读满计数
      }
      sub_404AD0(ArgList);  // 游标读 4 字节 → ArgList
      off_77F3FC(  // 日志打印（printf 风格）
        "MyServerId %d, Fatigue %d, FatigueMax %d, Cash %d",  // （上一调用/表达式的参数续行）
        (uint16_t)v445,  // （上一调用/表达式的参数续行）
        (uint16_t)v441,  // （上一调用/表达式的参数续行）
        *(uint16_t *)v440,  // （上一调用/表达式的参数续行）
        *(uint32_t *)ArgList);  // 取指针指向的值（参数）
      word_8F7C10 = v441;  // word_8F7C10 = v441（转发）
      LOWORD(word_77F804) = v445;  // 写全局 LOWORD（v445）
      word_8F7C14 = *(uint16_t *)v440;  // 写全局 word_8F7C14 = 游标值 v440
      dword_8F7C0C = *(uint32_t *)ArgList;  // 写全局 dword_8F7C0C = 游标值 ArgList
      if ( *(int *)ArgList < 0 )  // 字段为负则修正路径
      {
        off_77F3FC(aCriticalError_31, *(uint32_t *)ArgList);  // 日志打印（printf 风格）
        dword_8F7C0C = 0;  // dword_8F7C0C＝现金(Cash)
      }
      for ( i = 3; i != 0; --i )  // 循环：i 从 3 到 0（--）
      {
        v442 = 0;  // 设文案编号 0，稍后弹窗
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        sub_404AB0(dword_9B0BBC2);  // 游标读 2 字节 → dword_9B0BBC2
        sub_404A90(&v442);  // 游标读 1 字节 → v442
        off_77F3FC("QuestTrigger %d, QuestIndex %d", v442, *(uint16_t *)dword_9B0BBC2);  // 日志打印（printf 风格）
        if ( v442 != 0xFFFF )  // 条件判定 v442 != 0xFFFF
          sub_47D060(*(uint16_t *)dword_9B0BBC2, v442);  // 调用 sub_47D060
      }
      sub_404AB0(&v447);  // 游标读 2 字节 → v447
      off_77F3FC("ClearQuestNumber %d", (uint16_t)v447);  // 日志打印（printf 风格）
      if ( (uint16_t)v447 != 0 )  // 条件判定
      {
        do
        {
          *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
          sub_404AB0(dword_9B0BBC2);  // 游标读 2 字节 → dword_9B0BBC2
          v37 = *(uint16_t *)dword_9B0BBC2;
          HIDWORD(Time) = *(uint16_t *)dword_9B0BBC2;  // 全局/复合字段赋值
          *(uint32_t *)sub_468BA0((char *)&Time + 4) = v37;  // （表达式续行/复合语句）
          ++v34;  // 自增 v34（循环计数）
        }
        while ( v34 < (uint16_t)v447 );  // （表达式续行/复合语句）
      }
      sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
      off_77F3FC("TownIndex %d", HIBYTE(pArg4));  // 日志打印（printf 风格）
      v38 = sub_4CE8A0((uint32_t *)dword_8F84F0, HIBYTE(pArg4));  // 调用 sub_4CE8A0
      if ( v38 != 0 )  // 条件判定 v38 != 0
      {
        v39 = *(int **)(v38 + 100);
        v40 = *v39;  // v40 = *v39（解引用）
        *(uint32_t *)dword_9B0BBC2 = *v39;  // （表达式续行/复合语句）
        if ( *(int **)dword_9B0BBC2 != v39 )  // 条件判定
        {
          while ( *(uint32_t *)(v40 + 48) != 1 )  // （表达式/调用续行）
          {
            sub_4CE5F0((int *)dword_9B0BBC2);  // 调用 sub_4CE5F0
            v40 = *(uint32_t *)dword_9B0BBC2;
            if ( *(int **)dword_9B0BBC2 == v39 )  // 条件判定
              goto LABEL_87;  // 跳转合流点 LABEL_87
          }
          sub_45D190(SHIBYTE(pArg4), *(void **)(v40 + 16));  // sub_45D190 —— 进入/切换房间（DOOR_SHUT 自证）
        }
      }
      else  // 否则分支
      {
        off_77F3FC(aCriticalError_32);  // 日志打印（printf 风格）
      }
LABEL_87:  // 标签 LABEL_87：合流点
      v41 = v439;  // v41 = v439（转发）
      sub_41D300(v439, 1);  // sub_41D300 —— 模块切换 setter → 0x41CC80(onChangeModule) 转发
      *(uint8_t *)(v41[4] + 96) = 0;  // 字段清零 v41[4] + 96
      if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
        sub_461190(*((uint32_t *)dword_8F8528 + 4));  // sub_461190 —— 条件清除计时状态 +1244
      return 1;  // 处理完成，返回 1
    // ── [段 6] case 4 = type 5 CREATE_CHARACTER（建角回报）──
    //   成功（nArg5 低字节非 0）：播 CHARACTER_CREATED + 写 +16 对象 +276=1 + sub_46C0E0(0) 刷新列表
    case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        v13 = sub_422E70(680);  // 取本地化文案 680
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v13, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        sub_432EA0("CHARACTER_CREATED", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
        *(uint8_t *)(*(uint32_t *)(pArg1 + 16) + 276) = 1;  // 字段赋值
        sub_46C0E0(0);  // sub_46C0E0 —— 频道与角色页签切换
      }
      else  // 否则分支
      //   失败：错误码 switch 2/4/0x12/0x13/0x16/0x17/0x18 → 各取本地化弹窗文案（串 681..687）
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_40BE20(v14, "\nError %d", HIBYTE(nArg5));  // 调用 sub_40BE20
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
            v15 = (char *)sub_422E70(681);  // 取本地化文案 681
            off_77F3F8(v16, v15);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v17 = sub_422E70(682);  // 取本地化文案 682
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v17, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            v18 = sub_422E70(683);  // 取本地化文案 683
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v18, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            v19 = (char *)sub_422E70(684);  // 取本地化文案 684
            off_77F3F8(v20, v19);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
LABEL_1083:  // 标签 LABEL_1083：合流点
            break;  // 跳出本分支
          case 0x17:  // case 0x17 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
            v21 = (char *)sub_422E70(685);  // 取本地化文案 685
            off_77F3F8(v22, v21);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          case 0x18:  // case 0x18 = 类型 25 ENUM_CMDPACKET_REPAIR_EQUIPMENT（修理装备回报）
            v23 = (char *)sub_422E70(686);  // 取本地化文案 686
            off_77F3F8(v24, v23);  // 文本输出/弹窗提示
            v25 = sub_422E70(687);  // 取本地化文案 687
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v25, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            goto LABEL_1083;  // 跳转合流点 LABEL_1083
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 7] case 5 = type 6 DELETE_CHARACTER（删角回报）—— 成功播 CHARACTER_DELETED + 列表刷新 ──
    case 5:  // case 5 = 类型 6 ENUM_CMDPACKET_DELETE_CHARACTER（删角回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Index %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        v26 = sub_422E70(688);  // 取本地化文案 688
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v26, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        sub_432EA0("CHARACTER_DELETED", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
            v27 = (char *)sub_422E70(689);  // 取本地化文案 689
            off_77F3F8(v28, v27);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            v29 = sub_422E70(690);  // 取本地化文案 690
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v29, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x15:  // case 0x15 = 类型 22 ENUM_CMDPACKET_RENT_AVATAR（租时装回报）
            v30 = (char *)sub_422E70(691);  // 取本地化文案 691
            off_77F3F8(v31, v30);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
            v32 = sub_422E70(692);  // 取本地化文案 692
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v32, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x25:  // case 0x25 = 类型 38 ENUM_CMDPACKET_SET_USER_AREA（区域更新回报）
            v33 = sub_422E70(693);  // 取本地化文案 693
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v33, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 8] case 6 = type 7 RETURN_SELECT_CHARACTER（返回选角）—— sub_41D320 ──
    case 6:  // case 6 = 类型 7 ENUM_CMDPACKET_RETURN_SELECT_CHARACTER（返回选角）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
LABEL_32:  // 标签 LABEL_32：合流点
        sub_41D320(pArg1);  // sub_41D320 —— ★ 登出/回主界面资源卸载链
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 19 )  // 错误码 == 19 分支
          off_77F3FC(aFail_12);  // 日志打印（printf 风格）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 9] case 8 = type 9 RECOVER_STAMINA（疲劳恢复回报）—— Money/STAMINA_RECOVER 播报 ──
    case 8:  // case 8 = 类型 9 ENUM_CMDPACKET_RECOVER_STAMINA（疲劳恢复回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        nArg5 = 0;
        sub_404AD0(&nArg5);  // 游标读 4 字节 → nArg5
        off_77F3FC("Money %d", nArg5);  // 日志打印（printf 风格）
        (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 40))(  // 虚函数调用（vtable 槽）
          **((uint32_t **)dword_8F852C + 3),  // （上一调用/表达式的参数续行）
          nArg5);  // （上一调用/表达式的参数续行）
        if ( dword_8F7C04 != 0 )  // 条件判定 dword_8F7C04 != 0
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1060))(dword_8F7C04, 100);  // 虚函数调用（vtable 槽）
          if ( *(uint32_t *)(pArg1 + 12) == 1 )  // 读全局对象字段并与常数比较
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);  // 虚函数调用（vtable 槽）
          v44 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v45 = sub_422E70(695);  // 取本地化文案 695
          sub_43BEE0(v44, v45, -6567706, 0, -1);  // 调用 sub_43BEE0
          sub_432EA0("STAMINA_RECOVER", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
        }
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 18 )  // 错误码 == 18 分支
        {
          v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v47 = sub_422E70(696);  // 取本地化文案 696
          goto LABEL_983;  // 跳转合流点 LABEL_983
        }
        if ( HIBYTE(nArg5) == 22 )  // 错误码 == 22 分支
        {
          v408 = 697;  // 设文案编号 697，稍后弹窗
          goto LABEL_982;  // 跳转合流点 LABEL_982
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 10] case 9 = type 10 REQUEST_PEER（P2P 请求回报）—— 大错误码 switch ──
    //   子 switch：3/4/0x12/0x13/0x37/0x38 → 各错误文案（串 698..706, 1344..1349）分两路 off_77F3F8 弹窗或 sub_44E8D0 消息
    case 9:  // case 9 = 类型 10 ENUM_CMDPACKET_REQUEST_PEER（P2P 请求回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d, PeerRequestType %d", HIBYTE(pArg4), HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(pArg4) )  // 按第二字段（pArg4 高字节）分派
        {
          case 3:  // case 3 = 类型 4 ENUM_CMDPACKET_SELECT_CHARACTER（选角回报）
            v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
            v47 = sub_422E70(698);  // 取本地化文案 698
            goto LABEL_983;  // 跳转合流点 LABEL_983
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            if ( HIBYTE(nArg5) == 0 )  // 错误码 == 0 分支
            {
              v408 = 699;  // 设文案编号 699，稍后弹窗
              goto LABEL_982;  // 跳转合流点 LABEL_982
            }
            if ( HIBYTE(nArg5) == 2 )  // 错误码 == 2 分支
            {
              v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
              v47 = sub_422E70(700);  // 取本地化文案 700
              goto LABEL_983;  // 跳转合流点 LABEL_983
            }
            break;  // 跳出本分支
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
            {
              case 0:  // case 0 = 类型 1 ENUM_CMDPACKET_LOGIN（登录回报）
                v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
                v47 = sub_422E70(701);  // 取本地化文案 701
                goto LABEL_983;  // 跳转合流点 LABEL_983
              case 1:  // case 1 = 类型 2 ENUM_CMDPACKET_SET_UDP_IP_PORT
                v408 = 702;  // 设文案编号 702，稍后弹窗
                goto LABEL_982;  // 跳转合流点 LABEL_982
              case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
                v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
                v47 = sub_422E70(703);  // 取本地化文案 703
                goto LABEL_983;  // 跳转合流点 LABEL_983
              default:  // 未列出的码值 → 兜底
                break;  // 跳出本分支
            }
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
            {
              case 0:  // case 0 = 类型 1 ENUM_CMDPACKET_LOGIN（登录回报）
                v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
                v47 = sub_422E70(704);  // 取本地化文案 704
                goto LABEL_983;  // 跳转合流点 LABEL_983
              case 1:  // case 1 = 类型 2 ENUM_CMDPACKET_SET_UDP_IP_PORT
                v408 = 705;  // 设文案编号 705，稍后弹窗
                goto LABEL_982;  // 跳转合流点 LABEL_982
              case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
                v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
                v47 = sub_422E70(706);  // 取本地化文案 706
                goto LABEL_983;  // 跳转合流点 LABEL_983
              default:  // 未列出的码值 → 兜底
                break;  // 跳出本分支
            }
            break;  // 跳出本分支
          case 0x37:  // case 0x37 = 类型 56 ENUM_CMDPACKET_SET_PVP_READY_STATE
            if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
            {
              if ( HIBYTE(nArg5) == 1 )  // 错误码 == 1 分支
              {
                v49 = sub_422E70(1345);  // 取本地化文案 1345
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v49, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
              }
              else if ( HIBYTE(nArg5) == 2 )  // 否则错误码 == 2
              {
                v50 = sub_422E70(1346);  // 取本地化文案 1346
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v50, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
              }
            }
            else  // 否则分支
            {
              v48 = sub_422E70(1344);  // 取本地化文案 1344
              sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v48, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            }
            break;  // 跳出本分支
          case 0x38:  // case 0x38 = 类型 57 ENUM_CMDPACKET_SET_PVP_TEAM_MODE
            if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
            {
              if ( HIBYTE(nArg5) == 1 )  // 错误码 == 1 分支
              {
                v52 = sub_422E70(1348);  // 取本地化文案 1348
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v52, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
              }
              else if ( HIBYTE(nArg5) == 2 )  // 否则错误码 == 2
              {
                v53 = sub_422E70(1349);  // 取本地化文案 1349
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v53, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
              }
            }
            else  // 否则分支
            {
              v51 = sub_422E70(1347);  // 取本地化文案 1347
              sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v51, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            }
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 11] case 10 = type 11 RESPONSE_PEER（P2P 应答回报）—— 成功支：读写 ServerId/PeerRequestType ──
    //   sub_429830 取对象、sub_44BBA0/sub_4844B0 落位与资源装配（94 行）
    case 10:  // case 10 = 类型 11 ENUM_CMDPACKET_RESPONSE_PEER（P2P 应答回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        pArg4 = 0;
        sub_404AB0(&pArg4);  // 游标读 2 字节 → pArg4
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("ServerId %d, PeerRequestType %d", (uint16_t)pArg4, HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 1 )  // 错误码 == 1 分支
        {
          sub_4844B0((int *)dword_8F8538);  // sub_4844B0 —— 技能槽记录初始化（两内部缓冲析构）
          dword_8F85382 = dword_8F8538;  // dword_8F85382 = dword_8F8538（转发）
          *(uint16_t *)(dword_8F8538 + 4) = pArg4;  // 写字段 (uint16)dword_8F8538+4 = pArg4
          *(uint8_t *)(dword_8F85382 + 36) = 0;  // 字段清零 dword_8F85382 + 36
          *(uint8_t *)(dword_8F85382 + 64) = 0;  // 字段清零 dword_8F85382 + 64
          sub_44BBA0(2, 0);  // sub_44BBA0 —— 窗口显示切换（WINDOW_SHOW 音效）
        }
      }
      else  // 否则分支
      {
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d, PeerRequestType %d", HIBYTE(pArg4), HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(pArg4) )  // 按第二字段（pArg4 高字节）分派
        {
          case 3:  // case 3 = 类型 4 ENUM_CMDPACKET_SELECT_CHARACTER（选角回报）
            v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
            v47 = sub_422E70(707);  // 取本地化文案 707
            goto LABEL_983;  // 跳转合流点 LABEL_983
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            if ( HIBYTE(nArg5) == 0 )  // 错误码 == 0 分支
            {
              v408 = 708;  // 设文案编号 708，稍后弹窗
              goto LABEL_982;  // 跳转合流点 LABEL_982
            }
            if ( HIBYTE(nArg5) == 2 )  // 错误码 == 2 分支
            {
              v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
              v47 = sub_422E70(709);  // 取本地化文案 709
              goto LABEL_983;  // 跳转合流点 LABEL_983
            }
            break;  // 跳出本分支
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
            {
              case 0:  // case 0 = 类型 1 ENUM_CMDPACKET_LOGIN（登录回报）
                v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
                v47 = sub_422E70(710);  // 取本地化文案 710
                goto LABEL_983;  // 跳转合流点 LABEL_983
              case 1:  // case 1 = 类型 2 ENUM_CMDPACKET_SET_UDP_IP_PORT
                v408 = 711;  // 设文案编号 711，稍后弹窗
                goto LABEL_982;  // 跳转合流点 LABEL_982
              case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
                v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
                v47 = sub_422E70(712);  // 取本地化文案 712
                goto LABEL_983;  // 跳转合流点 LABEL_983
              default:  // 未列出的码值 → 兜底
                break;  // 跳出本分支
            }
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
            {
              case 0:  // case 0 = 类型 1 ENUM_CMDPACKET_LOGIN（登录回报）
                v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
                v47 = sub_422E70(713);  // 取本地化文案 713
                goto LABEL_983;  // 跳转合流点 LABEL_983
              case 1:  // case 1 = 类型 2 ENUM_CMDPACKET_SET_UDP_IP_PORT
                v408 = 714;  // 设文案编号 714，稍后弹窗
                goto LABEL_982;  // 跳转合流点 LABEL_982
              case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
                v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
                v47 = sub_422E70(715);  // 取本地化文案 715
                goto LABEL_983;  // 跳转合流点 LABEL_983
              default:  // 未列出的码值 → 兜底
                break;  // 跳出本分支
            }
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            if ( HIBYTE(pArg4) == 17 && HIBYTE(nArg5) == 2 )  // 条件判定
            {
              v55 = sub_429830((uint16_t)word_77F804);  // sub_429830 —— 表按键查找（uint16）
              v56 = sub_41A5E0(v55 + 53);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
              v415 = dword_9B759C[v56]
                   - (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C  // 虚函数调用（vtable 槽）
                                                                                               + 3));  // （续行：指针/参数偏移）
              v57 = (const char *)sub_422E70(716);  // 取本地化文案 716
              goto LABEL_812;  // 跳转合流点 LABEL_812
            }
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 12] case 11 = type 12 SET_PARTY_INFO（组队设置回报）—— 仅错误串 14 行 ──
    case 11:  // case 11 = 类型 12 ENUM_CMDPACKET_SET_PARTY_INFO（组队设置回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 8 )  // 错误码 == 8 分支
        {
          v58 = (char *)sub_422E70(717);  // 取本地化文案 717
          off_77F3F8(v59, v58);  // 文本输出/弹窗提示
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 13] case 12 = type 13 LEAVE_PARTY（离队回报） ──
    case 12:  // case 12 = 类型 13 ENUM_CMDPACKET_LEAVE_PARTY（离队回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 18 )  // 错误码 == 18 分支
        {
          v60 = (char *)sub_422E70(718);  // 取本地化文案 718
          off_77F3F8(v61, v60);  // 文本输出/弹窗提示
        }
        else if ( HIBYTE(nArg5) == 19 )  // 否则错误码 == 19
        {
          v62 = (char *)sub_422E70(719);  // 取本地化文案 719
          off_77F3F8(v63, v62);  // 文本输出/弹窗提示
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 14] case 13 = type 14 WALKOUT_PARTY_MEMBER（踢人回报）—— 错误串 + SeatIndex 判定 ──
    case 13:  // case 13 = 类型 14 ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER（踢人回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v64 = (char *)sub_422E70(720);  // 取本地化文案 720
            off_77F3F8(v65, v64);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            v66 = (char *)sub_422E70(721);  // 取本地化文案 721
            off_77F3F8(v67, v66);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          case 8:  // case 8 = 类型 9 ENUM_CMDPACKET_RECOVER_STAMINA（疲劳恢复回报）
            v68 = (char *)sub_422E70(722);  // 取本地化文案 722
            off_77F3F8(v69, v68);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 15] case 14 = type 15 START_GAME（开始游戏/进副本回报）—— 错误码 + 房间/副本入口刷新 ──
    case 14:  // case 14 = 类型 15 ENUM_CMDPACKET_START_GAME（开始游戏回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        off_77F3FC("Error %d, SeatIndex %d", HIBYTE(nArg5), HIBYTE(pArg4));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 22 )  // 错误码 == 22 分支
        {
          v70 = *(uint32_t *)(dword_8F850C + 4 * HIBYTE(pArg4) + 16);  // dword_8F850C＝房间/席位表
          if ( v70 != 0 )  // 条件判定 v70 != 0
          {
            if ( v70 == sub_429830((uint16_t)word_77F804) )  // 条件判定
            {
              strcpy(Buffer, (const char *)sub_422E70(723));  // 字符串拷贝
            }
            else  // 否则分支
            {
              if ( *(uint32_t *)(v70 + 40) < 0x10u )  // 读字段并与阈值比较（SSO 容量判定等）
                v71 = v70 + 20;
              else  // 否则分支
                v71 = *(uint32_t *)(v70 + 20);  // 读字段 v71 = v70 + 20
              v72 = (const char *)sub_422E70(724);  // 取本地化文案 724
              sprintf(Buffer, v72, v71);  // 格式化字符串到缓冲
            }
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
            *(uint8_t *)(*(uint32_t *)(pArg1 + 20) + 116) = 0;  // 字段赋值
          }
          else  // 否则分支
          {
            off_77F3FC(aCriticalError_33);  // 日志打印（printf 风格）
            *(uint8_t *)(*(uint32_t *)(pArg1 + 20) + 116) = 0;  // 字段赋值
          }
        }
        else  // 否则分支
        {
          if ( HIBYTE(nArg5) == 21 )  // 错误码 == 21 分支
          {
            v73 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
            v74 = sub_422E70(725);  // 取本地化文案 725
            sub_43BEE0(v73, v74, -6567706, 0, -1);  // 调用 sub_43BEE0
          }
          *(uint8_t *)(*(uint32_t *)(pArg1 + 20) + 116) = 0;  // 字段赋值
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 16] case 15 = type 16 SELECT_DUNGEON（选副本回报）—— 错误码 switch 0x15/0x13/8/0xE/0x11 ──
    //   0x11 支：sub_583B30 取自己席位 → sub_476B60 取房间 → sub_4F2CE0 取物品 → sprintf 串 2100 播报
    case 15:  // case 15 = 类型 16 ENUM_CMDPACKET_SELECT_DUNGEON（选副本回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
        return 1;  // 处理完成，返回 1
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
      {
        case 0x15:  // case 0x15 = 类型 22 ENUM_CMDPACKET_RENT_AVATAR（租时装回报）
          v75 = (char *)sub_422E70(726);  // 取本地化文案 726
          off_77F3F8(v76, v75);  // 文本输出/弹窗提示
          break;  // 跳出本分支
        case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
          v77 = (char *)sub_422E70(727);  // 取本地化文案 727
          off_77F3F8(v78, v77);  // 文本输出/弹窗提示
          break;  // 跳出本分支
        case 8:  // case 8 = 类型 9 ENUM_CMDPACKET_RECOVER_STAMINA（疲劳恢复回报）
          v79 = (char *)sub_422E70(728);  // 取本地化文案 728
          off_77F3F8(v80, v79);  // 文本输出/弹窗提示
          break;  // 跳出本分支
        case 0xE:  // case 0xE = 类型 15 ENUM_CMDPACKET_START_GAME（开始游戏回报）
          off_77F3FC(aFail_2);  // 日志打印（printf 风格）
          break;  // 跳出本分支
        case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
          HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
          sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
          off_77F3FC("SeatIndex %d", HIBYTE(pArg4));  // 日志打印（printf 风格）
          v81 = sub_583B30(*(uint32_t *)(dword_8F7A24 + 24));  // sub_583B30 —— 按 this+72 下标查 this+69 表（16字节/项），-1 则返回 -1
          v82 = v81;  // v82 = v81（转发）
          if ( v81 == -1 )  // 条件判定
          {
            off_77F3FC(aCriticalError_46);  // 日志打印（printf 风格）
            return 1;  // 处理完成，返回 1
          }
          v83 = (uint32_t *)sub_476B60(v81);  // 调用 sub_476B60
          v84 = v83;  // v84 = v83（转发）
          if ( v83 == nullptr )  // 条件判定 v83 == nullptr
          {
            off_77F3FC(aCriticalError_34, v82);  // 日志打印（printf 风格）
            return 1;  // 处理完成，返回 1
          }
          v85 = sub_4F2CE0(v83[24]);  // 调用 sub_4F2CE0
          v86 = *(uint32_t *)(dword_8F850C + 4 * HIBYTE(pArg4) + 16);  // dword_8F850C＝房间/席位表
          if ( v86 == 0 )  // 条件判定 v86 == 0
          {
            off_77F3FC(aCriticalError_47);  // 日志打印（printf 风格）
            return 1;  // 处理完成，返回 1
          }
          if ( v84[7] < 0x10u )  // 条件判定
            v87 = v84 + 2;
          else  // 否则分支
            v87 = (uint32_t *)v84[2];
          if ( *(uint32_t *)(v86 + 40) < 0x10u )  // 读字段并与阈值比较（SSO 容量判定等）
            v88 = v86 + 20;
          else  // 否则分支
            v88 = *(uint32_t *)(v86 + 20);  // 读字段 v88 = v86 + 20
          v416 = v87;  // v416 = v87（转发）
          v412 = v84[25];  // 读数组 v412 = v84[25]
          v411 = v85;  // v411 = v85（转发）
          v409 = v88;  // v409 = v88（转发）
          v89 = (const char *)sub_422E70(2100);  // 取本地化文案 2100
          sprintf(v449, v89, v409, v411, v412, v416);  // 格式化字符串到缓冲
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v449, -6567706, 0, -1);  // 调用 sub_43BEE0
          break;  // 跳出本分支
        default:  // 未列出的码值 → 兜底
          break;  // 跳出本分支
      }
      v90 = sub_453BE0(*(uint32_t *)(pArg1 + 24));  // sub_453BE0 —— 启动门判定
      v91 = *(uint32_t *)(pArg1 + 24);  // 读字段 v91 = pArg1 + 24
      if ( v90 != 0 )  // 条件判定 v90 != 0
      {
        if ( *(uint32_t *)(v91 + 288) != 0 )  // 读全局对象字段并与常数比较
          sub_454680(**(uint32_t **)(v91 + 276), *(uint32_t *)(*(uint32_t *)(v91 + 276) + 4));  // sub_454680 —— 房间选择确认
        else  // 否则分支
          off_77F3FC(aCriticalError0);  // 日志打印（printf 风格）
      }
      else  // 否则分支
      {
        *(uint8_t *)(v91 + 180) = 0;  // 字段清零 v91 + 180
      }
      return 1;  // 处理完成，返回 1
    // ── [段 17] case 17 = type 18 DELETE_ITEM（删物品回报）—— ItemSpace/SlotNumber + 逐槽 StackNumber ──
    //   sub_432F00 取物品栏、sub_474950/sub_47CD00 落地与刷新
    case 17:  // case 17 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("ItemSpace %d, SlotNumber %d", HIBYTE(pArg4), HIBYTE(nArg5));  // 日志打印（printf 风格）
        memset(&pBuf[1], 0, 12);  // 清零缓冲
        v92 = 0;  // 设文案编号 0，稍后弹窗
        v461 = 0;  // 设文案编号 0，稍后弹窗
        if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
        {
          do
          {
            v439 = nullptr;  // v439 = nullptr（转发）
            *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
            sub_404AB0(&v439);  // 游标读 2 字节 → v439
            sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
            off_77F3FC("SlotIndex %d, StackNumber %d", (uint16_t)v439, *(uint32_t *)dword_9B0BBC2);  // 日志打印（printf 风格）
            if ( HIBYTE(pArg4) == 3 )  // 第二字段 == 3
            {
              pObj30 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 788))(  // 虚函数调用（vtable 槽）
                      dword_8F7C04,  // （上一调用/表达式的参数续行）
                      (uint16_t)v439,  // （上一调用/表达式的参数续行）
                      nArg32);  // （上一调用/表达式的参数续行）
              if ( pObj30 != 0 )  // 条件判定 pObj30 != 0
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj30 + 4))(pObj30, 1);  // 虚函数调用（vtable 槽）
              nArg32 = (uint16_t)v439;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1080))(dword_8F7C04);  // 虚函数调用（vtable 槽）
            }
            else  // 否则分支
            {
              HIDWORD(Time) = *(uint32_t *)dword_9B0BBC2;  // 全局/复合字段赋值
              LODWORD(Time) = (uint16_t)v439;  // 全局/复合字段赋值
              sub_474950(&Time);  // 调用 sub_474950
            }
            ++v92;  // 自增 v92（循环计数）
          }
          while ( v92 < HIBYTE(nArg5) );  // 循环直到读满计数
        }
        if ( HIBYTE(pArg4) != 3 )  // 第二字段 != 3
        {
          v94 = (int *)sub_432F00(HIBYTE(pArg4));  // sub_432F00 —— 按类型取全局列表对象
          if ( sub_485150(v94, (int)pBuf) == 0 )  // 条件判定
          {
            v95 = (char *)sub_422E70(729);  // 取本地化文案 729
            off_77F3F8(v96, v95);  // 文本输出/弹窗提示
          }
        }
        sub_47CD00(dword_8F8540);  // 调用 sub_47CD00
        sub_5E5260(pBuf);  // 调用 sub_5E5260
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            v98 = (char *)sub_422E70(730);  // 取本地化文案 730
            off_77F3F8(v99, v98);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            v100 = (char *)sub_422E70(731);  // 取本地化文案 731
            off_77F3F8(v101, v100);  // 文本输出/弹窗提示
            break;  // 跳出本分支
          case 0x17:  // case 0x17 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
            off_77F3F8(v97, "item type error");  // 文本输出/弹窗提示
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        off_77F3FC("ItemSpace %d", HIBYTE(pArg4));  // 日志打印（printf 风格）
        v102 = (uint32_t *)sub_432F00(HIBYTE(pArg4));  // sub_432F00 —— 按类型取全局列表对象
        if ( v102 != nullptr )  // 条件判定 v102 != nullptr
          goto LABEL_243;  // 跳转合流点 LABEL_243
      }
      return 1;  // 处理完成，返回 1
    // ── [段 18] case 18 = type 19 MOVE_ITEMSPACE（移动物品栏回报，170 行）—— 移动成功/失败两条大支线 ──
    //   成功支逐条读 SlotIndex/StackNumber 并回写；LABEL_304 支：ItemSpace1/ItemSpace2 双双 sub_484FF0 刷新
    case 18:  // case 18 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        v445 = 0;  // 设文案编号 0，稍后弹窗
        v447 = 0;  // 设文案编号 0，稍后弹窗
        v441 = 0;  // 设文案编号 0，稍后弹窗
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_404AB0(&v445);  // 游标读 2 字节 → v445
        sub_404AD0(&v441);  // 游标读 4 字节 → v441
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404AB0(&v447);  // 游标读 2 字节 → v447
        off_77F3FC(  // 日志打印（printf 风格）
          "ItemSpace1 %d, ItemSlotIndex1 %d, MoveNumber %d, ItemSpace2 %d, ItemSlotIndex2 %d",  // （上一调用/表达式的参数续行）
          HIBYTE(pArg4),  // （上一调用/表达式的参数续行）
          (uint16_t)v445,  // （上一调用/表达式的参数续行）
          v441,  // （上一调用/表达式的参数续行）
          HIBYTE(nArg5),  // （上一调用/表达式的参数续行）
          (uint16_t)v447);  // （上一调用/表达式的参数续行）
        if ( HIBYTE(pArg4) == HIBYTE(nArg5) )  // 条件判定
        {
          v103 = (uint32_t *)sub_432F00(HIBYTE(pArg4));  // sub_432F00 —— 按类型取全局列表对象
          if ( v103 != nullptr && sub_485270(v103, (uint16_t)v445, (uint16_t)v447) == 0 )  // 条件判定
          {
            v104 = (char *)sub_422E70(732);  // 取本地化文案 732
            off_77F3F8(v105, v104);  // 文本输出/弹窗提示
          }
          return 1;  // 处理完成，返回 1
        }
        if ( HIBYTE(pArg4) != 0 )  // 第二字段 != 0
        {
          if ( HIBYTE(pArg4) != 2 )  // 第二字段 != 2
          {
            if ( HIBYTE(pArg4) != 1 )  // 第二字段 != 1
              goto LABEL_268;  // 跳转合流点 LABEL_268
            goto LABEL_257;  // 跳转合流点 LABEL_257
          }
          if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
          {
LABEL_257:  // 标签 LABEL_257：合流点
            if ( HIBYTE(nArg5) == 3 )  // 错误码 == 3 分支
            {
              v110 = (int *)sub_432F00(HIBYTE(pArg4));  // sub_432F00 —— 按类型取全局列表对象
              if ( sub_485510(v110, nArg3, (uint16_t)v445, (uint16_t)v447) == 0 )  // 条件判定
              {
                v108 = (char *)sub_422E70(734);  // 取本地化文案 734
                goto LABEL_733;  // 跳转合流点 LABEL_733
              }
              v111 = *(uint32_t *)(pArg1 + 12);  // 读字段 v111 = pArg1 + 12
              if ( v111 == 3 || v111 == 2 || v111 == 4 || v111 == 6 )  // 条件判定
              {
                pObj12 = dword_8F7C04;  // pObj12 = dword_8F7C04（转发）
                v113 = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_8F7C04 + 792))(  // 虚函数调用（vtable 槽）
                         dword_8F7C04,  // （上一调用/表达式的参数续行）
                         (uint16_t)v447,  // （上一调用/表达式的参数续行）
                         nArg32,  // （上一调用/表达式的参数续行）
                         nArg2);  // （上一调用/表达式的参数续行）
                if ( v113 != 0 )  // 条件判定 v113 != 0
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj12 + 812))(pObj12, v113);  // 虚函数调用（vtable 槽）
                else  // 否则分支
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj12 + 816))(pObj12, (uint16_t)v447);  // 虚函数调用（vtable 槽）
              }
LABEL_265:  // 标签 LABEL_265：合流点
              sub_47CD00(dword_8F8540);  // 调用 sub_47CD00
              return 1;  // 处理完成，返回 1
            }
LABEL_268:  // 标签 LABEL_268：合流点
            if ( HIBYTE(pArg4) > 1u || HIBYTE(nArg5) != 4 )  // 条件判定
            {
              if ( HIBYTE(pArg4) != 4 )  // 第二字段 != 4
              {
                if ( HIBYTE(pArg4) != 3 )  // 第二字段 != 3
                  return 1;  // 处理完成，返回 1
                v114 = HIBYTE(nArg5) == 4;
LABEL_273:  // 标签 LABEL_273：合流点
                if ( !v114 )  // 上一步标志为假则处理
                  return 1;  // 处理完成，返回 1
                v115 = *(int **)(dword_8F8538 + 16);  // dword_8F8538＝随身影身/占位管理器
                if ( HIBYTE(pArg4) == 4 )  // 第二字段 == 4
                {
                  if ( sub_485510(v115, nArg3, (uint16_t)v445, (uint16_t)v447) != 0 )  // 条件判定
                    goto LABEL_282;  // 跳转合流点 LABEL_282
                  v116 = (char *)sub_422E70(736);  // 取本地化文案 736
                }
                else  // 否则分支
                {
                  if ( sub_485510(v115, nArg3, (uint16_t)v447, (uint16_t)v445) != 0 )  // 条件判定
                    goto LABEL_282;  // 跳转合流点 LABEL_282
                  v116 = (char *)sub_422E70(737);  // 取本地化文案 737
                }
                off_77F3F8(v117, v116);  // 文本输出/弹窗提示
LABEL_282:  // 标签 LABEL_282：合流点
                for ( j = 0; j < 2; ++j )  // 循环：j 从 0 到 2（++）
                  sub_484710((uint32_t *)dword_8F8538, j, 0);  // sub_484710 —— 技能槽状态写入（两字段组合播报）
LABEL_289:  // 标签 LABEL_289：合流点
                sub_57A3A0(dword_8F8538);  // sub_57A3A0 —— std::string 构造辅助 3（698F90）
                sub_47CD00(dword_8F8540);  // 调用 sub_47CD00
                return 1;  // 处理完成，返回 1
              }
              if ( HIBYTE(nArg5) >= 2u )  // nArg5 >= 2u 则截断/分档
              {
                v114 = HIBYTE(nArg5) == 3;
                goto LABEL_273;  // 跳转合流点 LABEL_273
              }
            }
            v119 = (int *)sub_432F00(HIBYTE(pArg4));  // sub_432F00 —— 按类型取全局列表对象
            v120 = (int *)sub_432F00(HIBYTE(nArg5));  // sub_432F00 —— 按类型取全局列表对象
            if ( sub_485330(v119, (uint16_t)v445, v441, v120, (uint16_t)v447) == 0 )  // 条件判定
            {
              v121 = (char *)sub_422E70(735);  // 取本地化文案 735
              off_77F3F8(v122, v121);  // 文本输出/弹窗提示
            }
            for ( k = 0; k < 2; ++k )  // 循环：k 从 0 到 2（++）
              sub_484710((uint32_t *)dword_8F8538, k, 0);  // sub_484710 —— 技能槽状态写入（两字段组合播报）
            goto LABEL_289;  // 跳转合流点 LABEL_289
          }
        }
        else if ( HIBYTE(nArg5) != 2 )  // 否则条件分支
        {
          goto LABEL_257;  // 跳转合流点 LABEL_257
        }
        v106 = (int *)sub_432F00(HIBYTE(pArg4));  // sub_432F00 —— 按类型取全局列表对象
        v107 = (int *)sub_432F00(HIBYTE(nArg5));  // sub_432F00 —— 按类型取全局列表对象
        if ( sub_485330(v106, (uint16_t)v445, v441, v107, (uint16_t)v447) != 0 )  // 条件判定
          goto LABEL_265;  // 跳转合流点 LABEL_265
        v108 = (char *)sub_422E70(733);  // 取本地化文案 733
        goto LABEL_733;  // 跳转合流点 LABEL_733
      }
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
      {
        case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
          v124 = (char *)sub_422E70(738);  // 取本地化文案 738
LABEL_303:  // 标签 LABEL_303：合流点
          off_77F3F8(v125, v124);  // 文本输出/弹窗提示
          goto LABEL_304;  // 跳转合流点 LABEL_304
        case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
          v124 = (char *)sub_422E70(739);  // 取本地化文案 739
          goto LABEL_303;  // 跳转合流点 LABEL_303
        case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
          v124 = (char *)sub_422E70(740);  // 取本地化文案 740
          goto LABEL_303;  // 跳转合流点 LABEL_303
        case 8:  // case 8 = 类型 9 ENUM_CMDPACKET_RECOVER_STAMINA（疲劳恢复回报）
          v126 = sub_422E70(741);  // 取本地化文案 741
          break;  // 跳出本分支
        case 0xE:  // case 0xE = 类型 15 ENUM_CMDPACKET_START_GAME（开始游戏回报）
          v126 = sub_422E70(742);  // 取本地化文案 742
          break;  // 跳出本分支
        case 0x17:  // case 0x17 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
          v124 = (char *)sub_422E70(743);  // 取本地化文案 743
          goto LABEL_303;  // 跳转合流点 LABEL_303
        default:  // 未列出的码值 → 兜底
LABEL_304:  // 标签 LABEL_304：合流点
          HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
          HIBYTE(v444) = 0;  // 清 v444 高字节（即将读取）
          sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
          sub_404A90((uint8_t *)&v444 + 3);  // 游标读 1 字节 → v444 高位（错误码字段）
          off_77F3FC("ItemSpace1 %d, ItemSpace2 %d", HIBYTE(pArg4), HIBYTE(v444));  // 日志打印（printf 风格）
          v127 = (uint32_t *)sub_432F00(HIBYTE(pArg4));  // sub_432F00 —— 按类型取全局列表对象
          v128 = (uint32_t *)sub_432F00(HIBYTE(v444));  // sub_432F00 —— 按类型取全局列表对象
          if ( v127 != nullptr )  // 条件判定 v127 != nullptr
            sub_484FF0(v127);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
          if ( v128 != nullptr && v127 != v128 )  // 条件判定
            sub_484FF0(v128);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
          return 1;  // 处理完成，返回 1
      }
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v126, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
      goto LABEL_304;  // 跳转合流点 LABEL_304
    // ── [段 19] case 19 = type 20 SORT_ITEM（整理物品回报）—— 播 ARRANGE_FINISH + sub_484FF0 刷新 ──
    case 19:  // case 19 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("ItemSpace %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        v129 = (uint32_t *)sub_432F00(HIBYTE(nArg5));  // sub_432F00 —— 按类型取全局列表对象
        sub_484FF0(v129);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
        sub_432EA0("ARRANGE_FINISH", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
        return 1;  // 处理完成，返回 1
      }
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      if ( HIBYTE(nArg5) == 2 )  // 错误码 == 2 分支
      {
        v130 = (char *)sub_422E70(744);  // 取本地化文案 744
      }
      else  // 否则分支
      {
        if ( HIBYTE(nArg5) != 18 )  // 错误码 != 18 分支
          goto LABEL_316;  // 跳转合流点 LABEL_316
        v130 = (char *)sub_422E70(745);  // 取本地化文案 745
      }
      off_77F3F8(v131, v130);  // 文本输出/弹窗提示
LABEL_316:  // 标签 LABEL_316：合流点
      HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
      sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
      off_77F3FC("ItemSpace %d", HIBYTE(pArg4));  // 日志打印（printf 风格）
      v132 = (uint32_t *)sub_432F00(HIBYTE(pArg4));  // sub_432F00 —— 按类型取全局列表对象
      sub_484FF0(v132);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
      return 1;  // 处理完成，返回 1
    // ── [段 20] case 20 = type 21 BUY_ITEM（买物品回报，104 行）—— 成功支读写 Money/Medal/Cash/ItemNumber ──
    //   失败支错误码 switch 4/0xA/0x11/0x13/0x37/9 → 各文案
    case 20:  // case 20 = 类型 21 ENUM_CMDPACKET_BUY_ITEM（买物品回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        nArg5 = 0;
        v447 = 0;  // 设文案编号 0，稍后弹窗
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        *(uint32_t *)ArgList = 0;
        *(uint32_t *)v440 = 0;
        pArg4 = 0;
        v438 = 0;  // 设文案编号 0，稍后弹窗
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        sub_404AD0(ArgList);  // 游标读 4 字节 → ArgList
        sub_404AD0(&v438);  // 游标读 4 字节 → v438
        sub_404AD0(v440);  // 游标读 4 字节 → v440
        sub_404AB0(&nArg5);  // 游标读 2 字节 → nArg5
        sub_404AB0(&v447);  // 游标读 2 字节 → v447
        sub_404AD0(&pArg4);  // 游标读 4 字节 → pArg4
        off_77F3FC(  // 日志打印（printf 风格）
          "Money %d, Medal %d, fp %d, Cash %d, ItemSlotIndex %d, ItemIndex %d, Data %d",  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
          *(uint32_t *)ArgList,  // （上一调用/表达式的参数续行）
          v438,  // （上一调用/表达式的参数续行）
          *(uint32_t *)v440,  // （上一调用/表达式的参数续行）
          (uint16_t)nArg5,  // （上一调用/表达式的参数续行）
          (uint16_t)v447,  // （上一调用/表达式的参数续行）
          pArg4);  // （上一调用/表达式的参数续行）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 40))(  // 虚函数调用（vtable 槽）
          **((uint32_t **)dword_8F852C + 3),  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2);  // 取指针指向的值（参数）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(  // 虚函数调用（vtable 槽）
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),  // （上一调用/表达式的参数续行）
          *(uint32_t *)ArgList);  // 取指针指向的值（参数）
        dword_8F7C0C = *(uint32_t *)v440;  // 写全局 dword_8F7C0C = 游标值 v440
        if ( *(int *)v440 < 0 )  // 字段为负则修正路径
        {
          off_77F3FC(aCriticalError_31, *(uint32_t *)v440);  // 日志打印（printf 风格）
          dword_8F7C0C = 0;  // dword_8F7C0C＝现金(Cash)
        }
        pObj34 = sub_44A980((uint16_t)nArg5);  // sub_44A980 —— 带界索引 getter
        if ( pObj34 != 0 )  // 条件判定 pObj34 != 0
        {
          v134 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj34 + 60))(pObj34, (uint16_t)v447);  // 虚函数调用（vtable 槽）
          v135 = *(uint32_t *)pObj34;
          if ( v134 != 0 )  // 条件判定 v134 != 0
          {
            (*(void (/*thiscall*/ **)(int, unsigned int))(v135 + 48))(pObj34, pArg4);  // 虚函数调用（vtable 槽）
          }
          else  // 否则分支
          {
            v136 = (*(int (/*thiscall*/ **)(int))(v135 + 16))(pObj34);  // 虚函数调用（vtable 槽）
            off_77F3FC((char *)&byte_7246D4, (uint16_t)nArg5, *(uint32_t *)(v136 + 4));  // 日志打印（printf 风格）
          }
        }
        else  // 否则分支
        {
          pObj34 = sub_522300((void *)(uint16_t)v447, pArg4, 0, 0, -1, 1);  // 调用 sub_522300
          sub_484F40((int *)dword_8F852C, (uint16_t)nArg5, pObj34, 1);  // sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
        }
        if ( pObj34 != 0 )  // 条件判定 pObj34 != 0
        {
          v137 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj34 + 56))(pObj34);  // 虚函数调用（vtable 槽）
          sub_432EA0(v137, -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
          if ( *((uint32_t *)dword_8F8528 + 27) == 0 && (uint16_t)nArg5 >= 9u )  // 条件判定
            *(uint32_t *)(*((uint32_t *)dword_8F8528 + 14) + 56) = ((uint16_t)nArg5 - 9) / 32;  // 字段赋值
        }
        sub_47CD00(dword_8F8540);  // 调用 sub_47CD00
        if ( *(uint32_t *)(pArg1 + 12) == 6 )  // 读全局对象字段并与常数比较
        {
          dword_99FF082 = dword_99FF08;  // dword_99FF082 = dword_99FF08（转发）
          if ( dword_99FF08 != 0 )  // 条件判定 dword_99FF08 != 0
            *(uint32_t *)(dword_99FF082 + 4 * sub_48FCA0() + 112) = v438;  // 字段赋值
          else  // 否则分支
            off_77F3FC(byte_72B81C);  // 日志打印（printf 风格）
        }
        return 1;  // 处理完成，返回 1
      }
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
      {
        case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
          v139 = sub_422E70(746);  // 取本地化文案 746
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v139, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          return 1;  // 处理完成，返回 1
        case 0xA:  // case 0xA = 类型 11 ENUM_CMDPACKET_RESPONSE_PEER（P2P 应答回报）
          v140 = sub_422E70(747);  // 取本地化文案 747
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v140, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          return 1;  // 处理完成，返回 1
        case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
          goto LABEL_359;  // 跳转合流点 LABEL_359
        case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
          goto LABEL_361;  // 跳转合流点 LABEL_361
        case 0x37:  // case 0x37 = 类型 56 ENUM_CMDPACKET_SET_PVP_READY_STATE
          v141 = sub_422E70(1342);  // 取本地化文案 1342
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v141, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          break;  // 跳出本分支
        case 9:  // case 9 = 类型 10 ENUM_CMDPACKET_REQUEST_PEER（P2P 请求回报）
          off_77F3FC(aFailFp);  // 日志打印（printf 风格）
          break;  // 跳出本分支
        default:  // 未列出的码值 → 兜底
          break;  // 跳出本分支
      }
      return 1;  // 处理完成，返回 1
    // ── [段 21] case 21 = type 22 RENT_AVATAR（租时装回报）—— 成功支成功写物品 + sub_432EA0 播报（89 行） ──
    case 21:  // case 21 = 类型 22 ENUM_CMDPACKET_RENT_AVATAR（租时装回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        *(uint32_t *)ArgList = 0;
        *(uint32_t *)v440 = 0;
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        sub_404AD0(ArgList);  // 游标读 4 字节 → ArgList
        sub_404AD0(v440);  // 游标读 4 字节 → v440
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC(  // 日志打印（printf 风格）
          "Money %d, Medal %d, Cash %d, ItemNumber %d",  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
          *(uint32_t *)ArgList,  // （上一调用/表达式的参数续行）
          *(uint32_t *)v440,  // （上一调用/表达式的参数续行）
          HIBYTE(nArg5));  // （上一调用/表达式的参数续行）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 40))(  // 虚函数调用（vtable 槽）
          **((uint32_t **)dword_8F852C + 3),  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2);  // 取指针指向的值（参数）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(  // 虚函数调用（vtable 槽）
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),  // （上一调用/表达式的参数续行）
          *(uint32_t *)ArgList);  // 取指针指向的值（参数）
        dword_8F7C0C = *(uint32_t *)v440;  // 写全局 dword_8F7C0C = 游标值 v440
        if ( *(int *)v440 < 0 )  // 字段为负则修正路径
        {
          off_77F3FC(aCriticalError_31, *(uint32_t *)v440);  // 日志打印（printf 风格）
          dword_8F7C0C = 0;  // dword_8F7C0C＝现金(Cash)
        }
        v142 = 1;  // 设文案编号 1，稍后弹窗
        v439 = nullptr;  // v439 = nullptr（转发）
        if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
        {
          do
          {
            pArg4 = 0;
            v447 = 0;  // 设文案编号 0，稍后弹窗
            v438 = 0;  // 设文案编号 0，稍后弹窗
            sub_404AB0(&pArg4);  // 游标读 2 字节 → pArg4
            sub_404AB0(&v447);  // 游标读 2 字节 → v447
            sub_404AD0(&v438);  // 游标读 4 字节 → v438
            off_77F3FC("ItemSlotIndex %d ItemIndex %d Data %d", (uint16_t)pArg4, (uint16_t)v447, v438);  // 日志打印（printf 风格）
            pObj41 = sub_522300((void *)(uint16_t)v447, v438, 0, 0, -1, 1);  // 调用 sub_522300
            pObj13 = pObj41;  // pObj13 = pObj41（转发）
            if ( pObj41 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj41 + 20))(pObj41, 2) != 0 )  // 虚函数调用（vtable 槽）
            {
              sub_484F40((int *)dword_8F8534, (uint16_t)pArg4, pObj13, 1);  // sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
              v145 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj13 + 56))(pObj13);  // 虚函数调用（vtable 槽）
              sub_432EA0(v145, -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
              v146 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj13 + 172))(pObj13);  // 虚函数调用（vtable 槽）
              if ( sub_486820((int *)dword_8F8534, (uint16_t)pArg4, *v146, v142) != 0 )  // 条件判定
                ++v142;  // 自增 v142（循环计数）
            }
            else  // 否则分支
            {
              off_77F3FC(aCriticalError_35, (uint16_t)v447);  // 日志打印（printf 风格）
            }
            v439 = (int *)((char *)v439 + 1);
          }
          while ( (int)v439 < HIBYTE(nArg5) );  // （表达式续行/复合语句）
        }
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v147 = sub_422E70(748);  // 取本地化文案 748
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v147, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0xA:  // case 0xA = 类型 11 ENUM_CMDPACKET_RESPONSE_PEER（P2P 应答回报）
            v148 = sub_422E70(749);  // 取本地化文案 749
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v148, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
LABEL_359:  // 标签 LABEL_359：合流点
            off_77F3FC(aFail_14);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
LABEL_361:  // 标签 LABEL_361：合流点
            off_77F3FC(aFail_13);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 22] case 22 = type 23 EXTEND_AVATAR（续时装回报）—— sub_445150 释放 + sub_44A980 取槽 ──
    case 22:  // case 22 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        *(uint32_t *)ArgList = 0;
        nArg5 = 0;
        pArg4 = 0;
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        *(uint32_t *)v440 = 0;
        sub_404AD0(&nArg5);  // 游标读 4 字节 → nArg5
        sub_404AD0(&pArg4);  // 游标读 4 字节 → pArg4
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        sub_404AB0(ArgList);  // 游标读 2 字节 → ArgList
        sub_404AD0(v440);  // 游标读 4 字节 → v440
        off_77F3FC(  // 日志打印（printf 风格）
          "Money %d, Medal %d, Cash %d, ItemSlotIndex %d, Data %d",  // （上一调用/表达式的参数续行）
          nArg5,  // （上一调用/表达式的参数续行）
          pArg4,  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
          *(uint16_t *)ArgList,  // （上一调用/表达式的参数续行）
          *(uint32_t *)v440);  // 取指针指向的值（参数）
        (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 40))(  // 虚函数调用（vtable 槽）
          **((uint32_t **)dword_8F852C + 3),  // （上一调用/表达式的参数续行）
          nArg5);  // （上一调用/表达式的参数续行）
        (*(void (/*thiscall*/ **)(uint32_t, unsigned int))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(  // 虚函数调用（vtable 槽）
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),  // （上一调用/表达式的参数续行）
          pArg4);  // （上一调用/表达式的参数续行）
        dword_8F7C0C = *(uint32_t *)dword_9B0BBC2;  // 写全局 dword_8F7C0C = 游标值 dword_9B0BBC2
        if ( *(int *)dword_9B0BBC2 < 0 )  // 字段为负则修正路径
        {
          off_77F3FC(aCriticalError_31, *(uint32_t *)dword_9B0BBC2);  // 日志打印（printf 风格）
          dword_8F7C0C = 0;  // dword_8F7C0C＝现金(Cash)
        }
        v149 = sub_44A980(*(uint16_t *)ArgList);  // sub_44A980 —— 带界索引 getter
        pObj16 = __RTDynamicCast(v149, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
        v151 = (int *)pObj16;
        if ( pObj16 != 0 )  // 条件判定 pObj16 != 0
        {
          v152 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj16 + 188))(pObj16);  // 虚函数调用（vtable 槽）
          sub_583AB0(v152);  // sub_583AB0 —— 4 段缓冲拷贝构造（this+0/+18/+8/+46 ← a2 同偏移，46B080=内存复制）
          v153 = *v151;  // v153 = *v151（解引用）
          *(uint32_t *)&psz[4] = *(uint32_t *)v440;  // （表达式续行/复合语句）
          v461 = 1;  // 设文案编号 1，稍后弹窗
          (*(void (/*thiscall*/ **)(int *, char *))(v153 + 184))(v151, &psz[4]);  // 虚函数调用（vtable 槽）
          v461 = -1;
          sub_445150(&psz[4]);  // 调用 sub_445150
        }
        else  // 否则分支
        {
          off_77F3FC(aCriticalError_48);  // 日志打印（printf 风格）
        }
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0xA:  // case 0xA = 类型 11 ENUM_CMDPACKET_RESPONSE_PEER（P2P 应答回报）
            v154 = sub_422E70(750);  // 取本地化文案 750
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v154, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            off_77F3FC(aFail_16);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_15);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 23] case 23 = type 24 SELL_ITEM（卖物品回报）—— Money/ItemSpace/ItemSlotIndex/SellItemNumber ──
    case 23:  // case 23 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        pArg4 = 0;
        *(uint32_t *)ArgList = 0;
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404AB0(&pArg4);  // 游标读 2 字节 → pArg4
        sub_404AB0(ArgList);  // 游标读 2 字节 → ArgList
        off_77F3FC(  // 日志打印（printf 风格）
          "Money %d, ItemSpace %d, ItemSlotIndex %d, SellItemNumber %d",  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
          HIBYTE(nArg5),  // （上一调用/表达式的参数续行）
          (uint16_t)pArg4,  // （上一调用/表达式的参数续行）
          *(uint16_t *)ArgList);  // 取指针指向的值（参数）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 40))(  // 虚函数调用（vtable 槽）
          **((uint32_t **)dword_8F852C + 3),  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2);  // 取指针指向的值（参数）
        v155 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 56))(**((uint32_t **)dword_8F852C  // 虚函数调用（vtable 槽）
                                                                                                 + 3));  // （续行：指针/参数偏移）
        sub_432EA0(v155, -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
        if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
        {
          if ( HIBYTE(nArg5) == 3 )  // 错误码 == 3 分支
          {
            pObj4 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 788))(  // 虚函数调用（vtable 槽）
                     dword_8F7C04,  // （上一调用/表达式的参数续行）
                     (uint16_t)pArg4,  // （上一调用/表达式的参数续行）
                     nArg3);  // （上一调用/表达式的参数续行）
            if ( pObj4 != 0 )  // 条件判定 pObj4 != 0
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 虚函数调用（vtable 槽）
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1080))(dword_8F7C04, (uint16_t)pArg4);  // 虚函数调用（vtable 槽）
          }
        }
        else  // 否则分支
        {
          pObj3 = sub_44A980((uint16_t)pArg4);  // sub_44A980 —— 带界索引 getter
          pObj24 = pObj3;  // pObj24 = pObj3（转发）
          if ( pObj3 != 0 )  // 条件判定 pObj3 != 0
          {
            v158 = *(uint16_t *)ArgList;
            if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 44))(pObj3, nArg32) <= v158 )  // 虚函数调用（vtable 槽）
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj24 + 4))(pObj24, 1);  // 虚函数调用（vtable 槽）
              sub_484F40((int *)dword_8F852C, (uint16_t)pArg4, 0, 1);  // sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
            }
            else  // 否则分支
            {
              (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)pObj24 + 52))(pObj24, v158);  // 虚函数调用（vtable 槽）
            }
          }
        }
        sub_47CD00(dword_8F8540);  // 调用 sub_47CD00
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            off_77F3FC(aFail_19);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_18);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
            off_77F3FC(aFail_17);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x37:  // case 0x37 = 类型 56 ENUM_CMDPACKET_SET_PVP_READY_STATE
            v160 = sub_422E70(1343);  // 取本地化文案 1343
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v160, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x17:  // case 0x17 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
            off_77F3FC(aFailFp_0);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 24] case 24 = type 25 REPAIR_EQUIPMENT（修理回报）—— ITEM_REPAIR 播报 + 耐久回写 ──
    case 24:  // case 24 = 类型 25 ENUM_CMDPACKET_REPAIR_EQUIPMENT（修理装备回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0xA:  // case 0xA = 类型 11 ENUM_CMDPACKET_RESPONSE_PEER（P2P 应答回报）
            v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
            v47 = sub_422E70(751);  // 取本地化文案 751
LABEL_983:  // 标签 LABEL_983：合流点
            sub_43BEE0(v46, v47, -6567706, 0, -1);  // 调用 sub_43BEE0
            break;  // 跳出本分支
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            off_77F3FC(aFail_21);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_20);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
        return 1;  // 处理完成，返回 1
      }
      v161 = 0;  // 设文案编号 0，稍后弹窗
      *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
      pArg4 = 0;
      sub_404AD0(&pArg4);  // 游标读 4 字节 → pArg4
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      sub_404AB0(dword_9B0BBC2);  // 游标读 2 字节 → dword_9B0BBC2
      off_77F3FC("Money %d, ItemSpace %d, ItemSlotIndex %d", pArg4, HIBYTE(nArg5), *(uint16_t *)dword_9B0BBC2);  // 日志打印（printf 风格）
      (*(void (/*thiscall*/ **)(uint32_t, unsigned int))(***((uint32_t ***)dword_8F852C + 3) + 40))(  // 虚函数调用（vtable 槽）
        **((uint32_t **)dword_8F852C + 3),  // （上一调用/表达式的参数续行）
        pArg4);  // （上一调用/表达式的参数续行）
      if ( *(uint16_t *)dword_9B0BBC2 == 0xFFFF )  // 条件判定
      {
        pObj22 = dword_8F7C04;  // pObj22 = dword_8F7C04（转发）
        do
        {
          pObj26 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj22 + 792))(pObj22, v161);  // 虚函数调用（vtable 槽）
          if ( pObj26 != 0 )  // 条件判定 pObj26 != 0
          {
            v164 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj26 + 172))(pObj26);  // 虚函数调用（vtable 槽）
            v165 = sub_41A5E0(v164 + 18);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj26 + 192))(pObj26, v165);  // 虚函数调用（vtable 槽）
          }
          ++v161;  // 自增 v161（循环计数）
        }
        while ( v161 < 18 );  // 循环：v161 < 18 持续（计数循环）
        v166 = 0;  // 设文案编号 0，稍后弹窗
        for ( HIDWORD(Time) = *((uint32_t *)dword_8F852C + 2); v166 < SHIDWORD(Time); ++v166 )  // （表达式/调用续行）
        {
          pObj15 = sub_44A980(v166);  // sub_44A980 —— 带界索引 getter
          pObj8 = pObj15;  // pObj8 = pObj15（转发）
          if ( pObj15 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj15 + 20))(pObj15, 2) != 0 )  // 虚函数调用（vtable 槽）
          {
            v169 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 188))(pObj8);  // 虚函数调用（vtable 槽）
            v170 = sub_41A5E0(v169 + 32);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
            v171 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 172))(pObj8);  // 虚函数调用（vtable 槽）
            if ( v170 < sub_41A5E0(v171 + 18) )  // 条件判定
            {
              v172 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 172))(pObj8);  // 虚函数调用（vtable 槽）
              v173 = sub_41A5E0(v172 + 18);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj8 + 192))(pObj8, v173);  // 虚函数调用（vtable 槽）
            }
          }
        }
        goto LABEL_418;  // 跳转合流点 LABEL_418
      }
      if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
      {
        if ( HIBYTE(nArg5) != 3 )  // 错误码 != 3 分支
        {
LABEL_418:  // 标签 LABEL_418：合流点
          sub_44E850(dword_8F8528, 26);  // sub_44E850 —— 按池号批量回收活动对象
          sub_432EA0("ITEM_REPAIR", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
          return 1;  // 处理完成，返回 1
        }
        pObj31 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(  // 虚函数调用（vtable 槽）
                 dword_8F7C04,  // （上一调用/表达式的参数续行）
                 *(uint16_t *)dword_9B0BBC2);  // 取指针指向的值（参数）
        pObj28 = pObj31;  // pObj28 = pObj31（转发）
        if ( pObj31 != 0 )  // 条件判定 pObj31 != 0
        {
          v176 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj31 + 172))(pObj31, nArg32);  // 虚函数调用（vtable 槽）
          goto LABEL_416;  // 跳转合流点 LABEL_416
        }
      }
      else  // 否则分支
      {
        pObj18 = sub_44A980(*(uint16_t *)dword_9B0BBC2);  // sub_44A980 —— 带界索引 getter
        pObj28 = pObj18;  // pObj28 = pObj18（转发）
        if ( pObj18 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj18 + 20))(pObj18, 2) != 0 )  // 虚函数调用（vtable 槽）
        {
          v176 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj28 + 172))(pObj28, nArg32);  // 虚函数调用（vtable 槽）
LABEL_416:  // 标签 LABEL_416：合流点
          v178 = sub_41A5E0(v176 + 18);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj28 + 192))(pObj28, v178);  // 虚函数调用（vtable 槽）
          goto LABEL_418;  // 跳转合流点 LABEL_418
        }
      }
      off_77F3FC((char *)&byte_72B554);  // 日志打印（printf 风格）
      goto LABEL_418;  // 跳转合流点 LABEL_418
    // ── [段 25] case 25 = type 26 SET_ITEMTRADE_STATE（交易状态回报） ──
    case 25:  // case 25 = 类型 26 ENUM_CMDPACKET_SET_ITEMTRADE_STATE（交易状态回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 1:  // case 1 = 类型 2 ENUM_CMDPACKET_SET_UDP_IP_PORT
            v179 = sub_422E70(752);  // 取本地化文案 752
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v179, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            off_77F3FC(aFail_24);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v180 = sub_422E70(753);  // 取本地化文案 753
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v180, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_23);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 7:  // case 7 = 类型 8 ENUM_CMDPACKET_GET_USERINFO
            off_77F3FC(aFail_22);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 26] case 26 = type 27 COMPOUND_ITEM（合成回报，148 行）—— InputItemTypeNumber + 逐项 Material 装配 ──
    //   OutputItemTypeNumber 逐条输出（SlotIndex/ItemIndex/Data）→ sub_522300 PO 工厂建产物
    case 26:  // case 26 = 类型 27 ENUM_CMDPACKET_COMPOUND_ITEM（合成物品回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        off_77F3FC("InputItemTypeNumber %d", HIBYTE(pArg4));  // 日志打印（printf 风格）
        v181 = 0;  // 设文案编号 0，稍后弹窗
        if ( HIBYTE(pArg4) != 0 )  // 第二字段 != 0
        {
          do
          {
            HIBYTE(v444) = 0;  // 清 v444 高字节（即将读取）
            v447 = 0;  // 设文案编号 0，稍后弹窗
            v445 = 0;  // 设文案编号 0，稍后弹窗
            sub_404A90((uint8_t *)&v444 + 3);  // 游标读 1 字节 → v444 高位（错误码字段）
            sub_404AB0(&v447);  // 游标读 2 字节 → v447
            sub_404AD0(&v445);  // 游标读 4 字节 → v445
            off_77F3FC("ItemSpace %d, SlotIndex %d, ItemNumber %d", HIBYTE(v444), (uint16_t)v447, v445);  // 日志打印（printf 风格）
            if ( HIBYTE(v444) != 0 )  // 条件判定
            {
              if ( HIBYTE(v444) == 3 && dword_8F7C04 != 0 )  // 条件判定
              {
                pObj20 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 788))(  // 虚函数调用（vtable 槽）
                         dword_8F7C04,  // （上一调用/表达式的参数续行）
                         (uint16_t)v447);  // （上一调用/表达式的参数续行）
                if ( pObj20 != 0 )  // 条件判定 pObj20 != 0
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj20 + 4))(pObj20, 1);  // 虚函数调用（vtable 槽）
              }
            }
            else  // 否则分支
            {
              pObj5 = sub_44A980((uint16_t)v447);  // sub_44A980 —— 带界索引 getter
              v183 = __RTDynamicCast(
                       pObj5,  // （上一调用/表达式的参数续行）
                       0,  // （上一调用/表达式的参数续行）
                       &IRDItem `RTTI Type Descriptor',  // （上一调用/表达式的参数续行）
                       &CNRecipeStackable `RTTI Type Descriptor',  // （上一调用/表达式的参数续行）
                       0);  // （上一调用/表达式的参数续行）
              if ( v183 != 0 )  // 条件判定 v183 != 0
                dword_795D48 = *(uint32_t *)(v183 + 164);  // 读字段 dword_795D48 = v183 + 164
              if ( (uint16_t)v447 != 0  // 条件判定
                && (v184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 44))(pObj5)) <= (unsigned int)v445 )  // 虚函数调用（vtable 槽）
              {
                sub_484D50((int *)dword_8F852C, (uint16_t)v447);  // sub_484D50 —— 技能槽清空（按槽类型分流）
              }
              else  // 否则分支
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 52))(pObj5, v445);  // 虚函数调用（vtable 槽）
              }
            }
            ++v181;  // 自增 v181（循环计数）
          }
          while ( v181 < HIBYTE(pArg4) );  // 循环直到读满计数
        }
        v186 = sub_44E8D0((char *)dword_8F8528, (void *)0x22, 0, 0);  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
        HIDWORD(Time) = __RTDynamicCast(  // 全局/复合字段赋值
                          v186,  // （上一调用/表达式的参数续行）
                          0,  // （上一调用/表达式的参数续行）
                          &IRDPopupWindow `RTTI Type Descriptor',  // （上一调用/表达式的参数续行）
                          &CNRDCompoundResultWindow `RTTI Type Descriptor',  // （上一调用/表达式的参数续行）
                          0);  // （上一调用/表达式的参数续行）
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("OutputItemTypeNumber %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        v187 = 0;  // 设文案编号 0，稍后弹窗
        if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
        {
          do
          {
            v447 = 0;  // 设文案编号 0，稍后弹窗
            v441 = 0;  // 设文案编号 0，稍后弹窗
            v445 = 0;  // 设文案编号 0，稍后弹窗
            sub_404AB0(&v447);  // 游标读 2 字节 → v447
            sub_404AB0(&v441);  // 游标读 2 字节 → v441
            sub_404AD0(&v445);  // 游标读 4 字节 → v445
            off_77F3FC("SlotIndex %d, ItemIndex %d, Data %d", (uint16_t)v447, (uint16_t)v441, v445);  // 日志打印（printf 风格）
            if ( (uint16_t)v447 < *((int *)dword_8F852C + 2)  // 条件判定
              && (pObj19 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * (uint16_t)v447)) != 0 )  // （表达式/调用续行）
            {
              v189 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj19 + 60))(pObj19, (uint16_t)v441);  // 虚函数调用（vtable 槽）
              v190 = *(uint32_t *)pObj19;
              if ( v189 != 0 )  // 条件判定 v189 != 0
              {
                (*(void (/*thiscall*/ **)(int, int))(v190 + 48))(pObj19, v445);  // 虚函数调用（vtable 槽）
              }
              else  // 否则分支
              {
                v191 = (*(int (/*thiscall*/ **)(int))(v190 + 16))(pObj19);  // 虚函数调用（vtable 槽）
                off_77F3FC(aD_1, (uint16_t)v447, *(uint32_t *)(v191 + 4));  // 日志打印（printf 风格）
              }
            }
            else  // 否则分支
            {
              pObj19 = sub_522300((void *)(uint16_t)v441, v445, 0, 0, -1, 1);  // 调用 sub_522300
              sub_484F40((int *)dword_8F852C, (uint16_t)v447, pObj19, 1);  // sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
            }
            v114 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj19 + 20))(pObj19, 1) == 0;  // 虚函数调用（vtable 槽）
            v192 = v445;  // v192 = v445（转发）
            if ( v114 )  // 条件判定
              v192 = 1;  // 设文案编号 1，稍后弹窗
            sub_63F2F0(pObj19, v192);  // sub_63F2F0 —— 合成结果文本（459700/4015C0/422E70/45A340/69A5F0/477AF0，75 行）
            if ( v187 == HIBYTE(nArg5) - 1 )  // 条件判定
            {
              v193 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj19 + 56))(pObj19);  // 虚函数调用（vtable 槽）
              sub_432EA0(v193, -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
            }
            ++v187;  // 自增 v187（循环计数）
          }
          while ( v187 < HIBYTE(nArg5) );  // 循环直到读满计数
        }
        goto LABEL_265;  // 跳转合流点 LABEL_265
      }
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
      {
        case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
          v194 = sub_422E70(754);  // 取本地化文案 754
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v194, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          break;  // 跳出本分支
        case 0xE:  // case 0xE = 类型 15 ENUM_CMDPACKET_START_GAME（开始游戏回报）
          v195 = sub_422E70(755);  // 取本地化文案 755
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v195, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          break;  // 跳出本分支
        case 0x15:  // case 0x15 = 类型 22 ENUM_CMDPACKET_RENT_AVATAR（租时装回报）
          v196 = sub_422E70(756);  // 取本地化文案 756
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v196, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          break;  // 跳出本分支
        case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
          v197 = sub_422E70(757);  // 取本地化文案 757
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v197, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          break;  // 跳出本分支
        case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
          v198 = sub_422E70(758);  // 取本地化文案 758
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v198, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          break;  // 跳出本分支
        case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
          v199 = sub_422E70(759);  // 取本地化文案 759
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v199, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          break;  // 跳出本分支
        case 0x17:  // case 0x17 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
          off_77F3FC(aCriticalError_49);  // 日志打印（printf 风格）
          break;  // 跳出本分支
        default:  // 未列出的码值 → 兜底
          break;  // 跳出本分支
      }
      return 1;  // 处理完成，返回 1
    // ── [段 27] case 27 = type 28 DISJOINT_ITEM（分解回报，91 行）—— SlotIndex/OutputItemTypeNumber 族 ──
    case 27:  // case 27 = 类型 28 ENUM_CMDPACKET_DISJOINT_ITEM（分解物品回报）
      sub_54D2B0(0);  // sub_54D2B0 —— 21 行小辅助
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        sub_404AB0(dword_9B0BBC2);  // 游标读 2 字节 → dword_9B0BBC2
        off_77F3FC("SlotIndex %d", *(uint16_t *)dword_9B0BBC2);  // 日志打印（printf 风格）
        sub_4850B0((int *)dword_8F852C, *(uint16_t *)dword_9B0BBC2, 1u);  // sub_4850B0 —— 本地命令 0 执行：槽值设置或扣减（op 18）
        v200 = sub_44E8D0((char *)dword_8F8528, (void *)0x18, 0, 0);  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
        HIDWORD(Time) = __RTDynamicCast(  // 全局/复合字段赋值
                          v200,  // （上一调用/表达式的参数续行）
                          0,  // （上一调用/表达式的参数续行）
                          &IRDPopupWindow `RTTI Type Descriptor',  // （上一调用/表达式的参数续行）
                          &CNRDItemDisjointResultWindow `RTTI Type Descriptor',  // （上一调用/表达式的参数续行）
                          0);  // （上一调用/表达式的参数续行）
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("OutputItemTypeNumber %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        v201 = 0;  // 设文案编号 0，稍后弹窗
        if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
        {
          do
          {
            pArg4 = 0;
            v445 = 0;  // 设文案编号 0，稍后弹窗
            v447 = 0;  // 设文案编号 0，稍后弹窗
            sub_404AB0(&pArg4);  // 游标读 2 字节 → pArg4
            sub_404AB0(&v445);  // 游标读 2 字节 → v445
            sub_404AD0(&v447);  // 游标读 4 字节 → v447
            off_77F3FC("SlotIndex %d, ItemIndex %d, Data %d", (uint16_t)pArg4, (uint16_t)v445, v447);  // 日志打印（printf 风格）
            pObj39 = sub_44A980((uint16_t)pArg4);  // sub_44A980 —— 带界索引 getter
            if ( pObj39 != 0 )  // 条件判定 pObj39 != 0
            {
              v203 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj39 + 60))(pObj39, (uint16_t)v445);  // 虚函数调用（vtable 槽）
              v204 = *(uint32_t *)pObj39;
              if ( v203 != 0 )  // 条件判定 v203 != 0
              {
                (*(void (/*thiscall*/ **)(int, int))(v204 + 48))(pObj39, v447);  // 虚函数调用（vtable 槽）
              }
              else  // 否则分支
              {
                v205 = (*(int (/*thiscall*/ **)(int))(v204 + 16))(pObj39);  // 虚函数调用（vtable 槽）
                off_77F3FC(aD_1, (uint16_t)pArg4, *(uint32_t *)(v205 + 4));  // 日志打印（printf 风格）
              }
            }
            else  // 否则分支
            {
              pObj39 = sub_522300((void *)(uint16_t)v445, v447, 0, 0, -1, 1);  // 调用 sub_522300
              sub_484F40((int *)dword_8F852C, (uint16_t)pArg4, pObj39, 1);  // sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
            }
            v114 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj39 + 20))(pObj39, 1) == 0;  // 虚函数调用（vtable 槽）
            v206 = v447;  // v206 = v447（转发）
            if ( v114 )  // 条件判定
              v206 = 1;  // 设文案编号 1，稍后弹窗
            sub_63DFB0(pObj39, v206);  // sub_63DFB0 —— 奖励文本拼装（459700/4014D0/63DF50 + 477AF0 + 45A340，112 行）
            if ( v201 == HIBYTE(nArg5) - 1 )  // 条件判定
            {
              v207 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj39 + 56))(pObj39);  // 虚函数调用（vtable 槽）
              sub_432EA0(v207, -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
            }
            ++v201;  // 自增 v201（循环计数）
          }
          while ( v201 < HIBYTE(nArg5) );  // 循环直到读满计数
        }
        goto LABEL_489;  // 跳转合流点 LABEL_489
      }
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
      {
        case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
          v208 = sub_422E70(760);  // 取本地化文案 760
          break;  // 跳出本分支
        case 0x17:  // case 0x17 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
          v208 = sub_422E70(761);  // 取本地化文案 761
          break;  // 跳出本分支
        case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
          v208 = sub_422E70(762);  // 取本地化文案 762
          break;  // 跳出本分支
        case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
          v208 = sub_422E70(763);  // 取本地化文案 763
          break;  // 跳出本分支
        case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
          v208 = sub_422E70(764);  // 取本地化文案 764
          break;  // 跳出本分支
        default:  // 未列出的码值 → 兜底
          goto LABEL_747;  // 跳转合流点 LABEL_747
      }
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v208, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
      goto LABEL_747;  // 跳转合流点 LABEL_747
    // ── [段 28] case 28 = type 29 USE_LOTTERY_ITEM（抽奖物品回报）—— LotteryItemSlotIndex + 逐奖逐项 ──
    case 28:  // case 28 = 类型 29 ENUM_CMDPACKET_USE_LOTTERY_ITEM（抽奖物品回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        pArg4 = 0;
        sub_404AB0(&pArg4);  // 游标读 2 字节 → pArg4
        off_77F3FC("LotteryItemSlotIndex %d", (uint16_t)pArg4);  // 日志打印（printf 风格）
        pArg42 = pArg4;  // pArg42 = pArg4（转发）
        pObj27 = sub_44A980((uint16_t)pArg4);  // sub_44A980 —— 带界索引 getter
        if ( pObj27 != 0 )  // 条件判定 pObj27 != 0
        {
          if ( pArg42 != 0 && (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj27 + 44))(pObj27) <= 1 )  // 虚函数调用（vtable 槽）
            sub_484D50((int *)dword_8F852C, (uint16_t)pArg4);  // sub_484D50 —— 技能槽清空（按槽类型分流）
          else  // 否则分支
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj27 + 52))(pObj27, 1);  // 虚函数调用（vtable 槽）
        }
        else  // 否则分支
        {
          off_77F3FC(aCriticalError_36);  // 日志打印（printf 风格）
        }
        nArg5 = 0;
        v445 = 0;  // 设文案编号 0，稍后弹窗
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        v447 = 0;  // 设文案编号 0，稍后弹窗
        sub_404AB0(&nArg5);  // 游标读 2 字节 → nArg5
        sub_404AB0(&v445);  // 游标读 2 字节 → v445
        sub_404AD0(&v447);  // 游标读 4 字节 → v447
        sub_404AB0(dword_9B0BBC2);  // 游标读 2 字节 → dword_9B0BBC2
        off_77F3FC(  // 日志打印（printf 风格）
          "SlotIndex %d, ItemIndex %d, Data %d, Durability %d",  // （上一调用/表达式的参数续行）
          (uint16_t)nArg5,  // （上一调用/表达式的参数续行）
          (uint16_t)v445,  // （上一调用/表达式的参数续行）
          v447,  // （上一调用/表达式的参数续行）
          *(uint16_t *)dword_9B0BBC2);  // 取指针指向的值（参数）
        pObj21 = sub_44A980((uint16_t)nArg5);  // sub_44A980 —— 带界索引 getter
        pObj9 = pObj21;  // pObj9 = pObj21（转发）
        if ( pObj21 != 0 )  // 条件判定 pObj21 != 0
        {
          v213 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj21 + 60))(pObj21, (uint16_t)v445);  // 虚函数调用（vtable 槽）
          v214 = *(uint32_t *)pObj9;
          if ( v213 != 0 )  // 条件判定 v213 != 0
          {
            (*(void (/*thiscall*/ **)(int, int))(v214 + 48))(pObj9, v447);  // 虚函数调用（vtable 槽）
          }
          else  // 否则分支
          {
            v215 = (*(int (/*thiscall*/ **)(int))(v214 + 16))(pObj9);  // 虚函数调用（vtable 槽）
            off_77F3FC(aD_1, (uint16_t)nArg5, *(uint32_t *)(v215 + 4));  // 日志打印（printf 风格）
          }
        }
        else  // 否则分支
        {
          pObj9 = sub_522300((void *)(uint16_t)v445, v447, 0, 0, *(uint16_t *)dword_9B0BBC2, 1);  // 调用 sub_522300
          sub_484F40((int *)dword_8F852C, (uint16_t)nArg5, pObj9, 1);  // sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
        }
        if ( pObj9 != 0 )  // 条件判定 pObj9 != 0
        {
          sub_44E8D0((char *)dword_8F8528, (void *)0x23, pObj9, 1);  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
          v216 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 56))(pObj9);  // 虚函数调用（vtable 槽）
          sub_432EA0(v216, -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
        }
LABEL_489:  // 标签 LABEL_489：合流点
        sub_47CD00(dword_8F8540);  // 调用 sub_47CD00
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            v217 = sub_422E70(765);  // 取本地化文案 765
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v217, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0xE:  // case 0xE = 类型 15 ENUM_CMDPACKET_START_GAME（开始游戏回报）
            v218 = sub_422E70(766);  // 取本地化文案 766
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v218, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v219 = sub_422E70(767);  // 取本地化文案 767
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v219, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            v220 = sub_422E70(768);  // 取本地化文案 768
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v220, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 29] case 29 = type 30 CHANGE_SKILLSLOT（改技能栏回报）—— sub_483DA0 落表 ──
    case 29:  // case 29 = 类型 30 ENUM_CMDPACKET_CHANGE_SKILLSLOT（改技能栏回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("SlotIndex1 %d, SlotIndex2 %d", HIBYTE(pArg4), HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( sub_483DA0((int *)dword_8F853C, HIBYTE(pArg4), HIBYTE(nArg5)) == 0 )  // 条件判定
        {
          v221 = (char *)sub_422E70(769);  // 取本地化文案 769
          off_77F3F8(v222, v221);  // 文本输出/弹窗提示
        }
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 21 )  // 错误码 == 21 分支
        {
          off_77F3FC(aFail_25);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 19 )  // 否则错误码 == 19
        {
          off_77F3FC(aFail_3);  // 日志打印（printf 风格）
        }
        *((uint32_t *)dword_8F853C + 2) = (*((uint32_t *)dword_8F853C + 2) - 1)  // （表达式/调用续行）
                                      & ((*((uint32_t *)dword_8F853C + 2) - 1 <= 0) - 1);  // （表达式续行/复合语句）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 30] case 30 = type 31 BUY_SKILL（学技能回报）—— Sp/SlotIndex/SkillIndex/Level + sub_47DC90 族 ──
    case 30:  // case 30 = 类型 31 ENUM_CMDPACKET_BUY_SKILL（学技能回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(v444) = 0;  // 清 v444 高字节（即将读取）
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        sub_404AB0(dword_9B0BBC2);  // 游标读 2 字节 → dword_9B0BBC2
        sub_404A90((uint8_t *)&v444 + 3);  // 游标读 1 字节 → v444 高位（错误码字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        off_77F3FC(  // 日志打印（printf 风格）
          "Sp %d, SlotIndex %d, SkillIndex %d, Level %d",  // （上一调用/表达式的参数续行）
          *(uint16_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
          HIBYTE(v444),  // （上一调用/表达式的参数续行）
          HIBYTE(nArg5),  // （上一调用/表达式的参数续行）
          HIBYTE(pArg4));  // （上一调用/表达式的参数续行）
        Value = *(uint16_t *)dword_9B0BBC2;
        sub_57A3C0(HIBYTE(v444), HIBYTE(nArg5));  // sub_57A3C0 —— 对象/控件辅助（47DC90/483D50）
        v223 = sub_47DC90(HIBYTE(nArg5));  // 调用 sub_47DC90
        sub_47DEC0(0, HIBYTE(pArg4));  // 调用 sub_47DEC0
        *(uint32_t *)(v223 + 540) = 0;  // 写字段 v223 + 540 = 0（uint32）
        sub_583A40(v223);  // sub_583A40 —— 清空对象 +588 起的字符串槽（+601/+602 字节置 0，尾调 698F90 析构字符串）
        sub_47E4F0();  // 调用 sub_47E4F0
        if ( dword_8F7C04 != 0 )  // 条件判定 dword_8F7C04 != 0
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 1136))(  // 虚函数调用（vtable 槽）
            dword_8F7C04,  // （上一调用/表达式的参数续行）
            HIBYTE(nArg5),  // （上一调用/表达式的参数续行）
            HIBYTE(pArg4));  // （上一调用/表达式的参数续行）
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1152))(dword_8F7C04);  // 虚函数调用（vtable 槽）
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1156))(dword_8F7C04);  // 虚函数调用（vtable 槽）
        }
        if ( *((uint32_t *)dword_8F8528 + 26) == 3 )  // 条件判定
          sub_583A60(*((uint32_t *)dword_8F8528 + 17));  // sub_583A60 —— 读取 this+79 槽位（非 0 时调 0x5512D0 = 任务文本设置），0x583B90 流程取任务名用
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            off_77F3FC(aFail_27);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x15:  // case 0x15 = 类型 22 ENUM_CMDPACKET_RENT_AVATAR（租时装回报）
            off_77F3FC(aFail_26);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
            v224 = sub_422E70(770);  // 取本地化文案 770
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v224, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 31] case 31 = type 32 INCREASE_STATUS（加属性点回报，187 行）—— ★ SP_GET 播报 ──
    //   成功支：Level/Exp1/Exp2/Exp3/Sp 全量刷新 + sub_49D920 派生面板；失败支错误码分派
    case 31:  // case 31 = 类型 32 ENUM_CMDPACKET_INCREASE_STATUS（加属性点回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        v447 = 0;  // 设文案编号 0，稍后弹窗
        pArg4 = 0;
        sub_404AB0(dword_9B0BBC2);  // 游标读 2 字节 → dword_9B0BBC2
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404AD0(&pArg4);  // 游标读 4 字节 → pArg4
        sub_404AB0(&v447);  // 游标读 2 字节 → v447
        off_77F3FC(  // 日志打印（printf 风格）
          "SlotIndex %d, StatusType %d, ChangeValue %d, ChangeSubValue %d",  // （上一调用/表达式的参数续行）
          *(uint16_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
          HIBYTE(nArg5),  // （上一调用/表达式的参数续行）
          pArg4,  // （上一调用/表达式的参数续行）
          (uint16_t)v447);  // （上一调用/表达式的参数续行）
        sub_4850B0((int *)dword_8F852C, *(uint16_t *)dword_9B0BBC2, 1u);  // sub_4850B0 —— 本地命令 0 执行：槽值设置或扣减（op 18）
        v225 = HIBYTE(nArg5);
        if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
        {
          if ( HIBYTE(nArg5) == 1 )  // 错误码 == 1 分支
          {
            pArg43 = pArg4;  // pArg43 = pArg4（转发）
            v228 = (const char *)sub_422E70(772);  // 取本地化文案 772
            sprintf(Buffer, v228, pArg43);  // 格式化字符串到缓冲
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
            pObj = dword_8F7C04;  // pObj = dword_8F7C04（转发）
            if ( dword_8F7C04 != 0 )  // 条件判定 dword_8F7C04 != 0
            {
              v230 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);  // 虚函数调用（vtable 槽）
              v231 = *(uint32_t *)pObj;
              v232 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 1032))(pObj, *v230);  // 虚函数调用（vtable 槽）
              (*(void (/*thiscall*/ **)(int, unsigned int))(v231 + 1036))(pObj, pArg4 + *(uint32_t *)(v232 + 48));  // 虚函数调用（vtable 槽）
              if ( *(uint32_t *)(dword_8F7A24 + 12) != 3 )  // 读全局对象字段并与常数比较
              {
                v233 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1032))(pObj) + 44);  // 虚函数调用（vtable 槽）
                if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1032))(pObj) + 40) >= v233 )  // 虚函数调用（vtable 槽）
                {
                  v234 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
                  v235 = sub_422E70(773);  // 取本地化文案 773
                  sub_43BEE0(v234, v235, -6567706, 0, -1);  // 调用 sub_43BEE0
                }
              }
            }
            if ( (uint16_t)v447 != 0 && *(uint32_t *)(dword_8F7A24 + 12) != 3 )  // 条件判定
            {
              sub_57A430(1);  // sub_57A430 —— std::string 构造辅助 6（698F90）
              v419 = (uint16_t)v447;
              v236 = (const char *)sub_422E70(774);  // 取本地化文案 774
              sprintf(v452, v236, v419);  // 格式化字符串到缓冲
              sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v452, -6567706, 0, -1);  // 调用 sub_43BEE0
              sub_432EA0("SP_GET", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
              Value += (uint16_t)v447;  // 累计 Value += (uint16_t)v447
            }
          }
          else  // 否则分支
          {
            pObj40 = dword_8F7C04;  // pObj40 = dword_8F7C04（转发）
            v238 = 0;  // 设文案编号 0，稍后弹窗
            if ( dword_8F7C04 != 0 )  // 条件判定 dword_8F7C04 != 0
            {
              v238 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1052))(dword_8F7C04);  // 虚函数调用（vtable 槽）
              v225 = HIBYTE(nArg5);
            }
            switch ( v225 )  // （表达式/调用续行）
            {
              case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
                v420 = pArg4 / 0xA;  // v420 = pArg4 / 0xA（除法）
                v239 = (const char *)sub_422E70(775);  // 取本地化文案 775
                sprintf(v452, v239, v420);  // 格式化字符串到缓冲
                if ( v238 != 0 )  // 条件判定 v238 != 0
                  *(uint32_t *)v238 += pArg4;  // v238 += pArg4（指针推进/累加）
                break;  // 跳出本分支
              case 3:  // case 3 = 类型 4 ENUM_CMDPACKET_SELECT_CHARACTER（选角回报）
                v421 = pArg4 / 0xA;  // v421 = pArg4 / 0xA（除法）
                v240 = (const char *)sub_422E70(776);  // 取本地化文案 776
                sprintf(v452, v240, v421);  // 格式化字符串到缓冲
                if ( v238 != 0 )  // 条件判定 v238 != 0
                  *(uint32_t *)(v238 + 4) += pArg4;  // 字段 v238+4 += pArg4
                break;  // 跳出本分支
              case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
                v422 = pArg4 / 0xA;  // v422 = pArg4 / 0xA（除法）
                v241 = (const char *)sub_422E70(777);  // 取本地化文案 777
                sprintf(v452, v241, v422);  // 格式化字符串到缓冲
                if ( v238 != 0 )  // 条件判定 v238 != 0
                  *(uint16_t *)(v238 + 8) += pArg4;  // 字段赋值
                break;  // 跳出本分支
              case 5:  // case 5 = 类型 6 ENUM_CMDPACKET_DELETE_CHARACTER（删角回报）
                v423 = pArg4 / 0xA;  // v423 = pArg4 / 0xA（除法）
                v242 = (const char *)sub_422E70(778);  // 取本地化文案 778
                sprintf(v452, v242, v423);  // 格式化字符串到缓冲
                if ( v238 != 0 )  // 条件判定 v238 != 0
                  *(uint16_t *)(v238 + 10) += pArg4;  // 字段赋值
                break;  // 跳出本分支
              case 6:  // case 6 = 类型 7 ENUM_CMDPACKET_RETURN_SELECT_CHARACTER（返回选角）
                v424 = pArg4 / 0xA;  // v424 = pArg4 / 0xA（除法）
                v243 = (const char *)sub_422E70(779);  // 取本地化文案 779
                sprintf(v452, v243, v424);  // 格式化字符串到缓冲
                if ( v238 != 0 )  // 条件判定 v238 != 0
                  *(uint16_t *)(v238 + 12) += pArg4;  // 字段赋值
                break;  // 跳出本分支
              case 7:  // case 7 = 类型 8 ENUM_CMDPACKET_GET_USERINFO
                v425 = pArg4 / 0xA;  // v425 = pArg4 / 0xA（除法）
                v244 = (const char *)sub_422E70(780);  // 取本地化文案 780
                sprintf(v452, v244, v425);  // 格式化字符串到缓冲
                if ( v238 != 0 )  // 条件判定 v238 != 0
                  *(uint16_t *)(v238 + 14) += pArg4;  // 字段赋值
                break;  // 跳出本分支
              case 8:  // case 8 = 类型 9 ENUM_CMDPACKET_RECOVER_STAMINA（疲劳恢复回报）
                v426 = pArg4 / 0xA;  // v426 = pArg4 / 0xA（除法）
                v245 = (const char *)sub_422E70(781);  // 取本地化文案 781
                sprintf(v452, v245, v426);  // 格式化字符串到缓冲
                if ( v238 != 0 )  // 条件判定 v238 != 0
                  *(uint16_t *)(v238 + 64) += pArg4;  // 字段赋值
                break;  // 跳出本分支
              case 9:  // case 9 = 类型 10 ENUM_CMDPACKET_REQUEST_PEER（P2P 请求回报）
                v427 = pArg4 / 0xA;  // v427 = pArg4 / 0xA（除法）
                v246 = (const char *)sub_422E70(782);  // 取本地化文案 782
                sprintf(v452, v246, v427);  // 格式化字符串到缓冲
                if ( v238 != 0 )  // 条件判定 v238 != 0
                {
                  *(uint16_t *)(v238 + 16) += pArg4;  // 字段赋值
                  *(uint16_t *)(v238 + 18) += pArg4;  // 字段赋值
                  *(uint16_t *)(v238 + 20) += pArg4;  // 字段赋值
                  *(uint16_t *)(v238 + 22) += pArg4;  // 字段赋值
                }
                break;  // 跳出本分支
              case 10:  // case 10 = 类型 11 ENUM_CMDPACKET_RESPONSE_PEER（P2P 应答回报）
                v247 = sub_422E70(783);  // 取本地化文案 783
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v247, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
                v248 = (const char *)sub_422E70(784);  // 取本地化文案 784
                sprintf(v452, v248);  // 格式化字符串到缓冲
                sub_57A430(1);  // sub_57A430 —— std::string 构造辅助 6（698F90）
                break;  // 跳出本分支
              default:  // 未列出的码值 → 兜底
                break;  // 跳出本分支
            }
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v452, -6567706, 0, -1);  // 调用 sub_43BEE0
            if ( pObj40 != 0 )  // 条件判定 pObj40 != 0
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj40 + 1048))(pObj40, v238);  // 虚函数调用（vtable 槽）
              v249 = *(uint32_t *)pObj40;
              LOBYTE(v250) = sub_41C210(v439) == 0;  // 复合字段拆分/赋值
              (*(void (/*thiscall*/ **)(int, int))(v249 + 1056))(pObj40, v250);  // 虚函数调用（vtable 槽）
            }
          }
        }
        else  // 否则分支
        {
          if ( dword_8F7C04 != 0 )  // 条件判定 dword_8F7C04 != 0
          {
            v226 = *(uint32_t *)(dword_8F7A24 + 12);  // 读字段 v226 = (uint32)dword_8F7A24+12
            if ( v226 == 3 || v226 == 4 || v226 == 6 )  // 条件判定
              (*(void (/*stdcall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1232))(1);  // 虚函数调用（vtable 槽）
          }
          sub_57A430(1);  // sub_57A430 —— std::string 构造辅助 6（698F90）
          pArg44 = pArg4;  // pArg44 = pArg4（转发）
          v227 = (const char *)sub_422E70(771);  // 取本地化文案 771
          sprintf(Buffer, v227, pArg44);  // 格式化字符串到缓冲
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
          sub_432EA0("SP_GET", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
          Value += pArg4;  // 累计 Value += pArg4
        }
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_28);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            v251 = sub_422E70(785);  // 取本地化文案 785
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v251, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 1:  // case 1 = 类型 2 ENUM_CMDPACKET_SET_UDP_IP_PORT
            v252 = sub_422E70(3002);  // 取本地化文案 3002
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v252, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 32] case 32 = type 33 ACCEPT_QUEST（接任务回报）—— QuestIndex/QuestTrigger + QUEST_ACCEPT 播报 ──
    case 32:  // case 32 = 类型 33 ENUM_CMDPACKET_ACCEPT_QUEST（接任务回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        v444 = 0;  // 设文案编号 0，稍后弹窗
        sub_404AB0(&v444);  // 游标读 2 字节 → v444
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC(  // 日志打印（printf 风格）
          "QuestIndex %d, QuestTrigger %d, AcceptItemNumber %d",  // （上一调用/表达式的参数续行）
          (uint16_t)v444,  // （上一调用/表达式的参数续行）
          HIBYTE(pArg4),  // （上一调用/表达式的参数续行）
          HIBYTE(nArg5));  // （上一调用/表达式的参数续行）
        v253 = 0;  // 设文案编号 0，稍后弹窗
        if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
        {
          do
          {
            v447 = 0;  // 设文案编号 0，稍后弹窗
            v441 = 0;  // 设文案编号 0，稍后弹窗
            v445 = 0;  // 设文案编号 0，稍后弹窗
            sub_404AB0(&v447);  // 游标读 2 字节 → v447
            sub_404AB0(&v441);  // 游标读 2 字节 → v441
            sub_404AD0(&v445);  // 游标读 4 字节 → v445
            off_77F3FC("SlotIndex %d, ItemIndex %d, Data %d", (uint16_t)v447, (uint16_t)v441, v445);  // 日志打印（printf 风格）
            v254 = (int *)sub_44A980((uint16_t)v447);  // sub_44A980 —— 带界索引 getter
            if ( v254 != nullptr )  // 条件判定 v254 != nullptr
            {
              v255 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*v254 + 60))(v254, (uint16_t)v441);  // 虚函数调用（vtable 槽）
              v256 = *v254;  // v256 = *v254（解引用）
              if ( v255 != 0 )  // 条件判定 v255 != 0
              {
                (*(void (/*thiscall*/ **)(int *, int))(v256 + 48))(v254, v445);  // 虚函数调用（vtable 槽）
              }
              else  // 否则分支
              {
                v257 = (*(int (/*thiscall*/ **)(int *))(v256 + 16))(v254);  // 虚函数调用（vtable 槽）
                off_77F3FC(aD_1, (uint16_t)v447, *(uint32_t *)(v257 + 4));  // 日志打印（printf 风格）
              }
            }
            else  // 否则分支
            {
              v258 = sub_522300((void *)(uint16_t)v441, v445, 0, 0, -1, 1);  // 调用 sub_522300
              sub_484F40((int *)dword_8F852C, (uint16_t)v447, v258, 1);  // sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
            }
            ++v253;  // 自增 v253（循环计数）
          }
          while ( v253 < HIBYTE(nArg5) );  // 循环直到读满计数
        }
        v259 = sub_47D060((uint16_t)v444, HIBYTE(pArg4));  // 调用 sub_47D060
        if ( v259 != 0 )  // 条件判定 v259 != 0
        {
          if ( (uint8_t)sub_546620((uint16_t)v444) == 0 )  // 条件判定
          {
            v428 = unknown_libname_2((uint32_t *)(v259 + 4));
            v260 = (const char *)sub_422E70(786);  // 取本地化文案 786
            sprintf(Buffer, v260, v428);  // 格式化字符串到缓冲
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
          }
        }
        else  // 否则分支
        {
          off_77F3FC(aCriticalError_37);  // 日志打印（printf 风格）
        }
        sub_47D9D0((uint32_t *)dword_8F8540);  // 调用 sub_47D9D0
        sub_553FB0(*((uint32_t *)dword_8F8528 + 21));  // sub_553FB0 —— 任务 NPC 查询（47CC80/47CA40）
        sub_432EA0("QUEST_ACCEPT", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            off_77F3FC(aFail_29);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x17:  // case 0x17 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
            v261 = sub_422E70(787);  // 取本地化文案 787
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v261, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            v262 = sub_422E70(788);  // 取本地化文案 788
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v262, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 33] case 33 = type 34 GIVEUP_QUEST（放弃任务回报）—— sub_47C540/sub_47D9D0 ──
    case 33:  // case 33 = 类型 34 ENUM_CMDPACKET_GIVEUP_QUEST（放弃任务回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        nArg5 = 0;
        sub_404AB0(&nArg5);  // 游标读 2 字节 → nArg5
        off_77F3FC("QuestIndex %d", (uint16_t)nArg5);  // 日志打印（printf 风格）
        v263 = sub_47C540((uint16_t)nArg5);  // 调用 sub_47C540
        v264 = v263;  // v264 = v263（转发）
        if ( v263 != 0 )  // 条件判定 v263 != 0
        {
          v429 = unknown_libname_2((uint32_t *)(v263 + 4));
          v265 = (const char *)sub_422E70(789);  // 取本地化文案 789
          sprintf(Buffer, v265, v429);  // 格式化字符串到缓冲
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
          if ( *((uint32_t *)dword_8F8528 + 26) == 8 && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 22) + 16) == v264 )  // 条件判定
            sub_44AB50(0, 12);  // sub_44AB50 —— 页签切换
        }
        else  // 否则分支
        {
          off_77F3FC(aCriticalError_38);  // 日志打印（printf 风格）
        }
        sub_47D9D0((uint32_t *)dword_8F8540);  // 调用 sub_47D9D0
        sub_553FB0(*((uint32_t *)dword_8F8528 + 21));  // sub_553FB0 —— 任务 NPC 查询（47CC80/47CA40）
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 19 )  // 错误码 == 19 分支
          off_77F3FC(aFail_30);  // 日志打印（printf 风格）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 34] case 34 = type 35 SET_QUEST_TRIGGER（任务触发器回报）—— QUEST_COMPLETE1 播报 ──
    case 34:  // case 34 = 类型 35 ENUM_CMDPACKET_SET_QUEST_TRIGGER（任务触发器回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        pArg4 = 0;
        sub_404AB0(&pArg4);  // 游标读 2 字节 → pArg4
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("QuestIndex %d, Trigger %d", (uint16_t)pArg4, HIBYTE(nArg5));  // 日志打印（printf 风格）
        sub_47C8F0((uint16_t)pArg4, HIBYTE(nArg5));  // 调用 sub_47C8F0
        if ( HIBYTE(nArg5) == 0 )  // 错误码 == 0 分支
          sub_432EA0("QUEST_COMPLETE1", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 19 )  // 错误码 == 19 分支
        {
          off_77F3FC(aFail_32);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 22 )  // 否则错误码 == 22
        {
          off_77F3FC(aFail_31);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 35] case 35 = type 36 FINISH_QUEST（完成任务回报，194 行）—— ★ QUEST_COMPLETE2 + QuestType 分流 ──
    //   按 QuestType 分派奖励（经验/物品/技能点），sub_47C8F0/sub_44A980 等落地
    case 35:  // case 35 = 类型 36 ENUM_CMDPACKET_FINISH_QUEST（完成任务回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        v438 = 0;  // 设文案编号 0，稍后弹窗
        sub_404AB0(&v438);  // 游标读 2 字节 → v438
        off_77F3FC("QuestIndex %d", (uint16_t)v438);  // 日志打印（printf 风格）
        v266 = sub_47C8F0((uint16_t)v438, -1);  // 调用 sub_47C8F0
        v267 = v266;  // v267 = v266（转发）
        if ( v266 != 0 )  // 条件判定 v266 != 0
        {
          v430 = unknown_libname_2((uint32_t *)(v266 + 4));
          v268 = (const char *)sub_422E70(790);  // 取本地化文案 790
          sprintf(Buffer, v268, v430);  // 格式化字符串到缓冲
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
        }
        else  // 否则分支
        {
          off_77F3FC(aCriticalError_38);  // 日志打印（printf 风格）
        }
        sub_432EA0("QUEST_COMPLETE2", -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
        HIBYTE(v441) = 0;  // 清 v441 高字节（即将读取）
        sub_404A90((uint8_t *)&v441 + 3);  // 游标读 1 字节 → v441 高位（错误码字段）
        off_77F3FC("QuestType %d", HIBYTE(v441));  // 日志打印（printf 风格）
        if ( HIBYTE(v441) == 0 )  // 条件判定
        {
          HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
          sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
          off_77F3FC("ItemTypeNumber %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
          *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
          if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
          {
            do
            {
              HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
              v447 = 0;  // 设文案编号 0，稍后弹窗
              v444 = 0;  // 设文案编号 0，稍后弹窗
              sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
              sub_404AB0(&v447);  // 游标读 2 字节 → v447
              sub_404AD0(&v444);  // 游标读 4 字节 → v444
              off_77F3FC("ItemSpace %d, SlotIndex %d, ItemNumber %d", HIBYTE(pArg4), (uint16_t)v447, v444);  // 日志打印（printf 风格）
              if ( HIBYTE(pArg4) != 0 )  // 第二字段 != 0
              {
                if ( HIBYTE(pArg4) == 3 && dword_8F7C04 != 0 )  // 条件判定
                {
                  pObj17 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 788))(  // 虚函数调用（vtable 槽）
                           dword_8F7C04,  // （上一调用/表达式的参数续行）
                           (uint16_t)v447);  // （上一调用/表达式的参数续行）
                  if ( pObj17 != 0 )  // 条件判定 pObj17 != 0
                    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj17 + 4))(pObj17, 1);  // 虚函数调用（vtable 槽）
                }
              }
              else  // 否则分支
              {
                pObj37 = sub_44A980((uint16_t)v447);  // sub_44A980 —— 带界索引 getter
                pObj10 = pObj37;  // pObj10 = pObj37（转发）
                if ( pObj37 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj37 + 20))(pObj37, 2) != 0 )  // 虚函数调用（vtable 槽）
                  v444 = 1;  // 设文案编号 1，稍后弹窗
                if ( (uint16_t)v447 != 0 && (v271 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj10 + 44))(pObj10)) <= v444 )  // 虚函数调用（vtable 槽）
                  sub_484D50((int *)dword_8F852C, (uint16_t)v447);  // sub_484D50 —— 技能槽清空（按槽类型分流）
                else  // 否则分支
                  (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)pObj10 + 52))(pObj10, v444);  // 虚函数调用（vtable 槽）
              }
              ++*(uint32_t *)dword_9B0BBC2;  // 自增计数缓冲
            }
            while ( *(int *)dword_9B0BBC2 < HIBYTE(nArg5) );  // （表达式续行/复合语句）
          }
        }
        HIBYTE(v445) = 0;  // 清 v445 高字节（即将读取）
        sub_404A90((uint8_t *)&v445 + 3);  // 游标读 1 字节 → v445 高位（错误码字段）
        off_77F3FC("QuestRewardType %d", HIBYTE(v445));  // 日志打印（printf 风格）
        if ( HIBYTE(v445) != 0 )  // 条件判定
        {
          if ( HIBYTE(v445) == 1 )  // 条件判定
          {
            HIBYTE(v447) = 0;  // 清 v447 高字节（即将读取）
            HIBYTE(v444) = 0;  // 清 v444 高字节（即将读取）
            sub_404A90((uint8_t *)&v447 + 3);  // 游标读 1 字节 → v447 高位（错误码字段）
            sub_404A90((uint8_t *)&v444 + 3);  // 游标读 1 字节 → v444 高位（错误码字段）
            off_77F3FC("GrowType %d, SkillNumber %d", HIBYTE(v447), HIBYTE(v444));  // 日志打印（printf 风格）
            v282 = 0;  // 设文案编号 0，稍后弹窗
            if ( HIBYTE(v444) != 0 )  // 条件判定
            {
              do
              {
                HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
                HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
                v442 = 0;  // 设文案编号 0，稍后弹窗
                sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
                sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
                sub_404A90(&v442);  // 游标读 1 字节 → v442
                off_77F3FC("SlotIndex %d, SkillIndex %d, Level %d", HIBYTE(pArg4), HIBYTE(nArg5), v442);  // 日志打印（printf 风格）
                if ( v442 != 0 )  // 条件判定 v442 != 0
                  sub_57A3C0(HIBYTE(pArg4), HIBYTE(nArg5));  // sub_57A3C0 —— 对象/控件辅助（47DC90/483D50）
                else  // 否则分支
                  sub_57A3C0(HIBYTE(pArg4), 0);  // sub_57A3C0 —— 对象/控件辅助（47DC90/483D50）
                v431 = v442;  // v431 = v442（转发）
                sub_47DC90(HIBYTE(nArg5));  // 调用 sub_47DC90
                sub_47DEC0(0, v431);  // 调用 sub_47DEC0
                *(uint32_t *)(sub_47DC90(HIBYTE(nArg5)) + 540) = 0;  // 字段赋值
                ++v282;  // 自增 v282（循环计数）
              }
              while ( v282 < HIBYTE(v444) );  // 循环直到读满计数
            }
            sub_47E4F0();  // 调用 sub_47E4F0
            sub_44AB50(0, 12);  // sub_44AB50 —— 页签切换
          }
        }
        else  // 否则分支
        {
          v273 = sub_44E8D0((char *)dword_8F8528, (void *)0x27, v267, 0);  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
          v274 = __RTDynamicCast(
                   v273,  // （上一调用/表达式的参数续行）
                   0,  // （上一调用/表达式的参数续行）
                   &IRDPopupWindow `RTTI Type Descriptor',  // （上一调用/表达式的参数续行）
                   &CNRDQuestRewardWindow `RTTI Type Descriptor',  // （上一调用/表达式的参数续行）
                   0);  // （上一调用/表达式的参数续行）
          HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
          sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
          off_77F3FC("ItemTypeNumber %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
          v275 = 0;  // 设文案编号 0，稍后弹窗
          if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
          {
            do
            {
              pArg4 = 0;
              v444 = 0;  // 设文案编号 0，稍后弹窗
              v447 = 0;  // 设文案编号 0，稍后弹窗
              sub_404AB0(&pArg4);  // 游标读 2 字节 → pArg4
              sub_404AB0(&v444);  // 游标读 2 字节 → v444
              sub_404AD0(&v447);  // 游标读 4 字节 → v447
              off_77F3FC("SlotIndex %d, ItemIndex %d, Data %d", (uint16_t)pArg4, (uint16_t)v444, v447);  // 日志打印（printf 风格）
              pObj14 = sub_44A980((uint16_t)pArg4);  // sub_44A980 —— 带界索引 getter
              if ( pObj14 != 0 )  // 条件判定 pObj14 != 0
              {
                v277 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj14 + 60))(pObj14, (uint16_t)v444);  // 虚函数调用（vtable 槽）
                v278 = *(uint32_t *)pObj14;
                if ( v277 != 0 )  // 条件判定 v277 != 0
                {
                  (*(void (/*thiscall*/ **)(int, int))(v278 + 48))(pObj14, v447);  // 虚函数调用（vtable 槽）
                }
                else  // 否则分支
                {
                  v279 = (*(int (/*thiscall*/ **)(int))(v278 + 16))(pObj14);  // 虚函数调用（vtable 槽）
                  off_77F3FC(aD_1, (uint16_t)pArg4, *(uint32_t *)(v279 + 4));  // 日志打印（printf 风格）
                }
              }
              else  // 否则分支
              {
                pObj14 = sub_522300((void *)(uint16_t)v444, v447, 0, 0, -1, 1);  // 调用 sub_522300
                sub_484F40((int *)dword_8F852C, (uint16_t)pArg4, pObj14, 1);  // sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
              }
              if ( v274 != 0 )  // 条件判定 v274 != 0
              {
                v114 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj14 + 20))(pObj14, 1) == 0;  // 虚函数调用（vtable 槽）
                v280 = v447;  // v280 = v447（转发）
                if ( v114 )  // 条件判定
                  v280 = 1;  // 设文案编号 1，稍后弹窗
                sub_63F7E0(pObj14, v280);  // sub_63F7E0 —— 任务奖励文本（459700/4015C0/422E70/45A340/69A5F0/477AF0，75 行）
              }
              if ( v275 == HIBYTE(nArg5) - 1 && pObj14 != 0 )  // 条件判定
              {
                v281 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj14 + 56))(pObj14);  // 虚函数调用（vtable 槽）
                sub_432EA0(v281, -1, 0, 0);  // sub_432EA0 —— 音效播放包装（非空判定）
              }
              ++v275;  // 自增 v275（循环计数）
            }
            while ( v275 < HIBYTE(nArg5) );  // 循环直到读满计数
          }
        }
        sub_47CD00(dword_8F8540);  // 调用 sub_47CD00
        sub_546680((uint16_t)v438);  // sub_546680 —— 引导辅助 2（698F90）
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v283 = sub_422E70(791);  // 取本地化文案 791
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v283, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_34);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
            off_77F3FC(aFail_33);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 36] case 37 = type 38 SET_USER_AREA（区域更新回报）—— Error/TownIndex → sub_4CE8A0 换区 ──
    case 37:  // case 37 = 类型 38 ENUM_CMDPACKET_SET_USER_AREA（区域更新回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        off_77F3FC("Error %d TownIndex %d", HIBYTE(nArg5), HIBYTE(pArg4));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 21 )  // 错误码 == 21 分支
        {
          off_77F3FC(aFail_4);  // 日志打印（printf 风格）
          *(uint8_t *)(*(uint32_t *)(pArg1 + 20) + 116) = 0;  // 字段赋值
        }
        else if ( HIBYTE(nArg5) == 19 )  // 否则错误码 == 19
        {
          off_77F3FC(aFail_5);  // 日志打印（printf 风格）
          *(uint8_t *)(*(uint32_t *)(pArg1 + 20) + 116) = 0;  // 字段赋值
        }
        else if ( HIBYTE(nArg5) == 8 )  // 否则错误码 == 8
        {
          v284 = sub_4CE8A0((uint32_t *)dword_8F84F0, HIBYTE(pArg4));  // 调用 sub_4CE8A0
          if ( v284 != 0 )  // 条件判定 v284 != 0
          {
            v432 = unknown_libname_2((uint32_t *)(v284 + 4));
            v285 = (const char *)sub_422E70(792);  // 取本地化文案 792
            sprintf(Buffer, v285, v432);  // 格式化字符串到缓冲
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
          }
          else  // 否则分支
          {
            off_77F3FC(aCriticalError_39);  // 日志打印（printf 风格）
          }
          *(uint8_t *)(*(uint32_t *)(pArg1 + 20) + 116) = 0;  // 字段赋值
        }
        else  // 否则分支
        {
          if ( HIBYTE(nArg5) == 55 )  // 错误码 == 55 分支
          {
            v286 = sub_422E70(1339);  // 取本地化文案 1339
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v286, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          }
          *(uint8_t *)(*(uint32_t *)(pArg1 + 20) + 116) = 0;  // 字段赋值
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 37] case 41 = type 42 DIE_MONSTER（怪物死亡回报）—— MonsterUniqueId → sub_45EBE0 取怪 ──
    case 41:  // case 41 = 类型 42 ENUM_CMDPACKET_DIE_MONSTER（怪物死亡回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        pArg4 = 0;
        sub_404AB0(&pArg4);  // 游标读 2 字节 → pArg4
        off_77F3FC("MonsterUniqueId %d", (uint16_t)pArg4);  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 21 )  // 错误码 == 21 分支
          off_77F3FC(aFail_6);  // 日志打印（printf 风格）
        pObj29 = sub_45EBE0(529, (uint16_t)pArg4);  // 调用 sub_45EBE0
        if ( pObj29 != 0 )  // 条件判定 pObj29 != 0
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj29 + 84))(pObj29, 0);  // 虚函数调用（vtable 槽）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 38] case 42 = type 43 DIE_CHARACTER（角色死亡回报） ──
    case 42:  // case 42 = 类型 43 ENUM_CMDPACKET_DIE_CHARACTER（角色死亡回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 19 )  // 错误码 == 19 分支
        {
          off_77F3FC(aFail_36);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 18 )  // 否则错误码 == 18
        {
          off_77F3FC(aFail_35);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 39] case 43 = type 44 USE_COIN（使用金币回报）—— ServerId + sub_4850B0 结算 ──
    case 43:  // case 43 = 类型 44 ENUM_CMDPACKET_USE_COIN（使用金币回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        nArg5 = 0;
        sub_404AB0(&nArg5);  // 游标读 2 字节 → nArg5
        off_77F3FC("ServerId %d", (uint16_t)nArg5);  // 日志打印（printf 风格）
        sub_4850B0((int *)dword_8F852C, 1, 1u);  // sub_4850B0 —— 本地命令 0 执行：槽值设置或扣减（op 18）
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 30, 2);  // 虚函数调用（vtable 槽）
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(  // 虚函数调用（vtable 槽）
          dword_8F8520,  // （上一调用/表达式的参数续行）
          (uint16_t)word_77F804);  // （上一调用/表达式的参数续行）
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg5);  // 虚函数调用（vtable 槽）
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0, -1);  // 虚函数调用（vtable 槽）
        return 1;  // 处理完成，返回 1
      }
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
      {
        case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
          off_77F3FC(aFail_40);  // 日志打印（printf 风格）
          break;  // 跳出本分支
        case 0x15:  // case 0x15 = 类型 22 ENUM_CMDPACKET_RENT_AVATAR（租时装回报）
          off_77F3FC(aFail_39);  // 日志打印（printf 风格）
          break;  // 跳出本分支
        case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
          off_77F3FC(aFail_38);  // 日志打印（printf 风格）
          break;  // 跳出本分支
        case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
          off_77F3FC(aFail_37);  // 日志打印（printf 风格）
          break;  // 跳出本分支
        case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
          off_77F3FC(aFail_7);  // 日志打印（printf 风格）
          break;  // 跳出本分支
        default:  // 未列出的码值 → 兜底
          break;  // 跳出本分支
      }
      goto LABEL_747;  // 跳转合流点 LABEL_747
    // ── [段 40] case 44 = type 45 GIVEUP_GAME（放弃游戏回报）—— sub_458120 ──
    case 44:  // case 44 = 类型 45 ENUM_CMDPACKET_GIVEUP_GAME（放弃游戏回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_458120(*((uint32_t *)dword_8F8528 + 609));  // 调用 sub_458120
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 19 )  // 错误码 == 19 分支
          off_77F3FC(aFail_41);  // 日志打印（printf 风格）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 41] case 45 = type 46 GET_ITEM（捡物品回报）—— sub_425100/sub_425A00 容器操作 + sub_484FF0 ──
    case 45:  // case 45 = 类型 46 ENUM_CMDPACKET_GET_ITEM（捡物品回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 4 )  // 错误码 == 4 分支
        {
          v288 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v289 = sub_422E70(793);  // 取本地化文案 793
          sub_43BEE0(v288, v289, -6567706, 0, -1);  // 调用 sub_43BEE0
        }
        else if ( HIBYTE(nArg5) == 21 )  // 否则错误码 == 21
        {
          off_77F3FC(aFail_8);  // 日志打印（printf 风格）
        }
        sub_484FF0(dword_8F852C);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
        v290 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);  // 虚函数调用（vtable 槽）
        v291 = 0;  // 设文案编号 0，稍后弹窗
        pArg4 = sub_425100(v290);  // sub_425100 —— 容器长度（+30 组）
        if ( (int)pArg4 > 0 )  // 条件判定
        {
          do
          {
            pObj7 = (uint8_t *)sub_425A00(v291);  // sub_425A00 —— 元素取值（+30 组）
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pObj7 + 40))(pObj7, 289) != 0 )  // 虚函数调用（vtable 槽）
              pObj7[977] = 0;  // 写数组 pObj7[977] = 0
            ++v291;  // 自增 v291（循环计数）
          }
          while ( v291 < (int)pArg4 );  // （表达式续行/复合语句）
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 42] case 46 = type 47 USE_STACKABLE（使用消耗品回报）—— ItemSlotIndex + sub_4856E0 ──
    case 46:  // case 46 = 类型 47 ENUM_CMDPACKET_USE_STACKABLE（使用消耗品回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        nArg5 = 0;
        sub_404AB0(&nArg5);  // 游标读 2 字节 → nArg5
        off_77F3FC("ItemSlotIndex %d", (uint16_t)nArg5);  // 日志打印（printf 风格）
        if ( sub_4856E0((int *)dword_8F852C, (uint16_t)nArg5) == 0 )  // 条件判定
        {
          v108 = (char *)sub_422E70(794);  // 取本地化文案 794
LABEL_733:  // 标签 LABEL_733：合流点
          off_77F3F8(v109, v108);  // 文本输出/弹窗提示
        }
        goto LABEL_265;  // 跳转合流点 LABEL_265
      }
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
      {
        case 8:  // case 8 = 类型 9 ENUM_CMDPACKET_RECOVER_STAMINA（疲劳恢复回报）
          v410 = 795;  // 设文案编号 795，稍后弹窗
LABEL_745:  // 标签 LABEL_745：合流点
          v293 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v294 = sub_422E70(v410);  // 调用 sub_422E70
          break;  // 跳出本分支
        case 0xE:  // case 0xE = 类型 15 ENUM_CMDPACKET_START_GAME（开始游戏回报）
          v293 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v294 = sub_422E70(796);  // 取本地化文案 796
          break;  // 跳出本分支
        case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
          off_77F3FC(aFail_9);  // 日志打印（printf 风格）
          sub_484FF0(dword_8F852C);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
          return 1;  // 处理完成，返回 1
        case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
          v293 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v294 = sub_422E70(797);  // 取本地化文案 797
          break;  // 跳出本分支
        case 0x17:  // case 0x17 = 类型 24 ENUM_CMDPACKET_SELL_ITEM（卖物品回报）
          v410 = 798;  // 设文案编号 798，稍后弹窗
          goto LABEL_745;  // 跳转合流点 LABEL_745
        default:  // 未列出的码值 → 兜底
LABEL_747:  // 标签 LABEL_747：合流点
          sub_484FF0(dword_8F852C);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
          return 1;  // 处理完成，返回 1
      }
      sub_43BEE0(v293, v294, -6567706, 0, -1);  // 调用 sub_43BEE0
      goto LABEL_747;  // 跳转合流点 LABEL_747
    // ── [段 43] case 47 = type 48 MOVE_MAP（切图回报）—— 打印 ENUM_CMDPACKET_MOVE_MAP Error ──
    //   成功支：sub_423020/40/60/80/2E0 一族（切图序列）+ sub_4633B0
    case 47:  // case 47 = 类型 48 ENUM_CMDPACKET_MOVE_MAP（切图回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("ENUM_CMDPACKET_MOVE_MAP :: Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(pArg1 + 28) + 16) + 44) + 472) = 0;  // 字段赋值
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_43);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x14:  // case 0x14 = 类型 21 ENUM_CMDPACKET_BUY_ITEM（买物品回报）
            off_77F3FC(aFail_42);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            off_77F3FC(aFail_10);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
        if ( ++dword_9B9308 == 5 )  // 条件判定
        {
          sub_4232E0(&Time);  // sub_4232E0 —— 取当前时间
          v295 = sub_423020(&Time);  // sub_423020 —— 时间字段辅助·月
          v296 = sub_423040(&Time);  // sub_423040 —— 时间字段辅助·日
          v297 = sub_423060(&Time);  // sub_423060 —— 时间字段辅助·时
          pArg4 = sub_423080(&Time);  // sub_423080 —— 时间字段辅助·分
          v298 = sub_4633B0(dword_8F7C04);  // sub_4633B0 —— std::string 取数据指针（SSO 判定）
          off_77F3FC(aD_2, v295, v296, v297, pArg4, v298);  // 日志打印（printf 风格）
          MEMORY[0x1D8] = 0;  // 写数组 MEMORY[0x1D8] = 0
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 44] case 48 = type 49 SET_PLAY_RESULT（上报结算回报） ──
    case 48:  // case 48 = 类型 49 ENUM_CMDPACKET_SET_PLAY_RESULT（上报结算回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 19 )  // 错误码 == 19 分支
        {
          off_77F3FC(aFail_45);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 22 )  // 否则错误码 == 22
        {
          off_77F3FC(aFail_44);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 45] case 49 = type 50 DROP_ITEM（丢物品回报）—— ItemSpace/SlotIndex/DropNumber + item type error 检查 ──
    case 49:  // case 49 = 类型 50 ENUM_CMDPACKET_DROP_ITEM（丢物品回报）
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        pArg4 = 0;
        *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404AB0(&pArg4);  // 游标读 2 字节 → pArg4
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        off_77F3FC("ItemSpace %d, SlotIndex %d, DropNumber %d", HIBYTE(nArg5), (uint16_t)pArg4, *(uint32_t *)dword_9B0BBC2);  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) != 0 )  // 错误码 != 0 分支
        {
          if ( HIBYTE(nArg5) == 3 )  // 错误码 == 3 分支
          {
            pObj23 = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_8F7C04 + 788))(  // 虚函数调用（vtable 槽）
                     dword_8F7C04,  // （上一调用/表达式的参数续行）
                     (uint16_t)pArg4,  // （上一调用/表达式的参数续行）
                     nArg3,  // （上一调用/表达式的参数续行）
                     nArg2);  // （上一调用/表达式的参数续行）
            if ( pObj23 != 0 )  // 条件判定 pObj23 != 0
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj23 + 4))(pObj23, 1);  // 虚函数调用（vtable 槽）
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1080))(dword_8F7C04, (uint16_t)pArg4);  // 虚函数调用（vtable 槽）
            (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 816))(  // 虚函数调用（vtable 槽）
              dword_8F7C04,  // （上一调用/表达式的参数续行）
              (uint16_t)pArg4,  // （上一调用/表达式的参数续行）
              -1);  // （上一调用/表达式的参数续行）
          }
        }
        else if ( sub_4850B0((int *)dword_8F852C, (uint16_t)pArg4, *(unsigned int *)dword_9B0BBC2) == 0 )  // 否则条件分支
        {
          off_77F3FC((char *)&byte_72AB00);  // 日志打印（printf 风格）
          sub_47CD00(dword_8F8540);  // 调用 sub_47CD00
          return 1;  // 处理完成，返回 1
        }
        sub_47CD00(dword_8F8540);  // 调用 sub_47CD00
        return 1;  // 处理完成，返回 1
      }
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      if ( HIBYTE(nArg5) == 2 )  // 错误码 == 2 分支
      {
        off_77F3FC(aFailDb);  // 日志打印（printf 风格）
        goto LABEL_780;  // 跳转合流点 LABEL_780
      }
      if ( HIBYTE(nArg5) == 17 )  // 错误码 == 17 分支
      {
        v301 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
        v302 = sub_422E70(799);  // 取本地化文案 799
      }
      else  // 否则分支
      {
        if ( HIBYTE(nArg5) != 19 )  // 错误码 != 19 分支
        {
          if ( HIBYTE(nArg5) == 23 )  // 错误码 == 23 分支
            off_77F3F8(v300, "item type error");  // 文本输出/弹窗提示
LABEL_780:  // 标签 LABEL_780：合流点
          HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
          sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
          off_77F3FC("ItemSpace %d", HIBYTE(pArg4));  // 日志打印（printf 风格）
          v102 = (uint32_t *)sub_432F00(HIBYTE(pArg4));  // sub_432F00 —— 按类型取全局列表对象
          if ( v102 != nullptr )  // 条件判定 v102 != nullptr
LABEL_243:  // 标签 LABEL_243：合流点
            sub_484FF0(v102);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
          return 1;  // 处理完成，返回 1
        }
        v301 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
        v302 = sub_422E70(800);  // 取本地化文案 800
      }
      sub_43BEE0(v301, v302, -6567706, 0, -1);  // 调用 sub_43BEE0
      goto LABEL_780;  // 跳转合流点 LABEL_780
    // ── [段 46] case 50 = type 51 DECREASE_DURABILITY（扣耐久回报，50 行）—— EquipmentType + sub_41A5E0 防篡校验 ──
    case 50:  // case 50 = 类型 51 ENUM_CMDPACKET_DECREASE_DURABILITY（扣耐久回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        LOBYTE(nArg5) = 0;  // 清低字节
        sub_404A90(&nArg5);  // 游标读 1 字节 → nArg5
        off_77F3FC("EquipmentType %d", (uint8_t)nArg5);  // 日志打印（printf 风格）
        pObj38 = dword_8F7C04;  // pObj38 = dword_8F7C04（转发）
        pObj2 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, (uint8_t)nArg5);  // 虚函数调用（vtable 槽）
        if ( pObj2 != 0 )  // 条件判定 pObj2 != 0
        {
          v305 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 188))(pObj2, nArg32, nArg2);  // 虚函数调用（vtable 槽）
          v306 = sub_41A5E0(v305 + 32) == 1;  // sub_41A5E0：crypt4byte 解密校验
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 28, 2);  // 虚函数调用（vtable 槽）
          v307 = *(uint32_t *)dword_8F8520;
          v308 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj38 + 48))(pObj38);  // 虚函数调用（vtable 槽）
          (*(void (/*thiscall*/ **)(int, int))(v307 + 36))(dword_8F8520, v308);  // 虚函数调用（vtable 槽）
          v309 = *(uint32_t *)dword_8F8520;
          v310 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj38 + 52))(pObj38);  // 虚函数调用（vtable 槽）
          (*(void (/*thiscall*/ **)(int, int))(v309 + 36))(dword_8F8520, v310);  // 虚函数调用（vtable 槽）
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nArg5);  // 虚函数调用（vtable 槽）
          if ( v306 )  // 条件判定
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);  // 虚函数调用（vtable 槽）
          else  // 否则分支
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0);  // 虚函数调用（vtable 槽）
        }
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            off_77F3FC(aFail_49);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_48);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
            off_77F3FC(aFail_47);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0xB:  // case 0xB = 类型 12 ENUM_CMDPACKET_SET_PARTY_INFO（组队设置回报）
            off_77F3FC(aFail_46);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 47] case 52 = type 53 MAKE_PVP_ROOM（建 PVP 房回报）──────────────────
    case 52:  // case 52 = 类型 53 ENUM_CMDPACKET_MAKE_PVP_ROOM
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
        return 1;  // 处理完成，返回 1
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      if ( HIBYTE(nArg5) == 4 )  // 错误码 == 4 分支
      {
        v408 = 801;  // 设文案编号 801，稍后弹窗
        goto LABEL_982;  // 跳转合流点 LABEL_982
      }
      if ( HIBYTE(nArg5) == 19 )  // 错误码 == 19 分支
      {
        off_77F3FC(aFail_50);  // 日志打印（printf 风格）
        return 1;  // 处理完成，返回 1
      }
      if ( HIBYTE(nArg5) != 17 )  // 错误码 != 17 分支
        return 1;  // 处理完成，返回 1
      v311 = sub_41C1B0();  // sub_41C1B0 —— 按全局键 word_77F804 查表取对象
      v312 = sub_41A5E0(v311 + 53);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
      v415 = dword_9B759C[v312]
           - (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));  // 虚函数调用（vtable 槽）
      v57 = (const char *)sub_422E70(802);  // 取本地化文案 802
      goto LABEL_812;  // 跳转合流点 LABEL_812
    // ── [段 48] case 53 = type 54 ENTER_PVP_ROOM（进 PVP 房回报）—— IsReady + sub_48F580 ──
    case 53:  // case 53 = 类型 54 ENUM_CMDPACKET_ENTER_PVP_ROOM（进 PVP 房回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        for ( m = 0; m < 8; ++m )  // 循环：m 从 0 到 8（++）
        {
          HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
          sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
          off_77F3FC("IsReady %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
          sub_48F580(m, HIBYTE(nArg5) != 0);  // sub_48F580 —— 座位/就绪表置位并刷新房间列表
        }
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v408 = 803;  // 设文案编号 803，稍后弹窗
            goto LABEL_982;  // 跳转合流点 LABEL_982
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_51);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            v314 = sub_41C1B0();  // sub_41C1B0 —— 按全局键 word_77F804 查表取对象
            v315 = sub_41A5E0(v314 + 53);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
            v415 = dword_9B759C[v315]
                 - (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C  // 虚函数调用（vtable 槽）
                                                                                             + 3));  // （续行：指针/参数偏移）
            v57 = (const char *)sub_422E70(804);  // 取本地化文案 804
LABEL_812:  // 标签 LABEL_812：合流点
            sprintf(v449, v57, v415);  // 格式化字符串到缓冲
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v449, -6567706, 0, -1);  // 调用 sub_43BEE0
            break;  // 跳出本分支
          case 0x37:  // case 0x37 = 类型 56 ENUM_CMDPACKET_SET_PVP_READY_STATE
            v316 = sub_422E70(1341);  // 取本地化文案 1341
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v316, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 49] case 54..59 = type 55..60（PVP 座位/准备/队伍/死亡/超时 五连）：均仅读错误码 ──
    case 54:  // case 54 = 类型 55 ENUM_CMDPACKET_SET_PVP_SEAT_STATE（PVP 座位状态回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 19 )  // 错误码 == 19 分支
        {
          off_77F3FC(aFail_53);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 8 )  // 否则错误码 == 8
        {
          off_77F3FC(aFail_52);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    case 55:  // case 55 = 类型 56 ENUM_CMDPACKET_SET_PVP_READY_STATE
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 18 )  // 错误码 == 18 分支
        {
          off_77F3FC(aFail_55);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 22 )  // 否则错误码 == 22
        {
          off_77F3FC(aFail_54);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    case 56:  // case 56 = 类型 57 ENUM_CMDPACKET_SET_PVP_TEAM_MODE
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            off_77F3FC(aFail_58);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 8:  // case 8 = 类型 9 ENUM_CMDPACKET_RECOVER_STAMINA（疲劳恢复回报）
            off_77F3FC(aFail_57);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            off_77F3FC(aFail_56);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    case 57:  // case 57 = 类型 58 ENUM_CMDPACKET_DIE_PVP_CHARACTER
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 18 )  // 错误码 == 18 分支
        {
          off_77F3FC(aFail_60);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 19 )  // 否则错误码 == 19
        {
          off_77F3FC(aFail_59);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    case 58:  // case 58 = 类型 59 ENUM_CMDPACKET_PVP_TIME_OUT
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 8 )  // 错误码 == 8 分支
        {
          off_77F3FC(aFail_62);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 19 )  // 否则错误码 == 19
        {
          off_77F3FC(aFail_61);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    case 59:  // case 59 = 类型 60 ENUM_CMDPACKET_END_PVP_RESULT
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 8 )  // 错误码 == 8 分支
        {
          off_77F3FC(aFail_64);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 19 )  // 否则错误码 == 19
        {
          off_77F3FC(aFail_63);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    case 61:  // case 61 = 类型 62 ENUM_CMDPACKET_SET_PVP_MAP_INDEX
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 8 )  // 错误码 == 8 分支
        {
          off_77F3FC(aFail_66);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 19 )  // 否则错误码 == 19
        {
          off_77F3FC(aFail_65);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 50] case 62 = type 63 ADD_FRIEND（加好友回报）—— Name/Level/Job/GrowType/Unique ID + sub_47B150 ──
    case 62:  // case 62 = 类型 63 ENUM_CMDPACKET_ADD_FRIEND
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(v441) = 0;  // 清 v441 高字节（即将读取）
        HIBYTE(v445) = 0;  // 清 v445 高字节（即将读取）
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        v317 = (char *)sub_422E70(805);  // 取本地化文案 805
        sub_48BCC0(Destination, 0x1Fu, v317);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
        sub_404A90((uint8_t *)&v441 + 3);  // 游标读 1 字节 → v441 高位（错误码字段）
        sub_404A90((uint8_t *)&v445 + 3);  // 游标读 1 字节 → v445 高位（错误码字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC(  // 日志打印（printf 风格）
          "Name [%s], Level %d, Job %d, GrowType %d, Unique ID %d",  // （上一调用/表达式的参数续行）
          Destination,  // （上一调用/表达式的参数续行）
          HIBYTE(v441),  // （上一调用/表达式的参数续行）
          HIBYTE(v445),  // （上一调用/表达式的参数续行）
          HIBYTE(pArg4),  // （上一调用/表达式的参数续行）
          HIBYTE(nArg5));  // （上一调用/表达式的参数续行）
        sub_47B150(Destination, HIBYTE(v441), HIBYTE(v445), HIBYTE(pArg4), HIBYTE(nArg5));  // 调用 sub_47B150
        v318 = (const char *)sub_422E70(806);  // 取本地化文案 806
        sprintf(Buffer, v318, Destination);  // 格式化字符串到缓冲
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v319 = sub_422E70(807);  // 取本地化文案 807
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v319, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            v320 = sub_422E70(808);  // 取本地化文案 808
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v320, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x15:  // case 0x15 = 类型 22 ENUM_CMDPACKET_RENT_AVATAR（租时装回报）
            v321 = sub_422E70(809);  // 取本地化文案 809
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v321, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 51] case 63 = type 64 REMOVE_FRIEND（删好友回报）—— sub_47A980 ──
    case 63:  // case 63 = 类型 64 ENUM_CMDPACKET_REMOVE_FRIEND（删好友回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        v322 = (char *)sub_422E70(810);  // 取本地化文案 810
        sub_48BCC0(Destination, 0x1Fu, v322);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
        off_77F3FC("Name [%s]", Destination);  // 日志打印（printf 风格）
        sub_47A980(Destination);  // 调用 sub_47A980
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("Error %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 21 )  // 错误码 == 21 分支
        {
          v323 = sub_422E70(811);  // 取本地化文案 811
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v323, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 52] case 64 = type 65 DEBUG_COMMAND（★ GM 命令回报，49 行）—— DebugCommand %d 打印 ──
    //   与 docs/24 §一 0x41(65) ENUM_CMDPACKET_DEBUG_COMMAND 直证吻合；sub_442DF0/sub_4896B0 分派 GM 功能
    case 64:  // case 64 = 类型 65 ENUM_CMDPACKET_DEBUG_COMMAND（GM 调试回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
        return 1;  // 处理完成，返回 1
      HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      off_77F3FC("DebugCommand %d", HIBYTE(nArg5));  // 日志打印（printf 风格）
      switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
      {
        case 0:  // case 0 = 类型 1 ENUM_CMDPACKET_LOGIN（登录回报）
          word_8F7C14 = -1;
          word_8F7C10 = 0;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1060))(dword_8F7C04, 100);  // 虚函数调用（vtable 槽）
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);  // 虚函数调用（vtable 槽）
          pArg4 = *(uint32_t *)dword_9B0BBC;
          for ( *(uint32_t *)dword_9B0BBC2 = dword_9B0BBC; (uint8_t)sub_4296C0(dword_9B0BBC2) != 0; *(uint32_t *)dword_9B0BBC2 = dword_9B0BBC )  // （表达式/调用续行）
          {
            sub_4896B0(*(uint32_t *)(pArg4 + 12), 3);  // sub_4896B0 —— 全局键表 dword_99FBA4 建键写值
            sub_442DF0((char *)&Time + 4, 0);  // sub_442DF0 —— map 迭代器前进并回旧值
          }
          sub_41C270((int)v439, v324, 1u);  // sub_41C270 —— 对 this+248 子对象做 crypt4byte 初始化
          v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v47 = sub_422E70(812);  // 取本地化文案 812
          goto LABEL_983;  // 跳转合流点 LABEL_983
        case 1:  // case 1 = 类型 2 ENUM_CMDPACKET_SET_UDP_IP_PORT
          v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v47 = sub_422E70(813);  // 取本地化文案 813
          goto LABEL_983;  // 跳转合流点 LABEL_983
        case 2:  // case 2 = 类型 3 ENUM_CMDPACKET_EXIT（退出确认）
          v408 = 814;  // 设文案编号 814，稍后弹窗
          goto LABEL_982;  // 跳转合流点 LABEL_982
        case 3:  // case 3 = 类型 4 ENUM_CMDPACKET_SELECT_CHARACTER（选角回报）
          v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v47 = sub_422E70(815);  // 取本地化文案 815
          goto LABEL_983;  // 跳转合流点 LABEL_983
        case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
          v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v47 = sub_422E70(816);  // 取本地化文案 816
          goto LABEL_983;  // 跳转合流点 LABEL_983
        case 5:  // case 5 = 类型 6 ENUM_CMDPACKET_DELETE_CHARACTER（删角回报）
          v408 = 817;  // 设文案编号 817，稍后弹窗
          goto LABEL_982;  // 跳转合流点 LABEL_982
        case 6:  // case 6 = 类型 7 ENUM_CMDPACKET_RETURN_SELECT_CHARACTER（返回选角）
          v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
          v47 = sub_422E70(818);  // 取本地化文案 818
          goto LABEL_983;  // 跳转合流点 LABEL_983
        default:  // 未列出的码值 → 兜底
          break;  // 跳出本分支
      }
      return 1;  // 处理完成，返回 1
    // ── [段 53] case 66 = type 67 BUY_CERASHOP_ITEM（商城购买回报）—— sub_560140/sub_5601C0 ──
    case 66:  // case 66 = 类型 67 ENUM_CMDPACKET_BUY_CERASHOP_ITEM
      *(uint32_t *)ArgList = 0;
      *(uint32_t *)dword_9B0BBC2 = 0;  // 清零临时缓冲 dword_9B0BBC2
      pArg4 = 0;
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        nArg5 = 0;
        sub_404AD0(&nArg5);  // 游标读 4 字节 → nArg5
        sub_404AD0(&pArg4);  // 游标读 4 字节 → pArg4
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        sub_404AD0(ArgList);  // 游标读 4 字节 → ArgList
        off_77F3FC((char *)&byte_72A6C4, nArg5, pArg4, *(uint32_t *)dword_9B0BBC2, *(uint32_t *)ArgList);  // 日志打印（printf 风格）
        sub_5601C0(1, nArg5, pArg4, -1);  // sub_5601C0 —— 礼赠流程主函数（55E8B0/44E8D0/44E850/55CB60/4015C0/63EF60/55F7B0，60 行）
        if ( *(uint32_t *)dword_9B0BBC2 == *(uint32_t *)ArgList )  // 条件判定
          sub_560140(1, nArg5);  // sub_560140 —— 商品列表显示（698F90/55FDB0/44BBA0）
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        *(uint32_t *)v440 = 0;
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404AD0(&pArg4);  // 游标读 4 字节 → pArg4
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        sub_404AD0(ArgList);  // 游标读 4 字节 → ArgList
        sub_404AD0(v440);  // 游标读 4 字节 → v440
        off_77F3FC((char *)&byte_72A678, HIBYTE(nArg5), pArg4, *(uint32_t *)dword_9B0BBC2, *(uint32_t *)ArgList, *(uint32_t *)v440);  // 日志打印（printf 风格）
        if ( HIBYTE(nArg5) == 55 )  // 错误码 == 55 分支
        {
          v325 = sub_422E70(1340);  // 取本地化文案 1340
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v325, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        }
        else  // 否则分支
        {
          sub_5601C0(0, pArg4, *(uint32_t *)dword_9B0BBC2, HIBYTE(nArg5));  // sub_5601C0 —— 礼赠流程主函数（55E8B0/44E8D0/44E850/55CB60/4015C0/63EF60/55F7B0，60 行）
          if ( *(uint32_t *)ArgList == *(uint32_t *)v440 )  // 条件判定
            sub_560140(0, pArg4);  // sub_560140 —— 商品列表显示（698F90/55FDB0/44BBA0）
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 54] case 67 = type 68 GEN_CERATICKET（生成商城票回报）—— ERROR!ERROR! + Cera Ticket 日志 ──
    case 67:  // case 67 = 类型 68 ENUM_CMDPACKET_GEN_CERATICKET（生成商城票回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        memset(psz, 0, sizeof(psz));  // 清零缓冲
        v454 = 0;  // 设文案编号 0，稍后弹窗
        v455 = 0;  // 设文案编号 0，稍后弹窗
        nArg5 = 0;
        sub_48BCC0(psz, 0x40u, "ERROR!ERROR!");  // sub_48BCC0 —— 限量串读入或 strncpy 回退
        sub_404AD0(&nArg5);  // 游标读 4 字节 → nArg5
        off_77F3FC("Cera Ticket : %s, Random Value : %d", psz, nArg5);  // 日志打印（printf 风格）
        sub_55CB10(psz, nArg5);  // sub_55CB10 —— 商城状态（44E8D0）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 55] case 69 = type 70 GUILD_MEMER_LIST（公会成员名单）—— ENUM_CMDPACKET_GUILD_MEMER_LIST ──
    case 69:  // case 69 = 类型 70 ENUM_CMDPACKET_GUILD_MEMER_LIST
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8514 + 12))(dword_8F8514);  // 虚函数调用（vtable 槽）
        v326 = (char *)sub_422E70(819);  // 取本地化文案 819
        sub_48BCC0(Destination, 0x1Fu, v326);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_406D60((size_t *)(dword_8F8514 + 20), Destination);  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        off_77F3FC("ENUM_CMDPACKET_GUILD_MEMER_LIST - [%s] : %d guild members", Destination, HIBYTE(nArg5));  // 日志打印（printf 风格）
        for ( n = 0; n < HIBYTE(nArg5); ++n )  // （表达式/调用续行）
        {
          v328 = (char *)sub_422E70(820);  // 取本地化文案 820
          sub_48BCC0(&psz[32], 0x1Fu, v328);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
          v329 = (char *)sub_422E70(821);  // 取本地化文案 821
          sub_48BCC0(v458, 0xDu, v329);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
          sub_404AB0((uint16_t *)&v441 + 1);  // sub_404AB0 —— 游标读 2 字节
          sub_404A90((uint8_t *)&v447 + 3);  // 游标读 1 字节 → v447 高位（错误码字段）
          sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
          sub_404A90((uint8_t *)&v445 + 3);  // 游标读 1 字节 → v445 高位（错误码字段）
          v330 = sub_47B150(&psz[32], SHIWORD(v441), SHIBYTE(v447), SHIBYTE(pArg4), 0);  // 调用 sub_47B150
          *(uint32_t *)(v330 + 40) = SHIBYTE(v445);  // 字段 v330+40 = SHIBYTE(v445)
          v331 = (const char *)(v330 + 52);
          strcpy((char *)(v330 + 52), v458);  // 字符串拷贝
          v433 = *(uint32_t *)(v330 + 40);  // 读字段 v433 = v330 + 40
          v413 = *(uint32_t *)(v330 + 28);  // 读字段 v413 = v330 + 28
          v332 = (const char *)unknown_libname_2((uint32_t *)v330);
          off_77F3FC("\t[%s] as [%s]. Lv%d. Ch%d", v332, v331, v413, v433);  // 日志打印（printf 风格）
        }
        sub_479850(dword_8F8514);  // 调用 sub_479850
        sub_478F20(dword_8F8514);  // 调用 sub_478F20
      }
      return 1;  // 处理完成，返回 1
    // ── [段 56] case 70 = type 71 CALL_GUILD_CREATE_RIGHT（建会权限回报） ──
    case 70:  // case 70 = 类型 71 ENUM_CMDPACKET_CALL_GUILD_CREATE_RIGHT（公会成员名单回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 1:  // case 1 = 类型 2 ENUM_CMDPACKET_SET_UDP_IP_PORT
            sub_44E8D0((char *)dword_8F8528, (void *)0x34, 0, 1);  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
            break;  // 跳出本分支
          case 0x1C:  // case 0x1C = 类型 29 ENUM_CMDPACKET_USE_LOTTERY_ITEM（抽奖物品回报）
            v334 = sub_422E70(822);  // 取本地化文案 822
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v334, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x1D:  // case 0x1D = 类型 30 ENUM_CMDPACKET_CHANGE_SKILLSLOT（改技能栏回报）
            v335 = sub_422E70(823);  // 取本地化文案 823
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v335, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x1E:  // case 0x1E = 类型 31 ENUM_CMDPACKET_BUY_SKILL（学技能回报）
            v336 = sub_422E70(824);  // 取本地化文案 824
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v336, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            v337 = sub_422E70(825);  // 取本地化文案 825
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v337, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 57] case 71..74 = type 72..75（换频道/拉名单/EPLP 命令）：EPLP COMMAND FAILED 文案 ──
    case 71:  // case 71 = 类型 72 ENUM_CMDPACKET_SCORE_SCROLL_STATE（建会权限回报）
      sub_4772A0(0);  // 调用 sub_4772A0
      sub_45A420(2);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
      return 1;  // 处理完成，返回 1
    case 72:  // case 72 = 类型 73 ENUM_CMDPACKET_CARD_SELECT_RIGHT_STATE（积分滚动回报）
      sub_45A820(*((uint32_t *)dword_8F8528 + 609));  // sub_45A820 —— REWARD_DIVIDE_SET —— 划分按钮逐格排布
      nArg5 = 0;
      v349 = 1;  // 设文案编号 1，稍后弹窗
      for ( ii = 0; ii < 4; ++ii )  // 循环：ii 从 0 到 4（++）
      {
        sub_404AB0(&nArg5);  // 游标读 2 字节 → nArg5
        off_77F3FC(aD_3, ii, (int16_t)nArg5);  // 日志打印（printf 风格）
        if ( (uint16_t)nArg5 == 0 )  // 条件判定
          v349 = 0;  // 设文案编号 0，稍后弹窗
      }
      *(uint8_t *)(*((uint32_t *)dword_8F8528 + 609) + 660) = v349;  // 字段赋值
      return 1;  // 处理完成，返回 1
    case 73:  // case 73 = 类型 74 ENUM_CMDPACKET_SELECT_CARD（卡牌选择权回报）
      LOBYTE(nArg5) = 0;  // 清低字节
      for ( jj = 0; jj < 4; ++jj )  // 循环：jj 从 0 到 4（++）
      {
        sub_404A90(&nArg5);  // 游标读 1 字节 → nArg5
        off_77F3FC(aD_4, jj, (char)nArg5);  // 日志打印（printf 风格）
        sub_4577F0(jj, nArg5);  // 【奖励开箱等多处）】
      }
      return 1;  // 处理完成，返回 1
    case 74:  // case 74 = 类型 75 ENUM_CMDPACKET_EPLP_COMMAND（选卡回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(pArg4) = 0;  // 清 pArg4 高字节（即将写第二字段）
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        off_77F3FC("btn %d event %d", HIBYTE(pArg4), HIBYTE(nArg5));  // 日志打印（printf 风格）
        sub_457FB0(SHIBYTE(pArg4), HIBYTE(nArg5));  // sub_457FB0 —— 开箱模式切换显示
      }
      else  // 否则分支
      {
        off_77F3FC("EPLP COMMAND FAILED : errorEvent %d errorCode %d", 0, 0);  // 日志打印（printf 风格）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 58] case 75 = type 76 CALL_GUILD_LEVEL_UP（公会升级回报）—— sub_4BE1D0/sub_4BE1E0/sub_4BF1B0 ──
    case 75:  // case 75 = 类型 76 ENUM_CMDPACKET_CALL_GUILD_LEVEL_UP（EPLP 命令回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        v338 = sub_422E70(826);  // 取本地化文案 826
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v338, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        v339 = sub_429900(dword_8F8500);  // sub_429900 —— 本机槽实体查询（word_77F804 键）
        v340 = (uint8_t *)sub_4BF1B0((int **)dword_8F851C, v339);  // sub_4BF1B0 —— 按工会 id 查值指针
        v341 = v340;  // v341 = v340（转发）
        if ( v340 != nullptr )  // 条件判定 v340 != nullptr
        {
          v342 = sub_4BE1D0(v340);  // sub_4BE1D0 —— 标志读取（this+12）
          sub_4BE1E0(v341, v342 + 1);  // sub_4BE1E0 —— 标志字节写侧（this+12）
        }
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 0x1F:  // case 0x1F = 类型 32 ENUM_CMDPACKET_INCREASE_STATUS（加属性点回报）
            v343 = sub_422E70(827);  // 取本地化文案 827
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v343, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x20:  // case 0x20 = 类型 33 ENUM_CMDPACKET_ACCEPT_QUEST（接任务回报）
            v344 = sub_422E70(828);  // 取本地化文案 828
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v344, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x21:  // case 0x21 = 类型 34 ENUM_CMDPACKET_GIVEUP_QUEST（放弃任务回报）
            v345 = sub_422E70(829);  // 取本地化文案 829
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v345, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x22:  // case 0x22 = 类型 35 ENUM_CMDPACKET_SET_QUEST_TRIGGER（任务触发器回报）
            v346 = sub_422E70(830);  // 取本地化文案 830
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v346, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x23:  // case 0x23 = 类型 36 ENUM_CMDPACKET_FINISH_QUEST（完成任务回报）
            v347 = sub_422E70(831);  // 取本地化文案 831
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v347, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            v348 = sub_422E70(832);  // 取本地化文案 832
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v348, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 59] case 76 = type 77 GUILD_INFO（公会信息）—— ENUM_CMDPACKET_GUILD_INFO - generic error ──
    case 76:  // case 76 = 类型 77 ENUM_CMDPACKET_GUILD_INFO（公会升级回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_404AD0(&nArg5);  // 游标读 4 字节 → nArg5
        sub_404A90(&pArg4);  // 游标读 1 字节 → pArg4
        v333 = sub_4BF1B0((int **)dword_8F851C, nArg5);  // sub_4BF1B0 —— 按工会 id 查值指针
        if ( v333 == 0 )  // 条件判定 v333 == 0
          off_77F3FC("ENUM_CMDPACKET_GUILD_INFO - Unexpected guild information. guild = %d", nArg5);  // 日志打印（printf 风格）
        off_77F3FC(  // 日志打印（printf 风格）
          "ENUM_CMDPACKET_GUILD_INFO - guild information received. guild = %d, level = %d",  // （上一调用/表达式的参数续行）
          nArg5,  // （上一调用/表达式的参数续行）
          (uint8_t)pArg4);  // （上一调用/表达式的参数续行）
        sub_4BE2B0(v333, pArg4);  // sub_4BE2B0 —— 公会信息到达（on_receive_guild_info）
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC("ENUM_CMDPACKET_GUILD_INFO - generic error");  // 日志打印（printf 风格）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 60] case 77 = type 78 REQUEST_GUILD_ENTER（申请入会回报）—— sub_429830/sub_48BCC0 ──
    case 77:  // case 77 = 类型 78 ENUM_CMDPACKET_REQUEST_GUILD_ENTER（公会信息回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_404AB0(&nArg5);  // 游标读 2 字节 → nArg5
        sub_404AD0(&pArg4);  // 游标读 4 字节 → pArg4
        v352 = (char *)sub_422E70(833);  // 取本地化文案 833
        sub_48BCC0(&psz[32], 0x1Fu, v352);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
        v353 = sub_429830(nArg5);  // sub_429830 —— 表按键查找（uint16）
        v414 = unknown_libname_2((uint32_t *)(v353 + 16));
        v354 = (const char *)sub_422E70(834);  // 取本地化文案 834
        sprintf(v448, v354, v414, &psz[32]);  // 格式化字符串到缓冲
        sub_44E8D0((char *)dword_8F8528, (void *)0x35, (int)v448, pArg4);  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
      }
      else  // 否则分支
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        if ( HIBYTE(nArg5) == 3 )  // 错误码 == 3 分支
        {
          v357 = sub_422E70(835);  // 取本地化文案 835
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v357, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        }
        else if ( HIBYTE(nArg5) == 31 )  // 否则错误码 == 31
        {
          v356 = sub_422E70(836);  // 取本地化文案 836
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v356, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        }
        else  // 否则分支
        {
          if ( HIBYTE(nArg5) == 36 )  // 错误码 == 36 分支
            v355 = sub_422E70(837);  // 取本地化文案 837
          else  // 否则分支
            v355 = sub_422E70(838);  // 取本地化文案 838
LABEL_934:  // 标签 LABEL_934：合流点
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v355, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 61] case 78 = type 79 REQUEST_MEMBER_ENTER（成员进入请求回报，69 行）—— success/already requested/does not reply 三文案 ──
    case 78:  // case 78 = 类型 79 ENUM_CMDPACKET_REQUEST_MEMBER_ENTER（申请入会回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        v365 = (char *)sub_422E70(669);  // 取本地化文案 669
        sub_48BCC0(&psz[12], 0x32u, v365);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
        v366 = (const char *)sub_422E70(1508);  // 取本地化文案 1508
        sprintf(Buffer, v366, &psz[12]);  // 格式化字符串到缓冲
        off_77F3FC("ENUM_CMDPACKET_REQUEST_MEMBER_ENTER : %s success", &psz[12]);  // 日志打印（printf 风格）
        goto LABEL_950;  // 跳转合流点 LABEL_950
      }
      v367 = (char *)sub_422E70(669);  // 取本地化文案 669
      sub_48BCC0(&psz[12], 0x32u, v367);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
      {
        case '&':  // 字符分支 ’&’（非法字符过滤等）
          off_77F3FC("ENUM_CMDPACKET_REQUEST_MEMBER_ENTER : %s already requested", &psz[12]);  // 日志打印（printf 风格）
          return 1;  // 处理完成，返回 1
        case '\'':  // 字符分支 ’\’’（非法字符过滤等）
          v369 = (const char *)sub_422E70(1529);  // 取本地化文案 1529
          goto LABEL_955;  // 跳转合流点 LABEL_955
        case '(':  // 字符分支 ’(’（非法字符过滤等）
          v369 = (const char *)sub_422E70(1528);  // 取本地化文案 1528
LABEL_955:  // 标签 LABEL_955：合流点
          sprintf(Buffer, v369, &psz[12]);  // 格式化字符串到缓冲
          v370 = Buffer;  // v370 = Buffer（转发）
          goto LABEL_956;  // 跳转合流点 LABEL_956
        case ')':  // 字符分支 ’)’（非法字符过滤等）
          v373 = sub_422E70(1504);  // 取本地化文案 1504
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v373, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          return 1;  // 处理完成，返回 1
        case '*':  // 字符分支 ’*’（非法字符过滤等）
          v374 = sub_422E70(1505);  // 取本地化文案 1505
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v374, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          return 1;  // 处理完成，返回 1
        case '+':  // 字符分支 ’+’（非法字符过滤等）
          v375 = sub_422E70(1506);  // 取本地化文案 1506
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v375, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          return 1;  // 处理完成，返回 1
        case ',':  // 字符分支 ’,’（非法字符过滤等）
          off_77F3FC("ENUM_CMDPACKET_REQUEST_MEMBER_ENTER : %s does not reply", &psz[12]);  // 日志打印（printf 风格）
          return 1;  // 处理完成，返回 1
        case '.':  // 字符分支 ’.’（非法字符过滤等）
          v376 = sub_422E70(1526);  // 取本地化文案 1526
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v376, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          return 1;  // 处理完成，返回 1
        case '/':  // 字符分支 ’/’（非法字符过滤等）
        case '0':  // 字符分支 ’0’（非法字符过滤等）
          v368 = sub_422E70(1530);  // 取本地化文案 1530
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v368, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          return 1;  // 处理完成，返回 1
        case '1':  // 字符分支 ’1’（非法字符过滤等）
          v371 = sub_422E70(1503);  // 取本地化文案 1503
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v371, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          return 1;  // 处理完成，返回 1
        case '2':  // 字符分支 ’2’（非法字符过滤等）
          v372 = sub_422E70(1502);  // 取本地化文案 1502
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v372, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
          return 1;  // 处理完成，返回 1
        default:  // 未列出的码值 → 兜底
          v434 = HIBYTE(nArg5);
          v377 = (const char *)sub_422E70(1507);  // 取本地化文案 1507
          sprintf(v450, v377, v434);  // 格式化字符串到缓冲
          v370 = v450;  // v370 = v450（转发）
LABEL_956:  // 标签 LABEL_956：合流点
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v370, 0);  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
          break;  // 跳出本分支
      }
      return 1;  // 处理完成，返回 1
    // ── [段 62] case 79 = type 80 MEMBER_ENTER_REPLY（成员进入回复）—— failed 文案 + sub_478F40 ──
    case 79:  // case 79 = 类型 80 ENUM_CMDPACKET_MEMBER_ENTER_REPLY（成员进入请求回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        v378 = (char *)sub_422E70(669);  // 取本地化文案 669
        sub_48BCC0(&psz[12], 0x32u, v378);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
        if ( HIBYTE(nArg5) == 1 || HIBYTE(nArg5) == 2 )  // 条件判定
        {
          v380 = (const char *)sub_422E70((HIBYTE(nArg5) != 1) + 1509);  // 调用 sub_422E70
          sprintf(Buffer, v380, &psz[12]);  // 格式化字符串到缓冲
          sub_478F40(1);  // 调用 sub_478F40
        }
        else  // 否则分支
        {
          v379 = (const char *)sub_422E70(1524);  // 取本地化文案 1524
          sprintf(Buffer, v379);  // 格式化字符串到缓冲
        }
LABEL_950:  // 标签 LABEL_950：合流点
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
      }
      else  // 否则分支
      {
        off_77F3FC("ENUM_CMDPACKET_MEMBER_ENTER_REPLY failed");  // 日志打印（printf 风格）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 63] case 80 = type 81 MEMBER_SECEDE（成员退出）—— %s removed + sub_478EA0/sub_478F40 ──
    case 80:  // case 80 = 类型 81 ENUM_CMDPACKET_MEMBER_SECEDE（成员进入回复回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        v362 = (char *)sub_422E70(669);  // 取本地化文案 669
        sub_48BCC0(&psz[12], 0x32u, v362);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
        off_77F3FC("ENUM_CMDPACKET_MEMBER_SECEDE : %s removed", &psz[12]);  // 日志打印（printf 风格）
        v363 = (const char *)sub_422E70(1514);  // 取本地化文案 1514
        sprintf(Buffer, v363, &psz[12]);  // 格式化字符串到缓冲
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 调用 sub_43BEE0
        sub_478F40(1);  // 调用 sub_478F40
        sub_478EA0(1);  // 调用 sub_478EA0
      }
      else  // 否则分支
      {
        v364 = sub_422E70(1501);  // 取本地化文案 1501
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v364, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 64] case 81 = type 82 CALL_MEMER_LIST（拉取名单回报，38 行）—— upper/lower member 逐条明细 ──
    case 81:  // case 81 = 类型 82 ENUM_CMDPACKET_CALL_MEMER_LIST（成员退出回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8518 + 12))(dword_8F8518);  // 虚函数调用（vtable 槽）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_48BCC0(&psz[12], 0x32u, (char *)szPassword);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
        v358 = sub_47B150(&psz[12], HIBYTE(pArg4), 1, 0, 0);  // 调用 sub_47B150
        *(uint32_t *)(v358 + 40) = SHIBYTE(nArg5);  // 字段 v358+40 = SHIBYTE(nArg5)
        HIDWORD(Time) = strlen(&psz[12]);  // 全局/复合字段赋值
        if ( HIDWORD(Time) != 0 )  // 条件判定
          off_77F3FC("\tupper member- level:%d name:%s channel:%d", HIBYTE(pArg4), &psz[12], SHIBYTE(nArg5));  // 日志打印（printf 风格）
        sub_404A90((uint8_t *)&v445 + 3);  // 游标读 1 字节 → v445 高位（错误码字段）
        off_77F3FC("\t%d lower members founded", HIBYTE(v445));  // 日志打印（printf 风格）
        v359 = 0;  // 设文案编号 0，稍后弹窗
        if ( HIBYTE(v445) != 0 )  // 条件判定
        {
          do
          {
            sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
            sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
            v360 = (char *)sub_422E70(669);  // 取本地化文案 669
            sub_48BCC0(&psz[12], 0x32u, v360);  // sub_48BCC0 —— 限量串读入或 strncpy 回退
            v361 = sub_47B150(&psz[12], HIBYTE(pArg4), 1, 0, 0);  // 调用 sub_47B150
            *(uint32_t *)(v361 + 40) = SHIBYTE(nArg5);  // 字段 v361+40 = SHIBYTE(nArg5)
            off_77F3FC("\tlower member - level:%d name:%s channel:%d", HIBYTE(pArg4), &psz[12], SHIBYTE(nArg5));  // 日志打印（printf 风格）
            ++v359;  // 自增 v359（循环计数）
          }
          while ( v359 < HIBYTE(v445) );  // 循环直到读满计数
        }
        sub_478FC0(dword_8F8518);  // 调用 sub_478FC0
        sub_479850(dword_8F8518);  // 调用 sub_479850
      }
      else  // 否则分支
      {
        off_77F3FC("ENUM_CMDPACKET_CALL_MEMER_LIST failed");  // 日志打印（printf 风格）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 65] case 82 = type 83 UPGRADE_ITEM（升级物品回报，120 行）—— ENUM_CMDPACKET_UPGRADE_ITEM ──
    //   含 slot is NULL / equipment is NULL 双错误检查 + %d item added 明细
    case 82:  // case 82 = 类型 83 ENUM_CMDPACKET_UPGRADE_ITEM（拉取名单回报）
      sub_484FF0(dword_8F852C);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v355 = sub_422E70(1658);  // 取本地化文案 1658
            goto LABEL_934;  // 跳转合流点 LABEL_934
          case 0xA:  // case 0xA = 类型 11 ENUM_CMDPACKET_RESPONSE_PEER（P2P 应答回报）
            v355 = sub_422E70(1660);  // 取本地化文案 1660
            goto LABEL_934;  // 跳转合流点 LABEL_934
          case 0xD:  // case 0xD = 类型 14 ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER（踢人回报）
            v355 = sub_422E70(1654);  // 取本地化文案 1654
            goto LABEL_934;  // 跳转合流点 LABEL_934
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            v355 = sub_422E70(1652);  // 取本地化文案 1652
            goto LABEL_934;  // 跳转合流点 LABEL_934
          case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
            v355 = sub_422E70(1661);  // 取本地化文案 1661
            goto LABEL_934;  // 跳转合流点 LABEL_934
          default:  // 未列出的码值 → 兜底
            v435 = HIBYTE(nArg5);
            v391 = (const char *)sub_422E70(1662);  // 取本地化文案 1662
            goto LABEL_1019;  // 跳转合流点 LABEL_1019
        }
      }
      sub_4E9A50(&psz[4]);  // sub_4E9A50 —— 四内联 clong 构造 + 初值（0/0/-1/0）
      v461 = 2;  // 设文案编号 2，稍后弹窗
      sub_404AB0((uint16_t *)&v444 + 1);  // sub_404AB0 —— 游标读 2 字节
      sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      sub_404A90((uint8_t *)&v445 + 3);  // 游标读 1 字节 → v445 高位（错误码字段）
      sub_404AB0((uint16_t *)&v441 + 1);  // sub_404AB0 —— 游标读 2 字节
      off_77F3FC(  // 日志打印（printf 风格）
        "ENUM_CMDPACKET_UPGRADE_ITEM - slot:%d num:%d type:%d grade:%d slot:%d",  // （上一调用/表达式的参数续行）
        HIWORD(v444),  // （上一调用/表达式的参数续行）
        *(uint32_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
        HIBYTE(nArg5),  // （上一调用/表达式的参数续行）
        HIBYTE(v445),  // （上一调用/表达式的参数续行）
        HIWORD(v441));  // （上一调用/表达式的参数续行）
      sub_54D2B0(HIBYTE(nArg5));  // sub_54D2B0 —— 21 行小辅助
      v392 = HIWORD(v444);
      v393 = (int *)dword_8F852C;
      pObj11 = sub_44A980(HIWORD(v444));  // sub_44A980 —— 带界索引 getter
      if ( pObj11 == 0 )  // 条件判定 pObj11 == 0
      {
        v404 = sub_422E70(1661);  // 取本地化文案 1661
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v404, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        off_77F3FC("ENUM_CMDPACKET_UPGRADE_ITEM - ERROR!!! slot %d is NULL", HIWORD(v444));  // 日志打印（printf 风格）
        v461 = -1;
        sub_445150(&psz[4]);  // 调用 sub_445150
        return 1;  // 处理完成，返回 1
      }
      if ( *(uint32_t *)dword_9B0BBC2 != 0 )  // 条件判定
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj11 + 40))(pObj11, *(uint32_t *)dword_9B0BBC2);  // 虚函数调用（vtable 槽）
      else  // 否则分支
        sub_484D50(v393, v392);  // sub_484D50 —— 技能槽清空（按槽类型分流）
      pObj35 = sub_44A980(HIWORD(v441));  // sub_44A980 —— 带界索引 getter
      pObj25 = pObj35;  // pObj25 = pObj35（转发）
      if ( pObj35 == 0 )  // 条件判定 pObj35 == 0
      {
        v397 = sub_422E70(1658);  // 取本地化文案 1658
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v397, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
        off_77F3FC("ENUM_CMDPACKET_UPGRADE_ITEM - ERROR!!! equipment is NULL");  // 日志打印（printf 风格）
        v461 = -1;
        sub_445150(&psz[4]);  // 调用 sub_445150
        return 1;  // 处理完成，返回 1
      }
      v398 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj35 + 188))(pObj35);  // 虚函数调用（vtable 槽）
      sub_4E9FA0(&psz[4], v398);  // sub_4E9FA0 —— 四 clong 防篡拷贝（pArg2 → this）
      if ( HIBYTE(nArg5) <= 2u )  // 条件判定
      {
        sub_41C150((unsigned int)&psz[8], v399, HIBYTE(v445));  // sub_41C150 —— crypt4byte 初始化转发（0x41A590）
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj25 + 184))(pObj25, &psz[4]);  // 虚函数调用（vtable 槽）
        sub_44E8D0((char *)dword_8F8528, (void *)0x3C, pObj25, HIBYTE(nArg5));  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
      }
      else  // 否则分支
      {
        sub_583B50();  // sub_583B50 —— 释放全局缓冲 dword_9B9468 并清零 9B946C/9B9470（服务器列表缓存）【推断】
        sub_484D50((int *)dword_8F852C, HIWORD(v441));  // sub_484D50 —— 技能槽清空（按槽类型分流）
        sub_44E8D0((char *)dword_8F8528, (void *)0x3C, 0, HIBYTE(nArg5));  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        off_77F3FC("\t%d item added", HIBYTE(pArg4));  // 日志打印（printf 风格）
        v400 = 0;  // 设文案编号 0，稍后弹窗
        if ( HIBYTE(pArg4) != 0 )  // 第二字段 != 0
        {
          do
          {
            sub_404AB0((uint16_t *)&v447 + 1);  // sub_404AB0 —— 游标读 2 字节
            sub_404AB0((uint16_t *)&v439 + 1);  // sub_404AB0 —— 游标读 2 字节
            sub_404AD0(&v438);  // 游标读 4 字节 → v438
            sub_63B040(HIWORD(v439), v438);  // sub_63B040 —— 强化结果动画转发（63AFD0）
            off_77F3FC("\tslot:%d index:%d info:%d", HIWORD(v447), HIWORD(v439), v438);  // 日志打印（printf 风格）
            pObj33 = sub_44A980(HIWORD(v447));  // sub_44A980 —— 带界索引 getter
            pObj6 = pObj33;  // pObj6 = pObj33（转发）
            if ( pObj33 != 0 )  // 条件判定 pObj33 != 0
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj33 + 60))(pObj33, HIWORD(v439)) != 0 )  // 虚函数调用（vtable 槽）
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 48))(pObj6, v438);  // 虚函数调用（vtable 槽）
              else  // 否则分支
                off_77F3FC("%dslot is not empty. stack impossible", HIWORD(v447));  // 日志打印（printf 风格）
            }
            else  // 否则分支
            {
              v403 = sub_522300((void *)HIWORD(v439), v438, 0, 0, -1, 1);  // 调用 sub_522300
              sub_484F40((int *)dword_8F852C, HIWORD(v447), v403, 0);  // sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
            }
            ++v400;  // 自增 v400（循环计数）
          }
          while ( v400 < HIBYTE(pArg4) );  // 循环直到读满计数
          v461 = -1;
          sub_445150(&psz[4]);  // 调用 sub_445150
          return 1;  // 处理完成，返回 1
        }
      }
      v461 = -1;
      sub_445150(&psz[4]);  // 调用 sub_445150
      return 1;  // 处理完成，返回 1
    // ── [段 66] case 83 = type 84 RESET_ITEM_ATTR（重置物品属性回报）—— slot/num/type ──
    case 83:  // case 83 = 类型 84 ENUM_CMDPACKET_RESET_ITEM_ATTR（升级物品回报）
      sub_484FF0(dword_8F852C);  // sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            v387 = sub_422E70(1695);  // 取本地化文案 1695
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v387, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0xD:  // case 0xD = 类型 14 ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER（踢人回报）
            v390 = sub_422E70(1696);  // 取本地化文案 1696
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v390, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            v386 = sub_422E70(1657);  // 取本地化文案 1657
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v386, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x12:  // case 0x12 = 类型 19 ENUM_CMDPACKET_MOVE_ITEMSPACE（移动物品栏回报）
            v389 = sub_422E70(1694);  // 取本地化文案 1694
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v389, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            v388 = sub_422E70(1690);  // 取本地化文案 1690
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v388, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          case 0x16:  // case 0x16 = 类型 23 ENUM_CMDPACKET_EXTEND_AVATAR（续时装回报）
            v385 = sub_422E70(1661);  // 取本地化文案 1661
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v385, 0);  // 向消息池投递文案（0x1B = 消息窗类型）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            v435 = HIBYTE(nArg5);
            v391 = (const char *)sub_422E70(1698);  // 取本地化文案 1698
LABEL_1019:  // 标签 LABEL_1019：合流点
            sprintf(v450, v391, v435);  // 格式化字符串到缓冲
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v450, 0);  // sub_44E8D0 —— 对象池借出（按池号取可用对象）
            break;  // 跳出本分支
        }
        return 1;  // 处理完成，返回 1
      }
      sub_404AB0((uint16_t *)&nArg5 + 1);  // sub_404AB0 —— 游标读 2 字节
      sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
      sub_404AB0((uint16_t *)&pArg4 + 1);  // sub_404AB0 —— 游标读 2 字节
      off_77F3FC("ENUM_CMDPACKET_RESET_ITEM_ATTR - slot %d, num %d, type %d", HIWORD(nArg5), *(uint32_t *)dword_9B0BBC2, HIWORD(pArg4));  // 日志打印（printf 风格）
      v381 = HIWORD(nArg5);
      v382 = (int *)dword_8F852C;
      if ( sub_44A980(HIWORD(nArg5)) != 0 )  // 条件判定
      {
        v383 = *(uint32_t *)dword_9B0BBC2;
        if ( *(uint32_t *)dword_9B0BBC2 != 0 )  // 条件判定
        {
          pObj36 = sub_44A980(v381);  // sub_44A980 —— 带界索引 getter
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj36 + 40))(pObj36, v383);  // 虚函数调用（vtable 槽）
        }
        else  // 否则分支
        {
          sub_484D50(v382, v381);  // sub_484D50 —— 技能槽清空（按槽类型分流）
        }
      }
      else  // 否则分支
      {
        off_77F3FC("ENUM_CMDPACKET_RESET_ITEM_ATTR - slot %d is NULL", v381);  // 日志打印（printf 风格）
      }
      if ( HIWORD(pArg4) == 1 )  // 条件判定
      {
        v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
        v47 = sub_422E70(1699);  // 取本地化文案 1699
        goto LABEL_983;  // 跳转合流点 LABEL_983
      }
      if ( HIWORD(pArg4) != 2 )  // 条件判定
        return 1;  // 处理完成，返回 1
      v408 = 1700;  // 设文案编号 1700，稍后弹窗
LABEL_982:  // 标签 LABEL_982：合流点
      v46 = *((uint32_t **)dword_8F8528 + 7);  // 取消息池对象（dword_8F8528 第 7 项）
      v47 = sub_422E70(v408);  // 调用 sub_422E70
      goto LABEL_983;  // 跳转合流点 LABEL_983
    // ── [段 67] case 84..90 = type 85..91（摆摊族）：买摆摊物品/进/出/建/拆/完成展示 六连（sub_541xxx 族） ──
    case 84:  // case 84 = 类型 85 ENUM_CMDPACKET_BUY_PRIVATE_STORE_ITEM（重置物品属性回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_541AE0();  // 调用 sub_541AE0
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        sub_404AD0(ArgList);  // 游标读 4 字节 → ArgList
        sub_404AD0(v440);  // 游标读 4 字节 → v440
        sub_404AB0((uint16_t *)&v447 + 1);  // sub_404AB0 —— 游标读 2 字节
        sub_404AB0((uint16_t *)&pArg4 + 1);  // sub_404AB0 —— 游标读 2 字节
        sub_404AD0(&v438);  // 游标读 4 字节 → v438
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_404AB0((uint16_t *)&v445 + 1);  // sub_404AB0 —— 游标读 2 字节
        off_77F3FC(  // 日志打印（printf 风格）
          "Money %d, Medal %d, Cash %d, ItemSlotIndex %d, ItemIndex %d, Data %d",  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
          *(uint32_t *)ArgList,  // （上一调用/表达式的参数续行）
          *(uint32_t *)v440,  // （上一调用/表达式的参数续行）
          HIWORD(v447),  // （上一调用/表达式的参数续行）
          HIWORD(pArg4),  // （上一调用/表达式的参数续行）
          v438);  // （上一调用/表达式的参数续行）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 40))(  // 虚函数调用（vtable 槽）
          **((uint32_t **)dword_8F852C + 3),  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2);  // 取指针指向的值（参数）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(  // 虚函数调用（vtable 槽）
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),  // （上一调用/表达式的参数续行）
          *(uint32_t *)ArgList);  // 取指针指向的值（参数）
        dword_8F7C0C = *(uint32_t *)v440;  // 写全局 dword_8F7C0C = 游标值 v440
        if ( *(int *)v440 < 0 )  // 字段为负则修正路径
        {
          off_77F3FC(aCriticalError_31, *(uint32_t *)v440);  // 日志打印（printf 风格）
          dword_8F7C0C = 0;
        }
        sub_541C60(SBYTE2(v447), (void *)HIWORD(pArg4), v438, HIBYTE(nArg5), HIWORD(v445));  // sub_541C60 —— 摊位登记提交（522300/4F2D40/484F40 + 47CD00 音效）
      }
      else  // 否则分支
      {
        sub_541AE0();  // 调用 sub_541AE0
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_542000(SHIBYTE(nArg5));  // sub_542000 —— 摊位条目查询（422E70 取串 + 44E8D0，46 行）
      }
      return 1;  // 处理完成，返回 1
    case 85:  // case 85 = 类型 86 ENUM_CMDPACKET_ENTER_PRIVATE_STORE
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
        goto LABEL_1038;  // 跳转合流点 LABEL_1038
      sub_541AE0();  // 调用 sub_541AE0
      sub_404AB0((uint16_t *)&v444 + 1);  // sub_404AB0 —— 游标读 2 字节
      sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
      sub_541A60(2);  // sub_541A60 —— 摊位子页切换（44AB50 + 44E850 + 44BBA0）
      v436 = HIWORD(v444);
      sub_541A30();  // sub_541A30 —— 摊位条目名取串（10 行）
      sub_5419F0(v436);  // sub_5419F0 —— 摊位动画辅助（429830）
      for ( ; HIBYTE(nArg5) != 0; --HIBYTE(nArg5) )  // （表达式/调用续行）
      {
        sub_404AB0((uint16_t *)&v441 + 1);  // sub_404AB0 —— 游标读 2 字节
        sub_404AD0(ArgList);  // 游标读 4 字节 → ArgList
        sub_404AB0((uint16_t *)&v445 + 1);  // sub_404AB0 —— 游标读 2 字节
        sub_404AD0(dword_9B0BBC2);  // 游标读 4 字节 → dword_9B0BBC2
        sub_404A90((uint8_t *)&pArg4 + 3);  // 游标读 1 字节 → pArg4 高位（错误码字段）
        sub_404AB0((uint16_t *)&v447 + 1);  // sub_404AB0 —— 游标读 2 字节
        pObj32 = sub_541A30();  // sub_541A30 —— 摊位条目名取串（10 行）
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj32 + 56))(  // 虚函数调用（vtable 槽）
          pObj32,  // （上一调用/表达式的参数续行）
          HIWORD(v441),  // （上一调用/表达式的参数续行）
          *(uint32_t *)ArgList,  // （上一调用/表达式的参数续行）
          HIWORD(v445),  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
          HIBYTE(pArg4),  // （上一调用/表达式的参数续行）
          HIWORD(v447));  // （上一调用/表达式的参数续行）
        off_77F3FC(  // 日志打印（printf 风格）
          " slot %d, price %d, index %d, data %d, upgarade %d, durability %d",  // （上一调用/表达式的参数续行）
          HIWORD(v441),  // （上一调用/表达式的参数续行）
          *(uint32_t *)ArgList,  // （上一调用/表达式的参数续行）
          HIWORD(v445),  // （上一调用/表达式的参数续行）
          *(uint32_t *)dword_9B0BBC2,  // （上一调用/表达式的参数续行）
          HIBYTE(pArg4),  // （上一调用/表达式的参数续行）
          HIWORD(v447));  // （上一调用/表达式的参数续行）
      }
      return 1;  // 处理完成，返回 1
    case 86:  // case 86 = 类型 87 ENUM_CMDPACKET_EXIT_PRIVATE_STORE
    case 90:  // case 90 = 类型 91 ENUM_CMDPACKET_MOVE_TO_GATE（走向传送门回报）
LABEL_1038:  // 标签 LABEL_1038：合流点
      sub_541AE0();  // 调用 sub_541AE0
      return 1;  // 处理完成，返回 1
    case 87:  // case 87 = 类型 88 ENUM_CMDPACKET_CREATE_PRIVATE_STORE
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_541AE0();  // 调用 sub_541AE0
        off_77F3FC((char *)&byte_72A0DC);  // 日志打印（printf 风格）
        sub_430230(dword_8F7C08);  // sub_430230 —— 个人商店开店定位
        off_77F3FC((char *)&byte_72A0BC);  // 日志打印（printf 风格）
        sub_541A60(0);  // sub_541A60 —— 摊位子页切换（44AB50 + 44E850 + 44BBA0）
      }
      else  // 否则分支
      {
        sub_541AE0();  // 调用 sub_541AE0
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_5420A0(SHIBYTE(nArg5));  // sub_5420A0 —— 摊位条目查询 2（+43BEE0 图标 + 44ABE0）
      }
      return 1;  // 处理完成，返回 1
    case 88:  // case 88 = 类型 89 ENUM_CMDPACKET_REMOVE_PRIVATE_STORE
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_541AE0();  // 调用 sub_541AE0
        sub_42FBE0((uint32_t *)dword_8F7C08);  // sub_42FBE0 —— 商店复位
        sub_542AD0();  // sub_542AD0 —— 摊位页切换（44AB50 + 542940，60 行）
      }
      else  // 否则分支
      {
        sub_541AE0();  // 调用 sub_541AE0
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_542190(SHIBYTE(nArg5));  // sub_542190 —— 摊位条目查询 3（+44AB50 页切换）
      }
      return 1;  // 处理完成，返回 1
    case 89:  // case 89 = 类型 90 ENUM_CMDPACKET_COMPLETE_DISPLAY
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_541AE0();  // 调用 sub_541AE0
        sub_42FBF0((uint32_t *)dword_8F7C08);  // sub_42FBF0 —— 商店标志消解
        sub_541A60(1);  // sub_541A60 —— 摊位子页切换（44AB50 + 44E850 + 44BBA0）
      }
      else  // 否则分支
      {
        sub_541AE0();  // 调用 sub_541AE0
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_542220(SHIBYTE(nArg5));  // sub_542220 —— 摊位条目查询 4（28 行）
      }
      return 1;  // 处理完成，返回 1
    // ── [段 68] case 92 = type 93 ENTER_WARROOM（进战争房间回报）—— err %d + sub_583A80 ──
    case 92:  // case 92 = 类型 93 ENUM_CMDPACKET_ENTER_WARROOM
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        pArg4 = 0;
        nArg5 = 0;
        sub_404AD0(&pArg4);  // 游标读 4 字节 → pArg4
        sub_404AB0(&nArg5);  // 游标读 2 字节 → nArg5
        v406 = *(uint32_t *)(pArg1 + 40);  // 读字段 v406 = pArg1 + 40
        if ( *(uint32_t *)(v406 + 32) == 1 )  // 读全局对象字段并与常数比较
          sub_583A80(v406, (uint16_t)nArg5);  // sub_583A80 —— 数值槽 setter：+50 标志为真直写 +56，否则写 +52 = a2 - 基址表 dword_79D100[+44]
      }
      else  // 否则分支
      {
        HIBYTE(v439) = 0;  // 清 v439 高字节（即将读取）
        sub_404A90((uint8_t *)&v439 + 3);  // 游标读 1 字节 → v439 高位（错误码字段）
        switch ( HIBYTE(v439) )  // （表达式/调用续行）
        {
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            off_77F3FC((char *)&byte_729EF4);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0xA:  // case 0xA = 类型 11 ENUM_CMDPACKET_RESPONSE_PEER（P2P 应答回报）
            off_77F3FC(byte_729F08);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
LABEL_1077:  // 标签 LABEL_1077：合流点
            off_77F3FC(byte_729F14);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            off_77F3FC("err %d", HIBYTE(v439));  // 日志打印（printf 风格）
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 69] case 94..98 = type 95..99（战争房间/决斗场族）：座位状态/死亡/邮件族（sub_523xxx/sub_524xxx） ──
    case 94:  // case 94 = 类型 95 ENUM_CMDPACKET_DIE_WARROOM_CHARACTER
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        HIBYTE(nArg5) = -1;  // 复合字段拆分/赋值
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        off_77F3FC((char *)&byte_72A078, HIBYTE(nArg5));  // 日志打印（printf 风格）
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        if ( HIBYTE(nArg5) == 18 )  // 错误码 == 18 分支
        {
          off_77F3FC(byte_72A004);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 19 )  // 否则错误码 == 19
        {
          off_77F3FC(byte_72A020);  // 日志打印（printf 风格）
        }
        else  // 否则分支
        {
          off_77F3FC((char *)&byte_72A054, HIBYTE(nArg5));  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    case 95:  // case 95 = 类型 96 ENUM_CMDPACKET_START_WARROOM_TEMP（战争房间死亡回报）
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        if ( HIBYTE(nArg5) == 18 )  // 错误码 == 18 分支
        {
          off_77F3FC(byte_729FBC);  // 日志打印（printf 风格）
        }
        else if ( HIBYTE(nArg5) == 22 )  // 否则错误码 == 22
        {
          off_77F3FC(byte_729FD8);  // 日志打印（printf 风格）
        }
      }
      return 1;  // 处理完成，返回 1
    case 96:  // case 96 = 类型 97 ENUM_CMDPACKET_MAILBOX_SEND
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        sub_525130();  // 调用 sub_525130
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_523390(HIBYTE(nArg5));  // 调用 sub_523390
      }
      return 1;  // 处理完成，返回 1
    case 97:  // case 97 = 类型 98 ENUM_CMDPACKET_MAILBOX_EXTRACT_ITEM（收邮件附件回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        nArg5 = 0;
        sub_404AD0(&nArg5);  // 游标读 4 字节 → nArg5
        sub_524760(nArg5);  // 调用 sub_524760
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_523340(HIBYTE(nArg5));  // 调用 sub_523340
      }
      return 1;  // 处理完成，返回 1
    case 98:  // case 98 = 类型 99 ENUM_CMDPACKET_MAILBOX_OPEN（打开邮箱回报）
      if ( (uint8_t)nArg5 != 0 )  // 成败判定：包长低字节 != 0
      {
        nArg5 = 0;
        sub_404AB0(&nArg5);  // 游标读 2 字节 → nArg5
        sub_524790((int16_t)nArg5);  // 调用 sub_524790
      }
      else  // 否则分支
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        sub_522E50(HIBYTE(nArg5));  // 调用 sub_522E50
      }
      return 1;  // 处理完成，返回 1
    // ── [段 70] case 100 = type 101 QUICK_JOIN_ROOM（快速加入房间回报）—— sub_62DFD0/sub_642410 ──
    case 100:  // case 100 = 类型 101 ENUM_CMDPACKET_QUICK_JOIN_ROOM（快速加入房间回报）
      if ( dword_9B9534 != 0 )  // 条件判定 dword_9B9534 != 0
        sub_642410(1);  // sub_642410 —— PVP 房间列表数据 2（14 行）
      if ( dword_9B9454 != 0 )  // 条件判定 dword_9B9454 != 0
        sub_62DFD0(1);  // sub_62DFD0 —— 按钮按下标志写入
      if ( (uint8_t)nArg5 == 0 )  // 成败判定：包长低字节 == 0
      {
        HIBYTE(nArg5) = 0;  // 清 nArg5 高字节（即将写入错误码）
        sub_404A90((uint8_t *)&nArg5 + 3);  // 游标读 1 字节 → nArg5 高位（错误码字段）
        switch ( HIBYTE(nArg5) )  // 按错误码（nArg5 高字节）分派
        {
          case 4:  // case 4 = 类型 5 ENUM_CMDPACKET_CREATE_CHARACTER（建角回报）
            off_77F3FC(byte_729FA0);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
            off_77F3FC(byte_729F98);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          case 0x13:  // case 0x13 = 类型 20 ENUM_CMDPACKET_SORT_ITEM（整理物品回报）
            goto LABEL_1077;  // 跳转合流点 LABEL_1077
          case 0x37:  // case 0x37 = 类型 56 ENUM_CMDPACKET_SET_PVP_READY_STATE
            off_77F3FC(byte_729F70);  // 日志打印（printf 风格）
            break;  // 跳出本分支
          default:  // 未列出的码值 → 兜底
            off_77F3FC(byte_729F50);  // 日志打印（printf 风格）
            break;  // 跳出本分支
        }
      }
      return 1;  // 处理完成，返回 1
    // ── [段 71] default：未识别回报类型，直接 return 1 ──
    default:  // 未列出的码值 → 兜底
      return 1;  // 处理完成，返回 1
  }
}

