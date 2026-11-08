// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNRDAuraMinion                         主虚表槽位数: 30  字段数: 6
// 继承: CNRDAuraMinion -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   0064A900  CNRDAuraMinion__vmt30 更新槽（+4 宿主匹配 + 转发 64A880）（src/game/ui/aura_create.cpp:9387）
//   0064A300  CNRDAuraMinion__vmt4C 槽（+52 状态 + 80/84/88/92 四槽判据）（src/game/ui/aura_create.cpp:8938）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDAURAMINION
#define ARAD40JP_FIELDS_CNRDAURAMINION

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDAuraMinion_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x1  va=0064A900 宿主对象指针（0x64A900: nArg2 == *(this+4) 才转 sub_64A880；IRDAppendage__vmt30 收尾）
    unsigned char _unused_0x0008      [44]; // +0x0008..0x0033 未观测
    unsigned char    bAuraState          ; // +0x0034 (52) x2  va=0064A300 光环状态字节（0x64A300: pszArg2==1 置 1；+80/+84/+88/+92 四槽齐备时置 2）
    unsigned char _unused_0x0035      [27]; // +0x0035..0x004F 未观测
    unsigned int     nAuraStage          ; // +0x0050 (80) x2  va=0064A300 光环阶段值（0x64A300: ==2 时不再走 52 分支）
    unsigned int     pFxObjA             ; // +0x0054 (84) x1  va=0064A300 特效对象 A（0x64A300: 与 +88/+92 齐备为四槽判据之一）【推断】
    unsigned int     pFxObjB             ; // +0x0058 (88) x1  va=0064A300 特效对象 B（0x64A300 四槽判据之二）【推断】
    unsigned int     pFxObjC             ; // +0x005C (92) x1  va=0064A300 特效对象 C（0x64A300 四槽判据之三；0x64CD00 构造 *(this+25) 即本槽）【推断】
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】3 / 未命名 0 / 末尾偏移 +0x0060

#endif

