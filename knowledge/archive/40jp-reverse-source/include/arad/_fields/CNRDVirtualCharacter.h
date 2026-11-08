// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 B 弹道/机关/技能物件族还原）
// 类: CNRDVirtualCharacter         主虚表槽位数: 104  字段数: 21
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchB.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNRDVirtualCharacter -> CNRDObject -> KGameMessenger -> KMessenger
// 依据: ①通用偏移表（this+120 动画对象 / +642..644 帧覆盖 / +680..704 表现名字快照块〔0x4E1FE0〕/
//        +964..968 载荷缓冲对〔0x5FFF80〕/ +972.. 附属句柄面〔0x5FF8E0 数值槽初始化〕）
//        ②证据行 va 的 src 函数头注释 ③同族跨类印证 ④docs/92 官方名
// 本类证据: 虚拟角色（broadcast_debug.cpp §19 虚表家族 0x42F350-0x432C70；非 PO 系）
// 证据函数（src 头注释）: 0x42B1C0 CNRDVirtualCharacter__vmt150 —— 三元组写（+284，vt+336） /
//   0x42B220 CNRDVirtualCharacter__vmt164 —— 串数据指针（+588，vt+356） /
//   0x42B240 CNRDVirtualCharacter__vmt0 —— CNRDVirtualCharacter 析构（vt+0） /
//   0x42F350 CNRDVirtualCharacter__vmtC —— 复位与位置同步
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDVirtualCharacter_Fields {
    // ---- 区块 1：继承段（通用偏移表；动画对象/帧同步/参数灌入/帧覆盖/表现名字快照块〔0x4E1FE0〕） ----
    unsigned char _base_0x0000        [120]; // +0x0000..0x0077 继承段（见 src/cnrd/*.h、CNRDPassiveObject.h；不重复展开）
    unsigned int     pAnimObj              ; // +0x0078 (120) x4  动画对象指针（全库通用 this+120；0x499020/0x499080 帧时刻同步宿主）（证据: va=00499020）
    unsigned char _unused_0x007C      [36]; // +0x007C..0x009F 未观测
    unsigned int     pAnimBox640           ; // +0x00A0 (160) x1  帧 0 动画盒边界对象（0x432640：sub_4918E0(sub_4924C0(0),2) 写入；0x42FB00 双槽 +640/+644 释放）（证据: va=00432640）
    unsigned char _unused_0x00A4      [68]; // +0x00A4..0x00E7 未观测
    unsigned char    bAnimSync232          ; // +0x00E8 (232) x2  动画时刻同步开关（0x499020 关→开时同步帧时刻；0x498B70 复位）（证据: va=00499020）
    unsigned char _unused_0x00E9      [3]; // +0x00E9..0x00EB 未观测
    unsigned int     uAnimSync236          ; // +0x00EC (236) x1  动画同步参数 A（0x499020 写 nArg3）（证据: va=00499020）
    unsigned int     uAnimSync240          ; // +0x00F0 (240) x1  动画同步参数 B（0x499020 写 nArg4）（证据: va=00499020）
    float            fAnimSync244          ; // +0x00F4 (244) x4  动画同步浮点参数（0x499080 浮点版：非 0→0 时推帧）（证据: va=00499080）
    unsigned char    bParam248             ; // +0x00F8 (248) x1  参数灌入槽 1（0x42A8D0 CNRDObject__vmt11C 批量写 +248..+260）（证据: va=0042A8D0）
    unsigned char _unused_0x00F9      [3]; // +0x00F9..0x00FB 未观测
    unsigned int     uParam252             ; // +0x00FC (252) x1  参数灌入槽 2（0x42A8D0）（证据: va=0042A8D0）
    unsigned char    bParam256             ; // +0x0100 (256) x1  参数灌入槽 3（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0101      [3]; // +0x0101..0x0103 未观测
    unsigned int     uParam260             ; // +0x0104 (260) x1  参数灌入槽 4（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0108      [20]; // +0x0108..0x011B 未观测
    unsigned int     nJobId284             ; // +0x011C (284) x2  职业 id（0x432640 入口比较 +284；sub_4CE8A0(职业) 取外观条目；0x42B0F0 构造初值 4）（证据: va=00432640）
    unsigned int     nSubJob288            ; // +0x0120 (288) x1  职业子档 -1 哨兵（0x42B0F0 构造置 -1、0x432640 重载时重置）【推断】（证据: va=00432640）
    unsigned char _unused_0x0124      [4]; // +0x0124..0x0127 未观测
    unsigned int     pAnim296              ; // +0x0128 (296) x1  职业动画件 1（0x432640：外观条目 +269 串经 sub_431920 建件后写入）（证据: va=00432640）
    unsigned int     pAnim300              ; // +0x012C (300) x1  职业动画件 2（0x432640：外观条目 +213 串建件；sub_493D00 设速率 120.0）（证据: va=00432640）
    unsigned int     pAnim304              ; // +0x0130 (304) x1  职业动画件 3（0x432640：外观条目 +206 串建件）（证据: va=00432640）
    unsigned char _unused_0x0134      [32]; // +0x0134..0x0153 未观测
    unsigned int     pSlotTbl340           ; // +0x0154 (340) x1  职业槽表起点（0x432640：+340 = 0xFFFF 哨兵、+384 起 10×16 子对象释放；0x42B0F0 EH 构造 10×16）（证据: va=00432640）
    unsigned char _unused_0x0158      [200]; // +0x0158..0x021F 未观测
    unsigned int     pEqVec544             ; // +0x0220 (544) x2  装备槽向量 begin（0x432640/0x42B0F0：非 0 先 free 再清三字段 544/548/552）（证据: va=00432640）
    unsigned int     pEqVec548             ; // +0x0224 (548) x1  装备槽向量 end（同组三字段之二）（证据: va=00432640）
    unsigned int     pEqVec552             ; // +0x0228 (552) x1  装备槽向量 cap（同组三字段之三）（证据: va=00432640）
    unsigned char _unused_0x022C      [20]; // +0x022C..0x023F 未观测
    unsigned int     uOffset576            ; // +0x0240 (576) x4  职业位移表值 A（0x432640 按职业档写 2 / -3 / 0 / -10；vt+188 职业动画装载）（证据: va=00432640）
    unsigned int     uOffset580            ; // +0x0244 (580) x4  职业位移表值 B（0x432640 同批写 91 / 120 / 76 / 92）（证据: va=00432640）
};
#pragma pack(pop)

// 统计: 字段行 21 / 未命名 0 / 标【推断】1 / 末尾偏移 +0x0248
