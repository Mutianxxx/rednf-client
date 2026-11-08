// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDMakePriceWindow      主虚表槽位数: 9   字段数: 20
// 继承: CNRDMakePriceWindow -> nengine::CNFrame -> nengine::IControl -> nengine::IObject（基类段见 src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 9 个）:
//   +0  0x44C910 删除析构壳（44C940 挂虚表 + 5449D0 + 43C2E0）
//   +8  0x69C710 nengine 图片框 dtor（+104=0 / +4=0 / +8=3）
//   +16 0x69A520 nengine CNUIObject 构造（字段清零；+16/+17 可见与激活置 1；
//       +12 = dword_9D3BCC++ 全局控件 id 分配器；+64=1；sub_6569D0(+92)）
//   +24 0x544E20 CNRDMakePriceWindow__vmt18 定价确认槽（转发 544D10）
//   +28 0x69DE30 nengine 标签 Render（可见 +16 且 +104 图非空 → vt+152 绘制于 +20/+24）
//   +32 0x69C6C0 nengine 图片框 SetTexture（句柄 → +104；宽高取句柄 +36/+40 到 +28/+32）
//   字段语义即 nengine::CNUIObject/IControl 基类布局（src/platform/socket_ime.cpp:5060+ 逐槽直证）。
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDMAKEPRICEWINDOW
#define ARAD40JP_FIELDS_CNRDMAKEPRICEWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDMakePriceWindow_Fields {
    // ---- 区块: 控件族（可见/类型/id/纹理；0x69A520 / 0x69C6C0 / 0x69DE30） ----
    unsigned char _base_0x0000[4]; // +0x0000..0x0003 继承段（CNRDMakePriceWindow -> nengine::CNFrame -> nengine::IControl -> nengine::IObject）一行带过
    uint8_t          bInited             ; // +0x0004 (4) x3  va=0069C710 ★ 初始化完成标志（0x69C6C0 SetTexture: !=0 拒绝二次设置；0x69C710 图片框 dtor 清 0）
    unsigned char _unused_0005[3]; // +0x0005..0x0007 未观测
    uint32_t         nCtrlType           ; // +0x0008 (8) x2  va=0069C710 ★ 控件类型号（ctor 直证: 9 文本列表 / 3 图片框 / 1 按钮 / 5 滑条 / 7 标签页 / 6 图片组 / 2 标签；0x69C710 图片框置 3）
    uint32_t         nCtrlId             ; // +0x000C (12) x1  va=0069A520 ★ 控件 id（0x69A520: = dword_9D3BCC++ 全局控件 id 分配器；命中比较用）
    uint8_t          bVisible            ; // +0x0010 (16) x2  va=0069A520 ★ 可见标志（0x69A520 = 1；0x69DE30 标签 Render 门；子项递归门）
    uint8_t          bEnable             ; // +0x0011 (17) x1  va=0069A520 ★ 激活/可命中标志（0x69A520 = 1；IsMouseOver/HitTest/DragWindow 均判 +17）
    uint8_t          bDragChild          ; // +0x0012 (18) x1  va=0069A520 ★ 子项可拖动标志（0x69A520 = 0；Render 递归中 +17 && +18 才调 DragWindow）
    // ---- 区块: 状态机族（拖动/层级/构造装配位） ----
    unsigned char _unused_0013[1]; // +0x0013..0x0013 未观测
    uint32_t         nPosX               ; // +0x0014 (20) x1  va=0069A520 ★ 窗口位置 X（HitTest 命中矩形 +20/+24/+28/+32；DragWindow: pt.x - *(this+20)；MoveWindow 写 +5）
    uint32_t         nPosY               ; // +0x0018 (24) x1  va=0069A520 ★ 窗口位置 Y（同上；DragWindow: pt.y - *(this+24)）
    uint32_t         nWidth              ; // +0x001C (28) x2  va=0069A520 ★ 窗口宽（0x69C6C0 SetTexture: 句柄 +36 写入；HitTest 矩形）
    uint32_t         nHeight             ; // +0x0020 (32) x2  va=0069A520 ★ 窗口高（0x69C6C0 SetTexture: 句柄 +40 写入；HitTest 矩形）
    // ---- 区块: 数据缓冲族（位置缓存/抓取点/纹理矩形；0x69A5F0 / 0x69A650 / 0x69A6E0） ----
    uint32_t         nOldPosX            ; // +0x0024 (36) x1  va=0069A520 ★ 移动前旧 X（0x69A5F0 MoveWindow: *(this+9) = 旧 +5，供子项相对补偿）
    uint32_t         nOldPosY            ; // +0x0028 (40) x1  va=0069A520 ★ 移动前旧 Y（0x69A5F0: *(this+10) = 旧 +6）
    uint32_t         nGrabX              ; // +0x002C (44) x1  va=0069A520 ★ 拖动抓取点 X（0x69A650 DragWindow: pt.x - *(this+20)）
    uint32_t         nGrabY              ; // +0x0030 (48) x1  va=0069A520 ★ 拖动抓取点 Y（0x69A650: pt.y - *(this+24)；移动帧 pt - 抓取点）
    uint32_t         nTexU               ; // +0x0034 (52) x1  va=0069A520 ★ 纹理绘制左偏移（0x69A6E0 Render: *(this+13)）
    uint32_t         nTexV               ; // +0x0038 (56) x1  va=0069A520 ★ 纹理绘制上偏移（0x69A6E0 Render: *(this+14)）
    uint32_t         nTexW               ; // +0x003C (60) x1  va=0069A520 ★ 纹理绘制宽（0x69A6E0 Render: *(this+15)）
    uint8_t          field_0040          ; // +0x0040 (64) x1  va=0069A520 0x69A520 构造写 1（装配位，语义未定）
    unsigned char _unused_0041[3]; // +0x0041..0x0043 未观测
    uint32_t         field_0044          ; // +0x0044 (68) x1  va=0069A520 0x69A520 构造写 0（装配位，语义未定）
    unsigned char _unused_0048[32]; // +0x0048..0x0067 未观测
    uint32_t         pTexture            ; // +0x0068 (104) x3  va=0069C710 ★ 纹理/图片句柄（0x69C6C0 sub_418DD0 句柄解析入 +104；dtor 清 0；Render 空则跳过）
};
#pragma pack(pop)

// 统计: 字段行 20 / 语义名 18 / 标【推断】0 / 未命名 2 / 末尾偏移 +0x006C

#endif
