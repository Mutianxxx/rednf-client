"""Verify scalar source bindings, current-PVF endpoints and native edge cases."""
from pathlib import Path
from copy import deepcopy
from fractions import Fraction
import hashlib,json,struct,sys

ROOT=Path(__file__).resolve().parent
WORKSPACE=ROOT.parents[2]
sys.path.insert(0,str(ROOT.parent))
from static_evidence import chunk,SOURCE,SHA256,MD
from scalar_model import evaluate,model,f32,native_round_model


def main():
    checks=[]
    def check(name,value,detail=None):
        checks.append(dict(name=name,passed=bool(value),**({} if detail is None else {'detail':detail})))
    def same(name,a,b):check(name,a==b,dict(actual=a,expected=b))
    def at(va,hexdata,name):
        expected=bytes.fromhex(hexdata)
        same(name,chunk(va,len(expected))[0].hex(),expected.hex())
    contract=json.loads((ROOT/'scalar-contract.json').read_text(encoding='utf-8'))
    baseline=json.loads((ROOT/'unmodified-baseline-context.json').read_text(encoding='utf-8'))
    native=json.loads((ROOT/'native-evidence.json').read_text(encoding='utf-8'))
    same('source executable identity',SHA256,contract['source']['executable_sha256'])
    with (WORKSPACE/'DFO/Script.pvf').open('rb') as stream:
        same('current PVF archive identity',hashlib.file_digest(stream,'sha256').hexdigest(),contract['source']['pvf_sha256'])
    for row in native['excerpts']:
        raw=(ROOT/row['binary']).read_bytes()
        captured,off=chunk(row['start_va'],row['length'])
        check('capture '+row['binary'],raw==captured and off==row['file_offset'] and hashlib.sha256(raw).hexdigest()==row['sha256'])
        dis='\n'.join(f'{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in MD.disasm(raw,row['start_va']))
        check('assembly '+row['assembly'],(ROOT/row['assembly']).read_text(encoding='utf-8')==dis)
    for row in native['reused_excerpts']:
        raw=(WORKSPACE/row['base']/row['binary']).read_bytes()
        captured,off=chunk(int(row['va'],16),row['size'])
        check('reused '+row['name'],raw==captured and off==row['file_offset'] and hashlib.sha256(raw).hexdigest()==row['sha256'])
    for row in json.loads((ROOT/'rea-evidence.json').read_text(encoding='utf-8')):
        raw=(WORKSPACE/row['path']).read_bytes()
        data=json.loads(raw)['structuredContent']
        check('REA '+row['parameters']['procedure'],hashlib.sha256(raw).hexdigest()==row['sha256'] and
              data['evidence_id']==row['evidence_id'] and data['subject']['digest']['sha256']==SHA256)

    resources=json.loads((ROOT.parent/'resources.json').read_text(encoding='utf-8'))
    skill=next(x for x in resources['resources'] if x['path']==contract['source']['skill'])
    raw=(ROOT.parent/skill['raw_export']).read_bytes()
    same('current SKL export identity',hashlib.sha256(raw).hexdigest(),contract['source']['skill_sha256'])
    for section in ('dungeon','pvp'):
        table=contract['tables'][section]
        for index,token in enumerate(table['source']['value_tokens']):
            same(f'{section} current SKL token {index}',raw[token['start']:token['end']].decode('ascii'),str(token['value']))
    same('dungeon level-info column count',contract['tables']['dungeon']['column_count'],1)
    same('dungeon level-info rows',contract['tables']['dungeon']['rows'],30)
    same('pvp level-info rows',contract['tables']['pvp']['rows'],20)
    same('maximum-level PVF metadata',contract['runtime_metadata']['maximum_level']['current_pvf'],20)
    same('required-level PVF metadata',contract['runtime_metadata']['required_level']['current_pvf'],20)
    same('required-range PVF metadata',contract['runtime_metadata']['required_level_range']['current_pvf'],3)

    # Bind pivotal arguments/branches to source bytes, not decompiler type guesses.
    at(0x73C2B3,'e868e7d8ff','skill32 native scalar call')
    at(0x4CAA2D,'5050','bridge duplicates actor context')
    at(0x550117,'3bcf7427','equal context skips base ratio')
    at(0x5500D3,'3bf97209','unsigned level-index bounds')
    at(0x5500EC,'8d4e08','modifier runtime key from skill+8')
    at(0x5500F9,'506a01535751','modifier queryKind1 and argument order')
    at(0x54FD53,'85c0741683f8027511','primary mode filter only value2 gates')
    at(0x54FD7D,'833e06','actor filter wildcard6')
    at(0x54FDF6,'83c028','primary row stride40')
    at(0x54FF2E,'83c328','secondary row stride40')
    at(0x54FF3D,'83fb17','23 source slots')
    at(0x54FDC6,'d80dac10cc00d84d0cd8450c','native ordered percent arithmetic')
    at(0x5501E2,'f7f9','native effective-level signed division')
    at(0x5501E4,'8d9e78010000','reference cap is separate skill+178')
    at(0x55020A,'6aff6aff52','reference query uses equal -1 contexts')
    at(0x55023A,'83f801','reference-cap1 slope special case')
    at(0x5502CE,'d86d14d91c24','projection explicit float32 store')
    at(0x55030E,'d84d08','context numerator multiplies rounded float32')
    at(0x550315,'d95d08','context numerator explicit float32 store')
    at(0x55031D,'d87d08','context quotient uses stored numerator')
    at(0x550343,'d84d08d95d08','global multiplier explicit float32 store')
    at(0xCC10AC,'0ad7233c','current native percent constant float32')
    same('native multiplier initial values',struct.unpack('<ff',chunk(0xF5E954,8)[0]),(1.0,1.0))
    pointers=struct.unpack('<II',chunk(0x43AC28,8)[0]);remap=chunk(0x43AC30,6)[0]
    same('43ABF0 native true mode set',[i+4 for i,k in enumerate(remap) if pointers[k]==0x43AC1C],[4,6,7,9])

    for section,expected in [('dungeon',{1:552,20:3056,30:5158,31:0}),('pvp',{1:172,20:1954,30:0})]:
        for level,value in expected.items():same(f'{section} baseline level{level}',model(level,baseline,section=section)['scalar'],value)
    for level in (0,-1,-200):same(f'callsite lower clamp {level}',model(level,baseline)['scalar'],552)
    check('level30 marked above PVF maximum',model(30,baseline)['beyond_current_maximum'])
    check('baseline is not runtime observation',model(1,baseline)['observed_runtime'] is False)
    same('missing modifier snapshot not silently empty',evaluate(1,{'mode_id':3,'secondary_mode_gate':False})['status'],'needs_explicit_runtime_input')
    incomplete=deepcopy(baseline);incomplete['modifier_snapshot_complete']=False
    same('incomplete modifier snapshot rejected',evaluate(1,incomplete)['status'],'needs_explicit_runtime_input')
    row=dict(actor_filter=6,skill_key=900,column=0,percent_mode=0,amount=10,query_kind=1,mode_filter=0)
    def context(primary=(),secondary=(),**extra):
        result=deepcopy(baseline)
        result.update(runtime_skill_key=900,modifier_sources=[dict(slot=0,primary=list(primary),secondary=list(secondary),
                      secondary_gate_12c=True,secondary_gate_118=True)])
        result.update(extra);return result
    same('additive runtime row',model(1,context([row]))['scalar'],562)
    percent=dict(row,percent_mode=1,amount=10)
    same('percent10 truncation',model(1,context([percent]))['scalar'],607)
    same('ordered add then percentage',model(1,context([row,percent]))['scalar'],618)
    same('ordered percentage then add',model(1,context([percent,row]))['scalar'],617)
    same('primary before secondary',model(1,context([percent],[row]))['scalar'],617)
    same('wildcard actor filter needs no actor identity',model(1,context([row]))['scalar'],562)
    same('wrong runtime key excluded',model(1,context([dict(row,skill_key=32)]))['scalar'],552)
    missing_key=context([row]);del missing_key['runtime_skill_key']
    same('runtime skill key not assumed32',evaluate(1,missing_key)['status'],'needs_explicit_runtime_input')
    same('wrong query kind excluded',model(1,context([dict(row,query_kind=2)]))['scalar'],552)
    same('wrong column excluded',model(1,context([dict(row,column=1)]))['scalar'],552)
    same('specific matching actor filter',model(1,context([dict(row,actor_filter=2)],actor_filter=2))['scalar'],562)
    same('specific mismatching actor filter',model(1,context([dict(row,actor_filter=2)],actor_filter=3))['scalar'],552)
    same('primary mode2 requires43ABF0',model(1,context([dict(row,mode_filter=2)]))['scalar'],552)
    same('secondary has no mode2 filter',model(1,context([], [dict(row,mode_filter=2)]))['scalar'],562)
    for gate in ('secondary_gate_12c','secondary_gate_118'):
        c=context([], [row]);c['modifier_sources'][0][gate]=False
        same('secondary false '+gate,model(1,c)['scalar'],552)
    same('out-of-bounds skips additive modifier',model(30,context([row]),section='pvp')['scalar'],0)
    same('additive signed32 wrapping',model(1,context([dict(row,amount=2**31-1)]))['scalar'],-2147483097)
    same('negative percentage truncates toward zero',model(1,context([dict(percent,amount=-110)]))['scalar'],-55)

    active=deepcopy(baseline);active.update(mode_id=4)
    same('active mode needs runtime context',evaluate(1,active)['status'],'needs_explicit_runtime_input')
    active['actor_context_stat']=77
    same('active mode needs separate cap',evaluate(1,active)['reason'],'missing runtime input: runtime_reference_cap_178')
    active.update(runtime_reference_cap_178=20,rounding_half_global=0.5,environment_global_f5e954=1)
    same('explicit mode4 projection level1',model(1,active)['scalar'],567)
    same('explicit mode4 projection level30',model(30,active)['scalar'],4366)
    same('truncated integer slope',next(x for x in model(1,active)['trace'] if x['event']=='environment_projection')['slope'],131)
    c=dict(active,actor_context_stat=20)
    same('factor not silently1',evaluate(1,c)['reason'],'missing runtime input: context_factor_448150')
    c['context_factor_448150']={'77':2,'20':1}
    same('explicit context factor ratio',model(1,c)['scalar'],6112)
    c=dict(active,actor_context_stat=0,context_factor_448150={'77':1,'0':1})
    same('effective level has no lower clamp',next(x for x in model(1,c)['trace'] if x['event']=='environment_projection')['effective'],-5)
    same('negative effective projected result',model(1,c)['scalar'],3842)
    c=dict(active,actor_context_stat=20,runtime_reference_cap_178=1)
    same('cap1 uses raw row2 minus row1',next(x for x in model(30,c)['trace'] if x['event']=='environment_projection')['slope'],83)
    same('cap1 level30 projection',model(30,c)['scalar'],2959)
    c=dict(active,mode_id=3,secondary_mode_gate=True,environment_global_f5e958=2)
    same('secondary mode selects F5E958',model(1,c)['scalar'],1134)
    for mode in (3,5,8,10):
        c=dict(baseline,mode_id=mode)
        same('mode gate false '+str(mode),model(1,c)['scalar'],552)
    same('actor context -1 bypasses environment',model(1,dict(active,actor_context_stat=-1))['scalar'],552)
    same('runtime range0 bypasses environment',model(1,dict(active,runtime_required_level_range=0))['scalar'],552)
    same('runtime maximum1 bypasses environment',model(1,dict(active,runtime_maximum_level=1))['scalar'],552)
    same('447FF0 positive tie',native_round_model(Fraction(5,2),0.5),3)
    same('447FF0 negative tie',native_round_model(Fraction(-5,2),0.5),-3)
    same('float32 nearest-even tie',f32(2**24+1),Fraction(2**24))
    same('float32 subnormal nearest-even zero',f32(Fraction(1,2**150)),Fraction(0))
    same('float32 subnormal nearest-even up',f32(Fraction(3,2**150)),Fraction(1,2**148))
    result=dict(schema='60us-releasewave-scalar-verification-v1',passed=sum(x['passed'] for x in checks),total=len(checks),
                observed_native_execution=False,checks=checks)
    (ROOT/'verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2,default=str),encoding='utf-8')
    print(json.dumps(dict(passed=result['passed'],total=result['total'],failed=[x for x in checks if not x['passed']]),ensure_ascii=False,default=str))
    if result['passed']!=result['total']:raise SystemExit(1)

if __name__=='__main__':main()
