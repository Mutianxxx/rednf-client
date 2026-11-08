// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDInterfaceManager     主虚表槽位数: 1   字段数: 11
// 继承: CNRDInterfaceManager -> nengine::IAppendDraw（基类段见 src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 1 个）:
//   +0  0x44BA00 CNRDInterfaceManager__vmt0 构造/HUD 条装配（src/game/script_string.cpp:7316）
//       本类唯一槽函数：窗口族 vmt4 存根的宿主；装配 HUD 条(+2480..2496) 与窗口切换 id(+2448)
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDINTERFACEMANAGER
#define ARAD40JP_FIELDS_CNRDINTERFACEMANAGER

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDInterfaceManager_Fields {
    // ---- 区块: 状态机族（管理器状态/焦点 id；0x44BA00） ----
    unsigned char _unused_0000[4]; // +0x0000..0x0003 未观测
    uint32_t         nManagerState        // +0x0004 (4) x1  va=0044BA00 ★ 管理器状态（0x44BA00: *(this+4) != 0 或 nArg2 != 焦点 id 时进入切换分支）
    // ---- 区块: 控件族（窗口管理器/当前窗口 id；0x44BA00） ----
    unsigned char _unused_0008[8]; // +0x0008..0x000F 未观测
    uint32_t         pWndManager          // +0x0010 (16) x1  va=0044BA00 ★ 窗口管理器对象（0x44BA00: sub_464C60(*(this+16)) 取当前窗口）
    // ---- 区块: 状态机族（管理器状态/焦点 id；0x44BA00） ----
    unsigned char _unused_0014[92]; // +0x0014..0x006F 未观测
    uint32_t         nFocusWndId          // +0x0070 (112) x1  va=0044BA00 ★ 焦点窗口 id（0x44BA00: nArg2 != *(this+112) 判定切窗）
    // ---- 区块: 控件族（窗口管理器/当前窗口 id；0x44BA00） ----
    unsigned char _unused_0074[2332]; // +0x0074..0x098F 未观测
    uint32_t         nCurWndId            // +0x0990 (2448) x1  va=0044BA00 ★ 当前窗口 id（0x44BA00: nArg2 == *(this+2448) 快速返回）
    uint32_t         nPrevWndId           // +0x0994 (2452) x1  va=0044BA00 ★ 上一窗口 id（0x44BA00: fld_994 = *(this+2452)）
    unsigned char _unused_0998[12]; // +0x0998..0x09A3 未观测
    uint8_t          bWndVisible          // +0x09A4 (2468) x1  va=0044BA00 窗口可见位（0x44BA00: *(this+2468) != 0 分支）【推断】
    // ---- 区块: 数据缓冲族（HUD 条矩形与标志；0x44BA00） ----
    unsigned char _unused_09A5[11]; // +0x09A5..0x09AF 未观测
    uint32_t         nBarX                // +0x09B0 (2480) x1  va=0044BA00 ★ HUD 条 X（0x44BA00: *(this+2480)）
    uint32_t         nBarW                // +0x09B4 (2484) x2  va=0044BA00 ★ HUD 条宽（0x44BA00: *(this+2484)；<<24 | 0xFFFFFF 组颜色/尺寸参数）
    uint32_t         nBarY                // +0x09B8 (2488) x1  va=0044BA00 ★ HUD 条 Y（0x44BA00: *(this+2488)）
    uint32_t         nBarH                // +0x09BC (2492) x2  va=0044BA00 ★ HUD 条高（0x44BA00: *(this+2492)；同 <<24 | 0xFFFFFF 组参）
    uint32_t         nBarFlags            // +0x09C0 (2496) x1  va=0044BA00 HUD 条附加标志（0x44BA00: *(this+2496)）【推断】
};
#pragma pack(pop)

// 统计: 字段行 11 / 语义名 9 / 标【推断】2 / 未命名 0 / 末尾偏移 +0x09C4

#endif
