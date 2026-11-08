// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 资源管理器/独立族 · 族模板还原）
// 类: CNRDParticle                           主虚表槽位数: 19  字段数: 6
// 继承: CNRDParticle（RTTI 记录无基类）（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 各证据行函数头注释（0x697B30 ssPath 映射节点 / 0x4235A0 CNGameSocket 收包派发 / 0x4D3950 键值表卸载 / 0x529D80 CNRDParticle 出生初始化 / 0x6405E0 CNRDClassChangeWindow）
// 证据主源（本类槽函数 3 个 / 同族共享）:
//   00445C10  CNRDParticleCreater__vmt18 参数块整块拷贝（98 字节）（src/game/script_string.cpp:4500）
//   00529E00  CNRDParticle__vmt48 轴偏移求值器（+67 移动类型/+43 周期）（src/game/pvp_ui.cpp:5834）
//   00529D80  CNRDParticle__vmt4 出生初始化（+152 活动位/+89 寿命门/+104 时钟）（src/game/pvp_ui.cpp:5792）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDPARTICLE
#define ARAD40JP_FIELDS_CNRDPARTICLE

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDParticle_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（见 src/cnrd/*.h / src/nengine/*）一行带过
    unsigned int     pParamBlock         ; // +0x0004 (4) x1  va=00445C10 创建参数块（0x445C10 vmt18: qmemcpy(this+4, pArg2, 0x62) 98 字节整块拷入）（类型勘误：候选表 void 系取址式误判，按 4 字节占位，同 CNMage.h +0x1FB4 法）
    unsigned char _unused_0x0008      [59]; // +0x0008..0x0042 未观测
    unsigned int     nPeriodMs           ; // +0x0043 (67) x10 va=00529E00 周期 ms（0x529E00: +67 周期积分；==1 变速段时作总时长 t）
    unsigned char    bMoveType           ; // +0x0047 (71) x2  va=00529E00 移动类型（0x529E00: 0=线性 t·v0·0.001 / 1=梯形积分 / 2=往返折返）
    unsigned char _unused_0x0048      [17]; // +0x0048..0x0058 未观测
    unsigned int     nLifetime           ; // +0x0059 (89) x3  va=00529D80 寿命上限门（0x529D80: 非 0 且 <=nArg2 时置隐藏，并挂 clock_set_countdown(this+104, +89)）
    unsigned char _unused_0x005D      [1]; // +0x005D..0x005D 未观测
    int              nScaleParam         ; // +0x005E (94) x1  va=00529D80 缩放源参数（0x529D80: *((float*)this+37) = (float)*(int*)(this+94) 缩放写入 +148）
    unsigned char _unused_0x0062      [34]; // +0x0062..0x0083 未观测
    unsigned int     nAgeTicks           ; // +0x0084 (132) x13 va=00529E00 生命周期计数（0x529E00: *(this+132) 累计时间轴，除周期算相位）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0088

#endif

