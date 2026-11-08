import base64
from pathlib import Path
import requests
root = Path(__file__).resolve().parent / 'skill-review'
root.mkdir(exist_ok=True)
for name in ['SKILL.md', 'docs/install.md']:
    r = requests.get('https://api.github.com/repos/cellebrite-labs/ghidra-rpc/contents/'+name, timeout=30)
    r.raise_for_status()
    out = root / name.replace('/', '_')
    out.write_bytes(base64.b64decode(r.json()['content']))
    print(name, 'saved', out)
