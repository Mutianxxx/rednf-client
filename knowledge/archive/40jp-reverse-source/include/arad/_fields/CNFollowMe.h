// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNFollowMe                             主虚表槽位数: 30  字段数: 5
// 继承: CNFollowMe -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   0064DA00  CNFollowMe__vmtC 打开槽（+80 目标 + 88/92 速度加值 + 108 标志）（src/game/ui/aura_create.cpp:12212）
//   0064DAF0  CNFollowMe__vmt14 生成槽（+116 双动画件按 +170 状态二选一）（src/game/ui/aura_create.cpp:12264）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNFOLLOWME
#define ARAD40JP_FIELDS_CNFOLLOWME

#include <stdint.h>

#pragma pack(push, 1)
struct CNFollowMe_Fields {
    unsigned char _base_0x0000        [80]; // +0x0000..0x004F 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pFollowTarget       ; // +0x0050 (80) x5  va=0064DA00 跟随目标对象（0x64DA00: *(this+80) 经 vt+1032 取 +16 目标；vt+8 距离、sub_4D8FE0 半径比较）
    unsigned char _unused_0x0054      [4]; // +0x0054..0x0057 未观测
    float            fSpeedAddX          ; // +0x0058 (88) x1  va=0064DA00 X 速度加值（0x64DA00: sub_41A590(pArg2+830, +88) 累加）
    float            fSpeedAddY          ; // +0x005C (92) x1  va=0064DA00 Y 速度加值（0x64DA00: sub_41A590(pArg2+858, +92) 累加）
    unsigned char _unused_0x0060      [12]; // +0x0060..0x006B 未观测
    unsigned int     nFollowFlag         ; // +0x006C (108) x1  va=0064DA00 跟随标志（0x64DA00: *(this+108)!=0 才做速度累加）
    unsigned char _unused_0x0070      [4]; // +0x0070..0x0073 未观测
    unsigned int     pFollowAnim         ; // +0x0074 (116) x1  va=0064DAF0 跟随动画件（0x64DAF0: *(this+4*(*(uint8_t*)(*(this+116)+170)!=0)+116) 按 +170 状态二选一）
};
#pragma pack(pop)

// 统计: 字段行 5 / 语义名 5 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0078

#endif

