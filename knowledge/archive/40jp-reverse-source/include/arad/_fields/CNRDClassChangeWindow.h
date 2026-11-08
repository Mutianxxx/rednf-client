// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDClassChangeWindow                  主虚表槽位数: 14  字段数: 1
// 继承: CNRDClassChangeWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   006405E0  CNRDClassChangeWindow__vmtC 打开主函数（223 行：4CE8A0 职业 + 47E720）（src/game/ui/aura_create.cpp:237）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDCLASSCHANGEWINDOW
#define ARAD40JP_FIELDS_CNRDCLASSCHANGEWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDClassChangeWindow_Fields {
    unsigned char _base_0x0000        [33]; // +0x0000..0x0020 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    char             bJobVecDirty        ; // +0x0021 (33) x1  va=006405E0 职业数据脏位（0x6405E0: 打开时按 4CE8A0 判定并重建职业/技能两向量（16 字节/条，+132 起三端点）；失败打 "CHARACTER CREATE FAIL"）【推断】
};
#pragma pack(pop)

// 统计: 字段行 1 / 语义名 1 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x0022

#endif

