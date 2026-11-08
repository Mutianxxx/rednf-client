"""Preserve a node's source, binaries and evidence in a new immutable directory.

This is a resumable development backup, not a release acceptance check. Known
failures belong in the required progress document and are copied as evidence.
No source content package, existing save or original client is copied or changed.
"""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import shutil

ROOT = Path(__file__).resolve().parents[1]


def digest(path: Path) -> str:
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def local(value: str) -> Path:
    path = (ROOT / value).resolve()
    path.relative_to(ROOT)
    return path


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--node', required=True)
    parser.add_argument('--build-dir', required=True)
    parser.add_argument('--test-dir', required=True)
    parser.add_argument('--evidence-dir', required=True)
    parser.add_argument('--progress-file', required=True)
    args = parser.parse_args()
    if not re.fullmatch(r'[a-z0-9][a-z0-9-]{0,79}', args.node):
        raise RuntimeError('Node must be a short lowercase ASCII identifier')
    build, tests, evidence, progress = map(local, (args.build_dir, args.test_dir,
                                                 args.evidence_dir, args.progress_file))
    verification_path = build / 'build-verification.json'
    verification = json.loads(verification_path.read_text(encoding='utf-8'))
    if verification['status'] != 'pass' or not verification['tests_requested']:
        raise RuntimeError('A completed build with core/audio checks is required')
    if verification['test_directory'] != tests.relative_to(ROOT).as_posix():
        raise RuntimeError('Build and test directories do not match')
    # Keep the actual tested compiler inputs intact, even if new tooling was
    # added since this build. Added files are separately identified below.
    for name, expected in verification['sources'].items():
        if digest(ROOT / name) != expected:
            raise RuntimeError('Tested source has changed; finish the next node build first: ' + name)
    for name, expected in verification['binaries'].items():
        if digest(build / name) != expected:
            raise RuntimeError('Tested binary has changed: ' + name)
    for name, expected in verification.get('compiled_libraries', {}).items():
        if digest(build / name) != expected:
            raise RuntimeError('Tested compiled library has changed: ' + name)
    for name, expected in verification['reports'].items():
        if digest(tests / name) != expected:
            raise RuntimeError('Test report no longer matches its build: ' + name)
    progress_text = progress.read_text(encoding='utf-8')
    if not progress_text.strip():
        raise RuntimeError('A concrete progress/resume document is required')
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    output = ROOT / 'checkpoints' / (stamp + '-' + args.node)
    output.mkdir(parents=True, exist_ok=False)
    copied = []

    def copy(source: Path, target: Path) -> None:
        expected = digest(source)
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)
        if digest(target) != expected or digest(source) != expected:
            raise RuntimeError('A backup input changed during copying: ' + str(source))
        copied.append({'path': target.relative_to(output).as_posix(),
                       'size': target.stat().st_size, 'sha256': expected})

    source_files = {ROOT / 'CMakeLists.txt', ROOT / 'AGENTS.md', ROOT / 'CURRENT_TASK.md'}
    source_files.update(ROOT.glob('*.cmd'))
    for folder in ('include', 'src', 'tests', 'tools', 'docs'):
        for source in (ROOT / folder).rglob('*'):
            if source.is_file() and '__pycache__' not in source.parts and source.suffix != '.pyc':
                source_files.add(source)
    # Retain library source and dependency identity needed to rebuild the
    # project; installed compiler/CMake/SDL SDK archives stay external on D:.
    for name in ('dependencies.lock.json', 'json.hpp', 'stb_image_write.h', 'stb_truetype.h', 'stb_vorbis.c'):
        source = ROOT / 'third_party' / name
        if source.is_file():
            source_files.add(source)
    for directory in ('zlib-1.3.1', 'squirrel-2.1.1', 'squirrel-3.1-dnf'):
        dependency = ROOT / 'third_party' / directory
        if dependency.is_dir():
            source_files.update(source for source in dependency.rglob('*') if source.is_file())
    added_sources = []
    for source in sorted(source_files):
        name = source.relative_to(ROOT).as_posix()
        copy(source, output / 'source' / name)
        if name not in verification['sources']:
            added_sources.append(name)
    # Keep the relative include layout of the shared portable render adapter.
    # A restored source/ build resolves ../reverse-60us exactly as this project.
    render_header = ROOT.parent / 'reverse-60us/integration/include/dnf_ani_render.hpp'
    copy(render_header, output / 'reverse-60us/integration/include/dnf_ani_render.hpp')
    clock_header = ROOT.parent / 'reverse-60us/integration/include/dnf_ani_clock.hpp'
    copy(clock_header, output / 'reverse-60us/integration/include/dnf_ani_clock.hpp')
    for source in (ROOT.parent / 'agent.md', ROOT.parent / 'AGENTS.md'):
        if source.is_file():
            copy(source, output / 'workspace-instructions' / source.name)
    for source in (ROOT.parent / 'dnf-native-build-plan').rglob('*'):
        if source.is_file():
            copy(source, output / 'implementation-plan' / source.relative_to(ROOT.parent / 'dnf-native-build-plan'))
    for name in verification['binaries']:
        copy(build / name, output / 'runtime' / name)
    for name in verification.get('compiled_libraries', {}):
        copy(build / name, output / 'compiled-libraries' / name)
    for name in verification['reports']:
        copy(tests / name, output / 'evidence' / 'tests' / name)
    copy(verification_path, output / 'evidence' / 'build-verification.json')
    for source in evidence.rglob('*'):
        if source.is_file():
            copy(source, output / 'evidence' / 'node' / source.relative_to(evidence))
    profile = evidence / 'audits' / 'profile-config.json'
    if profile.is_file():
        copy(profile, output / 'runtime' / 'content-profile.json')
        launcher = ('@echo off\r\nsetlocal\r\ncd /d "%~dp0"\r\n'
                    '"%~dp0dnf_native.exe" --content-profile "%~dp0content-profile.json" '
                    '--save-dir "%~dp0saves" %*\r\n')
        target = output / 'runtime' / 'play.cmd'
        target.write_bytes(launcher.encode('ascii'))
        copied.append({'path': 'runtime/play.cmd', 'size': target.stat().st_size, 'sha256': digest(target)})
    target = output / 'PROGRESS.md'
    target.write_text(progress_text, encoding='utf-8')
    copied.append({'path': 'PROGRESS.md', 'size': target.stat().st_size, 'sha256': digest(target)})
    manifest = {'schema': 1, 'node': args.node, 'created_utc': datetime.now(timezone.utc).isoformat(),
                'kind': 'development-node-backup', 'full_beta_gate_passed': False,
                'build_status': verification['status'], 'binary_sha256': verification['binaries']['dnf_native.exe'],
                'build_directory': verification['build_directory'], 'test_directory': verification['test_directory'],
                'tested_source_files_unchanged': True,
                'additional_source_documentation_or_tooling': added_sources,
                'content_identity': verification['test_content_identity'],
                'user_frontend_validation': 'pending',
                'source_resources': 'External read-only content; not bundled. No existing save copied.',
                'resume_document': 'PROGRESS.md', 'files': sorted(copied, key=lambda item: item['path'])}
    (output / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    mismatches = [item['path'] for item in copied if digest(output / item['path']) != item['sha256']]
    if mismatches:
        raise RuntimeError('Backup verification failed: ' + repr(mismatches))
    latest = ('# Latest completed development node\n\n'
              f'Node: `{args.node}`\n\n'
              f'[Progress and resume instructions]({output.name}/PROGRESS.md)\n\n'
              f'EXE SHA256: `{manifest["binary_sha256"]}`\n\n'
              'This is an intermediate development backup. Known gaps and pending user verification '
              'are recorded in PROGRESS.md; the full beta acceptance gate remains open.\n')
    (ROOT / 'checkpoints' / 'LATEST.md').write_text(latest, encoding='utf-8')
    print(json.dumps({'status': 'pass', 'directory': str(output), 'files': len(copied),
                      'binary_sha256': manifest['binary_sha256']}, ensure_ascii=False))


if __name__ == '__main__':
    main()
