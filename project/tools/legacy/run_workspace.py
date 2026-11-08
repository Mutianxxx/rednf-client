"""Run a verified checkpoint immediately, or build current C++ in its own cache.

Never builds into or changes an existing checkpoint. Source preview uses its own
save/report directories and refuses a build whose inputs changed mid-compile.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import os
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def sha(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def read(path):
    return json.loads(path.read_text(encoding='utf-8'))


def source_inputs():
    paths = [ROOT/'CMakeLists.txt', ROOT/'third_party/dependencies.lock.json']
    for folder in ('include', 'src', 'tests', 'third_party/squirrel-3.1-dnf'):
        paths.extend(p for p in (ROOT/folder).rglob('*') if p.is_file())
    paths.extend((ROOT/'tools').rglob('*.py'))
    for name in ('dnf_ani_render.hpp', 'dnf_ani_clock.hpp'):
        paths.append(ROOT.parent/'reverse-60us/integration/include'/name)
    return {Path(os.path.relpath(p, ROOT)).as_posix(): sha(p) for p in sorted(paths)}


def prepare(mode):
    if mode == 'latest':
        latest = (ROOT/'checkpoints/LATEST.md').read_text(encoding='utf-8')
        progress = re.search(r'\]\(([^)]+/PROGRESS\.md)\)', latest)
        if not progress:
            raise RuntimeError('Latest checkpoint progress link is missing')
        # LATEST only points inside the preserved checkpoints tree.
        checkpoint = (ROOT/'checkpoints'/progress.group(1)).resolve().parent
        checkpoint.relative_to(ROOT/'checkpoints')
        manifest = read(checkpoint/'manifest.json')
        if manifest['build_status'] != 'pass':
            raise RuntimeError('Latest checkpoint has no accepted build')
        runtime = checkpoint/'runtime'
        for name in ('dnf_native.exe', 'SDL2.dll', 'libunwind.dll', 'content-profile.json'):
            expected = next(row['sha256'] for row in manifest['files'] if row['path'] == 'runtime/'+name)
            if sha(runtime/name) != expected:
                raise RuntimeError('Verified runtime changed: '+name)
        return runtime, runtime/'content-profile.json', runtime/'saves', runtime/'reports', 'verified-checkpoint'
    build = ROOT/'cache/source-user-build'
    verification = build/'build-verification.json'
    current = source_inputs()
    state = read(verification) if verification.exists() else {}
    up_to_date = state.get('status') in ('pass', 'build-only') and state.get('sources') == current
    if up_to_date:
        up_to_date = all((build/name).is_file() and sha(build/name) == value for name, value in state['binaries'].items())
    if not up_to_date:
        print('Current C++ source needs an incremental build. For instant play use Play-Latest-Verified.cmd.', flush=True)
        subprocess.run([sys.executable, '-X', 'utf8', '-B', str(ROOT/'tools/build.py'),
                        '--build-dir', str(build.relative_to(ROOT))], cwd=ROOT, check=True)
        state = read(verification)
    if state.get('sources') != source_inputs():
        raise RuntimeError('Source changed during preparation. Retry after the current edit finishes.')
    profile = ROOT/'cache/source-user-profile.json'
    client = ROOT.parent/'DNF1031客户端'
    profile.write_text(json.dumps({'profileId':'source-user-preview', 'pvfPath':str(client/'Script.pvf'),
        'resourceRoots':[str(client)], 'textEncoding':'CP936', 'parserVersion':'dnf-source-v1',
        'compatibilityProfileId':'1031-v1', 'ruleProfileId':'beta-foundation-v1'}, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    return build, profile, ROOT/'cache/source-user-saves', ROOT/'reports/source-user-runs', 'source-preview-not-formal-acceptance'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--mode', choices=('latest', 'source'), default='latest')
    parser.add_argument('--check', action='store_true', help='Validate and print paths without opening a window')
    args, extra = parser.parse_known_args()
    runtime, profile, saves, reports, scope = prepare(args.mode)
    run_id = args.mode+'-'+datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    command = [str(runtime/'dnf_native.exe'), '--content-profile', str(profile), '--save-dir', str(saves),
               '--report-dir', str(reports/run_id), '--run-id', run_id,
               '--ani-render-profile', 'inferred60us1031', '--ani-clock-policy', 'inferred60us-percent-deadlines', *extra]
    print(json.dumps({'scope':scope, 'exe':str(runtime/'dnf_native.exe'), 'saves':str(saves),
                      'reports':str(reports/run_id), 'command':command}, ensure_ascii=False), flush=True)
    if not args.check:
        return subprocess.call(command, cwd=ROOT)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
