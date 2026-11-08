# -*- coding: utf-8 -*-
"""客观粗注生成器 v10：广泛覆盖常见 C 反编译语句形态（客观描述，无语义猜测）。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

API = ('fopen|fclose|fseek|ftell|fflush|fread|fwrite|sprintf|strcpy|strlen|strncpy|strcmp|strncmp|memset|memcpy|qmemcpy|free|malloc|operator new|GetSystemMetrics|SetWindowPos|AdjustWindowRectEx|SendMessageA|PostMessageA|PostQuitMessage|ShowWindow|UpdateWindow|SetFocus|PeekMessageA|GetMessageA|TranslateMessage|DispatchMessageA|DefWindowProcA|FindWindowA|SetForegroundWindow|GetCurrentDirectoryA|SetCurrentDirectoryA|_findfirst|_findnext|_findclose|CreateFontA|CreateCompatibleDC|CreateCompatibleBitmap|CreateDIBSection|SelectObject|DeleteObject|DeleteDC|ReleaseDC|GetDC|GetWindowDC|TextOutA|GetTextExtentPoint32A|GetWindowLongA|SetWindowLongA|RegisterClassA|RegisterClassExA|CreateWindowExA|LoadIconA|LoadCursorA|DestroyWindow|InvalidateRect|RedrawWindow|BitBlt|StretchBlt|GetDIBits|CreateBitmap|GetClientRect|ClientToScreen|ScreenToClient|SetCursorPos|GetCursorPos|GetAsyncKeyState|GetKeyState|timeGetTime|GetTickCount|srand|rand|Sleep|GetLocalTime|GetSystemTime|GetModuleFileNameA|_access|WideCharToMultiByte|MultiByteToWideChar|CoCreateInstance|CoInitialize|CoUninitialize|InternetOpenA|InternetConnectA|HttpOpenRequestA|HttpSendRequestA|InternetCloseHandle|ShellExecuteExA|GetExitCodeProcess|DirectSoundCreate8|DirectInput8Create|Direct3DCreate8|InitializeCriticalSection|EnterCriticalSection|LeaveCriticalSection|DeleteCriticalSection|ImmReleaseContext|ImmGetContext|ImmSetCompositionWindow|QueryPerformanceCounter|QueryPerformanceFrequency|GlobalAlloc|GlobalFree|GlobalLock|GlobalUnlock|GetCurrentProcess|SetPriorityClass|AllocConsole|FreeConsole|GetStockObject|SetBkMode|SetTextColor|SetBkColor|CreateSolidBrush|GetProcessHeap|LoadLibraryA|GetProcAddress|FreeLibrary|exit|assert|time|realloc')

RULES = [
    # 与局部变量相关的守卫
    (re.compile(r'^if \( (\w+) != nullptr \)$'), lambda m: "若 %s 非空" % m.group(1)),
    (re.compile(r'^if \( (\w+) == nullptr \)$'), lambda m: "若 %s 为空" % m.group(1)),
    (re.compile(r'^if \( (\w+) != (\d+) \)$'), lambda m: "若 %s != %s" % (m.group(1), m.group(2))),
    (re.compile(r'^if \( (\w+) == (\d+) \)$'), lambda m: "若 %s == %s" % (m.group(1), m.group(2))),
    (re.compile(r'^if \( (\w+) >= (\d+) \)$'), lambda m: "若 %s >= %s" % (m.group(1), m.group(2))),
    (re.compile(r'^if \( (\w+) < (\d+) \)$'), lambda m: "若 %s < %s" % (m.group(1), m.group(2))),
    (re.compile(r'^if \( result >= (\d+) \)$'), lambda m: "若 result >= %s" % m.group(1)),
    (re.compile(r'^if \( result < (\d+) \)$'), lambda m: "若 result < %s" % m.group(1)),
    (re.compile(r'^if \( (\w+) != 0 \)$'), lambda m: "若 %s 非 0" % m.group(1)),
    (re.compile(r'^if \( (\w+) == 0 \)$'), lambda m: "若 %s 为 0" % m.group(1)),
    # this 字段守卫（uint8 字节偏移）
    (re.compile(r'^if \( \*\(\(uint8_t \*\)this \+ (\d+)\) != 0 \)$'), lambda m: "若 this 偏移 %s 非 0" % m.group(1)),
    (re.compile(r'^if \( \*\(\(uint8_t \*\)this \+ (\d+)\) == 0 \)$'), lambda m: "若 this 偏移 %s 为 0" % m.group(1)),
    (re.compile(r'^if \( \*\(\(uint32_t \*\)this \+ (\d+)\) != 0 \)$'), lambda m: "若 this 偏移 %d 非 0" % (int(m.group(1)))),
    (re.compile(r'^if \( \*\(\(uint32_t \*\)this \+ (\d+)\) == 0 \)$'), lambda m: "若 this 偏移 %d 为 0" % (int(m.group(1)))),
    # 简单赋值 v = v
    (re.compile(r'^(\w+) = (\w+);$'), lambda m: "%s = %s" % (m.group(1), m.group(2))),
    # 简单字段读
    (re.compile(r'^(\w+) = \*\(this \+ (\d+)\);$'), lambda m: "%s = this+%s" % (m.group(1), m.group(2))),
    (re.compile(r'^(\w+) = \*\(\(uint32_t \*\)this \+ (\d+)\);$'), lambda m: "%s = this 偏移 %d" % (m.group(1), int(m.group(2)))),
    (re.compile(r'^(\w+) = \*\(\(uint8_t \*\)this \+ (\d+)\);$'), lambda m: "%s = this 偏移 %s" % (m.group(1), m.group(2))),
    # 指针跟随
    (re.compile(r'^(\w+) = \*(\w+);$'), lambda m: "%s = 解引用 %s" % (m.group(1), m.group(2))),
    # 复合赋值
    (re.compile(r'^(\w+) \[(\w+)\] = (\w+);$'), lambda m: "%s[%s] = %s" % (m.group(1), m.group(2), m.group(3))),
    # 纯 API 调用
    (re.compile(r'^(' + API + r')\(.*\);$'), lambda m: "调 %s" % m.group(1)),
    # vtable 调用 (*(...))(this, ...)
    (re.compile(r'^\(\*\(.*?\)\)\(this\)\w*;$'), lambda m: "调 this 虚函数"),
]

def main():
    rel = sys.argv[1].replace("\\", "/").split("src/")[-1]
    path = ROOT + "\\src\\" + rel.replace("/", "\\")
    lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
    notes = []
    for i, l in enumerate(lines, 1):
        if '//' in l:
            continue
        s = l.strip()
        if not s or s in ('{', '}'):
            continue
        for rx, fn in RULES:
            m = rx.match(s)
            if m:
                try:
                    ann = fn(m)
                except Exception:
                    ann = None
                if ann and '"' not in ann and "'" not in ann and '/*' not in ann and '*/' not in ann:
                    notes.append([i, ann]); break
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto10_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
