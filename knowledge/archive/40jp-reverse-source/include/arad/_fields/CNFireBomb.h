// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNFireBomb                             主虚表槽位数: 30  字段数: 8
// 继承: CNFireBomb -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   0064D480  CNFireBomb__vmt4 复位（+152 帧数 + 128 倒计时 + 141/142）（src/game/ui/aura_create.cpp:11937）
//   0064D070  CNFireBomb__vmt14 爆炸流程（90 行：156/160/164 三动画件）（src/game/ui/aura_create.cpp:11767）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNFIREBOMB
#define ARAD40JP_FIELDS_CNFIREBOMB

#include <stdint.h>

#pragma pack(push, 1)
struct CNFireBomb_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x6  va=0064D480 宿主对象指针（0x64D480: *(this+4) 经 vt+44==273 判图类型、vt+200/vt+192 取件与高）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned int     nLifeMs             ; // +0x0050 (80) x3  va=0064D480 存活时长 ms（0x64D480: sub_698F90(this+128, *(this+80)) 倒计时时长）
    unsigned char _unused_0x0054      [57]; // +0x0054..0x008C 未观测
    unsigned char    bFadeFlagA          ; // +0x008D (141) x2  va=0064D480 淡出标志 A（0x64D480: ==273 分支清 0 后重挂倒计时）
    unsigned char    bFadeFlagB          ; // +0x008E (142) x2  va=0064D480 淡出标志 B（0x64D480 与 +141 成对清零）
    unsigned char _unused_0x008F      [9]; // +0x008F..0x0097 未观测
    unsigned int     nFrameCount         ; // +0x0098 (152) x1  va=0064D480 爆炸帧数（0x64D480: clock_now(this+128) >= *(this+152) 判到期）
    unsigned int     pBombAnimA          ; // +0x009C (156) x2  va=0064D070 爆炸动画件 A（0x64D070: sub_493A60(*(this+156), v11) + sub_4938F0 驱动）
    unsigned int     pBombAnimB          ; // +0x00A0 (160) x2  va=0064D070 爆炸动画件 B（0x64D070: *(this+160) 同流程）
    unsigned int     pBombAnimC          ; // +0x00A4 (164) x3  va=0064D070 爆炸动画件 C（0x64D070: *(this+164)；其 +170==0 时 sub_491D00 落位演播）
};
#pragma pack(pop)

// 统计: 字段行 8 / 语义名 8 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x00A8

#endif

