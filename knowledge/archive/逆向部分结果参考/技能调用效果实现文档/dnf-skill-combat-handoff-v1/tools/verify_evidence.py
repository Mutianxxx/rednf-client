"""Independent verification of the self-contained, selected chain evidence.
Full historical process logs and the complete readonly module are not bundled.
"""
from pathlib import Path
import hashlib, json, struct

def verify(root):
    e=root/'evidence/skill-chain-analysis';read=lambda p:json.loads(p.read_text('utf8'))
    code=read(e/'code-evidence.json');spans=0;source=0;calls=0
    for s in code['spans']:
        assert hashlib.sha256(bytes.fromhex(s['bytes'])).hexdigest()==s['sha256'],s['name'];spans+=1
    graph=read(e/'source-graph.json')
    for n in graph['nodes']:
        digest=n['raw_sha256'];raw=(e/'sources'/f'{digest}.bin').read_bytes()
        assert len(raw)==n['raw_bytes'] and hashlib.sha256(raw).hexdigest()==digest,n['path']
        parsed=read(e/'sources'/f'{digest}.json')
        # Several logical ANI paths contain identical bytes; archives are keyed
        # by content hash, so their token JSON may name another identical path.
        assert parsed['raw_sha256']==digest,n['path']
        assert len(parsed['tokens'])==len(raw)//5,n['path']
        for t,(typ,value) in zip(parsed['tokens'],struct.iter_unpack('<BI',raw)):
            assert t['type']==typ and t['raw']==value,n['path']
        source+=1
    chains=[]
    for path in sorted((e/'skills').glob('*.json')):
        skill=read(path)
        for phase in skill['phase_observations']:
            for c in phase['spawn_chains']:
                call=c.get('controller_call',{})
                if not call.get('direct_call_verified'):continue
                b=bytes.fromhex(call['bytes']);va=int(call['instruction_va'],16)
                assert len(b)==5 and b[0]==0xe8
                target=(va+5+struct.unpack('<i',b[1:])[0])&0xffffffff
                assert target==int(call['expected_target'],16)==int(call['decoded_direct_target'],16)
                assert va+5==int(call['return_va'],16)
                if c['call_chain_verified']:
                    assert all(c['checks'].values())
                    assert c['request']['object_id']==c['core']['object_id']==c['object_id']
                calls+=1;chains.append(dict(skill=skill['key'],sample=phase['sample'],object_id=c['object_id'],seq=c['request']['seq'],target=hex(target)))
    assert calls==code['verified_spawn_calls'],(calls,code['verified_spawn_calls'])
    return dict(ok=True,machine_code_spans=spans,raw_source_nodes=source,verified_E8_spawn_calls=calls,chains=chains,
        limit='Checks exact retained bytes and recorded chain summaries. Full original log replay is outside this package.')

if __name__=='__main__':print(json.dumps(verify(Path(__file__).resolve().parents[1]),ensure_ascii=False,indent=2))
