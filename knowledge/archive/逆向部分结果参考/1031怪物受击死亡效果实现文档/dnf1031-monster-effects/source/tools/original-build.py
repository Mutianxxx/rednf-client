"""Build the independent 1031 monster-animation preview using local SDL2/LLVM."""
import argparse
import hashlib
import json
import os
import shutil
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
VENDOR = ROOT.parent / "attack_demo/vendor"
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--toolchain", type=Path, default=Path("D:/dnf-rebuild/dnf-native-demo/third_party/llvm-mingw-20261006-ucrt-x86_64/bin"))
args = parser.parse_args()
clang = args.toolchain / "x86_64-w64-mingw32-clang++.exe"
if not clang.is_file():
    raise SystemExit("LLVM-MinGW toolchain not found; pass --toolchain")
(ROOT / "build").mkdir(exist_ok=True)
(ROOT / "reports").mkdir(exist_ok=True)
env = os.environ.copy()
env["PATH"] = str(args.toolchain) + os.pathsep + env["PATH"]
common = [str(clang), "-std=c++17", "-O2", "-DNOMINMAX", "-DWIN32_LEAN_AND_MEAN", "-Iinclude",
          "-I" + str(VENDOR), "-I" + str(VENDOR / "SDL2"), "-Wall", "-Wextra", "-Wno-unused-function"]
for name in ("resources", "main"):
    subprocess.run(common + ["-c", f"src/{name}.cpp", "-o", f"build/{name}.o"], cwd=ROOT, env=env, check=True)
subprocess.run([str(clang), "build/main.o", "build/resources.o", str(VENDOR / "libzlibstatic.a"), str(VENDOR / "libSDL2.dll.a"),
                "-lgdi32", "-lbcrypt", "-lshell32", "-municode", "-mwindows", "-static-libstdc++", "-o", "monster_demo.exe"], cwd=ROOT, env=env, check=True)
for name in ("SDL2.dll", "libunwind.dll"):
    shutil.copyfile(ROOT.parent / "attack_demo" / name, ROOT / name)
files = [ROOT / name for name in ("monster_demo.exe", "SDL2.dll", "libunwind.dll", "src/main.cpp", "src/resources.cpp", "include/dnf/resources.hpp", "include/dnf/geometry.hpp", "include/dnf/shared_death.hpp", "content/monsters.json")]
report = dict(toolchain=str(clang), files={p.relative_to(ROOT).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in files})
(ROOT / "reports/build-manifest.json").write_text(json.dumps(report, ensure_ascii=False, indent=2), "utf-8")
print("Built:", ROOT / "monster_demo.exe")
