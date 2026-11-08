"""Verify package hashes, resource member bytes, evidence, and optionally runtime."""
from pathlib import Path
import argparse, hashlib, json, os, subprocess
from verify_evidence import verify as evidence
from verify_asset_closure import verify as asset_closure

def digest(path):
    h=hashlib.sha256()
    with path.open('rb') as f:
        for b in iter(lambda:f.read(1048576),b''):h.update(b)
    return h.hexdigest()

def verify(root,check_manifest=True):
    report=dict(ok=False,errors=[])
    if check_manifest:
        m=json.loads((root/'manifest.json').read_text('utf8'));n=0
        for name,e in m['files'].items():
            p=root/name
            if not p.is_file() or p.stat().st_size!=e['size'] or digest(p)!=e['sha256']:report['errors'].append('file hash: '+name)
            n+=1
        report['manifest_files']=n
    assets=root/'demo/client-assets';a=json.loads((assets/'asset-manifest.json').read_text('utf8'))
    b=json.loads((root/'demo/content/battle.json').read_text('utf8'))
    assert a['source_exe_sha256']==b['source_exe_sha256']
    for archive in a['archives']:
        p=assets/archive['path'];assert digest(p)==archive['sha256'],str(p)
    streams={};count=0
    try:
        for entry in a['members']:
            path=assets/entry['archive']
            if path not in streams:streams[path]=path.open('rb')
            f=streams[path];f.seek(entry['offset']);raw=f.read(entry['size'])
            assert len(raw)==entry['size'] and hashlib.sha256(raw).hexdigest()==entry['member_sha256'],entry['logical_path'];count+=1
    finally:
        for f in streams.values():f.close()
    report['original_IMG_references']=count;report['npk_archives']=len(a['archives']);report['evidence']=evidence(root)
    raw=root/'derivation/raw';idx=json.loads((raw/'index.json').read_text('utf8'))
    assert digest(raw/'members.bin')==idx['members_sha256'];assert digest(raw/'directory-paths.txt.gz')==idx['directory_sha256']
    n=0
    with (raw/'members.bin').open('rb') as f:
        for path,e in idx['entries'].items():
            f.seek(e['offset']);data=f.read(e['size']);assert len(data)==e['size'] and hashlib.sha256(data).hexdigest()==e['sha256'],path;n+=1
    report['raw_PVF_members']=n;report['asset_closure']=asset_closure(root)
    report['ok']=not report['errors'] and report['asset_closure']['passed'];return report

def main():
    p=argparse.ArgumentParser();p.add_argument('--runtime',action='store_true');p.add_argument('--no-manifest',action='store_true');args=p.parse_args()
    root=Path(__file__).resolve().parents[1];r=verify(root,not args.no_manifest)
    if args.runtime and r['ok']:
        result=subprocess.run([str(root/'demo/battle_demo.exe'),'--verify'],cwd=root)
        r['runtime_exit_code']=result.returncode
        v=json.loads((root/'demo/reports/verification.json').read_text('utf8'))
        r['runtime']=v;r['ok']=r['ok'] and result.returncode==0 and v['passed']
    out=root/'demo/reports/delivery-verification.json';out.parent.mkdir(parents=True,exist_ok=True)
    out.write_text(json.dumps(r,ensure_ascii=False,indent=2),encoding='utf8')
    print(json.dumps({k:v for k,v in r.items() if k not in ('runtime','evidence')},ensure_ascii=False,indent=2));print('Report:',out)
    raise SystemExit(0 if r['ok'] else 1)

if __name__=='__main__':main()
