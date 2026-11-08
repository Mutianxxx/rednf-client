// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNRDDonkey                 主虚表槽位数: 85   字段数: 17
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNRDDonkey -> CNRDObject -> KGameMessenger -> KMessenger
// 族属: 核心对象族
// 依据: ①权威 struct src/cnrd/CNRDObject.h（会话 3 逐行精修 84 槽虚表 + 全字段）与
//        src/cnrd/IRDCollisionObject.h（167 槽命中链主战场）②证据行 va 的 src 函数头注释
// 本类证据行: 0x4BD510 绑定/动画盒写（equ_buff.cpp:11384）/ 0x4BD5E0 主人绑定（11396）/ 0x4BD720 摆摊驴装配（11509）
// 证据函数（src 头注释）: 0x4310E0 CNRDDonkey__vmt0 —— 驴子删除析构
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDDonkey_Fields {
    // ---- 区块 1：本段直证点（基类布局见 src/cnrd/CNRDObject.h / IRDCollisionObject.h） ----
    unsigned char _base_0x0000        [120]; // +0x0000..0x0077 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pAnimObj              ; // +0x0078 (120) x4  基类动画对象指针（★全库通用 this+120；src/cnrd/CNRDObject.h +0x078 animObj；0x499020/0x499080 帧时刻同步宿主）（证据: va=00499020）
    unsigned char _unused_0x007C      [108]; // +0x007C..0x00E7 未观测
    unsigned char    bSyncFlag             ; // +0x00E8 (232) x2  基类时刻同步开关位（0x499020 读旧值：非 0 转 0 时推进帧时刻）（证据: va=00499020）
    unsigned char _unused_0x00E9      [3]; // +0x00E9..0x00EB 未观测
    unsigned int     nSyncArgA             ; // +0x00EC (236) x1  基类时刻同步参数 A（0x499020 第三参 nArg3）（证据: va=00499020）
    unsigned int     nSyncArgB             ; // +0x00F0 (240) x1  基类时刻同步参数 B（0x499020 第四参 nArg4）（证据: va=00499020）
    float            fSyncTime             ; // +0x00F4 (244) x4  基类浮点时刻槽（0x499080 浮点版：非 0 转 0 时推帧）（证据: va=00499080）
    unsigned char    bQuad1                ; // +0x00F8 (248) x1  基类四元组字节槽 1（0x42A8D0 CNRDObject__vmt11C 批量写 +248..+260）（证据: va=0042A8D0）
    unsigned char _unused_0x00F9      [3]; // +0x00F9..0x00FB 未观测
    unsigned int     nQuad2                ; // +0x00FC (252) x1  基类四元组 dword 槽 2（0x42A8D0）（证据: va=0042A8D0）
    unsigned char    bQuad3                ; // +0x0100 (256) x1  基类四元组字节槽 3（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0101      [3]; // +0x0101..0x0103 未观测
    unsigned int     nQuad4                ; // +0x0104 (260) x1  基类四元组 dword 槽 4（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0108      [20]; // +0x0108..0x011B 未观测
    unsigned char    bBindGate284          ; // +0x011C (284) x2  绑定/记录门字节（0x4BD510：非 0 才把 nArg2/nArg3 记录到 +364/+368）（证据: va=004BD510）
    unsigned char    bField285             ; // +0x011D (285) x1  装配门字节（0x4BD720 首段判非 0）【推断】（证据: va=004BD720）
    unsigned char _unused_0x011E      [2]; // +0x011E..0x011F 未观测
    unsigned int     pMaster288            ; // +0x0120 (288) x1  主人绑定对象（0x4BD5E0：*(this+288)=nArg2 后经主人 vt+120/124/128 取位；抄主人 +652）（证据: va=004BD720）
    unsigned char _unused_0x0124      [12]; // +0x0124..0x012F 未观测
    unsigned int     pLayer304             ; // +0x0130 (304) x1  图层/子件槽（0x4BD720 取 fld_130 = *(this+304) 参与装配）【推断】（证据: va=004BD720）
    unsigned char _unused_0x0134      [56]; // +0x0134..0x016B 未观测
    unsigned int     nBindPos364           ; // +0x016C (364) x1  绑定坐标记录 X（0x4BD510：+284 门开时记 nArg2）（证据: va=004BD510）
    unsigned int     nBindPos368           ; // +0x0170 (368) x1  绑定坐标记录 Y（0x4BD510：门开时记 nArg3）（证据: va=004BD510）
    unsigned int     nBindRef372           ; // +0x0174 (372) x1  绑定参考值 A（0x4BD510：记 dword_8F7A24+20 的 +100，无则 -1 哨兵）（证据: va=004BD510）
    unsigned int     nBindRef376           ; // +0x0178 (376) x1  绑定参考值 B（0x4BD510：记 +104 首元素，无则 -1 哨兵）（证据: va=004BD510）
};
#pragma pack(pop)

// 统计: 字段行 17 / 未命名 0 / 标【推断】2 / 末尾偏移 +0x017C
