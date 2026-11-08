// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDSkillBuyWindow       主虚表槽位数: 14   字段数: 7
// 继承: CNRDSkillBuyWindow -> IRDWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 14 个）:
//   +0  0x550620 绘制（136 行：491530/491630 批次 + 418DD0 精灵 + 47EB10/5013F0/501420 技能数据）
//   +8  0x550480 __vmt8 Update（99 行：鼠标悬停格子高亮 44E8D0 消息 0x12 + CLICK_BUTTON2 翻页音
//       + 69C680/69C690 滚动；fld_14 = 16 * (*(*(this+20)+104) + 4) 格行换算）
//   +12 0x550960 打开槽（RECIPE_NOTICE 配方提示事件 43BEE0/432EA0 + 69C980/69A5F0 + 44BBA0）
//   +16 0x550420 状态切换槽（对象状态 17→18；dword_9B88CC/dword_795374 购买上下文）
//   +28 0x550B00 刷新槽（47F7D0 + 44ACC0/47DE90/47EB10/5013F0/501420 技能数据）
//   +4  0x44DD30 删除析构壳；+44 0x540360 IRDWindow__vmt2C 页签（44AB50(this+8,this+12,12)）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDSKILLBUYWINDOW
#define ARAD40JP_FIELDS_CNRDSKILLBUYWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDSkillBuyWindow_Fields {
    // ---- 区块: 控件族（技能格/滚动/宿主窗；0x550480） ----
    unsigned char _base_0x0000[4]; // +0x0000..0x0003 继承段（CNRDSkillBuyWindow -> IRDWindow -> nengine::IAppendDraw）一行带过
    uint32_t         pOwnerWnd           ; // +0x0004 (4) x3  va=00550480 ★ 宿主/父窗口（0x550480: *(*(this+4)+20)+24 / *(*(this+4)+24)+39*v11+46 定位技能格）
    uint32_t         pHostCtrl           ; // +0x0008 (8) x1  va=00550480 ★ 宿主控件（0x550480: *(*(this+8)+2504) 取子页号）
    uint32_t         nTabIndex           ; // +0x000C (12) x1  va=00540360 ★ 页签索引（vmt2C 0x540360: 44AB50(this+8, this+12, 12)）
    unsigned char _unused_0010[4]; // +0x0010..0x0013 未观测
    uint32_t         pItemSlotCtx        ; // +0x0014 (20) x3  va=00550480 ★ 物品槽上下文（0x550480: 其 +108 激活位 !=0 才换算格子 fld_14 = 16*(+104 + 4)）
    unsigned char _unused_0018[32]; // +0x0018..0x0037 未观测
    uint32_t         pSkillListCtrl      ; // +0x0038 (56) x2  va=00550480 ★ 技能列表控件（0x550480: fld_38 = sub_69C690(*(this+56)) 滚动行）
    uint32_t         field_003C          ; // +0x003C (60) x1  va=00550480 0x550480 读取槽（滚动态字段，语义未定）
    // ---- 区块: 状态机族（购买上下文；0x550480） ----
    unsigned char _unused_0040[260]; // +0x0040..0x0143 未观测
    uint32_t         nBuyCtxId           ; // +0x0144 (324) x3  va=00550480 ★ 购买上下文 id（0x550480: dword_9B88CC != pThis_44 或 dword_795374 != *(this+324) 判定上下文切换）
};
#pragma pack(pop)

// 统计: 字段行 7 / 语义名 6 / 标【推断】0 / 未命名 1 / 末尾偏移 +0x0148

#endif
