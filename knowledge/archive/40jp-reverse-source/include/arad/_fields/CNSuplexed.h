// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 光环/附加器(IRDAppendage)族 · 族模板还原）
// 类: CNSuplexed                             主虚表槽位数: 32  字段数: 6
// 继承: CNSuplexed -> IRDAppendage（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 基类 IRDAppendage（vmt4 复位 / vt+56 绑定宿主 / vt+76(0) 解除 / vt+760 状态写入）；光环基类 0x64A150..0x64A930（CNRDAuraMaster/CNRDAuraMinion）与生成装配 0x64A570/0x64A190；工厂 sub_64C2C0/64C710/64BDF0/64BBF0；属性加减经 sub_41A5E0/sub_41A590 防篡改闭环
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00650030  sub_650030 状态块写入（+88=-1/+92..100=0/+104=1 + vt+776(3) 门控）（src/nengine/zlib_inflate.cpp:10930）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNSUPLEXED
#define ARAD40JP_FIELDS_CNSUPLEXED

#include <stdint.h>

#pragma pack(push, 1)
struct CNSuplexed_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDAppendage 附加器基类，见 src/cnrd/*.h）一行带过
    unsigned int     pHostObj            ; // +0x0004 (4) x4  va=00650030 宿主对象指针（0x650030: 经宿主 vt+776(3) 门控后 vt+556 停 / vt+768 应用 / vt+556 再启）
    unsigned char _unused_0x0008      [80]; // +0x0008..0x0057 未观测
    unsigned int     nStateParamA        ; // +0x0058 (88) x1  va=00650030 状态参数 A（0x650030: *(this+88)=-1 无来源哨兵）
    unsigned int     nStateParamB        ; // +0x005C (92) x1  va=00650030 状态参数 B（0x650030: *(this+92)=0）
    unsigned int     nStateParamC        ; // +0x0060 (96) x1  va=00650030 状态参数 C（0x650030: *(this+96)=0）
    unsigned int     nStateParamD        ; // +0x0064 (100) x1  va=00650030 状态参数 D（0x650030: *(this+100)=0）
    unsigned char    bStateSet           ; // +0x0068 (104) x1  va=00650030 状态置位标志（0x650030: *(uint8_t*)(this+104)=1）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0069

#endif

