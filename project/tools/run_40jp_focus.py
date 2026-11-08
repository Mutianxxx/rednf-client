"""Run changed-path checks only, preserving each attempt and exact build identity."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import json
import os
import subprocess
import time
from build import ROOT, digest, input_hashes, local


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', default='cache/40jp-combat-build')
    parser.add_argument('--suite', help='One core focus suite for diagnosis; omitted runs the complete changed-path set')
    args = parser.parse_args()
    build = local(args.build_dir)
    verification = json.loads((build/'build-verification.json').read_text(encoding='utf-8'))
    if verification['status'] != 'build-only' or verification['sources'] != input_hashes():
        raise RuntimeError('Checks require unchanged inputs from a completed build-only receipt')
    for name, expected in verification['binaries'].items():
        if digest(build/name) != expected:
            raise RuntimeError('Compiled binary changed: '+name)
    config = json.loads((ROOT/'toolchain.local.json').read_text(encoding='utf-8'))
    client = Path(config['client_root']).resolve()
    toolchain = Path(config['toolchain_root']).resolve()
    llvm = next(toolchain.glob('llvm-mingw-*-ucrt-x86_64'))/'bin'
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    out = local('reports/40jp-deep-merge/verification/'+stamp)
    out.mkdir(parents=True, exist_ok=False)
    env = os.environ.copy()
    env['PATH'] = str(build)+os.pathsep+str(llvm)+os.pathsep+env['PATH']
    env['SDL_AUDIODRIVER'] = 'dummy'
    for name in ('TEMP', 'TMP', 'TMPDIR'):
        env[name] = str(ROOT/'cache/build-tmp')
    tasks = [('core', [build/'dnf_tests.exe', client, '--focus',
                        '40jp/'+args.suite if args.suite else '40jp'])]
    if not args.suite:
        tasks.extend([
            ('character-presentation', [build/'dnf_character_presentation_tests.exe', client]),
            ('ui', [build/'dnf_ui_tests.exe', client, out/'ui/reports/requested-ui']),
            ('application-profile', [build/'dnf_native.exe', '--content-profile', ROOT/'content-profile.json',
                '--save-dir', out/'application-profile/saves', '--report-dir', out/'application-profile/reports', '--profile-audit'])])
    receipt = {'schema': 1, 'node': '40jp-deep-merge-2', 'status': 'running',
        'scope': 'diagnostic-single-suite' if args.suite else 'changed-path-checks-only',
        'binary_sha256': verification['binaries']['dnf_tests.exe'],
        'application_sha256': verification['binaries']['dnf_native.exe'],
        'build_verification_sha256': digest(build/'build-verification.json'),
        'started_utc': datetime.now(timezone.utc).isoformat(), 'tasks': [],
        'frontend_validation': 'pending-user', 'full_regression': 'deferred-by-user'}
    target = out/'execution-receipt.json'
    def record():
        target.write_text(json.dumps(receipt, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    record()
    try:
        for name, command in tasks:
            working = out/name
            working.mkdir(parents=True)
            (working/'reports/requested-ui').mkdir(parents=True)
            print('CHECK', name, flush=True)
            started = time.monotonic()
            log = out/(name+'.log')
            with log.open('w', encoding='utf-8', errors='replace') as output:
                result = subprocess.run([str(x) for x in command], cwd=working, env=env,
                    stdout=output, stderr=subprocess.STDOUT, timeout=900)
            receipt['tasks'].append({'name': name, 'command': [str(x) for x in command],
                'returncode': result.returncode, 'seconds': time.monotonic()-started, 'log': log.name})
            record()
            print('DONE', name, result.returncode, flush=True)
            if result.returncode:
                raise RuntimeError('Changed-path check failed; see '+str(log))
        core = json.loads((out/'core/reports/40jp-focus/result.json').read_text(encoding='utf-8'))
        if core.get('status') != 'pass':
            raise RuntimeError('Missing successful core focus completion')
        receipt['content_identity'] = core['content_identity']
        if not args.suite:
            app = json.loads((out/'application-profile/reports/run.json').read_text(encoding='utf-8'))
            receipt['application_profile'] = app
        if input_hashes() != verification['sources']:
            raise RuntimeError('Compiled sources changed while checking')
        for name, expected in verification['binaries'].items():
            if digest(build/name) != expected:
                raise RuntimeError('Compiled binary changed while checking: '+name)
        receipt['status'] = 'pass'
    except BaseException as error:
        receipt.update(status='failed', error=str(error))
        raise
    finally:
        receipt['finished_utc'] = datetime.now(timezone.utc).isoformat()
        receipt['reports'] = {p.relative_to(out).as_posix(): digest(p) for p in sorted(out.rglob('*.json')) if p != target}
        record()
        print(json.dumps({'directory': str(out), 'status': receipt['status']}, ensure_ascii=False), flush=True)


if __name__ == '__main__':
    main()
