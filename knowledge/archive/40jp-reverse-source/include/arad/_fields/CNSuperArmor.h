// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNSuperArmor                           主虚表槽位数: 31  字段数: 2
// 继承: CNSuperArmor -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   00605D10  CNSuperArmor__vmt78 霸体躯体动画（SuperArmorBody.ani）（src/combat/passive_object.cpp:5748）
//   00605A70  CNSuperArmor__vmt54 霸体暂停级联（+80 件 + 88..92 组 4939E0）（src/combat/passive_object.cpp:5487）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNSUPERARMOR
#define ARAD40JP_FIELDS_CNSUPERARMOR

#include <stdint.h>

#pragma pack(push, 1)
struct CNSuperArmor_Fields {
    unsigned char _base_0x0000        [21]; // +0x0000..0x0014 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    char             bArmorState         ; // +0x0015 (21) x1  va=00605D10 霸体状态字节（0x605D10 vmt78: pThis+21 缓冲首字节，随霸体躯体动画 SuperArmorBody.ani 建立）【推断】
    unsigned char _unused_0x0016      [58]; // +0x0016..0x004F 未观测
    unsigned int     pArmorAnim          ; // +0x0050 (80) x1  va=00605A70 霸体动画件（0x605A70 vmt54: sub_4939E0(*(this+80), pszArg2) 暂停级联；0x605AC0 存 SuperArmorEffect.ani）
};
#pragma pack(pop)

// 统计: 字段行 2 / 语义名 2 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x0054

#endif

