"""Add bounded raw RE byte slices and reference figures to the completed archive."""
import gzip
import hashlib
import json
from pathlib import Path
import sys
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[1]
WORKSPACE = ROOT.parents[1]


def main():
    manifest_path = ROOT / 'catalog/source-manifest.json'
    manifest = json.loads(manifest_path.read_text(encoding='utf-8'))
    excluded_path = ROOT / 'catalog/excluded-files.json'
    excluded = json.loads(excluded_path.read_text(encoding='utf-8'))
    # Preserve the user prohibition on importing old GBA implementations/derived data.
    def forbidden(source):
        return source.startswith('dnf-result/supplements/') or any(p.lower().startswith(('gba-', 'dnf-gba')) for p in Path(source).parts)
    rejected = [e for e in manifest if forbidden(e['source'])]
    manifest = [e for e in manifest if not forbidden(e['source'])]
    remaining_by_archive = {}
    for e in manifest:
        remaining_by_archive.setdefault(e['archive'], []).append(e)
    for old_path in {e['archive'] for e in rejected}:
        # A rejected alias may share a canonical payload under an allowed source.
        # Retain that payload; only clean storage physically located in a banned tree.
        if not forbidden(old_path.removeprefix('archive/').removesuffix('.gz')):
            continue
        source_file = (ROOT / old_path).resolve()
        if not source_file.is_relative_to((ROOT / 'archive').resolve()):
            raise RuntimeError('Refusing to clean outside this generated archive')
        if old_path in remaining_by_archive:
            aliases = remaining_by_archive[old_path]
            replacement = 'archive/' + aliases[0]['source'] + ('.gz' if aliases[0]['archive_encoding'] == 'gzip' else '')
            destination = ROOT / replacement
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_bytes(source_file.read_bytes())
            for e in aliases:
                e['archive'] = replacement
        source_file.unlink(missing_ok=True)
    excluded.extend({'source': e['source'], 'bytes': e['bytes'], 'reason': 'old-gba-implementation-or-derived-data-not-imported'} for e in rejected)
    by_hash = {e['sha256']: {k: e[k] for k in ['archive', 'archive_encoding', 'stored_bytes', 'stored_sha256']} for e in manifest}
    existing = {e['source'] for e in manifest}
    added_sources = set()
    for e in excluded:
        source = e['source']
        if e['reason'] != 'binary-or-unselected-extension' or source in existing or forbidden(source):
            continue
        suffix = Path(source).suffix.lower()
        size = e.get('bytes', 0)
        raw_slice = suffix == '.bin' and size <= 1048576
        document = suffix in {'.doc', '.docx', '.rtf', '.pdf'} and size <= 16 * 1048576
        figure_source = source.startswith(('逆向部分结果参考/', 'reverse-60us/', 'dnf-godot-skill-demo/reports/', 'dnf-部分知识库/')) or (source.startswith('dnf-native-demo/reports/') and len(Path(source).parts) == 3)
        figure = suffix in {'.png', '.jpg', '.jpeg', '.gif', '.webp'} and figure_source and size <= 8 * 1048576
        if not (raw_slice or document or figure):
            continue
        raw = (WORKSPACE / source).read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        result = {'source': source, 'bytes': len(raw), 'sha256': digest,
                  'verification_scope': 'bytes-preserved-only-not-executed-or-visually-revalidated'}
        if digest in by_hash:
            result.update(by_hash[digest])
            result['deduplicated'] = True
        else:
            compress = len(raw) >= 65536 and suffix not in {'.png', '.jpg', '.jpeg', '.gif', '.webp'}
            payload = gzip.compress(raw, compresslevel=3, mtime=0) if compress else raw
            target_rel = 'archive/' + source + ('.gz' if compress else '')
            target = ROOT / target_rel
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(payload)
            stored = target.read_bytes()
            restored = gzip.decompress(stored) if compress else stored
            if hashlib.sha256(restored).hexdigest() != digest:
                raise RuntimeError('Source hash mismatch: ' + source)
            storage = {'archive': target_rel, 'archive_encoding': 'gzip' if compress else 'identity', 'stored_bytes': len(payload), 'stored_sha256': hashlib.sha256(payload).hexdigest()}
            by_hash[digest] = storage
            result.update(storage)
            result['deduplicated'] = False
        manifest.append(result)
        added_sources.add(source)
    manifest.sort(key=lambda e: e['source'])
    manifest_path.write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    remaining = [e for e in excluded if e['source'] not in added_sources]
    excluded_path.write_text(json.dumps(remaining, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    summary_path = ROOT / 'catalog/archive-summary.json'
    summary = json.loads(summary_path.read_text(encoding='utf-8'))
    summary.update({'supporting_evidence_added': len(added_sources), 'old_gba_aliases_excluded': len(rejected), 'selected_files': len(manifest), 'selected_bytes': sum(e['bytes'] for e in manifest), 'archived_aliases': len(manifest), 'unique_files': len(by_hash), 'unique_bytes': sum(e['stored_bytes'] for e in by_hash.values()), 'deduplicated_aliases': len(manifest)-len(by_hash), 'excluded_records': len(remaining), 'supplemented_utc': datetime.now(timezone.utc).isoformat()})
    summary_path.write_text(json.dumps(summary, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(summary, ensure_ascii=False))


if __name__ == '__main__':
    sys.stdout.reconfigure(encoding='utf-8')
    main()
