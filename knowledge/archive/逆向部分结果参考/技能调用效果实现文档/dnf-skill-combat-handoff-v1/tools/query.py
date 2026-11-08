"""Inspect a skill implementation or an exact raw PVF source member."""
from pathlib import Path
import argparse, json, sys

root=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(root/'derivation/lib'))
from prepare_content import PackedPvf, script

def main():
    p=argparse.ArgumentParser();group=p.add_mutually_exclusive_group(required=True)
    group.add_argument('--skill',help='e.g. hopsmash, bloodsword');group.add_argument('--source',help='normalized PVF path');a=p.parse_args()
    if a.source:value=script(PackedPvf(),a.source.replace('\\','/').lower())
    else:
        rows=json.loads((root/'docs/skills-index.json').read_text('utf8'))
        value=next((s for s in rows if s['key']==a.skill),None)
        if value is None:raise SystemExit('Unknown core skill; see demo/content/skills.json for catalog records.')
    print(json.dumps(value,ensure_ascii=False,indent=2))

if __name__=='__main__':main()
