// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNEquipmentAssaultAttackerCoat 主虚表槽位数: 79   字段数: 19
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNEquipmentAssaultAttackerCoat -> CNEventEquipment -> CNRDEquipment -> IRDItem
// 族属: 装备PO·事件触发族
// 依据: ①一族一模板（batchB 已定案同名沿用）：+8/12 技能槽记录〔0x485F70〕/ +36..40 状态字〔0x4859F0〕/
//        +1256..1260 条件组表〔0x604A50〕/ +1276 触发标志与 +1284 计数〔0x4BAC70〕/ +1288..1334 动画件表族〔0x4EF9D0〕/
//        +1432..1436 触发门〔0x604A50〕②证据行 va 的 src 函数头注释
//        ③同族 39 类同构（候选偏移签名 = 本族 19 字段，含事件触发面 0x4E8/0x598；装备 PO 族合计 68 类同一布局模板）
// 本类证据行: 效果触发槽 vmt88/8C/90/94/98/130（本族四/五通道编排，见 src/game/po_effects.cpp 0x5146B0..0x51A630 族）
// 证据函数（src 头注释）: CNEquipmentAssaultAttackerCoat 构造器（突击攻击者外套）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNEquipmentAssaultAttackerCoat_Fields {
    // ---- 区块 1：继承 IRDItem/CNRDEquipment 段（技能槽记录 0x485F70 / 状态字 0x4859F0） ----
    unsigned char _base_0x0000        [8]; // +0x0000..0x0007 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     nSkillRec8            ; // +0x0008 (8) x1  技能槽记录首字（0x485F70 IRDItem 深拷贝：this+8 ← pArg2[0]，记录 +8..+84 各字段 + 双容器）（证据: va=00485F70）
    unsigned int     nSkillRec12           ; // +0x000C (12) x1  技能槽记录次字（0x485F70：this+12 ← pArg2[4]）（证据: va=00485F70）
    unsigned char _unused_0x0010      [20]; // +0x0010..0x0023 未观测
    unsigned int     nStateWord36          ; // +0x0024 (36) x1  状态字（0x4859F0 状态判定：==0 直接通过；==3 时还须 +40 非 0）（证据: va=004859F0）
    unsigned char    bStateSub40           ; // +0x0028 (40) x1  状态子标志（0x4859F0 仅当状态字 ==3 时判此字节）（证据: va=004859F0）
    // ---- 区块 3：继承 CNRDEquipment 容器区（效果计数 0x4BAC70 / 动画件表 0x4EF9D0） ----
    unsigned char _unused_0x0029      [1215]; // +0x0029..0x04E7 未观测
    unsigned int     pCondVec1256          ; // +0x04E8 (1256) x1  条件组表 begin（0x604A50：非空且 end−begin ≠ 0 则跳过条件审批直接放行）（证据: va=00604A50）
    unsigned int     pCondVec1260          ; // +0x04EC (1260) x1  条件组表 end（0x604A50 与 +1256 求元素数）（证据: va=00604A50）
    unsigned char _unused_0x04F0      [12]; // +0x04F0..0x04FB 未观测
    unsigned char    bEffectArmed1276      ; // +0x04FC (1276) x1  效果触发已激活标志（0x4BAC70 计数归零时清 0；0x4BACA0 直写）（证据: va=004BAC70）
    // ---- 区块 5：事件触发面（条件组表 0x604A50 / 触发锁存 +1432..1436） ----
    unsigned char _unused_0x04FD      [7]; // +0x04FD..0x0503 未观测
    unsigned int     nEffectCount1284      ; // +0x0504 (1284) x1  效果触发计数（0x4BAC70 直写 nArg2；为 0 时联动清 +1276）（证据: va=004BAC70）
    unsigned char _unused_0x0508      [4]; // +0x0508..0x050B 未观测
    unsigned int     pAnimRow1292          ; // +0x050C (1292) x1  动画行表基址（0x4EF9D0：124 字节步距 × 行号 + 此基址 = 行条目）（证据: va=004EF9D0）
    unsigned char _unused_0x0510      [12]; // +0x0510..0x051B 未观测
    unsigned int     pRowVec1308           ; // +0x051C (1308) x1  动画行向量 begin（0x4EF9D0：与 +1312/+1316 构成 vector）（证据: va=004EF9D0）
    unsigned int     pRowVec1312           ; // +0x0520 (1312) x2  动画行向量 end（0x4EF9D0：(+1312 − +1308) >> 2 = 已建行数）（证据: va=004EF9D0）
    unsigned int     pRowVec1316           ; // +0x0524 (1316) x1  动画行向量 cap（0x4EF9D0 容量门：满则 sub_428220 扩容）（证据: va=004EF9D0）
    unsigned char    bAnimBuilt1320        ; // +0x0528 (1320) x2  动画件已装配门（0x4EF9D0 惰性一次：完成置 1；0x4EAF30 前初值 0）（证据: va=004EF9D0）
    unsigned char _unused_0x0529      [3]; // +0x0529..0x052B 未观测
    unsigned int     pAnimAtlas1324        ; // +0x052C (1324) x17 动画图集对象（0x4EF9D0 sub_4319E0 第一参；0x4EAF30 由宿主 +1092 记录）（证据: va=004EF9D0）
    unsigned int     pAnimHost1328         ; // +0x0530 (1328) x17 动画宿主对象（0x4EF9D0 sub_4319E0 第二参；0x4EAF30 由宿主 +1096 记录）（证据: va=004EF9D0）
    unsigned int     pEquipDef1332         ; // +0x0534 (1332) x20 装备/动画定义对象（0x4EF9D0 取其 +1056 动画行表与 +1088 图集；0x4EAF30 直记宿主）（证据: va=004EF9D0）
    unsigned char _unused_0x0538      [96]; // +0x0538..0x0597 未观测
    unsigned char    bTriggerLatch1432     ; // +0x0598 (1432) x3  效果触发锁存标志（0x604A50：置 1 后不再重复触发；初值 0）（证据: va=00604A50）
    unsigned char    bTriggerSub1433       ; // +0x0599 (1433) x3  效果触发附属字节（0x604A50 与 +1432 同批写）（证据: va=00604A50）
    unsigned char _unused_0x059A      [2]; // +0x059A..0x059B 未观测
    unsigned int     nSceneType1436        ; // +0x059C (1436) x2  场景类型/装备类别（0x604A50：==4 直接放行，否则与全局场景类型字段比对）（证据: va=00604A50）
};
#pragma pack(pop)

// 统计: 字段行 19 / 未命名 0 / 标【推断】0 / 末尾偏移 +0x05A0
