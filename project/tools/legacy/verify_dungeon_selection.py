"""Visible-window acceptance for dungeon selection using isolated character saves.

This verifier sends ordinary Windows messages to its own SDL window and reads
the runtime trace. Its level fixtures are prepared before launch; they do not
represent normal leveling or original-client behavior.
"""
from __future__ import annotations

import argparse
import ctypes as C
from ctypes import wintypes as W
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time
import traceback

from test_window import show_test_window


ROOT = Path(__file__).resolve().parents[1]
USER_SAVES = ROOT / "saves"
VK_LEFT = 0x25
VK_UP = 0x26
VK_RIGHT = 0x27
VK_DOWN = 0x28
VK_RETURN = 0x0D
VK_ESCAPE = 0x1B
VK_F12 = 0x7B


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def hashes(directory: Path) -> dict[str, str]:
    return {path.name: sha256(path) for path in directory.glob("*") if path.is_file()}


def fixture(level: int) -> dict:
    return {
        "schema": 4,
        "characters": [
            {
                "name": f"SelectGate{level}",
                "class": "swordman",
                "identity": {"job_id": 0, "growtype": 0, "awakening": 0},
                "level": level,
                "weapon": 0,
                "region_session": {
                    "version": 3,
                    "location": "entrance",
                    "player": {"id": 0, "x": 820, "y": 340, "hp": 180, "mp": 140, "dir": 1},
                },
            },
            *([None] * 19),
        ],
    }


