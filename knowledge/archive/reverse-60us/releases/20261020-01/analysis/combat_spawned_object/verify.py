"""Recheck immutable source identity, native anchors and current numeric registrations."""
from pathlib import Path
import json, hashlib, struct
from static_evidence import chunk, SOURCE, SHA256
from preview_contract import sample
ROOT=Path(__file__).resolve().parent
WORKSPACE=ROOT.parents[1]

def main():
    checks=[]
    def check(name,value):
        checks.append(dict(name=name,passed=bool(value)))
        if not value:raise AssertionError(name)
    contract=json.loads((ROOT/'preview-contract.json').read_text(encoding='utf-8'))
    index=json.loads((ROOT/'evidence-index.json').read_text(encoding='utf-8'))
    check('executable hash',SHA256==contract['source']['executable_sha256'])
    check('PVF hash',hashlib.sha256((WORKSPACE/'DFO/Script.pvf').read_bytes()).hexdigest()==contract['source']['pvf_sha256'])
    for record in index['native_captures']:
        data,off=chunk(record['start_va'],record['length'])
        stem=Path(record['path']).stem
        check('capture '+stem,off==record['file_offset'] and hashlib.sha256(data).hexdigest()==record['chunk_sha256']
              and data==(ROOT/(stem+'.bin')).read_bytes())
    def u32(va):return struct.unpack('<I',chunk(va,4)[0])[0]
    for label,va,expected in [
        ('Swordman spawn wrapper',0xD80F94+0x2B8,0x4EA4D0),
        ('Swordman attribute read',0xD80F94+0x1D0,0x744A50),
        ('opcode21 receive',0x8C5E64+21*4,0x8C4248),
        ('factory object20018',0x5F1F54+3*4,0x5EA85E),
        ('OBJ manager load slot',0xE4C4F4+8,0xA618E0),
        ('OBJ manager type2',0xA61FEC+2*4,0xA619C2),
        ('ReleaseWave tick',0xD057D4+0x188,0x5CE7A0),
        ('ReleaseWave remove',0xD057D4+0x164,0x49E840),
        ('ReleaseWave set basic ANI',0xD057D4+0x6C,0x407BC0),
        ('ReleaseWave set current ANI',0xD057D4+0xF0,0x49D070),
    ]:check(label,u32(va)==expected)
    for label,va,expected in [
        ('skill32 compare',0x73C147,'83f820'),
        ('phase0 guard',0x73C15B,'85c00f85'),
        ('spawn literal20018',0x73C2B9,'68324e0000'),
        ('spawn virtual2B8',0x73C2C0,'ff97b8020000'),
        ('spawn ret13args',0x4EA60F,'c23400'),
        ('writer opcode21',0x4E9F24,'6a026a15'),
        ('OBJ basic template34',0x884A85,'8d4634'),
        ('OBJ ATK template70',0x884CAE,'8d4e70'),
        ('write basic ANI+118',0x407BCE,'898118010000'),
        ('write current ANI+104',0x49B288,'89be04010000'),
        ('tick read ANI ended13A',0x5CE7AE,'8a883a010000'),
    ]:check(label,chunk(va,len(bytes.fromhex(expected)))[0].hex()==expected)
    for label,site,target in [
        ('receive factory',0x8C4395,0x5E8500),
        ('selected constructor',0x5EA884,0x5CE740),
        ('base constructor',0x5CE768,0x490720),
        ('numeric registration consumer',0x490812,0x4A0DA0),
        ('OBJ path consumer',0x4A0DEA,0x49F4D0),
        ('USA list initialize',0x44ADE5,0x882A50),
        ('list numeric parser',0x882ABB,0x831AD0),
        ('type2 parser',0xA619F8,0x884720),
        ('runtime ANI',0x49F6B0,0x472A60),
        ('runtime ATK lookup',0x49FAEE,0xB7D230),
        ('runtime ATK copy',0x49FB01,0x4A27E0),
        ('scalar setup',0x5CE77D,0x5C77B0),
        ('ANI constructor load',0x472B66,0xA29AD0),
        ('remove base request',0x49E862,0x499120),
    ]:
        b=chunk(site,5)[0]
        check(label,b[0]==0xE8 and (site+5+struct.unpack_from('<i',b,1)[0])&0xffffffff==target)
    for va,text in [(0xCCAF9C,'PassiveObject/'),(0xCCAFBC,'PassiveObject.usa.lst'),
                    (0xD7C750,'Effect/Animation/ReleaseWave1.ani'),(0xD7C708,'Effect/Animation/ReleaseWave2.ani'),
                    (0xE23520,'[basic motion]'),(0xE1F15C,'[attack info]'),(0xCF08A0,'WAVE_CANCLE')]:
        b=text.encode('utf-16le')+b'\0\0'
        check('native literal '+text,chunk(va,len(b))[0]==b)
    resources=json.loads((ROOT/'resources.json').read_text(encoding='utf-8'))
    for resource in resources['resources']:
        check('PVF export '+resource['path'],hashlib.sha256((ROOT/resource['raw_export']).read_bytes()).hexdigest()==resource['sha256'])
    for path,rows in contract['registrations'].items():
        row=rows[0]
        expected='Swordman/ReleaseWave.skl' if path.startswith('skill/') else 'Character/Swordman/ReleaseWave.obj'
        check('numeric row '+path,len(rows)==1 and row['path']==expected)
    tracks=contract['tracks']
    check('separate visual/attack timelines',[x['frame_delay_sum'] for x in tracks]==[490,420,400])
    check('object images stay empty',all(f['images'][0][0]=='' for f in tracks[2]['frames']))
    check('object box in every resource frame',all(f['attack_boxes']==[[-84,-50,0,168,100,234]] for f in tracks[2]['frames']))
    check('no invented ACT',contract['action_binding']['declared_act_paths']==[])
    for evidence in index['rea_evidence']:
        p=WORKSPACE/evidence['path']
        check('REA retained '+evidence['evidence_id'],hashlib.sha256(p.read_bytes()).hexdigest()==evidence['sha256'])
    # These boundary probes exercise the contract using independently confirmed
    # PVF durations and native ended/remove behavior, without claiming runtime timing.
    check('first native resource frames',all(t['frame']==0 for t in sample(0)['tracks']))
    check('attack frame1 at80',next(t for t in sample(80)['tracks'] if t['role'].startswith('spawned'))['frame']==1)
    check('attack active before400',len(sample(399)['attack_boxes_world'])==1)
    check('attack removed at normalized400',sample(400)['attack_boxes_world']==[])
    failed=sample(0,spawn_gate=False)
    check('visuals exist when spawn gate fails',len(failed['tracks'])==2 and failed['attack_boxes_world']==[])
    check('translated native geometry',sample(0,[100,200,10])['attack_boxes_world']==[[16.0,150.0,10.0,168.0,100.0,234.0]])
    result=dict(passed=True,checks=len(checks),results=checks,observed_execution=False,
                limitation='Static identities, anchors, exact registrations and limited timeline only; no observed target execution, accepted-hit formula or visual equivalence.')
    (ROOT/'verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps(dict(passed=True,checks=len(checks))))

if __name__=='__main__':main()
