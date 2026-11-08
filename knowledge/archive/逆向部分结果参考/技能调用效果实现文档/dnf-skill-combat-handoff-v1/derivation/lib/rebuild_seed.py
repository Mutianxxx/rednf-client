"""Recreate the normalized seed byte-for-byte from frozen raw members.
The seed catalog, appearance profile and string-ID/index order are frozen inputs.
"""
from pathlib import Path
import collections, hashlib, json, struct
from frozen_pvf import PackedPvf
from prepare_content import script, animation

def rebuild_seed():
    root=Path(__file__).resolve().parents[1]/'seed'
    expected=json.loads((root/'expected.json').read_text('utf8'))
    output=root/'cache/resources.bin'
    if output.exists() and hashlib.sha256(output.read_bytes()).hexdigest()==expected['resources_bin_sha256']:
        print('Seed normalized cache already verified',flush=True);return
    index=json.loads((root/'cache/index.json').read_text('utf8'))
    if hashlib.sha256((root/'cache/index.json').read_bytes()).hexdigest()!=expected['index_sha256']:raise ValueError('Seed index hash')
    p=PackedPvf();ids={s:i for i,s in enumerate(index['strings'])};stats=collections.Counter()
    temp=output.with_suffix('.tmp')
    with temp.open('wb') as f:
        for n,(path,e) in enumerate(index['entries'].items()):
            s=script(p,path)
            if s['raw_sha256']!=e['raw_sha256']:raise ValueError('Raw source identity: '+path)
            if path.endswith('.ani'):data=json.dumps(animation(s,stats),ensure_ascii=False,separators=(',',':')).encode('utf8')
            else:
                data=bytearray(b'\xb0\xd0')
                for t in s['tokens']:
                    typ=t['type']
                    if typ in (0,2):nt,nv=(2 if typ==0 else 4),t['raw']
                    else:nt,nv=(5 if typ==3 else 6),ids[t['value']]
                    data.extend(struct.pack('<BI',nt,nv))
            if f.tell()!=e['offset'] or len(data)!=e['size']:raise ValueError('Seed layout mismatch: '+path)
            f.write(data)
            if n%10000==0:print('Normalized seed members',n,flush=True)
    digest=hashlib.sha256(temp.read_bytes()).hexdigest()
    if digest!=expected['resources_bin_sha256']:raise ValueError('Seed byte reproduction mismatch: '+digest)
    temp.replace(output);print('Seed byte-for-byte reproduction passed',digest,flush=True)

if __name__=='__main__':rebuild_seed()