class VisibleWindowRun:
    def __init__(self, binary: Path, report: Path, level: int, resolution: tuple[int, int], timeout: float,
                 keyboard_only: bool = False):
        self.binary = binary
        self.report = report
        self.level = level
        self.resolution = resolution
        self.timeout = timeout
        self.keyboard_only = keyboard_only
        self.save_dir = report / "saves"
        self.save_dir.mkdir(parents=True)
        self.save_path = self.save_dir / "characters.json"
        self.save_path.write_text(json.dumps(fixture(level), indent=2), encoding="utf-8")
        self.process: subprocess.Popen | None = None
        self.window = None
        self.stdout = None
        self.stderr = None
        self.points: list[dict] = []
        self.held: set[int] = set()
        self.pointer_methods: set[str] = set()

    @property
    def trace_dir(self) -> Path:
        return self.report / "trace"

    def launch(self) -> None:
        self.report.mkdir(parents=True, exist_ok=True)
        self.trace_dir.mkdir()
        self.stdout = (self.report / "stdout.log").open("w", encoding="utf-8")
        self.stderr = (self.report / "stderr.log").open("w", encoding="utf-8")
        width, height = self.resolution
        self.process = subprocess.Popen(
            [
                str(self.binary), "--save-dir", str(self.save_dir),
                "--report-dir", str(self.trace_dir), "--run-id",
                f"selection-l{self.level}-{width}x{height}", "--resolution",
                str(width), str(height), "--trace", "--quit-after", "900",
            ],
            cwd=ROOT,
            stdout=self.stdout,
            stderr=self.stderr,
        )
        self.user = C.windll.user32
        self.user.SetProcessDPIAware()
        self.user.PostMessageW.argtypes = [W.HWND, W.UINT, W.WPARAM, W.LPARAM]
        self.user.PostMessageW.restype = W.BOOL
        self.user.GetWindowThreadProcessId.argtypes = [W.HWND, C.POINTER(W.DWORD)]
        self.user.GetClientRect.argtypes = [W.HWND, C.POINTER(W.RECT)]
        self.user.GetForegroundWindow.restype = W.HWND
        self.window = self._find_window()
        window_report = show_test_window(self.process)
        (self.report / "test-window.json").write_text(json.dumps(window_report, indent=2), encoding="utf-8")
        if not window_report.get("visible_on_top", False):
            raise RuntimeError(f"Test window was not confirmed visible on top: {window_report}")
        time.sleep(0.3)
        self.wait(lambda state: state.get("screen") == 0, "character selection screen")

    def _find_window(self):
        callback = C.WINFUNCTYPE(W.BOOL, W.HWND, W.LPARAM)
        found = []

        @callback
        def visit(hwnd, _):
            pid = W.DWORD()
            self.user.GetWindowThreadProcessId(hwnd, C.byref(pid))
            if self.process and pid.value == self.process.pid and self.user.IsWindowVisible(hwnd):
                found.append(hwnd)
            return True

        deadline = time.monotonic() + 15
        while time.monotonic() < deadline:
            self.user.EnumWindows(visit, 0)
            if found:
                return found[0]
            if self.process.poll() is not None:
                raise RuntimeError(f"Application exited during startup: {self.process.returncode}")
            time.sleep(0.1)
        raise RuntimeError("No visible SDL test window found for this process")

    def state(self) -> dict | None:
        if self.process and self.process.poll() is not None:
            raise RuntimeError(f"Application exited unexpectedly: {self.process.returncode}")
        try:
            return json.loads((self.trace_dir / "live.json").read_text(encoding="utf-8"))
        except (FileNotFoundError, PermissionError, json.JSONDecodeError):
            return None

    def wait(self, predicate, label: str, seconds: float | None = None) -> dict:
        deadline = time.monotonic() + (self.timeout if seconds is None else seconds)
        while time.monotonic() < deadline:
            snapshot = self.state()
            if snapshot is not None and predicate(snapshot):
                return snapshot
            time.sleep(0.04)
        raise RuntimeError(f"Timed out waiting for {label}; last state: {self.state()}")

    def assert_stays(self, predicate, label: str, duration: float = 0.65) -> dict:
        trace_path = self.trace_dir / "live.json"
        before = trace_path.stat().st_mtime_ns
        deadline = time.monotonic() + duration
        refresh_deadline = time.monotonic() + max(duration, 3)
        refreshed = False
        last = None
        while time.monotonic() < deadline or not refreshed:
            last = self.state()
            if last is not None and not predicate(last):
                raise RuntimeError(f"{label} changed unexpectedly: {last}")
            try:
                refreshed = refreshed or trace_path.stat().st_mtime_ns != before
            except (FileNotFoundError, PermissionError):
                pass
            if time.monotonic() > refresh_deadline:
                raise RuntimeError(f"No fresh runtime trace while checking {label}")
            time.sleep(0.04)
        return last

    def key(self, keycode: int, down: bool = True) -> None:
        scan = self.user.MapVirtualKeyW(keycode, 0)
        flags = 1 | (scan << 16) | (0 if down else (1 << 30) | (1 << 31))
        if keycode in (VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN):
            flags |= 1 << 24
        message = 0x100 if down else 0x101
        if not self.user.PostMessageW(self.window, message, keycode, flags):
            raise RuntimeError(f"Could not post key message 0x{keycode:x}")
        if down:
            self.held.add(keycode)
        else:
            self.held.discard(keycode)

    def tap(self, keycode: int, delay: float = 0.06) -> None:
        self.key(keycode, True)
        time.sleep(delay)
        self.key(keycode, False)
        time.sleep(0.08)

    def client_size(self) -> tuple[int, int]:
        rect = W.RECT()
        if not self.user.GetClientRect(self.window, C.byref(rect)):
            raise RuntimeError("GetClientRect failed for the visible test window")
        return rect.right - rect.left, rect.bottom - rect.top

    def client_point(self, logical: tuple[float, float]) -> tuple[int, int]:
        width, height = self.client_size()
        scale = min(width / 800.0, height / 600.0)
        return (
            round((width - 800 * scale) / 2 + logical[0] * scale),
            round((height - 600 * scale) / 2 + logical[1] * scale),
        )

    def mouse_move(self, logical: tuple[float, float], label: str) -> dict:
        x, y = self.client_point(logical)
        packed = x | (y << 16)
        # SDL may drop standalone motion while this managed desktop denies
        # foreground cursor focus. The game now samples pointer coordinates
        # on button-down too, so use a non-activating right click as an explicit
        # synthetic coordinate probe.
        if not self.user.PostMessageW(self.window, 0x204, 2, packed):
            raise RuntimeError("Could not post right-button pointer sample")
        time.sleep(0.06)
        self.user.PostMessageW(self.window, 0x205, 0, packed)
        method = "WM_RBUTTONDOWN/UP coordinate sample; not physical pointer motion"
        self.pointer_methods.add(method)
        snapshot = self.wait(
            lambda value: isinstance(value.get("ui_mouse"), list)
            and len(value["ui_mouse"]) == 2
            and abs(value["ui_mouse"][0] - logical[0]) <= 2
            and abs(value["ui_mouse"][1] - logical[1]) <= 2,
            f"logical pointer conversion for {label}",
        )
        self.points.append({
            "label": label,
            "logical": list(logical),
            "client": [x, y],
            "client_size": list(self.client_size()),
            "trace_ui_mouse": snapshot["ui_mouse"],
            "input": method,
        })
        return snapshot

    def click(self, logical: tuple[float, float], label: str) -> None:
        x, y = self.client_point(logical)
        packed = x | (y << 16)
        self.user.PostMessageW(self.window, 0x200, 0, packed)
        if not self.user.PostMessageW(self.window, 0x201, 1, packed):
            raise RuntimeError(f"Could not post mouse click for {label}")
        time.sleep(0.06)
        self.user.PostMessageW(self.window, 0x202, 0, packed)
        time.sleep(0.12)

    def capture(self, name: str) -> Path:
        image = self.trace_dir / "manual.png"
        before = image.stat().st_mtime_ns if image.exists() else 0
        self.tap(VK_F12)
        deadline = time.monotonic() + 3
        while time.monotonic() < deadline:
            if image.exists() and image.stat().st_mtime_ns != before and image.stat().st_size > 0:
                data = image.read_bytes()
                if data.startswith(b"\x89PNG\r\n\x1a\n") and data.endswith(b"IEND\xaeB`\x82"):
                    (self.report / f"{name}.png").write_bytes(data)
                    return self.report / f"{name}.png"
            time.sleep(0.04)
        raise RuntimeError(f"No new framebuffer capture produced for {name}")

    def record(self, name: str, snapshot: dict | None = None) -> dict:
        snapshot = snapshot or self.state()
        if snapshot is None:
            raise RuntimeError(f"No live trace available at checkpoint {name}")
        test_mode = snapshot.get("world", {}).get("test_mode", {})
        if isinstance(test_mode, dict) and any(test_mode.values()):
            raise RuntimeError(f"Test mode was enabled during ordinary selection input: {test_mode}")
        self.points.append({"checkpoint": name, "state": snapshot})
        (self.report / "steps.json").write_text(json.dumps(self.points, indent=2), encoding="utf-8")
        return snapshot

    def enter_game(self) -> dict:
        if self.keyboard_only:
            self.tap(VK_RETURN)
        else:
            self.click((400, 545), "resume-character")
        game = self.wait(
            lambda state: state.get("screen") == 2 and state.get("location") == "entrance",
            "isolated entrance save",
        )
        if game.get("menu"):
            self.tap(VK_ESCAPE)
            game = self.wait(lambda state: state.get("screen") == 2 and not state.get("menu"), "game menu closed")
        self.record("entrance-ready", game)
        return game

    @staticmethod
    def card_point(selection: dict, dungeon_id: int) -> tuple[float, float]:
        cards = selection.get("cards")
        if not isinstance(cards, list):
            raise RuntimeError("Dungeon selection trace is missing card rectangles")
        index = next((i for i, card in enumerate(cards) if card.get("id") == dungeon_id), None)
        if index is None:
            raise RuntimeError(f"Dungeon card {dungeon_id} is absent from the selection trace")
        target = cards[index]
        for row in range(1, 8):
            for col in range(1, 8):
                x = target["x"] + target["width"] * col / 8
                y = target["y"] + target["height"] * row / 8
                covered = any(
                    later["x"] <= x < later["x"] + later["width"]
                    and later["y"] <= y < later["y"] + later["height"]
                    for later in cards[index + 1 :]
                )
                if not covered:
                    return x, y
        raise RuntimeError(f"No unobscured hit point found for dungeon card {dungeon_id}")

    def activate_card(self, dungeon_id: int, label: str) -> dict:
        if self.keyboard_only:
            return self.navigate_card(dungeon_id, label)
        snapshot = self.state()
        selection = snapshot.get("dungeon_selection", {})
        point = self.card_point(selection, dungeon_id)
        self.click(point, label)
        return self.wait(
            lambda state: state.get("dungeon_selection", {}).get("open")
            and state["dungeon_selection"].get("selected") == dungeon_id,
            f"dungeon {dungeon_id} selected",
        )

    @staticmethod
    def arrow_path(selection: dict, dungeon_id: int) -> list[tuple[int, int]]:
        cards = selection.get("cards", [])
        selected = selection.get("selected")
        centers = {
            card["id"]: (card["x"] + card["width"] / 2, card["y"] + card["height"] / 2)
            for card in cards
        }
        if selected not in centers or dungeon_id not in centers:
            raise RuntimeError(f"Source layout lacks selected/target cards: {selected}, {dungeon_id}")
        queue = [(selected, [])]
        visited = {selected}
        for current, path in queue:
            if current == dungeon_id:
                return path
            origin_x, origin_y = centers[current]
            for keycode in (VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT):
                best_id, best_distance = current, float("inf")
                for card in cards:
                    dx = centers[card["id"]][0] - origin_x
                    dy = centers[card["id"]][1] - origin_y
                    forward = {VK_LEFT: -dx, VK_RIGHT: dx, VK_UP: -dy, VK_DOWN: dy}[keycode]
                    distance = dx * dx + dy * dy
                    if forward > 0 and distance < best_distance:
                        best_id, best_distance = card["id"], distance
                if best_id not in visited:
                    visited.add(best_id)
                    queue.append((best_id, path + [(keycode, best_id)]))
        raise RuntimeError(f"No source-layout arrow route from {selected} to {dungeon_id}")

    def navigate_card(self, dungeon_id: int, label: str) -> dict:
        snapshot = self.state()
        for keycode, expected in self.arrow_path(snapshot["dungeon_selection"], dungeon_id):
            self.tap(keycode)
            snapshot = self.wait(
                lambda value: value.get("dungeon_selection", {}).get("open")
                and value["dungeon_selection"].get("selected") == expected,
                f"arrow navigation to dungeon {expected}",
            )
            self.points.append({"label": label, "input": "WM_KEYDOWN/UP arrow key",
                                "keycode": keycode, "expected_selected": expected})
        return snapshot

    def walk_until_open(self, direction: int, label: str) -> dict:
        deadline = time.monotonic() + self.timeout
        while time.monotonic() < deadline:
            current = self.state()
            if current and current.get("dungeon_selection", {}).get("open"):
                return self.record(label, current)
            self.key(direction)
            time.sleep(0.07)
            self.key(direction, False)
            time.sleep(0.04)
        raise RuntimeError(f"Could not open selection by walking to the source trigger: {self.state()}")

    def leave_trigger(self) -> dict:
        selection = self.state().get("dungeon_selection", {})
        if not selection.get("awaiting_exit"):
            raise RuntimeError(f"Cancel did not arm entrance-exit requirement: {selection}")
        deadline = time.monotonic() + self.timeout
        while time.monotonic() < deadline:
            current = self.state()
            if not current["dungeon_selection"].get("awaiting_exit"):
                return self.record("left-entrance-trigger", current)
            self.key(VK_LEFT)
            time.sleep(0.07)
            self.key(VK_LEFT, False)
            time.sleep(0.04)
        raise RuntimeError(f"Walking out of entrance trigger did not rearm selection: {self.state()}")

    def duplicate_enter(self) -> dict:
        self.tap(VK_RETURN)
        entered = self.wait(
            lambda state: state.get("location") == "dungeon"
            and isinstance(state.get("run"), dict)
            and state["run"].get("run", {}).get("dungeon"),
            "dungeon entry",
        )
        run = entered["run"]["run"]
        if run.get("dungeon") <= 0 or "seed" not in run:
            raise RuntimeError(f"Dungeon trace has no stable run identity: {run}")
        self.record("first-dungeon-entry", entered)
        for _ in range(4):
            self.key(VK_RETURN, True)
            time.sleep(0.025)
            self.key(VK_RETURN, False)
            time.sleep(0.025)
        time.sleep(0.7)
        stable = self.state()
        final = stable.get("run", {})
        final = final.get("run", {}) if isinstance(final, dict) else {}
        if stable.get("location") != "dungeon" or final.get("dungeon") != run["dungeon"] or final.get("seed") != run["seed"]:
            raise RuntimeError(f"Duplicate Enter replaced or exited the active run: before={run}, after={final}")
        self.record("single-run-after-duplicate-enter", stable)
        return stable

    def close(self) -> None:
        active_error = sys.exc_info()[0] is not None
        cleanup_error = None
        forced_termination = False
        try:
            if self.process and self.process.poll() is None:
                if self.window:
                    for keycode in tuple(self.held):
                        try:
                            self.key(keycode, False)
                        except RuntimeError as error:
                            cleanup_error = str(error)
                    self.user.PostMessageW(self.window, 0x10, 0, 0)
                try:
                    self.process.wait(timeout=15)
                except subprocess.TimeoutExpired:
                    forced_termination = True
                    self.process.terminate()
                    self.process.wait(timeout=5)
            exit_code = self.process.returncode if self.process else None
            if self.process and (forced_termination or exit_code != 0):
                cleanup_error = f"Own test process did not exit normally: exit={exit_code}, forced={forced_termination}"
            (self.report / "process-exit.json").write_text(json.dumps({
                "exit_code": exit_code,
                "forced_termination": forced_termination,
                "status": "pass" if self.process and exit_code == 0 and not forced_termination and not cleanup_error else "fail",
                "error": cleanup_error,
            }, indent=2), encoding="utf-8")
        finally:
            if self.stdout:
                self.stdout.close()
            if self.stderr:
                self.stderr.close()
        if cleanup_error and not active_error:
            raise RuntimeError(cleanup_error)


