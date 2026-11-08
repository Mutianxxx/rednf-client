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
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x401010 sub_401010
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_401010(uint8_t *Block, char pszArg2)
{
  *(uint32_t *)Block = &nengine::IObject::`vftable';
  *(Block + 4) = 0;
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x401040 sub_401040
// ------------------------------------------------------------
void /*thiscall*/ sub_401040(uint32_t *this)
{
  sub_41A630((unsigned int)this);
  *this = &clong::`vftable';
}



// ------------------------------------------------------------
// 0x401060 sub_401060
// ------------------------------------------------------------
// attributes: thunk
void /*thiscall*/ sub_401060(void **this)
{
  sub_41B010(this);
}



// ------------------------------------------------------------
// 0x401090 sub_401090
// ------------------------------------------------------------
int sub_401090()
{
  uint32_t *pMem; // eax

  pMem = operator new(4u);
  if ( pMem == nullptr )
    return -2147483640;
  *pMem = &off_6C1570;
  dword_79C55C = (int)pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x4010C0 sub_4010C0
// ------------------------------------------------------------
char */*thiscall*/ sub_4010C0(char *this)
{
  sub_402780(this + 8);
  return this;
}



// ------------------------------------------------------------
// 0x4010D0 sub_4010D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4010D0(char *this)
{
  return sub_402740(this + 8);
}



// ------------------------------------------------------------
// 0x4010E0 sub_4010E0
// ------------------------------------------------------------
int sub_4010E0()
{
  sub_403400();
  sub_404490(&dword_79C0A0);
  if ( dword_79C55C != 0 )
  {
    (**(void (/*thiscall*/ ***)(int, int))dword_79C55C)(dword_79C55C, 1);
    dword_79C55C = 0;
  }
  if ( dword_79D078 != 0 )
  {
    (**(void (/*thiscall*/ ***)(int, int))dword_79D078)(dword_79D078, 1);
    dword_79D078 = 0;
  }
  sub_405340();
  sub_4033E0();
  byte_79C560 = 0;
  return 1;
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
  sub_404020();
  sub_403A90();
  if ( dword_79C0C0 != 0 )
    sub_402080((char *)(dword_79C0C0 + 113));
  sub_4020B0(Format);
  return sub_402440(&unk_79C0C8);
}



// ------------------------------------------------------------
// 0x401150 sub_401150
// ------------------------------------------------------------
void */*thiscall*/ sub_401150(void *Block, char pszArg2)
{
  sub_432D10(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x401170 sub_401170
// ------------------------------------------------------------
void /*thiscall*/ sub_401170(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C2B88;
  *((uint32_t *)this + 2) = 0;
  *(this + 12) = 1;
  *(this + 14) = 0;
  *(this + 13) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 4) = 0;
}



// ------------------------------------------------------------
// 0x4011C0 sub_4011C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4011C0(uint32_t *this, int nArg2)
{
  bool fld_e6; // cf
  int result; // eax

  fld_e6 = *(this + 6) < 0x10u;
  result = nArg2;
  *(this + 5) = nArg2;
  if ( fld_e6 )
    *((uint8_t *)this + nArg2 + 4) = 0;
  else
    *(uint8_t *)(*(this + 1) + nArg2) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4011E0 sub_4011E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4011E0(uint32_t *this, char pszArg2, size_t Size)
{
  void *fld_e1; // ebx

  if ( pszArg2 != 0 && *(this + 6) >= 0x10u )
  {
    fld_e1 = (void *)*(this + 1);
    if ( Size != 0 )
      memcpy(this + 1, fld_e1, Size);
    j__free(fld_e1);
  }
  *(this + 5) = Size;
  *(this + 6) = 15;
  *((uint8_t *)this + Size + 4) = 0;
}



// ------------------------------------------------------------
// 0x401230 sub_401230
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_401230(uint32_t *this, unsigned int uArg2, unsigned int uArg3)
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
    std::_String_base::_Xran((std::_String_base *)this);
  fld_e52 = uArg3;
  fld_e5 = *(this + 5) - uArg2;
  if ( fld_e5 < uArg3 )
    fld_e52 = *(this + 5) - uArg2;
  if ( fld_e52 != 0 )
  {
    fld_e6 = *(this + 6);
    pThis_1 = this + 1;
    if ( fld_e6 < 0x10 )
      pThis_12 = this + 1;
    else
      pThis_12 = (uint32_t *)*pThis_1;
    if ( fld_e6 < 0x10 )
      pThis_13 = this + 1;
    else
      pThis_13 = (uint32_t *)*pThis_1;
    memcpy_0((char *)pThis_13 + uArg2, (char *)pThis_12 + uArg2 + fld_e52, fld_e5 - fld_e52);
    fld_e62 = *(this + 6);
    fld_e53 = *(this + 5) - fld_e52;
    *(this + 5) = fld_e53;
    if ( fld_e62 >= 0x10 )
      pThis_1 = (uint32_t *)*pThis_1;
    *((uint8_t *)pThis_1 + fld_e53) = 0;
  }
  return this;
}



// ------------------------------------------------------------
// 0x4012B0 sub_4012B0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4012B0(uint32_t *this, unsigned int uArg2, size_t Size)
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
  else
  {
    fld_e6 = *(this + 6);
    v6 = fld_e6 >> 1;
    if ( uArg22 / 3 < fld_e6 >> 1 && fld_e6 <= -2 - v6 )
      uArg22 = v6 + fld_e6;
  }
  v9[8] = 0;
  pMem = operator new(uArg22 + 1);
  if ( Size != 0 )
  {
    if ( *(this + 6) < 0x10u )
      pThis_1 = this + 1;
    else
      pThis_1 = (const void *)*(this + 1);
    memcpy(pMem, pThis_1, Size);
  }
  if ( *(this + 6) >= 0x10u )
    j__free((void *)*(this + 1));
  result = this + 1;
  *((uint8_t *)this + 4) = 0;
  *(this + 1) = pMem;
  *(this + 6) = uArg22;
  *(this + 5) = Size;
  if ( uArg22 >= 0x10 )
    result = pMem;
  result[Size] = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4013E0 sub_4013E0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4013E0(size_t *this, uint8_t *uArg2, char pszArg3)
{
  unsigned int fld_e6; // eax
  uint8_t *fld_e5; // edi
  void *fld_e1; // ebp

  if ( uArg2 == (uint8_t *)-1 )
    std::_String_base::_Xlen((std::_String_base *)this);
  fld_e6 = *(this + 6);
  if ( fld_e6 < (unsigned int)uArg2 )
  {
    sub_4012B0(this, (unsigned int)uArg2, *(this + 5));
    return uArg2 != nullptr;
  }
  if ( pszArg3 != 0 && (unsigned int)uArg2 < 0x10 )
  {
    fld_e5 = (uint8_t *)*(this + 5);
    if ( uArg2 < fld_e5 )
      fld_e5 = uArg2;
    if ( fld_e6 >= 0x10 )
    {
      fld_e1 = (void *)*(this + 1);
      if ( fld_e5 != nullptr )
        memcpy(this + 1, fld_e1, (size_t)fld_e5);
      j__free(fld_e1);
    }
    *(this + 5) = (size_t)fld_e5;
    *(this + 6) = 15;
    fld_e5[(uint32_t)this + 4] = 0;
    return uArg2 != nullptr;
  }
  else
  {
    if ( uArg2 == nullptr )
    {
      *(this + 5) = 0;
      if ( fld_e6 >= 0x10 )
      {
        *(uint8_t *)*(this + 1) = 0;
        return false;
      }
      *((uint8_t *)this + 4) = 0;
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
  else
    return (uint32_t *)*(this + 4);
}



// ------------------------------------------------------------
// 0x4014B0 sub_4014B0
// ------------------------------------------------------------
void */*thiscall*/ sub_4014B0(void *Block, char pszArg2)
{
  sub_4017A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4014D0 sub_4014D0
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4014D0(size_t *this, size_t *pArg2, unsigned int uArg3, unsigned int uArg4)
{
  unsigned int uArg42; // edi
  unsigned int fld_e6; // eax
  bool v8; // zf
  uint32_t *v9; // ecx
  char **pThis_1; // ebx
  char **pThis_12; // eax
  unsigned int fld_e62; // eax

  if ( pArg2[5] < uArg3 )
    std::_String_base::_Xran((std::_String_base *)this);
  uArg42 = pArg2[5] - uArg3;
  if ( uArg4 < uArg42 )
    uArg42 = uArg4;
  if ( this == pArg2 )
  {
    sub_401230(this, uArg3 + uArg42, 0xFFFFFFFF);
    sub_401230(this, 0, uArg3);
    return this;
  }
  if ( uArg42 == -1 )
    std::_String_base::_Xlen((std::_String_base *)this);
  fld_e6 = *(this + 6);
  if ( fld_e6 >= uArg42 )
  {
    v8 = uArg42 == 0;
    if ( uArg42 == 0 )
    {
      *(this + 5) = 0;
      if ( fld_e6 < 0x10 )
        *((uint8_t *)this + 4) = 0;
      else
        *(uint8_t *)*(this + 1) = 0;
      return this;
    }
  }
  else
  {
    sub_4012B0(this, uArg42, *(this + 5));
    v8 = uArg42 == 0;
  }
  if ( !v8 )
  {
    if ( pArg2[6] < 0x10 )
      v9 = pArg2 + 1;
    else
      v9 = (uint32_t *)pArg2[1];
    pThis_1 = (char **)(this + 1);
    if ( *(this + 6) < 0x10 )
      pThis_12 = (char **)(this + 1);
    else
      pThis_12 = (char **)*pThis_1;
    memcpy(pThis_12, (char *)v9 + uArg3, uArg42);
    fld_e62 = *(this + 6);
    *(this + 5) = uArg42;
    if ( fld_e62 >= 0x10 )
      pThis_1 = (char **)*pThis_1;
    *((uint8_t *)pThis_1 + uArg42) = 0;
  }
  return this;
}



// ------------------------------------------------------------
// 0x4015C0 sub_4015C0
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

  fld_e6 = *(this + 6);
  pThis_1 = this + 1;
  if ( fld_e6 < 0x10 )
    pThis_12 = (unsigned int)(this + 1);
  else
    pThis_12 = *pThis_1;
  if ( (unsigned int)Src >= pThis_12 )
  {
    pThis_13 = fld_e6 < 0x10 ? (int)(this + 1) : *pThis_1;
    if ( pThis_13 + *(this + 5) > (unsigned int)Src )
    {
      if ( fld_e6 >= 0x10 )
        pThis_1 = (unsigned int *)*pThis_1;
      return sub_4014D0(this, this, Src - (uint8_t *)pThis_1, Size);
    }
  }
  if ( Size == -1 )
    std::_String_base::_Xlen((std::_String_base *)this);
  fld_e62 = *(this + 6);
  if ( fld_e62 < Size )
  {
    sub_4012B0(this, Size, *(this + 5));
    v10 = Size == 0;
LABEL_16:
    if ( !v10 )
    {
      if ( *(this + 6) < 0x10 )
        pThis_14 = this + 1;
      else
        pThis_14 = (void *)*pThis_1;
      memcpy(pThis_14, Src, Size);
      fld_e63 = *(this + 6);
      *(this + 5) = Size;
      if ( fld_e63 >= 0x10 )
        pThis_1 = (unsigned int *)*pThis_1;
      *((uint8_t *)pThis_1 + Size) = 0;
    }
    return this;
  }
  v10 = Size == 0;
  if ( Size != 0 )
    goto LABEL_16;
  *(this + 5) = 0;
  if ( fld_e62 >= 0x10 )
    pThis_1 = (unsigned int *)*pThis_1;
  *(uint8_t *)pThis_1 = 0;
  return this;
}



// ------------------------------------------------------------
// 0x401690 sub_401690
// ------------------------------------------------------------
int /*thiscall*/ sub_401690(int this, size_t *pArg2)
{
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((size_t *)this, pArg2, 0, 0xFFFFFFFF);
  return this;
}



// ------------------------------------------------------------
// 0x4016C0 sub_4016C0
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4016C0(size_t *this, char *Str)
{
  size_t nLen; // eax

  nLen = strlen(Str);
  return sub_4015C0(this, Str, nLen);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4016E0 sub_4016E0
// ------------------------------------------------------------
void /*stdcall*/ sub_4016E0(void **pArg1, void **pArg2)
{
  void **i; // esi

  for ( i = pArg1; i != pArg2; ++i )
    sub_41B010(i);
}



// ------------------------------------------------------------
// 0x401710 sub_401710
// ------------------------------------------------------------
int /*thiscall*/ sub_401710(int this, char *Str)
{
  size_t nLen; // eax

  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  nLen = strlen(Str);
  sub_4015C0((size_t *)this, Str, nLen);  // 【std::string构造赋值】
  return this;
}



// ------------------------------------------------------------
// 0x401740 sub_401740
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_401740(uint32_t *this, size_t *pArg2)
{
  sub_66AF9C();
  *this = &std::logic_error::`vftable';
  *(this + 8) = 0;
  *(this + 9) = 15;
  *((uint8_t *)this + 16) = 0;
  sub_4014D0(this + 3, pArg2, 0, 0xFFFFFFFF);
  return this;
}



// ------------------------------------------------------------
// 0x4017A0 sub_4017A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4017A0(void **this)
{
  *this = &std::logic_error::`vftable';
  if ( (unsigned int)*(this + 9) >= 0x10 )
    j__free(*(this + 4));
  *(this + 9) = (void *)15;
  *(this + 8) = nullptr;
  *((uint8_t *)this + 16) = 0;
  return sub_66B034(this);
}



// ------------------------------------------------------------
// 0x4017E0 sub_4017E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4017E0(int this)
{
  void **fld_4; // esi
  void **i; // edi

  fld_4 = *(void ***)(this + 4);
  if ( fld_4 != nullptr )
  {
    for ( i = *(void ***)(this + 8); fld_4 != i; ++fld_4 )
      sub_41B010(fld_4);
    j__free(*(void **)(this + 4));
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
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

  v4 = 15;
  v3 = 0;
  v2 = 0;
  nLen = strlen("vector<T> too long");
  sub_4015C0(&v1, "vector<T> too long", nLen);  // 【std::string构造赋值】
  pExceptionObject[12] = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4018B0 sub_4018B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4018B0(int this, size_t *pArg2)
{
  exception::exception((exception *)this, (const struct exception *)pArg2);
  *(uint32_t *)this = &std::logic_error::`vftable';
  *(uint32_t *)(this + 36) = 15;
  *(uint32_t *)(this + 32) = 0;
  *(uint8_t *)(this + 16) = 0;
  sub_4014D0((size_t *)(this + 12), pArg2 + 3, 0, 0xFFFFFFFF);
  return this;
}



// ------------------------------------------------------------
// 0x401920 sub_401920
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_401920(uint32_t *this, size_t *pArg2)
{
  sub_4018B0((int)this, pArg2);
  *this = &std::length_error::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x401950 sub_401950
// ------------------------------------------------------------
char /*thiscall*/ sub_401950(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x3FFFFFFF )
    sub_401830(this);
  pMem = (char *)operator new(4 * uArg2);
  *(this + 3) = &pMem[4 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x4019A0 sub_4019A0
// ------------------------------------------------------------
void /*thiscall*/ sub_4019A0(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x4019B0 sub_4019B0
// ------------------------------------------------------------
char */*thiscall*/ sub_4019B0(char *this)
{
  uint32_t *pThis_F8; // edi

  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C1588;
  *(this + 52) = 0;
  *((uint32_t *)this + 12) = &off_6C2B88;
  *((uint32_t *)this + 14) = 0;
  *(this + 60) = 1;
  *(this + 62) = 0;
  *(this + 61) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 16) = 0;
  *(this + 84) = 0;
  *((uint32_t *)this + 20) = &off_6C2B88;
  *((uint32_t *)this + 22) = 0;
  *(this + 92) = 1;
  *(this + 94) = 0;
  *(this + 93) = 0;
  *((uint32_t *)this + 26) = 0;
  *((uint32_t *)this + 25) = 0;
  *((uint32_t *)this + 24) = 0;
  pThis_F8 = this + 248;
  sub_41A630((unsigned int)(this + 248));
  *pThis_F8 = &clong::`vftable';
  *((uint32_t *)this + 68) = 0;
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 70) = 0;
  *((uint32_t *)this + 88) = 0;
  sub_41FDC0((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x401AA0 sub_401AA0
// ------------------------------------------------------------
char /*thiscall*/ sub_401AA0(uint32_t *this)
{
  *this = &off_6C1588;
  sub_420070();
  sub_4017E0((int)(this + 67));
  sub_41A580(this + 62);
  *(this + 20) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 84) = 0;
  *(this + 12) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 52) = 0;
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
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
  RegisterExceptionCallback(sub_401110);
  Time = timeGetTime();
  srand(Time);
  nRand = rand() % 100000;
  pMem = malloc(nRand);
  memset(pMem, 0, nRand);
  if ( sub_403340() < 0 )
    return 1;
  if ( sub_401090() < 0 )
    return 1;
  sub_403400();
  if ( sub_4037C0(nullptr, (int)&dword_79C0A0) < 0 )
    return 1;
  v11 = sub_422E70(20001);
  v7 = (const CHAR *)sub_422E70(20001);
  if ( sub_4048F0((int)hInstance, v7, v11, 0, 124, 124, 1) < 0 )
  {
    sub_4010E0();
    return 1;
  }
  sub_402AE0(lpCmdLine);
  ShowWindow(*(HWND *)(dword_79C0A0 + 16), 5);
  pMem2 = (char *)operator new(0x164u);
  if ( pMem2 != nullptr )
    pObj = sub_4019B0(pMem2);
  else
    pObj = nullptr;
  dword_79C0C0 = (int)pObj;
  if ( (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 4))(pObj, dword_79C0A0) == 1 )
    sub_404360(dword_79C0A0);
  if ( dword_79C0C0 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_79C0C0)(dword_79C0C0, 1);
  dword_79C0C0 = 0;
  sub_4010E0();
  if ( pMem != nullptr )
    free(pMem);
  return 0;
}



// ------------------------------------------------------------
// 0x401C90 sub_401C90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_401C90(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x401CB0 sub_401CB0
// ------------------------------------------------------------
int /*thiscall*/ sub_401CB0(LPCRITICAL_SECTION lpCriticalSection)
{
  InitializeCriticalSection(lpCriticalSection);
  return 0;
}



// ------------------------------------------------------------
// 0x401D30 sub_401D30
// ------------------------------------------------------------
int /*cdecl*/ sub_401D30(int nArg1, char pszArg2)
{
  int v2; // ecx
  int v3; // eax
  int v4; // edx
  int result; // eax

  v2 = 4 * nArg1 / 3;
  if ( (pszArg2 & 1) == 0 )
    v2 += nArg1 % 3;
  v3 = v2 / 76;
  if ( v2 % 76 != 0 )
  {
    v4 = v2 % 76 % 4;
    if ( v4 != 0 )
      v2 += 4 - v4;
  }
  result = v2 + 2 * v3 + 2;
  if ( (pszArg2 & 2) != 0 )
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
  if ( uArg1 == nullptr )
    return 0;
  pBuf = uArg3;
  if ( uArg3 == nullptr || uArg4 == nullptr || *uArg4 < sub_401D30(nArg2, pszArg5) )
    return 0;
  v7 = 0;
  v26 = 0;
  v25 = 0;
  v24 = nArg2 % 3;
  v8 = 4 * (nArg2 / 3) / 76;
  v9 = 19;
  if ( v8 >= 0 )
  {
    do
    {
      if ( v25 == v8 )
        v9 = 4 * (nArg2 / 3) % 76 / 4;
      if ( v9 > 0 )
      {
        for ( i = v9; i != 0; --i )
        {
          v11 = uArg12[1] | (*uArg12 << 8);
          v12 = uArg12 + 1;
          v13 = (v12[1] | (v11 << 8)) << 8;
          *pBuf = byte_6C1610[v13 >> 26];
          v13 <<= 6;
          pBuf[1] = byte_6C1610[v13 >> 26];
          uArg12 = v12 + 2;
          v13 <<= 6;
          v14 = pBuf + 2;
          *v14++ = byte_6C1610[v13 >> 26];
          *v14 = byte_6C1610[(v13 >> 20) & 0x3F];
          pBuf = v14 + 1;
        }
        v7 = v26;
        v8 = 4 * (nArg2 / 3) / 76;
      }
      v7 += 4 * v9;
      v26 = v7;
      if ( (pszArg5 & 2) == 0 )
      {
        *pBuf = 13;
        v15 = pBuf + 1;
        *v15 = 10;
        pBuf = v15 + 1;
        v7 += 2;
        v26 = v7;
      }
      ++v25;
    }
    while ( v25 <= v8 );
    if ( v7 != 0 && (pszArg5 & 2) == 0 )
    {
      pBuf -= 2;
      v7 -= 2;
    }
  }
  if ( v24 != 0 )
  {
    v16 = v24 + 1;
    if ( v24 != -1 )
    {
      v17 = 0;
      if ( v24 > 0 )
        v17 = *uArg12++;
      v18 = v17 << 8;
      if ( v24 > 1 )
      {
        v18 |= *uArg12;
        v16 = v24 + 1;
        ++uArg12;
      }
      v19 = v18 << 8;
      if ( v24 > 2 )
        v19 |= *uArg12;
      v20 = v19 << 8;
      if ( v16 > 0 )
      {
        for ( j = v16; j != 0; --j )
        {
          *pBuf++ = byte_6C1610[v20 >> 26];
          v20 <<= 6;
        }
      }
      v7 += v16;
      if ( (pszArg5 & 1) == 0 )
      {
        pBuf2 = 4 - v16;
        if ( 4 - v16 > 0 )
          memset(pBuf, 0x3Du, pBuf2);
        v7 += pBuf2;
      }
    }
  }
  *uArg4 = v7;
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

  dword_796E502 = dword_796E50;
  result = (int)FindFirstFileA(lpFileName, &FindFileData);
  hFindFile = (HANDLE)result;
  if ( result != -1 )
  {
    result = 1;
    do
    {
      if ( strcmp(FindFileData.cFileName, ".") != 0
        && strcmp(FindFileData.cFileName, (const char *)&word_6C1650) != 0
        && (FindFileData.dwFileAttributes & 0x10) != 1 )
      {
        DeleteFileA(FindFileData.cFileName);
        result = FindNextFileA(hFindFile, &FindFileData);
      }
    }
    while ( result != 0 );
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

  pThis_18 = (const char *)(this + 24);
  pThis_4B = (const char *)(this + 75);
  sprintf((char *const)(this + 386), "%s_%s.dmp", (const char *)(this + 75), (const char *)(this + 24));
  sprintf((char *const)(this + 646), "%s_%s.trc", pThis_4B, pThis_18);
  return sprintf((char *const)(this + 906), "DNF_DUMP.zip");
}



// ------------------------------------------------------------
// 0x402080 sub_402080
// ------------------------------------------------------------
// 【解读】
//   设置崩溃报告角色名（strncpy 0x32=50 字节 → this+75）并重生成文件名三元组。崩溃回调 ③ 调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_402080(char *this, char *Source)
{
  strncpy(this + 75, Source, 0x32u);
  return sub_402030((int)this);
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

  result = fopen(this + 386, "w");
  pFile = result;
  if ( result != nullptr )
  {
    fprintf(result, Format);
    return (FILE *)fclose(pFile);
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

  nArg32 = nArg3;
  v4 = nArg3 % 3 + 4 * nArg3 / 3;
  if ( v4 % 76 != 0 )
  {
    v5 = v4 % 76 % 4;
    if ( v5 != 0 )
      v4 += 4 - v5;
  }
  nArg3 = v4 + 2 * ((nArg3 % 3 + 4 * nArg3 / 3) / 76) + 2;
  return sub_401DA0(uArg1, nArg32, uArg2, &nArg3, 0);
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

  *(uint32_t *)this = nArg2;
  pszArg52 = pszArg5;
  *((uint32_t *)this + 1) = nArg3;
  pThis_7E = this + 126 - pszArg5;
  do
  {
    v8 = *pszArg52;
    pszArg52[pThis_7E] = *pszArg52;
    ++pszArg52;
  }
  while ( v8 != 0 );
  Time = timeGetTime();
  sprintf(this + 24, "%08x", Time);
  sprintf(this + 75, "_NONE");
  sub_402030((int)this);
  sub_401F80("*.dmp");  // 【崩溃报告链：旧转储清理 → 命名 → dmp 占位 → 7z 打包 DNF_DUMP…】
  sub_401F80("*.trc");  // 【崩溃报告链：旧转储清理 → 命名 → dmp 占位 → 7z 打包 DNF_DUMP…】
  return sub_401F80("*.zip");  // 【崩溃报告链：旧转储清理 → 命名 → dmp 占位 → 7z 打包 DNF_DUMP…】
}



// ------------------------------------------------------------
// 0x4021F0 sub_4021F0
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4021F0(size_t *this, uint32_t *pArg2, unsigned int uArg3, unsigned int uArg4)
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

  if ( pArg2[5] < uArg3 )
    std::_String_base::_Xran((std::_String_base *)this);
  uArg42 = uArg4;
  if ( pArg2[5] - uArg3 < uArg4 )
    uArg42 = pArg2[5] - uArg3;
  if ( -1 - *(this + 5) <= uArg42 )
    std::_String_base::_Xlen((std::_String_base *)this);
  if ( uArg42 == 0 )
    return this;
  fld_e5 = uArg42 + *(this + 5);
  fld_e52 = fld_e5;
  if ( fld_e5 == -1 )
    std::_String_base::_Xlen((std::_String_base *)this);
  fld_e6 = *(this + 6);
  if ( fld_e6 < fld_e5 )
  {
    sub_4012B0(this, fld_e5, *(this + 5));
    v8 = fld_e5 == 0;
    goto LABEL_12;
  }
  v8 = fld_e5 == 0;
  if ( fld_e5 != 0 )
  {
LABEL_12:
    if ( !v8 )
    {
      if ( pArg2[6] < 0x10u )
        v9 = pArg2 + 1;
      else
        v9 = (uint32_t *)pArg2[1];
      pThis_1 = (char *)(this + 1);
      if ( *(this + 6) < 0x10 )
        pThis_12 = (char *)(this + 1);
      else
        pThis_12 = *(char **)pThis_1;
      qmemcpy(&pThis_12[*(this + 5)], (char *)v9 + uArg3, uArg42);
      fld_e62 = *(this + 6) < 0x10;
      *(this + 5) = fld_e52;
      if ( !fld_e62 )
        pThis_1 = *(char **)pThis_1;
      pThis_1[fld_e52] = 0;
    }
    return this;
  }
  *(this + 5) = 0;
  if ( fld_e6 < 0x10 )
    *((uint8_t *)this + 4) = 0;
  else
    *(uint8_t *)*(this + 1) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4022F0 sub_4022F0
// ------------------------------------------------------------
size_t */*fastcall*/ sub_4022F0(std::_String_base *this, int nArg2, char *pszArg3, unsigned int uArg4)
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

  pThis_6 = *((uint32_t *)this + 6);
  if ( pThis_6 < 0x10 )
    pThis_4 = (char *)this + 4;
  else
    pThis_4 = *((char **)this + 1);
  if ( pszArg3 >= pThis_4 )
  {
    pThis_42 = (char *)this + 4;
    pThis_43 = pThis_6 < 0x10 ? (std::_String_base *)((char *)this + 4) : *(std::_String_base **)pThis_42;
    if ( (char *)pThis_43 + *((uint32_t *)this + 5) > pszArg3 )
    {
      if ( pThis_6 >= 0x10 )
        pThis_42 = *(char **)pThis_42;
      return sub_4021F0((size_t *)this, this, pszArg3 - pThis_42, uArg4);
    }
  }
  if ( -1 - *((uint32_t *)this + 5) <= uArg4 )
    std::_String_base::_Xlen(this);
  if ( uArg4 == 0 )
    return (size_t *)this;
  pThis_5 = uArg4 + *((uint32_t *)this + 5);
  if ( pThis_5 == -1 )
    std::_String_base::_Xlen(this);
  pThis_62 = *((uint32_t *)this + 6);
  if ( pThis_62 < pThis_5 )
  {
    sub_4012B0(this, pThis_5, *((uint32_t *)this + 5));
    v12 = pThis_5 == 0;
    goto LABEL_19;
  }
  v12 = pThis_5 == 0;
  if ( pThis_5 != 0 )
  {
LABEL_19:
    if ( !v12 )
    {
      if ( *((uint32_t *)this + 6) < 0x10u )
        pThis_44 = (char *)this + 4;
      else
        pThis_44 = *((char **)this + 1);
      qmemcpy(&pThis_44[*((uint32_t *)this + 5)], pszArg3, uArg4);
      pThis_63 = *((uint32_t *)this + 6) < 0x10u;
      *((uint32_t *)this + 5) = pThis_5;
      if ( !pThis_63 )
      {
        *(uint8_t *)(*((uint32_t *)this + 1) + pThis_5) = 0;
        return (size_t *)this;
      }
      *((uint8_t *)this + pThis_5 + 4) = 0;
    }
    return (size_t *)this;
  }
  *((uint32_t *)this + 5) = 0;
  if ( pThis_62 < 0x10 )
    *((uint8_t *)this + 4) = 0;
  else
    **((uint8_t **)this + 1) = 0;
  return (size_t *)this;
}



// ------------------------------------------------------------
// 0x402410 sub_402410
// ------------------------------------------------------------
size_t */*thiscall*/ sub_402410(std::_String_base *this, char *pszArg2)
{
  return sub_4022F0(this, 0, pszArg2, strlen(pszArg2));
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

  dword_796E502 = dword_796E50;
  pFile = fopen("DNF.trc", "rb");
  pFile3 = pFile;
  pMem2 = pFile;
  if ( pFile != nullptr )
  {
    v4 = _fileno(pFile);
    v5 = _filelength(v4);
    v6 = v5;
    if ( v5 != 0 )
    {
      pMem = operator new(v5);
      sub_66BD5A(pMem, v6, 1u, pFile3);  // 【fread封装】
      pFile2 = fopen((const char *)(this + 646), "wb");
      pFile5 = pFile2;
      if ( pFile2 != nullptr )
      {
        sub_66BC25(pMem, v6, 1u, pFile2);
        fclose(pFile5);
      }
      pFile3 = (FILE *)pMem2;
    }
    fclose(pFile3);
  }
  sprintf(
    Buffer,
    "a -tzip %s %s %s",
    (const char *)(this + 906),
    (const char *)(this + 386),
    (const char *)(this + 646));
  memset(&pExecInfo, 0, sizeof(pExecInfo));
  pExecInfo.hwnd = nullptr;
  pExecInfo.nShow = 0;
  pExecInfo.cbSize = 60;
  pExecInfo.lpFile = "7z";
  pExecInfo.lpParameters = Buffer;
  pExecInfo.lpDirectory = ".\\";
  pExecInfo.fMask = 320;
  pExecInfo.lpVerb = "open";
  ShellExecuteExA(&pExecInfo);
  GetExitCodeProcess(pExecInfo.hProcess, &ExitCode);
  while ( ExitCode == 259 )
  {
    Sleep(0x3E8u);
    GetExitCodeProcess(pExecInfo.hProcess, &ExitCode);
  }
  pFile4 = fopen((const char *)(this + 906), "rb");
  pFile6 = pFile4;
  if ( pFile4 != nullptr )
  {
    fseek(pFile4, 0, 2);
    nPos = ftell(pFile6);
    fseek(pFile6, 0, 0);
    pMem2 = operator new(nPos);
    sub_66BD5A(pMem2, nPos, 1u, pFile6);  // 【fread封装】
    fclose(pFile6);
    pMem3 = (char *)operator new(2 * nPos);
    sub_4020F0((uint8_t *)pMem2, pMem3, nPos);
    v26 = 15;
    v25 = 0;
    LOBYTE(v24) = 0;
    sub_4015C0(&v23, " content=", 9u);  // 【std::string构造赋值】
    v28 = 0;
    sub_4022F0((std::_String_base *)&v23, v13, pMem3, strlen(pMem3));
    v18 = 15;
    v17 = 0;
    LOBYTE(Block) = 0;
    sub_4015C0(&v15, (uint8_t *)(this + 126), strlen((const char *)(this + 126)));  // 【std::string构造赋值】
    LOBYTE(v28) = 1;
    sub_4028C0(&v15, &v23);
    if ( v18 >= 0x10 )
      j__free(Block);
    j_j__free(pMem3);
    j_j__free(pMem2);
    if ( v26 >= 0x10 )
      j__free(v24);
  }
}



// ------------------------------------------------------------
// 0x402740 sub_402740
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_402740(uint32_t *this)
{
  BOOL result; // eax
  void *fld_e1; // [esp-4h] [ebp-8h]

  fld_e1 = (void *)*(this + 1);
  *this = &off_6C16EC;
  result = InternetCloseHandle(fld_e1);
  *(this + 1) = 0;
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

  *this = &off_6C16EC;
  *(this + 1) = 0;
  pThis_2 = this + 2;
  *pThis_2 = 0;
  pThis_2[1] = 0;
  *(this + 1) = InternetOpenA("NIS::Http", 0, nullptr, nullptr, 0);
  return this;
}



// ------------------------------------------------------------
// 0x4027B0 sub_4027B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4027B0(uint32_t *Block, char pszArg2)
{
  sub_402740(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4027E0 unknown_libname_2
// ------------------------------------------------------------
// Microsoft VisualC 2-14/net runtime
uint32_t */*thiscall*/ unknown_libname_2(uint32_t *this)
{
  if ( *(this + 6) < 0x10u )
    return this + 1;
  else
    return (uint32_t *)*(this + 1);
}



// ------------------------------------------------------------
// 0x4027F0 sub_4027F0
// ------------------------------------------------------------
// 【解读】
//   URL 子串定位（memchr 首字符 + memcmp 全串推进）—— HTTP server/object 分隔查找。
// ------------------------------------------------------------
int /*thiscall*/ sub_4027F0(uint32_t *this, char *pszArg2, uint64_t uArg3)
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

  v4 = HIDWORD(uArg3);
  result = uArg3;
  if ( uArg3 > (unsigned int)*(this + 5) )
  {
    fld_e5 = *(this + 5);
    if ( (unsigned int)uArg3 >= fld_e5 )
      return -1;
    v6 = fld_e5 - uArg3;
    if ( HIDWORD(uArg3) > v6 )
      return -1;
    v7 = 1 - HIDWORD(uArg3) + v6;
    fld_e6 = *(this + 6);
    pThis_1 = (char *)(this + 1);
    pThis_12 = pThis_1;
    if ( fld_e6 >= 0x10 )
      pThis_1 = *(char **)pThis_1;
    v13 = &pThis_1[result];
    v10 = (char *)memchr(&pThis_1[result], *pszArg2, v7);
    if ( v10 != nullptr )
    {
      while ( memcmp(v10, pszArg2, v4) != 0 )
      {
        v7 = v7 + v13 - v10 - 1;
        v13 = v10 + 1;
        v10 = (char *)memchr(v10 + 1, *pszArg2, v7);
        if ( v10 == nullptr )
          return -1;
        v4 = HIDWORD(uArg3);
      }
      pThis_122 = pThis_12;
      if ( *(this + 6) >= 0x10u )
        pThis_122 = *(char **)pThis_12;
      return v10 - pThis_122;
    }
    else
    {
      return -1;
    }
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

  dword_796E502 = dword_796E50;
  v4 = sub_4027F0(pArg2, "/", 0x100000007uLL);
  v15 = 15;
  lpszServerName[4] = nullptr;
  LOBYTE(lpszServerName[0]) = 0;
  sub_4014D0(&v13, pArg2, 7u, v4 - 7);
  v21 = 0;
  v19 = 15;
  v18 = 0;
  LOBYTE(lpszObjectName) = 0;
  sub_4014D0(&v16, pArg2, v4, 0xFFFFFFFF);
  v5 = lpszServerName[0];
  if ( v15 < 0x10 )
    v5 = (const CHAR *)lpszServerName;
  fld_e1 = InternetConnectA(*(this + 1), v5, 0x50u, szPassword, szPassword, 3u, 0, 0);
  p_lpszObjectName = lpszObjectName;
  if ( v19 < 0x10 )
    p_lpszObjectName = (const CHAR *)&lpszObjectName;
  v8 = HttpOpenRequestA(fld_e1, "POST", p_lpszObjectName, nullptr, nullptr, nullptr, 0x80000000, 0);
  sprintf(szHeaders, "Content-Type: application/x-www-form-urlencoded");
  nLen = strlen(szHeaders);
  if ( pArg3[6] < 0x10u )
    v10 = pArg3 + 1;
  else
    v10 = (void *)pArg3[1];
  HttpSendRequestA(v8, szHeaders, nLen, v10, pArg3[5]);
  InternetCloseHandle(v8);
  InternetCloseHandle(fld_e1);
  if ( v19 >= 0x10 )
    j__free((void *)lpszObjectName);
  v19 = 15;
  v18 = 0;
  LOBYTE(lpszObjectName) = 0;
  if ( v15 >= 0x10 )
    j__free((void *)lpszServerName[0]);
  return 1;
}



// ============================================================
// SECTION 0x402A50 — 字符串参数包 / CString 数组 / vsprintf 格式化打包工具
// ============================================================
// ------------------------------------------------------------
// 0x402A50 sub_402A50
// ------------------------------------------------------------
int /*thiscall*/ sub_402A50(uint32_t *this)  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
{
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x402A60 sub_402A60
// ------------------------------------------------------------
int /*thiscall*/ sub_402A60(int this)
{
  if ( *(uint32_t *)(this + 8) != 0 )
    j_j__free(*(void **)(this + 8));
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x402A90 sub_402A90
// ------------------------------------------------------------
int /*thiscall*/ sub_402A90(int this, int pArg2)
{
  void *pMem; // eax

  if ( *(uint32_t *)(this + 8) != 0 )
    j_j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 12) = pArg2;
  *(uint32_t *)(this + 16) = pArg2;
  *(uint32_t *)(this + 8) = 0;
  pMem = operator new(pArg2 + 1);
  *(uint32_t *)(this + 8) = pMem;
  return pMem != nullptr ? 1 : -2147483640;
}



// ------------------------------------------------------------
// 0x402AE0 sub_402AE0
// ------------------------------------------------------------
int /*thiscall*/ sub_402AE0(int this, const char *pArg2)
{
  int result; // eax
  unsigned int nLen; // edi

  if ( pArg2 == nullptr )
    return 0x80000000;
  nLen = strlen(pArg2);
  if ( *(uint8_t *)(this + 4) == 0 )
  {
    if ( *(uint32_t *)(this + 8) != 0 )
      j_j__free(*(void **)(this + 8));
    *(uint8_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    *(uint32_t *)(this + 16) = 0;
LABEL_8:
    result = sub_402A90(this, nLen);
    if ( result < 0 )
      return result;
    goto LABEL_9;
  }
  if ( nLen >= *(uint32_t *)(this + 16) )
    goto LABEL_8;
LABEL_9:
  *(uint32_t *)(this + 12) = nLen;
  qmemcpy(*(void **)(this + 8), pArg2, nLen);
  *(uint8_t *)(nLen + *(uint32_t *)(this + 8)) = 0;
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x402B80 sub_402B80
// ------------------------------------------------------------
int /*thiscall*/ sub_402B80(int this, const char *pArg2)
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

  if ( pArg2 == nullptr )
    return 0x80000000;
  if ( *(uint8_t *)(this + 4) == 0 )
    return sub_402AE0(this, pArg2);
  nLen = strlen(pArg2);
  fld_10 = *(uint32_t *)(this + 16);
  fld_C = *(uint32_t *)(this + 12);
  nLen2 = nLen;
  fld_102 = fld_10;
  if ( fld_C + nLen < fld_10 )
  {
    qmemcpy((void *)(fld_C + *(uint32_t *)(this + 8)), pArg2, nLen);
    fld_C2 = nLen + *(uint32_t *)(this + 12);
    *(uint32_t *)(this + 12) = fld_C2;
    *(uint8_t *)(fld_C2 + *(uint32_t *)(this + 8)) = 0;
  }
  else
  {
    pMem = operator new(fld_10 + 1);
    qmemcpy(pMem, *(const void **)(this + 8), *(uint32_t *)(this + 16));
    *((uint8_t *)pMem + *(uint32_t *)(this + 16)) = 0;
    Block = pMem;
    result = sub_402A90(this, fld_102 + nLen2);
    if ( result < 0 )
      return result;
    qmemcpy(*(void **)(this + 8), Block, fld_102);
    qmemcpy((void *)(fld_102 + *(uint32_t *)(this + 8)), pArg2, nLen2);
    *(uint8_t *)(*(uint32_t *)(this + 8) + *(uint32_t *)(this + 12)) = 0;
    if ( Block != nullptr )
    {
      j_j__free(Block);
      return 1;
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x402CB0 sub_402CB0
// ------------------------------------------------------------
int /*thiscall*/ sub_402CB0(int this, int nArg2, const char *pArg3)
{
  int result; // eax
  unsigned int nLen; // eax
  int fld_C; // ecx
  int nArg22; // edx
  unsigned int v8; // eax
  void *Block; // [esp+8h] [ebp-8h]
  unsigned int nLen2; // [esp+Ch] [ebp-4h]

  if ( pArg3 == nullptr )
    return 0x80000000;
  nLen = strlen(pArg3);
  fld_C = *(uint32_t *)(this + 12);
  nArg22 = nArg2;
  nLen2 = nLen;
  if ( nArg2 >= fld_C || *(uint8_t *)(this + 4) == 0 )
    return sub_402B80(this, pArg3);
  v8 = fld_C + nLen;
  if ( v8 < *(uint32_t *)(this + 16) )
  {
    *(uint32_t *)(this + 12) = v8;
  }
  else
  {
    Block = operator new(fld_C + 1);
    qmemcpy(Block, *(const void **)(this + 8), *(uint32_t *)(this + 12));
    result = sub_402A90(this, nLen2 + *(uint32_t *)(this + 12));
    if ( result < 0 )
      return result;
    qmemcpy(*(void **)(this + 8), Block, strlen((const char *)Block));
    if ( Block != nullptr )
      j_j__free(Block);
    nArg22 = nArg2;
  }
  qmemcpy(
    (void *)(nArg22 + *(uint32_t *)(this + 8) + nLen2),
    (const void *)(*(uint32_t *)(this + 8) + nArg22),
    *(uint32_t *)(this + 12) - nArg22);
  qmemcpy((void *)(nArg22 + *(uint32_t *)(this + 8)), pArg3, nLen2);
  *(uint8_t *)(*(uint32_t *)(this + 8) + *(uint32_t *)(this + 12)) = 0;
  return 0x80000000;
}



// ------------------------------------------------------------
// 0x402DE0 sub_402DE0
// ------------------------------------------------------------
int /*thiscall*/ sub_402DE0(int this, signed int nArg2, signed int nArg3)
{
  signed int fld_C; // ecx
  signed int nArg33; // esi
  signed int i; // eax
  int fld_8; // ecx
  unsigned int nArg32; // ebx
  signed int v10; // ecx

  if ( *(uint8_t *)(this + 4) == 0 )
    return 0x80000000;
  fld_C = *(uint32_t *)(this + 12);
  if ( fld_C == 0 )
    return 1;
  if ( nArg2 < fld_C )
  {
    nArg32 = nArg3;
    v10 = fld_C - nArg2;
    if ( v10 < nArg3 )
      nArg32 = v10;
    qmemcpy((void *)(*(uint32_t *)(this + 8) + nArg2), (const void *)(*(uint32_t *)(this + 8) + nArg2 + nArg32), v10 - nArg32);
    memset((void *)(*(uint32_t *)(this + 12) + *(uint32_t *)(this + 8) - nArg32), 0, nArg32);
    *(uint32_t *)(this + 12) -= nArg32;
    return 0x80000000;
  }
  nArg33 = nArg3;
  if ( nArg3 >= fld_C )
    nArg33 = fld_C;
  for ( i = 0; i < nArg33; *(uint8_t *)(fld_8 + *(uint32_t *)(this + 12) - 1) = 0 )
    fld_8 = *(uint32_t *)(this + 8) - i++;
  *(uint32_t *)(this + 12) -= nArg33;
  return 0x80000000;
}



// ------------------------------------------------------------
// 0x402EA0 sub_402EA0
// ------------------------------------------------------------
int /*thiscall*/ sub_402EA0(int this, char pszArg2, char pszArg3)
{
  unsigned int v4; // edx
  uint8_t *fld_8; // eax

  if ( *(uint8_t *)(this + 4) == 0 || *(uint32_t *)(this + 12) == 0 )
    return 0x80000000;
  v4 = 0;
  do
  {
    fld_8 = (uint8_t *)(v4 + *(uint32_t *)(this + 8));
    if ( *fld_8 == pszArg2 )
      *fld_8 = pszArg3;
    ++v4;
  }
  while ( v4 < *(uint32_t *)(this + 12) );
  return 1;
}



// ------------------------------------------------------------
// 0x402EF0 sub_402EF0
// ------------------------------------------------------------
int /*thiscall*/ sub_402EF0(int this, char *Format, va_list ArgList)
{
  int result; // eax
  unsigned int nLen; // eax
  int nLen2; // edi
  char *fld_82; // [esp-10h] [ebp-18h]
  char *fld_8; // [esp-10h] [ebp-18h]

  if ( Format == nullptr )
    return 0x80000000;
  nLen = strlen(Format);
  nLen2 = nLen;
  if ( *(uint8_t *)(this + 4) != 0 )
  {
    if ( nLen < *(uint32_t *)(this + 16) || (result = sub_402A90(this, nLen)) >= 0 )
    {
      fld_8 = *(char **)(this + 8);
      *(uint32_t *)(this + 12) = nLen2;
      vsprintf(fld_8, Format, ArgList);
      *(uint8_t *)(nLen2 + *(uint32_t *)(this + 8)) = 0;
      return 1;
    }
  }
  else
  {
    if ( *(uint32_t *)(this + 8) != 0 )
      j_j__free(*(void **)(this + 8));
    *(uint8_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    *(uint32_t *)(this + 16) = 0;
    result = sub_402A90(this, nLen2);
    if ( result >= 0 )
    {
      fld_82 = *(char **)(this + 8);
      *(uint32_t *)(this + 12) = nLen2;
      vsprintf(fld_82, Format, ArgList);
      *(uint8_t *)(nLen2 + *(uint32_t *)(this + 8)) = 0;
      *(uint8_t *)(this + 4) = 1;
      return 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x402FB0 sub_402FB0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_402FB0(uint8_t *this, int pArg2)
{
  *(this + 4) = 0;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *(uint32_t *)this = &off_6C38F4;
  sub_402AE0((int)this, *(const char **)(pArg2 + 8));
  return this;
}



// ------------------------------------------------------------
// 0x403010 sub_403010
// ------------------------------------------------------------
void /*thiscall*/ sub_403010(uint32_t *this)
{
  void *fld_e2; // eax

  fld_e2 = (void *)*(this + 2);
  *this = &off_6C38F4;
  if ( fld_e2 != nullptr )
    j_j__free(fld_e2);
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *((uint8_t *)this + 4) = 0;
  *this = &nengine::IObject::`vftable';
}



// ------------------------------------------------------------
// 0x403050 sub_403050
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_403050(uint32_t *Block, char pszArg2)
{
  sub_403010(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x403080 sub_403080
// ------------------------------------------------------------
int /*thiscall*/ sub_403080(int this, int nArg2)
{
  int result; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
    return 0x80000000;
  result = sub_402A90(this, nArg2);
  if ( result >= 0 )
  {
    **(uint8_t **)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    *(uint8_t *)(this + 4) = 1;
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4030C0 sub_4030C0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4030C0(int this, uint8_t *pArg2, int nArg3, int nArg4)
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
  pMem3 = nullptr;
  fld_C2 = 0;
  fld_C3 = 0;
  fld_4 = *(uint8_t *)(this + 4);
  v18 = 0;
  if ( fld_4 != 0 )
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
    if ( pMem != nullptr )
    {
      *pMem = 0;
      fld_C2 = 0;
      v12 = 1;
    }
    v10 = nArg3 <= 0 ? 0 : nArg3;
    if ( v7 < v7 + fld_C )
    {
      do
      {
        pMem2[v10 - v7] = *(uint8_t *)(v10 + *(uint32_t *)(pThis + 8));
        ++v10;
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
    sub_402AE0((int)pArg2, pMem2);
    if ( pMem2 != nullptr )
      j_j__free(pMem2);
    return pArg2;
  }
  else
  {
    sub_402FB0(pArg2, (int)&v11);
    return pArg2;
  }
}



// ============================================================
// SECTION 0x4031E0 — 数学库与引擎子系统初始化（sin/cos/tan 表、rand 播种、随机数工具）
// ============================================================
// ------------------------------------------------------------
// 0x4031E0 sub_4031E0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4031E0(uint8_t *this)  // 【数学库与引擎子系统初始化（sin/cos/tan 表、rand 播种、随机数工具）】
{
  *(this + 4) = 0;
  *(uint32_t *)this = off_6C1748;
  sub_4050F0();
  sub_405150(this);
  return this;
}



// ------------------------------------------------------------
// 0x403230 sub_403230
// ------------------------------------------------------------
void */*thiscall*/ sub_403230(void *Block, char pszArg2)
{
  sub_403260();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x403260 sub_403260
// ------------------------------------------------------------
int /*thiscall*/ sub_403260(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = off_6C1748;
  result = sub_405160();
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4032B0 sub_4032B0
// ------------------------------------------------------------
int sub_4032B0()
{
  uint8_t *pMem; // eax
  uint8_t *v2; // eax

  if ( dword_79D078 != 0 )
    return -2147483646;
  pMem = operator new(0x80u);
  if ( pMem == nullptr )
    return -2147483640;
  v2 = sub_4031E0(pMem);  // 【数学库与引擎子系统初始化（sin/cos/tan 表、rand 播种、随机数工具）】
  if ( v2 == nullptr )
    return -2147483640;
  dword_79D078 = (int)v2;
  return 1;
}



// ------------------------------------------------------------
// 0x403340 sub_403340
// ------------------------------------------------------------
int sub_403340()
{
  int result; // eax
  DWORD Time; // eax

  if ( byte_79C560 != 0 )
    return -2147483646;
  result = sub_403840();
  if ( result >= 0 )
  {
    result = sub_405950();
    if ( result >= 0 )
    {
      result = sub_405440();
      if ( result >= 0 )
      {
        result = sub_4032B0();
        if ( result >= 0 )
        {
          Time = timeGetTime();
          srand(Time);
          sub_4051A0();  // 【tick_domains_init】
          byte_79C560 = 1;
          return 1;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4033E0 sub_4033E0
// ------------------------------------------------------------
int sub_4033E0()
{
  if ( dword_79C564 != 0 )
  {
    (**(void (/*thiscall*/ ***)(int, int))dword_79C564)(dword_79C564, 1);
    dword_79C564 = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x403400 sub_403400
// ------------------------------------------------------------
int sub_403400()
{
  return dword_79C564;
}



// ------------------------------------------------------------
// 0x403410 sub_403410
// ------------------------------------------------------------
void /*thiscall*/ sub_403410(uint32_t *this)
{
  uint32_t *pThis_1; // esi

  pThis_1 = this + 1;
  *this = off_6C1750;
  sub_6569D0(this + 1);
  j__free((void *)pThis_1[1]);
  pThis_1[1] = 0;
}



// ------------------------------------------------------------
// 0x403440 sub_403440
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_403440(uint8_t *this, void *pArg2)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C1754;
  *((uint32_t *)this + 7) = pArg2;
  *(this + 56) = 0;
  *((uint32_t *)this + 13) = &off_6C38F4;
  sub_402A50((uint32_t *)this + 13);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  *(this + 76) = 0;
  *((uint32_t *)this + 18) = &off_6C38F4;
  sub_402A50((uint32_t *)this + 18);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  *(this + 96) = 0;
  *((uint32_t *)this + 23) = &off_6C38F4;
  sub_402A50((uint32_t *)this + 23);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  *(this + 120) = 0;
  *((uint32_t *)this + 29) = off_6C174C;
  *((uint32_t *)this + 34) = sub_425940(this + 132);
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 37) = sub_425940(this + 144);
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 40) = sub_425940(this + 156);
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 43) = sub_425940(this + 168);
  *((uint32_t *)this + 44) = 0;
  sub_4044C0(this);
  return this;
}



// ------------------------------------------------------------
// 0x403550 sub_403550
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_403550(int nArg1, int nArg2, int nArg3, int nArg4)
{
  return 0x80000000;
}



// ------------------------------------------------------------
// 0x403560 sub_403560
// ------------------------------------------------------------
int /*thiscall*/ sub_403560(void **this)
{
  int result; // eax

  *this = &off_6C1754;
  sub_404560();
  sub_6569D0(this + 42);
  j__free(*(this + 43));
  *(this + 43) = nullptr;
  sub_6569D0(this + 39);
  j__free(*(this + 40));
  *(this + 40) = nullptr;
  sub_6569D0(this + 36);
  j__free(*(this + 37));
  *(this + 37) = nullptr;
  sub_6569D0(this + 33);
  j__free(*(this + 34));
  *(this + 34) = nullptr;
  *(this + 29) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 120) = 0;
  *(this + 23) = &off_6C38F4;
  sub_402A60((int)(this + 23));
  *(this + 23) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 96) = 0;
  *(this + 18) = &off_6C38F4;
  sub_402A60((int)(this + 18));
  *(this + 18) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 76) = 0;
  *(this + 13) = &off_6C38F4;
  result = sub_402A60((int)(this + 13));
  *(this + 13) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 56) = 0;
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x403690 sub_403690
// ------------------------------------------------------------
void **/*thiscall*/ sub_403690(void **Block, char pszArg2)
{
  sub_403560(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4036C0 sub_4036C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4036C0(uint32_t *Block, char pszArg2)
{
  sub_403410(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4036F0 sub_4036F0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4036F0(uint8_t *this, void *pArg2)
{
  sub_403440(this, pArg2);
  *(uint32_t *)this = &off_6C1778;
  sub_40B130(this);
  return this;
}



// ------------------------------------------------------------
// 0x403740 sub_403740
// ------------------------------------------------------------
void */*thiscall*/ sub_403740(void *Block, char pszArg2)
{
  sub_403770();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x403770 sub_403770
// ------------------------------------------------------------
int /*thiscall*/ sub_403770(void **this)
{
  *this = &off_6C1778;
  sub_404560();
  return sub_403560(this);
}



// ------------------------------------------------------------
// 0x4037C0 sub_4037C0
// ------------------------------------------------------------
int /*stdcall*/ sub_4037C0(void *Block, uint32_t *uArg2)
{
  uint8_t *pMem; // eax
  uint8_t *v4; // eax

  if ( Block != nullptr )
    return -2147483639;
  pMem = operator new(0xB8u);
  if ( pMem != nullptr )
    v4 = sub_4036F0(pMem, nullptr);
  else
    v4 = nullptr;
  *uArg2 = v4;
  return v4 != nullptr ? 1 : -2147483640;
}



// ------------------------------------------------------------
// 0x403840 sub_403840
// ------------------------------------------------------------
int sub_403840()
{
  uint32_t *pMem; // eax
  int v1; // edi

  pMem = operator new(0x10u);
  v1 = (int)pMem;
  if ( pMem == nullptr )
    return -2147483640;
  *pMem = off_6C1750;
  pMem[2] = sub_425940(pMem + 1);
  *(uint32_t *)(v1 + 12) = 0;
  sub_6569D0(v1 + 4);
  dword_79C564 = v1;
  return 1;
}



// ============================================================
// SECTION 0x4038D0 — 日志核心：NiLog 对象（QPC 计时日志 / 横幅 / 5000 行轮转 / OutputDebugString）
// ============================================================
// ------------------------------------------------------------
// 0x4038D0 sub_4038D0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4038D0(uint32_t *this)  // 【日志核心：NiLog 对象（QPC 计时日志 / 横幅 / 5000 行轮转 / O…】
{
  unsigned int result; // eax
  int v3; // ecx

  if ( byte_79C7B0[12 * *this] != 0 )
    OutputDebugStringA(Buffer);
  result = 12 * *this;
  v3 = dword_79C7B4[result / 4];
  if ( v3 >= 0 && byte_79C7B0[result] == 0 )
    return sub_403D60((&dword_79C568)[v3], (size_t)Buffer);
  return result;
}



// ------------------------------------------------------------
// 0x403920 sub_403920
// ------------------------------------------------------------
int sub_403920()
{
  int (/*thiscall*/ ***v0)(uint32_t); // eax

  dword_79C568 = nullptr;
  dword_79C56C = 0;
  dword_79C570 = 0;
  dword_79C574 = 0;
  dword_79C578 = 0;
  dword_79C57C = 0;
  dword_79C580 = 0;
  dword_79C584 = 0;
  dword_79C588 = 0;
  dword_79C58C = 0;
  dword_79C590 = 0;
  dword_79C594 = 0;
  dword_79C598 = 0;
  dword_79C59C = 0;
  dword_79C5A0 = 0;
  byte_77F2E3 = 1;
  dword_79C5A4 = 0;
  v0 = (int (/*thiscall*/ ***)(uint32_t))sub_406C50();  // 【NiMemory.log / NiProfile.log 日志对象（Gamebryo…】
  return (**v0)(v0);
}



// ------------------------------------------------------------
// 0x403990 sub_403990
// ------------------------------------------------------------
int /*cdecl*/ sub_403990(int nArg1, int nArg2, char pszArg3, int nArg4)
{
  int v5; // esi
  char *pMem; // eax
  char *v7; // eax

  if ( dword_79C7A8 == 16 )
    return -1;
  v5 = 0;
  while ( (&dword_79C568)[v5] != nullptr )
  {
    if ( dword_79C56C[v5] == 0 )
    {
      ++v5;
      break;
    }
    if ( dword_79C570[v5] == 0 )
    {
      v5 += 2;
      break;
    }
    if ( dword_79C574[v5] == 0 )
    {
      v5 += 3;
      break;
    }
    v5 += 4;
    if ( v5 >= 16 )
      break;
  }
  if ( v5 == 16 )
    return -1;
  pMem = (char *)operator new(0x128u);
  v7 = pMem != nullptr ? (char *)sub_404290(pMem, nArg1, nArg2, pszArg3, nArg4) : nullptr;
  (&dword_79C568)[v5] = v7;
  if ( v7 == nullptr )
    return -1;
  ++dword_79C7A8;
  return v5;
}



// ------------------------------------------------------------
// 0x403A90 sub_403A90
// ------------------------------------------------------------
void sub_403A90()
{
  unsigned int i; // esi
  char *v1; // edi

  for ( i = 0; i < 16; ++i )
  {
    v1 = (&dword_79C568)[i];
    if ( v1 != nullptr )
    {
      sub_4042D0((&dword_79C568)[i]);
      j__free(v1);
    }
    (&dword_79C568)[i] = nullptr;
  }
  dword_79C7A8 = 0;
}



// ------------------------------------------------------------
// 0x403AD0 sub_403AD0
// ------------------------------------------------------------
double sub_403AD0()
{
  LARGE_INTEGER PerformanceCount; // [esp+4h] [ebp-8h] BYREF

  if ( byte_77F2E4 != 0 )
  {
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&::PerformanceCount);
    byte_77F2E4 = 0;
  }
  QueryPerformanceCounter(&PerformanceCount);
  return (double)(PerformanceCount.QuadPart - ::PerformanceCount.QuadPart) / (double)Frequency.QuadPart;
}



// ------------------------------------------------------------
// 0x403B30 sub_403B30
// ------------------------------------------------------------
int /*stdcall*/ sub_403B30(int nArg1, int nArg2, int nArg3, int (/*thiscall*/ *uArg4)(int))
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
int /*thiscall*/ sub_403B60(uint32_t *this, int64_t Format)
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
    v4 = sub_403AD0();
    sprintf(Buffer, "%f: ", v4);
    nLen = strlen(Buffer);
    v3 = 512 - nLen;
    v2 = &Buffer[nLen];
  }
  result = _vsnprintf(v2, v3, (const char *const)Format, (va_list)HIDWORD(Format));
  v2[v3 - 1] = 0;
  return result;
}



// ------------------------------------------------------------
// 0x403BE0 sub_403BE0
// ------------------------------------------------------------
void sub_403BE0()
{
  sub_403A90();
  if ( byte_77F2E3 != 0 )
  {
    InitializeCriticalSection(&CriticalSection);
    byte_77F2E3 = 0;
  }
  DeleteCriticalSection(&CriticalSection);
}



// ------------------------------------------------------------
// 0x403C10 sub_403C10
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_403C10(unsigned int *pDwArg1, unsigned int uArg2, char *Format, char ArgList)
{
  *pDwArg1 = uArg2;
  if ( uArg2 < 0x20 && (byte_79C7B0[12 * uArg2] != 0 || dword_79C7B4[3 * uArg2] != -1) && Format != nullptr )
  {
    if ( byte_77F2E3 != 0 )
    {
      InitializeCriticalSection(&CriticalSection);
      byte_77F2E3 = 0;
    }
    EnterCriticalSection(&CriticalSection);
    sub_403B60(pDwArg1, __SPAIR64__(&ArgList, (unsigned int)Format));
    sub_4038D0(pDwArg1);  // 【日志核心：NiLog 对象（QPC 计时日志 / 横幅 / 5000 行轮转 / O…】
    if ( byte_77F2E3 != 0 )
    {
      InitializeCriticalSection(&CriticalSection);
      byte_77F2E3 = 0;
    }
    LeaveCriticalSection(&CriticalSection);
  }
  return pDwArg1;
}



// ------------------------------------------------------------
// 0x403CC0 sub_403CC0
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_403CC0(char *Format)
{
  char ArgList; // cl
  int v3; // [esp+0h] [ebp-4h] BYREF

  return sub_403C10((unsigned int *)&v3, 0, Format, ArgList);
}



// ------------------------------------------------------------
// 0x403CE0 sub_403CE0
// ------------------------------------------------------------
int sub_403CE0(char *Format, ...)
{
  int v1; // eax
  int v3; // [esp+0h] [ebp-208h] BYREF
  char Buffer[510]; // [esp+4h] [ebp-204h] BYREF
  char pBuf[2]; // [esp+202h] [ebp-6h] BYREF
  int dword_796E502; // [esp+204h] [ebp-4h]
  va_list va; // [esp+214h] [ebp+Ch] BYREF

  va_start(va, Format);
  dword_796E502 = dword_796E50;
  sub_404F40(50);
  v1 = _vsnprintf(Buffer, 0x1FEu, Format, va);
  if ( v1 >= 0 )
  {
    Buffer[v1] = 10;
    Buffer[v1 + 1] = 0;
  }
  else
  {
    strcpy(pBuf, "\n");
  }
  sub_403C10((unsigned int *)&v3, 0, Buffer, v3);
  return sub_404F80(50, 0);
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

  dword_796E502 = dword_796E50;
  v3 = *((uint32_t *)FileName + 65);
  if ( v3 != 0 )
  {
    nLen = strlen(ElementCount);
    ElementCounta = nLen;
    if ( nLen <= 512 )
    {
      qmemcpy(v11, ElementCount, nLen);
    }
    else
    {
      qmemcpy(v11, ElementCount, 0x1FCu);
      v6 = ElementCount + 508;
      *(uint16_t *)&v11[508] = *(uint16_t *)v6;
      ElementCounta = 512;
      nLen = 512;
      v11[510] = v6[2];
      v12 = 0;
    }
    if ( byte_79C7AC == 1 )
    {
      sub_406CD0(v11, nLen);
      nLen = ElementCounta;
    }
    v7 = *((uint32_t *)FileName + 71) + 1;
    v8 = *((uint32_t *)FileName + 71) - 4999 < 0;
    *((uint32_t *)FileName + 71) = v7;
    if ( v8 == __OFSUB__(v7, 5000) )
    {
      fclose(*((FILE **)FileName + 65));
      pFile = fopen(FileName, FileName + 288);
      *((uint32_t *)FileName + 65) = pFile;
      fclose(pFile);
      *((uint32_t *)FileName + 65) = fopen(FileName, FileName + 288);
      sprintf(Buffer, "/******************************************************\n");
      if ( byte_79C7AC != 0 )
        sub_406CD0(Buffer, strlen(Buffer));
      fprintf(*((FILE *const *)FileName + 65), Buffer);
      sprintf(Buffer, "* %s - Log File Opened\n", FileName);
      if ( byte_79C7AC != 0 )
        sub_406CD0(Buffer, strlen(Buffer));
      fprintf(*((FILE *const *)FileName + 65), Buffer);
      sprintf(
        Buffer,
        "*     %02d/%02d/%04d - %2d:%02d:%02d\n",
        *((uint16_t *)FileName + 133),
        *((uint16_t *)FileName + 135),
        *((uint16_t *)FileName + 132),
        *((uint16_t *)FileName + 136),
        *((uint16_t *)FileName + 137),
        *((uint16_t *)FileName + 138));
      if ( byte_79C7AC != 0 )
        sub_406CD0(Buffer, strlen(Buffer));
      fprintf(*((FILE *const *)FileName + 65), Buffer);
      sprintf(Buffer, "******************************************************/\n\n\n\n\n\n");
      if ( byte_79C7AC != 0 )
        sub_406CD0(Buffer, strlen(Buffer));
      fprintf(*((FILE *const *)FileName + 65), Buffer);
      nLen = ElementCounta;
      *((uint32_t *)FileName + 71) = 0;
    }
    sub_66BC25(v11, 1u, nLen, *((FILE **)FileName + 65));
    LOBYTE(v3) = *(FileName + 280);
    if ( (uint8_t)v3 != 0 )
      LOBYTE(v3) = fflush(*((FILE **)FileName + 65));
  }
  return v3;
}



// ------------------------------------------------------------
// 0x404020 sub_404020
// ------------------------------------------------------------
char *sub_404020()
{
  unsigned int i; // esi
  char *result; // eax

  for ( i = 0; i < 16; ++i )
  {
    result = (&dword_79C568)[i];
    if ( result != nullptr )
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

  dword_796E502 = dword_796E50;
  result = *((uint32_t *)FileName + 65);
  if ( result != 0 )
  {
    sub_403D60(FileName, "\n\n\n\n\n/******************************************************\n");
    sprintf(Buffer, "* %s - Log File Closed\n", FileName);
    sub_403D60(FileName, Buffer);
    GetLocalTime(&SystemTime);
    sprintf(
      Buffer,
      "*     %02d/%02d/%04d - %2d:%02d:%02d\n",
      SystemTime.wMonth,
      SystemTime.wDay,
      SystemTime.wYear,
      SystemTime.wHour,
      SystemTime.wMinute,
      SystemTime.wSecond);
    sub_403D60(FileName, Buffer);
    sub_403D60(FileName, "******************************************************/\n");
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

  dword_796E502 = dword_796E50;
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )
    {
      strcpy(Mode, "wt");
    }
    else
    {
      if ( nArg2 != 2 )
      {
        *((uint32_t *)FileName + 65) = 0;
        return 0;
      }
      byte_79C7AC = 1;
      strcpy(Mode, "wt");
    }
  }
  else
  {
    *(uint32_t *)Mode = &unk_742B61;
  }
  *((uint32_t *)FileName + 65) = fopen(FileName, Mode);
  strcpy(FileName + 288, Mode);
  if ( *((uint32_t *)FileName + 65) == 0 )
    return 0;
  sub_403D60(FileName, "/******************************************************\n");
  sprintf(Buffer, "* %s - Log File Opened\n", FileName);
  sub_403D60(FileName, Buffer);
  GetLocalTime((LPSYSTEMTIME)(FileName + 264));
  sprintf(
    Buffer,
    "*     %02d/%02d/%04d - %2d:%02d:%02d\n",
    *((uint16_t *)FileName + 133),
    *((uint16_t *)FileName + 135),
    *((uint16_t *)FileName + 132),
    *((uint16_t *)FileName + 136),
    *((uint16_t *)FileName + 137),
    *((uint16_t *)FileName + 138));
  sub_403D60(FileName, Buffer);
  sub_403D60(FileName, "******************************************************/\n\n\n\n\n\n");
  return 1;
}



// ------------------------------------------------------------
// 0x404290 sub_404290
// ------------------------------------------------------------
char */*thiscall*/ sub_404290(char *FileName, const char *pArg2, int nArg3, char pszArg4, int nArg5)
{
  char *v5; // esi

  *((uint32_t *)FileName + 71) = 0;
  v5 = strcpy(FileName, pArg2);
  v5[280] = pszArg4;
  sub_404130(v5, nArg3, nArg5);
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
// 0x4042E0 sub_4042E0
// ------------------------------------------------------------
LRESULT /*stdcall*/ sub_4042E0(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)  // 【Win32 窗口框架：主窗口过程 / 消息循环 / 单实例检测 / 全屏分辨率切换】
{
  LONG WindowLongA; // eax

  WindowLongA = GetWindowLongA(hWnd, 0);
  if ( WindowLongA != 0 )
    return (*(int (/*thiscall*/ **)(LONG, HWND, UINT, WPARAM, LPARAM))(*(uint32_t *)WindowLongA + 32))(
             WindowLongA,
             hWnd,
             Msg,
             wParam,
             lParam);
  else
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}



// ------------------------------------------------------------
// 0x404330 sub_404330
// ------------------------------------------------------------
HWND /*thiscall*/ sub_404330(HWND *this, HWND nArg2, HWND cy)
{
  HWND result; // eax
  HWND fld_e4; // ecx

  result = nArg2;
  *(this + 11) = nArg2;
  *(this + 12) = cy;
  fld_e4 = *(this + 4);
  if ( fld_e4 != nullptr )
    return (HWND)SetWindowPos(fld_e4, nullptr, 0, 0, (int)nArg2, (int)cy, 6u);
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

  fld_4 = *(uint8_t *)(this + 4);
  pThis = this;
  if ( fld_4 == 0 )
    return -2147483647;
  ShowWindow(*(HWND *)(this + 16), 1);
  UpdateWindow(*(HWND *)(this + 16));
  SetFocus(*(HWND *)(this + 16));
  if ( *(uint32_t *)(this + 8) == 1 )
    ShowCursor(false);
  fld_8 = *(uint32_t *)(this + 8);
  if ( fld_8 == 1 || fld_8 == 4 )
  {
    while ( !PeekMessageA(&Msg, nullptr, 0, 0, 1u) )
    {
LABEL_16:
      if ( *(uint32_t *)(pThis + 124) != 0 )
      {
        sub_4052D0();  // 【tick_domains_step】
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pThis + 124) + 12))(*(uint32_t *)(pThis + 124));
      }
    }
    while ( Msg.message != 18 )
    {
      TranslateMessage(&Msg);
      DispatchMessageA(&Msg);
      if ( !PeekMessageA(&Msg, nullptr, 0, 0, 1u) )
        goto LABEL_16;
    }
    return 1;
  }
  else if ( fld_8 == 3 || fld_8 == 2 )
  {
    while ( GetMessageA(&Msg, nullptr, 0, 0) )
    {
      sub_4052D0();  // 【tick_domains_step】
      TranslateMessage(&Msg);
      DispatchMessageA(&Msg);
    }
    return Msg.wParam;
  }
  else
  {
    return -2147483639;
  }
}



// ------------------------------------------------------------
// 0x404490 sub_404490
// ------------------------------------------------------------
int /*stdcall*/ sub_404490(uint32_t *uArg1)
{
  if ( *uArg1 != 0 )
    (**(void (/*thiscall*/ ***)(uint32_t, int))*uArg1)(*uArg1, 1);
  *uArg1 = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x4044C0 sub_4044C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4044C0(uint32_t *this)
{
  *(this + 2) = 0;
  *(this + 8) = 1;
  *(this + 3) = 50;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 9) = -1;
  *(this + 10) = -1;
  *(this + 11) = -1;
  *(this + 12) = -1;
  *(this + 31) = 0;
  *(this + 32) = 0;
  sub_4072B0(this + 29);
  memset(&byte_89D160, 0, 0x100u);
  sub_6569D0(this + 33);
  sub_6569D0(this + 36);
  sub_6569D0(this + 39);
  sub_6569D0(this + 42);
  *((uint8_t *)this + 180) = 0;
  CoInitialize(nullptr);
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);
}



// ------------------------------------------------------------
// 0x404560 sub_404560
// ------------------------------------------------------------
int /*thiscall*/ sub_404560(int this)
{
  int result; // eax

  sub_407310(this + 116);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 28))(this);
  CoUninitialize();
  result = sub_4044C0((uint32_t *)this);
  *(uint8_t *)(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x404590 sub_404590
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_404590(uint32_t *this, int nArg2, int nArg3)
{
  HWND fld_e4; // eax
  uint32_t *result; // eax
  uint32_t *v6; // edi

  *(this + 9) = nArg2;
  *(this + 10) = nArg3;
  if ( nArg2 == -1 )
    *(this + 9) = (GetSystemMetrics(0) >> 1) - (*(this + 11) >> 1);
  if ( *(this + 10) == -1 )
    *(this + 10) = (GetSystemMetrics(1) >> 1) - (*(this + 12) >> 1);
  fld_e4 = (HWND)*(this + 4);
  if ( fld_e4 != nullptr )
    SetWindowPos(fld_e4, nullptr, *(this + 9), *(this + 10), 0, 0, 5u);
  result = (uint32_t *)*(this + 34);
  v6 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)v6[2] + 20))(
                           v6[2],
                           *(this + 9),
                           *(this + 10));
      v6 = (uint32_t *)*v6;
    }
    while ( v6 != (uint32_t *)*(this + 34) );
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

  if ( Msg <= 0x112 )
  {
    if ( Msg == 274 )
    {
      if ( (wParam & 0xFFF0) == 0xF050 )
        return 0;
    }
    else
    {
      if ( Msg > 0x102 )
      {
        switch ( Msg )
        {
          case 0x104u:
          case 0x105u:
            goto LABEL_14;
          case 0x10Du:
          case 0x10Eu:
          case 0x10Fu:
            goto LABEL_30;
          default:
            return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
        }
      }
      if ( Msg >= 0x100 )
      {
LABEL_14:
        sub_406D90(Msg, wParam, lParam);  // 【IME 输入法处理族（Composition/Candidate/NotifyIME…】
        sub_407900(Msg, wParam, lParam);
      }
      else
      {
        switch ( Msg )
        {
          case 2u:
            *(uint8_t *)(this + 180) = 1;
            PostQuitMessage(0);
            break;
          case 6u:
            *(uint32_t *)(this + 32) = (uint16_t)wParam;
            CurrentProcess = GetCurrentProcess();
            if ( (uint16_t)wParam != 0 )
              SetPriorityClass(CurrentProcess, 0x20u);
            else
              SetPriorityClass(CurrentProcess, 0x4000u);
            break;
          case 0x10u:
            *(uint8_t *)(this + 180) = 1;
            return 0;
          default:
            break;
        }
      }
    }
    return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
  }
  if ( Msg <= 0x216 )
  {
    if ( Msg == 534 )
    {
      sub_404590((uint32_t *)this, *lParam, lParam[1]);
    }
    else
    {
      switch ( Msg )
      {
        case 0x113u:
          if ( *(uint32_t *)(this + 32) == 0 )
          {
            sub_4052D0();  // 【tick_domains_step】
            fld_7C = *(uint32_t *)(this + 124);
            if ( fld_7C != 0 )
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_7C + 12))(fld_7C);
          }
          break;
        case 0x200u:
        case 0x201u:
        case 0x202u:
        case 0x204u:
        case 0x205u:
          sub_407110(Msg, wParam, lParam);
          break;
        default:
          return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
      }
    }
    return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
  }
  if ( Msg != 642 )
  {
    if ( Msg == 1124 )
    {
      fld_80 = *(uint32_t *)(this + 128);
      if ( fld_80 != 0 )
        (*(void (/*thiscall*/ **)(int, HWND, int, WPARAM, int *))(*(uint32_t *)fld_80 + 4))(fld_80, hWnd, 1124, wParam, lParam);
    }
    return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
  }
LABEL_30:
  sub_407900(Msg, wParam, lParam);
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

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  WindowA = FindWindowA(lpClassName, nullptr);
  if ( WindowA != nullptr )
  {
    SetForegroundWindow(WindowA);
    return -2147483646;
  }
  else
  {
    *(uint32_t *)(this + 20) = nArg2;
    *(uint32_t *)(this + 8) = nArg8;
    sub_402AE0(this + 52, lpClassName);
    sub_402AE0(this + 72, pArg4);
    if ( *(uint32_t *)(this + 44) == -1 )
      *(uint32_t *)(this + 44) = 800;
    if ( *(uint32_t *)(this + 48) == -1 )
      *(uint32_t *)(this + 48) = 600;
    sub_404590((uint32_t *)this, *(uint32_t *)(this + 36), *(uint32_t *)(this + 40));
    result = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 24))(this, nArg5, nArg6, nArg7, nArg8);
    if ( result >= 0 )
    {
      sub_4076E0(*(HWND *)(this + 16));
      hWnd = *(HWND *)(this + 16);
      *(uint8_t *)(this + 4) = 1;
      return 1;
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
  if ( nArg3 >= nArg4 )
    return fArg2;
  if ( nArg3 > 0 )
    return (fArg2 - fArg1) * (double)nArg3 / (double)nArg4 + fArg1;
  return fArg1;
}



// ------------------------------------------------------------
// 0x4049F0 sub_4049F0
// ------------------------------------------------------------
double /*cdecl*/ sub_4049F0(float fArg1, float fArg2, int nArg3, int nArg4, char pszArg5)
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

  if ( nArg3 >= nArg4 )
    return fArg2;
  if ( nArg3 <= 0 )
    return fArg1;
  fArg12 = fArg1;
  fArg22 = fArg2;
  if ( pszArg5 == 0 )
  {
    nArg3 = nArg4 - nArg3;
    fArg12 = fArg2;
    fArg22 = fArg1;
  }
  v8 = (double)nArg4;
  v9 = fabs(fArg22 - fArg12);
  v10 = (v9 + v9) / v8;
  v16 = v10;
  v15 = -(v10 / v8);
  v14 = (v15 * (double)nArg3 * 0.5 + v16) * (double)nArg3;
  if ( (v12 | v13) != 0 )
    return fArg12 - v14;
  else
    return fArg12 + v14;
}



// ------------------------------------------------------------
// 0x404A80 sub_404A80
// ------------------------------------------------------------
int /*cdecl*/ sub_404A80(int nArg1)
{
  dword_79D060 = nArg1;
  return nArg1;
}



// ------------------------------------------------------------
// 0x404A90 sub_404A90
// ------------------------------------------------------------
int /*cdecl*/ sub_404A90(uint8_t *uArg1)
{
  int result; // eax

  result = dword_79D060 + 1;
  *uArg1 = *(uint8_t *)dword_79D060;
  dword_79D060 = result;
  return result;
}



// ------------------------------------------------------------
// 0x404AB0 sub_404AB0
// ------------------------------------------------------------
int /*cdecl*/ sub_404AB0(uint16_t *uArg1)
{
  int result; // eax

  result = dword_79D060 + 2;
  *uArg1 = *(uint16_t *)dword_79D060;
  dword_79D060 = result;
  return result;
}



// ------------------------------------------------------------
// 0x404AD0 sub_404AD0
// ------------------------------------------------------------
int /*cdecl*/ sub_404AD0(uint32_t *uArg1)
{
  int result; // eax

  result = dword_79D060 + 4;
  *uArg1 = *(uint32_t *)dword_79D060;
  dword_79D060 = result;
  return result;
}



// ------------------------------------------------------------
// 0x404AF0 sub_404AF0
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_404AF0(void *pArg1, unsigned int uArg2)
{
  int dword_79D0602; // edx

  dword_79D0602 = dword_79D060;
  qmemcpy(pArg1, (const void *)dword_79D060, uArg2);
  dword_79D060 = uArg2 + dword_79D0602;
  return uArg2;
}



// ------------------------------------------------------------
// 0x404B30 sub_404B30
// ------------------------------------------------------------
int /*cdecl*/ sub_404B30(uint8_t *uArg1, const char *pArg2, int pArg3)
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

  dword_796E502 = dword_796E50;
  uArg12 = uArg1;
  for ( i = 200; i != 0; --i )
  {
    *uArg12 = 0;
    uArg12 += 1024;
  }
  v22 = 0;
  nLen = strlen(pArg2);
  v6 = nLen == 0;
  nLen2 = nLen;
  v7 = 0;
  v20 = 0;
  if ( v6 )
  {
    *(uint32_t *)(pArg3 + 40) = 0;
    return 0;
  }
  else
  {
    v8 = 0;
    v24 = 0;
    do
    {
      v9 = &uArg1[v8];
      v10 = &pArg2[v7];
      Source = v9;
      v11 = v9 - v10;
      do
      {
        v12 = *v10;
        v10[v11] = *v10;
        ++v10;
      }
      while ( v12 != 0 );
      psz = 0;
      if ( *v9 == 10 )
      {
LABEL_62:
        v16 = psz + v24;
        ++psz;
LABEL_66:
        uArg1[v16] = 0;
      }
      else
      {
        while ( 1 )
        {
          v14 = v9[psz];
          if ( v14 == 13 )
            break;
          if ( v14 < 0
            && (v14 == -127
             || v14 == -126
             || v14 == -125
             || v14 == -124
             || v14 == -121
             || v14 == -120
             || v14 == -119
             || v14 == -118
             || v14 == -117
             || v14 == -116
             || v14 == -115
             || v14 == -114
             || v14 == -113
             || v14 == -112
             || v14 == -111
             || v14 == -110
             || v14 == -109
             || v14 == -108
             || v14 == -107
             || v14 == -106
             || v14 == -105
             || v14 == -104
             || v14 == -103
             || v14 == -102
             || v14 == -101
             || v14 == -100
             || v14 == -99
             || v14 == -98
             || v14 == -97
             || v14 == -32
             || v14 == -31
             || v14 == -30
             || v14 == -29
             || v14 == -28
             || v14 == -27
             || v14 == -26
             || v14 == -25
             || v14 == -24
             || v14 == -23
             || v14 == -22
             || v14 == -19
             || v14 == -18
             || v14 == -6
             || v14 == -5
             || v14 == -4) )
          {
            memset(Destination, 0, sizeof(Destination));
            v15 = psz + 2;
            strncpy(Destination, Source, psz + 2);
            if ( (*(int (/*thiscall*/ **)(uint32_t, char *, uint32_t))(**(uint32_t **)(pArg3 + 48) + 24))(
                   *(uint32_t *)(pArg3 + 48),
                   Destination,
                   *(uint32_t *)(pArg3 + 28)) != -1 )
            {
              uArg1[psz + v24] = 0;
              goto LABEL_67;
            }
          }
          else
          {
            memset(Destination, 0, sizeof(Destination));
            v15 = psz + 1;
            strncpy(Destination, Source, psz + 1);
            if ( (*(int (/*thiscall*/ **)(uint32_t, char *, uint32_t))(**(uint32_t **)(pArg3 + 48) + 24))(
                   *(uint32_t *)(pArg3 + 48),
                   Destination,
                   *(uint32_t *)(pArg3 + 28)) != -1 )
            {
              v16 = psz + v24;
              goto LABEL_66;
            }
          }
          psz = v15;
          if ( v15 >= nLen2 )
            goto LABEL_67;
          if ( Source[v15] == 10 )
            goto LABEL_62;
          v9 = Source;
        }
        v17 = v24 + psz++;
        uArg1[v17] = 0;
        if ( uArg1[psz + v24] == 10 )
          ++psz;
      }
LABEL_67:
      v7 = psz + v20;
      ++v22;
      v8 = v24 + 1024;
      v18 = psz + v20 < nLen2;
      v20 += psz;
      v24 += 1024;
    }
    while ( v18 );
    *(uint32_t *)(pArg3 + 40) = v22;
    return v22;
  }
}


// ------------------------------------------------------------
// 0x404E30 sub_404E30
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_404E30(int pArg1, int nArg2)
{
  int v2; // eax
  int v3; // eax
  int v5; // eax

  v2 = *(uint32_t *)(pArg1 + 12);
  if ( v2 != 0 )
  {
    v3 = v2 - 1;
    if ( v3 != 0 )
    {
      if ( v3 == 1 )
        return *(uint32_t *)(pArg1 + 28) - 5 * nArg2;
    }
    else
    {
      v5 = *(uint32_t *)(pArg1 + 28);
      if ( v5 > 5 * nArg2 )
        return (unsigned int)(v5 - 5 * nArg2) >> 1;
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

  _EAX = 0;
  v49 = 0;
  v51 = 200;
  do
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
    --v51;
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
  Sleep(0x64u);
  __asm
  {
    cpuid
    cpuid
  }
  memset(&dword_79CD40, 0, 0x320u);
  memset(&dword_79CA20, 0, 0x320u);
  dbl_79D070 = (double)(int64_t)(__rdtsc() - __PAIR64__(v50, v38) - v25 / 200) * 0.00001;
  memset(&dword_79C958, 0, 0xC8u);
  return 0;
}



// ------------------------------------------------------------
// 0x404F40 sub_404F40
// ------------------------------------------------------------
void /*usercall*/ sub_404F40(int _EAX@<eax>, unsigned int uArg2)
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
// 0x404F80 sub_404F80
// ------------------------------------------------------------
void /*usercall*/ sub_404F80(int _EAX@<eax>, unsigned int uArg2, char pszArg3)
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
    _EAX = 0;
    if ( pszArg3 != 0 )
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
// 0x405030 sub_405030
// ------------------------------------------------------------
int /*cdecl*/ sub_405030(unsigned int uArg1)
{
  if ( uArg1 < 0x64 )
    return dword_79CD40[2 * uArg1];
  else
    return 0;
}



// ------------------------------------------------------------
// 0x405060 sub_405060
// ------------------------------------------------------------
int /*cdecl*/ sub_405060(unsigned int uArg1, int nArg2, char pszArg3)
{
  int result; // eax

  if ( uArg1 < 0x32 )
  {
    if ( dbl_79D070 == 0.0 )
      sub_404E70();
    if ( pszArg3 == 1 )
      dword_79C958[uArg1] = 0;
    dword_79C958[uArg1] += nArg2;
    return nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4050B0 sub_4050B0
// ------------------------------------------------------------
int /*cdecl*/ sub_4050B0(unsigned int uArg1)
{
  if ( uArg1 >= 0x32 )
    return 0;
  if ( dbl_79D070 == 0.0 )
    sub_404E70();
  return dword_79C958[uArg1];
}



// ------------------------------------------------------------
// 0x4050F0 sub_4050F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4050F0(uint32_t *this)
{
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  return this + 2;
}



// ------------------------------------------------------------
// 0x405160 sub_405160
// ------------------------------------------------------------
HGDIOBJ */*thiscall*/ sub_405160(HGDIOBJ *this)
{
  HGDIOBJ *pThis_2; // esi
  int i; // ebx

  pThis_2 = this + 2;
  for ( i = 30; i != 0; --i )
  {
    if ( *pThis_2 != nullptr )
    {
      DeleteObject(*pThis_2);
      *pThis_2 = nullptr;
    }
    ++pThis_2;
  }
  *((uint8_t *)this + 4) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4051A0 sub_4051A0
// ------------------------------------------------------------
int sub_4051A0()  // 【tick_domains_init】
{
  dword_79D140 = timeGetTime();
  dword_79D080 = 0;
  dword_79D100[0] = 0;
  dword_79D084 = 0;
  dword_79D104 = 0;
  dword_79D088 = 0;
  dword_79D108 = 0;
  dword_79D08C = 0;
  dword_79D10C = 0;
  dword_79D0C0 = 100;
  dword_79D0C4 = 100;
  dword_79D0C8 = 100;
  dword_79D0CC = 100;
  dword_79D090 = 0;
  dword_79D0D0 = 100;
  dword_79D110 = 0;
  dword_79D094 = 0;
  dword_79D0D4 = 100;
  dword_79D114 = 0;
  dword_79D098 = 0;
  dword_79D0D8 = 100;
  dword_79D118 = 0;
  dword_79D09C = 0;
  dword_79D0DC = 100;
  dword_79D11C = 0;
  dword_79D0A0 = 0;
  dword_79D0E0 = 100;
  dword_79D120 = 0;
  dword_79D0A4 = 0;
  dword_79D0E4 = 100;
  dword_79D124 = 0;
  dword_79D0A8 = 0;
  dword_79D0E8 = 100;
  dword_79D128 = 0;
  dword_79D0AC = 0;
  dword_79D0EC = 100;
  dword_79D12C = 0;
  dword_79D0B0 = 0;
  dword_79D0F0 = 100;
  dword_79D130 = 0;
  dword_79D0B4 = 0;
  dword_79D0F4 = 100;
  dword_79D134 = 0;
  dword_79D0B8 = 0;
  dword_79D0F8 = 100;
  dword_79D138 = 0;
  dword_79D0BC = 0;
  dword_79D0FC = 100;
  dword_79D13C = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4052D0 sub_4052D0
// ------------------------------------------------------------
DWORD sub_4052D0()  // 【tick_domains_step】
{
  double dwNow; // st7
  int i; // esi
  double v2; // st6
  DWORD result; // eax
  int v4; // [esp+8h] [ebp-4h]

  dwNow = (double)(int)(timeGetTime() - dword_79D140);
  for ( i = 0; i < 16; *(float *)(i * 4 + 7983228) = v2 - (double)v4 )
  {
    v2 = (double)dword_79D0C0[i] * dwNow * 0.0099999998 + *(float *)(i * 4 + 7983232);
    v4 = (uint64_t)v2;
    dword_79D100[i++] += v4;
  }
  result = timeGetTime();
  dword_79D140 = result;
  return result;
}



// ------------------------------------------------------------
// 0x405340 sub_405340
// ------------------------------------------------------------
int sub_405340()
{
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  if ( dword_79D154 != nullptr )
    j__free(dword_79D154);
  dword_79D154 = nullptr;
  if ( dword_79D150 != nullptr )
    j__free(dword_79D150);
  dword_79D150 = nullptr;
  if ( dword_79D14C != nullptr )
    j__free(dword_79D14C);
  dword_79D14C = nullptr;
  if ( dword_79D148 != nullptr )
    j__free(dword_79D148);
  dword_79D148 = nullptr;
  if ( dword_79D144 != nullptr )
    j__free(dword_79D144);
  dword_79D144 = nullptr;
  return 1;
}



// ------------------------------------------------------------
// 0x4053E0 sub_4053E0
// ------------------------------------------------------------
double /*cdecl*/ sub_4053E0(int nArg1)
{
  return *((float *)dword_79D150 + (nArg1 % 360 + 360) % 360);
}



// ------------------------------------------------------------
// 0x405400 sub_405400
// ------------------------------------------------------------
double /*cdecl*/ sub_405400(int nArg1)
{
  return *((float *)dword_79D154 + (nArg1 % 360 + 360) % 360);
}



// ------------------------------------------------------------
// 0x405420 sub_405420
// ------------------------------------------------------------
double /*cdecl*/ sub_405420(int nArg1)
{
  return *((float *)Block + (nArg1 % 360 + 360) % 360);
}



// ------------------------------------------------------------
// 0x405440 sub_405440
// ------------------------------------------------------------
int sub_405440()
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
    return -2147483646;
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
    do
    {
      v5 = (double)(v1 - 90);
      ++v1;
      ++v0;
      v6 = v5 * 0.0174532925199433;
      *(float *)((char *)v0 + v2 - 4) = sin(v6);
      v7 = (double)v12;
      v12 = v1;
      v11 = v7 * 0.0174532925199433;
      *(v0 - 1) = sin(v11);
      *(float *)((char *)v0 + v3 - 4) = cos(v6);
      *(float *)((char *)v0 + v4 - 4) = cos(v11);
      *(float *)((char *)v0 + v10 - 4) = tan(v6);
      *(float *)((char *)v0 + v9 - 4) = tan(v11);
    }
    while ( v1 < 360 );
    return 1;
  }
  else
  {
    sub_405340();
    return -2147483640;
  }
}



// ------------------------------------------------------------
// 0x4055B0 sub_4055B0
// ------------------------------------------------------------
int /*cdecl*/ sub_4055B0(uint16_t *uArg1, int nArg2, unsigned int uArg3, unsigned int uArg4)
{
  unsigned int uArg42; // eax
  void *uArg12; // edi
  uint16_t v6; // ax
  int v7; // edx
  uint16_t v8; // bx
  int result; // eax

  uArg42 = uArg4;
  uArg12 = uArg1;
  if ( (uArg3 & 1) != 0 )
  {
    LOBYTE(v6) = 0;
    HIBYTE(v6) = uArg4 & 0xF8;
    uArg12 = uArg1 + 1;
    v7 = v6 | (uArg4 >> 19) & 0x1F | (uArg4 >> 5) & 0x7E0;
    uArg42 = uArg4;
    *uArg1 = v7;
  }
  LOBYTE(v8) = 0;
  HIBYTE(v8) = uArg42 & 0xF8;
  result = (uArg42 >> 5) & 0x7E0 | (uArg42 >> 19) & 0x1F | v8 | (((uArg42 >> 5) & 0x7E0 | (uArg42 >> 19) & 0x1F | v8) << 16);
  if ( uArg3 >> 1 != 0 )
    memset32(uArg12, result, uArg3 >> 1);
  return result;
}



// ------------------------------------------------------------
// 0x405630 sub_405630
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_405630(uint16_t *uArg1, uint16_t *uArg2, unsigned int uArg3)
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
  if ( (uArg3 & 1) != 0 )
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
    do
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
      uArg12 += 2;
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
// 0x4057E0 sub_4057E0
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_4057E0(unsigned int *pDwArg1, char *pszArg2, unsigned int uArg3, int pArg4)
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
  if ( (uArg3 & 1) != 0 )
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
  if ( v7 != 0 )
  {
    v9 = pszArg22 - (char *)pDwArg12;
    v13 = v9;
    v14 = v7;
    while ( 1 )
    {
      v10 = *(unsigned int *)((char *)result + v9);
      v11 = *result;
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
        break;
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
  while ( 1 )
  {
    v1 = 0;
    v33 = 0;
    v34 = 0;
    v35 = 0;
    v2 = v37 << 12;
    while ( 1 )
    {
      v31 = 0;
      v36 = 32 * v1;
      v3 = v2;
      do
      {
        v4 = (double)v31;
        v5 = (uint64_t)((double)v35 / (32.0 - v4));
        if ( (unsigned int)v5 > 0x1F )
          LODWORD(v5) = 31;
        *(int *)((char *)dword_87D160 + v3) = v5;
        v6 = v36 / (v37 + 32);
        if ( v6 >= 0x1F )
          v6 = 31;
        *(int *)((char *)&dword_7DD160 + v3) = v6;
        v7 = v1;
        if ( v1 > v0 || (v7 = v0, v8 = v1, v1 >= v0) )
          v8 = v0;
        if ( (unsigned int)(v7 - v8 - v37 + 32) >= 0x1F )
        {
          v11 = 31;
        }
        else
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
        else
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
        else
        {
          v20 = v1;
          if ( v1 <= v0 )
            v20 = v0;
          v21 = v37 + v20;
        }
        ++v0;
        *(int *)((char *)&dword_85D160 + v3) = v21;
        v3 += 4;
        v31 = v0;
        v36 += v33;
      }
      while ( v0 < 32 );
      v2 = v3;
      v35 += v37;
      ++v1;
      v22 = v33 - 1 <= -32;
      v34 += v32;
      --v33;
      if ( v22 )
        break;
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
        v24 += 16;
      }
      v23 += 32;
    }
    v22 = v32 - 1 <= 0;
    ++v37;
    --v32;
    v30 = v23;
    v29 = v24;
    if ( v22 )
      break;
    v0 = 0;
  }
  return 1;
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

  memset(&pBuf, 0, sizeof(pBuf));
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
  pBuf.lpfnWndProc = sub_4042E0;
  if ( RegisterClassExA(&pBuf) == 0 )
    return 0;
  v9 = 0;
  switch ( *(uint32_t *)(dwNewLong + 8) )
  {
    case 1:
    case 2:
      v9 = 0x80000000;
      break;
    case 3:
    case 4:
      v9 = 13565952;
      SetRect(&rc, 0, 0, *(uint32_t *)(dwNewLong + 44), *(uint32_t *)(dwNewLong + 48));
      AdjustWindowRect(&rc, (DWORD)&unk_840000, true);
      v10 = rc.bottom - rc.top;
      *(uint32_t *)(dwNewLong + 44) = rc.right - rc.left;
      *(uint32_t *)(dwNewLong + 48) = v10;
      break;
    default:
      break;
  }
  if ( nArg2 != 0 )
    *(uint32_t *)(dwNewLong + 24) = LoadMenuA(*(HINSTANCE *)(dwNewLong + 20), (LPCSTR)(uint16_t)nArg2);
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
  *(uint32_t *)(dwNewLong + 16) = Window;
  if ( Window == nullptr )
    return 0x80000000;
  SetWindowLongA(Window, 0, dwNewLong);
  SetWindowTextA(*(HWND *)(dwNewLong + 16), *(LPCSTR *)(dwNewLong + 80));
  hWnd = *(HWND *)(dwNewLong + 16);
  return 1;
}



// ------------------------------------------------------------
// 0x405DA0 sub_405DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_405DA0(int this)
{
  HWND fld_10; // eax
  int result; // eax

  if ( *(uint32_t *)(this + 24) != 0 )
  {
    DestroyMenu(*(HMENU *)(this + 24));
    *(uint32_t *)(this + 24) = 0;
  }
  fld_10 = *(HWND *)(this + 16);
  if ( fld_10 != nullptr )
  {
    ShowWindow(fld_10, 0);
    DestroyWindow(*(HWND *)(this + 16));
    *(uint32_t *)(this + 16) = 0;
  }
  result = *(uint32_t *)(this + 20);
  if ( result != 0 )
  {
    result = UnregisterClassA(*(LPCSTR *)(this + 60), *(HINSTANCE *)(this + 20));
    *(uint32_t *)(this + 20) = 0;
  }
  return result;
}



// ============================================================
// SECTION 0x405E00 — 引擎子系统事件分发框架（list/vector 容器事件路由，0x405E00-0x406C50）
// ============================================================
// ------------------------------------------------------------
// 0x405E00 sub_405E00
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_405E00(uint8_t *this, int nArg2, int nArg3)
{
  char *pThis_10; // edi

  *(this + 4) = 0;
  pThis_10 = this + 16;
  *(uint32_t *)this = &off_6C1948;
  *((uint32_t *)this + 2) = nArg2;
  *((uint32_t *)this + 5) = sub_425940(this + 16);
  *((uint32_t *)pThis_10 + 2) = 0;
  *((uint32_t *)this + 7) = nArg3;
  sub_407AD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x405E70 sub_405E70
// ------------------------------------------------------------
int /*thiscall*/ sub_405E70(void **this)
{
  *this = &off_6C1948;
  sub_407B20();
  sub_6569D0(this + 4);
  j__free(*(this + 5));
  *(this + 5) = nullptr;
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x405EE0 sub_405EE0
// ------------------------------------------------------------
void **/*thiscall*/ sub_405EE0(void **Block, char pszArg2)
{
  sub_405E70(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x405F10 sub_405F10
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_405F10(uint8_t *this, int nArg2, int nArg3)
{
  char *pThis_28; // edi

  *(this + 4) = 0;
  *((uint32_t *)this + 9) = nArg3;
  pThis_28 = this + 40;
  *(uint32_t *)this = &off_6C1960;
  *((uint32_t *)this + 2) = nArg2;
  *((uint32_t *)this + 11) = sub_425940(this + 40);
  *((uint32_t *)pThis_28 + 2) = 0;
  sub_407CF0(this);
  return this;
}



// ------------------------------------------------------------
// 0x405F80 sub_405F80
// ------------------------------------------------------------
int /*thiscall*/ sub_405F80(void **this)
{
  *this = &off_6C1960;
  sub_407C90();
  sub_6569D0(this + 10);
  j__free(*(this + 11));
  *(this + 11) = nullptr;
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x405FF0 sub_405FF0
// ------------------------------------------------------------
void **/*thiscall*/ sub_405FF0(void **Block, char pszArg2)
{
  sub_405F80(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x406020 sub_406020
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406020(uint8_t *this, int nArg2, int nArg3)
{
  char *pThis_10; // edi

  *(this + 4) = 0;
  *((uint32_t *)this + 3) = nArg3;
  pThis_10 = this + 16;
  *(uint32_t *)this = &off_6C19A0;
  *((uint32_t *)this + 2) = nArg2;
  *((uint32_t *)this + 5) = sub_425940(this + 16);
  *((uint32_t *)pThis_10 + 2) = 0;
  sub_407E80(this);
  return this;
}



// ------------------------------------------------------------
// 0x406090 sub_406090
// ------------------------------------------------------------
int /*thiscall*/ sub_406090(void **this)
{
  *this = &off_6C19A0;
  sub_416420();
  sub_6569D0(this + 4);
  j__free(*(this + 5));
  *(this + 5) = nullptr;
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x406100 sub_406100
// ------------------------------------------------------------
void **/*thiscall*/ sub_406100(void **Block, char pszArg2)
{
  sub_406090(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x406130 sub_406130
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406130(uint8_t *this, int nArg2, int nArg3)
{
  char *pThis_24; // edi

  *(this + 4) = 0;
  *((uint32_t *)this + 8) = nArg3;
  pThis_24 = this + 36;
  *(uint32_t *)this = &off_6C19C8;
  *((uint32_t *)this + 2) = nArg2;
  *((uint32_t *)this + 10) = sub_425940(this + 36);
  *((uint32_t *)pThis_24 + 2) = 0;
  *((uint32_t *)this + 13) = sub_425940(this + 48);
  *((uint32_t *)this + 14) = 0;
  sub_408060(this);
  return this;
}



// ------------------------------------------------------------
// 0x4061C0 sub_4061C0
// ------------------------------------------------------------
void /*thiscall*/ sub_4061C0(void **this)
{
  *this = &off_6C19C8;
  sub_408050();
  sub_6569D0(this + 12);
  j__free(*(this + 13));
  *(this + 13) = nullptr;
  sub_6569D0(this + 9);
  j__free(*(this + 10));
  *(this + 10) = nullptr;
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
}



// ------------------------------------------------------------
// 0x406250 sub_406250
// ------------------------------------------------------------
void **/*thiscall*/ sub_406250(void **Block, char pszArg2)
{
  sub_4061C0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x406280 sub_406280
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406280(uint8_t *this, int nArg2, int nArg3)
{
  sub_405F10(this, nArg2, nArg3);
  *(uint32_t *)this = &off_6C19E8;
  sub_408AC0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4062E0 sub_4062E0
// ------------------------------------------------------------
void */*thiscall*/ sub_4062E0(void *Block, char pszArg2)
{
  sub_406310();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x406310 sub_406310
// ------------------------------------------------------------
int /*thiscall*/ sub_406310(void **this)
{
  *this = &off_6C19E8;
  sub_407C90();
  return sub_405F80(this);
}



// ------------------------------------------------------------
// 0x406360 sub_406360
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406360(uint8_t *this, int nArg2, int nArg3)
{
  sub_406130(this, nArg2, nArg3);
  *(uint32_t *)this = &off_6C1A44;
  sub_40AA10(this);
  return this;
}



// ------------------------------------------------------------
// 0x4063C0 sub_4063C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4063C0(void *Block, char pszArg2)
{
  sub_4063F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4063F0 sub_4063F0
// ------------------------------------------------------------
void /*thiscall*/ sub_4063F0(void **this)
{
  *this = &off_6C1A44;
  sub_408050();
  sub_4061C0(this);
}



// ------------------------------------------------------------
// 0x406440 sub_406440
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406440(uint8_t *this, int nArg2, int nArg3)
{
  sub_406130(this, nArg2, nArg3);
  *(uint32_t *)this = &off_6C1A60;
  sub_40AE80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4064A0 sub_4064A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4064A0(void *Block, char pszArg2)
{
  sub_4064D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4064D0 sub_4064D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4064D0(void **this)
{
  *this = &off_6C1A60;
  sub_408050();
  sub_4061C0(this);
}



// ------------------------------------------------------------
// 0x406520 sub_406520
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406520(uint8_t *this, int nArg2, int nArg3)
{
  sub_406020(this, nArg2, nArg3);
  *(uint32_t *)this = &off_6C1A7C;
  sub_40B130(this);
  return this;
}



// ------------------------------------------------------------
// 0x406580 sub_406580
// ------------------------------------------------------------
void */*thiscall*/ sub_406580(void *Block, char pszArg2)
{
  sub_4065B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4065B0 sub_4065B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4065B0(void **this)
{
  *this = &off_6C1A7C;
  sub_416420();
  return sub_406090(this);
}



// ------------------------------------------------------------
// 0x406600 sub_406600
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_406600(uint8_t *this, int nArg2, int nArg3)
{
  sub_406020(this, nArg2, nArg3);
  *(uint32_t *)this = &off_6C1AA4;
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x406660 sub_406660
// ------------------------------------------------------------
void */*thiscall*/ sub_406660(void *Block, char pszArg2)
{
  sub_406690();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x406690 sub_406690
// ------------------------------------------------------------
int /*thiscall*/ sub_406690(void **this)
{
  *this = &off_6C1AA4;
  sub_416420();
  return sub_406090(this);
}



// ------------------------------------------------------------
// 0x4066E0 sub_4066E0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4066E0(uint8_t *this, int nArg2, int nArg3)
{
  sub_405E00(this, nArg2, nArg3);
  *(uint32_t *)this = &off_6C1ACC;
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x406740 sub_406740
// ------------------------------------------------------------
void */*thiscall*/ sub_406740(void *Block, char pszArg2)
{
  sub_406770();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x406770 sub_406770
// ------------------------------------------------------------
int /*thiscall*/ sub_406770(void **this)
{
  *this = &off_6C1ACC;
  sub_407B20();
  return sub_405E70(this);
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

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x406850 sub_406850
// ------------------------------------------------------------
int /*thiscall*/ sub_406850(uint32_t *this, int nArg2)
{
  int fld_e1; // edi
  int v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), nArg2);
  result = sub_4067C0(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  **(uint32_t **)(v4 + 4) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x406890 sub_406890
// ------------------------------------------------------------
int /*thiscall*/ sub_406890(uint32_t *this, int nArg2, uint32_t *Block)
{
  uint8_t *pMem; // eax
  uint8_t *v6; // eax
  int fld_e34; // edi
  int v8; // ebx

  *Block = 0;
  *Block = 0;
  if ( nArg2 != 3 )
    return -2147483639;
  pMem = operator new(0x2CEFCu);
  if ( pMem != nullptr )
    v6 = sub_406280(pMem, 3, (int)this);
  else
    v6 = nullptr;
  if ( v6 == nullptr )
    return -2147483640;
  *Block = v6;
  fld_e34 = *(this + 34);
  v8 = sub_40C0F0(fld_e34, *(uint32_t *)(fld_e34 + 4), Block);
  sub_4067C0(this + 33, 1u);
  *(uint32_t *)(fld_e34 + 4) = v8;
  **(uint32_t **)(v8 + 4) = v8;
  return 1;
}



// ------------------------------------------------------------
// 0x406970 sub_406970
// ------------------------------------------------------------
int /*thiscall*/ sub_406970(uint32_t *this, int nArg2, uint32_t *Block)
{
  uint8_t *pMem; // eax
  uint8_t *v5; // eax
  uint8_t *pMem2; // eax

  *Block = 0;
  switch ( nArg2 )
  {
    case 1:
      *Block = 0;
      pMem = operator new(0x44u);
      if ( pMem != nullptr )
        v5 = sub_406360(pMem, nArg2, (int)this);
      else
        v5 = nullptr;
      goto LABEL_7;
    case 2:
      *Block = 0;
      pMem2 = operator new(0x3Cu);
      if ( pMem2 != nullptr )
        v5 = sub_406440(pMem2, nArg2, (int)this);
      else
        v5 = nullptr;
LABEL_7:
      if ( v5 == nullptr )
        return -2147483640;
      *Block = v5;
LABEL_11:
      sub_406850(this + 36, (int)Block);
      return 1;
    case 3:
      *Block = 0;
      goto LABEL_11;
    default:
      *Block = 0;
      return -2147483639;
  }
}



// ------------------------------------------------------------
// 0x406A80 sub_406A80
// ------------------------------------------------------------
int /*thiscall*/ sub_406A80(uint32_t *this, int nArg2, uint32_t *Block)
{
  uint8_t *pMem2; // eax
  uint8_t *v6; // eax
  uint8_t *pMem; // eax
  int fld_e40; // edi
  int v9; // ebx

  *Block = 0;
  *Block = 0;
  if ( nArg2 == 1 )
  {
    pMem = operator new(0x1Cu);
    if ( pMem != nullptr )
      v6 = sub_406600(pMem, 1, (int)this);
    else
      v6 = nullptr;
  }
  else
  {
    if ( nArg2 != 2 )
      return -2147483639;
    pMem2 = operator new(0x20u);
    if ( pMem2 != nullptr )
      v6 = sub_406520(pMem2, 2, (int)this);
    else
      v6 = nullptr;
  }
  if ( v6 == nullptr )
    return -2147483640;
  *Block = v6;
  fld_e40 = *(this + 40);
  v9 = sub_40C0F0(fld_e40, *(uint32_t *)(fld_e40 + 4), Block);
  sub_4067C0(this + 39, 1u);
  *(uint32_t *)(fld_e40 + 4) = v9;
  **(uint32_t **)(v9 + 4) = v9;
  return 1;
}



// ------------------------------------------------------------
// 0x406B80 sub_406B80
// ------------------------------------------------------------
int /*thiscall*/ sub_406B80(uint32_t *this, int nArg2, uint32_t *uArg3)
{
  uint8_t *pMem; // eax
  uint8_t *v6; // eax

  *uArg3 = 0;
  if ( nArg2 == 1 )
    return 0;
  if ( nArg2 == 2 )
  {
    pMem = operator new(0x20u);
    if ( pMem != nullptr )
      v6 = sub_4066E0(pMem, 2, (int)this);
    else
      v6 = nullptr;
    if ( v6 != nullptr )
    {
      *uArg3 = v6;
      sub_406850(this + 42, (int)uArg3);
      return 1;
    }
    else
    {
      return -2147483640;
    }
  }
  else
  {
    *uArg3 = 0;
    return -2147483639;
  }
}



// ============================================================
// SECTION 0x406C50 — NiMemory.log / NiProfile.log 日志对象（Gamebryo 风格内存/性能日志）
// ============================================================
// ------------------------------------------------------------
// 0x406C50 sub_406C50
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

  result = sub_403990((int)"NiMemory.log", 1, 1, 0);
  if ( result >= 0 )
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

  result = sub_403990((int)"NiProfile.log", 1, 1, 0);
  if ( result >= 0 )
  {
    dword_79C7D8 = result;
    dword_79C7E4 = result;
    dword_79C7F0 = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x406CD0 sub_406CD0
// ------------------------------------------------------------
char /*cdecl*/ sub_406CD0(int nArg1, unsigned int uArg2)
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
// 0x406D00 sub_406D00
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_406D00(uint32_t *this, uint32_t *uArg2, int nArg3, unsigned int uArg4)
{
  uint32_t *pThis_1; // ebx
  uint32_t *pThis_12; // eax
  unsigned int v7; // esi
  unsigned int uArg42; // eax
  uint32_t *result; // eax

  pThis_1 = this + 1;
  if ( *(this + 6) < 0x10u )
    pThis_12 = this + 1;
  else
    pThis_12 = (uint32_t *)*pThis_1;
  if ( nArg3 != 0 )
    v7 = nArg3 - (uint32_t)pThis_12;
  else
    v7 = 0;
  uArg42 = uArg4;
  if ( uArg4 != 0 )
    uArg42 = uArg4 - nArg3;
  sub_401230(this, v7, uArg42);
  result = uArg2;
  if ( *(this + 6) < 0x10u )
    *uArg2 = (char *)pThis_1 + v7;
  else
    *uArg2 = *pThis_1 + v7;
  return result;
}



// ------------------------------------------------------------
// 0x406D60 sub_406D60
// ------------------------------------------------------------
size_t */*thiscall*/ sub_406D60(size_t *this, char *Src)
{
  return sub_4015C0(this, Src, strlen(Src));  // 【std::string构造赋值】
}



// ============================================================
// SECTION 0x406D90 — IME 输入法处理族（Composition/Candidate/NotifyIME，日志直证）
// ============================================================
// ------------------------------------------------------------
// 0x406D90 sub_406D90
// ------------------------------------------------------------
int /*stdcall*/ sub_406D90(int nArg1, unsigned int uArg2, int nArg3)  // 【IME 输入法处理族（Composition/Candidate/NotifyIME…】
{
  int result; // eax

  result = nArg1 - 256;
  if ( nArg1 == 256 )
  {
    if ( uArg2 >= 0x100 )
      return result;
    byte_89D160[uArg2] = 1;
  }
  else
  {
    result = nArg1 - 257;
    if ( nArg1 == 257 )
    {
      if ( uArg2 >= 0x100 )
        return result;
      byte_89D160[uArg2] = 0;
    }
  }
  if ( dword_89D260 != 0 )
    return (**(int (/*thiscall*/ ***)(int, int, unsigned int, int))dword_89D260)(dword_89D260, nArg1, uArg2, nArg3);
  return result;
}



// ------------------------------------------------------------
// 0x406DF0 sub_406DF0
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_406DF0(LONG uArg1, LONG uArg2)
{
  BOOL result; // eax
  struct tagPOINT Point; // [esp+8h] [ebp-8h] BYREF

  Point.x = uArg1;
  Point.y = uArg2;
  ClientToScreen(hWnd, &Point);
  result = SetCursorPos(Point.x, Point.y);
  pt.y = uArg2;
  pt.x = uArg1;
  return result;
}



// ------------------------------------------------------------
// 0x406E40 sub_406E40
// ------------------------------------------------------------
void /*thiscall*/ sub_406E40(int this)
{
  int fld_10; // eax
  int v3; // eax
  int i; // edi
  void *fld_4; // eax

  while ( *(uint32_t *)(this + 16) != 0 )
  {
    fld_10 = *(uint32_t *)(this + 16);
    if ( fld_10 != 0 )
    {
      v3 = fld_10 - 1;
      *(uint32_t *)(this + 16) = v3;
      if ( v3 == 0 )
        *(uint32_t *)(this + 12) = 0;
    }
  }
  for ( i = *(uint32_t *)(this + 8); i != 0; --i )
  {
    fld_4 = *(void **)(*(uint32_t *)(this + 4) + 4 * i - 4);
    if ( fld_4 != nullptr )
      j__free(fld_4);
  }
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x406EB0 sub_406EB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_406EB0(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
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

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "deque<T> too long", 0x11u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x406F40 sub_406F40
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_406F40(int this, unsigned int uArg2)
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

  uArg22 = uArg2;
  fld_8 = *(uint32_t *)(this + 8);
  if ( 0xFFFFFFF - fld_8 < uArg2 )
    sub_406ED0(this);
  v5 = fld_8 >> 1;
  if ( fld_8 >> 1 < 8 )
    v5 = 8;
  if ( uArg2 < v5 && fld_8 <= 0xFFFFFFF - v5 )
  {
    uArg2 = v5;
    uArg22 = v5;
  }
  fld_C = *(uint32_t *)(this + 12) >> 2;
  v7 = 4 * fld_C;
  pMem = (char *)operator new(4 * (uArg22 + fld_8));
  fld_82 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * fld_C) >> 2);
  fld_4 = (char *)memcpy_0(&pMem[4 * fld_C], (const void *)(4 * fld_C + *(uint32_t *)(this + 4)), fld_82);
  fld_42 = *(const void **)(this + 4);
  v10 = &fld_4[fld_82];
  if ( fld_C > uArg2 )
  {
    memcpy_0(v10, fld_42, 4 * ((int)(4 * uArg2) >> 2));
    v14 = 4 * ((int)(v7 - 4 * uArg2) >> 2);
    fld_43 = (char *)memcpy_0(pMem, (const void *)(4 * uArg2 + *(uint32_t *)(this + 4)), v14);
    pBuf = uArg2;
    pBuf2 = &fld_43[v14];
    if ( uArg2 == 0 )
      goto LABEL_15;
    goto LABEL_14;
  }
  pBuf3 = (char *)memcpy_0(v10, fld_42, 4 * (v7 >> 2)) + 4 * (v7 >> 2);
  if ( uArg2 != fld_C )
    memset(pBuf3, 0, 4 * (uArg2 - fld_C));
  if ( fld_C != 0 )
  {
    pBuf = fld_C;
    pBuf2 = pMem;
LABEL_14:
    memset(pBuf2, 0, 4 * pBuf);
  }
LABEL_15:
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  result = uArg2 + *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 4) = pMem;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x407090 sub_407090
// ------------------------------------------------------------
int /*thiscall*/ sub_407090(int this, uint32_t *uArg2)
{
  int fld_10; // eax
  unsigned int fld_8; // eax
  unsigned int fld_102; // edi
  unsigned int v6; // ebx
  uint32_t *fld_4; // edi
  int result; // eax

  fld_10 = *(uint32_t *)(this + 16);
  if ( (((uint8_t)fld_10 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(fld_10 + 4) >> 2 )
    sub_406F40(this, 1u);
  fld_8 = *(uint32_t *)(this + 8);
  fld_102 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);
  v6 = fld_102 >> 2;
  if ( fld_8 <= fld_102 >> 2 )
    v6 -= fld_8;
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);
  fld_4 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (fld_102 & 3));
  if ( fld_4 != nullptr )
    *fld_4 = *uArg2;
  result = *(uint32_t *)(this + 16) + 1;
  *(uint32_t *)(this + 16) = result;
  return result;
}



// ------------------------------------------------------------
// 0x407110 sub_407110
// ------------------------------------------------------------
int /*cdecl*/ sub_407110(int nArg1, int nArg2, int nArg3)
{
  int nArg32; // esi
  int nArg12; // edi
  int result; // eax

  nArg32 = nArg3;
  pt.x = (int16_t)nArg3;
  nArg12 = nArg1;
  pt.y = SHIWORD(nArg3);
  if ( byte_89D27C != 0 )
  {
    result = sub_407090((int)&unk_89D280, &nArg1);
  }
  else
  {
    result = nArg1 - 513;
    switch ( nArg1 )
    {
      case 513:
        result = 1;
        dword_89D26C = 1;
        byte_89D274 = 1;
        break;
      case 514:
        dword_89D26C = 8;
        byte_89D274 = 0;
        break;
      case 516:
        dword_89D26C = 2;
        byte_89D275 = 1;
        break;
      case 517:
        dword_89D26C = 16;
        byte_89D275 = 0;
        break;
      default:
        break;
    }
  }
  if ( dword_89D278 != 0 )
    return (**(int (/*thiscall*/ ***)(int, int, int, int))dword_89D278)(dword_89D278, nArg12, nArg2, nArg32);
  return result;
}



// ------------------------------------------------------------
// 0x4071D0 sub_4071D0
// ------------------------------------------------------------
BOOL sub_4071D0()
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
  byte_89D27C = 0;
  if ( dword_89D290 != 0 )
  {
    dword_89D2882 = dword_89D288;
    dword_89D28C2 = dword_89D28C;
    while ( 1 )
    {
      v3 = dword_89D28C2 >> 2;
      v4 = dword_89D28C2 - 4 * (dword_89D28C2 >> 2);
      if ( dword_89D2882 <= v3 )
        v3 -= dword_89D2882;
      sub_407110(*(uint32_t *)(*(uint32_t *)(dword_89D284 + 4 * v3) + 4 * v4), 0, 0);
      if ( dword_89D290 == 0 )
        break;
      dword_89D2882 = dword_89D288;
      dword_89D28C2 = dword_89D28C + 1;
      if ( 4 * dword_89D288 <= (unsigned int)++dword_89D28C )
      {
        dword_89D28C2 = 0;
        dword_89D28C = 0;
      }
      if ( --dword_89D290 == 0 )
      {
        dword_89D28C = 0;
        break;
      }
    }
  }
  v6 = y;
  Point.x = x;
  Point.y = y;
  ClientToScreen(hWnd, &Point);
  result = SetCursorPos(Point.x, Point.y);
  pt.y = v6;
  pt.x = x;
  return result;
}



// ------------------------------------------------------------
// 0x4072B0 sub_4072B0
// ------------------------------------------------------------
int64_t sub_4072B0()
{
  memset(&byte_8A6A98, 0, 0x400u);
  memset(&byte_8A6698, 0, 0x400u);
  memset(&byte_8A6298, 0, 0x400u);
  byte_8A6E98 = 0;
  byte_8A6E99 = 0;
  byte_8A6E9B = 0;
  byte_8A6E9C = 0;
  dword_8A6EA0 = nullptr;
  dword_8A6EA4 = nullptr;
  byte_8A6E9A = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x407310 sub_407310
// ------------------------------------------------------------
int /*thiscall*/ sub_407310(uint8_t *this)
{
  if ( dword_8A6EA4 != nullptr )
    ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);
  memset(&byte_8A6A98, 0, 0x400u);
  memset(&byte_8A6698, 0, 0x400u);
  memset(&byte_8A6298, 0, 0x400u);
  byte_8A6E98 = 0;
  byte_8A6E99 = 0;
  byte_8A6E9B = 0;
  byte_8A6E9C = 0;
  dword_8A6EA0 = nullptr;
  dword_8A6EA4 = nullptr;
  byte_8A6E9A = 0;
  *(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x407390 sub_407390
// ------------------------------------------------------------
int /*thiscall*/ sub_407390(uint8_t *this, LONG uArg2, LONG uArg3)
{
  struct tagCOMPOSITIONFORM CompForm; // [esp+0h] [ebp-1Ch] BYREF

  if ( *(this + 4) == 0 )
    return -2147483647;
  CompForm.ptCurrentPos.x = uArg2;
  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);
  CompForm.dwStyle = 2;
  CompForm.ptCurrentPos.y = uArg3;
  ImmSetCompositionWindow(dword_8A6EA4, &CompForm);
  ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);
  return 1;
}



// ------------------------------------------------------------
// 0x407400 sub_407400
// ------------------------------------------------------------
BOOL sub_407400()
{
  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);
  ImmNotifyIME(dword_8A6EA4, 0x15u, 1u, 0);
  return ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);
}



// ------------------------------------------------------------
// 0x407430 sub_407430
// ------------------------------------------------------------
int sub_407430()
{
  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);
  ImmNotifyIME(dword_8A6EA4, 0x15u, 4u, 0);
  ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);
  memset(&byte_8A6698, 0, 0x400u);
  memset(&byte_8A6A98, 0, 0x400u);
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

  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);
  switch ( nArg1 )
  {
    case 3:
      sub_40BE20("\n\n ...<IMN_CHANGECANDIDATE>", v19);
      CandidateListA = ImmGetCandidateListA(dword_8A6EA4, 0, nullptr, 0);
      v10 = CandidateListA;
      if ( CandidateListA != 0 )
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
            memset(&unk_89D298, 0, 0x9000u);
            v21 = 0;
            if ( dword_8A6EB0 != 0 )
            {
              v11 = (char *)&unk_89D298;
              dwOffset = pMem->dwOffset;
              do
              {
                v13 = (char *)pMem + *dwOffset;
                v14 = v11;
                do
                {
                  v15 = *v13++;
                  *v14++ = v15;
                }
                while ( v15 != 0 );
                v16 = (*(int (/*fastcall*/ **)(int, char *, char *))(*(uint32_t *)dword_8A6EB8 + 16))(
                        dword_8A6EB8,
                        v14,
                        v11);
                dword_8A6EB02 = dword_8A6EB0;
                *((uint32_t *)v11 + 8) = v16;
                ++dwOffset;
                v11 += 36;
                ++v21;
              }
              while ( v21 < dword_8A6EB02 );
            }
            goto LABEL_22;
          }
          j__free(pMem);
          ImmNotifyIME(dword_8A6EA4, 0x16u, 0, dwValue);
        }
      }
      break;
    case 4:
      dword_8A6EB0 = 0;
      dword_77F400 = -1;
      memset(&unk_89D298, 0, 0x9000u);
      break;
    case 5:
      sub_40BE20("\n\n ...<IMN_OPENCANDIDATE>", v19);
      v2 = ImmGetCandidateListA(dword_8A6EA4, 0, nullptr, 0);
      v3 = v2;
      if ( v2 != 0 )
      {
        pMem = (struct tagCANDIDATELIST *)operator new(v2);
        ImmGetCandidateListA(dword_8A6EA4, 0, pMem, v3);
        dword_8A6EB0 = pMem->dwCount;
        dword_77F400 = pMem->dwSelection;
        dwValue = pMem->dwPageStart;
        dword_77F404 = pMem->dwPageSize;
        if ( (unsigned int)dword_8A6EB0 < 0x400 && dword_8A6EB8 != 0 )
        {
          memset(&unk_89D298, 0, 0x9000u);
          v20 = 0;
          if ( dword_8A6EB0 != 0 )
          {
            pBuf = (char *)&unk_89D298;
            v6 = pMem->dwOffset;
            do
            {
              strcpy(pBuf, (const char *)pMem + *v6);
              v7 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8A6EB8 + 16))(dword_8A6EB8, pBuf);
              dword_8A6EB03 = dword_8A6EB0;
              *((uint32_t *)pBuf + 8) = v7;
              ++v6;
              pBuf += 36;
              ++v20;
            }
            while ( v20 < dword_8A6EB03 );
          }
LABEL_22:
          j__free(pMem);
        }
      }
      break;
    default:
      break;
  }
  ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);
  return 1;
}


// ------------------------------------------------------------
// 0x4076E0 sub_4076E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4076E0(uint8_t *this, HWND nArg2)
{
  HIMC Context; // eax

  if ( *(this + 4) != 0 )
    return -2147483646;
  dword_8A6EA0 = nArg2;
  Context = ImmGetContext(nArg2);
  dword_8A6EA4 = Context;
  if ( Context == nullptr )
    return -2147483647;
  ImmReleaseContext(dword_8A6EA0, Context);
  *(this + 4) = 1;
  return 1;
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

  dword_796E502 = dword_796E50;
  dword_8A6EA4 = ImmGetContext(dword_8A6EA0);
  sub_40BE20("\n IIme::Composition--------------------", v7);
  if ( (uArg2 & 0x800) != 0 )
  {
    CompositionStringA = ImmGetCompositionStringA(dword_8A6EA4, 0x800u, nullptr, 0);
    v3 = CompositionStringA;
    if ( CompositionStringA < 0x400 )
    {
      if ( CompositionStringA == 0 )
      {
LABEL_6:
        byte_8A6A98[v3] = 0;
        sub_40BE20("\nGCS_RESULTSTR : <%s>", (char)byte_8A6A98);
        memset(byte_8A6698, 0, sizeof(byte_8A6698));
        byte_8A6E9B = 0;
        goto LABEL_7;
      }
    }
    else
    {
      v3 = 1023;
    }
    ImmGetCompositionStringA(dword_8A6EA4, 0x800u, byte_8A6A98, v3);
    goto LABEL_6;
  }
LABEL_7:
  if ( (uArg2 & 8) != 0 )
  {
    if ( byte_8A6EAC != 0 )
    {
      result = ImmGetCompositionStringA(dword_8A6EA4, 8u, nullptr, 0);
      v5 = result;
      if ( result >= 0x400 )
        return result;
      ImmGetCompositionStringA(dword_8A6EA4, 8u, byte_8A6698, result);
      byte_8A6698[v5] = 0;
      byte_8A6E9B = 1;
      sub_40BE20("\nGCS_COMPSTR : <%s>", (char)byte_8A6698);
    }
    else
    {
      sub_407430();
    }
  }
  if ( (uArg2 & 0x80u) != 0 )
  {
    memset(Buf, 0, sizeof(Buf));
    v6 = ImmGetCompositionStringA(dword_8A6EA4, 0x80u, nullptr, 0);
    if ( v6 >= 0x400 )
      v6 = 1023;
    ImmGetCompositionStringA(dword_8A6EA4, 8u, Buf, v6);
    Buf[v6] = 0;
    dword_8A6EA8 = strlen(Buf);
    sub_40BE20("\n GCS_CURSORPOS : <%s> <%d>", (char)Buf);
  }
  return ImmReleaseContext(dword_8A6EA0, dword_8A6EA4);
}



// ------------------------------------------------------------
// 0x407900 sub_407900
// ------------------------------------------------------------
int /*thiscall*/ sub_407900(uint8_t *this, unsigned int uArg2, unsigned int uArg3, int nArg4)
{
  if ( *(this + 4) == 0 )
    return -2147483647;
  if ( uArg2 > 0x10E )
  {
    if ( uArg2 == 271 )
    {
      sub_407390(this, -1000, -1000);
      byte_8A6E9B = 1;
      sub_407740(uArg3, nArg4);
    }
    else if ( uArg2 == 642 )
    {
      sub_407480(uArg3, nArg4);
      return 0;
    }
  }
  else
  {
    switch ( uArg2 )
    {
      case 0x10Eu:
        memset(byte_8A6698, 0, sizeof(byte_8A6698));
        byte_8A6E9C = 1;
        byte_8A6E9B = 0;
        return 0;
      case 0x100u:
        if ( uArg3 >= 0x23 && uArg3 <= 0x28 )
          goto LABEL_22;
        if ( uArg3 == 45 )
        {
          byte_8A6298 = 45;
          byte_8A6E99 = byte_8A6E99 == 0;
          byte_8A6E9A = 1;
          return 0;
        }
        if ( uArg3 == 46 || uArg3 == 190 )
        {
LABEL_22:
          if ( uArg3 != 190 )
          {
            byte_8A6298 = uArg3;
            byte_8A6E9A = 1;
            return 0;
          }
        }
        break;
      case 0x102u:
        if ( uArg3 != 9 )
        {
          if ( uArg3 == 13 )
          {
            byte_8A6E98 = 1;
            return 0;
          }
          if ( strlen(byte_8A6A98) == 0 && nArg4 != 1 )
          {
            byte_8A6A98[0] = uArg3;
            return 0;
          }
        }
        break;
      case 0x10Du:
        byte_8A6E9B = 1;
        sub_407390(this, -1000, -1000);
        memset(byte_8A6A98, 0, sizeof(byte_8A6A98));
        memset(&byte_8A6298, 0, 0x400u);
        memset(byte_8A6698, 0, sizeof(byte_8A6698));
        byte_8A6E9A = 0;
        return 0;
      default:
        break;
    }
  }
  return 0;
}



// ============================================================
// SECTION 0x407AE0 — 子系统注册容器族（树/链表基础设施，为 0x41 区等上层共用）
// ============================================================
// ------------------------------------------------------------
// 0x407AE0 sub_407AE0
// ------------------------------------------------------------
int /*thiscall*/ sub_407AE0(uint8_t *this, int nArg2)  // 【子系统注册容器族（树/链表基础设施，为 0x41 区等上层共用）】
{
  int result; // eax
  int v4; // edx

  if ( *(this + 4) != 0 )
    return -2147483646;
  v4 = *(uint32_t *)this;
  *((uint32_t *)this + 3) = nArg2;
  result = (*(int (/*thiscall*/ **)(uint8_t *))(v4 + 12))(this);
  if ( result >= 0 )
  {
    *(this + 4) = 1;
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x407B20 sub_407B20
// ------------------------------------------------------------
int /*thiscall*/ sub_407B20(uint32_t *this)
{
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 16))(this);
  *(this + 3) = 0;
  *((uint8_t *)this + 4) = 0;
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

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x407BD0 sub_407BD0
// ------------------------------------------------------------
char /*thiscall*/ sub_407BD0(int this)
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
    v4 = *fld_14;
    if ( *fld_14 != fld_14 )
    {
      do
      {
        v5 = (int (/*thiscall*/ ***)(uint32_t, int))v4[2];
        if ( v5 != nullptr )
          LOBYTE(fld_14) = (**v5)(v5, 1);
        v4[2] = 0;
        v6 = (uint32_t *)*v4;
        if ( v4 != *(uint32_t **)(pThis_10 + 4) )
        {
          *(uint32_t *)v4[1] = v6;
          *(uint32_t *)(*v4 + 4) = v4[1];
          j__free(v4);
          fld_14 = (void **)(*(uint32_t *)(pThis_10 + 8) - 1);
          *(uint32_t *)(pThis_10 + 8) = fld_14;
        }
        v4 = v6;
      }
      while ( v6 != *(uint32_t **)(this + 20) );
    }
  }
  return (char)fld_14;
}



// ------------------------------------------------------------
// 0x407C40 sub_407C40
// ------------------------------------------------------------
int /*thiscall*/ sub_407C40(uint8_t *this, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  int result; // eax
  int v7; // edx

  if ( *(this + 4) != 0 )
    return -2147483646;
  *((uint32_t *)this + 4) = nArg2;
  *((uint32_t *)this + 5) = nArg3;
  *((uint32_t *)this + 6) = nArg4;
  v7 = *(uint32_t *)this;
  *(this + 13) = pszArg5;
  result = (*(int (/*thiscall*/ **)(uint8_t *))(v7 + 56))(this);
  if ( result >= 0 )
  {
    *(this + 4) = 1;
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x407C90 sub_407C90
// ------------------------------------------------------------
int /*thiscall*/ sub_407C90(uint32_t *this)
{
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *((uint8_t *)this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x407CB0 sub_407CB0
// ------------------------------------------------------------
char /*thiscall*/ sub_407CB0(uint8_t *this, int pArg2)
{
  *(this + 12) = 1;
  if ( *(uint32_t *)(pArg2 + 24) < 0x10u )
    sub_40F2B0((LPCSTR)(pArg2 + 4), 0);
  else
    sub_40F2B0(*(LPCSTR *)(pArg2 + 4), 0);
  return 1;
}



// ------------------------------------------------------------
// 0x407CF0 sub_407CF0
// ------------------------------------------------------------
int /*thiscall*/ sub_407CF0(uint8_t *this)
{
  *(this + 12) = 0;
  *(this + 13) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = 255;
  sub_6569D0(this + 40);
  return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);
}



// ------------------------------------------------------------
// 0x407D20 sub_407D20
// ------------------------------------------------------------
int /*thiscall*/ sub_407D20(uint8_t *this, uint32_t *uArg2)
{
  if ( *(this + 4) == 0 )
    return -2147483647;
  if ( *uArg2 == 0 )
    return -2147483647;
  (**(void (/*thiscall*/ ***)(uint32_t, int))*uArg2)(*uArg2, 1);
  sub_407EA0(uArg2);
  *uArg2 = 0;
  return 1;
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

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x407E00 sub_407E00
// ------------------------------------------------------------
int /*thiscall*/ sub_407E00(int this)
{
  int pThis_28; // ebx
  void **fld_2C; // eax
  uint32_t *v5; // esi
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // edi

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  pThis_28 = this + 40;
  sub_408220(this + 40);
  fld_2C = *(void ***)(this + 44);
  v5 = *fld_2C;
  if ( *fld_2C != fld_2C )
  {
    do
    {
      v6 = (void (/*thiscall*/ ***)(uint32_t, int))v5[2];
      if ( v6 != nullptr )
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
  return 1;
}



// ------------------------------------------------------------
// 0x407E80 sub_407E80
// ------------------------------------------------------------
int /*thiscall*/ sub_407E80(char *this)
{
  sub_6569D0(this + 16);
  return (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 28))(this);
}



// ------------------------------------------------------------
// 0x407EA0 sub_407EA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_407EA0(uint32_t *this, uint32_t *uArg2)
{
  uint32_t **fld_e1; // ebx
  uint32_t *result; // eax
  uint32_t *v5; // edi

  fld_e1 = (uint32_t **)*(this + 1);
  result = *fld_e1;
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
    else
    {
      result = (uint32_t *)*result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x407EF0 sub_407EF0
// ------------------------------------------------------------
int /*thiscall*/ sub_407EF0(int this, uint32_t *uArg2)
{
  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( *uArg2 == 0 )
    return -2147483647;
  (**(void (/*thiscall*/ ***)(uint32_t, int))*uArg2)(*uArg2, 1);
  sub_407EA0((uint32_t *)(this + 16), uArg2);
  *uArg2 = 0;
  return 1;
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

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x407FD0 sub_407FD0
// ------------------------------------------------------------
int /*thiscall*/ sub_407FD0(int this)
{
  int pThis_10; // ebx
  void **fld_14; // eax
  uint32_t *v5; // esi
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // edi

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  pThis_10 = this + 16;
  sub_408220(this + 16);
  fld_14 = *(void ***)(this + 20);
  v5 = *fld_14;
  if ( *fld_14 != fld_14 )
  {
    do
    {
      v6 = (void (/*thiscall*/ ***)(uint32_t, int))v5[2];
      if ( v6 != nullptr )
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
  return 1;
}



// ------------------------------------------------------------
// 0x408060 sub_408060
// ------------------------------------------------------------
int /*thiscall*/ sub_408060(uint8_t *this)
{
  *(this + 12) = 1;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 100;
  sub_6569D0(this + 36);
  sub_6569D0(this + 48);
  return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 16))(this);
}



// ------------------------------------------------------------
// 0x4080A0 sub_4080A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4080A0(int this, uint32_t *uArg2)
{
  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( *uArg2 == 0 )
    return -2147483647;
  (**(void (/*thiscall*/ ***)(uint32_t, int))*uArg2)(*uArg2, 1);
  sub_407EA0((uint32_t *)(this + 36), uArg2);
  *uArg2 = 0;
  return 1;
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

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x408180 sub_408180
// ------------------------------------------------------------
int /*thiscall*/ sub_408180(uint32_t *this, int nArg2)
{
  int fld_e1; // edi
  int v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), nArg2);
  result = sub_4080F0(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  **(uint32_t **)(v4 + 4) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x4081C0 sub_4081C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4081C0(int this, char pszArg2)
{
  int fld_34; // edi
  uint32_t *pThis_30; // esi
  int v5; // ebx

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( *(uint8_t *)(this + 12) != 0 )
  {
    fld_34 = *(uint32_t *)(this + 52);
    pThis_30 = (uint32_t *)(this + 48);
    v5 = sub_40C0F0(fld_34, *(uint32_t *)(fld_34 + 4), &pszArg2);
    sub_4080F0(pThis_30, 1u);
    *(uint32_t *)(fld_34 + 4) = v5;
    **(uint32_t **)(v5 + 4) = v5;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x408220 sub_408220
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
      while ( 1 )
      {
        v3 = **(uint32_t **)(pArg1 + 4);
        v4 = v2;
        v2 = (uint32_t *)*v2;
        *(uint32_t *)v4[1] = v2;
        *(uint32_t *)v2[1] = v3;
        **(uint32_t **)(v3 + 4) = v4;
        v5 = *(uint32_t *)(v3 + 4);
        *(uint32_t *)(v3 + 4) = v2[1];
        v2[1] = v4[1];
        v4[1] = v5;
        if ( v2 == v1 )
          break;
        pArg1 = pArg12;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x408280 sub_408280
// ------------------------------------------------------------
int /*thiscall*/ sub_408280(int this)
{
  int pThis_24; // ebx
  void **fld_28; // eax
  uint32_t *v5; // esi
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // edi

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  pThis_24 = this + 36;
  sub_408220(this + 36);
  fld_28 = *(void ***)(this + 40);
  v5 = *fld_28;
  if ( *fld_28 != fld_28 )
  {
    do
    {
      v6 = (void (/*thiscall*/ ***)(uint32_t, int))v5[2];
      if ( v6 != nullptr )
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
  return 1;
}



// ------------------------------------------------------------
// 0x408300 sub_408300
// ------------------------------------------------------------
int /*thiscall*/ sub_408300(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = &off_6C1BE8;
  result = sub_40F3B0();
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x408370 sub_408370
// ------------------------------------------------------------
int /*thiscall*/ sub_408370(uint32_t *this, int nArg2)
{
  *(this + 16) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x4083A0 sub_4083A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4083A0(uint32_t *this, int nArg2)
{
  *(this + 17) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x408400 sub_408400
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408400(uint8_t *Block, char pszArg2)
{
  sub_408300(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x408430 sub_408430
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408430(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C1BE8;
  *((uint32_t *)this + 2) = nArg2;
  sub_40F360();
  *((uint32_t *)this + 30) = nArg3;
  *(uint32_t *)this = &off_6C1C98;
  *((uint32_t *)this + 31) = nArg4;
  sub_40FD50(this);
  return this;
}



// ------------------------------------------------------------
// 0x4084A0 sub_4084A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4084A0(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = &off_6C1C98;
  sub_40FF30();
  *(uint32_t *)this = &off_6C1BE8;
  result = sub_40F3B0(this);
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x408500 sub_408500
// ------------------------------------------------------------
int /*stdcall*/ sub_408500(int xRight, int yBottom)
{
  return sub_411240(xRight, yBottom, 21);
}



// ------------------------------------------------------------
// 0x408520 sub_408520
// ------------------------------------------------------------
int /*thiscall*/ sub_408520(void *this, int nArg2, int nArg3)
{
  return (*(int (/*stdcall*/ **)(int, int, int))(*(uint32_t *)this + 140))(nArg2, (int)this + 48, nArg3);
}



// ------------------------------------------------------------
// 0x408540 sub_408540
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408540(uint8_t *Block, char pszArg2)
{
  sub_4084A0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x408570 sub_408570
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408570(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_408430(this, nArg2, nArg3, nArg4);
  *(uint32_t *)this = &off_6C1D50;
  return this;
}



// ------------------------------------------------------------
// 0x4085A0 sub_4085A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4085A0(void *Block, char pszArg2)
{
  sub_4085D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4085D0 sub_4085D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4085D0(uint8_t *this)
{
  *(uint32_t *)this = &off_6C1D50;
  sub_40FF30();
  return sub_4084A0(this);
}



// ------------------------------------------------------------
// 0x408620 sub_408620
// ------------------------------------------------------------
int /*thiscall*/ sub_408620(uint8_t *this)
{
  *(uint32_t *)this = &off_6C1E08;
  sub_40FF30();
  return sub_4084A0(this);
}



// ------------------------------------------------------------
// 0x408670 sub_408670
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408670(uint8_t *Block, char pszArg2)
{
  sub_408620(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4086A0 sub_4086A0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4086A0(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_408430(this, nArg2, nArg3, nArg4);
  *(this + 136) = 0;
  *(uint32_t *)this = &off_6C1EC0;
  return this;
}



// ------------------------------------------------------------
// 0x4086D0 sub_4086D0
// ------------------------------------------------------------
int /*stdcall*/ sub_4086D0(int xRight, int yBottom)
{
  return sub_411240(xRight, yBottom, 26);
}



// ------------------------------------------------------------
// 0x4086F0 sub_4086F0
// ------------------------------------------------------------
void */*thiscall*/ sub_4086F0(void *Block, char pszArg2)
{
  sub_408720();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x408720 sub_408720
// ------------------------------------------------------------
int /*thiscall*/ sub_408720(uint8_t *this)
{
  *(uint32_t *)this = &off_6C1EC0;
  sub_40FF30();
  return sub_408620(this);
}



// ------------------------------------------------------------
// 0x408770 sub_408770
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408770(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_408430(this, nArg2, nArg3, nArg4);
  *(this + 136) = 0;
  *(uint32_t *)this = &off_6C1F78;
  return this;
}



// ------------------------------------------------------------
// 0x4087A0 sub_4087A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4087A0(uint8_t *this)
{
  *(uint32_t *)this = &off_6C1F78;
  sub_40FF30();
  return sub_408620(this);
}



// ------------------------------------------------------------
// 0x4087F0 sub_4087F0
// ------------------------------------------------------------
int /*stdcall*/ sub_4087F0(int xRight, int yBottom)
{
  return sub_411240(xRight, yBottom, 25);
}



// ------------------------------------------------------------
// 0x408810 sub_408810
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408810(uint8_t *Block, char pszArg2)
{
  sub_4087A0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x408840 sub_408840
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408840(uint8_t *this, int nArg2)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C1BE8;
  *((uint32_t *)this + 2) = nArg2;
  sub_40F360();
  *(uint32_t *)this = &off_6C2030;
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4088A0 sub_4088A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4088A0(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = &off_6C2030;
  sub_40F420();
  *(uint32_t *)this = &off_6C1BE8;
  result = sub_40F3B0(this);
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x408900 sub_408900
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408900(uint8_t *Block, char pszArg2)
{
  sub_4088A0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x408930 sub_408930
// ------------------------------------------------------------
int /*thiscall*/ sub_408930(uint8_t *this)
{
  *(uint32_t *)this = &off_6C20E0;
  sub_40F420();
  return sub_4088A0(this);
}



// ------------------------------------------------------------
// 0x408980 sub_408980
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408980(uint8_t *Block, char pszArg2)
{
  sub_408930(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4089B0 sub_4089B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4089B0(int this, int nArg2, int nArg3)
{
  sub_408840((uint8_t *)this, nArg2);
  *(uint32_t *)(this + 108) = nArg3;
  *(uint32_t *)this = &off_6C2190;
  sub_413660(this);
  return this;
}



// ------------------------------------------------------------
// 0x408A10 sub_408A10
// ------------------------------------------------------------
void */*thiscall*/ sub_408A10(void *Block, char pszArg2)
{
  sub_408A40();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x408A40 sub_408A40
// ------------------------------------------------------------
int /*thiscall*/ sub_408A40(uint8_t *this)
{
  *(uint32_t *)this = &off_6C2190;
  sub_413800();
  return sub_408930(this);
}



// ------------------------------------------------------------
// 0x408A90 sub_408A90
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_408A90(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_408430(this, nArg2, nArg3, nArg4);
  *(this + 136) = 0;
  *(uint32_t *)this = &off_6C2240;
  return this;
}



// ------------------------------------------------------------
// 0x408AC0 sub_408AC0
// ------------------------------------------------------------
int /*thiscall*/ sub_408AC0(int this)
{
  *(uint32_t *)(this + 8) = 3;
  *(uint8_t *)(this + 52) = 0;
  *(uint32_t *)(this + 8248) = 0;
  *(uint32_t *)(this + 8252) = 0;
  *(uint32_t *)(this + 8256) = 0;
  *(uint32_t *)(this + 8264) = 0;
  *(uint32_t *)(this + 8272) = 0;
  *(uint8_t *)(this + 8268) = 0;
  *(uint32_t *)(this + 8328) = -1;
  *(uint32_t *)(this + 8332) = 0;
  *(uint32_t *)(this + 8260) = 0;
  *(uint32_t *)(this + 184040) = 0;
  *(uint32_t *)(this + 184048) = 0;
  *(uint32_t *)(this + 184052) = 0;
  *(uint32_t *)(this + 184056) = 0;
  memset((void *)(this + 8336), 0, 0x2A378u);
  memset((void *)(this + 181256), 0, 0xD4u);
  memset((void *)(this + 181468), 0, 0x600u);
  *(uint32_t *)(this + 184024) = 0;
  *(uint32_t *)(this + 184028) = 0;
  *(uint32_t *)(this + 184032) = 0;
  *(uint32_t *)(this + 184036) = 0;
  memset((void *)(this + 8276), 0, 0x34u);
  memset((void *)(this + 56), 0, 0x400u);
  memset((void *)(this + 1080), 0, 0x1C00u);
  memset((void *)(this + 183004), 0, 0x3FCu);
  return 0;
}



// ============================================================
// SECTION 0x408B90 — GDI 位图工具 + NEOPLE_WEB 内嵌浏览器窗口抓屏（BitBlt 采样）
// ============================================================
// ------------------------------------------------------------
// 0x408B90 sub_408B90
// ------------------------------------------------------------
int /*thiscall*/ sub_408B90(uint32_t *this)  // 【GDI 位图工具 + NEOPLE_WEB 内嵌浏览器窗口抓屏（BitBlt 采样）】
{
  int v2; // edi

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 76))(this);
  if ( v2 >= 0 )
    return 1;
  sub_407C90(this);
  return v2;
}



// ------------------------------------------------------------
// 0x408BC0 sub_408BC0
// ------------------------------------------------------------
int /*thiscall*/ sub_408BC0(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);
}



// ------------------------------------------------------------
// 0x408BD0 sub_408BD0
// ------------------------------------------------------------
int /*thiscall*/ sub_408BD0(uint32_t **this, int pArg2, uint32_t *uArg3)
{
  int result; // eax

  result = (*(int (/*stdcall*/ **)(uint32_t, int, uint32_t *))(**(this + 2063) + 200))(*(this + 2063), pArg2, uArg3);
  *(this + pArg2 + 14) = uArg3;
  return result;
}



// ------------------------------------------------------------
// 0x408C00 sub_408C00
// ------------------------------------------------------------
int /*thiscall*/ sub_408C00(uint32_t *this, int pArg2)
{
  int fld_e2063; // eax
  int result; // eax
  int v5; // [esp+8h] [ebp-4h] BYREF

  fld_e2063 = *(this + 2063);
  v5 = 0;
  if ( (*(int (/*stdcall*/ **)(int, int, int *))(*(uint32_t *)fld_e2063 + 204))(fld_e2063, pArg2, &v5) < 0 )
    return *(this + pArg2 + 14);
  result = v5;
  *(this + pArg2 + 14) = v5;
  return result;
}



// ------------------------------------------------------------
// 0x408C50 sub_408C50
// ------------------------------------------------------------
int /*thiscall*/ sub_408C50(uint32_t **this, int pArg2, int pArg3, uint32_t *uArg4)
{
  (*(void (/*stdcall*/ **)(uint32_t, int, int, uint32_t *))(**(this + 2063) + 252))(*(this + 2063), pArg2, pArg3, uArg4);
  *(this + 256 * pArg2 + pArg3 + 270) = uArg4;
  return pArg3;
}



// ------------------------------------------------------------
// 0x408C90 sub_408C90
// ------------------------------------------------------------
int /*thiscall*/ sub_408C90(uint32_t *this, int nArg2, int nArg3)
{
  int fld_e2063; // eax
  int v5; // esi
  int result; // eax
  int v7; // [esp+Ch] [ebp-4h] BYREF

  fld_e2063 = *(this + 2063);
  v7 = 0;
  v5 = nArg3 + (nArg2 << 8);
  if ( (*(int (/*stdcall*/ **)(int, int, int, int *))(*(uint32_t *)fld_e2063 + 248))(fld_e2063, nArg2, nArg3, &v7) < 0 )
    return *(this + v5 + 270);
  result = v7;
  *(this + v5 + 270) = v7;
  return result;
}



// ------------------------------------------------------------
// 0x408CF0 sub_408CF0
// ------------------------------------------------------------
int /*usercall*/ sub_408CF0@<eax>(uint32_t *pArg1@<esi>, HANDLE h)
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

  memset(pArg1, 0, 0x2Cu);
  result = GetObjectA(h, 24, pv);
  if ( result != 0 )
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
        else
          v5 = 16;
      }
      else
      {
        v5 = 8;
      }
    }
    else
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
    *pArg1 = 40;
    pArg1[1] = v6;
    pArg1[2] = v7;
    pArg1[5] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x408DB0 sub_408DB0
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
    return 1;
  if ( *(uint32_t *)(pArg1 + 184048) == nArg4 )
    return 1;
  if ( nArg4 == 1 )
  {
    v6 = *(int **)(pArg1 + 8252);
    v7 = *v6;
    v8 = 640;
    v13 = 480;
    (*(void (/*stdcall*/ **)(int *, uint8_t *, int, int))(v7 + 28))(v6, v12, nArg2, nArg3);
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
    if ( *(uint32_t *)(pArg1 + 184052) != 0 )
    {
      pMem = operator new(2 * *(uint32_t *)(pArg1 + 16) * *(uint32_t *)(pArg1 + 20));
      *(uint32_t *)(pArg1 + 184048) = 1;
      *(uint32_t *)(pArg1 + 184056) = pMem;
      return 1;
    }
    else
    {
      return 0x80000000;
    }
  }
  else
  {
    j_j__free(*(void **)(pArg1 + 184056));
    pObj = *(uint32_t *)(pArg1 + 184052);
    *(uint32_t *)(pArg1 + 184056) = 0;
    if ( pObj != 0 )
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 8))(pObj);
    *(uint32_t *)(pArg1 + 184052) = 0;
    *(uint32_t *)(pArg1 + 184048) = nArg4;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x408EE0 sub_408EE0
// ------------------------------------------------------------
int /*thiscall*/ sub_408EE0(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e2065)(uint32_t, int); // ecx
  int fld_e2064; // eax
  int fld_e2063; // eax
  int fld_e2062; // eax
  int fld_e46013; // eax

  if ( *(this + 2062) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 64))(this, 0);
    fld_e2065 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2065);
    if ( fld_e2065 != nullptr )
      (**fld_e2065)(fld_e2065, 1);
    fld_e2064 = *(this + 2064);
    *(this + 2065) = 0;
    if ( fld_e2064 != 0 )
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e2064 + 8))(fld_e2064);
    fld_e2063 = *(this + 2063);
    *(this + 2064) = 0;
    if ( fld_e2063 != 0 )
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e2063 + 8))(fld_e2063);
    fld_e2062 = *(this + 2062);
    *(this + 2063) = 0;
    if ( fld_e2062 != 0 )
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e2062 + 8))(fld_e2062);
    fld_e46013 = *(this + 46013);
    *(this + 2062) = 0;
    if ( fld_e46013 != 0 )
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e46013 + 8))(fld_e46013);
    *(this + 46013) = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x408F70 sub_408F70
// ------------------------------------------------------------
int /*thiscall*/ sub_408F70(uint32_t **this)
{
  (*(void (/*stdcall*/ **)(uint32_t))(**(this + 2064) + 32))(*(this + 2064));
  return sub_413EE0((DWORD)(this + 2069), 0);  // 【窗口尺寸调整族（GetWindowLong/GetSystemMetrics/Adj…】
}



// ------------------------------------------------------------
// 0x408FA0 sub_408FA0
// ------------------------------------------------------------
int /*thiscall*/ sub_408FA0(int this, int nArg2)
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
  (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 8256) + 32))(*(uint32_t *)(this + 8256));
  if ( *(uint8_t *)(this + 13) != 0 )
  {
    *(uint32_t *)(this + 8284) = *(uint32_t *)(pThis_2090 + 1080);
    *(uint32_t *)(this + 8296) = 1;
  }
  else
  {
    fld_24 = *(uint32_t *)(this + 36);
    *(uint32_t *)(this + 8284) = *(uint32_t *)(pThis_6418 + 8);
    *(uint32_t *)(this + 8296) = 2;
    WindowLongA = GetWindowLongA(*(HWND *)(fld_24 + 16), -16);
    fld_242 = *(uint32_t *)(this + 36);
    *(uint32_t *)(this + 184040) = WindowLongA;
    *(uint32_t *)(this + 184044) = GetWindowLongA(*(HWND *)(fld_242 + 16), -20);
  }
  *(uint8_t *)(this + 13) = nArg2 == 1;
  *(uint32_t *)(this + 8304) = nArg2 == 0;
  return sub_414090(this + 8276);
}



// ------------------------------------------------------------
// 0x409080 sub_409080
// ------------------------------------------------------------
int /*thiscall*/ sub_409080(void *this, HWND hWnd)
{
  HWND Window; // eax
  HWND v4; // edi

  Window = GetWindow(hWnd, 3u);
  v4 = Window;
  if ( Window != nullptr )
  {
    if ( (GetWindowLongA(Window, -16) & 0x10000000) != 0 )
      (*(void (/*thiscall*/ **)(void *, HWND))(*(uint32_t *)this + 72))(this, v4);
    (*(void (/*thiscall*/ **)(void *, HWND))(*(uint32_t *)this + 68))(this, v4);
  }
  return 1;
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
  dword_796E502 = dword_796E50;
  v5 = *(uint32_t *)(pArg1 + 184052);
  pArg13 = pArg1;
  if ( v5 == 0 )
    return 0x80000000;
  GetWindowRect(hWnd, &Rect);
  if ( Rect.right != Rect.left && Rect.bottom != Rect.top )
  {
    GetWindowRect(*(HWND *)(*(uint32_t *)(pArg12 + 36) + 16), &rcSrc1);
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
      if ( v36 == 1 )
      {
        SendMessageA(hWnd, 0x317u, (WPARAM)CompatibleDC, 62);
      }
      else
      {
        RedrawWindow(hWnd, nullptr, nullptr, 0x785u);
        BitBlt(CompatibleDC, 0, 0, nWidth, nHeight, WindowDC, rcDst.left, rcDst.top, 0xCC0020u);
      }
      sub_408CF0(&bmi, hbm);
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
          v29 = (int16_t)v10;
          while ( 1 )
          {
            v13 = v23 + 2 * top * (v21[0] / 2);
            v14 = v27 + 2 * v29 * (rc.top - top + nHeight - 1);
            v15 = left;
            if ( left < right )
            {
              do
              {
                *(uint16_t *)(v13 + 2 * v15) = *(uint16_t *)(v14 + 2 * (v15 - left)) & 0x1F
                                          | (2 * (*(uint16_t *)(v14 + 2 * (v15 - left)) & 0xFFE0));
                right = rc.right;
                left = rc.left;
                ++v15;
              }
              while ( v15 < rc.right );
            }
            if ( ++nWidth >= rc.bottom )
              break;
            top = nWidth;
          }
          CompatibleDC = v24;
          pArg12 = pArg13;
        }
        (*(void (/*cdecl*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg12 + 184052) + 68))(*(uint32_t *)(pArg12 + 184052), 0);
      }
      ReleaseDC(hWnd, hDC);
      SelectObject(CompatibleDC, h);
      DeleteObject(hbm);
      DeleteDC(CompatibleDC);
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
  return 1;
}


// ------------------------------------------------------------
// 0x4094C0 sub_4094C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4094C0(char *this, int nArg2, int dy)
{
  char fld_e4; // al
  int pThis_80F; // eax
  int v7; // eax
  char v8; // al
  char v9; // al
  int pThis_80F2; // edi
  struct tagRECT rc; // [esp+4h] [ebp-20h] BYREF
  struct tagRECT rcDst; // [esp+14h] [ebp-10h] BYREF

  fld_e4 = *(this + 4);
  if ( fld_e4 == 0 )
    return -2147483647;
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
    return 1;
  }
  if ( *((uint32_t *)this + 46012) == 1 )
  {
    sub_404F40(fld_e4, 6u);
    (*(void (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 2063) + 136))(*((uint32_t *)this + 2063));
    (*(void (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 2064) + 16))(*((uint32_t *)this + 2064));
    (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 68))(this, *(uint32_t *)(*((uint32_t *)this + 9) + 16));
    (*(void (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 2064) + 28))(*((uint32_t *)this + 2064));
    pThis_80F = (*(int (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 2063) + 140))(*((uint32_t *)this + 2063));
    sub_404F80(pThis_80F, 6u, 1);
  }
  v7 = sub_405060(0, 1, 0);
  sub_404F80(v7, 2u, 1);
  sub_404F40(v8, 2u);
  sub_404F40(v9, 3u);
  pThis_80F2 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**((uint32_t **)this + 2063) + 60))(
          *((uint32_t *)this + 2063),
          0,
          0,
          0,
          0);
  sub_404F80(pThis_80F2, 3u, 1);
  if ( pThis_80F2 >= 0 )
    return 1;
  if ( pThis_80F2 == -2005530520 )
    return (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 84))(this) >= 0 ? 1 : -2147483645;
  else
    return 0x80000000;
}



// ------------------------------------------------------------
// 0x409660 sub_409660
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

  dword_796E502 = dword_796E50;
  *(uint32_t *)(this + 32) = uArg2;
  if ( uArg2 >= 0xFF )
    *(uint32_t *)(this + 32) = 255;
  fld_20 = (double)*(unsigned int *)(this + 32) * 0.0039215689;
  v4 = 0;
  pThis_2C6DC = (uint16_t *)(this + 181980);
  do
  {
    v10 = *pThis_2C6DC;
    v8[v4] = (uint8_t)(uint64_t)((double)*(pThis_2C6DC - 256) * fld_20);
    v6 = (uint64_t)((double)v10 * fld_20);
    v11 = pThis_2C6DC[256];
    v8[v4 + 256] = (uint8_t)v6;
    v8[v4++ + 512] = (uint8_t)(uint64_t)((double)v11 * fld_20);
    ++pThis_2C6DC;
  }
  while ( v4 < 256 );
  return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint16_t *))(**(uint32_t **)(this + 8252) + 72))(
           *(uint32_t *)(this + 8252),
           0,
           v8);
}



// ------------------------------------------------------------
// 0x409750 sub_409750
// ------------------------------------------------------------
int /*thiscall*/ sub_409750(int this, char pszArg2)
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
  *(uint32_t *)(this + 8304) = pszArg2 == 0;
  if ( pszArg2 != 0 )
  {
    fld_24 = *(uint32_t *)(this + 36);
    *(uint32_t *)(this + 8284) = *(uint32_t *)(v6 + 8);
    *(uint32_t *)(this + 8296) = 2;
    WindowLongA = GetWindowLongA(*(HWND *)(fld_24 + 16), -16);
    fld_242 = *(uint32_t *)(this + 36);
    *(uint32_t *)(this + 184040) = WindowLongA;
    *(uint32_t *)(this + 184044) = GetWindowLongA(*(HWND *)(fld_242 + 16), -20);
  }
  else
  {
    *(uint32_t *)(this + 8284) = *(uint32_t *)(pThis_2090 + 1080);
    *(uint32_t *)(this + 8296) = 1;
  }
  result = (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 8256) + 32))(*(uint32_t *)(this + 8256));
  if ( result >= 0 )
  {
    result = (*(int (/*stdcall*/ **)(uint32_t, int))(**(uint32_t **)(this + 8252) + 56))(
               *(uint32_t *)(this + 8252),
               this + 8276);
    if ( result >= 0 )
      return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x409830 CompareFunction
// ------------------------------------------------------------
int /*cdecl*/ CompareFunction(uint32_t *pArg1, uint32_t *pArg2)
{
  int v2; // eax
  int v3; // ecx
  unsigned int v5; // eax
  unsigned int v6; // ecx

  v2 = pArg1[3];
  v3 = pArg2[3];
  if ( v2 > v3 )
    return -1;
  if ( v2 < v3 )
    return 1;
  if ( *pArg1 < *pArg2 )
    return -1;
  if ( *pArg1 > *pArg2 )
    return 1;
  v5 = pArg1[1];
  v6 = pArg2[1];
  if ( v6 > v5 )
    return -1;
  return v6 < v5;
}



// ------------------------------------------------------------
// 0x409870 sub_409870
// ------------------------------------------------------------
char /*thiscall*/ sub_409870(int this, int nArg2, int nArg3, int nArg4, uint32_t *uArg5)
{
  if ( *(uint32_t *)(this + 24) <= 0x10u
    && *(uint32_t *)(this + 8272) == 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         80) >= 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         80) >= 0 )
  {
    *uArg5 = 80;
    return 1;
  }
  if ( *(uint32_t *)(this + 24) <= 0xFu
    && *(uint32_t *)(this + 8272) <= 1u
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         73) >= 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         73) >= 0 )
  {
    *uArg5 = 73;
    return 1;
  }
  if ( *(uint32_t *)(this + 24) > 0x18u )
    goto LABEL_29;
  if ( *(uint32_t *)(this + 8272) == 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         77) >= 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         77) >= 0 )
  {
    *uArg5 = 77;
    return 1;
  }
  if ( *(uint32_t *)(this + 24) > 0x18u )
    goto LABEL_29;
  if ( *(uint32_t *)(this + 8272) <= 8u
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         75) >= 0
    && (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         75) >= 0 )
  {
    *uArg5 = 75;
    return 1;
  }
  if ( *(uint32_t *)(this + 24) > 0x18u
    || *(uint32_t *)(this + 8272) > 4u
    || (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         2,
         1,
         79) < 0
    || (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(
         *(uint32_t *)(this + 8248),
         nArg2,
         nArg3,
         nArg4,
         nArg4,
         79) < 0 )
  {
LABEL_29:
    if ( *(uint32_t *)(this + 24) > 0x20u
      || *(uint32_t *)(this + 8272) != 0
      || (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 40))(
           *(uint32_t *)(this + 8248),
           nArg2,
           nArg3,
           nArg4,
           2,
           1,
           71) < 0
      || (*(int (/*stdcall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)(this + 8248) + 48))(
           *(uint32_t *)(this + 8248),
           nArg2,
           nArg3,
           nArg4,
           nArg4,
           71) < 0 )
    {
      return 0;
    }
    else
    {
      *uArg5 = 71;
      return 1;
    }
  }
  else
  {
    *uArg5 = 79;
    return 1;
  }
}


// ------------------------------------------------------------
// 0x409AA0 sub_409AA0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_409AA0(uint8_t *Block, char pszArg2)
{
  sub_409AD0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x409AD0 sub_409AD0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_409AD0(uint8_t *this)
{
  return sub_4087A0(this);
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

  dword_796E502 = dword_796E50;
  v2 = *(int **)(pArg1 + 8248);
  *(uint32_t *)ArgList = pArg1;
  v3 = *v2;
  v67[0] = &off_6C2404;
  v67[1] = &off_6C2400;
  v66[0] = 1;
  v66[1] = 2;
  v78 = 0;
  v77 = 0;
  v80 = 0;
  v79 = 0;
  v76 = 0;
  if ( (*(int (/*stdcall*/ **)(int *))(v3 + 16))(v2) == 0 )
    goto LABEL_72;
  do
  {
    v4 = *(int **)ArgList;
    v5 = v76;
    v6 = **(uint32_t **)(*(uint32_t *)ArgList + 8248);
    v56 = *(uint32_t *)(*(uint32_t *)ArgList + 8248);
    v73 = 17292 * *(uint32_t *)(*(uint32_t *)ArgList + 8332) + *(uint32_t *)ArgList + 8336;
    v7 = (uint32_t *)v73;
    (*(void (/*stdcall*/ **)(int, int, uint32_t, int, uint32_t *))(v6 + 20))(v56, v76, 0, v73, uArg2);
    (*(void (/*stdcall*/ **)(int, int, uint32_t *))(*(uint32_t *)v4[2062] + 32))(v4[2062], v5, v7 + 267);
    v8 = v76;
    v9 = 0;
    v7[271] = 0;
    v7[4322] = 0;
    v10 = *(uint32_t *)v4[2062];
    v59 = v4[2062];
    v72 = 0;
    v11 = (*(int (/*stdcall*/ **)(int, int))(v10 + 24))(v59, v8);
    v12 = v7[270];
    v68 = v11;
    v65[0] = v12;
    v74 = 1;
    i = 0;
    if ( v11 != 0 )
    {
      v13 = v64;
      do
      {
        (*(void (/*stdcall*/ **)(int, int, unsigned int, unsigned int *))(*(uint32_t *)v4[2062] + 28))(
          v4[2062],
          v76,
          i,
          &v69);
        if ( v69 >= v4[4] && v70 >= v4[5] )
        {
          v14 = v71;
          v15 = 0;
          if ( v9 != 0 )
          {
            v16 = v64;
            while ( 1 )
            {
              if ( *(v16 - 1) == v69 && *v16 == v70 )
              {
                v14 = v71;
                if ( v16[2] == v71 )
                  break;
              }
              ++v15;
              v16 += 4;
              if ( v15 >= v9 )
              {
                v14 = v71;
                break;
              }
            }
          }
          if ( v15 == v9 )
          {
            v17 = v70;
            *(v13 - 1) = v69;
            v18 = 0;
            *v13 = v17;
            v19 = v74;
            v13[2] = v14;
            v13[1] = 0;
            ++v9;
            v13 += 4;
            if ( v19 != 0 )
            {
              do
              {
                if ( v14 == v65[v18] )
                  break;
                ++v18;
              }
              while ( v18 < v19 );
            }
            if ( v18 == v19 )
            {
              v65[v19] = v14;
              v74 = v19 + 1;
            }
          }
        }
        ++i;
      }
      while ( i < v68 );
      v72 = v9;
    }
    qsort(&Base, v9, 0x10u, CompareFunction);
    for ( i = 0; i < 8; i += 4 )
    {
      v20 = i;
      v21 = 3240 * *(uint32_t *)(v73 + 1084) + v73 + 1088;
      v22 = *(int **)ArgList;
      v62 = 3240 * *(uint32_t *)(v73 + 1084) + v73 + 1092;
      v23 = v76;
      v60 = *(uint32_t *)((char *)v66 + i);
      *(uint32_t *)v21 = v60;
      (*(void (/*stdcall*/ **)(int, int, int, int))(*(uint32_t *)v22[2062] + 52))(v22[2062], v23, v60, v62);
      v24 = *(uint32_t *)((char *)v67 + v20);
      v25 = 0;
      *(uint32_t *)(v21 + 216) = v24;
      v26 = v74 == 0;
      *(uint32_t *)(v21 + 224) = 0;
      *(uint32_t *)(v21 + 3228) = 0;
      *(uint8_t *)(v21 + 220) = 0;
      *(uint8_t *)(v21 + 3232) = 0;
      *(uint32_t *)(v21 + 3236) = 0;
      if ( !v26 )
      {
        while ( 1 )
        {
          v27 = v65[v25];
          v28 = **(uint32_t **)(*(uint32_t *)ArgList + 8248);
          v58 = *(uint32_t *)v21;
          v57 = v76;
          v55 = *(uint32_t *)(*(uint32_t *)ArgList + 8248);
          v82[v25] = 0;
          v64[v25 + 399] = 0;
          if ( (*(int (/*stdcall*/ **)(int, int, int, int, int, uint32_t))(v28 + 36))(v55, v57, v58, v27, v27, 0) >= 0 )
            break;
LABEL_45:
          if ( ++v25 >= v74 )
            goto LABEL_46;
        }
        if ( *(uint32_t *)v21 == 1 )
        {
          v26 = (*(uint32_t *)(v21 + 16) & 0x80000) == 0;
          v78 = 1;
          if ( !v26 )
          {
            v77 = 1;
            if ( v25 == 0 )
              v80 = 1;
          }
        }
        v29 = *(uint32_t *)(v21 + 32);
        if ( (v29 & 0x10000) != 0 )
        {
          if ( (v29 & 0x100000) != 0 )
          {
            v30 = *(int **)ArgList;
            v31 = **(uint32_t **)ArgList;
            v64[v25 + 419] = 80;
            if ( (*(int (/*thiscall*/ **)(int *, int, int, int))(v31 + 88))(v30, v21 + 4, 80, v27) >= 0 )
              v82[v25] = 1;
          }
          if ( v82[v25] != 0 )
            goto LABEL_42;
          v32 = *(int **)ArgList;
          v33 = **(uint32_t **)ArgList;
          v64[v25 + 419] = 64;
          if ( (*(int (/*thiscall*/ **)(int *, int, int, int))(v33 + 88))(v32, v21 + 4, 64, v27) >= 0 )
            v82[v25] = 1;
          if ( v82[v25] != 0 )
          {
LABEL_42:
            if ( *(uint8_t *)(*(uint32_t *)ArgList + 8268) != 0
              && (uint8_t)sub_409870(v76, *(uint32_t *)v21, v27, &v64[v25 + 399]) == 0 )
            {
              v82[v25] = 0;
            }
            goto LABEL_45;
          }
          v34 = *(int **)ArgList;
          v35 = **(uint32_t **)ArgList;
          v64[v25 + 419] = 128;
          if ( (*(int (/*thiscall*/ **)(int *, int, int, int))(v35 + 88))(v34, v21 + 4, 128, v27) >= 0 )
            v82[v25] = 1;
        }
        if ( v82[v25] == 0 )
        {
          v36 = *(int **)ArgList;
          v37 = **(uint32_t **)ArgList;
          v64[v25 + 419] = 32;
          if ( (*(int (/*thiscall*/ **)(int *, int, int, int))(v37 + 88))(v36, v21 + 4, 32, v27) >= 0 )
            v82[v25] = 1;
          if ( v82[v25] == 0 )
            goto LABEL_45;
        }
        goto LABEL_42;
      }
LABEL_46:
      if ( v72 != 0 )
      {
        v38 = 0;
        for ( j = v72; j != 0; --j )
        {
          for ( k = 0; k < v74; ++k )
          {
            if ( v64[v38 + 2] == v65[k] && v82[k] == 1 )
            {
              *(uint32_t *)(v21 + 20 * *(uint32_t *)(v21 + 224) + 228) = v64[v38 - 1];
              *(uint32_t *)(v21 + 20 * *(uint32_t *)(v21 + 224) + 232) = v64[v38];
              *(uint32_t *)(v21 + 20 * *(uint32_t *)(v21 + 224) + 236) = v64[v38 + 2];
              *(uint32_t *)(v21 + 20 * (*(uint32_t *)(v21 + 224) + 12)) = v64[k + 419];
              *(uint32_t *)(v21 + 20 * *(uint32_t *)(v21 + 224) + 244) = v64[k + 399];
              v26 = *(uint32_t *)v21 == 1;
              ++*(uint32_t *)(v21 + 224);
              if ( v26 )
                v79 = 1;
            }
          }
          v38 += 4;
        }
      }
      v41 = *(uint32_t *)(v21 + 224);
      v42 = 0;
      if ( v41 != 0 )
      {
        v43 = *(int **)ArgList;
        v44 = (int *)(v21 + 236);
        do
        {
          if ( *(v44 - 2) == v43[4] && *(v44 - 1) == v43[5] )
          {
            *(uint32_t *)(v21 + 3228) = v42;
            v45 = *v44;
            if ( *v44 == 23 || v45 == 24 || v45 == 25 )
              break;
          }
          ++v42;
          v44 += 5;
        }
        while ( v42 < *(uint32_t *)(v21 + 224) );
      }
      if ( v82[0] != 0 && (*(uint32_t *)(v21 + 16) & 0x80000) != 0 )
      {
        *(uint8_t *)(v21 + 220) = 1;
        *(uint8_t *)(v21 + 3232) = 1;
      }
      if ( v41 != 0 )
        ++*(uint32_t *)(v73 + 1084);
    }
    v46 = *(int **)ArgList;
    if ( *(uint32_t *)(v73 + 1084) != 0 )
      ++*(uint32_t *)(*(uint32_t *)ArgList + 8332);
    v47 = (uint32_t *)v46[2062];
    v48 = *v47;
    uArg2 = v47;
    v49 = ++v76;
  }
  while ( v49 < (*(int (**)(void))(v48 + 16))() );
LABEL_72:
  v50 = *(int **)ArgList;
  if ( *(uint32_t *)(*(uint32_t *)ArgList + 8332) == 0 )
    return 0x80000000;
  v51 = 0;
  for ( m = (uint32_t *)(*(uint32_t *)ArgList + 9420); *m == 0; m += 4323 )
  {
    if ( (unsigned int)++v51 >= *(uint32_t *)(*(uint32_t *)ArgList + 8332) )
      return 0x80000000;
  }
  v54 = *(uint32_t *)ArgList + 17292 * v51;
  *(uint32_t *)(v54 + 25624) = 0;
  v50[2082] = v51;
  if ( *(uint32_t *)(v54 + 9424) == 2 )
  {
    if ( v78 == 0 )
    {
      off_77F3F8((char)v50, "D3DAPPERR_NOHARDWAREDEVICE, MSGWARN_SWITCHEDTOREF");
      return 1;
    }
    if ( v79 == 0 )
    {
      off_77F3F8((char)v50, "D3DAPPERR_HALNOTCOMPATIBLE, MSGWARN_SWITCHEDTOREF");
      return 1;
    }
    if ( v77 == 0 )
    {
      off_77F3F8((char)v50, "D3DAPPERR_NOWINDOWEDHAL, MSGWARN_SWITCHEDTOREF");
      return 1;
    }
    if ( v80 == 0 )
    {
      off_77F3F8((char)v50, "D3DAPPERR_NODESKTOPHAL, MSGWARN_SWITCHEDTOREF");
      return 1;
    }
    off_77F3F8((char)v50, "D3DAPPERR_NOHALTHISMODE, MSGWARN_SWITCHEDTOREF");
  }
  return 1;
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

  pD3D = Direct3DCreate8(220);
  *((uint32_t *)this + 2062) = pD3D;
  if ( pD3D == 0 )
    return 0x80000000;
  SetRect((LPRECT)(this + 184024), 0, 0, *((uint32_t *)this + 4), *((uint32_t *)this + 5));
  sub_409AE0(this);  // 【D3D8 应用初始化：设备/模式枚举（qsort）、D3DAPPERR 错误分类、R…】
  pThis_822 = 17292 * *((uint32_t *)this + 2082);
  v5 = (int)(this + pThis_822 + 8336);
  v6 = 3240 * *(uint32_t *)(this + pThis_822 + 25624);
  v7 = *(uint32_t *)(v6 + v5 + 4316);
  v8 = v6 + v5 + 1088;
  v9 = (uint32_t *)(v8 + 20 * v7 + 228);
  Block = (uint32_t *)v5;
  if ( v9 == nullptr )
    return 0x80000000;
  *((uint32_t *)this + 2077) = (uint8_t)*(this + 8268);
  *((uint32_t *)this + 2078) = v9[4];
  pThis_9 = *((uint32_t *)this + 9);
  *((uint32_t *)this + 2073) = *(uint32_t *)(v8 + 3236);
  *((uint32_t *)this + 2075) = *(uint32_t *)(pThis_9 + 16);
  fld_e13 = *(this + 13);
  *((uint32_t *)this + 2076) = fld_e13 == 0;
  if ( fld_e13 != 0 )
  {
    *((uint32_t *)this + 2072) = 1;
    *((uint32_t *)this + 2069) = *v9;
    *((uint32_t *)this + 2070) = v9[1];
    *((uint32_t *)this + 2071) = v9[2];
    *((uint32_t *)this + 2074) = 2;
  }
  else
  {
    pThis_4 = *((uint32_t *)this + 4);
    pThis_5 = *((uint32_t *)this + 5);
    *((uint32_t *)this + 2072) = 1;
    *((uint32_t *)this + 2069) = pThis_4;
    *((uint32_t *)this + 2070) = pThis_5;
    *((uint32_t *)this + 2071) = *(uint32_t *)(v5 + 1080);
    *((uint32_t *)this + 2074) = 1;
  }
  v14 = 0;
  while ( 1 )
  {
    result = (*(int (/*stdcall*/ **)(uint32_t, int, int, uint32_t, int, char *, char *))(**((uint32_t **)this + 2062) + 60))(
               *((uint32_t *)this + 2062),
               v14,
               1,
               *(uint32_t *)(*((uint32_t *)this + 9) + 16),
               32,
               this + 8276,
               this + 8252);
    if ( result >= 0 )
      break;
    if ( ++v14 >= 2 )
      return result;
  }
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 22, 1);
  (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 28))(this, 137, 0);
  (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 28))(this, 7, (uint8_t)*(this + 8268));
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 27, 1);
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 15, 1);
  (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 28))(this, 24, 0);
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 25, 5);
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 19, 5);
  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 28))(this, 20, 6);
  (*(void (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 36))(this, 0, 1, 4);
  (*(void (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 36))(this, 0, 13, 3);
  (*(void (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 36))(this, 0, 14, 3);
  (*(void (/*stdcall*/ **)(uint32_t, char *))(**((uint32_t **)this + 2063) + 28))(*((uint32_t *)this + 2063), this + 181256);
  v15 = 0;
  pThis_2CADC = this + 183004;
  do
  {
    if ( (*(int (/*stdcall*/ **)(uint32_t, int, int, uint32_t, int, int, int))(**((uint32_t **)this + 2062) + 40))(
           *((uint32_t *)this + 2062),
           v14,
           1,
           Block[270],
           1,
           3,
           v15) >= 0 )
      *pThis_2CADC = 1;
    ++v15;
    ++pThis_2CADC;
  }
  while ( v15 < 255 );
  result = sub_67BA58(*((uint32_t *)this + 2063), this + 8256);
  if ( result >= 0 )
  {
    if ( operator new(0x88u) != nullptr )
      v16 = (uint32_t *)sub_4143A0(7, this);  // 【对象销毁/容器壳】
    else
      v16 = nullptr;
    if ( v16 != nullptr )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v16 + 176))(v16, *((uint32_t *)this + 2063));
      v16[33] = *((uint32_t *)this + 9);
      pThis_80F = *((uint32_t *)this + 2063);
      *((uint32_t *)this + 2065) = v16;
      (*(void (/*stdcall*/ **)(int, char *))(*(uint32_t *)pThis_80F + 76))(pThis_80F, this + 181468);
      if ( *((uint16_t *)this + 90989) == 255 )
      {
        v18 = 0;
        pThis_2C6DC = this + 181980;
        do
        {
          LOBYTE(v20) = 0;
          HIBYTE(v20) = v18;
          pThis_2C6DC += 2;
          v21 = v18 | v20;
          *((uint16_t *)pThis_2C6DC - 257) = v21;
          *((uint16_t *)pThis_2C6DC - 1) = v21;
          *((uint16_t *)pThis_2C6DC + 255) = v21;
          ++v18;
        }
        while ( v18 < 256 );
      }
      if ( *(this + 13) != 0 )
        SetWindowPos(*(HWND *)(*((uint32_t *)this + 9) + 16), HWND_MESSAGE|0x2, 0, 0, 0, 0, 3u);
      return 1;
    }
    else
    {
      return -2147483640;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x40A4E0 sub_40A4E0
// ------------------------------------------------------------
int /*thiscall*/ sub_40A4E0(uint32_t *this, int nArg2)
{
  int fld_e1; // edi
  int v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), nArg2);
  result = sub_407D70(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  **(uint32_t **)(v4 + 4) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x40A520 sub_40A520
// ------------------------------------------------------------
int /*thiscall*/ sub_40A520(int this, int nArg2, uint32_t *Block)
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

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  switch ( nArg2 )
  {
    case 1:
    case 8:
    case 16:
      if ( *(uint32_t *)(this + 183088) != 0 )
      {
        pMem = operator new(0x88u);
        if ( pMem != nullptr )
          fld_203C = sub_408570(pMem, nArg2, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));
        else
          fld_203C = nullptr;
      }
      else
      {
        pMem2 = operator new(0x8Cu);
        if ( pMem2 != nullptr )
          fld_203C = sub_4086A0(pMem2, nArg2, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));
        else
          fld_203C = nullptr;
        fld_203C[136] = 1;
      }
      if ( fld_203C != nullptr )
        goto LABEL_14;
      return -2147483640;
    case 3:
      pMem3 = operator new(0x70u);
      if ( pMem3 != nullptr )
        fld_203C = (uint8_t *)sub_4089B0((int)pMem3, nArg2, *(uint32_t *)(this + 8252));
      else
        fld_203C = nullptr;
      goto LABEL_22;
    case 7:
      *Block = *(uint32_t *)(this + 8260);
      return 1;
    case 12:
    case 13:
      pMem4 = operator new(0x8Cu);
      if ( pMem4 != nullptr )
        fld_203C2 = sub_408A90(pMem4, 14, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));
      else
        fld_203C2 = nullptr;
      *Block = fld_203C2;
      if ( fld_203C2 != nullptr )
        goto LABEL_29;
      goto LABEL_23;
    case 14:
      pMem5 = operator new(0x8Cu);
      if ( pMem5 != nullptr )
        fld_203C = sub_408770(pMem5, nArg2, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));
      else
        fld_203C = nullptr;
      goto LABEL_22;
    case 15:
      pMem6 = operator new(0x8Cu);
      if ( pMem6 != nullptr )
        fld_203C = sub_4086A0(pMem6, nArg2, *(uint32_t *)(this + 8252), *(uint32_t *)(this + 8256));
      else
        fld_203C = nullptr;
LABEL_22:
      if ( fld_203C != nullptr )
      {
LABEL_14:
        *Block = fld_203C;
        sub_40A4E0((uint32_t *)(this + 40), (int)Block);
        result = 1;
      }
      else
      {
LABEL_23:
        result = -2147483640;
      }
      break;
    case 18:
    case 19:
    case 20:
LABEL_29:
      sub_40A4E0((uint32_t *)(this + 40), (int)Block);
      result = 1;
      break;
    default:
      *Block = 0;
      result = -2147483639;
      break;
  }
  return result;
}



// ============================================================
// SECTION 0x40A800 — DirectSound8 声音子系统（DirectSoundCreate8 / 协作级 / 缓冲管理）
// ============================================================
// ------------------------------------------------------------
// 0x40A800 sub_40A800
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40A800(uint8_t *this, void *pArg2, int nArg3)  // 【DirectSound8 声音子系统（DirectSoundCreate8 / 协作…】
{
  *(this + 4) = 0;
  *((uint32_t *)this + 2) = pArg2;
  *(uint32_t *)this = &off_6C2408;
  *(this + 28) = 0;
  *((uint32_t *)this + 6) = &off_6C38F4;
  sub_402A50((uint32_t *)this + 6);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  *((uint32_t *)this + 11) = nArg3;
  sub_4144F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x40A870 sub_40A870
// ------------------------------------------------------------
char /*thiscall*/ sub_40A870(uint32_t *this)
{
  *this = &off_6C2408;
  sub_414510();
  *(this + 6) = &off_6C38F4;
  sub_402A60((int)(this + 6));
  *(this + 6) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 28) = 0;
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x40A8E0 sub_40A8E0
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_40A8E0(uint32_t *uArg1)
{
  *uArg1 = 0;
  return 0x80000000;
}



// ------------------------------------------------------------
// 0x40A900 sub_40A900
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40A900(uint32_t *Block, char pszArg2)
{
  sub_40A870(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40A930 sub_40A930
// ------------------------------------------------------------
int /*thiscall*/ sub_40A930(int this, void *pArg2, int nArg3, int nArg4)
{
  sub_40A800((uint8_t *)this, pArg2, nArg3);  // 【DirectSound8 声音子系统（DirectSoundCreate8 / 协作…】
  *(uint32_t *)this = &off_6C243C;
  *(uint32_t *)(this + 64) = nArg4;
  sub_414560(this);
  return this;
}



// ------------------------------------------------------------
// 0x40A990 sub_40A990
// ------------------------------------------------------------
void */*thiscall*/ sub_40A990(void *Block, char pszArg2)
{
  sub_40A9C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40A9C0 sub_40A9C0
// ------------------------------------------------------------
char /*thiscall*/ sub_40A9C0(uint32_t *this)
{
  *this = &off_6C243C;
  sub_4145E0();
  return sub_40A870(this);
}



// ------------------------------------------------------------
// 0x40AA10 sub_40AA10
// ------------------------------------------------------------
int /*thiscall*/ sub_40AA10(uint32_t *this)
{
  *(this + 2) = 1;
  *(this + 15) = 0;
  *(this + 16) = 0;
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
    return -2147483646;
  *(this + 4) = Block;
  *(this + 5) = a3;
  *(this + 6) = a4;
  if ( DirectSoundCreate8(nullptr, v5, nullptr) < 0 )
    return -2147483616;
  if ( (*v5)->lpVtbl->SetCooperativeLevel(*v5, (HWND)(*(this + 8))[4].lpVtbl, 1) < 0 )
    return -2147483631;
  v7 = operator new(0x44u);
  if ( v7 != nullptr )
    v8 = sub_40A930((int)v7, nullptr, (int)this, (int)*v5);
  else
    v8 = 0;
  *(this + 16) = (LPDIRECTSOUND8)v8;
  v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  if ( v9 >= 0 )
  {
    v10 = sub_414850(0, 0, 129);
    if ( v10 >= 0 )
    {
      return 1;
    }
    else
    {
      sub_408050(this);
      return v10;
    }
  }
  else
  {
    sub_408050(this);
    return v9;
  }
}



// ------------------------------------------------------------
// 0x40AB70 sub_40AB70
// ------------------------------------------------------------
int /*thiscall*/ sub_40AB70(LPDIRECTSOUND8 *this)
{
  int result; // eax

  result = sub_40AA20(this, *(this + 4), *(this + 5), *(this + 6));
  if ( result >= 0 )
    return 1;
  return result;
}



// ------------------------------------------------------------
// 0x40AB90 sub_40AB90
// ------------------------------------------------------------
int /*thiscall*/ sub_40AB90(int *this)
{
  void (/*thiscall*/ ***fld_e16)(uint32_t, int); // ecx
  int result; // eax

  fld_e16 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  if ( fld_e16 != nullptr )
    (**fld_e16)(fld_e16, 1);
  result = *(this + 15);
  *(this + 16) = 0;
  if ( result != 0 )
    result = (*(int (/*stdcall*/ **)(int))(*(uint32_t *)result + 8))(result);
  *(this + 15) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40ABC0 sub_40ABC0
// ------------------------------------------------------------
int /*thiscall*/ sub_40ABC0(int *this, int nArg2, int *pDwArg3)
{
  void *pMem; // eax
  int fld_e15; // eax
  int fld_e10; // edi
  int v8; // ebx

  if ( nArg2 != 0 )
  {
    *pDwArg3 = 0;
    return -2147483639;
  }
  else
  {
    pMem = operator new(0x44u);
    if ( pMem != nullptr )
      fld_e15 = sub_40A930((int)pMem, nullptr, (int)this, *(this + 15));
    else
      fld_e15 = 0;
    *pDwArg3 = fld_e15;
    if ( fld_e15 != 0 )
    {
      fld_e10 = *(this + 10);
      v8 = sub_40C0F0(fld_e10, *(uint32_t *)(fld_e10 + 4), pDwArg3);
      sub_4080F0(this + 9, 1u);
      *(uint32_t *)(fld_e10 + 4) = v8;
      **(uint32_t **)(v8 + 4) = v8;
      return 1;
    }
    else
    {
      return -2147483640;
    }
  }
}



// ------------------------------------------------------------
// 0x40ACA0 sub_40ACA0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40ACA0(uint8_t *this, void *pArg2, int nArg3)
{
  sub_40A800(this, pArg2, nArg3);  // 【DirectSound8 声音子系统（DirectSoundCreate8 / 协作…】
  *(uint32_t *)this = &off_6C2470;
  sub_414D40(this);
  return this;
}



// ------------------------------------------------------------
// 0x40AD00 sub_40AD00
// ------------------------------------------------------------
char /*thiscall*/ sub_40AD00(uint32_t *this)
{
  *this = &off_6C2470;
  sub_414E00();
  return sub_40A870(this);
}



// ------------------------------------------------------------
// 0x40AD50 sub_40AD50
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_40AD50(uint32_t *this)
{
  return *(this + 4) / 0x64u + 100;
}



// ------------------------------------------------------------
// 0x40AD70 sub_40AD70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40AD70(uint32_t *Block, char pszArg2)
{
  sub_40AD00(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40ADA0 sub_40ADA0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40ADA0(uint8_t *this, void *pArg2, int nArg3)
{
  sub_40ACA0(this, pArg2, nArg3);
  *(uint32_t *)this = &off_6C24A4;
  sub_414D40(this);
  return this;
}



// ------------------------------------------------------------
// 0x40AE00 sub_40AE00
// ------------------------------------------------------------
void */*thiscall*/ sub_40AE00(void *Block, char pszArg2)
{
  sub_40AE30();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40AE30 sub_40AE30
// ------------------------------------------------------------
char /*thiscall*/ sub_40AE30(uint32_t *this)
{
  *this = &off_6C24A4;
  sub_414E00();
  return sub_40AD00(this);
}



// ------------------------------------------------------------
// 0x40AE90 sub_40AE90
// ------------------------------------------------------------
int /*thiscall*/ sub_40AE90(uint32_t *this, int nArg2, uint32_t *Block)
{
  uint32_t *Block2; // edi
  uint8_t *pMem2; // eax
  uint8_t *v6; // eax
  uint8_t *pMem; // eax

  if ( nArg2 >= 0 )
  {
    if ( nArg2 <= 3 )
    {
      Block2 = Block;
      *Block = 0;
      pMem = operator new(0x48u);
      if ( pMem != nullptr )
        v6 = sub_40ACA0(pMem, (void *)nArg2, (int)this);
      else
        v6 = nullptr;
      goto LABEL_9;
    }
    if ( nArg2 == 5 )
    {
      Block2 = Block;
      *Block = 0;
      pMem2 = operator new(0x48u);
      if ( pMem2 != nullptr )
        v6 = sub_40ADA0(pMem2, (void *)5, (int)this);
      else
        v6 = nullptr;
LABEL_9:
      if ( v6 == nullptr )
        return -2147483640;
      *Block2 = v6;
      sub_408180(this + 9, (int)Block2);
      return 1;
    }
  }
  *Block = 0;
  return -2147483639;
}



// ------------------------------------------------------------
// 0x40AF90 sub_40AF90
// ------------------------------------------------------------
char /*thiscall*/ sub_40AF90(uint8_t *this, int nArg2)
{
  if ( *(this + 12) != 0 )
    return *(this + *((uint32_t *)this + nArg2 + 196) + 269);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x40AFC0 sub_40AFC0
// ------------------------------------------------------------
bool /*thiscall*/ sub_40AFC0(uint8_t *this, int nArg2)
{
  return *(this + 12) != 0 && *(this + *((uint32_t *)this + nArg2 + 196) + 269) == 0;
}



// ------------------------------------------------------------
// 0x40B000 sub_40B000
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B000(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C24D8;
  *((uint32_t *)this + 2) = nArg2;
  sub_415190();
  *((uint32_t *)this + 773) = nArg4;
  *(uint32_t *)this = &off_6C2510;
  *((uint32_t *)this + 774) = nArg3;
  sub_4157E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x40B080 sub_40B080
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B080(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C24D8;
  *((uint32_t *)this + 2) = nArg2;
  sub_415190();
  *((uint32_t *)this + 841) = nArg4;
  *(uint32_t *)this = &off_6C2548;
  *((uint32_t *)this + 842) = nArg3;
  sub_4157E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x40B100 sub_40B100
// ------------------------------------------------------------
int /*thiscall*/ sub_40B100(uint32_t *this)
{
  return *(this + 773);
}



// ------------------------------------------------------------
// 0x40B110 sub_40B110
// ------------------------------------------------------------
int /*thiscall*/ sub_40B110(uint32_t *this)
{
  return *(this + 774);
}



// ------------------------------------------------------------
// 0x40B120 sub_40B120
// ------------------------------------------------------------
int /*thiscall*/ sub_40B120(uint32_t *this)
{
  return *(this + 775);
}



// ------------------------------------------------------------
// 0x40B130 sub_40B130
// ------------------------------------------------------------
void /*thiscall*/ sub_40B130(uint32_t *this)
{
  *(this + 7) = 0;
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
// 0x40B170 sub_40B170
// ------------------------------------------------------------
int /*thiscall*/ sub_40B170(int *this)
{
  int result; // eax

  result = *(this + 7);
  if ( result != 0 )
    result = (*(int (/*stdcall*/ **)(int))(*(uint32_t *)result + 8))(result);
  *(this + 7) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40B190 sub_40B190
// ------------------------------------------------------------
void /*thiscall*/ sub_40B190(Concurrency::details::TaskStack *this)
{
  *(uint32_t *)this = &off_6C24D8;
  Concurrency::details::TaskStack::ResetOverflow(this);
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
}



// ------------------------------------------------------------
// 0x40B1E0 sub_40B1E0
// ------------------------------------------------------------
Concurrency::details::TaskStack */*thiscall*/ sub_40B1E0(Concurrency::details::TaskStack *Block, char pszArg2)
{
  sub_40B190(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40B210 sub_40B210
// ------------------------------------------------------------
int /*thiscall*/ sub_40B210(int this, void *Block, uint32_t *uArg3)
{
  uint32_t *uArg32; // ecx
  uint8_t *pMem; // eax
  uint8_t *fld_C; // eax
  uint8_t *pMem2; // eax
  int fld_14; // edi
  int v10; // ebx

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( Block != nullptr )
  {
    if ( Block != (void *)1 )
    {
      if ( Block != (void *)2 )
        return -2147483639;
      uArg32 = uArg3;
      *uArg3 = 0;
      goto LABEL_16;
    }
    pMem = operator new(0xD2Cu);
    if ( pMem != nullptr )
      fld_C = sub_40B080(pMem, 1, *(uint32_t *)(this + 12), *(uint32_t *)(this + 28));
    else
      fld_C = nullptr;
  }
  else
  {
    pMem2 = operator new(0xC1Cu);
    if ( pMem2 != nullptr )
      fld_C = sub_40B000(pMem2, 0, *(uint32_t *)(this + 12), *(uint32_t *)(this + 28));
    else
      fld_C = nullptr;
  }
  if ( fld_C == nullptr )
    return -2147483640;
  uArg32 = uArg3;
  *uArg3 = fld_C;
LABEL_16:
  fld_14 = *(uint32_t *)(this + 20);
  v10 = sub_40C0F0(fld_14, *(uint32_t *)(fld_14 + 4), uArg32);
  sub_407F40((uint32_t *)(this + 16), 1u);
  *(uint32_t *)(fld_14 + 4) = v10;
  **(uint32_t **)(v10 + 4) = v10;
  return 1;
}



// ------------------------------------------------------------
// 0x40B350 sub_40B350
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B350(uint8_t *this, int nArg2, int nArg3)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C24D8;
  *((uint32_t *)this + 2) = nArg2;
  sub_415190();
  *((uint32_t *)this + 772) = nArg3;
  *(uint32_t *)this = &off_6C2580;
  return this;
}



// ------------------------------------------------------------
// 0x40B3B0 sub_40B3B0
// ------------------------------------------------------------
void */*thiscall*/ sub_40B3B0(void *Block, char pszArg2)
{
  sub_40B3E0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40B3E0 sub_40B3E0
// ------------------------------------------------------------
void /*thiscall*/ sub_40B3E0(Concurrency::details::TaskStack *this)
{
  *(uint32_t *)this = &off_6C24D8;
  Concurrency::details::TaskStack::ResetOverflow(this);
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
}



// ------------------------------------------------------------
// 0x40B430 sub_40B430
// ------------------------------------------------------------
int /*thiscall*/ sub_40B430(int this, void *Block, uint32_t *uArg3)
{
  uint32_t *uArg32; // ecx
  uint8_t *pMem; // eax
  uint8_t *fld_C; // eax
  int fld_14; // edi
  int v9; // ebx

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( Block != nullptr )
  {
    if ( Block != (void *)1 && Block != (void *)2 )
      return -2147483639;
    uArg32 = uArg3;
    *uArg3 = 0;
  }
  else
  {
    pMem = operator new(0xC14u);
    if ( pMem != nullptr )
      fld_C = sub_40B350(pMem, 0, *(uint32_t *)(this + 12));
    else
      fld_C = nullptr;
    if ( fld_C == nullptr )
      return -2147483640;
    uArg32 = uArg3;
    *uArg3 = fld_C;
  }
  fld_14 = *(uint32_t *)(this + 20);
  v9 = sub_40C0F0(fld_14, *(uint32_t *)(fld_14 + 4), uArg32);
  sub_407F40((uint32_t *)(this + 16), 1u);
  *(uint32_t *)(fld_14 + 4) = v9;
  **(uint32_t **)(v9 + 4) = v9;
  return 1;
}



// ------------------------------------------------------------
// 0x40B530 sub_40B530
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B530(uint8_t *this, int nArg2, int nArg3)
{
  *(this + 4) = 0;
  *((uint32_t *)this + 3) = nArg3;
  *(uint32_t *)this = &off_6C25B8;
  *((uint32_t *)this + 2) = nArg2;
  sub_4163E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x40B590 sub_40B590
// ------------------------------------------------------------
int /*thiscall*/ sub_40B590(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = &off_6C25B8;
  result = sub_416420();
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40B620 sub_40B620
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B620(uint8_t *Block, char pszArg2)
{
  sub_40B590(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40B650 sub_40B650
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_40B650(uint8_t *this, int nArg2, int nArg3)
{
  sub_40B530(this, nArg2, nArg3);
  *(uint32_t *)this = &off_6C25EC;
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x40B6B0 sub_40B6B0
// ------------------------------------------------------------
void */*thiscall*/ sub_40B6B0(void *Block, char pszArg2)
{
  sub_40B6E0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40B6E0 sub_40B6E0
// ------------------------------------------------------------
int /*thiscall*/ sub_40B6E0(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = &off_6C25EC;
  ((void (*)(void))sub_416420)();
  *(uint32_t *)this = &off_6C25B8;
  result = sub_416420(this);
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40B740 sub_40B740
// ------------------------------------------------------------
int /*thiscall*/ sub_40B740(int this, int nArg2, void *pArg3)
{
  sub_40B530((uint8_t *)this, nArg2, (int)pArg3);
  *(uint32_t *)this = &off_6C2620;
  *(uint8_t *)(this + 84) = 0;
  *(uint32_t *)(this + 80) = &off_6C38F4;
  sub_402A50((uint32_t *)(this + 80));  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  sub_416E70(this);
  return this;
}



// ------------------------------------------------------------
// 0x40B7B0 sub_40B7B0
// ------------------------------------------------------------
int /*thiscall*/ sub_40B7B0(uint32_t *this)
{
  int result; // eax

  *this = &off_6C2620;
  sub_416420(this);
  *(this + 20) = &off_6C38F4;
  sub_402A60((int)(this + 20));
  *(this + 20) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 84) = 0;
  *this = &off_6C25B8;
  result = sub_416420(this);
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40B840 sub_40B840
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40B840(uint32_t *Block, char pszArg2)
{
  sub_40B7B0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40B870 sub_40B870
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40B870(uint32_t *this, int nArg2, void *pArg3)
{
  sub_40B740((int)this, nArg2, pArg3);
  *this = &off_6C2654;
  sub_416E70(this);
  return this;
}



// ------------------------------------------------------------
// 0x40B8D0 sub_40B8D0
// ------------------------------------------------------------
void */*thiscall*/ sub_40B8D0(void *Block, char pszArg2)
{
  sub_40B900();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40B900 sub_40B900
// ------------------------------------------------------------
int /*thiscall*/ sub_40B900(uint32_t *this)
{
  *this = &off_6C2654;
  sub_416420(this);
  return sub_40B7B0(this);
}



// ------------------------------------------------------------
// 0x40B950 sub_40B950
// ------------------------------------------------------------
int /*thiscall*/ sub_40B950(uint32_t *this, int nArg2)
{
  int fld_e1; // edi
  int v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), nArg2);
  result = sub_407B40(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  **(uint32_t **)(v4 + 4) = v4;
  return result;
}



// ============================================================
// SECTION 0x40B990 — 文本测量（GetTextExtentPoint32）/ GDI 文本渲染 / 容器工具
// ============================================================
// ------------------------------------------------------------
// 0x40B990 sub_40B990
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

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  switch ( nArg2 )
  {
    case 1:
      fld_C = *(uint32_t *)(*(uint32_t *)(this + 12) + 8);
      if ( fld_C == 1 )
        goto LABEL_14;
      if ( fld_C != 3 )
        goto LABEL_23;
      pMem = operator new(0x84u);
      if ( pMem != nullptr )
        fld_1C = sub_40B870(pMem, nArg2, (void *)this);
      else
        fld_1C = nullptr;
      goto LABEL_20;
    case 2:
      goto LABEL_23;
    case 3:
      fld_C2 = *(uint32_t *)(*(uint32_t *)(this + 12) + 8);
      if ( fld_C2 == 1 )
        goto LABEL_14;
      if ( fld_C2 != 3 )
        goto LABEL_23;
      pMem2 = operator new(0xA0u);
      if ( pMem2 != nullptr )
        fld_1C = (void *)sub_40D510(pMem2, *(uint32_t *)(*(uint32_t *)(this + 28) + 16), nArg2, this);
      else
        fld_1C = nullptr;
      goto LABEL_20;
    case 4:
      fld_C3 = *(uint32_t *)(*(uint32_t *)(this + 12) + 8);
      if ( fld_C3 == 1 )
      {
LABEL_14:
        pMem3 = operator new(0x10u);
        if ( pMem3 != nullptr )
          fld_1C = sub_40B650(pMem3, nArg2, this);
        else
          fld_1C = nullptr;
      }
      else
      {
        if ( fld_C3 != 3 )
          goto LABEL_23;
        if ( operator new(0x20104u) != nullptr )
          fld_1C = (void *)sub_4185B0(*(HWND *)(*(uint32_t *)(this + 28) + 16), nArg2, this);
        else
          fld_1C = nullptr;
      }
LABEL_20:
      if ( fld_1C == nullptr )
        return -2147483640;
      *Block = fld_1C;
LABEL_23:
      sub_40B950((uint32_t *)(this + 16), (int)Block);
      result = 1;
      break;
    default:
      *Block = 0;
      return -2147483639;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40BB70 sub_40BB70
// ------------------------------------------------------------
LONG /*thiscall*/ sub_40BB70(HDC *this, LPCSTR lpString)
{
  int v4; // eax
  struct tagSIZE psizl; // [esp+8h] [ebp-8h] BYREF

  if ( lpString == nullptr )
    return 0;
  v4 = lstrlenA(lpString);
  GetTextExtentPoint32A(*(this + 10), lpString, v4, &psizl);
  return psizl.cx;
}



// ------------------------------------------------------------
// 0x40BBB0 sub_40BBB0
// ------------------------------------------------------------
int /*thiscall*/ sub_40BBB0(HDC *this, LPCSTR lpString, LONG uArg3)
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

  dword_796E502 = dword_796E50;
  if ( lpString == nullptr )
    return -1;
  v6 = lstrlenA(lpString);
  GetTextExtentPoint32A(*(this + 10), lpString, v6, &psizl);
  if ( uArg3 >= psizl.cx )
    return -1;
  v7 = 0;
  memset(String, 0, sizeof(String));
  lpStringa = (LPCSTR)strlen(lpString);
  while ( v7 < (int)lpStringa )
  {
    v8 = lpString[v7];
    v9 = v7;
    String[v7] = v8;
    String[v7 + 1] = 0;
    if ( v8 < 0
      && (v8 == -127
       || v8 == -126
       || v8 == -125
       || v8 == -124
       || v8 == -121
       || v8 == -120
       || v8 == -119
       || v8 == -118
       || v8 == -117
       || v8 == -116
       || v8 == -115
       || v8 == -114
       || v8 == -113
       || v8 == -112
       || v8 == -111
       || v8 == -110
       || v8 == -109
       || v8 == -108
       || v8 == -107
       || v8 == -106
       || v8 == -105
       || v8 == -104
       || v8 == -103
       || v8 == -102
       || v8 == -101
       || v8 == -100
       || v8 == -99
       || v8 == -98
       || v8 == -97
       || v8 == -32
       || v8 == -31
       || v8 == -30
       || v8 == -29
       || v8 == -28
       || v8 == -27
       || v8 == -26
       || v8 == -25
       || v8 == -24
       || v8 == -23
       || v8 == -22
       || v8 == -19
       || v8 == -18
       || v8 == -6
       || v8 == -5
       || v8 == -4) )
    {
      String[v7 + 1] = lpString[v7 + 1];
      String[v7++ + 2] = 0;
    }
    ++v7;
    v10 = lstrlenA(String);
    GetTextExtentPoint32A(*(this + 10), String, v10, &psizl);
    if ( uArg3 <= psizl.cx )
      return v9 + 1;
  }
  return -1;
}



// ------------------------------------------------------------
// 0x40BDD0 sub_40BDD0
// ------------------------------------------------------------
int /*thiscall*/ sub_40BDD0(uint32_t *this)
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
    if ( result < 0 )
      break;
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*i + 20))(*i);
    sub_411240(512, 512, 25);
    if ( ++v2 >= 4 )
      return 1;
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
int /*usercall*/ sub_40BE20@<eax>(DWORD uArg1@<ecx>, char *Format, ...)
{
  int result; // eax
  HANDLE StdHandle; // eax
  DWORD nLen; // [esp-Ch] [ebp-10h]
  DWORD NumberOfCharsWritten; // [esp+0h] [ebp-4h] BYREF
  va_list va; // [esp+10h] [ebp+Ch] BYREF

  va_start(va, Format);
  NumberOfCharsWritten = uArg1;
  result = _access("_DEBUG", 0);
  if ( result == 0 )
  {
    memset(byte_8A6EC8, 0, sizeof(byte_8A6EC8));
    vsprintf(byte_8A6EC8, Format, va);
    nLen = strlen(byte_8A6EC8);
    NumberOfCharsWritten = 0;
    StdHandle = GetStdHandle(0xFFFFFFF5);
    return WriteConsoleA(StdHandle, byte_8A6EC8, nLen, &NumberOfCharsWritten, nullptr);
  }
  return result;
}



// ------------------------------------------------------------
// 0x40BEA0 sub_40BEA0
// ------------------------------------------------------------
int */*thiscall*/ sub_40BEA0(int *this)
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
          break;
        *this = (int)result;
      }
      *this = (int)result;
    }
    else
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 45) == 0 )
      {
        do
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
// 0x40BF00 sub_40BF00
// ------------------------------------------------------------
int /*thiscall*/ sub_40BF00(std::_String_base *this, unsigned int uArg2, unsigned int uArg3, const char *pArg4, unsigned int uArg5)
{
  unsigned int pThis_5; // edx
  int pThis_52; // ecx
  int pThis_6; // eax
  int result; // eax

  if ( *((uint32_t *)this + 5) < uArg2 )
    std::_String_base::_Xran(this);
  pThis_5 = uArg3;
  if ( *((uint32_t *)this + 5) - uArg2 < uArg3 )
    pThis_5 = *((uint32_t *)this + 5) - uArg2;
  if ( pThis_5 == 0 )
    goto LABEL_12;
  pThis_52 = pThis_5;
  if ( pThis_5 >= uArg5 )
    pThis_52 = uArg5;
  pThis_6 = *((uint32_t *)this + 6) < 0x10u ? (int)this + 4 : *((uint32_t *)this + 1);
  result = memcmp((const char *)(pThis_6 + uArg2), pArg4, pThis_52);
  if ( result == 0 )
  {
LABEL_12:
    if ( pThis_5 >= uArg5 )
      return pThis_5 != uArg5;
    else
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40BF80 sub_40BF80
// ------------------------------------------------------------
int /*thiscall*/ sub_40BF80(int this)
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
  memset(&pbmi.bmiHeader.biCompression, 0, 24);
  *(uint32_t *)(this + 44) = CreateDIBSection(nullptr, &pbmi, 0, (void **)(this + 48), nullptr, 0);
  *(uint16_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  memset((void *)(this + 80), 0, 0x50u);
  fld_402 = *(uint32_t *)(this + 64) * *(uint32_t *)(this + 60);
  fld_30 = *(char **)(this + 48);
  if ( fld_402 != 0 )
  {
    v7 = fld_402 & 1;
    v8 = fld_402 >> 1;
    memset32(fld_30, 65537, v8);
    v9 = &fld_30[4 * v8];
    for ( i = v7; i != 0; --i )
    {
      *(uint16_t *)v9 = 1;
      v9 += 2;
    }
  }
  v11 = (HDC)pbmi.bmiColors[0];
  CompatibleDC = CreateCompatibleDC(*(HDC *)pbmi.bmiColors);
  fld_2C = *(void **)(this + 44);
  *(uint32_t *)(this + 40) = CompatibleDC;
  SelectObject(CompatibleDC, fld_2C);
  return ReleaseDC(*(HWND *)(this + 36), v11);
}



// ------------------------------------------------------------
// 0x40C040 sub_40C040
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_40C040(int this, LPCSTR lpString, COLORREF color, int nArg4)
{
  unsigned int fld_3C; // ecx
  char *fld_30; // edi
  char v7; // cf
  unsigned int v8; // ecx
  char *v9; // edi
  int i; // ecx
  BOOL result; // eax

  *(uint16_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  memset((void *)(this + 80), 0, 0x50u);
  fld_3C = *(uint32_t *)(this + 60) * *(uint32_t *)(this + 64);
  fld_30 = *(char **)(this + 48);
  if ( fld_3C != 0 )
  {
    v7 = fld_3C & 1;
    v8 = fld_3C >> 1;
    memset32(fld_30, 65537, v8);
    v9 = &fld_30[4 * v8];
    for ( i = v7; i != 0; --i )
    {
      *(uint16_t *)v9 = 1;
      v9 += 2;
    }
  }
  SetBkMode(*(HDC *)(this + 40), 1);
  SetTextColor(*(HDC *)(this + 40), color);
  result = TextOutA(*(HDC *)(this + 40), 0, 0, lpString, strlen(lpString));
  if ( nArg4 == 1 )
    return TextOutA(*(HDC *)(this + 40), 1, 0, lpString, strlen(lpString));
  return result;
}



// ------------------------------------------------------------
// 0x40C0E0 sub_40C0E0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_40C0E0(uint32_t *this)
{
  return sub_40BDD0(this);
}



// ------------------------------------------------------------
// 0x40C0F0 sub_40C0F0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_40C0F0(int nArg1, int nArg2, uint32_t *uArg3)
{
  uint32_t *result; // eax

  result = operator new(0xCu);
  if ( result != nullptr )
  {
    *result = nArg1;
    result[1] = nArg2;
    result[2] = *uArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40C120 sub_40C120
// ------------------------------------------------------------
void /*thiscall*/ sub_40C120(uint32_t *this)
{
  *(this + 6) = 15;
  *(this + 5) = 0;
  *((uint8_t *)this + 4) = 0;
}



// ------------------------------------------------------------
// 0x40C140 sub_40C140
// ------------------------------------------------------------
void /*thiscall*/ sub_40C140(void **this)
{
  sub_6569D0(this);
  j__free(*(this + 1));
  *(this + 1) = nullptr;
}



// ------------------------------------------------------------
// 0x40C160 sub_40C160
// ------------------------------------------------------------
bool /*stdcall*/ sub_40C160(unsigned int *pDwArg1, uint32_t *pArg2)
{
  const char *v2; // eax

  if ( pArg2[6] < 0x10u )
    v2 = (const char *)(pArg2 + 1);
  else
    v2 = (const char *)pArg2[1];
  return sub_40BF00((std::_String_base *)pDwArg1, 0, pDwArg1[5], v2, pArg2[5]) < 0;
}



// ------------------------------------------------------------
// 0x40C1A0 sub_40C1A0
// ------------------------------------------------------------
void /*thiscall*/ sub_40C1A0(uint32_t *this)
{
  *(this + 9) = 15;
  *(this + 8) = 0;
  *((uint8_t *)this + 16) = 0;
}



// ------------------------------------------------------------
// 0x40C1C0 sub_40C1C0
// ------------------------------------------------------------
void /*thiscall*/ sub_40C1C0(uint32_t *this)
{
  *(this + 1) = sub_425940(this);
  *(this + 2) = 0;
}



// ------------------------------------------------------------
// 0x40C1E0 sub_40C1E0
// ------------------------------------------------------------
void **/*thiscall*/ sub_40C1E0(void **Block, char pszArg2)
{
  sub_4017A0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x40C210 sub_40C210
// ------------------------------------------------------------
void /*thiscall*/ sub_40C210(uint32_t *this)
{
  char *fld_e5; // eax
  char *v3; // edi
  char *fld_e6; // eax
  char *v5; // edi

  fld_e5 = (char *)*(this + 5);
  if ( fld_e5 != nullptr )
  {
    v3 = fld_e5 - 4;
    `eh vector destructor iterator'(v2, 0x34u, *((uint32_t *)v2 - 1), sub_5014C0);
    j_j__free(v3);
    *(this + 5) = 0;
  }
  v4 = (char *)*(this + 6);
  if ( v4 != nullptr )
  {
    v5 = v4 - 4;
    `eh vector destructor iterator'(fld_e6, 0xCu, *((uint32_t *)fld_e6 - 1), (void (/*thiscall*/ *)(void *))sub_40C140);
    j_j__free(v5);
    *(this + 6) = 0;
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

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x40C300 sub_40C300
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40C300(uint32_t *this, int nArg2, int nArg3, int nArg4, size_t *pArg5, char pszArg6)
{
  char *pThis_3; // edi

  *(this + 1) = nArg3;
  pThis_3 = (char *)(this + 3);
  *this = nArg2;
  *(this + 2) = nArg4;
  *(this + 9) = 15;
  *(this + 8) = 0;
  *((uint8_t *)this + 16) = 0;
  sub_4014D0(this + 3, pArg5, 0, 0xFFFFFFFF);
  *((uint32_t *)pThis_3 + 7) = pArg5[7];
  *((uint8_t *)this + 44) = pszArg6;
  *((uint8_t *)this + 45) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x40C360 sub_40C360
// ------------------------------------------------------------
int /*thiscall*/ sub_40C360(uint32_t *this, char *Src)
{
  int v3; // eax
  int v4; // esi
  size_t v6; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  int v8; // [esp+1Ch] [ebp-18h]
  unsigned int v9; // [esp+20h] [ebp-14h]
  int dword_796E502; // [esp+24h] [ebp-10h]
  int v11; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(&v6, Src, strlen(Src));  // 【std::string构造赋值】
  v11 = 0;
  v3 = *(uint32_t *)sub_5014F0(&Src, &v6);
  if ( v3 == *(this + 3) )
  {
    if ( v9 >= 0x10 )
      j__free(Block);
    return 0;
  }
  else
  {
    v4 = *(uint32_t *)(**(uint32_t **)(*(uint32_t *)(v3 + 40) + 4) + 8);
    if ( v9 >= 0x10 )
      j__free(Block);
    return v4;
  }
}



// ------------------------------------------------------------
// 0x40C430 sub_40C430
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_40C430(int nArg1, int nArg2, int nArg3, size_t *pArg4, char pszArg5)
{
  uint32_t *pMem; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  pMem = operator new(0x30u);
  v7[4] = pMem;
  v7[8] = (void *)1;
  v7[3] = pMem;
  if ( pMem != nullptr )
    sub_40C300(pMem, nArg1, nArg2, nArg3, pArg4, pszArg5);
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
    sub_401740(pExceptionObject, (int)v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_40BEA0(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 45) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 45) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 45) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_6600D0(v4);
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
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v25 + 8) = sub_4429F0(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 45) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
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
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 44);
  *((uint8_t *)v5 + 44) = *((uint8_t *)pDwArg32 + 44);
  *((uint8_t *)pDwArg32 + 44) = v14;
LABEL_35:
  v15 = (void **)Block;
  if ( *((uint8_t *)Block + 44) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 44) != 1 )
          break;
        v17 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v17 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v17 + 44) == 0 )
          {
            *((uint8_t *)v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_442AC0(v6);
            v17 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v17 + 44) != 1 || *(uint8_t *)(v17[2] + 44) != 1 )
          {
            if ( *(uint8_t *)(v17[2] + 44) == 1 )
            {
              *(uint8_t *)(*v17 + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;
              sub_433290(v17);
              v17 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(v17[2] + 44) = 1;
            sub_442AC0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v17 + 44) == 0 )
          {
            *((uint8_t *)v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_433290(v6);
            v17 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v17[2] + 44) != 1 || *(uint8_t *)(*v17 + 44) != 1 )
          {
            if ( *(uint8_t *)(*v17 + 44) == 1 )
            {
              *(uint8_t *)(v17[2] + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;
              sub_442AC0(v17);
              v17 = (uint32_t *)*v6;
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(*v17 + 44) = 1;
            sub_433290(v6);
            break;
          }
        }
        *((uint8_t *)v17 + 44) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 44) = 1;
  }
  if ( (unsigned int)v15[9] >= 0x10 )
    j__free(v15[4]);
  Block2 = Block;
  *((uint32_t *)Block + 9) = 15;
  Block2[8] = 0;
  *((uint8_t *)Block2 + 16) = 0;
  j__free(Block2);
  v19 = pThis[2];
  if ( v19 != 0 )
    pThis[2] = v19 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x40C7A0 sub_40C7A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40C7A0(uint32_t *this, size_t *pArg2)
{
  sub_4018B0((int)this, pArg2);
  *this = &std::out_of_range::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x40C7C0 sub_40C7C0
// ------------------------------------------------------------
char /*stdcall*/ sub_40C7C0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 45);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_40C7C0(i[2]);
    i = (void **)*i;
    sub_5014C0(Block2);
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
    sub_401740(pExceptionObject, &v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_40C430(*(this + 1), (int)pArg4, *(this + 1), pArg5, 0);
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
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = fld_e1 + 1;
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 44) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 44) != 0 )
        {
          if ( fld_e16 == (uint32_t *)v12[2] )
          {
            fld_e16 = (uint32_t *)*v10;
            sub_442AC0(*v10);
          }
          *(uint8_t *)(fld_e16[1] + 44) = 1;
          *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
          sub_433290(*(uint32_t *)(fld_e16[1] + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 44) != 0 )
      {
        if ( fld_e16 == (uint32_t *)*v12 )
        {
          fld_e16 = (uint32_t *)*v10;
          sub_433290(*v10);
        }
        *(uint8_t *)(fld_e16[1] + 44) = 1;
        *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
        sub_442AC0(*(uint32_t *)(fld_e16[1] + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 44) = 1;
      *(uint8_t *)(v14 + 44) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 44) = 0;
      fld_e16 = *(uint32_t **)(*v10 + 4);
LABEL_21:
      v10 = fld_e16 + 1;
      if ( *(uint8_t *)(fld_e16[1] + 44) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 44) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x40C9C0 sub_40C9C0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_40C9C0(uint32_t *this, int **pDwArg2)
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
  pDwArg22 = *result;
  fld_e3 = *result == (int **)*(this + 3);
  pDwArg2 = *result;
  if ( !fld_e3 )
  {
    v6 = pDwArg22[10];
    v7 = (uint32_t ***)v6[1];
    v8 = *v7;
    if ( *v7 != v7 )
    {
      do
      {
        v9 = (uint32_t **)*v8;
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
      while ( v9 != v7 );
    }
    return sub_40C4C0(pThis_2, &pDwArg2, pDwArg22);  // 【STL map/set 红黑树模板实例 + 字体位图缓存（invalid map/s…】
  }
  return result;
}



// ------------------------------------------------------------
// 0x40CA40 sub_40CA40
// ------------------------------------------------------------
int /*thiscall*/ sub_40CA40(int *this, int pArg2, size_t *pArg3)
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
      else
        v9 = *(const char **)(fld_e1 + 16);
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )
        goto LABEL_16;
      if ( v10 < v8 )
        v8 = v10;
      v11 = pArg32[6] < 0x10 ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];
      nCmp = memcmp(v11, v9, v8);
      v13 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )
      {
LABEL_16:
        v14 = *(uint32_t *)(fld_e1 + 32);
        if ( v10 >= v14 )
          v15 = v10 != v14;
        else
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      fld_e1 = v13 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);
      if ( *(uint8_t *)(fld_e1 + 45) != 0 )
        break;
    }
    fld_e12 = v19;
    this = pThis;
  }
  fld_e122 = fld_e12;
  pArg3 = fld_e12;
  if ( v5 != 0 )
  {
    if ( fld_e12 == *(size_t **)*(this + 1) )
    {
      *(uint32_t *)pArg2 = *sub_40C810(this, &pArg3, 1, fld_e12, pArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      return pArg2;
    }
    sub_501430(&pArg3);
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10 )
    v18 = (const char *)(pArg32 + 1);
  else
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )
  {
    *(uint32_t *)pArg2 = fld_e122;
    *(uint8_t *)(pArg2 + 4) = 0;
  }
  else
  {
    *(uint32_t *)pArg2 = *sub_40C810(pThis, &pArg3, v21, fld_e12, pArg32);
    *(uint8_t *)(pArg2 + 4) = 1;
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x40CBA0 sub_40CBA0
// ------------------------------------------------------------
int **/*thiscall*/ sub_40CBA0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
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
    sub_40C7C0(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
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
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
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
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x40CC60 sub_40CC60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40CC60(int *this)
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

  sub_40C210(this);
  *this = 168;
  pMem = operator new(0x2224u);
  v3 = nullptr;
  if ( pMem != nullptr )
  {
    v4 = pMem + 1;
    *pMem = 168;
    `eh vector constructor iterator'(v2 + 1, 0x34u, 168, (void (/*thiscall*/ *)(void *))sub_40C1A0, sub_5014C0);
  }
  else
  {
    v4 = nullptr;
  }
  *(this + 5) = (int)v4;
  v5 = *this;
  v6 = (int *)operator new(12 * *this + 4);
  if ( v6 != nullptr )
  {
    v3 = v6 + 1;
    *v6 = v5;
    `eh vector constructor iterator'(
      pMem2 + 1,
      0xCu,
      v5,
      (void (/*thiscall*/ *)(void *))sub_40C1C0,
      (void (/*thiscall*/ *)(void *))sub_40C140);
  }
  v7 = *this;
  *(this + 6) = (int)v3;
  v8 = 0;
  if ( v7 != 0 )
  {
    Block = nullptr;
    do
    {
      fld_e5 = *(this + 5);
      v10 = Block[fld_e5 + 40];
      v11 = &Block[fld_e5];
      if ( v10 != 0 )
        sub_40C9C0(this, (int **)v11);
      v11[40] = 0;
      v11[41] = v8;
      sub_4015C0((size_t *)v11 + 3, szPassword, 0);  // 【std::string构造赋值】
      *((uint16_t *)v11 + 22) = 0;
      *((uint32_t *)v11 + 12) = 0;
      v11[42] = v8 / 0x2A;
      ++v8;
      Block += 52;
    }
    while ( v8 < *this );
  }
  *(this + 1) = 0;
  fld_e3 = *(void ***)(*(this + 3) + 4);
  pThis_2 = this + 2;
  sub_40C7C0(fld_e3);
  *(uint32_t *)(pThis_2[1] + 4) = pThis_2[1];
  result = (uint32_t *)pThis_2[1];
  pThis_2[2] = 0;
  *result = result;
  *(uint32_t *)(pThis_2[1] + 8) = pThis_2[1];
  return result;
}



// ------------------------------------------------------------
// 0x40CDC0 sub_40CDC0
// ------------------------------------------------------------
void /*thiscall*/ sub_40CDC0(int *this, uint32_t *pArg2)
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
  if ( pArg2 != nullptr )
  {
    v4 = pArg2 + 3;
    v5 = *(uint32_t *)sub_5014F0(v15, pArg2 + 3);
    if ( v5 == *(this + 3) )
    {
      fld_e6 = (uint32_t *)(*(this + 6) + 12 * *((uint8_t *)pArg22 + 41));
      v12 = 15;
      v11 = 0;
      LOBYTE(Block) = 0;
      sub_4014D0(&v9, v4, 0, 0xFFFFFFFF);
      fld_e62 = fld_e6;
      v16 = 0;
      sub_40CA40(this + 2, (int)v14, &v9);
      v16 = -1;
      if ( v12 >= 0x10 )
        j__free(Block);
      v12 = 15;
      v11 = 0;
      LOBYTE(Block) = 0;
    }
    else
    {
      fld_e6 = *(uint32_t **)(v5 + 40);
    }
    v7 = fld_e6[1];
    pArg2 = sub_40C0F0(v7, *(uint32_t *)(v7 + 4), &pArg2);
    sub_40C270(fld_e6, 1u);
    pArg23 = pArg2;
    *(uint32_t *)(v7 + 4) = pArg2;
    *(uint32_t *)pArg23[1] = pArg23;
    ++*(this + 1);
  }
}



// ------------------------------------------------------------
// 0x40CEC0 sub_40CEC0
// ------------------------------------------------------------
int /*thiscall*/ sub_40CEC0(uint32_t *this)
{
  unsigned int nRand; // edi
  int result; // eax

  nRand = *(this + 5) + 52 * ((unsigned int)rand() % *this);
  sub_40C9C0(this, (int **)nRand);
  *(uint8_t *)(nRand + 40) = 0;
  sub_4015C0((size_t *)(nRand + 12), szPassword, 0);  // 【std::string构造赋值】
  *(uint16_t *)(nRand + 44) = 0;
  *(uint32_t *)(nRand + 48) = 0;
  result = *(this + 1) - 1;
  *(this + 1) = result;
  return result;
}



// ------------------------------------------------------------
// 0x40CF10 sub_40CF10
// ------------------------------------------------------------
int /*thiscall*/ sub_40CF10(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_40CBA0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x40CF50 sub_40CF50
// ------------------------------------------------------------
void /*thiscall*/ sub_40CF50(int *this)
{
  int *pThis; // esi
  int *v2; // eax
  int *v3; // [esp-8h] [ebp-1Ch]
  int *pThis2; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  v5 = 0;
  sub_40C210(this);
  v2 = (int *)pThis[3];
  pThis += 2;
  v3 = (int *)*v2;
  v5 = -1;
  sub_40CBA0((int ***)pThis, &pThis2, v3, v2);
  j__free((void *)pThis[1]);
  pThis[1] = 0;
  pThis[2] = 0;
}



// ------------------------------------------------------------
// 0x40CFC0 sub_40CFC0
// ------------------------------------------------------------
int /*thiscall*/ sub_40CFC0(uint32_t *this)
{
  unsigned int v2; // eax
  int i; // ecx
  unsigned int v5; // edx

  if ( *(this + 1) == *this - 1 )
    sub_40CEC0(this);
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
// 0x40D020 sub_40D020
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

  v8 = (uint16_t *)sub_40C360(lpString);
  if ( v8 != nullptr )
  {
    v9 = (const CHAR *)v8[1];
    v10 = v8[3];
    v11 = *v8;
    ++v8[22];
    v12 = *((uint8_t *)v8 + 42);
    v13 = &v9[v10];
    lpStringa = v9;
    v14 = v11 + v8[2];
    v29 = v11;
    v30 = lpStringa;
    v31 = v14;
    v32 = (int)v13;
    v15 = v8[3];
    result = (uint16_t *)(nArg3 + v8[2]);
    nArg32 = nArg3;
    nArg42 = nArg4;
    v27 = result;
    v28 = nArg4 + v15;
  }
  else
  {
    result = (uint16_t *)sub_40CFC0(*(this + 4));
    v17 = result;
    if ( result == nullptr )
      return result;
    v12 = *((uint8_t *)result + 42);
    v33 = *result;
    v34 = (const CHAR *)result[1];
    v35 = *result + 512;
    v36 = result[1] + 12;
    v18 = (int *)*(this + v12 + 5);
    v19 = *v18;
    v37 = v12;
    (*(void (/*thiscall*/ **)(int *))(v19 + 84))(v18);
    (*(void (/*thiscall*/ **)(uint32_t, int *, uint32_t))(*(uint32_t *)*(this + v12 + 5) + 24))(*(this + v12 + 5), &v33, 0);
    sub_40C040(lpString, color, 0);
    v20 = 0;
    v38 = 0;
    do
    {
      v21 = v20 << 10;
      v40 = 0;
      v39 = v20 << 10;
      do
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
        v21 += 2;
        v22 = ++v40 < 512;
        v39 = v21;
      }
      while ( v22 );
      v38 = ++v20;
    }
    while ( v20 < 12 );
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + v12 + 5) + 88))(*(this + v12 + 5));
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
    *((uint8_t *)v17 + 40) = 1;
    *((uint32_t *)v17 + 2) = color;
    sub_4015C0(lpString, strlen(lpString));  // 【std::string构造赋值】
    ++v17[22];
    *((uint32_t *)v17 + 12) = GetTickCount();
    result = (uint16_t *)sub_40CDC0(v17);
  }
  pObj = *(this + v12 + 5);
  if ( pObj != 0 )
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
// 0x40D220 sub_40D220
// ------------------------------------------------------------
int */*thiscall*/ sub_40D220(int *this)
{
  int *pThis_2; // esi
  int pThis_22; // eax

  pThis_2 = this + 2;
  pThis_22 = sub_433B80(this + 2);
  pThis_2[1] = pThis_22;
  *(uint8_t *)(pThis_22 + 45) = 1;
  *(uint32_t *)(pThis_2[1] + 4) = pThis_2[1];
  *(uint32_t *)pThis_2[1] = pThis_2[1];
  *(uint32_t *)(pThis_2[1] + 8) = pThis_2[1];
  pThis_2[2] = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  sub_40CC60(this);
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

  *(uint32_t *)this = &off_6C26EC;
  SelectObject(*((HDC *)this + 10), *((HGDIOBJ *)this + 14));
  DeleteObject(*((HGDIOBJ *)this + 13));
  DeleteObject(*((HGDIOBJ *)this + 11));
  DeleteObject(*((HGDIOBJ *)this + 10));
  pThis_4 = *((void **)this + 4);
  if ( pThis_4 != nullptr )
  {
    sub_40CF50(*((int **)this + 4));
    j__free(pThis_4);
  }
  *((uint32_t *)this + 4) = 0;
  pThis_14 = this + 20;
  for ( i = 4; i != 0; --i )
  {
    if ( *pThis_14 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_14)(*pThis_14, 1);
    *pThis_14++ = 0;
  }
  sub_416420(this);
  if ( _access("_DEBUG", 0) == 0 )
    FreeConsole();
  *(uint32_t *)this = &off_6C25B8;
  result = sub_416420(this);
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40D380 sub_40D380
// ------------------------------------------------------------
void /*thiscall*/ sub_40D380(
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
        char *lpString)
{
  if ( a6 != 0 )
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
  if ( a7 != 0 )
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

  sub_40B530((uint8_t *)this, nArg3, (int)Block);
  *(uint32_t *)this = &off_6C26EC;
  if ( _access("_DEBUG", 0) == 0 )
  {
    AllocConsole();
    sub_40BE20(v5, "\n<Start Console Log>...\n\n");
  }
  *(uint32_t *)(this + 36) = nArg2;
  *(uint32_t *)(this + 60) = 512;
  *(uint32_t *)(this + 64) = 12;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint16_t *)(this + 72) = 0;
  memset((void *)(this + 80), 0, 0x50u);
  sub_40BF80(this);
  FontA = CreateFontA(*(uint32_t *)(this + 68), 0, 0, 0, 100, 0, 0, 0, 0x80u, 0, 0, 0, 0, "MS UI Gothic");
  fld_28 = *(HDC *)(this + 40);
  *(uint32_t *)(this + 52) = FontA;
  *(uint32_t *)(this + 56) = SelectObject(fld_28, FontA);
  pMem = (int *)operator new(0x1Cu);
  if ( pMem != nullptr )
    *(uint32_t *)(this + 16) = sub_40D220(pMem);
  else
    *(uint32_t *)(this + 16) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x40D630 sub_40D630
// ------------------------------------------------------------
char */*thiscall*/ sub_40D630(char *Block, char pszArg2)
{
  sub_40D290(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ============================================================
// SECTION 0x40D660 — 大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）
// ============================================================
// ------------------------------------------------------------
// 0x40D660 sub_40D660
// ------------------------------------------------------------
char /*cdecl*/ sub_40D660(int nArg1)  // 【大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）】
{
  int i; // esi
  char result; // al

  for ( i = 0; i < 4096; ++i )
  {
    result = *(uint8_t *)(i + nArg1);
    if ( result == 0 )
      break;
    if ( result >= 0 )
    {
      result = tolower(result);
      *(uint8_t *)(i + nArg1) = result;
    }
    else
    {
      ++i;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D6A0 sub_40D6A0
// ------------------------------------------------------------
int /*cdecl*/ sub_40D6A0(int pArg1)
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 77) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x40D6C0 sub_40D6C0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_40D6C0(uint32_t *pArg1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 77) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 77) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D6E0 sub_40D6E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40D6E0(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;
  if ( *(uint8_t *)(*result + 77) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);
  fld_e1 = *(this + 1);
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )
  {
    *(uint32_t *)(fld_e1 + 4) = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;
  }
  else
  {
    v4 = *(uint32_t **)(pArg2 + 4);
    if ( pArg2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D740 sub_40D740
// ------------------------------------------------------------
int /*thiscall*/ sub_40D740(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 77) == 0 )
    *(uint32_t *)(v3 + 4) = pArg2;
  *(uint32_t *)(result + 4) = pArg2[1];
  fld_e1 = *(this + 1);
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )
  {
    *(uint32_t *)(fld_e1 + 4) = result;
    *(uint32_t *)(result + 8) = pArg2;
    pArg2[1] = result;
  }
  else
  {
    v5 = (uint32_t *)pArg2[1];
    if ( pArg2 == (uint32_t *)v5[2] )
      v5[2] = result;
    else
      *v5 = result;
    *(uint32_t *)(result + 8) = pArg2;
    pArg2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D7A0 sub_40D7A0
// ------------------------------------------------------------
int /*thiscall*/ sub_40D7A0(void *this)
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
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 77) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 77) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 77) == 0 );
        if ( *(uint8_t *)(result + 77) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 77) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40D800 sub_40D800
// ------------------------------------------------------------
int */*thiscall*/ sub_40D800(int *this)
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
          break;
        *this = (int)result;
      }
      *this = (int)result;
    }
    else
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 77) == 0 )
      {
        do
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
// 0x40D860 sub_40D860
// ------------------------------------------------------------
uint32_t *sub_40D860()
{
  uint32_t *result; // eax

  result = operator new(0x50u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 76) = 1;
  *((uint8_t *)result + 77) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40D8A0 sub_40D8A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40D8A0(uint32_t *this)
{
  uint32_t *result; // eax
  uint32_t *v3; // esi

  result = (uint32_t *)*(this + 1);
  v3 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)v3[2];
      if ( result != nullptr )
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
// 0x40D8E0 sub_40D8E0
// ------------------------------------------------------------
int */*thiscall*/ sub_40D8E0(int **this, int pArg2)
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

  fld_e1 = *(this + 1);
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
      else
        v7 = *v6;
      v8 = v3[8];
      if ( v8 == 0 )
        goto LABEL_14;
      v9 = v3[8];
      if ( v8 >= v5 )
        v9 = v5;
      v10 = (unsigned int)v3[9] < 0x10 ? (const char *)(v3 + 4) : (const char *)v3[4];
      nCmp = memcmp(v10, v7, v9);
      v12 = nCmp < 0;
      v5 = v17;
      if ( nCmp == 0 )
      {
LABEL_14:
        if ( v8 < v5 )
          goto LABEL_17;
        v12 = false;
      }
      if ( v12 )
      {
LABEL_17:
        v3 = (int *)v3[2];
        goto LABEL_19;
      }
      fld_e12 = v3;
      v3 = (int *)*v3;
LABEL_19:
      if ( *((uint8_t *)v3 + 77) != 0 )
        return fld_e12;
    }
  }
  return fld_e1;
}



// ------------------------------------------------------------
// 0x40D9A0 sub_40D9A0
// ------------------------------------------------------------
int /*thiscall*/ sub_40D9A0(int this)
{
  if ( *(uint32_t *)(this + 32) >= 0x10u )
    j__free(*(void **)(this + 12));
  *(uint32_t *)(this + 32) = 15;
  *(uint32_t *)(this + 28) = 0;
  *(uint8_t *)(this + 12) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x40D9D0 sub_40D9D0
// ------------------------------------------------------------
void /*thiscall*/ sub_40D9D0(int this)
{
  if ( *(uint32_t *)(this + 60) >= 0x10u )
    j__free(*(void **)(this + 40));
  *(uint32_t *)(this + 60) = 15;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 40) = 0;
  if ( *(uint32_t *)(this + 24) >= 0x10u )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x40DA20 sub_40DA20
// ------------------------------------------------------------
void /*thiscall*/ sub_40DA20(int this)
{
  if ( *(uint32_t *)(this + 72) >= 0x10u )
    j__free(*(void **)(this + 52));
  *(uint32_t *)(this + 72) = 15;
  *(uint32_t *)(this + 68) = 0;
  *(uint8_t *)(this + 52) = 0;
  if ( *(uint32_t *)(this + 36) >= 0x10u )
    j__free(*(void **)(this + 16));
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 15;
  *(uint8_t *)(this + 16) = 0;
}



// ------------------------------------------------------------
// 0x40DA70 sub_40DA70
// ------------------------------------------------------------
int **/*thiscall*/ sub_40DA70(int **this, int **pDwArg2, unsigned int *pDwArg3)
{
  int *v5; // eax
  unsigned int v6; // ecx
  const char *v7; // eax
  int *v9; // [esp+18h] [ebp+Ch]

  v5 = sub_40D8E0(this, (int)pDwArg3);
  v9 = v5;
  if ( v5 == *(this + 1)
    || ((v6 = v5[8], (unsigned int)v5[9] < 0x10) ? (v7 = (const char *)(v5 + 4)) : (v7 = (const char *)v5[4]),
        sub_40BF00((std::_String_base *)pDwArg3, 0, pDwArg3[5], v7, v6) < 0) )
  {
    *pDwArg2 = *(this + 1);
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = v9;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x40DAE0 sub_40DAE0
// ------------------------------------------------------------
int /*thiscall*/ sub_40DAE0(int this, size_t *pArg2)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((size_t *)this, pArg2, 0, 0xFFFFFFFF);
  *(uint32_t *)(this + 28) = pArg2[7];
  *(uint32_t *)(this + 32) = pArg2[8];
  *(uint32_t *)(this + 60) = 15;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 40) = 0;
  sub_4014D0((size_t *)(this + 36), pArg2 + 9, 0, 0xFFFFFFFF);
  return this;
}



// ------------------------------------------------------------
// 0x40DB60 sub_40DB60
// ------------------------------------------------------------
int /*thiscall*/ sub_40DB60(int this, size_t *pArg2, uint32_t *pArg3)  // 【NPK条目构造】
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((size_t *)this, pArg2, 0, 0xFFFFFFFF);
  *(uint32_t *)(this + 28) = *pArg3;
  *(uint32_t *)(this + 32) = pArg3[1];
  *(uint32_t *)(this + 60) = 15;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 40) = 0;
  sub_4014D0((size_t *)(this + 36), pArg3 + 2, 0, 0xFFFFFFFF);
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

  fld_e2 = *(this + 2);
  if ( 97612893 - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x40DC70 sub_40DC70
// ------------------------------------------------------------
int */*thiscall*/ sub_40DC70(int **this, char *pszArg2)
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

  dword_796E502 = dword_796E50;
  pszArg22 = pszArg2;
  v4 = (char *)(Src - pszArg2);
  do
  {
    v5 = *pszArg22;
    pszArg22[(uint32_t)v4] = *pszArg22;
    ++pszArg22;
  }
  while ( v5 != 0 );
  sub_40D660((int)Src);  // 【大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）】
  v11 = 15;
  v10 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(&v8, Src, strlen(Src));  // 【std::string构造赋值】
  v14 = 0;
  v6 = *sub_40DA70(this, (int **)&pszArg2, &v8);
  if ( v11 >= 0x10 )
    j__free(Block);
  if ( v6 == *(this + 1) )
    return nullptr;
  else
    return v6 + 10;
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

  for ( i = strlen(pszArg5) - 1; i >= 0; --i )
  {
    if ( pszArg5[i] == 92 )
      pszArg5[i] = 47;
  }
  sub_40D660((int)pszArg5);  // 【大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）】
  fld_e1 = *(this + 1);
  v8 = *fld_e1;
  if ( *fld_e1 == (int *)fld_e1 )
    goto LABEL_8;
  while ( 1 )
  {
    pFile4 = sub_40DC70((int **)v8 + 10, pszArg5);
    if ( pFile4 != nullptr )
      break;
    v8 = (int *)*v8;
    if ( v8 == (int *)*(this + 1) )
      goto LABEL_8;
  }
  pFile = (FILE *)v8[2];
  pFile2 = (FILE **)(v8 + 2);
  *pDwArg3 = *pFile4;
  *uArg4 = pFile4[1];
  if ( pFile != nullptr )
  {
    fseek(pFile, *pFile4, 0);
    *(uint32_t *)(pArg2 + 24) = 15;
    *(uint32_t *)(pArg2 + 20) = 0;
    *(uint8_t *)(pArg2 + 4) = 0;
    sub_4014D0((size_t *)pArg2, (size_t *)v8 + 3, 0, 0xFFFFFFFF);
    return pArg2;
  }
  if ( v8 == (int *)-8
    || ((pFile3 = (size_t *)(v8 + 3), (unsigned int)v8[9] < 0x10)
      ? (v13 = (const char *)(v8 + 4))
      : (v13 = (const char *)v8[4]),
        pFile5 = fopen(v13, "rb"),
        v15 = pFile5,
        pFile5 == nullptr) )
  {
LABEL_8:
    *(uint32_t *)(pArg2 + 24) = 15;
    *(uint32_t *)(pArg2 + 20) = 0;
    *(uint8_t *)(pArg2 + 4) = 0;
    sub_4015C0((size_t *)pArg2, szPassword, 0);  // 【std::string构造赋值】
    return pArg2;
  }
  fseek(pFile5, *pFile4, 0);
  *pFile2 = v15;
  *(uint32_t *)(pArg2 + 24) = 15;
  *(uint32_t *)(pArg2 + 20) = 0;
  *(uint8_t *)(pArg2 + 4) = 0;
  sub_4014D0((size_t *)pArg2, pFile3, 0, 0xFFFFFFFF);
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

  for ( i = strlen(pszArg4) - 1; i >= 0; --i )
  {
    if ( pszArg4[i] == 92 )
      pszArg4[i] = 47;
  }
  sub_40D660((int)pszArg4);  // 【大小写归一文件查找 + 文件名红黑树（NPK 内索引的磁盘侧支撑）】
  fld_e1 = *(this + 1);
  v7 = *fld_e1;
  if ( *fld_e1 == (int *)fld_e1 )
    return nullptr;
  while ( 1 )
  {
    pFile5 = sub_40DC70((int **)v7 + 10, pszArg4);
    pFile4 = pFile5;
    if ( pFile5 != nullptr )
      break;
    v7 = (int *)*v7;
    if ( v7 == (int *)*(this + 1) )
      return nullptr;
  }
  pFile = (FILE *)v7[2];
  pFile2 = (FILE **)(v7 + 2);
  *pDwArg2 = *pFile5;
  *uArg3 = pFile5[1];
  if ( pFile != nullptr )
  {
    fseek(pFile, *pFile5, 0);
    return pFile;
  }
  if ( pFile2 == nullptr )
    return nullptr;
  v13 = (unsigned int)pFile2[7] < 0x10 ? (const char *)(pFile2 + 2) : (const char *)pFile2[2];
  pFile3 = fopen(v13, "rb");
  if ( pFile3 == nullptr )
    return nullptr;
  fseek(pFile3, *pFile4, 0);
  *pFile2 = pFile3;
  return pFile3;
}



// ------------------------------------------------------------
// 0x40DFB0 sub_40DFB0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_40DFB0(int nArg1, int nArg2, int nArg3, size_t *pArg4, char pszArg5)
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
  if ( pMem != nullptr )
  {
    *pMem = nArg1;
    pMem[1] = nArg2;
    pMem[2] = nArg3;
    sub_40DAE0((int)(pMem + 3), pArg4);
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
  v4 = *((uint8_t *)Block + 77);
  pThis = this;
  if ( v4 != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v25 = 0;
    sub_401740(pExceptionObject, &v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  sub_40D800((int *)&Block);
  if ( *(uint8_t *)(*Block2 + 77) != 0 )
  {
    v5 = Block2[2];
LABEL_8:
    v7 = Block2[1];
    if ( *(uint8_t *)(v5 + 77) == 0 )
      *(uint32_t *)(v5 + 4) = v7;
    pThis2 = pThis;
    v9 = pThis[1];
    if ( *(int **)(v9 + 4) == Block2 )
    {
      *(uint32_t *)(v9 + 4) = v5;
    }
    else if ( *(int **)v7 == Block2 )
    {
      *(uint32_t *)v7 = v5;
    }
    else
    {
      *(uint32_t *)(v7 + 8) = v5;
    }
    if ( *(int **)pThis2[1] == Block2 )
    {
      if ( *(uint8_t *)(v5 + 77) != 0 )
      {
        v10 = (uint32_t *)v7;
      }
      else
      {
        v10 = sub_40D6C0((uint32_t *)v5);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v10;
    }
    if ( *(int **)(pThis2[1] + 8) == Block2 )
    {
      if ( *(uint8_t *)(v5 + 77) != 0 )
      {
        *(uint32_t *)(pThis2[1] + 8) = v7;
      }
      else
      {
        v11 = sub_40D6A0(v5);
        pThis2 = pThis;
        *(uint32_t *)(pThis[1] + 8) = v11;
      }
    }
    goto LABEL_35;
  }
  if ( *(uint8_t *)(Block2[2] + 77) != 0 )
  {
    v5 = *Block2;
    goto LABEL_8;
  }
  Block3 = Block;
  v5 = Block[2];
  if ( Block == Block2 )
    goto LABEL_8;
  *(uint32_t *)(*Block2 + 4) = Block;
  *Block3 = *Block2;
  if ( Block3 == (int *)Block2[2] )
  {
    v7 = (int)Block3;
  }
  else
  {
    v7 = Block3[1];
    if ( *(uint8_t *)(v5 + 77) == 0 )
      *(uint32_t *)(v5 + 4) = v7;
    *(uint32_t *)v7 = v5;
    Block3[2] = Block2[2];
    *(uint32_t *)(Block2[2] + 4) = Block3;
  }
  v12 = pThis[1];
  if ( *(int **)(v12 + 4) == Block2 )
  {
    *(uint32_t *)(v12 + 4) = Block3;
  }
  else
  {
    Block32 = (int **)Block2[1];
    if ( *Block32 == Block2 )
      *Block32 = Block3;
    else
      Block32[2] = Block3;
  }
  Block3[1] = Block2[1];
  v14 = *((uint8_t *)Block3 + 76);
  *((uint8_t *)Block3 + 76) = *((uint8_t *)Block2 + 76);
  *((uint8_t *)Block2 + 76) = v14;
  pThis2 = pThis;
LABEL_35:
  if ( *((uint8_t *)Block2 + 76) == 1 )
  {
    if ( v5 != *(uint32_t *)(pThis2[1] + 4) )
    {
      do
      {
        if ( *(uint8_t *)(v5 + 76) != 1 )
          break;
        pObj = *(uint8_t **)v7;
        if ( v5 == *(uint32_t *)v7 )
        {
          pObj = *(uint8_t **)(v7 + 8);
          if ( pObj[76] == 0 )
          {
            pObj[76] = 1;
            *(uint8_t *)(v7 + 76) = 0;
            sub_40D6E0(pThis2, v7);
            pObj = *(uint8_t **)(v7 + 8);
            pThis2 = pThis;
          }
          if ( pObj[77] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)pObj + 76) != 1 || *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) != 1 )
          {
            if ( *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)pObj + 76) = 1;
              pObj[76] = 0;
              sub_40D740(pThis2, pObj);
              pObj = *(uint8_t **)(v7 + 8);
              pThis2 = pThis;
            }
            pObj[76] = *(uint8_t *)(v7 + 76);
            *(uint8_t *)(v7 + 76) = 1;
            *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) = 1;
            sub_40D6E0(pThis2, v7);
            break;
          }
        }
        else
        {
          if ( pObj[76] == 0 )
          {
            pObj[76] = 1;
            *(uint8_t *)(v7 + 76) = 0;
            sub_40D740(pThis2, (uint32_t *)v7);
            pObj = *(uint8_t **)v7;
            pThis2 = pThis;
          }
          if ( pObj[77] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) != 1 || *(uint8_t *)(*(uint32_t *)pObj + 76) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)pObj + 76) == 1 )
            {
              *(uint8_t *)(*((uint32_t *)pObj + 2) + 76) = 1;
              pObj[76] = 0;
              sub_40D6E0(pThis2, (int)pObj);
              pObj = *(uint8_t **)v7;
              pThis2 = pThis;
            }
            pObj[76] = *(uint8_t *)(v7 + 76);
            *(uint8_t *)(v7 + 76) = 1;
            *(uint8_t *)(*(uint32_t *)pObj + 76) = 1;
            sub_40D740(pThis2, (uint32_t *)v7);
            break;
          }
        }
        pObj[76] = 0;
LABEL_53:
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
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *pDwArg2 = Block;
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
    sub_40DD60((int ***)&unk_8A76C8 + 4 * nArg5, pArg1, pDwArg2, uArg4, FileName);
    return pArg1;
  }
  else
  {
    if ( fopen(FileName, "rb") != nullptr )
      *pDwArg2 = 0;
    *(uint32_t *)(pArg1 + 20) = 0;
    *(uint32_t *)(pArg1 + 24) = 15;
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
  if ( pFile == nullptr )
    return nullptr;
  v7 = _fileno(pFile);
  *pDwArg2 = _filelength(v7);
  *pDwArg1 = 0;
  return pFile2;
}



// ------------------------------------------------------------
// 0x40E450 sub_40E450
// ------------------------------------------------------------
char /*stdcall*/ sub_40E450(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 77);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_40E450(i[2]);
    i = (void **)*i;
    sub_40DA20((int)Block2);
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
    sub_401740(pExceptionObject, &v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_40DFB0(*(this + 1), (int)pArg4, *(this + 1), pArg5, 0);
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
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = fld_e1 + 1;
  v11 = (int)fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 76) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 76) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_40D6E0(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 76) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 76) = 0;
          sub_40D740(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 76) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_40D740(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 76) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 76) = 0;
        sub_40D6E0(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 76) = 1;
      *(uint8_t *)(v14 + 76) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 76) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 76) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 76) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x40E650 sub_40E650
// ------------------------------------------------------------
void */*thiscall*/ sub_40E650(void **this, int *pDwArg2, int nArg3)
{
  char v3; // al
  uint32_t *fld_e1; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)pDwArg2 + 77);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    fld_e1 = sub_40DFB0((int)*(this + 1), nArg3, (int)*(this + 1), (size_t *)pDwArg2 + 3, *((uint8_t *)pDwArg2 + 76));
    if ( *((uint8_t *)Block + 77) != 0 )
      Block = fld_e1;
    v6 = *pDwArg2;
    v10 = 0;
    *fld_e1 = sub_40E650(v6, fld_e1);
    fld_e1[2] = sub_40E650(pDwArg2[2], fld_e1);
  }
  return Block;
}



// ------------------------------------------------------------
// 0x40E700 sub_40E700
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
      else
        v9 = *(const char **)(fld_e1 + 16);
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )
        goto LABEL_16;
      if ( v10 < v8 )
        v8 = v10;
      v11 = pArg32[6] < 0x10 ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];
      nCmp = memcmp(v11, v9, v8);
      v13 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )
      {
LABEL_16:
        v14 = *(uint32_t *)(fld_e1 + 32);
        if ( v10 >= v14 )
          v15 = v10 != v14;
        else
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      fld_e1 = v13 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);
      if ( *(uint8_t *)(fld_e1 + 77) != 0 )
        break;
    }
    fld_e12 = v19;
    this = pThis;
  }
  fld_e122 = fld_e12;
  pArg3 = fld_e12;
  if ( v5 != 0 )
  {
    if ( fld_e12 == *(size_t **)*(this + 1) )
    {
      *(uint32_t *)pArg2 = *sub_40E4A0(this, &pArg3, 1, fld_e12, pArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      return pArg2;
    }
    sub_40D7A0(&pArg3);
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10 )
    v18 = (const char *)(pArg32 + 1);
  else
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )
  {
    *(uint32_t *)pArg2 = fld_e122;
    *(uint8_t *)(pArg2 + 4) = 0;
  }
  else
  {
    *(uint32_t *)pArg2 = *sub_40E4A0(pThis, &pArg3, v21, fld_e12, pArg32);
    *(uint8_t *)(pArg2 + 4) = 1;
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x40E860 sub_40E860
// ------------------------------------------------------------
int **/*thiscall*/ sub_40E860(void ****this, int **pDwArg2, int *Block, int *pDwArg4)
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
  fld_e1 = *(this + 1);
  if ( Block == (int *)*fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_40E450(fld_e1[1]);
    (*(this + 1))[1] = (void **)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (void **)*(this + 1);
    *pDwArg2 = (int *)**(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( Block != pDwArg4 )
    {
      do
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
                break;
              Block2 = (int *)i;
            }
            Block2 = (int *)i;
          }
          else
          {
            Block2 = (int *)Block2[2];
            for ( j = *(int **)v11; *((uint8_t *)j + 77) == 0; j = (int *)*j )
              Block2 = j;
          }
        }
        sub_40E050(this, &Block, Block22);
      }
      while ( Block2 != pDwArg42 );
    }
    *pDwArg2 = Block2;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x40E920 sub_40E920
// ------------------------------------------------------------
int */*thiscall*/ sub_40E920(int this, int pArg2)
{
  int fld_4; // edi
  int **fld_42; // edx
  int *result; // eax
  int *v6; // ecx
  int fld_43; // esi
  int **v8; // ecx

  fld_4 = *(uint32_t *)(this + 4);
  *(uint32_t *)(fld_4 + 4) = sub_40E650((void **)this, *(int **)(*(uint32_t *)(pArg2 + 4) + 4), fld_4);
  *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8);
  fld_42 = *(int ***)(this + 4);
  result = fld_42[1];
  if ( *((uint8_t *)result + 77) != 0 )
  {
    *fld_42 = (int *)fld_42;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 77) == 0 )
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 77) == 0 );
    }
    *fld_42 = result;
    fld_43 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(fld_43 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 77) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(fld_43 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40E9B0 sub_40E9B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40E9B0(uint32_t *this)
{
  uint32_t *result; // eax

  sub_40E450(*(void ***)(*(this + 1) + 4));
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  result = (uint32_t *)*(this + 1);
  *(this + 2) = 0;
  *result = result;
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

  dword_796E502 = dword_796E50;
  pThis = this;
  v27 = 15;
  v26 = 0;
  LOBYTE(Block) = 0;
  v29 = 0;
  sub_66BD5A(Str2, 0x10u, 1u, Stream);  // 【fread封装】
  if ( strncmp("NeoplePack_Bill", Str2, 0x10u) == 0 )
  {
    sub_66BD5A(&Buffer, 4u, 1u, Stream);  // 【fread封装】
    Streama = nullptr;
    if ( Buffer > 0 )
    {
      do
      {
        sub_66BD5A(&v23, 4u, 1u, Stream);  // 【fread封装】
        sub_66BD5A(v24, 4u, 1u, Stream);  // 【fread封装】
        sub_66BD5A(Src, 0x100u, 1u, Stream);  // 【fread封装】
        Src[255] = 0;
        v18 = 15;
        v17 = 0;
        LOBYTE(v16) = 0;
        sub_4015C0(&v15, Src, strlen(Src));  // 【std::string构造赋值】
        LOBYTE(v29) = 1;
        v4 = (size_t *)sub_40DB60((int)v8, &v15, &v23);  // 【NPK条目构造】
        LOBYTE(v29) = 2;
        sub_40E700(pThis, (int)v7, v4);  // 【NPK名字树插入】
        if ( v14 >= 0x10 )
          j__free(v12);
        v14 = 15;
        v13 = 0;
        LOBYTE(v12) = 0;
        if ( v11 >= 0x10 )
          j__free(v9);
        v11 = 15;
        v10 = 0;
        LOBYTE(v9) = 0;
        LOBYTE(v29) = 0;
        if ( v18 >= 0x10 )
          j__free(v16);
        v6 = __OFSUB__((char *)&Streama->_ptr + 1, Buffer);
        v5 = (int)&Streama->_ptr - Buffer + 1 < 0;
        v18 = 15;
        v17 = 0;
        LOBYTE(v16) = 0;
        Streama = (FILE *)((char *)Streama + 1);
      }
      while ( v5 != v6 );
    }
    if ( v27 >= 0x10 )
      j__free(Block);
    return 1;
  }
  else
  {
    if ( v27 >= 0x10 )
      j__free(Block);
    return 0;
  }
}



// ------------------------------------------------------------
// 0x40EC10 sub_40EC10
// ------------------------------------------------------------
int /*thiscall*/ sub_40EC10(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_40E860((void ****)this, (int **)&v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x40EC50 sub_40EC50
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40EC50(uint32_t *this, int nArg2)
{
  uint32_t *v3; // eax
  uint32_t v5[8]; // [esp+0h] [ebp-20h] BYREF

  v5[4] = v5;
  v5[3] = this;
  v3 = sub_40D860();
  *(this + 1) = v3;
  *((uint8_t *)v3 + 77) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  v5[7] = 0;
  sub_40E920((int)this, nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x40ECE0 sub_40ECE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40ECE0(uint32_t *this)
{
  char *pThis_8; // edi
  uint32_t *v3; // eax

  *(this + 7) = 15;
  *(this + 6) = 0;
  *((uint8_t *)this + 8) = 0;
  pThis_8 = (char *)(this + 8);
  v3 = sub_40D860();
  *((uint32_t *)pThis_8 + 1) = v3;
  *((uint8_t *)v3 + 77) = 1;
  *(uint32_t *)(*((uint32_t *)pThis_8 + 1) + 4) = *((uint32_t *)pThis_8 + 1);
  **((uint32_t **)pThis_8 + 1) = *((uint32_t *)pThis_8 + 1);
  *(uint32_t *)(*((uint32_t *)pThis_8 + 1) + 8) = *((uint32_t *)pThis_8 + 1);
  *((uint32_t *)pThis_8 + 2) = 0;
  *this = 0;
  return this;
}



// ------------------------------------------------------------
// 0x40ED50 sub_40ED50
// ------------------------------------------------------------
void /*thiscall*/ sub_40ED50(int this)
{
  int *fld_24; // eax
  int pThis_20; // esi
  int *v4; // [esp-8h] [ebp-28h]
  int v5[5]; // [esp+Ch] [ebp-14h] BYREF

  v5[1] = this;
  fld_24 = *(int **)(this + 36);
  pThis_20 = this + 32;
  v4 = (int *)*fld_24;
  v5[4] = 0;
  sub_40E860((void ****)(this + 32), (int **)v5, v4, fld_24);
  j__free(*(void **)(pThis_20 + 4));
  *(uint32_t *)(pThis_20 + 4) = 0;
  *(uint32_t *)(pThis_20 + 8) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 15;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x40EDE0 sub_40EDE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40EDE0(uint32_t *this, uint32_t *pArg2)
{
  uint32_t *pThis_1; // ecx

  pThis_1 = this + 1;
  *this = *pArg2;
  pThis_1[6] = 15;
  pThis_1[5] = 0;
  *((uint8_t *)pThis_1 + 4) = 0;
  sub_4014D0(pThis_1, pArg2 + 1, 0, 0xFFFFFFFF);
  sub_40EC50(this + 8, (int)(pArg2 + 8));
  return this;
}



// ------------------------------------------------------------
// 0x40EE50 sub_40EE50
// ------------------------------------------------------------
void /*thiscall*/ sub_40EE50(void *this)
{
  sub_40ED50((int)this + 8);
}



// ------------------------------------------------------------
// 0x40EE60 sub_40EE60
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_40EE60(int nArg1, int nArg2, uint32_t *uArg3)
{
  uint32_t *pMem; // esi
  void *v5[9]; // [esp+0h] [ebp-24h] BYREF

  v5[5] = v5;
  pMem = operator new(0x34u);
  v5[4] = pMem;
  v5[8] = (void *)1;
  v5[3] = pMem;
  if ( pMem != nullptr )
  {
    pMem[1] = nArg2;
    *pMem = nArg1;
    sub_40EDE0(pMem + 2, uArg3);
  }
  return pMem;
}



// ------------------------------------------------------------
// 0x40EEF0 sub_40EEF0
// ------------------------------------------------------------
int /*thiscall*/ sub_40EEF0(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_40EE60(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);
  result = sub_40DBE0(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x40EF30 sub_40EF30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_40EF30(uint32_t *this)
{
  uint32_t **fld_e1; // eax
  uint32_t *v3; // esi
  uint32_t *result; // eax
  bool fld_e12; // zf
  uint32_t *v6; // ebx

  fld_e1 = (uint32_t **)*(this + 1);
  v3 = *fld_e1;
  *fld_e1 = fld_e1;
  result = (uint32_t *)*(this + 1);
  result[1] = result;
  fld_e12 = v3 == (uint32_t *)*(this + 1);
  *(this + 2) = 0;
  if ( !fld_e12 )
  {
    do
    {
      v6 = (uint32_t *)*v3;
      sub_40EE50(v3);
      j__free(v3);
      result = (uint32_t *)*(this + 1);
      v3 = v6;
    }
    while ( v6 != result );
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

  dword_796E502 = dword_796E50;
  sub_40ECE0(&v33);
  v38 = 0;
  strcpy(psz, lpPathName);
  nLen = strlen(psz);
  if ( nLen > 0 )
  {
    v4 = Buffer[nLen + 1023];
    if ( v4 != 92 && v4 != 47 )
    {
      psz[nLen] = 92;
      psz[nLen + 1] = 0;
    }
  }
  GetCurrentDirectoryA(0x400u, Buffer);
  SetCurrentDirectoryA(lpPathName);
  lpPathNamea = 0;
  v5 = (void *)_findfirst("*.npk", (int)v31);
  v23 = v5;
  if ( v5 != (void *)-1 )
  {
    pFile = fopen(FileName, "rb");
    pFile3 = pFile;
    pFile5 = pFile;
    if ( pFile != nullptr )
    {
      if ( sub_40E9E0(v34, pFile) != 0 )  // 【NPK 资源包加载器（NeoplePack_Bill 魔数 / *.npk 目录扫描…】
      {
        v8 = 0;
        do
        {
          v9 = psz[v8];
          v30[v8++ - 1] = v9;
        }
        while ( v9 != 0 );
        nLen2 = strlen(FileName) + 1;
        v11 = &v28;
        do
          v12 = *++v11;
        while ( v12 != 0 );
        qmemcpy(v11, FileName, nLen2);
        sub_4015C0(&Src, &v30[strlen(&Src)] - v30);  // 【std::string构造赋值】
        sub_40EEF0(&v33);
        sub_40E9B0(v34);
        v5 = v23;
        pFile3 = pFile5;
        lpPathNamea = 1;
      }
      fclose(pFile3);
    }
    while ( _findnext(v5, (int)v31) == 0 )
    {
      pFile2 = fopen(FileName, "rb");
      pFile4 = pFile2;
      pFile22 = pFile2;
      if ( pFile2 != nullptr )
      {
        if ( sub_40E9E0(v34, pFile2) != 0 )  // 【NPK 资源包加载器（NeoplePack_Bill 魔数 / *.npk 目录扫描…】
        {
          v15 = 0;
          do
          {
            v16 = psz[v15];
            v30[v15++ - 1] = v16;
          }
          while ( v16 != 0 );
          nLen3 = strlen(FileName) + 1;
          v18 = &v28;
          do
            v19 = *++v18;
          while ( v19 != 0 );
          qmemcpy(v18, FileName, nLen3);
          sub_4015C0(&Src, &v30[strlen(&Src)] - v30);  // 【std::string构造赋值】
          fld_e1 = *(this + 1);
          v21 = sub_40EE60(fld_e1, *(uint32_t *)(fld_e1 + 4), (int)&v33);
          sub_40DBE0(this, 1u);
          *(uint32_t *)(fld_e1 + 4) = v21;
          *(uint32_t *)v21[1] = v21;
          sub_40E450(*(void **)(v35 + 4));
          v5 = v23;
          pFile4 = pFile22;
          *(uint32_t *)(v35 + 4) = v35;
          v36 = 0;
          *(uint32_t *)v35 = v35;
          *(uint32_t *)(v35 + 8) = v35;
          ++lpPathNamea;
        }
        fclose(pFile4);
      }
    }
    _findclose((intptr_t)v5);
  }
  SetCurrentDirectoryA(Buffer);
  v38 = -1;
  sub_40ED50(&v33);
  return lpPathNamea;
}


// ============================================================
// SECTION 0x40F2F0 — 矩形/绘制辅助与杂项（SetRect 族、sprite 小工具）
// ============================================================
// ------------------------------------------------------------
// 0x40F2F0 sub_40F2F0
// ------------------------------------------------------------
void /*thiscall*/ sub_40F2F0(int this)  // 【矩形/绘制辅助与杂项（SetRect 族、sprite 小工具）】
{
  sub_40D8A0((uint32_t *)this);
  sub_40EF30((uint32_t *)this);
  sub_40EF30((uint32_t *)this);
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x40F360 sub_40F360
// ------------------------------------------------------------
int /*thiscall*/ sub_40F360(uint32_t *this)
{
  uint32_t *pThis; // esi
  int v2; // eax
  int result; // eax

  pThis = this;
  v2 = *this;
  *((uint8_t *)this + 44) = 0;
  *((uint8_t *)this + 45) = 0;
  result = (*(int (/*stdcall*/ **)(int))(v2 + 92))(-16711936);
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
  pThis += 12;
  *pThis = 0;
  pThis[1] = 0;
  pThis[2] = 0;
  pThis[3] = 0;
  return result;
}



// ------------------------------------------------------------
// 0x40F3C0 sub_40F3C0
// ------------------------------------------------------------
int /*thiscall*/ sub_40F3C0(void *this, int nArg2, int nArg3, int nArg4)
{
  int result; // eax
  int pThis_8; // edx
  int pThis_7; // ecx

  if ( *((uint8_t *)this + 4) != 0 )
    return -2147483646;
  pThis_8 = nArg4 + *((uint32_t *)this + 8);
  *((uint32_t *)this + 6) = nArg4;
  pThis_7 = *((uint32_t *)this + 7);
  *((uint32_t *)this + 3) = nArg2;
  *((uint32_t *)this + 5) = nArg3;
  SetRect((LPRECT)this + 3, 0, 0, nArg3 + pThis_7, pThis_8);
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 172))(this);
  if ( result >= 0 )
  {
    *((uint8_t *)this + 4) = 1;
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F420 sub_40F420
// ------------------------------------------------------------
int /*thiscall*/ sub_40F420(int this)
{
  void *fld_C; // eax

  if ( *(uint8_t *)(this + 4) == 1 )
  {
    if ( *(uint32_t *)(this + 16) != 0 )
      j_j__free(*(void **)(this + 16));
    fld_C = *(void **)(this + 12);
    *(uint32_t *)(this + 16) = 0;
    if ( fld_C != nullptr )
      j_j__free(fld_C);
    *(uint32_t *)(this + 12) = 0;
    *(uint8_t *)(this + 4) = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x40F470 sub_40F470
// ------------------------------------------------------------
int /*thiscall*/ sub_40F470(int this)
{
  uint32_t *pMem; // eax
  int fld_182; // ebx
  unsigned int v5; // ecx
  int v6; // edx
  int fld_C; // edi
  size_t fld_18; // [esp-4h] [ebp-8h]

  if ( *(uint32_t *)(this + 12) == 0 )
    return -2147483647;
  if ( *(uint32_t *)(this + 16) != 0 )
    j_j__free(*(void **)(this + 16));
  fld_18 = 4 * *(uint32_t *)(this + 24);
  *(uint32_t *)(this + 16) = 0;
  pMem = operator new(fld_18);
  if ( pMem == nullptr )
    return -2147483640;
  fld_182 = *(uint32_t *)(this + 24);
  v5 = 0;
  v6 = 0;
  fld_C = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 16) = pMem;
  if ( fld_182 != 0 )
  {
    do
    {
      pMem[v5] = fld_C + 2 * v6;
      v6 += *(uint32_t *)(this + 20);
      ++v5;
    }
    while ( v5 < *(uint32_t *)(this + 24) );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x40F4E0 sub_40F4E0
// ------------------------------------------------------------
bool /*thiscall*/ sub_40F4E0(uint32_t *this, int nArg2, int nArg3, uint32_t *pArg4)
{
  if ( nArg2 < *pArg4 )
    return true;
  if ( nArg3 < pArg4[1] || nArg2 + *(this + 5) > pArg4[2] )
    return true;
  return nArg3 + *(this + 6) > pArg4[3];
}



// ------------------------------------------------------------
// 0x40F530 sub_40F530
// ------------------------------------------------------------
bool /*stdcall*/ sub_40F530(int nArg1, int nArg2, uint32_t *pArg3)
{
  if ( nArg1 < *pArg3 )
    return true;
  if ( nArg2 < pArg3[1] || nArg1 >= pArg3[2] )
    return true;
  return nArg2 >= pArg3[3];
}



// ------------------------------------------------------------
// 0x40F560 sub_40F560
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_40F560(int this, unsigned int uArg2)
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
  if ( result != 0 )
  {
    do
    {
      v7 = *(uint16_t **)(fld_10 + 4 * v4);
      if ( (*(uint8_t *)(this + 20) & 1) != 0 )
        *v7++ = uArg22;
      v8 = 0;
      if ( (*(uint32_t *)(this + 20) & 0xFFFFFFFE) != 0 )
      {
        do
          *(uint32_t *)&v7[2 * v8++] = v5;
        while ( v8 < *(uint32_t *)(this + 20) >> 1 );
        uArg22 = uArg2;
      }
      result = *(uint32_t *)(this + 24);
      ++v4;
    }
    while ( v4 < result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F5F0 sub_40F5F0
// ------------------------------------------------------------
int /*thiscall*/ sub_40F5F0(uint32_t *this, int nArg2, int nArg3, unsigned int uArg4)
{
  int result; // eax
  int16_t v5; // bx

  result = *(this + 12);
  if ( nArg2 >= result )
  {
    result = *(this + 13);
    if ( nArg3 >= result && nArg2 < *(this + 14) && nArg3 < *(this + 15) )
    {
      LOBYTE(v5) = 0;
      HIBYTE(v5) = uArg4 & 0xF8;
      result = *(this + 4);
      *(uint16_t *)(*(uint32_t *)(result + 4 * nArg3) + 2 * nArg2) = v5 | (uArg4 >> 19) & 0x1F | (uArg4 >> 5) & 0x7E0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F650 sub_40F650
// ------------------------------------------------------------
int /*thiscall*/ sub_40F650(uint32_t *this, int nArg2, int nArg3)
{
  int16_t fld_e4; // cx

  if ( nArg2 < *(this + 12) || nArg3 < *(this + 13) || nArg2 >= *(this + 14) || nArg3 >= *(this + 15) )
    return 0;
  fld_e4 = *(uint16_t *)(*(uint32_t *)(*(this + 4) + 4 * nArg3) + 2 * nArg2);
  return 8 * (fld_e4 & 0x1F | (4 * (fld_e4 & 0x7E0 | (8 * (fld_e4 & 0xF800)))));
}



// ------------------------------------------------------------
// 0x40F6A0 sub_40F6A0
// ------------------------------------------------------------
int /*thiscall*/ sub_40F6A0(uint32_t *this, int nArg2, int nArg3, unsigned int uArg4, unsigned int uArg5)
{
  uint16_t *fld_e4; // edi
  uint16_t v6; // dx
  int v7; // eax
  int result; // eax

  fld_e4 = (uint16_t *)(*(uint32_t *)(*(this + 4) + 4 * nArg3) + 2 * nArg2);
  LOBYTE(v6) = 0;
  HIBYTE(v6) = uArg5 & 0xF8;
  v7 = v6 | (uArg5 >> 19) & 0x1F | (uArg5 >> 5) & 0x7E0;
  if ( (uArg4 & 1) != 0 )
    *fld_e4++ = v7;
  result = (uint16_t)v7 | ((uint16_t)v7 << 16);
  if ( uArg4 >> 1 != 0 )
    memset32(fld_e4, result, uArg4 >> 1);
  return result;
}



// ------------------------------------------------------------
// 0x40F700 sub_40F700
// ------------------------------------------------------------
int /*thiscall*/ sub_40F700(uint32_t *this, int nArg2, int nArg3, int nArg4, unsigned int uArg5)
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
  if ( nArg4 != 0 )
  {
    fld_e4 = (int *)(*(this + 4) + 4 * nArg3);
    do
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
// 0x40F750 sub_40F750
// ------------------------------------------------------------
int /*thiscall*/ sub_40F750(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
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
  if ( v9 >= 0 )
  {
    v18 = v9 + 1;
    while ( 1 )
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
      result = (*(int (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, nArg23, nArg33, nArg6);
      if ( --v18 == 0 )
        break;
      v6 = v14;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F830 sub_40F830
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_40F830(void *this, int nArg2, int nArg3, unsigned int uArg4, int nArg5)
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

  if ( uArg4 == 0 )
    return (*(int (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, nArg2, nArg3, nArg5);
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
    ++v8;
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, nArg2, v11, nArg5);
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v16, i + nArg2, nArg5);
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v12 + nArg3, v11, nArg5);
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v8, i + nArg2, nArg5);
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, nArg2, i + v8, nArg5);
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v16, nArg3, nArg5);
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v12 + nArg3, i + v8, nArg5);
    (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 32))(this, v8, nArg3, nArg5);
    result = v13 + 1;
    v13 = result;
    ++nArg2;
    --nArg3;
    if ( result >= uArg42 )
      break;
    v7 = v16;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40F970 sub_40F970
// ------------------------------------------------------------
int /*thiscall*/ sub_40F970(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  (*(void (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 36))(this, nArg2, nArg3, nArg4, nArg6);
  (*(void (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 36))(this, nArg2, nArg3 + nArg5 - 1, nArg4, nArg6);
  (*(void (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 40))(this, nArg2, nArg3, nArg5, nArg6);
  return (*(int (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 40))(this, nArg2 + nArg4 - 1, nArg3, nArg5, nArg6);
}



// ------------------------------------------------------------
// 0x40F9E0 sub_40F9E0
// ------------------------------------------------------------
int /*thiscall*/ sub_40F9E0(void *this, int nArg2, int nArg3, int nArg4, unsigned int uArg5, int nArg6)
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
// 0x40FA20 sub_40FA20
// ------------------------------------------------------------
char /*thiscall*/ sub_40FA20(int this, int nArg2, int nArg3, int pArg4)
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
      LOBYTE(v5) = sub_40F4E0((uint32_t *)this, nArg2, nArg3, (uint32_t *)(pArg4 + 48));
      if ( (uint8_t)v5 == 0 )
      {
        v7 = *(uint32_t *)(pArg4 + 16);
        fld_10 = *(uint32_t *)(this + 16);
        fld_14 = 2 * *(uint32_t *)(this + 20);
        v5 = 0;
        fld_18 = *(uint32_t *)(this + 24);
        if ( fld_18 != 0 )
        {
          v12 = 2 * nArg2;
          v11 = (uint32_t *)(v7 + 4 * nArg3);
          do
            qmemcpy((void *)(v12 + *v11++), *(const void **)(fld_10 + 4 * v5++), fld_14);
          while ( v5 < fld_18 );
        }
      }
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x40FAC0 sub_40FAC0
// ------------------------------------------------------------
char /*thiscall*/ sub_40FAC0(int this, int nArg2, int nArg3, int pArg4, unsigned int uArg5)
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
      LOBYTE(fld_14) = sub_40F4E0((uint32_t *)this, nArg2, nArg3, (uint32_t *)(pArg4 + 48));
      if ( (uint8_t)fld_14 == 0 )
      {
        fld_14 = *(uint32_t *)(this + 20);
        fld_10 = *(uint32_t *)(this + 16);
        v8 = *(uint32_t *)(pArg4 + 16);
        fld_18 = *(uint32_t *)(this + 24);
        v10 = 0;
        fld_142 = fld_14;
        fld_102 = fld_10;
        if ( fld_18 != 0 )
        {
          v14 = 2 * nArg2;
          v11 = (uint32_t *)(v8 + 4 * nArg3);
          do
            LOBYTE(fld_14) = sub_4055B0((uint16_t *)(v14 + *v11++), *(uint32_t *)(fld_102 + 4 * v10++), fld_142, uArg5);
          while ( v10 < fld_18 );
        }
      }
    }
  }
  return fld_14;
}



// ------------------------------------------------------------
// 0x40FB50 sub_40FB50
// ------------------------------------------------------------
char /*thiscall*/ sub_40FB50(int this, int nArg2, int nArg3, int pArg4)
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
      LOBYTE(fld_14) = sub_40F4E0((uint32_t *)this, nArg2, nArg3, (uint32_t *)(pArg4 + 48));
      if ( (uint8_t)fld_14 == 0 )
      {
        fld_14 = *(uint32_t *)(this + 20);
        fld_10 = *(uint32_t *)(this + 16);
        v7 = *(uint32_t *)(pArg4 + 16);
        fld_18 = *(uint32_t *)(this + 24);
        v9 = 0;
        fld_142 = fld_14;
        fld_102 = fld_10;
        if ( fld_18 != 0 )
        {
          v13 = 2 * nArg2;
          v10 = (uint32_t *)(v7 + 4 * nArg3);
          do
            LOBYTE(fld_14) = sub_405630((uint16_t *)(v13 + *v10++), *(uint16_t **)(fld_102 + 4 * v9++), fld_142);
          while ( v9 < fld_18 );
        }
      }
    }
  }
  return fld_14;
}



// ------------------------------------------------------------
// 0x40FBE0 sub_40FBE0
// ------------------------------------------------------------
char /*thiscall*/ sub_40FBE0(int this, int nArg2, int nArg3, int pArg4, int nArg5, int nArg6)
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
      LOBYTE(v7) = sub_40F4E0((uint32_t *)this, nArg2, nArg3, (uint32_t *)(pArg4 + 48));
      if ( (uint8_t)v7 == 0 )
      {
        fld_14 = *(uint32_t *)(this + 20);
        fld_10 = *(uint32_t *)(this + 16);
        fld_18 = *(uint32_t *)(this + 24);
        v11 = 0;
        fld_142 = fld_14;
        v7 = *(uint32_t *)(pArg4 + 16);
        fld_102 = fld_10;
        if ( fld_18 != 0 )
        {
          v16 = 2 * nArg2;
          v12 = (uint32_t *)(v7 + 4 * nArg3);
          do
            LOBYTE(v7) = (uint8_t)sub_4057E0(
                                            (unsigned int *)(v16 + *v12++),
                                            *(char **)(fld_102 + 4 * v11++),
                                            fld_142,
                                            nArg5 + (nArg6 << 12));
          while ( v11 < fld_18 );
        }
      }
    }
  }
  return v7;
}



// ------------------------------------------------------------
// 0x40FC80 sub_40FC80
// ------------------------------------------------------------
int /*thiscall*/ sub_40FC80(void *this, int nArg2, int nArg3, int nArg4)
{
  int result; // eax

  result = nArg4;
  if ( nArg4 != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, void *))(*(uint32_t *)nArg4 + 152))(nArg4, nArg2, nArg3, this);
  return result;
}



// ------------------------------------------------------------
// 0x40FCB0 sub_40FCB0
// ------------------------------------------------------------
bool /*cdecl*/ sub_40FCB0(float *pArg1, float *pArg2, float *pArg3)
{
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st5
  bool result; // al
  float v9; // [esp+Ch] [ebp+Ch]
  float v10; // [esp+10h] [ebp+10h]

  if ( *pArg2 <= (double)*pArg3 )
    v4 = *pArg3;
  else
    v4 = *pArg2;
  *pArg1 = v4;
  if ( pArg2[2] >= (double)pArg3[2] )
    v5 = pArg3[2];
  else
    v5 = pArg2[2];
  pArg1[2] = v5;
  if ( pArg2[1] <= (double)pArg3[1] )
    v6 = pArg3[1];
  else
    v6 = pArg2[1];
  v9 = v6;
  pArg1[1] = v6;
  if ( pArg2[3] >= (double)pArg3[3] )
    v7 = pArg3[3];
  else
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
// 0x40FD50 sub_40FD50
// ------------------------------------------------------------
int /*thiscall*/ sub_40FD50(int this)
{
  *(uint8_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x40FD90 sub_40FD90
// ------------------------------------------------------------
int /*thiscall*/ sub_40FD90(uint32_t *this, int *pDwArg2)
{
  int result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // ebx
  int fld_e9; // ecx
  int fld_e10; // eax
  int v11; // [esp+10h] [ebp+8h]

  result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, pDwArg2[5], pDwArg2[6]);
  if ( result >= 0 )
  {
    v5 = pDwArg2[2];
    if ( v5 == 8 || v5 == 16 || v5 == 14 || v5 == 15 )
    {
      v6 = pDwArg2[8];
      v7 = *pDwArg2;
      v8 = pDwArg2[7];
      pDwArg2[7] = 0;
      pDwArg2[8] = 0;
      v11 = v6;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t *))(v7 + 152))(pDwArg2, 0, 0, this);
      pDwArg2[7] = v8;
      pDwArg2[8] = v11;
      fld_e9 = *(this + 9);
      *(this + 8) = v11;
      fld_e10 = *(this + 10);
      *(this + 7) = v8;
      pDwArg2[9] = fld_e9;
      pDwArg2[10] = fld_e10;
    }
    else if ( v5 == 11 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
      sub_40FC80(this, 0, 0, (int)pDwArg2);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
      return 1;
    }
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x40FE40 sub_40FE40
// ------------------------------------------------------------
int /*thiscall*/ sub_40FE40(char *this, int nArg2)
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
    return -2147483646;
  *(this + 4) = 1;
  (*(void (/*stdcall*/ **)(int, uint32_t, char *))(*(uint32_t *)nArg2 + 56))(nArg2, 0, v11);
  v4 = yBottom;
  v5 = xRight;
  v10 = yBottom;
  v9 = xRight;
  *((uint32_t *)this + 28) = nArg2;
  *((uint32_t *)this + 5) = v5;
  *((uint32_t *)this + 6) = v4;
  *((uint32_t *)this + 9) = v5;
  *((uint32_t *)this + 10) = v4;
  *(this + 76) = 1;
  SetRect((LPRECT)(this + 88), 0, 0, v9, v10);
  SetRect(
    (LPRECT)this + 3,
    0,
    0,
    *((uint32_t *)this + 5) + *((uint32_t *)this + 7),
    *((uint32_t *)this + 6) + *((uint32_t *)this + 8));
  if ( v12 != 1 )
    return 1;
  pThis_1C = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, char *))(**((uint32_t **)this + 28) + 60))(
         *((uint32_t *)this + 28),
         0,
         this + 116);
  if ( pThis_1C >= 0 )
  {
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 84))(this);
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 88))(this);
    pThis_1A = *((uint32_t *)this + 26);
    v8 = *(uint32_t *)this;
    *((uint32_t *)this + 3) = *((uint32_t *)this + 27);
    *((uint32_t *)this + 20) = pThis_1A;
    pThis_1C = (*(int (/*thiscall*/ **)(char *))(v8 + 172))(this);
    if ( pThis_1C >= 0 )
      return 1;
  }
  (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 20))(this);
  return pThis_1C;
}



// ------------------------------------------------------------
// 0x40FF30 sub_40FF30
// ------------------------------------------------------------
int /*thiscall*/ sub_40FF30(int this)
{
  int fld_74; // eax
  bool fld_4C; // zf
  int fld_70; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
  {
    sub_405060(1u, -4 * *(uint32_t *)(this + 24) - *(uint32_t *)(this + 80) * *(uint32_t *)(this + 84), 0);
    fld_74 = *(uint32_t *)(this + 116);
    if ( fld_74 != 0 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_74 + 8))(*(uint32_t *)(this + 116));
    fld_4C = *(uint8_t *)(this + 76) == 0;
    *(uint32_t *)(this + 116) = 0;
    if ( fld_4C )
    {
      fld_70 = *(uint32_t *)(this + 112);
      if ( fld_70 != 0 )
        (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_70 + 8))(*(uint32_t *)(this + 112));
      *(uint32_t *)(this + 112) = 0;
    }
    if ( *(uint32_t *)(this + 16) != 0 )
      j_j__free(*(void **)(this + 16));
    *(uint32_t *)(this + 16) = 0;
    *(uint32_t *)(this + 112) = 0;
    *(uint32_t *)(this + 116) = 0;
    *(uint32_t *)(this + 88) = 0;
    *(uint32_t *)(this + 92) = 0;
    *(uint32_t *)(this + 96) = 0;
    *(uint32_t *)(this + 100) = 0;
    *(uint32_t *)(this + 104) = 0;
    *(uint32_t *)(this + 108) = 0;
    *(uint8_t *)(this + 76) = 0;
    *(uint8_t *)(this + 4) = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x40FFC0 sub_40FFC0
// ------------------------------------------------------------
int /*thiscall*/ sub_40FFC0(int this)
{
  int result; // eax

  if ( *(uint8_t *)(this + 44) != 0 )
    return -2147483642;
  result = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 112) + 64))(
             *(uint32_t *)(this + 112),
             0,
             this + 104,
             this + 48,
             0);
  if ( result >= 0 )
  {
    *(uint8_t *)(this + 44) = 1;
    return 1;
  }
  return result;
}


