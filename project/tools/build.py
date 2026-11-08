"""Build the isolated refactor; record exact inputs and run headless regressions."""
from pathlib import Path
from datetime import datetime, timezone
from concurrent.futures import ThreadPoolExecutor, as_completed
import argparse, hashlib, json, os, subprocess, sys, time, shutil
from legacy.package_playable import require_game_closed

ROOT = Path(__file__).resolve().parents[1]

def digest(path):
    with path.open('rb') as stream: return hashlib.file_digest(stream, 'sha256').hexdigest()

def input_hashes():
    paths = [ROOT/'CMakeLists.txt', ROOT/'content-profile.json']
    for directory in ('include','src','tests','cmake'):
        paths.extend(p for p in (ROOT/directory).rglob('*') if p.is_file())
    paths.extend(p for p in (ROOT/'tools').glob('*.py'))
    for directory in ('squirrel-3.1-dnf','zlib-1.3.1','native-contracts'):
        paths.extend(p for p in (ROOT/'third_party'/directory).rglob('*') if p.is_file())
    paths.extend(p for p in (ROOT/'third_party').glob('*') if p.is_file())
    return {p.relative_to(ROOT).as_posix():digest(p) for p in sorted(set(paths)) if p.suffix!='.pyc'}

def local(path):
    result=(ROOT/path).resolve()
    if not result.is_relative_to(ROOT): raise ValueError('Build/test output must stay in project/')
    return result

