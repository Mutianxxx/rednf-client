// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNChaosModule                          主虚表槽位数: 5   字段数: 3
// 继承: CNChaosModule -> nengine__IModule -> nengine__IObject -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00487BA0  sub_487BA0 对象/掉落物生成（+44 引用、+284、45E870/45E680 场景注册）（src/game/skill_load_tutorial.cpp:6651）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNCHAOSMODULE
#define ARAD40JP_FIELDS_CNCHAOSMODULE

#include <stdint.h>

#pragma pack(push, 1)
struct CNChaosModule_Fields {
    unsigned char _base_0x0000        [28]; // +0x0000..0x001B 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pFrameObj           ; // +0x001C (28) x1  va=00487BA0 逐帧驱动对象（0x487BA0: sub_4294E0(*(this+28)) 主帧驱动）【推断】
    unsigned char _unused_0x0020      [60]; // +0x0020..0x005B 未观测
    unsigned int     pSceneObj           ; // +0x005C (92) x6  va=00487BA0 场景对象/掉落物（0x487BA0: fld_5C=*(this+92)；sub_45E870 建 / sub_45E680 判 / 其 vt+284 设属性）
    unsigned char _unused_0x0060      [32]; // +0x0060..0x007F 未观测
    unsigned char    bOnceFlag           ; // +0x0080 (128) x2  va=00487BA0 一次性初始化标志（0x487BA0: *(uint8_t*)(this+128)==0 → 置 1 并初始化 8×28 字节槽表）
};
#pragma pack(pop)

// 统计: 字段行 3 / 语义名 3 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x0081

#endif

