// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNAsura
// 结论: ★ 本类在 40JP（2006-06-13 日服客户端 ARAD.exe）中【不存在】，
//       因此无字段表可还原 —— 本文件为存在性反证记录（占位）。
// ------------------------------------------------------------
// 反证证据（四路独立验证，全部为直证）:
//   ① RTTI 全表（data/rtti_hierarchy.txt，743 类）无 "CNAsura" 类型描述符；
//   ② 虚表映射（data/rtti_vtable_map.txt，783 个 VT / 746 个 TD）无该名字；
//   ③ 虚表槽位 dump（data/class_method_slots.txt，97K 行）无该名字；
//   ④ 全库源码 grep（src/ 77 文件 + work/ dump + docs/）无该名字。
// ------------------------------------------------------------
// 该客户端「职业分支」的真实存在方式（data-driven，非 C++ 类）:
//   本二进制只实现 4 个可玩职业基类（IRDCharacter 的派生全集）:
//     CNFighter / CNGunner / CNMage / CNSwordman
//   转职分支只以【数据】形式存在，代码侧统一走 CNFighter/CNGunner/CNMage/CNSwordman
//   + growtype 编号：
//     job0=swordman: 1=weaponmaster 3=berserker 4=asura
//     job1=fighter:  2=striker 3=streetfighter 4=grabbler
//     job2=gunner:   1=ranger 2=launcher 4=spitfire
//     job3=mage:     2=summoner 3=battlemage
//   证据: src/game/equ_buff.cpp:15-18 与 :72-126（sub_4B0080 .equ 路径表，
//         字符串 "character/<job>/growtype/<branch>.equ"）。
// ------------------------------------------------------------
// CNAsura 与数据名称的对应关系:
////  · 数据名: asura（asura.equ，src/game/equ_buff.cpp:126 直证）
//  · 若需建模：引用 CNSwordman 字段表（同目录 CNSwordman.h）
// ------------------------------------------------------------
// 字段归属建议（本类如按后续版本命名习惯建模）:
//   其运行时字段 = 上述对应基类（CNSwordman）的字段表
//   （见同目录 CNSwordman.h）；无任何该分支独占的 C++ 字段证据。
// ============================================================
#ifndef ARAD40JP_FIELDS_CNASURA
#define ARAD40JP_FIELDS_CNASURA

// 【不存在】无字段表 —— 见文件头反证记录。
// 若后续需要建模该职业分支，请引用对应基类字段表：
#include "CNSwordman.h"   // 例：typedef CNSwordman_Fields CNAsura_Fields;（语义同基类，无分支独占字段证据）

#endif
