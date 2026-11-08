"""Package an existing Windows build without building or launching the game.

Run from any directory: python tools/package_playable.py
Only the named release files are replaced; existing unrelated files are kept.
"""
from __future__ import annotations

import ctypes
from ctypes import wintypes
from datetime import datetime
import hashlib
import json
import os
from pathlib import Path, PureWindowsPath
import shutil
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[1]
PAYLOAD = ("dnf_native.exe", "SDL2.dll", "libunwind.dll")
LAUNCHER = """@echo off
setlocal
cd /d "%~dp0.."
"%~dp0dnf_native.exe" %*
set "_dnf_exit=%errorlevel%"
if not "%_dnf_exit%"=="0" (
    echo Game exited with code %_dnf_exit%. See README.txt and ../reports/runs/.
    pause
)
exit /b %_dnf_exit%
"""
README = """DNF C++ / SDL2 男鬼剑士洛兰测试版
本地发布时间：{created}

启动
双击本目录的 play.cmd，启动不需要 Python 或编译器。
开始操作前，请先切换到英文输入法。输入法兼容问题暂不列入本轮修复。
命令行可传递参数，例如：play.cmd --resolution 1280 720
指定其他原客户端位置：play.cmd --client "D:\\你的原客户端目录"

资源与目录
这是本地可玩程序目录，不是独立资源包。默认仍需工程目录同级的
../DNF1031客户端，内含完整 Script.pvf、NPK、音乐及其他原客户端资源。
原客户端只读。请保持 playable 与 build 同级，不要单独移动 playable。
程序以 exe 的两级父目录（dnf-native-demo）为工作目录。
本目录已包含 SDL2.dll 和 libunwind.dll；不需要用 Python 启动游戏。

测试路线
鼠标创建或选择男鬼剑士（20 槽，分两页）→ 赛利亚房间向南出口 →
艾尔文防线向右 → 洛兰入口向右选择进入（入口也可按 Enter）→
地下城按原 DGN 候选生成房间，清怪后沿小地图和开放的门继续探索，
击败首领后可结算返回。当前开放洛兰与洛兰深处，特殊任务房间仍有限制。

操作
方向键移动；连续按同一水平方向奔跑。
X 普通攻击；C 跳跃；下+C 后跳。
Z 技能指令终结，部分指令使用 X 或 Space。
A S D F G H Q W E R T Y 为技能快捷键；Space 默认后备格挡。
K 技能与快捷键配置；I 物品栏；L 任务；M 地图；Esc 菜单或关闭面板。
靠近地面掉落物按 X 拾取；掉落牌上的 P 是参考截图中的标记。
靠近赛利亚按 Enter 对话。
城镇其他 NPC 与通关后的德利拉同样可靠近按 Enter，或点击人物交谈。
物品栏：切换装备／消耗品等分类，鼠标右键或双击穿戴；右键装备槽卸下。
装扮页与场景共用实际衣物、皮肤和武器外观；「试穿」可组合七项源装扮，
仅预览，不增加背包物品、不改变属性或存档；「还原」撤销试穿。
在 NPC 商店选择「背包 / 出售」后，右键背包物品出售一件。
连突刺需先跑攻；银光落刃与空中连斩需在空中；
三段斩、月光斩与空中连斩需续段输入；格挡需保持按键。
崩山击按住可延长跳跃；基础鬼剑士保留剑光和斩击，狂战士血气旺盛的
派生冲击波不默认赠送。银光落刃达到足够高度时才有落地冲击组合。
Esc 菜单可调整分辨率、全屏、垂直同步及返回选角。
F8 保存反馈包；F12 截图；F3 调试信息。正常游玩以实际装备决定武器外观。
F5 恢复 HP/MP；F6 重载场景，属于调试操作，不属于普通流程验收。

共享存档与报告
与原 build/play.cmd 共享 dnf-native-demo/saves/characters.json，
不会另建用户角色副本，也不会在发布时复制或覆盖存档。
正常关闭窗口和返回选角会保存；有效旧档备份为 characters.bak.json。
显示设置同在 saves 内；运行报告、截图与反馈包在 reports/runs 内。
如需隔离存档，可传 --save-dir "其他存档目录"。

当前范围
未转职男鬼剑士、13 项基础技能及洛兰/洛兰深处房间流程。
已接入本地区任务、NPC 商店、维修、装备、药水及地面掉落，
两地下城普通候选共33张，旧救援5.map与门型不兼容7.map仅保留来源，
没有凭空连接。金库、邮件、活动商店和袖珍罐服务尚未开放。
相关窗口还需要按原客户端截图继续还原。
页面、UI、地图和图层仍需继续对照原客户端，视觉尚未全体验收。
普通攻击、技能动画、武器层、遮挡与时序仍需实际核对。
本发布脚本只复制已有构建和记录哈希，不运行测试，也不宣称测试通过。
伤害使用 demo 训练参数；装备、防御、异常、成长与完整原版公式未完成。
四转职、觉醒、TP、其他地区任务和完整原客户端内容仍未完成。
"""


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def running_game_pids() -> list[int]:
    """Enumerate all Windows processes; fail closed if enumeration fails."""
    if os.name != "nt":
        raise RuntimeError("Packaging requires Windows process enumeration.")

    class ProcessEntry(ctypes.Structure):
        _fields_ = [
            ("dwSize", wintypes.DWORD), ("cntUsage", wintypes.DWORD),
            ("th32ProcessID", wintypes.DWORD), ("th32DefaultHeapID", ctypes.c_size_t),
            ("th32ModuleID", wintypes.DWORD), ("cntThreads", wintypes.DWORD),
            ("th32ParentProcessID", wintypes.DWORD), ("pcPriClassBase", wintypes.LONG),
            ("dwFlags", wintypes.DWORD), ("szExeFile", wintypes.WCHAR * 260),
        ]

    kernel = ctypes.WinDLL("kernel32", use_last_error=True)
    kernel.CreateToolhelp32Snapshot.argtypes = (wintypes.DWORD, wintypes.DWORD)
    kernel.CreateToolhelp32Snapshot.restype = wintypes.HANDLE
    for name in ("Process32FirstW", "Process32NextW"):
        function = getattr(kernel, name)
        function.argtypes = (wintypes.HANDLE, ctypes.POINTER(ProcessEntry))
        function.restype = wintypes.BOOL
    kernel.CloseHandle.argtypes = (wintypes.HANDLE,)
    kernel.CloseHandle.restype = wintypes.BOOL
    handle = kernel.CreateToolhelp32Snapshot(0x00000002, 0)  # TH32CS_SNAPPROCESS
    if handle == ctypes.c_void_p(-1).value:
        raise ctypes.WinError(ctypes.get_last_error())
    try:
        entry = ProcessEntry()
        entry.dwSize = ctypes.sizeof(entry)
        found = []
        ok = kernel.Process32FirstW(handle, ctypes.byref(entry))
        while ok:
            if entry.szExeFile.casefold() == "dnf_native.exe":
                found.append(int(entry.th32ProcessID))
            ok = kernel.Process32NextW(handle, ctypes.byref(entry))
        error = ctypes.get_last_error()
        if error != 18:  # ERROR_NO_MORE_FILES
            raise ctypes.WinError(error)
        return found
    finally:
        kernel.CloseHandle(handle)


