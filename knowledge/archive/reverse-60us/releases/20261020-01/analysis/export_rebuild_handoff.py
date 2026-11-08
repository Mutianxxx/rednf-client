"""Create a new, source-identical 60US handoff; never overwrite a release."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import shutil

SOURCE = Path(__file__).resolve().parents[1]
WORKSPACE = Path('D:/dnf-rebuild')
DESTINATION = WORKSPACE / 'reverse-60us'
RELEASE_ID = '20261020-01'


def digest(path):
    h = hashlib.sha256()
    with path.open('rb') as f:
        for block in iter(lambda: f.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()


def write_json(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, ensure_ascii=False, indent=2) + '\n', encoding='utf8')


def main():
    release = DESTINATION / 'releases' / RELEASE_ID
    if DESTINATION.exists():
        raise FileExistsError(f'New handoff root required: {DESTINATION}')
    selected = set()

    def tree(path):
        for f in path.rglob('*'):
            if f.is_symlink():
                raise ValueError(f'Unexpected symlink: {f}')
            if f.is_file() and '__pycache__' not in f.parts and f.suffix != '.pyc':
                selected.add(f)

    tree(SOURCE / 'combat-preview')
    analysis = SOURCE / 'analysis'
    for p in analysis.iterdir():
        if p.is_dir() and (p.name.startswith('combat_') or p.name in {
                'npk60', 'decompiled', 'evidence', 'samples', 'skill-review',
                'preview-validation', 'unpack_audit'}):
            tree(p)
        elif p.is_file() and p.suffix.lower() in {
                '.py', '.mjs', '.md', '.json', '.asm', '.cpp', '.log', '.txt'}:
            selected.add(p)
    rea = analysis / 'rea'
    for p in rea.iterdir():
        if p.is_file():
            selected.add(p)
    tree(rea / 'results')
    tree(rea / 'jobs')
    tree(analysis / 'unpack_attempts/001/patcher-source')
    # Keep the static baseline required by executable_source.py, without
    # copying the client, memory dumps, tools, or failed executable variants.
    for name in ['DFO_fixed_v3.original.exe', 'installed.json', 'README.md', 'restore-original.ps1']:
        selected.add(analysis / 'unpack_attempts/001/launcher_test' / name)
    for name in ['README.md', 'validation.json', 'fixed-v4-import-manifest.json']:
        selected.add(analysis / 'unpack_attempts/001' / name)
    for p in (analysis / 'tools').glob('*.json'):
        selected.add(p)

    touched = [
        'agent.md', 'dnf-native-demo/CURRENT_TASK.md',
        'rep-player-1031-pvf/CURRENT_TASK.md', 'rep-player-1031-pvf/docs/PROGRESS.md',
        'dnf-native-build-plan/README.md',
        'dnf-native-build-plan/13-execution-plan-and-acceptance.md',
        'dnf-native-build-plan/appendices/task-graph.json',
        'dnf-native-build-plan/appendices/evidence-index.json',
        'dnf-native-build-plan/verification/plan-validation.json',
    ]
    # Compare the old plan's historical evidence before making any edits.
    old_index = json.loads((WORKSPACE / 'dnf-native-build-plan/appendices/evidence-index.json').read_text(encoding='utf8'))
    baseline = []
    for row in old_index['source_files']:
        p = WORKSPACE / row['workspace_relative_path']
        actual = digest(p) if p.is_file() else None
        baseline.append(dict(id=row['id'], path=row['workspace_relative_path'],
                             historical_sha256=row['sha256'], observed_sha256=actual,
                             matches=actual == row['sha256']))

    release.mkdir(parents=True)
    records = []
    for src in sorted(selected):
        relative = src.relative_to(SOURCE)
        dst = release / relative
        dst.parent.mkdir(parents=True, exist_ok=True)
        before = digest(src)
        shutil.copy2(src, dst)
        copied = digest(dst)
        after = digest(src)
        if not before == copied == after:
            raise ValueError(f'Copy verification failed: {relative}')
        records.append(dict(path=relative.as_posix(), bytes=src.stat().st_size, sha256=copied))
    backups = []
    for name in touched:
        src = WORKSPACE / name
        dst = DESTINATION / 'handoff/workspace-before' / name
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dst)
        before = digest(src)
        if digest(dst) != before:
            raise ValueError(f'Backup verification failed: {name}')
        backups.append(dict(path=name, bytes=src.stat().st_size, sha256=before))
    write_json(DESTINATION / 'handoff/workspace-before-manifest.json', dict(files=backups))
    write_json(DESTINATION / 'handoff/old-plan-evidence-before.json', dict(
        scope='Historical plan source hashes compared before this handoff; no baselines refreshed.',
        files=baseline, preexisting_mismatches=sum(not r['matches'] for r in baseline)))
    write_json(DESTINATION / 'package-manifest.json', dict(
        format_version=1, release_id=RELEASE_ID,
        created_at_utc=datetime.now(timezone.utc).isoformat(),
        source_workspace=str(SOURCE), snapshot_root=f'releases/{RELEASE_ID}',
        files=records, total_bytes=sum(r['bytes'] for r in records),
        external_client=dict(default_path=str(SOURCE / 'DFO'),
            pvf_sha256='23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98',
            installed_exe_sha256='bdd14a558658dd0b20def0aa9fa4b355b98855075a05ba6de7f60c4da695495e',
            static_evidence_exe_sha256='a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'),
        excluded=['DFO client/PVF/ImagePacks2', 'analysis/rea/tmp',
                  'analysis/tools binaries', 'analysis/deps', 'analysis/angr_deps',
                  'live memory dumps and failed unpack executables', '__pycache__'],
        status='source-identical snapshot; runtime integration pending'))
    print(json.dumps(dict(release=str(release), files=len(records),
        mib=round(sum(r['bytes'] for r in records)/1024/1024, 2),
        plan_backups=len(backups), preexisting_plan_mismatches=sum(not r['matches'] for r in baseline))))


if __name__ == '__main__':
    main()
