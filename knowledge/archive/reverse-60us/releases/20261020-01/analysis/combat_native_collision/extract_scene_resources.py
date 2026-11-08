"""Read-only, selected scene-object resource evidence from the current 60US PVF.

Path normalization below is a report resolver policy, not recovered native code.
The raw paths, source bytes, token order and unresolved references are retained.
"""
from pathlib import Path
from collections import deque
import hashlib
import json
import posixpath
import sys

OUT = Path(__file__).resolve().parent
WORKSPACE = OUT.parents[1]
sys.path.insert(0, str(WORKSPACE / 'analysis'))
sys.path.insert(0, str(WORKSPACE / 'combat-preview'))
from pvf60 import Pvf60
from pvf_model import parse_document, listing_rows, node_record

EXPECTED = '23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98'
SELECTED = [
    'passiveobject/mapobject/breakableobject/barrel.obj',
    'passiveobject/mapobject/breakableobject/actiontree2lorien.obj',
    'passiveobject/mapobject/breakableobject/smallgrasslorien.obj',
    'passiveobject/actionobject/breakableobject/telephone.obj',
]
PVF_SUFFIXES = {'.obj', '.act', '.ani', '.ptl', '.atk', '.als'}


def main():
    pvf = Pvf60(WORKSPACE / 'DFO' / 'Script.pvf')
    digest = hashlib.sha256(pvf.data).hexdigest()
    if digest != EXPECTED:
        raise ValueError('Unexpected PVF identity; review selected source paths')
    dest = OUT / 'scene-pvf'
    dest.mkdir(exist_ok=True)
    queue = deque(SELECTED)
    visited = set()
    resources = []
    edges = []
    while queue:
        path = queue.popleft()
        if path in visited:
            continue
        visited.add(path)
        raw = pvf.read(path)
        doc = parse_document(raw, path)
        stem = path.replace('/', '__')
        (dest / (stem + '.raw')).write_bytes(raw)
        (dest / (stem + '.utf8.txt')).write_text(doc.text, encoding='utf8')
        resources.append({
            'path': path, 'sha256': doc.sha256, 'size': len(raw), 'encoding': doc.encoding,
            'entry_crc_verified': True, 'archive_entry': pvf.by_path[path],
            'raw_export': 'scene-pvf/' + stem + '.raw',
            'text_export': 'scene-pvf/' + stem + '.utf8.txt',
            'fields': [node_record(n) for n in doc.events],
            'parse_warnings': doc.warnings,
        })
        for token in doc.tokens:
            if token.kind != 'string':
                continue
            value = token.text.replace('\\', '/')
            suffix = posixpath.splitext(value.lower())[1]
            if suffix not in PVF_SUFFIXES:
                continue
            normalized = posixpath.normpath(posixpath.join(posixpath.dirname(path), value)).lower()
            candidates = [p for p in dict.fromkeys([normalized, value.lower()]) if p in pvf.by_path]
            edge = {'source': path, 'raw_token': token.to_dict(),
                    'resolver_candidates': candidates, 'relative_candidate': normalized,
                    'native_execution_established': False}
            edges.append(edge)
            if len(candidates) == 1:
                queue.append(candidates[0])
            elif not candidates:
                edge['unresolved'] = 'No matching PVF entry using the explicitly declared report resolver'
            else:
                edge['unresolved'] = 'Ambiguous: relative and archive-root paths both exist'
    registrations = []
    for listing in ['passiveobject/passiveobject.lst', 'passiveobject/passiveobject.usa.lst',
                    'passiveobject/passiveobject.jpn.lst']:
        doc = parse_document(pvf.read(listing), listing)
        selected = []
        for row in listing_rows(doc):
            resolved = posixpath.normpath(posixpath.join('passiveobject', row['path'].replace('\\', '/'))).lower()
            if resolved in SELECTED:
                selected.append({'resolved_report_path': resolved, **row})
        registrations.append({'path': listing, 'sha256': doc.sha256,
                              'entry_crc_verified': True, 'selected_rows': selected})
    report = {
        'schema': '60us-selected-scene-object-source-evidence-v1',
        'archive': str(pvf.path), 'archive_sha256': digest,
        'tree_crc_verified': True, 'selected_objects': SELECTED,
        'resolver_policy': 'Raw tokens retained; report resolves relative directory + raw path, normalizes dot segments, then also considers archive-root raw path. This policy is not a recovered native normalization rule.',
        'registrations': registrations, 'resources': resources, 'resource_edges': edges,
        'limitations': [
            'Selected source resources only, not an exhaustive scene-object or subclass audit.',
            'Resource declarations and path resolution do not prove native execution.',
            'Generic PassiveObject HP/destruction consumers must not be applied to every specialized scene subclass.',
            'Commented last-action paths are retained in raw bytes but never treated as active fields.',
            'Generic lastACT execution and final destroy-particle dispatch are established separately in scene-destruction-contract.json; particle internals remain unrecovered.',
        ],
    }
    (OUT / 'scene-resources.json').write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf8')
    print(json.dumps({'archive_sha256': digest, 'selected_objects': len(SELECTED),
                      'resources': len(resources), 'edges': len(edges),
                      'unresolved_edges': sum('unresolved' in e for e in edges)}, ensure_ascii=False))


if __name__ == '__main__':
    main()