def running_game_image(pid: int) -> str:
    """Read an enumerated game's image using query-only process access."""
    if os.name != "nt":
        raise RuntimeError("Game image verification requires Windows.")
    kernel = ctypes.WinDLL("kernel32", use_last_error=True)
    kernel.OpenProcess.argtypes = (wintypes.DWORD, wintypes.BOOL, wintypes.DWORD)
    kernel.OpenProcess.restype = wintypes.HANDLE
    kernel.QueryFullProcessImageNameW.argtypes = (
        wintypes.HANDLE, wintypes.DWORD, wintypes.LPWSTR, ctypes.POINTER(wintypes.DWORD))
    kernel.QueryFullProcessImageNameW.restype = wintypes.BOOL
    kernel.CloseHandle.argtypes = (wintypes.HANDLE,)
    kernel.CloseHandle.restype = wintypes.BOOL
    handle = kernel.OpenProcess(0x1000, False, pid)  # PROCESS_QUERY_LIMITED_INFORMATION
    if not handle:
        raise ctypes.WinError(ctypes.get_last_error())
    try:
        capacity = 32768  # Windows extended-length path capacity, including NUL.
        buffer = ctypes.create_unicode_buffer(capacity)
        length = wintypes.DWORD(capacity)
        if not kernel.QueryFullProcessImageNameW(handle, 0, buffer, ctypes.byref(length)):
            raise ctypes.WinError(ctypes.get_last_error())
        image = buffer.value
        path = PureWindowsPath(image)
        if not length.value or not path.is_absolute() or path.name.casefold() != "dnf_native.exe":
            raise RuntimeError(f"PID {pid} has no verifiable absolute dnf_native.exe image path.")
        return image
    finally:
        kernel.CloseHandle(handle)


def _resolved_windows_parts(path: Path | str, *, strict: bool) -> tuple[str, ...]:
    """Resolve junctions/symlinks before case-insensitive component comparison."""
    resolved = str(Path(path).resolve(strict=strict))
    # realpath can retain an extended-length prefix if the input already had it.
    # Compare DOS and extended spellings of the same resolved path identically.
    if resolved.casefold().startswith("\\\\?\\unc\\"):
        resolved = "\\\\" + resolved[8:]
    elif resolved.startswith("\\\\?\\"):
        resolved = resolved[4:]
    canonical = PureWindowsPath(resolved)
    if not canonical.is_absolute():
        raise RuntimeError(f"Cannot verify an absolute resolved Windows path: {path}")
    return tuple(part.casefold() for part in canonical.parts)


