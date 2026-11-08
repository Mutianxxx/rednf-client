// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNRDWarRoomBattleTalkBox   主虚表槽位数: 4    字段数: 9
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNRDWarRoomBattleTalkBox -> CNRDCharacterTalkBox -> nengine__IAppendDraw
// 族属: 核心对象族
// 依据: ①权威 struct src/cnrd/CNRDObject.h（会话 3 逐行精修 84 槽虚表 + 全字段）与
//        src/cnrd/IRDCollisionObject.h（167 槽命中链主战场）②证据行 va 的 src 函数头注释
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDWarRoomBattleTalkBox_Fields {
    // ---- 区块 1：本段直证点（基类布局见 src/cnrd/CNRDObject.h / IRDCollisionObject.h） ----
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     nBindId4              ; // +0x0004 (4) x1  绑定 id（0x49B3F0 tick 分派门：nArg2 == *(this+4) 才继续）（证据: va=0049B3F0）
    unsigned char    bTickEnable8          ; // +0x0008 (8) x2  tick 使能字节（0x49B3F0：非 0 才驱动图层节点并走 vt+8）（证据: va=0049B3F0）
    unsigned char _unused_0x0009      [3]; // +0x0009..0x000B 未观测
    unsigned int     szText12              ; // +0x000C (12) x1  内嵌 std::string 首字节（0x49B570：sub_4015C0(this+12, 空串) 复位）（候选表 size_t 按 32 位目标 4 字节占位声明）（证据: va=0049B570）
    unsigned char _unused_0x0010      [24]; // +0x0010..0x0027 未观测
    unsigned int     nCmdId40              ; // +0x0028 (40) x1  命令/节点 id 槽（0x49B570：初始 -1 哨兵）（证据: va=0049B570）
    unsigned char _unused_0x002C      [4]; // +0x002C..0x002F 未观测
    unsigned int     pCmdVecBegin48        ; // +0x0030 (48) x4  命令节点向量 begin（0x49B570：(+52 − +48) >> 2 = 元素数，逐条释放）（证据: va=0049B570）
    unsigned int     pCmdVecEnd52          ; // +0x0034 (52) x2  命令节点向量 end（证据: va=0049B570）
    unsigned int     pCmdVecCap56          ; // +0x0038 (56) x1  命令节点向量 cap（0x49B570 清 0）（证据: va=0049B570）
    unsigned char _unused_0x003C      [13]; // +0x003C..0x0048 未观测
    unsigned char    field_0049            ; // +0x0049 (73) x1  复位清零字节（0x49B520/0x49B570 置 0；无消费点直证 → 保留占位名）（证据: va=0049B570）
    unsigned char    field_004A            ; // +0x004A (74) x1  复位清零字节（同上成对置 0；无消费点直证 → 保留占位名）（证据: va=0049B570）
};
#pragma pack(pop)

// 统计: 字段行 9 / 未命名 2 / 标【推断】0 / 末尾偏移 +0x004B
