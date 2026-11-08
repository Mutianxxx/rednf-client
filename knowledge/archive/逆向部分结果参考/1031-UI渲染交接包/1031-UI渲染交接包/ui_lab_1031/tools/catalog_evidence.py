"""Bind all UI tokens to exact decrypted bytes without re-running string decoding."""
import hashlib, importlib.util, json, struct
from pathlib import Path
from common import ROOT,WORK,CLIENT,verify_client

def main():
    verify_client(True)
    spec=importlib.util.spec_from_file_location('ui1031_pvf',WORK/'combat_ui_1031/tools/pvf_reader.py');reader=importlib.util.module_from_spec(spec);spec.loader.exec_module(reader)
    pvf=reader.Pvf(CLIENT/'Script.pvf');scripts=json.loads((ROOT/'catalog/scripts.json').read_text('utf8'));index=json.loads((ROOT/'catalog/index.json').read_text('utf8'));by_path={r['path']:r for r in index['windows']}
    try:
        for script in scripts:
            path=script['path'];raw=pvf.read(path);target=(ROOT/'catalog/raw'/Path(path+'.bin')).resolve();target.relative_to((ROOT/'catalog/raw').resolve());target.parent.mkdir(parents=True,exist_ok=True);target.write_bytes(raw)
            if raw:
                rebuilt=b''.join(struct.pack('<Bi',t['type'],t['raw']) for t in script['tokens'])
                if rebuilt!=raw[2:]:raise ValueError('Native/Python token disagreement: '+path)
            evidence=dict(sha256=hashlib.sha256(raw).hexdigest(),raw_file=target.relative_to(ROOT).as_posix(),header_hex=raw[:2].hex(),pvf_entry=pvf.by_name[path])
            script.update(evidence);by_path[path].update(evidence)
    finally:pvf.close()
    for file,value in [('scripts.json',scripts),('index.json',index)]:
        p=ROOT/'catalog'/file;t=p.with_suffix('.json.new');t.write_text(json.dumps(value,ensure_ascii=False,indent=2),'utf8');t.replace(p)
    print(json.dumps(dict(verified=len(scripts),native_token_roundtrip=True),ensure_ascii=False))

if __name__=='__main__':main()
