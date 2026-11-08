"""Run the visible, isolated --combat-effects-fixture and review its evidence.

This injects accepted diagnostic hits to inspect render/lifecycle behavior. It is
not ordinary keyboard, collision, combat balance, or original-PC visual parity
acceptance. The original client is never launched and user saves are hashed.
"""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import subprocess
import time
import uuid

from test_window import show_test_window

ROOT = Path(__file__).resolve().parents[1]


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def save_hashes() -> dict[str, str]:
    return {p.relative_to(ROOT / 'saves').as_posix(): digest(p)
            for p in (ROOT / 'saves').rglob('*') if p.is_file()}


def read_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding='utf-8'))


def review(report: Path, launch: dict | None) -> dict:
    fixture = read_json(report / 'effects-fixture.json')
    runtime = read_json(report / 'runtime.json')
    events = read_json(report / 'events.json')
    checks = []

    def check(name: str, passed: bool, detail=None):
        checks.append({'check': name, 'passed': bool(passed), 'detail': detail})

    trials = {row['key']: row for row in fixture['trials']}
    samples = fixture['samples']
    expected = [f'shared-{side}-{strength}' for side in ('left', 'right', 'above', 'below')
                for strength in ('weak', 'strong')]
    expected += ['explicit-ghost', 'explicit-chief', 'hurt-standing', 'hurt-knockdown',
                 'airborne-rehit', 'hopsmash-base', 'hopsmash-blood-vigorous']
    check('all-15-cases-completed', fixture.get('completed') and set(trials) == set(expected)
          and all('end' in row for row in trials.values()))
    check('isolated-save-directory', Path(fixture['isolated_save_directory']).resolve()
          == (report / 'saves').resolve())
    check('asset-load-errors-empty', not runtime.get('asset_errors'), runtime.get('asset_errors'))
    check('renderer-errors-empty', not runtime.get('render_errors'), runtime.get('render_errors'))
    check('captures-exist', len(samples) >= 100 and all(Path(row['capture']).is_file() for row in samples), len(samples))
    check('sample-timing-within-one-tick', all(0 <= row['elapsed_ms'] - row['requested_ms'] <= 18
                                            for row in samples), 'Capped submission only in this fixture')

    # The diagnostic hit is scheduled at 350ms, then the shared death burst
    # lasts 220ms. These samples bracket fragment age 550/625/680/700/730ms.
    for side, strength in ((side, strength) for side in ('left', 'right', 'above', 'below')
                           for strength in ('weak', 'strong')):
        key = f'shared-{side}-{strength}'
        rows = {row['requested_ms']: row for row in samples if row['case'] == key}
        needed = (850, 1120, 1200, 1250, 1270, 1300)
        check(key + '-fragment-display-boundary-sampled', all(t in rows for t in needed), sorted(rows))
        if all(t in rows for t in needed):
            fragments = [rows[t]['state']['targets'][0] for t in needed]
            check(key + '-700ms-cap-and-150ms-fade-observed',
                  [m['fragment_display_ms'] for m in fragments] == [700] * len(needed)
                  and fragments[0]['fragment_opacity'] == 1
                  # Real rendering may sample up to one simulation tick past
                  # a requested time; the first fade sample is then below 1.
                  and 0.85 <= fragments[1]['fragment_opacity'] <= 1
                  and 0.35 <= fragments[2]['fragment_opacity'] <= 0.55
                  and 0 <= fragments[3]['fragment_opacity'] <= 0.25
                  and fragments[4]['fragment_opacity'] == 0
                  and fragments[5]['fragment_opacity'] == 0,
                  [m['fragment_opacity'] for m in fragments])

    vectors = {'left': (1, 0), 'right': (-1, 0), 'above': (0, 1), 'below': (0, -1)}
    for side, vector in vectors.items():
        strength_rows = {}
        for strength in ('weak', 'strong'):
            key = f'shared-{side}-{strength}'
            rows = [s for s in samples if s['case'] == key]
            target_rows = [s['state']['targets'][0] for s in rows if s['state']['targets']]
            dead = next((m for m in target_rows if m['death_route']), None)
            check(key + '-shared-route', dead and dead['death_route'] == 'shared-source-palette'
                  and not dead['independent_death'], dead['death_route'] if dead else None)
            check(key + '-white-then-fragments', any(m['life'] == 1 for m in target_rows)
                  and any(m['life'] == 2 and m['fragment_count'] > 0 for m in target_rows))
            if dead:
                direction = dead['impact']['direction']
                velocity = dead['fragment_velocity_mean']
                check(key + '-away-from-attacker', sum(a*b for a, b in zip(direction, vector)) > .99
                      and sum(a*b for a, b in zip(velocity[:2], vector)) > 0,
                      {'impact': direction, 'fragment_mean': velocity})
                strength_rows[strength] = dead['impact']['speed_scale']
            end = trials.get(key, {}).get('end', {}).get('targets', [])
            check(key + '-removed', end and end[0]['life'] == 3)
        check('strong-faster-than-weak-' + side, set(strength_rows) == {'weak', 'strong'}
              and strength_rows['strong'] > strength_rows['weak'], strength_rows)

    for key in ('explicit-ghost', 'explicit-chief'):
        rows = [s['state']['targets'][0] for s in samples if s['case'] == key and s['state']['targets']]
        dead = next((m for m in rows if m['death_route']), None)
        check(key + '-source-last-action', dead and dead['independent_death']
              and dead['death_route'] == 'last-action' and dead['death_motion'].endswith('/action/die.act')
              and all(m['fragment_count'] == 0 for m in rows), dead)
        end = trials.get(key, {}).get('end', {}).get('targets', [])
        check(key + '-removed-after-source-duration', end and end[0]['life'] == 3)

    for key in ('hurt-standing', 'hurt-knockdown'):
        rows = [s['state']['targets'][0] for s in samples if s['case'] == key and s['state']['targets']]
        check(key + '-nonlethal-reaction', rows and min(m['hp'] for m in rows) < 10000
              and all(m['hp'] > 0 and not m['death_route'] for m in rows)
              and any(m['animation'] in ('damage1', 'damage2', 'down') for m in rows))

    knockdown = [s['state']['targets'][0] for s in samples
                 if s['case'] == 'hurt-knockdown' and s['state']['targets']]
    down = [m for m in knockdown if m['animation'] == 'down']
    check('knockdown-uses-source-lying-animation', bool(down) and
          all(m['animation_path'].endswith('/down.ani') for m in down))
    check('knockdown-recovers-without-source-placeholder-wait', bool(knockdown) and
          knockdown[-1]['animation'] == 'stay')

    grouped = {}
    key = None
    for event in events:
        if event['kind'] == 'fixture_case':
            key = event['name']
            grouped[key] = []
        elif key:
            grouped[key].append(event)
    air = grouped.get('airborne-rehit', [])
    check('airborne-accepted-rehit-and-relaunch', sum(e['kind'] == 'hit' for e in air) == 2
          and sum(e['kind'] == 'relaunch' for e in air) >= 2)
    for key, should_have_wave in [('hopsmash-base', False), ('hopsmash-blood-vigorous', True)]:
        rows = [s for s in samples if s['case'] == key]
        effects = [e for row in rows for e in row['state']['world']['effect_instances']]
        wave = any(e['animation'].endswith('/hopsmashsubfront1.ani') for e in effects)
        check(key + '-passive-branch', wave == should_have_wave
              and all(row['state']['world']['blood_vigorous_level'] == int(should_have_wave) for row in rows),
              {'wave_observed': wave, 'expected': should_have_wave})
        check(key + '-sword-and-smash', all(any(e['animation'].endswith('/hopsmash/' + name + '.ani')
                                              for e in effects) for name in ('sword', 'smash')))
    if launch:
        check('process-exit-zero', launch.get('returncode') == 0, launch.get('returncode'))
        check('user-saves-unchanged', launch.get('user_saves_before') == launch.get('user_saves_after'))
        check('visible-on-top', launch.get('test_window', {}).get('visible_on_top'), launch.get('test_window'))
    result = {'scope': fixture['scope'], 'passed': all(c['passed'] for c in checks),
              'check_count': len(checks), 'checks': checks,
              'visual_review_required': True, 'ordinary_input_acceptance': False,
              'original_pc_pixel_parity': False, 'report_directory': str(report)}
    (report / 'effects-acceptance.json').write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding='utf-8')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary', type=Path, default=ROOT / 'build/dnf_native.exe')
    parser.add_argument('--resolution', nargs=2, type=int, default=[800, 600])
    parser.add_argument('--timeout', type=float, default=150)
    parser.add_argument('--review-only', type=Path, help='Review an existing fixture directory without launching anything')
    args = parser.parse_args()
    if args.review_only:
        report = args.review_only.resolve()
        launch_file = report / 'effects-process.json'
        result = review(report, read_json(launch_file) if launch_file.exists() else None)
    else:
        binary = args.binary.resolve()
        run_id = 'effects-' + datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S') + '-' + uuid.uuid4().hex[:6]
        report = ROOT / 'reports/runs' / run_id
        report.mkdir(parents=True)
        command = [str(binary), '--combat-effects-fixture', '--run-id', run_id,
                   '--report-dir', str(report), '--resolution', *map(str, args.resolution)]
        launch = {'binary': str(binary), 'binary_sha256': digest(binary), 'command': command,
                  'user_saves_before': save_hashes(), 'started_utc': datetime.now(timezone.utc).isoformat()}
        print(json.dumps({'report_directory': str(report), 'command': command}, ensure_ascii=False), flush=True)
        with (report / 'stdout.log').open('w', encoding='utf-8') as stdout, (report / 'stderr.log').open('w', encoding='utf-8') as stderr:
            process = subprocess.Popen(command, cwd=ROOT, stdout=stdout, stderr=stderr)
            launch['test_window'] = show_test_window(process)
            deadline = time.monotonic() + args.timeout
            try:
                process.wait(timeout=max(.1, deadline-time.monotonic()))
            except subprocess.TimeoutExpired:
                process.terminate()
                process.wait(timeout=10)
                launch['timeout'] = True
            launch['returncode'] = process.returncode
        launch.update(user_saves_after=save_hashes(), finished_utc=datetime.now(timezone.utc).isoformat())
        (report / 'effects-process.json').write_text(json.dumps(launch, ensure_ascii=False, indent=2), encoding='utf-8')
        if not (report / 'effects-fixture.json').exists():
            raise SystemExit('Fixture did not complete. Inspect '+str(report / 'stderr.log'))
        result = review(report, launch)
    print(json.dumps({k: v for k, v in result.items() if k != 'checks'}, ensure_ascii=False, indent=2))
    for row in result['checks']:
        if not row['passed']:
            print('FAILED:', row['check'], json.dumps(row.get('detail'), ensure_ascii=False))
    raise SystemExit(0 if result['passed'] else 1)


if __name__ == '__main__':
    main()
