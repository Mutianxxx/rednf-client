from pathlib import Path
import os, subprocess, shutil, hashlib, json
root=Path(__file__).resolve().parents[1]
base=root.parent/'attack_demo'
tool=Path('D:/dnf-rebuild/dnf-native-demo/third_party/llvm-mingw-20261006-ucrt-x86_64/bin')
env=os.environ.copy();env['PATH']=str(tool)+os.pathsep+env['PATH']
(root/'build').mkdir(exist_ok=True);(root/'reports').mkdir(exist_ok=True)
common=[str(tool/'x86_64-w64-mingw32-clang++.exe'),'-std=c++17','-O2','-DNOMINMAX','-DWIN32_LEAN_AND_MEAN','-I'+str(root/'include'),'-I'+str(base/'vendor'),'-I'+str(base/'vendor/SDL2'),'-Wall','-Wextra','-Wno-unused-function','-Wno-misleading-indentation']
for name in ['main','resources']:
    subprocess.run(common+['-c',str(root/f'src/{name}.cpp'),'-o',str(root/f'build/{name}.o')],env=env,check=True)
subprocess.run([common[0],str(root/'build/main.o'),str(root/'build/resources.o'),str(base/'vendor/libzlibstatic.a'),str(base/'vendor/libSDL2.dll.a'),'-lgdi32','-lbcrypt','-municode','-static-libstdc++','-o',str(root/'battle_demo.exe')],env=env,check=True)
for name in ['SDL2.dll','libunwind.dll']:shutil.copyfile(base/name,root/name)
files=[*root.glob('src/*'),*root.glob('include/dnf/*'),*root.glob('tools/*.py'),*root.glob('content/*.json'),*root.glob('content/cache/*'),root/'battle_demo.exe',root/'SDL2.dll',root/'libunwind.dll']
manifest=dict(compiler=common[0],source_client='DNF/DNF',sha256={p.relative_to(root).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in files if p.is_file()},borrowed_sources=['skill_lab_v3/src/resources.cpp','skill_lab_v3/src/canvas.hpp','monster_demo/include/dnf/shared_death.hpp'])
(root/'reports/build-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf8')
print(root/'battle_demo.exe')
