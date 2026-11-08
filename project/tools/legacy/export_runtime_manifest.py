"""Hash the original byte ranges actually accessed in a completed run.

No source writes and no repackaging. PVF range hashes cover encrypted, padded
bytes, explicitly separate from the decrypted script hashes in source-evidence.
"""
from pathlib import Path
import argparse
import hashlib
import json

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('report_directory', type=Path)
args = parser.parse_args()
directory = args.report_directory.resolve()
resources = json.loads((directory/'resources.json').read_text(encoding='utf-8'))
rows = []
for kind, collection in (('pvf', 'pvf_reads'), ('npk', 'npk_reads')):
    for name, entry in resources[collection].items():
        archive = Path(entry['pvf' if kind == 'pvf' else 'archive'])
        length = (entry['size']+3)&~3 if kind == 'pvf' else entry['length']
        with archive.open('rb') as stream:
            stream.seek(entry['offset'])
            raw = stream.read(length)
        if len(raw) != length:
            raise ValueError('Source range truncated: '+str(archive)+' '+name)
        rows.append({'kind':kind, 'resource':name, **entry, 'hashed_length':length,
                     'sha256':hashlib.sha256(raw).hexdigest(),
                     'hash_encoding':'encrypted padded PVF bytes' if kind == 'pvf' else 'raw NPK entry'})
result = {'run_id':resources['run_id'], 'entries':rows,
          'scope':'Actually accessed PVF/NPK byte ranges only; no complete dependency closure. '
                  'Loose music/audio.xml/fonts and toolchain are external dependencies.'}
(directory/'resource-manifest.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'run_id':resources['run_id'],'entries':len(rows)},indent=2))
