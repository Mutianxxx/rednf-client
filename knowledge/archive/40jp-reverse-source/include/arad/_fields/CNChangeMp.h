// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNChangeMp                             主虚表槽位数: 30  字段数: 6
// 继承: CNChangeMp -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00602200  CNChangeMp__vmt4 MP 恢复激活（MP_RECOVERED + 4049C0 插值）（src/combat/passive_object.cpp:2101）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNCHANGEMP
#define ARAD40JP_FIELDS_CNCHANGEMP

#include <stdint.h>

#pragma pack(push, 1)
struct CNChangeMp_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x4  va=00602200 宿主对象指针（0x602200: *(this+4) 经 vt+752/vt+744 直接加减 MP；本人/他人两路径）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned int     nTotalMs            ; // +0x0050 (80) x2  va=00602200 总时长 ms（0x602200: sub_4049C0(0.0, *(this+80), now, *(this+84)) 插值终点）
    unsigned int     nDurationMs         ; // +0x0054 (84) x1  va=00602200 持续时长 ms（0x602200: 插值第四参；0x602380 出生装配用之挂 MpUp.ani 倒计时）
    unsigned int     nCurValue           ; // +0x0058 (88) x3  va=00602200 当前递增进度（0x602200: *(this+88)=v4；与 +80 相等且件耗尽时 vt+76(0) 收尾）
    unsigned int     pMpFxObj            ; // +0x005C (92) x3  va=00602200 MP 表现对象（0x602200: *(this+92) 非 0 且其 +148>=4 时播 "MP_RECOVERED"）
    unsigned char    bPlayedOnce         ; // +0x0060 (96) x2  va=00602200 播报一次标志（0x602200: *(uint8_t*)(this+96)==0 → 置 1 并播 MP_RECOVERED）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0061

#endif

