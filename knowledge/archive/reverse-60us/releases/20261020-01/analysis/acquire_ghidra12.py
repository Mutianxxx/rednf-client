"""Acquire official pinned Ghidra via verified resumable byte ranges."""
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
from pathlib import Path
import time
import zipfile
import requests

root=Path(__file__).resolve().parent/'tools'
root.mkdir(exist_ok=True)
name='ghidra_12.1.4_PUBLIC_20260921.zip'
size=569649598
digest='ddac49f903da9d5bac833e5cc79395098b9c33cfd3279be5f31bd00387d2d4db'
api='https://api.github.com/repos/NationalSecurityAgency/ghidra/releases/assets/579530646?download=1'
chunk=8*1024*1024
parts=root/'ghidra12-parts'
parts.mkdir(exist_ok=True)
dest=root/name

if not dest.exists() or dest.stat().st_size!=size:
 r=requests.get(api,headers={'Accept':'application/octet-stream','Range':'bytes=0-1023'},stream=True,timeout=(20,40))
 r.raise_for_status()
 signed=r.url
 r.close()
 def acquire(i):
  begin=i*chunk;end=min(size,begin+chunk)-1
  p=parts/f'{i:04d}.part'
  if p.exists() and p.stat().st_size==end-begin+1:return i,'cached'
  for attempt in range(5):
   try:
    # Unique query prevents caches from replaying the first tiny range.
    u=signed+'&rea_range='+str(i)
    with requests.get(u,headers={'Range':f'bytes={begin}-{end}'},stream=True,timeout=(20,60)) as resp:
     if resp.status_code!=206 or resp.headers.get('Content-Range')!=f'bytes {begin}-{end}/{size}':
      raise ValueError(f'Unexpected range {resp.status_code} {resp.headers.get("Content-Range")}')
     with p.open('wb') as out:
      for data in resp.iter_content(256*1024):out.write(data)
    if p.stat().st_size!=end-begin+1:raise ValueError('Truncated range')
    return i,'downloaded'
   except Exception as exc:
    if attempt==4:raise
    time.sleep(min(2**attempt,8))
  raise AssertionError()
 with ThreadPoolExecutor(max_workers=8) as pool:
  futures=[pool.submit(acquire,i) for i in range((size+chunk-1)//chunk)]
  for k,f in enumerate(as_completed(futures),1):
   print('part',f.result(),'complete',k,'of',len(futures),flush=True)
 with dest.open('wb') as out:
  for i in range((size+chunk-1)//chunk):out.write((parts/f'{i:04d}.part').read_bytes())
with dest.open('rb') as f:actual=hashlib.file_digest(f,'sha256').hexdigest()
if actual!=digest:raise ValueError(f'SHA256 mismatch: {actual}')
with zipfile.ZipFile(dest) as z:
 if z.testzip() is not None:raise ValueError('Zip CRC failure')
 z.extractall(root)
(root/'ghidra12-source.json').write_text(json.dumps(dict(url=api,name=name,size=size,sha256=actual,upstream_digest=digest),indent=2),encoding='utf-8')
print('READY',root/'ghidra_12.1.4_PUBLIC',flush=True)
