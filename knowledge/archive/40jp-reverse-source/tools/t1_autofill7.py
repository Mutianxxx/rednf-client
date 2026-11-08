# -*- coding: utf-8 -*-
"""客观粗注生成器 v7：
1) 收集全仓库既有调用点语义标注 `sub_XXXX(  // 【语义名】` 建映射；
2) 对纯调用行 `sub_XXXX(...);` 用映射语义名（无则用地址）；
3) 附带 v5/v6 的客观形态。
"""
import io, re, sys, json, glob, os

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

SEM = re.compile(r'sub_([0-9A-F]{6})\s*\([^)]*\d*[^)]*\)\s*;\s*//\s*【([^】]+)】')
API = re.compile(r'^(fopen|fclose|fseek|ftell|fflush|fread|fwrite|sprintf|strcpy|strlen|strncpy|strcmp|strncmp|strncmp|_stricmp|memset|memcpy|memmove|free|malloc|realloc|assert|time|rand|srand|sprintf|vsprintf|_access|_fileno|_filelength|GetLocalTime|GetSystemTime|GetTickCount|GetAsyncKeyState|GetKeyState|GetCursorPos|SetCursorPos|ClientToScreen|ScreenToClient|GetClientRect|GetWindowRect|GetSystemMetrics|SetWindowPos|MoveWindow|AdjustWindowRectEx|SendMessageA|PostMessageA|PostQuitMessage|ShowWindow|UpdateWindow|SetFocus|PeekMessageA|GetMessageA|TranslateMessage|DispatchMessageA|DefWindowProcA|FindWindowA|SetForegroundWindow|GetForegroundWindow|GetCurrentDirectoryA|SetCurrentDirectoryA|_findfirst|_findnext|_findclose|CreateFontA|CreateCompatibleDC|CreateCompatibleBitmap|CreateDIBSection|SelectObject|DeleteObject|DeleteDC|ReleaseDC|GetDC|GetWindowDC|TextOutA|TextOutW|DrawTextA|GetTextExtentPoint32A|GetWindowLongA|SetWindowLongA|RegisterClassA|CreateWindowExA|LoadIconA|LoadCursorA|DestroyWindow|InvalidateRect|RedrawWindow|BitBlt|StretchBlt|GetDIBits|CreateBitmap|GetDCEx|Sleep|ExitProcess|GetModuleFileNameA|WideCharToMultiByte|MultiByteToWideChar|CoCreateInstance|CoInitialize|CoUninitialize|CoTaskMemFree|InternetOpenA|InternetConnectA|HttpOpenRequestA|HttpSendRequestA|InternetCloseHandle|ShellExecuteExA|GetExitCodeProcess|DirectSoundCreate8|DirectInput8Create|Direct3DCreate8|InitializeCriticalSection|EnterCriticalSection|LeaveCriticalSection|DeleteCriticalSection|ImmReleaseContext|ImmGetContext|ImmSetCompositionWindow|ImmGetCompositionStringA|ImmNotifyIME|QueryPerformanceCounter|QueryPerformanceFrequency|GlobalAlloc|GlobalFree|GlobalLock|GlobalUnlock|HeapAlloc|HeapFree|GetCurrentProcess|SetPriorityClass|GetStockObject|SetBkMode|SetTextColor|SetBkColor|CreateSolidBrush|CreatePen|MoveToEx|LineTo|Rectangle|Ellipse|GetProcessHeap|LoadLibraryA|GetProcAddress|FreeLibrary)\(',)
FIELD = re.compile(r'^(fld_[0-9A-Fa-f]+) = \*\(this \+ (\d+)\);$')

def main():
    rel = sys.argv[1].replace("\\", "/").split("src/")[-1]
    path = ROOT + "\\src\\" + rel.replace("/", "\\")
    # build semantic map from whole repo
    semmap = {}
    for p in glob.glob(os.path.join(ROOT, "src", "**", "*.cpp"), recursive=True):
        try:
            txt = io.open(p, encoding="utf-8", errors="replace").read()
        except Exception:
            continue
        for m in SEM.finditer(txt):
            va = m.group(1)
            name = m.group(2).strip()
            if va not in semmap:
                semmap[va] = name
    lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
    notes = []
    for i, l in enumerate(lines, 1):
        if '//' in l:
            continue
        s = l.strip()
        if not s:
            continue
        ann = None
        m = re.match(r'^sub_([0-9A-F]{6})\(.*\);$', s)
        if m:
            va = m.group(1)
            nm = semmap.get(va)
            ann = ("调 %s —— %s" % (va, nm)) if nm else ("调 sub_%s" % va)
        if ann is None:
            m = API.match(s)
            if m and s.endswith(';'):
                ann = "调 %s" % m.group(1)
        if ann is None:
            m = FIELD.match(s)
            if m:
                ann = "%s = this+%s 字段" % (m.group(1), m.group(2))
        if ann:
            notes.append([i, ann])
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto7_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("semmap=%d notes=%d -> %s" % (len(semmap), len(notes), out))

if __name__ == "__main__":
    main()
