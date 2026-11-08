"""Read-only replay of source identity, authoritative captures and semantic anchors."""
from pathlib import Path
import hashlib
import json
import struct
from audit60 import RAW, OUT, PE, off

EXPECTED = 'a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'
checks = []
def check(name, condition):
    checks.append({'name':name,'ok':bool(condition)})
def u32(va):return struct.unpack_from('<I',RAW,off(va))[0]
def rel32(site):
    p=off(site)
    return ((site+5+struct.unpack_from('<i',RAW,p+1)[0]) & 0xffffffff) if RAW[p] in (0xe8,0xe9) else None
check('source sha256', hashlib.sha256(RAW).hexdigest() == EXPECTED)
manifest=json.loads((OUT/'capture-manifest.json').read_text(encoding='utf8'))
for c in manifest['authoritative_excerpts']:
    start=int(c['va_start'],16);p=off(start);b=RAW[p:p+c['length']]
    check(c['bin'],c['file_offset']==p and hashlib.sha256(b).hexdigest()==c['sha256'] and (OUT/c['bin']).read_bytes()==b)
slots={0x22c:0x4fe290,0x234:0x744b90,0x238:0x744ba0,0x23c:0x4edf70,0x240:0x4aef80,0x260:0x4f8a30,0x2f8:0x4f5c20,0x36c:0x7447b0,0x370:0x4ac830,0x374:0x4ac7c0,0x378:0x4ac7f0,0x37c:0x4ac810,0x390:0x7447d0,0x398:0x7447f0,0x39c:0x744800,0x3a0:0x744820,0x3a4:0x744830,0x3d8:0x4ad960,0x3dc:0x744b70,0x3e0:0x4af540,0x3e4:0x4ac440,0x3e8:0x4af140,0x3ec:0x4f58c0}
for slot,target in slots.items():check(f'monster vtable+{slot:X}',u32(0xd8385c+slot)==target)
for slot,target in {0x38:0x8e49b0,0x60:0x4efc80,0x164:0x499120,0x188:0x4fb720,0x3c4:0x744870,0x5a0:0x4f2a40,0x5d0:0x750cd0,0x654:0x4fa1d0}.items():check(f'death monster vtable+{slot:X}',u32(0xd8385c+slot)==target)
for site,target in {0x4f9ac2:0x4b28d0,0x4f59dd:0x4b4e00,0x4feba0:0x4bad60,0x500d5b:0x472a60,0x501c99:0x4a3900,0xa3f151:0x830590,0xa3f267:0x8304e0,0xa3f286:0x778880,0xa32229:0x4936d0,0xa32238:0x4936d0,0x4937d7:0xa29ad0}.items():check(f'rel32 {site:X}->{target:X}',rel32(site)==target)
check('message 0x13 (=19) case',u32(0x8c5e64+0x13*4)==0x8c39b0)
check('message 0x17 (=23) case',u32(0x8c5e64+0x17*4)==0x8c4d73)
check('monster death tick case remap',RAW[off(0x4fce84)+5]==1 and u32(0x4fce68+4)==0x4fcb2a)
check('Monster slot38 false stub',RAW[off(0x8e49b0):off(0x8e49b0)+3]==bytes.fromhex('32c0c3'))
check('Monster slot5D0 ret stub',RAW[off(0x750cd0)]==0xc3)
check('slot654 protected entry jump',rel32(0x4fa1f0)==0x13baa5f)
check('slot654 shared protection thunk',RAW[off(0x13baa5f):off(0x13baa5f)+5]==bytes.fromhex('687e0e1008') and rel32(0x13baa64)==0x12ee7c9)
check('removal message begin opcode',RAW[off(0x499155):off(0x499155)+4]==bytes.fromhex('6a026a17'))
check('removal request pending flag',RAW[off(0x49919e):off(0x49919e)+7]==bytes.fromhex('c686e801000001'))
check('removal receiver resolve',rel32(0x8c4db7)==0x50b820)
check('death ANI frame scale call',rel32(0x4fcbe0)==0xa297b0)
check('death scale threshold f32',RAW[off(0xcd0928):off(0xcd0928)+4]==struct.pack('<f',1.2))
aura_type=b'.?AVCNRDAuraMaster@@\0'
check('AuraMaster RTTI',RAW[off(0xf61e98)+8:off(0xf61e98)+8+len(aura_type)]==aura_type)
check('apply-state switch',list(struct.unpack_from('<10I',RAW,off(0x4bc798)))==[0x4badeb,0x4baf16,0x4bafee,0x4bb091,0x4bb249,0x4bb976,0x4bbacc,0x4bc23a,0x4bc2b1,0x4bc3fd])
check('tick-state switch',list(struct.unpack_from('<9I',RAW,off(0x4bdad0)))==[0x4bccc7,0x4bd035,0x4bda00,0x4bd06a,0x4bd0b7,0x4bd649,0x4bd696,0x4bd98b,0x4bd9d8])
check('geometry epsilon 2^-23',RAW[off(0xcab8e8):off(0xcab8e8)+8]==bytes.fromhex('000000000000803e'))
reaction=json.loads((OUT/'monster-reaction-contract.json').read_text(encoding='utf8'))
for c in reaction['observed_static']['motions']+reaction['observed_static']['actions']:
    p=off(int(c['literal_va'],16));s=(c['tag']+'\0').encode('utf-16le');check('literal '+c['tag'],RAW[p:p+len(s)]==s)
