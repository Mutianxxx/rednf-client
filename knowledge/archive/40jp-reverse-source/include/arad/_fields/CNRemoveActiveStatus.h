// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNRemoveActiveStatus                   主虚表槽位数: 30  字段数: 2
// 继承: CNRemoveActiveStatus -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00651B10  sub_651B10 清 +80 标志并复位 +100 挂接件（src/nengine/zlib_inflate.cpp:1708）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNREMOVEACTIVESTATUS
#define ARAD40JP_FIELDS_CNREMOVEACTIVESTATUS

#include <stdint.h>

#pragma pack(push, 1)
struct CNRemoveActiveStatus_Fields {
    unsigned char _base_0x0000        [80]; // +0x0000..0x004F 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned char    bActiveFlag         ; // +0x0050 (80) x1  va=00651B10 解除激活标志（0x651B10: *(uint8_t*)(this+80)=0 清）
    unsigned char _unused_0x0051      [19]; // +0x0051..0x0063 未观测
    unsigned int     pAttachObj          ; // +0x0064 (100) x1  va=00651B10 挂接对象（0x651B10: *(this+100) 非空调其 vt+12(0) 解除）
};
#pragma pack(pop)

// 统计: 字段行 2 / 语义名 2 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0068

#endif

