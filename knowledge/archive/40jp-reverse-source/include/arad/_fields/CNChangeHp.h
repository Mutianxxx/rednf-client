// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNChangeHp                             主虚表槽位数: 31  字段数: 7
// 继承: CNChangeHp -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   005FD6C0  CNChangeHp__vmt14（+100 模式 1/2 + 4938F0/491D00/491690）（src/combat/swordman_skills.cpp:6733）
//   005FD640  CNChangeHp__vmt78（叶子：+80/+84/+88/+100/+96 参数装载）（src/combat/swordman_skills.cpp:6683）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNCHANGEHP
#define ARAD40JP_FIELDS_CNCHANGEHP

#include <stdint.h>

#pragma pack(push, 1)
struct CNChangeHp_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x2  va=005FD6C0 宿主对象指针（0x5FD6C0: *(this+4) 经 vt+192 取高度、vt+200 取件；0x5FD7C0 主例程）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned int     nHpDelta            ; // +0x0050 (80) x1  va=005FD640 HP 变更值（0x5FD640 vmt78: *(this+80)=nArg2；0x602200 族同槽为总时长）
    unsigned int     nDurationMs         ; // +0x0054 (84) x1  va=005FD640 持续时长 ms（0x5FD640: *(this+84)=nArg3）
    unsigned char    bShowFlag           ; // +0x0058 (88) x1  va=005FD640 显示控制标志（0x5FD640: *(this+88)=pszArg4）
    unsigned char _unused_0x0059      [7]; // +0x0059..0x005F 未观测
    unsigned char    bMode2Flag          ; // +0x0060 (96) x1  va=005FD640 模式 2 分支标志（0x5FD640: *(this+96)=0 复位；0x5FD6C0: *(this+100)==2 时二次弹跳闪烁）
    unsigned char _unused_0x0061      [3]; // +0x0061..0x0063 未观测
    unsigned int     nEffMode            ; // +0x0064 (100) x1  va=005FD640 效果模式（0x5FD640: *(this+100)=nArg5；0x5FD6C0 ==1 走 4938F0+491D00 落位）
    unsigned char _unused_0x0068      [12]; // +0x0068..0x0073 未观测
    unsigned int     pNumAnim            ; // +0x0074 (116) x2  va=005FD6C0 飘字动画件（0x5FD6C0: sub_4938F0(*(this+116)) 驱动恢复数字飘字）
};
#pragma pack(pop)

// 统计: 字段行 7 / 语义名 7 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0078

#endif

