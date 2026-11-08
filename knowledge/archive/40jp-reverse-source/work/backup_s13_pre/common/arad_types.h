// ============================================================
// 【40JP逆向源代码工程】src/common/arad_types.h
// 公共类型定义 —— L2 转写层的类型基础设施
// ARAD.exe (Ver. 200606130k0515, i386, ImageBase 0x400000) 逆向产物
// ============================================================
#ifndef ARAD40JP_COMMON_TYPES_H
#define ARAD40JP_COMMON_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

// ---- CRT 别名（原 binary 为 MSVC 静态 CRT）----
#define free     free
#define operator_new(size) ((void*)0)   /* 占位: 原始调用为全局 operator new */

// ---- 引擎常用全局（.data 区，地址见注释）----
// 0x8F7C04 本地玩家 / 0x8F7C08 副玩家 / 0x8F8520 会话管理器(CNRDUDpModule 族)
// 0x8F8528 主管理器 / 0x8F8548 用户设置 / 0x79D100 tick[16] / 0x79D0C0 rate[16]
// 0x79C0B0 渲染器 / 0x79C0A4 退出对象 / 0x79C0B4 选项对象
// 详见 src/nengine/time_system.h 与 src/nengine/camera_fx.h

#endif // ARAD40JP_COMMON_TYPES_H
