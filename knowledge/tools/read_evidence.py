"""Find or restore archived evidence without requiring any original workspace tree."""
import argparse
import gzip
import hashlib
import json
from pathlib import Path
import sys
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--find', help='Case-insensitive source-path substring')
    group.add_argument('--extract', help='Exact original workspace-relative source path')
    group.add_argument('--verify', action='store_true', help='Verify every unique archived payload')
    args = parser.parse_args()
    manifest_bytes = (ROOT / 'catalog/source-manifest.json').read_bytes()
    manifest = json.loads(manifest_bytes)
    if args.find:
        matches = [x for x in manifest if args.find.casefold() in x['source'].casefold()]
        print(json.dumps({'matches': len(matches), 'first_50': [x['source'] for x in matches[:50]]}, ensure_ascii=False, indent=2))
        return
    if args.verify:
        entries = {x['archive']: x for x in manifest}.values()
    else:
        entries = [x for x in manifest if x['source'] == args.extract.replace('\\', '/')]
        if len(entries) != 1:
            parser.error('Source not found uniquely; use --find first.')
    count = 0
    started = datetime.now(timezone.utc).isoformat()
    for entry in entries:
        stored = (ROOT / entry['archive']).read_bytes()
        if hashlib.sha256(stored).hexdigest() != entry['stored_sha256']:
            raise RuntimeError('Stored bytes mismatch: ' + entry['source'])
        raw = gzip.decompress(stored) if entry['archive_encoding'] == 'gzip' else stored
        if len(raw) != entry['bytes'] or hashlib.sha256(raw).hexdigest() != entry['sha256']:
            raise RuntimeError('Source bytes mismatch: ' + entry['source'])
        count += 1
        if args.verify and count % 5000 == 0:
            print(json.dumps({'verified_unique_payloads': count}), flush=True)
        if not args.verify:
            target = (ROOT / 'reading-room' / entry['source']).resolve()
            if not target.is_relative_to((ROOT / 'reading-room').resolve()):
                raise RuntimeError('Invalid archive source path')
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(raw)
            print(json.dumps({'restored': str(target), 'sha256': entry['sha256'], 'bytes': len(raw)}, ensure_ascii=False))
    if args.verify:
        report = {'status': 'pass', 'started_utc': started, 'finished_utc': datetime.now(timezone.utc).isoformat(),
                  'source_aliases': len(manifest), 'verified_unique_files': count, 'hash_mismatches': 0,
                  'missing_payloads': 0, 'manifest_sha256': hashlib.sha256(manifest_bytes).hexdigest(),
                  'scope': 'Every final-manifest canonical path read; stored SHA256, codec restoration, raw byte length and source SHA256 checked.'}
        (ROOT / 'catalog/full-payload-verification.json').write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
        print(json.dumps(report))


if __name__ == '__main__':
    sys.stdout.reconfigure(encoding='utf-8')
    main()
