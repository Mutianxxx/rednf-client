// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNAimVitalPoint                        主虚表槽位数: 30  字段数: 4
// 继承: CNAimVitalPoint -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   00652300  sub_652300 激活下发（+88 播放 + 高度修正图层属性）（src/nengine/zlib_inflate.cpp:2221）
//   006522A0  sub_6522A0 扣除 tick（+80→宿主 +1278、+84→宿主 +466）（src/nengine/zlib_inflate.cpp:2196）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNAIMVITALPOINT
#define ARAD40JP_FIELDS_CNAIMVITALPOINT

#include <stdint.h>

#pragma pack(push, 1)
struct CNAimVitalPoint_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x1  va=00652300 宿主对象指针（0x652300: vt+192 取高、vt+776(3) 门控；AimedVitalPoint.ani）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    float            fAimValue           ; // +0x0050 (80) x1  va=006522A0 瞄准扣减值（0x6522A0: *(float*)(this+80) 从宿主 +1278 扣除）
    unsigned int     nAimSlot            ; // +0x0054 (84) x1  va=006522A0 瞄准槽索引（0x6522A0: *(this+84) 从宿主 +466 扣除）
    unsigned int     pAimAnim            ; // +0x0058 (88) x1  va=00652300 瞄准动画件（0x652300: sub_4938F0(*(this+88)) 驱动播放 + 图层属性下发）
};
#pragma pack(pop)

// 统计: 字段行 4 / 语义名 4 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x005C

#endif

