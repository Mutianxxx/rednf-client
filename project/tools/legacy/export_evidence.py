"""Preserve bounded PC evidence without assigning unverified replay semantics."""
from pathlib import Path
import sqlite3
import zlib
import json
import hashlib

root = Path(__file__).resolve().parents[1]
source = root.parent/'dnf-result/research/dnf-evidence.sqlite3'
db = sqlite3.connect(source.as_uri()+'?mode=ro&immutable=1', uri=True)
output = root/'reports/source-evidence'
output.mkdir(parents=True, exist_ok=True)
prefix = 'etc/pvppracticecombo/replay/swordman/'
manifest = []

def preserve(path, raw_z, model_z):
    raw = zlib.decompress(raw_z)
    model = json.loads(zlib.decompress(model_z))
    digest = hashlib.sha256(raw).hexdigest()
    target = output/path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(raw)
    target.with_suffix(target.suffix+'.json').write_text(json.dumps(model, ensure_ascii=False, indent=2), encoding='utf-8')
    manifest.append({'source':'pc', 'pvf_path':path, 'raw_size':len(raw), 'sha256':digest,
                     'model_sha256_matches':model.get('sha256')==digest})

for row in db.execute('SELECT path,raw_z,model_z FROM files WHERE source=? AND path>=? AND path<? ORDER BY path',
                      ('pc',prefix,prefix+'~')):
    preserve(*row)
for name in ('upperslash','hardattack','tripleslash','dashattackmultihit','ashenfork','jumpattackmulti',
             'normalwave','khazan','vaneslash','gorecross','hopsmash','moonlightslash','guard',
             'basicattackup','shortswordmastery','blademastery','heavyswordmastery','bluntmastery','armormasterylight'):
    row = db.execute('SELECT path,raw_z,model_z FROM files WHERE source=? AND path=?',('pc','skill/swordman/'+name+'.skl')).fetchone()
    if row: preserve(*row)
for path in ('map/elvengard/tile/dummy.til','character/swordman/swordman.chr',
             'map/elvengard/(r)gate.map','map/elvengard/elvengard.map','map/elvengard/d_elvengard.map',
             'map/lorien/s0.map','map/lorien/4.map','map/lorien/b1.map'):
    row = db.execute('SELECT path,raw_z,model_z FROM files WHERE source=? AND path=?',('pc',path)).fetchone()
    if row: preserve(*row)
result = {'source_database':str(source), 'files':manifest,
          'replay_scope':'raw bytes, ordered fields/tokens, hashes only; time/key semantics unverified; no original replay playback claim'}
(output/'manifest.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'files':len(manifest),'hashes_match':all(x['model_sha256_matches'] for x in manifest)},indent=2))
