"""Build from bundled SDK files with an external LLVM-MinGW compiler.
Usage: python demo/tools/build.py --toolchain C:/path/to/llvm-mingw/bin
Alternatively set LLVM_MINGW_BIN, or put the compiler on PATH.
"""
from pathlib import Path
import argparse, hashlib, json, os, shutil, subprocess

def main():
    a=argparse.ArgumentParser();a.add_argument('--toolchain',default=os.getenv('LLVM_MINGW_BIN'));args=a.parse_args()
    root=Path(__file__).resolve().parents[1];vendor=root.parent/'vendor';name='x86_64-w64-mingw32-clang++.exe'
    compiler=str(Path(args.toolchain)/name) if args.toolchain else shutil.which(name)
    if not compiler or not Path(compiler).is_file():raise SystemExit('LLVM-MinGW compiler required. Use --toolchain <bin> or LLVM_MINGW_BIN.')
    tool=Path(compiler).resolve().parent;env=os.environ.copy();env['PATH']=str(tool)+os.pathsep+env.get('PATH','')
    version=subprocess.check_output([compiler,'--version'],env=env,text=True).strip()
    (root/'build').mkdir(exist_ok=True);(root/'reports').mkdir(exist_ok=True)
    common=[compiler,'-std=c++17','-O2','-DNOMINMAX','-DWIN32_LEAN_AND_MEAN','-I'+str(root/'include'),'-I'+str(vendor),'-I'+str(vendor/'SDL2'),'-Wall','-Wextra','-Wno-unused-function','-Wno-misleading-indentation']
    for name in ['main','resources']:subprocess.run(common+['-c',str(root/f'src/{name}.cpp'),'-o',str(root/f'build/{name}.o')],env=env,check=True)
    subprocess.run([compiler,str(root/'build/main.o'),str(root/'build/resources.o'),str(vendor/'libzlibstatic.a'),str(vendor/'libSDL2.dll.a'),'-lgdi32','-lbcrypt','-municode','-static-libstdc++','-o',str(root/'battle_demo.exe')],env=env,check=True)
    for name in ['SDL2.dll','libunwind.dll']:shutil.copyfile(vendor/'runtime'/name,root/name)
    files=[*root.glob('src/*'),*root.glob('include/dnf/*'),*root.glob('tools/*.py'),*root.glob('content/*.json'),*root.glob('content/cache/*'),root/'battle_demo.exe',root/'SDL2.dll',root/'libunwind.dll']
    manifest=dict(compiler_version=version,compiler=compiler,source_client='client-assets (bound source version, subset original IMG)',
        sha256={p.relative_to(root).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in files if p.is_file()})
    (root/'reports/build-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf8')
    print('Built',root/'battle_demo.exe',flush=True)

if __name__=='__main__':main()
