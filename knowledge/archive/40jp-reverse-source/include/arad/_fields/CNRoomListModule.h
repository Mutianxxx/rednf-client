// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRoomListModule         主虚表槽位数: 5   字段数: 12
// 继承: CNRoomListModule -> nengine::IModule -> nengine::IObject -> nengine::IAppendDraw（基类段见 src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 5 个）:
//   +4  0x45CB30 CNRoomListModule__vmt4 房间列表帧处理（src/game/worldmap_reward.cpp:11133）
//       主帧 tick → 悬停房间窗口 alpha 渐变(sub_42B420 100/255/500ms) → 1000ms 节流自动刷新
//       → 选中房 id 比对(sub_48C860) / 14000ms 周期窗(nRand 比对 +160)
//   +8  0x45B4A0 CNRoomListModule__vmt8 房间列表通知（世界地图装载失败同串）
//   +0  0x41F940 删除析构；+12/+16 = DllMain 桩 / nullsub
// ============================================================
#ifndef ARAD40JP_FIELDS_CNROOMLISTMODULE
#define ARAD40JP_FIELDS_CNROOMLISTMODULE

#include <stdint.h>

#pragma pack(push, 1)
struct CNRoomListModule_Fields {
    // ---- 区块: 状态机族（选中房 id / 首帧 / 清位；0x45CB30） ----
    unsigned char _base_0x0000[44]; // +0x0000..0x002B 继承段（CNRoomListModule -> nengine::IModule -> nengine::IObject -> nengine::IAppendDraw）一行带过
    uint32_t         nUiMask             ; // +0x002C (44) x1  va=0045CB30 UI 掩码字段（0x45CB30: sub_4294E0(*(this+44)) 每帧驱动）【推断】
    // ---- 区块: 数据缓冲族（房间 id 查询入参） ----
    unsigned char _unused_0030[52]; // +0x0030..0x0063 未观测
    uint32_t         nQueryRoomId        ; // +0x0064 (100) x1  va=0045CB30 房间查询 id（0x45CB30: sub_48C920(&v47,&v46,pObj,*(this+100),v34) 入参）
    // ---- 区块: 控件族（列表控件/选中窗口；0x45CB30） ----
    uint32_t         pRoomListCtrl       ; // +0x0068 (104) x1  va=0045CB30 ★ 房间列表控件（0x45CB30: 其 +32 状态 !=1 且 clock_now > +112+1000 → 1000ms 节流自动刷新）
    uint32_t         nCurRoomId          ; // +0x006C (108) x2  va=0045CB30 ★ 当前房间 id（0x45CB30: *(this+108) == sub_48C860(pObj) 判定是否换房；随后写回）
    // ---- 区块: 计时族（1000ms 节流 / 14000ms 周期；0x45CB30） ----
    uint32_t         nRefreshTimer       ; // +0x0070 (112) x2  va=0045CB30 ★ 上次刷新时刻（0x45CB30: clock_now(this+16) > *(this+112) + 1000 即满 1s 节流）
    uint8_t          bFirstTick          ; // +0x0074 (116) x2  va=0045CB30 ★ 首帧标志（0x45CB30: ==0 → 置 1 并做首帧初始化）
    unsigned char _unused_0075[3]; // +0x0075..0x0077 未观测
    uint32_t         nSelRoomBgId        ; // +0x0078 (120) x2  va=0045CB30 选中房间背景 id（0x45CB30: LODWORD(v42)=*(this+120)，用后清 0）
    unsigned char _unused_007C[13]; // +0x007C..0x0088 未观测
    uint8_t          field_0089          ; // +0x0089 (137) x1  va=0045CB30 复位组字节（0x45CB30 清 0，语义未定）
    uint8_t          field_008A          ; // +0x008A (138) x1  va=0045CB30 复位组字节（0x45CB30 清 0，语义未定）
    unsigned char _unused_008B[13]; // +0x008B..0x0097 未观测
    uint32_t         pSelRoomWnd         ; // +0x0098 (152) x6  va=0045CB30 ★ 选中房间窗口（0x45CB30: sub_45E680 有效判定；调其 vt+284 设可见/alpha，选新则先复位旧窗）
    uint32_t         nBlinkTimer         ; // +0x009C (156) x2  va=0045CB30 ★ 闪烁/刷新计时（0x45CB30: clock_now(this+16) >= *(this+156) + 14000 即 14s 周期）
    uint32_t         nRandCache          ; // +0x00A0 (160) x2  va=0045CB30 ★ 随机数缓存（0x45CB30: nRand == *(this+160) 时更新，供随机房间名/广告）
};
#pragma pack(pop)

// 统计: 字段行 12 / 语义名 9 / 标【推断】1 / 未命名 2 / 末尾偏移 +0x00A4

#endif
