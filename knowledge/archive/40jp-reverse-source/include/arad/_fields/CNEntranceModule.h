// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNEntranceModule         主虚表槽位数: 5   字段数: 25
// 继承: CNEntranceModule -> nengine::IModule -> nengine::IObject -> nengine::IAppendDraw（基类段见 src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 5 个）:
//   +4  0x46C300 CNEntranceModule__vmt4 选角界面帧（src/game/ui_icon_perf.cpp:9703）
//       退出确认(vt+20(10)/vt+16(84)) / sub_46BD70 键盘导航(SELECT_CHARACTER/CLICK_BUTTON4)
//       / 一次性 M_CHARACTER_SELECT(+50) / UDP 上报(+48→+49) / 角色按钮(CLICK_BUTTON2)
//       角色条目 144 字节/条于 this+80 / 名字输入框(CLICK_BUTTON2→Enter 提交)
//   +0  0x41ECB0 删除析构；+8/+12/+16 = 基类退出 / DllMain 桩 / nullsub
// ============================================================
#ifndef ARAD40JP_FIELDS_CNENTRANCEMODULE
#define ARAD40JP_FIELDS_CNENTRANCEMODULE

#include <stdint.h>

#pragma pack(push, 1)
struct CNEntranceModule_Fields {
    // ---- 区块: 状态机族（选中/使能/一次性门；0x46C300） ----
    unsigned char _base_0x0000[44]; // +0x0000..0x002B 继承段（CNEntranceModule -> nengine::IModule -> nengine::IObject -> nengine::IAppendDraw）一行带过
    uint32_t         nSelectedChar       ; // +0x002C (44) x2  va=0046C300 ★ 角色选中锁存（0x46C300: *(this+44)=1 进入「已选」分支；==1 时走角色板/滚动段）
    uint8_t          bUdpReportOn        ; // +0x0030 (48) x1  va=0046C300 UDP 上报使能位（0x46C300: *(this+48)!=0 且 +49==0 → sub_45DDA0(dword_8F8524,1)）
    uint8_t          bUdpReported        ; // +0x0031 (49) x2  va=0046C300 ★ UDP 已上报标志（0x46C300: 上报后 *(this+49)=1 防重复）
    uint8_t          bCharSelSent        ; // +0x0032 (50) x2  va=0046C300 ★ M_CHARACTER_SELECT 一次性发送标志（0x46C300: ==0 → sub_432EA0 发事件后置 1）
    // ---- 区块: 控件族（角色按钮/滚动/输入框；0x46C300） ----
    unsigned char _unused_0033[1]; // +0x0033..0x0033 未观测
    uint32_t         pCharCardBoard      ; // +0x0034 (52) x3  va=0046C300 ★ 角色选中板（0x46C300: 其 +16 置 0 取消高亮）
    uint8_t          bInputEnable        ; // +0x0038 (56) x6  va=0046C300 ★ 键盘输入使能（0x46C300: *(this+56)!=0 才允许 sub_46BD70 键盘导航与全部按钮响应）
    // ---- 区块: 数据缓冲族（角色条目数组） ----
    unsigned char _unused_0039[7]; // +0x0039..0x003F 未观测
    uint32_t         pCharEntryVecBegin  ; // +0x0040 (64) x4  va=0046C300 ★ 角色条目数组 begin（0x46C300: (*(this+68)-*(this+64))>>2 >= 8 → 已满 8 角色）
    uint32_t         nCharCount          ; // +0x0044 (68) x4  va=0046C300 ★ 角色数（begin/end 差 >>2；>=8 时提示「角色已满」）
    unsigned char _unused_0048[8]; // +0x0048..0x004F 未观测
    uint32_t         pCharEntryArray     ; // +0x0050 (80) x1  va=0046C300 ★ 角色条目数组基址（0x46C300: *(this+80) + 144*nSelChar，144 字节/条）
    unsigned char _unused_0054[8]; // +0x0054..0x005B 未观测
    uint32_t         nCurChar            ; // +0x005C (92) x6  va=0046C300 ★ 当前选中角色下标（0x46C300: ==-1 未选；44E8D0(0x1E) 名字板定位）
    unsigned char _unused_0060[8]; // +0x0060..0x0067 未观测
    uint32_t         pBtnCharBoard       ; // +0x0068 (104) x1  va=0046C300 ★ 角色选中板按钮（0x46C300: fld_68=+104 命中 → +44 锁存 1、清选中板 +16、置 +176 高亮、sub_46BA60(切页)+44E850(30)）
    uint32_t         pBtnCharName        ; // +0x006C (108) x2  va=0046C300 ★ 角色名板按钮（0x46C300: fld_6C=+108 命中且当前角色 != -1 → 44E8D0(0x1E) 弹角色名说明 + CLICK_BUTTON2）
    uint32_t         pBtnCharCancel      ; // +0x0070 (112) x2  va=0046C300 ★ 取消选中按钮（0x46C300: fld_70=+112 命中且当前角色 != -1 → sub_46BCB0(清除选中) + CLICK_BUTTON4）
    uint32_t         pBtnBack            ; // +0x0074 (116) x1  va=0046C300 ★ 返回按钮（0x46C300: fld_74=+116 命中 → sub_41C860 退出确认 + CLICK_BUTTON3，并直接 return）
    // ---- 区块: 计时族（进入门时间戳；0x46C300） ----
    unsigned char _unused_0078[52]; // +0x0078..0x00AB 未观测
    uint32_t         nEnterTimeGate      ; // +0x00AC (172) x4  va=0046C300 ★ 进入门时间戳（0x46C300: ==-1 或 clock_now(this+16) > 该值+300 才响应 SELECT_CHARACTER）
    uint32_t         pEnterBtnLight      ; // +0x00B0 (176) x2  va=0046C300 进入按钮高亮（0x46C300: 其 +16 置 1/0 切换）
    uint32_t         pBtnCreateChar      ; // +0x00B4 (180) x3  va=0046C300 创建角色按钮（0x46C300: 命中 → sub_46BA60 切换创建面板）
    unsigned char _unused_00B8[52]; // +0x00B8..0x00EB 未观测
    uint32_t         pBtnScrollUp        ; // +0x00EC (236) x1  va=0046C300 上滚按钮（0x46C300: "SCROLL_ARROW" → sub_69C400(当前-1)）
    uint32_t         pBtnScrollDown      ; // +0x00F0 (240) x1  va=0046C300 下滚按钮（0x46C300: "SCROLL_ARROW" → sub_69C400(当前+1)）
    uint32_t         pScrollCtrl         ; // +0x00F4 (244) x6  va=0046C300 滚动条控件（0x46C300: sub_69C380/69C3A0/69C500 取值/步长/上限）
    uint32_t         pBtnNameEdit        ; // +0x00F8 (248) x1  va=0046C300 ★ 名字编辑按钮（0x46C300: 命中且角色数<8 → sub_422E70(140) 提示串）
    uint32_t         pNameEditBox        ; // +0x00FC (252) x4  va=0046C300 ★ 名字输入框（0x46C300: 其 +16 可见位；置 1 后 sub_69BCC0 聚焦 + dword_79BE4C）
    uint32_t         pNameEditCtrl       ; // +0x0100 (256) x7  va=0046C300 ★ 名字输入控件（0x46C300: sub_69B740 取串 → 校验 → 发 5 号包 + "Character Name send"）
    uint32_t         pBtnExitA           ; // +0x0104 (260) x1  va=0046C300 退出按钮 A（0x46C300: 命中 → sub_41C860）
    uint32_t         pBtnExitB           ; // +0x0108 (264) x1  va=0046C300 退出按钮 B（与 +260 成组的退出/辅助按钮槽）【推断】
};
#pragma pack(pop)

// 统计: 字段行 25 / 语义名 24 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x010C

#endif
