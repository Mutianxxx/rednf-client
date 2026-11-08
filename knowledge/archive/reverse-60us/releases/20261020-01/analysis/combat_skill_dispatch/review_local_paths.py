from pathlib import Path
import sys,json,hashlib,struct,csv
sys.path.insert(0,r'D:\dnf\60US\analysis\deps')
import pefile
ROOT=Path(__file__).parent
d=json.loads((ROOT/'local-dispatch-paths.json').read_text(encoding='utf8'));raw=Path(d['source']).read_bytes();pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase
assert hashlib.sha256(raw).hexdigest()==d['source_sha256']
for x in d['paths']:
    b=bytes.fromhex(x['path_bytes_hex']);o=x['path_bytes_file_offset'];assert raw[o:o+len(b)]==b;assert hashlib.sha256(b).hexdigest()==x['path_bytes_sha256']
    for va,slot in ((x['consume_call_va'],0x768),(x['request_call_va'],0x28c)):
        off=pe.get_offset_from_rva(int(va,0)-base);op=raw[off:off+6];assert op[0]==0xff and 0x90<=op[1]<=0x97 and struct.unpack_from('<I',op,2)[0]==slot
    assert x['consume_stack_args_in_callee_order'][0]['literal']==x['skill_id']
    assert len(x['consume_stack_args_in_callee_order'])==4
catalog=json.loads((ROOT.parent/'combat_catalog'/'skills.json').read_text(encoding='utf8'))
selections=[('Swordman',5,20,'0x72acf3','0072AC9D-0072AD76','state 0/11/8; command559140(id5) != -1; vector[(skill6 level>0),0]'),
('Fighter',1,47,'0x6a371f','006A36F8-006A373E','command559140(id1,0) != -1; qualification AL !=0; EDI zero within excerpt; state request has null vector'),
('Fighter',5,30,'0x6a3cba','006A3C95-006A3CD5','command559140(id5,EDI) != -1; qualification AL !=0; upstream helper6B5CD0 and exact zero-register dominance separately retained'),
('Gunner_variants_2_5',3,19,'0x6d5683','006D55E5-006D56E5','state0/11/12/4/8; command559140(id3) !=-1 OR (state12/4 AND command-object vslot48 succeeds); vector[3]'),
('Gunner_variants_2_5',4,20,'0x6d5731','006D56E5-006D5793','state0/11/8; command559140(id4) !=-1; vector[4]'),
('Mage',4,22,'0x6f0c65','006F0BD7-006F0CC3','state0/11/8; EBX0 and EDI-1 at excerpt start; command559140(id4) !=-1; vector[4]'),
('Mage',12,23,'0x6f2a1b','006F29F2-006F2A97','command559140(id12) !=-1; vector[12]; upstream state gate admits0/11/8/22 (separate exploratory span6F29C0 from29C1 aligned)'),
('Priest',1,20,'0x7103c1','0071036D-007103E2','state0/11/8; command559140(id1,this+25E4) !=-1; EBX0 before request; null vector'),
('Priest',11,26,'0x71042a','007103E2-00710445','state0/11/8; command559140(id11,EBX) !=-1; previous block setsEBX0 on both paths; null vector')]
ids={'Swordman':[0],'Fighter':[1],'Gunner_variants_2_5':[2,5],'Mage':[3],'Priest':[4]};reviewed=[]
for name,skill,state,call,excerpt,note in selections:
    path=next(x for x in d['paths'] if x['native_class']==name and x['skill_id']==skill and x['state']==state and x['consume_call_va']==call)
    proof=json.loads((ROOT/(excerpt+'.json')).read_text(encoding='utf8'));chunk=(ROOT/(excerpt+'.bin')).read_bytes();assert chunk==raw[proof['file_offset']:proof['file_offset']+proof['length']]
    candidates=[{k:s[k] for k in ('class_id','class_label','skill_id','path','registration_source','source')} for s in catalog if s['class_id'] in ids[name] and s['skill_id']==skill]
    reviewed.append({**path,'manual_review':'instruction sequence, literal IDs, command gate and consume failure bypass checked; partial local controller contract','local_guard_notes':note,'excerpt':{'id':excerpt,**proof},'pvf_registration_candidates':candidates,'class_id_applicability':ids[name] if name!='Gunner_variants_2_5' else None,'variant_boundary':'Shared CNGunner native path; class2/class5 applicability and upstream variant guards remain unresolved, so registration candidates are not asserted behavior bindings' if name=='Gunner_variants_2_5' else None})
result={'source':d['source'],'source_sha256':d['source_sha256'],'scope':'9 manually inspected local release/request examples; all are partial controller contracts','paths':reviewed,'all_local_paths_verified_against_source':len(d['paths']),'runtime_execution_observed':False}
(ROOT/'reviewed-local-paths.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf8')
with (ROOT/'local-dispatch-paths.csv').open('w',encoding='utf-8-sig',newline='') as f:
    writer=csv.DictWriter(f,fieldnames=['native_class','skill_id','state','consume_call_va','request_call_va','pvf_registration_candidates','variant_boundary','status']);writer.writeheader()
    for x in d['paths']:
        names=[str(s['class_id'])+':'+s['path'] for s in catalog if s['class_id'] in ids[x['native_class']] and s['skill_id']==x['skill_id']]
        writer.writerow({**{k:x[k] for k in ('native_class','skill_id','state','consume_call_va','request_call_va','status')},'pvf_registration_candidates':' | '.join(names),'variant_boundary':'job2/job5 applicability unresolved' if x['native_class']=='Gunner_variants_2_5' else 'upstream guards still required'})
counts={n:sum(x['native_class']==n for x in d['paths']) for n in ids}
unique={n:len({(x['skill_id'],x['state']) for x in d['paths'] if x['native_class']==n}) for n in ids}
print(json.dumps({'local_path_count':len(d['paths']),'counts':counts,'unique_id_state_pairs':unique,'manual_examples':len(reviewed),'all_paths_match_source':True,'all_actual_arg_flags':sorted({tuple(p['literal'] for p in x['consume_stack_args_in_callee_order'][1:]) for x in d['paths']},key=str)},indent=2))
