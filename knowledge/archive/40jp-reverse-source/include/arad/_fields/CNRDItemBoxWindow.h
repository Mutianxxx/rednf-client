// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDItemBoxWindow                      主虚表槽位数: 15  字段数: 9
// 继承: CNRDItemBoxWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   0063B4D0  CNRDItemBoxWindow__vmt8 Update（111 行：CLICK_BUTTON2 + 56/60/64 三按钮）（src/game/ui/window_party.cpp:9269）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDITEMBOXWINDOW
#define ARAD40JP_FIELDS_CNRDITEMBOXWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDItemBoxWindow_Fields {
    unsigned char _base_0x0000        [8]; // +0x0000..0x0007 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pHostCtrl           ; // +0x0008 (8) x3  va=0063B4D0 宿主控件（0x63B4D0: fld_8=*(this+8)；sub_69A500(fld_8)==1 且其 +2504==2 时触发本窗动作）
    unsigned char _unused_0x000C      [4]; // +0x000C..0x000F 未观测
    unsigned int     pOwnerWnd           ; // +0x0010 (16) x2  va=0063B4D0 宿主窗口指针（0x63B4D0: *(*(this+16)+2504) 取模式号 ==14/2 判本窗职责）【推断】
    unsigned char _unused_0x0014      [16]; // +0x0014..0x0023 未观测
    unsigned int     nSelItemSlot        ; // +0x0024 (36) x4  va=0063B4D0 选中物品槽 id（0x63B4D0: fld_24=*(this+36)；0→帧 15、1→帧 0xE 换算图标）
    unsigned int     uActive             ; // +0x0028 (40) x3  va=0063B4D0 激活标志（0x63B4D0: *(this+40)==1 且 clock_now(this+68)>=1000 才走 63B280 校验并置 2）
    unsigned char _unused_0x002C      [4]; // +0x002C..0x002F 未观测
    unsigned int     nSubState           ; // +0x0030 (48) x7  va=0063B4D0 子状态/校验结果（0x63B4D0: 由 63B280 返回 1 置 2；非 1 则直接关窗）
    unsigned int     pPendingItem        ; // +0x0034 (52) x2  va=0063B4D0 待处理物品（0x63B4D0: *(this+48) 非 0 时跳过拾取段直接收尾）
    unsigned int     pBtnAction          ; // +0x0038 (56) x2  va=0063B4D0 主操作按钮（0x63B4D0: fld_38=*(this+56)；其 +17 命中且 +12==dword_79BE34 → CLICK_BUTTON2）
    unsigned int     pBtnConfirm         ; // +0x003C (60) x3  va=0063B4D0 确认按钮（0x63B4D0: fld_3C=*(this+60) 命中 → CLICK_BUTTON2 + 0x39 号命令）
    unsigned int     pBtnCancel          ; // +0x0040 (64) x4  va=0063B4D0 取消按钮（0x63B4D0: fld_40=*(this+64) 命中 → CLICK_BUTTON2 + 0x39 号命令）
};
#pragma pack(pop)

// 统计: 字段行 9 / 语义名 9 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x0044

#endif