def require_game_closed(target_directory: Path | None = None) -> None:
    """Keep packaging strict; allow builds only away from verified game images.

    A build caller must validate its output directory before passing it here.
    Unreadable/exited/reused PIDs or unresolved image paths fail closed. This
    observes current processes; it never stops them or skips verification.
    """
    pids = running_game_pids()
    if not pids:
        return
    if target_directory is None:
        raise RuntimeError("Close dnf_native.exe before packaging; running PIDs: " +
                           ", ".join(map(str, pids)))
    target = _resolved_windows_parts(target_directory, strict=False)
    blocked, unknown = [], []
    for pid in pids:
        try:
            image = running_game_image(pid)
            executable = _resolved_windows_parts(image, strict=True)
        except (OSError, RuntimeError, ValueError) as error:
            unknown.append(f"{pid} ({error})")
            continue
        if executable[:len(target)] == target:
            blocked.append(str(pid))
    if blocked or unknown:
        details = []
        if blocked:
            details.append("running image inside build directory, PIDs: " + ", ".join(blocked))
        if unknown:
            details.append("cannot verify running image, PIDs: " + ", ".join(unknown))
        raise RuntimeError(f"Cannot write build directory {target_directory}; " + "; ".join(details))


def package() -> Path:
    require_game_closed()
    build = ROOT / "build"
    release = ROOT / "playable"
    if release.resolve() != release:
        raise RuntimeError("playable must be a real directory directly under the project.")
    for name in PAYLOAD:
        if not (build / name).is_file():
            raise FileNotFoundError(f"Missing build/{name}; finish the build first.")

    # Stage all bytes before replacing release files. The existing directory,
    # unrelated files, saves and reports are never removed or copied.
    with tempfile.TemporaryDirectory(prefix=".package-playable-", dir=ROOT) as temporary:
        staging = Path(temporary)
        source_hashes = {}
        for name in PAYLOAD:
            source_hashes[name] = sha256(build / name)
            shutil.copy2(build / name, staging / name)
            if sha256(staging / name) != source_hashes[name]:
                raise RuntimeError(f"Source changed while copying build/{name}; retry after build finishes.")
        created = datetime.now().astimezone()
        (staging / "play.cmd").write_bytes(LAUNCHER.replace("\n", "\r\n").encode("ascii"))
        (staging / "README.txt").write_bytes(
            README.format(created=created.isoformat(timespec="seconds"))
            .replace("\n", "\r\n").encode("utf-8-sig"))
        file_names = (*PAYLOAD, "play.cmd", "README.txt")
        manifest = {
            "schema": 1,
            "product": "DNF C++ SDL2 Swordman/Lorien local playable demo",
            "version_date": created.date().isoformat(),
            "created_at": created.isoformat(timespec="seconds"),
            "source_binary": {"path": "build/dnf_native.exe", "sha256": source_hashes["dnf_native.exe"]},
            "files": [{"path": name, "size": (staging / name).stat().st_size,
                       "sha256": sha256(staging / name)} for name in file_names],
            "manifest_hash_scope": "All payload files; manifest.json excludes itself to avoid a self-referential hash.",
            "standalone_resource_package": False,
            "dependencies": {
                "platform": "Windows x64",
                "bundled_runtime": ["SDL2.dll", "libunwind.dll"],
                "external_client_default": "../DNF1031客户端 (relative to dnf-native-demo)",
                "external_client_override": "--client PATH",
                "external_resources": "Complete original PC client: Script.pvf, NPK, music and other referenced files; read-only.",
                "python_required_to_play": False,
            },
            "working_directory": "Executable parent.parent = dnf-native-demo; keep playable beside build.",
            "shared_user_saves": "dnf-native-demo/saves; not copied or changed by packaging.",
            "verification": "Packaging only; no build or game tests executed; complete visual acceptance pending.",
        }
        (staging / "manifest.json").write_text(
            json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        for name, expected in source_hashes.items():
            if sha256(build / name) != expected:
                raise RuntimeError(f"build/{name} changed during packaging; retry after build finishes.")
        require_game_closed()
        release.mkdir(exist_ok=True)
        for name in (*file_names, "manifest.json"):
            os.replace(staging / name, release / name)
    return release


if __name__ == "__main__":
    try:
        destination = package()
    except (OSError, RuntimeError) as error:
        print(f"Packaging failed: {error}", file=sys.stderr)
        raise SystemExit(1)
    print(f"Packaged existing build: {destination}")
    print(f"Launch: {destination / 'play.cmd'}")
