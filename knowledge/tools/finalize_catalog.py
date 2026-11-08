"""Finalize the materialized archive inventory and verify canonical storage coverage."""
from collections import Counter
from datetime import datetime, timezone
import gzip
import hashlib
import json
import os
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
WORKSPACE = ROOT.parents[1]


def dump(name, value):
    (ROOT / 'catalog' / name).write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


def main():
    manifest = json.loads((ROOT / 'catalog/source-manifest.json').read_text(encoding='utf-8'))
    summary = json.loads((ROOT / 'catalog/archive-summary.json').read_text(encoding='utf-8'))
    excluded = json.loads((ROOT / 'catalog/excluded-files.json').read_text(encoding='utf-8'))
    by_archive = {e['archive']: e for e in manifest}
    present = set()
    for d, _, files in os.walk(ROOT / 'archive'):
        for name in files:
            present.add((Path(d) / name).relative_to(ROOT).as_posix())
    restored = []
    for missing in sorted(set(by_archive) - present):
        e = by_archive[missing]
        raw = (WORKSPACE / e['source']).read_bytes()
        if hashlib.sha256(raw).hexdigest() != e['sha256']:
            raise RuntimeError('Cannot restore canonical bytes from current source: ' + e['source'])
        payload = gzip.compress(raw, compresslevel=3, mtime=0) if e['archive_encoding'] == 'gzip' else raw
        if hashlib.sha256(payload).hexdigest() != e['stored_sha256']:
            raise RuntimeError('Canonical encoding mismatch: ' + e['source'])
        target = ROOT / missing
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(payload)
        restored.append({'archive': missing, 'source': e['source'], 'sha256': e['sha256']})
    if any(any(part.lower().startswith(('gba-', 'dnf-gba')) for part in Path(e['source']).parts) or e['source'].startswith('dnf-result/supplements/') for e in manifest):
        raise RuntimeError('Forbidden old GBA source remained in materialized manifest')
    summary.update({'root_coverage': [x for x in summary['root_coverage'] if x != 'dnf-result/supplements'],
                    'extension_distribution': dict(Counter(Path(e['source']).suffix.lower() for e in manifest)),
                    'selected_files': len(manifest), 'selected_bytes': sum(e['bytes'] for e in manifest),
                    'unique_files': len(by_archive), 'unique_bytes': sum(e['stored_bytes'] for e in by_archive.values()),
                    'canonical_payloads_present': len(by_archive), 'canonical_payloads_missing': 0,
                    'finalized_utc': datetime.now(timezone.utc).isoformat()})
    dump('archive-summary.json', summary)
    dump('inventory-summary.json', summary)
    dump('selected-files.json', [{'source': e['source'], 'bytes': e['bytes']} for e in manifest])
    dump('canonical-storage-repair.json', {'status': 'pass', 'repaired_payloads': len(restored), 'reason': 'Retain canonical allowed-source storage when excluded aliases share the same bytes.', 'records': restored, 'missing_after_repair': 0})
    dump('exclusion-summary.json', {'records': len(excluded), 'reason_counts': dict(Counter(e['reason'] for e in excluded)), 'reference_only_roots': ['DNF1031客户端', 'dnf-android', 'dnf-result/canonical', 'dnf-result/sources', 'dnf-result/supplements', 'dnf-native-demo/checkpoints', 'dnf-native-demo/cache'], 'scope': 'Excluded directory roots are boundary references; their children were not claimed as copied or revalidated.'})
    print(json.dumps({'canonical_payloads_present': len(by_archive), 'repaired_payloads': len(restored), 'missing': 0, 'aliases': len(manifest), 'archive_bytes': summary['unique_bytes']}))


if __name__ == '__main__':
    sys.stdout.reconfigure(encoding='utf-8')
    main()
