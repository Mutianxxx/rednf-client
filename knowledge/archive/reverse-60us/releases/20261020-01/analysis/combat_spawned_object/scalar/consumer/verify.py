"""Verify consumer bridge bytes, retained evidence and bounded numeric examples."""
from pathlib import Path
from copy import deepcopy
import json,hashlib,struct,sys
ROOT=Path(__file__).resolve().parent
WORKSPACE=ROOT.parents[3]
sys.path.insert(0,str(ROOT.parents[1]))
from static_evidence import chunk,SHA256,MD
from consumer_model import evaluate,initial_multiplier,normal_base


def main():
    checks=[]
    def check(name,value,detail=None):checks.append(dict(name=name,passed=bool(value),**({} if detail is None else dict(detail=detail))))
    def same(name,a,b):check(name,a==b,dict(actual=a,expected=b))
    def at(va,expected,name):same(name,chunk(va,len(bytes.fromhex(expected)))[0].hex(),expected)
    evidence=json.loads((ROOT/'evidence.json').read_text(encoding='utf-8'))
    contract=json.loads((ROOT/'consumer-contract.json').read_text(encoding='utf-8'))
    same('source executable',SHA256,contract['source']['executable_sha256'])
    for row in evidence['excerpts']:
        data=(ROOT/row['binary']).read_bytes();expected,off=chunk(row['va'],row['length'])
        check('capture '+row['name'],data==expected and hashlib.sha256(data).hexdigest()==row['sha256'] and off==row['file_offset'])
        asm='\n'.join(f'{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in MD.disasm(data,row['va']))
        check('assembly '+row['name'],(ROOT/row['assembly']).read_text(encoding='utf-8')==asm)
    for row in evidence['reused_excerpts']:
        data=(WORKSPACE/row['base']/row['binary']).read_bytes();expected,off=chunk(int(row['va'],16),row['size'])
        check('reuse '+row['name'],data==expected and hashlib.sha256(data).hexdigest()==row['sha256'] and off==row['file_offset'])
    for row in evidence['external_references']:
        same('external '+row['path'],hashlib.sha256((WORKSPACE/row['path']).read_bytes()).hexdigest(),row['sha256'])
    for row in evidence['rea_evidence']:
        data=(WORKSPACE/row['path']).read_bytes();d=json.loads(data)['structuredContent']
        check('REA '+row['parameters']['procedure'],hashlib.sha256(data).hexdigest()==row['sha256'] and
              d['evidence_id']==row['evidence_id'] and d['subject']['digest']['sha256']==SHA256)
    resources=json.loads((ROOT.parents[1]/'resources.json').read_text(encoding='utf-8'))
    atk=next(r for r in resources['resources'] if r['path']==contract['source']['attackinfo'])
    raw=(ROOT.parents[1]/atk['raw_export']).read_bytes()
    same('current ATK export identity',hashlib.sha256(raw).hexdigest(),contract['source']['attackinfo_sha256'])
    for tag in ('damage','absolute damage','damage bonus','weapon damage apply'):
        check('PVF absent '+tag,not any(r['tag']==tag for r in atk['fields']))
    at(0x5C77B3,'db4508','constructor signed scalar fild')
    at(0x5C77C2,'d95d08','constructor scalar float32 store')
    at(0x5C77C5,'8b86e0050000','protected template damage index5E0')
    at(0x49FAFB,'8d8edc050000','PVF ATK template destination')
    at(0x49FB01,'e8da2c0000','PVF ATK template copy')
    at(0x437F89,'e8a2d4ffff','ATK constructor calls reset')
    at(0x4354E7,'c7461800000000','reset attack type0')
    at(0x4354B2,'8b0dd8012101','reset bonus protected slot write prefix')
    at(0x4354F7,'8b4620','reset weapon apply protected slot index')
    at(0x8C43B2,'ff9044030000','spawn owner slot344')
    at(0x8C43CA,'e8a199c4ff','spawn scene register call')
    at(0x50DFF3,'ff5210','normal register entity slot10')
    at(0x49F01A,'8d8edc050000','source template ATK pointer')
    at(0x49F023,'ff9098010000','template ATK install slot198')
    at(0x49F029,'8b8648010000','runtime action pointer override')
    at(0x49F034,'8db8b0000000','action ATK at+B0')
    at(0x49F076,'ff9298010000','action override installs same slot198')
    at(0x4EDCDB,'8d8e60020000','install destination current+260')
    at(0x4EDCF8,'e8e34afbff','nonnull ATK copy4A27E0')
    at(0x4EDD01,'ff90a0010000','nonnull ATK install resets hit history')
    at(0x438650,'8d8160020000c3','current getter returns+260')
    at(0x4EB798,'ff909c010000','numeric pack attacker current ATK')
    at(0x4EB974,'e8377af4ff','numeric reads protected damage float')
    at(0x4EB979,'d99d28feffff','damage to numeric+0')
    at(0x4EB996,'8d4b10','bonus source independently ATK+10')
    at(0x4EB9A4,'d99d2efeffff','bonus numeric+6 f32')
    at(0x49DD6D,'ff90d8010000','snapshot owner weapon0 getter')
    at(0x49DD73,'8987a0070000','snapshot stores+7A0')
    at(0x49DDAD,'ff90e8010000','snapshot owner weapon1 getter')
    at(0x49DDB3,'8987b0070000','snapshot stores+7B0')
    at(0x4390E0,'8b81a0070000c3','weapon0 snapshot getter')
    at(0x439120,'8b81b0070000c3','weapon1 snapshot getter')
    at(0x49EE85,'c786e400000021000000','passive type mask21')
    at(0x407B60,'8b81e4000000c3','type mask getter')
    at(0x455B83,'88888e010000','numeric alternate byte18E default0')
    at(0x8E49B0,'32c0c3','Swordman owner slot1BC false')
    at(0x4390B2,'ffa2bc010000','passive slot1BC forwards to owner')
    at(0x8B862A,'e891f3ffff','normal base dispatch')
    at(0x8B79E1,'d84633','type1 weapon operand numeric33')
    at(0x8B79E6,'d8462f','type0/2 operand numeric2F')
    at(0x8B79E9,'d94606','base multiplier reads bonus numeric6')
    at(0x8B79FF,'d95d08','base initial stage float32 store')
    at(0x8B866F,'d95d08','normal base result float32 store')
    at(0x4EC9F4,'e857bc3c00','common numeric call8B8650')
    at(0x8B8E8B,'e8b4863400','numeric terminal C01544')
    at(0x8B8E91,'8986bd010000','numeric terminal result+1BD')
    at(0x4B2ECD,'8945ec','save returned numeric integer')
    at(0x4B3031,'017dec','possible HP-derived damage addition')
    at(0x4B312F,'2b45ec','ordinary HP subtraction uses downstream value')
    at(0x4B3135,'ff97e8030000','absolute HP update slot3E8')
    for offset,value in [('10',0x49F010),('198',0x4EDCD0),('19C',0x438650),('1BC',0x439090),('344',0x49DD10),('380',0x49F010)]:
        same('ReleaseWave vtable slot'+offset,struct.unpack('<I',chunk(0xD057D4+int(offset,16),4)[0])[0],value)
    same('Swordman owner vtable1BC',struct.unpack('<I',chunk(0xD80F94+0x1BC,4)[0])[0],0x8E49B0)
    context=json.loads((ROOT/'declared-template-context.json').read_text(encoding='utf-8'))
    for scalar in (552,5158):
        result=evaluate(scalar,context)
        same('template base scalar'+str(scalar),result['installed_current_atk']['damage'],float(scalar))
        same('first-stage scalar'+str(scalar),result['first_numeric_stage']['value_f32'],float(scalar))
        same('no invented final damage'+str(scalar),result['final_victim_damage'],None)
        check('no native runtime claim'+str(scalar),result['observed_runtime'] is False)
    for key in ('slot10_registration_reached','current_atk_snapshot_unchanged','action_atk_override','normal_base_route_established'):
        c=deepcopy(context);del c[key]
        same('missing bridge input '+key,evaluate(552,c)['status'],'needs_explicit_runtime_input')
    c=deepcopy(context);c['action_atk_override']=dict(damage=10,absolute_damage=0,damage_bonus=0,attack_type=1,weapon_damage_apply=False)
    same('action ATK override supersedes scalar',evaluate(552,c)['first_numeric_stage']['value_f32'],10.0)
    same('zero scalar common entry rejection',evaluate(0,context)['common_numeric_entry_result'],0)
    basic=dict(damage=552,damage_bonus=0,attack_type=1,weapon_damage_apply=False)
    same('weapon disabled ignores absent operand',initial_multiplier(basic,{})['value_f32'],552.0)
    same('magic weapon enabled adds operand',initial_multiplier(dict(basic,weapon_damage_apply=True),dict(numeric_33=100))['value_f32'],652.0)
    same('physic weapon enabled uses2F',initial_multiplier(dict(basic,weapon_damage_apply=True,attack_type=0),dict(numeric_2f=20,numeric_33=100))['value_f32'],572.0)
    same('bonus150 is independent multiplier',initial_multiplier(dict(basic,damage=100,damage_bonus=150),{})['value_f32'],250.0)
    same('first numeric stage has no integer truncation',initial_multiplier(dict(basic,damage_bonus=10),{})['value_f32'],607.2000122070312)
    numeric=dict(numeric_3b=0,numeric_43=0,numeric_18a=4,numeric_47=0)
    factors={'protected_global_10bfe78':250,'448c10_attacker_0':1}
    same('explicit neutral full base',normal_base(basic,numeric,factors)['value_f32'],552.0)
    same('stat ratio affects base without weapon apply',normal_base(basic,dict(numeric,numeric_43=250),factors)['value_f32'],1104.0)
    same('numeric47 enters as1+term',normal_base(basic,dict(numeric,numeric_47=1),factors)['value_f32'],1104.0)
    factors2=dict(factors,**{'448c10_attacker_5':2})
    same('explicit mode factor scales stat first',normal_base(basic,dict(numeric,numeric_18a=0,numeric_43=125),factors2)['value_f32'],1104.0)
    result=dict(schema='60us-skill32-consumer-verification-v1',passed=sum(x['passed'] for x in checks),total=len(checks),
                observed_native_execution=False,checks=checks)
    (ROOT/'verification.json').write_text(json.dumps(result,indent=2,default=str),encoding='utf-8')
    print(json.dumps(dict(passed=result['passed'],total=result['total'],failed=[x for x in checks if not x['passed']]),default=str))
    if result['passed']!=result['total']:raise SystemExit(1)

if __name__=='__main__':main()