check('BASE ANI literal',RAW[off(0xe49288):off(0xe49288)+22]=='[BASE ANI]\0'.encode('utf-16le'))
scene=json.loads((OUT/'scene-destruction-contract.json').read_text(encoding='utf8'))
for slot,target in {0x60:0x5e14e0,0x64:0x407bb0,0x15c:0x4a0840,0x164:0x49e840,0x188:0x49dc70,0x22c:0x49d7d0,0x234:0x4391e0,0x238:0x439200,0x260:0x49f310,0x28c:0x4ed1d0,0x290:0x4edac0,0x2f8:0x4eb780,0x33c:0x439070,0x348:0x49d0e0,0x35c:0x4391d0,0x360:0x4391f0}.items():check(f'passive vtable+{slot:X}',u32(0xcbb7d4+slot)==target)
for slot,target in {0x20:0x49d220,0x60:0x5e14e0,0x70:0x407bf0,0x100:0x4e9480}.items():check(f'lastaction transient vtable+{slot:X}',u32(0xccec5c+slot)==target)
for site,target in {0x49e862:0x499120,0x49f3f5:0x49f090,0x49d884:0x50b820,0x49daa1:0x4e9ea0,0x4a0b0e:0x4e9ea0,0x4a08dc:0x4a3900,0x4a08f1:0x4a3900,0x4a0935:0x4a3820,0x4a095e:0x50dd70,0x4a385f:0x49f240,0x4e948b:0x499f10,0x4a0a6a:0x50e060,0x49fde8:0x4a3440}.items():check(f'scene rel32 {site:X}->{target:X}',rel32(site)==target)
for name,site,data in [
    ('HP subtraction',0x49f3ab,'2bfb'),
    ('state1 HP write',0x49d832,'8938'),
    ('HP destroy flag write',0x49fd8a,'c6403401'),
    ('HP destroy callback removal',0x49d114,'ff9264010000'),
    ('world active flag virtual read',0x50caf2,'ff5264'),
    ('world self notification arguments',0x50c760,'8b03538bcbff905c010000'),
    ('timer strict greater branch',0x49d9df,'2bcf3bca7e0a'),
    ('transient marks end flag',0x49f2e6,'889685010000'),
]:
    p=off(site);b=bytes.fromhex(data);check('scene '+name,RAW[p:p+len(b)]==b)
imports=[(e.dll,i.name) for e in PE.DIRECTORY_ENTRY_IMPORT for i in e.imports if i.address==0x140f05c]
check('scene clock kernel32 GetTickCount',imports==[(b'kernel32.dll',b'GetTickCount')])
literals=[('[hp max]',0xe23374),('[hp destroy]',0xe23358),('[object destroy condition]',0xe23320),('[destroy condition]',0xe232f8),('[destroy action]',0xe2321c),('[destroy particle]',0xe23410)]
literals.extend((r['tag'],int(r['literal'],16)) for r in scene['observed_static']['destroy_conditions']['parser_cases'])
literals.extend((r['tag'],int(r['literal'],16)) for r in scene['observed_static']['destroy_conditions']['action_parser'])
for tag,address in literals:
    p=off(address);b=(tag+'\0').encode('utf-16le');check('scene literal '+tag,RAW[p:p+len(b)]==b)
