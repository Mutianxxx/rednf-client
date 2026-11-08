"""Build only the offline helper from the delivered source and vendor files."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
from common import ROOT, WORK


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', required=True, help='Windows x64 LLVM-MinGW clang++ executable')
    parser.add_argument('--out', default=str(ROOT/'bin/ui_assets.exe'))
    args = parser.parse_args()
    compiler = Path(args.compiler).resolve()
    environment = os.environ.copy()
    environment['PATH'] = str(compiler.parent)+os.pathsep+environment.get('PATH', '')
    vendor = WORK/'attack_demo/vendor'
    output = Path(args.out).resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run([str(compiler), '-std=c++17', '-O2', '-DNOMINMAX', '-DWIN32_LEAN_AND_MEAN',
        '-I'+str(WORK/'monster_demo/include'), '-I'+str(vendor), str(ROOT/'src/assets.cpp'),
        str(WORK/'monster_demo/src/resources.cpp'), str(vendor/'libzlibstatic.a'),
        '-municode', '-static-libstdc++', '-o', str(output)],
        cwd=ROOT, env=environment, check=True)
    runtime = ROOT/'bin/libunwind.dll'
    if (output.parent/runtime.name).resolve() != runtime.resolve():
        shutil.copyfile(runtime, output.parent/runtime.name)


if __name__ == '__main__':
    main()
