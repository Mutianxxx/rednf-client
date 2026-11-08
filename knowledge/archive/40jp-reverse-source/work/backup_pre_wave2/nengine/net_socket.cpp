// ============================================================
// 【40JP逆向源代码工程】src/nengine/net_socket.cpp
// ARAD.exe 网络连接对象 —— 客户端发包 API（两步式）
//
// 身份定案（2026-10-06 会话 2）：全局实例 = dword_8F7B08。
//   退出清理 sub_41C1E0 对其调 sub_6989F0（ISocket 族关闭）；
//   连接族 sub_698DC0（socket/setsockopt/WSAAsyncSelect/connect 直证）同族。
//   早期误判为"镜头特效"已纠正 —— 见 docs/90 发现日志。
//
// 发包协议（反编译直证）:
//   Begin(type):  构造 12 字节包头 {01, type, ...}，锁定发送上下文
//   Commit():     填大小(+448 缓冲 +12)、序号(+464 WORD 自增)、
//                 校验和(sub_48BE40)、按包名表(off_790928)记日志、
//                 type==3 → 置发送锁(+466)（登录类包锁发送）、实际发送(sub_698A50)
// ============================================================

#include "camera_fx.h"   // 借用 g_socketGlobal/g_mainManager 声明

// ---- 对象字段（this = 连接对象） ----
//  +0x04  （连接族使用）
//  +0x08  BYTE 已连接
//  +0x1B0(448) 发送缓冲指针
//  +0x1B4(452) 发送上下文指针（12 字节包头）
//  +0x1CC(460) 发送长度
//  +0x1D0(464) WORD 发送序号（自增）
//  +0x1D2(466) BYTE 发送锁（type==3 的包置位）

extern int  engine_log(const char* fmt, ...);   // off_77F3FC 引擎输出
extern int  sub_698D70(void* conn);             // 0x698D70 申领发送上下文
extern void sub_698C80(void* hdr12, int len);   // 0x698C80 写入包头队列
extern int  sub_698A50(void* conn);             // 0x698A50 实际发送（返回 1 = 成功）
extern unsigned int sub_48BE40(void* over, void* buf); // 0x48BE40 校验和计算
extern void sub_48BD40(void* dst, void* src, void* lenCtx); // 0x48BD40 包体拷贝
extern const char* const off_790928[];          // 包名表（按 type 索引，4 字节/项）
extern void* sub_422E70(int strId);             // 0x422E70 字符串表取串
extern void  sub_44E8D0(void* mgr, void* id, void* str, int flag); // 0x44E8D0 播报层
extern void* g_mainManager;                     // dword_8F8528

// ------------------------------------------------------------
// 0x423200 —— 发包开始：Begin(type)
// ------------------------------------------------------------
int packet_send_begin(void* conn, char type)
{
    if (*(BYTE*)((char*)conn + 8) == 0)
        return (int)0x80000004;                       // 未连接
    if (*(int*)((char*)conn + 452) != 0 || *(int*)((char*)conn + 448) != 0) {
        engine_log("%s", "asc_6C37C8");               // 上一包未提交（原文错误串）
        return (int)0x80000000;
    }
    BYTE hdr[2] = { 1, (BYTE)type };                  // 包头前两字节
    int zero = 0;
    *(int*)((char*)conn + 452) = sub_698D70(conn);    // 申领上下文
    sub_698C80(hdr, 12);                              // 12 字节包头框架入队
    *(int*)((char*)conn + 448) = 0;
    return 1;
}

// ------------------------------------------------------------
// 0x423380 —— 发包提交：Commit()
// ------------------------------------------------------------
int packet_send_commit(void* conn)
{
    if (*(BYTE*)((char*)conn + 466) != 0) {
        engine_log("%s", "SendLock ");                // 发送锁错误串（0x42 块自证）
        return (int)0x80000000;
    }
    if (*(BYTE*)((char*)conn + 8) == 0)
        return (int)0x80000004;

    int ctx = *(int*)((char*)conn + 452);
    if (ctx == 0)
        return (int)0x80000000;

    *(int*)(ctx + 2) = *(int*)((char*)conn + 448) + 12;         // 包总长 = 缓冲 + 包头
    *(unsigned short*)(ctx + 10) = *(unsigned short*)((char*)conn + 464); // 序号
    ++*(unsigned short*)((char*)conn + 464);                    // 序号自增
    *(unsigned int*)(ctx + 6) = sub_48BE40((void*)(ctx + 10),
                                           (void*)(*(int*)((char*)conn + 448) + 2));
    sub_48BD40((void*)(ctx + 12), (void*)(*(int*)((char*)conn + 448)),
               (void*)(*(int*)((char*)conn + 460)));            // 包体拷入

    *(int*)((char*)conn + 452) = 0;
    *(int*)((char*)conn + 448) = 0;

    // 发送日志（含日期时间戳）
    engine_log("\n[-> COMMAND PACKET] Packet : %s, Size : %d, CheckSum : %d (%2d%2d-%2d:%2d:%2d)",
               off_790928[*(BYTE*)(ctx + 1)],   // 包名表按 type 索引
               *(int*)(ctx + 2), *(unsigned int*)(ctx + 6));

    if (*(BYTE*)(ctx + 1) == 3)
        *(BYTE*)((char*)conn + 466) = 1;              // type 3 → 锁发送（登录流程）

    int rc = sub_698A50(conn);                        // 实际发送
    if (rc != 1 && g_mainManager != 0) {
        // 发送异常 → 本地播报串 145（网络错误提示）
        sub_44E8D0(g_mainManager, (void*)0x1B, sub_422E70(145), 1);
    }
    return rc;
}
