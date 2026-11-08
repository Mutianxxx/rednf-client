"""Read-only source inventory and byte-preserving, deduplicated evidence archive."""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import gzip
import json
import os
from pathlib import Path
import shutil
import sys
from datetime import datetime, timezone

WORKSPACE = Path(__file__).resolve().parents[3]
DEST = Path(__file__).resolve().parents[1]
ROOTS = [
    'dnf-native-demo/docs', 'dnf-native-demo/reports',
    'dnf-native-build-plan', 'reverse-60us/reports', 'reverse-60us/handoff',
    'reverse-60us/integration', 'dnf-result/docs', 'dnf-result/research',
    'dnf-result/catalog', 'dnf-result/inventory', 'dnf-result/schemas',
    'dnf-result/imports/android', 'dnf-result/imports/android-revision-20261016',
    'dnf-result/imports/rednf', 'dnf-godot-skill-demo/docs',
    'dnf-godot-skill-demo/reports', 'rep-player-1031-pvf/docs',
    'rep-player-1031-pvf/validation', 'rep-player/rep-player-main',
    '逆向部分结果参考', 'skills', 'dnf-部分知识库', 'pvf官方文档',
    'reverse-60us/releases/20261020-01/analysis',
    'reverse-60us/releases/20261020-01/combat-preview',
]
DIRECT = [
    'agent.md', 'AGENTS.md', 'dnf-native-demo/AGENTS.md',
    'dnf-native-demo/CURRENT_TASK.md', 'dnf-native-demo/README.md',
    'reverse-60us/AGENTS.md', 'reverse-60us/CURRENT_TASK.md',
    'reverse-60us/MODULE_MAP.md', 'reverse-60us/PORTING_PLAN.md',
    'reverse-60us/README.md', 'reverse-60us/package-manifest.json',
    'dnf-result/README.md', 'dnf-result/agent.md',
    'dnf-godot-skill-demo/CURRENT_TASK.md', 'dnf-godot-skill-demo/README.md',
    'rep-player-1031-pvf/CURRENT_TASK.md', 'rep-player-1031-pvf/README-1031.md',
    'rep-player-1031-pvf/README.md', 'rep-player-1031-pvf/RELEASE_NOTES.md',
]
SKIP_DIRS = {
    'cache', 'build', 'checkpoints', 'releases', 'saves', '.git', '.godot',
    'node_modules', 'third_party', 'vendor', 'dist', 'target', 'bin', 'obj',
    '__pycache__', '.venv', 'venv', 'compiled-libraries', 'gba-workspace',
    'dnf-gba', 'gba-tools', 'gba-policies',
}
TEXT_EXTS = {
    '.md', '.txt', '.json', '.jsonl', '.csv', '.tsv', '.xml', '.html', '.htm',
    '.yaml', '.yml', '.toml', '.ini', '.cfg', '.log', '.nut', '.lua', '.c',
    '.cc', '.cpp', '.h', '.hpp', '.py', '.js', '.ts', '.css', '.sln', '.vcxproj',
    '.cmake', '.asm', '.s', '.sql', '.rst', '.act', '.skl', '.mob', '.equ',
    '.obj', '.lay', '.ui', '.map', '.til', '.lst', '.ani', '.als', '.atk',
    '.ptl', '.chr', '.aic', '.ai', '.stk', '.etc', '.str', '.scr', '.quest',
    '.sqlite3', '.db',
}
MAX_FILE = 64 * 1024 * 1024


