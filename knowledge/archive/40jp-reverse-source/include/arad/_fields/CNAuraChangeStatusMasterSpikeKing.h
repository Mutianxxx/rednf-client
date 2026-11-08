// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNAuraChangeStatusMasterSpikeKing      主虚表槽位数: 37  字段数: 5
// 继承: CNAuraChangeStatusMasterSpikeKing -> CNAuraChangeStatusMaster -> CNRDAuraMaster -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 4 个 / 同族共享）:
//   0064A790  CNRDAuraMaster__vmt4 析构复位（vt+724 判 + 转发 64A680）（src/game/ui/aura_create.cpp:9291）
//   0064A190  CNRDAuraMaster__vmt18 生成槽（+124 件 4938F0/491D00 落位）（src/game/ui/aura_create.cpp:8826）
//   0064B540  CNAuraChangeStatusMaster__vmt78 变化生效（+128 键缓冲 + +456 计数）（src/game/ui/aura_create.cpp:10093）
//   0064B300  CNAuraChangeStatusMasterSpikeKing__vmt84（+460 + CNSpirit 转型）（src/game/ui/aura_create.cpp:9972）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNAURACHANGESTATUSMASTERSPIKEKING
#define ARAD40JP_FIELDS_CNAURACHANGESTATUSMASTERSPIKEKING

#include <stdint.h>

#pragma pack(push, 1)
struct CNAuraChangeStatusMasterSpikeKing_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x5  va=0064A790 宿主对象指针（0x64A790 族；0x64B300: nArg2 == *(this+4) 判自身）
    unsigned char _unused_0x0008      [116]; // +0x0008..0x007B 未观测
    unsigned int     pAuraAnim           ; // +0x007C (124) x2  va=0064A190 光环动画件（0x64A190: *(this+124) 非 0 且宿主 vt+940()==0 时 4938F0 播放 + 491D00 落位）
    char             szStatusKeyBuf      ; // +0x0080 (128) x2  va=0064B540 状态键缓冲（0x64B540: sub_5F8000 12 字节/条 memcmp 的 key 数组基址）
    unsigned char _unused_0x0081      [327]; // +0x0081..0x01C7 未观测
    unsigned int     pKeyVecEnd          ; // +0x01C8 (456) x2  va=0064B540 状态键向量末（0x64B540: *(this+456) count）
    unsigned char    bSpiritFlag         ; // +0x01CC (460) x1  va=0064B300 精灵魂标志（0x64B300: *(uint8_t*)(this+460)!=0 时须目标为 CNSpirit 才返 true）
};
#pragma pack(pop)

// 统计: 字段行 5 / 语义名 5 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x01CD

#endif

