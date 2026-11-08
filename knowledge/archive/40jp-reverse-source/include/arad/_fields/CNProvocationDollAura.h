// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNProvocationDollAura                  主虚表槽位数: 38  字段数: 1
// 继承: CNProvocationDollAura -> CNRDAuraMaster -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   0064A790  CNRDAuraMaster__vmt4 析构复位（vt+724 判 + 转发 64A680）（src/game/ui/aura_create.cpp:9291）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNPROVOCATIONDOLLAURA
#define ARAD40JP_FIELDS_CNPROVOCATIONDOLLAURA

#include <stdint.h>

#pragma pack(push, 1)
struct CNProvocationDollAura_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x1  va=0064A790 宿主对象指针（0x64A790: vt+724 判后解除；vmt1C 0x64A960 经 4926A0/4922F0 嘲讽目标）
};
#pragma pack(pop)

// 统计: 字段行 1 / 语义名 1 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0008

#endif