def dump(path: Path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


def scan():
    files = {}
    skipped = []
    for rel in ROOTS:
        base = WORKSPACE / rel
        if not base.exists():
            skipped.append({'source': rel, 'reason': 'source-not-found'})
            continue
        print(json.dumps({'scan_started': rel}, ensure_ascii=False), flush=True)
        before = len(files)
        pending = [base]
        while pending:
            directory = pending.pop()
            with os.scandir(directory) as entries:
              for item in entries:
                q = Path(item.path)
                source = q.relative_to(WORKSPACE).as_posix()
                name = item.name
                if item.is_symlink():
                    skipped.append({'source': source, 'reason': 'symlink-not-followed'})
                    continue
                if item.is_dir(follow_symlinks=False):
                    excluded_name = name.casefold() in SKIP_DIRS or 'dfq' in name.casefold()
                    duplicate_source = source.startswith('dnf-native-demo/reports/') and name.casefold() in {'source', 'staging', 'sealed', 'compiled-libraries'}
                    if excluded_name or duplicate_source:
                        skipped.append({'source': source, 'reason': 'excluded-directory-no-recursion'})
                    else:
                        pending.append(q)
                    continue
                size = item.stat(follow_symlinks=False).st_size
                reason = None
                if 'dfq' in source.casefold():
                    reason = 'dfq-content-excluded'
                elif q.suffix.casefold() not in TEXT_EXTS and name not in {'CMakeLists.txt', 'LICENSE', 'NOTICE'}:
                    reason = 'binary-or-unselected-extension'
                elif size > MAX_FILE:
                    reason = 'large-file-reference-only'
                if reason:
                    skipped.append({'source': source, 'bytes': size, 'reason': reason})
                else:
                    files[source] = size
        print(json.dumps({'scan_finished': rel, 'selected': len(files) - before, 'total_selected': len(files)}, ensure_ascii=False), flush=True)
    for rel in ['dnf-result/canonical', 'dnf-result/sources', 'dnf-result/supplements', 'dnf-android', 'DNF1031客户端', 'dnf-native-demo/checkpoints', 'dnf-native-demo/cache']:
        skipped.append({'source': rel, 'reason': 'large-raw-source-or-historical-artifacts-reference-only-no-recursion'})
    for rel in DIRECT:
        q = WORKSPACE / rel
        if q.is_file():
            files[rel] = q.stat().st_size
        else:
            skipped.append({'source': rel, 'reason': 'source-not-found'})
    return files, skipped


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--archive', action='store_true')
    args = parser.parse_args()
    selected, excluded = scan()
    summary = {
        'generated_utc': datetime.now(timezone.utc).isoformat(),
        'workspace': str(WORKSPACE), 'selected_files': len(selected),
        'selected_bytes': sum(selected.values()), 'excluded_records': len(excluded),
        'root_coverage': ROOTS, 'direct_files': DIRECT,
        'extension_distribution': dict(Counter(Path(s).suffix.lower() for s in selected)),
        'evidence_warning': 'Archive coverage is not semantic review, native proof, feature acceptance or frontend verification.',
    }
    dump(DEST / 'catalog' / 'inventory-summary.json', summary)
    dump(DEST / 'catalog' / 'selected-files.json', [{'source': k, 'bytes': v} for k, v in sorted(selected.items())])
    dump(DEST / 'catalog' / 'excluded-files.json', excluded)
    if not args.archive:
        print(json.dumps(summary, ensure_ascii=False))
        return
    manifest = []
    by_hash = {}
    copied_bytes = 0
    for index, (source, size) in enumerate(sorted(selected.items()), 1):
        raw = (WORKSPACE / source).read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        entry = {'source': source, 'bytes': size, 'sha256': digest,
                 'verification_scope': 'bytes-preserved-only-source-claims-not-revalidated'}
        if digest in by_hash:
            entry.update(by_hash[digest])
            entry['deduplicated'] = True
        else:
            rel_dest = 'archive/' + source
            compressed = len(raw) >= 65536
            stored = gzip.compress(raw, compresslevel=3, mtime=0) if compressed else raw
            if compressed:
                rel_dest += '.gz'
            target = DEST / rel_dest
            target.parent.mkdir(parents=True, exist_ok=True)
            stored_hash = hashlib.sha256(stored).hexdigest()
            if not target.exists() or hashlib.sha256(target.read_bytes()).hexdigest() != stored_hash:
                target.write_bytes(stored)
            check = target.read_bytes()
            restored = gzip.decompress(check) if compressed else check
            if hashlib.sha256(restored).hexdigest() != digest:
                raise RuntimeError('Archive verification failed: ' + source)
            storage = {'archive': rel_dest, 'archive_encoding': 'gzip' if compressed else 'identity',
                       'stored_bytes': len(stored), 'stored_sha256': stored_hash}
            by_hash[digest] = storage
            entry.update(storage)
            entry['deduplicated'] = False
            copied_bytes += len(stored)
        manifest.append(entry)
        if index % 500 == 0:
            print(json.dumps({'processed': index, 'total': len(selected), 'unique': len(by_hash), 'copied_bytes': copied_bytes}), flush=True)
    dump(DEST / 'catalog' / 'source-manifest.json', manifest)
    summary.update({'status': 'archived-and-hash-verified', 'archived_aliases': len(manifest), 'unique_files': len(by_hash), 'unique_bytes': copied_bytes, 'deduplicated_aliases': len(manifest)-len(by_hash), 'hash_mismatches': 0})
    dump(DEST / 'catalog' / 'archive-summary.json', summary)
    outline = WORKSPACE / 'dnf-native-demo/docs/ARCHITECTURE-REFACTOR-OUTLINE.md'
    (DEST / 'architecture').mkdir(exist_ok=True)
    shutil.copyfile(outline, DEST / 'architecture/ARCHITECTURE-REFACTOR-OUTLINE.md')
    print(json.dumps(summary, ensure_ascii=False), flush=True)


if __name__ == '__main__':
    sys.stdout.reconfigure(encoding='utf-8')
    main()
