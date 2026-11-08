// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNChangeStatus                         主虚表槽位数: 33  字段数: 6
// 继承: CNChangeStatus -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   005F8570  CNChangeStatus__vmt4（+96 模式 1/2 + 4600B0/4E77D0/5E5260）（src/combat/swordman_skills.cpp:2476）
//   005F8080  CNChangeStatus__vmt14（+44 剩余时间 + switch 3/5/6/7 分档动画）（src/combat/swordman_skills.cpp:2267）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNCHANGESTATUS
#define ARAD40JP_FIELDS_CNCHANGESTATUS

#include <stdint.h>

#pragma pack(push, 1)
struct CNChangeStatus_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x7  va=005F8570 宿主对象指针（0x5F8570: *(this+4) 经 vt+940 判、vt+340 图类型、60003 变体比对）
    unsigned char _unused_0x0008      [36]; // +0x0008..0x002B 未观测
    unsigned int     nExpireMs           ; // +0x002C (44) x2  va=005F8080 剩余时间 ms（0x5F8080: *(this+44) - clock_now(this+8)；<500 时做 255→0 淡出）
    unsigned char _unused_0x0030      [48]; // +0x0030..0x005F 未观测
    unsigned int     nStatusMode         ; // +0x0060 (96) x4  va=005F8570 状态模式（0x5F8080: switch 3/5/6/7 分派动画组；0x5F8570: ==1/==2 分派）
    unsigned int     pStatFxA            ; // +0x0064 (100) x4  va=005F8570 状态件 A（0x5F8570: ==2 时 fld_64=**(this+100) 经 vt+40/vt+92 取值回调）
    unsigned int     pStatFxB            ; // +0x0068 (104) x1  va=005F8570 状态件 B（0x5F8570: ==2 时 *(this+104) 同 A 流程）
    unsigned char _unused_0x006C      [4]; // +0x006C..0x006F 未观测
    unsigned int     pStatFxVec          ; // +0x0070 (112) x3  va=005F8080 状态件数组（0x5F8080: *(this+112) 4 字节/项；switch 3/5 按 +170 状态 ±2 偏移取件）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0074

#endif

