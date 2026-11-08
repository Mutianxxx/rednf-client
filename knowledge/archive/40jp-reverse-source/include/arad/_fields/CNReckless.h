// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNReckless                             主虚表槽位数: 31  字段数: 8
// 继承: CNReckless -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   00650B50  sub_650B50 参数装配（40 号表 8 项 → +44/80/100/104/84/88/92/96）（src/nengine/zlib_inflate.cpp:765）
//   00650A10  sub_650A10 属性累加 tick（+80/100/84/104/88/92/96 七槽入宿主）（src/nengine/zlib_inflate.cpp:698）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRECKLESS
#define ARAD40JP_FIELDS_CNRECKLESS

#include <stdint.h>

#pragma pack(push, 1)
struct CNReckless_Fields {
    unsigned char _base_0x0000        [44]; // +0x0000..0x002B 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     nParamSlotA         ; // +0x002C (44) x1  va=00650B50 参数槽 A（0x650B50: *(this+44)=表项[0]）
    unsigned char _unused_0x0030      [32]; // +0x0030..0x004F 未观测
    unsigned int     nParamSlotB         ; // +0x0050 (80) x2  va=00650A10 参数槽 B（0x650B50: *(this+80)=表项[1]；0x650A10 累加进宿主 +60）
    unsigned int     nDefenseAdd         ; // +0x0054 (84) x2  va=00650A10 防御加算（0x650A10: *(this+84) 累加进宿主 +116）
    int              fHpRegenRate        ; // +0x0058 (88) x2  va=00650A10 HP 回复率 ×0.01（0x650A10: *(this+88)×0.001 累加进宿主 +830）
    int              fMpRegenRate        ; // +0x005C (92) x2  va=00650A10 MP 回复率 ×0.01（0x650A10: *(this+92)×0.001 累加进宿主 +858）
    unsigned int     nStatAddSource      ; // +0x0060 (96) x2  va=00650A10 属性加算源（0x650A10: *(this+96) 逐个加进宿主 +284 起 16 属性槽，步长 14）
    float            fAtkPct             ; // +0x0064 (100) x2  va=00650A10 攻击百分比（0x650B50: *(this+100)=表项[2]×(-0.01)；0x650A10 累加进宿主 +1054）
    float            fCastPct            ; // +0x0068 (104) x2  va=00650A10 施法百分比（0x650B50: *(this+104)=表项[3]×(-0.01)；0x650A10 累加进宿主 +1110）
};
#pragma pack(pop)

// 统计: 字段行 8 / 语义名 8 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x006C

#endif