def level_one_case(binary: Path, report: Path, timeout: float, keyboard_only: bool = False) -> dict:
    run = VisibleWindowRun(binary, report, 1, (800, 600), timeout, keyboard_only)
    try:
        run.launch()
        initial = run.enter_game()
        if initial.get("progression", {}).get("level") != 1:
            raise RuntimeError(f"Level-1 fixture loaded at unexpected level: {initial.get('progression')}")
        opened = run.walk_until_open(VK_RIGHT, "level-one-selection-open")
        if not opened.get("dungeon_selection", {}).get("cards"):
            raise RuntimeError("Candidate does not export dungeon_selection card rectangles in live.json")
        selected = run.activate_card(1, "select-lorien")
        run.record("level-one-select-lorien", selected)
        run.capture("level-one-selected")

        if not keyboard_only:
            point_two = run.card_point(selected["dungeon_selection"], 2)
            hovered = run.mouse_move(point_two, "hover-lorien-inside")
            state = hovered["dungeon_selection"]
            if state.get("selected") != 1 or state.get("hovered") != 2:
                raise RuntimeError(f"Hover changed selection or missed card: {state}")
            run.record("hover-is-independent-of-selection", hovered)
            run.capture("hover-lorien-inside")

            blank = run.mouse_move((20, 20), "clear-hover")
            state = blank["dungeon_selection"]
            if state.get("selected") != 1 or state.get("hovered") != 0:
                raise RuntimeError(f"Pointer exit changed selected dungeon or retained hover: {state}")
            run.record("selection-retained-after-hover-exit", blank)
        else:
            blank = selected

        hover_before = blank["dungeon_selection"]["hovered"]
        run.tap(VK_UP)
        arrow_selected = run.wait(
            lambda value: value.get("dungeon_selection", {}).get("selected") == 2,
            "Up arrow selects Lorien Inside",
        )
        if not keyboard_only and arrow_selected["dungeon_selection"].get("hovered") != hover_before:
            raise RuntimeError("Arrow navigation changed the pointer hover state")
        run.record("up-arrow-selects-inside" if keyboard_only else "up-arrow-changes-selection-only", arrow_selected)
        run.capture("up-arrow-selection")

        for label in ("K", "I", "M"):
            run.tap(ord(label))
            snapshot = run.assert_stays(
                lambda value: value.get("dungeon_selection", {}).get("open")
                and not value.get("menu") and not value.get("skill_menu")
                and not value.get("map_menu") and value.get("panel") == 0,
                f"selection consumes {label} menu key",
            )
            if "map_menu" not in snapshot:
                raise RuntimeError("Candidate trace must expose map_menu for selection input-consumption verification")
            if snapshot.get("menu") or snapshot.get("skill_menu") or snapshot.get("map_menu") or snapshot.get("panel") != 0:
                raise RuntimeError(f"Selection key {label} opened a menu behind selection: {snapshot}")
            run.record(f"selection-consumes-{label.lower()}-menu-key", snapshot)
        run.capture("selection-consumes-menu-keys")

        selected_inside = run.activate_card(2, "select-lorien-inside-level-one")
        if selected_inside["dungeon_selection"].get("selected") != 2:
            raise RuntimeError("Could not select the level-2 dungeon card")
        run.tap(VK_RETURN)
        blocked = run.assert_stays(
            lambda value: value.get("dungeon_selection", {}).get("open")
            and value["dungeon_selection"].get("selected") == 2
            and value.get("location") == "entrance",
            "level-one Enter rejection",
        )
        run.record("level-one-enter-blocked", blocked)
        run.capture("level-one-gate-blocked")
        if not keyboard_only:
            enter_button = blocked["dungeon_selection"].get("enter_button")
            if not isinstance(enter_button, dict):
                raise RuntimeError("Selection trace is missing enter-button rectangle")
            run.click((enter_button["x"] + enter_button["width"] / 2,
                       enter_button["y"] + enter_button["height"] / 2), "level-one-enter-button")
            button_blocked = run.assert_stays(
                lambda value: value.get("location") == "entrance" and value.get("dungeon_selection", {}).get("open"),
                "level-one button rejection",
            )
            run.record("level-one-button-blocked", button_blocked)

        run.tap(VK_ESCAPE)
        cancelled = run.wait(
            lambda value: not value.get("dungeon_selection", {}).get("open"), "selection cancelled"
        )
        if not cancelled["dungeon_selection"].get("awaiting_exit"):
            raise RuntimeError(f"Cancel did not require leaving the entrance trigger: {cancelled['dungeon_selection']}")
        run.record("cancel-awaits-trigger-exit", cancelled)
        run.capture("cancelled-selection")
        time.sleep(0.45)
        run.tap(VK_RETURN)
        stayed_closed = run.assert_stays(
            lambda value: value.get("location") == "entrance"
            and not value.get("dungeon_selection", {}).get("open"),
            "cancelled selection remains closed",
        )
        run.record("no-reopen-before-leaving-trigger", stayed_closed)

        run.leave_trigger()
        run.walk_until_open(VK_RIGHT, "selection-reopened-after-reentry")
        run.capture("selection-after-reentry")
        selected_lorien = run.activate_card(1, "select-lorien-after-reentry")
        if selected_lorien["dungeon_selection"].get("selected") != 1:
            raise RuntimeError("Could not select Lorien after leaving and re-entering the trigger")
        run.capture("level-one-ready-to-enter")
        entered = run.duplicate_enter()
        if entered["run"]["run"].get("dungeon") != 1:
            raise RuntimeError(f"Level-one candidate entered the wrong dungeon: {entered['run']['run']}")
        run.capture("level-one-dungeon-entry")
        return {
            "status": "pass",
            "level_fixture": 1,
            "resolution": list(run.resolution),
            "input_mode": "keyboard-only" if keyboard_only else "keyboard-and-pointer",
            "minimum_level_rejection": {"dungeon": 2, "required_level": 2, "actual_level": 1, "enter_key": True,
                                        "enter_button": "unverified" if keyboard_only else True},
            "hover_selected_independence": "unverified" if keyboard_only else True,
            "pointer_verification": {"status": "unverified" if keyboard_only else "pass",
                                     "scope": "Pointer checks skipped in keyboard-only mode" if keyboard_only else "Synthetic window-message coordinates and hover only"},
            "high_dpi_verification": {"status": "unverified"},
            "pointer_methods": sorted(run.pointer_methods),
            "up_arrow_selects_inside": True,
            "up_arrow_selection_keeps_hover": "unverified" if keyboard_only else True,
            "selection_consumes_menu_keys": ["K", "I", "M"],
            "cancel_requires_exit_and_reentry": True,
            "duplicate_entry_single_run": True,
            "run_identity": {"dungeon": entered["run"]["run"]["dungeon"], "seed": entered["run"]["run"]["seed"]},
            "window_message_points": run.points,
        }
    finally:
        run.close()


