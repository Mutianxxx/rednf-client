// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNChangeDamageBonusRate                主虚表槽位数: 30  字段数: 6
// 继承: CNChangeDamageBonusRate -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   0064CB10  CNChangeDamageBonusRate__vmt4 伤害率变更（攻击力上升粒子）（src/game/ui/aura_create.cpp:11402）
//   0064CA60  CNChangeDamageBonusRate__vmtC 打开槽（+80 开关 + 84 类型 + 88 数值）（src/game/ui/aura_create.cpp:11345）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNCHANGEDAMAGEBONUSRATE
#define ARAD40JP_FIELDS_CNCHANGEDAMAGEBONUSRATE

#include <stdint.h>

#pragma pack(push, 1)
struct CNChangeDamageBonusRate_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x2  va=0064CB10 宿主对象指针（0x64CB10: *(this+4) 经 dword_8F7A24+12 判本机；4600B0 演播）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned char    bAtkUp              ; // +0x0050 (80) x2  va=0064CB10 攻击加成开关（0x64CA60: *(uint8_t*)(this+80)!=0 走 +1306/+1334 加算、==0 走 +1320/+1348）
    unsigned char _unused_0x0051      [3]; // +0x0051..0x0053 未观测
    unsigned int     nBonusType          ; // +0x0054 (84) x3  va=0064CA60 加成类型（0x64CA60: *(this+84) ∈{0,3} 走物理侧、∈{1,3} 走魔法侧）
    unsigned int     nBonusValue         ; // +0x0058 (88) x4  va=0064CB10 加成数值（0x64CA60: *(this+88) 加算进宿主 +1306/+1320/+1334/+1348）
    unsigned char    bDamageAdd          ; // +0x005C (92) x1  va=0064CB10 伤害加算标志（0x64CB10: *(uint8_t*)(this+92)!=0 且 dword_8F7A24+12 判本机）
    unsigned char _unused_0x005D      [3]; // +0x005D..0x005F 未观测
    unsigned int     pFxObj              ; // +0x0060 (96) x4  va=0064CB10 特效对象（0x64CB10: *(this+96)==0 时新建 AttackPowerUp.ptl 粒子对象）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0064

#endif

