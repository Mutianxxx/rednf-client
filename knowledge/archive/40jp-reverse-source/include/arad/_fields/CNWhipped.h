// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNWhipped                              主虚表槽位数: 30  字段数: 7
// 继承: CNWhipped -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 3 个 / 同族共享）:
//   0064DB50  CNWhipped__vmt14 生成槽（+104 时长 699000/42B420）（src/game/ui/aura_create.cpp:12284）
//   0064E6A0  CNWhipped__vmt1C 生成装配（+80 开关 + 92 倍率 + 96/100 加算）（src/game/ui/aura_create.cpp:12960）
//   0064E1A0  CNWhipped__vmt4 复位（+108 特效件演播）（src/game/ui/aura_create.cpp:12649）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNWHIPPED
#define ARAD40JP_FIELDS_CNWHIPPED

#include <stdint.h>

#pragma pack(push, 1)
struct CNWhipped_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x4  va=0064DB50 宿主对象指针（0x64E6A0: RTDynamicCast(*(this+4) → IRDMonster)；vt+1040 取属性组）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned char    bApplyFlag          ; // +0x0050 (80) x2  va=0064E6A0 加算开关（0x64E6A0: *(uint8_t*)(this+80)!=0 且宿主非空才把 +96/+100 加算进 vt+1040 件）
    unsigned char _unused_0x0051      [11]; // +0x0051..0x005B 未观测
    float            fBonusMul           ; // +0x005C (92) x10 va=0064E6A0 加算倍率（0x64E6A0: *(float*)(件+4) = (*(float*)(this+92)+1.0) × 原值）
    unsigned int     nAddValueA          ; // +0x0060 (96) x2  va=0064E6A0 加算值 A（0x64E6A0: *(uint32_t*)(件+72) += *(this+96)）
    unsigned int     nAddValueB          ; // +0x0064 (100) x2  va=0064E6A0 加算值 B（0x64E6A0: *件 += *(this+100)）
    unsigned int     nDurationMs         ; // +0x0068 (104) x1  va=0064DB50 持续时间 ms（0x64DB50: fld_68=*(this+104) 作 clock_now/42B420 插值终点）
    unsigned int     pFxObj              ; // +0x006C (108) x5  va=0064E1A0 特效对象（0x64E1A0: fld_6C=**(this+108)；件 vt+40 复位 + vt+92 取值经 sub_4600B0 演播）
};
#pragma pack(pop)

// 统计: 字段行 7 / 语义名 7 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0070

#endif