def run_parallel_tests(build, client, test_run, env, worker_count):
    """Run independent headless suites in isolated processes and directories."""
    worker_root = test_run/'workers'
    log_root = test_run/'logs'
    worker_root.mkdir(parents=True, exist_ok=True)
    log_root.mkdir(parents=True, exist_ok=True)

    tasks = []
    def add(name, command):
        working = worker_root/name
        working.mkdir(parents=True, exist_ok=True)
        tasks.append({'name':name, 'command':[str(item) for item in command],
                      'working':working, 'log':log_root/(name+'.log')})

    add('frame-statistics', [build/'dnf_frame_statistics_tests.exe'])
    add('character-presentation', [build/'dnf_character_presentation_tests.exe', client])
    audio_work = worker_root/'audio'; audio_work.mkdir(parents=True, exist_ok=True)
    (audio_work/'reports').mkdir(parents=True, exist_ok=True)
    add('audio', [build/'dnf_audio_tests.exe', client, audio_work/'reports'/'audio-tests.json'])
    ui_work = worker_root/'ui'; ui_work.mkdir(parents=True, exist_ok=True)
    (ui_work/'reports'/'requested-ui').mkdir(parents=True, exist_ok=True)
    add('ui', [build/'dnf_ui_tests.exe', client, ui_work/'reports'/'requested-ui'])
    preview_work = worker_root/'skill-preview'; preview_work.mkdir(parents=True, exist_ok=True)
    (preview_work/'reports').mkdir(parents=True, exist_ok=True)
    add('skill-preview', [build/'dnf_skill_preview_tests.exe', client, preview_work/'reports'])
    group_names=('source-cache-and-content-index', 'catalog-simulation-and-progression',
                 'learning-damage-and-status', 'combat-ai-and-map-access', 'experimental-actions-and-nut',
                 'ui-and-female-gunner', 'character-and-skill-source', 'scene-and-resource', 'world-combat',
                 'timing-and-effects', 'gunner-source-and-basic-runtime', 'fighter-ai-and-reaction-runtime')
    for group, name in enumerate(group_names):
        add('core-'+name, [build/'dnf_tests.exe', client, '--group', group])

    def execute(task):
        started = time.monotonic()
        try:
            with task['log'].open('w', encoding='utf-8', errors='replace') as output:
                completed = subprocess.run(task['command'], cwd=task['working'], env=env,
                                           stdout=output, stderr=subprocess.STDOUT, check=False)
            return {'name':task['name'], 'status':'pass' if completed.returncode == 0 else 'failed',
                    'returncode':completed.returncode, 'seconds':round(time.monotonic()-started, 3),
                    'log':task['log'].relative_to(test_run).as_posix()}
        except BaseException as error:
            return {'name':task['name'], 'status':'failed', 'returncode':None,
                    'seconds':round(time.monotonic()-started, 3), 'error':str(error),
                    'log':task['log'].relative_to(test_run).as_posix()}

    print(f'PARALLEL TESTS workers={worker_count} tasks={len(tasks)}', flush=True)
    for task in tasks:
        print('TEST START', task['name'], flush=True)
    results = []
    with ThreadPoolExecutor(max_workers=worker_count) as pool:
        future_map = {pool.submit(execute, task):task['name'] for task in tasks}
        for future in as_completed(future_map):
            result = future.result()
            results.append(result)
            print('TEST DONE', result['name'], result['status'],
                  f"{result['seconds']:.1f}s", flush=True)

    reports = test_run/'reports'
    reports.mkdir(parents=True, exist_ok=True)
    for task in tasks:
        source = task['working']/'reports'
        if not source.exists():
            continue
        for item in sorted(source.rglob('*.json')):
            relative = item.relative_to(source)
            if 'test-saves' in relative.parts:
                continue
            destination = reports/relative
            destination.parent.mkdir(parents=True, exist_ok=True)
            if destination.exists():
                if digest(destination) != digest(item):
                    raise RuntimeError(f'Parallel test reports collide with different contents: {relative.as_posix()}')
                continue
            shutil.copy2(item, destination)

    by_name = {result['name']:result for result in results}
    core_groups = []
    for group, name in enumerate(group_names):
        report_path = reports/f'core-group-{group}-result.json'
        if report_path.is_file():
            group_result = json.loads(report_path.read_text(encoding='utf-8'))
        else:
            group_result = {'status':'failed', 'group':group, 'name':name,
                            'error':'Group process did not produce its completion report'}
        core_groups.append(group_result)
        task_result = by_name.get('core-'+name, {})
        if task_result.get('status') != 'pass' and group_result.get('status') == 'pass':
            group_result['status'] = 'failed'
            group_result['error'] = 'Group process returned a nonzero exit status'
    identity_path = reports/'test-content-identity.json'
    identity = None
    if identity_path.is_file():
        identity = json.loads(identity_path.read_text(encoding='utf-8'))['identity']
        presentation_path = reports/'character-presentation-tests.json'
        if presentation_path.is_file():
            presentation_identity = json.loads(presentation_path.read_text(encoding='utf-8')).get('pvf_identity')
            if presentation_identity != identity['pvf_sha256']:
                raise RuntimeError('Character presentation used a different PVF identity')
    core_status = 'pass' if all(group.get('status') == 'pass' for group in core_groups) else 'failed'
    (reports/'core-tests.json').write_text(json.dumps({
        'status':core_status,
        'scope':'All twelve isolated core-test groups; each group has its own process and output directory',
        'groups':core_groups,
        'content_identity':identity}, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    summary = {'status':'pass' if all(result['status'] == 'pass' for result in results) and core_status == 'pass' else 'failed',
               'parallel_workers':worker_count, 'tasks':sorted(results, key=lambda item:item['name']),
               'core_groups':core_groups}
    (reports/'test-run-summary.json').write_text(json.dumps(summary, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    failed = [result for result in results if result['status'] != 'pass']
    if failed or core_status != 'pass':
        detail = ', '.join(f"{item['name']} (exit {item.get('returncode')}; {item['log']})" for item in failed)
        failed_groups = [str(item.get('group')) for item in core_groups if item.get('status') != 'pass']
        if failed_groups:
            detail += ('; ' if detail else '') + 'core groups failed: ' + ','.join(failed_groups)
        raise RuntimeError('Parallel test failure: '+detail)
    return summary

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir',type=Path,default=Path('cache/refactor-build'))
    parser.add_argument('--test-dir',type=Path,default=Path('cache/refactor-tests'))
    parser.add_argument('--test',action='store_true')
    parser.add_argument('--test-workers',type=int,default=min(2, max(1, os.cpu_count() or 1)),
                        help='Maximum number of isolated headless test processes (default: up to 2; PVF parsing is memory-heavy)')
    parser.add_argument('--node',default='cpp-architecture-A0-A2')
    parser.add_argument('--source-baseline',default='mage-upper457')
    parser.add_argument('--client',type=Path)
    parser.add_argument('--jobs',type=int,default=6)
    args=parser.parse_args()
    if args.test_workers < 1 or args.test_workers > 32:
        parser.error('--test-workers must be between 1 and 32')
    config=json.loads((ROOT/'toolchain.local.json').read_text(encoding='utf-8'))
    toolchain=Path(os.environ.get('DNF_TOOLCHAIN_ROOT',config['toolchain_root'])).resolve()
    client=(args.client or Path(config['client_root'])).resolve()
    if not (client/'Script.pvf').is_file(): raise RuntimeError(f'Missing source PVF: {client}')
    build,tests=local(args.build_dir),local(args.test_dir)
    require_game_closed(target_directory=build)
    llvm=next(toolchain.glob('llvm-mingw-*-ucrt-x86_64'))/'bin'
    cmake=next(toolchain.glob('cmake-*-windows-x86_64'))/'bin/cmake.exe'
    ninja=toolchain/'ninja/ninja.exe'
    env=os.environ.copy();env['PATH']=str(llvm)+os.pathsep+env['PATH']
    for names,directory in [(('TEMP','TMP','TMPDIR'),'build-tmp'),(('CLANG_MODULE_CACHE_PATH',),'clang-modules'),
                             (('CCACHE_DIR',),'ccache'),(('SCCACHE_DIR',),'sccache')]:
        path=ROOT/'cache'/directory;path.mkdir(parents=True,exist_ok=True)
        for name in names: env[name]=str(path)
    build.mkdir(parents=True,exist_ok=True);tests.mkdir(parents=True,exist_ok=True)
    run_id=datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    test_run=tests/'runs'/run_id
    verification={'schema':3,'node':args.node,'status':'running',
        'started_utc':datetime.now(timezone.utc).isoformat(),'source_baseline':args.source_baseline,
        'build_directory':str(build.relative_to(ROOT)),'test_directory':str(tests.relative_to(ROOT)),
        'test_run_directory':str(test_run.relative_to(ROOT)),'test_workers':args.test_workers,
        'sources':input_hashes(),'tests_requested':args.test,'frontend_validation':'pending-user',
        'toolchain':{'root':str(toolchain),'clang_sha256':digest(llvm/'clang++.exe'),
                     'cmake_sha256':digest(cmake),'ninja_sha256':digest(ninja)}}
    target=build/'build-verification.json'
    def record():target.write_text(json.dumps(verification,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    record();started=time.time_ns()
    def run(command,cwd=ROOT):
        print('RUN',subprocess.list2cmdline([str(x) for x in command]),flush=True)
        subprocess.run([str(x) for x in command],cwd=cwd,env=env,check=True)
    try:
        run([cmake,'-S',ROOT,'-B',build,'-G','Ninja','-DCMAKE_BUILD_TYPE=Release',
             '-DCMAKE_C_COMPILER='+str(llvm/'clang.exe'),'-DCMAKE_CXX_COMPILER='+str(llvm/'clang++.exe'),
             '-DCMAKE_MAKE_PROGRAM='+str(ninja),'-DDNF_TOOLCHAIN_ROOT='+str(toolchain),'-DDNF_CLIENT_ROOT='+str(client)])
        run([cmake,'--build',build,'-j',str(max(1,args.jobs))])
        names=('dnf_native.exe','dnf_skill_preview.exe','dnf_skill_previewer.exe','dnf_skill_preview_tests.exe',
               'dnf_tests.exe','dnf_audio_tests.exe',
               'dnf_ui_tests.exe','dnf_inspect.exe','dnf_character_presentation_tests.exe','dnf_frame_statistics_tests.exe',
               'SDL2.dll','libunwind.dll')
        verification['binaries']={name:digest(build/name) for name in names}
        verification['compiled_libraries']={p.relative_to(build).as_posix():digest(p) for p in sorted(build.rglob('*.a'))}
        if args.test:
            before=digest(client/'Script.pvf')
            verification['test_execution']=run_parallel_tests(build,client,test_run,env,args.test_workers)
            reports={p.relative_to(tests).as_posix():digest(p) for p in sorted((test_run/'reports').rglob('*.json'))
                     if 'test-saves' not in p.parts and p.stat().st_mtime_ns>=started}
            identity=json.loads((test_run/'reports/test-content-identity.json').read_text(encoding='utf-8'))['identity']
            for name,key in [('audio-tests.json','content_identity'),('requested-ui/ui-runtime-tests.json','content_identity')]:
                if json.loads((test_run/'reports'/name).read_text(encoding='utf-8'))[key]!=identity:
                    raise RuntimeError('Headless consumers used different content identities')
            after=digest(client/'Script.pvf')
            if before!=after or identity['pvf_sha256']!=before:raise RuntimeError('PVF identity changed')
            verification.update(reports=reports,test_content_identity=identity,test_pvf_sha256=after)
        run([sys.executable,'-X','utf8','-B',ROOT/'tools/verify_architecture.py','--build-dir',build])
        if input_hashes()!=verification['sources']:raise RuntimeError('Inputs changed during build or testing')
        for name,expected in verification['binaries'].items():
            if digest(build/name)!=expected:raise RuntimeError(f'Binary changed: {name}')
        verification['status']='pass' if args.test else 'build-only'
    except BaseException as error:
        verification.update(status='failed',error=str(error));raise
    finally:
        verification['finished_utc']=datetime.now(timezone.utc).isoformat();record()

if __name__=='__main__':main()
