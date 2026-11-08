// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 资源管理器/独立族 · 族模板还原）
// 类: CNAnimationLoader                      主虚表槽位数: 14  字段数: 4
// 继承: CNAnimationLoader -> IFileResourceManager（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 各证据行函数头注释（0x697B30 ssPath 映射节点 / 0x4235A0 CNGameSocket 收包派发 / 0x4D3950 键值表卸载 / 0x529D80 CNRDParticle 出生初始化 / 0x6405E0 CNRDClassChangeWindow）
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00697B30  sub_697B30 映射节点构造（+8 SSO 路径 + 尾补 \ + 264 值）（src/platform/socket_ime.cpp:3717）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNANIMATIONLOADER
#define ARAD40JP_FIELDS_CNANIMATIONLOADER

#include <stdint.h>

#pragma pack(push, 1)
struct CNAnimationLoader_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（见 src/cnrd/*.h / src/nengine/*）一行带过
    unsigned int     nResKey             ; // +0x0004 (4) x1  va=00697B30 资源键/序号（0x697B30 映射节点构造: *(this+4)=nArg2）
    unsigned short   uPathTerm           ; // +0x0007 (7) x1  va=00697B30 路径尾终止位（0x697B30: +7+len 处补 \）【推断】；与上一宽槽（结束于 +0x0007）字节级重叠，两行均直证
    char             szAnimPath          ; // +0x0008 (8) x1  va=00697B30 动画路径串（0x697B30: strcpy(this+8, pArg3)）；与上一宽槽（结束于 +0x0008）字节级重叠，两行均直证
    unsigned char _unused_0x0009      [255]; // +0x0009..0x0107 未观测
    unsigned int     nAnimHandle         ; // +0x0108 (264) x2  va=00697B30 动画句柄（0x697B30: *(this+264)=nArg4）
};
#pragma pack(pop)

// 统计: 字段行 4 / 语义名 4 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x010C

#endif

