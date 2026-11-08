"""Record evidence-backed field origins and bounded arithmetic interfaces."""
from pathlib import Path
import json,sys,hashlib
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT.parent/'combat_spawned_object'))
from static_evidence import SHA256,chunk
from native_verify import template
from numeric_model import bounded,critical_stage,defense_ratio

def digest(path):return hashlib.file_digest(path.open('rb'),'sha256').hexdigest()
def main():
 resources_path=ROOT.parent/'combat_spawned_object/resources.json'
 resources=json.loads(resources_path.read_text(encoding='utf-8'))
 atk=next(r for r in resources['resources'] if r['path']=='passiveobject/character/swordman/attackinfo/releasewave.atk')
 raw_atk=ROOT.parent/'combat_spawned_object'/atk['raw_export']
 refs=[resources_path,raw_atk,ROOT.parent/'combat_spawned_object/scalar/scalar-contract.json',
       ROOT.parent/'combat_spawned_object/scalar/consumer/consumer-contract.json',
       ROOT.parent/'combat_attackinfo/hardattack-attackinfo-contract.json',
       ROOT.parent/'combat_spawned_object/scalar/consumer/008B8650-numeric_full.bin']
 mappings=[
  ('5','int8','ATK+18 attack type, packed4EB98D','0 physic,1 magic,2 ignore defense enumeration'),
  ('e','byte','ATK+138 protected int,4EBA4E..5C; [ignore defense] boolean parser837961..7996','gates defense stage and absolute victim subtraction'),
  ('f','float32','ATK+8 protected int converted f32,4EBA62..73; [absolute damage] parser836D46','absolute component input'),
  ('13','float32','ATK+100 protected float,4EBA79..84; [critical hit] parser837800..782D','ATK critical rate addend'),
  ('17','float32','ATK+1A4 protected float,4EBA8A..8F; parser tag not established','additional rate when numeric1B5 true'),
  ('1b','float32','ATK+1AC protected float,4EBA9B..AA0; parser tag not established','postcritical multiplier percent'),
  ('1f/23/27','float32','ATK+140/+148/+150 decoded int to f32,4EBAC0..BB2B','[human/fort/monster damage rate], independent runtime c3/c4/c5 gates'),
  ('4b/4f/53/57','float32 bit patterns','owner.slot2A4().slot344(3) protected +2C8/+2D0/+2D8/+2E0,4EC5A5..800; absent-owner branch writes0','kind0/1 critical and numeric1B5 critical additions'),
  ('5b','float32','4EBB63..87,521FF0 from owner context and level','alternate numeric18E critical addend'),
  ('5f','float32','attacker protected+518,4EBD2F..67','shared victim-reduction coefficient; packing uses max(1-value,0)'),
  ('63/67','int32','attacker.slot1E0/1F0,4EBD6B..81','weapon contribution to absolute component'),
  ('6f','float32','owner.slot2A4().slot500(attacker,victim),4EBDCF..E2; no owner writes0','critical multiplier when flags195 mask11 matches'),
  ('8b','int32','victim.slot344(3) ->4B5680,4EBE48..55','kind0 defense base'),
  ('8f','int32','victim.slot344(3) protected+310,4EBED0','kind0 defense bonus percent'),
  ('93','float32','victim.slot344(3) protected+2A8,4EBEE4..EF','kind0 extra reduction percent'),
  ('97','int32','victim.slot344(3) ->4B5760,4EBEFB..F08','kind1 defense base'),
  ('9b','int32','victim.slot344(3) protected+320,4EBF95','kind1 defense bonus percent'),
  ('9f','float32','victim.slot344(3) protected+2C0,4EBFA9..FB4','kind1 extra reduction percent'),
  ('a3/a7','float32','victim.slot344(3) protected+38/+40 and+58/+60 calculation,4EBFC0..4EC15C','additional flat subtraction, not the defense-ratio numerator'),
  ('ab','float32','victim protected+510,4EC154..199','weapon absolute contribution coefficient; packing uses max(1-value,0)'),
  ('af/b3','int32','victim.slot344(3) protected+2A0/+2B8,4EC21C/2AA','absolute subtraction operands'),
  ('b7/bb','int32','conditional victim.slotE4 protected+294,4EC39F..3EF','additional absolute subtraction operands'),
  ('bf','float32','victim.slot344(3) protected+2F8,4EC2BE..2C9','critical rate subtractend'),
  ('18a','int8','global mode packed4EC90F','mode4 fixed level50,mode6/7 runtime table level'),
  ('18b','int8','attacker.slot1D0 low byte packed4EC930','signed level for ordinary mode'),
  ('195/199','uint32','runtime type masks, caller packing','attacker/victim branch masks; do not replace with assumed player flags'),
  ('1b5','byte','4E90F0(victim,attacker) result packed4EB832','direction-dependent rate-addition predicate'),
  ('1bc','byte','43ABF0(-1) result packed4EC91B','doubles protected denominator scale'),
 ]
 contract=dict(schema='60us-bounded-damage-numeric-contract-v1',
  source=dict(executable='DFO/DFO_fixed_v3.exe',executable_sha256=SHA256,
   pvf='DFO/Script.pvf',pvf_sha256='23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98',
   current_atk=atk['path'],current_atk_sha256=atk['sha256'],encoding=atk['encoding']),
  status='static-client-evidence-and-284-native-arithmetic-fixtures-not-client-runtime-or-final-hp-damage',
  interface=dict(incoming='binary32 B at8B8808 after element and random-variation stages',
   outgoing='8B8B41 x87 value and last FST binary32 store; later factors and final integer are excluded',
   runtime_operands='numeric_* byte offsets plus explicitly supplied protected globals, 448C10 samples, RNG return and mode tables',
   callback='victim.slot320 effects excluded; combined model requires an explicit no-mutation snapshot declaration'),
  functions=dict(defense='8B7C90; ordinary caller8B8835',critical='8B7AB0; caller8B8A82',
   defense_caller='8B8808..8B88BF',attacker_stat='8B88BF..8B893A',absolute='8B893A..8B8A62',postcritical='8B8A87..8B8B41'),
  field_origins=[dict(numeric_offset='+'+a,storage=b,source=c,meaning=d) for a,b,c,d in mappings],
  ordinary_defense=dict(gate='(flags199&0x11)==0x11 && type!=2 && !numericE',
   defense='f32(baseInt*(1+bonusInt*f32(.01))); then f32(*448C10(victim,1))',
   ratio='f32(D / max(1, K*level + D)); K is protected10BFEB0(type0) or10BFED0(type1), doubled if1BC',
   low_level_exception='ONLY D<0 && signedEffectiveLevel<10: ratio=f32(D*f32(.0025))',
   extra='f32(numeric93_or9F*f32(.01))',caller='f32(B*((1-ratio)-extra*numeric5F)), then flat stat/divisor subtraction'),
  critical=dict(base_constant=3,scale_constant=100,
   threshold='critical iff x87(effectiveRateF32*100) > signedRNGReturn % 10000; IDIV remainder truncates toward zero',
   rate_clamp=False,return_and_byte='AL and numeric+1A5',
   multiplier='protected10BFE90 * numeric6F when flags195 mask0x11 matches',
   null_pointer='8B7AB0 returns AL0 for null damage pointer; bounded caller always passes nonnull; standalone model requires a value'),
  absolute=dict(applies_to_types=[0,1],
   expression='(numericF + [weaponApply ? int63_or67*numericAB : 0]) * (1+bonus6*.01) * (1+numeric37_or3B*.01)',
   precision='store absolute component f32 before attacker context7/9 multiplier and addition',
   victim_subtraction='when flags199 mask11 && !numericE: f32(intAF_orB3*numeric5F+intB7_orBB)*victimContext8/10',
   warning='bypasses earlier percentage-defense stage, but still receives these bonuses, victim subtraction, critical and later multipliers'),
  postcritical=dict(conditional_1a6_constant_va='DF5190',conditional_1a6_constant_f32=1.100000023841858,
   difference='numeric1A7=trunc((B*constant)-B), with extended product retained for further multiplication',
   scales='numeric1B*.01*int1AC*.01, conditional categories1F/23/27*.01, optional6B',
   minimum='max(value,1) only at8B8B29; later numeric stages can alter it',
   precision='FST8B8AD2/AE0/AF6/B0C/B26 stores f32 but keeps extended x87 stack value'),
  current_releasewave=dict(attack_type=1,absent_tags=[t for t in ['damage','absolute damage','damage bonus','weapon damage apply','critical hit','ignore defense'] if not any(x['tag']==t for x in atk['fields'])],
   inherited_evidence='existing scalar/consumer contract establishes positive scalar as installed current damage under explicit no-action-override context',
   unproven='Do not derive live critical rate, protected global denominator scales, owner stats or final damage from this ATK alone.'),
  references=[dict(path=str(p.relative_to(ROOT.parents[1])).replace('\\','/'),sha256=digest(p)) for p in refs],
  boundaries=['Earlier8B8650 element and random variation are supplied as incoming B, not reconstructed here.',
   '8B8B41..8B8E9C includes factor arrays, mode4/HP-dependent paths, later additions, C01544 and numeric1BD.',
   '4B28D0 may change returned numeric integer before ordinary4B312F HP subtraction.',
   'Original process, collision, graphics and final HP damage are not exercised by the synthetic harness.'])
 (ROOT/'numeric-contract.json').write_text(json.dumps(contract,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
 examples=[]
 n,e=template();n['numeric_97']=2000
 examples.append(dict(label='declared defense-only context, input552',numeric=n,external=e,result=bounded(552,n,e)))
 for rng in (299,300):
  n,e=template();e['8ae160_return']=rng
  examples.append(dict(label='critical threshold '+str(rng),numeric=n,external=e,result=critical_stage(552,n,e)))
 for level in (9,10):
  n,e=template();n.update(numeric_18b=level,numeric_97=-10)
  examples.append(dict(label='negative defense level'+str(level),numeric=n,external=e,result=defense_ratio(n,e)))
 for kind in (1,2):
  n,e=template(kind);n['numeric_f']=50
  examples.append(dict(label='absolute50 type'+str(kind),numeric=n,external=e,result=bounded(552,n,e)))
 (ROOT/'declared-examples.json').write_text(json.dumps(dict(observed_client_runtime=False,examples=examples),indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
 print(json.dumps(dict(field_origins=len(mappings),examples=len(examples))))

if __name__=='__main__':main()