def level_two_wide_case(binary: Path, report: Path, timeout: float, keyboard_only: bool = False) -> dict:
    run = VisibleWindowRun(binary, report, 2, (1280, 720), timeout, keyboard_only)
    try:
        run.launch()
        initial = run.enter_game()
        if initial.get("progression", {}).get("level") != 2:
            raise RuntimeError(f"Level-2 fixture loaded at unexpected level: {initial.get('progression')}")
        opened = run.walk_until_open(VK_RIGHT, "wide-level-two-selection-open")
        if not keyboard_only:
            selection = opened["dungeon_selection"]
            point = run.card_point(selection, 2)
            hover = run.mouse_move(point, "wide-hover-lorien-inside")
            if hover["dungeon_selection"].get("hovered") != 2:
                raise RuntimeError(f"Wide coordinate conversion did not hover dungeon 2: {hover}")
            run.record("wide-coordinate-conversion", hover)
            run.capture("wide-coordinate-hover")
        else:
            run.record("wide-keyboard-selection-open", opened)
            run.capture("wide-keyboard-selection-open")
        selected = run.activate_card(2, "wide-select-lorien-inside")
        if selected["dungeon_selection"].get("selected") != 2:
            raise RuntimeError(f"Wide-window input did not select dungeon 2: {selected}")
        run.record("wide-level-two-selected", selected)
        run.capture("wide-level-two-selected")
        entered = run.duplicate_enter()
        if entered["run"]["run"].get("dungeon") != 2:
            raise RuntimeError(f"Exact-minimum level fixture failed dungeon-2 admission: {entered['run']['run']}")
        run.capture("wide-level-two-dungeon-entry")
        return {
            "status": "pass",
            "level_fixture": 2,
            "resolution": list(run.resolution),
            "input_mode": "keyboard-only" if keyboard_only else "keyboard-and-pointer",
            "minimum_level_admission": {"dungeon": 2, "required_level": 2, "actual_level": 2},
            "wide_coordinate_conversion": {"status": "unverified"} if keyboard_only else [point for point in run.points if "client" in point],
            "pointer_verification": {"status": "unverified" if keyboard_only else "pass",
                                     "scope": "Pointer checks skipped in keyboard-only mode" if keyboard_only else "Synthetic window-message coordinates and hover only"},
            "high_dpi_verification": {"status": "unverified"},
            "pointer_methods": sorted(run.pointer_methods),
            "duplicate_entry_single_run": True,
            "run_identity": {"dungeon": entered["run"]["run"]["dungeon"], "seed": entered["run"]["run"]["seed"]},
            "window_message_points": run.points,
        }
    finally:
        run.close()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--binary", type=Path, default=ROOT / "build/dnf_native.exe")
    parser.add_argument("--report-dir", type=Path)
    parser.add_argument("--timeout", type=float, default=15)
    parser.add_argument("--keyboard-only", action="store_true",
                        help="Use Return and source-layout arrow navigation; skip pointer checks and report pointer/high-DPI verification as unverified")
    args = parser.parse_args()
    if os.name != "nt":
        parser.error("Visible SDL window verification requires Windows")
    binary = args.binary.resolve()
    if not binary.is_file():
        parser.error(f"Executable does not exist: {binary}")
    report = args.report_dir.resolve() if args.report_dir else ROOT / "reports/runs" / (
        "dungeon-selection-" + datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S%fZ")
    )
    runs_root = (ROOT / "reports/runs").resolve()
    try:
        report.relative_to(runs_root)
    except ValueError:
        parser.error(f"Report directory must be under {runs_root}")
    report.mkdir(parents=True, exist_ok=False)

    binary_hash = sha256(binary)
    user_before = hashes(USER_SAVES) if USER_SAVES.exists() else {}
    (report / "fixture-scope.json").write_text(json.dumps({
        "scope": "Two isolated character saves written before launch; level 1 and 2 are diagnostic entry fixtures, not normal level acquisition",
        "input": "PostMessageW keyboard events only; not physical-key or IME validation" if args.keyboard_only else "PostMessageW keyboard/mouse events to each visible application window; not physical-key or IME validation",
        "input_mode": "keyboard-only" if args.keyboard_only else "keyboard-and-pointer",
        "pointer_boundary": "Pointer checks skipped; cursor and coordinate conversion remain unverified" if args.keyboard_only else "Uses right-button point samples and records the synthetic method. Does not prove physical pointer motion or high-DPI scaling.",
        "layout": "Source-layout geometric arrow routes use live.json card rectangles; two window sizes are captured but pointer/high-DPI conversion is unverified" if args.keyboard_only else "Selection rectangles and state are read from live.json; 1280x720 pointer conversion is checked against the runtime ui_mouse trace",
        "original_client_parity": False,
        "user_save_hashes_before": user_before,
        "binary_sha256": binary_hash,
    }, indent=2), encoding="utf-8")

    result = {"status": "fail", "binary": str(binary), "binary_sha256": binary_hash,
              "input_mode": "keyboard-only" if args.keyboard_only else "keyboard-and-pointer",
              "pointer_verification": {"status": "unverified", "reason": "Keyboard-only mode" if args.keyboard_only else "Full pointer checks have not completed"},
              "high_dpi_verification": {"status": "unverified"},
              "report_directory": str(report.relative_to(ROOT)), "cases": []}
    try:
        result["cases"].append(level_one_case(binary, report / "level-one-800x600", args.timeout, args.keyboard_only))
        result["cases"].append(level_two_wide_case(binary, report / "level-two-1280x720", args.timeout, args.keyboard_only))
        result["status"] = "pass"
        if not args.keyboard_only:
            result["pointer_verification"] = {"status": "pass", "scope": "Synthetic pointer coordinates/hover; physical pointer and high-DPI excluded"}
    except Exception as error:
        result["error"] = str(error)
        result["traceback"] = traceback.format_exc()
    finally:
        user_after = hashes(USER_SAVES) if USER_SAVES.exists() else {}
        result["user_saves_unchanged"] = user_before == user_after
        result["changed_user_save_files"] = sorted(
            name for name in user_before.keys() | user_after.keys()
            if user_before.get(name) != user_after.get(name)
        )
        if not result["user_saves_unchanged"]:
            result["status"] = "fail"
        (report / "acceptance.json").write_text(json.dumps(result, indent=2), encoding="utf-8")
    print(json.dumps(result, indent=2), flush=True)
    return 0 if result["status"] == "pass" else 1


if __name__ == "__main__":
    raise SystemExit(main())
