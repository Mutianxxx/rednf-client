"""Cross-check one isolated candidate's build, GUI and static evidence identities.

This checks archived results; it does not launch games, certify original-client
parity or mark unimplemented characters/skills complete. Output is append-only.
"""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def sha(path: Path) -> str:
    with path.open('rb') as source:
        return hashlib.file_digest(source, 'sha256').hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary', type=Path, required=True)
    parser.add_argument('--build-log', type=Path, required=True)
    parser.add_argument('--settings-run', type=Path, required=True)
    parser.add_argument('--controls-run', type=Path, required=True)
    parser.add_argument('--effects-run', type=Path, required=True)
    parser.add_argument('--flow-run', type=Path)
    parser.add_argument('--visual-review', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    output = (ROOT / args.output).resolve()
    output.relative_to(ROOT / 'reports')
    if output.exists():
        raise SystemExit('Refusing to replace an existing candidate audit: ' + str(output))
    artifacts, checks = {}, []

    def file(path: Path) -> Path:
        path = (ROOT / path).resolve()
        label = path.relative_to(ROOT).as_posix()
        artifacts[label] = {'sha256': sha(path), 'bytes': path.stat().st_size}
        return path

    def read(path: Path):
        return json.loads(file(path).read_text(encoding='utf-8'))

    def check(name, passed, details=None):
        checks.append({'check': name, 'passed': bool(passed), 'detail': details})

    binary_hash = sha(file(args.binary))
    log_bytes = file(args.build_log).read_bytes()
    # Windows PowerShell 5.1 redirects native output as UTF-16 with a BOM;
    # Python-generated logs and newer shells can use UTF-8.
    log = log_bytes.decode('utf-16' if log_bytes.startswith((b'\xff\xfe', b'\xfe\xff'))
                           else 'utf-8-sig')
    check('complete-build-log-core-and-audio-pass', '"status": "pass"' in log and
          'Audio checks 30 pass' in log and 'Traceback' not in log)
    for run, kind in ((args.settings_run, 'settings'), (args.controls_run, 'controls')):
        acceptance = read(run / 'acceptance.json')
        check(kind + '-accepted-with-current-binary', acceptance.get('status') == 'pass' and
              acceptance.get('binary_sha256') == binary_hash, acceptance.get('binary_sha256'))
        check(kind + '-user-saves-unchanged', acceptance.get('user_saves_unchanged'))
        window = read(run / 'test-window.json')
        check(kind + '-window-visible-on-top', window.get('visible_on_top'))
    settings = read(args.settings_run / 'settings-check.json')
    controls = read(args.controls_run / 'gorecross-check.json')
    check('gorecross-ordinary-both-directions', controls.get('status') == 'pass' and
          controls.get('binary_sha256') == binary_hash and len(controls.get('trials', [])) == 2)
    check('settings-process-reload-window-visible', read(args.settings_run / 'test-windowreload.json').get('visible_on_top'))
    launch = read(args.effects_run / 'effects-process.json')
    effects = read(args.effects_run / 'effects-acceptance.json')
    check('effects-current-binary-and-exit-zero', launch.get('binary_sha256') == binary_hash and
          launch.get('returncode') == 0)
    check('effects-accepted', effects.get('passed') and effects.get('check_count') == 74)
    check('effects-isolated-and-visible', launch.get('user_saves_before') == launch.get('user_saves_after') and
          launch.get('test_window', {}).get('visible_on_top'))
    if args.flow_run:
        flow = read(args.flow_run / 'acceptance.json')
        check('ordinary-dungeon-flow-current-binary', flow.get('status') == 'pass' and
              flow.get('binary_sha256') == binary_hash)
        check('ordinary-dungeon-flow-saves-protected', flow.get('user_saves_unchanged'))
        reload = read(args.flow_run / 'reload-check.json')
        check('ordinary-dungeon-flow-actual-reload', reload.get('levels_equal') and reload.get('bindings_equal') and
              set(reload.get('dungeons_cleared_on_reload', [])) >= {1, 2})
    prefix = Path('reports/combat-native-reverse')
    for report in ('axis-motion-tests.json', 'particle-motion-tests.json', 'user-feedback-tests.json',
                   'character-identity-tests.json', 'native-attack-tests.json', 'character-catalog-tests.json',
                   'animation-events/tests.json', 'audio/tests.json', 'jump-physics/verification.json',
                   'gunner-attack/followup/verification.json', 'skill-data/verification.json'):
        data = read(prefix / report)
        check(report + '-pass', data.get('status') in ('pass', 'passed'))
    core = read(Path('reports/core-tests.json'))
    check('core-report-pass', core.get('status') == 'pass')
    visual = read(args.visual_review)
    check('manual-review-is-scoped-to-current-candidate', visual.get('binary_sha256') == binary_hash and
          visual.get('original_pc_parity') is False)
    for row in visual['images']:
        file(Path(row['path']))
    for source in ('CMakeLists.txt', 'tools/build.py', 'tools/verify_flow.py', 'tools/verify_combat_effects.py',
                   'include/dnf/axis_motion.hpp', 'include/dnf/particle_motion.hpp', 'src/axis_motion.cpp',
                   'src/particle_motion.cpp', 'src/combat.cpp', 'tests/test_axis_motion.cpp',
                   'tests/test_particle_motion.cpp', 'tests/test_skill_effects.cpp', 'CURRENT_TASK.md',
                   'docs/IMPLEMENTATION.md', 'docs/RENDERING.md', 'docs/PORTING.md'):
        file(Path(source))
    for name, expected in (('DNF.exe', '246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264'),
                           ('Script.pvf', 'd13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d')):
        actual = sha(ROOT.parent / 'DNF1031客户端' / name)
        check('original-source-' + name, actual == expected, actual)
    check('candidate-binary-remained-unchanged', sha((ROOT / args.binary).resolve()) == binary_hash)
    result = {'status': 'pass' if all(c['passed'] for c in checks) else 'fail',
              'created_utc': datetime.now(timezone.utc).isoformat(), 'binary_sha256': binary_hash,
              'scope': 'Archived candidate/build/input/fixture/source identity checks; no full release or original-client parity claim',
              'all_characters_complete': False, 'original_pc_parity': False,
              'check_count': len(checks), 'checks': checks, 'artifacts': artifacts}
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding='utf-8')
    print(json.dumps({k: v for k, v in result.items() if k not in ('checks', 'artifacts')}, ensure_ascii=False, indent=2))
    for row in checks:
        if not row['passed']:
            print('FAILED:', row['check'], row.get('detail'))
    raise SystemExit(0 if result['status'] == 'pass' else 1)


if __name__ == '__main__':
    main()
