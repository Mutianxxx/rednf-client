// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 资源管理器/独立族 · 族模板还原）
// 类: CNGameSocket                           主虚表槽位数: 2   字段数: 3
// 继承: CNGameSocket -> nengine__ISocket -> nengine__IObject（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 各证据行函数头注释（0x697B30 ssPath 映射节点 / 0x4235A0 CNGameSocket 收包派发 / 0x4D3950 键值表卸载 / 0x529D80 CNRDParticle 出生初始化 / 0x6405E0 CNRDClassChangeWindow）
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   004235A0  CNGameSocket__vmt4 收包派发（nLen 日志 + 48BE70 喂分发器 + SOCKET CLOSE%d）（src/game/broadcast_debug.cpp:3246）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNGAMESOCKET
#define ARAD40JP_FIELDS_CNGAMESOCKET

#include <stdint.h>

#pragma pack(push, 1)
struct CNGameSocket_Fields {
    unsigned char _base_0x0000        [8]; // +0x0000..0x0007 继承基类段（见 src/cnrd/*.h / src/nengine/*）一行带过
    unsigned char    bWaitMode           ; // +0x0008 (8) x1  va=004235A0 等待/直读模式（0x4235A0: !=0 走 sub_698D90 取包长，否则 sub_698B50 直读）
    unsigned char _unused_0x0009      [427]; // +0x0009..0x01B3 未观测
    unsigned int     nSocketHandle       ; // +0x01B4 (436) x2  va=004235A0 socket 句柄（0x4235A0: "SOCKET CLOSE %d" 打印 *(this+436)）
    unsigned char _unused_0x01B8      [16]; // +0x01B8..0x01C7 未观测
    unsigned int     nCloseState         ; // +0x01C8 (456) x1  va=004235A0 关闭状态（0x4235A0: fld_1C8=*(this+456)；*(this+436)==0 时走关闭收尾）
};
#pragma pack(pop)

// 统计: 字段行 3 / 语义名 3 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x01CC

#endif

