"""Download the official Ghidra release, retaining an auditable source URL."""
import hashlib
import json
from pathlib import Path
import time
import zipfile
import requests

root = Path(__file__).resolve().parent / 'tools'
root.mkdir(exist_ok=True)
url = 'https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_11.3.2_build/ghidra_11.3.2_PUBLIC_20250415.zip'
path = root / 'ghidra_11.3.2_PUBLIC_20250415.zip'
if not path.exists() or path.stat().st_size != 446297359:
    api_url = 'https://api.github.com/repos/NationalSecurityAgency/ghidra/releases/assets/246690652?download=1'
    with requests.get(api_url, headers={'Accept': 'application/octet-stream'}, stream=True, timeout=(30, 90)) as response:
        response.raise_for_status()
        print('download', response.status_code, response.headers.get('Content-Length'), flush=True)
        total, last = 0, time.monotonic()
        with path.open('wb') as f:
            for chunk in response.iter_content(4 * 1024 * 1024):
                f.write(chunk)
                total += len(chunk)
                if time.monotonic() - last >= 10:
                    print('bytes', total, flush=True)
                    last = time.monotonic()
if path.stat().st_size != 446297359 or not zipfile.is_zipfile(path):
    raise ValueError(f'Incomplete Ghidra archive: {path.stat().st_size}')
with path.open('rb') as f:
    sha = hashlib.file_digest(f, 'sha256').hexdigest()
print('extracting', sha, flush=True)
with zipfile.ZipFile(path) as z:
    z.extractall(root)
(root / 'ghidra-source.json').write_text(json.dumps({'url':url,'size':path.stat().st_size,'sha256':sha},indent=2),encoding='utf-8')
print('complete', flush=True)
