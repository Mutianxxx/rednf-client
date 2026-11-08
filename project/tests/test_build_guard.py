"""Mock-only safety checks. Never enumerate/stop real games or start a build."""
from __future__ import annotations

import ast
from contextlib import ExitStack
import hashlib
import importlib.util
import io
import json
from pathlib import Path, PureWindowsPath
import sys
import types
import unittest
from unittest.mock import patch


STAGING = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("staged_package_playable", STAGING / "tools/package_playable.py")
GUARD = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(GUARD)


def folded_parts(path):
    return tuple(part.casefold() for part in PureWindowsPath(str(path)).parts)


class GuardBoundaryTests(unittest.TestCase):
    def invoke(self, target, images, *, aliases=(), unresolved=()):
        self.resolutions = []
        unresolved = {folded_parts(path) for path in unresolved}

        def resolve(path, *, strict=False):
            self.resolutions.append((str(path), strict))
            parts = PureWindowsPath(str(path)).parts
            key = folded_parts(path)
            if key in unresolved:
                raise FileNotFoundError("Mock missing/unverifiable image")
            for alias, destination in aliases:
                prefix = folded_parts(alias)
                if key[:len(prefix)] == prefix:
                    return PureWindowsPath(destination).joinpath(*parts[len(prefix):])
            return PureWindowsPath(str(path))

        def query(pid):
            value = images[pid]
            if isinstance(value, BaseException):
                raise value
            return value

        with ExitStack() as stack:
            stack.enter_context(patch.object(GUARD, "running_game_pids", return_value=list(images)))
            stack.enter_context(patch.object(GUARD, "running_game_image", side_effect=query))
            stack.enter_context(patch.object(Path, "resolve", autospec=True, side_effect=resolve))
            return GUARD.require_game_closed(target_directory=target)

    def rejects(self, target, images, **kwargs):
        with self.assertRaises(RuntimeError) as failure:
            self.invoke(target, images, **kwargs)
        return str(failure.exception)

    def test_same_directory_blocks(self):
        message = self.rejects("D:/project/cache/build20", {11: "D:/project/cache/build20/dnf_native.exe"})
        self.assertIn("inside build directory", message)
        self.assertIn("11", message)

    def test_subdirectory_blocks(self):
        self.rejects("D:/project/cache/build20", {12: "D:/project/cache/build20/Release/dnf_native.exe"})

    def test_case_and_separator_variants_block(self):
        self.rejects("d:/PROJECT/cache/BUILD20", {13: "D:\\project\\CACHE\\build20\\DNF_NATIVE.EXE"})

    def test_different_immutable_checkpoint_allows(self):
        self.invoke("D:/project/cache/build20", {14: "D:/project/checkpoints/node19/runtime/dnf_native.exe"})
        self.assertEqual(self.resolutions[0], (str(Path("D:/project/cache/build20")), False))
        self.assertTrue(self.resolutions[-1][1], "Image existence/resolution must be strict")

    def test_sibling_prefix_is_not_a_child(self):
        self.invoke("D:/project/cache/build20", {15: "D:/project/cache/build20-old/dnf_native.exe"})

    def test_different_drive_allows(self):
        self.invoke("D:/project/cache/build20", {16: "E:/checkpoints/node19/runtime/dnf_native.exe"})

    def test_resolved_target_junction_blocks(self):
        self.rejects("D:/project/cache/build-link", {17: "D:/project/cache/actual/Release/dnf_native.exe"},
                     aliases=[("D:/project/cache/build-link", "D:/project/cache/actual")])

    def test_resolved_executable_junction_blocks(self):
        self.rejects("D:/project/cache/build20", {18: "D:/project/launch-link/dnf_native.exe"},
                     aliases=[("D:/project/launch-link", "D:/project/cache/build20")])

    def test_separate_resolved_checkpoint_junction_allows(self):
        self.invoke("D:/project/cache/build-link", {19: "D:/project/checkpoint-link/dnf_native.exe"},
                    aliases=[("D:/project/cache/build-link", "D:/project/cache/build20"),
                             ("D:/project/checkpoint-link", "D:/project/checkpoints/node19/runtime")])

    def test_extended_dos_prefix_cannot_hide_same_directory(self):
        self.rejects("D:/project/cache/build20", {20: "\\\\?\\D:\\project\\cache\\build20\\dnf_native.exe"})

    def test_extended_unc_prefix_cannot_hide_same_directory(self):
        self.rejects("\\\\server\\share\\build20", {21: "\\\\?\\UNC\\server\\share\\build20\\dnf_native.exe"})

    def test_access_denied_pid_blocks(self):
        message = self.rejects("D:/project/cache/build20", {22: PermissionError("Mock query access denied")})
        self.assertIn("cannot verify running image", message)
        self.assertIn("22", message)

    def test_exited_pid_blocks(self):
        self.rejects("D:/project/cache/build20", {23: ProcessLookupError("Mock process exited after enumeration")})

    def test_unknown_pid_alongside_separate_checkpoint_still_blocks(self):
        self.rejects("D:/project/cache/build20", {24: "D:/project/checkpoints/node19/runtime/dnf_native.exe",
                                                25: OSError("Mock inaccessible image")})

    def test_unresolvable_image_blocks(self):
        image = "D:/project/checkpoints/node19/runtime/dnf_native.exe"
        self.rejects("D:/project/cache/build20", {26: image}, unresolved=[image])

    def test_default_packaging_blocks_every_game_without_path_queries(self):
        with patch.object(GUARD, "running_game_pids", return_value=[27]), \
             patch.object(GUARD, "running_game_image", side_effect=AssertionError("Default packaging must stay strict")), \
             patch.object(Path, "resolve", side_effect=AssertionError("No path exception for default packaging")):
            with self.assertRaisesRegex(RuntimeError, "before packaging.*27"):
                GUARD.require_game_closed()

    def test_no_game_allows_default_and_target_without_queries(self):
        with patch.object(GUARD, "running_game_pids", return_value=[]), \
             patch.object(GUARD, "running_game_image", side_effect=AssertionError("No process to query")):
            GUARD.require_game_closed()
            GUARD.require_game_closed(target_directory=Path("D:/project/cache/build20"))

    def test_enumeration_failure_blocks(self):
        with patch.object(GUARD, "running_game_pids", side_effect=OSError("Mock enumeration failed")), \
             patch.object(GUARD, "running_game_image", side_effect=AssertionError("No known PID")):
            with self.assertRaises(OSError):
                GUARD.require_game_closed(target_directory=Path("D:/project/cache/build20"))


