// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 资源管理器/独立族 · 族模板还原）
// 类: CNSlangTextFilter                      主虚表槽位数: 7   字段数: 4
// 继承: CNSlangTextFilter -> ITextFilter -> IAbstractInterface（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 各证据行函数头注释（0x697B30 ssPath 映射节点 / 0x4235A0 CNGameSocket 收包派发 / 0x4D3950 键值表卸载 / 0x529D80 CNRDParticle 出生初始化 / 0x6405E0 CNRDClassChangeWindow）
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   004D3950  sub_4D3950 键值配置表卸载（+4 加载标志 + +24/+28 两表 free）（src/game/combat_core.cpp:1970）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNSLANGTEXTFILTER
#define ARAD40JP_FIELDS_CNSLANGTEXTFILTER

#include <stdint.h>

#pragma pack(push, 1)
struct CNSlangTextFilter_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（见 src/cnrd/*.h / src/nengine/*）一行带过
    unsigned char    bLoaded             ; // +0x0004 (4) x4  va=004D3950 加载标志（0x4D3950: ==0 直接返回 0；卸载成功清 0）
    unsigned char _unused_0x0005      [19]; // +0x0005..0x0017 未观测
    unsigned int     pKeyTable           ; // +0x0018 (24) x9  va=004D3950 key 表指针数组（0x4D3950: *(this+24) 逐条 free 两个 0x20 定长串）
    unsigned int     pValueTable         ; // +0x001C (28) x4  va=004D3950 value 表指针数组（0x4D3950: *(this+28) 同组 free）
    unsigned int     nEntryCount         ; // +0x0020 (32) x5  va=004D3950 条目数（0x4D3950: *(this+32) 循环上界；0x4D39F0 SJIS 匹配）
};
#pragma pack(pop)

// 统计: 字段行 4 / 语义名 4 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0024

#endif

