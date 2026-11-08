// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNEnchantActiveStatus                  主虚表槽位数: 31  字段数: 6
// 继承: CNEnchantActiveStatus -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   005E5C90  CNEnchantActiveStatus__vmt78（叶子：6 参字段直写）（src/combat/fighter_skills.cpp:1700）
//   006507C0  sub_6507C0 暂停解除刷新（+93 使能 + 108..112 逐件闪烁）（src/nengine/zlib_inflate.cpp:558）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNENCHANTACTIVESTATUS
#define ARAD40JP_FIELDS_CNENCHANTACTIVESTATUS

#include <stdint.h>

#pragma pack(push, 1)
struct CNEnchantActiveStatus_Fields {
    unsigned char _base_0x0000        [44]; // +0x0000..0x002B 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     nTimerParam         ; // +0x002C (44) x1  va=005E5C90 计时参数（0x5E5C90 vmt78: *(this+44)=nArg6）
    unsigned char _unused_0x0030      [32]; // +0x0030..0x004F 未观测
    unsigned int     nStatusId           ; // +0x0050 (80) x1  va=005E5C90 状态 id（0x5E5C90: *(this+80)=nArg2）
    float            fStatusValue        ; // +0x0054 (84) x1  va=005E5C90 状态数值（0x5E5C90: *(float*)(this+84)=(float)nArg3）
    unsigned int     nStatusDur          ; // +0x0058 (88) x1  va=005E5C90 状态时长（0x5E5C90: *(this+88)=nArg4）
    unsigned char    bStatusFlag         ; // +0x005C (92) x1  va=005E5C90 状态标志（0x5E5C90: *(uint8_t*)(this+92)=pszArg5）
    unsigned char    bEnableFlag         ; // +0x005D (93) x2  va=006507C0 使能/暂停标志（0x6507C0: pszArg2==0 且 *(uint8_t*)(this+93)!=0 才重扫挂接表并逐件闪烁）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x005E

#endif