for descriptor,name in [(0xf428a0,'.?AVCNRDPassiveObject@@'),(0xf586dc,'.?AVCNRDPooledObjectAddAction@@'),(0xf54a18,'.?AVCNRDObjectParticleCreater@@')]:
    p=off(descriptor)+8;b=(name+'\0').encode('ascii');check('scene RTTI '+name,RAW[p:p+len(b)]==b)
import sys
sys.path.insert(0,str(OUT.parent))
from pvf60 import Pvf60
pvf=Pvf60(OUT.parents[1]/'DFO'/'Script.pvf')
resources=json.loads((OUT/'scene-resources.json').read_text(encoding='utf8'))
check('scene PVF archive identity',hashlib.sha256(pvf.data).hexdigest()==resources['archive_sha256']=='23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98')
for record in resources['resources']:
    current=pvf.read(record['path'])
    check('scene resource '+record['path'],hashlib.sha256(current).hexdigest()==record['sha256'] and (OUT/record['raw_export']).read_bytes()==current)
telephone=next(r for r in resources['resources'] if r['path'].endswith('/telephone.obj'))
check('telephone commented last action excluded',not any(n['tag']=='last action' for n in telephone['fields']) and b'//[last action]' in (OUT/telephone['raw_export']).read_bytes())
for crosscheck in scene['rea_crosschecks']:
    evidence=json.loads((OUT/crosscheck['result']).read_text(encoding='utf8'))['structuredContent']
    body=evidence['raw_result']['value']['procedure']['body']['ranges']
    check('scene REA identity '+crosscheck['function'],evidence['evidence_id']==crosscheck['evidence_id'] and evidence['subject']['digest']['sha256']==EXPECTED and len(body)==1 and [body[0]['start'].lower(),body[0]['end'].lower()]==[x.lower() for x in crosscheck['body_inclusive']])
specialized=json.loads((OUT/'scene-specialized-contract.json').read_text(encoding='utf8'))
for row in specialized['factory']['selected']:
    descriptor=int(row['descriptor'],16);table=int(row['vtable'],16)
    b=(row['rtti']+'\0').encode('ascii');p=off(descriptor)+8
    check('scene specialized RTTI '+row['rtti'],RAW[p:p+len(b)]==b and u32(u32(table-4)+12)==descriptor)
for table in [0xccc88c,0xd4d26c]:
    for slot,target in {0x260:0x5f5fb0,0x348:0x5f5b40,0x188:0x5f6b60,0x22c:0x5f7700,0x15c:0x5f5ca0,0x164:0x5f4fa0,0x388:0x5f5ae0,0x38c:0x5f5e80}.items():
        check(f'scene specialized vtable{table:X}+{slot:X}',u32(table+slot)==target)
for slot,target in {0x260:0x5f33c0,0x188:0x5f3500,0x15c:0x5f3b00,0x374:0x5c86f0,0x378:0x5f32e0}.items():
    check(f'scene grass vtable+{slot:X}',u32(0xcf10f4+slot)==target)
for object_id,target in [(221,0x5e904d),(224,0x5e85f6)]:
    case=RAW[off(0x5f1620)+object_id-1]
    check(f'scene factory ID{object_id}',u32(0x5f1604+4*case)==target)
for site,target in {0x5e8618:0x5e70c0,0x5e86ab:0x5c8660,0x5e9073:0x490830,0x4908fa:0x5f6640,0x5c86ca:0x5f3770,0x4a0dea:0x49f4d0,0x49fc45:0x507940,0x49fc57:0x4392e0,0x5f60ed:0x49f310,0x5f5b5c:0x49d0e0,0x5f33ed:0x49f310,0x5f3520:0x49dc70,0x5f5cab:0x4a0840,0x5f3b24:0x4a0840}.items():
    check(f'scene specialized rel32{site:X}->{target:X}',rel32(site)==target)
for tag,address in [('[int data]',0xe1d8e8),('[string data]',0xe1d8cc),('[pass all]',0xe2364c),('[do not pass]',0xe23600)]:
    b=(tag+'\0').encode('utf-16le');p=off(address)
    check('scene specialized literal '+tag,RAW[p:p+len(b)]==b)
