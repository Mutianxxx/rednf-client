from pathlib import Path
import json
from reaction_model import sample_horizontal

HERE = Path(__file__).resolve().parent
evidence = json.loads((HERE/'evidence-index.json').read_text())
vectors = json.loads((HERE/'native-vectors.json').read_text())
assert vectors['matches'] == 126 and vectors['mismatches'] == 0
contract = dict(schema='60us-reaction-motion-bounded-v1', source_sha256=evidence['sha256'],
    original_client_runtime_observed=False,
    scope='decoded-input state3 horizontal setup; gravity/impulse arithmetic, not full reaction execution',
    state3=dict(apply='0x4bb091', tick='0x4bd06a',
        payload=['direction','scaleInteger','damageVariant','optional3=0','optional4=0'],
        scale='float32(scaleInteger * float32(.01))',
        call=dict(slot='0x518',target='0x4ba620',
            args=['&speed','&acceleration','optional4','optional3==2','scaleFloat'],
            callee_pop_bytes=20),
        duration_storage='protected actor+0x16c0',
        threshold='timer(actor+0x1564)>=duration',
        state_request_on_threshold={'virtual410(3)=true':9,'false':0},
        request_application_automatic=False),
    horizontal=dict(stats=['decoded stats+218','decoded_float32 stats+220'],
        stats_source='actor.virtual344(3); both reads assumed stable',
        ordinary_duration='trunc(trunc(max(int32(2000-trunc(f32(stat218)*f32(stat220))),0)*.25f)*f32(scale))',
        kind1_speed=800, kind2_speed=400, kind12_duration='trunc(f32(scale)*333.0f)',
        ordinary_deceleration_caps={'flag=true':0,'kind=-1,flag=false':30,'other':150},
        acceleration='idiv(int32(speed*-1000),min(cap,duration)); zero denominator -> zero acceleration',
        zero_motion_gate='decoded actor18D8=0 clears speed/acceleration, preserves duration',
        direction_applied_separately=True),
    gravity=dict(function='0x4b9fa0',true_base=-1500,false_base='protected actor+163c',
        map_offset='mapdata+9dc + actor+1660, only if mapdata exists and true/base!=0',
        false_scale='idiv(int32(trunc(f32(stats238)*f32(stats240))*base_with_map),100)',
        installation='0x4ba0c0: mode1=true, mode2=false, other explicit; axis2 countdown=-1'),
    artifacts={'evidence':'evidence-index.json','numeric_model':'reaction_model.py',
        'native_vectors':'native-vectors.json','native_verifier':'native_verify.py'},
    verification=dict(matches=126,mismatches=0,kind=vectors['evidence_kind']),
    unknowns=['Runtime stats, map offsets and clock/hitpause inputs',
        'Full state4 reentry/randomization/bounce/landing lifecycle',
        'Hit acceptance and absolute HP computation',
        'ACT execution, state request acceptance and native visual comparison'])
(HERE/'reaction-motion-contract.json').write_text(json.dumps(contract,indent=2)+'\n',encoding='utf8')
sample = sample_horizontal(0,False,100,1000,1.0,True,[50,50,50,50,50],initial_xyz=(0,0,12))
(HERE/'example-horizontal.json').write_text(json.dumps(sample,indent=2)+'\n',encoding='utf8')
print('Reaction contract and explicit-input horizontal sample written; native vectors 126/126')
