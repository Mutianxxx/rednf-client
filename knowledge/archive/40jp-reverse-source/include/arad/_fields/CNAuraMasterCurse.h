// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNAuraMasterCurse                      主虚表槽位数: 37  字段数: 6
// 继承: CNAuraMasterCurse -> CNRDAuraMaster -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   006499A0  CNAuraMasterCurse__vmt4 复位（+128 诅咒件 + 153/154 + 164 周期）（src/game/ui/aura_create.cpp:8379）
//   0064A190  CNRDAuraMaster__vmt18 生成槽（+124 件 4938F0/491D00 落位）（src/game/ui/aura_create.cpp:8826）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNAURAMASTERCURSE
#define ARAD40JP_FIELDS_CNAURAMASTERCURSE

#include <stdint.h>

#pragma pack(push, 1)
struct CNAuraMasterCurse_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x3  va=006499A0 宿主对象指针（0x6499A0: vt+940 判、vt+340 图类型）
    unsigned char _unused_0x0008      [116]; // +0x0008..0x007B 未观测
    unsigned int     pAuraAnim           ; // +0x007C (124) x2  va=0064A190 光环动画件（0x64A190: *(this+124) 非 0 且宿主 vt+940()==0 时 4938F0 播放 + 491D00 落位）
    unsigned int     pCurseAnim          ; // +0x0080 (128) x8  va=006499A0 诅咒动画件（0x6499A0: *(this+128) 经 vt+12/vt+112 复位 + 宿主坐标合成落位）
    unsigned char _unused_0x0084      [21]; // +0x0084..0x0098 未观测
    unsigned char    bCastFlagA          ; // +0x0099 (153) x1  va=006499A0 施放标志 A（0x6499A0: 与 +154 成对清 0，随 +164 到期重挂 125ms 倒计时）
    unsigned char    bCastFlagB          ; // +0x009A (154) x1  va=006499A0 施放标志 B（0x6499A0 与 +153 成对清 0）
    unsigned char _unused_0x009B      [9]; // +0x009B..0x00A3 未观测
    unsigned int     nNextTickMs         ; // +0x00A4 (164) x1  va=006499A0 下个周期时刻 ms（0x6499A0: clock_now(this+140) >= *(this+164) 判到期重挂）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x00A8

#endif

