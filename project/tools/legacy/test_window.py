"""Keep the requested visible SDL test window above other windows on Windows."""
import os
import time


def show_test_window(process, timeout=15):
    if os.name != 'nt':
        return {'supported': False}
    import ctypes as C
    from ctypes import wintypes as W
    user = C.windll.user32
    user.GetWindowThreadProcessId.argtypes = [W.HWND, C.POINTER(W.DWORD)]
    user.ShowWindow.argtypes = [W.HWND, C.c_int]
    user.SetForegroundWindow.argtypes = [W.HWND]
    user.SetWindowPos.argtypes = [W.HWND, W.HWND, C.c_int, C.c_int, C.c_int, C.c_int, W.UINT]
    callback = C.WINFUNCTYPE(W.BOOL, W.HWND, W.LPARAM)
    found = []

    @callback
    def visit(hwnd, _):
        pid = W.DWORD()
        user.GetWindowThreadProcessId(hwnd, C.byref(pid))
        if pid.value == process.pid and user.IsWindowVisible(hwnd):
            found.append(hwnd)
        return True

    deadline = time.monotonic()+timeout
    while process.poll() is None and time.monotonic() < deadline:
        user.EnumWindows(visit, 0)
        if found:
            hwnd = found[0]
            user.ShowWindow(hwnd, 9)  # SW_RESTORE
            foreground = bool(user.SetForegroundWindow(hwnd))
            # Windows may reject foreground focus from a background tool. Keep
            # this test's own window visible above others until it closes.
            visible = bool(user.SetWindowPos(hwnd, W.HWND(-1), 0, 0, 0, 0, 0x43))
            return {'supported': True, 'foreground_requested': foreground, 'visible_on_top': visible}
        time.sleep(.1)
    return {'supported': True, 'window_found': False}
