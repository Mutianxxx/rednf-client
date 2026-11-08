"""Freeze a compiled 40JP candidate with optional changed-path checks; preserve the verified baseline."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import shutil

ROOT = Path(__file__).resolve().parents[2]


def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def local(value):
    path = (ROOT / value).resolve()
    if not path.is_relative_to(ROOT):
        raise ValueError('Candidate inputs/outputs must stay in project/')
    return path


def write_json(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', default='cache/40jp-combat-build')
    parser.add_argument('--node', default='40jp-combat-merge-1')
    parser.add_argument('--suffix', default='40jp-combat-merge-build-only')
    parser.add_argument('--build-log', default='cache/40jp-combat-merge-build-final.log')
    parser.add_argument('--report-dir', action='append', default=[])
    parser.add_argument('--focused-evidence')
    args = parser.parse_args()
    if not args.node or any(c not in 'abcdefghijklmnopqrstuvwxyz0123456789-' for c in args.node + args.suffix):
        raise ValueError('Node and suffix must be lowercase path-free identifiers')
    build = local(args.build_dir)
    receipt_path = build / 'build-verification.json'
    verification = json.loads(receipt_path.read_text(encoding='utf-8'))
    if verification['status'] != 'build-only' or verification['tests_requested']:
        raise RuntimeError('This tool requires a build-only receipt; full regression is not promoted here')
    verified_paths = ('Play-Latest-Verified.cmd', 'LATEST_CHECKPOINT.json')
    verified = {name: digest(ROOT / name) for name in verified_paths}
    for name, expected in verification['sources'].items():
        if digest(local(name)) != expected:
            raise RuntimeError('Compiled input changed: ' + name)
    for category in ('binaries', 'compiled_libraries'):
        for name, expected in verification[category].items():
            if digest(build / name) != expected:
                raise RuntimeError('Compiled artifact changed: ' + name)
    architecture_path = ROOT / 'reports/migration/architecture-check.json'
    architecture = json.loads(architecture_path.read_text(encoding='utf-8'))
    if architecture['status'] != 'pass':
        raise RuntimeError('Source ownership check has not passed')

    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    out = local('checkpoints/' + stamp + '-' + args.suffix)
    out.mkdir(parents=True, exist_ok=False)
    marker = out / 'INCOMPLETE'
    marker.write_text('Backup is incomplete until both hash passes finish.\n', encoding='ascii')
    rows = {}

    def copy(source, relative):
        target = out / relative
        key = target.relative_to(out).as_posix()
        if key in rows:
            return
        target.parent.mkdir(parents=True, exist_ok=True)
        expected = digest(source)
        shutil.copy2(source, target)
        if digest(target) != expected or digest(source) != expected:
            raise RuntimeError('Copy/source mismatch: ' + key)
        rows[key] = {'path': key, 'size': target.stat().st_size, 'sha256': expected}

    def generated(relative, content, encoding='utf-8'):
        path = out / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(content, encoding=encoding, newline='\r\n')
        key = path.relative_to(out).as_posix()
        rows[key] = {'path': key, 'size': path.stat().st_size, 'sha256': digest(path)}

    for name in verification['sources']:
        copy(local(name), 'source/' + name)
    for directory in ('tools', 'docs', 'licenses', 'third_party/SDL2-2.32.10'):
        for path in sorted((ROOT / directory).rglob('*')):
            if path.is_file() and '__pycache__' not in path.parts and path.suffix != '.pyc':
                copy(path, 'source/' + path.relative_to(ROOT).as_posix())
    excluded = {*verified_paths, 'LATEST_40JP_CANDIDATE.json', 'Play-40JP-Merge-Candidate.cmd'}
    for path in sorted(ROOT.iterdir()):
        if path.is_file() and path.name not in excluded:
            copy(path, 'source/' + path.name)
    runtime_names = {'dnf_native.exe', 'SDL2.dll', 'libunwind.dll'}
    for name in verification['binaries']:
        copy(build / name, ('runtime/' if name in runtime_names else 'compiled-tools/') + name)
    for name in verification['compiled_libraries']:
        copy(build / name, 'compiled-libraries/' + name)
    copy(ROOT / 'content-profile.json', 'runtime/content-profile.json')
    for path in sorted((ROOT / 'licenses').rglob('*')):
        if path.is_file():
            copy(path, 'runtime/licenses/' + path.relative_to(ROOT / 'licenses').as_posix())
    for name in ('build-verification.json', 'compile_commands.json', 'CMakeCache.txt'):
        copy(build / name, 'evidence/' + name)
    copy(architecture_path, 'evidence/architecture-check.json')
    copy(local(args.build_log), 'evidence/final-build.log')
    for directory in args.report_dir or ['reports/40jp-review']:
        report = local(directory)
        if not report.is_dir():
            raise RuntimeError('Missing requested report directory: ' + directory)
        for path in sorted(report.rglob('*')):
            if path.is_file():
                copy(path, 'evidence/' + report.name + '/' + path.relative_to(report).as_posix())
    focused_status = 'not-run'
    if args.focused_evidence:
        focused = local(args.focused_evidence)
        receipt = json.loads((focused / 'execution-receipt.json').read_text(encoding='utf-8'))
        if (receipt.get('status') != 'pass' or receipt.get('scope') != 'changed-path-checks-only'
                or receipt.get('binary_sha256') != verification['binaries']['dnf_tests.exe']
                or receipt.get('application_sha256') != verification['binaries']['dnf_native.exe']
                or receipt.get('build_verification_sha256') != digest(receipt_path)
                or {task['name'] for task in receipt.get('tasks', [])} !=
                   {'core', 'character-presentation', 'ui', 'application-profile'}
                or any(task.get('returncode') != 0 for task in receipt.get('tasks', []))):
            raise RuntimeError('Changed-path checks must pass and bind this build, test binary and application')
        focused_status = 'pass-focused-only'
        for path in sorted(focused.rglob('*')):
            if path.is_file():
                copy(path, 'evidence/focused-checks/' + path.relative_to(focused).as_posix())
    for name in ('PROGRESS.md', 'AGENTS.md'):
        copy(ROOT.parent / name, 'workspace/' + name)
    for name in ('INDEX.md', 'archive/40jp-reverse-source/source-manifest.json',
                 'archive/40jp-reverse-source/ARCHIVE-NOTES.md'):
        copy(ROOT.parent / 'knowledge' / name, 'evidence/knowledge/' + name)
    launcher = ('@echo off\nsetlocal\ncd /d "%~dp0"\n'
                'echo 40JP development candidate: full regression deferred; frontend pending.\n'
                '"%~dp0dnf_native.exe" --content-profile "%~dp0content-profile.json" '
                '--save-dir "%~dp0saves" --report-dir "%~dp0reports" %*\n'
                'set "dnf_exit=%errorlevel%"\nif not "%dnf_exit%"=="0" pause\nexit /b %dnf_exit%\n')
    generated('runtime/play.cmd', launcher, 'ascii')
    exe_hash = verification['binaries']['dnf_native.exe']
    progress = ('# 40JP 战斗与女格斗家体验候选\n\n'
                '**状态：编译通过；完整回归按用户要求暂缓，前台游戏与原版动态对照待用户。**\n\n'
                '用户要求暂缓长回归测试，当前保存可体验的开发候选；修改路径专项结果单独列出。\n'
                '启动 `runtime/play.cmd`，存档与日志都在本候选内；旧已验证入口保持原位。\n\n'
                f'本节点：`{args.node}`；针对修改路径的专项检查：`{focused_status}`。\n'
                f'EXE SHA256：`{exe_hash}`。\n'
                f'编译结束：`{verification["finished_utc"]}`。\n'
                '实现、来源、女格斗家覆盖与未完成内容见 `evidence/` 内节点报告。\n'
                '源码在 `source/`，编译身份在 `evidence/build-verification.json`；\n'
                '恢复时先核对 manifest，不重启已结束历史测试。全部技能、UI引擎和最终beta尚未完成。\n')
    generated('PROGRESS.md', progress)
    for row in rows.values():
        path = out / row['path']
        if path.stat().st_size != row['size'] or digest(path) != row['sha256']:
            raise RuntimeError('Second hash pass failed: ' + row['path'])
    for name, expected in verification['sources'].items():
        if digest(local(name)) != expected:
            raise RuntimeError('Input changed during backup: ' + name)
    if {name: digest(ROOT / name) for name in verified_paths} != verified:
        raise RuntimeError('Verified baseline pointer changed during candidate backup')
    manifest = {'schema': 1, 'node': args.node, 'kind': 'build-only-development-candidate',
                'created_utc': datetime.now(timezone.utc).isoformat(), 'build_status': 'build-only',
                'runtime_tests': 'full-regression-deferred-by-user', 'focused_checks': focused_status, 'frontend_validation': 'pending-user',
                'full_beta_gate_passed': False, 'binary_sha256': exe_hash,
                'source_baseline': verification['source_baseline'], 'hash_passes': 2,
                'verified_baseline_pointers': verified, 'file_count': len(rows),
                'bytes': sum(row['size'] for row in rows.values()), 'files': list(rows.values())}
    write_json(out / 'manifest.json', manifest)
    marker.unlink()
    pointer = {'directory': str(out), 'manifest_sha256': digest(out / 'manifest.json'),
               'status': 'build-only', 'runtime_tests': 'full-regression-deferred-by-user', 'focused_checks': focused_status, 'binary_sha256': exe_hash}
    write_json(ROOT / 'LATEST_40JP_CANDIDATE.json', pointer)
    relative = str(out.relative_to(ROOT))
    (ROOT / 'Play-40JP-Merge-Candidate.cmd').write_text(
        '@echo off\ncall "%~dp0' + relative + '\\runtime\\play.cmd" %*\n', encoding='ascii', newline='\r\n')
    print(json.dumps({**pointer, 'files': manifest['file_count'], 'bytes': manifest['bytes'], 'hash_passes': 2}, ensure_ascii=False))


if __name__ == '__main__':
    main()
