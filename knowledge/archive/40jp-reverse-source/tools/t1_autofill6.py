# -*- coding: utf-8 -*-
"""客观粗注生成器 v6：调用语句/字段读取等客观形态（仅描述行为）。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

def describe_call(s):
    m = re.match(r'^(sub|unknown_libname_?|j__|j_j__|nullsub_?|std::)?_?([0-9A-Fa-f]{6})?\s*\(', s)
    return None

def main():
    rel = sys.argv[1].replace("\\", "/").split("src/")[-1]
    path = ROOT + "\\src\\" + rel.replace("/", "\\")
    lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
    notes = []
    for i, l in enumerate(lines, 1):
        if '//' in l:
            continue
        s = l.strip()
        if not s:
            continue
        ann = None
        # 纯调用语句: sub_XXXX(...); 或 known api(...);
        m = re.match(r'^(sub_[0-9A-F]{6})\((.*)\);$', s)
        if m:
            ann = "调 %s" % m.group(1)
        elif re.match(r'^(fopen|fclose|fseek|ftell|fflush|fread|fwrite|sprintf|strcpy|strlen|strncpy|strcmp|strncmp|memset|memcpy|qmemcpy|free|malloc|operator new|GetSystemMetrics|SetWindowPos|AdjustWindowRectEx|SendMessageA|PostQuitMessage|ShowWindow|UpdateWindow|SetFocus|PeekMessageA|GetMessageA|TranslateMessage|DispatchMessageA|DefWindowProcA|FindWindowA|SetForegroundWindow|GetCurrentDirectoryA|SetCurrentDirectoryA|_findfirst|_findnext|_findclose|CreateFontA|CreateCompatibleDC|CreateDIBSection|SelectObject|DeleteObject|DeleteDC|ReleaseDC|GetDC|TextOutA|GetTextExtentPoint32A|GetWindowLongA|SetWindowLongA|RegisterClassA|CreateWindowExA|LoadIconA|LoadCursorA|GetAsyncKeyState|timeGetTime|srand|rand|printf|exit|GetTickCount|Sleep|ImmReleaseContext|InvalidateRect|RedrawWindow|BitBlt|GetDIBits|GetWindowDC|CreateBitmap|GetClientRect|ClientToScreen|SetCursorPos|QueryPerformanceCounter|GetLocalTime|GetSystemTime|GetModuleFileNameA|_access|WideCharToMultiByte|MultiByteToWideChar|CoCreateInstance|CoInitialize|CoUninitialize|InternetOpenA|InternetConnectA|HttpOpenRequestA|HttpSendRequestA|InternetCloseHandle|ShellExecuteExA|GetExitCodeProcess|DirectSoundCreate8|DirectInput8Create|Direct3DCreate8|InitializeCriticalSection|EnterCriticalSection|LeaveCriticalSection|DeleteCriticalSection|InterlockedIncrement|InterlockedDecrement)\(', s):
            ann = "调 %s" % s.split('(')[0]
        # 字段读取 fld_eN = *(this + N)
        m = re.match(r'^(fld_[0-9A-Fa-f]+) = \*\(this \+ (\d+)\);$', s)
        if m:
            ann = "%s = this+%s 字段" % (m.group(1), m.group(2))
        if ann:
            notes.append([i, ann])
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto6_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
