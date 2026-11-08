// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNGrabbedBlastBlood                    主虚表槽位数: 30  字段数: 5
// 继承: CNGrabbedBlastBlood -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00650E80  sub_650E80 命中落位偏移（+84=±43、+88=-1、+92=max(10,110-高)）（src/nengine/zlib_inflate.cpp:938）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNGRABBEDBLASTBLOOD
#define ARAD40JP_FIELDS_CNGRABBEDBLASTBLOOD

#include <stdint.h>

#pragma pack(push, 1)
struct CNGrabbedBlastBlood_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x6  va=00650E80 宿主对象指针（0x650E80: vt+152 朝向、vt+192 高度、vt+776(3) 门控）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned int     nHitSide            ; // +0x0050 (80) x1  va=00650E80 命中侧标志（0x650E80: fld_50=*(this+80) 经宿主 vt+152 取朝向）
    unsigned int     nOffsetX            ; // +0x0054 (84) x1  va=00650E80 落位偏移 X（0x650E80: *(this+84) = 朝向 ? 43 : -43 单段偏移）
    unsigned int     nOffsetY            ; // +0x0058 (88) x1  va=00650E80 落位偏移 Y（0x650E80: *(this+88) = -1 哨兵）
    unsigned int     nOffsetZ            ; // +0x005C (92) x1  va=00650E80 落位偏移 Z（0x650E80: *(this+92) = max(10, 110-宿主高) 高度钳制）
};
#pragma pack(pop)

// 统计: 字段行 5 / 语义名 5 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0060

#endif