class FakeFunction:
    def __init__(self, callback):
        self.callback = callback
        self.argtypes = None
        self.restype = None

    def __call__(self, *args):
        return self.callback(*args)


class FakeKernel:
    def __init__(self, *, image="D:/project/checkpoints/node19/runtime/dnf_native.exe", open_ok=True, query_ok=True):
        self.calls = []
        self.image, self.open_ok, self.query_ok = image, open_ok, query_ok
        self.handle = 0x1234567887654321
        self.OpenProcess = FakeFunction(self.open)
        self.QueryFullProcessImageNameW = FakeFunction(self.query)
        self.CloseHandle = FakeFunction(self.close)

    def open(self, access, inherit, pid):
        self.calls.append(("open", access, inherit, pid))
        return self.handle if self.open_ok else None

    def query(self, handle, flags, buffer, length):
        self.calls.append(("query", handle, flags, length._obj.value))
        if not self.query_ok:
            return 0
        buffer.value = self.image
        length._obj.value = len(self.image)
        return 1

    def close(self, handle):
        self.calls.append(("close", handle))
        return 1


class QueryApiTests(unittest.TestCase):
    def query(self, kernel):
        with patch.object(GUARD, "os", types.SimpleNamespace(name="nt")), \
             patch.object(GUARD.ctypes, "WinDLL", create=True, return_value=kernel), \
             patch.object(GUARD.ctypes, "get_last_error", create=True, return_value=5), \
             patch.object(GUARD.ctypes, "WinError", create=True, side_effect=lambda code: OSError(code, "Mock Windows API failure")):
            return GUARD.running_game_image(81)

    def test_query_only_access_and_handle_width(self):
        kernel = FakeKernel()
        self.assertEqual(self.query(kernel), kernel.image)
        self.assertEqual(kernel.calls[0], ("open", 0x1000, False, 81))
        self.assertEqual(kernel.calls[1], ("query", kernel.handle, 0, 32768))
        self.assertEqual(kernel.calls[-1], ("close", kernel.handle))
        self.assertIs(kernel.OpenProcess.restype, GUARD.wintypes.HANDLE)
        self.assertIs(kernel.QueryFullProcessImageNameW.argtypes[0], GUARD.wintypes.HANDLE)

    def test_open_failure_is_not_treated_as_a_different_checkpoint(self):
        kernel = FakeKernel(open_ok=False)
        with self.assertRaises(OSError):
            self.query(kernel)
        self.assertEqual(len(kernel.calls), 1)

    def test_query_failure_closes_handle_and_rejects(self):
        kernel = FakeKernel(query_ok=False)
        with self.assertRaises(OSError):
            self.query(kernel)
        self.assertEqual(kernel.calls[-1], ("close", kernel.handle))

    def test_relative_image_is_not_verified(self):
        kernel = FakeKernel(image="runtime/dnf_native.exe")
        with self.assertRaises(RuntimeError):
            self.query(kernel)
        self.assertEqual(kernel.calls[-1], ("close", kernel.handle))

    def test_reused_pid_with_another_image_is_not_verified(self):
        kernel = FakeKernel(image="D:/project/checkpoints/node19/runtime/other.exe")
        with self.assertRaises(RuntimeError):
            self.query(kernel)
        self.assertEqual(kernel.calls[-1], ("close", kernel.handle))

    def test_empty_image_is_not_verified(self):
        kernel = FakeKernel(image="")
        with self.assertRaises(RuntimeError):
            self.query(kernel)
        self.assertEqual(kernel.calls[-1], ("close", kernel.handle))


