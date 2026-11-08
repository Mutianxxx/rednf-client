// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNSummonMonsterAura                    主虚表槽位数: 38  字段数: 3
// 继承: CNSummonMonsterAura -> CNRDAuraMaster -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   0064A790  CNRDAuraMaster__vmt4 析构复位（vt+724 判 + 转发 64A680）（src/game/ui/aura_create.cpp:9291）
//   0064A570  CNRDAuraMaster__vmt1C 生成装配（+80 标志组 + 92 计时 + 64A3D0）（src/game/ui/aura_create.cpp:9137）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNSUMMONMONSTERAURA
#define ARAD40JP_FIELDS_CNSUMMONMONSTERAURA

#include <stdint.h>

#pragma pack(push, 1)
struct CNSummonMonsterAura_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x2  va=0064A790 宿主对象指针（光环族通用：证据行经 *(this+4) 调宿主 vt+308/340/672/776 等做目标判定与状态写入）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned int     nAuraFlags          ; // +0x0050 (80) x2  va=0064A570 光环标志组（0x64A570: >>5 与 &0x20 判 64A3D0 召唤装配）
    unsigned char _unused_0x0054      [8]; // +0x0054..0x005B 未观测
    unsigned char    bTimerStruct        ; // +0x005C (92) x1  va=0064A570 计时结构（0x64A570: sub_607290(this+92, clock_now(this+8)) 首帧基准）
};
#pragma pack(pop)

// 统计: 字段行 3 / 语义名 3 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x005D

#endif

