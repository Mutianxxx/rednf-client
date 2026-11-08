from pathlib import Path
import hashlib
import importlib.metadata
import json
import subprocess
import sys
root=Path(__file__).resolve().parent
workspace=root.parent
sys.path.insert(0,str(root/'angr_deps'))
inventory=json.loads((root/'inventory.json').read_text(encoding='utf-8'))
sources=[]
for entry in inventory:
    source=workspace/entry['path']
    with source.open('rb') as f:
        digest=hashlib.file_digest(f,'sha256').hexdigest()
    if digest!=entry['sha256']:
        raise RuntimeError(f'Source changed: {source}')
    sources.append(dict(path=str(source),sha256=digest,unchanged=True))
verified=subprocess.run([str(root/'pvf60_verify.exe'),str(workspace/'DFO'/'Script.pvf')],capture_output=True,text=True,check=True)
native=json.loads(verified.stdout)
summary=json.loads((root/'pvf'/'summary.json').read_text(encoding='utf-8'))
if native['files_verified']!=summary['verified_contents'] or native['files_verified']!=99501:
    raise RuntimeError('Independent verifier counts differ')
wrong=subprocess.run([str(root/'pvf60_verify.exe'),str(workspace/'DFO'/'Script.pvf'),'0x81a79011'],capture_output=True,text=True)
if wrong.returncode!=1 or 'CRC mismatch' not in wrong.stderr:
    raise RuntimeError('Wrong-key rejection failed')
versions={name:importlib.metadata.version(name) for name in ['angr','pefile','capstone']}
result=dict(sources=sources,python_verification=summary['verified_contents'],
    cpp_verification=native,wrong_key_rejected=dict(key='0x81a79011',exit_code=wrong.returncode,error=wrong.stderr.strip()),
    tools=versions,game_executed=False,original_exe_independently_unpacked=False,
    pseudocode_count=len(list((root/'decompiled').glob('*.c'))),
    skill=dict(name='ghidra-rpc',repository='https://github.com/cellebrite-labs/ghidra-rpc',
        path='C:/Users/16908/.codex/skills/ghidra-rpc',
        sha256=hashlib.sha256(Path('C:/Users/16908/.codex/skills/ghidra-rpc/SKILL.md').read_bytes()).hexdigest(),
        runtime_ready=False,reason='Official Ghidra release download incomplete; offline angr used.'))
(root/'verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(result,ensure_ascii=True,indent=2))
