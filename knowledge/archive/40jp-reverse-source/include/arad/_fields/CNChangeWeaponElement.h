// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNChangeWeaponElement                  主虚表槽位数: 30  字段数: 5
// 继承: CNChangeWeaponElement -> CNEnchantWeapon -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   005FF170  CNEnchantWeapon__vmt20（字符串 FROST_OFF/FLAME_OFF 分派）（src/combat/swordman_skills.cpp:8074）
//   005FF860  CNEnchantWeapon__vmt4（+80 档 + +92 类型 + +104 计时）（src/combat/swordman_skills.cpp:8492）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNCHANGEWEAPONELEMENT
#define ARAD40JP_FIELDS_CNCHANGEWEAPONELEMENT

#include <stdint.h>

#pragma pack(push, 1)
struct CNChangeWeaponElement_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x2  va=005FF170 宿主对象指针（0x5FF170 同族：vt+212 播属性开关音；本类继承 CNEnchantWeapon）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned int     nElementKind        ; // +0x0050 (80) x1  va=005FF860 附魔类型（0x5FF860: *(this+80) 档位分派）
    unsigned char _unused_0x0054      [8]; // +0x0054..0x005B 未观测
    unsigned int     nElementGrade       ; // +0x005C (92) x3  va=005FF860 属性档位（0x5FF170: *(this+92) 0/1 定 FROST/FLAME）
    unsigned char _unused_0x0060      [4]; // +0x0060..0x0063 未观测
    unsigned char    bEnchantDone        ; // +0x0064 (100) x7  va=005FF860 附魔完成标志（0x5FF860: *(uint8_t*)(this+100)）
    unsigned char _unused_0x0065      [3]; // +0x0065..0x0067 未观测
    unsigned int     nTimerEnd           ; // +0x0068 (104) x1  va=005FF860 计时到期值（0x5FF860: *(this+104)）
};
#pragma pack(pop)

// 统计: 字段行 5 / 语义名 5 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x006C

#endif