for name,site,data in [
    ('HP from int6 slot35C',0x5f67be,'ff925c030000'),
    ('maxHP from int6 slot360',0x5f67d4,'ff9260030000'),
    ('counter native increment',0x5f5b7d,'4089867c080000'),
    ('counter HP reset',0x5f5b9c,'ff975c030000'),
    ('counter etc0 ANI selection',0x5f5b25,'ff92f0000000'),
    ('reaction etc1 flag',0x5f5bc8,'c7863c09000001000000'),
    ('reaction end exact flag',0x5f6c5d,'80b83a01000001'),
    ('grass independent count method',0x5c86f0,'ff8174080000c3'),
    ('grass direct accepted contact',0x5f36cd,'ff9060020000'),
    ('default HP and maxHP zero',0x437b11,'891e895e04'),
    ('state1 absolute HP payload1',0x49d7fe,'8b7804'),
    ('state1 after HP write callback',0x49d89b,'ff9248030000'),
]:
    b=bytes.fromhex(data);p=off(site);check('scene specialized '+name,RAW[p:p+len(b)]==b)
for crosscheck in specialized['rea_crosschecks']:
    evidence=json.loads((OUT/crosscheck['result']).read_text(encoding='utf8'))['structuredContent']
    ranges=evidence['raw_result']['value']['procedure']['body']['ranges']
    actual=[[r['start'].lower(),r['end'].lower()] for r in ranges]
    check('scene specialized REA '+crosscheck['function'],evidence['evidence_id']==crosscheck['evidence_id'] and evidence['subject']['digest']['sha256']==EXPECTED and actual==crosscheck['ranges_inclusive'])
from scene_state_model import selected_config, SceneState, demonstration
from dataclasses import replace
for object_id,ints in [(221,[1,1,1,0,0,30,1]),(224,[1,2,0,0,0,100,1]),(244,[32,1])]:
    config=selected_config(object_id,resources)
    check(f'scene model current PVF config{object_id}',config.ints==ints and not config.hp_destroy)
model_cases=demonstration()
check('scene model explicit native input traces',len(model_cases['traces'])==4)
# The selected MapObject resources do not have etcANI1. This explicit synthetic
# fixture exercises the independently recovered flag/ANI-end branch; it is not
# claimed to be an additional current PVF scene object.
fixture=replace(selected_config(224,resources),etc=['counter.ani','damage.ani'])
model=SceneState(fixture)
model.on_native_hp_write(1)
check('scene model marked etcANI1 selected',model.restore_basic_on_end and model.current_ani.endswith('/damage.ani'))
events=model.on_native_frame_ended()
check('scene model explicit end restores basic only when marked',len(events)==1 and events[0]['reset'] and model.current_ani.endswith('actiontree2-0.ani') and not model.restore_basic_on_end)
rejected=0
for instance,method in [(SceneState(selected_config(221,resources)),'on_native_accepted_contact'),(SceneState(selected_config(244,resources)),'on_native_hp_write')]:
    try:
        getattr(instance,method)(0) if method=='on_native_hp_write' else getattr(instance,method)()
    except ValueError:
        rejected+=1
check('scene model does not confuse contact and HP inputs',rejected==2)
from scene_preview_loader import ScenePreviewCatalog
catalog=ScenePreviewCatalog()
loaded_tree=catalog.object(224)
loaded_grass=catalog.object(244)
check('scene loader current tree binding',loaded_tree['parameters']['count_limit']==2 and loaded_tree['etc_ani'][0]['declared_loop']==[1] and len(loaded_tree['etc_ani'])==1)
check('scene loader current grass binding',loaded_grass['parameters']['native_max_hp_initial']==0 and loaded_grass['parameters']['contact_count_threshold']==2 and loaded_grass['etc_ani'][0]['declared_loop']==[0] and len(loaded_grass['etc_ani'])==3)
sampler=catalog.sampler(221)
sample=sampler.sample({'kind':'native_absolute_hp_write','new_absolute_hp':0})
check('scene loader sample applies explicit HP event',sample['state']['hp']==1 and sample['state']['count']==1 and sample['state']['active'] and any(e['kind']=='removal_request' for e in sample['output_events']))
reject_overlap=False
try:
    sampler.sample({'kind':'overlap'})
except ValueError:
    reject_overlap=True
check('scene loader refuses geometric overlap event',reject_overlap)
result={'source_sha256':EXPECTED,'checks':checks,'total':len(checks),'passed':sum(x['ok'] for x in checks),'failed':[x['name'] for x in checks if not x['ok']],'scope':'Static byte/anchor verification, not native runtime execution or formula/visual validation.'}
(OUT/'verification-result.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
print(json.dumps({k:v for k,v in result.items() if k!='checks'},ensure_ascii=False,indent=2))
raise SystemExit(0 if not result['failed'] else 1)
