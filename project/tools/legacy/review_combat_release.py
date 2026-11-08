"""Audit a combat release against completed real-window runs and source hashes.

Does not launch the game or infer original-client visual fidelity from logs.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
from PIL import Image

root = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--input-run', required=True, type=Path)
parser.add_argument('--deep-run', type=Path)
parser.add_argument('--skill-run', required=True, type=Path)
parser.add_argument('--effects-run', required=True, type=Path)
parser.add_argument('--scene-run', required=True, type=Path)
parser.add_argument('--failed-run', action='append', default=[], type=Path)
parser.add_argument('--failed-visual-run', action='append', default=[], type=Path)
args = parser.parse_args()
out = root/'reports/combat-rework'
out.mkdir(exist_ok=True)


def read(path):
    return json.loads(path.read_text(encoding='utf-8-sig'))


def sha(path):
    value = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024*1024), b''):
            value.update(block)
    return value.hexdigest()


def relative(path):
    return str(path.resolve().relative_to(root))


checks = []


def check(name, passed, detail=None):
    checks.append({'check': name, 'passed': bool(passed), 'detail': detail})


binary = sha(root/'build/dnf_native.exe')
check('build-and-playable-identical', sha(root/'playable/dnf_native.exe') == binary)
payload = []
for entry in read(root/'playable/manifest.json')['files']:
    file = root/'playable'/entry['path']
    actual = sha(file)
    check('payload-'+entry['path'], actual == entry['sha256'] and file.stat().st_size == entry['size'])
    payload.append({'file': entry['path'], 'sha256': actual})

core = []
for name in ('core-tests.json', 'appearance-tests.json', 'skill-chain-rework/tests.json',
             'monster-rework/tests.json', 'elvengard-rework/tests.json', 'combat-feel/tests.json'):
    path = root/'reports'/name
    report = read(path)
    check('core-report-'+name, report['status'] == 'pass')
    core.append({'file': relative(path), 'sha256': sha(path),
                 'checks': len(report.get('checks', [])), 'status': report['status']})

runs = []
run_directories = [('normal-input', args.input_run), ('skill-smoke', args.skill_run),
                   ('effects-fixture', args.effects_run), ('scene-smoke', args.scene_run)]
if args.deep_run:
    run_directories.append(('normal-deep-input', args.deep_run))
for kind, directory in run_directories:
    directory = directory.resolve()
    is_input = kind.endswith('input')
    process_file = directory/('acceptance.json' if is_input else
                              'effects-process.json' if kind == 'effects-fixture' else 'process-check.json')
    process = read(process_file)
    check(kind+'-binary-identity', process['binary_sha256'] == binary)
    check(kind+'-completion', process.get('status') == 'pass' if is_input
          else process.get('returncode') == 0)
    if is_input:
        check(kind+'-user-saves-unchanged', process['user_saves_unchanged'])
        windows = [read(p) for p in directory.glob('test-window*.json')]
    else:
        windows = [process.get('test_window', {})]
    check(kind+'-visible-on-top', bool(windows) and all(w.get('visible_on_top') for w in windows))
    runtimes = []
    for file in directory.rglob('runtime.json'):
        runtime = read(file)
        check(kind+'-runtime-errors-'+relative(file), not any(runtime.get(k) for k in
              ('asset_errors', 'render_errors', 'audio_errors', 'unresolved_sound_ids')))
        runtimes.append({k: runtime.get(k) for k in ('mode', 'duration_seconds', 'frames', 'ticks',
                        'median_frame_ms', 'p95_frame_ms', 'max_frame_ms', 'render_unsupported')})
    check(kind+'-runtime-record-exists', bool(runtimes))
    manifest = directory/'resource-manifest.json'
    range_count = None
    if manifest.exists():
        ranges = read(manifest)['entries']
        for entry in ranges:
            archive = Path(entry['pvf' if entry['kind'] == 'pvf' else 'archive'])
            with archive.open('rb') as stream:
                stream.seek(entry['offset'])
                raw = stream.read(entry['hashed_length'])
            if len(raw) != entry['hashed_length'] or hashlib.sha256(raw).hexdigest() != entry['sha256']:
                raise ValueError('Source range changed: '+str(archive)+' '+entry['resource'])
        range_count = len(ranges)
        check(kind+'-accessed-source-ranges-unchanged', True, range_count)
    review = directory/'visual-review.json'
    runs.append({'kind': kind, 'directory': relative(directory), 'process': process,
                 'runtime': runtimes, 'windows': windows, 'source_range_count': range_count,
                 'visual_review': relative(review) if review.exists() else None})

skills = read(args.skill_run/'skill-samples.json')
trials, samples = skills['trials'], skills['samples']
check('skills-13-by-two-directions', {(t['skill_index'], t['direction']) for t in trials} ==
      {(i, d) for i in range(13) for d in (-1, 1)} and len(trials) == 26)
check('skills-182-samples', len(samples) == 182 and
      all({s['phase'] for s in samples if s['step'] == t['step']} == set(range(7)) for t in trials))
captures = list((args.skill_run/'captures').glob('skill-*.png'))
check('skills-182-real-capture-files', len(captures) == 182)
events = read(args.skill_run/'events.json')
stage_rows = []
for offset, trial in enumerate(trials):
    end = trials[offset+1]['tick'] if offset+1 < len(trials) else 10**12
    events_here = [e for e in events if trial['tick'] <= e['tick'] < end]
    latest = max((s for s in samples if s['step'] == trial['step']), key=lambda s: s['phase'])
    stages = [e['name'] for e in events_here if e['kind'] == 'stage']
    if trial['skill_index'] == 2:
        check('three-slash-stages-'+str(trial['direction']), stages == ['tripleslash:0', 'tripleslash:1', 'tripleslash:2'])
    if trial['skill_index'] == 8:
        check('vane-three-pulses-'+str(trial['direction']),
              len([e for e in events_here if e['kind'] == 'pulse' and e['name'] == 'vaneslash']) == 3)
        check('vane-capture-downslash-'+str(trial['direction']),
              sum(e['kind'] == 'hit' and e['name'] == 'vaneslash:capture' for e in events_here) == 1 and
              sum(e['kind'] == 'hit' and e['name'] == 'vaneslash:downslash' for e in events_here) == 1)
    if trial['skill_index'] != 12:
        check('skill-unlocks-'+str(trial['step']), latest['state']['active'] == -1)
    stage_rows.append({'step': trial['step'], 'skill': trial['skill_index'], 'direction': trial['direction'],
                       'stages': stages, 'last_active': latest['state']['active']})

effects = read(args.effects_run/'effects-acceptance.json')
check('effects-fixture-checks', effects['passed'], effects['check_count'])
effects_process = read(args.effects_run/'effects-process.json')
current_saves = {p.relative_to(root/'saves').as_posix(): sha(p)
                 for p in (root/'saves').rglob('*') if p.is_file()}
check('user-saves-still-equal-to-fixture-baseline', current_saves == effects_process['user_saves_before'] ==
      effects_process['user_saves_after'])
scenes = sorted((args.scene_run/'captures').glob('scene-*.png'))
sizes = [list(Image.open(file).size) for file in scenes]
check('six-scenes-three-resolutions', len(scenes) == 6 and
      {tuple(size) for size in sizes} == {(800, 600), (1280, 720), (1024, 768)}, sizes)

sources = []
for name, expected in (
    ('Script.pvf', 'd13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d'),
    ('DNF.exe', '246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264'),
):
    path = root.parent/'DNF1031客户端'/name
    actual = sha(path)
    check('original-'+name+'-unchanged', actual == expected)
    sources.append({'file': str(path), 'sha256': actual})

failures = [{'directory': relative(p), 'result': read(p/'acceptance.json')}
            for p in args.failed_run]
visual_failures = [{'directory': relative(p), 'result': read(p/'visual-review.json')}
                   for p in args.failed_visual_run]
report = {'recorded_utc': datetime.now(timezone.utc).isoformat(),
          'automated_checks_passed': all(c['passed'] for c in checks), 'binary_sha256': binary,
          'checks': checks, 'payload': payload, 'core': core, 'runs': runs,
          'skill_stage_audit': stage_rows, 'original_sources': sources, 'preserved_failures': failures,
          'preserved_visual_findings': visual_failures,
          'original_client_pixel_parity': False,
          'scope': 'Automated build/package/source/window-run audit. Visual reviews are separate observations. '
                   'Skill and effects fixtures inject controlled scenarios; they do not certify ordinary input or PC combat balance.',
          'remaining': ['Complete native skill controller creation/timing/conditions',
                        'Exact original damage/defense/growth and fragment-speed formula',
                        'Blood/age-rating branches, full ACT behavior and special sounds',
                        'Independent depth sorting of each fragment',
                        'Complete original UI, advanced jobs, storage/mail/event services']}
(out/'verification.json').write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding='utf-8')
print(json.dumps({'automated_checks_passed': report['automated_checks_passed'],
                  'checks': len(checks), 'binary_sha256': binary,
                  'report': relative(out/'verification.json')}, ensure_ascii=False, indent=2))
raise SystemExit(0 if report['automated_checks_passed'] else 1)
