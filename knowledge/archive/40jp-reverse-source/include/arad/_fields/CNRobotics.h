// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNRobotics                             主虚表槽位数: 30  字段数: 3
// 继承: CNRobotics -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   005FA680  CNRobotics__vmt4（对象列表扫描 + 4BE520 键匹配 + 5FA5D0/5FA510）（src/combat/swordman_skills.cpp:4256）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNROBOTICS
#define ARAD40JP_FIELDS_CNROBOTICS

#include <stdint.h>

#pragma pack(push, 1)
struct CNRobotics_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x4  va=005FA680 宿主对象指针（0x5FA680: vt+80 取对象列表；列表项 RTDynamicCast 到 IRDMonster 并 4C0400 过滤）
    unsigned char _unused_0x0008      [76]; // +0x0008..0x0053 未观测
    unsigned int     nTargetKey          ; // +0x0054 (84) x1  va=005FA680 目标查找键（0x5FA680: *(uint32_t*)sub_4BE520(v17,&pObj32) == *(this+84) 判命中）
    unsigned char _unused_0x0058      [4]; // +0x0058..0x005B 未观测
    unsigned int     pRoboAnim           ; // +0x005C (92) x1  va=005FA680 机器人动画件（0x5FA680: 尾段经件 vt+732 调用驱动播放）【推断】
};
#pragma pack(pop)

// 统计: 字段行 3 / 语义名 3 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x0060

#endif

