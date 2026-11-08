// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDPrivateStoreWindow   主虚表槽位数: 29   字段数: 4
// 继承: CNRDPrivateStoreWindow -> IRDWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 29 个）:
//   +0  0x543BB0 构造（220 行：45E680 物品枚举 + 4BD630/4BD650 + 5515A0 + 5424B0；
//       尾缀登记单例 dword_9B8034；日志自证 "Another private shop created!"）
//   +8  0x542650 __vmt8 Update（57 行：悬停格有上架物品 → 44E8D0 消息 0x1A 请求物品说明；
//       页签 1/2 或未悬停且 dword_9B88D0 非空、dword_795378==9 时解除 26 号对象）
//   +96 0x542C40 __vmt60 条目菜单请求（挂链 +36 → 数量 +8 / 数组 +12；4BE520 解物品后 44E8D0 消息 0x41）
//   +68 0x5443F0 __vmt44 条目动作槽；+76 0x542BB0 __vmt4C 清单清空槽
//   +100 0x541900 __vmt64 子窗口槽（+8 置 2 = 默认展示页）；+108 0x5419E0 __vmt6C 取当前子页号
//   +80/+84/+88 0x541F40/0x541FA0/0x541FD0 发 85 买 / 89 拆摊 / 87 退摊（docs/24 露店协议族）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDPRIVATESTOREWINDOW
#define ARAD40JP_FIELDS_CNRDPRIVATESTOREWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDPrivateStoreWindow_Fields {
    // ---- 区块: 控件族（子窗/页签；0x541900 / 0x5419E0） ----
    unsigned char _base_0x0000[4]; // +0x0000..0x0003 继承段（CNRDPrivateStoreWindow -> IRDWindow -> nengine::IAppendDraw）一行带过
    uint32_t         pOwnerWnd           ; // +0x0004 (4) x1  va=00542650 ★ 宿主/父窗口（0x542650: fld_4 = *(this+4)；vmt10 末尾复位 0）
    uint32_t         pHostCtrl           ; // +0x0008 (8) x1  va=00542650 ★ 宿主控件（0x542650: *(*(this+8)+2504) 取宿主页签；vmt64 子窗口槽置 2 = 默认展示页）
    uint32_t         nTabIndex           ; // +0x000C (12) x1  va=00540360 ★ 页签索引（vmt2C 0x540360: 44AB50(this+8, this+12, 12)）
    // ---- 区块: 数据缓冲族（上架条目挂链；0x542C40） ----
    unsigned char _unused_0010[20]; // +0x0010..0x0023 未观测
    uint32_t         pSellEntryList      ; // +0x0024 (36) x3  va=00542650 ★ 上架条目挂链（0x542650/0x542C40: fld_24 = *(this+36)，其 +8 数量 / +12 数组）
};
#pragma pack(pop)

// 统计: 字段行 4 / 语义名 4 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0028

#endif
