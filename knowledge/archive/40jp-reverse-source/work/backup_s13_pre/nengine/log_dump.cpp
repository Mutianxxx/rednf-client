// ============================================================
// 【40JP逆向源代码工程】src/nengine/log_dump.cpp
// 模块: 引擎核心 0x40 区 —— 程序入口 / 日志 / 崩溃报告链 / NPK 包加载 / Win32-D3D8-DSound-DInput 框架
// 来源: work/dump_engine.txt  区块: 0x400000-0x410000
// 层级: L2 转写层（Hex-Rays 逐字对应）+【L1 精修层】
//
// 【L1 精修内容】（注释级，函数体与 L2 逐字一致，零改动）:
//   ① 文件头重写 + 23 个 SECTION 分区横幅（23 段生效）+ SECTION 索引表
//   ② 44 个关键函数【解读】注释块（WinMain/崩溃链/NPK/日志核心/D3D8/IME/控制台）
//   ③ 12 个函数标记行追加 [串: "..."] 字符串证据尾注（逐函数覆盖）
//
// ★★ 崩溃报告完整流程（本区直证，全链在 0x401F80-0x4028C0）:
//   [运行时] WinMain(0x401B20)
//     ├→ sub_402170(0, hInstance, off_77F284[0], off_77F288[0])   崩溃上下文初始化:
//     │    · 上报目标串 → ctx+126（unk_79C0C8 对象，off_77F284/288=上报地址对【推断:URL】）
//     │    · timeGetTime → "%08x" 实例号 ctx+24；角色名占位 "_NONE" ctx+75
//     │    · sub_402030 生成文件名: "%s_%s.dmp"(ctx+386) / "%s_%s.trc"(ctx+646)
//     │      / "DNF_DUMP.zip"(ctx+906)，前缀=角色名_实例号
//     │    · sub_401F80 清理旧 *.dmp / *.trc / *.zip
//     └→ RegisterExceptionCallback(sub_401110)                     注册崩溃回调
//   [崩溃时] sub_401110(异常信息串)
//     ① sub_404020()  冲刷日志 fflush
//     ② sub_403A90()  NiLog 收尾
//     ③ 主管理器(dword_79C0C0)+113 角色名 → sub_402080 覆写报告名（50B 上限）
//     ④ sub_4020B0(异常串) 写 dmp 占位文件
//     ⑤ sub_402440 ★ 打包上报:
//         a. DNF.trc 全量复制为 %s_%s.trc
//         b. sprintf "a -tzip %s %s %s" → ShellExecuteExA("7z","open",".\\")
//            —— 调系统 7-Zip 命令行打包 dmp+trc → DNF_DUMP.zip
//         c. GetExitCodeProcess 轮询 259(STILL_ACTIVE) + Sleep(1000ms)
//         d. zip 全量 → base64（0x4020F0 长度 + 0x401DA0 编码，76 列折行）
//         e. 拼 " content=" → sub_4028C0: InternetConnectA + HttpOpenRequestA("POST")
//            + "Content-Type: application/x-www-form-urlencoded" + HttpSendRequestA
//            （会话标识 InternetOpenA("NIS::Http")，0x402780）
//
// 其它要点:
//   - 0x401B20 WinMain 的 malloc(rand()%100000) 为启动哨兵分配；srand(timeGetTime) 播种。
//   - 日志体系: NiLog（0x403D60 写入器，5000 行轮转 + Log File Opened/Closed 横幅 +
//     "%02d/%02d/%04d - %2d:%02d:%02d" 时间戳）、NiMemory.log（0x406C60）、
//     NiProfile.log（0x406CA0）、_DEBUG 调试控制台（0x40D510 AllocConsole + MS UI Gothic）。
//   - NPK 封包: "NeoplePack_Bill" 魔数（0x40E9E0）+ "*.npk" 目录扫描（0x40EF70）+
//     文件名 tolower 红黑树索引（0x40D660-0x40E860）；包内文件打开 0x40E3E0 被
//     gfx_texture.cpp 0x418CD0（IMG）复用。
//   - off_77F3FC = 全局日志函数指针（引擎级格式化打印）；sub_404F40/404F80 = NiProfile
//     计时作用域对（rdtsc 底层 0x404E70）。
//   - off_77F284/288: 崩溃上报地址数据对【推断】。
//
// 函数数: 442（L1 覆盖 442：解读 44 / 串证据 12 / 分区 23）
// ============================================================

#include "../../common/arad_types.h"
// ============================================================
// SECTION 索引（按 VA 升序）
// ============================================================
//   0x401000 — 基础设施：nengine::IObject 构造/析构桩 + MSVC std::string(CString) 模板实例族
//   0x401B20 — 程序入口 WinMain 与全局初始化链（崩溃回调注册 / 随机播种 / 子系统聚合初始化）
//   0x401F80 — ★★ 崩溃报告链：旧转储清理 → 命名 → dmp 占位 → 7z 打包 DNF_DUMP.zip → base64 → NIS::Http 上报
//   0x402A50 — 字符串参数包 / CString 数组 / vsprintf 格式化打包工具
//   0x4031E0 — 数学库与引擎子系统初始化（sin/cos/tan 表、rand 播种、随机数工具）
//   0x4038D0 — 日志核心：NiLog 对象（QPC 计时日志 / 横幅 / 5000 行轮转 / OutputDebugString）
//   0x4042E0 — Win32 窗口框架：主窗口过程 / 消息循环 / 单实例检测 / 全屏分辨率切换
//   0x4049C0 — 插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）
//   0x405C20 — 窗口类注册与创建 / GDI 图标位图工具
//   0x405E00 — 引擎子系统事件分发框架（list/vector 容器事件路由，0x405E00-0x406C50）
//   0x406C50 — NiMemory.log / NiProfile.log 日志对象（Gamebryo 风格内存/性能日志）
//   0x406D90 — IME 输入法处理族（Composition/Candidate/NotifyIME，日志直证）
//   0x407AE0 — 子系统注册容器族（树/链表基础设施，为 0x41 区等上层共用）
//   0x408B90 — GDI 位图工具 + NEOPLE_WEB 内嵌浏览器窗口抓屏（BitBlt 采样）
//   0x409AE0 — D3D8 应用初始化：设备/模式枚举（qsort）、D3DAPPERR 错误分类、REF 设备回退警告
//   0x40A800 — DirectSound8 声音子系统（DirectSoundCreate8 / 协作级 / 缓冲管理）
//   0x40B140 — DirectInput8 输入子系统（DirectInput8Create / 键盘设备容器）
//   0x40B990 — 文本测量（GetTextExtentPoint32）/ GDI 文本渲染 / 容器工具
//   0x40C4C0 — STL map/set 红黑树模板实例 + 字体位图缓存（invalid map/set iterator 诊断）
//   0x40D020 — 调试控制台（_DEBUG：AllocConsole / MS UI Gothic / DIB 行缓冲 / FreeConsole）
//   0x40D660 — 大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）
//   0x40E9E0 — ★★ NPK 资源包加载器（NeoplePack_Bill 魔数 / *.npk 目录扫描 / 包内文件定位）
//   0x40F2F0 — 矩形/绘制辅助与杂项（SetRect 族、sprite 小工具）
// ============================================================

// ============================================================
// SECTION 0x401000 — 基础设施：nengine::IObject 构造/析构桩 + MSVC std::string(CString) 模板实例族
// ============================================================
// ------------------------------------------------------------
// 0x401000 sub_401000
// ------------------------------------------------------------
// 【解读】
//   nengine::IObject 构造桩：写 IObject vftable + this+4 清零（引用计数/标志头）。
//   全引擎对象的最基础构造，0x41/0x65 区大量对象的第一步。
// ------------------------------------------------------------
void /*thiscall*/ sub_401000(uint8_t *this)  // 【基础设施：nengine::IObject 构造/析构桩 + MSVC std::s…】
{
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *(this + 4) = 0;  // this+4 清 0
}



// ------------------------------------------------------------
// 0x401010 sub_401010 —— nengine::IObject 析构桩（虚表覆写为 IObject::vftable，+4 清零；低位置位时 free）
// 崩溃链/日志对象族的公共析构壳 —— 先重置虚表指针，再按需释放内存。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_401010(uint8_t *Block, char pszArg2)  // 函数 nengine::IObject 析构桩（虚表覆写为 IObject::vftable，+4 清零；低位置位时 free）
{
  *(uint32_t *)Block = &nengine::IObject::`vftable';
  *(Block + 4) = 0;
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x401040 sub_401040 —— clong 构造（·sub_41A630 随机源初始化 + 挂 clong::vftable）
// clong = 高精度随机长整数对象（0x4019B0 大型对象 +248 处内嵌一例）。
// ------------------------------------------------------------
void /*thiscall*/ sub_401040(uint32_t *this)  // 函数 clong 构造（·sub_41A630 随机源初始化 + 挂 clong::vftable）
{
  sub_41A630((unsigned int)this);  // 调 sub_41A630
  *this = &clong::`vftable';
}



// ------------------------------------------------------------
// 0x401060 sub_401060
// ------------------------------------------------------------
// attributes: thunk
void /*thiscall*/ sub_401060(void **this)
{
  sub_41B010(this);  // 调 sub_41B010
}



// ------------------------------------------------------------
// 0x401090 sub_401090 —— NIS::Http 全局单例构造（operator new(4) + 挂 off_6C1570 虚表 → dword_79C55C）
// 崩溃上报 HTTP 会话单例登记；0x4010E0 退出清理经虚表槽 0 释放并置 0。
// ------------------------------------------------------------
int sub_401090()  // 函数 NIS::Http 全局单例构造（operator new(4) + 挂 off_6C1570 虚表 → dword_79C55C）
{
  uint32_t *pMem; // eax

  pMem = operator new(4u);
  if ( pMem == nullptr )  // 若 pMem 为空
    return -2147483640;  // 返回 0x80000008（内存不足）
  *pMem = &off_6C1570;
  dword_79C55C = (int)pMem;
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x4010C0 sub_4010C0 —— HTTP 会话对象构造转发（this+8 → ·sub_402780 InternetOpenA）
// 与 0x4010D0 析构转发（this+8 → ·sub_402740 InternetCloseHandle）成对。
// ------------------------------------------------------------
char */*thiscall*/ sub_4010C0(char *this)  // 函数 HTTP 会话对象构造转发（this+8 → ·sub_402780 InternetOpenA）
{
  sub_402780(this + 8);
  return this;
}



// ------------------------------------------------------------
// 0x4010D0 sub_4010D0 —— HTTP 会话对象析构转发（this+8 → ·sub_402740 = InternetCloseHandle + 句柄置 0）
// 与 ·sub_4010C0 成对；off_6C16EC 虚表族的关闭路径。
// ------------------------------------------------------------
int /*thiscall*/ sub_4010D0(char *this)  // 函数 HTTP 会话对象析构转发（this+8 → ·sub_402740 = InternetCloseHandle + 句柄置 0）
{
  return sub_402740(this + 8);  // 调 HTTP 会话句柄关闭（InternetCloseHandle + 句柄置 0）
}



// ------------------------------------------------------------
// 0x4010E0 sub_4010E0 —— 全局关停清理链（主管理器槽释放 → 两全局单例虚表槽 0 释放 → ·sub_405340/·sub_4033E0 收尾 → byte_79C560 复位）
// WinMain 退出分支与 0x4048F0 单实例退出均调用: ·sub_403400 日志容器取值 →
// ·sub_404490(&dword_79C0A0) 主管理器释放 → dword_79C55C（NIS::Http）/ dword_79D078（数学子系统）置 0。
// ------------------------------------------------------------
int sub_4010E0()  // 函数 全局关停清理链（主管理器槽释放 → 两全局单例虚表槽 0 释放 → ·sub_405340/·sub_4033E0 收尾 → byte_…
{
  sub_403400();  // 调 sub_403400
  sub_404490(&dword_79C0A0);  // 调 sub_404490
  if ( dword_79C55C != 0 )  // 若 dword_79C55C != 0
  {
    (**(void (/*thiscall*/ ***)(int, int))dword_79C55C)(dword_79C55C, 1);
    dword_79C55C = 0;  // dword_79C55C = 0/空
  }
  if ( dword_79D078 != 0 )  // 若 dword_79D078 != 0
  {
    (**(void (/*thiscall*/ ***)(int, int))dword_79D078)(dword_79D078, 1);
    dword_79D078 = 0;  // dword_79D078 = 0/空
  }
  sub_405340();  // 调 sub_405340
  sub_4033E0();  // 调 sub_4033E0
  byte_79C560 = 0;  // byte_79C560 = 0/空
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x401110 sub_401110
// ------------------------------------------------------------
// 【解读】
//   ★★ 崩溃回调本体（WinMain 中 RegisterExceptionCallback(0x401110) 注册，参数=异常信息串）:
//     ① sub_404020()  冲刷日志 fflush；
//     ② sub_403A90()  NiLog/QPC 日志对象收尾；
//     ③ dword_79C0C0（主管理器）非 0 时 sub_402080(管理器+113) 取角色名 → 设为报告名；
//     ④ sub_4020B0(Format) 写 dmp 占位文件（异常信息串为内容）；
//     ⑤ sub_402440(&unk_79C0C8) 7z 打包 + HTTP 上报（上下文对象 = WinMain 初始化的 79C0C8）。
//   完整链见文件头“崩溃报告流程图”。
// ------------------------------------------------------------
int /*cdecl*/ sub_401110(char *Format)
{
  sub_404020();  // 调 sub_404020
  sub_403A90();  // 调 sub_403A90
  if ( dword_79C0C0 != 0 )  // 若 dword_79C0C0 != 0
    sub_402080((char *)(dword_79C0C0 + 113));  // 调 sub_402080
  sub_4020B0(Format);  // 调 sub_4020B0
  return sub_402440(&unk_79C0C8);
}



// ------------------------------------------------------------
// 0x401150 sub_401150 —— crypt4byte 派生析构壳（·sub_432D10 转发 → ·sub_41A580 挂 crypt4byte::vftable 并递减全局计数）
// 与 ·sub_401010 同构（差异: 基类换为 crypt4byte，额外 --dword_8F7A08）。
// ------------------------------------------------------------
void */*thiscall*/ sub_401150(void *Block, char pszArg2)  // 函数 crypt4byte 派生析构壳（·sub_432D10 转发 → ·sub_41A580 挂 crypt4byte::vftable …
{
  sub_432D10(Block);  // 调 sub_432D10
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x401170 sub_401170 —— nengine::CNTimer 计时子对象构造（挂 off_6C2B88 = CNTimer::vftable，+12 置 1）
// ★ 全库复用度最高的内嵌子对象（战斗中状态/怪物/UI/界面对象 20+ 处内嵌时钟域）。
// +4/+8 清零、+12=1、+13/+14 标志清零、+16/+20/+24 计数清零。
// ------------------------------------------------------------
void /*thiscall*/ sub_401170(uint8_t *this)  // 函数 nengine::CNTimer 计时子对象构造（挂 off_6C2B88 = CNTimer::vftable，+12 置 1）
{
  *(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)this = &off_6C2B88;  // vftable = off_6C2B88
  *((uint32_t *)this + 2) = 0;  // this 偏移 8 清 0
  *(this + 12) = 1;  // this+12 = 1
  *(this + 14) = 0;  // this+14 清 0
  *(this + 13) = 0;  // this+13 清 0
  *((uint32_t *)this + 6) = 0;  // this 偏移 24 清 0
  *((uint32_t *)this + 5) = 0;  // this 偏移 20 清 0
  *((uint32_t *)this + 4) = 0;  // this 偏移 16 清 0
}



// ------------------------------------------------------------
// 0x4011C0 sub_4011C0 —— std::string 长度字段写入（+20=长度，按 +24 容量判内联缓冲或堆指针落尾 NUL）
// MSVC std::string(_String_base) 内联小串(容量<16)用 this+4，堆串用 *(this+4)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4011C0(uint32_t *this, int nArg2)  // 函数 std::string 长度字段写入（+20=长度，按 +24 容量判内联缓冲或堆指针落尾 NUL）
{
  bool fld_e6; // cf
  int result; // eax

  fld_e6 = *(this + 6) < 0x10u;
  result = nArg2;
  *(this + 5) = nArg2;  // this+5 = 参数2
  if ( fld_e6 )
    *((uint8_t *)this + nArg2 + 4) = 0;
  else  // 否则分支
    *(uint8_t *)(*(this + 1) + nArg2) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4011E0 sub_4011E0 —— std::string 释放回内联态（堆缓冲 free → +20=Size、+24=15、尾 NUL）
// assign/clear 系列的收尾原语；missing_tail.cpp 多处以 (ptr, 1, 0) 形式复用。
// ------------------------------------------------------------
void /*thiscall*/ sub_4011E0(uint32_t *this, char pszArg2, size_t Size)  // 函数 std::string 释放回内联态（堆缓冲 free → +20=Size、+24=15、尾 NUL）
{
  void *fld_e1; // ebx

  if ( pszArg2 != 0 && *(this + 6) >= 0x10u )
  {
    fld_e1 = (void *)*(this + 1);
    if ( Size != 0 )  // 若 Size != 0
      memcpy(this + 1, fld_e1, Size);  // 调 memcpy
    j__free(fld_e1);
  }
  *(this + 5) = Size;
  *(this + 6) = 15;  // this+6 = 15
  *((uint8_t *)this + Size + 4) = 0;
}



// ------------------------------------------------------------
// 0x401230 sub_401230 —— std::string::erase(pos, n) 模板实例（越界走 _Xran；memcpy_0 左移尾部）
// 返回 this；n 超长时截到剩余长度。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_401230(uint32_t *this, unsigned int uArg2, unsigned int uArg3)  // 函数 std::string::erase(pos, n) 模板实例（越界走 _Xran；memcpy_0 左移尾部）
{
  unsigned int fld_e52; // edi
  unsigned int fld_e5; // eax
  unsigned int fld_e6; // ecx
  uint32_t *pThis_1; // ebx
  uint32_t *pThis_12; // edx
  uint32_t *pThis_13; // ecx
  unsigned int fld_e62; // ecx
  unsigned int fld_e53; // eax

  if ( *(this + 5) < uArg2 )
    std::_String_base::_Xran((std::_String_base *)this);  // CRT 抛出 out_of_range（下标越界）
  fld_e52 = uArg3;
  fld_e5 = *(this + 5) - uArg2;
  if ( fld_e5 < uArg3 )
    fld_e52 = *(this + 5) - uArg2;
  if ( fld_e52 != 0 )  // 若 fld_e52 != 0
  {
    fld_e6 = *(this + 6);  // fld_e6 = this+6 字段
    pThis_1 = this + 1;
    if ( fld_e6 < 0x10 )
      pThis_12 = this + 1;
    else  // 否则分支
      pThis_12 = (uint32_t *)*pThis_1;
    if ( fld_e6 < 0x10 )
      pThis_13 = this + 1;
    else  // 否则分支
      pThis_13 = (uint32_t *)*pThis_1;
    memcpy_0((char *)pThis_13 + uArg2, (char *)pThis_12 + uArg2 + fld_e52, fld_e5 - fld_e52);
    fld_e62 = *(this + 6);  // fld_e62 = this+6 字段
    fld_e53 = *(this + 5) - fld_e52;
    *(this + 5) = fld_e53;
    if ( fld_e62 >= 0x10 )  // 若 fld_e62 >= 0x10
      pThis_1 = (uint32_t *)*pThis_1;
    *((uint8_t *)pThis_1 + fld_e53) = 0;
  }
  return this;
}



// ------------------------------------------------------------
// 0x4012B0 sub_4012B0 —— std::string 缓冲重分配（MSVC 对齐 16 增长策略: 新容量 = 请求|15，几何增长条件满足时取 1.5 倍）
// operator new 新块 + memcpy 旧内容 + free 旧堆块，起止/容量/尾 NUL 同步。
// 全库 std::string 扩容唯一落地（0x4014D0/0x4015C0/0x4013E0/0x4021F0 等共用）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4012B0(uint32_t *this, unsigned int uArg2, size_t Size)  // 函数 std::string 缓冲重分配（MSVC 对齐 16 增长策略: 新容量 = 请求|15，几何增长条件满足时取 1.5 倍）
{
  unsigned int uArg22; // esi
  unsigned int fld_e6; // ebx
  unsigned int v6; // ecx
  const void *pThis_1; // eax
  uint8_t *result; // eax
  uint32_t v9[9]; // [esp+0h] [ebp-24h] BYREF
  void *pMem; // [esp+2Ch] [ebp+8h]

  uArg22 = uArg2 | 0xF;
  v9[5] = v9;
  v9[4] = this;
  if ( (uArg2 | 0xF) == 0xFFFFFFFF )
  {
    uArg22 = uArg2;
  }
  else  // 否则分支
  {
    fld_e6 = *(this + 6);  // fld_e6 = this+6 字段
    v6 = fld_e6 >> 1;
    if ( uArg22 / 3 < fld_e6 >> 1 && fld_e6 <= -2 - v6 )
      uArg22 = v6 + fld_e6;
  }
  v9[8] = 0;
  pMem = operator new(uArg22 + 1);
  if ( Size != 0 )  // 若 Size != 0
  {
    if ( *(this + 6) < 0x10u )
      pThis_1 = this + 1;
    else  // 否则分支
      pThis_1 = (const void *)*(this + 1);
    memcpy(pMem, pThis_1, Size);  // 调 memcpy
  }
  if ( *(this + 6) >= 0x10u )
    j__free((void *)*(this + 1));
  result = this + 1;
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  *(this + 1) = pMem;
  *(this + 6) = uArg22;
  *(this + 5) = Size;
  if ( uArg22 >= 0x10 )  // 若 uArg22 >= 0x10
    result = pMem;
  result[Size] = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4013E0 sub_4013E0 —— std::string::resize(n, ch) 模板实例（增长走 ·sub_4012B0，收缩回内联态或就地截断）
// n == -1 抛 _Xlen；返回是否非空。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4013E0(size_t *this, uint8_t *uArg2, char pszArg3)  // 函数 std::string::resize(n, ch) 模板实例（增长走 ·sub_4012B0，收缩回内联态或就地截断）
{
  unsigned int fld_e6; // eax
  uint8_t *fld_e5; // edi
  void *fld_e1; // ebp

  if ( uArg2 == (uint8_t *)-1 )
    std::_String_base::_Xlen((std::_String_base *)this);  // CRT 抛出 length_error（字符串过长）
  fld_e6 = *(this + 6);  // fld_e6 = this+6 字段
  if ( fld_e6 < (unsigned int)uArg2 )
  {
    sub_4012B0(this, (unsigned int)uArg2, *(this + 5));  // 调 sub_4012B0
    return uArg2 != nullptr;
  }
  if ( pszArg3 != 0 && (unsigned int)uArg2 < 0x10 )
  {
    fld_e5 = (uint8_t *)*(this + 5);
    if ( uArg2 < fld_e5 )
      fld_e5 = uArg2;
    if ( fld_e6 >= 0x10 )  // 若 fld_e6 >= 0x10
    {
      fld_e1 = (void *)*(this + 1);
      if ( fld_e5 != nullptr )  // 若 fld_e5 非空
        memcpy(this + 1, fld_e1, (size_t)fld_e5);  // 调 memcpy
      j__free(fld_e1);
    }
    *(this + 5) = (size_t)fld_e5;
    *(this + 6) = 15;  // this+6 = 15
    fld_e5[(uint32_t)this + 4] = 0;
    return uArg2 != nullptr;
  }
  else  // 否则分支
  {
    if ( uArg2 == nullptr )  // 若 uArg2 为空
    {
      *(this + 5) = 0;  // this+5 清 0
      if ( fld_e6 >= 0x10 )  // 若 fld_e6 >= 0x10
      {
        *(uint8_t *)*(this + 1) = 0;
        return false;
      }
      *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
    }
    return uArg2 != nullptr;
  }
}



// ------------------------------------------------------------
// 0x4014A0 unknown_libname_1
// ------------------------------------------------------------
// Microsoft VisualC 2-14/net runtime
uint32_t */*thiscall*/ unknown_libname_1(uint32_t *this)
{
  if ( *(this + 9) < 0x10u )
    return this + 4;
  else  // 否则分支
    return (uint32_t *)*(this + 4);
}



// ------------------------------------------------------------
// 0x4014B0 sub_4014B0 —— std::logic_error 析构壳（·sub_4017A0 + 低位置位 free）
// 与 ·sub_401010 同构族（差异: 基类为 std::logic_error）；配套 0x401740 构造。
// ------------------------------------------------------------
void */*thiscall*/ sub_4014B0(void *Block, char pszArg2)  // 函数 std::logic_error 析构壳（·sub_4017A0 + 低位置位 free）
{
  sub_4017A0();  // 调 sub_4017A0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x4014D0 sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
// ★ std::string 赋值主路径: this == pArg2 时经 ·sub_401230 两次 erase 自转；
// 否则按需 ·sub_4012B0 扩容后 memcpy 子串。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4014D0(size_t *this, size_t *pArg2, unsigned int uArg3, unsigned int uArg4)  // 函数 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
{
  unsigned int uArg42; // edi
  unsigned int fld_e6; // eax
  bool v8; // zf
  uint32_t *v9; // ecx
  char **pThis_1; // ebx
  char **pThis_12; // eax
  unsigned int fld_e62; // eax

  if ( pArg2[5] < uArg3 )
    std::_String_base::_Xran((std::_String_base *)this);  // CRT 抛出 out_of_range（下标越界）
  uArg42 = pArg2[5] - uArg3;
  if ( uArg4 < uArg42 )
    uArg42 = uArg4;
  if ( this == pArg2 )
  {
    sub_401230(this, uArg3 + uArg42, 0xFFFFFFFF);  // 调 sub_401230
    sub_401230(this, 0, uArg3);  // 调 sub_401230
    return this;
  }
  if ( uArg42 == -1 )
    std::_String_base::_Xlen((std::_String_base *)this);  // CRT 抛出 length_error（字符串过长）
  fld_e6 = *(this + 6);  // fld_e6 = this+6 字段
  if ( fld_e6 >= uArg42 )  // 若 fld_e6 >= uArg42
  {
    v8 = uArg42 == 0;
    if ( uArg42 == 0 )  // 若 uArg42 == 0
    {
      *(this + 5) = 0;  // this+5 清 0
      if ( fld_e6 < 0x10 )
        *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
      else  // 否则分支
        *(uint8_t *)*(this + 1) = 0;
      return this;
    }
  }
  else  // 否则分支
  {
    sub_4012B0(this, uArg42, *(this + 5));  // 调 sub_4012B0
    v8 = uArg42 == 0;
  }
  if ( !v8 )
  {
    if ( pArg2[6] < 0x10 )
      v9 = pArg2 + 1;
    else  // 否则分支
      v9 = (uint32_t *)pArg2[1];
    pThis_1 = (char **)(this + 1);
    if ( *(this + 6) < 0x10 )
      pThis_12 = (char **)(this + 1);
    else  // 否则分支
      pThis_12 = (char **)*pThis_1;  // pThis_12 = 解引用跟踪 pThis_1
    memcpy(pThis_12, (char *)v9 + uArg3, uArg42);  // 调 memcpy
    fld_e62 = *(this + 6);  // fld_e62 = this+6 字段
    *(this + 5) = uArg42;
    if ( fld_e62 >= 0x10 )  // 若 fld_e62 >= 0x10
      pThis_1 = (char **)*pThis_1;  // pThis_1 = 解引用跟踪 pThis_1
    *((uint8_t *)pThis_1 + uArg42) = 0;
  }
  return this;
}



// ------------------------------------------------------------
// 0x4015C0 sub_4015C0 —— std::string 构造赋值（从 [Src, Src+Size) 拷贝）
// ★ 跨文件登记名即 std::string 构造赋值；覆盖检测: Src 落在自身缓冲内时改走 ·sub_4014D0 子串赋值。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4015C0(size_t *this, uint8_t *Src, size_t Size)  // 【std::string构造赋值】
{
  unsigned int fld_e6; // ecx
  unsigned int *pThis_1; // ebx
  unsigned int pThis_12; // eax
  int pThis_13; // eax
  size_t fld_e62; // eax
  bool v10; // zf
  void *pThis_14; // eax
  unsigned int fld_e63; // eax

  fld_e6 = *(this + 6);  // fld_e6 = this+6 字段
  pThis_1 = this + 1;
  if ( fld_e6 < 0x10 )
    pThis_12 = (unsigned int)(this + 1);
  else  // 否则分支
    pThis_12 = *pThis_1;  // pThis_12 = 解引用 pThis_1
  if ( (unsigned int)Src >= pThis_12 )
  {
    pThis_13 = fld_e6 < 0x10 ? (int)(this + 1) : *pThis_1;
    if ( pThis_13 + *(this + 5) > (unsigned int)Src )
    {
      if ( fld_e6 >= 0x10 )  // 若 fld_e6 >= 0x10
        pThis_1 = (unsigned int *)*pThis_1;
      return sub_4014D0(this, this, Src - (uint8_t *)pThis_1, Size);  // 调 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    }
  }
  if ( Size == -1 )
    std::_String_base::_Xlen((std::_String_base *)this);  // CRT 抛出 length_error（字符串过长）
  fld_e62 = *(this + 6);  // fld_e62 = this+6 字段
  if ( fld_e62 < Size )
  {
    sub_4012B0(this, Size, *(this + 5));  // 调 sub_4012B0
    v10 = Size == 0;
LABEL_16:  // LABEL_16（跳转目标）
    if ( !v10 )
    {
      if ( *(this + 6) < 0x10 )
        pThis_14 = this + 1;
      else  // 否则分支
        pThis_14 = (void *)*pThis_1;
      memcpy(pThis_14, Src, Size);  // 调 memcpy
      fld_e63 = *(this + 6);  // fld_e63 = this+6 字段
      *(this + 5) = Size;
      if ( fld_e63 >= 0x10 )  // 若 fld_e63 >= 0x10
        pThis_1 = (unsigned int *)*pThis_1;
      *((uint8_t *)pThis_1 + Size) = 0;
    }
    return this;
  }
  v10 = Size == 0;
  if ( Size != 0 )  // 若 Size != 0
    goto LABEL_16;  // 跳转 LABEL_16
  *(this + 5) = 0;  // this+5 清 0
  if ( fld_e62 >= 0x10 )  // 若 fld_e62 >= 0x10
    pThis_1 = (unsigned int *)*pThis_1;
  *(uint8_t *)pThis_1 = 0;
  return this;
}



// ------------------------------------------------------------
// 0x401690 sub_401690 —— std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全量赋值）
// 被 0x401920 等异常对象拷贝链复用。
// ------------------------------------------------------------
int /*thiscall*/ sub_401690(int this, size_t *pArg2)  // 函数 std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全量赋值）
{
  *(uint32_t *)(this + 20) = 0;  // this+20（uint32 槽）= 0
  *(uint32_t *)(this + 24) = 15;  // this+24（uint32 槽）= 15
  *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
  sub_4014D0((size_t *)this, pArg2, 0, 0xFFFFFFFF);  // 调 sub_4014D0
  return this;
}



// ------------------------------------------------------------
// 0x4016C0 sub_4016C0 —— std::string 由 C 串赋值（strlen + ·sub_4015C0）
// C 串入口薄封装。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4016C0(size_t *this, char *Str)  // 函数 std::string 由 C 串赋值（strlen + ·sub_4015C0）
{
  size_t nLen; // eax

  nLen = strlen(Str);  // CRT 字符串长度（逐字节扫描到 NUL）
  return sub_4015C0(this, Str, nLen);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4016E0 sub_4016E0 —— 指针区间批量释放（[pArg1, pArg2) 逐元素 ·sub_41B010 引用计数递减）
// vector<T> 析构模板实例。
// ------------------------------------------------------------
void /*stdcall*/ sub_4016E0(void **pArg1, void **pArg2)  // 函数 指针区间批量释放（[pArg1, pArg2) 逐元素 ·sub_41B010 引用计数递减）
{
  void **i; // esi

  for ( i = pArg1; i != pArg2; ++i )
    sub_41B010(i);  // 调 sub_41B010
}



// ------------------------------------------------------------
// 0x401710 sub_401710 —— std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
// 构造函数体形式（含字段预置）。
// ------------------------------------------------------------
int /*thiscall*/ sub_401710(int this, char *Str)  // 函数 std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
{
  size_t nLen; // eax

  *(uint32_t *)(this + 24) = 15;  // this+24（uint32 槽）= 15
  *(uint32_t *)(this + 20) = 0;  // this+20（uint32 槽）= 0
  *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
  nLen = strlen(Str);  // CRT 字符串长度（逐字节扫描到 NUL）
  sub_4015C0((size_t *)this, Str, nLen);  // 【std::string构造赋值】
  return this;
}



// ------------------------------------------------------------
// 0x401740 sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
// 被 0x401830（vector too long 抛出器）复用。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_401740(uint32_t *this, size_t *pArg2)  // 函数 std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
{
  sub_66AF9C();  // 调 sub_66AF9C
  *this = &std::logic_error::`vftable';
  *(this + 8) = 0;  // this+8 清 0
  *(this + 9) = 15;  // this+9 = 15
  *((uint8_t *)this + 16) = 0;  // this 偏移 16 字节 = 0
  sub_4014D0(this + 3, pArg2, 0, 0xFFFFFFFF);  // 调 sub_4014D0
  return this;
}



// ------------------------------------------------------------
// 0x4017A0 sub_4017A0 —— std::logic_error 析构（堆消息串 free → ·sub_66B034 基类释放）
// 异常对象析构标准形态。
// ------------------------------------------------------------
int /*thiscall*/ sub_4017A0(void **this)  // 函数 std::logic_error 析构（堆消息串 free → ·sub_66B034 基类释放）
{
  *this = &std::logic_error::`vftable';
  if ( (unsigned int)*(this + 9) >= 0x10 )
    j__free(*(this + 4));  // free this+4
  *(this + 9) = (void *)15;
  *(this + 8) = nullptr;  // this+8 = 空指针
  *((uint8_t *)this + 16) = 0;  // this 偏移 16 字节 = 0
  return sub_66B034(this);  // 调 exception 基类析构：装虚表并在 +8 非 0 时 free(+4) 缓冲
}



// ------------------------------------------------------------
// 0x4017E0 sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
// ·0x401AA0 大型对象 +268 处调用（vector 成员）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4017E0(int this)  // 函数 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
{
  void **fld_4; // esi
  void **i; // edi

  fld_4 = *(void ***)(this + 4);
  if ( fld_4 != nullptr )  // 若 fld_4 非空
  {
    for ( i = *(void ***)(this + 8); fld_4 != i; ++fld_4 )
      sub_41B010(fld_4);  // 调 sub_41B010
    j__free(*(void **)(this + 4));  // free this+4
  }
  *(uint32_t *)(this + 4) = 0;  // this+4（uint32 槽）= 0
  *(uint32_t *)(this + 8) = 0;  // this+8（uint32 槽）= 0
  *(uint32_t *)(this + 12) = 0;  // this+12（uint32 槽）= 0
}



// ------------------------------------------------------------
// 0x401830 sub_401830
// ------------------------------------------------------------
// 【解读】
//   std::length_error("vector<T> too long") 抛出器 —— MSVC vector::reserve 模板实例的溢出路径。
// ------------------------------------------------------------
void /*noreturn*/ sub_401830()
{
  size_t nLen; // eax
  size_t v1; // [esp+0h] [ebp-50h] BYREF
  char v2; // [esp+4h] [ebp-4Ch]
  int v3; // [esp+14h] [ebp-3Ch]
  int v4; // [esp+18h] [ebp-38h]
  uint32_t pExceptionObject[13]; // [esp+1Ch] [ebp-34h] BYREF

  v4 = 15;  // 临时串容量 15
  v3 = 0;
  v2 = 0;
  nLen = strlen("vector<T> too long");  // CRT 字符串长度（逐字节扫描到 NUL）
  sub_4015C0(&v1, "vector<T> too long", nLen);  // 【std::string构造赋值】
  pExceptionObject[12] = 0;
  sub_401740(pExceptionObject, &v1);  // 构造异常对象
  pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
}



// ------------------------------------------------------------
// 0x4018B0 sub_4018B0 —— std::logic_error 拷贝构造（exception 基类拷贝 + ·sub_4014D0 消息串深拷贝）
// ·0x401920 length_error 拷贝的中间层。
// ------------------------------------------------------------
int /*thiscall*/ sub_4018B0(int this, size_t *pArg2)  // 函数 std::logic_error 拷贝构造（exception 基类拷贝 + ·sub_4014D0 消息串深拷贝）
{
  exception::exception((exception *)this, (const struct exception *)pArg2);
  *(uint32_t *)this = &std::logic_error::`vftable';
  *(uint32_t *)(this + 36) = 15;  // this+36（uint32 槽）= 15
  *(uint32_t *)(this + 32) = 0;  // this+32（uint32 槽）= 0
  *(uint8_t *)(this + 16) = 0;  // this 偏移 16 清 0
  sub_4014D0((size_t *)(this + 12), pArg2 + 3, 0, 0xFFFFFFFF);  // 调 sub_4014D0
  return this;
}



// ------------------------------------------------------------
// 0x401920 sub_401920 —— std::length_error 拷贝构造（·sub_4018B0 + 覆写 length_error::vftable）
// 与 ·sub_4018B0 同构（差异: 末行改挂 length_error 虚表）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_401920(uint32_t *this, size_t *pArg2)  // 函数 std::length_error 拷贝构造（·sub_4018B0 + 覆写 length_error::vftable）
{
  sub_4018B0((int)this, pArg2);  // 调 sub_4018B0
  *this = &std::length_error::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x401950 sub_401950 —— 指针 vector::reserve(n) 模板实例（new(4n)，起/止/容量三指针就位）
// n=0 直接返回 0；n > 0x3FFFFFFF 走 ·0x401830 抛 vector<T> too long。
// ------------------------------------------------------------
char /*thiscall*/ sub_401950(uint32_t *this, unsigned int uArg2)  // 函数 指针 vector::reserve(n) 模板实例（new(4n)，起/止/容量三指针就位）
{
  char *pMem; // eax

  *(this + 1) = 0;  // this+1 清 0
  *(this + 2) = 0;  // this+2 清 0
  *(this + 3) = 0;  // this+3 清 0
  if ( uArg2 == 0 )  // 若 uArg2 == 0
    return 0;
  if ( uArg2 > 0x3FFFFFFF )
    sub_401830(this);  // 调 sub_401830
  pMem = (char *)operator new(4 * uArg2);
  *(this + 3) = &pMem[4 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x4019A0 sub_4019A0 —— 指针 vector 三字段清零（起/止/容量 = 0）
// vector 默认构造尾段。
// ------------------------------------------------------------
void /*thiscall*/ sub_4019A0(uint32_t *this)  // 函数 指针 vector 三字段清零（起/止/容量 = 0）
{
  *(this + 1) = 0;  // this+1 清 0
  *(this + 2) = 0;  // this+2 清 0
  *(this + 3) = 0;  // this+3 清 0
}



// ------------------------------------------------------------
// 0x4019B0 sub_4019B0 —— 大型管理对象构造（0x164 字节；挂 off_6C1588 虚表 + 两处 CNTimer 子对象 + clong 子对象）
// ★ 崩溃链角色名宿主: WinMain 中 new(0x164) 后赋 dword_79C0C0；崩溃回调经 +113 取角色名覆写报告名。
// 内嵌两个 CNTimer 子对象（+48/+80，各挂 off_6C2B88）与 +248 clong 子对象；尾调 ·sub_41FDC0。
// ------------------------------------------------------------
char */*thiscall*/ sub_4019B0(char *this)  // 函数 大型管理对象构造（0x164 字节；挂 off_6C1588 虚表 + 两处 CNTimer 子对象 + clong 子对象）
{
  uint32_t *pThis_F8; // edi

  *(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)this = &off_6C1588;  // vftable = off_6C1588
  *(this + 52) = 0;  // this+52 清 0
  *((uint32_t *)this + 12) = &off_6C2B88;  // this 偏移 48 = 接口/vftable off_6C2B88
  *((uint32_t *)this + 14) = 0;  // this 偏移 56 清 0
  *(this + 60) = 1;  // this+60 = 1
  *(this + 62) = 0;  // this+62 清 0
  *(this + 61) = 0;  // this+61 清 0
  *((uint32_t *)this + 18) = 0;  // this 偏移 72 清 0
  *((uint32_t *)this + 17) = 0;  // this 偏移 68 清 0
  *((uint32_t *)this + 16) = 0;  // this 偏移 64 清 0
  *(this + 84) = 0;  // this+84 清 0
  *((uint32_t *)this + 20) = &off_6C2B88;  // this 偏移 80 = 接口/vftable off_6C2B88
  *((uint32_t *)this + 22) = 0;  // this 偏移 88 清 0
  *(this + 92) = 1;  // this+92 = 1
  *(this + 94) = 0;  // this+94 清 0
  *(this + 93) = 0;  // this+93 清 0
  *((uint32_t *)this + 26) = 0;  // this 偏移 104 清 0
  *((uint32_t *)this + 25) = 0;  // this 偏移 100 清 0
  *((uint32_t *)this + 24) = 0;  // this 偏移 96 清 0
  pThis_F8 = this + 248;
  sub_41A630((unsigned int)(this + 248));  // 调 sub_41A630
  *pThis_F8 = &clong::`vftable';
  *((uint32_t *)this + 68) = 0;  // this 偏移 272 清 0
  *((uint32_t *)this + 69) = 0;  // this 偏移 276 清 0
  *((uint32_t *)this + 70) = 0;  // this 偏移 280 清 0
  *((uint32_t *)this + 88) = 0;  // this 偏移 352 清 0
  sub_41FDC0((int)this);  // 调 sub_41FDC0
  return this;
}



// ------------------------------------------------------------
// 0x401AA0 sub_401AA0 —— 大型管理对象析构（·sub_420070 全局关停链 + +268 vector 释放 + 各子对象虚表逐段回归 IObject）
// 与 ·0x4019B0 成对: +268 指针 vector 经 ·sub_4017E0 释放、+248 clong 经 ·sub_41A580 收尾，
// +48/+80 两 CNTimer 槽与对象头依次回写 nengine::IObject::vftable。
// ------------------------------------------------------------
char /*thiscall*/ sub_401AA0(uint32_t *this)  // 函数 大型管理对象析构（·sub_420070 全局关停链 + +268 vector 释放 + 各子对象虚表逐段回归 IObject）
{
  *this = &off_6C1588;  // vftable = off_6C1588
  sub_420070();  // 调 sub_420070
  sub_4017E0((int)(this + 67));  // 调 sub_4017E0
  sub_41A580(this + 62);
  *(this + 20) = &nengine::IObject::`vftable';  // this 偏移 20 = IObject vftable
  *((uint8_t *)this + 84) = 0;  // this 偏移 84 字节 = 0
  *(this + 12) = &nengine::IObject::`vftable';  // this 偏移 12 = IObject vftable
  *((uint8_t *)this + 52) = 0;  // this 偏移 52 字节 = 0
  *this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  return 0;
}



// ============================================================
// SECTION 0x401B20 — 程序入口 WinMain 与全局初始化链（崩溃回调注册 / 随机播种 / 子系统聚合初始化）
// ============================================================
// ------------------------------------------------------------
// 0x401B20 _WinMain@16
// ------------------------------------------------------------
// 【解读】
//   ★ WinMain 入口:
//     sub_402170(0, hInstance, off_77F284[0], off_77F288[0]) —— 崩溃上报上下文初始化
//       （off_77F284/288 数据对 = 上报目标串【推断：URL/主机名】）；
//     RegisterExceptionCallback(sub_401110) —— 崩溃报告链入口；
//     timeGetTime 播种 srand + malloc(rand()%100000) 哨兵分配；
//     初始化链: sub_403340（数学表+声音+日志对象）→ sub_401090（NIS::Http 等）→
//       sub_403400 → sub_4037C0（主管理器 dword_79C0A0/C0C0）；
//     sub_4048F0 = 单实例检测（FindWindowA 命中 → SetForegroundWindow 唤醒旧实例）；
//     sub_404360 = 主消息循环；退出时 sub_4010E0 清理。
// ------------------------------------------------------------
int /*stdcall*/ WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  DWORD Time; // eax
  size_t nRand; // esi
  void *pMem; // ebx
  const CHAR *v7; // eax
  char *pMem2; // eax
  char *pObj; // eax
  int v11; // [esp-14h] [ebp-20h]

  sub_402170(0, hInstance, off_77F284[0], off_77F288[0]);  // 【对 *.dmp / *.trc / *.zip 各调一次】
  RegisterExceptionCallback(sub_401110);  // 注册异常回调 sub_401110（崩溃链入口）
  Time = timeGetTime();  // CRT 取系统毫秒计时（winmm）
  srand(Time);  // timeGetTime 播种 srand
  nRand = rand() % 100000;  // CRT 伪随机数（LCG 递推）
  pMem = malloc(nRand);  // malloc 哨兵分配
  memset(pMem, 0, nRand);  // memset 清零
  if ( sub_403340() < 0 )  // sub_403340 数学表+声音+日志对象初始化
    return 1;  // 失败返回 1
  if ( sub_401090() < 0 )  // sub_401090 NIS::Http 初始化
    return 1;  // 失败返回 1
  sub_403400();  // sub_403400 初始化
  if ( sub_4037C0(nullptr, (int)&dword_79C0A0) < 0 )  // sub_4037C0 建主管理器 dword_79C0A0
    return 1;  // 失败返回 1
  v11 = sub_422E70(20001);  // v11 = 资源文本 20001（窗口类名）
  v7 = (const CHAR *)sub_422E70(20001);  // v7 = 同一文本
  if ( sub_4048F0((int)hInstance, v7, v11, 0, 124, 124, 1) < 0 )  // sub_4048F0 单实例检测 + 建窗
  {
    sub_4010E0();  // 失败：sub_4010E0 清理
    return 1;
  }
  sub_402AE0(lpCmdLine);  // sub_402AE0 登记命令行
  ShowWindow(*(HWND *)(dword_79C0A0 + 16), 5);  // ShowWindow 显示主窗口 (5 = SW_SHOW)
  pMem2 = (char *)operator new(0x164u);  // pMem2 = new 0x164
  if ( pMem2 != nullptr )  // 分配成功
    pObj = sub_4019B0(pMem2);  // pObj = sub_4019B0 构造引擎对象
  else  // 否则分支
    pObj = nullptr;
  dword_79C0C0 = (int)pObj;  // dword_79C0C0 = 引擎对象
  if ( (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 4))(pObj, dword_79C0A0) == 1 )  // 调 vt+4 槽初始化（传主管理器）返回 1
    sub_404360(dword_79C0A0);  // sub_404360 主消息循环
  if ( dword_79C0C0 != 0 )  // 引擎对象非空
    (**(void (/*thiscall*/ ***)(int, int))dword_79C0C0)(dword_79C0C0, 1);  // 调虚表首项(对象, 1) 释放
  dword_79C0C0 = 0;  // dword_79C0C0 清 0
  sub_4010E0();  // sub_4010E0 退出清理
  if ( pMem != nullptr )  // 哨兵内存非空
    free(pMem);
  return 0;
}



// ------------------------------------------------------------
// 0x401C90 sub_401C90 —— 六字段清零构造（this+0..+20 全部置 0）
// socket_ime.cpp 3611 以 this+6 调用 —— 网络对象子块初始化【推断】。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_401C90(uint32_t *this)  // 函数 六字段清零构造（this+0..+20 全部置 0）
{
  *this = 0;  // this[0] 清 0
  *(this + 1) = 0;  // this[1] 清 0
  *(this + 2) = 0;  // this[2] 清 0
  *(this + 3) = 0;  // this[3] 清 0
  *(this + 4) = 0;  // this[4] 清 0
  *(this + 5) = 0;  // this[5] 清 0
  return this;
}



// ------------------------------------------------------------
// 0x401CB0 sub_401CB0 —— 临界区初始化（InitializeCriticalSection 转发，返回 0）
// socket_ime.cpp 3650 以 this+24 调用 —— 网络对象同步原语【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_401CB0(LPCRITICAL_SECTION lpCriticalSection)  // 函数 临界区初始化（InitializeCriticalSection 转发，返回 0）
{
  InitializeCriticalSection(lpCriticalSection);  // InitializeCriticalSection 初始化临界区
  return 0;
}



// ------------------------------------------------------------
// 0x401D30 sub_401D30 —— base64 输出长度计算（4n/3 加权 + 76 列折行补齐 + CRLF 行数 + 尾 2 字节）
// pszArg2 位0 = 不补等号填充、位1 = 不加 CRLF；·0x401DA0 编码前用它校验调用方缓冲够不够。
// ------------------------------------------------------------
int /*cdecl*/ sub_401D30(int nArg1, char pszArg2)  // 函数 base64 输出长度计算（4n/3 加权 + 76 列折行补齐 + CRLF 行数 + 尾 2 字节）
{
  int v2; // ecx
  int v3; // eax
  int v4; // edx
  int result; // eax

  v2 = 4 * nArg1 / 3;  // v2 = 4n/3（base64 主体长度）
  if ( (pszArg2 & 1) == 0 )  // 不补等号填充
    v2 += nArg1 % 3;  // v2 += n%3
  v3 = v2 / 76;  // v3 = v2/76（折行数）
  if ( v2 % 76 != 0 )  // 有余数
  {
    v4 = v2 % 76 % 4;  // v4 = 末行长度 % 4
    if ( v4 != 0 )  // 非 4 整
      v2 += 4 - v4;  // 补齐到 4 的倍数
  }
  result = v2 + 2 * v3 + 2;  // result = v2 + 2×折行数 + 2（含 CRLF 长度）
  if ( (pszArg2 & 2) != 0 )  // 位1 = 不加 CRLF
    return v2;
  return result;
}



// ------------------------------------------------------------
// 0x401DA0 sub_401DA0
// ------------------------------------------------------------
// 【解读】
//   base64 编码器（127 行，标准字母表；由 0x4020F0 计算输出缓冲长度后调用）。
// ------------------------------------------------------------
int /*cdecl*/ sub_401DA0(uint8_t *uArg1, int nArg2, uint8_t *uArg3, uint32_t *uArg4, char pszArg5)
{
  uint8_t *uArg12; // esi
  uint8_t *pBuf; // edi
  int v7; // ebx
  int v8; // ecx
  int v9; // eax
  int i; // edx
  int v11; // ecx
  uint8_t *v12; // esi
  unsigned int v13; // ecx
  uint8_t *v14; // edi
  uint8_t *v15; // edi
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  unsigned int v20; // eax
  int j; // esi
  unsigned int pBuf2; // edx
  int v24; // [esp+Ch] [ebp-14h]
  int v25; // [esp+1Ch] [ebp-4h]
  int v26; // [esp+28h] [ebp+8h]

  uArg12 = uArg1;
  if ( uArg1 == nullptr )  // uArg1 为空
    return 0;
  pBuf = uArg3;  // pBuf = 输出起点
  if ( uArg3 == nullptr || uArg4 == nullptr || *uArg4 < sub_401D30(nArg2, pszArg5) )  // 输出/长度指针空或缓冲不足
    return 0;
  v7 = 0;  // v7 = 已写 0
  v26 = 0;
  v25 = 0;  // v25 = 0（行号）
  v24 = nArg2 % 3;  // v24 = n%3（尾组）
  v8 = 4 * (nArg2 / 3) / 76;  // v8 = 整行数
  v9 = 19;  // v9 = 19（每行 76 字符/4 = 19 组）
  if ( v8 >= 0 )  // 整行数 >= 0
  {
    do  // 逐行循环
    {
      if ( v25 == v8 )  // 末行
        v9 = 4 * (nArg2 / 3) % 76 / 4;  // v9 = 末行组数
      if ( v9 > 0 )  // 本行组数 > 0
      {
        for ( i = v9; i != 0; --i )  // 逐组 i
        {
          v11 = uArg12[1] | (*uArg12 << 8);  // v11 = 取 2 字节拼 16 位
          v12 = uArg12 + 1;  // v12 = 源前进
          v13 = (v12[1] | (v11 << 8)) << 8;  // v13 = 3 字节拼 24 位
          *pBuf = byte_6C1610[v13 >> 26];  // pBuf[0] = 字母表[v13>>26]（高 6 位）
          v13 <<= 6;
          pBuf[1] = byte_6C1610[v13 >> 26];  // pBuf[1] = 次 6 位
          uArg12 = v12 + 2;  // uArg12 前进 3 字节
          v13 <<= 6;
          v14 = pBuf + 2;
          *v14++ = byte_6C1610[v13 >> 26];  // pBuf[2] = 第 3 组 6 位
          *v14 = byte_6C1610[(v13 >> 20) & 0x3F];  // pBuf[3] = 第 4 组 6 位
          pBuf = v14 + 1;  // pBuf = 前进 4
        }
        v7 = v26;
        v8 = 4 * (nArg2 / 3) / 76;  // 重载整行数
      }
      v7 += 4 * v9;  // v7 += 4×组数
      v26 = v7;
      if ( (pszArg5 & 2) == 0 )  // 不加 CRLF
      {
        *pBuf = 13;  // 写 CR \r
        v15 = pBuf + 1;
        *v15 = 10;  // 写 LF \n
        pBuf = v15 + 1;
        v7 += 2;
        v26 = v7;
      }
      ++v25;  // 行号 ++
    }
    while ( v25 <= v8 );  // 未到末行继续
    if ( v7 != 0 && (pszArg5 & 2) == 0 )  // 末行非空且加 CRLF
    {
      pBuf -= 2;  // 回退多余 CRLF
      v7 -= 2;
    }
  }
  if ( v24 != 0 )  // 尾组非空
  {
    v16 = v24 + 1;  // v16 = v24+1（尾组输出字符数）
    if ( v24 != -1 )
    {
      v17 = 0;
      if ( v24 > 0 )  // 尾组 > 0
        v17 = *uArg12++;  // v17 = 取第 1 字节并前进
      v18 = v17 << 8;
      if ( v24 > 1 )  // 尾组 > 1
      {
        v18 |= *uArg12;  // v18 |= 第 2 字节
        v16 = v24 + 1;
        ++uArg12;  // 源前进
      }
      v19 = v18 << 8;
      if ( v24 > 2 )  // 尾组 > 2
        v19 |= *uArg12;  // v19 |= 第 3 字节
      v20 = v19 << 8;
      if ( v16 > 0 )
      {
        for ( j = v16; j != 0; --j )  // 逐字符 j
        {
          *pBuf++ = byte_6C1610[v20 >> 26];  // pBuf++ = 字母表[v20>>26]
          v20 <<= 6;
        }
      }
      v7 += v16;
      if ( (pszArg5 & 1) == 0 )  // 不补等号
      {
        pBuf2 = 4 - v16;  // pBuf2 = 4 - v16（补等号数）
        if ( 4 - v16 > 0 )  // 需补
          memset(pBuf, 0x3Du, pBuf2);  // memset 补 0x3D（=）
        v7 += pBuf2;
      }
    }
  }
  *uArg4 = v7;  // *uArg4 = 输出长度 v7
  return 1;
}


// ============================================================
// SECTION 0x401F80 — ★★ 崩溃报告链：旧转储清理 → 命名 → dmp 占位 → 7z 打包 DNF_DUMP.zip → base64 → NIS::Http 上报
// ============================================================
// ------------------------------------------------------------
// 0x401F80 sub_401F80
// ------------------------------------------------------------
// 【解读】
//   旧转储清理：FindFirstFileA 循环 DeleteFileA（跳过 "."/".." 与目录位 0x10）。
//   0x402170 对 "*.dmp" / "*.trc" / "*.zip" 各调一次 —— 启动时清空上次残留。
// ------------------------------------------------------------
int /*cdecl*/ sub_401F80(LPCSTR lpFileName)  // 【崩溃报告链：旧转储清理 → 命名 → dmp 占位 → 7z 打包 DNF_DUMP…】
{
  int result; // eax
  HANDLE hFindFile; // [esp+0h] [ebp-148h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+4h] [ebp-144h] BYREF
  int dword_796E502; // [esp+144h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 = dword_796E50（栈检）
  result = (int)FindFirstFileA(lpFileName, &FindFileData);  // FindFirstFileA 查找首个匹配文件
  hFindFile = (HANDLE)result;  // hFindFile = 搜索句柄
  if ( result != -1 )  // 找到文件（非 INVALID_HANDLE_VALUE）
  {
    result = 1;
    do  // do 循环体
    {  // 遍历
      if ( strcmp(FindFileData.cFileName, ".") != 0  // 非 . 
        && strcmp(FindFileData.cFileName, (const char *)&word_6C1650) != 0  // 非 ..（word_6C1650 备份串）
        && (FindFileData.dwFileAttributes & 0x10) != 1 )  // 非目录（属性位 0x10）
      {
        DeleteFileA(FindFileData.cFileName);  // DeleteFileA 删除该文件
        result = FindNextFileA(hFindFile, &FindFileData);  // FindNextFileA 继续
      }
    }
    while ( result != 0 );  // 循环直到无更多
  }
  return result;
}



// ------------------------------------------------------------
// 0x402030 sub_402030
// ------------------------------------------------------------
// 【解读】
//   转储文件名三元组生成:
//     this+386 ← "%s_%s.dmp"；this+646 ← "%s_%s.trc"；this+906 ← "DNF_DUMP.zip"；
//     前缀 = 角色名(this+75) + "_" + %08x timeGetTime 实例号(this+24)。
// ------------------------------------------------------------
int /*thiscall*/ sub_402030(int this)
{
  const char *pThis_18; // edi
  const char *pThis_4B; // ebx

  pThis_18 = (const char *)(this + 24);  // pThis_18 = this+24（实例号串）
  pThis_4B = (const char *)(this + 75);  // pThis_4B = this+75（角色名串）
  sprintf((char *const)(this + 386), "%s_%s.dmp", (const char *)(this + 75), (const char *)(this + 24));  // sprintf %s_%s.dmp 到 this+386
  sprintf((char *const)(this + 646), "%s_%s.trc", pThis_4B, pThis_18);  // sprintf %s_%s.trc 到 this+646
  return sprintf((char *const)(this + 906), "DNF_DUMP.zip");  // sprintf DNF_DUMP.zip 到 this+906
}



// ------------------------------------------------------------
// 0x402080 sub_402080
// ------------------------------------------------------------
// 【解读】
//   设置崩溃报告角色名（strncpy 0x32=50 字节 → this+75）并重生成文件名三元组。崩溃回调 ③ 调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_402080(char *this, char *Source)
{
  strncpy(this + 75, Source, 0x32u);  // strncpy 角色名到 this+75（限 50）
  return sub_402030((int)this);  // sub_402030 重生成文件名三元组
}



// ------------------------------------------------------------
// 0x4020B0 sub_4020B0
// ------------------------------------------------------------
// 【解读】
//   写 dmp 占位文件（fopen(this+386,"w") + fprintf + fclose），内容 = 异常回调入参串。崩溃回调 ④ 调用。
// ------------------------------------------------------------
FILE */*thiscall*/ sub_4020B0(const char *this, char *Format)
{
  FILE *result; // eax
  FILE *pFile; // esi

  result = fopen(this + 386, "w");  // fopen this+386 写模式
  pFile = result;  // pFile = 句柄
  if ( result != nullptr )  // 打开成功
  {
    fprintf(result, Format);  // fprintf 写 Format（异常入参串）
    return (FILE *)fclose(pFile);  // fclose
  }
  return result;
}



// ------------------------------------------------------------
// 0x4020F0 sub_4020F0
// ------------------------------------------------------------
// 【解读】
//   base64 输出长度计算: len = 4n/3 + n/3；再按 76 列折行补齐（+4-(len%76%4)）
//   并加 CRLF×2/76 行与尾 2 字节 → sub_401DA0(数据, n, 输出, &len, 0)。
// ------------------------------------------------------------
int /*stdcall*/ sub_4020F0(uint8_t *uArg1, uint8_t *uArg2, int nArg3)
{
  int nArg32; // esi
  int v4; // ecx
  int v5; // edx

  nArg32 = nArg3;  // nArg32 = nArg3（数据长度）
  v4 = nArg3 % 3 + 4 * nArg3 / 3;  // v4 = n%3 + 4n/3
  if ( v4 % 76 != 0 )  // 折行后需补齐
  {
    v5 = v4 % 76 % 4;  // v5 = 末行 % 4
    if ( v5 != 0 )  // 非 4 整
      v4 += 4 - v5;  // 补齐到 4 的倍数
  }
  nArg3 = v4 + 2 * ((nArg3 % 3 + 4 * nArg3 / 3) / 76) + 2;  // nArg3 = 总长 + 2×折行数 + 2
  return sub_401DA0(uArg1, nArg32, uArg2, &nArg3, 0);  // sub_401DA0 base64 编码
}



// ------------------------------------------------------------
// 0x402170 sub_402170
// ------------------------------------------------------------
// 【解读】
//   ★ 崩溃上报上下文初始化（WinMain 首个调用）:
//     this+0/+4 ← a2/a3（回调登记）；上报目标串 a5 → this+126；
//     timeGetTime → "%08x" 实例号 → this+24；角色名占位 "_NONE" → this+75；
//     sub_402030 生成文件名三元组；随后 sub_401F80 清理旧 *.dmp/*.trc/*.zip。
// ------------------------------------------------------------
int /*thiscall*/ sub_402170(char *this, int nArg2, int nArg3, int nArg4, char *pszArg5)  // 【对 *.dmp / *.trc / *.zip 各调一次】
{
  char *pszArg52; // eax
  int pThis_7E; // edx
  char v8; // cl
  DWORD Time; // eax

  *(uint32_t *)this = nArg2;  // this[0] = nArg2（回调上下文）
  pszArg52 = pszArg5;
  *((uint32_t *)this + 1) = nArg3;
  pThis_7E = this + 126 - pszArg5;  // pThis_7E = 目标偏移（this+126 - src）
  do  // 逐字符复制（自实现 strcpy）
  {
    v8 = *pszArg52;  // v8 = 当前字符
    pszArg52[pThis_7E] = *pszArg52;  // 写目标
    ++pszArg52;  // 源前进
  }
  while ( v8 != 0 );  // 直到遇 \0
  Time = timeGetTime();  // CRT 取系统毫秒计时（winmm）
  sprintf(this + 24, "%08x", Time);  // sprintf %08x 实例号到 this+24
  sprintf(this + 75, "_NONE");  // sprintf _NONE 角色名占位到 this+75
  sub_402030((int)this);  // sub_402030 生成文件名三元组
  sub_401F80("*.dmp");  // 【崩溃报告链：旧转储清理 → 命名 → dmp 占位 → 7z 打包 DNF_DUMP…】
  sub_401F80("*.trc");  // 【崩溃报告链：旧转储清理 → 命名 → dmp 占位 → 7z 打包 DNF_DUMP…】
  return sub_401F80("*.zip");  // 【崩溃报告链：旧转储清理 → 命名 → dmp 占位 → 7z 打包 DNF_DUMP…】
}



// ------------------------------------------------------------
// 0x4021F0 sub_4021F0 —— std::string::append(str, pos, n) 模板实例（含自引用重叠路径）
// 与 ·sub_4014D0 同族（差异: 追加语义，目标长度 = 原长 + n）。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4021F0(size_t *this, uint32_t *pArg2, unsigned int uArg3, unsigned int uArg4)  // 函数 std::string::append(str, pos, n) 模板实例（含自引用重叠路径）
{
  unsigned int uArg42; // edi
  unsigned int fld_e5; // esi
  unsigned int fld_e6; // eax
  bool v8; // zf
  uint32_t *v9; // esi
  char *pThis_1; // edx
  char *pThis_12; // eax
  bool fld_e62; // cf
  unsigned int fld_e52; // [esp+1Ch] [ebp+10h]

  if ( pArg2[5] < uArg3 )  // pos > 源长度
    std::_String_base::_Xran((std::_String_base *)this);  // 抛 _Xran 越界
  uArg42 = uArg4;  // uArg42 = 追加数
  if ( pArg2[5] - uArg3 < uArg4 )  // 超出剩余则截断
    uArg42 = pArg2[5] - uArg3;
  if ( -1 - *(this + 5) <= uArg42 )  // 长度溢出
    std::_String_base::_Xlen((std::_String_base *)this);  // 抛 _Xlen
  if ( uArg42 == 0 )  // 追加 0 个
    return this;
  fld_e5 = uArg42 + *(this + 5);  // fld_e5 = 追加后总长
  fld_e52 = fld_e5;  // fld_e52 = 总长
  if ( fld_e5 == -1 )  // 总长为 -1（溢出）
    std::_String_base::_Xlen((std::_String_base *)this);  // 抛 _Xlen
  fld_e6 = *(this + 6);  // fld_e6 = 当前容量
  if ( fld_e6 < fld_e5 )  // 容量不足
  {
    sub_4012B0(this, fld_e5, *(this + 5));  // sub_4012B0 缓冲重分配
    v8 = fld_e5 == 0;  // v8 = 新长是否为 0
    goto LABEL_12;  // 跳 LABEL_12
  }
  v8 = fld_e5 == 0;  // v8 = 新长为 0
  if ( fld_e5 != 0 )  // 新长非 0
  {
LABEL_12:
    if ( !v8 )  // 非空情形
    {
      if ( pArg2[6] < 0x10u )  // 源串容量 < 16（内联）
        v9 = pArg2 + 1;  // v9 = pArg2+1 内联缓冲
      else  // 否则分支
        v9 = (uint32_t *)pArg2[1];  // v9 = 堆上缓冲
      pThis_1 = (char *)(this + 1);  // pThis_1 = this+1
      if ( *(this + 6) < 0x10 )  // 容量 < 16
        pThis_12 = (char *)(this + 1);  // pThis_12 = this+1
      else  // 否则分支
        pThis_12 = *(char **)pThis_1;  // pThis_12 = 堆上缓冲
      qmemcpy(&pThis_12[*(this + 5)], (char *)v9 + uArg3, uArg42);  // qmemcpy 追加源子串
      fld_e62 = *(this + 6) < 0x10;  // fld_e62 = 容量 < 16
      *(this + 5) = fld_e52;  // this+5 = 新长度
      if ( !fld_e62 )  // 容量 >= 16
        pThis_1 = *(char **)pThis_1;  // pThis_1 = 堆上缓冲
      pThis_1[fld_e52] = 0;  // 补串尾 0
    }
    return this;
  }
  *(this + 5) = 0;  // this+5 清 0
  if ( fld_e6 < 0x10 )  // 容量 < 16
    *((uint8_t *)this + 4) = 0;  // 内联首字节清 0
  else  // 否则分支
    *(uint8_t *)*(this + 1) = 0;  // 堆上首字节清 0
  return this;
}



// ------------------------------------------------------------
// 0x4022F0 sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
// pos 落在自身缓冲内时转 ·sub_4021F0 追加子串；0x402410 为其 C 串包装。
// ------------------------------------------------------------
size_t */*fastcall*/ sub_4022F0(std::_String_base *this, int nArg2, char *pszArg3, unsigned int uArg4)  // 函数 std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
{
  unsigned int pThis_6; // esi
  char *pThis_4; // eax
  char *pThis_42; // eax
  std::_String_base *pThis_43; // ecx
  unsigned int pThis_62; // eax
  bool v12; // zf
  char *pThis_44; // eax
  bool pThis_63; // cf
  unsigned int pThis_5; // [esp+18h] [ebp+Ch]

  pThis_6 = *((uint32_t *)this + 6);  // pThis_6 = this+6 容量
  if ( pThis_6 < 0x10 )  // 容量 < 16
    pThis_4 = (char *)this + 4;  // pThis_4 = this+4 内联
  else  // 否则分支
    pThis_4 = *((char **)this + 1);  // pThis_4 = 堆上缓冲
  if ( pszArg3 >= pThis_4 )  // 插入源落在本串缓冲内
  {
    pThis_42 = (char *)this + 4;  // pThis_42 = this+4
    pThis_43 = pThis_6 < 0x10 ? (std::_String_base *)((char *)this + 4) : *(std::_String_base **)pThis_42;  // pThis_43 = 缓冲区指针
    if ( (char *)pThis_43 + *((uint32_t *)this + 5) > pszArg3 )  // 源在有效数据内
    {
      if ( pThis_6 >= 0x10 )  // 容量 >= 16
        pThis_42 = *(char **)pThis_42;  // pThis_42 = 堆上缓冲
      return sub_4021F0((size_t *)this, this, pszArg3 - pThis_42, uArg4);  // 转 sub_4021F0 追加子串
    }
  }
  if ( -1 - *((uint32_t *)this + 5) <= uArg4 )  // 长度溢出
    std::_String_base::_Xlen(this);  // 抛 _Xlen
  if ( uArg4 == 0 )  // 插入 0 个
    return (size_t *)this;
  pThis_5 = uArg4 + *((uint32_t *)this + 5);  // pThis_5 = 插入后总长
  if ( pThis_5 == -1 )  // 总长为 -1
    std::_String_base::_Xlen(this);  // 抛 _Xlen
  pThis_62 = *((uint32_t *)this + 6);  // pThis_62 = 当前容量
  if ( pThis_62 < pThis_5 )  // 容量不足
  {
    sub_4012B0(this, pThis_5, *((uint32_t *)this + 5));  // sub_4012B0 重分配
    v12 = pThis_5 == 0;  // v12 = 新长为 0
    goto LABEL_19;  // 跳 LABEL_19
  }
  v12 = pThis_5 == 0;  // v12 = 新长为 0
  if ( pThis_5 != 0 )  // 新长非 0
  {
LABEL_19:
    if ( !v12 )  // 非空
    {
      if ( *((uint32_t *)this + 6) < 0x10u )  // 容量 < 16
        pThis_44 = (char *)this + 4;  // pThis_44 = this+4
      else  // 否则分支
        pThis_44 = *((char **)this + 1);  // pThis_44 = 堆上缓冲
      qmemcpy(&pThis_44[*((uint32_t *)this + 5)], pszArg3, uArg4);  // qmemcpy 拷贝插入内容
      pThis_63 = *((uint32_t *)this + 6) < 0x10u;  // pThis_63 = 容量 < 16
      *((uint32_t *)this + 5) = pThis_5;  // this+5 = 新长度
      if ( !pThis_63 )  // 容量 >= 16
      {
        *(uint8_t *)(*((uint32_t *)this + 1) + pThis_5) = 0;  // 堆上补串尾 0
        return (size_t *)this;
      }
      *((uint8_t *)this + pThis_5 + 4) = 0;  // 内联补串尾 0
    }
    return (size_t *)this;
  }
  *((uint32_t *)this + 5) = 0;  // this+5 清 0
  if ( pThis_62 < 0x10 )  // 容量 < 16
    *((uint8_t *)this + 4) = 0;  // 内联首清 0
  else  // 否则分支
    **((uint8_t **)this + 1) = 0;  // 堆上首清 0
  return (size_t *)this;
}



// ------------------------------------------------------------
// 0x402410 sub_402410 —— std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
// insert 的 C 串入口。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_402410(std::_String_base *this, char *pszArg2)  // 函数 std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
{
  return sub_4022F0(this, 0, pszArg2, strlen(pszArg2));  // 转 sub_4022F0 插入 C 串
}



// ------------------------------------------------------------
// 0x402440 sub_402440
// ------------------------------------------------------------
// 【解读】
//   ★★ 崩溃打包上报本体（崩溃报告链第 5 步）:
//     ① fopen("DNF.trc","rb") → 读全量 → 复制为 %s_%s.trc（this+646）；
//     ② sprintf(Buffer, "a -tzip %s %s %s", zip, dmp, trc) →
//        ShellExecuteExA("7z", "open", ".\", fMask=320 SEE_MASK_NOCLOSEPROCESS) ——
//        ★ 调用系统 7-Zip 命令行把 dmp+trc 打包成 DNF_DUMP.zip；
//     ③ GetExitCodeProcess 轮询 259(STILL_ACTIVE) + Sleep(0x3E8=1000ms) 等待打包完成；
//     ④ 读 zip 全量 → base64 编码（0x4020F0/0x401DA0）→ 拼 " content=" 前缀 →
//        sub_4028C0 HTTP POST 上报（上报目标 = this+126）。
// ------------------------------------------------------------
void /*thiscall*/ sub_402440(int this)
{
  FILE *pFile; // eax
  FILE *pFile3; // esi
  int v4; // eax
  size_t v5; // eax
  size_t v6; // edi
  FILE *pFile2; // eax
  FILE *pFile5; // esi
  FILE *pFile4; // eax
  FILE *pFile6; // esi
  int nPos; // edi
  char *pMem3; // esi
  int v13; // edx
  SHELLEXECUTEINFOA pExecInfo; // [esp+Ch] [ebp-158h] BYREF
  size_t v15; // [esp+48h] [ebp-11Ch] BYREF
  void *Block; // [esp+4Ch] [ebp-118h]
  int v17; // [esp+5Ch] [ebp-108h]
  unsigned int v18; // [esp+60h] [ebp-104h]
  void *pMem; // [esp+64h] [ebp-100h]
  DWORD ExitCode; // [esp+68h] [ebp-FCh] BYREF
  void *pMem2; // [esp+6Ch] [ebp-F8h]
  char Buffer[200]; // [esp+70h] [ebp-F4h] BYREF
  size_t v23; // [esp+138h] [ebp-2Ch] BYREF
  void *v24; // [esp+13Ch] [ebp-28h]
  int v25; // [esp+14Ch] [ebp-18h]
  unsigned int v26; // [esp+150h] [ebp-14h]
  int dword_796E502; // [esp+154h] [ebp-10h]
  int v28; // [esp+160h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 = dword_796E50（栈检）
  pFile = fopen("DNF.trc", "rb");  // fopen DNF.trc 读模式
  pFile3 = pFile;  // pFile3 = 句柄
  pMem2 = pFile;  // pMem2 = 句柄
  if ( pFile != nullptr )  // 打开成功
  {
    v4 = _fileno(pFile);  // _fileno 取文件号
    v5 = _filelength(v4);  // _filelength 取文件长度
    v6 = v5;  // v6 = 长度
    if ( v5 != 0 )  // 长度非 0
    {
      pMem = operator new(v5);  // pMem = new 长度缓冲
      sub_66BD5A(pMem, v6, 1u, pFile3);  // 【fread封装】
      pFile2 = fopen((const char *)(this + 646), "wb");  // fopen this+646（%s_%s.trc）写模式
      pFile5 = pFile2;  // pFile5 = 句柄
      if ( pFile2 != nullptr )  // 打开成功
      {
        sub_66BC25(pMem, v6, 1u, pFile2);  // 写 pMem 到目标 trc
        fclose(pFile5);
      }
      pFile3 = (FILE *)pMem2;  // pFile3 复位
    }
    fclose(pFile3);  // fclose trc 源
  }
  sprintf(  // sprintf 拼 7z 命令行 a -tzip <zip> <dmp> <trc>
    Buffer,
    "a -tzip %s %s %s",
    (const char *)(this + 906),
    (const char *)(this + 386),
    (const char *)(this + 646));
  memset(&pExecInfo, 0, sizeof(pExecInfo));  // pExecInfo 清零
  pExecInfo.hwnd = nullptr;
  pExecInfo.nShow = 0;  // nShow = 0（隐藏）
  pExecInfo.cbSize = 60;  // cbSize = 60
  pExecInfo.lpFile = "7z";  // lpFile = 7z
  pExecInfo.lpParameters = Buffer;  // lpParameters = 命令行
  pExecInfo.lpDirectory = ".\\";
  pExecInfo.fMask = 320;  // fMask = 320（SEE_MASK_NOCLOSEPROCESS）
  pExecInfo.lpVerb = "open";  // lpVerb = open
  ShellExecuteExA(&pExecInfo);  // ShellExecuteExA 执行 7z
  GetExitCodeProcess(pExecInfo.hProcess, &ExitCode);  // GetExitCodeProcess 取退出码
  while ( ExitCode == 259 )  // 退出码 == 259（STILL_ACTIVE 仍在运行）
  {
    Sleep(0x3E8u);  // Sleep 1000ms 等待
    GetExitCodeProcess(pExecInfo.hProcess, &ExitCode);  // 再取退出码
  }
  pFile4 = fopen((const char *)(this + 906), "rb");  // fopen DNF_DUMP.zip 读模式
  pFile6 = pFile4;  // pFile6 = 句柄
  if ( pFile4 != nullptr )  // 打开成功
  {
    fseek(pFile4, 0, 2);  // fseek 到文件尾
    nPos = ftell(pFile6);  // nPos = ftell 文件大小
    fseek(pFile6, 0, 0);  // fseek 回文件头
    pMem2 = operator new(nPos);  // pMem2 = new nPos 缓冲
    sub_66BD5A(pMem2, nPos, 1u, pFile6);  // 【fread封装】
    fclose(pFile6);
    pMem3 = (char *)operator new(2 * nPos);  // pMem3 = new 2×nPos 缓冲（base64 输出）
    sub_4020F0((uint8_t *)pMem2, pMem3, nPos);  // sub_4020F0 base64 编码
    v26 = 15;  // v26 = 15（串容量）
    v25 = 0;
    LOBYTE(v24) = 0;  // v24 低字节 = 0
    sub_4015C0(&v23, " content=", 9u);  // 【std::string构造赋值】
    v28 = 0;
    sub_4022F0((std::_String_base *)&v23, v13, pMem3, strlen(pMem3));  // sub_4022F0 拼 base64 内容
    v18 = 15;
    v17 = 0;
    LOBYTE(Block) = 0;  // Block 低字节 = 0
    sub_4015C0(&v15, (uint8_t *)(this + 126), strlen((const char *)(this + 126)));  // 【std::string构造赋值】
    LOBYTE(v28) = 1;  // v28 低字节 = 1
    sub_4028C0(&v15, &v23);  // sub_4028C0 HTTP POST 上报
    if ( v18 >= 0x10 )  // 串容量 >= 16
      j__free(Block);  // free 目标串
    j_j__free(pMem3);  // free pMem3（base64）
    j_j__free(pMem2);  // free pMem2（zip）
    if ( v26 >= 0x10 )  // 串容量 >= 16
      j__free(v24);  // free 内容串
  }
}



// ------------------------------------------------------------
// 0x402740 sub_402740 —— HTTP 会话句柄关闭（InternetCloseHandle + 句柄置 0）
// 即 ·0x4010D0 的转发目标；WinInet 句柄唯一释放点之一。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_402740(uint32_t *this)  // 函数 HTTP 会话句柄关闭（InternetCloseHandle + 句柄置 0）
{
  BOOL result; // eax
  void *fld_e1; // [esp-4h] [ebp-8h]

  fld_e1 = (void *)*(this + 1);  // fld_e1 = this[1] 句柄
  *this = &off_6C16EC;  // vftable off_6C16EC
  result = InternetCloseHandle(fld_e1);  // InternetCloseHandle 关闭
  *(this + 1) = 0;  // this[1] 清 0
  return result;
}



// ------------------------------------------------------------
// 0x402780 sub_402780
// ------------------------------------------------------------
// 【解读】
//   WinInet 会话构造: InternetOpenA("NIS::Http", 0/PRECONFIG, 0,0,0)。
//   "NIS::Http" = 上报代理标识（NIS = Neople Internet Service【推断】）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_402780(uint32_t *this)
{
  uint32_t *pThis_2; // ecx

  *this = &off_6C16EC;  // vftable off_6C16EC
  *(this + 1) = 0;  // this[1] 清 0
  pThis_2 = this + 2;
  *pThis_2 = 0;  // this[2] 清 0
  pThis_2[1] = 0;  // this[3] 清 0
  *(this + 1) = InternetOpenA("NIS::Http", 0, nullptr, nullptr, 0);  // InternetOpenA 建会话（NIS::Http）
  return this;
}



// ------------------------------------------------------------
// 0x4027B0 sub_4027B0 —— HTTP 会话对象析构壳（·sub_402740 + 低位置位 free）
// 与 ·sub_401150 同构（差异: 基类为 off_6C16EC 网络对象）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4027B0(uint32_t *Block, char pszArg2)  // 函数 HTTP 会话对象析构壳（·sub_402740 + 低位置位 free）
{
  sub_402740(Block);  // sub_402740 关闭会话
  if ( (pszArg2 & 1) != 0 )  // pszArg2 位 0
    j__free(Block);  // free
  return Block;
}



// ------------------------------------------------------------
// 0x4027E0 unknown_libname_2
// ------------------------------------------------------------
// Microsoft VisualC 2-14/net runtime
uint32_t */*thiscall*/ unknown_libname_2(uint32_t *this)
{
  if ( *(this + 6) < 0x10u )  // 容量 < 16（内联）
    return this + 1;  // 返回 this+1 内联
  else  // 否则分支
    return (uint32_t *)*(this + 1);  // 返回堆上缓冲
}



// ------------------------------------------------------------
// 0x4027F0 sub_4027F0
// ------------------------------------------------------------
// 【解读】
//   URL 子串定位（memchr 首字符 + memcmp 全串推进）—— HTTP server/object 分隔查找。
// ------------------------------------------------------------
int /*thiscall*/ sub_4027F0(uint32_t *this, char *pszArg2, uint64_t uArg3)  // 函数 v4 = sub_4027F0 定位 http 之后斜杠（长度 7）；sub_4027F0 —— v4 = sub_4027F0 定位 …
{
  int result; // eax
  unsigned int v4; // esi
  unsigned int fld_e5; // ebx
  unsigned int v6; // ebx
  size_t v7; // ebx
  unsigned int fld_e6; // edx
  char *pThis_1; // ecx
  char *v10; // eax
  char *pThis_122; // ecx
  char *v13; // [esp+8h] [ebp-4h]
  char *pThis_12; // [esp+18h] [ebp+Ch]

  v4 = HIDWORD(uArg3);  // v4 = HIDWORD(uArg3)（子串长度）
  result = uArg3;  // result = uArg3 低 32 位（起始偏移）
  if ( uArg3 > (unsigned int)*(this + 5) )  // 起始偏移 > 串长
  {
    fld_e5 = *(this + 5);  // fld_e5 = 串长
    if ( (unsigned int)uArg3 >= fld_e5 )  // 起始 >= 串长
      return -1;  // 返回 -1（未找到）
    v6 = fld_e5 - uArg3;  // v6 = 剩余长度
    if ( HIDWORD(uArg3) > v6 )  // 子串长度 > 剩余
      return -1;  // 返回 -1
    v7 = 1 - HIDWORD(uArg3) + v6;  // v7 = 可搜长度
    fld_e6 = *(this + 6);  // fld_e6 = 容量
    pThis_1 = (char *)(this + 1);  // pThis_1 = this+1
    pThis_12 = pThis_1;
    if ( fld_e6 >= 0x10 )  // 容量 >= 16
      pThis_1 = *(char **)pThis_1;  // pThis_1 = 堆上缓冲
    v13 = &pThis_1[result];  // v13 = 起始位置
    v10 = (char *)memchr(&pThis_1[result], *pszArg2, v7);  // memchr 找首字符
    if ( v10 != nullptr )  // 找到
    {
      while ( memcmp(v10, pszArg2, v4) != 0 )  // memcmp 全串比较不等
      {
        v7 = v7 + v13 - v10 - 1;  // v7 收缩
        v13 = v10 + 1;  // v13 = 下一位置
        v10 = (char *)memchr(v10 + 1, *pszArg2, v7);  // 继续 memchr
        if ( v10 == nullptr )  // 未找到
          return -1;  // 返回 -1
        v4 = HIDWORD(uArg3);  // v4 复位
      }
      pThis_122 = pThis_12;  // pThis_122 = 基址
      if ( *(this + 6) >= 0x10u )  // 容量 >= 16
        pThis_122 = *(char **)pThis_12;  // pThis_122 = 堆上缓冲
      return v10 - pThis_122;  // 返回偏移 v10 - 基址
    }
    else  // 否则分支
    {
      return -1;  // 未找到
    }  // 返回 -1
  }
  return result;
}



// ------------------------------------------------------------
// 0x4028C0 sub_4028C0
// ------------------------------------------------------------
// 【解读】
//   ★ HTTP POST 上报执行器:
//     拆分 server/object（sub_4027F0 memchr/memchr 定位）→ InternetConnectA →
//     HttpOpenRequestA("POST") → 头 "Content-Type: application/x-www-form-urlencoded" →
//     HttpSendRequestA（body = base64 后的 DNF_DUMP.zip）→ InternetCloseHandle。
// ------------------------------------------------------------
char /*thiscall*/ sub_4028C0(HINTERNET *this, size_t *pArg2, uint32_t *pArg3)
{
  unsigned int v4; // edi
  const CHAR *v5; // eax
  void *fld_e1; // ebx
  const CHAR *p_lpszObjectName; // eax
  void *v8; // esi
  DWORD nLen; // kr00_4
  void *v10; // ecx
  CHAR szHeaders[64]; // [esp+Ch] [ebp-88h] BYREF
  size_t v13; // [esp+4Ch] [ebp-48h] BYREF
  LPCSTR lpszServerName[5]; // [esp+50h] [ebp-44h] BYREF
  unsigned int v15; // [esp+64h] [ebp-30h]
  size_t v16; // [esp+68h] [ebp-2Ch] BYREF
  LPCSTR lpszObjectName; // [esp+6Ch] [ebp-28h] BYREF
  int v18; // [esp+7Ch] [ebp-18h]
  unsigned int v19; // [esp+80h] [ebp-14h]
  int dword_796E502; // [esp+84h] [ebp-10h]
  int v21; // [esp+90h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 = dword_796E50（栈检）
  v4 = sub_4027F0(pArg2, "/", 0x100000007uLL);  // v4 = sub_4027F0 定位 http 之后斜杠（长度 7）
  v15 = 15;
  lpszServerName[4] = nullptr;
  LOBYTE(lpszServerName[0]) = 0;  // lpszServerName[0] 清 0
  sub_4014D0(&v13, pArg2, 7u, v4 - 7);  // sub_4014D0 取 server 部分（跳过 http:// 7 字节）
  v21 = 0;
  v19 = 15;
  v18 = 0;
  LOBYTE(lpszObjectName) = 0;  // lpszObjectName 清 0
  sub_4014D0(&v16, pArg2, v4, 0xFFFFFFFF);  // sub_4014D0 取 object 部分（/ 之后）
  v5 = lpszServerName[0];  // v5 = server 串
  if ( v15 < 0x10 )  // 容量 < 16（内联）
    v5 = (const CHAR *)lpszServerName;  // v5 = 内联缓冲
  fld_e1 = InternetConnectA(*(this + 1), v5, 0x50u, szPassword, szPassword, 3u, 0, 0);  // InternetConnectA 连接 (端口 80)
  p_lpszObjectName = lpszObjectName;  // p_lpszObjectName = object 串
  if ( v19 < 0x10 )  // 容量 < 16
    p_lpszObjectName = (const CHAR *)&lpszObjectName;  // p_lpszObjectName = 内联
  v8 = HttpOpenRequestA(fld_e1, "POST", p_lpszObjectName, nullptr, nullptr, nullptr, 0x80000000, 0);  // HttpOpenRequestA POST 打开请求
  sprintf(szHeaders, "Content-Type: application/x-www-form-urlencoded");  // sprintf Content-Type 头
  nLen = strlen(szHeaders);  // nLen = 头长度
  if ( pArg3[6] < 0x10u )  // pArg3 容量 < 16
    v10 = pArg3 + 1;  // v10 = pArg3+1 内联
  else  // 否则分支
    v10 = (void *)pArg3[1];  // v10 = 堆上缓冲
  HttpSendRequestA(v8, szHeaders, nLen, v10, pArg3[5]);  // HttpSendRequestA 发送（body = base64 数据）
  InternetCloseHandle(v8);  // InternetCloseHandle 关请求
  InternetCloseHandle(fld_e1);  // InternetCloseHandle 关连接
  if ( v19 >= 0x10 )  // server 容量 >= 16
    j__free((void *)lpszObjectName);  // free server 串
  v19 = 15;
  v18 = 0;
  LOBYTE(lpszObjectName) = 0;  // lpszObjectName 清 0
  if ( v15 >= 0x10 )  // v15 >= 16
    j__free((void *)lpszServerName[0]);  // free 堆上 server
  return 1;
}



// ============================================================
// SECTION 0x402A50 — 字符串参数包 / CString 数组 / vsprintf 格式化打包工具
// ============================================================
// ------------------------------------------------------------
// 0x402A50 sub_402A50 —— 字符串参数包构造（+8/+12/+16 三字段清零）
// off_6C38F4 = nengine::CNString 虚表族；0x403440/0x402FB0/0x4030C0 均以裸三字段形式内嵌复用。
// ------------------------------------------------------------
int /*thiscall*/ sub_402A50(uint32_t *this)  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
{
  *(this + 2) = 0;  // this+2 清 0
  *(this + 3) = 0;  // this+3 清 0
  *(this + 4) = 0;  // this+4 清 0
  return 0;
}



// ------------------------------------------------------------
// 0x402A60 sub_402A60 —— 字符串包释放（+8 缓冲 free + +4/+8/+12/+16 四字段清零）
// 被 0x403560 析构链对 +52/+72/+92 三段逐一调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_402A60(int this)  // 函数 字符串包释放（+8 缓冲 free + +4/+8/+12/+16 四字段清零）
{
  if ( *(uint32_t *)(this + 8) != 0 )  // 若 this 偏移 8 非 0
    j_j__free(*(void **)(this + 8));  // free this+8
  *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
  *(uint32_t *)(this + 8) = 0;  // this+8（uint32 槽）= 0
  *(uint32_t *)(this + 12) = 0;  // this+12（uint32 槽）= 0
  *(uint32_t *)(this + 16) = 0;  // this+16（uint32 槽）= 0
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x402A90 sub_402A90 —— 字符串包缓冲重分配（free 旧缓冲 → operator new(n+1) → 起止指针同步）
// 能力字段 +16 = 容量、+12 = 当前长度；失败返回 0x80000000。
// ------------------------------------------------------------
int /*thiscall*/ sub_402A90(int this, int pArg2)  // 函数 字符串包缓冲重分配（free 旧缓冲 → operator new(n+1) → 起止指针同步）
{
  void *pMem; // eax

  if ( *(uint32_t *)(this + 8) != 0 )  // 若 this 偏移 8 非 0
    j_j__free(*(void **)(this + 8));  // free this+8
  *(uint32_t *)(this + 12) = pArg2;  // this+12 = pArg2
  *(uint32_t *)(this + 16) = pArg2;  // this+16 = pArg2
  *(uint32_t *)(this + 8) = 0;  // this+8（uint32 槽）= 0
  pMem = operator new(pArg2 + 1);
  *(uint32_t *)(this + 8) = pMem;  // this+8 = pMem
  return pMem != nullptr ? 1 : -2147483640;
}



// ------------------------------------------------------------
// 0x402AE0 sub_402AE0 —— 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
// ★ 字符串包主赋值；0x4048F0 用它将窗口类名/标题存入 +52/+72，0x402FB0 拷构造也走它。
// ------------------------------------------------------------
int /*thiscall*/ sub_402AE0(int this, const char *pArg2)  // 函数 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
{
  int result; // eax
  unsigned int nLen; // edi

  if ( pArg2 == nullptr )  // 若 pArg2 为空
    return 0x80000000;  // 返回 0x80000000（失败）
  nLen = strlen(pArg2);  // CRT 字符串长度（逐字节扫描到 NUL）
  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
  {
    if ( *(uint32_t *)(this + 8) != 0 )  // 若 this 偏移 8 非 0
      j_j__free(*(void **)(this + 8));  // free this+8
    *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
    *(uint32_t *)(this + 8) = 0;  // this+8（uint32 槽）= 0
    *(uint32_t *)(this + 12) = 0;  // this+12（uint32 槽）= 0
    *(uint32_t *)(this + 16) = 0;  // this+16（uint32 槽）= 0
LABEL_8:  // LABEL_8（跳转目标）
    result = sub_402A90(this, nLen);  // 调 字符串包缓冲重分配（free 旧缓冲 → operator new(n+1) → 起止指针同步）
    if ( result < 0 )  // 若 result < 0
      return result;
    goto LABEL_9;  // 跳转 LABEL_9
  }
  if ( nLen >= *(uint32_t *)(this + 16) )
    goto LABEL_8;  // 跳转 LABEL_8
LABEL_9:  // LABEL_9（跳转目标）
  *(uint32_t *)(this + 12) = nLen;  // this+12 = nLen
  qmemcpy(*(void **)(this + 8), pArg2, nLen);  // 调 qmemcpy
  *(uint8_t *)(nLen + *(uint32_t *)(this + 8)) = 0;
  *(uint8_t *)(this + 4) = 1;
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x402B80 sub_402B80 —— 字符串包追接 C 串（余量足则就地追接，不足先 new 暂存后扩容回填）
// +12 为当前长度、+16 为容量；pArg2 为空返回 0x80000000。
// ------------------------------------------------------------
int /*thiscall*/ sub_402B80(int this, const char *pArg2)  // 函数 字符串包追接 C 串（余量足则就地追接，不足先 new 暂存后扩容回填）
{
  int result; // eax
  unsigned int nLen; // eax
  unsigned int fld_10; // ecx
  int fld_C; // edx
  void *pMem; // eax
  unsigned int fld_C2; // ecx
  void *Block; // [esp+8h] [ebp-Ch]
  unsigned int fld_102; // [esp+Ch] [ebp-8h]
  unsigned int nLen2; // [esp+10h] [ebp-4h]

  if ( pArg2 == nullptr )  // 若 pArg2 为空
    return 0x80000000;  // 返回 0x80000000（失败）
  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return sub_402AE0(this, pArg2);  // 调 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
  nLen = strlen(pArg2);  // CRT 字符串长度（逐字节扫描到 NUL）
  fld_10 = *(uint32_t *)(this + 16);
  fld_C = *(uint32_t *)(this + 12);
  nLen2 = nLen;
  fld_102 = fld_10;
  if ( fld_C + nLen < fld_10 )
  {
    qmemcpy((void *)(fld_C + *(uint32_t *)(this + 8)), pArg2, nLen);  // 调 qmemcpy
    fld_C2 = nLen + *(uint32_t *)(this + 12);
    *(uint32_t *)(this + 12) = fld_C2;  // this+12 = fld_C2
    *(uint8_t *)(fld_C2 + *(uint32_t *)(this + 8)) = 0;
  }
  else  // 否则分支
  {
    pMem = operator new(fld_10 + 1);
    qmemcpy(pMem, *(const void **)(this + 8), *(uint32_t *)(this + 16));  // 调 qmemcpy
    *((uint8_t *)pMem + *(uint32_t *)(this + 16)) = 0;
    Block = pMem;
    result = sub_402A90(this, fld_102 + nLen2);  // 调 字符串包缓冲重分配（free 旧缓冲 → operator new(n+1) → 起止指针同步）
    if ( result < 0 )  // 若 result < 0
      return result;
    qmemcpy(*(void **)(this + 8), Block, fld_102);  // 调 qmemcpy
    qmemcpy((void *)(fld_102 + *(uint32_t *)(this + 8)), pArg2, nLen2);  // 调 qmemcpy
    *(uint8_t *)(*(uint32_t *)(this + 8) + *(uint32_t *)(this + 12)) = 0;
    if ( Block != nullptr )  // 若 Block 非空
    {
      j_j__free(Block);
      return 1;  // 返回 1（成功）
    }
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x402CB0 sub_402CB0 —— 字符串包在偏移 nArg2 处插入 C 串（越界或未分配则转 ·sub_402B80 追接）
// 自缓冲扩容路径用 strlen 复核暂存块长度【推断: 暂存块无独立长度字段】。
// ------------------------------------------------------------
int /*thiscall*/ sub_402CB0(int this, int nArg2, const char *pArg3)  // 函数 字符串包在偏移 nArg2 处插入 C 串（越界或未分配则转 ·sub_402B80 追接）
{
  int result; // eax
  unsigned int nLen; // eax
  int fld_C; // ecx
  int nArg22; // edx
  unsigned int v8; // eax
  void *Block; // [esp+8h] [ebp-8h]
  unsigned int nLen2; // [esp+Ch] [ebp-4h]

  if ( pArg3 == nullptr )  // 若 pArg3 为空
    return 0x80000000;  // 返回 0x80000000（失败）
  nLen = strlen(pArg3);  // CRT 字符串长度（逐字节扫描到 NUL）
  fld_C = *(uint32_t *)(this + 12);
  nArg22 = nArg2;
  nLen2 = nLen;
  if ( nArg2 >= fld_C || *(uint8_t *)(this + 4) == 0 )
    return sub_402B80(this, pArg3);  // 调 字符串包追接 C 串（余量足则就地追接，不足先 new 暂存后扩容回填）
  v8 = fld_C + nLen;
  if ( v8 < *(uint32_t *)(this + 16) )
  {
    *(uint32_t *)(this + 12) = v8;  // this+12 = v8
  }
  else  // 否则分支
  {
    Block = operator new(fld_C + 1);
    qmemcpy(Block, *(const void **)(this + 8), *(uint32_t *)(this + 12));  // 调 qmemcpy
    result = sub_402A90(this, nLen2 + *(uint32_t *)(this + 12));  // 调 字符串包缓冲重分配（free 旧缓冲 → operator new(n+1) → 起止指针同步）
    if ( result < 0 )  // 若 result < 0
      return result;
    qmemcpy(*(void **)(this + 8), Block, strlen((const char *)Block));  // 调 qmemcpy
    if ( Block != nullptr )  // 若 Block 非空
      j_j__free(Block);
    nArg22 = nArg2;
  }
  qmemcpy(  // 调 qmemcpy
    (void *)(nArg22 + *(uint32_t *)(this + 8) + nLen2),
    (const void *)(*(uint32_t *)(this + 8) + nArg22),
    *(uint32_t *)(this + 12) - nArg22);
  qmemcpy((void *)(nArg22 + *(uint32_t *)(this + 8)), pArg3, nLen2);  // 调 qmemcpy
  *(uint8_t *)(*(uint32_t *)(this + 8) + *(uint32_t *)(this + 12)) = 0;
  return 0x80000000;  // 返回 0x80000000（失败）
}



// ------------------------------------------------------------
// 0x402DE0 sub_402DE0 —— 字符串包按范围抹除（前段左移 + 尾段 memset 清零，同步收缩 +12 长度）
// nArg2 超长时改为尾部逐字节清零循环。
// ------------------------------------------------------------
int /*thiscall*/ sub_402DE0(int this, signed int nArg2, signed int nArg3)  // 函数 字符串包按范围抹除（前段左移 + 尾段 memset 清零，同步收缩 +12 长度）
{
  signed int fld_C; // ecx
  signed int nArg33; // esi
  signed int i; // eax
  int fld_8; // ecx
  unsigned int nArg32; // ebx
  signed int v10; // ecx

  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return 0x80000000;  // 返回 0x80000000（失败）
  fld_C = *(uint32_t *)(this + 12);
  if ( fld_C == 0 )  // 若 fld_C == 0
    return 1;  // 返回 1（成功）
  if ( nArg2 < fld_C )
  {
    nArg32 = nArg3;
    v10 = fld_C - nArg2;
    if ( v10 < nArg3 )
      nArg32 = v10;
    qmemcpy((void *)(*(uint32_t *)(this + 8) + nArg2), (const void *)(*(uint32_t *)(this + 8) + nArg2 + nArg32), v10 - nArg32);  // 调 qmemcpy
    memset((void *)(*(uint32_t *)(this + 12) + *(uint32_t *)(this + 8) - nArg32), 0, nArg32);  // 调 memset
    *(uint32_t *)(this + 12) -= nArg32;
    return 0x80000000;  // 返回 0x80000000（失败）
  }
  nArg33 = nArg3;
  if ( nArg3 >= fld_C )  // 若 nArg3 >= fld_C
    nArg33 = fld_C;
  for ( i = 0; i < nArg33; *(uint8_t *)(fld_8 + *(uint32_t *)(this + 12) - 1) = 0 )
    fld_8 = *(uint32_t *)(this + 8) - i++;
  *(uint32_t *)(this + 12) -= nArg33;
  return 0x80000000;  // 返回 0x80000000（失败）
}



// ------------------------------------------------------------
// 0x402EA0 sub_402EA0 —— 字符串包单体字符替换（全量扫描，源字符 → 目标字符）
// 未分配或空串返回 0x80000000。
// ------------------------------------------------------------
int /*thiscall*/ sub_402EA0(int this, char pszArg2, char pszArg3)  // 函数 字符串包单体字符替换（全量扫描，源字符 → 目标字符）
{
  unsigned int v4; // edx
  uint8_t *fld_8; // eax

  if ( *(uint8_t *)(this + 4) == 0 || *(uint32_t *)(this + 12) == 0 )
    return 0x80000000;  // 返回 0x80000000（失败）
  v4 = 0;
  do  // do 循环体
  {
    fld_8 = (uint8_t *)(v4 + *(uint32_t *)(this + 8));
    if ( *fld_8 == pszArg2 )
      *fld_8 = pszArg3;  // 写指针 = pszArg3
    ++v4;  // v4 自增
  }
  while ( v4 < *(uint32_t *)(this + 12) );
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x402EF0 sub_402EF0 —— 字符串包 vsprintf 格式化写入（按 Format 串长预扩缓冲，再 vsprintf 填充）
// 字符串包格式化落地的核心；失败返回 0x80000000。
// ------------------------------------------------------------
int /*thiscall*/ sub_402EF0(int this, char *Format, va_list ArgList)  // 函数 字符串包 vsprintf 格式化写入（按 Format 串长预扩缓冲，再 vsprintf 填充）
{
  int result; // eax
  unsigned int nLen; // eax
  int nLen2; // edi
  char *fld_82; // [esp-10h] [ebp-18h]
  char *fld_8; // [esp-10h] [ebp-18h]

  if ( Format == nullptr )  // 若 Format 为空
    return 0x80000000;  // 返回 0x80000000（失败）
  nLen = strlen(Format);  // CRT 字符串长度（逐字节扫描到 NUL）
  nLen2 = nLen;
  if ( *(uint8_t *)(this + 4) != 0 )  // 若 this 偏移 4 非 0
  {
    if ( nLen < *(uint32_t *)(this + 16) || (result = sub_402A90(this, nLen)) >= 0 )  // 调 字符串包缓冲重分配（free 旧缓冲 → operator new(n+1) → 起止指针同步）
    {
      fld_8 = *(char **)(this + 8);
      *(uint32_t *)(this + 12) = nLen2;  // this+12 = nLen2
      vsprintf(fld_8, Format, ArgList);  // 调 vsprintf
      *(uint8_t *)(nLen2 + *(uint32_t *)(this + 8)) = 0;
      return 1;  // 返回 1（成功）
    }
  }
  else  // 否则分支
  {
    if ( *(uint32_t *)(this + 8) != 0 )  // 若 this 偏移 8 非 0
      j_j__free(*(void **)(this + 8));  // free this+8
    *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
    *(uint32_t *)(this + 8) = 0;  // this+8（uint32 槽）= 0
    *(uint32_t *)(this + 12) = 0;  // this+12（uint32 槽）= 0
    *(uint32_t *)(this + 16) = 0;  // this+16（uint32 槽）= 0
    result = sub_402A90(this, nLen2);  // 调 字符串包缓冲重分配（free 旧缓冲 → operator new(n+1) → 起止指针同步）
    if ( result >= 0 )  // 若 result >= 0
    {
      fld_82 = *(char **)(this + 8);
      *(uint32_t *)(this + 12) = nLen2;  // this+12 = nLen2
      vsprintf(fld_82, Format, ArgList);  // 调 vsprintf
      *(uint8_t *)(nLen2 + *(uint32_t *)(this + 8)) = 0;
      *(uint8_t *)(this + 4) = 1;
      return 1;  // 返回 1（成功）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x402FB0 sub_402FB0 —— 字符串包拷贝构造（挂 off_6C38F4 虚表 + 从源包 +8 缓冲 ·sub_402AE0 赋值）
// ·0x4030C0 空源分支的兜底路径。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_402FB0(uint8_t *this, int pArg2)  // 函数 字符串包拷贝构造（挂 off_6C38F4 虚表 + 从源包 +8 缓冲 ·sub_402AE0 赋值）
{
  *(this + 4) = 0;  // this+4 清 0
  *((uint32_t *)this + 2) = 0;  // this 偏移 8 清 0
  *((uint32_t *)this + 3) = 0;  // this 偏移 12 清 0
  *((uint32_t *)this + 4) = 0;  // this 偏移 16 清 0
  *(uint32_t *)this = &off_6C38F4;  // vftable = off_6C38F4
  sub_402AE0((int)this, *(const char **)(pArg2 + 8));  // 调 sub_402AE0
  return this;
}



// ------------------------------------------------------------
// 0x403010 sub_403010 —— 字符串包析构（+8 缓冲 free + 字段清零 + 回落 nengine::IObject::vftable）
// off_6C38F4 虚表族析构标准形态。
// ------------------------------------------------------------
void /*thiscall*/ sub_403010(uint32_t *this)  // 函数 字符串包析构（+8 缓冲 free + 字段清零 + 回落 nengine::IObject::vftable）
{
  void *fld_e2; // eax

  fld_e2 = (void *)*(this + 2);
  *this = &off_6C38F4;  // vftable = off_6C38F4
  if ( fld_e2 != nullptr )  // 若 fld_e2 非空
    j_j__free(fld_e2);
  *(this + 2) = 0;  // this+2 清 0
  *(this + 3) = 0;  // this+3 清 0
  *(this + 4) = 0;  // this+4 清 0
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  *this = &nengine::IObject::`vftable';  // vftable 复位 IObject
}



// ------------------------------------------------------------
// 0x403050 sub_403050 —— 字符串包析构壳（·sub_403010 + 低位置位 free）
// 与 ·sub_4036C0 同构族。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_403050(uint32_t *Block, char pszArg2)  // 函数 字符串包析构壳（·sub_403010 + 低位置位 free）
{
  sub_403010(Block);  // 调 sub_403010
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x403080 sub_403080 —— 字符串包预分配置空（·sub_402A90 扩容后置空串并标记 +4 有效）
// socket_ime.cpp 6835 以 (pArg2+5) / (len/5+5) 调用 —— 分包缓冲预留【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_403080(int this, int nArg2)  // 函数 字符串包预分配置空（·sub_402A90 扩容后置空串并标记 +4 有效）
{
  int result; // eax

  if ( *(uint8_t *)(this + 4) != 0 )  // 若 this 偏移 4 非 0
    return 0x80000000;  // 返回 0x80000000（失败）
  result = sub_402A90(this, nArg2);  // 调 字符串包缓冲重分配（free 旧缓冲 → operator new(n+1) → 起止指针同步）
  if ( result >= 0 )  // 若 result >= 0
  {
    **(uint8_t **)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;  // this+12（uint32 槽）= 0
    *(uint8_t *)(this + 4) = 1;
    return 1;  // 返回 1（成功）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4030C0 sub_4030C0 —— 字符串包子串拷贝构造（[nArg3, nArg3+nArg4) 切片到 pArg2；源未就绪走 ·sub_402FB0）
// socket_ime.cpp 7041 用于从长缓冲切片取首段（+2 字段）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4030C0(int this, uint8_t *pArg2, int nArg3, int nArg4)  // 函数 字符串包子串拷贝构造（[nArg3, nArg3+nArg4) 切片到 pArg2；源未就绪走 ·sub_402FB0）
{
  char fld_4; // al
  int fld_C; // ebx
  int v7; // esi
  char *pMem; // eax
  char *pMem2; // edi
  int v10; // eax
  int (/*thiscall*/ **v11)(void *, char); // [esp+8h] [ebp-28h] BYREF
  char v12; // [esp+Ch] [ebp-24h]
  char *pMem3; // [esp+10h] [ebp-20h]
  int fld_C2; // [esp+14h] [ebp-1Ch]
  int fld_C3; // [esp+18h] [ebp-18h]
  int v16; // [esp+1Ch] [ebp-14h]
  int pThis; // [esp+20h] [ebp-10h]
  int v18; // [esp+2Ch] [ebp-4h]

  pThis = this;
  v16 = 0;
  v12 = 0;
  v11 = &off_6C38F4;
  pMem3 = nullptr;  // pMem3 = 0/空
  fld_C2 = 0;
  fld_C3 = 0;
  fld_4 = *(uint8_t *)(this + 4);
  v18 = 0;
  if ( fld_4 != 0 )  // 若 fld_4 != 0
  {
    fld_C = *(uint32_t *)(this + 12);
    v7 = nArg3 <= 0 ? 0 : nArg3;
    if ( v7 + nArg4 < fld_C )
      fld_C = v7 + nArg4;
    fld_C2 = fld_C;
    fld_C3 = fld_C;
    pMem = (char *)operator new(fld_C + 1);
    pMem2 = pMem;
    pMem3 = pMem;
    if ( pMem != nullptr )  // 若 pMem 非空
    {
      *pMem = 0;  // 写指针 = 0
      fld_C2 = 0;
      v12 = 1;
    }
    v10 = nArg3 <= 0 ? 0 : nArg3;
    if ( v7 < v7 + fld_C )
    {
      do  // do 循环体
      {
        pMem2[v10 - v7] = *(uint8_t *)(v10 + *(uint32_t *)(pThis + 8));
        ++v10;  // v10 自增
      }
      while ( v10 < v7 + fld_C );
    }
    pMem2[fld_C] = 0;
    pArg2[4] = 0;
    LOBYTE(v18) = 1;
    *(uint32_t *)pArg2 = &off_6C38F4;
    *((uint32_t *)pArg2 + 2) = 0;
    *((uint32_t *)pArg2 + 3) = 0;
    *((uint32_t *)pArg2 + 4) = 0;
    sub_402AE0((int)pArg2, pMem2);  // 调 sub_402AE0
    if ( pMem2 != nullptr )  // 若 pMem2 非空
      j_j__free(pMem2);
    return pArg2;
  }
  else  // 否则分支
  {
    sub_402FB0(pArg2, (int)&v11);  // 调 sub_402FB0
    return pArg2;
  }
}



// ============================================================
// SECTION 0x4031E0 — 数学库与引擎子系统初始化（sin/cos/tan 表、rand 播种、随机数工具）
// ============================================================
// ------------------------------------------------------------
// 0x4031E0 sub_4031E0 —— 数学/随机子系统对象构造（挂 off_6C1748 虚表 + ·sub_4050F0 字段清零 + ·sub_405150 初始化）
// ·0x4032B0 以 new(0x80) 装配，登记全局 dword_79D078。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4031E0(uint8_t *this)  // 【数学库与引擎子系统初始化（sin/cos/tan 表、rand 播种、随机数工具）】
{
  *(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)this = off_6C1748;  // vftable off_6C1748
  sub_4050F0();  // sub_4050F0 字段清零
  sub_405150(this);  // sub_405150 初始化
  return this;
}



// ------------------------------------------------------------
// 0x403230 sub_403230 —— 数学子系统对象析构壳（·sub_403260 + 低位置位 free）
// 与 ·sub_4036C0 同构族。
// ------------------------------------------------------------
void */*thiscall*/ sub_403230(void *Block, char pszArg2)  // 函数 数学子系统对象析构壳（·sub_403260 + 低位置位 free）
{
  sub_403260();  // sub_403260 析构
  if ( (pszArg2 & 1) != 0 )  // pszArg2 位 0
    j__free(Block);  // free
  return Block;
}



// ------------------------------------------------------------
// 0x403260 sub_403260 —— 数学子系统对象析构（·sub_405160 批量 DeleteObject + 回落 nengine::IObject::vftable）
// 与 ·0x4031E0 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_403260(uint8_t *this)  // 函数 数学子系统对象析构（·sub_405160 批量 DeleteObject + 回落 nengine::IObject::vftable…
{
  int result; // eax

  *(uint32_t *)this = off_6C1748;  // vftable off_6C1748
  result = sub_405160();  // sub_405160 批量 DeleteObject
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *(this + 4) = 0;  // this+4 清 0
  return result;
}



// ------------------------------------------------------------
// 0x4032B0 sub_4032B0 —— 数学/随机子系统全局单例构造（dword_79D078 非空即返回 -2147483646）
// WinMain 经 ·sub_403340 初始化链调用；0x4010E0 退出时虚表槽 0 释放置 0。
// ------------------------------------------------------------
int sub_4032B0()  // 函数 数学/随机子系统全局单例构造（dword_79D078 非空即返回 -2147483646）
{
  uint8_t *pMem; // eax
  uint8_t *v2; // eax

  if ( dword_79D078 != 0 )  // dword_79D078 已存在
    return -2147483646;  // 返回 -2147483646
  pMem = operator new(0x80u);  // pMem = new 0x80
  if ( pMem == nullptr )  // 分配失败
    return -2147483640;  // 返回 -2147483640
  v2 = sub_4031E0(pMem);  // 【数学库与引擎子系统初始化（sin/cos/tan 表、rand 播种、随机数工具）】
  if ( v2 == nullptr )  // 构造失败
    return -2147483640;  // 返回 -2147483640
  dword_79D078 = (int)v2;  // dword_79D078 = 单例
  return 1;
}



// ------------------------------------------------------------
// 0x403340 sub_403340 —— 全局初始化聚合链（·sub_403840 日志容器 → ·sub_405950 三角函数表 → ·sub_405440 → ·sub_4032B0 → srand(timeGetTime) → ·sub_4051A0 帧时钟域）
// byte_79C560 为已初始化标志（重复调用返回 -2147483646）；WinMain 首个判错点。
// 任一环返回负值即中断并返回该值。
// ------------------------------------------------------------
int sub_403340()  // 函数 全局初始化聚合链（·sub_403840 日志容器 → ·sub_405950 三角函数表 → ·sub_405440 → ·sub_4…
{
  int result; // eax
  DWORD Time; // eax

  if ( byte_79C560 != 0 )  // byte_79C560 已初始化
    return -2147483646;  // 返回 -2147483646
  result = sub_403840();  // sub_403840 建日志容器
  if ( result >= 0 )  // 成功
  {
    result = sub_405950();  // sub_405950 三角函数表
    if ( result >= 0 )  // 成功
    {
      result = sub_405440();  // 调 三角函数表构建（6 块 new(0x5A0) = 各 360 槽）
      if ( result >= 0 )  // 成功
      {
        result = sub_4032B0();  // sub_4032B0 数学子系统单例
        if ( result >= 0 )  // 成功
        {
          Time = timeGetTime();  // CRT 取系统毫秒计时（winmm）
          srand(Time);  // srand 播种
          sub_4051A0();  // 【tick_domains_init】
          byte_79C560 = 1;  // byte_79C560 = 1（已初始化）
          return 1;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4033E0 sub_4033E0 —— 日志容器全局单例释放（dword_79C564 经虚表槽 0 析构并置 0）
// ·0x4010E0 关停链末段调用；与 ·sub_403840 构造、·sub_403400 取值器配套。
// ------------------------------------------------------------
int sub_4033E0()  // 函数 日志容器全局单例释放（dword_79C564 经虚表槽 0 析构并置 0）
{
  if ( dword_79C564 != 0 )  // dword_79C564 非空
  {
    (**(void (/*thiscall*/ ***)(int, int))dword_79C564)(dword_79C564, 1);  // 调虚表首项(对象, 1) 释放
    dword_79C564 = 0;  // dword_79C564 清 0
  }
  return 1;
}



// ------------------------------------------------------------
// 0x403400 sub_403400 —— 日志容器全局单例取值器（返回 dword_79C564，无副作用）
// 配套 ·sub_403840 构造 / ·sub_4033E0 释放。
// ------------------------------------------------------------
int sub_403400()  // 函数 日志容器全局单例取值器（返回 dword_79C564，无副作用）
{
  return dword_79C564;
}



// ------------------------------------------------------------
// 0x403410 sub_403410 —— 日志容器析构（挂 off_6C1750 + ·sub_6569D0 链表清空 + 缓冲 free）
// ·0x403840 所构造 0x10 字节容器的配套析构。
// ------------------------------------------------------------
void /*thiscall*/ sub_403410(uint32_t *this)  // 函数 日志容器析构（挂 off_6C1750 + ·sub_6569D0 链表清空 + 缓冲 free）
{
  uint32_t *pThis_1; // esi

  pThis_1 = this + 1;
  *this = off_6C1750;  // vftable off_6C1750
  sub_6569D0(this + 1);  // sub_6569D0 清链表
  j__free((void *)pThis_1[1]);  // free 缓冲
  pThis_1[1] = 0;  // pThis_1[1] 清 0
}



// ------------------------------------------------------------
// 0x403440 sub_403440 —— 事件/日志分发对象构造（挂 off_6C1754 + 三段字符串包 + 四条哨兵链 ·sub_425940 + ·sub_4044C0）
// ★ 引擎子系统基座: +52/+72/+92 三段字符串包（off_6C38F4 族）、+132/+144/+156/+168 四条哨兵链，
// 尾调 ·sub_4044C0 做状态初始化（含 CoInitialize）；0x4036F0 为其派生构造。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_403440(uint8_t *this, void *pArg2)  // 函数 事件/日志分发对象构造（挂 off_6C1754 + 三段字符串包 + 四条哨兵链 ·sub_425940 + ·sub_4044C0）
{
  *(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)this = &off_6C1754;  // vftable off_6C1754
  *((uint32_t *)this + 7) = pArg2;
  *(this + 56) = 0;  // this+56 清 0
  *((uint32_t *)this + 13) = &off_6C38F4;  // this[13] = 字符串包 vftable off_6C38F4
  sub_402A50((uint32_t *)this + 13);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  *(this + 76) = 0;  // this+76 清 0
  *((uint32_t *)this + 18) = &off_6C38F4;  // this[18] = 字符串包 vftable
  sub_402A50((uint32_t *)this + 18);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  *(this + 96) = 0;  // this+96 清 0
  *((uint32_t *)this + 23) = &off_6C38F4;  // this[23] = 字符串包 vftable
  sub_402A50((uint32_t *)this + 23);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  *(this + 120) = 0;  // this+120 清 0
  *((uint32_t *)this + 29) = off_6C174C;
  *((uint32_t *)this + 34) = sub_425940(this + 132);  // this[34] = sub_425940 建哨兵链 1
  *((uint32_t *)this + 35) = 0;  // this[35] 清 0
  *((uint32_t *)this + 37) = sub_425940(this + 144);  // this[37] = sub_425940 建哨兵链 2
  *((uint32_t *)this + 38) = 0;  // this[38] 清 0
  *((uint32_t *)this + 40) = sub_425940(this + 156);  // this[40] = sub_425940 建哨兵链 3
  *((uint32_t *)this + 41) = 0;  // this[41] 清 0
  *((uint32_t *)this + 43) = sub_425940(this + 168);  // this[43] = sub_425940 建哨兵链 4
  *((uint32_t *)this + 44) = 0;  // this[44] 清 0
  sub_4044C0(this);  // sub_4044C0 状态初始化
  return this;
}



// ------------------------------------------------------------
// 0x403550 sub_403550 —— 恒失败存根（固定返回 0x80000000）
// 占位虚槽；本文件内无调用者。
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_403550(int nArg1, int nArg2, int nArg3, int nArg4)  // 函数 恒失败存根（固定返回 0x80000000）
{
  return 0x80000000;  // 恒返回 0x80000000（占位）
}



// ------------------------------------------------------------
// 0x403560 sub_403560 —— 事件/日志分发对象析构（四哨兵链 ·sub_6569D0 清空 + ·sub_404560 收尾 + 三字符串包析构回落 IObject）
// 链 +132/+144/+156/+168 逐条清空并 free 存储；字符串包 +52/+72/+92 经 ·sub_402A60 析构。
// +116 槽回落 IObject::vftable；与 ·0x403440 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_403560(void **this)  // 函数 事件/日志分发对象析构（四哨兵链 ·sub_6569D0 清空 + ·sub_404560 收尾 + 三字符串包析构回落 IObject…
{
  int result; // eax

  *this = &off_6C1754;  // vftable off_6C1754
  sub_404560();  // sub_404560 状态回卷
  sub_6569D0(this + 42);  // sub_6569D0 清链 4
  j__free(*(this + 43));  // free 链 4 存储
  *(this + 43) = nullptr;  // this[43] 清 0
  sub_6569D0(this + 39);  // sub_6569D0 清链 3
  j__free(*(this + 40));  // free 链 3 存储
  *(this + 40) = nullptr;  // this[40] 清 0
  sub_6569D0(this + 36);  // sub_6569D0 清链 2
  j__free(*(this + 37));  // free 链 2 存储
  *(this + 37) = nullptr;  // this[37] 清 0
  sub_6569D0(this + 33);  // sub_6569D0 清链 1
  j__free(*(this + 34));  // free 链 1 存储
  *(this + 34) = nullptr;  // this[34] 清 0
  *(this + 29) = &nengine::IObject::`vftable';  // this[29] = IObject vftable
  *((uint8_t *)this + 120) = 0;  // this+120 清 0
  *(this + 23) = &off_6C38F4;
  sub_402A60((int)(this + 23));  // sub_402A60 析构字符串包 3
  *(this + 23) = &nengine::IObject::`vftable';  // this[23] = IObject vftable
  *((uint8_t *)this + 96) = 0;  // this+96 清 0
  *(this + 18) = &off_6C38F4;
  sub_402A60((int)(this + 18));  // sub_402A60 析构字符串包 2
  *(this + 18) = &nengine::IObject::`vftable';  // this[18] = IObject vftable
  *((uint8_t *)this + 76) = 0;  // this+76 清 0
  *(this + 13) = &off_6C38F4;
  result = sub_402A60((int)(this + 13));  // sub_402A60 析构字符串包 1
  *(this + 13) = &nengine::IObject::`vftable';  // this[13] = IObject vftable
  *((uint8_t *)this + 56) = 0;  // this+56 清 0
  *this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this+4 清 0
  return result;
}



// ------------------------------------------------------------
// 0x403690 sub_403690 —— 事件分发对象析构壳（·sub_403560 + 低位置位 free）
// 与 ·sub_403740 同构族。
// ------------------------------------------------------------
void **/*thiscall*/ sub_403690(void **Block, char pszArg2)  // 函数 事件分发对象析构壳（·sub_403560 + 低位置位 free）
{
  sub_403560(Block);  // sub_403560 析构
  if ( (pszArg2 & 1) != 0 )  // pszArg2 位 0
    j__free(Block);  // free
  return Block;
}



// ------------------------------------------------------------
// 0x4036C0 sub_4036C0 —— 日志容器析构壳（·sub_403410 + 低位置位 free）
// 与 ·sub_403690 同构族。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4036C0(uint32_t *Block, char pszArg2)  // 函数 日志容器析构壳（·sub_403410 + 低位置位 free）
{
  sub_403410(Block);  // sub_403410 析构
  if ( (pszArg2 & 1) != 0 )  // pszArg2 位 0
    j__free(Block);  // free
  return Block;
}



// ------------------------------------------------------------
// 0x4036F0 sub_4036F0 —— 事件分发对象派生构造（·sub_403440 基构造 → 覆写 off_6C1778 → ·sub_40B130 让 +28 槽清零）
// ·0x4037C0 以 new(0xB8) 装配并挂入 uArg2。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4036F0(uint8_t *this, void *pArg2)  // 函数 事件分发对象派生构造（·sub_403440 基构造 → 覆写 off_6C1778 → ·sub_40B130 让 +28 槽清零）
{
  sub_403440(this, pArg2);  // sub_403440 基构造
  *(uint32_t *)this = &off_6C1778;  // vftable off_6C1778（派生）
  sub_40B130(this);  // sub_40B130 让 +28 槽清零
  return this;
}



// ------------------------------------------------------------
// 0x403740 sub_403740 —— 事件分发派生对象析构壳（·sub_403770 + 低位置位 free）
// 与 ·sub_403690 同构族。
// ------------------------------------------------------------
void */*thiscall*/ sub_403740(void *Block, char pszArg2)  // 函数 事件分发派生对象析构壳（·sub_403770 + 低位置位 free）
{
  sub_403770();  // sub_403770 析构
  if ( (pszArg2 & 1) != 0 )  // pszArg2 位 0
    j__free(Block);  // free
  return Block;
}



// ------------------------------------------------------------
// 0x403770 sub_403770 —— 事件分发派生对象析构（先覆写 off_6C1778 → ·sub_404560 状态回卷 → ·sub_403560 基析构）
// 与 ·0x4036F0 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_403770(void **this)  // 函数 事件分发派生对象析构（先覆写 off_6C1778 → ·sub_404560 状态回卷 → ·sub_403560 基析构）
{
  *this = &off_6C1778;  // vftable off_6C1778
  sub_404560();  // sub_404560 状态回卷
  return sub_403560(this);  // 转 sub_403560 基析构
}



// ------------------------------------------------------------
// 0x4037C0 sub_4037C0 —— 事件分发对象工厂（Block 非空返回 -2147483639；否则 new(0xB8) + ·sub_4036F0 → *uArg2）
// WinMain 以 (nullptr, &dword_79C0A0) 调用 —— 主管理器诞生点，失败返回 -2147483640。
// ------------------------------------------------------------
int /*stdcall*/ sub_4037C0(void *Block, uint32_t *uArg2)  // 函数 事件分发对象工厂（Block 非空返回 -2147483639；否则 new(0xB8) + ·sub_4036F0 → *uArg2）
{
  uint8_t *pMem; // eax
  uint8_t *v4; // eax

  if ( Block != nullptr )  // Block 非空
    return -2147483639;  // 返回 -2147483639
  pMem = operator new(0xB8u);  // pMem = new 0xB8
  if ( pMem != nullptr )  // 分配成功
    v4 = sub_4036F0(pMem, nullptr);  // v4 = sub_4036F0 构造
  else  // 否则分支
    v4 = nullptr;
  *uArg2 = v4;  // *uArg2 = 对象
  return v4 != nullptr ? 1 : -2147483640;  // 成功返回 1 否则 -2147483640
}



// ------------------------------------------------------------
// 0x403840 sub_403840 —— 日志容器构造（new(0x10) + 挂 off_6C1750 + 哨兵链 ·sub_425940 + ·sub_6569D0 清空 → dword_79C564）
// ·sub_403340 初始化链首环。
// ------------------------------------------------------------
int sub_403840()  // 函数 日志容器构造（new(0x10) + 挂 off_6C1750 + 哨兵链 ·sub_425940 + ·sub_6569D0 清空 →…
{
  uint32_t *pMem; // eax
  int v1; // edi

  pMem = operator new(0x10u);  // pMem = new 0x10
  v1 = (int)pMem;
  if ( pMem == nullptr )  // 分配失败
    return -2147483640;  // 返回 -2147483640
  *pMem = off_6C1750;  // vftable off_6C1750
  pMem[2] = sub_425940(pMem + 1);  // pMem[2] = sub_425940 建哨兵链
  *(uint32_t *)(v1 + 12) = 0;  // this+12 清 0
  sub_6569D0(v1 + 4);  // sub_6569D0 清链
  dword_79C564 = v1;  // dword_79C564 = 容器
  return 1;
}



// ============================================================
// SECTION 0x4038D0 — 日志核心：NiLog 对象（QPC 计时日志 / 横幅 / 5000 行轮转 / OutputDebugString）
// ============================================================
// ------------------------------------------------------------
// 0x4038D0 sub_4038D0 —— NiLog 分派写入（按 *this 索引查控制台标志 byte_79C7B0 与文件槽 dword_79C7B4，转发 ·sub_403D60）
// byte_79C7B0[12*idx] 非 0 时先 OutputDebugStringA（Buffer 为 0x403C10 族共用格式化缓冲）；
// dword_79C7B4[3*idx] 为 -1 表示该槽无绑定文件。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4038D0(uint32_t *this)  // 【日志核心：NiLog 对象（QPC 计时日志 / 横幅 / 5000 行轮转 / O…】
{
  unsigned int result; // eax
  int v3; // ecx

  if ( byte_79C7B0[12 * *this] != 0 )  // 该槽控制台标志非 0
    OutputDebugStringA(Buffer);  // OutputDebugStringA 输出到调试器
  result = 12 * *this;  // result = 12×索引（文件槽偏移）
  v3 = dword_79C7B4[result / 4];  // v3 = 文件槽索引 dword_79C7B4
  if ( v3 >= 0 && byte_79C7B0[result] == 0 )  // 槽绑定文件且非控制台
    return sub_403D60((&dword_79C568)[v3], (size_t)Buffer);  // sub_403D60 写入文件对象
  return result;
}



// ------------------------------------------------------------
// 0x403920 sub_403920 —— 日志全局态复位（dword_79C568 起 16 槽全清 + byte_77F2E3 置 1 + ·sub_406C50 取全局日志对象经虚表槽 0 调用）
// ·0x420DA0 引擎主引导入口首调；与 ·sub_403A90 全面关闭成对。
// ------------------------------------------------------------
int sub_403920()  // 函数 日志全局态复位（dword_79C568 起 16 槽全清 + byte_77F2E3 置 1 + ·sub_406C50 取全局日志对…
{
  int (/*thiscall*/ ***v0)(uint32_t); // eax

  dword_79C568 = nullptr;
  dword_79C56C = 0;  // dword_79C56C 清 0
  dword_79C570 = 0;  // dword_79C570 清 0
  dword_79C574 = 0;  // dword_79C574 清 0
  dword_79C578 = 0;  // dword_79C578 清 0
  dword_79C57C = 0;  // dword_79C57C 清 0
  dword_79C580 = 0;  // dword_79C580 清 0
  dword_79C584 = 0;  // dword_79C584 清 0
  dword_79C588 = 0;  // dword_79C588 清 0
  dword_79C58C = 0;  // dword_79C58C 清 0
  dword_79C590 = 0;  // dword_79C590 清 0
  dword_79C594 = 0;  // dword_79C594 清 0
  dword_79C598 = 0;  // dword_79C598 清 0
  dword_79C59C = 0;  // dword_79C59C 清 0
  dword_79C5A0 = 0;  // dword_79C5A0 清 0
  byte_77F2E3 = 1;
  dword_79C5A4 = 0;  // dword_79C5A4 清 0
  v0 = (int (/*thiscall*/ ***)(uint32_t))sub_406C50();  // 【NiMemory.log / NiProfile.log 日志对象（Gamebryo…】
  return (**v0)(v0);  // 调虚表首项(对象) 初始化
}



// ------------------------------------------------------------
// 0x403990 sub_403990 —— 日志文件登记（16 槽表线性探测空位 → new(0x128) + ·sub_404290 构造，返回槽号）
// dword_79C7A8 计数满 16 返回 -1；调用方: ·0x420DA0 登记 DNF.trc、·0x406C60/·0x406CA0 登记 NiMemory.log/NiProfile.log。
// ------------------------------------------------------------
int /*cdecl*/ sub_403990(int nArg1, int nArg2, char pszArg3, int nArg4)  // 函数 日志文件登记（16 槽表线性探测空位 → new(0x128) + ·sub_404290 构造，返回槽号）
{
  int v5; // esi
  char *pMem; // eax
  char *v7; // eax

  if ( dword_79C7A8 == 16 )  // 若 dword_79C7A8 == 16
    return -1;  // 返回错误码 -1
  v5 = 0;
  while ( (&dword_79C568)[v5] != nullptr )
  {
    if ( dword_79C56C[v5] == 0 )
    {
      ++v5;  // v5 自增
      break;  // 跳出 switch
    }
    if ( dword_79C570[v5] == 0 )
    {
      v5 += 2;  // v5 前进 2
      break;  // 跳出 switch
    }
    if ( dword_79C574[v5] == 0 )
    {
      v5 += 3;  // v5 前进 3
      break;  // 跳出 switch
    }
    v5 += 4;  // v5 前进 4
    if ( v5 >= 16 )  // 若 v5 >= 16
      break;  // 跳出 switch
  }
  if ( v5 == 16 )  // 若 v5 == 16
    return -1;  // 返回错误码 -1
  pMem = (char *)operator new(0x128u);
  v7 = pMem != nullptr ? (char *)sub_404290(pMem, nArg1, nArg2, pszArg3, nArg4) : nullptr;  // 调 日志槽对象构造（+284 行计数清零 + strcpy 文件名 + +280 输出标志 + ·sub_404130 打开文件）
  (&dword_79C568)[v5] = v7;
  if ( v7 == nullptr )  // 若 v7 为空
    return -1;  // 返回错误码 -1
  ++dword_79C7A8;
  return v5;
}



// ------------------------------------------------------------
// 0x403A90 sub_403A90 —— 日志全面关闭（16 槽逐一 ·sub_4042D0 关闭（写 Log File Closed 横幅）+ free，计数清零）
// 崩溃回调第二步与 ·sub_403BE0 退出清理均调用。
// ------------------------------------------------------------
void sub_403A90()  // 函数 日志全面关闭（16 槽逐一 ·sub_4042D0 关闭（写 Log File Closed 横幅）+ free，计数清零）
{
  unsigned int i; // esi
  char *v1; // edi

  for ( i = 0; i < 16; ++i )
  {
    v1 = (&dword_79C568)[i];
    if ( v1 != nullptr )  // 若 v1 非空
    {
      sub_4042D0((&dword_79C568)[i]);  // 调 sub_4042D0
      j__free(v1);
    }
    (&dword_79C568)[i] = nullptr;
  }
  dword_79C7A8 = 0;  // dword_79C7A8 = 0/空
}



// ------------------------------------------------------------
// 0x403AD0 sub_403AD0 —— QPC 高精度计时（首调缓存 QueryPerformanceFrequency/基准计数，返回相对秒数）
// byte_77F2E4 为频率未初始化标志；·sub_403B60 用它给日志行加 %f 时间戳前缀。
// ------------------------------------------------------------
double sub_403AD0()  // 函数 QPC 高精度计时（首调缓存 QueryPerformanceFrequency/基准计数，返回相对秒数）
{
  LARGE_INTEGER PerformanceCount; // [esp+4h] [ebp-8h] BYREF

  if ( byte_77F2E4 != 0 )  // 若 byte_77F2E4 != 0
  {
    QueryPerformanceFrequency(&Frequency);  // 调 QueryPerformanceFrequency
    QueryPerformanceCounter(&::PerformanceCount);  // 调 QueryPerformanceCounter
    byte_77F2E4 = 0;  // byte_77F2E4 = 0/空
  }
  QueryPerformanceCounter(&PerformanceCount);  // 调 QueryPerformanceCounter
  return (double)(PerformanceCount.QuadPart - ::PerformanceCount.QuadPart) / (double)Frequency.QuadPart;
}



// ------------------------------------------------------------
// 0x403B30 sub_403B30 —— 泛型循环调用器（对 nArg1 + i*nArg2 重复 nArg3 次调 uArg4）
// missing_tail.cpp 以 (pMem, 16, n, sub_680131) 形式批量初始化 16 字节元素数组。
// ------------------------------------------------------------
int /*stdcall*/ sub_403B30(int nArg1, int nArg2, int nArg3, int (/*thiscall*/ *uArg4)(int))  // 函数 泛型循环调用器（对 nArg1 + i*nArg2 重复 nArg3 次调 uArg4）
{
  int result; // eax
  int i; // edi

  result = nArg3 - 1;
  if ( nArg3 - 1 >= 0 )
  {
    for ( i = nArg3; i != 0; --i )
    {
      result = uArg4(nArg1);
      nArg1 += nArg2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x403B60 sub_403B60 [串: "%f: "]
// ------------------------------------------------------------
int /*thiscall*/ sub_403B60(uint32_t *this, int64_t Format)  // 函数 用它给日志行加 %f 时间戳前缀
{
  char *v2; // edi
  size_t v3; // esi
  double v4; // st7
  unsigned int nLen; // eax
  int result; // eax

  v2 = Buffer;
  v3 = 512;
  if ( byte_79C7B8[12 * *this] != 0 )
  {
    v4 = sub_403AD0();  // 调 QPC 高精度计时（首调缓存 QueryPerformanceFrequency/基准计数，返回相对秒数）
    sprintf(Buffer, "%f: ", v4);  // 调 sprintf
    nLen = strlen(Buffer);  // CRT 字符串长度（逐字节扫描到 NUL）
    v3 = 512 - nLen;
    v2 = &Buffer[nLen];
  }
  result = _vsnprintf(v2, v3, (const char *const)Format, (va_list)HIDWORD(Format));
  v2[v3 - 1] = 0;
  return result;
}



// ------------------------------------------------------------
// 0x403BE0 sub_403BE0 —— 日志关机（·sub_403A90 全槽关闭 → 临界区按标志补初始化后 DeleteCriticalSection）
// byte_77F2E3 = 临界区未初始化标志（0 表示已初始化）。
// ------------------------------------------------------------
void sub_403BE0()  // 函数 日志关机（·sub_403A90 全槽关闭 → 临界区按标志补初始化后 DeleteCriticalSection）
{
  sub_403A90();  // 调 sub_403A90
  if ( byte_77F2E3 != 0 )  // 若 byte_77F2E3 != 0
  {
    InitializeCriticalSection(&CriticalSection);  // 调 InitializeCriticalSection
    byte_77F2E3 = 0;  // byte_77F2E3 = 0/空
  }
  DeleteCriticalSection(&CriticalSection);  // 调 DeleteCriticalSection
}



// ------------------------------------------------------------
// 0x403C10 sub_403C10 —— 日志格式化写入核心（临界区内 ·sub_403B60 vsnprintf → ·sub_4038D0 分派写入）
// uArg2 >= 0x20 或槽未启用（byte_79C7B0 与文件槽双判）即直接跳过；*pDwArg1 传回槽号。
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_403C10(unsigned int *pDwArg1, unsigned int uArg2, char *Format, char ArgList)  // 函数 日志格式化写入核心（临界区内 ·sub_403B60 vsnprintf → ·sub_4038D0 分派写入）
{
  *pDwArg1 = uArg2;  // 写指针 = uArg2
  if ( uArg2 < 0x20 && (byte_79C7B0[12 * uArg2] != 0 || dword_79C7B4[3 * uArg2] != -1) && Format != nullptr )
  {
    if ( byte_77F2E3 != 0 )  // 若 byte_77F2E3 != 0
    {
      InitializeCriticalSection(&CriticalSection);  // 调 InitializeCriticalSection
      byte_77F2E3 = 0;  // byte_77F2E3 = 0/空
    }
    EnterCriticalSection(&CriticalSection);  // 调 EnterCriticalSection
    sub_403B60(pDwArg1, __SPAIR64__(&ArgList, (unsigned int)Format));  // 调 sub_403B60
    sub_4038D0(pDwArg1);  // 【日志核心：NiLog 对象（QPC 计时日志 / 横幅 / 5000 行轮转 / O…】
    if ( byte_77F2E3 != 0 )  // 若 byte_77F2E3 != 0
    {
      InitializeCriticalSection(&CriticalSection);  // 调 InitializeCriticalSection
      byte_77F2E3 = 0;  // byte_77F2E3 = 0/空
    }
    LeaveCriticalSection(&CriticalSection);  // 调 LeaveCriticalSection
  }
  return pDwArg1;
}



// ------------------------------------------------------------
// 0x403CC0 sub_403CC0 —— 日志写入薄封装（槽 0 + ·sub_403C10）
// 无槽号变体入口。
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_403CC0(char *Format)  // 函数 日志写入薄封装（槽 0 + ·sub_403C10）
{
  char ArgList; // cl
  int v3; // [esp+0h] [ebp-4h] BYREF

  return sub_403C10((unsigned int *)&v3, 0, Format, ArgList);  // 调 日志格式化写入核心（临界区内 ·sub_403B60 vsnprintf → ·sub_4038D0 分派写入）
}



// ------------------------------------------------------------
// 0x403CE0 sub_403CE0 —— 日志 printf 变参入口（·sub_404F40 计时域 50 开始 → _vsnprintf + 补换行 → ·sub_403C10 → ·sub_404F80 计时结束）
// sub_404F40/404F80 = NiProfile rdtsc 计时作用域对（见文件头）。
// ------------------------------------------------------------
int sub_403CE0(char *Format, ...)  // 函数 日志 printf 变参入口（·sub_404F40 计时域 50 开始 → _vsnprintf + 补换行 → ·sub_403C1…
{
  int v1; // eax
  int v3; // [esp+0h] [ebp-208h] BYREF
  char Buffer[510]; // [esp+4h] [ebp-204h] BYREF
  char pBuf[2]; // [esp+202h] [ebp-6h] BYREF
  int dword_796E502; // [esp+204h] [ebp-4h]
  va_list va; // [esp+214h] [ebp+Ch] BYREF

  va_start(va, Format);
  dword_796E502 = dword_796E50;  // 栈检 cookie
  sub_404F40(50);  // 调 sub_404F40
  v1 = _vsnprintf(Buffer, 0x1FEu, Format, va);
  if ( v1 >= 0 )  // 若 v1 >= 0
  {
    Buffer[v1] = 10;
    Buffer[v1 + 1] = 0;
  }
  else  // 否则分支
  {
    strcpy(pBuf, "\n");  // 调 strcpy
  }
  sub_403C10((unsigned int *)&v3, 0, Buffer, v3);  // 调 sub_403C10
  return sub_404F80(50, 0);  // 调 NiProfile 计时作用域离开（槽耗时累计 = (rdtsc 差)/时间基准；pszArg3 非 0 先清零）
}



// ------------------------------------------------------------
// 0x403D60 sub_403D60
// ------------------------------------------------------------
// 【解读】
//   NiLog 文件写入器（核心）:
//     行计数(+71) 满 5000 行（-4999 < 0 / OFSUB 5000）时 fclose+fopen 重开 —— 日志轮转；
//     横幅 "/**...**\n * %s - Log File Opened\n *     %02d/%02d/%04d - %2d:%02d:%02d"；
//     byte_79C7AC == 1 时同步镜像到控制台（sub_406CD0）；
//     入参超过 512 字节截断到 0x1FC+3（防溢出）。
// ------------------------------------------------------------
char /*thiscall*/ sub_403D60(char *FileName, const char *ElementCount)
{
  int v3; // eax
  signed int nLen; // eax
  const char *v6; // esi
  int v7; // ecx
  bool v8; // sf
  FILE *pFile; // eax
  uint8_t v11[511]; // [esp+4h] [ebp-304h] BYREF
  char v12; // [esp+203h] [ebp-105h]
  char Buffer[256]; // [esp+204h] [ebp-104h] BYREF
  int dword_796E502; // [esp+304h] [ebp-4h]
  size_t ElementCounta; // [esp+310h] [ebp+8h]

  dword_796E502 = dword_796E50;  // 栈检 cookie
  v3 = *((uint32_t *)FileName + 65);  // v3 = FileName[65] 文件句柄
  if ( v3 != 0 )  // 句柄非 0（文件已打开）
  {
    nLen = strlen(ElementCount);  // nLen = strlen(入参)
    ElementCounta = nLen;  // ElementCounta = 入参长度
    if ( nLen <= 512 )  // 长度 <= 512
    {
      qmemcpy(v11, ElementCount, nLen);  // qmemcpy 全量拷贝到行缓冲 v11
    }
    else  // 否则分支
    {
      qmemcpy(v11, ElementCount, 0x1FCu);  // 否则截断：先拷 0x1FC 字节
      v6 = ElementCount + 508;  // v6 = 入参 + 508
      *(uint16_t *)&v11[508] = *(uint16_t *)v6;  // v11[508] = 拷贝尾部 2 字节
      ElementCounta = 512;
      nLen = 512;
      v11[510] = v6[2];  // v11[510] = 尾部第 3 字节
      v12 = 0;
    }
    if ( byte_79C7AC == 1 )  // byte_79C7AC == 1（镜像到控制台）
    {
      sub_406CD0(v11, nLen);  // sub_406CD0 输出到控制台
      nLen = ElementCounta;
    }
    v7 = *((uint32_t *)FileName + 71) + 1;  // v7 = 行计数 + 1
    v8 = *((uint32_t *)FileName + 71) - 4999 < 0;  // v8 = 行计数 < 4999
    *((uint32_t *)FileName + 71) = v7;  // 行计数 = v7
    if ( v8 == __OFSUB__(v7, 5000) )  // 行计数达 5000（轮转触发）
    {
      fclose(*((FILE **)FileName + 65));  // fclose 关闭当前日志
      pFile = fopen(FileName, FileName + 288);  // fopen 重开（FileName+288 为模式串）
      *((uint32_t *)FileName + 65) = pFile;  // FileName[65] = 新句柄
      fclose(pFile);  // fclose 临时句柄
      *((uint32_t *)FileName + 65) = fopen(FileName, FileName + 288);  // 重新 fopen 赋 FileName[65]
      sprintf(Buffer, "/******************************************************\n");  // sprintf 横幅起始行（星号框）
      if ( byte_79C7AC != 0 )  // 镜像控制台
        sub_406CD0(Buffer, strlen(Buffer));  // sub_406CD0 输出
      fprintf(*((FILE *const *)FileName + 65), Buffer);  // fprintf 写横幅
      sprintf(Buffer, "* %s - Log File Opened\n", FileName);
      if ( byte_79C7AC != 0 )  // 镜像控制台
        sub_406CD0(Buffer, strlen(Buffer));  // sub_406CD0 输出
      fprintf(*((FILE *const *)FileName + 65), Buffer);  // fprintf 写打开横幅
      sprintf(  // sprintf 时间戳行 %02d/%02d/%04d - %2d:%02d:%02d
        Buffer,
        "*     %02d/%02d/%04d - %2d:%02d:%02d\n",  // 月
        *((uint16_t *)FileName + 133),  // 日
        *((uint16_t *)FileName + 135),  // 年
        *((uint16_t *)FileName + 132),  // 时
        *((uint16_t *)FileName + 136),  // 分
        *((uint16_t *)FileName + 137),  // 秒
        *((uint16_t *)FileName + 138));
      if ( byte_79C7AC != 0 )  // 镜像控制台
        sub_406CD0(Buffer, strlen(Buffer));  // sub_406CD0 输出
      fprintf(*((FILE *const *)FileName + 65), Buffer);  // fprintf 写时间戳
      sprintf(Buffer, "******************************************************/\n\n\n\n\n\n");  // sprintf 横幅结束行（星号收尾）
      if ( byte_79C7AC != 0 )  // 镜像控制台
        sub_406CD0(Buffer, strlen(Buffer));  // sub_406CD0 输出
      fprintf(*((FILE *const *)FileName + 65), Buffer);  // fprintf 写结束横幅
      nLen = ElementCounta;
      *((uint32_t *)FileName + 71) = 0;  // 行计数复位 0
    }
    sub_66BC25(v11, 1u, nLen, *((FILE **)FileName + 65));  // sub_66BC25 写 nLen 字节日志到文件
    LOBYTE(v3) = *(FileName + 280);  // v3 低字节 = FileName+280（刷新标志）
    if ( (uint8_t)v3 != 0 )  // 刷新标志非 0
      LOBYTE(v3) = fflush(*((FILE **)FileName + 65));  // fflush 立即刷盘
  }
  return v3;
}



// ------------------------------------------------------------
// 0x404020 sub_404020 —— 日志冲刷（16 槽逐一 fflush）
// 崩溃回调第一步 —— 崩溃时先把残留日志落盘再打包。
// ------------------------------------------------------------
char *sub_404020()  // 函数 日志冲刷（16 槽逐一 fflush）
{
  unsigned int i; // esi
  char *result; // eax

  for ( i = 0; i < 16; ++i )
  {
    result = (&dword_79C568)[i];
    if ( result != nullptr )  // 若 result 非空
      result = (char *)fflush(*((FILE **)result + 65));
  }
  return result;
}



// ------------------------------------------------------------
// 0x404050 sub_404050
// ------------------------------------------------------------
// 【解读】
//   日志关闭横幅（Log File Closed + GetLocalTime + 5 空行）→ fclose。
// ------------------------------------------------------------
int /*thiscall*/ sub_404050(char *FileName)
{
  int result; // eax
  struct _SYSTEMTIME SystemTime; // [esp+4h] [ebp-114h] BYREF
  char Buffer[256]; // [esp+14h] [ebp-104h] BYREF
  int dword_796E502; // [esp+114h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 栈检 cookie
  result = *((uint32_t *)FileName + 65);
  if ( result != 0 )  // 若 result != 0
  {
    sub_403D60(FileName, "\n\n\n\n\n/******************************************************\n");  // 调 sub_403D60
    sprintf(Buffer, "* %s - Log File Closed\n", FileName);  // 调 sprintf
    sub_403D60(FileName, Buffer);  // 调 sub_403D60
    GetLocalTime(&SystemTime);  // 调 GetLocalTime
    sprintf(  // 调 sprintf
      Buffer,
      "*     %02d/%02d/%04d - %2d:%02d:%02d\n",
      SystemTime.wMonth,
      SystemTime.wDay,
      SystemTime.wYear,
      SystemTime.wHour,
      SystemTime.wMinute,
      SystemTime.wSecond);
    sub_403D60(FileName, Buffer);  // 调 sub_403D60
    sub_403D60(FileName, "******************************************************/\n");  // 调 sub_403D60
    result = fclose(*((FILE **)FileName + 65));
  }
  *((uint32_t *)FileName + 65) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x404130 sub_404130
// ------------------------------------------------------------
// 【解读】
//   日志文件打开（fopen + strcpy 文件名 + Log File Opened 横幅）。
// ------------------------------------------------------------
char /*thiscall*/ sub_404130(char *FileName, int nArg2, int nArg3)
{
  char Buffer[256]; // [esp+4h] [ebp-10Ch] BYREF
  char Mode[8]; // [esp+104h] [ebp-Ch] BYREF
  int dword_796E502; // [esp+10Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // 栈检 cookie
  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    if ( nArg2 == 1 )  // 若 nArg2 == 1
    {
      strcpy(Mode, "wt");  // 调 strcpy
    }
    else  // 否则分支
    {
      if ( nArg2 != 2 )  // 若 nArg2 != 2
      {
        *((uint32_t *)FileName + 65) = 0;
        return 0;
      }
      byte_79C7AC = 1;
      strcpy(Mode, "wt");  // 调 strcpy
    }
  }
  else  // 否则分支
  {
    *(uint32_t *)Mode = &unk_742B61;
  }
  *((uint32_t *)FileName + 65) = fopen(FileName, Mode);
  strcpy(FileName + 288, Mode);  // 调 strcpy
  if ( *((uint32_t *)FileName + 65) == 0 )
    return 0;
  sub_403D60(FileName, "/******************************************************\n");  // 调 sub_403D60
  sprintf(Buffer, "* %s - Log File Opened\n", FileName);  // 调 sprintf
  sub_403D60(FileName, Buffer);  // 调 sub_403D60
  GetLocalTime((LPSYSTEMTIME)(FileName + 264));  // 调 GetLocalTime
  sprintf(  // 调 sprintf
    Buffer,
    "*     %02d/%02d/%04d - %2d:%02d:%02d\n",
    *((uint16_t *)FileName + 133),
    *((uint16_t *)FileName + 135),
    *((uint16_t *)FileName + 132),
    *((uint16_t *)FileName + 136),
    *((uint16_t *)FileName + 137),
    *((uint16_t *)FileName + 138));
  sub_403D60(FileName, Buffer);  // 调 sub_403D60
  sub_403D60(FileName, "******************************************************/\n\n\n\n\n\n");  // 调 sub_403D60
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x404290 sub_404290 —— 日志槽对象构造（+284 行计数清零 + strcpy 文件名 + +280 输出标志 + ·sub_404130 打开文件）
// ·0x403990 内 new(0x128) 后调用；文件名即日志名（DNF.trc / NiMemory.log / NiProfile.log）。
// ------------------------------------------------------------
char */*thiscall*/ sub_404290(char *FileName, const char *pArg2, int nArg3, char pszArg4, int nArg5)  // 函数 日志槽对象构造（+284 行计数清零 + strcpy 文件名 + +280 输出标志 + ·sub_404130 打开文件）
{
  char *v5; // esi

  *((uint32_t *)FileName + 71) = 0;
  v5 = strcpy(FileName, pArg2);
  v5[280] = pszArg4;
  sub_404130(v5, nArg3, nArg5);  // 调 sub_404130
  return v5;
}



// ------------------------------------------------------------
// 0x4042D0 sub_4042D0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_4042D0(char *FileName)
{
  return sub_404050(FileName);
}



// ============================================================
// SECTION 0x4042E0 — Win32 窗口框架：主窗口过程 / 消息循环 / 单实例检测 / 全屏分辨率切换
// ============================================================
// ------------------------------------------------------------
// 0x4042E0 sub_4042E0 —— 窗口过程转发器（GWLP_USERDATA 取管理器对象 → 虚表槽 32 转发；无则 DefWindowProcA 兜底）
// Win32 消息入口壳；dword_79C0A0+16 处窗口的实际窗口过程为 ·0x404620。
// ------------------------------------------------------------
LRESULT /*stdcall*/ sub_4042E0(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)  // 【Win32 窗口框架：主窗口过程 / 消息循环 / 单实例检测 / 全屏分辨率切换】
{
  LONG WindowLongA; // eax

  WindowLongA = GetWindowLongA(hWnd, 0);  // GetWindowLongA 取窗口附加数据
  if ( WindowLongA != 0 )  // 附加数据非 0（有引擎对象）
    return (*(int (/*thiscall*/ **)(LONG, HWND, UINT, WPARAM, LPARAM))(*(uint32_t *)WindowLongA + 32))(  // 调对象 vt+32 槽 WndProc 处理
             WindowLongA,
             hWnd,
             Msg,
             wParam,
             lParam);
  else  // 否则分支
    return DefWindowProcA(hWnd, Msg, wParam, lParam);  // 否则交 DefWindowProcA 默认处理
}



// ------------------------------------------------------------
// 0x404330 sub_404330 —— 窗口尺寸记录 + SetWindowPos 刷新（宽高存 +44/+48，HWND 在 +16）
// ·0x4048F0 初始化时经 ·sub_404590 调用；SetWindowPos 标志 6 = SWP_NOMOVE|SWP_NOZORDER（仅调尺寸）。
// ------------------------------------------------------------
HWND /*thiscall*/ sub_404330(HWND *this, HWND nArg2, HWND cy)  // 函数 窗口尺寸记录 + SetWindowPos 刷新（宽高存 +44/+48，HWND 在 +16）
{
  HWND result; // eax
  HWND fld_e4; // ecx

  result = nArg2;
  *(this + 11) = nArg2;  // this[11] = 宽 nArg2
  *(this + 12) = cy;  // this[12] = 高 cy
  fld_e4 = *(this + 4);  // fld_e4 = this[4] 窗口句柄
  if ( fld_e4 != nullptr )  // 句柄非空
    return (HWND)SetWindowPos(fld_e4, nullptr, 0, 0, (int)nArg2, (int)cy, 6u);  // SetWindowPos 仅改尺寸 (标志 6)
  return result;
}



// ------------------------------------------------------------
// 0x404360 sub_404360
// ------------------------------------------------------------
// 【解读】
//   主消息循环: ShowWindow/UpdateWindow/SetFocus → PeekMessage(帧驱动)+GetMessage 双泵 → TranslateMessage/DispatchMessage；每帧 sub_4052D0(timeGetTime 帧计时)。
// ------------------------------------------------------------
WPARAM /*thiscall*/ sub_404360(int this)
{
  char fld_4; // al
  int fld_8; // esi
  struct tagMSG Msg; // [esp+4h] [ebp-20h] BYREF
  int pThis; // [esp+20h] [ebp-4h]

  fld_4 = *(uint8_t *)(this + 4);  // fld_4 = this+4 就绪位
  pThis = this;
  if ( fld_4 == 0 )  // 未就绪
    return -2147483647;  // 返回 0x80000001（未就绪）
  ShowWindow(*(HWND *)(this + 16), 1);  // ShowWindow 显示窗口 (SW_SHOWNORMAL)
  UpdateWindow(*(HWND *)(this + 16));  // UpdateWindow 刷新
  SetFocus(*(HWND *)(this + 16));  // SetFocus 设焦点
  if ( *(uint32_t *)(this + 8) == 1 )  // 模式 == 1（全屏）
    ShowCursor(false);  // 隐藏鼠标光标
  fld_8 = *(uint32_t *)(this + 8);  // fld_8 = this+8 运行模式
  if ( fld_8 == 1 || fld_8 == 4 )  // 模式 1 或 4（帧驱动泵）
  {
    while ( !PeekMessageA(&Msg, nullptr, 0, 0, 1u) )  // PeekMessageA 无消息时空转
    {
LABEL_16:  // LABEL_16（无消息时）
      if ( *(uint32_t *)(pThis + 124) != 0 )  // this+124 帧对象非空
      {
        sub_4052D0();  // 【tick_domains_step】
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pThis + 124) + 12))(*(uint32_t *)(pThis + 124));  // 调帧对象 vt+12 槽（帧更新）
      }
    }
    while ( Msg.message != 18 )  // 消息非 WM_QUIT(18)
    {
      TranslateMessage(&Msg);  // TranslateMessage 转换
      DispatchMessageA(&Msg);  // DispatchMessageA 派发
      if ( !PeekMessageA(&Msg, nullptr, 0, 0, 1u) )  // PeekMessageA 取下一消息
        goto LABEL_16;  // 无消息跳 LABEL_16
    }
    return 1;  // 返回 1（成功）
  }
  else if ( fld_8 == 3 || fld_8 == 2 )  // 模式 3 或 2（GetMessage 泵）
  {
    while ( GetMessageA(&Msg, nullptr, 0, 0) )  // GetMessageA 阻塞取消息
    {
      sub_4052D0();  // 【tick_domains_step】
      TranslateMessage(&Msg);
      DispatchMessageA(&Msg);
    }
    return Msg.wParam;  // 返回退出码 Msg.wParam
  }
  else  // 否则分支
  {
    return -2147483639;  // 返回 0x80000009（类型错）
  }
}



// ------------------------------------------------------------
// 0x404490 sub_404490 —— 主管理器槽位释放（*uArg1 非空经虚表槽 0 析构 → 置 0）
// ·0x4010E0 关停链以 &dword_79C0A0 调用。
// ------------------------------------------------------------
int /*stdcall*/ sub_404490(uint32_t *uArg1)  // 函数 主管理器槽位释放（*uArg1 非空经虚表槽 0 析构 → 置 0）
{
  if ( *uArg1 != 0 )  // *uArg1 非空
    (**(void (/*thiscall*/ ***)(uint32_t, int))*uArg1)(*uArg1, 1);  // 调虚表首项(对象,1) 析构
  *uArg1 = 0;  // *uArg1 清 0
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x4044C0 sub_4044C0 —— 事件分发对象状态初始化（+8=1/+12=50 默认 + 四槽 -1 + ·sub_4072B0 全局缓冲清零 + CoInitialize）
// ★ 尾行虚表槽 20 调用为对象自初始化钩子；byte_89D160 为 256 字节全局缓冲，
// ·sub_4072B0 清三块 0x400 字节区域（IME 族全局态）【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4044C0(uint32_t *this)  // 函数 事件分发对象状态初始化（+8=1/+12=50 默认 + 四槽 -1 + ·sub_4072B0 全局缓冲清零 + CoInitiali…
{
  *(this + 2) = 0;  // this+2 清 0
  *(this + 8) = 1;  // this+8 = 1
  *(this + 3) = 50;  // this+3 = 50
  *(this + 4) = 0;  // this+4 清 0
  *(this + 5) = 0;  // this+5 清 0
  *(this + 6) = 0;  // this+6 清 0
  *(this + 9) = -1;  // this+9 = -1
  *(this + 10) = -1;  // this+10 = -1
  *(this + 11) = -1;  // this+11 = -1
  *(this + 12) = -1;  // this+12 = -1
  *(this + 31) = 0;  // this+31 清 0
  *(this + 32) = 0;  // this+32 清 0
  sub_4072B0(this + 29);  // sub_4072B0 全局缓冲清零（IME 族）
  memset(&byte_89D160, 0, 0x100u);  // memset byte_89D160 清零（256B）
  sub_6569D0(this + 33);  // sub_6569D0 清哨兵链 1
  sub_6569D0(this + 36);  // sub_6569D0 清哨兵链 2
  sub_6569D0(this + 39);  // sub_6569D0 清哨兵链 3
  sub_6569D0(this + 42);  // sub_6569D0 清哨兵链 4
  *((uint8_t *)this + 180) = 0;  // this 偏移 180 字节 = 0
  CoInitialize(nullptr);  // CoInitialize 初始化 COM
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);  // 调虚表 +20 槽自初始化钩子
}



// ------------------------------------------------------------
// 0x404560 sub_404560 —— 事件分发对象状态回卷（·sub_407310 释放全局 GDI/IME 资源 → 虚表槽 28 → CoUninitialize → ·sub_4044C0 复位）
// ·0x403770 派生析构调用；与 ·0x4044C0 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_404560(int this)  // 函数 事件分发对象状态回卷（·sub_407310 释放全局 GDI/IME 资源 → 虚表槽 28 → CoUninitialize → ·…
{
  int result; // eax

  sub_407310(this + 116);  // sub_407310 释放全局 GDI/IME 资源
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 28))(this);  // 调虚表 +28 槽
  CoUninitialize();  // CoUninitialize 反初始化 COM
  result = sub_4044C0((uint32_t *)this);  // sub_4044C0 复位状态
  *(uint8_t *)(this + 4) = 0;  // this+4 清 0
  return result;
}



// ------------------------------------------------------------
// 0x404590 sub_404590 —— 窗口定位 + 子对象广播（-1 时按 GetSystemMetrics 居中；+136 哨兵链遍历逐节点经虚表槽 20 通知坐标）
// WM_SIZE(534) 与 ·sub_4048F0 / ·sub_404330 初始化均调用；SetWindowPos 标志 5 = SWP_NOSIZE|SWP_NOZORDER（仅调位置）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_404590(uint32_t *this, int nArg2, int nArg3)  // 函数 窗口定位 + 子对象广播（-1 时按 GetSystemMetrics 居中；+136 哨兵链遍历逐节点经虚表槽 20 通知坐标）
{
  HWND fld_e4; // eax
  uint32_t *result; // eax
  uint32_t *v6; // edi

  *(this + 9) = nArg2;  // this+9 = nArg2（X）
  *(this + 10) = nArg3;  // this+10 = nArg3（Y）
  if ( nArg2 == -1 )  // X == -1
    *(this + 9) = (GetSystemMetrics(0) >> 1) - (*(this + 11) >> 1);  // 按屏幕宽居中
  if ( *(this + 10) == -1 )  // Y == -1
    *(this + 10) = (GetSystemMetrics(1) >> 1) - (*(this + 12) >> 1);  // 按屏幕高居中
  fld_e4 = (HWND)*(this + 4);  // fld_e4 = this[4] 窗口句柄
  if ( fld_e4 != nullptr )  // 句柄非空
    SetWindowPos(fld_e4, nullptr, *(this + 9), *(this + 10), 0, 0, 5u);  // SetWindowPos 仅移动 (标志 5)
  result = (uint32_t *)*(this + 34);  // result = this+34 哨兵链
  v6 = (uint32_t *)*result;  // v6 = 首节点
  if ( (uint32_t *)*result != result )  // 链表非空
  {
    do  // 逐节点
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)v6[2] + 20))(  // 调子对象 vt+20 槽通知坐标
                           v6[2],
                           *(this + 9),
                           *(this + 10));
      v6 = (uint32_t *)*v6;  // v6 = 下一节点
    }
    while ( v6 != (uint32_t *)*(this + 34) );  // 回到哨兵
  }
  return result;
}



// ------------------------------------------------------------
// 0x404620 sub_404620
// ------------------------------------------------------------
// 【解读】
//   主窗口过程 WndProc: DefWindowProcA 兜底分发；sub_406D90/sub_407900 = IME 主处理；
//   PostQuitMessage 退出；GetCurrentProcess+SetPriorityClass —— 状态切换时调优先级【推断：挂起降级】。
// ------------------------------------------------------------
LRESULT /*thiscall*/ sub_404620(int this, HWND hWnd, UINT Msg, WPARAM wParam, int *lParam)
{
  HANDLE CurrentProcess; // eax
  int fld_7C; // ecx
  int fld_80; // ecx

  if ( Msg <= 0x112 )  // Msg <= WM_SYSCOMMAND(0x112)
  {
    if ( Msg == 274 )  // Msg == WM_SYSCOMMAND(274)
    {
      if ( (wParam & 0xFFF0) == 0xF050 )  // SC_KEYMENU 命令
        return 0;
    }
    else  // 否则分支
    {
      if ( Msg > 0x102 )  // Msg > WM_CHAR(0x102)
      {
        switch ( Msg )  // 按 Msg 分派
        {
          case 0x104u:  // case WM_SYSCHAR(0x104)
          case 0x105u:  // case WM_SYSKEYDOWN(0x105)
            goto LABEL_14;  // 跳 LABEL_14（IME 处理）
          case 0x10Du:  // case WM_IME_STARTCOMPOSITION(0x10D)
          case 0x10Eu:  // case 0x10E
          case 0x10Fu:  // case 0x10F
            goto LABEL_30;  // 跳 LABEL_30
          default:  // 默认分支
            return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);  // 交 DefWindowProcA
        }
      }
      if ( Msg >= 0x100 )  // Msg >= WM_KEYDOWN(0x100)
      {
LABEL_14:  // LABEL_14（按键/IME）
        sub_406D90(Msg, wParam, lParam);  // 【IME 输入法处理族（Composition/Candidate/NotifyIME…】
        sub_407900(Msg, wParam, lParam);  // sub_407900 按键处理
      }
      else  // 否则分支
      {
        switch ( Msg )  // 按 Msg 分派（低值）
        {
          case 2u:  // case WM_DESTROY(2)
            *(uint8_t *)(this + 180) = 1;  // this+180 = 1（退出标志）
            PostQuitMessage(0);  // PostQuitMessage 投递退出
            break;  // 跳出 switch
          case 6u:  // case WM_ACTIVATE(6)
            *(uint32_t *)(this + 32) = (uint16_t)wParam;  // this+32 = 激活态
            CurrentProcess = GetCurrentProcess();  // CurrentProcess = 当前进程
            if ( (uint16_t)wParam != 0 )  // 激活
              SetPriorityClass(CurrentProcess, 0x20u);  // SetPriorityClass NORMAL_PRIORITY_CLASS(0x20)
            else  // 否则分支
              SetPriorityClass(CurrentProcess, 0x4000u);  // 非激活：IDLE_PRIORITY_CLASS(0x4000)
            break;  // 跳出 switch
          case 0x10u:  // case WM_CLOSE(0x10)
            *(uint8_t *)(this + 180) = 1;  // this+180 = 1
            return 0;
          default:  // 默认分支
            break;  // 跳出 switch
        }
      }
    }
    return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);  // 交 DefWindowProcA
  }
  if ( Msg <= 0x216 )
  {
    if ( Msg == 534 )  // Msg == WM_SIZE(534)
    {
      sub_404590((uint32_t *)this, *lParam, lParam[1]);  // sub_404590 窗口定位 + 子对象广播
    }
    else  // 否则分支
    {
      switch ( Msg )  // 按 Msg 分派
      {
        case 0x113u:  // case WM_TIMER(0x113)
          if ( *(uint32_t *)(this + 32) == 0 )  // this+32 为 0（激活态）
          {
            sub_4052D0();  // 【tick_domains_step】
            fld_7C = *(uint32_t *)(this + 124);  // fld_7C = this+124 帧对象
            if ( fld_7C != 0 )  // 非空
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_7C + 12))(fld_7C);  // 调 vt+12 槽（帧更新）
          }
          break;  // 跳出 switch
        case 0x200u:  // case WM_MOUSEMOVE(0x200)
        case 0x201u:  // case WM_LBUTTONDOWN(0x201)
        case 0x202u:  // case WM_LBUTTONUP(0x202)
        case 0x204u:  // case WM_RBUTTONDOWN(0x204)
        case 0x205u:  // case WM_RBUTTONUP(0x205)
          sub_407110(Msg, wParam, lParam);  // sub_407110 鼠标事件处理
          break;  // 跳出 switch
        default:  // 默认分支
          return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);  // 交 DefWindowProcA
      }
    }
    return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);  // 交 DefWindowProcA
  }
  if ( Msg != 642 )  // Msg != WM_IME_CHAR(642)
  {
    if ( Msg == 1124 )
    {
      fld_80 = *(uint32_t *)(this + 128);  // fld_80 = this+128 对象
      if ( fld_80 != 0 )  // 非空
        (*(void (/*thiscall*/ **)(int, HWND, int, WPARAM, int *))(*(uint32_t *)fld_80 + 4))(fld_80, hWnd, 1124, wParam, lParam);  // 调 vt+4 槽（传事件）
    }
    return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);  // 交 DefWindowProcA
  }
LABEL_30:  // LABEL_30（IME 结束处理）
  sub_407900(Msg, wParam, lParam);  // sub_407900 收尾处理
  return 0;
}



// ------------------------------------------------------------
// 0x4048F0 sub_4048F0
// ------------------------------------------------------------
// 【解读】
//   单实例检测: FindWindowA(类名) 命中 → SetForegroundWindow 唤醒旧实例 + sub_402AE0 通知后退出。
// ------------------------------------------------------------
int /*thiscall*/ sub_4048F0(int this, int nArg2, LPCSTR lpClassName, const char *pArg4, int nArg5, int nArg6, int nArg7, int nArg8)
{
  int result; // eax
  HWND WindowA; // eax

  if ( *(uint8_t *)(this + 4) != 0 )  // this+4 已初始化
    return -2147483646;  // 返回 0x80000002（已初始化）
  WindowA = FindWindowA(lpClassName, nullptr);  // FindWindowA 按类名查找已有窗口
  if ( WindowA != nullptr )  // 找到（已有实例）
  {
    SetForegroundWindow(WindowA);  // 调 SetForegroundWindow
    return -2147483646;  // 返回 0x80000002（已初始化）
  }
  else  // 否则分支
  {
    *(uint32_t *)(this + 20) = nArg2;  // this+20 = 参数2
    *(uint32_t *)(this + 8) = nArg8;  // this+8 = 参数8
    sub_402AE0(this + 52, lpClassName);  // 调 sub_402AE0
    sub_402AE0(this + 72, pArg4);  // 调 sub_402AE0
    if ( *(uint32_t *)(this + 44) == -1 )
      *(uint32_t *)(this + 44) = 800;  // this+44（uint32 槽）= 800
    if ( *(uint32_t *)(this + 48) == -1 )
      *(uint32_t *)(this + 48) = 600;  // this+48（uint32 槽）= 600
    sub_404590((uint32_t *)this, *(uint32_t *)(this + 36), *(uint32_t *)(this + 40));  // 调 sub_404590
    result = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 24))(this, nArg5, nArg6, nArg7, nArg8);  // 调用虚函数/间接调用
    if ( result >= 0 )  // 若 result >= 0
    {
      sub_4076E0(*(HWND *)(this + 16));  // 调 sub_4076E0
      hWnd = *(HWND *)(this + 16);
      *(uint8_t *)(this + 4) = 1;
      return 1;  // 返回 1（成功）
    }
  }
  return result;
}



// ============================================================
// SECTION 0x4049C0 — 插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）
// ============================================================
// ------------------------------------------------------------
// 0x4049C0 sub_4049C0
// ------------------------------------------------------------
// 【解读】
//   区间线性插值 lerp（与 src/nengine/camera_fx.cpp 引用的 0x4049C0 同址 —— lerp_f 源头）。
// ------------------------------------------------------------
double /*cdecl*/ sub_4049C0(float fArg1, float fArg2, int nArg3, int nArg4)  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
{
  if ( nArg3 >= nArg4 )  // t >= tEnd
    return fArg2;  // 返回终点值 fArg2
  if ( nArg3 > 0 )  // t > 0
    return (fArg2 - fArg1) * (double)nArg3 / (double)nArg4 + fArg1;  // 返回 from + (to-from)×t/tEnd（线性插值）
  return fArg1;  // 返回起点值 fArg1
}



// ------------------------------------------------------------
// 0x4049F0 sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
// 与 ·0x4049C0 直插值配对 —— 镜头/UI 缓动曲线族【推断】；边界同 lerp（t>=tEnd 返回 to、t<=0 返回 from）。
// ------------------------------------------------------------
double /*cdecl*/ sub_4049F0(float fArg1, float fArg2, int nArg3, int nArg4, char pszArg5)  // 函数 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
{
  double fArg12; // st7
  double fArg22; // st6
  double v8; // st5
  long double v9; // st4
  long double v10; // st4
  uint8_t v12; // c0
  uint8_t v13; // c3
  double v14; // st5
  float v15; // [esp+0h] [ebp-4h]
  float v16; // [esp+18h] [ebp+14h]

  if ( nArg3 >= nArg4 )  // t >= tEnd
    return fArg2;
  if ( nArg3 <= 0 )  // t <= 0
    return fArg1;
  fArg12 = fArg1;  // fArg12 = fArg1（起点）
  fArg22 = fArg2;  // fArg22 = fArg2（终点）
  if ( pszArg5 == 0 )  // pszArg5 为 0（反向）
  {
    nArg3 = nArg4 - nArg3;  // nArg3 = tEnd - t
    fArg12 = fArg2;  // fArg12 = 终点
    fArg22 = fArg1;  // fArg22 = 起点
  }
  v8 = (double)nArg4;  // v8 = tEnd
  v9 = fabs(fArg22 - fArg12);  // v9 = |终点-起点|
  v10 = (v9 + v9) / v8;  // v10 = 2×距离 / tEnd
  v16 = v10;
  v15 = -(v10 / v8);  // v15 = -(v10/tEnd)
  v14 = (v15 * (double)nArg3 * 0.5 + v16) * (double)nArg3;  // v14 = (v15×t×0.5 + v16)×t（抛物线项）
  if ( (v12 | v13) != 0 )  // 方向标志
    return fArg12 - v14;  // 反向：返回 起点 - v14
  else  // 否则分支
    return fArg12 + v14;  // 正向：返回 起点 + v14
}



// ------------------------------------------------------------
// 0x404A80 sub_404A80 —— 流读取游标设置（dword_79D060 = nArg1）
// 与 0x404A90/0x404AB0/0x404AD0/0x404AF0 组成游标读取族。
// ------------------------------------------------------------
int /*cdecl*/ sub_404A80(int nArg1)  // 函数 流读取游标设置（dword_79D060 = nArg1）
{
  dword_79D060 = nArg1;  // dword_79D060 = 游标 nArg1
  return nArg1;
}



// ------------------------------------------------------------
// 0x404A90 sub_404A90 —— 游标读 1 字节（*uArg1 取值，游标 +1）
// 与 ·0x404AB0/·0x404AD0 同构（差异: 读取宽度 1/2/4 字节）。
// ------------------------------------------------------------
int /*cdecl*/ sub_404A90(uint8_t *uArg1)  // 函数 游标读 1 字节（*uArg1 取值，游标 +1）
{
  int result; // eax

  result = dword_79D060 + 1;  // result = 游标+1
  *uArg1 = *(uint8_t *)dword_79D060;  // *uArg1 = 读 1 字节
  dword_79D060 = result;  // 游标 = result
  return result;
}



// ------------------------------------------------------------
// 0x404AB0 sub_404AB0 —— 游标读 2 字节
// 与 ·0x404A90 同构（差异: uint16）。
// ------------------------------------------------------------
int /*cdecl*/ sub_404AB0(uint16_t *uArg1)
{
  int result; // eax

  result = dword_79D060 + 2;  // result = 游标+2
  *uArg1 = *(uint16_t *)dword_79D060;  // *uArg1 = 读 2 字节
  dword_79D060 = result;  // 游标 = result
  return result;
}



// ------------------------------------------------------------
// 0x404AD0 sub_404AD0 —— 游标读 4 字节
// 与 ·0x404A90 同构（差异: uint32）；skill_load_tutorial.cpp 0x48BC90 用它读取长度前缀。
// ------------------------------------------------------------
int /*cdecl*/ sub_404AD0(uint32_t *uArg1)
{
  int result; // eax

  result = dword_79D060 + 4;  // result = 游标+4
  *uArg1 = *(uint32_t *)dword_79D060;  // *uArg1 = 读 4 字节
  dword_79D060 = result;  // 游标 = result
  return result;
}



// ------------------------------------------------------------
// 0x404AF0 sub_404AF0 —— 游标读 n 字节到目标缓冲（qmemcpy 批量版）
// 与 ·0x404A90 族同源，返回拷贝字节数。
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_404AF0(void *pArg1, unsigned int uArg2)  // 函数 游标读 n 字节到目标缓冲（qmemcpy 批量版）
{
  int dword_79D0602; // edx

  dword_79D0602 = dword_79D060;
  qmemcpy(pArg1, (const void *)dword_79D060, uArg2);  // qmemcpy uArg2 字节到目标
  dword_79D060 = uArg2 + dword_79D0602;  // 游标 += uArg2
  return uArg2;
}



// ------------------------------------------------------------
// 0x404B30 sub_404B30 —— 超长文本按 1024 字节切片（200 段缓冲清 0 + 逐段拷贝，段内按 CR / 多字节字符边界截断）
// ★ 大文本分块器: 显式比对多字节前导字节表(-127..-4 即 0x81..0xFC)避免截断双字节字符；
// 每段经 pArg3+48 虚表槽 24 逐字符回调（返回 -1 即命中换行/边界截断）；段数写回 pArg3+40。
// ------------------------------------------------------------
int /*cdecl*/ sub_404B30(uint8_t *uArg1, const char *pArg2, int pArg3)  // 函数 超长文本按 1024 字节切片（200 段缓冲清 0 + 逐段拷贝，段内按 CR / 多字节字符边界截断）
{
  uint8_t *uArg12; // eax
  int i; // ecx
  unsigned int nLen; // eax
  bool v6; // zf
  int v7; // eax
  int v8; // esi
  char *v9; // esi
  const char *v10; // eax
  int v11; // edx
  char v12; // cl
  unsigned int psz; // ebx
  char v14; // al
  unsigned int v15; // esi
  int v16; // edx
  int v17; // edx
  bool v18; // cf
  int v20; // [esp+0h] [ebp-418h]
  unsigned int nLen2; // [esp+4h] [ebp-414h]
  int v22; // [esp+8h] [ebp-410h]
  char *Source; // [esp+Ch] [ebp-40Ch]
  int v24; // [esp+10h] [ebp-408h]
  char Destination[1024]; // [esp+14h] [ebp-404h] BYREF
  int dword_796E502; // [esp+414h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 = dword_796E50（栈检）
  uArg12 = uArg1;  // uArg12 = uArg1（输出缓冲）
  for ( i = 200; i != 0; --i )  // 循环 200 段
  {
    *uArg12 = 0;  // 每段首字节清 0
    uArg12 += 1024;  // 段指针 += 1024
  }
  v22 = 0;  // v22 = 0（段计数）
  nLen = strlen(pArg2);  // nLen = 源串长
  v6 = nLen == 0;  // v6 = 长度为 0
  nLen2 = nLen;  // nLen2 = 长度
  v7 = 0;  // v7 = 0（源偏移）
  v20 = 0;
  if ( v6 )  // 长度为 0
  {
    *(uint32_t *)(pArg3 + 40) = 0;  // pArg3+40 = 0（段数）
    return 0;
  }
  else  // 否则分支
  {
    v8 = 0;  // v8 = 0（输出偏移）
    v24 = 0;
    do  // 逐段
    {
      v9 = &uArg1[v8];  // v9 = 输出段起点
      v10 = &pArg2[v7];  // v10 = 源当前位置
      Source = v9;
      v11 = v9 - v10;  // v11 = 输出-源 偏移
      do  // 逐字符复制
      {
        v12 = *v10;  // v12 = 当前字符
        v10[v11] = *v10;  // 写输出（偏移寻址）
        ++v10;  // 源 ++
      }
      while ( v12 != 0 );  // 直到串尾
      psz = 0;  // psz = 0（段内偏移）
      if ( *v9 == 10 )  // 首个字符为 \n
      {
LABEL_62:
        v16 = psz + v24;  // v16 = 段尾偏移
        ++psz;  // psz ++
LABEL_66:
        uArg1[v16] = 0;  // 补串尾 0
      }
      else  // 否则分支
      {
        while ( 1 )  // 当 1 非 0 循环
        {
          v14 = v9[psz];  // v14 = 当前字符
          if ( v14 == 13 )  // 遇 \r
            break;  // 跳出
          if ( v14 < 0  // 多字节前导字节（<0 且属 0x81..0xFC 表）
            && (v14 == -127
             || v14 == -126  // GBK 双字节前导字节表项 -126
             || v14 == -125  // GBK 双字节前导字节表项 -125
             || v14 == -124  // GBK 双字节前导字节表项 -124
             || v14 == -121  // GBK 双字节前导字节表项 -121
             || v14 == -120  // GBK 双字节前导字节表项 -120
             || v14 == -119  // GBK 双字节前导字节表项 -119
             || v14 == -118  // GBK 双字节前导字节表项 -118
             || v14 == -117  // GBK 双字节前导字节表项 -117
             || v14 == -116  // GBK 双字节前导字节表项 -116
             || v14 == -115  // GBK 双字节前导字节表项 -115
             || v14 == -114  // GBK 双字节前导字节表项 -114
             || v14 == -113  // GBK 双字节前导字节表项 -113
             || v14 == -112  // GBK 双字节前导字节表项 -112
             || v14 == -111  // GBK 双字节前导字节表项 -111
             || v14 == -110  // GBK 双字节前导字节表项 -110
             || v14 == -109  // GBK 双字节前导字节表项 -109
             || v14 == -108  // GBK 双字节前导字节表项 -108
             || v14 == -107  // GBK 双字节前导字节表项 -107
             || v14 == -106  // GBK 双字节前导字节表项 -106
             || v14 == -105  // GBK 双字节前导字节表项 -105
             || v14 == -104  // GBK 双字节前导字节表项 -104
             || v14 == -103  // GBK 双字节前导字节表项 -103
             || v14 == -102  // GBK 双字节前导字节表项 -102
             || v14 == -101  // GBK 双字节前导字节表项 -101
             || v14 == -100  // GBK 双字节前导字节表项 -100
             || v14 == -99  // GBK 双字节前导字节表项 -99
             || v14 == -98  // GBK 双字节前导字节表项 -98
             || v14 == -97  // GBK 双字节前导字节表项 -97
             || v14 == -32  // GBK 双字节前导字节表项 -32
             || v14 == -31  // GBK 双字节前导字节表项 -31
             || v14 == -30  // GBK 双字节前导字节表项 -30
             || v14 == -29  // GBK 双字节前导字节表项 -29
             || v14 == -28  // GBK 双字节前导字节表项 -28
             || v14 == -27  // GBK 双字节前导字节表项 -27
             || v14 == -26  // GBK 双字节前导字节表项 -26
             || v14 == -25  // GBK 双字节前导字节表项 -25
             || v14 == -24  // GBK 双字节前导字节表项 -24
             || v14 == -23  // GBK 双字节前导字节表项 -23
             || v14 == -22  // GBK 双字节前导字节表项 -22
             || v14 == -19  // GBK 双字节前导字节表项 -19
             || v14 == -18  // GBK 双字节前导字节表项 -18
             || v14 == -6  // GBK 双字节前导字节表项 -6
             || v14 == -5  // GBK 双字节前导字节表项 -5
             || v14 == -4) )
          {
            memset(Destination, 0, sizeof(Destination));  // Destination 清零
            v15 = psz + 2;  // v15 = psz+2（双字节步进）
            strncpy(Destination, Source, psz + 2);  // strncpy 拷贝含双字节
            if ( (*(int (/*thiscall*/ **)(uint32_t, char *, uint32_t))(**(uint32_t **)(pArg3 + 48) + 24))(  // 调 pArg3+48 虚表 +24 槽回调（判换行/边界）
                   *(uint32_t *)(pArg3 + 48),
                   Destination,
                   *(uint32_t *)(pArg3 + 28)) != -1 )
            {
              uArg1[psz + v24] = 0;  // uArg1[psz+v24] = 0（段截断）
              goto LABEL_67;  // 跳 LABEL_67
            }
          }
          else  // 否则分支
          {
            memset(Destination, 0, sizeof(Destination));  // Destination 清零
            v15 = psz + 1;  // v15 = psz+1（单字节步进）
            strncpy(Destination, Source, psz + 1);  // strncpy 拷贝单字节
            if ( (*(int (/*thiscall*/ **)(uint32_t, char *, uint32_t))(**(uint32_t **)(pArg3 + 48) + 24))(  // 调回调判边界
                   *(uint32_t *)(pArg3 + 48),
                   Destination,
                   *(uint32_t *)(pArg3 + 28)) != -1 )
            {
              v16 = psz + v24;  // v16 = 段尾偏移
              goto LABEL_66;  // 跳 LABEL_66
            }
          }
          psz = v15;
          if ( v15 >= nLen2 )  // 段内达串尾
            goto LABEL_67;  // 跳 LABEL_67
          if ( Source[v15] == 10 )  // Source[v15] 为 \n
            goto LABEL_62;  // 跳 LABEL_62
          v9 = Source;
        }
        v17 = v24 + psz++;  // v17 = v24 + psz
        uArg1[v17] = 0;
        if ( uArg1[psz + v24] == 10 )  // 下一字符为 \n
          ++psz;  // psz ++
      }
LABEL_67:  // LABEL_67（段结束）
      v7 = psz + v20;  // v7 = psz + v20（源推进）
      ++v22;  // 段计数 ++
      v8 = v24 + 1024;
      v18 = psz + v20 < nLen2;  // v18 = 源未到串尾
      v20 += psz;
      v24 += 1024;
    }
    while ( v18 );  // 未到串尾继续
    *(uint32_t *)(pArg3 + 40) = v22;  // pArg3+40 = 段数 v22
    return v22;
  }
}


// ------------------------------------------------------------
// 0x404E30 sub_404E30 —— 文本测量结果换算（pArg1+12 模式分派: 1 = 居中 (总宽-5n)/2，2 = 右起 总宽-5n）
// gfx_texture.cpp 4195 处与 ·sub_404B30 返回值相加 —— 大文本布局宽度补偿【推断】。
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_404E30(int pArg1, int nArg2)  // 函数 文本测量结果换算（pArg1+12 模式分派: 1 = 居中 (总宽-5n)/2，2 = 右起 总宽-5n）
{
  int v2; // eax
  int v3; // eax
  int v5; // eax

  v2 = *(uint32_t *)(pArg1 + 12);  // v2 = pArg1+12（布局模式）
  if ( v2 != 0 )  // 模式非 0
  {
    v3 = v2 - 1;  // v3 = 模式-1
    if ( v3 != 0 )  // 非居中模式
    {
      if ( v3 == 1 )  // 模式 2（右起）
        return *(uint32_t *)(pArg1 + 28) - 5 * nArg2;  // 返回 总宽 - 5×字符数
    }
    else  // 否则分支
    {
      v5 = *(uint32_t *)(pArg1 + 28);  // v5 = pArg1+28（总宽）
      if ( v5 > 5 * nArg2 )  // 总宽 > 5×字符数
        return (unsigned int)(v5 - 5 * nArg2) >> 1;  // 返回 (总宽-5×字符数)/2（居中补偿）
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x404E70 sub_404E70
// ------------------------------------------------------------
// 【解读】
//   rdtsc 高精度时钟封装（__rdtsc + HIDWORD 拼装 + Sleep 校准循环）—— NiProfile 计时底层。
// ------------------------------------------------------------
int sub_404E70()
{
  unsigned int v18; // edi
  unsigned int v19; // esi
  uint64_t v24; // rax
  int64_t v25; // kr00_8
  BOOL v26; // ett
  bool v27; // zf
  uint64_t v37; // rax
  unsigned int v38; // esi
  int64_t v49; // [esp+Ch] [ebp-10h]
  unsigned int v50; // [esp+10h] [ebp-Ch]
  int v51; // [esp+18h] [ebp-4h]

  _EAX = 0;  // _EAX = 0/空
  v49 = 0;
  v51 = 200;
  do  // do 循环体
  {
    __asm
    {
      cpuid
      cpuid
      cpuid
      cpuid
    }
    _RAX = __rdtsc();
    v18 = HIDWORD(_RAX);
    v19 = _RAX;
    __asm
    {
      cpuid
      cpuid
    }
    v24 = __rdtsc() - __PAIR64__(v18, v19);
    v25 = v24 + v49;
    v26 = __CFADD__((uint32_t)v24, (uint32_t)v49);
    _EAX = v51 - 1;
    v27 = v51 == 1;
    LODWORD(v49) = v25;
    HIDWORD(v49) += HIDWORD(v24) + v26;
    --v51;  // v51 自减
  }
  while ( !v27 );
  _KR08_8 = v25 / 200;
  __asm
  {
    cpuid
    cpuid
  }
  v37 = __rdtsc();
  v50 = HIDWORD(v37);
  v38 = v37;
  Sleep(0x64u);  // 调 Sleep
  __asm
  {
    cpuid
    cpuid
  }
  memset(&dword_79CD40, 0, 0x320u);  // 调 memset
  memset(&dword_79CA20, 0, 0x320u);  // 调 memset
  dbl_79D070 = (double)(int64_t)(__rdtsc() - __PAIR64__(v50, v38) - v25 / 200) * 0.00001;
  memset(&dword_79C958, 0, 0xC8u);  // 调 memset
  return 0;
}



// ------------------------------------------------------------
// 0x404F40 sub_404F40 —— NiProfile 计时作用域进入（100 槽起点：rdtsc 双读打时间戳）
// uArg2 为 0..99 槽位；时间基准 dbl_79D070 未校准时先 ·sub_404E70；
// 写 dword_79CA20 槽对（64 位 rdtsc）—— 与 ·sub_404F80 成对。
// ------------------------------------------------------------
void /*usercall*/ sub_404F40(int _EAX@<eax>, unsigned int uArg2)  // 函数 NiProfile 计时作用域进入（100 槽起点：rdtsc 双读打时间戳）
{
  int16_t v2; // fps
  bool v3; // c0
  char v4; // c2
  bool v5; // c3
  uint64_t v14; // rax

  if ( uArg2 < 0x64 )
  {
    v3 = dbl_79D070 < 0.0;
    v4 = 0;
    v5 = dbl_79D070 == 0.0;
    LOWORD(_EAX) = v2;
    if ( dbl_79D070 == 0.0 )
      _EAX = sub_404E70();
    __asm
    {
      cpuid
      cpuid
    }
    v14 = __rdtsc();
    dword_79CA20[2 * uArg2] = v14;
    dword_79CA24[2 * uArg2] = HIDWORD(v14);
  }
}



// ------------------------------------------------------------
// 0x404F80 sub_404F80 —— NiProfile 计时作用域离开（槽耗时累计 = (rdtsc 差)/时间基准；pszArg3 非 0 先清零）
// 双精度折算耗时后累加进 dword_79CD40 槽对；
// ★ 与 ·sub_404F40 成对，槽值经 ·sub_405030 读出。
// ------------------------------------------------------------
void /*usercall*/ sub_404F80(int _EAX@<eax>, unsigned int uArg2, char pszArg3)  // 函数 NiProfile 计时作用域离开（槽耗时累计 = (rdtsc 差)/时间基准；pszArg3 非 0 先清零）
{
  int16_t v3; // fps
  bool v4; // c0
  char v5; // c2
  bool v6; // c3
  int64_t v16; // rcx
  uint64_t v17; // kr08_8

  if ( uArg2 < 0x64 )
  {
    v4 = dbl_79D070 < 0.0;
    v5 = 0;
    v6 = dbl_79D070 == 0.0;
    LOWORD(_EAX) = v3;
    if ( dbl_79D070 == 0.0 )
      _EAX = sub_404E70();
    __asm { cpuid }
    _EAX = 0;  // _EAX = 0/空
    if ( pszArg3 != 0 )  // 若 pszArg3 != 0
    {
      dword_79CD40[2 * uArg2] = 0;
      dword_79CD44[2 * uArg2] = 0;
    }
    __asm { cpuid }
    LODWORD(v16) = dword_79CA20[2 * uArg2];
    HIDWORD(v16) = dword_79CA24[2 * uArg2];
    v17 = (uint64_t)((double)(__rdtsc() - v16) / dbl_79D070)
        + __PAIR64__(dword_79CD44[2 * uArg2], dword_79CD40[2 * uArg2]);
    dword_79CD40[2 * uArg2] = v17;
    dword_79CD44[2 * uArg2] = HIDWORD(v17);
  }
}



// ------------------------------------------------------------
// 0x405030 sub_405030 —— NiProfile 槽耗时读取（uArg1 < 100 返回 dword_79CD40 槽值，否则 0）
// 与 ·sub_4050B0 同为只读访问器（后者读 50 槽计数表 dword_79C958）。
// ------------------------------------------------------------
int /*cdecl*/ sub_405030(unsigned int uArg1)  // 函数 NiProfile 槽耗时读取（uArg1 < 100 返回 dword_79CD40 槽值，否则 0）
{
  if ( uArg1 < 0x64 )
    return dword_79CD40[2 * uArg1];
  else  // 否则分支
    return 0;
}



// ------------------------------------------------------------
// 0x405060 sub_405060 —— 帧计数累加（uArg1 < 50：pszArg3==1 先清槽，再 += nArg2）
// 写 dword_79C958 槽（50 槽）；pszArg3 为 1 表示复位后再计。
// ------------------------------------------------------------
int /*cdecl*/ sub_405060(unsigned int uArg1, int nArg2, char pszArg3)  // 函数 帧计数累加（uArg1 < 50：pszArg3==1 先清槽，再 += nArg2）
{
  int result; // eax

  if ( uArg1 < 0x32 )
  {
    if ( dbl_79D070 == 0.0 )
      sub_404E70();  // 调 sub_404E70
    if ( pszArg3 == 1 )  // 若 pszArg3 == 1
      dword_79C958[uArg1] = 0;
    dword_79C958[uArg1] += nArg2;
    return nArg2;  // 返回入参
  }
  return result;
}



// ------------------------------------------------------------
// 0x4050B0 sub_4050B0 —— 帧计数读取（uArg1 >= 50 返回 0，否则取 dword_79C958 槽值）
// 读取前若时间基准未校准则先 ·sub_404E70 —— 与 ·sub_405060 写口成对。
// ------------------------------------------------------------
int /*cdecl*/ sub_4050B0(unsigned int uArg1)
{
  if ( uArg1 >= 0x32 )  // 若 uArg1 >= 0x32
    return 0;
  if ( dbl_79D070 == 0.0 )
    sub_404E70();  // 调 sub_404E70
  return dword_79C958[uArg1];
}



// ------------------------------------------------------------
// 0x4050F0 sub_4050F0 —— 30 槽句柄表构造（this+8 起 30 个 dword 清零，返回 this+8）
// ★ 由 ·0x4031E0 数学子系统构造调用；与 ·sub_405160（逐槽 DeleteObject）成对。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4050F0(uint32_t *this)  // 函数 30 槽句柄表构造（this+8 起 30 个 dword 清零，返回 this+8）
{
  *(this + 2) = 0;  // this+2 清 0
  *(this + 3) = 0;  // this+3 清 0
  *(this + 4) = 0;  // this+4 清 0
  *(this + 5) = 0;  // this+5 清 0
  *(this + 6) = 0;  // this+6 清 0
  *(this + 7) = 0;  // this+7 清 0
  *(this + 8) = 0;  // this+8 清 0
  *(this + 9) = 0;  // this+9 清 0
  *(this + 10) = 0;  // this+10 清 0
  *(this + 11) = 0;  // this+11 清 0
  *(this + 12) = 0;  // this+12 清 0
  *(this + 13) = 0;  // this+13 清 0
  *(this + 14) = 0;  // this+14 清 0
  *(this + 15) = 0;  // this+15 清 0
  *(this + 16) = 0;  // this+16 清 0
  *(this + 17) = 0;  // this+17 清 0
  *(this + 18) = 0;  // this+18 清 0
  *(this + 19) = 0;  // this+19 清 0
  *(this + 20) = 0;  // this+20 清 0
  *(this + 21) = 0;  // this+21 清 0
  *(this + 22) = 0;  // this+22 清 0
  *(this + 23) = 0;  // this+23 清 0
  *(this + 24) = 0;  // this+24 清 0
  *(this + 25) = 0;  // this+25 清 0
  *(this + 26) = 0;  // this+26 清 0
  *(this + 27) = 0;  // this+27 清 0
  *(this + 28) = 0;  // this+28 清 0
  *(this + 29) = 0;  // this+29 清 0
  *(this + 30) = 0;  // this+30 清 0
  *(this + 31) = 0;  // this+31 清 0
  return this + 2;
}



// ------------------------------------------------------------
// 0x405160 sub_405160 —— 30 槽句柄表释放（逐槽 DeleteObject 并置空，字节 +4 清零）
// ★ 由 ·0x403260 数学子系统析构调用；与 ·sub_4050F0 构造成对。
// ------------------------------------------------------------
HGDIOBJ */*thiscall*/ sub_405160(HGDIOBJ *this)  // 调 30 槽句柄表释放（逐槽 DeleteObject 并置空，字节 +4 清零）
{
  HGDIOBJ *pThis_2; // esi
  int i; // ebx

  pThis_2 = this + 2;
  for ( i = 30; i != 0; --i )
  {
    if ( *pThis_2 != nullptr )
    {
      DeleteObject(*pThis_2);  // 调 DeleteObject
      *pThis_2 = nullptr;  // 写指针 = nullptr
    }
    ++pThis_2;
  }
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  return this;
}



// ------------------------------------------------------------
// 0x4051A0 sub_4051A0 —— 帧时钟域初始化（基准 = timeGetTime；16 组三表清零：倍率 100 / 残留 0 / 累加 0）
// ★ 由 ·sub_403340 全局初始化链调用（srand 之后一步）；每帧由 ·sub_4052D0 推进。
// ------------------------------------------------------------
int sub_4051A0()  // 【tick_domains_init】
{
  dword_79D140 = timeGetTime();  // 基准帧时刻 = timeGetTime()
  dword_79D080 = 0;  // 域0 残留 g_tickFrac[0] = 0
  dword_79D100[0] = 0;  // 域0 时钟 g_domainTick[0] = 0
  dword_79D084 = 0;  // 域1 残留 = 0
  dword_79D104 = 0;  // 域1 时钟 = 0
  dword_79D088 = 0;  // 域2 残留 = 0
  dword_79D108 = 0;  // 域2 时钟 = 0
  dword_79D08C = 0;  // 域3 残留 = 0
  dword_79D10C = 0;  // 域3 时钟 = 0
  dword_79D0C0 = 100;  // 域0 倍率 g_tickRate[0] = 100
  dword_79D0C4 = 100;  // 域1 倍率 = 100
  dword_79D0C8 = 100;  // 域2 倍率 = 100
  dword_79D0CC = 100;  // 域3 倍率 = 100
  dword_79D090 = 0;  // 域4 残留 = 0
  dword_79D0D0 = 100;  // 域4 倍率 = 100
  dword_79D110 = 0;  // 域4 时钟 = 0
  dword_79D094 = 0;  // 域5 残留 = 0
  dword_79D0D4 = 100;  // 域5 倍率 = 100
  dword_79D114 = 0;  // 域5 时钟 = 0
  dword_79D098 = 0;  // 域6 残留 = 0
  dword_79D0D8 = 100;  // 域6 倍率 = 100
  dword_79D118 = 0;  // 域6 时钟 = 0
  dword_79D09C = 0;  // 域7 残留 = 0
  dword_79D0DC = 100;  // 域7 倍率 = 100
  dword_79D11C = 0;  // 域7 时钟 = 0
  dword_79D0A0 = 0;  // 域8 残留 = 0
  dword_79D0E0 = 100;  // 域8 倍率 = 100
  dword_79D120 = 0;  // 域8 时钟 = 0
  dword_79D0A4 = 0;  // 域9 残留 = 0
  dword_79D0E4 = 100;  // 域9 倍率 = 100
  dword_79D124 = 0;  // 域9 时钟 = 0
  dword_79D0A8 = 0;  // 域10 残留 = 0
  dword_79D0E8 = 100;  // 域10 倍率 = 100
  dword_79D128 = 0;  // 域10 时钟 = 0
  dword_79D0AC = 0;  // 域11 残留 = 0
  dword_79D0EC = 100;  // 域11 倍率 = 100
  dword_79D12C = 0;  // 域11 时钟 = 0
  dword_79D0B0 = 0;  // 域12 残留 = 0
  dword_79D0F0 = 100;  // 域12 倍率 = 100
  dword_79D130 = 0;  // 域12 时钟 = 0
  dword_79D0B4 = 0;  // 域13 残留 = 0
  dword_79D0F4 = 100;  // 域13 倍率 = 100
  dword_79D134 = 0;  // 域13 时钟 = 0
  dword_79D0B8 = 0;  // 域14 残留 = 0
  dword_79D0F8 = 100;  // 域14 倍率 = 100
  dword_79D138 = 0;  // 域14 时钟 = 0
  dword_79D0BC = 0;  // 域15 残留 = 0
  dword_79D0FC = 100;  // 域15 倍率 = 100
  dword_79D13C = 0;  // 域15 时钟 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x4052D0 sub_4052D0 —— 帧时钟域步进（按 timeGetTime 帧差推进 16 槽累加器，更新基准）
// 每槽 倍率*帧差*0.01 + 上次小数残留 → 整数累加、小数回写（不丢精度）；
// ★ WndProc WM_TIMER(0x113) 与 gfx_texture 帧循环调用 —— 帧驱动源。
// ------------------------------------------------------------
DWORD sub_4052D0()  // 【tick_domains_step】
{
  double dwNow; // st7
  int i; // esi
  double v2; // st6
  DWORD result; // eax
  int v4; // [esp+8h] [ebp-4h]

  dwNow = (double)(int)(timeGetTime() - dword_79D140);  // CRT 取系统毫秒计时（winmm）
  for ( i = 0; i < 16; *(float *)(i * 4 + 7983228) = v2 - (double)v4 )
  {
    v2 = (double)dword_79D0C0[i] * dwNow * 0.0099999998 + *(float *)(i * 4 + 7983232);
    v4 = (uint64_t)v2;  // v4 = 类型转换(v2)
    dword_79D100[i++] += v4;
  }
  result = timeGetTime();  // CRT 取系统毫秒计时（winmm）
  dword_79D140 = result;
  return result;
}



// ------------------------------------------------------------
// 0x405340 sub_405340 —— 全局缓冲释放（Block 与 dword_79D144..154 五表 free + 置空）
// ★ ·0x4010E0 全局关停清理链调用；·sub_405440 分配失败时亦回滚调用。
// ------------------------------------------------------------
int sub_405340()  // 函数 全局缓冲释放（Block 与 dword_79D144..154 五表 free + 置空）
{
  if ( Block != nullptr )  // 若 Block 非空
    j__free(Block);  // free 堆对象
  Block = nullptr;  // Block = 0/空
  if ( dword_79D154 != nullptr )  // 若 dword_79D154 非空
    j__free(dword_79D154);
  dword_79D154 = nullptr;  // dword_79D154 = 0/空
  if ( dword_79D150 != nullptr )  // 若 dword_79D150 非空
    j__free(dword_79D150);
  dword_79D150 = nullptr;  // dword_79D150 = 0/空
  if ( dword_79D14C != nullptr )  // 若 dword_79D14C 非空
    j__free(dword_79D14C);
  dword_79D14C = nullptr;  // dword_79D14C = 0/空
  if ( dword_79D148 != nullptr )  // 若 dword_79D148 非空
    j__free(dword_79D148);
  dword_79D148 = nullptr;  // dword_79D148 = 0/空
  if ( dword_79D144 != nullptr )  // 若 dword_79D144 非空
    j__free(dword_79D144);
  dword_79D144 = nullptr;  // dword_79D144 = 0/空
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x4053E0 sub_4053E0 —— sin 查表（dword_79D150 表，角度 %360 归一含负角修正）
// ★ 弹道散布/发射角计算族大量调用（passive_object / gunner_state / spider_trap 等）。
// ------------------------------------------------------------
double /*cdecl*/ sub_4053E0(int nArg1)  // 函数 sin 查表（dword_79D150 表，角度 %360 归一含负角修正）
{
  return *((float *)dword_79D150 + (nArg1 % 360 + 360) % 360);
}



// ------------------------------------------------------------
// 0x405400 sub_405400 —— cos 查表（dword_79D154 表，角度 %360 归一含负角修正）
// 与 ·sub_4053E0 成对；anim_parser / passive_object 散布向量分解使用。
// ------------------------------------------------------------
double /*cdecl*/ sub_405400(int nArg1)  // 函数 cos 查表（dword_79D154 表，角度 %360 归一含负角修正）
{
  return *((float *)dword_79D154 + (nArg1 % 360 + 360) % 360);
}



// ------------------------------------------------------------
// 0x405420 sub_405420 —— tan 查表（Block 表，角度 %360 归一含负角修正）
// equ_buff 等调用；三表由 ·sub_405440 一次构建。
// ------------------------------------------------------------
double /*cdecl*/ sub_405420(int nArg1)  // 函数 tan 查表（Block 表，角度 %360 归一含负角修正）
{
  return *((float *)Block + (nArg1 % 360 + 360) % 360);
}



// ------------------------------------------------------------
// 0x405440 sub_405440 —— 三角函数表构建（6 块 new(0x5A0) = 各 360 槽）
// dword_79D150/154/Block = sin/cos/tan(k 度) 主表，dword_79D144/148/14C 为 -90 度相移变体；
// ★ 由 ·sub_403340 初始化链调用；分配失败 ·sub_405340 回滚返回负值。
// ------------------------------------------------------------
int sub_405440()  // 函数 三角函数表构建（6 块 new(0x5A0) = 各 360 槽）
{
  float *v0; // ecx
  int v1; // edx
  int v2; // esi
  int v3; // edi
  int v4; // ebx
  double v5; // st7
  long double v6; // st7
  double v7; // st6
  int v9; // [esp+0h] [ebp-14h]
  int v10; // [esp+4h] [ebp-10h]
  long double v11; // [esp+8h] [ebp-Ch]
  int v12; // [esp+10h] [ebp-4h]

  if ( dword_79D144 != nullptr || dword_79D148 != nullptr || dword_79D14C != nullptr )
    return -2147483646;  // 返回 0x80000002（已初始化）
  dword_79D144 = operator new(0x5A0u);
  dword_79D148 = operator new(0x5A0u);
  dword_79D14C = operator new(0x5A0u);
  dword_79D150 = operator new(0x5A0u);
  dword_79D154 = operator new(0x5A0u);
  Block = operator new(0x5A0u);
  if ( dword_79D144 != nullptr && dword_79D148 != nullptr && dword_79D14C != nullptr )
  {
    v0 = (float *)dword_79D150;
    v10 = (uint8_t *)dword_79D14C - (uint8_t *)dword_79D150;
    v1 = 0;
    v2 = (uint8_t *)dword_79D144 - (uint8_t *)dword_79D150;
    v3 = (uint8_t *)dword_79D148 - (uint8_t *)dword_79D150;
    v4 = (uint8_t *)dword_79D154 - (uint8_t *)dword_79D150;
    v12 = 0;
    v9 = (uint8_t *)Block - (uint8_t *)dword_79D150;
    do  // do 循环体
    {
      v5 = (double)(v1 - 90);
      ++v1;  // v1 自增
      ++v0;  // v0 自增
      v6 = v5 * 0.0174532925199433;
      *(float *)((char *)v0 + v2 - 4) = sin(v6);
      v7 = (double)v12;  // v7 = 类型转换(v12)
      v12 = v1;
      v11 = v7 * 0.0174532925199433;
      *(v0 - 1) = sin(v11);
      *(float *)((char *)v0 + v3 - 4) = cos(v6);
      *(float *)((char *)v0 + v4 - 4) = cos(v11);
      *(float *)((char *)v0 + v10 - 4) = tan(v6);
      *(float *)((char *)v0 + v9 - 4) = tan(v11);
    }
    while ( v1 < 360 );  // 当 v1 < 360 循环
    return 1;  // 返回 1（成功）
  }
  else  // 否则分支
  {
    sub_405340();  // 调 sub_405340
    return -2147483640;  // 返回 0x80000008（内存不足）
  }
}



// ------------------------------------------------------------
// 0x4055B0 sub_4055B0 —— 像素填充 A（32 位色源截 5/6/5 位打包为 565 色，填 16 位缓冲）
// uArg3 为奇数时首像素单独写，其余按 32 位双像素 memset32 铺满；
// ·0x40FAC0 绘制循环逐行调用。
// ------------------------------------------------------------
int /*cdecl*/ sub_4055B0(uint16_t *uArg1, int nArg2, unsigned int uArg3, unsigned int uArg4)  // 函数 像素填充 A（32 位色源截 5/6/5 位打包为 565 色，填 16 位缓冲）
{
  unsigned int uArg42; // eax
  void *uArg12; // edi
  uint16_t v6; // ax
  int v7; // edx
  uint16_t v8; // bx
  int result; // eax

  uArg42 = uArg4;
  uArg12 = uArg1;
  if ( (uArg3 & 1) != 0 )  // 若位测试非 0
  {
    LOBYTE(v6) = 0;
    HIBYTE(v6) = uArg4 & 0xF8;
    uArg12 = uArg1 + 1;
    v7 = v6 | (uArg4 >> 19) & 0x1F | (uArg4 >> 5) & 0x7E0;
    uArg42 = uArg4;
    *uArg1 = v7;  // 写指针 = v7
  }
  LOBYTE(v8) = 0;
  HIBYTE(v8) = uArg42 & 0xF8;
  result = (uArg42 >> 5) & 0x7E0 | (uArg42 >> 19) & 0x1F | v8 | (((uArg42 >> 5) & 0x7E0 | (uArg42 >> 19) & 0x1F | v8) << 16);
  if ( uArg3 >> 1 != 0 )
    memset32(uArg12, result, uArg3 >> 1);
  return result;
}



// ------------------------------------------------------------
// 0x405630 sub_405630 —— 像素灰度 B（565 源按 R*0.222 + G*0.707 + B*0.071 亮度加权重打包，双像素并行）
// uArg3 为奇数时首像素单独处理；·0x40FB50 绘制循环逐行调用。
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_405630(uint16_t *uArg1, uint16_t *uArg2, unsigned int uArg3)  // 函数 像素灰度 B（565 源按 R*0.222 + G*0.707 + B*0.071 亮度加权重打包，双像素并行）
{
  uint16_t *uArg22; // esi
  uint16_t *uArg12; // ebx
  uint64_t v5; // rax
  unsigned int result; // eax
  double v7; // st7
  double v8; // st6
  uint16_t *v9; // esi
  uint64_t v10; // rax
  int v11; // edi
  double v12; // st7
  double v13; // st6
  uint64_t v14; // rax
  int v15; // [esp+14h] [ebp+8h]
  int v16; // [esp+14h] [ebp+8h]
  unsigned int v17; // [esp+1Ch] [ebp+10h]

  uArg22 = uArg2;
  uArg12 = uArg1;
  if ( (uArg3 & 1) != 0 )  // 若位测试非 0
  {
    uArg22 = uArg2 + 1;
    v5 = (uint64_t)((double)((uint8_t)HIBYTE(*uArg2) & 0xF8) * 0.222
                          + (double)(((uint16_t)*uArg2 >> 3) & 0xFC) * 0.707
                          + (double)(uint8_t)(8 * *uArg2) * 0.07099999999999999);
    uArg12 = uArg1 + 1;
    *uArg1 = ((unsigned int)v5 >> 3) | (8 * (v5 & 0xFC | (32 * (v5 & 0xFFF8))));
  }
  result = uArg3 >> 1;
  if ( uArg3 >> 1 != 0 )
  {
    v17 = uArg3 >> 1;
    do  // do 循环体
    {
      v7 = (double)((uint8_t)HIBYTE(*uArg22) & 0xF8) * 0.222;
      v8 = (double)(((uint16_t)*uArg22 >> 3) & 0xFC);
      v15 = (uint8_t)(8 * *uArg22);
      v9 = uArg22 + 1;
      v10 = (uint64_t)(v7 + v8 * 0.707 + (double)v15 * 0.07099999999999999);
      v11 = (uint16_t)((unsigned int)v10 >> 3) | (uint16_t)(8 * (v10 & 0xFC | (32 * (v10 & 0xFFF8))));
      v12 = (double)((uint8_t)HIBYTE(*v9) & 0xF8) * 0.222;
      v13 = (double)(((uint16_t)*v9 >> 3) & 0xFC);
      v16 = (uint8_t)(8 * *v9);
      uArg22 = v9 + 1;
      v14 = (uint64_t)(v12 + v13 * 0.707 + (double)v16 * 0.07099999999999999);
      uArg12 += 2;  // uArg12 前进 2
      *((uint32_t *)uArg12 - 1) = v11
                          | (((uint16_t)((unsigned int)v14 >> 3)
                            | (uint16_t)(8 * (v14 & 0xFC | (32 * (v14 & 0xFFF8))))) << 16);
      result = v17 - 1;
      v17 = result;
    }
    while ( result != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4057E0 sub_4057E0 —— 查表混合 C（逐 5 位分量以 源/目标低位索引 32×32 表 pArg4 后按 6 位步长打包）
// uArg3 为奇数时首像素单独处理；·0x40FBE0 绘制循环逐行调用（表由调用方提供）【推断】。
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_4057E0(unsigned int *pDwArg1, char *pszArg2, unsigned int uArg3, int pArg4)  // 函数 查表混合 C（逐 5 位分量以 源/目标低位索引 32×32 表 pArg4 后按 6 位步长打包）
{
  unsigned int uArg32; // ebx
  unsigned int *pDwArg12; // esi
  char *pszArg22; // edi
  unsigned int v7; // ebx
  unsigned int *result; // eax
  int v9; // edi
  unsigned int v10; // ecx
  unsigned int v11; // eax
  int *v12; // [esp+1Ch] [ebp+8h]
  int v13; // [esp+20h] [ebp+Ch]
  unsigned int v14; // [esp+24h] [ebp+10h]

  uArg32 = uArg3;
  pDwArg12 = pDwArg1;
  pszArg22 = pszArg2;
  if ( (uArg3 & 1) != 0 )  // 若位测试非 0
  {
    uArg32 = uArg3;
    pDwArg12 = (unsigned int *)((char *)pDwArg1 + 2);
    *(uint16_t *)pDwArg1 = *(uint16_t *)(pArg4 + 4 * ((*(uint16_t *)pszArg2 & 0x1F) + 32 * (*(uint16_t *)pDwArg1 & 0x1F)))
                 | ((*(uint16_t *)(pArg4 + 4 * (((*(uint16_t *)pszArg2 >> 6) & 0x1F) + 32 * ((*(uint16_t *)pDwArg1 >> 6) & 0x1F)))
                   | (uint16_t)(32
                                      * *(uint16_t *)(pArg4
                                                 + 4
                                                 * (((uint16_t)(*(uint16_t *)pszArg2 >> 6) >> 5)
                                                  + 32 * ((uint16_t)(*(uint16_t *)pDwArg1 >> 6) >> 5))))) << 6);
    pszArg22 = pszArg2 + 2;
  }
  v7 = uArg32 >> 1;
  result = pDwArg12;
  v12 = (int *)pDwArg12;
  if ( v7 != 0 )  // 若 v7 != 0
  {
    v9 = pszArg22 - (char *)pDwArg12;
    v13 = v9;
    v14 = v7;
    while ( 1 )  // 当 1 非 0 循环
    {
      v10 = *(unsigned int *)((char *)result + v9);
      v11 = *result;  // v11 = 解引用 result
      *v12 = *(uint32_t *)(pArg4 + 4 * ((v10 & 0x1F) + 32 * (v11 & 0x1F)))
           | ((*(uint32_t *)(pArg4 + 4 * (((v10 >> 6) & 0x1F) + 32 * ((v11 >> 6) & 0x1F)))
             | (32
              * (*(uint32_t *)(pArg4 + 4 * (((uint16_t)v10 >> 11) + 32 * ((uint16_t)v11 >> 11)))
               | (32
                * (*(uint32_t *)(pArg4 + 4 * ((HIWORD(v10) & 0x1F) + 32 * (HIWORD(v11) & 0x1F)))
                 | ((*(uint32_t *)(pArg4 + 4 * (((v10 >> 22) & 0x1F) + 32 * ((v11 >> 22) & 0x1F)))
                   | (32 * *(uint32_t *)(pArg4 + 4 * ((v10 >> 27) + 32 * (v11 >> 27))))) << 6)))))) << 6);
      result = (unsigned int *)++v12;
      if ( --v14 == 0 )
        break;  // 跳出 switch
      v9 = v13;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x405950 sub_405950
// ------------------------------------------------------------
// 【解读】
//   三角函数表构建（sin/cos/tan 查表初始化，172 行）—— sub_403340 初始化链一环。
// ------------------------------------------------------------
int sub_405950()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  int v3; // ebx
  double v4; // st4
  uint64_t v5; // rax
  unsigned int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // edx
  int v17; // eax
  uint64_t v18; // rax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  bool v22; // cc
  int v23; // edx
  int v24; // eax
  int v25; // esi
  int i; // edi
  int j; // ecx
  int v29; // [esp+Ch] [ebp-24h]
  int v30; // [esp+10h] [ebp-20h]
  int v31; // [esp+14h] [ebp-1Ch]
  int v32; // [esp+18h] [ebp-18h]
  int v33; // [esp+1Ch] [ebp-14h]
  int v34; // [esp+20h] [ebp-10h]
  int v35; // [esp+24h] [ebp-Ch]
  int v36; // [esp+28h] [ebp-8h]
  int v37; // [esp+2Ch] [ebp-4h]

  v0 = 0;
  v37 = 0;
  v29 = 0;
  v30 = 0;
  v32 = 32;
  while ( 1 )  // 当 1 非 0 循环
  {
    v1 = 0;
    v33 = 0;
    v34 = 0;
    v35 = 0;
    v2 = v37 << 12;
    while ( 1 )  // 当 1 非 0 循环
    {
      v31 = 0;
      v36 = 32 * v1;
      v3 = v2;
      do  // do 循环体
      {
        v4 = (double)v31;  // v4 = 类型转换(v31)
        v5 = (uint64_t)((double)v35 / (32.0 - v4));
        if ( (unsigned int)v5 > 0x1F )
          LODWORD(v5) = 31;
        *(int *)((char *)dword_87D160 + v3) = v5;
        v6 = v36 / (v37 + 32);
        if ( v6 >= 0x1F )  // 若 v6 >= 0x1F
          v6 = 31;
        *(int *)((char *)&dword_7DD160 + v3) = v6;
        v7 = v1;
        if ( v1 > v0 || (v7 = v0, v8 = v1, v1 >= v0) )
          v8 = v0;
        if ( (unsigned int)(v7 - v8 - v37 + 32) >= 0x1F )
        {
          v11 = 31;
        }
        else  // 否则分支
        {
          v9 = v1;
          if ( v1 > v0 || (v9 = v0, v10 = v1, v1 >= v0) )
            v10 = v0;
          v11 = v9 - v10 - v37 + 32;
        }
        *(int *)((char *)&dword_7BD160 + v3) = v11;
        v12 = v1;
        if ( v1 > v0 || (v12 = v0, v13 = v1, v1 >= v0) )
          v13 = v0;
        v14 = v13 * ((32 - v12) / 32);
        v15 = v0 + v37;
        v16 = v1;
        if ( v1 <= v0 + v37 )
          v16 = v0 + v37;
        if ( v14 + v16 >= 31 )
        {
          v17 = 31;
        }
        else  // 否则分支
        {
          if ( v1 > v15 )
            v15 = v1;
          v17 = v15 + v14;
        }
        *(int *)((char *)dword_83D160 + v3) = v17;
        v18 = (uint64_t)(v4 * ((double)v37 * 0.03125) + (double)v34 * 0.03125);
        if ( (unsigned int)v18 >= 0x20 )
          LODWORD(v18) = 32;
        *(int *)((char *)&dword_79D160 + v3) = v18;
        v19 = v1;
        if ( v1 <= v0 )
          v19 = v0;
        if ( v37 + v19 >= 31 )
        {
          v21 = 31;
        }
        else  // 否则分支
        {
          v20 = v1;
          if ( v1 <= v0 )
            v20 = v0;
          v21 = v37 + v20;
        }
        ++v0;  // v0 自增
        *(int *)((char *)&dword_85D160 + v3) = v21;
        v3 += 4;  // v3 前进 4
        v31 = v0;
        v36 += v33;
      }
      while ( v0 < 32 );  // 当 v0 < 32 循环
      v2 = v3;
      v35 += v37;
      ++v1;  // v1 自增
      v22 = v33 - 1 <= -32;
      v34 += v32;
      --v33;  // v33 自减
      if ( v22 )
        break;  // 跳出 switch
      v0 = 0;
    }
    v23 = v30;
    v24 = v29;
    v25 = 32 * v37;
    for ( i = 32; i != 0; --i )
    {
      for ( j = 0; j < 32; j += 4 )
      {
        *(int *)((char *)&dword_7FD160 + v24) = dword_87D160[32 * v25 + 32 * *(int *)((char *)dword_83D160 + v24) + j];
        *(int *)((char *)&dword_81D160 + v24) = dword_83D160[v23 + *(int *)((char *)dword_87D160 + v24)];
        *(int *)((char *)&dword_7FD164 + v24) = dword_87D164[32 * v25 + 32 * *(int *)((char *)&dword_83D164 + v24) + j];
        *(int *)((char *)&dword_81D164 + v24) = dword_83D160[v23 + *(int *)((char *)dword_87D164 + v24)];
        *(int *)((char *)&dword_7FD168 + v24) = dword_87D168[32 * v25 + 32 * *(int *)((char *)&dword_83D168 + v24) + j];
        *(int *)((char *)&dword_81D168 + v24) = dword_83D160[v23 + *(int *)((char *)dword_87D168 + v24)];
        *(int *)((char *)&dword_7FD16C + v24) = dword_87D16C[32 * v25 + 32 * *(int *)((char *)&dword_83D16C + v24) + j];
        *(int *)((char *)&dword_81D16C + v24) = dword_83D160[v23 + *(int *)((char *)dword_87D16C + v24)];
        v24 += 16;  // v24 前进 16
      }
      v23 += 32;  // v23 前进 32
    }
    v22 = v32 - 1 <= 0;
    ++v37;  // v37 自增
    --v32;  // v32 自减
    v30 = v23;
    v29 = v24;
    if ( v22 )
      break;  // 跳出 switch
    v0 = 0;
  }
  return 1;  // 返回 1（成功）
}


// ============================================================
// SECTION 0x405C20 — 窗口类注册与创建 / GDI 图标位图工具
// ============================================================
// ------------------------------------------------------------
// 0x405C20 sub_405C20
// ------------------------------------------------------------
// 【解读】
//   窗口类注册+主窗口创建: LoadIconA/RegisterClassExA/SetRect/AdjustWindowRect/LoadMenuA/CreateWindowExA/SetWindowTextA。
// ------------------------------------------------------------
int /*thiscall*/ sub_405C20(LONG dwNewLong, int nArg2, uint16_t uArg3, uint16_t uArg4, int nArg5)  // 【窗口类注册与创建 / GDI 图标位图工具】
{
  HBRUSH StockObject; // eax
  const CHAR *v7; // ecx
  DWORD v9; // edi
  int v10; // edx
  HWND Window; // eax
  HINSTANCE v12; // [esp-8h] [ebp-50h]
  WNDCLASSEXA pBuf; // [esp+8h] [ebp-40h] BYREF
  struct tagRECT rc; // [esp+38h] [ebp-10h] BYREF

  memset(&pBuf, 0, sizeof(pBuf));  // 调 memset
  v12 = *(HINSTANCE *)(dwNewLong + 20);
  pBuf.cbSize = 48;
  pBuf.hInstance = v12;
  pBuf.cbClsExtra = 0;
  pBuf.cbWndExtra = 40;
  pBuf.style = 11;
  pBuf.hIcon = LoadIconA(v12, (LPCSTR)uArg3);
  pBuf.hIconSm = LoadIconA(*(HINSTANCE *)(dwNewLong + 20), (LPCSTR)uArg4);
  StockObject = (HBRUSH)GetStockObject(4);
  v7 = *(const CHAR **)(dwNewLong + 60);
  pBuf.hbrBackground = StockObject;
  pBuf.lpszClassName = v7;
  pBuf.lpfnWndProc = sub_4042E0;  // 调 窗口过程转发器（GWLP_USERDATA 取管理器对象 → 虚表槽 32 转发；无则 DefWindowProcA 兜底）
  if ( RegisterClassExA(&pBuf) == 0 )
    return 0;
  v9 = 0;
  switch ( *(uint32_t *)(dwNewLong + 8) )
  {
    case 1:  // case 分支 1
    case 2:  // case 分支 2
      v9 = 0x80000000;
      break;  // 跳出 switch
    case 3:  // case 分支 3
    case 4:  // case 分支 4
      v9 = 13565952;
      SetRect(&rc, 0, 0, *(uint32_t *)(dwNewLong + 44), *(uint32_t *)(dwNewLong + 48));
      AdjustWindowRect(&rc, (DWORD)&unk_840000, true);
      v10 = rc.bottom - rc.top;
      *(uint32_t *)(dwNewLong + 44) = rc.right - rc.left;  // dwNewLong+44 = rc.right - rc.left
      *(uint32_t *)(dwNewLong + 48) = v10;  // dwNewLong+48 = v10
      break;  // 跳出 switch
    default:  // 默认分支
      break;  // 跳出 switch
  }
  if ( nArg2 != 0 )  // 若 nArg2 != 0
    *(uint32_t *)(dwNewLong + 24) = LoadMenuA(*(HINSTANCE *)(dwNewLong + 20), (LPCSTR)(uint16_t)nArg2);  // dwNewLong+24 = LoadMenuA(*(HINSTANCE *)(dwNewLong + 20), (LPCSTR)(uint16_t)nArg2)
  Window = CreateWindowExA(
             0,
             *(LPCSTR *)(dwNewLong + 60),
             *(LPCSTR *)(dwNewLong + 80),
             v9,
             *(uint32_t *)(dwNewLong + 36),
             *(uint32_t *)(dwNewLong + 40),
             *(uint32_t *)(dwNewLong + 44),
             *(uint32_t *)(dwNewLong + 48),
             nullptr,
             *(HMENU *)(dwNewLong + 24),
             *(HINSTANCE *)(dwNewLong + 20),
             nullptr);
  *(uint32_t *)(dwNewLong + 16) = Window;  // dwNewLong+16 = Window
  if ( Window == nullptr )  // 若 Window 为空
    return 0x80000000;  // 返回 0x80000000（失败）
  SetWindowLongA(Window, 0, dwNewLong);  // 调 SetWindowLongA
  SetWindowTextA(*(HWND *)(dwNewLong + 16), *(LPCSTR *)(dwNewLong + 80));
  hWnd = *(HWND *)(dwNewLong + 16);
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x405DA0 sub_405DA0 —— 窗口对象销毁（DestroyMenu(+24) + ShowWindow/DestroyWindow(+16) + UnregisterClassA(类名+60)）
// 三句柄字段逐项销毁并置空 —— 窗口框架退出路径。
// ------------------------------------------------------------
int /*thiscall*/ sub_405DA0(int this)  // 函数 窗口对象销毁（DestroyMenu(+24) + ShowWindow/DestroyWindow(+16) + Unregister…
{
  HWND fld_10; // eax
  int result; // eax

  if ( *(uint32_t *)(this + 24) != 0 )  // 若 this 偏移 24 非 0
  {
    DestroyMenu(*(HMENU *)(this + 24));
    *(uint32_t *)(this + 24) = 0;  // this+24（uint32 槽）= 0
  }
  fld_10 = *(HWND *)(this + 16);
  if ( fld_10 != nullptr )  // 若 fld_10 非空
  {
    ShowWindow(fld_10, 0);  // 调 ShowWindow
    DestroyWindow(*(HWND *)(this + 16));  // 调 DestroyWindow
    *(uint32_t *)(this + 16) = 0;  // this+16（uint32 槽）= 0
  }
  result = *(uint32_t *)(this + 20);
  if ( result != 0 )  // 若 result != 0
  {
    result = UnregisterClassA(*(LPCSTR *)(this + 60), *(HINSTANCE *)(this + 20));
    *(uint32_t *)(this + 20) = 0;  // this+20（uint32 槽）= 0
  }
  return result;
}



// ============================================================
// SECTION 0x405E00 — 引擎子系统事件分发框架（list/vector 容器事件路由，0x405E00-0x406C50）
// ============================================================
// ------------------------------------------------------------
// 0x405E00 sub_405E00 —— 事件分发对象构造 A（挂 off_6C1948 虚表 + ·sub_407AD0 初始化）
// +8 = nArg2 宿主 / +20 哨兵指针（this+16 自指节点）/ +28 = nArg3。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_405E00(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 A（挂 off_6C1948 虚表 + ·sub_407AD0 初始化）
{
  char *pThis_10; // edi

  *(this + 4) = 0;  // this+4 清 0
  pThis_10 = this + 16;
  *(uint32_t *)this = &off_6C1948;  // vftable = off_6C1948
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  *((uint32_t *)this + 5) = sub_425940(this + 16);  // this 偏移 20 = sub_425940(this+16)
  *((uint32_t *)pThis_10 + 2) = 0;
  *((uint32_t *)this + 7) = nArg3;  // this 偏移 28 = 参数3
  sub_407AD0(this);  // 调 sub_407AD0
  return this;
}



// ------------------------------------------------------------
// 0x405E70 sub_405E70 —— 事件分发对象析构 A（虚表还原 + ·sub_407B20 停止 + 链表清 + 回落 IObject::vftable）
// ·sub_6569D0 清 this+16 链并 free 哨兵指针（+20）；与 ·sub_405E00 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_405E70(void **this)  // 函数 事件分发对象析构 A（虚表还原 + ·sub_407B20 停止 + 链表清 + 回落 IObject::vftable）
{
  *this = &off_6C1948;  // vftable = off_6C1948
  sub_407B20();  // 调 sub_407B20
  sub_6569D0(this + 4);
  j__free(*(this + 5));  // free this+5
  *(this + 5) = nullptr;  // this+5 = 空指针
  *this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x405EE0 sub_405EE0 —— 事件分发对象删除壳 A（·sub_405E70 + 低位置位 free）
// 与 ·sub_405E00 族配对的标准删除壳。
// ------------------------------------------------------------
void **/*thiscall*/ sub_405EE0(void **Block, char pszArg2)  // 函数 事件分发对象删除壳 A（·sub_405E70 + 低位置位 free）
{
  sub_405E70(Block);  // 调 sub_405E70
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x405F10 sub_405F10 —— 事件分发对象构造 B（挂 off_6C1960 虚表 + ·sub_407CF0 初始化）
// +8 = nArg2 / +36 = nArg3 / +40 自指哨兵（指针存 +44）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_405F10(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 B（挂 off_6C1960 虚表 + ·sub_407CF0 初始化）
{
  char *pThis_28; // edi

  *(this + 4) = 0;  // this+4 清 0
  *((uint32_t *)this + 9) = nArg3;  // this 偏移 36 = 参数3
  pThis_28 = this + 40;
  *(uint32_t *)this = &off_6C1960;  // vftable = off_6C1960
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  *((uint32_t *)this + 11) = sub_425940(this + 40);  // this 偏移 44 = sub_425940(this+40)
  *((uint32_t *)pThis_28 + 2) = 0;
  sub_407CF0(this);  // 调 sub_407CF0
  return this;
}



// ------------------------------------------------------------
// 0x405F80 sub_405F80 —— 事件分发对象析构 B（虚表还原 + ·sub_407C90 状态复位 + 链表清 + IObject 回落）
// ·sub_6569D0 清 this+40 链并 free 哨兵指针（+44）；与 ·sub_405F10 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_405F80(void **this)  // 函数 事件分发对象析构 B（虚表还原 + ·sub_407C90 状态复位 + 链表清 + IObject 回落）
{
  *this = &off_6C1960;  // vftable = off_6C1960
  sub_407C90();  // 调 sub_407C90
  sub_6569D0(this + 10);
  j__free(*(this + 11));  // free this+11
  *(this + 11) = nullptr;  // this+11 = 空指针
  *this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x405FF0 sub_405FF0 —— 事件分发对象删除壳 B（·sub_405F80 + 低位置位 free）
// 与 ·sub_405F10 族配对的标准删除壳。
// ------------------------------------------------------------
void **/*thiscall*/ sub_405FF0(void **Block, char pszArg2)  // 函数 事件分发对象删除壳 B（·sub_405F80 + 低位置位 free）
{
  sub_405F80(Block);  // 调 sub_405F80
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x406020 sub_406020 —— 事件分发对象构造 C（挂 off_6C19A0 虚表 + ·sub_407E80 链表清）
// +8 = nArg2 / +12 = nArg3 / +16 自指哨兵（指针存 +20）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406020(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 C（挂 off_6C19A0 虚表 + ·sub_407E80 链表清）
{
  char *pThis_10; // edi

  *(this + 4) = 0;  // this+4 清 0
  *((uint32_t *)this + 3) = nArg3;  // this 偏移 12 = 参数3
  pThis_10 = this + 16;
  *(uint32_t *)this = &off_6C19A0;  // vftable = off_6C19A0
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  *((uint32_t *)this + 5) = sub_425940(this + 16);  // this 偏移 20 = sub_425940(this+16)
  *((uint32_t *)pThis_10 + 2) = 0;
  sub_407E80(this);  // 调 sub_407E80
  return this;
}



// ------------------------------------------------------------
// 0x406090 sub_406090 —— 事件分发对象析构 C（虚表还原 + ·sub_416420 基类析构 + 链表清 + IObject 回落）
// ·sub_416420 = 虚表槽 36 调用 + 字节 +4 清零；与 ·sub_406020 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_406090(void **this)  // 函数 事件分发对象析构 C（虚表还原 + ·sub_416420 基类析构 + 链表清 + IObject 回落）
{
  *this = &off_6C19A0;  // vftable = off_6C19A0
  sub_416420();  // 调 sub_416420
  sub_6569D0(this + 4);
  j__free(*(this + 5));  // free this+5
  *(this + 5) = nullptr;  // this+5 = 空指针
  *this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x406100 sub_406100 —— 事件分发对象删除壳 C（·sub_406090 + 低位置位 free）
// 与 ·sub_406020 族配对的标准删除壳。
// ------------------------------------------------------------
void **/*thiscall*/ sub_406100(void **Block, char pszArg2)  // 函数 事件分发对象删除壳 C（·sub_406090 + 低位置位 free）
{
  sub_406090(Block);  // 调 sub_406090
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x406130 sub_406130 —— 事件分发对象构造 D（挂 off_6C19C8 虚表 + 双哨兵链 + ·sub_408060 初始化）
// +8 = nArg2 / +32 = nArg3 / +36 与 +48 两条自指哨兵链（指针存 +40/+52）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406130(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 D（挂 off_6C19C8 虚表 + 双哨兵链 + ·sub_408060 初始化）
{
  char *pThis_24; // edi

  *(this + 4) = 0;  // this+4 清 0
  *((uint32_t *)this + 8) = nArg3;  // this 偏移 32 = 参数3
  pThis_24 = this + 36;
  *(uint32_t *)this = &off_6C19C8;  // vftable = off_6C19C8
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  *((uint32_t *)this + 10) = sub_425940(this + 36);  // this 偏移 40 = sub_425940(this+36)
  *((uint32_t *)pThis_24 + 2) = 0;
  *((uint32_t *)this + 13) = sub_425940(this + 48);  // this 偏移 52 = sub_425940(this+48)
  *((uint32_t *)this + 14) = 0;  // this 偏移 56 清 0
  sub_408060(this);  // 调 sub_408060
  return this;
}



// ------------------------------------------------------------
// 0x4061C0 sub_4061C0 —— 事件分发对象析构 D（虚表还原 + ·sub_408050 槽清理 + 双链表清 + IObject 回落）
// 两条链（+36/+48）分别经 ·sub_6569D0 清空；与 ·sub_406130 成对。
// ------------------------------------------------------------
void /*thiscall*/ sub_4061C0(void **this)  // 函数 事件分发对象析构 D（虚表还原 + ·sub_408050 槽清理 + 双链表清 + IObject 回落）
{
  *this = &off_6C19C8;  // vftable = off_6C19C8
  sub_408050();  // 调 sub_408050
  sub_6569D0(this + 12);
  j__free(*(this + 13));  // free this+13
  *(this + 13) = nullptr;  // this+13 = 空指针
  sub_6569D0(this + 9);
  j__free(*(this + 10));  // free this+10
  *(this + 10) = nullptr;  // this+10 = 空指针
  *this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
}



// ------------------------------------------------------------
// 0x406250 sub_406250 —— 事件分发对象删除壳 D（·sub_4061C0 + 低位置位 free）
// 与 ·sub_406130 族配对的标准删除壳。
// ------------------------------------------------------------
void **/*thiscall*/ sub_406250(void **Block, char pszArg2)  // 函数 事件分发对象删除壳 D（·sub_4061C0 + 低位置位 free）
{
  sub_4061C0(Block);  // 调 sub_4061C0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x406280 sub_406280 —— 事件分发对象构造 E（·sub_405F10 装配后改挂 off_6C19E8 + ·sub_408AC0 初始化）
// ·sub_408AC0 写 +8=3 / +52 / +8248 等大对象状态 —— 渲染与文本宿主【推断】。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406280(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 E（·sub_405F10 装配后改挂 off_6C19E8 + ·sub_408AC0 初始化）
{
  sub_405F10(this, nArg2, nArg3);  // 调 sub_405F10
  *(uint32_t *)this = &off_6C19E8;  // vftable = off_6C19E8
  sub_408AC0(this);  // 调 sub_408AC0
  return this;
}



// ------------------------------------------------------------
// 0x4062E0 sub_4062E0 —— 事件分发对象删除壳 E（·sub_406310 + 低位置位 free）
// 与 ·sub_406280 族配对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_4062E0(void *Block, char pszArg2)  // 函数 事件分发对象删除壳 E（·sub_406310 + 低位置位 free）
{
  sub_406310();  // 调 sub_406310
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x406310 sub_406310 —— 事件分发对象析构 E（虚表改回 off_6C19E8 + ·sub_407C90 + 回落 ·sub_405F80）
// 与 ·sub_406280 成对；三级回落链 E → B → IObject。
// ------------------------------------------------------------
int /*thiscall*/ sub_406310(void **this)  // 函数 事件分发对象析构 E（虚表改回 off_6C19E8 + ·sub_407C90 + 回落 ·sub_405F80）
{
  *this = &off_6C19E8;  // vftable = off_6C19E8
  sub_407C90();  // 调 sub_407C90
  return sub_405F80(this);  // 调 事件分发对象析构 B（虚表还原 + ·sub_407C90 状态复位 + 链表清 + IObject 回落）
}



// ------------------------------------------------------------
// 0x406360 sub_406360 —— 事件分发对象构造 F（·sub_406130 装配后改挂 off_6C1A44 + ·sub_40AA10 初始化）
// ·sub_40AA10 写 +8=1 / +60 / +64 清零 —— 与 ·sub_406440 同父族。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406360(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 F（·sub_406130 装配后改挂 off_6C1A44 + ·sub_40AA10 初始化）
{
  sub_406130(this, nArg2, nArg3);  // 调 sub_406130
  *(uint32_t *)this = &off_6C1A44;  // vftable = off_6C1A44
  sub_40AA10(this);  // 调 sub_40AA10
  return this;
}



// ------------------------------------------------------------
// 0x4063C0 sub_4063C0 —— 事件分发对象删除壳 F（·sub_4063F0 + 低位置位 free）
// 与 ·sub_406360 族配对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_4063C0(void *Block, char pszArg2)  // 函数 事件分发对象删除壳 F（·sub_4063F0 + 低位置位 free）
{
  sub_4063F0();  // 调 sub_4063F0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x4063F0 sub_4063F0 —— 事件分发对象析构 F（虚表改回 off_6C1A44 + ·sub_408050 + 回落 ·sub_4061C0）
// 与 ·sub_406360 成对。
// ------------------------------------------------------------
void /*thiscall*/ sub_4063F0(void **this)  // 函数 事件分发对象析构 F（虚表改回 off_6C1A44 + ·sub_408050 + 回落 ·sub_4061C0）
{
  *this = &off_6C1A44;  // vftable = off_6C1A44
  sub_408050();  // 调 sub_408050
  sub_4061C0(this);  // 调 sub_4061C0
}



// ------------------------------------------------------------
// 0x406440 sub_406440 —— 事件分发对象构造 G（·sub_406130 装配后改挂 off_6C1A60 + ·sub_40AE80 初始化）
// ·sub_40AE80 仅写 +8=2；与 ·sub_406360 同父族（差异：虚表常量与初始化体）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406440(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 G（·sub_406130 装配后改挂 off_6C1A60 + ·sub_40AE80 初始化）
{
  sub_406130(this, nArg2, nArg3);  // 调 sub_406130
  *(uint32_t *)this = &off_6C1A60;  // vftable = off_6C1A60
  sub_40AE80(this);  // 调 sub_40AE80
  return this;
}



// ------------------------------------------------------------
// 0x4064A0 sub_4064A0 —— 事件分发对象删除壳 G（·sub_4064D0 + 低位置位 free）
// 与 ·sub_406440 族配对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_4064A0(void *Block, char pszArg2)  // 函数 事件分发对象删除壳 G（·sub_4064D0 + 低位置位 free）
{
  sub_4064D0();  // 调 sub_4064D0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x4064D0 sub_4064D0 —— 事件分发对象析构 G（虚表改回 off_6C1A60 + ·sub_408050 + 回落 ·sub_4061C0）
// 与 ·sub_406440 成对；与 ·sub_4063F0 逐行同构（差异仅虚表常量）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4064D0(void **this)  // 函数 事件分发对象析构 G（虚表改回 off_6C1A60 + ·sub_408050 + 回落 ·sub_4061C0）
{
  *this = &off_6C1A60;  // vftable = off_6C1A60
  sub_408050();  // 调 sub_408050
  sub_4061C0(this);  // 调 sub_4061C0
}



// ------------------------------------------------------------
// 0x406520 sub_406520 —— 事件分发对象构造 H（·sub_406020 装配后改挂 off_6C1A7C + ·sub_40B130 初始化）
// ·sub_40B130 仅写 +28=0；与 ·sub_406600 同父族。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406520(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 H（·sub_406020 装配后改挂 off_6C1A7C + ·sub_40B130 初始化）
{
  sub_406020(this, nArg2, nArg3);  // 调 sub_406020
  *(uint32_t *)this = &off_6C1A7C;  // vftable = off_6C1A7C
  sub_40B130(this);  // 调 sub_40B130
  return this;
}



// ------------------------------------------------------------
// 0x406580 sub_406580 —— 事件分发对象删除壳 H（·sub_4065B0 + 低位置位 free）
// 与 ·sub_406520 族配对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_406580(void *Block, char pszArg2)  // 函数 事件分发对象删除壳 H（·sub_4065B0 + 低位置位 free）
{
  sub_4065B0();  // 调 sub_4065B0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x4065B0 sub_4065B0 —— 事件分发对象析构 H（虚表改回 off_6C1A7C + ·sub_416420 + 回落 ·sub_406090）
// 与 ·sub_406520 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4065B0(void **this)  // 函数 事件分发对象析构 H（虚表改回 off_6C1A7C + ·sub_416420 + 回落 ·sub_406090）
{
  *this = &off_6C1A7C;  // vftable = off_6C1A7C
  sub_416420();  // 调 sub_416420
  return sub_406090(this);  // 调 事件分发对象析构 C（虚表还原 + ·sub_416420 基类析构 + 链表清 + IObject 回落）
}



// ------------------------------------------------------------
// 0x406600 sub_406600 —— 事件分发对象构造 I（·sub_406020 装配后改挂 off_6C1AA4 + nullsub_3 空初始化）
// 与 ·sub_406520 同父族（差异仅虚表常量与空初始化钩子）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406600(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 I（·sub_406020 装配后改挂 off_6C1AA4 + nullsub_3 空初始化）
{
  sub_406020(this, nArg2, nArg3);  // 调 sub_406020
  *(uint32_t *)this = &off_6C1AA4;  // vftable = off_6C1AA4
  nullsub_3(this);  // nullsub（空桩）
  return this;
}



// ------------------------------------------------------------
// 0x406660 sub_406660 —— 事件分发对象删除壳 I（·sub_406690 + 低位置位 free）
// 与 ·sub_406600 族配对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_406660(void *Block, char pszArg2)  // 函数 事件分发对象删除壳 I（·sub_406690 + 低位置位 free）
{
  sub_406690();  // 调 sub_406690
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x406690 sub_406690 —— 事件分发对象析构 I（虚表改回 off_6C1AA4 + ·sub_416420 + 回落 ·sub_406090）
// 与 ·sub_406600 成对；与 ·sub_4065B0 逐行同构（差异仅虚表常量）。
// ------------------------------------------------------------
int /*thiscall*/ sub_406690(void **this)  // 函数 事件分发对象析构 I（虚表改回 off_6C1AA4 + ·sub_416420 + 回落 ·sub_406090）
{
  *this = &off_6C1AA4;  // vftable = off_6C1AA4
  sub_416420();  // 调 sub_416420
  return sub_406090(this);  // 调 事件分发对象析构 C（虚表还原 + ·sub_416420 基类析构 + 链表清 + IObject 回落）
}



// ------------------------------------------------------------
// 0x4066E0 sub_4066E0 —— 事件分发对象构造 J（·sub_405E00 装配后改挂 off_6C1ACC + nullsub_3）
// off_6C1948 族的派生变体 —— 与 ·sub_405E00 同父族。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4066E0(uint8_t *this, int nArg2, int nArg3)  // 函数 事件分发对象构造 J（·sub_405E00 装配后改挂 off_6C1ACC + nullsub_3）
{
  sub_405E00(this, nArg2, nArg3);  // 调 sub_405E00
  *(uint32_t *)this = &off_6C1ACC;  // vftable = off_6C1ACC
  nullsub_3(this);  // nullsub（空桩）
  return this;
}



// ------------------------------------------------------------
// 0x406740 sub_406740 —— 事件分发对象删除壳 J（·sub_406770 + 低位置位 free）
// 与 ·sub_4066E0 族配对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_406740(void *Block, char pszArg2)  // 函数 事件分发对象删除壳 J（·sub_406770 + 低位置位 free）
{
  sub_406770();  // 调 sub_406770
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x406770 sub_406770 —— 事件分发对象析构 J（虚表改回 off_6C1ACC + ·sub_407B20 + 回落 ·sub_405E70）
// 与 ·sub_4066E0 成对；三级回落链 J → A → IObject。
// ------------------------------------------------------------
int /*thiscall*/ sub_406770(void **this)  // 函数 事件分发对象析构 J（虚表改回 off_6C1ACC + ·sub_407B20 + 回落 ·sub_405E70）
{
  *this = &off_6C1ACC;  // vftable = off_6C1ACC
  sub_407B20();  // 调 sub_407B20
  return sub_405E70(this);  // 调 事件分发对象析构 A（虚表还原 + ·sub_407B20 停止 + 链表清 + 回落 IObject::vftable）
}



// ------------------------------------------------------------
// 0x4067C0 sub_4067C0
// ------------------------------------------------------------
// 【解读】
//   std::length_error("list<T> too long") 抛出器（list 模板实例）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4067C0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // fld_e2 = this+2 字段
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // 调 sub_401740
    pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+2 = result
  return result;
}



// ------------------------------------------------------------
// 0x406850 sub_406850 —— 链表节点插入（·sub_40C0F0 建 12 字节节点挂入哨兵环）
// this 为哨兵指针槽、计数在 +4；·sub_4067C0 做 list too long 溢出检查；
// 被 ·sub_406970 / ·sub_406B80 调用，·sub_406890 / ·sub_406A80 内联同一序列。
// ------------------------------------------------------------
int /*thiscall*/ sub_406850(uint32_t *this, int nArg2)  // 函数 链表节点插入（·sub_40C0F0 建 12 字节节点挂入哨兵环）
{
  int fld_e1; // edi
  int v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), nArg2);  // v4 = sub_40C0F0(...)
  result = sub_4067C0(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;  // fld_e1+4 = v4
  **(uint32_t **)(v4 + 4) = v4;  // v4 偏移 4 指向自身（自环）
  return result;
}



// ------------------------------------------------------------
// 0x406890 sub_406890 —— 容器添加 A（仅类型 3：new(0x2CEFC) → ·sub_406280 → 挂 +136 链表）
// 类型不符返回 -2147483639，分配失败 -2147483640；新对象指针写回 *Block。
// ------------------------------------------------------------
int /*thiscall*/ sub_406890(uint32_t *this, int nArg2, uint32_t *Block)  // 函数 容器添加 A（仅类型 3：new(0x2CEFC) → ·sub_406280 → 挂 +136 链表）
{
  uint8_t *pMem; // eax
  uint8_t *v6; // eax
  int fld_e34; // edi
  int v8; // ebx

  *Block = 0;
  *Block = 0;
  if ( nArg2 != 3 )  // 若 nArg2 != 3
    return -2147483639;  // 返回 0x80000009（类型错）
  pMem = operator new(0x2CEFCu);
  if ( pMem != nullptr )  // 若 pMem 非空
    v6 = sub_406280(pMem, 3, (int)this);  // 调 事件分发对象构造 E（·sub_405F10 装配后改挂 off_6C19E8 + ·sub_408AC0 初始化）
  else  // 否则分支
    v6 = nullptr;  // v6 = 空指针
  if ( v6 == nullptr )  // 若 v6 为空
    return -2147483640;  // 返回 0x80000008（内存不足）
  *Block = v6;  // 写指针 = v6
  fld_e34 = *(this + 34);  // fld_e34 = this+34 字段
  v8 = sub_40C0F0(fld_e34, *(uint32_t *)(fld_e34 + 4), Block);  // v8 = sub_40C0F0(...)
  sub_4067C0(this + 33, 1u);  // 调 sub_4067C0
  *(uint32_t *)(fld_e34 + 4) = v8;  // fld_e34+4 = v8
  **(uint32_t **)(v8 + 4) = v8;  // v8 偏移 4 指向自身（自环）
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x406970 sub_406970 —— 容器添加 B（类型 1 → ·sub_406360 / 类型 2 → ·sub_406440，挂 +144 链表）
// 类型 3 直接挂链（外部已建对象，*Block 置 0）—— 与 ·sub_406890 同构。
// ------------------------------------------------------------
int /*thiscall*/ sub_406970(uint32_t *this, int nArg2, uint32_t *Block)  // 函数 容器添加 B（类型 1 → ·sub_406360 / 类型 2 → ·sub_406440，挂 +144 链表）
{
  uint8_t *pMem; // eax
  uint8_t *v5; // eax
  uint8_t *pMem2; // eax

  *Block = 0;
  switch ( nArg2 )
  {
    case 1:  // case 分支 1
      *Block = 0;
      pMem = operator new(0x44u);
      if ( pMem != nullptr )  // 若 pMem 非空
        v5 = sub_406360(pMem, nArg2, (int)this);  // 调 事件分发对象构造 F（·sub_406130 装配后改挂 off_6C1A44 + ·sub_40AA10 初始化）
      else  // 否则分支
        v5 = nullptr;  // v5 = 空指针
      goto LABEL_7;  // 跳转 LABEL_7
    case 2:  // case 分支 2
      *Block = 0;
      pMem2 = operator new(0x3Cu);
      if ( pMem2 != nullptr )  // 若 pMem2 非空
        v5 = sub_406440(pMem2, nArg2, (int)this);  // 调 事件分发对象构造 G（·sub_406130 装配后改挂 off_6C1A60 + ·sub_40AE80 初始化）
      else  // 否则分支
        v5 = nullptr;  // v5 = 空指针
LABEL_7:  // LABEL_7（跳转目标）
      if ( v5 == nullptr )  // 若 v5 为空
        return -2147483640;  // 返回 0x80000008（内存不足）
      *Block = v5;  // 写指针 = v5
LABEL_11:  // LABEL_11（跳转目标）
      sub_406850(this + 36, (int)Block);  // 调 sub_406850
      return 1;  // 返回 1（成功）
    case 3:  // case 分支 3
      *Block = 0;
      goto LABEL_11;  // 跳转 LABEL_11
    default:  // 默认分支
      *Block = 0;
      return -2147483639;  // 返回 0x80000009（类型错）
  }
}



// ------------------------------------------------------------
// 0x406A80 sub_406A80 —— 容器添加 C（类型 1 → ·sub_406600 / 类型 2 → ·sub_406520，挂 +160 链表）
// 与 ·sub_406890 同构（差异：两种类型分派 + 对象 0x1C/0x20）。
// ------------------------------------------------------------
int /*thiscall*/ sub_406A80(uint32_t *this, int nArg2, uint32_t *Block)  // 函数 容器添加 C（类型 1 → ·sub_406600 / 类型 2 → ·sub_406520，挂 +160 链表）
{
  uint8_t *pMem2; // eax
  uint8_t *v6; // eax
  uint8_t *pMem; // eax
  int fld_e40; // edi
  int v9; // ebx

  *Block = 0;
  *Block = 0;
  if ( nArg2 == 1 )  // 若 nArg2 == 1
  {
    pMem = operator new(0x1Cu);
    if ( pMem != nullptr )  // 若 pMem 非空
      v6 = sub_406600(pMem, 1, (int)this);  // 调 事件分发对象构造 I（·sub_406020 装配后改挂 off_6C1AA4 + nullsub_3 空初始化）
    else  // 否则分支
      v6 = nullptr;  // v6 = 空指针
  }
  else  // 否则分支
  {
    if ( nArg2 != 2 )  // 若 nArg2 != 2
      return -2147483639;  // 返回 0x80000009（类型错）
    pMem2 = operator new(0x20u);
    if ( pMem2 != nullptr )  // 若 pMem2 非空
      v6 = sub_406520(pMem2, 2, (int)this);  // 调 事件分发对象构造 H（·sub_406020 装配后改挂 off_6C1A7C + ·sub_40B130 初始化）
    else  // 否则分支
      v6 = nullptr;  // v6 = 空指针
  }
  if ( v6 == nullptr )  // 若 v6 为空
    return -2147483640;  // 返回 0x80000008（内存不足）
  *Block = v6;  // 写指针 = v6
  fld_e40 = *(this + 40);  // fld_e40 = this+40 字段
  v9 = sub_40C0F0(fld_e40, *(uint32_t *)(fld_e40 + 4), Block);  // v9 = sub_40C0F0(...)
  sub_4067C0(this + 39, 1u);  // 调 sub_4067C0
  *(uint32_t *)(fld_e40 + 4) = v9;  // fld_e40+4 = v9
  **(uint32_t **)(v9 + 4) = v9;  // v9 偏移 4 指向自身（自环）
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x406B80 sub_406B80 —— 容器添加 D（类型 1 直接返回 0；类型 2 → ·sub_4066E0 挂 +168 链表）
// 与 ·sub_406A80 同族的最小变体。
// ------------------------------------------------------------
int /*thiscall*/ sub_406B80(uint32_t *this, int nArg2, uint32_t *uArg3)  // 函数 容器添加 D（类型 1 直接返回 0；类型 2 → ·sub_4066E0 挂 +168 链表）
{
  uint8_t *pMem; // eax
  uint8_t *v6; // eax

  *uArg3 = 0;  // 写指针 = 0
  if ( nArg2 == 1 )  // 若 nArg2 == 1
    return 0;
  if ( nArg2 == 2 )  // 若 nArg2 == 2
  {
    pMem = operator new(0x20u);
    if ( pMem != nullptr )  // 若 pMem 非空
      v6 = sub_4066E0(pMem, 2, (int)this);  // 调 事件分发对象构造 J（·sub_405E00 装配后改挂 off_6C1ACC + nullsub_3）
    else  // 否则分支
      v6 = nullptr;  // v6 = 空指针
    if ( v6 != nullptr )  // 若 v6 非空
    {
      *uArg3 = v6;  // 写指针 = v6
      sub_406850(this + 42, (int)uArg3);  // 调 sub_406850
      return 1;  // 返回 1（成功）
    }
    else  // 否则分支
    {
      return -2147483640;  // 返回 0x80000008（内存不足）
    }
  }
  else  // 否则分支
  {
    *uArg3 = 0;  // 写指针 = 0
    return -2147483639;  // 返回 0x80000009（类型错）
  }
}



// ============================================================
// SECTION 0x406C50 — NiMemory.log / NiProfile.log 日志对象（Gamebryo 风格内存/性能日志）
// ============================================================
// ------------------------------------------------------------
// 0x406C50 sub_406C50 —— NiMemory 日志对象全局访问口（返回 off_77F2E8）
// ★ 由 ·0x403920 日志全局态复位取回后经虚表槽 0 调用 —— 内存日志单例。
// ------------------------------------------------------------
int (***sub_406C50())()  // 【NiMemory.log / NiProfile.log 日志对象（Gamebryo…】
{
  return off_77F2E8;
}



// ------------------------------------------------------------
// 0x406C60 sub_406C60
// ------------------------------------------------------------
// 【解读】
//   NiMemory.log 日志对象构造（Gamebryo 风格内存分配跟踪日志，基类 sub_403990）。
// ------------------------------------------------------------
int sub_406C60()
{
  int result; // eax

  result = sub_403990((int)"NiMemory.log", 1, 1, 0);  // 调 日志文件登记（16 槽表线性探测空位 → new(0x128) + ·sub_404290 构造，返回槽号）
  if ( result >= 0 )  // 若 result >= 0
  {
    dword_79C7FC = result;
    dword_79C808 = result;
    dword_79C814 = result;
    dword_79C820 = result;
    byte_79C824 = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x406CA0 sub_406CA0
// ------------------------------------------------------------
// 【解读】
//   NiProfile.log 日志对象构造（性能采样日志）。
// ------------------------------------------------------------
int sub_406CA0()
{
  int result; // eax

  result = sub_403990((int)"NiProfile.log", 1, 1, 0);  // 调 日志文件登记（16 槽表线性探测空位 → new(0x128) + ·sub_404290 构造，返回槽号）
  if ( result >= 0 )  // 若 result >= 0
  {
    dword_79C7D8 = result;
    dword_79C7E4 = result;
    dword_79C7F0 = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x406CD0 sub_406CD0 —— 日志行字节变换（逐字节先循环右移 2 再异或 0x9D，就地改写）
// byte_79C7AC == 1（日志以模式 2 打开）时写入路径逐行调用 —— 行文本混淆输出【推断】。
// ------------------------------------------------------------
char /*cdecl*/ sub_406CD0(int nArg1, unsigned int uArg2)  // 函数 日志行字节变换（逐字节先循环右移 2 再异或 0x9D，就地改写）
{
  unsigned int i; // ecx
  char result; // al

  for ( i = 0; i < uArg2; ++i )
  {
    result = *(uint8_t *)(i + nArg1) >> 2;
    *(uint8_t *)(i + nArg1) = (result | (*(uint8_t *)(i + nArg1) << 6)) ^ 0x9D;
  }
  return result;
}



// ------------------------------------------------------------
// 0x406D00 sub_406D00 —— std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
// nArg3 非 0 时 pos = nArg3 - 缓冲基址，uArg4 非 0 时 n = uArg4 - nArg3；
// 擦除起点写回 *uArg2（SSO 与否分两支）—— 上层字符串裁剪工具【推断】。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_406D00(uint32_t *this, uint32_t *uArg2, int nArg3, unsigned int uArg4)  // 函数 std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
{
  uint32_t *pThis_1; // ebx
  uint32_t *pThis_12; // eax
  unsigned int v7; // esi
  unsigned int uArg42; // eax
  uint32_t *result; // eax

  pThis_1 = this + 1;
  if ( *(this + 6) < 0x10u )
    pThis_12 = this + 1;
  else  // 否则分支
    pThis_12 = (uint32_t *)*pThis_1;
  if ( nArg3 != 0 )  // 若 nArg3 != 0
    v7 = nArg3 - (uint32_t)pThis_12;
  else  // 否则分支
    v7 = 0;
  uArg42 = uArg4;
  if ( uArg4 != 0 )  // 若 uArg4 != 0
    uArg42 = uArg4 - nArg3;
  sub_401230(this, v7, uArg42);  // 调 sub_401230
  result = uArg2;
  if ( *(this + 6) < 0x10u )
    *uArg2 = (char *)pThis_1 + v7;
  else  // 否则分支
    *uArg2 = *pThis_1 + v7;
  return result;
}



// ------------------------------------------------------------
// 0x406D60 sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
// ·sub_4015C0 = 跨文件登记的 std::string 构造赋值具名。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_406D60(size_t *this, char *Src)  // 函数 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
{
  return sub_4015C0(this, Src, strlen(Src));  // 【std::string构造赋值】
}



// ============================================================
// SECTION 0x406D90 — IME 输入法处理族（Composition/Candidate/NotifyIME，日志直证）
// ============================================================
// ------------------------------------------------------------
// 0x406D90 sub_406D90 —— 键盘按键状态表维护（256/257 = WM_KEYDOWN/UP 置 1/清 0）
// 键码 wParam < 256 索引 byte_89D160 状态表；随后转发宿主 dword_89D260 虚表槽 0；
// ★ WndProc Msg >= 0x100 分支调用（与 ·sub_407900 并列）。
// ------------------------------------------------------------
int /*stdcall*/ sub_406D90(int nArg1, unsigned int uArg2, int nArg3)  // 【IME 输入法处理族（Composition/Candidate/NotifyIME…】
{
  int result; // eax

  result = nArg1 - 256;  // result = Msg - WM_KEYDOWN(256)
  if ( nArg1 == 256 )  // Msg == WM_KEYDOWN(256)
  {
    if ( uArg2 >= 0x100 )  // 键码 >= 256（含系统键，忽略）
      return result;
    byte_89D160[uArg2] = 1;  // 键态表 byte_89D160[键码] 置 1（按下）
  }
  else  // 否则分支
  {
    result = nArg1 - 257;  // result = Msg - WM_KEYUP(257)
    if ( nArg1 == 257 )  // Msg == WM_KEYUP(257)
    {
      if ( uArg2 >= 0x100 )  // 键码 >= 256
        return result;
      byte_89D160[uArg2] = 0;  // 键态表[键码] 清 0（抬起）
    }
  }
  if ( dword_89D260 != 0 )  // dword_89D260 宿主非空
    return (**(int (/*thiscall*/ ***)(int, int, unsigned int, int))dword_89D260)(dword_89D260, nArg1, uArg2, nArg3);  // 转发宿主虚表首项（Msg, wParam, lParam）
  return result;
}



// ------------------------------------------------------------
// 0x406DF0 sub_406DF0 —— 光标位置设置（ClientToScreen 换算 + SetCursorPos，同步回写全局 pt）
// 输入子系统回正入口（全局 pt 缓存光标坐标）。
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_406DF0(LONG uArg1, LONG uArg2)  // 函数 光标位置设置（ClientToScreen 换算 + SetCursorPos，同步回写全局 pt）
{
  BOOL result; // eax
  struct tagPOINT Point; // [esp+8h] [ebp-8h] BYREF

  Point.x = uArg1;
  Point.y = uArg2;
  ClientToScreen(hWnd, &Point);  // ClientToScreen 客户区坐标转屏幕坐标
  result = SetCursorPos(Point.x, Point.y);  // SetCursorPos 设置光标位置
  pt.y = uArg2;  // pt.y = uArg2（同步全局）
  pt.x = uArg1;
  return result;
}



// ------------------------------------------------------------
// 0x406E40 sub_406E40 —— 动态缓冲整体释放（+16 计数递减归零 → +4 槽指针表逐项 free → 计数与表指针清零）
// ★ 被 broadcast_debug / pvp_ui / gfx_texture / rtti_core 等多处收尾调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_406E40(int this)  // 函数 动态缓冲整体释放（+16 计数递减归零 → +4 槽指针表逐项 free → 计数与表指针清零）
{
  int fld_10; // eax
  int v3; // eax
  int i; // edi
  void *fld_4; // eax

  while ( *(uint32_t *)(this + 16) != 0 )  // this+16 计数非 0
  {
    fld_10 = *(uint32_t *)(this + 16);  // fld_10 = this+16 计数
    if ( fld_10 != 0 )  // 计数非 0
    {
      v3 = fld_10 - 1;  // v3 = 计数-1
      *(uint32_t *)(this + 16) = v3;  // this+16 = v3
      if ( v3 == 0 )  // 递减到 0
        *(uint32_t *)(this + 12) = 0;  // this+12 清 0
    }
  }
  for ( i = *(uint32_t *)(this + 8); i != 0; --i )  // 逐块 i（this+8 块数）
  {
    fld_4 = *(void **)(*(uint32_t *)(this + 4) + 4 * i - 4);  // fld_4 = this+4 第 i 块指针
    if ( fld_4 != nullptr )  // 非空
      j__free(fld_4);  // free 块
  }
  if ( *(uint32_t *)(this + 4) != 0 )  // this+4 表非空
    j__free(*(void **)(this + 4));  // free 表
  *(uint32_t *)(this + 8) = 0;  // this+8 清 0
  *(uint32_t *)(this + 4) = 0;  // this+4 清 0
}



// ------------------------------------------------------------
// 0x406EB0 sub_406EB0 —— 容器初始化（this+4..+16 四个字段清零，返回 this）
// 与 ·sub_406F40（deque too long）同族的最小初始化桩。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_406EB0(uint32_t *this)  // 函数 容器初始化（this+4..+16 四个字段清零，返回 this）
{
  *(this + 1) = 0;  // this+1 清 0
  *(this + 2) = 0;  // this+2 清 0
  *(this + 3) = 0;  // this+3 清 0
  *(this + 4) = 0;  // this+4 清 0
  return this;
}



// ------------------------------------------------------------
// 0x406ED0 sub_406ED0
// ------------------------------------------------------------
// 【解读】
//   std::length_error("deque<T> too long") 抛出器（deque 模板实例）。
// ------------------------------------------------------------
void /*noreturn*/ sub_406ED0()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;  // 临时串容量 15
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "deque<T> too long", 0x11u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);  // 构造异常对象
  pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
}



// ------------------------------------------------------------
// 0x406F40 sub_406F40 —— deque 扩容（容量取 max(uArg2, 8, 容量/2)，跨块搬移 + 零填充）
// 溢出先 ·sub_406ED0 抛 deque too long；环形块起点 fld_C，尾区按块搬移复位；
// ★ 由 ·sub_407090 追加路径在换块前置调用。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_406F40(int this, unsigned int uArg2)  // 函数 deque 扩容（容量取 max(uArg2, 8, 容量/2)，跨块搬移 + 零填充）
{
  unsigned int uArg22; // edx
  unsigned int fld_8; // eax
  unsigned int v5; // ecx
  unsigned int fld_C; // edi
  int v7; // esi
  char *fld_4; // eax
  const void *fld_42; // ecx
  char *v10; // eax
  char *pBuf3; // edx
  unsigned int pBuf; // ecx
  char *pBuf2; // edi
  size_t v14; // esi
  char *fld_43; // eax
  unsigned int result; // eax
  size_t fld_82; // [esp+8h] [ebp-Ch]
  char *pMem; // [esp+10h] [ebp-4h]

  uArg22 = uArg2;  // uArg22 = uArg2（新增块数）
  fld_8 = *(uint32_t *)(this + 8);  // fld_8 = this+8 当前块数
  if ( 0xFFFFFFF - fld_8 < uArg2 )  // 超出 0xFFFFFFF 上限
    sub_406ED0(this);  // 抛 deque too long
  v5 = fld_8 >> 1;  // v5 = 块数/2
  if ( fld_8 >> 1 < 8 )  // 增量 < 8
    v5 = 8;
  if ( uArg2 < v5 && fld_8 <= 0xFFFFFFF - v5 )  // 请求增量不足且容量允许
  {
    uArg2 = v5;
    uArg22 = v5;
  }
  fld_C = *(uint32_t *)(this + 12) >> 2;  // fld_C = this+12 起点 >> 2
  v7 = 4 * fld_C;  // v7 = 4×起点
  pMem = (char *)operator new(4 * (uArg22 + fld_8));  // 分配 4×(新增+现块数) 新块表
  fld_82 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * fld_C) >> 2);  // fld_82 = 后段字节数
  fld_4 = (char *)memcpy_0(&pMem[4 * fld_C], (const void *)(4 * fld_C + *(uint32_t *)(this + 4)), fld_82);  // memcpy 中段搬移
  fld_42 = *(const void **)(this + 4);  // fld_42 = 旧块表
  v10 = &fld_4[fld_82];  // v10 = 目标位置+
  if ( fld_C > uArg2 )  // 起点 > 新增（分两段）
  {
    memcpy_0(v10, fld_42, 4 * ((int)(4 * uArg2) >> 2));  // memcpy 前段
    v14 = 4 * ((int)(v7 - 4 * uArg2) >> 2);  // v14 = 剩余字节数
    fld_43 = (char *)memcpy_0(pMem, (const void *)(4 * uArg2 + *(uint32_t *)(this + 4)), v14);  // memcpy 后段
    pBuf = uArg2;
    pBuf2 = &fld_43[v14];  // pBuf2 = 尾部
    if ( uArg2 == 0 )  // 无前段
      goto LABEL_15;  // 跳 LABEL_15
    goto LABEL_14;  // 跳转 LABEL_14
  }
  pBuf3 = (char *)memcpy_0(v10, fld_42, 4 * (v7 >> 2)) + 4 * (v7 >> 2);  // memcpy 单段 + 前进
  if ( uArg2 != fld_C )  // 新增 != 起点
    memset(pBuf3, 0, 4 * (uArg2 - fld_C));  // memset 清零新增部分
  if ( fld_C != 0 )  // 起点非 0
  {
    pBuf = fld_C;  // pBuf = 起点
    pBuf2 = pMem;  // pBuf2 = 新表头
LABEL_14:  // LABEL_14（跳转目标）
    memset(pBuf2, 0, 4 * pBuf);  // memset 清零前段
  }
LABEL_15:  // LABEL_15（跳转目标）
  if ( *(uint32_t *)(this + 4) != 0 )  // 旧块表非空
    j__free(*(void **)(this + 4));  // free 旧块表
  result = uArg2 + *(uint32_t *)(this + 8);  // result = 新增 + 现块数
  *(uint32_t *)(this + 4) = pMem;  // this+4 = 新块表
  *(uint32_t *)(this + 8) = result;  // this+8 = 新块数
  return result;
}



// ------------------------------------------------------------
// 0x407090 sub_407090 —— deque 元素追加（按环形偏移定位块，块空时 new(0x10) 补块，+16 计数递增）
// 索引 = (计数 + 环形头) & 3 决定块与块内槽；插入值写槽后计数 +1。
// ------------------------------------------------------------
int /*thiscall*/ sub_407090(int this, uint32_t *uArg2)  // 函数 deque 元素追加（按环形偏移定位块，块空时 new(0x10) 补块，+16 计数递增）
{
  int fld_10; // eax
  unsigned int fld_8; // eax
  unsigned int fld_102; // edi
  unsigned int v6; // ebx
  uint32_t *fld_4; // edi
  int result; // eax

  fld_10 = *(uint32_t *)(this + 16);  // fld_10 = this+16 计数
  if ( (((uint8_t)fld_10 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(fld_10 + 4) >> 2 )  // 起环边界且块数不足
    sub_406F40(this, 1u);  // 扩容 1 块
  fld_8 = *(uint32_t *)(this + 8);  // fld_8 = this+8 块数
  fld_102 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);  // fld_102 = 计数 + 环头
  v6 = fld_102 >> 2;  // v6 = 页索引
  if ( fld_8 <= fld_102 >> 2 )  // 回绕
    v6 -= fld_8;  // v6 -= 块数
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )  // 目标页为空
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);  // 分配 0x10 字节块（4 元素）
  fld_4 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (fld_102 & 3));  // fld_4 = 目标元素地址
  if ( fld_4 != nullptr )  // 地址非空
    *fld_4 = *uArg2;  // *fld_4 = *uArg2（写值）
  result = *(uint32_t *)(this + 16) + 1;  // result = 计数+1
  *(uint32_t *)(this + 16) = result;  // this+16 = 新计数
  return result;
}



// ------------------------------------------------------------
// 0x407110 sub_407110 —— 鼠标消息分发（byte_89D27C 置位时先入队，否则更新 pt 与 dword_89D26C 按键掩码）
// 513/514 = 右键按/弹 → 掩码 1/8；516/517 = 中键 → 2/16；
// ★ WndProc 0x200/0x201/0x202/0x204/0x205 分支调用，尾部转发 dword_89D278 宿主。
// ------------------------------------------------------------
int /*cdecl*/ sub_407110(int nArg1, int nArg2, int nArg3)  // 函数 鼠标消息分发（byte_89D27C 置位时先入队，否则更新 pt 与 dword_89D26C 按键掩码）
{
  int nArg32; // esi
  int nArg12; // edi
  int result; // eax

  nArg32 = nArg3;
  pt.x = (int16_t)nArg3;  // pt.x = 低 16 位（x 坐标）
  nArg12 = nArg1;
  pt.y = SHIWORD(nArg3);  // pt.y = 高 16 位（y 坐标）
  if ( byte_89D27C != 0 )  // 入队模式 byte_89D27C 非 0
  {
    result = sub_407090((int)&unk_89D280, &nArg1);  // sub_407090 把消息入队
  }
  else  // 否则分支
  {
    result = nArg1 - 513;  // result = Msg - WM_RBUTTONDOWN(513)
    switch ( nArg1 )  // 按 Msg 分派
    {
      case 513:  // case WM_RBUTTONDOWN(513)
        result = 1;
        dword_89D26C = 1;  // dword_89D26C = 1（右键按下掩码）
        byte_89D274 = 1;
        break;  // 跳出 switch
      case 514:  // case WM_RBUTTONUP(514)
        dword_89D26C = 8;  // dword_89D26C = 8（右键抬起掩码）
        byte_89D274 = 0;
        break;  // 跳出 switch
      case 516:  // case WM_MBUTTONDOWN(516)
        dword_89D26C = 2;  // dword_89D26C = 2（中键按下掩码）
        byte_89D275 = 1;
        break;  // 跳出 switch
      case 517:  // case WM_MBUTTONUP(517)
        dword_89D26C = 16;  // dword_89D26C = 16（中键抬起掩码）
        byte_89D275 = 0;
        break;  // 跳出 switch
      default:  // 默认分支
        break;  // 跳出 switch
    }
  }
  if ( dword_89D278 != 0 )  // dword_89D278 宿主非空
    return (**(int (/*thiscall*/ ***)(int, int, int, int))dword_89D278)(dword_89D278, nArg12, nArg2, nArg32);  // 转发宿主虚表首项（Msg, wParam, lParam）
  return result;
}



// ------------------------------------------------------------
// 0x4071D0 sub_4071D0 —— 鼠标消息回放（队列逐条经 ·sub_407110 重发 + 光标位置复位）
// byte_89D27C 先清 0 防止回灌；队列态 dword_89D284 块表 / 89D288 环头 / 89D28C 读指针 / 89D290 计数；
// ★ script_string 在组合复位后调用。
// ------------------------------------------------------------
BOOL sub_4071D0()  // 函数 鼠标消息回放（队列逐条经 ·sub_407110 重发 + 光标位置复位）
{
  LONG x; // esi
  unsigned int dword_89D2882; // edx
  unsigned int dword_89D28C2; // ecx
  unsigned int v3; // eax
  unsigned int v4; // ecx
  LONG v6; // edi
  BOOL result; // eax
  struct tagPOINT Point; // [esp+8h] [ebp-Ch] BYREF
  LONG y; // [esp+10h] [ebp-4h]

  y = pt.y;
  x = pt.x;
  byte_89D27C = 0;  // byte_89D27C 清 0（防回灌）
  if ( dword_89D290 != 0 )  // 队列计数非 0
  {
    dword_89D2882 = dword_89D288;  // dword_89D2882 = 环头
    dword_89D28C2 = dword_89D28C;  // dword_89D28C2 = 读指针
    while ( 1 )  // 逐条回放
    {
      v3 = dword_89D28C2 >> 2;  // v3 = 页索引
      v4 = dword_89D28C2 - 4 * (dword_89D28C2 >> 2);  // v4 = 页内偏移
      if ( dword_89D2882 <= v3 )  // 回绕
        v3 -= dword_89D2882;  // v3 -= 环头
      sub_407110(*(uint32_t *)(*(uint32_t *)(dword_89D284 + 4 * v3) + 4 * v4), 0, 0);  // sub_407110 重发该消息
      if ( dword_89D290 == 0 )  // 计数已为 0
        break;  // 跳出 switch
      dword_89D2882 = dword_89D288;  // 重载环头
      dword_89D28C2 = dword_89D28C + 1;  // 读指针 +1
      if ( 4 * dword_89D288 <= (unsigned int)++dword_89D28C )  // 越过块边界
      {
        dword_89D28C2 = 0;  // 读指针复位 0
        dword_89D28C = 0;  // 环头清 0
      }
      if ( --dword_89D290 == 0 )  // 计数 -- 归零
      {
        dword_89D28C = 0;  // 读指针清 0
        break;  // 跳出 switch
      }
    }
  }
  v6 = y;
  Point.x = x;
  Point.y = y;
  ClientToScreen(hWnd, &Point);  // ClientToScreen 换算
  result = SetCursorPos(Point.x, Point.y);  // SetCursorPos 复位光标
  pt.y = v6;
  pt.x = x;
  return result;
}



// ------------------------------------------------------------
// 0x4072B0 sub_4072B0 —— IME 全局态清零（三块 0x400 缓冲 + byte_8A6E98..9C 标志 + 两上下文句柄）
// ★ 由 ·0x4044C0 事件分发对象状态初始化调用（传参忽略，纯全局复位）；与 ·sub_407310 成对。
// ------------------------------------------------------------
int64_t sub_4072B0()  // 调 IME 全局态清零（三块 0x400 缓冲 + byte_8A6E98..9C 标志 + 两上下文句柄）
{
  memset(&byte_8A6A98, 0, 0x400u);  // memset byte_8A6A98 清零（1KB）
  memset(&byte_8A6698, 0, 0x400u);  // memset byte_8A6698 清零
  memset(&byte_8A6298, 0, 0x400u);  // memset byte_8A6298 清零
  byte_8A6E98 = 0;  // byte_8A6E98 清 0
  byte_8A6E99 = 0;  // byte_8A6E99 清 0
  byte_8A6E9B = 0;  // byte_8A6E9B 清 0
  byte_8A6E9C = 0;  // byte_8A6E9C 清 0
  dword_8A6EA0 = nullptr;  // dword_8A6EA0 清 0（IME 窗口句柄）
  dword_8A6EA4 = nullptr;  // dword_8A6EA4 清 0（IME 上下文）
  byte_8A6E9A = 0;  // byte_8A6E9A 清 0
  return 0;
}



// ------------------------------------------------------------
// 0x407310 sub_407310 —— IME 全局资源释放（ImmReleaseContext + 三缓冲清零 + 句柄与标志清零）
// ★ 由 ·0x404560 状态回卷调用（以 this+116 传入，仅用于字节 +4 清零）；与 ·sub_4072B0 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_407310(uint8_t *this)  // 函数 IME 全局资源释放（ImmReleaseContext + 三缓冲清零 + 句柄与标志清零）
{
  if ( dword_8A6EA4 != nullptr )  // dword_8A6EA4 非空
    ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);  // ImmReleaseContext 释放 IME 上下文
  memset(&byte_8A6A98, 0, 0x400u);  // memset byte_8A6A98 清零
  memset(&byte_8A6698, 0, 0x400u);  // memset byte_8A6698 清零
  memset(&byte_8A6298, 0, 0x400u);  // memset byte_8A6298 清零
  byte_8A6E98 = 0;  // byte_8A6E98 清 0
  byte_8A6E99 = 0;  // byte_8A6E99 清 0
  byte_8A6E9B = 0;  // byte_8A6E9B 清 0
  byte_8A6E9C = 0;  // byte_8A6E9C 清 0
  dword_8A6EA0 = nullptr;  // dword_8A6EA0 清 0
  dword_8A6EA4 = nullptr;  // dword_8A6EA4 清 0
  byte_8A6E9A = 0;  // byte_8A6E9A 清 0
  *(this + 4) = 0;  // this+4 清 0
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x407390 sub_407390 —— IME 组合窗口定位（ImmSetCompositionWindow，dwStyle=2 指定光标点 uArg2/uArg3）
// 字节 +4 未就绪返回 -2147483647；·sub_407900 以 (-1000,-1000) 移出屏。
// ------------------------------------------------------------
int /*thiscall*/ sub_407390(uint8_t *this, LONG uArg2, LONG uArg3)  // 函数 IME 组合窗口定位（ImmSetCompositionWindow，dwStyle=2 指定光标点 uArg2/uArg3）
{
  struct tagCOMPOSITIONFORM CompForm; // [esp+0h] [ebp-1Ch] BYREF

  if ( *(this + 4) == 0 )
    return -2147483647;  // 返回 0x80000001（未就绪）
  CompForm.ptCurrentPos.x = uArg2;
  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);  // API 取输入法上下文（IME）
  CompForm.dwStyle = 2;
  CompForm.ptCurrentPos.y = uArg3;
  ImmSetCompositionWindow(dword_8A6EA4, &CompForm);  // 调 ImmSetCompositionWindow
  ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);  // 调 ImmReleaseContext
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x407400 sub_407400 —— IME 强制上屏（ImmNotifyIME(NI_COMPOSITIONSTR, CPS_COMPLETE=1, 0)）
// ★ 跨文件分析确证为 completeIMEComposit；组合串超长时 NCEdit 调用。
// ------------------------------------------------------------
BOOL sub_407400()  // 函数 IME 强制上屏（ImmNotifyIME(NI_COMPOSITIONSTR, CPS_COMPLETE=1, 0)）
{
  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);  // API 取输入法上下文（IME）
  ImmNotifyIME(dword_8A6EA4, 0x15u, 1u, 0);  // 调 ImmNotifyIME
  return ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);
}



// ------------------------------------------------------------
// 0x407430 sub_407430 —— IME 取消组合（ImmNotifyIME(NI_COMPOSITIONSTR, CPS_CANCEL=4, 0) + 清 A/B 双缓冲）
// ★ NCEdit::Empty 与组合异常收尾调用。
// ------------------------------------------------------------
int sub_407430()  // 函数 IME 取消组合（ImmNotifyIME(NI_COMPOSITIONSTR, CPS_CANCEL=4, 0) + 清 A/B 双缓…
{
  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);  // API 取输入法上下文（IME）
  ImmNotifyIME(dword_8A6EA4, 0x15u, 4u, 0);  // 调 ImmNotifyIME
  ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);  // 调 ImmReleaseContext
  memset(&byte_8A6698, 0, 0x400u);  // 调 memset
  memset(&byte_8A6A98, 0, 0x400u);  // 调 memset
  return 0;
}



// ------------------------------------------------------------
// 0x407480 sub_407480 [串: "\n\n ...<IMN_CHANGECANDIDATE>" | "\n\n ...<IMN_OPENCANDIDATE>"]
// ------------------------------------------------------------
char /*stdcall*/ sub_407480(int nArg1, int nArg2)
{
  size_t v2; // eax
  DWORD v3; // esi
  struct tagCANDIDATELIST *pMem; // ebx
  char *pBuf; // esi
  DWORD *v6; // edi
  int v7; // eax
  unsigned int dword_8A6EB03; // ecx
  size_t CandidateListA; // eax
  DWORD v10; // esi
  char *v11; // esi
  DWORD *dwOffset; // edi
  char *v13; // eax
  char *v14; // edx
  char v15; // cl
  int v16; // eax
  unsigned int dword_8A6EB02; // ecx
  char v19; // [esp+0h] [ebp-Ch]
  unsigned int v20; // [esp+14h] [ebp+8h]
  unsigned int v21; // [esp+14h] [ebp+8h]

  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);  // API 取输入法上下文（IME）
  switch ( nArg1 )
  {
    case 3:  // case 分支 3
      sub_40BE20("\n\n ...<IMN_CHANGECANDIDATE>", v19);  // 调 sub_40BE20
      CandidateListA = ImmGetCandidateListA(dword_8A6EA4, 0, nullptr, 0);
      v10 = CandidateListA;
      if ( CandidateListA != 0 )  // 若 CandidateListA != 0
      {
        pMem = (struct tagCANDIDATELIST *)operator new(CandidateListA);
        ImmGetCandidateListA(dword_8A6EA4, 0, pMem, v10);
        dword_8A6EB0 = pMem->dwCount;
        dword_77F400 = pMem->dwSelection;
        dword_77F404 = pMem->dwPageSize;
        if ( (unsigned int)dword_8A6EB0 < 0x400 && dword_8A6EB8 != 0 )
        {
          dwValue = pMem->dwPageSize * (pMem->dwSelection / pMem->dwPageSize);
          if ( pMem->dwPageStart == dwValue )
          {
            memset(&unk_89D298, 0, 0x9000u);  // 调 memset
            v21 = 0;
            if ( dword_8A6EB0 != 0 )  // 若 dword_8A6EB0 != 0
            {
              v11 = (char *)&unk_89D298;
              dwOffset = pMem->dwOffset;
              do  // do 循环体
              {
                v13 = (char *)pMem + *dwOffset;
                v14 = v11;
                do  // do 循环体
                {
                  v15 = *v13++;
                  *v14++ = v15;
                }
                while ( v15 != 0 );  // 当 v15 != 0 循环
                v16 = (*(int (/*fastcall*/ **)(int, char *, char *))(*(uint32_t *)dword_8A6EB8 + 16))(
                        dword_8A6EB8,
                        v14,
                        v11);
                dword_8A6EB02 = dword_8A6EB0;
                *((uint32_t *)v11 + 8) = v16;  // v11 偏移 32 = v16
                ++dwOffset;
                v11 += 36;  // v11 前进 36
                ++v21;  // v21 自增
              }
              while ( v21 < dword_8A6EB02 );  // 当 v21 < dword_8A6EB02 循环
            }
            goto LABEL_22;  // 跳转 LABEL_22
          }
          j__free(pMem);
          ImmNotifyIME(dword_8A6EA4, 0x16u, 0, dwValue);  // 调 ImmNotifyIME
        }
      }
      break;  // 跳出 switch
    case 4:  // case 分支 4
      dword_8A6EB0 = 0;  // dword_8A6EB0 = 0/空
      dword_77F400 = -1;
      memset(&unk_89D298, 0, 0x9000u);  // 调 memset
      break;  // 跳出 switch
    case 5:  // case 分支 5
      sub_40BE20("\n\n ...<IMN_OPENCANDIDATE>", v19);  // 调 sub_40BE20
      v2 = ImmGetCandidateListA(dword_8A6EA4, 0, nullptr, 0);
      v3 = v2;
      if ( v2 != 0 )  // 若 v2 != 0
      {
        pMem = (struct tagCANDIDATELIST *)operator new(v2);
        ImmGetCandidateListA(dword_8A6EA4, 0, pMem, v3);
        dword_8A6EB0 = pMem->dwCount;
        dword_77F400 = pMem->dwSelection;
        dwValue = pMem->dwPageStart;
        dword_77F404 = pMem->dwPageSize;
        if ( (unsigned int)dword_8A6EB0 < 0x400 && dword_8A6EB8 != 0 )
        {
          memset(&unk_89D298, 0, 0x9000u);  // 调 memset
          v20 = 0;
          if ( dword_8A6EB0 != 0 )  // 若 dword_8A6EB0 != 0
          {
            pBuf = (char *)&unk_89D298;
            v6 = pMem->dwOffset;
            do  // do 循环体
            {
              strcpy(pBuf, (const char *)pMem + *v6);  // 调 strcpy
              v7 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8A6EB8 + 16))(dword_8A6EB8, pBuf);
              dword_8A6EB03 = dword_8A6EB0;
              *((uint32_t *)pBuf + 8) = v7;
              ++v6;  // v6 自增
              pBuf += 36;  // pBuf 前进 36
              ++v20;  // v20 自增
            }
            while ( v20 < dword_8A6EB03 );  // 当 v20 < dword_8A6EB03 循环
          }
LABEL_22:  // LABEL_22（跳转目标）
          j__free(pMem);
        }
      }
      break;  // 跳出 switch
    default:  // 默认分支
      break;  // 跳出 switch
  }
  ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);  // 调 ImmReleaseContext
  return 1;  // 返回 1（成功）
}


// ------------------------------------------------------------
// 0x4076E0 sub_4076E0 —— IME 子系统附着（ImmGetContext 探测后立即释放，记录全局 HWND 与字节 +4 就绪）
// 已附着返回 -2147483646，取不到上下文返回 -2147483647；
// ★ 窗口创建成功后由窗口框架（·0x4048F0）调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_4076E0(uint8_t *this, HWND nArg2)  // 函数 IME 子系统附着（ImmGetContext 探测后立即释放，记录全局 HWND 与字节 +4 就绪）
{
  HIMC Context; // eax

  if ( *(this + 4) != 0 )
    return -2147483646;  // 返回 0x80000002（已初始化）
  dword_8A6EA0 = nArg2;
  Context = ImmGetContext(nArg2);  // API 取输入法上下文（IME）
  dword_8A6EA4 = Context;
  if ( Context == nullptr )  // 若 Context 为空
    return -2147483647;  // 返回 0x80000001（未就绪）
  ImmReleaseContext(dword_8A6EA0, Context);  // 调 ImmReleaseContext
  *(this + 4) = 1;  // this+4 = 1
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x407740 sub_407740 [串: "\n IIme::Composition--------------------" | "\nGCS_RESULTSTR : <%s>" | "\nGCS_COMPSTR : <%s>"]
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_407740(int nArg1, int16_t uArg2)
{
  unsigned int CompositionStringA; // eax
  DWORD v3; // esi
  unsigned int result; // eax
  unsigned int v5; // esi
  unsigned int v6; // esi
  char v7; // [esp+0h] [ebp-410h]
  char Buf[1024]; // [esp+Ch] [ebp-404h] BYREF
  int dword_796E502; // [esp+40Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // 栈检 cookie
  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);  // API 取输入法上下文（IME）
  sub_40BE20("\n IIme::Composition--------------------", v7);  // 调 sub_40BE20
  if ( (uArg2 & 0x800) != 0 )
  {
    CompositionStringA = ImmGetCompositionStringA(dword_8A6EA4, 0x800u, nullptr, 0);
    v3 = CompositionStringA;
    if ( CompositionStringA < 0x400 )
    {
      if ( CompositionStringA == 0 )  // 若 CompositionStringA == 0
      {
LABEL_6:  // LABEL_6（跳转目标）
        byte_8A6A98[v3] = 0;
        sub_40BE20("\nGCS_RESULTSTR : <%s>", (char)byte_8A6A98);  // 调 sub_40BE20
        memset(byte_8A6698, 0, sizeof(byte_8A6698));  // 调 memset
        byte_8A6E9B = 0;  // byte_8A6E9B = 0/空
        goto LABEL_7;  // 跳转 LABEL_7
      }
    }
    else  // 否则分支
    {
      v3 = 1023;
    }
    ImmGetCompositionStringA(dword_8A6EA4, 0x800u, byte_8A6A98, v3);  // 调 ImmGetCompositionStringA
    goto LABEL_6;  // 跳转 LABEL_6
  }
LABEL_7:  // LABEL_7（跳转目标）
  if ( (uArg2 & 8) != 0 )  // 若位测试非 0
  {
    if ( byte_8A6EAC != 0 )  // 若 byte_8A6EAC != 0
    {
      result = ImmGetCompositionStringA(dword_8A6EA4, 8u, nullptr, 0);
      v5 = result;
      if ( result >= 0x400 )  // 若 result >= 0x400
        return result;
      ImmGetCompositionStringA(dword_8A6EA4, 8u, byte_8A6698, result);  // 调 ImmGetCompositionStringA
      byte_8A6698[v5] = 0;
      byte_8A6E9B = 1;
      sub_40BE20("\nGCS_COMPSTR : <%s>", (char)byte_8A6698);  // 调 sub_40BE20
    }
    else  // 否则分支
    {
      sub_407430();  // 调 sub_407430
    }
  }
  if ( (uArg2 & 0x80u) != 0 )
  {
    memset(Buf, 0, sizeof(Buf));  // 调 memset
    v6 = ImmGetCompositionStringA(dword_8A6EA4, 0x80u, nullptr, 0);
    if ( v6 >= 0x400 )  // 若 v6 >= 0x400
      v6 = 1023;
    ImmGetCompositionStringA(dword_8A6EA4, 8u, Buf, v6);  // 调 ImmGetCompositionStringA
    Buf[v6] = 0;
    dword_8A6EA8 = strlen(Buf);  // CRT 字符串长度（逐字节扫描到 NUL）
    sub_40BE20("\n GCS_CURSORPOS : <%s> <%d>", (char)Buf);  // 调 sub_40BE20
  }
  return ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);
}



// ------------------------------------------------------------
// 0x407900 sub_407900 —— IME 消息总处理（STARTCOMPOSITION 0x10D / ENDCOMPOSITION 0x10E / COMPOSITION 271 / NOTIFY 642）
// 271 且 nArg4 位 0x800 → ·sub_407740；642 → ·sub_407480；键处理 0x100/0x102 维护虚键与提交标志；
// ★ WndProc 两分支调用（0x10D-0x10F 与 642）。
// ------------------------------------------------------------
int /*thiscall*/ sub_407900(uint8_t *this, unsigned int uArg2, unsigned int uArg3, int nArg4)  // 函数 IME 消息总处理（STARTCOMPOSITION 0x10D / ENDCOMPOSITION 0x10E / COMPOSITIO…
{
  if ( *(this + 4) == 0 )
    return -2147483647;  // 返回 0x80000001（未就绪）
  if ( uArg2 > 0x10E )
  {
    if ( uArg2 == 271 )  // 若 uArg2 == 271
    {
      sub_407390(this, -1000, -1000);  // 调 sub_407390
      byte_8A6E9B = 1;
      sub_407740(uArg3, nArg4);  // 调 sub_407740
    }
    else if ( uArg2 == 642 )
    {
      sub_407480(uArg3, nArg4);  // 调 sub_407480
      return 0;
    }
  }
  else  // 否则分支
  {
    switch ( uArg2 )
    {
      case 0x10Eu:  // case 分支 0x10E
        memset(byte_8A6698, 0, sizeof(byte_8A6698));  // 调 memset
        byte_8A6E9C = 1;
        byte_8A6E9B = 0;  // byte_8A6E9B = 0/空
        return 0;
      case 0x100u:  // case 分支 0x100
        if ( uArg3 >= 0x23 && uArg3 <= 0x28 )
          goto LABEL_22;  // 跳转 LABEL_22
        if ( uArg3 == 45 )  // 若 uArg3 == 45
        {
          byte_8A6298 = 45;
          byte_8A6E99 = byte_8A6E99 == 0;
          byte_8A6E9A = 1;
          return 0;
        }
        if ( uArg3 == 46 || uArg3 == 190 )
        {
LABEL_22:  // LABEL_22（跳转目标）
          if ( uArg3 != 190 )  // 若 uArg3 != 190
          {
            byte_8A6298 = uArg3;
            byte_8A6E9A = 1;
            return 0;
          }
        }
        break;  // 跳出 switch
      case 0x102u:  // case 分支 0x102
        if ( uArg3 != 9 )  // 若 uArg3 != 9
        {
          if ( uArg3 == 13 )  // 若 uArg3 == 13
          {
            byte_8A6E98 = 1;
            return 0;
          }
          if ( strlen(byte_8A6A98) == 0 && nArg4 != 1 )  // CRT 字符串长度（逐字节扫描到 NUL）
          {
            byte_8A6A98[0] = uArg3;
            return 0;
          }
        }
        break;  // 跳出 switch
      case 0x10Du:  // case 分支 0x10D
        byte_8A6E9B = 1;
        sub_407390(this, -1000, -1000);  // 调 sub_407390
        memset(byte_8A6A98, 0, sizeof(byte_8A6A98));  // 调 memset
        memset(&byte_8A6298, 0, 0x400u);  // 调 memset
        memset(byte_8A6698, 0, sizeof(byte_8A6698));  // 调 memset
        byte_8A6E9A = 0;  // byte_8A6E9A = 0/空
        return 0;
      default:  // 默认分支
        break;  // 跳出 switch
    }
  }
  return 0;
}



// ============================================================
// SECTION 0x407AE0 — 子系统注册容器族（树/链表基础设施，为 0x41 区等上层共用）
// ============================================================
// ------------------------------------------------------------
// 0x407AE0 sub_407AE0 —— 事件分发对象启动（+12 存宿主 → 虚表槽 12 初始化 → 置字节 +4 就绪）
// ★ broadcast_debug 初始化链调用（失败弹 CStringManager 文案）；与 ·sub_407B20 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_407AE0(uint8_t *this, int nArg2)  // 【子系统注册容器族（树/链表基础设施，为 0x41 区等上层共用）】
{
  int result; // eax
  int v4; // edx

  if ( *(this + 4) != 0 )
    return -2147483646;  // 返回 0x80000002（已初始化）
  v4 = *(uint32_t *)this;
  *((uint32_t *)this + 3) = nArg2;  // this 偏移 12 = 参数2
  result = (*(int (/*thiscall*/ **)(uint8_t *))(v4 + 12))(this);  // 调用虚函数/间接调用
  if ( result >= 0 )  // 若 result >= 0
  {
    *(this + 4) = 1;  // this+4 = 1
    return 1;  // 返回 1（成功）
  }
  return result;
}



// ------------------------------------------------------------
// 0x407B20 sub_407B20 —— 事件分发对象停止（虚表槽 16 关闭 + +12 与字节 +4 清零）
// 被 ·sub_405E70 / ·sub_406770 析构链调用 —— 与 ·sub_407AE0 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_407B20(uint32_t *this)  // 函数 事件分发对象停止（虚表槽 16 关闭 + +12 与字节 +4 清零）
{
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 16))(this);  // 调 this 虚函数
  *(this + 3) = 0;  // this+3 清 0
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x407B40 sub_407B40 [串: "list<T> too long"]
// ------------------------------------------------------------
int /*thiscall*/ sub_407B40(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // fld_e2 = this+2 字段
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // 调 sub_401740
    pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+2 = result
  return result;
}



// ------------------------------------------------------------
// 0x407BD0 sub_407BD0 —— 事件分发对象子项批量析构（+16 哨兵链逐节点虚表槽 0 销毁 + 节点回收）
// 字节 +4 就绪才执行；先 ·sub_408220 重排，回收时 +8 计数递减；★ gfx_texture 调用。
// ------------------------------------------------------------
char /*thiscall*/ sub_407BD0(int this)  // 函数 事件分发对象子项批量析构（+16 哨兵链逐节点虚表槽 0 销毁 + 节点回收）
{
  void **fld_14; // eax
  int pThis_10; // ebx
  uint32_t *v4; // esi
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  uint32_t *v6; // edi

  LOBYTE(fld_14) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_14 != 0 )
  {
    pThis_10 = this + 16;
    sub_408220(this + 16);
    fld_14 = *(void ***)(this + 20);
    v4 = *fld_14;  // v4 = 解引用 fld_14
    if ( *fld_14 != fld_14 )
    {
      do  // do 循环体
      {
        v5 = (int (/*thiscall*/ ***)(uint32_t, int))v4[2];
        if ( v5 != nullptr )  // 若 v5 非空
          LOBYTE(fld_14) = (**v5)(v5, 1);
        v4[2] = 0;
        v6 = (uint32_t *)*v4;
        if ( v4 != *(uint32_t **)(pThis_10 + 4) )
        {
          *(uint32_t *)v4[1] = v6;
          *(uint32_t *)(*v4 + 4) = v4[1];
          j__free(v4);
          fld_14 = (void **)(*(uint32_t *)(pThis_10 + 8) - 1);
          *(uint32_t *)(pThis_10 + 8) = fld_14;  // pThis_10+8 = fld_14
        }
        v4 = v6;
      }
      while ( v6 != *(uint32_t **)(this + 20) );
    }
  }
  return (char)fld_14;
}



// ------------------------------------------------------------
// 0x407C40 sub_407C40 —— 事件分发对象带参启动（+16/+20/+24 三参数 + 字节 +13 标志 → 虚表槽 56）
// ★ broadcast_debug 以 640/480/16 启动渲染宿主；与 ·sub_407C90 复位成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_407C40(uint8_t *this, int nArg2, int nArg3, int nArg4, char pszArg5)  // 函数 事件分发对象带参启动（+16/+20/+24 三参数 + 字节 +13 标志 → 虚表槽 56）
{
  int result; // eax
  int v7; // edx

  if ( *(this + 4) != 0 )
    return -2147483646;  // 返回 0x80000002（已初始化）
  *((uint32_t *)this + 4) = nArg2;  // this 偏移 16 = 参数2
  *((uint32_t *)this + 5) = nArg3;  // this 偏移 20 = 参数3
  *((uint32_t *)this + 6) = nArg4;  // this 偏移 24 = 参数4
  v7 = *(uint32_t *)this;
  *(this + 13) = pszArg5;
  result = (*(int (/*thiscall*/ **)(uint8_t *))(v7 + 56))(this);  // 调用虚函数/间接调用
  if ( result >= 0 )  // 若 result >= 0
  {
    *(this + 4) = 1;  // this+4 = 1
    return 1;  // 返回 1（成功）
  }
  return result;
}



// ------------------------------------------------------------
// 0x407C90 sub_407C90 —— 事件分发对象状态复位（虚表槽 60 关闭 + +16..+36 五字段与字节 +4 清零）
// 被 ·sub_405F80 / ·sub_406310 析构链调用 —— 与 ·sub_407C40 启动成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_407C90(uint32_t *this)  // 函数 事件分发对象状态复位（虚表槽 60 关闭 + +16..+36 五字段与字节 +4 清零）
{
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);  // 调 this 虚函数
  *(this + 4) = 0;  // this+4 清 0
  *(this + 5) = 0;  // this+5 清 0
  *(this + 6) = 0;  // this+6 清 0
  *(this + 7) = 0;  // this+7 清 0
  *(this + 8) = 0;  // this+8 清 0
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x407CB0 sub_407CB0 —— 路径写入 NPK 包搜索目录（按 std::string 容量判 SSO 后转发 ·sub_40F2B0）
// ·sub_40F2B0 → ·sub_40EF70(*.npk 扫描)；★ broadcast_debug 以 ImagePacks2/ 调用。
// ------------------------------------------------------------
char /*thiscall*/ sub_407CB0(uint8_t *this, int pArg2)  // 函数 路径写入 NPK 包搜索目录（按 std::string 容量判 SSO 后转发 ·sub_40F2B0）
{
  *(this + 12) = 1;  // this+12 = 1
  if ( *(uint32_t *)(pArg2 + 24) < 0x10u )
    sub_40F2B0((LPCSTR)(pArg2 + 4), 0);  // 调 sub_40F2B0
  else  // 否则分支
    sub_40F2B0(*(LPCSTR *)(pArg2 + 4), 0);  // 调 sub_40F2B0
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x407CF0 sub_407CF0 —— 事件分发对象带状态复位（+12/+13 清零 + 五字段（末位 255）+ 链表清 → 虚表槽 52）
// 与 ·sub_405F10 构造成对 —— ·sub_6569D0 清 this+40 哨兵链。
// ------------------------------------------------------------
int /*thiscall*/ sub_407CF0(uint8_t *this)  // 函数 事件分发对象带状态复位（+12/+13 清零 + 五字段（末位 255）+ 链表清 → 虚表槽 52）
{
  *(this + 12) = 0;  // this+12 清 0
  *(this + 13) = 0;  // this+13 清 0
  *((uint32_t *)this + 4) = 0;  // this 偏移 16 清 0
  *((uint32_t *)this + 5) = 0;  // this 偏移 20 清 0
  *((uint32_t *)this + 6) = 0;  // this 偏移 24 清 0
  *((uint32_t *)this + 7) = 0;  // this 偏移 28 清 0
  *((uint32_t *)this + 8) = 255;  // this 偏移 32 = 255
  sub_6569D0(this + 40);
  return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);  // 调用虚函数并返回
}



// ------------------------------------------------------------
// 0x407D20 sub_407D20 —— 子对象解绑（虚表槽 0 销毁所指向对象 + ·sub_407EA0 摘链 + 指针置空）
// 字节 +4 未就绪或 *uArg2 为空均返回 -2147483647。
// ------------------------------------------------------------
int /*thiscall*/ sub_407D20(uint8_t *this, uint32_t *uArg2)  // 函数 子对象解绑（虚表槽 0 销毁所指向对象 + ·sub_407EA0 摘链 + 指针置空）
{
  if ( *(this + 4) == 0 )
    return -2147483647;  // 返回 0x80000001（未就绪）
  if ( *uArg2 == 0 )
    return -2147483647;  // 返回 0x80000001（未就绪）
  (**(void (/*thiscall*/ ***)(uint32_t, int))*uArg2)(*uArg2, 1);
  sub_407EA0(uArg2);  // 调 sub_407EA0
  *uArg2 = 0;  // 写指针 = 0
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x407D70 sub_407D70 [串: "list<T> too long"]
// ------------------------------------------------------------
int /*thiscall*/ sub_407D70(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // fld_e2 = this+2 字段
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // 调 sub_401740
    pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+2 = result
  return result;
}



// ------------------------------------------------------------
// 0x407E00 sub_407E00 —— 事件分发对象子项批量析构（+40 哨兵链逐节点虚表槽 0 销毁 + 回收）
// 与 ·sub_407BD0 / ·sub_407FD0 逐行同构（差异：链表偏移 +40）。
// ------------------------------------------------------------
int /*thiscall*/ sub_407E00(int this)  // 函数 事件分发对象子项批量析构（+40 哨兵链逐节点虚表槽 0 销毁 + 回收）
{
  int pThis_28; // ebx
  void **fld_2C; // eax
  uint32_t *v5; // esi
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // edi

  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  pThis_28 = this + 40;
  sub_408220(this + 40);
  fld_2C = *(void ***)(this + 44);
  v5 = *fld_2C;  // v5 = 解引用 fld_2C
  if ( *fld_2C != fld_2C )
  {
    do  // do 循环体
    {
      v6 = (void (/*thiscall*/ ***)(uint32_t, int))v5[2];
      if ( v6 != nullptr )  // 若 v6 非空
        (**v6)(v6, 1);
      v5[2] = 0;
      v7 = (uint32_t *)*v5;
      if ( v5 != *(uint32_t **)(pThis_28 + 4) )
      {
        *(uint32_t *)v5[1] = v7;
        *(uint32_t *)(*v5 + 4) = v5[1];
        j__free(v5);
        --*(uint32_t *)(pThis_28 + 8);
      }
      v5 = v7;
    }
    while ( v7 != *(uint32_t **)(this + 44) );
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x407E80 sub_407E80 —— 事件分发对象链表清（·sub_6569D0 清 this+16 链 → 虚表槽 28）
// 与 ·sub_406020 构造成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_407E80(char *this)  // 函数 事件分发对象链表清（·sub_6569D0 清 this+16 链 → 虚表槽 28）
{
  sub_6569D0(this + 16);
  return (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 28))(this);  // 调用虚函数并返回
}



// ------------------------------------------------------------
// 0x407EA0 sub_407EA0 —— 链表按值摘除（遍历哨兵环，节点 +8 == *uArg2 时摘除 free 且计数递减）
// 全链遍历不提前退出 —— 移除全部匹配（list::remove 语义）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_407EA0(uint32_t *this, uint32_t *uArg2)
{
  uint32_t **fld_e1; // ebx
  uint32_t *result; // eax
  uint32_t *v5; // edi

  fld_e1 = (uint32_t **)*(this + 1);
  result = *fld_e1;  // result = 解引用 fld_e1
  while ( result != fld_e1 )
  {
    if ( result[2] == *uArg2 )
    {
      v5 = (uint32_t *)*result;
      if ( result != (uint32_t *)*(this + 1) )
      {
        *(uint32_t *)result[1] = v5;
        *(uint32_t *)(*result + 4) = result[1];
        j__free(result);
        --*(this + 2);
      }
      result = v5;
    }
    else  // 否则分支
    {
      result = (uint32_t *)*result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x407EF0 sub_407EF0 —— 子对象解绑 B（虚表槽 0 销毁 + ·sub_407EA0 从 +16 链摘除 + 置空）
// 与 ·sub_407D20 同构（差异：显式传链表 this+16）。
// ------------------------------------------------------------
int /*thiscall*/ sub_407EF0(int this, uint32_t *uArg2)  // 函数 子对象解绑 B（虚表槽 0 销毁 + ·sub_407EA0 从 +16 链摘除 + 置空）
{
  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  if ( *uArg2 == 0 )
    return -2147483647;  // 返回 0x80000001（未就绪）
  (**(void (/*thiscall*/ ***)(uint32_t, int))*uArg2)(*uArg2, 1);
  sub_407EA0((uint32_t *)(this + 16), uArg2);  // 调 sub_407EA0
  *uArg2 = 0;  // 写指针 = 0
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x407F40 sub_407F40 [串: "list<T> too long"]
// ------------------------------------------------------------
int /*thiscall*/ sub_407F40(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // fld_e2 = this+2 字段
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // 调 sub_401740
    pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+2 = result
  return result;
}



// ------------------------------------------------------------
// 0x407FD0 sub_407FD0 —— 事件分发对象子项批量析构（+16 哨兵链逐节点虚表槽 0 销毁 + 回收）
// 与 ·sub_407E00 逐行同构（差异：链表偏移 +16）。
// ------------------------------------------------------------
int /*thiscall*/ sub_407FD0(int this)  // 函数 事件分发对象子项批量析构（+16 哨兵链逐节点虚表槽 0 销毁 + 回收）
{
  int pThis_10; // ebx
  void **fld_14; // eax
  uint32_t *v5; // esi
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // edi

  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  pThis_10 = this + 16;
  sub_408220(this + 16);
  fld_14 = *(void ***)(this + 20);
  v5 = *fld_14;  // v5 = 解引用 fld_14
  if ( *fld_14 != fld_14 )
  {
    do  // do 循环体
    {
      v6 = (void (/*thiscall*/ ***)(uint32_t, int))v5[2];
      if ( v6 != nullptr )  // 若 v6 非空
        (**v6)(v6, 1);
      v5[2] = 0;
      v7 = (uint32_t *)*v5;
      if ( v5 != *(uint32_t **)(pThis_10 + 4) )
      {
        *(uint32_t *)v5[1] = v7;
        *(uint32_t *)(*v5 + 4) = v5[1];
        j__free(v5);
        --*(uint32_t *)(pThis_10 + 8);
      }
      v5 = v7;
    }
    while ( v7 != *(uint32_t **)(this + 20) );
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x408060 sub_408060 —— 事件分发对象初始化（+12=1 + +16..+24 清零 + +28=100 + 双链表清 → 虚表槽 16）
// 与 ·sub_406130 构造成对；双链（+36/+48）均经 ·sub_6569D0 清空。
// ------------------------------------------------------------
int /*thiscall*/ sub_408060(uint8_t *this)  // 函数 事件分发对象初始化（+12=1 + +16..+24 清零 + +28=100 + 双链表清 → 虚表槽 16）
{
  *(this + 12) = 1;  // this+12 = 1
  *((uint32_t *)this + 4) = 0;  // this 偏移 16 清 0
  *((uint32_t *)this + 5) = 0;  // this 偏移 20 清 0
  *((uint32_t *)this + 6) = 0;  // this 偏移 24 清 0
  *((uint32_t *)this + 7) = 100;  // this 偏移 28 = 100
  sub_6569D0(this + 36);
  sub_6569D0(this + 48);
  return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 16))(this);  // 调用虚函数并返回
}



// ------------------------------------------------------------
// 0x4080A0 sub_4080A0 —— 子对象解绑 C（虚表槽 0 销毁 + ·sub_407EA0 从 +36 链摘除 + 置空）
// 与 ·sub_407D20 / ·sub_407EF0 同族（差异：链表偏移 +36）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4080A0(int this, uint32_t *uArg2)  // 函数 子对象解绑 C（虚表槽 0 销毁 + ·sub_407EA0 从 +36 链摘除 + 置空）
{
  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  if ( *uArg2 == 0 )
    return -2147483647;  // 返回 0x80000001（未就绪）
  (**(void (/*thiscall*/ ***)(uint32_t, int))*uArg2)(*uArg2, 1);
  sub_407EA0((uint32_t *)(this + 36), uArg2);  // 调 sub_407EA0
  *uArg2 = 0;  // 写指针 = 0
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x4080F0 sub_4080F0 [串: "list<T> too long"]
// ------------------------------------------------------------
int /*thiscall*/ sub_4080F0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // fld_e2 = this+2 字段
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // 调 sub_401740
    pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+2 = result
  return result;
}



// ------------------------------------------------------------
// 0x408180 sub_408180 —— 链表节点插入 B（·sub_40C0F0 建节点挂哨兵环 + ·sub_4080F0 计数与溢出检查）
// 与 ·sub_406850 逐行同构（差异：抛出器为 ·sub_4080F0）；
// ★ 被 ·0x40AE90 调用（以对象 +36 处列表指针传入）。
// ------------------------------------------------------------
int /*thiscall*/ sub_408180(uint32_t *this, int nArg2)  // 函数 链表节点插入 B（·sub_40C0F0 建节点挂哨兵环 + ·sub_4080F0 计数与溢出检查）
{
  int fld_e1; // edi
  int v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), nArg2);  // v4 = sub_40C0F0(...)
  result = sub_4080F0(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;  // fld_e1+4 = v4
  **(uint32_t **)(v4 + 4) = v4;  // v4 偏移 4 指向自身（自环）
  return result;
}



// ------------------------------------------------------------
// 0x4081C0 sub_4081C0 —— 事件分发对象注册子项（字节 +12 就绪时 ·sub_40C0F0 建节点挂 +48 链表）
// ★ gfx_texture 0x414530 以 sub_4081C0(this+44, this) 调用 —— 对象注册入口。
// ------------------------------------------------------------
int /*thiscall*/ sub_4081C0(int this, char pszArg2)  // 函数 事件分发对象注册子项（字节 +12 就绪时 ·sub_40C0F0 建节点挂 +48 链表）
{
  int fld_34; // edi
  uint32_t *pThis_30; // esi
  int v5; // ebx

  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  if ( *(uint8_t *)(this + 12) != 0 )  // 若 this 偏移 12 非 0
  {
    fld_34 = *(uint32_t *)(this + 52);
    pThis_30 = (uint32_t *)(this + 48);  // pThis_30 = this+48 指针
    v5 = sub_40C0F0(fld_34, *(uint32_t *)(fld_34 + 4), &pszArg2);  // 调 list 结点分配（12B：前驱/后继/数据）
    sub_4080F0(pThis_30, 1u);  // 调 sub_4080F0
    *(uint32_t *)(fld_34 + 4) = v5;  // fld_34+4 = v5
    **(uint32_t **)(v5 + 4) = v5;  // v5 偏移 4 指向自身（自环）
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x408220 sub_408220 —— 哨兵链表重排（+8 计数 >= 2 时对链首区段做四指针解链交换）
// ★ ·sub_407BD0 / ·sub_407E00 / ·sub_407FD0 / ·sub_408280 在销毁循环前统一调用【推断】。
// ------------------------------------------------------------
void /*fastcall*/ sub_408220(int pArg1)
{
  uint32_t **v1; // ebx
  uint32_t *v2; // eax
  int v3; // esi
  uint32_t *v4; // edx
  int v5; // edi
  int pArg12; // [esp+0h] [ebp-4h]

  pArg12 = pArg1;
  if ( *(uint32_t *)(pArg1 + 8) >= 2u )
  {
    v1 = *(uint32_t ***)(pArg1 + 4);
    v2 = (uint32_t *)**v1;
    if ( v2 != v1 )
    {
      while ( 1 )  // 当 1 非 0 循环
      {
        v3 = **(uint32_t **)(pArg1 + 4);
        v4 = v2;
        v2 = (uint32_t *)*v2;
        *(uint32_t *)v4[1] = v2;
        *(uint32_t *)v2[1] = v3;
        **(uint32_t **)(v3 + 4) = v4;  // v3 偏移 4 指向自身（自环）
        v5 = *(uint32_t *)(v3 + 4);
        *(uint32_t *)(v3 + 4) = v2[1];  // v3+4 = v2[1]
        v2[1] = v4[1];
        v4[1] = v5;
        if ( v2 == v1 )
          break;  // 跳出 switch
        pArg1 = pArg12;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x408280 sub_408280 —— 事件分发对象子项批量析构（+36 哨兵链逐节点虚表槽 0 销毁 + 回收）
// 与 ·sub_407E00 / ·sub_407FD0 逐行同构（差异：链表偏移 +36）。
// ------------------------------------------------------------
int /*thiscall*/ sub_408280(int this)  // 函数 事件分发对象子项批量析构（+36 哨兵链逐节点虚表槽 0 销毁 + 回收）
{
  int pThis_24; // ebx
  void **fld_28; // eax
  uint32_t *v5; // esi
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // edi

  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  pThis_24 = this + 36;
  sub_408220(this + 36);
  fld_28 = *(void ***)(this + 40);
  v5 = *fld_28;  // v5 = 解引用 fld_28
  if ( *fld_28 != fld_28 )
  {
    do  // do 循环体
    {
      v6 = (void (/*thiscall*/ ***)(uint32_t, int))v5[2];
      if ( v6 != nullptr )  // 若 v6 非空
        (**v6)(v6, 1);
      v5[2] = 0;
      v7 = (uint32_t *)*v5;
      if ( v5 != *(uint32_t **)(pThis_24 + 4) )
      {
        *(uint32_t *)v5[1] = v7;
        *(uint32_t *)(*v5 + 4) = v5[1];
        j__free(v5);
        --*(uint32_t *)(pThis_24 + 8);
      }
      v5 = v7;
    }
    while ( v7 != *(uint32_t **)(this + 40) );
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x408300 sub_408300 —— IObject 基类析构（挂 off_6C1BE8 → ·sub_40F3B0（虚表槽 120）→ 回落 IObject::vftable）
// 字节 +4 清零；★ 与 ·sub_408400 删除壳成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_408300(uint8_t *this)  // 函数 IObject 基类析构（挂 off_6C1BE8 → ·sub_40F3B0（虚表槽 120）→ 回落 IObject::vftabl…
{
  int result; // eax

  *(uint32_t *)this = &off_6C1BE8;  // vftable = off_6C1BE8
  result = sub_40F3B0();  // 调 : 转发虚表槽 +120 并返回
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *(this + 4) = 0;  // this+4 清 0
  return result;
}



// ------------------------------------------------------------
// 0x408370 sub_408370 —— 字段设置器（this+64 = nArg2，返回 nArg2）
// 与 ·sub_4083A0（this+68）同构的 setter 对。
// ------------------------------------------------------------
int /*thiscall*/ sub_408370(uint32_t *this, int nArg2)  // 函数 字段设置器（this+64 = nArg2，返回 nArg2）
{
  *(this + 16) = nArg2;  // this+16 = 参数2
  return nArg2;  // 返回入参
}



// ------------------------------------------------------------
// 0x4083A0 sub_4083A0 —— 字段设置器（this+68 = nArg2，返回 nArg2）
// 与 ·sub_408370（this+64）同构的 setter 对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4083A0(uint32_t *this, int nArg2)  // 函数 字段设置器（this+68 = nArg2，返回 nArg2）
{
  *(this + 17) = nArg2;  // this+17 = 参数2
  return nArg2;  // 返回入参
}



// ------------------------------------------------------------
// 0x408400 sub_408400 —— IObject 基类删除壳（·sub_408300 + 低位置位 free）
// 与 ·sub_408300 成对的标准删除壳。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408400(uint8_t *Block, char pszArg2)  // 函数 IObject 基类删除壳（·sub_408300 + 低位置位 free）
{
  sub_408300(Block);  // 调 sub_408300
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x408430 sub_408430 —— 显示对象基类构造（off_6C1BE8 → off_6C1C98 两级虚表）
// this[2]=nArg2；·sub_40F360 初始化 off_6C1BE8 子对象（vt+92 传 -16711936 = 0xFF00FF00【推断：默认填充色】）
// this[30]/[31] 存 nArg3/nArg4 后改挂 off_6C1C98，末以 ·sub_40FD50 清 +76..+132 状态区
// ★ 被 ·sub_408570 / ·sub_4086A0 / ·sub_408770 / ·sub_408A90 复用为基类构造（由 ·0x40A520 资源工厂装配）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408430(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数 显示对象基类构造（off_6C1BE8 → off_6C1C98 两级虚表）
{
  *(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)this = &off_6C1BE8;  // vftable = off_6C1BE8
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  sub_40F360();  // 调 sub_40F360
  *((uint32_t *)this + 30) = nArg3;  // this 偏移 120 = 参数3
  *(uint32_t *)this = &off_6C1C98;  // vftable = off_6C1C98
  *((uint32_t *)this + 31) = nArg4;  // this 偏移 124 = 参数4
  sub_40FD50(this);  // 调 sub_40FD50
  return this;
}



// ------------------------------------------------------------
// 0x4084A0 sub_4084A0 —— 显示对象基类析构（虚表逐级回落 off_6C1C98 → off_6C1BE8 → IObject::vftable）
// ·sub_40FF30 释放本层绘制资源（+112/+116 接口 vt+8、+16 缓冲 free、+88..+108 清零）后交 ·sub_40F3B0（基类 vt+120）
// 字节 +4 清零；与 ·sub_408430 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4084A0(uint8_t *this)  // 函数 显示对象基类析构（虚表逐级回落 off_6C1C98 → off_6C1BE8 → IObject::vftable）
{
  int result; // eax

  *(uint32_t *)this = &off_6C1C98;  // vftable = off_6C1C98
  sub_40FF30();  // 调 sub_40FF30
  *(uint32_t *)this = &off_6C1BE8;  // vftable = off_6C1BE8
  result = sub_40F3B0(this);  // 调 : 转发虚表槽 +120 并返回
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *(this + 4) = 0;  // this+4 清 0
  return result;
}



// ------------------------------------------------------------
// 0x408500 sub_408500 —— 表面创建转发 A（用法标志 21）
// 直通 ·0x411240（D3D 表面创建与行表建立）；同族 ·sub_4086D0 传 26 —— 该值触发 ·0x411240 内尺寸向上取 2 的幂（·sub_4111E0）。
// ------------------------------------------------------------
int /*stdcall*/ sub_408500(int xRight, int yBottom)  // 函数 表面创建转发 A（用法标志 21）
{
  return sub_411240(xRight, yBottom, 21);
}



// ------------------------------------------------------------
// 0x408520 sub_408520 —— 绘制参数转发（基类虚表槽 140）
// 以 this+48 子对象地址为中间参数调 vt+140，两端传 nArg2/nArg3【推断：资源绑定或描述填写路径】。
// ------------------------------------------------------------
int /*thiscall*/ sub_408520(void *this, int nArg2, int nArg3)  // 函数 绘制参数转发（基类虚表槽 140）
{
  return (*(int (/*stdcall*/ **)(int, int, int))(*(uint32_t *)this + 140))(nArg2, (int)this + 48, nArg3);  // 调用虚函数并返回
}



// ------------------------------------------------------------
// 0x408540 sub_408540 —— 删除壳（·sub_4084A0 + 低位置位 free）
// 与 ·sub_4084A0 成对的标准删除壳。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408540(uint8_t *Block, char pszArg2)  // 函数 删除壳（·sub_4084A0 + 低位置位 free）
{
  sub_4084A0(Block);  // 调 sub_4084A0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x408570 sub_408570 —— 派生构造（off_6C1D50）
// ·sub_408430 基构造后改挂 off_6C1D50；0x88 对象 —— ·0x40A520 类型 1/8/16 经此创建。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408570(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数 派生构造（off_6C1D50）
{
  sub_408430(this, nArg2, nArg3, nArg4);  // 调 sub_408430
  *(uint32_t *)this = &off_6C1D50;  // vftable = off_6C1D50
  return this;
}



// ------------------------------------------------------------
// 0x4085A0 sub_4085A0 —— 删除壳（·sub_4085D0 + 低位置位 free）
// 与 ·sub_4085D0 成对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_4085A0(void *Block, char pszArg2)  // 函数 删除壳（·sub_4085D0 + 低位置位 free）
{
  sub_4085D0();  // 调 sub_4085D0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x4085D0 sub_4085D0 —— 析构（off_6C1D50 → ·sub_4084A0）
// 先 ·sub_40FF30 释放本层绘制资源，再交 ·sub_4084A0 基析构；与 ·sub_408570 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4085D0(uint8_t *this)  // 函数 析构（off_6C1D50 → ·sub_4084A0）
{
  *(uint32_t *)this = &off_6C1D50;  // vftable = off_6C1D50
  sub_40FF30();  // 调 sub_40FF30
  return sub_4084A0(this);  // 调 显示对象基类析构（虚表逐级回落 off_6C1C98 → off_6C1BE8 → IObject::vftable）
}



// ------------------------------------------------------------
// 0x408620 sub_408620 —— 析构（off_6C1E08 → ·sub_4084A0）
// 与 ·sub_4085D0 同构（差异：虚表常量 off_6C1E08）；被 ·sub_408720 / ·sub_4087A0 / ·sub_409AD0 复用。
// ------------------------------------------------------------
int /*thiscall*/ sub_408620(uint8_t *this)  // 函数 析构（off_6C1E08 → ·sub_4084A0）
{
  *(uint32_t *)this = &off_6C1E08;  // vftable = off_6C1E08
  sub_40FF30();  // 调 sub_40FF30
  return sub_4084A0(this);  // 调 显示对象基类析构（虚表逐级回落 off_6C1C98 → off_6C1BE8 → IObject::vftable）
}



// ------------------------------------------------------------
// 0x408670 sub_408670 —— 删除壳（·sub_408620 + 低位置位 free）
// 与 ·sub_408620 成对的标准删除壳。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408670(uint8_t *Block, char pszArg2)  // 函数 删除壳（·sub_408620 + 低位置位 free）
{
  sub_408620(Block);  // 调 sub_408620
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x4086A0 sub_4086A0 —— 派生构造（off_6C1EC0，+136 标志清零）
// ·0x40A520 类型 15 经此创建（0x8C 对象）；类型 1/8/16 的另一分支同族（+136 置 1）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4086A0(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数 派生构造（off_6C1EC0，+136 标志清零）
{
  sub_408430(this, nArg2, nArg3, nArg4);  // 调 sub_408430
  *(this + 136) = 0;  // this+136 清 0
  *(uint32_t *)this = &off_6C1EC0;  // vftable = off_6C1EC0
  return this;
}



// ------------------------------------------------------------
// 0x4086D0 sub_4086D0 —— 表面创建转发 B（用法标志 26）
// 直通 ·0x411240；26 使其内 nArg6==26 分支成立 → 尺寸经 ·sub_4111E0 向上取 2 的幂。
// ------------------------------------------------------------
int /*stdcall*/ sub_4086D0(int xRight, int yBottom)  // 函数 表面创建转发 B（用法标志 26）
{
  return sub_411240(xRight, yBottom, 26);
}



// ------------------------------------------------------------
// 0x4086F0 sub_4086F0 —— 删除壳（·sub_408720 + 低位置位 free）
// 与 ·sub_408720 成对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_4086F0(void *Block, char pszArg2)  // 函数 删除壳（·sub_408720 + 低位置位 free）
{
  sub_408720();  // 调 sub_408720
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x408720 sub_408720 —— 析构（off_6C1EC0 → ·sub_408620 → ·sub_4084A0）
// 与 ·sub_4085D0 族同构（差异：多一级虚表回落）；被 ·sub_4086F0 复用。
// ------------------------------------------------------------
int /*thiscall*/ sub_408720(uint8_t *this)  // 函数 析构（off_6C1EC0 → ·sub_408620 → ·sub_4084A0）
{
  *(uint32_t *)this = &off_6C1EC0;  // vftable = off_6C1EC0
  sub_40FF30();  // 调 sub_40FF30
  return sub_408620(this);  // 调 析构（off_6C1E08 → ·sub_4084A0）
}



// ------------------------------------------------------------
// 0x408770 sub_408770 —— 派生构造（off_6C1F78，+136 标志清零）
// 与 ·sub_4086A0 同构（差异：虚表常量 off_6C1F78）；0x8C 对象 —— ·0x40A520 类型 14 经此创建。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408770(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数 派生构造（off_6C1F78，+136 标志清零）
{
  sub_408430(this, nArg2, nArg3, nArg4);  // 调 sub_408430
  *(this + 136) = 0;  // this+136 清 0
  *(uint32_t *)this = &off_6C1F78;  // vftable = off_6C1F78
  return this;
}



// ------------------------------------------------------------
// 0x4087A0 sub_4087A0 —— 析构（off_6C1F78 → ·sub_408620）
// 与 ·sub_408720 同构；·sub_409AD0 为转发至此的 thunk。
// ------------------------------------------------------------
int /*thiscall*/ sub_4087A0(uint8_t *this)  // 函数 析构（off_6C1F78 → ·sub_408620）
{
  *(uint32_t *)this = &off_6C1F78;  // vftable = off_6C1F78
  sub_40FF30();  // 调 sub_40FF30
  return sub_408620(this);  // 调 析构（off_6C1E08 → ·sub_4084A0）
}



// ------------------------------------------------------------
// 0x4087F0 sub_4087F0 —— 表面创建转发 C（用法标志 25）
// 与 ·sub_408500 同构（差异：标志值）；gfx_texture ·0x411240 调用点亦用 25。
// ------------------------------------------------------------
int /*stdcall*/ sub_4087F0(int xRight, int yBottom)  // 函数 表面创建转发 C（用法标志 25）
{
  return sub_411240(xRight, yBottom, 25);
}



// ------------------------------------------------------------
// 0x408810 sub_408810 —— 删除壳（·sub_4087A0 + 低位置位 free）
// 与 ·sub_4087A0 成对的标准删除壳。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408810(uint8_t *Block, char pszArg2)  // 函数 删除壳（·sub_4087A0 + 低位置位 free）
{
  sub_4087A0(Block);  // 调 sub_4087A0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x408840 sub_408840 —— 显示对象第二基类构造（off_6C1BE8 → off_6C2030，单参）
// ·sub_40F360 初始化基类子对象，this[2]=nArg2 后改挂 off_6C2030 并调 nullsub_3；被 ·sub_4089B0 复用。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408840(uint8_t *this, int nArg2)  // 函数 显示对象第二基类构造（off_6C1BE8 → off_6C2030，单参）
{
  *(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)this = &off_6C1BE8;  // vftable = off_6C1BE8
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  sub_40F360();  // 调 sub_40F360
  *(uint32_t *)this = &off_6C2030;  // vftable = off_6C2030
  nullsub_3(this);  // nullsub（空桩）
  return this;
}



// ------------------------------------------------------------
// 0x4088A0 sub_4088A0 —— 第二基类析构（off_6C2030 → off_6C1BE8 → IObject::vftable）
// 经 ·sub_40F420 释放 +12/+16 缓冲；字节 +4 清零，与 ·sub_408840 成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4088A0(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = &off_6C2030;  // vftable = off_6C2030
  sub_40F420();  // 调 sub_40F420
  *(uint32_t *)this = &off_6C1BE8;  // vftable = off_6C1BE8
  result = sub_40F3B0(this);  // 调 : 转发虚表槽 +120 并返回
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *(this + 4) = 0;  // this+4 清 0
  return result;
}



// ------------------------------------------------------------
// 0x408900 sub_408900 —— 删除壳（·sub_4088A0 + 低位置位 free）
// 与 ·sub_4088A0 成对的标准删除壳。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408900(uint8_t *Block, char pszArg2)  // 函数 删除壳（·sub_4088A0 + 低位置位 free）
{
  sub_4088A0(Block);  // 调 sub_4088A0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x408930 sub_408930 —— 派生析构（off_6C20E0 → ·sub_4088A0）
// 先 ·sub_40F420 释放缓冲，再交 ·sub_4088A0 基析构；被 ·sub_408A40 调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_408930(uint8_t *this)  // 函数 派生析构（off_6C20E0 → ·sub_4088A0）
{
  *(uint32_t *)this = &off_6C20E0;  // vftable = off_6C20E0
  sub_40F420();  // 调 sub_40F420
  return sub_4088A0(this);
}



// ------------------------------------------------------------
// 0x408980 sub_408980 —— 删除壳（·sub_408930 + 低位置位 free）
// 与 ·sub_408930 成对的标准删除壳。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408980(uint8_t *Block, char pszArg2)  // 函数 删除壳（·sub_408930 + 低位置位 free）
{
  sub_408930(Block);  // 调 sub_408930
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x4089B0 sub_4089B0 —— 派生构造（off_6C2190，+108 = nArg3）
// ·sub_408840 基构造后写 this[27]=nArg3 并改挂 off_6C2190，末调 ·sub_413660（+104 清零）；0x70 对象 —— ·0x40A520 类型 3 与 gfx_texture 0x413B80 容器克隆共用。
// ------------------------------------------------------------
int /*thiscall*/ sub_4089B0(int this, int nArg2, int nArg3)  // 函数 派生构造（off_6C2190，+108 = nArg3）
{
  sub_408840((uint8_t *)this, nArg2);  // 调 sub_408840
  *(uint32_t *)(this + 108) = nArg3;  // this+108 = 参数3
  *(uint32_t *)this = &off_6C2190;  // vftable = off_6C2190
  sub_413660(this);  // 调 sub_413660
  return this;
}



// ------------------------------------------------------------
// 0x408A10 sub_408A10 —— 删除壳（·sub_408A40 + 低位置位 free）
// 与 ·sub_408A40 成对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_408A10(void *Block, char pszArg2)  // 函数 删除壳（·sub_408A40 + 低位置位 free）
{
  sub_408A40();  // 调 sub_408A40
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x408A40 sub_408A40 —— 析构（off_6C2190 → ·sub_413800 图像状态复位 → ·sub_408930）
// 先交 ·sub_413800 复位图像状态，再走 ·sub_408930 / ·sub_4088A0 两级基析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_408A40(uint8_t *this)  // 函数 析构（off_6C2190 → ·sub_413800 图像状态复位 → ·sub_408930）
{
  *(uint32_t *)this = &off_6C2190;  // vftable = off_6C2190
  sub_413800();  // 调 sub_413800
  return sub_408930(this);  // 调 派生析构（off_6C20E0 → ·sub_4088A0）
}



// ------------------------------------------------------------
// 0x408A90 sub_408A90 —— 派生构造（off_6C2240，+136 标志清零）
// 与 ·sub_408770 同构（差异：虚表常量 off_6C2240）；·0x40A520 类型 12/13 经此创建（内部固定以类型 14 传入）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408A90(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数 派生构造（off_6C2240，+136 标志清零）
{
  sub_408430(this, nArg2, nArg3, nArg4);  // 调 sub_408430
  *(this + 136) = 0;  // this+136 清 0
  *(uint32_t *)this = &off_6C2240;  // vftable = off_6C2240
  return this;
}



// ------------------------------------------------------------
// 0x408AC0 sub_408AC0 —— 渲染宿主对象初始化（约 184KB 大对象）
// 置 this+8 = 3；批量清 this+8336 起 0x2A378（显示模式表）、this+181256 起 0xD4、this+181468 起 0x600（三段 256 项 uint16 表）与 +56/+1080/+8276/+183004 等区
// ★ 被 ·sub_406280（事件分发对象构造 E，挂 off_6C19E8）调用 —— D3D8 应用框架宿主【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_408AC0(int this)  // 函数 渲染宿主对象初始化（约 184KB 大对象）
{
  *(uint32_t *)(this + 8) = 3;  // this+8（uint32 槽）= 3
  *(uint8_t *)(this + 52) = 0;  // this 偏移 52 清 0
  *(uint32_t *)(this + 8248) = 0;  // this+8248（uint32 槽）= 0
  *(uint32_t *)(this + 8252) = 0;  // this+8252（uint32 槽）= 0
  *(uint32_t *)(this + 8256) = 0;  // this+8256（uint32 槽）= 0
  *(uint32_t *)(this + 8264) = 0;  // this+8264（uint32 槽）= 0
  *(uint32_t *)(this + 8272) = 0;  // this+8272（uint32 槽）= 0
  *(uint8_t *)(this + 8268) = 0;  // this 偏移 8268 清 0
  *(uint32_t *)(this + 8328) = -1;  // this+8328 = -1
  *(uint32_t *)(this + 8332) = 0;  // this+8332（uint32 槽）= 0
  *(uint32_t *)(this + 8260) = 0;  // this+8260（uint32 槽）= 0
  *(uint32_t *)(this + 184040) = 0;  // this+184040（uint32 槽）= 0
  *(uint32_t *)(this + 184048) = 0;  // this+184048（uint32 槽）= 0
  *(uint32_t *)(this + 184052) = 0;  // this+184052（uint32 槽）= 0
  *(uint32_t *)(this + 184056) = 0;  // this+184056（uint32 槽）= 0
  memset((void *)(this + 8336), 0, 0x2A378u);  // 调 memset
  memset((void *)(this + 181256), 0, 0xD4u);  // 调 memset
  memset((void *)(this + 181468), 0, 0x600u);  // 调 memset
  *(uint32_t *)(this + 184024) = 0;  // this+184024（uint32 槽）= 0
  *(uint32_t *)(this + 184028) = 0;  // this+184028（uint32 槽）= 0
  *(uint32_t *)(this + 184032) = 0;  // this+184032（uint32 槽）= 0
  *(uint32_t *)(this + 184036) = 0;  // this+184036（uint32 槽）= 0
  memset((void *)(this + 8276), 0, 0x34u);  // 调 memset
  memset((void *)(this + 56), 0, 0x400u);  // 调 memset
  memset((void *)(this + 1080), 0, 0x1C00u);  // 调 memset
  memset((void *)(this + 183004), 0, 0x3FCu);  // 调 memset
  return 0;
}



// ============================================================
// SECTION 0x408B90 — GDI 位图工具 + NEOPLE_WEB 内嵌浏览器窗口抓屏（BitBlt 采样）
// ============================================================
// ------------------------------------------------------------
// 0x408B90 sub_408B90 —— 设备可用性检查（虚表槽 76）
// 槽 76 成功即返回 1；失败经 ·sub_407C90（虚表槽 60 关闭 + 状态位 +16 复位）后原样返回错误码。
// ------------------------------------------------------------
int /*thiscall*/ sub_408B90(uint32_t *this)  // 【GDI 位图工具 + NEOPLE_WEB 内嵌浏览器窗口抓屏（BitBlt 采样）】
{
  int v2; // edi

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 76))(this);
  if ( v2 >= 0 )  // 若 v2 >= 0
    return 1;  // 返回 1（成功）
  sub_407C90(this);  // 调 sub_407C90
  return v2;
}



// ------------------------------------------------------------
// 0x408BC0 sub_408BC0 —— 设备创建转发（虚表槽 80）
// 无守卫直通 this【推断：设备/资源创建入口】。
// ------------------------------------------------------------
int /*thiscall*/ sub_408BC0(void *this)  // 函数 设备创建转发（虚表槽 80）
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);  // 调用虚函数并返回
}



// ------------------------------------------------------------
// 0x408BD0 sub_408BD0 —— 出参缓存写 A（一维）
// 经 this+8252 对象 vt+200 调用后回写缓存 this[pArg2+14]【推断：设备能力/模式查询缓存】。
// ------------------------------------------------------------
int /*thiscall*/ sub_408BD0(uint32_t **this, int pArg2, uint32_t *uArg3)  // 函数 出参缓存写 A（一维）
{
  int result; // eax

  result = (*(int (/*stdcall*/ **)(uint32_t, int, uint32_t *))(**(this + 2063) + 200))(*(this + 2063), pArg2, uArg3);  // 调用虚函数/间接调用
  *(this + pArg2 + 14) = uArg3;
  return result;
}



// ------------------------------------------------------------
// 0x408C00 sub_408C00 —— 出参缓存读 A（一维，失败回退）
// 调 vt+204 成功则刷新并返回新值，失败回退缓存 this[pArg2+14]。
// ------------------------------------------------------------
int /*thiscall*/ sub_408C00(uint32_t *this, int pArg2)  // 函数 出参缓存读 A（一维，失败回退）
{
  int fld_e2063; // eax
  int result; // eax
  int v5; // [esp+8h] [ebp-4h] BYREF

  fld_e2063 = *(this + 2063);  // fld_e2063 = this+2063 字段
  v5 = 0;
  if ( (*(int (/*stdcall*/ **)(int, int, int *))(*(uint32_t *)fld_e2063 + 204))(fld_e2063, pArg2, &v5) < 0 )
    return *(this + pArg2 + 14);
  result = v5;
  *(this + pArg2 + 14) = v5;
  return result;
}



// ------------------------------------------------------------
// 0x408C50 sub_408C50 —— 出参缓存写 B（二维，步长 256）
// vt+252 调用后写 this + 256*pArg2 + pArg3 + 270，返回 pArg3。
// ------------------------------------------------------------
int /*thiscall*/ sub_408C50(uint32_t **this, int pArg2, int pArg3, uint32_t *uArg4)  // 函数 出参缓存写 B（二维，步长 256）
{
  (*(void (/*stdcall*/ **)(uint32_t, int, int, uint32_t *))(**(this + 2063) + 252))(*(this + 2063), pArg2, pArg3, uArg4);  // 调用虚函数/间接调用
  *(this + 256 * pArg2 + pArg3 + 270) = uArg4;
  return pArg3;
}



// ------------------------------------------------------------
// 0x408C90 sub_408C90 —— 出参缓存读 B（二维，失败回退）
// vt+248 成功则刷新 this + 256*nArg2 + nArg3 + 270，失败回退缓存值。
// ------------------------------------------------------------
int /*thiscall*/ sub_408C90(uint32_t *this, int nArg2, int nArg3)  // 函数 出参缓存读 B（二维，失败回退）
{
  int fld_e2063; // eax
  int v5; // esi
  int result; // eax
  int v7; // [esp+Ch] [ebp-4h] BYREF

  fld_e2063 = *(this + 2063);  // fld_e2063 = this+2063 字段
  v7 = 0;
  v5 = nArg3 + (nArg2 << 8);
  if ( (*(int (/*stdcall*/ **)(int, int, int, int *))(*(uint32_t *)fld_e2063 + 248))(fld_e2063, nArg2, nArg3, &v7) < 0 )
    return *(this + v5 + 270);
  result = v7;
  *(this + v5 + 270) = v7;
  return result;
}



// ------------------------------------------------------------
// 0x408CF0 sub_408CF0 —— GDI 位图 → BITMAPINFOHEADER（40 字节）转换
// GetObjectA(h, 24) 取 BITMAP 结构；按 位面*位数 选 4/8/16/24/32 bpp，写 biSize=40、biWidth/Height、biPlanes/biBitCount，
// biSizeImage = 高 * (((宽*bpp+31)&~31)/8)；★ 被 ·0x4090D0（NEOPLE_WEB 抓屏）用作 GetDIBits 前置。
// ------------------------------------------------------------
int /*usercall*/ sub_408CF0@<eax>(uint32_t *pArg1@<esi>, HANDLE h)  // 函数 GDI 位图 → BITMAPINFOHEADER（40 字节）转换
{
  int result; // eax
  int16_t v3; // bx
  uint16_t v4; // ax
  uint16_t v5; // ax
  int v6; // ecx
  int v7; // edi
  signed int v8; // eax
  uint8_t pv[4]; // [esp+4h] [ebp-18h] BYREF
  int v10; // [esp+8h] [ebp-14h]
  int v11; // [esp+Ch] [ebp-10h]
  int16_t v12; // [esp+14h] [ebp-8h]
  int v13; // [esp+16h] [ebp-6h]

  memset(pArg1, 0, 0x2Cu);  // 调 memset
  result = GetObjectA(h, 24, pv);
  if ( result != 0 )  // 若 result != 0
  {
    v3 = v12;
    v4 = v12 * v13;
    if ( v12 * (uint16_t)v13 == 1 )
    {
      v5 = 1;
    }
    else if ( v4 > 4u )
    {
      if ( v4 > 8u )
      {
        if ( v4 > 0x10u )
          v5 = v4 > 0x18u ? 32 : 24;
        else  // 否则分支
          v5 = 16;
      }
      else  // 否则分支
      {
        v5 = 8;
      }
    }
    else  // 否则分支
    {
      v5 = 4;
    }
    v6 = v10;
    v7 = v11;
    v8 = (v10 * v5 + 31) & 0xFFFFFFE0;
    *((uint16_t *)pArg1 + 7) = v13;
    *((uint16_t *)pArg1 + 6) = v3;
    result = v7 * (v8 / 8);
    pArg1[8] = 0;
    pArg1[4] = 0;
    pArg1[9] = 0;
    *pArg1 = 40;  // 写指针 = 40
    pArg1[1] = v6;
    pArg1[2] = v7;
    pArg1[5] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x408DB0 sub_408DB0 —— 全屏/窗口形态切换（nArg4 == 1 进入，否则退出）
// 进入：由 this+8252 vt+28 读 212 字节描述（v12[60] 位 1 置位且 v12[61] 位 0 清零时，默认 640x480 改 1024x512 —— 与 ·0x411240 同判据）→ vt+80(宽,高,1,0,23) 重建 → new(2*宽*高) 像素缓冲存 +184056
// 退出：free +184056 并 vt+8 释放 +184052，+184048 记形态；+13 == 0 或形态未变直接返回 1，+184052 为空返 0x80000000。
// ------------------------------------------------------------
unsigned int /*userpurge*/ sub_408DB0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)
{
  int *v6; // eax
  int v7; // ecx
  int v8; // ebx
  void *pMem; // eax
  int pObj; // eax
  uint8_t v12[212]; // [esp+4h] [ebp-D8h] BYREF
  int v13; // [esp+D8h] [ebp-4h]

  if ( *(uint8_t *)(pArg1 + 13) == 0 )
    return 1;  // 返回 1（成功）
  if ( *(uint32_t *)(pArg1 + 184048) == nArg4 )
    return 1;  // 返回 1（成功）
  if ( nArg4 == 1 )  // 若 nArg4 == 1
  {
    v6 = *(int **)(pArg1 + 8252);
    v7 = *v6;  // v7 = 解引用 v6
    v8 = 640;
    v13 = 480;
    (*(void (/*stdcall*/ **)(int *, uint8_t *, int, int))(v7 + 28))(v6, v12, nArg2, nArg3);  // 调用虚函数/间接调用
    if ( (v12[60] & 2) != 0 && (v12[61] & 1) == 0 )
    {
      v8 = 1024;
      v13 = 512;
    }
    (*(void (/*stdcall*/ **)(uint32_t, int, int, int, uint32_t, int))(**(uint32_t **)(pArg1 + 8252) + 80))(
      *(uint32_t *)(pArg1 + 8252),
      v8,
      v13,
      1,
      0,
      23);
    if ( *(uint32_t *)(pArg1 + 184052) != 0 )  // 若 pArg1 偏移 184052 != 0
    {
      pMem = operator new(2 * *(uint32_t *)(pArg1 + 16) * *(uint32_t *)(pArg1 + 20));
      *(uint32_t *)(pArg1 + 184048) = 1;  // pArg1+184048 = 1
      *(uint32_t *)(pArg1 + 184056) = pMem;  // pArg1+184056 = pMem
      return 1;  // 返回 1（成功）
    }
    else  // 否则分支
    {
      return 0x80000000;  // 返回 0x80000000（失败）
    }
  }
  else  // 否则分支
  {
    j_j__free(*(void **)(pArg1 + 184056));
    pObj = *(uint32_t *)(pArg1 + 184052);
    *(uint32_t *)(pArg1 + 184056) = 0;  // pArg1+184056 = 0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 8))(pObj);  // 调用虚函数/间接调用
    *(uint32_t *)(pArg1 + 184052) = 0;  // pArg1+184052 = 0
    *(uint32_t *)(pArg1 + 184048) = nArg4;  // pArg1+184048 = nArg4
    return 1;  // 返回 1（成功）
  }
}



// ------------------------------------------------------------
// 0x408EE0 sub_408EE0 —— 设备与渲染对象链释放（+8248..+8260 四接口 + 抓屏接口）
// this+8248 非空时先 vt+64 解绑；再依次释放 +8260（经 (**fld)(fld,1) 自释放）、+8256、+8252、+8248、+184052（各 vt+8）并全部置 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_408EE0(uint32_t *this)  // 函数 设备与渲染对象链释放（+8248..+8260 四接口 + 抓屏接口）
{
  void (/*thiscall*/ ***fld_e2065)(uint32_t, int); // ecx
  int fld_e2064; // eax
  int fld_e2063; // eax
  int fld_e2062; // eax
  int fld_e46013; // eax

  if ( *(this + 2062) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 64))(this, 0);  // 调用虚函数/间接调用
    fld_e2065 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2065);
    if ( fld_e2065 != nullptr )  // 若 fld_e2065 非空
      (**fld_e2065)(fld_e2065, 1);
    fld_e2064 = *(this + 2064);  // fld_e2064 = this+2064 字段
    *(this + 2065) = 0;  // this+2065 清 0
    if ( fld_e2064 != 0 )  // 若 fld_e2064 != 0
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e2064 + 8))(fld_e2064);  // 调用虚函数/间接调用
    fld_e2063 = *(this + 2063);  // fld_e2063 = this+2063 字段
    *(this + 2064) = 0;  // this+2064 清 0
    if ( fld_e2063 != 0 )  // 若 fld_e2063 != 0
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e2063 + 8))(fld_e2063);  // 调用虚函数/间接调用
    fld_e2062 = *(this + 2062);  // fld_e2062 = this+2062 字段
    *(this + 2063) = 0;  // this+2063 清 0
    if ( fld_e2062 != 0 )  // 若 fld_e2062 != 0
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e2062 + 8))(fld_e2062);  // 调用虚函数/间接调用
    fld_e46013 = *(this + 46013);  // fld_e46013 = this+46013 字段
    *(this + 2062) = 0;  // this+2062 清 0
    if ( fld_e46013 != 0 )  // 若 fld_e46013 != 0
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e46013 + 8))(fld_e46013);  // 调用虚函数/间接调用
    *(this + 46013) = 0;  // this+46013 清 0
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x408F70 sub_408F70 —— 显示模式应用转发
// this+8256 对象 vt+32 恢复，再交 ·sub_413EE0(this + 8276, 0)（窗口尺寸调整族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_408F70(uint32_t **this)
{
  (*(void (/*stdcall*/ **)(uint32_t))(**(this + 2064) + 32))(*(this + 2064));  // 调用虚函数/间接调用
  return sub_413EE0((DWORD)(this + 2069), 0);  // 【窗口尺寸调整族（GetWindowLong/GetSystemMetrics/Adj…】
}



// ------------------------------------------------------------
// 0x408FA0 sub_408FA0 —— 全屏/窗口切换（nArg2 0/1）
// 按 +8328 设备索引取 17292 步长表项（+8336 基址）；+8296 记模式（1 全屏 / 2 窗口）、+8284 记宽高，窗口分支另取 GetWindowLongA(-16/-20) 存 +184040/+184044，末调 ·sub_414090(+8276)
// ★ 发布指令直证：broadcast_debug 的 //full → ·0x408FA0(1)、//normal → ·0x408FA0(0)。
// ------------------------------------------------------------
int /*thiscall*/ sub_408FA0(int this, int nArg2)  // 函数 全屏/窗口切换（nArg2 0/1）
{
  int fld_2088; // ecx
  int pThis_2090; // edi
  int pThis_6418; // ebx
  int fld_24; // ecx
  LONG WindowLongA; // eax
  int fld_242; // edx

  fld_2088 = 17292 * *(uint32_t *)(this + 8328);
  pThis_2090 = fld_2088 + this + 8336;
  pThis_6418 = 3240 * *(uint32_t *)(fld_2088 + this + 25624)
     + pThis_2090
     + 1088
     + 20 * *(uint32_t *)(3240 * *(uint32_t *)(fld_2088 + this + 25624) + pThis_2090 + 4316)
     + 228;
  (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 8256) + 32))(*(uint32_t *)(this + 8256));  // 调用虚函数/间接调用
  if ( *(uint8_t *)(this + 13) != 0 )  // 若 this 偏移 13 非 0
  {
    *(uint32_t *)(this + 8284) = *(uint32_t *)(pThis_2090 + 1080);  // this+8284 = *(uint32_t *)(pThis_2090 + 1080)
    *(uint32_t *)(this + 8296) = 1;  // this+8296（uint32 槽）= 1
  }
  else  // 否则分支
  {
    fld_24 = *(uint32_t *)(this + 36);
    *(uint32_t *)(this + 8284) = *(uint32_t *)(pThis_6418 + 8);  // this+8284 = *(uint32_t *)(pThis_6418 + 8)
    *(uint32_t *)(this + 8296) = 2;  // this+8296（uint32 槽）= 2
    WindowLongA = GetWindowLongA(*(HWND *)(fld_24 + 16), -16);
    fld_242 = *(uint32_t *)(this + 36);
    *(uint32_t *)(this + 184040) = WindowLongA;  // this+184040 = WindowLongA
    *(uint32_t *)(this + 184044) = GetWindowLongA(*(HWND *)(fld_242 + 16), -20);  // this+184044 = GetWindowLongA(*(HWND *)(fld_242 + 16), -20)
  }
  *(uint8_t *)(this + 13) = nArg2 == 1;
  *(uint32_t *)(this + 8304) = nArg2 == 0;  // this+8304 = nArg2 == 0
  return sub_414090(this + 8276);  // 调 窗口尺寸调整（带边框变体）
}



// ------------------------------------------------------------
// 0x409080 sub_409080 —— 前序兄弟窗口遍历挂钩
// GetWindow(hWnd, GW_HWNDPREV) 非空时：可见窗口（样式 0x10000000）先经虚表槽 72，再统一经槽 68【推断：窗口枚举回调】。
// ------------------------------------------------------------
int /*thiscall*/ sub_409080(void *this, HWND hWnd)
{
  HWND Window; // eax
  HWND v4; // edi

  Window = GetWindow(hWnd, 3u);
  v4 = Window;
  if ( Window != nullptr )  // 若 Window 非空
  {
    if ( (GetWindowLongA(Window, -16) & 0x10000000) != 0 )
      (*(void (/*thiscall*/ **)(void *, HWND))(*(uint32_t *)this + 72))(this, v4);  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(void *, HWND))(*(uint32_t *)this + 68))(this, v4);  // 调用虚函数/间接调用
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x4090D0 sub_4090D0
// ------------------------------------------------------------
// 【解读】
//   ★ NEOPLE_WEB 窗口抓屏: GetWindowTextA 比对 "NEOPLE_WEB"（0x652D30 内嵌浏览器窗口）→
//     GetWindowRect/IntersectRect 裁剪 → GetWindowDC/CreateCompatibleDC/BitBlt 拷贝浏览器画面 →
//     GDI 位图供纹理上传（sub_408CF0）。内嵌网页显示到游戏画面的通路。
// ------------------------------------------------------------
int /*userpurge*/ sub_4090D0@<eax>(int pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>, HWND hWnd)
{
  int pArg12; // ebx
  int v5; // eax
  HDC WindowDC; // esi
  HDC CompatibleDC; // edi
  LONG top; // ecx
  int v10; // eax
  LONG right; // ebx
  LONG left; // esi
  int v13; // edx
  int v14; // edi
  LONG v15; // ecx
  int pObj; // eax
  struct tagBITMAPINFO bmi; // [esp+4h] [ebp-12Ch] BYREF
  RECT rcSrc1; // [esp+30h] [ebp-100h] BYREF
  uint32_t v21[2]; // [esp+40h] [ebp-F0h] BYREF
  float v22[2]; // [esp+48h] [ebp-E8h] BYREF
  int v23; // [esp+50h] [ebp-E0h]
  HDC v24; // [esp+54h] [ebp-DCh]
  struct tagRECT rcDst; // [esp+58h] [ebp-D8h] BYREF
  HGDIOBJ h; // [esp+68h] [ebp-C8h]
  int v27; // [esp+6Ch] [ebp-C4h]
  int pArg13; // [esp+70h] [ebp-C0h]
  int v29; // [esp+74h] [ebp-BCh]
  HDC hDC; // [esp+78h] [ebp-B8h]
  struct tagRECT Rect; // [esp+7Ch] [ebp-B4h] BYREF
  struct tagRECT rc; // [esp+8Ch] [ebp-A4h] BYREF
  HBITMAP hbm; // [esp+9Ch] [ebp-94h]
  int nHeight; // [esp+A0h] [ebp-90h]
  int nWidth; // [esp+A4h] [ebp-8Ch]
  char v36; // [esp+ABh] [ebp-85h]
  CHAR String[128]; // [esp+ACh] [ebp-84h] BYREF
  int dword_796E502; // [esp+12Ch] [ebp-4h]

  pArg12 = pArg1;
  dword_796E502 = dword_796E50;  // 栈检 cookie
  v5 = *(uint32_t *)(pArg1 + 184052);
  pArg13 = pArg1;
  if ( v5 == 0 )  // 若 v5 == 0
    return 0x80000000;  // 返回 0x80000000（失败）
  GetWindowRect(hWnd, &Rect);  // 调 GetWindowRect
  if ( Rect.right != Rect.left && Rect.bottom != Rect.top )
  {
    GetWindowRect(*(HWND *)(*(uint32_t *)(pArg12 + 36) + 16), &rcSrc1);  // 调 GetWindowRect
    IntersectRect(&rcDst, &rcSrc1, &Rect);
    nWidth = rcDst.right - rcDst.left;
    nHeight = rcDst.bottom - rcDst.top;
    if ( IntersectRect(&rc, &rcSrc1, &Rect) )
    {
      OffsetRect(&rcDst, -Rect.left, -Rect.top);
      OffsetRect(&rc, -rcSrc1.left, -rcSrc1.top);
      v36 = 0;
      GetWindowTextA(hWnd, String, 128);
      if ( strcmp(String, "NEOPLE_WEB") == 0 )
        v36 = 1;
      WindowDC = GetWindowDC(hWnd);
      hDC = WindowDC;
      CompatibleDC = CreateCompatibleDC(WindowDC);
      v24 = CompatibleDC;
      hbm = CreateBitmap(nWidth, nHeight, 1u, 0x10u, nullptr);
      h = SelectObject(CompatibleDC, hbm);
      if ( v36 == 1 )  // 若 v36 == 1
      {
        SendMessageA(hWnd, 0x317u, (WPARAM)CompatibleDC, 62);  // 调 SendMessageA
      }
      else  // 否则分支
      {
        RedrawWindow(hWnd, nullptr, nullptr, 0x785u);  // 调 RedrawWindow
        BitBlt(CompatibleDC, 0, 0, nWidth, nHeight, WindowDC, rcDst.left, rcDst.top, 0xCC0020u);  // 调 BitBlt
      }
      sub_408CF0(&bmi, hbm);  // 调 sub_408CF0
      if ( GetDIBits(CompatibleDC, hbm, 0, nHeight, *(LPVOID *)(pArg12 + 184056), &bmi, 0) != 0 )
      {
        (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t *, uint32_t, uint32_t, int, int))(**(uint32_t **)(pArg12 + 184052) + 64))(
          *(uint32_t *)(pArg12 + 184052),
          0,
          v21,
          0,
          0,
          nArg2,
          nArg3);
        top = rc.top;
        v27 = *(uint32_t *)(pArg12 + 184056);
        v23 = v21[1];
        v10 = (int)((16 * nWidth + 31) & 0xFFFFFFE0) / 16;
        nWidth = rc.top;
        if ( rc.top < rc.bottom )
        {
          right = rc.right;
          left = rc.left;
          v29 = (int16_t)v10;  // v29 = 截断(v10)
          while ( 1 )  // 当 1 非 0 循环
          {
            v13 = v23 + 2 * top * (v21[0] / 2);
            v14 = v27 + 2 * v29 * (rc.top - top + nHeight - 1);
            v15 = left;
            if ( left < right )
            {
              do  // do 循环体
              {
                *(uint16_t *)(v13 + 2 * v15) = *(uint16_t *)(v14 + 2 * (v15 - left)) & 0x1F
                                          | (2 * (*(uint16_t *)(v14 + 2 * (v15 - left)) & 0xFFE0));
                right = rc.right;
                left = rc.left;
                ++v15;  // v15 自增
              }
              while ( v15 < rc.right );
            }
            if ( ++nWidth >= rc.bottom )
              break;  // 跳出 switch
            top = nWidth;
          }
          CompatibleDC = v24;
          pArg12 = pArg13;
        }
        (*(void (/*cdecl*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg12 + 184052) + 68))(*(uint32_t *)(pArg12 + 184052), 0);  // 调用虚函数/间接调用
      }
      ReleaseDC(hWnd, hDC);  // 调 ReleaseDC
      SelectObject(CompatibleDC, h);  // 调 SelectObject
      DeleteObject(hbm);  // 调 DeleteObject
      DeleteDC(CompatibleDC);  // 调 DeleteDC
      pObj = *(uint32_t *)(pArg12 + 8256);
      v22[0] = (float)rc.left;
      v22[1] = (float)rc.top;
      (*(void (/*stdcall*/ **)(int, uint32_t, struct tagRECT *, uint32_t, uint32_t, uint32_t, float *, int))(*(uint32_t *)pObj + 20))(
        pObj,
        *(uint32_t *)(pArg12 + 184052),
        &rc,
        0,
        0,
        0,
        v22,
        -1);
    }
  }
  return 1;  // 返回 1（成功）
}


// ------------------------------------------------------------
// 0x4094C0 sub_4094C0 —— 每帧呈现（Present）
// 位移参数非 0 → CopyRect/OffsetRect/IntersectRect 后交 vt+60（双矩形）处理；主路径以 NiProfile 槽 2/3/6（·sub_404F40/·sub_404F80）计时包住 vt+136/vt+16/vt+68/vt+28 与 vt+60(0,0,0,0)
// 呈现失败为 0x88760868（D3DERR_DEVICELOST）时经 vt+84 尝试重置设备，成功返 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4094C0(char *this, int nArg2, int dy)  // 函数 每帧呈现（Present）
{
  char fld_e4; // al
  int pThis_80F; // eax
  int v7; // eax
  char v8; // al
  char v9; // al
  int pThis_80F2; // edi
  struct tagRECT rc; // [esp+4h] [ebp-20h] BYREF
  struct tagRECT rcDst; // [esp+14h] [ebp-10h] BYREF

  fld_e4 = *(this + 4);  // fld_e4 = this+4 字段
  if ( fld_e4 == 0 )  // 若 fld_e4 == 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  if ( nArg2 != 0 || dy != 0 )
  {
    CopyRect(&rcDst, (const RECT *)(this + 184024));
    OffsetRect(&rcDst, nArg2, dy);
    IntersectRect(&rc, (const RECT *)(this + 184024), &rcDst);
    IntersectRect(&rcDst, (const RECT *)(this + 184024), &rcDst);
    OffsetRect(&rc, -nArg2, -dy);
    (*(void (/*stdcall*/ **)(uint32_t, struct tagRECT *, struct tagRECT *, uint32_t, uint32_t))(**((uint32_t **)this + 2063) + 60))(
      *((uint32_t *)this + 2063),
      &rc,
      &rcDst,
      0,
      0);
    return 1;  // 返回 1（成功）
  }
  if ( *((uint32_t *)this + 46012) == 1 )
  {
    sub_404F40(fld_e4, 6u);  // 调 sub_404F40
    (*(void (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 2063) + 136))(*((uint32_t *)this + 2063));  // 调用虚函数/间接调用
    (*(void (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 2064) + 16))(*((uint32_t *)this + 2064));  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 68))(this, *(uint32_t *)(*((uint32_t *)this + 9) + 16));  // 调用虚函数/间接调用
    (*(void (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 2064) + 28))(*((uint32_t *)this + 2064));  // 调用虚函数/间接调用
    pThis_80F = (*(int (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 2063) + 140))(*((uint32_t *)this + 2063));
    sub_404F80(pThis_80F, 6u, 1);  // 调 sub_404F80
  }
  v7 = sub_405060(0, 1, 0);  // 调 帧计数累加（uArg1 < 50：pszArg3==1 先清槽，再 += nArg2）
  sub_404F80(v7, 2u, 1);  // 调 sub_404F80
  sub_404F40(v8, 2u);  // 调 sub_404F40
  sub_404F40(v9, 3u);  // 调 sub_404F40
  pThis_80F2 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**((uint32_t **)this + 2063) + 60))(
          *((uint32_t *)this + 2063),
          0,
          0,
          0,
          0);
  sub_404F80(pThis_80F2, 3u, 1);  // 调 sub_404F80
  if ( pThis_80F2 >= 0 )  // 若 pThis_80F2 >= 0
    return 1;  // 返回 1（成功）
  if ( pThis_80F2 == -2005530520 )
    return (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 84))(this) >= 0 ? 1 : -2147483645;
  else  // 否则分支
    return 0x80000000;  // 返回 0x80000000（失败）
}



// ------------------------------------------------------------
// 0x409660 sub_409660 —— 调色/伽马表重算
// uArg2 clamp 到 255，系数 = uArg2 * (1/255)；对 +181468 起三段 256 项 uint16 表（0x600）缩放成 768 字节 RGB888，交 this+8252 vt+72 下发【推断：调色或伽马设置】。
// ------------------------------------------------------------
int /*thiscall*/ sub_409660(int this, unsigned int uArg2)
{
  double fld_20; // st7
  int v4; // esi
  uint16_t *pThis_2C6DC; // edi
  uint64_t v6; // rax
  uint16_t v8[768]; // [esp+Ch] [ebp-604h] BYREF
  int dword_796E502; // [esp+60Ch] [ebp-4h]
  int v10; // [esp+618h] [ebp+8h]
  int v11; // [esp+618h] [ebp+8h]

  dword_796E502 = dword_796E50;  // 栈检 cookie
  *(uint32_t *)(this + 32) = uArg2;  // this+32 = uArg2
  if ( uArg2 >= 0xFF )  // 若 uArg2 >= 0xFF
    *(uint32_t *)(this + 32) = 255;  // this+32（uint32 槽）= 255
  fld_20 = (double)*(unsigned int *)(this + 32) * 0.0039215689;
  v4 = 0;
  pThis_2C6DC = (uint16_t *)(this + 181980);  // pThis_2C6DC = this+181980 指针
  do  // do 循环体
  {
    v10 = *pThis_2C6DC;  // v10 = 解引用 pThis_2C6DC
    v8[v4] = (uint8_t)(uint64_t)((double)*(pThis_2C6DC - 256) * fld_20);
    v6 = (uint64_t)((double)v10 * fld_20);
    v11 = pThis_2C6DC[256];
    v8[v4 + 256] = (uint8_t)v6;
    v8[v4++ + 512] = (uint8_t)(uint64_t)((double)v11 * fld_20);
    ++pThis_2C6DC;
  }
  while ( v4 < 256 );  // 当 v4 < 256 循环
  return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint16_t *))(**(uint32_t **)(this + 8252) + 72))(
           *(uint32_t *)(this + 8252),
           0,
           v8);
}



// ------------------------------------------------------------
// 0x409750 sub_409750 —— 模式切换应用（含设备 Apply）
// 与 ·sub_408FA0 同构（差异：入参为字节标志、全程写 +8284/+8296、不做 +184040 记录）；末先 this+8256 vt+32 再 this+8252 vt+56(this+8276) 应用显示模式。
// ------------------------------------------------------------
int /*thiscall*/ sub_409750(int this, char pszArg2)  // 函数 模式切换应用（含设备 Apply）
{
  int fld_2088; // eax
  int pThis_6418; // ecx
  int pThis_2090; // eax
  int v6; // edi
  int fld_24; // ecx
  LONG WindowLongA; // eax
  int fld_242; // edx
  int result; // eax

  fld_2088 = 17292 * *(uint32_t *)(this + 8328);
  pThis_6418 = *(uint32_t *)(fld_2088 + this + 25624);
  pThis_2090 = fld_2088 + this + 8336;
  v6 = 3240 * pThis_6418 + pThis_2090 + 1088 + 20 * *(uint32_t *)(3240 * pThis_6418 + pThis_2090 + 4316) + 228;
  *(uint8_t *)(this + 13) = pszArg2;
  *(uint32_t *)(this + 8304) = pszArg2 == 0;  // this+8304 = pszArg2 == 0
  if ( pszArg2 != 0 )  // 若 pszArg2 != 0
  {
    fld_24 = *(uint32_t *)(this + 36);
    *(uint32_t *)(this + 8284) = *(uint32_t *)(v6 + 8);  // this+8284 = *(uint32_t *)(v6 + 8)
    *(uint32_t *)(this + 8296) = 2;  // this+8296（uint32 槽）= 2
    WindowLongA = GetWindowLongA(*(HWND *)(fld_24 + 16), -16);
    fld_242 = *(uint32_t *)(this + 36);
    *(uint32_t *)(this + 184040) = WindowLongA;  // this+184040 = WindowLongA
    *(uint32_t *)(this + 184044) = GetWindowLongA(*(HWND *)(fld_242 + 16), -20);  // this+184044 = GetWindowLongA(*(HWND *)(fld_242 + 16), -20)
  }
  else  // 否则分支
  {
    *(uint32_t *)(this + 8284) = *(uint32_t *)(pThis_2090 + 1080);  // this+8284 = *(uint32_t *)(pThis_2090 + 1080)
    *(uint32_t *)(this + 8296) = 1;  // this+8296（uint32 槽）= 1
  }
  result = (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 8256) + 32))(*(uint32_t *)(this + 8256));  // 调用虚函数/间接调用
  if ( result >= 0 )  // 若 result >= 0
  {
    result = (*(int (/*stdcall*/ **)(uint32_t, int))(**(uint32_t **)(this + 8252) + 56))(
               *(uint32_t *)(this + 8252),
               this + 8276);
    if ( result >= 0 )  // 若 result >= 0
      return 1;  // 返回 1（成功）
  }
  return result;
}



// ------------------------------------------------------------
// 0x409830 CompareFunction —— 显示模式三键比较器（qsort 回调）
// 字段 [3] 降序 → [0] 升序 → [1] 降序；被 ·sub_409AE0 的 qsort 使用。
// ------------------------------------------------------------
int /*cdecl*/ CompareFunction(uint32_t *pArg1, uint32_t *pArg2)  // 函数 显示模式三键比较器（qsort 回调）
{
  int v2; // eax
  int v3; // ecx
  unsigned int v5; // eax
  unsigned int v6; // ecx

  v2 = pArg1[3];
  v3 = pArg2[3];
  if ( v2 > v3 )
    return -1;  // 返回错误码 -1
  if ( v2 < v3 )
    return 1;  // 返回 1（成功）
  if ( *pArg1 < *pArg2 )
    return -1;  // 返回错误码 -1
  if ( *pArg1 > *pArg2 )
    return 1;  // 返回 1（成功）
  v5 = pArg1[1];
  v6 = pArg2[1];
  if ( v6 > v5 )
    return -1;  // 返回错误码 -1
  return v6 < v5;
}



// ------------------------------------------------------------
// 0x409870 sub_409870 —— 像素格式/多重采样预设回退链
// 按 this+24 与 this+8272 的阈值依次试探 80 / 73 / 77 / 75 / 79 / 71 六组预设（各经 this+8248 vt+40 与 vt+48），首个可行者写入 *uArg5 并返回 1
// 由 ·sub_409AE0 在适配器/模式枚举中对每项调用（+8268 使能时）。
// ------------------------------------------------------------
char /*thiscall*/ sub_409870(int this, int nArg2, int nArg3, int nArg4, uint32_t *uArg5)  // 函数 像素格式/多重采样预设回退链
{
  if ( *(uint32_t *)(this + 24) <= 0x10u  // 多采样数 <= 16
    && *(uint32_t *)(this + 8272) == 0  // this+8272 为 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(  // 调 D3D vt+40 槽检测多采样 (格式 80)
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         80) >= 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(  // 调 vt+48 槽确认多采样
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         80) >= 0 )
  {
    *uArg5 = 80;  // *uArg5 = 80（采样档 80）
    return 1;  // 返回 1（成功）
  }
  if ( *(uint32_t *)(this + 24) <= 0xFu  // 多采样数 <= 15
    && *(uint32_t *)(this + 8272) <= 1u  // this+8272 <= 1
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(  // 检测多采样 (格式 73)
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         73) >= 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(  // 确认
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         73) >= 0 )
  {
    *uArg5 = 73;
    return 1;  // 返回 1（成功）
  }
  if ( *(uint32_t *)(this + 24) > 0x18u )  // 多采样数 > 24
    goto LABEL_29;  // 跳转 LABEL_29
  if ( *(uint32_t *)(this + 8272) == 0  // this+8272 为 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(  // 检测多采样 (格式 77)
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         77) >= 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(  // 确认
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         77) >= 0 )
  {
    *uArg5 = 77;
    return 1;  // 返回 1（成功）
  }
  if ( *(uint32_t *)(this + 24) > 0x18u )  // 多采样数 > 24
    goto LABEL_29;  // 跳转 LABEL_29
  if ( *(uint32_t *)(this + 8272) <= 8u  // 多采样数 <= 8
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(  // 检测多采样 (格式 75)
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         75) >= 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(  // 确认
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         75) >= 0 )
  {
    *uArg5 = 75;
    return 1;  // 返回 1（成功）
  }
  if ( *(uint32_t *)(this + 24) > 0x18u  // 多采样数 > 24
    || *(uint32_t *)(this + 8272) > 4u  // this+8272 > 4
    || (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(  // 检测多采样 (格式 79)
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         79) < 0
    || (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(  // 确认
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         79) < 0 )
  {
LABEL_29:  // LABEL_29（更低档回退）
    if ( *(uint32_t *)(this + 24) > 0x20u  // 多采样数 > 32
      || *(uint32_t *)(this + 8272) != 0  // this+8272 != 0
      || (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(  // 检测多采样 (格式 71)
           *(uint32_t *)(this + 8248),
           nArg2,
           nArg3,
           nArg4,
           2,
           1,
           71) < 0
      || (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(  // 确认
           *(uint32_t *)(this + 8248),
           nArg2,
           nArg3,
           nArg4,
           nArg4,
           71) < 0 )
    {
      return 0;
    }
    else  // 否则分支
    {
      *uArg5 = 71;
      return 1;  // 返回 1（成功）
    }
  }
  else  // 否则分支
  {
    *uArg5 = 79;
    return 1;  // 返回 1（成功）
  }
}


// ------------------------------------------------------------
// 0x409AA0 sub_409AA0 —— 删除壳（·sub_409AD0 + 低位置位 free）
// 与 ·sub_409AD0 成对的标准删除壳。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_409AA0(uint8_t *Block, char pszArg2)  // 函数 删除壳（·sub_409AD0 + 低位置位 free）
{
  sub_409AD0(Block);  // 调 sub_409AD0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x409AD0 sub_409AD0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_409AD0(uint8_t *this)
{
  return sub_4087A0(this);  // 调 析构（off_6C1F78 → ·sub_408620）
}



// ============================================================
// SECTION 0x409AE0 — D3D8 应用初始化：设备/模式枚举（qsort）、D3DAPPERR 错误分类、REF 设备回退警告
// ============================================================
// ------------------------------------------------------------
// 0x409AE0 sub_409AE0
// ------------------------------------------------------------
// 【解读】
//   D3D 应用设备/模式枚举（387 行）: qsort(sub_409870) 排序显示模式表；
//   D3DAPPERR_NOHARDWAREDEVICE/NOWINDOWEDHAL/NOHALTHISMODE 等错误分类 →
//   MSGWARN_SWITCHEDTOREF 警告（退回 REF 软件渲染时的提示路径）。
// ------------------------------------------------------------
unsigned int /*usercall*/ sub_409AE0@<eax>(int pArg1@<ecx>, uint32_t *uArg2@<edi>)
{
  int *v2; // eax
  int v3; // ecx
  int *v4; // edi
  int v5; // ebx
  int v6; // ecx
  uint32_t *v7; // esi
  int v8; // ecx
  size_t v9; // ebx
  int v10; // edx
  int v11; // eax
  int v12; // edx
  unsigned int *v13; // esi
  unsigned int v14; // edx
  size_t v15; // ecx
  uint32_t *v16; // eax
  unsigned int v17; // ecx
  unsigned int v18; // eax
  unsigned int v19; // ecx
  unsigned int v20; // edi
  int v21; // esi
  int *v22; // ecx
  int v23; // edx
  int v24; // eax
  int v25; // edi
  bool v26; // zf
  int v27; // ebx
  int v28; // edx
  int v29; // eax
  int *v30; // ecx
  int v31; // edx
  int *v32; // ecx
  int v33; // edx
  int *v34; // ecx
  int v35; // edx
  int *v36; // ecx
  int v37; // edx
  int v38; // edx
  size_t j; // edi
  unsigned int k; // ecx
  int v41; // ebx
  unsigned int v42; // edx
  int *v43; // edi
  int *v44; // ecx
  int v45; // eax
  int *v46; // eax
  uint32_t *v47; // eax
  int v48; // edx
  unsigned int v49; // esi
  int *v50; // ecx
  int v51; // eax
  uint32_t *m; // edx
  int v54; // edx
  int v55; // [esp-1Ch] [ebp-7A8h]
  int v56; // [esp-18h] [ebp-7A4h]
  int v57; // [esp-18h] [ebp-7A4h]
  int v58; // [esp-14h] [ebp-7A0h]
  int v59; // [esp-Ch] [ebp-798h]
  int v60; // [esp-Ch] [ebp-798h]
  int v62; // [esp-8h] [ebp-794h]
  int Base; // [esp+4h] [ebp-788h] BYREF
  uint32_t v64[439]; // [esp+8h] [ebp-784h] BYREF
  uint32_t v65[20]; // [esp+6E4h] [ebp-A8h]
  uint32_t v66[2]; // [esp+734h] [ebp-58h]
  uint32_t v67[2]; // [esp+73Ch] [ebp-50h]
  unsigned int v68; // [esp+744h] [ebp-48h]
  unsigned int v69; // [esp+748h] [ebp-44h] BYREF
  unsigned int v70; // [esp+74Ch] [ebp-40h]
  unsigned int v71; // [esp+754h] [ebp-38h]
  size_t v72; // [esp+758h] [ebp-34h]
  int v73; // [esp+75Ch] [ebp-30h]
  unsigned int v74; // [esp+760h] [ebp-2Ch]
  unsigned int i; // [esp+764h] [ebp-28h]
  int v76; // [esp+768h] [ebp-24h]
  char v77; // [esp+76Ch] [ebp-20h]
  char v78; // [esp+76Dh] [ebp-1Fh]
  char v79; // [esp+76Eh] [ebp-1Eh]
  char v80; // [esp+76Fh] [ebp-1Dh]
  char ArgList[4]; // [esp+770h] [ebp-1Ch]
  uint8_t v82[20]; // [esp+774h] [ebp-18h]
  int dword_796E502; // [esp+788h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 栈检 cookie
  v2 = *(int **)(pArg1 + 8248);  // v2 = pArg1+8248 设备管理器
  *(uint32_t *)ArgList = pArg1;
  v3 = *v2;  // v3 = *v2 虚表
  v67[0] = &off_6C2404;
  v67[1] = &off_6C2400;
  v66[0] = 1;
  v66[1] = 2;
  v78 = 0;  // v78 = 0（硬设备可用标志）
  v77 = 0;  // v77 = 0（窗式 HAL 标志）
  v80 = 0;  // v80 = 0（桌面 HAL 标志）
  v79 = 0;  // v79 = 0（HAL 兼容本模式标志）
  v76 = 0;  // v76 = 0（适配器索引）
  if ( (*(int (/*stdcall*/ **)(int *))(v3 + 16))(v2) == 0 )  // 调 vt+16 槽取适配器数；为 0
    goto LABEL_72;  // 跳 LABEL_72
  do  // 逐适配器循环
  {
    v4 = *(int **)ArgList;  // v4 = pArg1 引擎对象
    v5 = v76;  // v5 = v76 适配器索引
    v6 = **(uint32_t **)(*(uint32_t *)ArgList + 8248);  // v6 = 设备管理器虚表
    v56 = *(uint32_t *)(*(uint32_t *)ArgList + 8248);  // v56 = 设备管理器
    v73 = 17292 * *(uint32_t *)(*(uint32_t *)ArgList + 8332) + *(uint32_t *)ArgList + 8336;  // v73 = 适配器记录槽（8336 + idx×17292）
    v7 = (uint32_t *)v73;  // v7 = 记录指针
    (*(void (/*stdcall*/ **)(int, int, uint32_t, int, uint32_t *))(v6 + 20))(v56, v76, 0, v73, uArg2);  // 调 vt+20 槽取适配器信息到 v73
    (*(void (/*stdcall*/ **)(int, int, uint32_t *))(*(uint32_t *)v4[2062] + 32))(v4[2062], v5, v7 + 267);  // 调 v4[2062] vt+32 槽取显示模式计数到 v7+267×4
    v8 = v76;  // v8 = 适配器索引
    v9 = 0;  // v9 = 0（模式计数）
    v7[271] = 0;  // v7[271] 清 0
    v7[4322] = 0;  // v7[4322] 清 0
    v10 = *(uint32_t *)v4[2062];  // v10 = 引擎对象[2062] 虚表
    v59 = v4[2062];  // v59 = 引擎对象[2062]
    v72 = 0;
    v11 = (*(int (/*stdcall*/ **)(int, int))(v10 + 24))(v59, v8);  // 调 vt+24 槽取模式数 v68
    v12 = v7[270];  // v12 = v7[270] 当前模式
    v68 = v11;  // v68 = 模式数
    v65[0] = v12;
    v74 = 1;  // v74 = 1（像素格式数）
    i = 0;
    if ( v11 != 0 )  // 模式数非 0
    {
      v13 = v64;  // v13 = v64 模式表
      do  // 逐模式
      {
        (*(void (/*stdcall*/ **)(int, int, unsigned int, unsigned int *))(*(uint32_t *)v4[2062] + 28))(  // 调 vt+28 槽取第 i 个模式规格到 v69/v70/v71
          v4[2062],
          v76,
          i,
          &v69);
        if ( v69 >= v4[4] && v70 >= v4[5] )  // 模式分辨率 >= 窗口尺寸
        {
          v14 = v71;  // v14 = v71（像素格式）
          v15 = 0;
          if ( v9 != 0 )  // 已有模式记录
          {
            v16 = v64;
            while ( 1 )  // 遍历已有模式查重
            {
              if ( *(v16 - 1) == v69 && *v16 == v70 )  // 宽高相同
              {
                v14 = v71;  // v14 = 像素格式
                if ( v16[2] == v71 )  // 像素格式也相同
                  break;  // 跳出 switch
              }
              ++v15;  // v15 ++
              v16 += 4;  // v16 += 16字节
              if ( v15 >= v9 )  // 遍历完
              {
                v14 = v71;
                break;  // 跳出 switch
              }
            }
          }
          if ( v15 == v9 )  // 未重复（v15 == v9）
          {
            v17 = v70;  // v17 = 高
            *(v13 - 1) = v69;  // 记录宽
            v18 = 0;
            *v13 = v17;  // 记录高
            v19 = v74;
            v13[2] = v14;  // 记录像素格式
            v13[1] = 0;
            ++v9;  // 模式计数 ++
            v13 += 4;  // 记录指针 += 16
            if ( v19 != 0 )  // 像素格式表非空
            {
              do  // 遍历像素格式表查重
              {
                if ( v14 == v65[v18] )  // 格式已存在
                  break;  // 跳出 switch
                ++v18;  // v18 ++
              }
              while ( v18 < v19 );  // 未到末尾
            }
            if ( v18 == v19 )  // 新像素格式（v18 == v19）
            {
              v65[v19] = v14;
              v74 = v19 + 1;
            }
          }
        }
        ++i;  // 模式 i ++
      }
      while ( i < v68 );  // 未到模式数继续
      v72 = v9;  // v72 = v9（去重后模式数）
    }
    qsort(&Base, v9, 0x10u, CompareFunction);  // qsort 按 CompareFunction 排序模式表
    for ( i = 0; i < 8; i += 4 )  // i = 0 到 8（步长 4）
    {
      v20 = i;
      v21 = 3240 * *(uint32_t *)(v73 + 1084) + v73 + 1088;  // v21 = 显示模式子记录槽
      v22 = *(int **)ArgList;  // v22 = 引擎对象
      v62 = 3240 * *(uint32_t *)(v73 + 1084) + v73 + 1092;  // v62 = 子记录偏移
      v23 = v76;  // v23 = 适配器索引
      v60 = *(uint32_t *)((char *)v66 + i);  // v60 = v66[i/4]（设备类型）
      *(uint32_t *)v21 = v60;  // 写设备类型 v51
      (*(void (/*stdcall*/ **)(int, int, int, int))(*(uint32_t *)v22[2062] + 52))(v22[2062], v23, v60, v62);  // 调 vt+52 槽枚举该设备类型的模式
      v24 = *(uint32_t *)((char *)v67 + v20);  // v24 = v67[i/4]（vftable 指针标记）
      v25 = 0;
      *(uint32_t *)(v21 + 216) = v24;  // v21+216 = v24
      v26 = v74 == 0;  // v26 = 像素格式数是否为 0
      *(uint32_t *)(v21 + 224) = 0;  // v21+224 = 0（模式计数）
      *(uint32_t *)(v21 + 3228) = 0;  // v21+3228 清 0
      *(uint8_t *)(v21 + 220) = 0;  // v21+220 清 0
      *(uint8_t *)(v21 + 3232) = 0;  // v21+3232 清 0
      *(uint32_t *)(v21 + 3236) = 0;  // v21+3236 清 0
      if ( !v26 )  // 像素格式数非 0
      {
        while ( 1 )  // 逐像素格式
        {
          v27 = v65[v25];
          v28 = **(uint32_t **)(*(uint32_t *)ArgList + 8248);  // v28 = 设备管理器虚表
          v58 = *(uint32_t *)v21;  // v58 = v21 值
          v57 = v76;  // v57 = 适配器索引
          v55 = *(uint32_t *)(*(uint32_t *)ArgList + 8248);  // v55 = 设备管理器
          v82[v25] = 0;  // v82[v25] 清 0
          v64[v25 + 399] = 0;  // v64[v25+399] 清 0
          if ( (*(int (/*stdcall*/ **)(int, int, int, int, int, uint32_t))(v28 + 36))(v55, v57, v58, v27, v27, 0) >= 0 )  // 调 vt+36 槽检查设备/格式支持
            break;  // 跳出 switch
LABEL_45:  // LABEL_45（下一个格式）
          if ( ++v25 >= v74 )  // 像素格式 ++ 达末尾
            goto LABEL_46;  // 跳 LABEL_46
        }
        if ( *(uint32_t *)v21 == 1 )  // 设备类型 == 1（HAL）
        {
          v26 = (*(uint32_t *)(v21 + 16) & 0x80000) == 0;  // v26 = 能力位 0x80000 是否为 0
          v78 = 1;  // v78 = 1（硬设备可用）
          if ( !v26 )  // 能力位非 0
          {
            v77 = 1;  // v77 = 1（窗式 HAL）
            if ( v25 == 0 )  // 首格式
              v80 = 1;
          }
        }
        v29 = *(uint32_t *)(v21 + 32);  // v29 = v21+32 能力
        if ( (v29 & 0x10000) != 0 )  // 能力位 0x10000
        {
          if ( (v29 & 0x100000) != 0 )  // 能力位 0x100000
          {
            v30 = *(int **)ArgList;  // v30 = 引擎对象
            v31 = **(uint32_t **)ArgList;  // v31 = 引擎虚表
            v64[v25 + 419] = 80;  // v64[v25+419] = 80（深度格式 D16）
            if ( (*(int (/*thiscall*/ **)(int *, int, int, int))(v31 + 88))(v30, v21 + 4, 80, v27) >= 0 )  // 调 vt+88 槽检查深度格式
              v82[v25] = 1;  // 支持：v82[v25] = 1
          }
          if ( v82[v25] != 0 )  // v82[v25] 非 0
            goto LABEL_42;  // 跳 LABEL_42
          v32 = *(int **)ArgList;  // v32 = 引擎对象
          v33 = **(uint32_t **)ArgList;  // v33 = 引擎虚表
          v64[v25 + 419] = 64;  // v64[v25+419] = 64（深度格式 D32）
          if ( (*(int (/*thiscall*/ **)(int *, int, int, int))(v33 + 88))(v32, v21 + 4, 64, v27) >= 0 )  // 调 vt+88 槽检查
            v82[v25] = 1;  // 支持：v82[v25] = 1
          if ( v82[v25] != 0 )  // v82[v25] 非 0
          {
LABEL_42:
            if ( *(uint8_t *)(*(uint32_t *)ArgList + 8268) != 0  // 引擎对象+8268 非 0
              && (uint8_t)sub_409870(v76, *(uint32_t *)v21, v27, &v64[v25 + 399]) == 0 )  // sub_409870 进一步校验
            {
              v82[v25] = 0;
            }
            goto LABEL_45;  // 跳 LABEL_45
          }
          v34 = *(int **)ArgList;  // v34 = 引擎对象
          v35 = **(uint32_t **)ArgList;  // v35 = 引擎虚表
          v64[v25 + 419] = 128;  // v64[v25+419] = 128（深度格式 D24）
          if ( (*(int (/*thiscall*/ **)(int *, int, int, int))(v35 + 88))(v34, v21 + 4, 128, v27) >= 0 )  // 调 vt+88 槽检查
            v82[v25] = 1;  // 支持：v82[v25] = 1
        }
        if ( v82[v25] == 0 )  // v82[v25] 仍为 0
        {
          v36 = *(int **)ArgList;  // v36 = 引擎对象
          v37 = **(uint32_t **)ArgList;  // v37 = 引擎虚表
          v64[v25 + 419] = 32;  // v64[v25+419] = 32（深度格式 D16 备选）
          if ( (*(int (/*thiscall*/ **)(int *, int, int, int))(v37 + 88))(v36, v21 + 4, 32, v27) >= 0 )  // 调 vt+88 槽检查
            v82[v25] = 1;  // 支持：v82[v25] = 1
          if ( v82[v25] == 0 )  // v82[v25] 为 0
            goto LABEL_45;  // 跳 LABEL_45
        }
        goto LABEL_42;  // 跳 LABEL_42
      }
LABEL_46:  // LABEL_46（模式枚举完成）
      if ( v72 != 0 )  // 模式数非 0
      {
        v38 = 0;
        for ( j = v72; j != 0; --j )  // 逐模式 j
        {
          for ( k = 0; k < v74; ++k )  // 逐像素格式 k
          {
            if ( v64[v38 + 2] == v65[k] && v82[k] == 1 )  // 该模式像素格式匹配且可用
            {
              *(uint32_t *)(v21 + 20 * *(uint32_t *)(v21 + 224) + 228) = v64[v38 - 1];  // 写模式宽
              *(uint32_t *)(v21 + 20 * *(uint32_t *)(v21 + 224) + 232) = v64[v38];  // 写模式高
              *(uint32_t *)(v21 + 20 * *(uint32_t *)(v21 + 224) + 236) = v64[v38 + 2];  // 写像素格式
              *(uint32_t *)(v21 + 20 * (*(uint32_t *)(v21 + 224) + 12)) = v64[k + 419];  // 写深度格式
              *(uint32_t *)(v21 + 20 * *(uint32_t *)(v21 + 224) + 244) = v64[k + 399];  // 写 v64[k+399]
              v26 = *(uint32_t *)v21 == 1;  // v26 = 设备类型是否为 1
              ++*(uint32_t *)(v21 + 224);  // 模式计数 ++
              if ( v26 )  // 设备类型 1
                v79 = 1;  // v79 = 1（HAL 兼容本模式）
            }
          }
          v38 += 4;  // v38 += 16字节
        }
      }
      v41 = *(uint32_t *)(v21 + 224);  // v41 = 模式计数
      v42 = 0;
      if ( v41 != 0 )  // 模式数非 0
      {
        v43 = *(int **)ArgList;  // v43 = 引擎对象
        v44 = (int *)(v21 + 236);  // v44 = v21+236（模式表项）
        do  // 逐项
        {
          if ( *(v44 - 2) == v43[4] && *(v44 - 1) == v43[5] )  // 匹配窗口尺寸
          {
            *(uint32_t *)(v21 + 3228) = v42;  // v21+3228 = 模式序号
            v45 = *v44;  // v45 = 像素格式
            if ( *v44 == 23 || v45 == 24 || v45 == 25 )  // 像素格式 23/24/25（窗口兼容格式）
              break;  // 跳出 switch
          }
          ++v42;  // v42 ++
          v44 += 5;  // 项 += 20字节
        }
        while ( v42 < *(uint32_t *)(v21 + 224) );  // 未到末尾继续
      }
      if ( v82[0] != 0 && (*(uint32_t *)(v21 + 16) & 0x80000) != 0 )  // 首格式可用且能力位 0x80000
      {
        *(uint8_t *)(v21 + 220) = 1;  // v21+220 = 1
        *(uint8_t *)(v21 + 3232) = 1;  // v21+3232 = 1
      }
      if ( v41 != 0 )  // 模式数非 0
        ++*(uint32_t *)(v73 + 1084);  // 该适配器模式计数 ++
    }
    v46 = *(int **)ArgList;  // v46 = 引擎对象
    if ( *(uint32_t *)(v73 + 1084) != 0 )  // 适配器有效模式数非 0
      ++*(uint32_t *)(*(uint32_t *)ArgList + 8332);  // 适配器计数 ++
    v47 = (uint32_t *)v46[2062];  // v47 = 引擎对象[2062]
    v48 = *v47;  // v48 = 虚表
    uArg2 = v47;
    v49 = ++v76;
  }
  while ( v49 < (*(int (**)(void))(v48 + 16))() );  // 适配器未遍历完继续
LABEL_72:
  v50 = *(int **)ArgList;  // v50 = 引擎对象
  if ( *(uint32_t *)(*(uint32_t *)ArgList + 8332) == 0 )  // 适配器计数 == 0
    return 0x80000000;  // 返回 0x80000000（失败）
  v51 = 0;
  for ( m = (uint32_t *)(*(uint32_t *)ArgList + 9420); *m == 0; m += 4323 )  // 查找有模式的适配器
  {
    if ( (unsigned int)++v51 >= *(uint32_t *)(*(uint32_t *)ArgList + 8332) )  // 适配器 ++ 达末尾
      return 0x80000000;  // 返回 0x80000000（失败）
  }
  v54 = *(uint32_t *)ArgList + 17292 * v51;  // v54 = 选中适配器记录槽
  *(uint32_t *)(v54 + 25624) = 0;  // v54+25624 清 0
  v50[2082] = v51;  // 引擎对象[2082] = 适配器序号
  if ( *(uint32_t *)(v54 + 9424) == 2 )  // 该适配器设备类型 == 2（REF 软件渲染）
  {
    if ( v78 == 0 )  // 无硬设备
    {
      off_77F3F8((char)v50, "D3DAPPERR_NOHARDWAREDEVICE, MSGWARN_SWITCHEDTOREF");  // 警告 D3DAPPERR_NOHARDWAREDEVICE, MSGWARN_SWITCHEDTOREF
      return 1;  // 返回 1（成功）
    }
    if ( v79 == 0 )  // v79 为 0（HAL 不兼容）
    {
      off_77F3F8((char)v50, "D3DAPPERR_HALNOTCOMPATIBLE, MSGWARN_SWITCHEDTOREF");  // 警告 D3DAPPERR_HALNOTCOMPATIBLE
      return 1;  // 返回 1（成功）
    }
    if ( v77 == 0 )  // v77 为 0（无窗式 HAL）
    {
      off_77F3F8((char)v50, "D3DAPPERR_NOWINDOWEDHAL, MSGWARN_SWITCHEDTOREF");  // 警告 D3DAPPERR_NOWINDOWEDHAL
      return 1;  // 返回 1（成功）
    }
    if ( v80 == 0 )  // v80 为 0（无桌面 HAL）
    {
      off_77F3F8((char)v50, "D3DAPPERR_NODESKTOPHAL, MSGWARN_SWITCHEDTOREF");  // 警告 D3DAPPERR_NODESKTOPHAL
      return 1;  // 返回 1（成功）
    }
    off_77F3F8((char)v50, "D3DAPPERR_NOHALTHISMODE, MSGWARN_SWITCHEDTOREF");  // 警告 D3DAPPERR_NOHALTHISMODE
  }
  return 1;  // 返回 1（成功）
}


// ------------------------------------------------------------
// 0x40A130 sub_40A130
// ------------------------------------------------------------
// 【解读】
//   Direct3DCreate8 初始化（158 行）: 设备枚举 + 模式选择 + SetWindowPos 应用。
// ------------------------------------------------------------
int /*thiscall*/ sub_40A130(char *this)
{
  int pD3D; // eax
  int result; // eax
  int pThis_822; // eax
  int v5; // edi
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  uint32_t *v9; // eax
  int pThis_9; // edx
  char fld_e13; // cl
  int pThis_4; // ecx
  int pThis_5; // edx
  int v14; // ebx
  int v15; // edi
  uint32_t *v16; // edi
  int pThis_80F; // eax
  int v18; // ecx
  char *pThis_2C6DC; // edx
  int16_t v20; // ax
  int16_t v21; // ax
  uint32_t *Block; // [esp+4h] [ebp-14h]
  uint32_t *pThis_2CADC; // [esp+8h] [ebp-10h]

  pD3D = Direct3DCreate8(220);  // Direct3DCreate8(220) 创建设备接口
  *((uint32_t *)this + 2062) = pD3D;  // this 偏移 8248 = pD3D
  if ( pD3D == 0 )  // 创建失败
    return 0x80000000;  // 返回 0x80000000（失败）
  SetRect((LPRECT)(this + 184024), 0, 0, *((uint32_t *)this + 4), *((uint32_t *)this + 5));  // SetRect 显示区 = (0,0,宽,高)
  sub_409AE0(this);  // 【D3D8 应用初始化：设备/模式枚举（qsort）、D3DAPPERR 错误分类、R…】
  pThis_822 = 17292 * *((uint32_t *)this + 2082);  // pThis_822 = 17292×选中适配器序号
  v5 = (int)(this + pThis_822 + 8336);  // v5 = 适配器记录基址
  v6 = 3240 * *(uint32_t *)(this + pThis_822 + 25624);  // v6 = 3240×选中设备序号
  v7 = *(uint32_t *)(v6 + v5 + 4316);  // v7 = 当前模式序号
  v8 = v6 + v5 + 1088;  // v8 = 模式表基址
  v9 = (uint32_t *)(v8 + 20 * v7 + 228);  // v9 = 模式表项地址
  Block = (uint32_t *)v5;  // Block = 适配器记录
  if ( v9 == nullptr )  // 模式表空
    return 0x80000000;  // 返回 0x80000000（失败）
  *((uint32_t *)this + 2077) = (uint8_t)*(this + 8268);  // this 偏移 8308 = (uint8_t)*(this + 8268)
  *((uint32_t *)this + 2078) = v9[4];  // this 偏移 8312 = v9[4]
  pThis_9 = *((uint32_t *)this + 9);  // pThis_9 = this 偏移 9
  *((uint32_t *)this + 2073) = *(uint32_t *)(v8 + 3236);  // this 偏移 8292 = *(uint32_t *)(v8 + 3236)
  *((uint32_t *)this + 2075) = *(uint32_t *)(pThis_9 + 16);  // this 偏移 8300 = *(uint32_t *)(pThis_9 + 16)
  fld_e13 = *(this + 13);  // fld_e13 = this+13 字段
  *((uint32_t *)this + 2076) = fld_e13 == 0;  // this 偏移 8304 = fld_e13 == 0
  if ( fld_e13 != 0 )  // 全屏
  {
    *((uint32_t *)this + 2072) = 1;  // this 偏移 8288 = 1
    *((uint32_t *)this + 2069) = *v9;  // this 偏移 8276 = *v9
    *((uint32_t *)this + 2070) = v9[1];  // this 偏移 8280 = v9[1]
    *((uint32_t *)this + 2071) = v9[2];  // this 偏移 8284 = v9[2]
    *((uint32_t *)this + 2074) = 2;  // this 偏移 8296 = 2
  }
  else  // 窗口态
  {
    pThis_4 = *((uint32_t *)this + 4);  // pThis_4 = this 偏移 4
    pThis_5 = *((uint32_t *)this + 5);  // pThis_5 = this 偏移 5
    *((uint32_t *)this + 2072) = 1;  // this 偏移 8288 = 1
    *((uint32_t *)this + 2069) = pThis_4;  // this 偏移 8276 = pThis_4
    *((uint32_t *)this + 2070) = pThis_5;  // this 偏移 8280 = pThis_5
    *((uint32_t *)this + 2071) = *(uint32_t *)(v5 + 1080);  // this 偏移 8284 = *(uint32_t *)(v5 + 1080)
    *((uint32_t *)this + 2074) = 1;  // this 偏移 8296 = 1
  }
  v14 = 0;
  while ( 1 )  // 尝试创建设备
  {
    result = (*(int (/*stdcall*/ **)(uint32_t, int, int, uint32_t, int, char *, char *))(**((uint32_t **)this + 2062) + 60))(  // 调 D3D vt+60 槽 CreateDevice
               *((uint32_t *)this + 2062),
               v14,
               1,
               *(uint32_t *)(*((uint32_t *)this + 9) + 16),
               32,
               this + 8276,
               this + 8252);
    if ( result >= 0 )  // 成功跳出
      break;  // 跳出 switch
    if ( ++v14 >= 2 )  // 尝试 ++ 达 2 次
      return result;
  }
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 22, 1);  // 调 this 虚表 +28 槽 (this, 22, 1)
  (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 28))(this, 137, 0);  // 设状态 137=0
  (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 28))(this, 7, (uint8_t)*(this + 8268));  // 设状态 7=配置位
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 27, 1);  // 调 this 虚表 +28 槽 (this, 27, 1)
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 15, 1);  // 调 this 虚表 +28 槽 (this, 15, 1)
  (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 28))(this, 24, 0);  // 设状态 24=0
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 25, 5);  // 调 this 虚表 +28 槽 (this, 25, 5)
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 19, 5);  // 调 this 虚表 +28 槽 (this, 19, 5)
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 20, 6);  // 调 this 虚表 +28 槽 (this, 20, 6)
  (*(void (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 36))(this, 0, 1, 4);  // 调 this vt+36 槽 设纹理采样状态 (0,1,4)
  (*(void (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 36))(this, 0, 13, 3);  // 设纹理采样状态 (0,13,3)
  (*(void (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 36))(this, 0, 14, 3);  // 设纹理采样状态 (0,14,3)
  (*(void (/*stdcall*/ **)(uint32_t, char *))(**((uint32_t **)this + 2063) + 28))(*((uint32_t *)this + 2063), this + 181256);  // 调设备对象 this[2063] vt+28 槽（资源管理）
  v15 = 0;
  pThis_2CADC = this + 183004;  // pThis_2CADC = this+183004（格式可用表）
  do  // 遍历 255 格式
  {
    if ( (*(int (/*stdcall*/ **)(uint32_t, int, int, uint32_t, int, int, int))(**((uint32_t **)this + 2062) + 40))(  // 调 D3D vt+40 槽检测格式支持
           *((uint32_t *)this + 2062),
           v14,
           1,
           Block[270],
           1,
           3,
           v15) >= 0 )
      *pThis_2CADC = 1;  // 支持置 1
    ++v15;  // v15 自增
    ++pThis_2CADC;  // 表指针 ++
  }
  while ( v15 < 255 );  // 255 格式遍历完
  result = sub_67BA58(*((uint32_t *)this + 2063), this + 8256);  // sub_67BA58 初始化设备对象
  if ( result >= 0 )  // 成功
  {
    if ( operator new(0x88u) != nullptr )  // new 0x88 分配容器
      v16 = (uint32_t *)sub_4143A0(7, this);  // 【对象销毁/容器壳】
    else  // 否则分支
      v16 = nullptr;  // v16 = 空指针
    if ( v16 != nullptr )  // 构造成功
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v16 + 176))(v16, *((uint32_t *)this + 2063));  // 调 vt+176 槽绑定设备对象
      v16[33] = *((uint32_t *)this + 9);  // v16[33] = this[9] 窗口对象
      pThis_80F = *((uint32_t *)this + 2063);  // pThis_80F = this 偏移 2063
      *((uint32_t *)this + 2065) = v16;  // this 偏移 8260 = v16
      (*(void (/*stdcall*/ **)(int, char *))(*(uint32_t *)pThis_80F + 76))(pThis_80F, this + 181468);  // 调设备对象 vt+76 槽
      if ( *((uint16_t *)this + 90989) == 255 )  // this 偏移 181978（uint16）== 255
      {
        v18 = 0;
        pThis_2C6DC = this + 181980;  // pThis_2C6DC = this+181980 调色板
        do  // 填 256 色调色板
        {
          LOBYTE(v20) = 0;  // v20 低位 = 0
          HIBYTE(v20) = v18;  // v20 高位 = v18
          pThis_2C6DC += 2;  // pThis_2C6DC 前进 2
          v21 = v18 | v20;
          *((uint16_t *)pThis_2C6DC - 257) = v21;  // 写调色板项
          *((uint16_t *)pThis_2C6DC - 1) = v21;  // 写副本
          *((uint16_t *)pThis_2C6DC + 255) = v21;  // 写第三副本
          ++v18;  // v18 自增
        }
        while ( v18 < 256 );  // 256 项完成
      }
      if ( *(this + 13) != 0 )  // 全屏标志非 0
        SetWindowPos(*(HWND *)(*((uint32_t *)this + 9) + 16), HWND_MESSAGE|0x2, 0, 0, 0, 0, 3u);  // 调 SetWindowPos
      return 1;  // 返回 1（成功）
    }
    else  // 否则分支
    {
      return -2147483640;  // 返回 0x80000008（内存不足）
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x40A4E0 sub_40A4E0 —— 链表尾插（this+4 哨兵环）
// ·sub_40C0F0 建节点 → ·sub_407D70 计数与溢出检查（list<T> too long）→ 挂链；与 ·sub_408180 同构（差异：链表位于 this+4、抛出器为 ·sub_407D70）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40A4E0(uint32_t *this, int nArg2)  // 函数 链表尾插（this+4 哨兵环）
{
  int fld_e1; // edi
  int v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), nArg2);  // v4 = sub_40C0F0(...)
  result = sub_407D70(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;  // fld_e1+4 = v4
  **(uint32_t **)(v4 + 4) = v4;  // v4 偏移 4 指向自身（自环）
  return result;
}



// ------------------------------------------------------------
// 0x40A520 sub_40A520 —— 渲染资源工厂（按接口类型分派）
// 1/8/16 → 0x88 ·sub_408570（或 +183088 非 0 时 ·sub_4086A0 且 +136=1）；3 → 0x70 ·sub_4089B0；7 → 取 +8260；12/13 → 0x8C ·sub_408A90(类型 14)；14 → ·sub_408770；15 → ·sub_4086A0；18/19/20 → 仅登记；
// 成功者经 ·sub_40A4E0 挂入 +40 链；+4 未就绪返 0x80000001，分配失败 0x80000008，类型未知 0x80000009。
// ------------------------------------------------------------
int /*thiscall*/ sub_40A520(int this, int nArg2, uint32_t *Block)  // 函数 渲染资源工厂（按接口类型分派）
{
  int result; // eax
  uint8_t *pMem; // eax
  uint8_t *fld_203C; // eax
  uint8_t *pMem2; // eax
  uint8_t *pMem5; // eax
  uint8_t *pMem6; // eax
  void *pMem3; // eax
  uint8_t *pMem4; // eax
  uint8_t *fld_203C2; // eax

  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  switch ( nArg2 )
  {
    case 1:  // case 分支 1
    case 8:  // case 分支 8
    case 16:  // case 分支 16
      if ( *(uint32_t *)(this + 183088) != 0 )  // 若 this 偏移 183088 非 0
      {
        pMem = operator new(0x88u);
        if ( pMem != nullptr )  // 若 pMem 非空
          fld_203C = sub_408570(pMem, nArg2, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));  // 调 派生构造（off_6C1D50）
        else  // 否则分支
          fld_203C = nullptr;  // fld_203C = 空指针
      }
      else  // 否则分支
      {
        pMem2 = operator new(0x8Cu);
        if ( pMem2 != nullptr )  // 若 pMem2 非空
          fld_203C = sub_4086A0(pMem2, nArg2, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));  // 调 派生构造（off_6C1EC0，+136 标志清零）
        else  // 否则分支
          fld_203C = nullptr;  // fld_203C = 空指针
        fld_203C[136] = 1;
      }
      if ( fld_203C != nullptr )  // 若 fld_203C 非空
        goto LABEL_14;  // 跳转 LABEL_14
      return -2147483640;  // 返回 0x80000008（内存不足）
    case 3:  // case 分支 3
      pMem3 = operator new(0x70u);
      if ( pMem3 != nullptr )  // 若 pMem3 非空
        fld_203C = (uint8_t *)sub_4089B0((int)pMem3, nArg2, *(uint32_t *)(this + 8252));  // 调 派生构造（off_6C2190，+108 = nArg3）
      else  // 否则分支
        fld_203C = nullptr;  // fld_203C = 空指针
      goto LABEL_22;  // 跳转 LABEL_22
    case 7:  // case 分支 7
      *Block = *(uint32_t *)(this + 8260);
      return 1;  // 返回 1（成功）
    case 12:  // case 分支 12
    case 13:  // case 分支 13
      pMem4 = operator new(0x8Cu);
      if ( pMem4 != nullptr )  // 若 pMem4 非空
        fld_203C2 = sub_408A90(pMem4, 14, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));  // 调 派生构造（off_6C2240，+136 标志清零）
      else  // 否则分支
        fld_203C2 = nullptr;  // fld_203C2 = 空指针
      *Block = fld_203C2;  // 写指针 = fld_203C2
      if ( fld_203C2 != nullptr )  // 若 fld_203C2 非空
        goto LABEL_29;  // 跳转 LABEL_29
      goto LABEL_23;  // 跳转 LABEL_23
    case 14:  // case 分支 14
      pMem5 = operator new(0x8Cu);
      if ( pMem5 != nullptr )  // 若 pMem5 非空
        fld_203C = sub_408770(pMem5, nArg2, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));  // 调 派生构造（off_6C1F78，+136 标志清零）
      else  // 否则分支
        fld_203C = nullptr;  // fld_203C = 空指针
      goto LABEL_22;  // 跳转 LABEL_22
    case 15:  // case 分支 15
      pMem6 = operator new(0x8Cu);
      if ( pMem6 != nullptr )  // 若 pMem6 非空
        fld_203C = sub_4086A0(pMem6, nArg2, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));  // 调 派生构造（off_6C1EC0，+136 标志清零）
      else  // 否则分支
        fld_203C = nullptr;  // fld_203C = 空指针
LABEL_22:  // LABEL_22（跳转目标）
      if ( fld_203C != nullptr )  // 若 fld_203C 非空
      {
LABEL_14:  // LABEL_14（跳转目标）
        *Block = fld_203C;  // 写指针 = fld_203C
        sub_40A4E0((uint32_t *)(this + 40), (int)Block);  // 调 sub_40A4E0
        result = 1;
      }
      else  // 否则分支
      {
LABEL_23:  // LABEL_23（跳转目标）
        result = -2147483640;
      }
      break;  // 跳出 switch
    case 18:  // case 分支 18
    case 19:  // case 分支 19
    case 20:  // case 分支 20
LABEL_29:  // LABEL_29（跳转目标）
      sub_40A4E0((uint32_t *)(this + 40), (int)Block);  // 调 sub_40A4E0
      result = 1;
      break;  // 跳出 switch
    default:  // 默认分支
      *Block = 0;
      result = -2147483639;
      break;  // 跳出 switch
  }
  return result;
}



// ============================================================
// SECTION 0x40A800 — DirectSound8 声音子系统（DirectSoundCreate8 / 协作级 / 缓冲管理）
// ============================================================
// ------------------------------------------------------------
// 0x40A800 sub_40A800 —— 声音对象基类构造（off_6C2408）
// 字节 +4=0、this[2]=pArg2、this[11]=nArg3；this+24 处内嵌字符串包（off_6C38F4）经 ·sub_402A50 初始化，末 ·sub_4144F0 状态清零。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40A800(uint8_t *this, void *pArg2, int nArg3)  // 【DirectSound8 声音子系统（DirectSoundCreate8 / 协作…】
{
  *(this + 4) = 0;  // this+4 清 0
  *((uint32_t *)this + 2) = pArg2;  // this 偏移 8 = pArg2
  *(uint32_t *)this = &off_6C2408;  // vftable = off_6C2408
  *(this + 28) = 0;  // this+28 清 0
  *((uint32_t *)this + 6) = &off_6C38F4;  // this 偏移 24 = 接口/vftable off_6C38F4
  sub_402A50((uint32_t *)this + 6);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  *((uint32_t *)this + 11) = nArg3;  // this 偏移 44 = 参数3
  sub_4144F0(this);  // 调 sub_4144F0
  return this;
}



// ------------------------------------------------------------
// 0x40A870 sub_40A870 —— 声音对象基类析构（off_6C2408 → IObject::vftable）
// ·sub_414510 释放 +48 日志接口容器，+24 串包经 ·sub_402A60 释放；+28 与 +4 清零。
// ------------------------------------------------------------
char /*thiscall*/ sub_40A870(uint32_t *this)  // 函数 声音对象基类析构（off_6C2408 → IObject::vftable）
{
  *this = &off_6C2408;  // vftable = off_6C2408
  sub_414510();  // 调 sub_414510
  *(this + 6) = &off_6C38F4;
  sub_402A60((int)(this + 6));  // 调 sub_402A60
  *(this + 6) = &nengine::IObject::`vftable';  // this 偏移 6 = IObject vftable
  *((uint8_t *)this + 28) = 0;  // this 偏移 28 字节 = 0
  *this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x40A8E0 sub_40A8E0 —— 存根：出参置 0，恒返 0x80000000（该能力未支持）
// 被声音对象虚表引用，不实现实际语义。
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_40A8E0(uint32_t *uArg1)
{
  *uArg1 = 0;  // 写指针 = 0
  return 0x80000000;  // 返回 0x80000000（失败）
}



// ------------------------------------------------------------
// 0x40A900 sub_40A900 —— 删除壳（·sub_40A870 + 低位置位 free）
// 与 ·sub_40A870 成对的标准删除壳。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40A900(uint32_t *Block, char pszArg2)  // 函数 删除壳（·sub_40A870 + 低位置位 free）
{
  sub_40A870(Block);  // 调 sub_40A870
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40A930 sub_40A930 —— 缓冲对象构造（off_6C243C，+64 = nArg4 设备接口）
// ·sub_40A800 基构造后写 this[16]=nArg4 并改挂 off_6C243C，末 ·sub_414560 清 +52/+56/+60；0x44 对象 —— ·0x40AA20 与 ·0x40ABC0 经 new 装配。
// ------------------------------------------------------------
int /*thiscall*/ sub_40A930(int this, void *pArg2, int nArg3, int nArg4)  // 函数 缓冲对象构造（off_6C243C，+64 = nArg4 设备接口）
{
  sub_40A800((uint8_t *)this, pArg2, nArg3);  // 【DirectSound8 声音子系统（DirectSoundCreate8 / 协作…】
  *(uint32_t *)this = &off_6C243C;  // vftable = off_6C243C
  *(uint32_t *)(this + 64) = nArg4;  // this+64 = 参数4
  sub_414560(this);  // 调 sub_414560
  return this;
}



// ------------------------------------------------------------
// 0x40A990 sub_40A990 —— 删除壳（·sub_40A9C0 + 低位置位 free）
// 与 ·sub_40A9C0 成对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_40A990(void *Block, char pszArg2)  // 函数 删除壳（·sub_40A9C0 + 低位置位 free）
{
  sub_40A9C0();  // 调 sub_40A9C0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40A9C0 sub_40A9C0 —— 析构（off_6C243C → ·sub_4145E0 声音槽位表释放 → ·sub_40A870）
// 经 ·sub_4145E0 逐槽释放后回收槽表，再走基类析构。
// ------------------------------------------------------------
char /*thiscall*/ sub_40A9C0(uint32_t *this)  // 函数 析构（off_6C243C → ·sub_4145E0 声音槽位表释放 → ·sub_40A870）
{
  *this = &off_6C243C;  // vftable = off_6C243C
  sub_4145E0();  // 调 sub_4145E0
  return sub_40A870(this);  // 调 声音对象基类析构（off_6C2408 → IObject::vftable）
}



// ------------------------------------------------------------
// 0x40AA10 sub_40AA10 —— 状态初始化（+8=1，+60/+64 清零）
// 被 ·0x406360（事件分发对象构造 F，挂 off_6C1A44）调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_40AA10(uint32_t *this)  // 函数 状态初始化（+8=1，+60/+64 清零）
{
  *(this + 2) = 1;  // this+2 = 1
  *(this + 15) = 0;  // this+15 清 0
  *(this + 16) = 0;  // this+16 清 0
  return 0;
}



// ------------------------------------------------------------
// 0x40AA20 sub_40AA20
// ------------------------------------------------------------
// 【解读】
//   DirectSoundCreate8 + SetCooperativeLevel —— 声音子系统构造（缓冲对象 sub_40A930 族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40AA20(
        LPDIRECTSOUND8 *this,
        struct IDirectSound8 *Block,
        struct IDirectSound8 *a3,
        struct IDirectSound8 *a4)
{
  LPDIRECTSOUND8 *v5; // edi
  void *v7; // eax
  int v8; // edi
  int v9; // ebx
  int v10; // edi

  v5 = this + 15;
  if ( *(this + 15) != nullptr )
    return -2147483646;  // 返回 0x80000002（已初始化）
  *(this + 4) = Block;
  *(this + 5) = a3;
  *(this + 6) = a4;
  if ( DirectSoundCreate8(nullptr, v5, nullptr) < 0 )
    return -2147483616;  // 返回错误码 -2147483616
  if ( (*v5)->lpVtbl->SetCooperativeLevel(*v5, (HWND)(*(this + 8))[4].lpVtbl, 1) < 0 )
    return -2147483631;  // 返回错误码 -2147483631
  v7 = operator new(0x44u);
  if ( v7 != nullptr )  // 若 v7 非空
    v8 = sub_40A930((int)v7, nullptr, (int)this, (int)*v5);  // 调 缓冲对象构造（off_6C243C，+64 = nArg4 设备接口）
  else  // 否则分支
    v8 = 0;
  *(this + 16) = (LPDIRECTSOUND8)v8;
  v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  if ( v9 >= 0 )  // 若 v9 >= 0
  {
    v10 = sub_414850(0, 0, 129);  // 调 声音缓冲创建（描述结构 → vt+12）
    if ( v10 >= 0 )  // 若 v10 >= 0
    {
      return 1;  // 返回 1（成功）
    }
    else  // 否则分支
    {
      sub_408050(this);  // 调 sub_408050
      return v10;
    }
  }
  else  // 否则分支
  {
    sub_408050(this);  // 调 sub_408050
    return v9;
  }
}



// ------------------------------------------------------------
// 0x40AB70 sub_40AB70 —— 设备初始化转发
// ·sub_40AA20(this, this+16, this+20, this+24) 重入；成功返回 1，失败原样返回错误码。
// ------------------------------------------------------------
int /*thiscall*/ sub_40AB70(LPDIRECTSOUND8 *this)
{
  int result; // eax

  result = sub_40AA20(this, *(this + 4), *(this + 5), *(this + 6));
  if ( result >= 0 )  // 若 result >= 0
    return 1;  // 返回 1（成功）
  return result;
}



// ------------------------------------------------------------
// 0x40AB90 sub_40AB90 —— 设备与缓冲释放
// this+64 对象经 (**fld)(fld,1) 自释放；this+60 接口 vt+8 释放，双字段清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_40AB90(int *this)
{
  void (/*thiscall*/ ***fld_e16)(uint32_t, int); // ecx
  int result; // eax

  fld_e16 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  if ( fld_e16 != nullptr )  // 若 fld_e16 非空
    (**fld_e16)(fld_e16, 1);
  result = *(this + 15);  // result = this+15
  *(this + 16) = 0;  // this+16 清 0
  if ( result != 0 )  // 若 result != 0
    result = (*(int (/*stdcall*/ **)(int))(*(uint32_t *)result + 8))(result);  // 调用虚函数/间接调用
  *(this + 15) = 0;  // this+15 清 0
  return result;
}



// ------------------------------------------------------------
// 0x40ABC0 sub_40ABC0 —— 缓冲工厂（nArg2 必须为 0）
// new(0x44) → ·sub_40A930(空, this, this+60) → 出参并挂入 +36 链（·sub_40C0F0 建节点 + ·sub_4080F0 计数）；nArg2 非 0 返 0x80000009，分配失败 0x80000008。
// ------------------------------------------------------------
int /*thiscall*/ sub_40ABC0(int *this, int nArg2, int *pDwArg3)  // 函数 缓冲工厂（nArg2 必须为 0）
{
  void *pMem; // eax
  int fld_e15; // eax
  int fld_e10; // edi
  int v8; // ebx

  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    *pDwArg3 = 0;  // 写指针 = 0
    return -2147483639;  // 返回 0x80000009（类型错）
  }
  else  // 否则分支
  {
    pMem = operator new(0x44u);
    if ( pMem != nullptr )  // 若 pMem 非空
      fld_e15 = sub_40A930((int)pMem, nullptr, (int)this, *(this + 15));  // 调 缓冲对象构造（off_6C243C，+64 = nArg4 设备接口）
    else  // 否则分支
      fld_e15 = 0;
    *pDwArg3 = fld_e15;  // 写指针 = fld_e15
    if ( fld_e15 != 0 )  // 若 fld_e15 != 0
    {
      fld_e10 = *(this + 10);  // fld_e10 = this+10 字段
      v8 = sub_40C0F0(fld_e10, *(uint32_t *)(fld_e10 + 4), pDwArg3);  // v8 = sub_40C0F0(...)
      sub_4080F0(this + 9, 1u);  // 调 sub_4080F0
      *(uint32_t *)(fld_e10 + 4) = v8;  // fld_e10+4 = v8
      **(uint32_t **)(v8 + 4) = v8;  // v8 偏移 4 指向自身（自环）
      return 1;  // 返回 1（成功）
    }
    else  // 否则分支
    {
      return -2147483640;  // 返回 0x80000008（内存不足）
    }
  }
}



// ------------------------------------------------------------
// 0x40ACA0 sub_40ACA0 —— 3D 缓冲对象构造（off_6C2470）
// ·sub_40A800 基构造后改挂 off_6C2470，末 ·sub_414D40 清 +52..+68 五接口字段；0x48 对象 —— ·0x40AE90 类型 0..3 经此创建。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40ACA0(uint8_t *this, void *pArg2, int nArg3)  // 函数 3D 缓冲对象构造（off_6C2470）
{
  sub_40A800(this, pArg2, nArg3);  // 【DirectSound8 声音子系统（DirectSoundCreate8 / 协作…】
  *(uint32_t *)this = &off_6C2470;  // vftable = off_6C2470
  sub_414D40(this);  // 调 sub_414D40
  return this;
}



// ------------------------------------------------------------
// 0x40AD00 sub_40AD00 —— 析构（off_6C2470 → ·sub_414E00 释放五 COM 接口 → ·sub_40A870）
// 接口按 +68/+60/+64/+56/+52 顺序 Release。
// ------------------------------------------------------------
char /*thiscall*/ sub_40AD00(uint32_t *this)  // 函数 析构（off_6C2470 → ·sub_414E00 释放五 COM 接口 → ·sub_40A870）
{
  *this = &off_6C2470;  // vftable = off_6C2470
  sub_414E00();  // 调 sub_414E00
  return sub_40A870(this);  // 调 声音对象基类析构（off_6C2408 → IObject::vftable）
}



// ------------------------------------------------------------
// 0x40AD50 sub_40AD50 —— 参数换算：this+16 / 100 + 100
// 【推断：采样率或延迟参数换算为时长值】。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_40AD50(uint32_t *this)  // 函数 参数换算：this+16 / 100 + 100
{
  return *(this + 4) / 0x64u + 100;
}



// ------------------------------------------------------------
// 0x40AD70 sub_40AD70 —— 删除壳（·sub_40AD00 + 低位置位 free）
// 与 ·sub_40AD00 成对的标准删除壳。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40AD70(uint32_t *Block, char pszArg2)  // 函数 删除壳（·sub_40AD00 + 低位置位 free）
{
  sub_40AD00(Block);  // 调 sub_40AD00
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40ADA0 sub_40ADA0 —— 3D 缓冲变体构造（off_6C24A4）
// ·sub_40ACA0 构造后改挂 off_6C24A4 并再过一次 ·sub_414D40；·0x40AE90 类型 5 经此创建。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40ADA0(uint8_t *this, void *pArg2, int nArg3)  // 函数 3D 缓冲变体构造（off_6C24A4）
{
  sub_40ACA0(this, pArg2, nArg3);  // 调 sub_40ACA0
  *(uint32_t *)this = &off_6C24A4;  // vftable = off_6C24A4
  sub_414D40(this);  // 调 sub_414D40
  return this;
}



// ------------------------------------------------------------
// 0x40AE00 sub_40AE00 —— 删除壳（·sub_40AE30 + 低位置位 free）
// 与 ·sub_40AE30 成对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_40AE00(void *Block, char pszArg2)  // 函数 删除壳（·sub_40AE30 + 低位置位 free）
{
  sub_40AE30();  // 调 sub_40AE30
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40AE30 sub_40AE30 —— 析构（off_6C24A4 → ·sub_414E00 五接口释放 → ·sub_40AD00）
// 与 ·sub_40AD00 同族（差异：虚表常量）。
// ------------------------------------------------------------
char /*thiscall*/ sub_40AE30(uint32_t *this)  // 函数 析构（off_6C24A4 → ·sub_414E00 五接口释放 → ·sub_40AD00）
{
  *this = &off_6C24A4;  // vftable = off_6C24A4
  sub_414E00();  // 调 sub_414E00
  return sub_40AD00(this);  // 调 析构（off_6C2470 → ·sub_414E00 释放五 COM 接口 → ·sub_40A870）
}



// ------------------------------------------------------------
// 0x40AE90 sub_40AE90 —— 3D 缓冲工厂（类型 0..3 与 5）
// 0..3 → 0x48 ·sub_40ACA0；5 → ·sub_40ADA0；成功经 ·sub_408180 挂入 +36 链；分配失败 0x80000008，类型未知 0x80000009。
// ------------------------------------------------------------
int /*thiscall*/ sub_40AE90(uint32_t *this, int nArg2, uint32_t *Block)  // 函数 3D 缓冲工厂（类型 0..3 与 5）
{
  uint32_t *Block2; // edi
  uint8_t *pMem2; // eax
  uint8_t *v6; // eax
  uint8_t *pMem; // eax

  if ( nArg2 >= 0 )  // 若 nArg2 >= 0
  {
    if ( nArg2 <= 3 )
    {
      Block2 = Block;
      *Block = 0;
      pMem = operator new(0x48u);
      if ( pMem != nullptr )  // 若 pMem 非空
        v6 = sub_40ACA0(pMem, (void *)nArg2, (int)this);  // 调 3D 缓冲对象构造（off_6C2470）
      else  // 否则分支
        v6 = nullptr;  // v6 = 空指针
      goto LABEL_9;  // 跳转 LABEL_9
    }
    if ( nArg2 == 5 )  // 若 nArg2 == 5
    {
      Block2 = Block;
      *Block = 0;
      pMem2 = operator new(0x48u);
      if ( pMem2 != nullptr )  // 若 pMem2 非空
        v6 = sub_40ADA0(pMem2, (void *)5, (int)this);  // 调 3D 缓冲变体构造（off_6C24A4）
      else  // 否则分支
        v6 = nullptr;  // v6 = 空指针
LABEL_9:  // LABEL_9（跳转目标）
      if ( v6 == nullptr )  // 若 v6 为空
        return -2147483640;  // 返回 0x80000008（内存不足）
      *Block2 = v6;  // 写指针 = v6
      sub_408180(this + 9, (int)Block2);  // 调 sub_408180
      return 1;  // 返回 1（成功）
    }
  }
  *Block = 0;
  return -2147483639;  // 返回 0x80000009（类型错）
}



// ------------------------------------------------------------
// 0x40AF90 sub_40AF90 —— 槽状态读取（非零返回）
// this+12 非 0 时返回 *(this + this[nArg2+196] + 269)（槽表基址 +784），否则返 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_40AF90(uint8_t *this, int nArg2)  // 函数 槽状态读取（非零返回）
{
  if ( *(this + 12) != 0 )
    return *(this + *((uint32_t *)this + nArg2 + 196) + 269);
  else  // 否则分支
    return 0;
}



// ------------------------------------------------------------
// 0x40AFC0 sub_40AFC0 —— 槽空闲判定（返回布尔）
// 与 ·sub_40AF90 同构（差异：判等 0 返回布尔）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_40AFC0(uint8_t *this, int nArg2)  // 函数 槽空闲判定（返回布尔）
{
  return *(this + 12) != 0 && *(this + *((uint32_t *)this + nArg2 + 196) + 269) == 0;
}



// ------------------------------------------------------------
// 0x40B000 sub_40B000 —— 输入设备对象构造（off_6C24D8 → off_6C2510）
// this[2]=nArg2；·sub_415190 输入映射表重置（六段 memset）；this[773]/[774] 存 nArg4/nArg3 后改挂 off_6C2510，末 ·sub_4157E0 清设备槽 +3088；0xC1C 对象 —— ·0x40B210 类型 0。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B000(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数 输入设备对象构造（off_6C24D8 → off_6C2510）
{
  *(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)this = &off_6C24D8;  // vftable = off_6C24D8
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  sub_415190();  // 调 sub_415190
  *((uint32_t *)this + 773) = nArg4;  // this 偏移 3092 = 参数4
  *(uint32_t *)this = &off_6C2510;  // vftable = off_6C2510
  *((uint32_t *)this + 774) = nArg3;  // this 偏移 3096 = 参数3
  sub_4157E0(this);  // 调 sub_4157E0
  return this;
}



// ------------------------------------------------------------
// 0x40B080 sub_40B080 —— 输入设备对象构造变体（off_6C2548）
// this[841]/[842] 存 nArg4/nArg3（+3364/+3368），其余与 ·sub_40B000 同构；0xD2C 对象 —— ·0x40B210 类型 1。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B080(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数 输入设备对象构造变体（off_6C2548）
{
  *(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)this = &off_6C24D8;  // vftable = off_6C24D8
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  sub_415190();  // 调 sub_415190
  *((uint32_t *)this + 841) = nArg4;  // this 偏移 3364 = 参数4
  *(uint32_t *)this = &off_6C2548;  // vftable = off_6C2548
  *((uint32_t *)this + 842) = nArg3;  // this 偏移 3368 = 参数3
  sub_4157E0(this);  // 调 sub_4157E0
  return this;
}



// ------------------------------------------------------------
// 0x40B100 sub_40B100 —— 参数读取（+3092）
// ·sub_40B000 写入的首参（this[773]）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B100(uint32_t *this)  // 函数 参数读取（+3092）
{
  return *(this + 773);
}



// ------------------------------------------------------------
// 0x40B110 sub_40B110 —— 参数读取（+3096）
// ·sub_40B000 写入的次参（this[774]）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B110(uint32_t *this)  // 函数 参数读取（+3096）
{
  return *(this + 774);
}



// ------------------------------------------------------------
// 0x40B120 sub_40B120 —— 字段读取（+3100）
// 与 ·sub_40B100 / ·sub_40B110 同构的第三个读数（this[775]）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B120(uint32_t *this)  // 函数 字段读取（+3100）
{
  return *(this + 775);
}



// ------------------------------------------------------------
// 0x40B130 sub_40B130 —— 字段清零（this+28 = 0）
// 被 ·0x4036F0 / ·0x406520 事件分发对象构造调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_40B130(uint32_t *this)  // 函数 字段清零（this+28 = 0）
{
  *(this + 7) = 0;  // this+7 清 0
}



// ============================================================
// SECTION 0x40B140 — DirectInput8 输入子系统（DirectInput8Create / 键盘设备容器）
// ============================================================
// ------------------------------------------------------------
// 0x40B140 sub_40B140
// ------------------------------------------------------------
// 【解读】
//   DirectInput8Create —— 输入子系统构造（设备容器 0x40B210/0x40B990）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B140(int this)  // 【DirectInput8 输入子系统（DirectInput8Create / 键盘…】
{
  return DirectInput8Create(
           *(HINSTANCE *)(*(uint32_t *)(this + 12) + 20),
           0x800u,
           &riidltf,
           (LPVOID *)(this + 28),
           nullptr) >= 0
       ? 1
       : -2147483584;
}



// ------------------------------------------------------------
// 0x40B170 sub_40B170 —— DirectInput8 接口释放（this+28，vt+8）
// 与 ·0x40B140 DirectInput8Create 创建成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B170(int *this)  // 函数 DirectInput8 接口释放（this+28，vt+8）
{
  int result; // eax

  result = *(this + 7);  // result = this+7
  if ( result != 0 )  // 若 result != 0
    result = (*(int (/*stdcall*/ **)(int))(*(uint32_t *)result + 8))(result);  // 调用虚函数/间接调用
  *(this + 7) = 0;  // this+7 清 0
  return result;
}



// ------------------------------------------------------------
// 0x40B190 sub_40B190 —— 输入容器基类析构（off_6C24D8 → 子对象清理桩 → IObject::vftable）
// 与 ·sub_40B3E0 逐行同构（差异：无）。
// ------------------------------------------------------------
void /*thiscall*/ sub_40B190(Concurrency::details::TaskStack *this)  // 函数 输入容器基类析构（off_6C24D8 → 子对象清理桩 → IObject::vftable）
{
  *(uint32_t *)this = &off_6C24D8;  // vftable = off_6C24D8
  Concurrency::details::TaskStack::ResetOverflow(this);
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
}



// ------------------------------------------------------------
// 0x40B1E0 sub_40B1E0 —— 删除壳（·sub_40B190 + 低位置位 free）
// 与 ·sub_40B190 成对的标准删除壳。
// ------------------------------------------------------------
Concurrency::details::TaskStack */*thiscall*/ sub_40B1E0(Concurrency::details::TaskStack *Block, char pszArg2)  // 调 删除壳（·sub_40B190 + 低位置位 free）
{
  sub_40B190(Block);  // 调 sub_40B190
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40B210 sub_40B210 —— 输入设备工厂（按 Block 0/1/2 选型）
// 1 → 0xD2C ·sub_40B080(1, this+12, this+28)；0 → 0xC1C ·sub_40B000(0, ...)；2 → 仅登记；出参挂 +16 链（·sub_40C0F0 + ·sub_407F40）；
// +4 未就绪返 0x80000001，分配失败 0x80000008，类型未知 0x80000009。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B210(int this, void *Block, uint32_t *uArg3)  // 函数 输入设备工厂（按 Block 0/1/2 选型）
{
  uint32_t *uArg32; // ecx
  uint8_t *pMem; // eax
  uint8_t *fld_C; // eax
  uint8_t *pMem2; // eax
  int fld_14; // edi
  int v10; // ebx

  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  if ( Block != nullptr )  // 若 Block 非空
  {
    if ( Block != (void *)1 )
    {
      if ( Block != (void *)2 )
        return -2147483639;  // 返回 0x80000009（类型错）
      uArg32 = uArg3;
      *uArg3 = 0;  // 写指针 = 0
      goto LABEL_16;  // 跳转 LABEL_16
    }
    pMem = operator new(0xD2Cu);
    if ( pMem != nullptr )  // 若 pMem 非空
      fld_C = sub_40B080(pMem, 1, *(uint32_t *)(this + 12), *(uint32_t *)(this + 28));  // 调 输入设备对象构造变体（off_6C2548）
    else  // 否则分支
      fld_C = nullptr;  // fld_C = 空指针
  }
  else  // 否则分支
  {
    pMem2 = operator new(0xC1Cu);
    if ( pMem2 != nullptr )  // 若 pMem2 非空
      fld_C = sub_40B000(pMem2, 0, *(uint32_t *)(this + 12), *(uint32_t *)(this + 28));  // 调 输入设备对象构造（off_6C24D8 → off_6C2510）
    else  // 否则分支
      fld_C = nullptr;  // fld_C = 空指针
  }
  if ( fld_C == nullptr )  // 若 fld_C 为空
    return -2147483640;  // 返回 0x80000008（内存不足）
  uArg32 = uArg3;
  *uArg3 = fld_C;  // 写指针 = fld_C
LABEL_16:  // LABEL_16（跳转目标）
  fld_14 = *(uint32_t *)(this + 20);
  v10 = sub_40C0F0(fld_14, *(uint32_t *)(fld_14 + 4), uArg32);  // v10 = sub_40C0F0(...)
  sub_407F40((uint32_t *)(this + 16), 1u);  // 调 sub_407F40
  *(uint32_t *)(fld_14 + 4) = v10;  // fld_14+4 = v10
  **(uint32_t **)(v10 + 4) = v10;  // v10 偏移 4 指向自身（自环）
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x40B350 sub_40B350 —— 输入容器构造（off_6C2580，+3088 = nArg3）
// this[772]=nArg3；仅调 ·sub_415190 映射表重置（不调 ·sub_4157E0）；0xC14 对象 —— ·sub_40B430 创建。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B350(uint8_t *this, int nArg2, int nArg3)  // 函数 输入容器构造（off_6C2580，+3088 = nArg3）
{
  *(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)this = &off_6C24D8;  // vftable = off_6C24D8
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  sub_415190();  // 调 sub_415190
  *((uint32_t *)this + 772) = nArg3;  // this 偏移 3088 = 参数3
  *(uint32_t *)this = &off_6C2580;  // vftable = off_6C2580
  return this;
}



// ------------------------------------------------------------
// 0x40B3B0 sub_40B3B0 —— 删除壳（·sub_40B3E0 + 低位置位 free）
// 与 ·sub_40B3E0 成对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_40B3B0(void *Block, char pszArg2)  // 函数 删除壳（·sub_40B3E0 + 低位置位 free）
{
  sub_40B3E0();  // 调 sub_40B3E0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40B3E0 sub_40B3E0 —— 容器析构（off_6C24D8 → 子对象清理桩 → IObject::vftable）
// 与 ·sub_40B190 逐行同构（差异：无）。
// ------------------------------------------------------------
void /*thiscall*/ sub_40B3E0(Concurrency::details::TaskStack *this)  // 函数 容器析构（off_6C24D8 → 子对象清理桩 → IObject::vftable）
{
  *(uint32_t *)this = &off_6C24D8;  // vftable = off_6C24D8
  Concurrency::details::TaskStack::ResetOverflow(this);
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
}



// ------------------------------------------------------------
// 0x40B430 sub_40B430 —— 输入容器工厂 B
// Block == 0 → 0xC14 ·sub_40B350(0, this+12)；1/2 → 仅登记；挂 +16 链；与 ·sub_40B210 同构（差异：单一对象型别）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B430(int this, void *Block, uint32_t *uArg3)
{
  uint32_t *uArg32; // ecx
  uint8_t *pMem; // eax
  uint8_t *fld_C; // eax
  int fld_14; // edi
  int v9; // ebx

  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  if ( Block != nullptr )  // 若 Block 非空
  {
    if ( Block != (void *)1 && Block != (void *)2 )
      return -2147483639;  // 返回 0x80000009（类型错）
    uArg32 = uArg3;
    *uArg3 = 0;  // 写指针 = 0
  }
  else  // 否则分支
  {
    pMem = operator new(0xC14u);
    if ( pMem != nullptr )  // 若 pMem 非空
      fld_C = sub_40B350(pMem, 0, *(uint32_t *)(this + 12));  // 调 输入容器构造（off_6C2580，+3088 = nArg3）
    else  // 否则分支
      fld_C = nullptr;  // fld_C = 空指针
    if ( fld_C == nullptr )  // 若 fld_C 为空
      return -2147483640;  // 返回 0x80000008（内存不足）
    uArg32 = uArg3;
    *uArg3 = fld_C;  // 写指针 = fld_C
  }
  fld_14 = *(uint32_t *)(this + 20);
  v9 = sub_40C0F0(fld_14, *(uint32_t *)(fld_14 + 4), uArg32);  // v9 = sub_40C0F0(...)
  sub_407F40((uint32_t *)(this + 16), 1u);  // 调 sub_407F40
  *(uint32_t *)(fld_14 + 4) = v9;  // fld_14+4 = v9
  **(uint32_t **)(v9 + 4) = v9;  // v9 偏移 4 指向自身（自环）
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x40B530 sub_40B530 —— 文本/绘制容器基类构造（off_6C25B8）
// this[2]=nArg2、this[3]=nArg3 后挂 off_6C25B8，末 ·sub_4163E0 转发 vt+32；被 ·0x40B650 与 gfx_texture ·0x4185B0（GDI 文本渲染器）复用。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B530(uint8_t *this, int nArg2, int nArg3)  // 函数 文本/绘制容器基类构造（off_6C25B8）
{
  *(this + 4) = 0;  // this+4 清 0
  *((uint32_t *)this + 3) = nArg3;  // this 偏移 12 = 参数3
  *(uint32_t *)this = &off_6C25B8;  // vftable = off_6C25B8
  *((uint32_t *)this + 2) = nArg2;  // this 偏移 8 = 参数2
  sub_4163E0(this);  // 调 sub_4163E0
  return this;
}



// ------------------------------------------------------------
// 0x40B590 sub_40B590 —— 基类析构（off_6C25B8 → ·sub_416420 复位 → IObject::vftable）
// 复位含 vt+36 调用与状态位 +4 清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B590(uint8_t *this)  // 函数 基类析构（off_6C25B8 → ·sub_416420 复位 → IObject::vftable）
{
  int result; // eax

  *(uint32_t *)this = &off_6C25B8;  // vftable = off_6C25B8
  result = sub_416420();  // 调 复位（vt+36 + 状态位清 0）
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *(this + 4) = 0;  // this+4 清 0
  return result;
}



// ------------------------------------------------------------
// 0x40B620 sub_40B620 —— 删除壳（·sub_40B590 + 低位置位 free）
// 与 ·sub_40B590 成对的标准删除壳。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B620(uint8_t *Block, char pszArg2)  // 函数 删除壳（·sub_40B590 + 低位置位 free）
{
  sub_40B590(Block);  // 调 sub_40B590
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40B650 sub_40B650 —— 派生构造（off_6C25EC）
// ·sub_40B530 基构造后改挂 off_6C25EC 并调 nullsub_3。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B650(uint8_t *this, int nArg2, int nArg3)  // 函数 派生构造（off_6C25EC）
{
  sub_40B530(this, nArg2, nArg3);  // 调 sub_40B530
  *(uint32_t *)this = &off_6C25EC;  // vftable = off_6C25EC
  nullsub_3(this);  // nullsub（空桩）
  return this;
}



// ------------------------------------------------------------
// 0x40B6B0 sub_40B6B0 —— 删除壳（·sub_40B6E0 + 低位置位 free）
// 与 ·sub_40B6E0 成对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_40B6B0(void *Block, char pszArg2)  // 函数 删除壳（·sub_40B6E0 + 低位置位 free）
{
  sub_40B6E0();  // 调 sub_40B6E0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40B6E0 sub_40B6E0 —— 二级析构（off_6C25EC → off_6C25B8 → IObject::vftable）
// 两次 ·sub_416420 复位并逐级回落虚表。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B6E0(uint8_t *this)  // 函数 二级析构（off_6C25EC → off_6C25B8 → IObject::vftable）
{
  int result; // eax

  *(uint32_t *)this = &off_6C25EC;  // vftable = off_6C25EC
  ((void (*)(void))sub_416420)();  // 调 复位（vt+36 + 状态位清 0）
  *(uint32_t *)this = &off_6C25B8;  // vftable = off_6C25B8
  result = sub_416420(this);  // 调 复位（vt+36 + 状态位清 0）
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *(this + 4) = 0;  // this+4 清 0
  return result;
}



// ------------------------------------------------------------
// 0x40B740 sub_40B740 —— 字形/文本对象构造（off_6C2620）
// ·sub_40B530 基构造后改挂 off_6C2620；this+80 内嵌字符串包（off_6C38F4）经 ·sub_402A50 初始化、+84 标志清零，末 ·sub_416E70 字体对象与全局字形缓存复位。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B740(int this, int nArg2, void *pArg3)  // 函数 字形/文本对象构造（off_6C2620）
{
  sub_40B530((uint8_t *)this, nArg2, (int)pArg3);  // 调 sub_40B530
  *(uint32_t *)this = &off_6C2620;  // vftable = off_6C2620
  *(uint8_t *)(this + 84) = 0;  // this 偏移 84 清 0
  *(uint32_t *)(this + 80) = &off_6C38F4;  // this+80 = vftable/接口 off_6C38F4
  sub_402A50((uint32_t *)(this + 80));  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  sub_416E70(this);  // 调 sub_416E70
  return this;
}



// ------------------------------------------------------------
// 0x40B7B0 sub_40B7B0 —— 两级析构（off_6C2620 → off_6C25B8 → IObject::vftable）
// this+80 串包经 ·sub_402A60 释放，两次 ·sub_416420 复位。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B7B0(uint32_t *this)  // 函数 两级析构（off_6C2620 → off_6C25B8 → IObject::vftable）
{
  int result; // eax

  *this = &off_6C2620;  // vftable = off_6C2620
  sub_416420(this);  // 调 sub_416420
  *(this + 20) = &off_6C38F4;
  sub_402A60((int)(this + 20));  // 调 sub_402A60
  *(this + 20) = &nengine::IObject::`vftable';  // this 偏移 20 = IObject vftable
  *((uint8_t *)this + 84) = 0;  // this 偏移 84 字节 = 0
  *this = &off_6C25B8;  // vftable = off_6C25B8
  result = sub_416420(this);  // 调 复位（vt+36 + 状态位清 0）
  *this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
  return result;
}



// ------------------------------------------------------------
// 0x40B840 sub_40B840 —— 删除壳（·sub_40B7B0 + 低位置位 free）
// 与 ·sub_40B7B0 成对的标准删除壳。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40B840(uint32_t *Block, char pszArg2)  // 函数 删除壳（·sub_40B7B0 + 低位置位 free）
{
  sub_40B7B0(Block);  // 调 sub_40B7B0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40B870 sub_40B870 —— 派生构造（off_6C2654）
// ·sub_40B740 基构造后改挂 off_6C2654，末再次 ·sub_416E70 复位字形缓存。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40B870(uint32_t *this, int nArg2, void *pArg3)  // 函数 派生构造（off_6C2654）
{
  sub_40B740((int)this, nArg2, pArg3);  // 调 sub_40B740
  *this = &off_6C2654;  // vftable = off_6C2654
  sub_416E70(this);  // 调 sub_416E70
  return this;
}



// ------------------------------------------------------------
// 0x40B8D0 sub_40B8D0 —— 删除壳（·sub_40B900 + 低位置位 free）
// 与 ·sub_40B900 成对的标准删除壳。
// ------------------------------------------------------------
void */*thiscall*/ sub_40B8D0(void *Block, char pszArg2)  // 函数 删除壳（·sub_40B900 + 低位置位 free）
{
  sub_40B900();  // 调 sub_40B900
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40B900 sub_40B900 —— 析构（off_6C2654 → ·sub_416420 → ·sub_40B7B0 链）
// 先复位再交 ·sub_40B7B0 完成两级析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B900(uint32_t *this)  // 函数 析构（off_6C2654 → ·sub_416420 → ·sub_40B7B0 链）
{
  *this = &off_6C2654;  // vftable = off_6C2654
  sub_416420(this);  // 调 sub_416420
  return sub_40B7B0(this);  // 调 两级析构（off_6C2620 → off_6C25B8 → IObject::vftable）
}



// ------------------------------------------------------------
// 0x40B950 sub_40B950 —— list 头插（12B 结点 + 哨兵环链）
// ·sub_40C0F0 分配结点挂入哨兵 next；长度上限经 ·sub_407B40（list<T> too long）校验。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B950(uint32_t *this, int nArg2)  // 函数 list 头插（12B 结点 + 哨兵环链）
{
  int fld_e1; // edi
  int v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), nArg2);  // v4 = sub_40C0F0(...)
  result = sub_407B40(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;  // fld_e1+4 = v4
  **(uint32_t **)(v4 + 4) = v4;  // v4 偏移 4 指向自身（自环）
  return result;
}



// ============================================================
// SECTION 0x40B990 — 文本测量（GetTextExtentPoint32）/ GDI 文本渲染 / 容器工具
// ============================================================
// ------------------------------------------------------------
// 0x40B990 sub_40B990 —— 文本对象工厂（按格式 1/3 建字形/控制台/字模对象挂链）
// switch(nArg2)=1/2/3/4：格式字段 (this+12)+8 为 1 或 3 时按 0x84/0xA0/0x10/0x20104
// 字节分交 ·sub_40B870 / ·sub_40D510 / ·sub_40B650 / ·sub_4185B0 构造；成功对象经
// ·sub_40B950 挂链，分配失败返回 -2147483640。
// ------------------------------------------------------------
int /*thiscall*/ sub_40B990(int this, int nArg2, uint32_t *Block)  // 【文本测量（GetTextExtentPoint32）/ GDI 文本渲染 / 容器工具】
{
  int result; // eax
  int fld_C; // eax
  uint32_t *pMem; // eax
  void *fld_1C; // eax
  int fld_C2; // eax
  void *pMem2; // eax
  int fld_C3; // eax
  uint8_t *pMem3; // eax

  if ( *(uint8_t *)(this + 4) == 0 )  // 若 this 偏移 4 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  switch ( nArg2 )
  {
    case 1:  // case 分支 1
      fld_C = *(uint32_t *)(*(uint32_t *)(this + 12) + 8);
      if ( fld_C == 1 )  // 若 fld_C == 1
        goto LABEL_14;  // 跳转 LABEL_14
      if ( fld_C != 3 )  // 若 fld_C != 3
        goto LABEL_23;  // 跳转 LABEL_23
      pMem = operator new(0x84u);
      if ( pMem != nullptr )  // 若 pMem 非空
        fld_1C = sub_40B870(pMem, nArg2, (void *)this);  // 调 派生构造（off_6C2654）
      else  // 否则分支
        fld_1C = nullptr;  // fld_1C = 空指针
      goto LABEL_20;  // 跳转 LABEL_20
    case 2:  // case 分支 2
      goto LABEL_23;  // 跳转 LABEL_23
    case 3:  // case 分支 3
      fld_C2 = *(uint32_t *)(*(uint32_t *)(this + 12) + 8);
      if ( fld_C2 == 1 )  // 若 fld_C2 == 1
        goto LABEL_14;  // 跳转 LABEL_14
      if ( fld_C2 != 3 )  // 若 fld_C2 != 3
        goto LABEL_23;  // 跳转 LABEL_23
      pMem2 = operator new(0xA0u);
      if ( pMem2 != nullptr )  // 若 pMem2 非空
        fld_1C = (void *)sub_40D510(pMem2, *(uint32_t *)(*(uint32_t *)(this + 28) + 16), nArg2, this);
      else  // 否则分支
        fld_1C = nullptr;  // fld_1C = 空指针
      goto LABEL_20;  // 跳转 LABEL_20
    case 4:  // case 分支 4
      fld_C3 = *(uint32_t *)(*(uint32_t *)(this + 12) + 8);
      if ( fld_C3 == 1 )  // 若 fld_C3 == 1
      {
LABEL_14:  // LABEL_14（跳转目标）
        pMem3 = operator new(0x10u);
        if ( pMem3 != nullptr )  // 若 pMem3 非空
          fld_1C = sub_40B650(pMem3, nArg2, this);  // 调 派生构造（off_6C25EC）
        else  // 否则分支
          fld_1C = nullptr;  // fld_1C = 空指针
      }
      else  // 否则分支
      {
        if ( fld_C3 != 3 )  // 若 fld_C3 != 3
          goto LABEL_23;  // 跳转 LABEL_23
        if ( operator new(0x20104u) != nullptr )
          fld_1C = (void *)sub_4185B0(*(HWND *)(*(uint32_t *)(this + 28) + 16), nArg2, this);  // 调 文本渲染器构造（32x32 DIB + 兼容 DC）
        else  // 否则分支
          fld_1C = nullptr;  // fld_1C = 空指针
      }
LABEL_20:  // LABEL_20（跳转目标）
      if ( fld_1C == nullptr )  // 若 fld_1C 为空
        return -2147483640;  // 返回 0x80000008（内存不足）
      *Block = fld_1C;  // 写指针 = fld_1C
LABEL_23:  // LABEL_23（跳转目标）
      sub_40B950((uint32_t *)(this + 16), (int)Block);  // 调 sub_40B950
      result = 1;
      break;  // 跳出 switch
    default:  // 默认分支
      *Block = 0;
      return -2147483639;  // 返回 0x80000009（类型错）
  }
  return result;
}



// ------------------------------------------------------------
// 0x40BB70 sub_40BB70 —— 文本像素宽度测量（GetTextExtentPoint32A 的 cx）
// 空串返回 0；DC 取自 this+40。
// ------------------------------------------------------------
LONG /*thiscall*/ sub_40BB70(HDC *this, LPCSTR lpString)  // 函数 文本像素宽度测量（GetTextExtentPoint32A 的 cx）
{
  int v4; // eax
  struct tagSIZE psizl; // [esp+8h] [ebp-8h] BYREF

  if ( lpString == nullptr )  // 若 lpString 为空
    return 0;
  v4 = lstrlenA(lpString);  // API 字符串长度（Win32 ANSI）
  GetTextExtentPoint32A(*(this + 10), lpString, v4, &psizl);  // 调 GetTextExtentPoint32A
  return psizl.cx;
}



// ------------------------------------------------------------
// 0x40BBB0 sub_40BBB0 —— 按像素宽截断位搜索（双字节前导字节感知，逐字累加测量）
// 逐字 GetTextExtentPoint32A：宽度达 uArg3 返回下标+1，循环尽返回 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_40BBB0(HDC *this, LPCSTR lpString, LONG uArg3)  // 函数 按像素宽截断位搜索（双字节前导字节感知，逐字累加测量）
{
  int v6; // eax
  int v7; // esi
  char v8; // al
  int v9; // edi
  int v10; // eax
  struct tagSIZE psizl; // [esp+Ch] [ebp-80Ch] BYREF
  CHAR String[2048]; // [esp+14h] [ebp-804h] BYREF
  int dword_796E502; // [esp+814h] [ebp-4h]
  LPCSTR lpStringa; // [esp+820h] [ebp+8h]

  dword_796E502 = dword_796E50;  // 栈检 cookie
  if ( lpString == nullptr )  // 若 lpString 为空
    return -1;  // 返回错误码 -1
  v6 = lstrlenA(lpString);  // API 字符串长度（Win32 ANSI）
  GetTextExtentPoint32A(*(this + 10), lpString, v6, &psizl);  // 调 GetTextExtentPoint32A
  if ( uArg3 >= psizl.cx )
    return -1;  // 返回错误码 -1
  v7 = 0;
  memset(String, 0, sizeof(String));  // 调 memset
  lpStringa = (LPCSTR)strlen(lpString);  // CRT 字符串长度（逐字节扫描到 NUL）
  while ( v7 < (int)lpStringa )
  {
    v8 = lpString[v7];
    v9 = v7;
    String[v7] = v8;
    String[v7 + 1] = 0;
    if ( v8 < 0
      && (v8 == -127
       || v8 == -126  // GBK 双字节前导字节表项 -126
       || v8 == -125  // GBK 双字节前导字节表项 -125
       || v8 == -124  // GBK 双字节前导字节表项 -124
       || v8 == -121  // GBK 双字节前导字节表项 -121
       || v8 == -120  // GBK 双字节前导字节表项 -120
       || v8 == -119  // GBK 双字节前导字节表项 -119
       || v8 == -118  // GBK 双字节前导字节表项 -118
       || v8 == -117  // GBK 双字节前导字节表项 -117
       || v8 == -116  // GBK 双字节前导字节表项 -116
       || v8 == -115  // GBK 双字节前导字节表项 -115
       || v8 == -114  // GBK 双字节前导字节表项 -114
       || v8 == -113  // GBK 双字节前导字节表项 -113
       || v8 == -112  // GBK 双字节前导字节表项 -112
       || v8 == -111  // GBK 双字节前导字节表项 -111
       || v8 == -110  // GBK 双字节前导字节表项 -110
       || v8 == -109  // GBK 双字节前导字节表项 -109
       || v8 == -108  // GBK 双字节前导字节表项 -108
       || v8 == -107  // GBK 双字节前导字节表项 -107
       || v8 == -106  // GBK 双字节前导字节表项 -106
       || v8 == -105  // GBK 双字节前导字节表项 -105
       || v8 == -104  // GBK 双字节前导字节表项 -104
       || v8 == -103  // GBK 双字节前导字节表项 -103
       || v8 == -102  // GBK 双字节前导字节表项 -102
       || v8 == -101  // GBK 双字节前导字节表项 -101
       || v8 == -100  // GBK 双字节前导字节表项 -100
       || v8 == -99  // GBK 双字节前导字节表项 -99
       || v8 == -98  // GBK 双字节前导字节表项 -98
       || v8 == -97  // GBK 双字节前导字节表项 -97
       || v8 == -32  // GBK 双字节前导字节表项 -32
       || v8 == -31  // GBK 双字节前导字节表项 -31
       || v8 == -30  // GBK 双字节前导字节表项 -30
       || v8 == -29  // GBK 双字节前导字节表项 -29
       || v8 == -28  // GBK 双字节前导字节表项 -28
       || v8 == -27  // GBK 双字节前导字节表项 -27
       || v8 == -26  // GBK 双字节前导字节表项 -26
       || v8 == -25  // GBK 双字节前导字节表项 -25
       || v8 == -24  // GBK 双字节前导字节表项 -24
       || v8 == -23  // GBK 双字节前导字节表项 -23
       || v8 == -22  // GBK 双字节前导字节表项 -22
       || v8 == -19  // GBK 双字节前导字节表项 -19
       || v8 == -18  // GBK 双字节前导字节表项 -18
       || v8 == -6  // GBK 双字节前导字节表项 -6
       || v8 == -5  // GBK 双字节前导字节表项 -5
       || v8 == -4) )
    {
      String[v7 + 1] = lpString[v7 + 1];
      String[v7++ + 2] = 0;
    }
    ++v7;  // v7 自增
    v10 = lstrlenA(String);  // API 字符串长度（Win32 ANSI）
    GetTextExtentPoint32A(*(this + 10), String, v10, &psizl);  // 调 GetTextExtentPoint32A
    if ( uArg3 <= psizl.cx )
      return v9 + 1;
  }
  return -1;  // 返回错误码 -1
}



// ------------------------------------------------------------
// 0x40BDD0 sub_40BDD0 —— 4 槽表面初始化循环（·sub_411240 512×512×25）
// 每槽先管理对象虚发 +8(12,槽位) 建表项、旧对象虚发 +20 释放，再建 512² 表面；
// 4 槽全成返回 1。【推断: 精灵/层池】
// ------------------------------------------------------------
int /*thiscall*/ sub_40BDD0(uint32_t *this)  // 函数 4 槽表面初始化循环（·sub_411240 512×512×25）
{
  int v2; // edi
  uint32_t *i; // esi
  int result; // eax

  v2 = 0;
  for ( i = this + 5; ; ++i )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t *))(**(uint32_t **)(*(this + 3) + 12) + 8))(
               *(uint32_t *)(*(this + 3) + 12),
               12,
               i);
    if ( result < 0 )  // 若 result < 0
      break;  // 跳出 switch
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*i + 20))(*i);  // 调用虚函数/间接调用
    sub_411240(512, 512, 25);  // 调 sub_411240
    if ( ++v2 >= 4 )
      return 1;  // 返回 1（成功）
  }
  return result;
}



// ------------------------------------------------------------
// 0x40BE20 sub_40BE20
// ------------------------------------------------------------
// 【解读】
//   _DEBUG 控制台单行输出: _access 探测控制台状态 + GetStdHandle/WriteConsoleA。
//   全引擎调试打印的最终出口（0x655A90/0x657120 等都转发到这里）。
// ------------------------------------------------------------
int /*usercall*/ sub_40BE20@<eax>(DWORD uArg1@<ecx>, char *Format, ...)  // 函数 摘链(推断)
{
  int result; // eax
  HANDLE StdHandle; // eax
  DWORD nLen; // [esp-Ch] [ebp-10h]
  DWORD NumberOfCharsWritten; // [esp+0h] [ebp-4h] BYREF
  va_list va; // [esp+10h] [ebp+Ch] BYREF

  va_start(va, Format);
  NumberOfCharsWritten = uArg1;
  result = _access("_DEBUG", 0);
  if ( result == 0 )  // 若 result == 0
  {
    memset(byte_8A6EC8, 0, sizeof(byte_8A6EC8));  // 调 memset
    vsprintf(byte_8A6EC8, Format, va);  // 调 vsprintf
    nLen = strlen(byte_8A6EC8);  // CRT 字符串长度（逐字节扫描到 NUL）
    NumberOfCharsWritten = 0;  // NumberOfCharsWritten = 0/空
    StdHandle = GetStdHandle(0xFFFFFFF5);
    return WriteConsoleA(StdHandle, byte_8A6EC8, nLen, &NumberOfCharsWritten, nullptr);
  }
  return result;
}



// ------------------------------------------------------------
// 0x40BEA0 sub_40BEA0 —— 红黑树迭代器自增（后继；哨兵位 +45）
// 右子非哨兵取右子树最左；否则沿 +4 父链上爬至当前为其右子。MSVC _Tree 迭代器形。
// ------------------------------------------------------------
int */*thiscall*/ sub_40BEA0(int *this)  // 函数 红黑树迭代器自增（后继；哨兵位 +45）
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 45) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 45) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 45) == 0; result = (int *)result[1] )
      {
        if ( *this != result[2] )
          break;  // 跳出 switch
        *this = (int)result;
      }
      *this = (int)result;
    }
    else  // 否则分支
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 45) == 0 )
      {
        do  // do 循环体
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 45) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40BF00 sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
// 以 pos/len 对目标串前缀比较；this+24 容量、<16 时数据在 this+4。
// ------------------------------------------------------------
int /*thiscall*/ sub_40BF00(std::_String_base *this, unsigned int uArg2, unsigned int uArg3, const char *pArg4, unsigned int uArg5)  // 函数 std::string 比较（memcmp + 长度序；越界走 _Xran）
{
  unsigned int pThis_5; // edx
  int pThis_52; // ecx
  int pThis_6; // eax
  int result; // eax

  if ( *((uint32_t *)this + 5) < uArg2 )
    std::_String_base::_Xran(this);  // CRT 抛出 out_of_range（下标越界）
  pThis_5 = uArg3;
  if ( *((uint32_t *)this + 5) - uArg2 < uArg3 )
    pThis_5 = *((uint32_t *)this + 5) - uArg2;
  if ( pThis_5 == 0 )  // 若 pThis_5 == 0
    goto LABEL_12;  // 跳转 LABEL_12
  pThis_52 = pThis_5;
  if ( pThis_5 >= uArg5 )  // 若 pThis_5 >= uArg5
    pThis_52 = uArg5;
  pThis_6 = *((uint32_t *)this + 6) < 0x10u ? (int)this + 4 : *((uint32_t *)this + 1);
  result = memcmp((const char *)(pThis_6 + uArg2), pArg4, pThis_52);
  if ( result == 0 )  // 若 result == 0
  {
LABEL_12:  // LABEL_12（跳转目标）
    if ( pThis_5 >= uArg5 )  // 若 pThis_5 >= uArg5
      return pThis_5 != uArg5;
    else  // 否则分支
      return -1;  // 返回错误码 -1
  }
  return result;
}



// ------------------------------------------------------------
// 0x40BF80 sub_40BF80 —— 控制台离屏 DIB 建立（512×12·16bpp + 0x00010001 填充）
// CreateDIBSection 挂 this+44、位缓冲 this+48；0x00010001 重复填充作空标记。
// 兼容 DC 由窗口 DC(this+36) 建，SelectObject 到 this+40。
// ------------------------------------------------------------
int /*thiscall*/ sub_40BF80(int this)  // 函数 控制台离屏 DIB 建立（512×12·16bpp + 0x00010001 填充）
{
  HDC DC; // eax
  int fld_40; // edx
  LONG fld_3C; // ecx
  unsigned int fld_402; // ecx
  char *fld_30; // edi
  char v7; // cf
  unsigned int v8; // ecx
  char *v9; // edi
  int i; // ecx
  HDC v11; // edi
  HDC CompatibleDC; // eax
  void *fld_2C; // [esp-4h] [ebp-3Ch]
  BITMAPINFO pbmi; // [esp+Ch] [ebp-2Ch] BYREF

  DC = GetDC(*(HWND *)(this + 36));
  fld_40 = *(uint32_t *)(this + 64);
  fld_3C = *(uint32_t *)(this + 60);
  pbmi.bmiColors[0] = (RGBQUAD)DC;
  pbmi.bmiHeader.biSize = 40;
  pbmi.bmiHeader.biWidth = fld_3C;
  pbmi.bmiHeader.biHeight = -fld_40;
  pbmi.bmiHeader.biPlanes = 1;
  pbmi.bmiHeader.biBitCount = 16;
  memset(&pbmi.bmiHeader.biCompression, 0, 24);  // 调 memset
  *(uint32_t *)(this + 44) = CreateDIBSection(nullptr, &pbmi, 0, (void **)(this + 48), nullptr, 0);  // this+44 = CreateDIBSection(nullptr, &pbmi, 0, (void **)(this + 48), nullptr, 0)
  *(uint16_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;  // this+76（uint32 槽）= 0
  memset((void *)(this + 80), 0, 0x50u);  // 调 memset
  fld_402 = *(uint32_t *)(this + 64) * *(uint32_t *)(this + 60);
  fld_30 = *(char **)(this + 48);
  if ( fld_402 != 0 )  // 若 fld_402 != 0
  {
    v7 = fld_402 & 1;
    v8 = fld_402 >> 1;
    memset32(fld_30, 65537, v8);
    v9 = &fld_30[4 * v8];
    for ( i = v7; i != 0; --i )
    {
      *(uint16_t *)v9 = 1;
      v9 += 2;  // v9 前进 2
    }
  }
  v11 = (HDC)pbmi.bmiColors[0];
  CompatibleDC = CreateCompatibleDC(*(HDC *)pbmi.bmiColors);
  fld_2C = *(void **)(this + 44);
  *(uint32_t *)(this + 40) = CompatibleDC;  // this+40 = CompatibleDC
  SelectObject(CompatibleDC, fld_2C);  // 调 SelectObject
  return ReleaseDC(*(HWND *)(this + 36), v11);
}



// ------------------------------------------------------------
// 0x40C040 sub_40C040 —— DIB 清屏与文本绘制（nArg4==1 时 1px 偏移重绘）
// 背景重置 0x00010001，SetBkMode(1)+SetTextColor(color) 后 TextOutA(0,0)。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_40C040(int this, LPCSTR lpString, COLORREF color, int nArg4)  // 函数 DIB 清屏与文本绘制（nArg4==1 时 1px 偏移重绘）
{
  unsigned int fld_3C; // ecx
  char *fld_30; // edi
  char v7; // cf
  unsigned int v8; // ecx
  char *v9; // edi
  int i; // ecx
  BOOL result; // eax

  *(uint16_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;  // this+76（uint32 槽）= 0
  memset((void *)(this + 80), 0, 0x50u);  // 调 memset
  fld_3C = *(uint32_t *)(this + 60) * *(uint32_t *)(this + 64);
  fld_30 = *(char **)(this + 48);
  if ( fld_3C != 0 )  // 若 fld_3C != 0
  {
    v7 = fld_3C & 1;
    v8 = fld_3C >> 1;
    memset32(fld_30, 65537, v8);
    v9 = &fld_30[4 * v8];
    for ( i = v7; i != 0; --i )
    {
      *(uint16_t *)v9 = 1;
      v9 += 2;  // v9 前进 2
    }
  }
  SetBkMode(*(HDC *)(this + 40), 1);  // 调 SetBkMode
  SetTextColor(*(HDC *)(this + 40), color);  // 调 SetTextColor
  result = TextOutA(*(HDC *)(this + 40), 0, 0, lpString, strlen(lpString));
  if ( nArg4 == 1 )  // 若 nArg4 == 1
    return TextOutA(*(HDC *)(this + 40), 1, 0, lpString, strlen(lpString));
  return result;
}



// ------------------------------------------------------------
// 0x40C0E0 sub_40C0E0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_40C0E0(uint32_t *this)
{
  return sub_40BDD0(this);  // 调 4 槽表面初始化循环（·sub_411240 512×512×25）
}



// ------------------------------------------------------------
// 0x40C0F0 sub_40C0F0 —— list 结点分配（12B：前驱/后继/数据）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_40C0F0(int nArg1, int nArg2, uint32_t *uArg3)  // 函数 list 结点分配（12B：前驱/后继/数据）
{
  uint32_t *result; // eax

  result = operator new(0xCu);
  if ( result != nullptr )  // 若 result 非空
  {
    *result = nArg1;  // 写指针 = nArg1
    result[1] = nArg2;
    result[2] = *uArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40C120 sub_40C120 —— 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
// ------------------------------------------------------------
void /*thiscall*/ sub_40C120(uint32_t *this)  // 函数 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
{
  *(this + 6) = 15;  // this+6 = 15
  *(this + 5) = 0;  // this+5 清 0
  *((uint8_t *)this + 4) = 0;  // this 偏移 4 字节 = 0
}



// ------------------------------------------------------------
// 0x40C140 sub_40C140 —— 桶结点销毁（·sub_6569D0 清首字段 + free 附属块 + 置空）
// ------------------------------------------------------------
void /*thiscall*/ sub_40C140(void **this)  // 函数 桶结点销毁（·sub_6569D0 清首字段 + free 附属块 + 置空）
{
  sub_6569D0(this);  // 调 sub_6569D0
  j__free(*(this + 1));  // free this+1
  *(this + 1) = nullptr;  // this+1 = 空指针
}



// ------------------------------------------------------------
// 0x40C160 sub_40C160 —— map 键比较器（string < string，经 ·sub_40BF00）
// ------------------------------------------------------------
bool /*stdcall*/ sub_40C160(unsigned int *pDwArg1, uint32_t *pArg2)  // 函数 map 键比较器（string < string，经 ·sub_40BF00）
{
  const char *v2; // eax

  if ( pArg2[6] < 0x10u )
    v2 = (const char *)(pArg2 + 1);
  else  // 否则分支
    v2 = (const char *)pArg2[1];
  return sub_40BF00((std::_String_base *)pDwArg1, 0, pDwArg1[5], v2, pArg2[5]) < 0;  // 调 std::string 比较（memcmp + 长度序；越界走 _Xran）
}



// ------------------------------------------------------------
// 0x40C1A0 sub_40C1A0 —— 空串初始化（this+16 系）
// —— 与 ·sub_40C120 同构（差异：串基址 4 → 16）。
// ------------------------------------------------------------
void /*thiscall*/ sub_40C1A0(uint32_t *this)  // 函数 空串初始化（this+16 系）
{
  *(this + 9) = 15;  // this+9 = 15
  *(this + 8) = 0;  // this+8 清 0
  *((uint8_t *)this + 16) = 0;  // this 偏移 16 字节 = 0
}



// ------------------------------------------------------------
// 0x40C1C0 sub_40C1C0 —— 环形链表哨兵初始化（·sub_425940 分配 + 计数清零）
// ------------------------------------------------------------
void /*thiscall*/ sub_40C1C0(uint32_t *this)  // 函数 环形链表哨兵初始化（·sub_425940 分配 + 计数清零）
{
  *(this + 1) = sub_425940(this);  // 调 this 偏移 20 = sub_425940(this+16)
  *(this + 2) = 0;  // this+2 清 0
}



// ------------------------------------------------------------
// 0x40C1E0 sub_40C1E0 —— logic_error 删除壳（·sub_4017A0 析构 + 低位 free）
// ------------------------------------------------------------
void **/*thiscall*/ sub_40C1E0(void **Block, char pszArg2)  // 函数 logic_error 删除壳（·sub_4017A0 析构 + 低位 free）
{
  sub_4017A0(Block);  // 调 sub_4017A0
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ------------------------------------------------------------
// 0x40C210 sub_40C210 —— 控制台记录双数组释放（0x34 字节 / 0xC 字节元素族）
// this+20 起的 0x34 字节元素数组经 ·sub_5014C0 析构；this+24 起的 0xC 字节数组经 ·sub_40C140。
// ------------------------------------------------------------
void /*thiscall*/ sub_40C210(uint32_t *this)  // 函数 控制台记录双数组释放（0x34 字节 / 0xC 字节元素族）
{
  char *fld_e5; // eax
  char *v3; // edi
  char *fld_e6; // eax
  char *v5; // edi

  fld_e5 = (char *)*(this + 5);
  if ( fld_e5 != nullptr )  // 若 fld_e5 非空
  {
    v3 = fld_e5 - 4;
    `eh vector destructor iterator'(v2, 0x34u, *((uint32_t *)v2 - 1), sub_5014C0);  // MSVC EH 向量析构迭代器（批量析构数组元素）
    j_j__free(v3);
    *(this + 5) = 0;  // this+5 清 0
  }
  v4 = (char *)*(this + 6);
  if ( v4 != nullptr )  // 若 v4 非空
  {
    v5 = v4 - 4;
    `eh vector destructor iterator'(fld_e6, 0xCu, *((uint32_t *)fld_e6 - 1), (void (/*thiscall*/ *)(void *))sub_40C140);  // 调 桶结点销毁（·sub_6569D0 清首字段 + free 附属块 + 置空）
    j_j__free(v5);
    *(this + 6) = 0;  // this+6 清 0
  }
}



// ------------------------------------------------------------
// 0x40C270 sub_40C270 [串: "list<T> too long"]
// ------------------------------------------------------------
int /*thiscall*/ sub_40C270(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // fld_e2 = this+2 字段
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // 调 sub_401740
    pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+2 = result
  return result;
}



// ------------------------------------------------------------
// 0x40C300 sub_40C300 —— 树结点值构造（键串 + 坐标三元 + 颜色标记）
// 前置 nArg2/nArg3/nArg4 三整型，this+12 串自 pArg5 拷贝，this+44 存标记、+45 清 0。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40C300(uint32_t *this, int nArg2, int nArg3, int nArg4, size_t *pArg5, char pszArg6)  // 函数 树结点值构造（键串 + 坐标三元 + 颜色标记）
{
  char *pThis_3; // edi

  *(this + 1) = nArg3;  // this+1 = 参数3
  pThis_3 = (char *)(this + 3);  // pThis_3 = this+3 指针
  *this = nArg2;  // 写指针 = nArg2
  *(this + 2) = nArg4;  // this+2 = 参数4
  *(this + 9) = 15;  // this+9 = 15
  *(this + 8) = 0;  // this+8 清 0
  *((uint8_t *)this + 16) = 0;  // this 偏移 16 字节 = 0
  sub_4014D0(this + 3, pArg5, 0, 0xFFFFFFFF);  // 调 sub_4014D0
  *((uint32_t *)pThis_3 + 7) = pArg5[7];
  *((uint8_t *)this + 44) = pszArg6;  // this 偏移 44（字节）= pszArg6
  *((uint8_t *)this + 45) = 0;  // this 偏移 45 字节 = 0
  return this;
}



// ------------------------------------------------------------
// 0x40C360 sub_40C360 —— 文本→记录查找（红黑树命中返回 node+40 记录链句柄，未命中 0）
// 先建临时串再经 ·sub_5014F0 查树。【推断: 句柄取自记录 +4→+8 链】
// ------------------------------------------------------------
int /*thiscall*/ sub_40C360(uint32_t *this, char *Src)  // 函数 文本→记录查找（红黑树命中返回 node+40 记录链句柄，未命中 0）
{
  int v3; // eax
  int v4; // esi
  size_t v6; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  int v8; // [esp+1Ch] [ebp-18h]
  unsigned int v9; // [esp+20h] [ebp-14h]
  int dword_796E502; // [esp+24h] [ebp-10h]
  int v11; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 栈检 cookie
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(&v6, Src, strlen(Src));  // 【std::string构造赋值】
  v11 = 0;
  v3 = *(uint32_t *)sub_5014F0(&Src, &v6);
  if ( v3 == *(this + 3) )
  {
    if ( v9 >= 0x10 )  // 若 v9 >= 0x10
      j__free(Block);  // free 堆对象
    return 0;
  }
  else  // 否则分支
  {
    v4 = *(uint32_t *)(**(uint32_t **)(*(uint32_t *)(v3 + 40) + 4) + 8);
    if ( v9 >= 0x10 )  // 若 v9 >= 0x10
      j__free(Block);  // free 堆对象
    return v4;
  }
}



// ------------------------------------------------------------
// 0x40C430 sub_40C430 —— 树结点分配+构造（0x30B，·sub_40C300）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_40C430(int nArg1, int nArg2, int nArg3, size_t *pArg4, char pszArg5)  // 函数 树结点分配+构造（0x30B，·sub_40C300）
{
  uint32_t *pMem; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  pMem = operator new(0x30u);
  v7[4] = pMem;
  v7[8] = (void *)1;
  v7[3] = pMem;
  if ( pMem != nullptr )  // 若 pMem 非空
    sub_40C300(pMem, nArg1, nArg2, nArg3, pArg4, pszArg5);  // 调 sub_40C300
  return pMem;
}



// ============================================================
// SECTION 0x40C4C0 — STL map/set 红黑树模板实例 + 字体位图缓存（invalid map/set iterator 诊断）
// ============================================================
// ------------------------------------------------------------
// 0x40C4C0 sub_40C4C0
// ------------------------------------------------------------
// 【解读】
//   std::map 红黑树模板实例（228 行）: "invalid map/set<T> iterator" 抛出 + 插入/重平衡 —— 调试控制台文本表的容器。
// ------------------------------------------------------------
int ***/*thiscall*/ sub_40C4C0(uint32_t *this, int ***uArg2, int **pDwArg3)  // 【STL map/set 红黑树模板实例 + 字体位图缓存（invalid map/s…】
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  void **v15; // eax
  uint32_t *pThis3; // ecx
  uint32_t *v17; // eax
  uint32_t *Block2; // eax
  int v19; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v22[20]; // [esp+34h] [ebp-34h] BYREF
  int v23; // [esp+48h] [ebp-20h]
  int v24; // [esp+4Ch] [ebp-1Ch]
  int v25; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v28; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 45) != 0 )
  {
    v24 = 15;
    v23 = 0;
    v22[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v28 = 0;
    sub_401740(pExceptionObject, (int)v22);  // 构造异常对象
    pExceptionObject[0] = &std::out_of_range::`vftable';  // 设 out_of_range vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛 out_of_range 异常
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_40BEA0(&pDwArg3);  // 调 sub_40BEA0
  if ( *((uint8_t *)*pDwArg32 + 45) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:  // LABEL_8（跳转目标）
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 45) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;  // v8+4 = v4
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else  // 否则分支
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 45) != 0 )
      {
        v9 = v6;
      }
      else  // 否则分支
      {
        v9 = (int *)sub_6600D0(v4);  // 调 红黑树最小结点（沿左子下行，哨兵位 +45）
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v25 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 45) != 0 )
        *(uint32_t *)(v10 + 8) = v6;  // v10+8 = v6
      else  // 否则分支
        *(uint32_t *)(v25 + 8) = sub_4429F0(v4);  // v25+8 = sub_4429F0(v4)
    }
    goto LABEL_35;  // 跳转 LABEL_35
  }
  if ( *((uint8_t *)pDwArg32[2] + 45) != 0 )
  {
    v4 = *pDwArg32;  // v4 = 解引用 pDwArg32
    goto LABEL_8;  // 跳转 LABEL_8
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;  // 跳转 LABEL_8
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else  // 否则分支
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 45) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;  // v12+4 = v5
  }
  else  // 否则分支
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;  // 写指针 = v5
    else  // 否则分支
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 44);
  *((uint8_t *)v5 + 44) = *((uint8_t *)pDwArg32 + 44);  // v5 偏移 44（字节）= *((uint8_t *)pDwArg32 + 44)
  *((uint8_t *)pDwArg32 + 44) = v14;
LABEL_35:  // LABEL_35（跳转目标）
  v15 = (void **)Block;
  if ( *((uint8_t *)Block + 44) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do  // do 循环体
      {
        if ( *((uint8_t *)v4 + 44) != 1 )
          break;  // 跳出 switch
        v17 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v17 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v17 + 44) == 0 )
          {
            *((uint8_t *)v17 + 44) = 1;  // v17 偏移 44（字节）= 1
            *((uint8_t *)v6 + 44) = 0;  // v6 偏移 44（字节）= 0
            sub_442AC0(v6);  // 调 sub_442AC0
            v17 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )
            goto LABEL_53;  // 跳转 LABEL_53
          if ( *(uint8_t *)(*v17 + 44) != 1 || *(uint8_t *)(v17[2] + 44) != 1 )
          {
            if ( *(uint8_t *)(v17[2] + 44) == 1 )
            {
              *(uint8_t *)(*v17 + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;  // v17 偏移 44（字节）= 0
              sub_433290(v17);  // 调 sub_433290
              v17 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);  // v17 偏移 44（字节）= *((uint8_t *)v6 + 44)
            *((uint8_t *)v6 + 44) = 1;  // v6 偏移 44（字节）= 1
            *(uint8_t *)(v17[2] + 44) = 1;
            sub_442AC0(v6);  // 调 sub_442AC0
            break;  // 跳出 switch
          }
        }
        else  // 否则分支
        {
          if ( *((uint8_t *)v17 + 44) == 0 )
          {
            *((uint8_t *)v17 + 44) = 1;  // v17 偏移 44（字节）= 1
            *((uint8_t *)v6 + 44) = 0;  // v6 偏移 44（字节）= 0
            sub_433290(v6);  // 调 sub_433290
            v17 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )
            goto LABEL_53;  // 跳转 LABEL_53
          if ( *(uint8_t *)(v17[2] + 44) != 1 || *(uint8_t *)(*v17 + 44) != 1 )
          {
            if ( *(uint8_t *)(*v17 + 44) == 1 )
            {
              *(uint8_t *)(v17[2] + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;  // v17 偏移 44（字节）= 0
              sub_442AC0(v17);  // 调 sub_442AC0
              v17 = (uint32_t *)*v6;
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);  // v17 偏移 44（字节）= *((uint8_t *)v6 + 44)
            *((uint8_t *)v6 + 44) = 1;  // v6 偏移 44（字节）= 1
            *(uint8_t *)(*v17 + 44) = 1;
            sub_433290(v6);  // 调 sub_433290
            break;  // 跳出 switch
          }
        }
        *((uint8_t *)v17 + 44) = 0;  // v17 偏移 44（字节）= 0
LABEL_53:  // LABEL_53（跳转目标）
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 44) = 1;  // v4 偏移 44（字节）= 1
  }
  if ( (unsigned int)v15[9] >= 0x10 )
    j__free(v15[4]);
  Block2 = Block;
  *((uint32_t *)Block + 9) = 15;
  Block2[8] = 0;
  *((uint8_t *)Block2 + 16) = 0;
  j__free(Block2);
  v19 = pThis[2];
  if ( v19 != 0 )  // 若 v19 != 0
    pThis[2] = v19 - 1;
  *uArg2 = pDwArg3;  // 写指针 = pDwArg3
  return uArg2;
}


// ------------------------------------------------------------
// 0x40C7A0 sub_40C7A0 —— out_of_range 异常构造（·sub_4018B0 拷贝 + 改挂 vftable）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40C7A0(uint32_t *this, size_t *pArg2)  // 函数 out_of_range 异常构造（·sub_4018B0 拷贝 + 改挂 vftable）
{
  sub_4018B0((int)this, pArg2);  // 调 sub_4018B0
  *this = &std::out_of_range::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x40C7C0 sub_40C7C0 —— 红黑树递归销毁（后序；元素析构 ·sub_5014C0）
// 哨兵位 +45；先 +8 子树递归，再析构并 free 本结点。
// ------------------------------------------------------------
char /*stdcall*/ sub_40C7C0(void **Block)  // 函数 红黑树递归销毁（后序；元素析构 ·sub_5014C0）
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 45);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_40C7C0(i[2]);  // 调 sub_40C7C0
    i = (void **)*i;  // i = 解引用跟踪 i
    sub_5014C0(Block2);  // 调 sub_5014C0
    j__free(Block2);
    result = *((uint8_t *)i + 45);
  }
  return result;
}



// ------------------------------------------------------------
// 0x40C810 sub_40C810
// ------------------------------------------------------------
// 【解读】
//   std::map 红黑树插入（114 行）: "map/set<T> too long" + sub_40C430 结点分配 —— MSVC _Tree::_Insert。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40C810(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, size_t *pArg5)
{
  uint32_t *fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  uint32_t *fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  uint32_t *fld_e15; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x7FFFFFE )
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // 调 sub_401740
    pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
  }
  fld_e1 = sub_40C430(*(this + 1), (int)pArg4, *(this + 1), pArg5, 0);  // 调 树结点分配+构造（0x30B，·sub_40C300）
  fld_e12 = (uint32_t *)*(this + 1);
  fld_e15 = fld_e1;
  ++*(this + 2);
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;  // 写指针 = fld_e1
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;  // 写指针 = fld_e1
  }
  else  // 否则分支
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // fld_e14 = this+1 字段
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // fld_e14+8 = fld_e1
  }
  v10 = fld_e1 + 1;
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 44) == 0 )
  {
    while ( 1 )  // 当 1 非 0 循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;  // v14 = 解引用 v13
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 44) != 0 )
        {
          if ( fld_e16 == (uint32_t *)v12[2] )
          {
            fld_e16 = (uint32_t *)*v10;
            sub_442AC0(*v10);  // 调 sub_442AC0
          }
          *(uint8_t *)(fld_e16[1] + 44) = 1;
          *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
          sub_433290(*(uint32_t *)(fld_e16[1] + 4));  // 调 sub_433290
          goto LABEL_21;  // 跳转 LABEL_21
        }
      }
      else if ( *(uint8_t *)(v14 + 44) != 0 )
      {
        if ( fld_e16 == (uint32_t *)*v12 )
        {
          fld_e16 = (uint32_t *)*v10;
          sub_433290(*v10);  // 调 sub_433290
        }
        *(uint8_t *)(fld_e16[1] + 44) = 1;
        *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
        sub_442AC0(*(uint32_t *)(fld_e16[1] + 4));  // 调 sub_442AC0
        goto LABEL_21;  // 跳转 LABEL_21
      }
      *(uint8_t *)(*v10 + 44) = 1;
      *(uint8_t *)(v14 + 44) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 44) = 0;
      fld_e16 = *(uint32_t **)(*v10 + 4);
LABEL_21:  // LABEL_21（跳转目标）
      v10 = fld_e16 + 1;
      if ( *(uint8_t *)(fld_e16[1] + 44) != 0 )
      {
        fld_e1 = fld_e15;
        break;  // 跳出 switch
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 44) = 1;
  *uArg2 = fld_e1;  // 写指针 = fld_e1
  return uArg2;
}



// ------------------------------------------------------------
// 0x40C9C0 sub_40C9C0 —— map 元素删除（先清 node+40 内层环链，再 ·sub_40C4C0 摘除）
// ------------------------------------------------------------
int ***/*thiscall*/ sub_40C9C0(uint32_t *this, int **pDwArg2)  // 函数 map 元素删除（先清 node+40 内层环链，再 ·sub_40C4C0 摘除）
{
  int ***result; // eax
  int **pDwArg22; // ecx
  bool fld_e3; // zf
  int *v6; // edi
  uint32_t ***v7; // ebx
  uint32_t **v8; // eax
  uint32_t **v9; // esi
  char v10[4]; // [esp+4h] [ebp-8h] BYREF
  uint32_t *pThis_2; // [esp+8h] [ebp-4h]

  pThis_2 = this + 2;
  result = (int ***)sub_5014F0(v10, pDwArg2 + 3);
  pDwArg22 = *result;  // pDwArg22 = 解引用 result
  fld_e3 = *result == (int **)*(this + 3);
  pDwArg2 = *result;  // pDwArg2 = 解引用 result
  if ( !fld_e3 )
  {
    v6 = pDwArg22[10];
    v7 = (uint32_t ***)v6[1];
    v8 = *v7;  // v8 = 解引用 v7
    if ( *v7 != v7 )
    {
      do  // do 循环体
      {
        v9 = (uint32_t **)*v8;  // v9 = 解引用跟踪 v8
        if ( v8 != (uint32_t **)v6[1] )
        {
          *v8[1] = v9;
          (*v8)[1] = v8[1];
          j__free(v8);
          pDwArg22 = pDwArg2;
          --v6[2];
        }
        v8 = v9;
      }
      while ( v9 != v7 );  // 当 v9 != v7 循环
    }
    return sub_40C4C0(pThis_2, &pDwArg2, pDwArg22);  // 【STL map/set 红黑树模板实例 + 字体位图缓存（invalid map/s…】
  }
  return result;
}



// ------------------------------------------------------------
// 0x40CA40 sub_40CA40 —— 红黑树插入定位（字符串键比较 → 命中或 ·sub_40C810 建结点）
// 返回 {iterator, inserted}：命中置 false，否则按比较位插左/右。
// ------------------------------------------------------------
int /*thiscall*/ sub_40CA40(int *this, int pArg2, size_t *pArg3)  // 函数 红黑树插入定位（字符串键比较 → 命中或 ·sub_40C810 建结点）
{
  int fld_e1; // ebx
  size_t *fld_e12; // esi
  char v5; // al
  size_t *pArg32; // edi
  size_t i; // esi
  unsigned int v8; // ecx
  const char *v9; // eax
  unsigned int v10; // edx
  const char *v11; // esi
  int nCmp; // eax
  bool v13; // sf
  unsigned int v14; // esi
  int v15; // eax
  size_t *fld_e122; // ebx
  const char *v18; // eax
  size_t *v19; // [esp+Ch] [ebp-14h]
  int *pThis; // [esp+18h] [ebp-8h]
  char v21; // [esp+1Ch] [ebp-4h]

  fld_e1 = *(uint32_t *)(*(this + 1) + 4);
  fld_e12 = (size_t *)*(this + 1);
  v5 = 1;
  pArg32 = pArg3;
  pThis = this;
  v21 = 1;
  if ( *(uint8_t *)(fld_e1 + 45) == 0 )
  {
    for ( i = pArg3[5]; ; i = pArg3[5] )
    {
      v8 = *(uint32_t *)(fld_e1 + 32);
      v19 = (size_t *)fld_e1;
      if ( *(uint32_t *)(fld_e1 + 36) < 0x10u )
        v9 = (const char *)(fld_e1 + 16);
      else  // 否则分支
        v9 = *(const char **)(fld_e1 + 16);
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )  // 若 v10 == 0
        goto LABEL_16;  // 跳转 LABEL_16
      if ( v10 < v8 )
        v8 = v10;
      v11 = pArg32[6] < 0x10 ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];  // v11 = pArg32[...]
      nCmp = memcmp(v11, v9, v8);
      v13 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )  // 若 nCmp == 0
      {
LABEL_16:  // LABEL_16（跳转目标）
        v14 = *(uint32_t *)(fld_e1 + 32);
        if ( v10 >= v14 )  // 若 v10 >= v14
          v15 = v10 != v14;
        else  // 否则分支
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      fld_e1 = v13 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);
      if ( *(uint8_t *)(fld_e1 + 45) != 0 )
        break;  // 跳出 switch
    }
    fld_e12 = v19;
    this = pThis;
  }
  fld_e122 = fld_e12;
  pArg3 = fld_e12;
  if ( v5 != 0 )  // 若 v5 != 0
  {
    if ( fld_e12 == *(size_t **)*(this + 1) )
    {
      *(uint32_t *)pArg2 = *sub_40C810(this, &pArg3, 1, fld_e12, pArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      return pArg2;
    }
    sub_501430(&pArg3);  // 调 sub_501430
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10 )
    v18 = (const char *)(pArg32 + 1);
  else  // 否则分支
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )  // 调 std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    *(uint32_t *)pArg2 = fld_e122;
    *(uint8_t *)(pArg2 + 4) = 0;
  }
  else  // 否则分支
  {
    *(uint32_t *)pArg2 = *sub_40C810(pThis, &pArg3, v21, fld_e12, pArg32);
    *(uint8_t *)(pArg2 + 4) = 1;
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x40CBA0 sub_40CBA0 —— map 区间删除（循环 ·sub_40C4C0；空区间整树清）
// ------------------------------------------------------------
int **/*thiscall*/ sub_40CBA0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)  // 函数 map 区间删除（循环 ·sub_40C4C0；空区间整树清）
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_40C7C0(*(void ***)(fld_e1 + 4));  // 调 sub_40C7C0
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);  // fld_e12 = this+1 字段
    *(this + 2) = nullptr;  // this+2 = 空指针
    *fld_e12 = fld_e12;  // 写指针 = fld_e12
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else  // 否则分支
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do  // do 循环体
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 45) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 45) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 45) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;  // 跳出 switch
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else  // 否则分支
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 45) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_40C4C0(this, (int ***)&pDwArg3, v10);  // 【STL map/set 红黑树模板实例 + 字体位图缓存（invalid map/s…】
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;  // 写指针 = pDwArg32
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x40CC60 sub_40CC60 —— 控制台记录池重建（168×0x34 槽 + 168×0xC 桶；树/文本清空）
// 每槽置 +41 槽号、+42=槽号/42 网格行、串清空（szPassword）；+40 有链路先经 ·sub_40C9C0 摘除；
// 末尾重置 this+8 处红黑树哨兵环并计数清零。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40CC60(int *this)  // 函数 控制台记录池重建（168×0x34 槽 + 168×0xC 桶；树/文本清空）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // ebx
  uint32_t *v4; // esi
  int v5; // esi
  int *pMem2; // eax
  int v7; // eax
  unsigned int v8; // ebx
  int fld_e5; // esi
  char v10; // al
  char *v11; // esi
  void **fld_e3; // edx
  uint32_t *pThis_2; // edi
  uint32_t *result; // eax
  char *Block; // [esp+Ch] [ebp-10h]

  sub_40C210(this);  // 调 sub_40C210
  *this = 168;  // 写指针 = 168
  pMem = operator new(0x2224u);
  v3 = nullptr;  // v3 = 空指针
  if ( pMem != nullptr )  // 若 pMem 非空
  {
    v4 = pMem + 1;
    *pMem = 168;  // 写指针 = 168
    `eh vector constructor iterator'(v2 + 1, 0x34u, 168, (void (/*thiscall*/ *)(void *))sub_40C1A0, sub_5014C0);  // 调 空串初始化（this+16 系）
  }
  else  // 否则分支
  {
    v4 = nullptr;  // v4 = 空指针
  }
  *(this + 5) = (int)v4;
  v5 = *this;  // v5 = 解引用 this
  v6 = (int *)operator new(12 * *this + 4);
  if ( v6 != nullptr )  // 若 v6 非空
  {
    v3 = v6 + 1;
    *v6 = v5;  // 写指针 = v5
    `eh vector constructor iterator'(
      pMem2 + 1,
      0xCu,
      v5,
      (void (/*thiscall*/ *)(void *))sub_40C1C0,  // 调 环形链表哨兵初始化（·sub_425940 分配 + 计数清零）
      (void (/*thiscall*/ *)(void *))sub_40C140);  // 调 桶结点销毁（·sub_6569D0 清首字段 + free 附属块 + 置空）
  }
  v7 = *this;  // v7 = 解引用 this
  *(this + 6) = (int)v3;
  v8 = 0;
  if ( v7 != 0 )  // 若 v7 != 0
  {
    Block = nullptr;  // Block = 0/空
    do  // do 循环体
    {
      fld_e5 = *(this + 5);  // fld_e5 = this+5 字段
      v10 = Block[fld_e5 + 40];
      v11 = &Block[fld_e5];
      if ( v10 != 0 )  // 若 v10 != 0
        sub_40C9C0(this, (int **)v11);  // 调 sub_40C9C0
      v11[40] = 0;
      v11[41] = v8;
      sub_4015C0((size_t *)v11 + 3, szPassword, 0);  // 【std::string构造赋值】
      *((uint16_t *)v11 + 22) = 0;
      *((uint32_t *)v11 + 12) = 0;  // v11 偏移 48 = 0
      v11[42] = v8 / 0x2A;
      ++v8;  // v8 自增
      Block += 52;  // Block 前进 52
    }
    while ( v8 < *this );
  }
  *(this + 1) = 0;  // this+1 清 0
  fld_e3 = *(void ***)(*(this + 3) + 4);
  pThis_2 = this + 2;
  sub_40C7C0(fld_e3);  // 调 sub_40C7C0
  *(uint32_t *)(pThis_2[1] + 4) = pThis_2[1];
  result = (uint32_t *)pThis_2[1];
  pThis_2[2] = 0;
  *result = result;  // 写指针 = result
  *(uint32_t *)(pThis_2[1] + 8) = pThis_2[1];
  return result;
}



// ------------------------------------------------------------
// 0x40CDC0 sub_40CDC0 —— 文本记录挂链（红黑树去重 ·sub_40CA40 + 12B 结点环链 + ·sub_40C270 计数）
// 槽由记录 +41 定位 this+24 槽表；未命中先建树，再 ·sub_40C0F0 结点插入桶环。
// ------------------------------------------------------------
void /*thiscall*/ sub_40CDC0(int *this, uint32_t *pArg2)  // 函数 文本记录挂链（红黑树去重 ·sub_40CA40 + 12B 结点环链 + ·sub_40C270 计数）
{
  uint32_t *pArg22; // edi
  size_t *v4; // ebx
  int v5; // eax
  uint32_t *fld_e6; // edi
  int v7; // ebx
  uint32_t *pArg23; // eax
  size_t v9; // [esp+8h] [ebp-34h] BYREF
  void *Block; // [esp+Ch] [ebp-30h]
  int v11; // [esp+1Ch] [ebp-20h]
  unsigned int v12; // [esp+20h] [ebp-1Ch]
  uint32_t *fld_e62; // [esp+24h] [ebp-18h]
  uint8_t v14[4]; // [esp+28h] [ebp-14h] BYREF
  uint8_t v15[4]; // [esp+2Ch] [ebp-10h] BYREF
  int v16; // [esp+38h] [ebp-4h]

  pArg22 = pArg2;
  if ( pArg2 != nullptr )  // 若 pArg2 非空
  {
    v4 = pArg2 + 3;
    v5 = *(uint32_t *)sub_5014F0(v15, pArg2 + 3);
    if ( v5 == *(this + 3) )
    {
      fld_e6 = (uint32_t *)(*(this + 6) + 12 * *((uint8_t *)pArg22 + 41));
      v12 = 15;
      v11 = 0;
      LOBYTE(Block) = 0;
      sub_4014D0(&v9, v4, 0, 0xFFFFFFFF);  // 调 sub_4014D0
      fld_e62 = fld_e6;
      v16 = 0;
      sub_40CA40(this + 2, (int)v14, &v9);  // 调 sub_40CA40
      v16 = -1;
      if ( v12 >= 0x10 )  // 若 v12 >= 0x10
        j__free(Block);  // free 堆对象
      v12 = 15;
      v11 = 0;
      LOBYTE(Block) = 0;
    }
    else  // 否则分支
    {
      fld_e6 = *(uint32_t **)(v5 + 40);
    }
    v7 = fld_e6[1];
    pArg2 = sub_40C0F0(v7, *(uint32_t *)(v7 + 4), &pArg2);  // 调 list 结点分配（12B：前驱/后继/数据）
    sub_40C270(fld_e6, 1u);  // 调 sub_40C270
    pArg23 = pArg2;
    *(uint32_t *)(v7 + 4) = pArg2;  // v7+4 = pArg2
    *(uint32_t *)pArg23[1] = pArg23;
    ++*(this + 1);
  }
}



// ------------------------------------------------------------
// 0x40CEC0 sub_40CEC0 —— 随机淘汰一槽（rand()%槽数 → ·sub_40C9C0 摘除；计数减一）
// 槽位 = 池基址 + 52×rand()%槽数；文本复位空串。
// ------------------------------------------------------------
int /*thiscall*/ sub_40CEC0(uint32_t *this)  // 函数 随机淘汰一槽（rand()%槽数 → ·sub_40C9C0 摘除；计数减一）
{
  unsigned int nRand; // edi
  int result; // eax

  nRand = *(this + 5) + 52 * ((unsigned int)rand() % *this);  // CRT 伪随机数（LCG 递推）
  sub_40C9C0(this, (int **)nRand);  // 调 sub_40C9C0
  *(uint8_t *)(nRand + 40) = 0;
  sub_4015C0((size_t *)(nRand + 12), szPassword, 0);  // 【std::string构造赋值】
  *(uint16_t *)(nRand + 44) = 0;
  *(uint32_t *)(nRand + 48) = 0;  // nRand+48 = 0
  result = *(this + 1) - 1;
  *(this + 1) = result;  // this+1 = result
  return result;
}



// ------------------------------------------------------------
// 0x40CF10 sub_40CF10 —— 桶结构全释放（·sub_40CBA0 区间清 + free 桶数组）
// ------------------------------------------------------------
int /*thiscall*/ sub_40CF10(int this)  // 函数 桶结构全释放（·sub_40CBA0 区间清 + free 桶数组）
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_40CBA0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));  // 调 sub_40CBA0
  j__free(*(void **)(this + 4));  // free this+4
  *(uint32_t *)(this + 4) = 0;  // this+4（uint32 槽）= 0
  *(uint32_t *)(this + 8) = 0;  // this+8（uint32 槽）= 0
  return 0;
}



// ------------------------------------------------------------
// 0x40CF50 sub_40CF50 —— 表全释放（·sub_40C210 + ·sub_40CBA0 + free）
// —— 与 ·sub_40CF10 同构（差异：作用区 this+8、带 -1 析构守卫）。
// ------------------------------------------------------------
void /*thiscall*/ sub_40CF50(int *this)  // 函数 表全释放（·sub_40C210 + ·sub_40CBA0 + free）
{
  int *pThis; // esi
  int *v2; // eax
  int *v3; // [esp-8h] [ebp-1Ch]
  int *pThis2; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  v5 = 0;
  sub_40C210(this);  // 调 sub_40C210
  v2 = (int *)pThis[3];
  pThis += 2;  // pThis 前进 2
  v3 = (int *)*v2;
  v5 = -1;
  sub_40CBA0((int ***)pThis, &pThis2, v3, v2);  // 调 sub_40CBA0
  j__free((void *)pThis[1]);
  pThis[1] = 0;
  pThis[2] = 0;
}



// ------------------------------------------------------------
// 0x40CFC0 sub_40CFC0 —— 空闲槽分配（满则 ·sub_40CEC0 淘汰；行号 12×(i%42)）
// 扫描 +40 标志找空槽；无则返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_40CFC0(uint32_t *this)  // 函数 空闲槽分配（满则 ·sub_40CEC0 淘汰；行号 12×(i%42)）
{
  unsigned int v2; // eax
  int i; // ecx
  unsigned int v5; // edx

  if ( *(this + 1) == *this - 1 )
    sub_40CEC0(this);  // 调 sub_40CEC0
  v2 = 0;
  if ( *this == 0 )
    return 0;
  for ( i = *(this + 5); *(uint8_t *)(i + 40) != 0; i += 52 )
  {
    if ( ++v2 >= *this )
      return 0;
  }
  v5 = v2 % 0x2A;
  *(uint16_t *)i = 0;
  *(uint16_t *)(i + 2) = 12 * v5;
  return i;
}



// ============================================================
// SECTION 0x40D020 — 调试控制台（_DEBUG：AllocConsole / MS UI Gothic / DIB 行缓冲 / FreeConsole）
// ============================================================
// ------------------------------------------------------------
// 0x40D020 sub_40D020 —— 控制台文本提交（复用/新建槽 → DIB 绘制 → 显示对象虚发 +132）
// 命中槽取其场域直绘；新槽经 ·sub_40CFC0 分配、·sub_40C040 写 DIB、逐扫描线虚发 +32
// 推 512 像素；宽由虚发 +16 测量，GetTickCount 记时，末 ·sub_40CDC0 挂表。
// ------------------------------------------------------------
uint16_t */*thiscall*/ sub_40D020(uint32_t *this, int nArg2, int nArg3, int nArg4, COLORREF color, CHAR *lpString, int nArg7)  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
{
  uint16_t *v8; // eax
  const CHAR *v9; // edx
  int v10; // ecx
  int v11; // esi
  int v12; // ebx
  const CHAR *v13; // ecx
  int v14; // edx
  int v15; // ecx
  uint16_t *result; // eax
  uint16_t *v17; // esi
  int *v18; // ecx
  int v19; // edx
  int v20; // eax
  int v21; // ecx
  bool v22; // cc
  int v23; // eax
  int pObj; // edi
  int nArg32; // [esp+Ch] [ebp-40h] BYREF
  int nArg42; // [esp+10h] [ebp-3Ch]
  uint16_t *v27; // [esp+14h] [ebp-38h]
  int v28; // [esp+18h] [ebp-34h]
  int v29; // [esp+1Ch] [ebp-30h] BYREF
  LPCSTR v30; // [esp+20h] [ebp-2Ch]
  int v31; // [esp+24h] [ebp-28h]
  int v32; // [esp+28h] [ebp-24h]
  int v33; // [esp+2Ch] [ebp-20h] BYREF
  const CHAR *v34; // [esp+30h] [ebp-1Ch]
  int v35; // [esp+34h] [ebp-18h]
  int v36; // [esp+38h] [ebp-14h]
  int v37; // [esp+3Ch] [ebp-10h]
  int v38; // [esp+40h] [ebp-Ch]
  int v39; // [esp+44h] [ebp-8h]
  int v40; // [esp+48h] [ebp-4h]
  LPCSTR lpStringa; // [esp+64h] [ebp+18h]

  v8 = (uint16_t *)sub_40C360(lpString);  // 调 文本→记录查找（红黑树命中返回 node+40 记录链句柄，未命中 0）
  if ( v8 != nullptr )  // 若 v8 非空
  {
    v9 = (const CHAR *)v8[1];
    v10 = v8[3];
    v11 = *v8;  // v11 = 解引用 v8
    ++v8[22];
    v12 = *((uint8_t *)v8 + 42);
    v13 = &v9[v10];
    lpStringa = v9;
    v14 = v11 + v8[2];
    v29 = v11;
    v30 = lpStringa;
    v31 = v14;
    v32 = (int)v13;  // v32 = 截断(v13)
    v15 = v8[3];
    result = (uint16_t *)(nArg3 + v8[2]);
    nArg32 = nArg3;
    nArg42 = nArg4;
    v27 = result;
    v28 = nArg4 + v15;
  }
  else  // 否则分支
  {
    result = (uint16_t *)sub_40CFC0(*(this + 4));  // 调 空闲槽分配（满则 ·sub_40CEC0 淘汰；行号 12×(i%42)）
    v17 = result;
    if ( result == nullptr )  // 若 result 为空
      return result;
    v12 = *((uint8_t *)result + 42);
    v33 = *result;  // v33 = 解引用 result
    v34 = (const CHAR *)result[1];
    v35 = *result + 512;
    v36 = result[1] + 12;
    v18 = (int *)*(this + v12 + 5);
    v19 = *v18;  // v19 = 解引用 v18
    v37 = v12;
    (*(void (/*thiscall*/ **)(int *))(v19 + 84))(v18);  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(uint32_t, int *, uint32_t))(*(uint32_t *)*(this + v12 + 5) + 24))(*(this + v12 + 5), &v33, 0);  // 调用虚函数/间接调用
    sub_40C040(lpString, color, 0);  // 调 sub_40C040
    v20 = 0;
    v38 = 0;
    do  // do 循环体
    {
      v21 = v20 << 10;
      v40 = 0;
      v39 = v20 << 10;
      do  // do 循环体
      {
        if ( *(uint16_t *)(v21 + *(this + 12)) != 1 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + v12 + 5) + 32))(
            *(this + v12 + 5),
            v40 + *v17,
            v20 + v17[1],
            -1);
          v21 = v39;
          v20 = v38;
          v12 = v37;
        }
        v21 += 2;  // v21 前进 2
        v22 = ++v40 < 512;
        v39 = v21;
      }
      while ( v22 );
      v38 = ++v20;
    }
    while ( v20 < 12 );  // 当 v20 < 12 循环
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + v12 + 5) + 88))(*(this + v12 + 5));  // 调用虚函数/间接调用
    v23 = (*(int (/*thiscall*/ **)(uint32_t *, CHAR *))(*this + 16))(this, lpString);
    v30 = v34;
    nArg32 = nArg3;
    v31 = v33 + v23;
    nArg42 = nArg4;
    v29 = v33;
    v27 = (uint16_t *)(nArg3 + v23);
    v32 = v36;
    v28 = nArg4 + v36 - (uint32_t)v34;
    v17[2] = v35 - v33;
    v17[3] = v36 - (uint16_t)v34;
    *((uint8_t *)v17 + 40) = 1;  // v17 偏移 40（字节）= 1
    *((uint32_t *)v17 + 2) = color;  // v17 偏移 8 = color
    sub_4015C0(lpString, strlen(lpString));  // 【std::string构造赋值】
    ++v17[22];
    *((uint32_t *)v17 + 12) = GetTickCount();  // v17 偏移 48 = GetTickCount()
    result = (uint16_t *)sub_40CDC0(v17);  // 调 文本记录挂链（红黑树去重 ·sub_40CA40 + 12B 结点环链 + ·sub_40C270 计数）
  }
  pObj = *(this + v12 + 5);
  if ( pObj != 0 )  // 若 pObj != 0
    return (uint16_t *)(*(int (/*thiscall*/ **)(int, int *, int *, int, uint32_t, COLORREF, int))(*(uint32_t *)pObj + 132))(
                                 pObj,
                                 &nArg32,
                                 &v29,
                                 nArg2,
                                 0,
                                 color,
                                 nArg7);
  return result;
}


// ------------------------------------------------------------
// 0x40D220 sub_40D220 —— 控制台容器骨架（·sub_433B80 哨兵 + ·sub_40CC60 池初始化）
// ------------------------------------------------------------
int */*thiscall*/ sub_40D220(int *this)  // 函数 控制台容器骨架（·sub_433B80 哨兵 + ·sub_40CC60 池初始化）
{
  int *pThis_2; // esi
  int pThis_22; // eax

  pThis_2 = this + 2;
  pThis_22 = sub_433B80(this + 2);  // 调 map 节点分配（0x30）
  pThis_2[1] = pThis_22;
  *(uint8_t *)(pThis_22 + 45) = 1;
  *(uint32_t *)(pThis_2[1] + 4) = pThis_2[1];
  *(uint32_t *)pThis_2[1] = pThis_2[1];
  *(uint32_t *)(pThis_2[1] + 8) = pThis_2[1];
  pThis_2[2] = 0;
  *(this + 5) = 0;  // this+5 清 0
  *(this + 6) = 0;  // this+6 清 0
  sub_40CC60(this);  // 调 sub_40CC60
  return this;
}



// ------------------------------------------------------------
// 0x40D290 sub_40D290 [串: "_DEBUG"]
// ------------------------------------------------------------
int /*thiscall*/ sub_40D290(char *this)
{
  void *pThis_4; // edi
  uint32_t *pThis_14; // edi
  int i; // ebx
  int result; // eax

  *(uint32_t *)this = &off_6C26EC;  // vftable = off_6C26EC
  SelectObject(*((HDC *)this + 10), *((HGDIOBJ *)this + 14));  // 调 SelectObject
  DeleteObject(*((HGDIOBJ *)this + 13));  // 调 DeleteObject
  DeleteObject(*((HGDIOBJ *)this + 11));  // 调 DeleteObject
  DeleteObject(*((HGDIOBJ *)this + 10));  // 调 DeleteObject
  pThis_4 = *((void **)this + 4);
  if ( pThis_4 != nullptr )  // 若 pThis_4 非空
  {
    sub_40CF50(*((int **)this + 4));  // 调 sub_40CF50
    j__free(pThis_4);
  }
  *((uint32_t *)this + 4) = 0;  // this 偏移 16 清 0
  pThis_14 = this + 20;
  for ( i = 4; i != 0; --i )
  {
    if ( *pThis_14 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_14)(*pThis_14, 1);
    *pThis_14++ = 0;
  }
  sub_416420(this);  // 调 sub_416420
  if ( _access("_DEBUG", 0) == 0 )
    FreeConsole();  // 调 FreeConsole
  *(uint32_t *)this = &off_6C25B8;  // vftable = off_6C25B8
  result = sub_416420(this);  // 调 复位（vt+36 + 状态位清 0）
  *(uint32_t *)this = &nengine::IObject::`vftable';  // vftable 复位 IObject
  *(this + 4) = 0;  // this+4 清 0
  return result;
}



// ------------------------------------------------------------
// 0x40D380 sub_40D380 —— 控制台描边字（12 邻位偏移重绘 + 可选斜角 + 本体）
// a6!=0：八邻 + 四向 ±2 共 12 次 ·sub_40D020；a7!=0 再补 (1,1) 斜角；最后中心本体。
// ------------------------------------------------------------
void /*thiscall*/ sub_40D380(  // 调 控制台描边字（12 邻位偏移重绘 + 可选斜角 + 本体）
        int **this,
        int a2,
        int a3,
        int a4,
        COLORREF a5,
        char a6,
        char a7,
        COLORREF color,
        COLORREF a9,
        int a10,
        int a11,
        char *lpString)  // 函数 控制台描边字（12 邻位偏移重绘 + 可选斜角 + 本体）
{
  if ( a6 != 0 )  // 若 a6 != 0
  {
    sub_40D020(this, a2, a3 - 1, a4 - 1, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3, a4 - 1, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3 + 1, a4 - 1, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3 - 1, a4, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3 + 1, a4, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3 - 1, a4 + 1, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3, a4 + 1, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3 + 1, a4 + 1, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3 + 2, a4, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3 - 2, a4, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3, a4 + 2, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
    sub_40D020(this, a2, a3, a4 - 2, color, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
  }
  if ( a7 != 0 )  // 若 a7 != 0
    sub_40D020(this, a2, a3 + 1, a4 + 1, a9, lpString, 1);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
  sub_40D020(this, a2, a3, a4, a5, lpString, 0);  // 【调试控制台（_DEBUG：AllocConsole / MS UI Gothic /…】
}



// ------------------------------------------------------------
// 0x40D510 sub_40D510
// ------------------------------------------------------------
// 【解读】
//   ★ 调试控制台初始化（_DEBUG）: AllocConsole + "\n<Start Console Log>...\n\n" +
//     sub_40BE20 输出 + CreateFontA("MS UI Gothic") + sub_40BF80 CreateDIBSection 行缓冲。
// ------------------------------------------------------------
int /*thiscall*/ sub_40D510(int this, int nArg2, int nArg3, void *Block)
{
  DWORD v5; // ecx
  HFONT FontA; // eax
  int *pMem; // eax
  HDC fld_28; // [esp-Ch] [ebp-24h]

  sub_40B530((uint8_t *)this, nArg3, (int)Block);  // 调 sub_40B530
  *(uint32_t *)this = &off_6C26EC;  // vftable = off_6C26EC
  if ( _access("_DEBUG", 0) == 0 )
  {
    AllocConsole();  // 调 AllocConsole
    sub_40BE20(v5, "\n<Start Console Log>...\n\n");  // 调 sub_40BE20
  }
  *(uint32_t *)(this + 36) = nArg2;  // this+36 = 参数2
  *(uint32_t *)(this + 60) = 512;  // this+60（uint32 槽）= 512
  *(uint32_t *)(this + 64) = 12;  // this+64（uint32 槽）= 12
  *(uint32_t *)(this + 68) = 12;  // this+68（uint32 槽）= 12
  *(uint32_t *)(this + 20) = 0;  // this+20（uint32 槽）= 0
  *(uint32_t *)(this + 24) = 0;  // this+24（uint32 槽）= 0
  *(uint32_t *)(this + 28) = 0;  // this+28（uint32 槽）= 0
  *(uint32_t *)(this + 32) = 0;  // this+32（uint32 槽）= 0
  *(uint32_t *)(this + 48) = 0;  // this+48（uint32 槽）= 0
  *(uint32_t *)(this + 16) = 0;  // this+16（uint32 槽）= 0
  *(uint32_t *)(this + 76) = 0;  // this+76（uint32 槽）= 0
  *(uint16_t *)(this + 72) = 0;
  memset((void *)(this + 80), 0, 0x50u);  // 调 memset
  sub_40BF80(this);  // 调 sub_40BF80
  FontA = CreateFontA(*(uint32_t *)(this + 68), 0, 0, 0, 100, 0, 0, 0, 0x80u, 0, 0, 0, 0, "MS UI Gothic");
  fld_28 = *(HDC *)(this + 40);
  *(uint32_t *)(this + 52) = FontA;  // this+52 = FontA
  *(uint32_t *)(this + 56) = SelectObject(fld_28, FontA);  // this+56 = SelectObject(fld_28, FontA)
  pMem = (int *)operator new(0x1Cu);
  if ( pMem != nullptr )  // 若 pMem 非空
    *(uint32_t *)(this + 16) = sub_40D220(pMem);  // this+16 = sub_40D220(pMem)
  else  // 否则分支
    *(uint32_t *)(this + 16) = 0;  // this+16（uint32 槽）= 0
  return this;
}



// ------------------------------------------------------------
// 0x40D630 sub_40D630 —— 删除壳（·sub_40D290 析构 + 低位 free）
// ------------------------------------------------------------
char */*thiscall*/ sub_40D630(char *Block, char pszArg2)  // 函数 删除壳（·sub_40D290 析构 + 低位 free）
{
  sub_40D290(Block);  // 调 sub_40D290
  if ( (pszArg2 & 1) != 0 )  // scalar deleting 位 0 置位（是否 free）
    j__free(Block);  // free 堆对象
  return Block;
}



// ============================================================
// SECTION 0x40D660 — 大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）
// ============================================================
// ------------------------------------------------------------
// 0x40D660 sub_40D660 —— 文件名大小写归一（tolower；高位前导字节跳过；4096 上限）
// ------------------------------------------------------------
char /*cdecl*/ sub_40D660(int nArg1)  // 【大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）】
{
  int i; // esi
  char result; // al

  for ( i = 0; i < 4096; ++i )
  {
    result = *(uint8_t *)(i + nArg1);
    if ( result == 0 )  // 若 result == 0
      break;  // 跳出 switch
    if ( result >= 0 )  // 若 result >= 0
    {
      result = tolower(result);
      *(uint8_t *)(i + nArg1) = result;
    }
    else  // 否则分支
    {
      ++i;  // i 自增
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D6A0 sub_40D6A0 —— 子树最右（最大键）定位
// 沿 +8 子链下沉至哨兵前。【推断: _Tree 最值辅助】
// ------------------------------------------------------------
int /*cdecl*/ sub_40D6A0(int pArg1)  // 函数 子树最右（最大键）定位
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 77) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x40D6C0 sub_40D6C0 —— 子树最左（最小键）定位
// —— 与 ·sub_40D6A0 对称（沿 +0 子链）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_40D6C0(uint32_t *pArg1)  // 函数 子树最左（最小键）定位
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 77) == 0 )
  {
    do  // do 循环体
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 77) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D6E0 sub_40D6E0 —— 红黑树左旋（右子提升；+77 系）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40D6E0(uint32_t *this, int pArg2)  // 函数 红黑树左旋（右子提升；+77 系）
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;  // pArg2+8 = *result
  if ( *(uint8_t *)(*result + 77) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);
  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1+4 = result
    *result = pArg2;  // 写指针 = pArg2
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4 = result
  }
  else  // 否则分支
  {
    v4 = *(uint32_t **)(pArg2 + 4);
    if ( pArg2 == *v4 )
      *v4 = result;  // 写指针 = result
    else  // 否则分支
      v4[2] = result;
    *result = pArg2;  // 写指针 = pArg2
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4 = result
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D740 sub_40D740 —— 红黑树右旋（左子提升）
// —— 与 ·sub_40D6E0 对称。
// ------------------------------------------------------------
int /*thiscall*/ sub_40D740(uint32_t *this, uint32_t *pArg2)  // 函数 红黑树右旋（左子提升）
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;  // result = 解引用 pArg2
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 77) == 0 )
    *(uint32_t *)(v3 + 4) = pArg2;  // v3+4 = pArg2
  *(uint32_t *)(result + 4) = pArg2[1];  // result+4 = pArg2[1]
  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1+4 = result
    *(uint32_t *)(result + 8) = pArg2;  // result+8 = pArg2
    pArg2[1] = result;
  }
  else  // 否则分支
  {
    v5 = (uint32_t *)pArg2[1];
    if ( pArg2 == (uint32_t *)v5[2] )
      v5[2] = result;
    else  // 否则分支
      *v5 = result;  // 写指针 = result
    *(uint32_t *)(result + 8) = pArg2;  // result+8 = pArg2
    pArg2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D7A0 sub_40D7A0 —— 红黑树迭代器自减（前驱；哨兵位 +77）
// ------------------------------------------------------------
int /*thiscall*/ sub_40D7A0(void *this)  // 函数 红黑树迭代器自减（前驱；哨兵位 +77）
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 77) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else  // 否则分支
  {
    v3 = *v1;  // v3 = 解引用 v1
    if ( *(uint8_t *)(*v1 + 77) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 77) == 0 )
      {
        do  // do 循环体
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;  // 跳出 switch
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 77) == 0 );
        if ( *(uint8_t *)(result + 77) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else  // 否则分支
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 77) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D800 sub_40D800 —— 红黑树迭代器自增（后继）
// —— 与 ·sub_40BEA0 同构（差异：哨兵位 77 与 45）。
// ------------------------------------------------------------
int */*thiscall*/ sub_40D800(int *this)  // 函数 红黑树迭代器自增（后继）
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 77) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 77) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 77) == 0; result = (int *)result[1] )
      {
        if ( *this != result[2] )
          break;  // 跳出 switch
        *this = (int)result;
      }
      *this = (int)result;
    }
    else  // 否则分支
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 77) == 0 )
      {
        do  // do 循环体
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 77) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D860 sub_40D860 —— 树头结点分配（0x50B；+76=1 / +77 由调用者置哨兵）
// 前三字段清零后返回。
// ------------------------------------------------------------
uint32_t *sub_40D860()  // 函数 树头结点分配（0x50B；+76=1 / +77 由调用者置哨兵）
{
  uint32_t *result; // eax

  result = operator new(0x50u);
  if ( result != nullptr )  // 若 result 非空
    *result = 0;  // 写指针 = 0
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 76) = 1;
  *((uint8_t *)result + 77) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40D8A0 sub_40D8A0 —— 包文件流全关闭（环链逐结点 fclose(node+8)）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40D8A0(uint32_t *this)  // 函数 包文件流全关闭（环链逐结点 fclose(node+8)）
{
  uint32_t *result; // eax
  uint32_t *v3; // esi

  result = (uint32_t *)*(this + 1);
  v3 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do  // do 循环体
    {
      result = (uint32_t *)v3[2];
      if ( result != nullptr )  // 若 result 非空
      {
        result = (uint32_t *)fclose((FILE *)v3[2]);
        v3[2] = 0;
      }
      v3 = (uint32_t *)*v3;
    }
    while ( v3 != (uint32_t *)*(this + 1) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D8E0 sub_40D8E0 —— 红黑树下界查找（lower_bound；字符串键 memcmp 下降）
// 未命中返回哨兵；供 ·sub_40DA70 复用。【推断: MSVC _Lower_bound 形】
// ------------------------------------------------------------
int */*thiscall*/ sub_40D8E0(int **this, int pArg2)  // 函数 红黑树下界查找（lower_bound；字符串键 memcmp 下降）
{
  int *fld_e1; // ecx
  int *v3; // eax
  unsigned int v4; // edx
  unsigned int v5; // esi
  const char **v6; // ecx
  const char *v7; // edi
  unsigned int v8; // ebx
  int v9; // ecx
  const char *v10; // esi
  int nCmp; // edx
  bool v12; // sf
  unsigned int v14; // [esp+0h] [ebp-Ch]
  const char **i; // [esp+4h] [ebp-8h]
  int *fld_e12; // [esp+8h] [ebp-4h]
  unsigned int v17; // [esp+14h] [ebp+8h]

  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  v3 = (int *)fld_e1[1];
  fld_e12 = fld_e1;
  if ( *((uint8_t *)v3 + 77) == 0 )
  {
    v4 = *(uint32_t *)(pArg2 + 24);
    v5 = *(uint32_t *)(pArg2 + 20);
    v6 = (const char **)(pArg2 + 4);
    v17 = v5;
    v14 = v4;
    for ( i = v6; ; v6 = i )
    {
      if ( v14 < 0x10 )
        v7 = (const char *)v6;
      else  // 否则分支
        v7 = *v6;  // v7 = 解引用 v6
      v8 = v3[8];
      if ( v8 == 0 )  // 若 v8 == 0
        goto LABEL_14;  // 跳转 LABEL_14
      v9 = v3[8];
      if ( v8 >= v5 )  // 若 v8 >= v5
        v9 = v5;
      v10 = (unsigned int)v3[9] < 0x10 ? (const char *)(v3 + 4) : (const char *)v3[4];
      nCmp = memcmp(v10, v7, v9);
      v12 = nCmp < 0;
      v5 = v17;
      if ( nCmp == 0 )  // 若 nCmp == 0
      {
LABEL_14:  // LABEL_14（跳转目标）
        if ( v8 < v5 )
          goto LABEL_17;  // 跳转 LABEL_17
        v12 = false;
      }
      if ( v12 )
      {
LABEL_17:  // LABEL_17（跳转目标）
        v3 = (int *)v3[2];
        goto LABEL_19;  // 跳转 LABEL_19
      }
      fld_e12 = v3;
      v3 = (int *)*v3;
LABEL_19:  // LABEL_19（跳转目标）
      if ( *((uint8_t *)v3 + 77) != 0 )
        return fld_e12;
    }
  }
  return fld_e1;
}



// ------------------------------------------------------------
// 0x40D9A0 sub_40D9A0 —— 单字段串析构（this+12 起；容量 ≥16 才 free）
// ------------------------------------------------------------
int /*thiscall*/ sub_40D9A0(int this)  // 函数 单字段串析构（this+12 起；容量 ≥16 才 free）
{
  if ( *(uint32_t *)(this + 32) >= 0x10u )
    j__free(*(void **)(this + 12));  // free this+12
  *(uint32_t *)(this + 32) = 15;  // this+32（uint32 槽）= 15
  *(uint32_t *)(this + 28) = 0;  // this+28（uint32 槽）= 0
  *(uint8_t *)(this + 12) = 0;  // this 偏移 12 清 0
  return 0;
}



// ------------------------------------------------------------
// 0x40D9D0 sub_40D9D0 —— 双字段串析构（this+40 与 this+4）
// ------------------------------------------------------------
void /*thiscall*/ sub_40D9D0(int this)  // 函数 双字段串析构（this+40 与 this+4）
{
  if ( *(uint32_t *)(this + 60) >= 0x10u )
    j__free(*(void **)(this + 40));  // free this+40
  *(uint32_t *)(this + 60) = 15;  // this+60（uint32 槽）= 15
  *(uint32_t *)(this + 56) = 0;  // this+56（uint32 槽）= 0
  *(uint8_t *)(this + 40) = 0;  // this 偏移 40 清 0
  if ( *(uint32_t *)(this + 24) >= 0x10u )
    j__free(*(void **)(this + 4));  // free this+4
  *(uint32_t *)(this + 20) = 0;  // this+20（uint32 槽）= 0
  *(uint32_t *)(this + 24) = 15;  // this+24（uint32 槽）= 15
  *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
}



// ------------------------------------------------------------
// 0x40DA20 sub_40DA20 —— 双字段串析构（this+52 与 this+16）
// —— 与 ·sub_40D9D0 同构（差异：偏移对 52/16）。
// ------------------------------------------------------------
void /*thiscall*/ sub_40DA20(int this)  // 函数 双字段串析构（this+52 与 this+16）
{
  if ( *(uint32_t *)(this + 72) >= 0x10u )
    j__free(*(void **)(this + 52));  // free this+52
  *(uint32_t *)(this + 72) = 15;  // this+72（uint32 槽）= 15
  *(uint32_t *)(this + 68) = 0;  // this+68（uint32 槽）= 0
  *(uint8_t *)(this + 52) = 0;  // this 偏移 52 清 0
  if ( *(uint32_t *)(this + 36) >= 0x10u )
    j__free(*(void **)(this + 16));  // free this+16
  *(uint32_t *)(this + 32) = 0;  // this+32（uint32 槽）= 0
  *(uint32_t *)(this + 36) = 15;  // this+36（uint32 槽）= 15
  *(uint8_t *)(this + 16) = 0;  // this 偏移 16 清 0
}



// ------------------------------------------------------------
// 0x40DA70 sub_40DA70 —— map 查找（·sub_40D8E0 下界 + ·sub_40BF00 等值判定）
// ------------------------------------------------------------
int **/*thiscall*/ sub_40DA70(int **this, int **pDwArg2, unsigned int *pDwArg3)  // 函数 map 查找（·sub_40D8E0 下界 + ·sub_40BF00 等值判定）
{
  int *v5; // eax
  unsigned int v6; // ecx
  const char *v7; // eax
  int *v9; // [esp+18h] [ebp+Ch]

  v5 = sub_40D8E0(this, (int)pDwArg3);  // 调 红黑树下界查找（lower_bound；字符串键 memcmp 下降）
  v9 = v5;
  if ( v5 == *(this + 1)
    || ((v6 = v5[8], (unsigned int)v5[9] < 0x10) ? (v7 = (const char *)(v5 + 4)) : (v7 = (const char *)v5[4]),
        sub_40BF00((std::_String_base *)pDwArg3, 0, pDwArg3[5], v7, v6) < 0) )  // 调 std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    *pDwArg2 = *(this + 1);
    return pDwArg2;
  }
  else  // 否则分支
  {
    *pDwArg2 = v9;  // 写指针 = v9
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x40DAE0 sub_40DAE0 —— 包条目值构造（双串 + 尺寸字段）
// 串一自 pArg2、串二自 pArg2+9；+28/+32 取 pArg2[7]/[8]。
// ------------------------------------------------------------
int /*thiscall*/ sub_40DAE0(int this, size_t *pArg2)  // 函数 包条目值构造（双串 + 尺寸字段）
{
  *(uint32_t *)(this + 24) = 15;  // this+24（uint32 槽）= 15
  *(uint32_t *)(this + 20) = 0;  // this+20（uint32 槽）= 0
  *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
  sub_4014D0((size_t *)this, pArg2, 0, 0xFFFFFFFF);  // 调 sub_4014D0
  *(uint32_t *)(this + 28) = pArg2[7];  // this+28 = pArg2[7]
  *(uint32_t *)(this + 32) = pArg2[8];  // this+32 = pArg2[8]
  *(uint32_t *)(this + 60) = 15;  // this+60（uint32 槽）= 15
  *(uint32_t *)(this + 56) = 0;  // this+56（uint32 槽）= 0
  *(uint8_t *)(this + 40) = 0;  // this 偏移 40 清 0
  sub_4014D0((size_t *)(this + 36), pArg2 + 9, 0, 0xFFFFFFFF);  // 调 sub_4014D0
  return this;
}



// ------------------------------------------------------------
// 0x40DB60 sub_40DB60 —— NPK 条目构造（文件名串 + 大小串）
// —— 与 ·sub_40DAE0 同构（差异：尺寸取自独立参数 pArg3 结构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40DB60(int this, size_t *pArg2, uint32_t *pArg3)  // 【NPK条目构造】
{
  *(uint32_t *)(this + 24) = 15;  // this+24（uint32 槽）= 15
  *(uint32_t *)(this + 20) = 0;  // this+20（uint32 槽）= 0
  *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
  sub_4014D0((size_t *)this, pArg2, 0, 0xFFFFFFFF);  // 调 sub_4014D0
  *(uint32_t *)(this + 28) = *pArg3;  // this+28 = *pArg3
  *(uint32_t *)(this + 32) = pArg3[1];  // this+32 = pArg3[1]
  *(uint32_t *)(this + 60) = 15;  // this+60（uint32 槽）= 15
  *(uint32_t *)(this + 56) = 0;  // this+56（uint32 槽）= 0
  *(uint8_t *)(this + 40) = 0;  // this 偏移 40 清 0
  sub_4014D0((size_t *)(this + 36), pArg3 + 2, 0, 0xFFFFFFFF);  // 调 sub_4014D0
  return this;
}



// ------------------------------------------------------------
// 0x40DBE0 sub_40DBE0 [串: "list<T> too long"]
// ------------------------------------------------------------
int /*thiscall*/ sub_40DBE0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // fld_e2 = this+2 字段
  if ( 97612893 - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // 调 sub_401740
    pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+2 = result
  return result;
}



// ------------------------------------------------------------
// 0x40DC70 sub_40DC70 —— 按名查包内条目（归一化名 → ·sub_40DA70；命中返回 node+40 记录）
// 名先拷入 1024B 栈缓冲转小写；未命中返回 0。
// ------------------------------------------------------------
int */*thiscall*/ sub_40DC70(int **this, char *pszArg2)  // 函数 按名查包内条目（归一化名 → ·sub_40DA70；命中返回 node+40 记录）
{
  char *pszArg22; // eax
  char *v4; // edx
  char v5; // cl
  int *v6; // esi
  unsigned int v8; // [esp+8h] [ebp-42Ch] BYREF
  void *Block; // [esp+Ch] [ebp-428h]
  int v10; // [esp+1Ch] [ebp-418h]
  unsigned int v11; // [esp+20h] [ebp-414h]
  char Src[1024]; // [esp+24h] [ebp-410h] BYREF
  int dword_796E502; // [esp+424h] [ebp-10h]
  int v14; // [esp+430h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 栈检 cookie
  pszArg22 = pszArg2;
  v4 = (char *)(Src - pszArg2);  // v4 = 目标-源 偏移
  do  // do 循环体
  {  // 逐字符复制
    v5 = *pszArg22;  // v5 = 解引用 pszArg22
    pszArg22[(uint32_t)v4] = *pszArg22;  // 写目标
    ++pszArg22;  // 源 ++
  }
  while ( v5 != 0 );  // 当 v5 != 0 循环
  sub_40D660((int)Src);  // 【大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）】
  v11 = 15;
  v10 = 0;
  LOBYTE(Block) = 0;  // Block 清 0
  sub_4015C0(&v8, Src, strlen(Src));  // 【std::string构造赋值】
  v14 = 0;
  v6 = *sub_40DA70(this, (int **)&pszArg2, &v8);  // sub_40DA70 红黑树按键查找
  if ( v11 >= 0x10 )  // 若 v11 >= 0x10
    j__free(Block);  // free 堆对象
  if ( v6 == *(this + 1) )  // 未命中
    return nullptr;
  else  // 否则分支
    return v6 + 10;  // 返回命中结点 +10
}



// ------------------------------------------------------------
// 0x40DD60 sub_40DD60
// ------------------------------------------------------------
// 【解读】
//   NPK 内文件查找（磁盘名→索引）: tolower 归一 + sub_40DC70 红黑树匹配 + fseek 定位。
// ------------------------------------------------------------
int /*thiscall*/ sub_40DD60(int ***this, int pArg2, int *pDwArg3, uint32_t *uArg4, char *pszArg5)
{
  signed int i; // eax
  int **fld_e1; // eax
  int *v8; // esi
  int *pFile4; // edi
  FILE *pFile; // eax
  FILE **pFile2; // ebx
  const char *v13; // eax
  FILE *pFile5; // eax
  FILE *v15; // esi
  size_t *pFile3; // [esp+28h] [ebp+14h]

  for ( i = strlen(pszArg5) - 1; i >= 0; --i )  // 从尾到头扫描路径
  {
    if ( pszArg5[i] == 92 )  // 反斜杠 \ 字符
      pszArg5[i] = 47;
  }
  sub_40D660((int)pszArg5);  // 【大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）】
  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  v8 = *fld_e1;  // v8 = 解引用 fld_e1
  if ( *fld_e1 == (int *)fld_e1 )  // 树空
    goto LABEL_8;  // 跳转 LABEL_8
  while ( 1 )  // 当 1 非 0 循环
  {
    pFile4 = sub_40DC70((int **)v8 + 10, pszArg5);  // sub_40DC70 按名匹配
    if ( pFile4 != nullptr )  // 若 pFile4 非空
      break;  // 跳出 switch
    v8 = (int *)*v8;  // v8 = 下一结点
    if ( v8 == (int *)*(this + 1) )  // 回到头部
      goto LABEL_8;  // 跳转 LABEL_8
  }
  pFile = (FILE *)v8[2];
  pFile2 = (FILE **)(v8 + 2);  // pFile2 = 包流槽地址
  *pDwArg3 = *pFile4;  // *pDwArg3 = 数据偏移
  *uArg4 = pFile4[1];  // *uArg4 = 数据大小
  if ( pFile != nullptr )  // 若 pFile 非空
  {
    fseek(pFile, *pFile4, 0);  // 调 fseek
    *(uint32_t *)(pArg2 + 24) = 15;  // pArg2+24 = 15
    *(uint32_t *)(pArg2 + 20) = 0;  // pArg2+20 = 0
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4 清 0
    sub_4014D0((size_t *)pArg2, (size_t *)v8 + 3, 0, 0xFFFFFFFF);  // 调 sub_4014D0
    return pArg2;
  }
  if ( v8 == (int *)-8  // v8 == -8（异常防护）
    || ((pFile3 = (size_t *)(v8 + 3), (unsigned int)v8[9] < 0x10)  // pFile3 = 串体
      ? (v13 = (const char *)(v8 + 4))
      : (v13 = (const char *)v8[4]),
        pFile5 = fopen(v13, "rb"),  // fopen 打开包文件
        v15 = pFile5,
        pFile5 == nullptr) )  // 打开失败
  {
LABEL_8:  // LABEL_8（跳转目标）
    *(uint32_t *)(pArg2 + 24) = 15;  // pArg2+24 = 15
    *(uint32_t *)(pArg2 + 20) = 0;  // pArg2+20 = 0
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4 清 0
    sub_4015C0((size_t *)pArg2, szPassword, 0);  // 【std::string构造赋值】
    return pArg2;
  }
  fseek(pFile5, *pFile4, 0);  // 调 fseek
  *pFile2 = v15;  // 写指针 = v15
  *(uint32_t *)(pArg2 + 24) = 15;  // pArg2+24 = 15
  *(uint32_t *)(pArg2 + 20) = 0;  // pArg2+20 = 0
  *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4 清 0
  sub_4014D0((size_t *)pArg2, pFile3, 0, 0xFFFFFFFF);  // 调 sub_4014D0
  return pArg2;
}



// ------------------------------------------------------------
// 0x40DED0 sub_40DED0
// ------------------------------------------------------------
// 【解读】
//   NPK 内文件查找（包态，返回文件长度）: 同上 + fopen 包流。
// ------------------------------------------------------------
FILE */*thiscall*/ sub_40DED0(int ***this, int *pDwArg2, uint32_t *uArg3, char *pszArg4)  // 【NPK缓存查找】
{
  signed int i; // eax
  int **fld_e1; // eax
  int *v7; // esi
  int *pFile5; // eax
  int *pFile4; // edi
  FILE *pFile; // ebx
  FILE **pFile2; // esi
  const char *v13; // eax
  FILE *pFile3; // ebx

  for ( i = strlen(pszArg4) - 1; i >= 0; --i )  // CRT 字符串长度（逐字节扫描到 NUL）
  {
    if ( pszArg4[i] == 92 )
      pszArg4[i] = 47;
  }
  sub_40D660((int)pszArg4);  // 【大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）】
  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  v7 = *fld_e1;  // v7 = 解引用 fld_e1
  if ( *fld_e1 == (int *)fld_e1 )
    return nullptr;
  while ( 1 )  // 当 1 非 0 循环
  {
    pFile5 = sub_40DC70((int **)v7 + 10, pszArg4);  // 调 按名查包内条目（归一化名 → ·sub_40DA70；命中返回 node+40 记录）
    pFile4 = pFile5;
    if ( pFile5 != nullptr )  // 若 pFile5 非空
      break;  // 跳出 switch
    v7 = (int *)*v7;
    if ( v7 == (int *)*(this + 1) )
      return nullptr;
  }
  pFile = (FILE *)v7[2];
  pFile2 = (FILE **)(v7 + 2);
  *pDwArg2 = *pFile5;
  *uArg3 = pFile5[1];
  if ( pFile != nullptr )  // 若 pFile 非空
  {
    fseek(pFile, *pFile5, 0);  // 调 fseek
    return pFile;
  }
  if ( pFile2 == nullptr )  // 若 pFile2 为空
    return nullptr;
  v13 = (unsigned int)pFile2[7] < 0x10 ? (const char *)(pFile2 + 2) : (const char *)pFile2[2];
  pFile3 = fopen(v13, "rb");
  if ( pFile3 == nullptr )  // 若 pFile3 为空
    return nullptr;
  fseek(pFile3, *pFile4, 0);  // 调 fseek
  *pFile2 = pFile3;  // 写指针 = pFile3
  return pFile3;
}



// ------------------------------------------------------------
// 0x40DFB0 sub_40DFB0 —— 包索引树结点分配（0x50B：偏移/长度/序号 + ·sub_40DAE0 值）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_40DFB0(int nArg1, int nArg2, int nArg3, size_t *pArg4, char pszArg5)  // 函数 包索引树结点分配（0x50B：偏移/长度/序号 + ·sub_40DAE0 值）
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  pMem = operator new(0x50u);
  pMem2 = pMem;
  v8[4] = pMem;
  v8[8] = (void *)1;
  v8[3] = pMem;
  if ( pMem != nullptr )  // 若 pMem 非空
  {
    *pMem = nArg1;  // 写指针 = nArg1
    pMem[1] = nArg2;
    pMem[2] = nArg3;
    sub_40DAE0((int)(pMem + 3), pArg4);  // 调 sub_40DAE0
    *((uint8_t *)pMem2 + 76) = pszArg5;
    *((uint8_t *)pMem2 + 77) = 0;
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x40E050 sub_40E050 [串: "invalid map/set<T> iterator"]
// ------------------------------------------------------------
int **/*thiscall*/ sub_40E050(uint32_t *this, int **pDwArg2, int *Block)
{
  int *Block2; // edi
  char v4; // al
  int v5; // ebx
  int *Block3; // eax
  int v7; // esi
  uint32_t *pThis2; // ecx
  int v9; // eax
  uint32_t *v10; // eax
  int v11; // eax
  int v12; // ecx
  int **Block32; // ecx
  char v14; // cl
  uint8_t *pObj; // eax
  bool v16; // zf
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-54h] BYREF
  size_t v20; // [esp+34h] [ebp-2Ch] BYREF
  char v21; // [esp+38h] [ebp-28h]
  int v22; // [esp+48h] [ebp-18h]
  int v23; // [esp+4Ch] [ebp-14h]
  uint32_t *pThis; // [esp+50h] [ebp-10h]
  int v25; // [esp+5Ch] [ebp-4h]

  Block2 = Block;
  v4 = *((uint8_t *)Block + 77);  // v4 = 结点+77（nil 标志）
  pThis = this;
  if ( v4 != 0 )  // 若 v4 != 0
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v25 = 0;
    sub_401740(pExceptionObject, &v20);  // 调 sub_401740
    pExceptionObject[0] = &std::out_of_range::`vftable';  // 设 out_of_range vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛 out_of_range 异常
  }
  sub_40D800((int *)&Block);  // 调 sub_40D800
  if ( *(uint8_t *)(*Block2 + 77) != 0 )  // 后继为 nil
  {
    v5 = Block2[2];
LABEL_8:  // LABEL_8（跳转目标）
    v7 = Block2[1];
    if ( *(uint8_t *)(v5 + 77) == 0 )  // v5 非 nil
      *(uint32_t *)(v5 + 4) = v7;  // v5+4 = v7
    pThis2 = pThis;
    v9 = pThis[1];
    if ( *(int **)(v9 + 4) == Block2 )  // 表头+4 == 待删结点（更新最左）
    {
      *(uint32_t *)(v9 + 4) = v5;  // v9+4 = v5
    }
    else if ( *(int **)v7 == Block2 )  // 父左子 == 待删结点
    {
      *(uint32_t *)v7 = v5;  // *v7 = v5
    }
    else  // 否则分支
    {
      *(uint32_t *)(v7 + 8) = v5;  // v7+8 = v5
    }
    if ( *(int **)pThis2[1] == Block2 )  // 表头首 == 待删结点
    {
      if ( *(uint8_t *)(v5 + 77) != 0 )  // v5 非 nil
      {
        v10 = (uint32_t *)v7;
      }
      else  // 否则分支
      {
        v10 = sub_40D6C0((uint32_t *)v5);  // v10 = sub_40D6C0 最左
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v10;  // 表头首 = v10
    }
    if ( *(int **)(pThis2[1] + 8) == Block2 )  // 表头+8 == 待删结点
    {
      if ( *(uint8_t *)(v5 + 77) != 0 )  // v5 非 nil
      {
        *(uint32_t *)(pThis2[1] + 8) = v7;  // 表头+8 = v7
      }
      else  // 否则分支
      {
        v11 = sub_40D6A0(v5);  // 表头+8 = sub_40D6A0 最右
        pThis2 = pThis;
        *(uint32_t *)(pThis[1] + 8) = v11;
      }
    }
    goto LABEL_35;  // 跳转 LABEL_35
  }
  if ( *(uint8_t *)(Block2[2] + 77) != 0 )  // 右子为 nil（单子）
  {
    v5 = *Block2;  // v5 = 解引用 Block2
    goto LABEL_8;  // 跳转 LABEL_8
  }
  Block3 = Block;
  v5 = Block[2];
  if ( Block == Block2 )  // Block == 待删结点
    goto LABEL_8;  // 跳转 LABEL_8
  *(uint32_t *)(*Block2 + 4) = Block;  // 待删结点左子 = Block
  *Block3 = *Block2;
  if ( Block3 == (int *)Block2[2] )  // Block3 == 右子
  {
    v7 = (int)Block3;  // v7 = 截断(Block3)
  }
  else  // 否则分支
  {
    v7 = Block3[1];
    if ( *(uint8_t *)(v5 + 77) == 0 )  // v5 非 nil
      *(uint32_t *)(v5 + 4) = v7;  // v5+4 = v7
    *(uint32_t *)v7 = v5;  // *v7 = v5
    Block3[2] = Block2[2];  // Block3[2] = 右子
    *(uint32_t *)(Block2[2] + 4) = Block3;  // 右子[1] = Block3
  }
  v12 = pThis[1];
  if ( *(int **)(v12 + 4) == Block2 )  // 表头+4 == 待删结点
  {
    *(uint32_t *)(v12 + 4) = Block3;  // v12+4 = Block3
  }
  else  // 否则分支
  {
    Block32 = (int **)Block2[1];  // Block32 = 待删结点父
    if ( *Block32 == Block2 )  // 父左子 == 待删结点
      *Block32 = Block3;  // 写指针 = Block3
    else  // 否则分支
      Block32[2] = Block3;
  }
  Block3[1] = Block2[1];
  v14 = *((uint8_t *)Block3 + 76);
  *((uint8_t *)Block3 + 76) = *((uint8_t *)Block2 + 76);
  *((uint8_t *)Block2 + 76) = v14;
  pThis2 = pThis;
LABEL_35:  // LABEL_35（跳转目标）
  if ( *((uint8_t *)Block2 + 76) == 1 )
  {
    if ( v5 != *(uint32_t *)(pThis2[1] + 4) )
    {
      do  // do 循环体
      {
        if ( *(uint8_t *)(v5 + 76) != 1 )
          break;  // 跳出 switch
        pObj = *(uint8_t **)v7;
        if ( v5 == *(uint32_t *)v7 )
        {
          pObj = *(uint8_t **)(v7 + 8);
          if ( pObj[76] == 0 )
          {
            pObj[76] = 1;
            *(uint8_t *)(v7 + 76) = 0;
            sub_40D6E0(pThis2, v7);  // 调 sub_40D6E0
            pObj = *(uint8_t **)(v7 + 8);
            pThis2 = pThis;
          }
          if ( pObj[77] != 0 )
            goto LABEL_53;  // 跳转 LABEL_53
          if ( *(uint8_t *)(*(uint32_t *)pObj + 76) != 1 || *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) != 1 )
          {
            if ( *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)pObj + 76) = 1;
              pObj[76] = 0;
              sub_40D740(pThis2, pObj);  // 调 sub_40D740
              pObj = *(uint8_t **)(v7 + 8);
              pThis2 = pThis;
            }
            pObj[76] = *(uint8_t *)(v7 + 76);
            *(uint8_t *)(v7 + 76) = 1;
            *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) = 1;
            sub_40D6E0(pThis2, v7);  // 调 sub_40D6E0
            break;  // 跳出 switch
          }
        }
        else  // 否则分支
        {
          if ( pObj[76] == 0 )
          {
            pObj[76] = 1;
            *(uint8_t *)(v7 + 76) = 0;
            sub_40D740(pThis2, (uint32_t *)v7);  // 调 sub_40D740
            pObj = *(uint8_t **)v7;
            pThis2 = pThis;
          }
          if ( pObj[77] != 0 )
            goto LABEL_53;  // 跳转 LABEL_53
          if ( *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) != 1 || *(uint8_t *)(*(uint32_t *)pObj + 76) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)pObj + 76) == 1 )
            {
              *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) = 1;
              pObj[76] = 0;
              sub_40D6E0(pThis2, (int)pObj);  // 调 sub_40D6E0
              pObj = *(uint8_t **)v7;
              pThis2 = pThis;
            }
            pObj[76] = *(uint8_t *)(v7 + 76);
            *(uint8_t *)(v7 + 76) = 1;
            *(uint8_t *)(*(uint32_t *)pObj + 76) = 1;
            sub_40D740(pThis2, (uint32_t *)v7);  // 调 sub_40D740
            break;  // 跳出 switch
          }
        }
        pObj[76] = 0;
LABEL_53:  // LABEL_53（跳转目标）
        v5 = v7;
        v16 = v7 == *(uint32_t *)(pThis2[1] + 4);
        v7 = *(uint32_t *)(v7 + 4);
      }
      while ( !v16 );
    }
    *(uint8_t *)(v5 + 76) = 1;
  }
  if ( (unsigned int)Block2[18] >= 0x10 )
    j__free((void *)Block2[13]);
  Block2[18] = 15;
  Block2[17] = 0;
  *((uint8_t *)Block2 + 52) = 0;
  if ( (unsigned int)Block2[9] >= 0x10 )
    j__free((void *)Block2[4]);
  Block2[9] = 15;
  Block2[8] = 0;
  *((uint8_t *)Block2 + 16) = 0;
  j__free(Block2);
  v17 = pThis[2];
  if ( v17 != 0 )  // 若 v17 != 0
    pThis[2] = v17 - 1;
  *pDwArg2 = Block;  // 写指针 = Block
  return pDwArg2;
}


// ------------------------------------------------------------
// 0x40E360 sub_40E360
// ------------------------------------------------------------
// 【解读】
//   包内文件打开（磁盘态）: sub_40DD60 查找 + fopen。被 gfx_texture 0x418CD0（IMG 打开）复用。
// ------------------------------------------------------------
int /*cdecl*/ sub_40E360(int pArg1, int *pDwArg2, char *FileName, uint32_t *uArg4, int nArg5)
{
  if ( dword_8A76D4[4 * nArg5] != 0 )
  {
    sub_40DD60((int ***)&unk_8A76C8 + 4 * nArg5, pArg1, pDwArg2, uArg4, FileName);  // 调 sub_40DD60
    return pArg1;
  }
  else  // 否则分支
  {
    if ( fopen(FileName, "rb") != nullptr )
      *pDwArg2 = 0;  // 写指针 = 0
    *(uint32_t *)(pArg1 + 20) = 0;  // pArg1+20 = 0
    *(uint32_t *)(pArg1 + 24) = 15;  // pArg1+24 = 15
    *(uint8_t *)(pArg1 + 4) = 0;
    sub_4015C0((size_t *)pArg1, szPassword, 0);  // 【std::string构造赋值】
    return pArg1;
  }
}



// ------------------------------------------------------------
// 0x40E3E0 sub_40E3E0
// ------------------------------------------------------------
// 【解读】
//   包内文件打开（NPK 态）: sub_40DED0 红黑树定位 + fopen(NPK) + _fileno/_filelength —— 返回包流 FILE*。
// ------------------------------------------------------------
FILE */*cdecl*/ sub_40E3E0(int *pDwArg1, int *pDwArg2, char *FileName, int nArg4)  // 【NPK按名取数据流】
{
  FILE *pFile; // eax
  FILE *pFile2; // esi
  int v7; // eax

  if ( dword_8A76D4[4 * nArg4] != 0 )
    return sub_40DED0((int ***)&unk_8A76C8 + 4 * nArg4, pDwArg1, pDwArg2, FileName);  // 【NPK缓存查找】
  pFile = fopen(FileName, "rb");
  pFile2 = pFile;
  if ( pFile == nullptr )  // 若 pFile 为空
    return nullptr;
  v7 = _fileno(pFile);
  *pDwArg2 = _filelength(v7);
  *pDwArg1 = 0;  // 写指针 = 0
  return pFile2;
}



// ------------------------------------------------------------
// 0x40E450 sub_40E450 —— 包索引树递归销毁（后序；值析构 ·sub_40DA20）
// —— 与 ·sub_40C7C0 同构（差异：哨兵位 77、析构函数不同）。
// ------------------------------------------------------------
char /*stdcall*/ sub_40E450(void **Block)  // 函数 包索引树递归销毁（后序；值析构 ·sub_40DA20）
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 77);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_40E450(i[2]);  // 调 sub_40E450
    i = (void **)*i;  // i = 解引用跟踪 i
    sub_40DA20((int)Block2);  // 调 sub_40DA20
    j__free(Block2);
    result = *((uint8_t *)i + 77);
  }
  return result;
}



// ------------------------------------------------------------
// 0x40E4A0 sub_40E4A0 [串: "map/set<T> too long"]
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40E4A0(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, size_t *pArg5)
{
  uint32_t *fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  int *v10; // eax
  int v11; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  uint32_t *fld_e15; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x3FFFFFE )
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // 调 sub_401740
    pExceptionObject[0] = &std::length_error::`vftable';  // 设 length_error vftable
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛 length_error 异常
  }
  fld_e1 = sub_40DFB0(*(this + 1), (int)pArg4, *(this + 1), pArg5, 0);  // 调 包索引树结点分配（0x50B：偏移/长度/序号 + ·sub_40DAE0 值）
  fld_e12 = (uint32_t *)*(this + 1);
  fld_e15 = fld_e1;
  ++*(this + 2);
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;  // 写指针 = fld_e1
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;  // 写指针 = fld_e1
  }
  else  // 否则分支
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // fld_e14 = this+1 字段
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // fld_e14+8 = fld_e1
  }
  v10 = fld_e1 + 1;
  v11 = (int)fld_e1;  // v11 = 截断(fld_e1)
  if ( *(uint8_t *)(fld_e1[1] + 76) == 0 )
  {
    while ( 1 )  // 当 1 非 0 循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;  // v14 = 解引用 v13
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 76) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;  // v11 = 解引用 v10
            sub_40D6E0(this, *v10);  // 调 sub_40D6E0
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 76) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 76) = 0;
          sub_40D740(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));  // 调 sub_40D740
          goto LABEL_21;  // 跳转 LABEL_21
        }
      }
      else if ( *(uint8_t *)(v14 + 76) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;  // v11 = 解引用 v10
          sub_40D740(this, (uint32_t *)*v10);  // 调 sub_40D740
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 76) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 76) = 0;
        sub_40D6E0(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));  // 调 sub_40D6E0
        goto LABEL_21;  // 跳转 LABEL_21
      }
      *(uint8_t *)(*v10 + 76) = 1;
      *(uint8_t *)(v14 + 76) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 76) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:  // LABEL_21（跳转目标）
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 76) != 0 )
      {
        fld_e1 = fld_e15;
        break;  // 跳出 switch
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 76) = 1;
  *uArg2 = fld_e1;  // 写指针 = fld_e1
  return uArg2;
}



// ------------------------------------------------------------
// 0x40E650 sub_40E650 —— 树子树递归复制（克隆进 ·sub_40DFB0；递归挂 +0/+8 子链）
// 返回新子树根。【推断: MSVC _Copy_nodes 形】
// ------------------------------------------------------------
void */*thiscall*/ sub_40E650(void **this, int *pDwArg2, int nArg3)  // 函数 树子树递归复制（克隆进 ·sub_40DFB0；递归挂 +0/+8 子链）
{
  char v3; // al
  uint32_t *fld_e1; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);  // Block = this+1
  v3 = *((uint8_t *)pDwArg2 + 77);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )  // 若 v3 == 0
  {
    fld_e1 = sub_40DFB0((int)*(this + 1), nArg3, (int)*(this + 1), (size_t *)pDwArg2 + 3, *((uint8_t *)pDwArg2 + 76));  // 调 包索引树结点分配（0x50B：偏移/长度/序号 + ·sub_40DAE0 值）
    if ( *((uint8_t *)Block + 77) != 0 )
      Block = fld_e1;
    v6 = *pDwArg2;  // v6 = 解引用 pDwArg2
    v10 = 0;
    *fld_e1 = sub_40E650(v6, fld_e1);  // 调 树子树递归复制（克隆进 ·sub_40DFB0；递归挂 +0/+8 子链）
    fld_e1[2] = sub_40E650(pDwArg2[2], fld_e1);  // 调 树子树递归复制（克隆进 ·sub_40DFB0；递归挂 +0/+8 子链）
  }
  return Block;
}



// ------------------------------------------------------------
// 0x40E700 sub_40E700 —— NPK 名字树插入（字符串键定位 → ·sub_40E4A0 建结点）
// ------------------------------------------------------------
int /*thiscall*/ sub_40E700(int *this, int pArg2, size_t *pArg3)  // 【NPK名字树插入】
{
  int fld_e1; // ebx
  size_t *fld_e12; // esi
  char v5; // al
  size_t *pArg32; // edi
  size_t i; // esi
  unsigned int v8; // ecx
  const char *v9; // eax
  unsigned int v10; // edx
  const char *v11; // esi
  int nCmp; // eax
  bool v13; // sf
  unsigned int v14; // esi
  int v15; // eax
  size_t *fld_e122; // ebx
  const char *v18; // eax
  size_t *v19; // [esp+Ch] [ebp-14h]
  int *pThis; // [esp+18h] [ebp-8h]
  char v21; // [esp+1Ch] [ebp-4h]

  fld_e1 = *(uint32_t *)(*(this + 1) + 4);
  fld_e12 = (size_t *)*(this + 1);
  v5 = 1;
  pArg32 = pArg3;
  pThis = this;
  v21 = 1;
  if ( *(uint8_t *)(fld_e1 + 77) == 0 )
  {
    for ( i = pArg3[5]; ; i = pArg3[5] )
    {
      v8 = *(uint32_t *)(fld_e1 + 32);
      v19 = (size_t *)fld_e1;
      if ( *(uint32_t *)(fld_e1 + 36) < 0x10u )
        v9 = (const char *)(fld_e1 + 16);
      else  // 否则分支
        v9 = *(const char **)(fld_e1 + 16);
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )  // 若 v10 == 0
        goto LABEL_16;  // 跳转 LABEL_16
      if ( v10 < v8 )
        v8 = v10;
      v11 = pArg32[6] < 0x10 ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];  // v11 = pArg32[...]
      nCmp = memcmp(v11, v9, v8);
      v13 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )  // 若 nCmp == 0
      {
LABEL_16:  // LABEL_16（跳转目标）
        v14 = *(uint32_t *)(fld_e1 + 32);
        if ( v10 >= v14 )  // 若 v10 >= v14
          v15 = v10 != v14;
        else  // 否则分支
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      fld_e1 = v13 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);
      if ( *(uint8_t *)(fld_e1 + 77) != 0 )
        break;  // 跳出 switch
    }
    fld_e12 = v19;
    this = pThis;
  }
  fld_e122 = fld_e12;
  pArg3 = fld_e12;
  if ( v5 != 0 )  // 若 v5 != 0
  {
    if ( fld_e12 == *(size_t **)*(this + 1) )
    {
      *(uint32_t *)pArg2 = *sub_40E4A0(this, &pArg3, 1, fld_e12, pArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      return pArg2;
    }
    sub_40D7A0(&pArg3);  // 调 sub_40D7A0
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10 )
    v18 = (const char *)(pArg32 + 1);
  else  // 否则分支
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )  // 调 std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    *(uint32_t *)pArg2 = fld_e122;
    *(uint8_t *)(pArg2 + 4) = 0;
  }
  else  // 否则分支
  {
    *(uint32_t *)pArg2 = *sub_40E4A0(pThis, &pArg3, v21, fld_e12, pArg32);
    *(uint8_t *)(pArg2 + 4) = 1;
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x40E860 sub_40E860 —— 包索引树区间删除（循环 ·sub_40E050；全清分支）
// —— 与 ·sub_40CBA0 同构（差异：+77 系、删除核 ·sub_40E050）。
// ------------------------------------------------------------
int **/*thiscall*/ sub_40E860(void ****this, int **pDwArg2, int *Block, int *pDwArg4)  // 函数 包索引树区间删除（循环 ·sub_40E050；全清分支）
{
  int *pDwArg42; // ebx
  int *Block2; // esi
  void ***fld_e1; // eax
  uint32_t *fld_e12; // eax
  int *Block22; // ecx
  int v11; // eax
  int *j; // eax
  int i; // eax

  pDwArg42 = pDwArg4;
  Block2 = Block;
  fld_e1 = *(this + 1);  // fld_e1 = this+1 字段
  if ( Block == (int *)*fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_40E450(fld_e1[1]);  // 调 sub_40E450
    (*(this + 1))[1] = (void **)*(this + 1);
    fld_e12 = *(this + 1);  // fld_e12 = this+1 字段
    *(this + 2) = nullptr;  // this+2 = 空指针
    *fld_e12 = fld_e12;  // 写指针 = fld_e12
    (*(this + 1))[2] = (void **)*(this + 1);
    *pDwArg2 = (int *)**(this + 1);
    return pDwArg2;
  }
  else  // 否则分支
  {
    if ( Block != pDwArg4 )
    {
      do  // do 循环体
      {
        Block22 = Block2;
        if ( *((uint8_t *)Block2 + 77) == 0 )
        {
          v11 = Block2[2];
          if ( *(uint8_t *)(v11 + 77) != 0 )
          {
            for ( i = Block2[1]; *(uint8_t *)(i + 77) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( Block2 != *(int **)(i + 8) )
                break;  // 跳出 switch
              Block2 = (int *)i;
            }
            Block2 = (int *)i;
          }
          else  // 否则分支
          {
            Block2 = (int *)Block2[2];
            for ( j = *(int **)v11; *((uint8_t *)j + 77) == 0; j = (int *)*j )
              Block2 = j;
          }
        }
        sub_40E050(this, &Block, Block22);  // 调 sub_40E050
      }
      while ( Block2 != pDwArg42 );
    }
    *pDwArg2 = Block2;  // 写指针 = Block2
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x40E920 sub_40E920 —— 包索引树复制（·sub_40E650 克隆对方根；重算哨兵最左/最右）
// ------------------------------------------------------------
int */*thiscall*/ sub_40E920(int this, int pArg2)  // 函数 包索引树复制（·sub_40E650 克隆对方根；重算哨兵最左/最右）
{
  int fld_4; // edi
  int **fld_42; // edx
  int *result; // eax
  int *v6; // ecx
  int fld_43; // esi
  int **v8; // ecx

  fld_4 = *(uint32_t *)(this + 4);
  *(uint32_t *)(fld_4 + 4) = sub_40E650((void **)this, *(int **)(*(uint32_t *)(pArg2 + 4) + 4), fld_4);  // fld_4+4 = sub_40E650((void **)this, *(int **)(*(uint32_t *)(pArg2 + 4) + 4), fld_4)
  *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8);  // this+8 = *(uint32_t *)(pArg2 + 8)
  fld_42 = *(int ***)(this + 4);
  result = fld_42[1];
  if ( *((uint8_t *)result + 77) != 0 )
  {
    *fld_42 = (int *)fld_42;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
  }
  else  // 否则分支
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 77) == 0 )
    {
      do  // do 循环体
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 77) == 0 );
    }
    *fld_42 = result;  // 写指针 = result
    fld_43 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(fld_43 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 77) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(fld_43 + 8) = v8;  // fld_43+8 = v8
  }
  return result;
}



// ------------------------------------------------------------
// 0x40E9B0 sub_40E9B0 —— 包索引树清空（·sub_40E450 全销毁 + 哨兵环复位 + 计数清零）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40E9B0(uint32_t *this)  // 函数 包索引树清空（·sub_40E450 全销毁 + 哨兵环复位 + 计数清零）
{
  uint32_t *result; // eax

  sub_40E450(*(void ***)(*(this + 1) + 4));  // 调 sub_40E450
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  result = (uint32_t *)*(this + 1);
  *(this + 2) = 0;  // this+2 清 0
  *result = result;  // 写指针 = result
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  return result;
}



// ============================================================
// SECTION 0x40E9E0 — ★★ NPK 资源包加载器（NeoplePack_Bill 魔数 / *.npk 目录扫描 / 包内文件定位）
// ============================================================
// ------------------------------------------------------------
// 0x40E9E0 sub_40E9E0
// ------------------------------------------------------------
// 【解读】
//   ★ NPK 包打开: 读包头 strncmp("NeoplePack_Bill") 魔数校验 → 包索引构建
//     （sub_40E700 红黑树，文件名 tolower 归一 sub_40D660）。Neople 自有封包格式。
// ------------------------------------------------------------
int /*thiscall*/ sub_40E9E0(int *this, FILE *Stream)  // 【NPK 资源包加载器（NeoplePack_Bill 魔数 / *.npk 目录扫描…】
{
  size_t *v4; // eax
  bool v5; // sf
  bool v6; // of
  uint8_t v7[8]; // [esp+8h] [ebp-1B0h] BYREF
  uint8_t v8[4]; // [esp+10h] [ebp-1A8h] BYREF
  void *v9; // [esp+14h] [ebp-1A4h]
  int v10; // [esp+24h] [ebp-194h]
  unsigned int v11; // [esp+28h] [ebp-190h]
  void *v12; // [esp+38h] [ebp-180h]
  int v13; // [esp+48h] [ebp-170h]
  unsigned int v14; // [esp+4Ch] [ebp-16Ch]
  size_t v15; // [esp+50h] [ebp-168h] BYREF
  void *v16; // [esp+54h] [ebp-164h]
  int v17; // [esp+64h] [ebp-154h]
  unsigned int v18; // [esp+68h] [ebp-150h]
  int *pThis; // [esp+6Ch] [ebp-14Ch]
  int Buffer; // [esp+70h] [ebp-148h] BYREF
  char Src[256]; // [esp+74h] [ebp-144h] BYREF
  char Str2[16]; // [esp+174h] [ebp-44h] BYREF
  int v23; // [esp+184h] [ebp-34h] BYREF
  uint8_t v24[8]; // [esp+188h] [ebp-30h] BYREF
  void *Block; // [esp+190h] [ebp-28h]
  int v26; // [esp+1A0h] [ebp-18h]
  unsigned int v27; // [esp+1A4h] [ebp-14h]
  int dword_796E502; // [esp+1A8h] [ebp-10h]
  int v29; // [esp+1B4h] [ebp-4h]
  FILE *Streama; // [esp+1C0h] [ebp+8h]

  dword_796E502 = dword_796E50;  // dword_796E502 = dword_796E50（栈检）
  pThis = this;
  v27 = 15;  // v27 = 15（串容量）
  v26 = 0;
  LOBYTE(Block) = 0;  // Block 低字节 = 0
  v29 = 0;
  sub_66BD5A(Str2, 0x10u, 1u, Stream);  // 【fread封装】
  if ( strncmp("NeoplePack_Bill", Str2, 0x10u) == 0 )  // 魔数 == NeoplePack_Bill
  {
    sub_66BD5A(&Buffer, 4u, 1u, Stream);  // 【fread封装】
    Streama = nullptr;  // Streama = 条目计数 0
    if ( Buffer > 0 )  // 条目数 > 0
    {
      do  // 逐条目循环
      {
        sub_66BD5A(&v23, 4u, 1u, Stream);  // 【fread封装】
        sub_66BD5A(v24, 4u, 1u, Stream);  // 【fread封装】
        sub_66BD5A(Src, 0x100u, 1u, Stream);  // 【fread封装】
        Src[255] = 0;  // Src 强制补串尾
        v18 = 15;  // v18 = 15（串容量）
        v17 = 0;
        LOBYTE(v16) = 0;  // v16 低字节 = 0
        sub_4015C0(&v15, Src, strlen(Src));  // 【std::string构造赋值】
        LOBYTE(v29) = 1;  // v29 低字节 = 1
        v4 = (size_t *)sub_40DB60((int)v8, &v15, &v23);  // 【NPK条目构造】
        LOBYTE(v29) = 2;  // v29 低字节 = 2
        sub_40E700(pThis, (int)v7, v4);  // 【NPK名字树插入】
        if ( v14 >= 0x10 )  // v14 容量 >= 16
          j__free(v12);  // free 临时串
        v14 = 15;
        v13 = 0;
        LOBYTE(v12) = 0;  // v12 低字节 = 0
        if ( v11 >= 0x10 )  // v11 容量 >= 16
          j__free(v9);  // free 临时串
        v11 = 15;
        v10 = 0;
        LOBYTE(v9) = 0;  // v9 低字节 = 0
        LOBYTE(v29) = 0;  // v29 低字节 = 0
        if ( v18 >= 0x10 )  // v18 容量 >= 16
          j__free(v16);  // free 临时串
        v6 = __OFSUB__((char *)&Streama->_ptr + 1, Buffer);  // v6 = 溢出标志
        v5 = (int)&Streama->_ptr - Buffer + 1 < 0;  // v5 = 符号标志
        v18 = 15;
        v17 = 0;
        LOBYTE(v16) = 0;  // v16 低字节 = 0
        Streama = (FILE *)((char *)Streama + 1);  // 条目计数 ++
      }
      while ( v5 != v6 );  // 未遍历完继续
    }
    if ( v27 >= 0x10 )  // v27 容量 >= 16
      j__free(Block);  // free 临时串
    return 1;  // 返回 1（成功）
  }
  else  // 否则分支
  {
    if ( v27 >= 0x10 )  // v27 容量 >= 16
      j__free(Block);  // free
    return 0;  // 返回 0（魔数不符）
  }
}



// ------------------------------------------------------------
// 0x40EC10 sub_40EC10 —— 包索引树全销毁（区间删除 + free 根结点 + 计数清零）
// ------------------------------------------------------------
int /*thiscall*/ sub_40EC10(int this)  // 函数 包索引树全销毁（区间删除 + free 根结点 + 计数清零）
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_40E860((void ****)this, (int **)&v3, **(int ***)(this + 4), *(int **)(this + 4));  // sub_40E860 树区间删除
  j__free(*(void **)(this + 4));  // free 根结点
  *(uint32_t *)(this + 4) = 0;  // this+4 清 0
  *(uint32_t *)(this + 8) = 0;  // this+8 清 0
  return 0;
}



// ------------------------------------------------------------
// 0x40EC50 sub_40EC50 —— 包索引树复制构造（哨兵 ·sub_40D860 + 复制源 ·sub_40E920）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40EC50(uint32_t *this, int nArg2)  // 函数 包索引树复制构造（哨兵 ·sub_40D860 + 复制源 ·sub_40E920）
{
  uint32_t *v3; // eax
  uint32_t v5[8]; // [esp+0h] [ebp-20h] BYREF

  v5[4] = v5;
  v5[3] = this;
  v3 = sub_40D860();  // v3 = sub_40D860 建哨兵
  *(this + 1) = v3;  // this+1 = 哨兵
  *((uint8_t *)v3 + 77) = 1;  // 哨兵+77 = 1（nil 标志）
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);  // 哨兵+4 自环
  *(uint32_t *)*(this + 1) = *(this + 1);  // 哨兵自环
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);  // 哨兵+8 自环
  *(this + 2) = 0;  // this+2 计数清 0
  v5[7] = 0;
  sub_40E920((int)this, nArg2);  // sub_40E920 复制源树
  return this;
}



// ------------------------------------------------------------
// 0x40ECE0 sub_40ECE0 —— 子容器初始化（串头 + 哨兵树 ·sub_40D860 + 首字段清零）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40ECE0(uint32_t *this)  // 函数 子容器初始化（串头 + 哨兵树 ·sub_40D860 + 首字段清零）
{
  char *pThis_8; // edi
  uint32_t *v3; // eax

  *(this + 7) = 15;  // this+7 = 15（串容量）
  *(this + 6) = 0;  // this+6 = 0（串长）
  *((uint8_t *)this + 8) = 0;  // this+8 清 0
  pThis_8 = (char *)(this + 8);  // pThis_8 = this+8
  v3 = sub_40D860();  // v3 = sub_40D860 建哨兵
  *((uint32_t *)pThis_8 + 1) = v3;  // this+9 = 哨兵
  *((uint8_t *)v3 + 77) = 1;  // 哨兵+77 = 1
  *(uint32_t *)(*((uint32_t *)pThis_8 + 1) + 4) = *((uint32_t *)pThis_8 + 1);  // 哨兵+4 自环
  **((uint32_t **)pThis_8 + 1) = *((uint32_t *)pThis_8 + 1);  // 哨兵自环
  *(uint32_t *)(*((uint32_t *)pThis_8 + 1) + 8) = *((uint32_t *)pThis_8 + 1);  // 哨兵+8 自环
  *((uint32_t *)pThis_8 + 2) = 0;  // this+10 清 0
  *this = 0;  // *this 清 0
  return this;
}



// ------------------------------------------------------------
// 0x40ED50 sub_40ED50 —— 子容器销毁（树区间删除 + free 根 + this+8 串释放）
// ------------------------------------------------------------
void /*thiscall*/ sub_40ED50(int this)  // 函数 子容器销毁（树区间删除 + free 根 + this+8 串释放）
{
  int *fld_24; // eax
  int pThis_20; // esi
  int *v4; // [esp-8h] [ebp-28h]
  int v5[5]; // [esp+Ch] [ebp-14h] BYREF

  v5[1] = this;
  fld_24 = *(int **)(this + 36);  // fld_24 = this+36 树根
  pThis_20 = this + 32;
  v4 = (int *)*fld_24;
  v5[4] = 0;
  sub_40E860((void ****)(this + 32), (int **)v5, v4, fld_24);  // sub_40E860 树区间删除
  j__free(*(void **)(pThis_20 + 4));  // free 根结点
  *(uint32_t *)(pThis_20 + 4) = 0;  // 根+4 清 0
  *(uint32_t *)(pThis_20 + 8) = 0;  // 根+8 清 0
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+28 串容量 >= 16
    j__free(*(void **)(this + 8));  // free 堆上串
  *(uint32_t *)(this + 24) = 0;  // this+24 = 0（串长）
  *(uint32_t *)(this + 28) = 15;  // this+28 = 15（容量）
  *(uint8_t *)(this + 8) = 0;  // this+8 清 0
}



// ------------------------------------------------------------
// 0x40EDE0 sub_40EDE0 —— 包条目复制构造（序号 + 串 + 树 ·sub_40EC50）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40EDE0(uint32_t *this, uint32_t *pArg2)  // 函数 包条目复制构造（序号 + 串 + 树 ·sub_40EC50）
{
  uint32_t *pThis_1; // ecx

  pThis_1 = this + 1;
  *this = *pArg2;  // *this = *pArg2（序号）
  pThis_1[6] = 15;  // pThis_1[6] = 15（串容量）
  pThis_1[5] = 0;  // pThis_1[5] = 0（串长）
  *((uint8_t *)pThis_1 + 4) = 0;  // pThis_1+4 清 0
  sub_4014D0(pThis_1, pArg2 + 1, 0, 0xFFFFFFFF);  // sub_4014D0 复制文件名字串
  sub_40EC50(this + 8, (int)(pArg2 + 8));  // sub_40EC50 复制子容器树
  return this;
}



// ------------------------------------------------------------
// 0x40EE50 sub_40EE50 —— 包条目析构（转发 ·sub_40ED50 至 this+8 子对象）
// ------------------------------------------------------------
void /*thiscall*/ sub_40EE50(void *this)  // 函数 包条目析构（转发 ·sub_40ED50 至 this+8 子对象）
{
  sub_40ED50((int)this + 8);  // sub_40ED50 析构子对象 this+8
}



// ------------------------------------------------------------
// 0x40EE60 sub_40EE60 —— 包链表结点分配（0x34B：序号对 + ·sub_40EDE0 条目）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_40EE60(int nArg1, int nArg2, uint32_t *uArg3)  // 函数 包链表结点分配（0x34B：序号对 + ·sub_40EDE0 条目）
{
  uint32_t *pMem; // esi
  void *v5[9]; // [esp+0h] [ebp-24h] BYREF

  v5[5] = v5;
  pMem = operator new(0x34u);  // v5[5] = v5
  v5[4] = pMem;  // pMem = new 0x34（结点）
  v5[8] = (void *)1;  // v5[4] = pMem
  v5[3] = pMem;  // v5[8] = 1（展开标记）
  if ( pMem != nullptr )  // v5[3] = pMem
  {  // 分配成功
    pMem[1] = nArg2;
    *pMem = nArg1;  // pMem[1] = nArg2
    sub_40EDE0(pMem + 2, uArg3);  // *pMem = nArg1（序号对）
  }  // sub_40EDE0 构造条目到 pMem+2
  return pMem;
}



// ------------------------------------------------------------
// 0x40EEF0 sub_40EEF0 —— 包链表头插（·sub_40EE60 结点 + 容量校验 ·sub_40DBE0）
// —— 与 ·sub_40B950 同构（差异：载荷 0x34B、校验例程不同）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40EEF0(int *this, uint32_t *uArg2)  // 函数 包链表头插（·sub_40EE60 结点 + 容量校验 ·sub_40DBE0）
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this[1] 哨兵
  v4 = sub_40EE60(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);  // v4 = sub_40EE60 建结点
  result = sub_40DBE0(this, 1u);  // sub_40DBE0 容量校验
  *(uint32_t *)(fld_e1 + 4) = v4;  // 哨兵+4 = 新结点
  *(uint32_t *)v4[1] = v4;  // 断链复位
  return result;
}



// ------------------------------------------------------------
// 0x40EF30 sub_40EF30 —— 包链表全清（环链摘除 + ·sub_40EE50 逐结点析构）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40EF30(uint32_t *this)  // 函数 包链表全清（环链摘除 + ·sub_40EE50 逐结点析构）
{
  uint32_t **fld_e1; // eax
  uint32_t *v3; // esi
  uint32_t *result; // eax
  bool fld_e12; // zf
  uint32_t *v6; // ebx

  fld_e1 = (uint32_t **)*(this + 1);  // fld_e1 = this[1] 哨兵
  v3 = *fld_e1;  // v3 = *fld_e1 首结点
  *fld_e1 = fld_e1;  // 哨兵断自环
  result = (uint32_t *)*(this + 1);  // result = 哨兵
  result[1] = result;  // 哨兵+4 自环
  fld_e12 = v3 == (uint32_t *)*(this + 1);  // fld_e12 = 链表空
  *(this + 2) = 0;  // 计数清 0
  if ( !fld_e12 )  // 链表非空
  {
    do  // 逐结点
    {
      v6 = (uint32_t *)*v3;  // v6 = 下一结点
      sub_40EE50(v3);  // sub_40EE50 析构结点
      j__free(v3);  // free
      result = (uint32_t *)*(this + 1);  // result = 哨兵
      v3 = v6;
    }
    while ( v6 != result );  // 回到哨兵
  }
  return result;
}



// ------------------------------------------------------------
// 0x40EF70 sub_40EF70
// ------------------------------------------------------------
// 【解读】
//   ★ *.npk 扫描装载: GetCurrentDirectoryA/SetCurrentDirectoryA + _findfirst/_findnext
//     遍历 "*.npk" → 逐包 sub_40E9E0 打开 → 挂入包管理器（0x40EEF0 链表）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40EF70(int *this, LPCSTR lpPathName)
{
  int nLen; // kr00_4
  CHAR v4; // cl
  void *v5; // edi
  FILE *pFile; // eax
  FILE *pFile3; // esi
  int v8; // eax
  char v9; // cl
  unsigned int nLen2; // eax
  char *v11; // edi
  char v12; // cl
  FILE *pFile2; // eax
  FILE *pFile4; // esi
  int v15; // eax
  char v16; // cl
  unsigned int nLen3; // eax
  char *v18; // edi
  char v19; // cl
  int fld_e1; // esi
  uint32_t *v21; // edi
  void *v23; // [esp+Ch] [ebp-D5Ch]
  FILE *pFile5; // [esp+10h] [ebp-D58h]
  FILE *pFile22; // [esp+10h] [ebp-D58h]
  CHAR Buffer[1024]; // [esp+14h] [ebp-D54h] BYREF
  char psz[1023]; // [esp+414h] [ebp-954h] BYREF
  char v28; // [esp+813h] [ebp-555h] BYREF
  char Src; // [esp+814h] [ebp-554h] BYREF
  uint8_t v30[1023]; // [esp+815h] [ebp-553h] BYREF
  int v31[5]; // [esp+C14h] [ebp-154h] BYREF
  char FileName[260]; // [esp+C28h] [ebp-140h] BYREF
  int v33; // [esp+D2Ch] [ebp-3Ch] BYREF
  uint8_t v34[4]; // [esp+D4Ch] [ebp-1Ch] BYREF
  int v35; // [esp+D50h] [ebp-18h]
  int v36; // [esp+D54h] [ebp-14h]
  int dword_796E502; // [esp+D58h] [ebp-10h]
  int v38; // [esp+D64h] [ebp-4h]
  int lpPathNamea; // [esp+D70h] [ebp+8h]

  dword_796E502 = dword_796E50;  // dword_796E502 = dword_796E50（栈检）
  sub_40ECE0(&v33);  // sub_40ECE0 初始化子容器 v33
  v38 = 0;
  strcpy(psz, lpPathName);  // strcpy 路径到 psz
  nLen = strlen(psz);  // nLen = 路径长
  if ( nLen > 0 )  // 非空
  {
    v4 = Buffer[nLen + 1023];  // v4 = 末字符
    if ( v4 != 92 && v4 != 47 )  // 非 \ 或 /
    {
      psz[nLen] = 92;  // 补路径分隔符 \
      psz[nLen + 1] = 0;  // 补串尾
    }
  }
  GetCurrentDirectoryA(0x400u, Buffer);  // GetCurrentDirectoryA 保存当前目录
  SetCurrentDirectoryA(lpPathName);  // SetCurrentDirectoryA 切到目标目录
  lpPathNamea = 0;  // lpPathNamea = 0（包计数）
  v5 = (void *)_findfirst("*.npk", (int)v31);  // _findfirst 查找 *.npk
  v23 = v5;  // v23 = 搜索句柄
  if ( v5 != (void *)-1 )  // 找到文件
  {
    pFile = fopen(FileName, "rb");  // fopen(FileName) 打开包
    pFile3 = pFile;  // pFile3 = 句柄
    pFile5 = pFile;  // pFile5 = 句柄
    if ( pFile != nullptr )  // 打开成功
    {
      if ( sub_40E9E0(v34, pFile) != 0 )  // 【NPK 资源包加载器（NeoplePack_Bill 魔数 / *.npk 目录扫描…】
      {
        v8 = 0;
        do  // 复制路径串
        {
          v9 = psz[v8];
          v30[v8++ - 1] = v9;  // 逐字符复制（跳过首字节）
        }
        while ( v9 != 0 );  // 直到串尾
        nLen2 = strlen(FileName) + 1;  // nLen2 = 文件名长 + 1
        v11 = &v28;
        do  // 找串尾
          v12 = *++v11;
        while ( v12 != 0 );  // 直到串尾
        qmemcpy(v11, FileName, nLen2);  // qmemcpy 拼文件名
        sub_4015C0(&Src, &v30[strlen(&Src)] - v30);  // 【std::string构造赋值】
        sub_40EEF0(&v33);  // sub_40EEF0 挂入包链表
        sub_40E9B0(v34);  // sub_40E9B0 释放
        v5 = v23;  // v5 复位
        pFile3 = pFile5;  // pFile3 复位
        lpPathNamea = 1;  // lpPathNamea = 1（已装载 1 包）
      }
      fclose(pFile3);
    }
    while ( _findnext(v5, (int)v31) == 0 )  // _findnext 遍历下一个 *.npk
    {
      pFile2 = fopen(FileName, "rb");  // fopen 打开
      pFile4 = pFile2;  // pFile4 = 句柄
      pFile22 = pFile2;  // pFile22 = 句柄
      if ( pFile2 != nullptr )  // 打开成功
      {
        if ( sub_40E9E0(v34, pFile2) != 0 )  // 【NPK 资源包加载器（NeoplePack_Bill 魔数 / *.npk 目录扫描…】
        {
          v15 = 0;
          do  // 复制路径串
          {
            v16 = psz[v15];
            v30[v15++ - 1] = v16;  // 逐字符复制
          }
          while ( v16 != 0 );  // 直到串尾
          nLen3 = strlen(FileName) + 1;  // nLen3 = 文件名长 + 1
          v18 = &v28;
          do  // 找串尾
            v19 = *++v18;
          while ( v19 != 0 );  // 直到串尾
          qmemcpy(v18, FileName, nLen3);  // qmemcpy 拼文件名
          sub_4015C0(&Src, &v30[strlen(&Src)] - v30);  // 【std::string构造赋值】
          fld_e1 = *(this + 1);  // fld_e1 = this[1] 哨兵
          v21 = sub_40EE60(fld_e1, *(uint32_t *)(fld_e1 + 4), (int)&v33);  // v21 = sub_40EE60 建结点
          sub_40DBE0(this, 1u);  // sub_40DBE0 容量校验
          *(uint32_t *)(fld_e1 + 4) = v21;  // 哨兵+4 = 新结点
          *(uint32_t *)v21[1] = v21;  // 断链复位
          sub_40E450(*(void **)(v35 + 4));  // sub_40E450 清树
          v5 = v23;  // v5 复位
          pFile4 = pFile22;  // pFile4 复位
          *(uint32_t *)(v35 + 4) = v35;  // 根+4 自环复位
          v36 = 0;
          *(uint32_t *)v35 = v35;  // 根自环
          *(uint32_t *)(v35 + 8) = v35;  // 根+8 自环
          ++lpPathNamea;  // 包计数 ++
        }
        fclose(pFile4);
      }
    }
    _findclose((intptr_t)v5);  // _findclose 关闭搜索
  }
  SetCurrentDirectoryA(Buffer);  // SetCurrentDirectoryA 恢复原目录
  v38 = -1;
  sub_40ED50(&v33);  // sub_40ED50 析构子容器
  return lpPathNamea;  // 返回包计数
}


// ============================================================
// SECTION 0x40F2F0 — 矩形/绘制辅助与杂项（SetRect 族、sprite 小工具）
// ============================================================
// ------------------------------------------------------------
// 0x40F2F0 sub_40F2F0 —— 包管理收尾（关流 ·sub_40D8A0 + 两轮链表清空 + free 管理块）
// ------------------------------------------------------------
void /*thiscall*/ sub_40F2F0(int this)  // 【矩形/绘制辅助与杂项（SetRect 族、sprite 小工具）】
{
  sub_40D8A0((uint32_t *)this);  // 调 sub_40D8A0
  sub_40EF30((uint32_t *)this);  // 调 sub_40EF30
  sub_40EF30((uint32_t *)this);  // 调 sub_40EF30
  j__free(*(void **)(this + 4));  // free this+4
  *(uint32_t *)(this + 4) = 0;  // this+4（uint32 槽）= 0
}



// ------------------------------------------------------------
// 0x40F360 sub_40F360 —— 精灵复位（虚发 +92 传 0xFF00FF00；状态字段区清零）
// ------------------------------------------------------------
int /*thiscall*/ sub_40F360(uint32_t *this)  // 函数 精灵复位（虚发 +92 传 0xFF00FF00；状态字段区清零）
{
  uint32_t *pThis; // esi
  int v2; // eax
  int result; // eax

  pThis = this;
  v2 = *this;  // v2 = 解引用 this
  *((uint8_t *)this + 44) = 0;  // this 偏移 44 字节 = 0
  *((uint8_t *)this + 45) = 0;  // this 偏移 45 字节 = 0
  result = (*(int (/*stdcall*/ **)(int))(v2 + 92))(-16711936);  // 调用虚函数/间接调用
  pThis[3] = 0;
  pThis[4] = 0;
  pThis[16] = 0;
  pThis[5] = 0;
  pThis[6] = 0;
  pThis[7] = 0;
  pThis[8] = 0;
  pThis[9] = 0;
  pThis[10] = 0;
  pThis[18] = 0;
  pThis += 12;  // pThis 前进 12
  *pThis = 0;  // 写指针 = 0
  pThis[1] = 0;
  pThis[2] = 0;
  pThis[3] = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40F3C0 sub_40F3C0 —— 精灵建立（设坐标 + SetRect + 虚发 +172 建面）
// 已建立（+4!=0）返回 -2147483646；+172 失败码原样返回。
// ------------------------------------------------------------
int /*thiscall*/ sub_40F3C0(void *this, int nArg2, int nArg3, int nArg4)  // 函数 精灵建立（设坐标 + SetRect + 虚发 +172 建面）
{
  int result; // eax
  int pThis_8; // edx
  int pThis_7; // ecx

  if ( *((uint8_t *)this + 4) != 0 )  // 若 this 偏移 4 非 0
    return -2147483646;  // 返回 0x80000002（已初始化）
  pThis_8 = nArg4 + *((uint32_t *)this + 8);
  *((uint32_t *)this + 6) = nArg4;  // this 偏移 24 = 参数4
  pThis_7 = *((uint32_t *)this + 7);  // pThis_7 = this 偏移 7
  *((uint32_t *)this + 3) = nArg2;  // this 偏移 12 = 参数2
  *((uint32_t *)this + 5) = nArg3;  // this 偏移 20 = 参数3
  SetRect((LPRECT)this + 3, 0, 0, nArg3 + pThis_7, pThis_8);
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 172))(this);  // 调用虚函数/间接调用
  if ( result >= 0 )  // 若 result >= 0
  {
    *((uint8_t *)this + 4) = 1;  // this 偏移 4 字节 = 1
    return 1;  // 返回 1（成功）
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F420 sub_40F420 —— 精灵缓冲释放（行表 +16 与位缓冲 +12 free；清 +4 标志）
// ------------------------------------------------------------
int /*thiscall*/ sub_40F420(int this)  // 函数 精灵缓冲释放（行表 +16 与位缓冲 +12 free；清 +4 标志）
{
  void *fld_C; // eax

  if ( *(uint8_t *)(this + 4) == 1 )
  {
    if ( *(uint32_t *)(this + 16) != 0 )  // 若 this 偏移 16 非 0
      j_j__free(*(void **)(this + 16));  // free this+16
    fld_C = *(void **)(this + 12);
    *(uint32_t *)(this + 16) = 0;  // this+16（uint32 槽）= 0
    if ( fld_C != nullptr )  // 若 fld_C 非空
      j_j__free(fld_C);
    *(uint32_t *)(this + 12) = 0;  // this+12（uint32 槽）= 0
    *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x40F470 sub_40F470 —— DIB 行指针表构建（4×高；步距 this+20，基址 this+12）
// 旧表先 free；重分配 4×height 后逐行 = 基址 + 2×行距像素。
// ------------------------------------------------------------
int /*thiscall*/ sub_40F470(int this)  // 函数 DIB 行指针表构建（4×高；步距 this+20，基址 this+12）
{
  uint32_t *pMem; // eax
  int fld_182; // ebx
  unsigned int v5; // ecx
  int v6; // edx
  int fld_C; // edi
  size_t fld_18; // [esp-4h] [ebp-8h]

  if ( *(uint32_t *)(this + 12) == 0 )  // 若 this 偏移 12 为 0
    return -2147483647;  // 返回 0x80000001（未就绪）
  if ( *(uint32_t *)(this + 16) != 0 )  // 若 this 偏移 16 非 0
    j_j__free(*(void **)(this + 16));  // free this+16
  fld_18 = 4 * *(uint32_t *)(this + 24);
  *(uint32_t *)(this + 16) = 0;  // this+16（uint32 槽）= 0
  pMem = operator new(fld_18);
  if ( pMem == nullptr )  // 若 pMem 为空
    return -2147483640;  // 返回 0x80000008（内存不足）
  fld_182 = *(uint32_t *)(this + 24);
  v5 = 0;
  v6 = 0;
  fld_C = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 16) = pMem;  // this+16 = pMem
  if ( fld_182 != 0 )  // 若 fld_182 != 0
  {
    do  // do 循环体
    {
      pMem[v5] = fld_C + 2 * v6;
      v6 += *(uint32_t *)(this + 20);
      ++v5;  // v5 自增
    }
    while ( v5 < *(uint32_t *)(this + 24) );
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x40F4E0 sub_40F4E0 —— 越界判定（true = 需裁剪；含宽 this+20 高 this+24）
// 参数 pArg4 为裁剪矩形：起点+宽高越出即返回 true。
// ------------------------------------------------------------
bool /*thiscall*/ sub_40F4E0(uint32_t *this, int nArg2, int nArg3, uint32_t *pArg4)  // 函数 越界判定（true = 需裁剪；含宽 this+20 高 this+24）
{
  if ( nArg2 < *pArg4 )
    return true;
  if ( nArg3 < pArg4[1] || nArg2 + *(this + 5) > pArg4[2] )
    return true;
  return nArg3 + *(this + 6) > pArg4[3];
}



// ------------------------------------------------------------
// 0x40F530 sub_40F530 —— 点越界判定（true = 越界）
// —— 与 ·sub_40F4E0 同族（点式比较，无宽高参与）。
// ------------------------------------------------------------
bool /*stdcall*/ sub_40F530(int nArg1, int nArg2, uint32_t *pArg3)  // 函数 点越界判定（true = 越界）
{
  if ( nArg1 < *pArg3 )
    return true;
  if ( nArg2 < pArg3[1] || nArg1 >= pArg3[2] )
    return true;
  return nArg2 >= pArg3[3];
}



// ------------------------------------------------------------
// 0x40F560 sub_40F560 —— 全表填充（RGB888→565 打包；逐行 dword 铺满）
// 565：uArg2>>19 取 R5、(uArg2>>5)&0x7E0 取 G6、&0xF8 取 B5。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_40F560(int this, unsigned int uArg2)  // 函数 全表填充（RGB888→565 打包；逐行 dword 铺满）
{
  int16_t uArg22; // bx
  int16_t v3; // dx
  unsigned int v4; // edi
  int v5; // esi
  unsigned int result; // eax
  uint16_t *v7; // edx
  unsigned int v8; // eax
  int fld_10; // [esp+Ch] [ebp-4h]

  uArg22 = uArg2;
  fld_10 = *(uint32_t *)(this + 16);
  LOBYTE(v3) = 0;
  HIBYTE(v3) = uArg2 & 0xF8;
  v4 = 0;
  v5 = (uint16_t)(v3 | (uArg2 >> 19) & 0x1F | (uArg2 >> 5) & 0x7E0)
     | ((uint16_t)(v3 | (uArg2 >> 19) & 0x1F | (uArg2 >> 5) & 0x7E0) << 16);
  result = *(uint32_t *)(this + 24);
  if ( result != 0 )  // 若 result != 0
  {
    do  // do 循环体
    {
      v7 = *(uint16_t **)(fld_10 + 4 * v4);
      if ( (*(uint8_t *)(this + 20) & 1) != 0 )
        *v7++ = uArg22;
      v8 = 0;
      if ( (*(uint32_t *)(this + 20) & 0xFFFFFFFE) != 0 )
      {
        do  // do 循环体
          *(uint32_t *)&v7[2 * v8++] = v5;
        while ( v8 < *(uint32_t *)(this + 20) >> 1 );
        uArg22 = uArg2;
      }
      result = *(uint32_t *)(this + 24);
      ++v4;  // v4 自增
    }
    while ( v4 < result );  // 当 v4 < result 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F5F0 sub_40F5F0 —— 像素写入（RECT 边界内写 565 值）
// 边界 this+48 起 RECT；行表 this+16。
// ------------------------------------------------------------
int /*thiscall*/ sub_40F5F0(uint32_t *this, int nArg2, int nArg3, unsigned int uArg4)  // 函数 像素写入（RECT 边界内写 565 值）
{
  int result; // eax
  int16_t v5; // bx

  result = *(this + 12);  // result = this+12
  if ( nArg2 >= result )  // 若 nArg2 >= result
  {
    result = *(this + 13);  // result = this+13
    if ( nArg3 >= result && nArg2 < *(this + 14) && nArg3 < *(this + 15) )
    {
      LOBYTE(v5) = 0;
      HIBYTE(v5) = uArg4 & 0xF8;
      result = *(this + 4);  // result = this+4
      *(uint16_t *)(*(uint32_t *)(result + 4 * nArg3) + 2 * nArg2) = v5 | (uArg4 >> 19) & 0x1F | (uArg4 >> 5) & 0x7E0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F650 sub_40F650 —— 像素读取（565 → 888 位展开）
// 越界返回 0；分量按位左移回 32 位色。【推断: 展开位宽】
// ------------------------------------------------------------
int /*thiscall*/ sub_40F650(uint32_t *this, int nArg2, int nArg3)  // 函数 像素读取（565 → 888 位展开）
{
  int16_t fld_e4; // cx

  if ( nArg2 < *(this + 12) || nArg3 < *(this + 13) || nArg2 >= *(this + 14) || nArg3 >= *(this + 15) )
    return 0;
  fld_e4 = *(uint16_t *)(*(uint32_t *)(*(this + 4) + 4 * nArg3) + 2 * nArg2);
  return 8 * (fld_e4 & 0x1F | (4 * (fld_e4 & 0x7E0 | (8 * (fld_e4 & 0xF800)))));
}



// ------------------------------------------------------------
// 0x40F6A0 sub_40F6A0 —— 水平条填充（起 x,y 长 uArg4，色 uArg5 打包 565）
// 奇数长度先写 1 像素再 dword 铺。
// ------------------------------------------------------------
int /*thiscall*/ sub_40F6A0(uint32_t *this, int nArg2, int nArg3, unsigned int uArg4, unsigned int uArg5)  // 函数 水平条填充（起 x,y 长 uArg4，色 uArg5 打包 565）
{
  uint16_t *fld_e4; // edi
  uint16_t v6; // dx
  int v7; // eax
  int result; // eax

  fld_e4 = (uint16_t *)(*(uint32_t *)(*(this + 4) + 4 * nArg3) + 2 * nArg2);
  LOBYTE(v6) = 0;
  HIBYTE(v6) = uArg5 & 0xF8;
  v7 = v6 | (uArg5 >> 19) & 0x1F | (uArg5 >> 5) & 0x7E0;
  if ( (uArg4 & 1) != 0 )  // 若位测试非 0
    *fld_e4++ = v7;
  result = (uint16_t)v7 | ((uint16_t)v7 << 16);
  if ( uArg4 >> 1 != 0 )
    memset32(fld_e4, result, uArg4 >> 1);
  return result;
}



// ------------------------------------------------------------
// 0x40F700 sub_40F700 —— 垂直条填充（行表跨 nArg4 行逐行写）
// —— 与 ·sub_40F6A0 对称（行列互换）。
// ------------------------------------------------------------
int /*thiscall*/ sub_40F700(uint32_t *this, int nArg2, int nArg3, int nArg4, unsigned int uArg5)  // 函数 垂直条填充（行表跨 nArg4 行逐行写）
{
  uint16_t v5; // dx
  int result; // eax
  int nArg42; // edx
  int *fld_e4; // ecx
  int v9; // esi

  LOBYTE(v5) = 0;
  HIBYTE(v5) = uArg5 & 0xF8;
  result = v5 | (uArg5 >> 19) & 0x1F | (uArg5 >> 5) & 0x7E0;
  nArg42 = nArg4;
  if ( nArg4 != 0 )  // 若 nArg4 != 0
  {
    fld_e4 = (int *)(*(this + 4) + 4 * nArg3);
    do  // do 循环体
    {
      v9 = *fld_e4++;
      --nArg42;
      *(uint16_t *)(v9 + 2 * nArg2) = result;
    }
    while ( nArg42 != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F750 sub_40F750 —— 直线绘制（Bresenham；逐点虚发 +32 出图）
// 迭代 = max(|dx|,|dy|)+1 次，按误差换步进方向。
// ------------------------------------------------------------
int /*thiscall*/ sub_40F750(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数 直线绘制（Bresenham；逐点虚发 +32 出图）
{
  int v6; // ecx
  signed int v7; // edi
  signed int v8; // ebx
  int v9; // esi
  int result; // eax
  int v11; // eax
  bool v12; // cc
  int v14; // [esp+10h] [ebp-Ch]
  int nArg22; // [esp+14h] [ebp-8h]
  int nArg32; // [esp+18h] [ebp-4h]
  int nArg33; // [esp+24h] [ebp+8h]
  int v18; // [esp+28h] [ebp+Ch]
  int nArg23; // [esp+2Ch] [ebp+10h]
  int v20; // [esp+30h] [ebp+14h]

  v6 = nArg4 - nArg2;
  nArg22 = nArg2;
  nArg32 = nArg3;
  v7 = abs32(nArg4 - nArg2);
  v8 = abs32(nArg5 - nArg3);
  v20 = nArg5 - nArg3;
  v14 = nArg4 - nArg2;
  v9 = v7;
  if ( v7 <= v8 )
    v9 = v8;
  result = nArg2;
  nArg23 = nArg2;
  nArg33 = nArg3;
  if ( v9 >= 0 )  // 若 v9 >= 0
  {
    v18 = v9 + 1;
    while ( 1 )  // 当 1 非 0 循环
    {
      v11 = v7 + nArg22;
      v12 = v7 + nArg22 <= v9;
      nArg22 += v7;
      nArg32 += v8;
      if ( !v12 )
      {
        nArg22 = v11 - v9;
        nArg23 += 2 * (v6 >= 0) - 1;
      }
      if ( nArg32 > v9 )
      {
        nArg32 -= v9;
        nArg33 += 2 * (v20 >= 0) - 1;
      }
      result = (*(int (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, nArg23, nArg33, nArg6);  // 调用虚函数/间接调用
      if ( --v18 == 0 )
        break;  // 跳出 switch
      v6 = v14;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F830 sub_40F830 —— 圆轮廓绘制（八向对称点虚发 +32；迭代 uArg4 步）
// uArg4==0 退化为单点一次出图。【推断: 圆弧描点】
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_40F830(void *this, int nArg2, int nArg3, unsigned int uArg4, int nArg5)  // 函数 圆轮廓绘制（八向对称点虚发 +32；迭代 uArg4 步）
{
  unsigned int result; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // edx
  int v11; // [esp+Ch] [ebp-10h]
  int v12; // [esp+10h] [ebp-Ch]
  unsigned int v13; // [esp+14h] [ebp-8h]
  unsigned int uArg42; // [esp+18h] [ebp-4h]
  int i; // [esp+2Ch] [ebp+10h]
  int v16; // [esp+30h] [ebp+14h]

  if ( uArg4 == 0 )  // 若 uArg4 == 0
    return (*(int (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, nArg2, nArg3, nArg5);  // 调用虚函数并返回
  uArg42 = uArg4;
  v13 = 0;
  v7 = nArg2 + uArg4;
  v8 = nArg2 - uArg4;
  v9 = nArg3 - nArg2;
  v12 = nArg2 - nArg3;
  for ( i = nArg3 - nArg2; ; v9 = i )
  {
    v16 = v7 - 1;
    v11 = v9 + v7 - 1;
    --uArg42;
    ++v8;  // v8 自增
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, nArg2, v11, nArg5);  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v16, i + nArg2, nArg5);  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v12 + nArg3, v11, nArg5);  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v8, i + nArg2, nArg5);  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, nArg2, i + v8, nArg5);  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v16, nArg3, nArg5);  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v12 + nArg3, i + v8, nArg5);  // 调用虚函数/间接调用
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v8, nArg3, nArg5);  // 调用虚函数/间接调用
    result = v13 + 1;
    v13 = result;
    ++nArg2;
    --nArg3;
    if ( result >= uArg42 )  // 若 result >= uArg42
      break;  // 跳出 switch
    v7 = v16;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F970 sub_40F970 —— 矩形边框（两横虚发 +36 + 两纵虚发 +40）
// ------------------------------------------------------------
int /*thiscall*/ sub_40F970(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数 矩形边框（两横虚发 +36 + 两纵虚发 +40）
{
  (*(void (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 36))(this, nArg2, nArg3, nArg4, nArg6);  // 调用虚函数/间接调用
  (*(void (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 36))(this, nArg2, nArg3 + nArg5 - 1, nArg4, nArg6);  // 调用虚函数/间接调用
  (*(void (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 40))(this, nArg2, nArg3, nArg5, nArg6);  // 调用虚函数/间接调用
  return (*(int (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 40))(this, nArg2 + nArg4 - 1, nArg3, nArg5, nArg6);  // 调用虚函数并返回
}



// ------------------------------------------------------------
// 0x40F9E0 sub_40F9E0 —— 矩形填充（uArg5 行逐行虚发 +36 横描）
// ------------------------------------------------------------
int /*thiscall*/ sub_40F9E0(void *this, int nArg2, int nArg3, int nArg4, unsigned int uArg5, int nArg6)  // 函数 矩形填充（uArg5 行逐行虚发 +36 横描）
{
  unsigned int i; // esi
  int result; // eax

  for ( i = 0; i < uArg5; ++i )
    result = (*(int (/*thiscall*/ **)(void *, int, unsigned int, int, int))(*(uint32_t *)this + 36))(
               this,
               nArg2,
               i + nArg3,
               nArg4,
               nArg6);
  return result;
}



// ------------------------------------------------------------
// 0x40FA20 sub_40FA20 —— 精灵贴图拷贝（逐行 qmemcpy；目标行表 pArg4+16）
// 双侧 +4 就绪且 ·sub_40F4E0 未越界才拷贝；行字节 2×this+20。
// ------------------------------------------------------------
char /*thiscall*/ sub_40FA20(int this, int nArg2, int nArg3, int pArg4)  // 函数 精灵贴图拷贝（逐行 qmemcpy；目标行表 pArg4+16）
{
  unsigned int v5; // eax
  int v7; // edi
  unsigned int fld_14; // edx
  unsigned int fld_18; // [esp+4h] [ebp-4h]
  uint32_t *v11; // [esp+10h] [ebp+8h]
  int v12; // [esp+14h] [ebp+Ch]
  int fld_10; // [esp+18h] [ebp+10h]

  LOBYTE(v5) = *(uint8_t *)(this + 4);
  if ( (uint8_t)v5 != 0 )
  {
    LOBYTE(v5) = *(uint8_t *)(pArg4 + 4);
    if ( (uint8_t)v5 != 0 )
    {
      LOBYTE(v5) = sub_40F4E0((uint32_t *)this, nArg2, nArg3, (uint32_t *)(pArg4 + 48));  // 调 越界判定（true = 需裁剪；含宽 this+20 高 this+24）
      if ( (uint8_t)v5 == 0 )
      {
        v7 = *(uint32_t *)(pArg4 + 16);
        fld_10 = *(uint32_t *)(this + 16);
        fld_14 = 2 * *(uint32_t *)(this + 20);
        v5 = 0;
        fld_18 = *(uint32_t *)(this + 24);
        if ( fld_18 != 0 )  // 若 fld_18 != 0
        {
          v12 = 2 * nArg2;
          v11 = (uint32_t *)(v7 + 4 * nArg3);
          do  // do 循环体
            qmemcpy((void *)(v12 + *v11++), *(const void **)(fld_10 + 4 * v5++), fld_14);  // 调 qmemcpy
          while ( v5 < fld_18 );  // 当 v5 < fld_18 循环
        }
      }
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x40FAC0 sub_40FAC0 —— 精灵贴图·32→565（·sub_4055B0 转换填充）
// —— 与 ·sub_40FA20 同构（差异：转换型逐像素）。
// ------------------------------------------------------------
char /*thiscall*/ sub_40FAC0(int this, int nArg2, int nArg3, int pArg4, unsigned int uArg5)  // 函数 精灵贴图·32→565（·sub_4055B0 转换填充）
{
  unsigned int fld_14; // eax
  int fld_10; // ecx
  int v8; // edi
  unsigned int fld_18; // ebx
  unsigned int v10; // esi
  uint32_t *v11; // edi
  int fld_102; // [esp+4h] [ebp-4h]
  int v14; // [esp+10h] [ebp+8h]
  unsigned int fld_142; // [esp+18h] [ebp+10h]

  LOBYTE(fld_14) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_14 != 0 )
  {
    LOBYTE(fld_14) = *(uint8_t *)(pArg4 + 4);
    if ( (uint8_t)fld_14 != 0 )
    {
      LOBYTE(fld_14) = sub_40F4E0((uint32_t *)this, nArg2, nArg3, (uint32_t *)(pArg4 + 48));  // 调 越界判定（true = 需裁剪；含宽 this+20 高 this+24）
      if ( (uint8_t)fld_14 == 0 )
      {
        fld_14 = *(uint32_t *)(this + 20);
        fld_10 = *(uint32_t *)(this + 16);
        v8 = *(uint32_t *)(pArg4 + 16);
        fld_18 = *(uint32_t *)(this + 24);
        v10 = 0;
        fld_142 = fld_14;
        fld_102 = fld_10;
        if ( fld_18 != 0 )  // 若 fld_18 != 0
        {
          v14 = 2 * nArg2;
          v11 = (uint32_t *)(v8 + 4 * nArg3);
          do  // do 循环体
            LOBYTE(fld_14) = sub_4055B0((uint16_t *)(v14 + *v11++), *(uint32_t *)(fld_102 + 4 * v10++), fld_142, uArg5);  // 调 像素填充 A（32 位色源截 5/6/5 位打包为 565 色，填 16 位缓冲）
          while ( v10 < fld_18 );  // 当 v10 < fld_18 循环
        }
      }
    }
  }
  return fld_14;
}



// ------------------------------------------------------------
// 0x40FB50 sub_40FB50 —— 精灵贴图·灰度（·sub_405630）
// —— 与 ·sub_40FA20 同构（差异：565 灰度化例程）。
// ------------------------------------------------------------
char /*thiscall*/ sub_40FB50(int this, int nArg2, int nArg3, int pArg4)  // 函数 精灵贴图·灰度（·sub_405630）
{
  unsigned int fld_14; // eax
  int fld_10; // ecx
  int v7; // edi
  unsigned int fld_18; // ebx
  unsigned int v9; // esi
  uint32_t *v10; // edi
  int fld_102; // [esp+4h] [ebp-4h]
  int v13; // [esp+10h] [ebp+8h]
  unsigned int fld_142; // [esp+18h] [ebp+10h]

  LOBYTE(fld_14) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_14 != 0 )
  {
    LOBYTE(fld_14) = *(uint8_t *)(pArg4 + 4);
    if ( (uint8_t)fld_14 != 0 )
    {
      LOBYTE(fld_14) = sub_40F4E0((uint32_t *)this, nArg2, nArg3, (uint32_t *)(pArg4 + 48));  // 调 越界判定（true = 需裁剪；含宽 this+20 高 this+24）
      if ( (uint8_t)fld_14 == 0 )
      {
        fld_14 = *(uint32_t *)(this + 20);
        fld_10 = *(uint32_t *)(this + 16);
        v7 = *(uint32_t *)(pArg4 + 16);
        fld_18 = *(uint32_t *)(this + 24);
        v9 = 0;
        fld_142 = fld_14;
        fld_102 = fld_10;
        if ( fld_18 != 0 )  // 若 fld_18 != 0
        {
          v13 = 2 * nArg2;
          v10 = (uint32_t *)(v7 + 4 * nArg3);
          do  // do 循环体
            LOBYTE(fld_14) = sub_405630((uint16_t *)(v13 + *v10++), *(uint16_t **)(fld_102 + 4 * v9++), fld_142);  // 调 像素灰度 B（565 源按 R*0.222 + G*0.707 + B*0.071 亮度加权重打包，双像素并行）
          while ( v9 < fld_18 );  // 当 v9 < fld_18 循环
        }
      }
    }
  }
  return fld_14;
}



// ------------------------------------------------------------
// 0x40FBE0 sub_40FBE0 —— 精灵贴图·查表混合（·sub_4057E0；参数 nArg5+(nArg6<<12)）
// —— 与 ·sub_40FA20 同构（差异：混合例程带附加参数）。
// ------------------------------------------------------------
char /*thiscall*/ sub_40FBE0(int this, int nArg2, int nArg3, int pArg4, int nArg5, int nArg6)  // 函数 精灵贴图·查表混合（·sub_4057E0；参数 nArg5+(nArg6<<12)）
{
  int v7; // eax
  unsigned int fld_14; // eax
  int fld_10; // ecx
  unsigned int fld_18; // ebx
  unsigned int v11; // esi
  uint32_t *v12; // edi
  int fld_102; // [esp+4h] [ebp-8h]
  unsigned int fld_142; // [esp+8h] [ebp-4h]
  int v16; // [esp+14h] [ebp+8h]

  LOBYTE(v7) = *(uint8_t *)(this + 4);
  if ( (uint8_t)v7 != 0 )
  {
    LOBYTE(v7) = *(uint8_t *)(pArg4 + 4);
    if ( (uint8_t)v7 != 0 )
    {
      LOBYTE(v7) = sub_40F4E0((uint32_t *)this, nArg2, nArg3, (uint32_t *)(pArg4 + 48));  // 调 越界判定（true = 需裁剪；含宽 this+20 高 this+24）
      if ( (uint8_t)v7 == 0 )
      {
        fld_14 = *(uint32_t *)(this + 20);
        fld_10 = *(uint32_t *)(this + 16);
        fld_18 = *(uint32_t *)(this + 24);
        v11 = 0;
        fld_142 = fld_14;
        v7 = *(uint32_t *)(pArg4 + 16);
        fld_102 = fld_10;
        if ( fld_18 != 0 )  // 若 fld_18 != 0
        {
          v16 = 2 * nArg2;
          v12 = (uint32_t *)(v7 + 4 * nArg3);
          do  // do 循环体
            LOBYTE(v7) = (uint8_t)sub_4057E0(  // 调 查表混合 C（逐 5 位分量以 源/目标低位索引 32×32 表 pArg4 后按 6 位步长打包）
                                            (unsigned int *)(v16 + *v12++),
                                            *(char **)(fld_102 + 4 * v11++),
                                            fld_142,
                                            nArg5 + (nArg6 << 12));
          while ( v11 < fld_18 );  // 当 v11 < fld_18 循环
        }
      }
    }
  }
  return v7;
}



// ------------------------------------------------------------
// 0x40FC80 sub_40FC80 —— 贴图转发（目标对象虚发 +152(this, x, y)）
// 目标为空直接返回。
// ------------------------------------------------------------
int /*thiscall*/ sub_40FC80(void *this, int nArg2, int nArg3, int nArg4)  // 函数 贴图转发（目标对象虚发 +152(this, x, y)）
{
  int result; // eax

  result = nArg4;
  if ( nArg4 != 0 )  // 若 nArg4 != 0
    return (*(int (/*thiscall*/ **)(int, int, int, void *))(*(uint32_t *)nArg4 + 152))(nArg4, nArg2, nArg3, this);  // 调用虚函数并返回
  return result;
}



// ------------------------------------------------------------
// 0x40FCB0 sub_40FCB0 —— 矩形求交（写 pArg1；返回是否非空）
// 交矩形：x/y 取大、右下取小。
// ------------------------------------------------------------
bool /*cdecl*/ sub_40FCB0(float *pArg1, float *pArg2, float *pArg3)  // 函数 矩形求交（写 pArg1；返回是否非空）
{
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st5
  bool result; // al
  float v9; // [esp+Ch] [ebp+Ch]
  float v10; // [esp+10h] [ebp+10h]

  if ( *pArg2 <= (double)*pArg3 )
    v4 = *pArg3;  // v4 = 解引用 pArg3
  else  // 否则分支
    v4 = *pArg2;  // v4 = 解引用 pArg2
  *pArg1 = v4;  // 写指针 = v4
  if ( pArg2[2] >= (double)pArg3[2] )
    v5 = pArg3[2];
  else  // 否则分支
    v5 = pArg2[2];
  pArg1[2] = v5;
  if ( pArg2[1] <= (double)pArg3[1] )
    v6 = pArg3[1];
  else  // 否则分支
    v6 = pArg2[1];
  v9 = v6;
  pArg1[1] = v6;
  if ( pArg2[3] >= (double)pArg3[3] )
    v7 = pArg3[3];
  else  // 否则分支
    v7 = pArg2[3];
  pArg1[3] = v7;
  result = false;
  if ( v4 < v5 )
  {
    v10 = v7;
    if ( v9 < (double)v10 )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40FD50 sub_40FD50 —— 状态复位（+76..+132 字段清零）
// ------------------------------------------------------------
int /*thiscall*/ sub_40FD50(int this)  // 函数 状态复位（+76..+132 字段清零）
{
  *(uint8_t *)(this + 76) = 0;  // this 偏移 76 清 0
  *(uint32_t *)(this + 80) = 0;  // this+80（uint32 槽）= 0
  *(uint32_t *)(this + 84) = 0;  // this+84（uint32 槽）= 0
  *(uint32_t *)(this + 88) = 0;  // this+88（uint32 槽）= 0
  *(uint32_t *)(this + 92) = 0;  // this+92（uint32 槽）= 0
  *(uint32_t *)(this + 96) = 0;  // this+96（uint32 槽）= 0
  *(uint32_t *)(this + 100) = 0;  // this+100（uint32 槽）= 0
  *(uint32_t *)(this + 104) = 0;  // this+104（uint32 槽）= 0
  *(uint32_t *)(this + 108) = 0;  // this+108（uint32 槽）= 0
  *(uint32_t *)(this + 112) = 0;  // this+112（uint32 槽）= 0
  *(uint32_t *)(this + 116) = 0;  // this+116（uint32 槽）= 0
  *(uint32_t *)(this + 128) = 0;  // this+128（uint32 槽）= 0
  *(uint32_t *)(this + 132) = 0;  // this+132（uint32 槽）= 0
  return 0;
}



// ------------------------------------------------------------
// 0x40FD90 sub_40FD90 —— 表面附加（虚发 +12(w,h)；格式 8/16/14/15 换绑，11 走 +84/+88 直贴）
// 换绑：暂清面尺寸→虚发 +152→回填尺寸到 this+28/+32 及该面 +36/+40。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_40FD90(uint32_t *this, int *pDwArg2)  // 函数 表面附加（虚发 +12(w,h)；格式 8/16/14/15 换绑，11 走 +84/+88 直贴）
{
  int result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // ebx
  int fld_e9; // ecx
  int fld_e10; // eax
  int v11; // [esp+10h] [ebp+8h]

  result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, pDwArg2[5], pDwArg2[6]);  // 调用虚函数/间接调用
  if ( result >= 0 )  // 若 result >= 0
  {
    v5 = pDwArg2[2];
    if ( v5 == 8 || v5 == 16 || v5 == 14 || v5 == 15 )
    {
      v6 = pDwArg2[8];
      v7 = *pDwArg2;  // v7 = 解引用 pDwArg2
      v8 = pDwArg2[7];
      pDwArg2[7] = 0;
      pDwArg2[8] = 0;
      v11 = v6;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t *))(v7 + 152))(pDwArg2, 0, 0, this);  // 调用虚函数/间接调用
      pDwArg2[7] = v8;
      pDwArg2[8] = v11;
      fld_e9 = *(this + 9);  // fld_e9 = this+9 字段
      *(this + 8) = v11;
      fld_e10 = *(this + 10);  // fld_e10 = this+10 字段
      *(this + 7) = v8;
      pDwArg2[9] = fld_e9;
      pDwArg2[10] = fld_e10;
    }
    else if ( v5 == 11 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);  // 调 this 虚函数
      sub_40FC80(this, 0, 0, (int)pDwArg2);  // 调 sub_40FC80
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);  // 调 this 虚函数
      return 1;  // 返回 1（成功）
    }
    return 1;  // 返回 1（成功）
  }
  return result;
}



// ------------------------------------------------------------
// 0x40FE40 sub_40FE40 —— 精灵建立（源 +56 取尺寸；格式==1 走 +60 目标面与 +172 创建）
// 失败路径虚发 +20 释放并回错误码。【推断: 尺寸源虚表 +56】
// ------------------------------------------------------------
int /*thiscall*/ sub_40FE40(char *this, int nArg2)  // 函数 精灵建立（源 +56 取尺寸；格式==1 走 +60 目标面与 +172 创建）
{
  int v4; // ecx
  int v5; // eax
  int pThis_1C; // edi
  int pThis_1A; // edx
  int v8; // eax
  int v9; // [esp-Ch] [ebp-30h]
  int v10; // [esp-8h] [ebp-2Ch]
  char v11[12]; // [esp+4h] [ebp-20h] BYREF
  int v12; // [esp+10h] [ebp-14h]
  int xRight; // [esp+1Ch] [ebp-8h]
  int yBottom; // [esp+20h] [ebp-4h]

  if ( *(this + 4) != 0 )
    return -2147483646;  // 返回 0x80000002（已初始化）
  *(this + 4) = 1;  // this+4 = 1
  (*(void (/*stdcall*/ **)(int, uint32_t, char *))(*(uint32_t *)nArg2 + 56))(nArg2, 0, v11);  // 调用虚函数/间接调用
  v4 = yBottom;
  v5 = xRight;
  v10 = yBottom;
  v9 = xRight;
  *((uint32_t *)this + 28) = nArg2;  // this 偏移 112 = 参数2
  *((uint32_t *)this + 5) = v5;  // this 偏移 20 = v5
  *((uint32_t *)this + 6) = v4;  // this 偏移 24 = v4
  *((uint32_t *)this + 9) = v5;  // this 偏移 36 = v5
  *((uint32_t *)this + 10) = v4;  // this 偏移 40 = v4
  *(this + 76) = 1;  // this+76 = 1
  SetRect((LPRECT)(this + 88), 0, 0, v9, v10);
  SetRect(
    (LPRECT)this + 3,
    0,
    0,
    *((uint32_t *)this + 5) + *((uint32_t *)this + 7),
    *((uint32_t *)this + 6) + *((uint32_t *)this + 8));
  if ( v12 != 1 )  // 若 v12 != 1
    return 1;  // 返回 1（成功）
  pThis_1C = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, char *))(**((uint32_t **)this + 28) + 60))(
         *((uint32_t *)this + 28),
         0,
         this + 116);
  if ( pThis_1C >= 0 )  // 若 pThis_1C >= 0
  {
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 84))(this);  // 调 this 虚函数
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 88))(this);  // 调 this 虚函数
    pThis_1A = *((uint32_t *)this + 26);  // pThis_1A = this 偏移 26
    v8 = *(uint32_t *)this;
    *((uint32_t *)this + 3) = *((uint32_t *)this + 27);  // this 偏移 12 = *((uint32_t *)this + 27)
    *((uint32_t *)this + 20) = pThis_1A;  // this 偏移 80 = pThis_1A
    pThis_1C = (*(int (/*thiscall*/ **)(char *))(v8 + 172))(this);
    if ( pThis_1C >= 0 )  // 若 pThis_1C >= 0
      return 1;  // 返回 1（成功）
  }
  (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 20))(this);  // 调 this 虚函数
  return pThis_1C;
}



// ------------------------------------------------------------
// 0x40FF30 sub_40FF30 —— 精灵销毁（·sub_405060 计数回退；+116/+112 虚发 +8 释放；free 行表）
// +76==0 时连 +112 一并释放。
// ------------------------------------------------------------
int /*thiscall*/ sub_40FF30(int this)  // 函数 精灵销毁（·sub_405060 计数回退；+116/+112 虚发 +8 释放；free 行表）
{
  int fld_74; // eax
  bool fld_4C; // zf
  int fld_70; // eax

  if ( *(uint8_t *)(this + 4) != 0 )  // 若 this 偏移 4 非 0
  {
    sub_405060(1u, -4 * *(uint32_t *)(this + 24) - *(uint32_t *)(this + 80) * *(uint32_t *)(this + 84), 0);  // 调 sub_405060
    fld_74 = *(uint32_t *)(this + 116);
    if ( fld_74 != 0 )  // 若 fld_74 != 0
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_74 + 8))(*(uint32_t *)(this + 116));  // 调用虚函数/间接调用
    fld_4C = *(uint8_t *)(this + 76) == 0;
    *(uint32_t *)(this + 116) = 0;  // this+116（uint32 槽）= 0
    if ( fld_4C )
    {
      fld_70 = *(uint32_t *)(this + 112);
      if ( fld_70 != 0 )  // 若 fld_70 != 0
        (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_70 + 8))(*(uint32_t *)(this + 112));  // 调用虚函数/间接调用
      *(uint32_t *)(this + 112) = 0;  // this+112（uint32 槽）= 0
    }
    if ( *(uint32_t *)(this + 16) != 0 )  // 若 this 偏移 16 非 0
      j_j__free(*(void **)(this + 16));  // free this+16
    *(uint32_t *)(this + 16) = 0;  // this+16（uint32 槽）= 0
    *(uint32_t *)(this + 112) = 0;  // this+112（uint32 槽）= 0
    *(uint32_t *)(this + 116) = 0;  // this+116（uint32 槽）= 0
    *(uint32_t *)(this + 88) = 0;  // this+88（uint32 槽）= 0
    *(uint32_t *)(this + 92) = 0;  // this+92（uint32 槽）= 0
    *(uint32_t *)(this + 96) = 0;  // this+96（uint32 槽）= 0
    *(uint32_t *)(this + 100) = 0;  // this+100（uint32 槽）= 0
    *(uint32_t *)(this + 104) = 0;  // this+104（uint32 槽）= 0
    *(uint32_t *)(this + 108) = 0;  // this+108（uint32 槽）= 0
    *(uint8_t *)(this + 76) = 0;  // this 偏移 76 清 0
    *(uint8_t *)(this + 4) = 0;  // this 偏移 4 清 0
  }
  return 1;  // 返回 1（成功）
}



// ------------------------------------------------------------
// 0x40FFC0 sub_40FFC0 —— 表面锁定（对 this+112 对象虚发 +64；+104/+48 回填；+44 置锁标志）
// 已锁（+44!=0）返回 -2147483642。
// ------------------------------------------------------------
int /*thiscall*/ sub_40FFC0(int this)  // 函数 表面锁定（对 this+112 对象虚发 +64；+104/+48 回填；+44 置锁标志）
{
  int result; // eax

  if ( *(uint8_t *)(this + 44) != 0 )  // 若 this 偏移 44 非 0
    return -2147483642;  // 返回错误码 -2147483642
  result = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 112) + 64))(
             *(uint32_t *)(this + 112),
             0,
             this + 104,
             this + 48,
             0);
  if ( result >= 0 )  // 若 result >= 0
  {
    *(uint8_t *)(this + 44) = 1;
    return 1;  // 返回 1（成功）
  }
  return result;
}