class BuildIntegrationTests(unittest.TestCase):
    def test_guard_receives_validated_directory_before_any_build_process(self):
        source = (STAGING / "tools/build.py").read_text(encoding="utf-8")
        tree = ast.parse(source)
        guards = [node for node in ast.walk(tree) if isinstance(node, ast.Call)
                  and isinstance(node.func, ast.Name) and node.func.id == "require_game_closed"]
        self.assertEqual(len(guards), 1)
        self.assertEqual(guards[0].args, [])
        self.assertEqual([(item.arg, ast.unparse(item.value)) for item in guards[0].keywords],
                         [("target_directory", "build_dir")])
        validation = source.index("if not build_dir.is_relative_to(r):")
        self.assertLess(validation, source.index("require_game_closed(target_directory=build_dir)"))
        self.assertLess(guards[0].lineno, min(node.lineno for node in ast.walk(tree)
                        if isinstance(node, ast.Call) and isinstance(node.func, ast.Attribute)
                        and isinstance(node.func.value, ast.Name) and node.func.value.id == "subprocess"
                        and node.func.attr == "run"))


if __name__ == "__main__":
    output = io.StringIO()
    suite = unittest.defaultTestLoader.loadTestsFromModule(sys.modules[__name__])
    result = unittest.TextTestRunner(stream=output, verbosity=2).run(suite)
    report_directory = STAGING / "reports"
    report_directory.mkdir(exist_ok=True)
    (report_directory / "mock-tests.log").write_text(output.getvalue(), encoding="utf-8")
    inputs = [STAGING / "tools/package_playable.py", STAGING / "tools/build.py", Path(__file__)]
    summary = {"schema": 1, "status": "pass" if result.wasSuccessful() else "failed",
               "tests_run": result.testsRun, "failures": len(result.failures), "errors": len(result.errors),
               "process_enumeration": "mocked", "process_image_query": "mocked",
               "junction_resolution": "mocked", "build_started": False, "game_started_or_stopped": False,
               "python": sys.executable,
               "sources": [{"path": path.relative_to(STAGING).as_posix(),
                            "sha256": hashlib.sha256(path.read_bytes()).hexdigest()} for path in inputs]}
    (report_directory / "mock-tests.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    sys.stdout.write(output.getvalue())
    print(json.dumps(summary, indent=2))
    raise SystemExit(0 if result.wasSuccessful() else 1)
