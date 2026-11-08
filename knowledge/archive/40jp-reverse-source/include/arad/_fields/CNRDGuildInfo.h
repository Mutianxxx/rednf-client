// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDGuildInfo                          主虚表槽位数: 4   字段数: 5
// 继承: CNRDGuildInfo -> HttpFileCallBack（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   004BEA70  sub_4BEA70 纹章下载完成回调 on_complete（状态 2→4/6）（src/game/equ_buff.cpp:12718）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDGUILDINFO
#define ARAD40JP_FIELDS_CNRDGUILDINFO

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDGuildInfo_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     nLoadState          ; // +0x0004 (4) x3  va=004BEA70 纹章下载状态（0x4BEA70: ==2 处理完成；置 6 失败（串短/后缀不符）、置 4 成功）
    unsigned int     nGuildId            ; // +0x0008 (8) x1  va=004BEA70 公会 id（0x4BEA70: 日志 "guild = %d" 第二参）
    unsigned char _unused_0x000C      [49]; // +0x000C..0x003C 未观测
    unsigned char    bReadyFlagA         ; // +0x003D (61) x1  va=004BEA70 就绪标志 A（0x4BEA70: 纹章通过时清 0）
    unsigned char    bReadyFlagB         ; // +0x003E (62) x1  va=004BEA70 就绪标志 B（0x4BEA70: 与 +61 成对清 0）
    unsigned char _unused_0x003F      [13]; // +0x003F..0x004B 未观测
    size_t           szEmblemPath        ; // +0x004C (76) x1  va=004BEA70 纹章路径串（0x4BEA70: +76 存下载文件名，sub_4015C0 std::string 赋值）
};
#pragma pack(pop)

// 统计: 字段行 5 / 语义名 5 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0050

#endif

