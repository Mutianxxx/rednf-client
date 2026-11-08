// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDGuildManager                       主虚表槽位数: 4   字段数: 8
// 继承: CNRDGuildManager -> CNRDBuddyManager（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   0047AAF0  CNRDGuildManager__vmtC（RTTI 自证）（src/game/login_channel.cpp:9681）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDGUILDMANAGER
#define ARAD40JP_FIELDS_CNRDGUILDMANAGER

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDGuildManager_Fields {
    unsigned char _base_0x0000        [48]; // +0x0000..0x002F 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     nGuildVecA          ; // +0x0030 (48) x1  va=0047AAF0 公会条目向量槽 A（0x47AAF0: 与 +52/+56/+60 四槽同组清零）【推断】
    unsigned int     nGuildVecB          ; // +0x0034 (52) x1  va=0047AAF0 公会条目向量槽 B（0x47AAF0 四槽清零之二）【推断】
    unsigned int     nGuildVecC          ; // +0x0038 (56) x1  va=0047AAF0 公会条目向量槽 C（0x47AAF0 四槽清零之三；条目表按 180 字节/条 sub_501490）【推断】
    unsigned int     nGuildFlagA         ; // +0x003C (60) x1  va=0047AAF0 公会标志槽 A（0x47AAF0 四槽清零之四）【推断】
    unsigned char _unused_0x0040      [13]; // +0x0040..0x004C 未观测
    unsigned char    bGuildFlagB         ; // +0x004D (77) x1  va=0047AAF0 公会标志字节 B（0x47AAF0: 清 0，与 +78 成对）【推断】
    unsigned char    bGuildFlagC         ; // +0x004E (78) x1  va=0047AAF0 公会标志字节 C（0x47AAF0: 清 0，与 +77 成对）【推断】
    unsigned char _unused_0x004F      [26]; // +0x004F..0x0068 未观测
    unsigned char    bGuildFlagD         ; // +0x0069 (105) x1  va=0047AAF0 公会标志字节 D（0x47AAF0: 清 0，与 +106 成对）【推断】
    unsigned char    bGuildFlagE         ; // +0x006A (106) x1  va=0047AAF0 公会标志字节 E（0x47AAF0: 清 0，与 +105 成对）【推断】
};
#pragma pack(pop)

// 统计: 字段行 8 / 语义名 8 / 标【推断】8 / 未命名 0 / 末尾偏移 +0x006B

#endif

