"""Extract only the selected current-PVF skill32 resource chain, with CRC/hash evidence."""
from pathlib import Path
import sys, json, hashlib
ROOT = Path(__file__).resolve().parent
WORKSPACE = ROOT.parents[1]
sys.path.insert(0, str(WORKSPACE / 'analysis'))
sys.path.insert(0, str(WORKSPACE / 'combat-preview'))
from pvf60 import Pvf60
from pvf_model import parse_document, listing_rows, node_record, parse_animation

def main():
    pvf = Pvf60(WORKSPACE / 'DFO' / 'Script.pvf')
    expected = '23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98'
    digest = hashlib.sha256(pvf.data).hexdigest()
    if digest != expected:
        raise ValueError('Unexpected current PVF; registrations must be reviewed')
    paths = [
        'skill/swordmanskill.lst', 'skill/swordman/releasewave.skl',
        'passiveobject/passiveobject.lst', 'passiveobject/passiveobject.usa.lst',
        'passiveobject/passiveobject.jpn.lst', 'passiveobject/old passiveobject.lst',
        'passiveobject/character/swordman/releasewave.obj',
        'passiveobject/character/swordman/animation/releasewave.ani',
        'passiveobject/character/swordman/attackinfo/releasewave.atk',
        'character/swordman/effect/animation/releasewave1.ani',
        'character/swordman/effect/animation/releasewave2.ani',
    ]
    exports = ROOT / 'pvf'
    exports.mkdir(exist_ok=True)
    records = []
    for path in paths:
        raw = pvf.read(path)
        doc = parse_document(raw,path)
        stem = path.replace('/','__')
        (exports / (stem+'.raw')).write_bytes(raw)
        (exports / (stem+'.utf8.txt')).write_text(doc.text, encoding='utf-8')
        record = dict(path=path, sha256=doc.sha256, size=len(raw), encoding='cp949',
                      archive_entry=pvf.by_path[path], entry_crc_verified=True,
                      raw_export='pvf/'+stem+'.raw', utf8_export='pvf/'+stem+'.utf8.txt')
        if path.endswith('.lst'):
            record['selected_rows'] = [row for row in listing_rows(doc)
                if row['id'] == (32 if path.startswith('skill/') else 20018)]
        elif path.endswith('.ani'):
            record['animation'] = parse_animation(raw,path)
        else:
            record['fields'] = [node_record(n) for n in doc.events]
        records.append(record)
    report = dict(schema='60us-skill32-resource-evidence-v1', archive=str(pvf.path),
                  archive_sha256=digest, tree_crc_verified=True, resources=records,
                  limitations=['Static current-PVF data; no observed native execution.',
                    'All list variants agree for object 20018; native list-selection proof is tracked separately.',
                    'ReleaseWave.obj declares no ACT; no ACT file is invented.',
                    'Empty IMAGE strings in object ANI are retained; visual effects are separate native literals.'])
    (ROOT / 'resources.json').write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding='utf-8')
    print(json.dumps(dict(resources=len(records), source_sha256=digest,
                         exports=str(exports)), ensure_ascii=True))

if __name__ == '__main__':
    main()
