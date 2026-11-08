from pathlib import Path
import argparse
import hashlib,json,os,subprocess,time
from datetime import datetime, timezone
from package_playable import require_game_closed
r=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser(description='Build the C++ demo; all compiler caches stay in this project on D:.')
parser.add_argument('--build-dir',type=Path,default=Path('build'),help='Project-local build directory; e.g. cache/build-next')
parser.add_argument('--test',action='store_true',help='Run core, audio and hidden UI regressions after building')
parser.add_argument('--test-dir',type=Path,help='Isolated project-local working directory for tests, fixtures and reports')
options=parser.parse_args()
build_dir=(r/options.build_dir).resolve()
if not build_dir.is_relative_to(r):raise SystemExit('Build directory must stay inside this project')
test_dir=(r/options.test_dir).resolve() if options.test_dir else r
if not test_dir.is_relative_to(r):raise SystemExit('Test directory must stay inside this project')
# Never let a help/unknown-option query trigger a build. Protect running images
# in this validated output tree; never stop games in another checkpoint.
require_game_closed(target_directory=build_dir)
t=r/'third_party'; llvm=next(t.glob('llvm-mingw-*-ucrt-x86_64'))/'bin'; cmake=next(t.glob('cmake-*-windows-x86_64'))/'bin'/'cmake.exe'; ninja=t/'ninja/ninja.exe'
env=os.environ.copy();env['PATH']=str(llvm)+os.pathsep+env['PATH']
# Keep compiler scratch files and optional compiler caches beside this project.
# Configure child processes explicitly: direct Python invocation must behave the
# same as build.cmd, regardless of the user's Windows TEMP/TMP settings.
cache=r/'cache'
for names, directory in [
    (('TEMP','TMP','TMPDIR'), cache/'build-tmp'),
    (('CLANG_MODULE_CACHE_PATH',), cache/'clang-modules'),
    (('CCACHE_DIR',), cache/'ccache'),
    (('SCCACHE_DIR',), cache/'sccache'),
]:
    directory.mkdir(parents=True,exist_ok=True)
    for name in names:env[name]=str(directory)
print(f"Build temporary files: {env['TEMP']}",flush=True)
args=[str(cmake),'-S',str(r),'-B',str(build_dir),'-G','Ninja','-DCMAKE_BUILD_TYPE=Release','-DCMAKE_C_COMPILER='+str(llvm/'clang.exe'),'-DCMAKE_CXX_COMPILER='+str(llvm/'clang++.exe'),'-DCMAKE_MAKE_PROGRAM='+str(ninja)]

def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream,'sha256').hexdigest()

def sources():
    paths=[r/'CMakeLists.txt']
    for directory in ('include','src','tests'):
        paths.extend(path for path in (r/directory).rglob('*') if path.is_file())
    paths.extend((r/'tools').rglob('*.py'))
    # The patched VM is a real compiler input, including its ABI/budget headers.
    # Hash it with the game sources so a third-party edit cannot reuse old tests.
    paths.extend(path for path in (r/'third_party/squirrel-3.1-dnf').rglob('*') if path.is_file())
    paths.append(r/'third_party/dependencies.lock.json')
    paths.append(r.parent/'reverse-60us/integration/include/dnf_ani_render.hpp')
    paths.append(r.parent/'reverse-60us/integration/include/dnf_ani_clock.hpp')
    return {Path(os.path.relpath(path,r)).as_posix():digest(path) for path in sorted(paths)}

# Bind successful checks to actual source and executable bytes. A later failed
# invocation replaces the latest status with failed, so stale reports cannot
# masquerade as acceptance of a newly built binary.
build_dir.mkdir(parents=True,exist_ok=True)
started_ns=time.time_ns()
verification={'schema':1,'status':'running','started_utc':datetime.now(timezone.utc).isoformat(),
              'build_directory':build_dir.relative_to(r).as_posix(),
              'test_directory':test_dir.relative_to(r).as_posix(),
              'tests_requested':options.test,'sources':sources()}
verification_path=build_dir/'build-verification.json'
def record():
    verification_path.write_text(json.dumps(verification,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
record()
try:
    subprocess.run(args,check=True,env=env)
    subprocess.run([str(cmake),'--build',str(build_dir),'-j','6'],check=True,env=env)
    verification['binaries']={name:digest(build_dir/name) for name in
                              ('dnf_native.exe','dnf_skill_preview.exe','dnf_tests.exe','dnf_audio_tests.exe','dnf_ui_tests.exe','dnf_inspect.exe','SDL2.dll','libunwind.dll')}
    verification['compiled_libraries']={path.relative_to(build_dir).as_posix():digest(path)
        for path in sorted(build_dir.rglob('*')) if path.is_file() and path.suffix.lower() in ('.a','.lib','.pdb')}
    if options.test:
        test_dir.mkdir(parents=True,exist_ok=True)
        verification['test_pvf_before_sha256']=digest(r.parent/'DNF1031客户端/Script.pvf')
        subprocess.run([str(build_dir/'dnf_tests.exe'),str(r.parent/'DNF1031客户端')],check=True,env=env,cwd=test_dir)
        subprocess.run([str(build_dir/'dnf_audio_tests.exe'),str(r.parent/'DNF1031客户端'),str(test_dir/'reports/audio-tests.json')],check=True,env=env,cwd=test_dir)
        subprocess.run([str(build_dir/'dnf_ui_tests.exe'),str(r.parent/'DNF1031客户端'),str(test_dir/'reports/requested-ui')],check=True,env=env,cwd=test_dir)
        verification['reports']={}
        for path in sorted((test_dir/'reports').rglob('*.json')):
            if 'test-saves' in path.relative_to(test_dir/'reports').parts or path.stat().st_mtime_ns<started_ns:
                continue
            verification['reports'][path.relative_to(test_dir).as_posix()]=digest(path)
        verification['test_pvf_sha256']=digest(r.parent/'DNF1031客户端/Script.pvf')
        core_identity=json.loads((test_dir/'reports/test-content-identity.json').read_text(encoding='utf-8'))['identity']
        audio_identity=json.loads((test_dir/'reports/audio-tests.json').read_text(encoding='utf-8'))['content_identity']
        ui_identity=json.loads((test_dir/'reports/requested-ui/ui-runtime-tests.json').read_text(encoding='utf-8'))['content_identity']
        if (core_identity!=audio_identity or core_identity!=ui_identity or core_identity['pvf_sha256']!=verification['test_pvf_before_sha256'] or
                verification['test_pvf_before_sha256']!=verification['test_pvf_sha256']):
            raise RuntimeError('Core/audio/UI content identities or PVF bytes changed during testing')
        verification['test_content_identity']=core_identity
    if sources()!=verification['sources']:
        raise RuntimeError('Source inputs changed during the build/test invocation; coordinate writers and rebuild')
    if any(digest(build_dir/name)!=expected for name,expected in verification['binaries'].items()):
        raise RuntimeError('An executable changed during verification')
    if any(digest(build_dir/name)!=expected for name,expected in verification['compiled_libraries'].items()):
        raise RuntimeError('A compiled library changed during verification')
    verification['status']='pass' if options.test else 'build-only'
except BaseException as error:
    verification['status']='failed'
    verification['error']=str(error)
    raise
finally:
    verification['finished_utc']=datetime.now(timezone.utc).isoformat()
    record()
