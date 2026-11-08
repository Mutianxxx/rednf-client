"""Build this package's exact reference sources without sibling demo projects."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--toolchain", type=Path, required=True, help="LLVM-MinGW bin directory")
    args = parser.parse_args()
    compiler = args.toolchain.resolve() / "x86_64-w64-mingw32-clang++.exe"
    if not compiler.is_file():
        parser.error("x86_64-w64-mingw32-clang++.exe not found")
    build = ROOT / "build"
    build.mkdir(exist_ok=True)
    env = os.environ.copy()
    env["PATH"] = str(compiler.parent) + os.pathsep + env.get("PATH", "")
    vendor = ROOT / "vendor"
    common = [str(compiler), "-std=c++17", "-O2", "-DNOMINMAX", "-DWIN32_LEAN_AND_MEAN",
              "-I" + str(ROOT / "source/include"), "-I" + str(vendor),
              "-I" + str(vendor / "SDL2"), "-Wall", "-Wextra", "-Wno-unused-function"]
    for name in ("resources", "main"):
        subprocess.run(common + ["-c", str(ROOT / f"source/src/{name}.cpp"),
                                 "-o", str(build / f"{name}.o")], env=env, check=True)
    subprocess.run([str(compiler), str(build / "main.o"), str(build / "resources.o"),
                    str(vendor / "libzlibstatic.a"), str(vendor / "libSDL2.dll.a"),
                    "-lgdi32", "-lbcrypt", "-lshell32", "-municode", "-mwindows",
                    "-static-libstdc++", "-o", str(build / "monster_demo.exe")], env=env, check=True)
    (build / "content").mkdir(exist_ok=True)
    shutil.copyfile(ROOT / "data/monsters.json", build / "content/monsters.json")
    for name in ("SDL2.dll", "libunwind.dll"):
        shutil.copyfile(vendor / "runtime" / name, build / name)
    print(build / "monster_demo.exe")

if __name__ == "__main__":
    main()
