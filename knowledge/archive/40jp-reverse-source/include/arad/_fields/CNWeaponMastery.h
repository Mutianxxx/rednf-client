// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNWeaponMastery                        主虚表槽位数: 30  字段数: 9
// 继承: CNWeaponMastery -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   005F9CA0  CNWeaponMastery__vmt8（攻击属性面 +96/+100/+104 写入）（src/combat/swordman_skills.cpp:3705）
//   005F9B40  CNWeaponMastery__vmtC（+858/+1292/+1208 三槽累加）（src/combat/swordman_skills.cpp:3634）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNWEAPONMASTERY
#define ARAD40JP_FIELDS_CNWEAPONMASTERY

#include <stdint.h>

#pragma pack(push, 1)
struct CNWeaponMastery_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x2  va=005F9CA0 宿主对象指针（0x5F9CA0/0x5F9B40: RTDynamicCast(*(this+4) → IRDCharacter) 后取 vt+792(8)/vt+1096）
    unsigned char _unused_0x0008      [80]; // +0x0008..0x0057 未观测
    unsigned int     nCharCtx            ; // +0x0058 (88) x1  va=005F9CA0 角色上下文槽（0x5F9CA0: v13 != *(this+88) 判变更后才写属性面）【推断】
    unsigned char _unused_0x005C      [4]; // +0x005C..0x005F 未观测
    unsigned int     nAtkType            ; // +0x0060 (96) x3  va=005F9CA0 攻击属性类型（0x5F9CA0: *(this+96)!=17 时写 pArg2 属性面；17 为无效哨兵）
    unsigned int     nAtkValue           ; // +0x0064 (100) x2  va=005F9CA0 攻击属性值（0x5F9CA0: 写 pArg2+4*v9+36；同类已存在时累加）
    unsigned int     nAtkDur             ; // +0x0068 (104) x2  va=005F9CA0 攻击属性时长（0x5F9CA0: fld_68=*(this+104) 写入属性面第三天）
    float            fAtkBonus           ; // +0x006C (108) x2  va=005F9B40 攻击加值 1（0x5F9B40: sub_41A590(pArg2+858, +108) 累加）
    float            fAtkBonus2          ; // +0x0070 (112) x1  va=005F9B40 攻击加值 2（0x5F9B40: 累加进 pArg2+1292）
    float            fAtkBonus3          ; // +0x0074 (116) x1  va=005F9CA0 攻击加值 3（0x5F9CA0: *(float*)(pArg2+136) = *(float*)(this+116) × 宿主系数）
    float            fSpecRate           ; // +0x0078 (120) x2  va=005F9B40 特殊/暴击率（0x5F9B40: *(this+120)!=0.0 时 sub_4AED60(*(this+120)) 触发）
};
#pragma pack(pop)

// 统计: 字段行 9 / 语义名 9 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x007C

#endif

