from pathlib import Path
import sys,json,struct,hashlib
sys.path.insert(0,r'D:\dnf\60US\analysis\deps')
import pefile
ROOT=Path(__file__).parent
SOURCE=Path(r'D:\dnf\60US\DFO\DFO_fixed_v3.exe');raw=SOURCE.read_bytes();pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase
def bs(va,n):
    o=pe.get_offset_from_rva(va-base);return raw[o:o+n]
def ptr(va):return struct.unpack('<I',bs(va,4))[0]
def digest(b):return hashlib.sha256(b).hexdigest()
def region(va,n):return {'va':f'0x{va:08X}','rva':f'0x{va-base:08X}','file_offset':pe.get_offset_from_rva(va-base),'length':n,'sha256':digest(bs(va,n)),'hex':bs(va,n).hex()}
source={'path':str(SOURCE),'sha256':digest(raw),'image_base':f'0x{base:08X}','evidence_type':'static x86 instruction/data bytes; no target execution'}
controllers=json.loads((ROOT/'controllers.json').read_text(encoding='utf8'))
by_name={x['rtti_name']:x for x in controllers['classes']}
labels=['Swordman','Fighter','Gunner','Mage','Priest','ATGunner']
ctors=[0x7469b0,0x746f50,0x747510,0x747b70,0x7488e0,0x747510]
writes=[0x7469e8,0x746f89,0x747550,0x747ba9,0x748917,0x747550]
rows=[]
for i,label in enumerate(labels):
    c=by_name['.?AVCN'+('Gunner' if i==5 else label)+'@@'];v=c['complete_object_locators'][0]['vtables'][0]
    rows.append({'class_id':i,'label':label,'factory_va':'0x00748C40','factory_case_va':f'0x{ptr(0x748db4+i*4):08X}','constructor_va':f'0x{ctors[i]:08X}','constructor_argument':1 if i==5 else 0,'constructor_vtable_write':region(writes[i],6),'rtti_name':c['rtti_name'],'type_descriptor_va':c['type_descriptor_va'],'col_va':c['complete_object_locators'][0]['col_va'],'vtable_va':v['vtable_va'],'slots':v['slots'],'variant_boundary':'Gunner/ATGunner share one native class and vtable; job index is 2/5 in common constructor; per-skill variant branches remain to trace' if i in (2,5) else None})
skills=json.loads((ROOT.parent/'combat_catalog'/'skills.json').read_text(encoding='utf8'))
skill_evidence=[{k:x[k] for k in ('class_id','class_label','skill_id','path','registration','registration_source','source')} for x in skills if x['class_id']==0 and x['skill_id'] in (5,6)]
chain={
 'source':source,'scope':'Swordman registered skill 5 to native pending-state request 20; six-class controller/factory map; shared state serialization and opcode-5 application',
 'pvf_skills':skill_evidence,'classes':rows,
 'hardattack':{
   'class_id':0,'skill_id':5,'skill_path':'skill/swordman/hardattack.skl','processing_vslot':'0x188','processing_va':'0x00726150',
   'state_gate':{'field':'this+0x155C (protected integer)','establish_field_va':'0x0072AB4D','accepted_states':[0,11,8],'block_va':'0x0072AC9D'},
   'command_gate':{'getter_vslot':'0x73C','getter_va':'0x004CC270','getter_semantics':'returns this+0x26A0 object; no argument cleanup; the pushed pair belongs to following 0x559140','call_va':'0x0072ACD9','function_va':'0x00559140','args':['skill_id=5','this+0x25E4'],'success_comparison':'return != -1'},
   'qualify_and_consume':{'call_va':'0x0072ACF3','vslot':'0x768','function_va':'0x004C1D30','delegates_va':'0x004D9040','args':[5,1,1,1],'success':'AL != 0','mp_compare_call_va':'0x004D91EF','mp_cost_call_va':'0x004D9554','mp_read_va':'0x004D9565','mp_subtract_va':'0x004D956A','mp_commit_va':'0x004D956F','mp_commit_vslot':'0x3F4'},
   'state_request':{'call_va':'0x0072AD5E','vslot':'0x28C','function_va':'0x004ED1D0','args':[20,'&vector',1,0,0],'vector':['skill6_level > 0 ? 1 : 0',0],'skill6_path':'skill/swordman/hardattackcharge.skl','pending_state_write_va':'0x004ED29A','pending_state_field':'this+0x4A0','pending_vector_field':'this+0x4A4','pending_priority_field':'this+0x4B4','description':'qualified request is queued subject to gating/priority; this routine does not directly invoke the state handler'},
 },
 'state_synchronization':{
  'serialization_function':'0x004EDAC0','serialization_vslot':'0x290','guard':['this+0x49D == 0','this+0x4A0 != -1'],
  'writer_begin_call':'0x004EDB07','writer_begin_args':[5,2],
  'body_fields_in_order':['object vslot+0x3C as word','object vslot+0x40 as word','pending state this+0x4A0 low byte','encoded vector length as word','encoded vector bytes'],
  'encode_vector_va':'0x004EDA70','encode_integer_va':'0x004ED2E0','encode_rule':'big-endian groups of 7 bits; high bit means another group follows; decoder shl accumulator by 7 then add byte&0x7F; 32-bit integer boundary',
  'send_candidate_call_va':'0x004EDBC8','manager_global':'0x010C0790','manager_vslot':'0x44','manager_args':[1,-1,'this',3],'mark_serialized_va':'0x004EDBCD','mark_field':'this+0x49D=1',
  'receive_dispatcher_va':'0x008C1A30','opcode_source':'word [packet+1]','opcode_switch_table_va':'0x008C5E64','opcode':5,'receive_case_va':'0x008C2162',
  'receive_state_read_call_va':'0x008C219B','receive_state_storage':'byte [ebp+0xB]','decode_integer_vector_call_va':'0x008C222C','decode_integer_vector_va':'0x004ED490',
  'object_lookup_va':'0x0050B820','object_lookup_call_va':'0x008C2263','target_rtti':'IRDCollisionObject','target_type_descriptor_va':'0x00F4287C',
  'state_handler_call_va':'0x008C2395','state_handler_vslot':'0x22C','state_handler_args':['decoded state byte','&decoded integer vector',1,1],
  'pending_compare_call_va':'0x008C23E4','pending_get_vslot':'0x294','pending_get_va':'0x00438700','clear_pending_call_va':'0x008C23F6','clear_pending_vslot':'0x298','clear_pending_va':'0x00438710',
  'boundary':'sender/receiver structure and opcode match statically; manager transport, server policy and actual gameplay execution are not observed',
 },
 'unknowns':['Exact semantic names of all eligibility flags and command recognition internals','MP rounding and final resource deltas in a live matching-hash process','Variant-specific Gunner/ATGunner skill branches','All other registered skill-ID to state/action bindings','Full state-20 substate controller and attack acceptance are separate analyses','Local prediction, server authority and actual packet traffic are not proven by static matching']
}
(ROOT/'dispatch-chain.json').write_text(json.dumps(chain,ensure_ascii=False,indent=2),encoding='utf8')
curated={
'00726150-00726750':'Swordman processing entry: EBX zero, state field and initial switch',
'0072AB31-0072AC9D':'Establish EDI=&this+155C, existing state gates, previous skill block',
'0072AC9D-0072AD76':'Clean complete skill-5 command/qualification/state-20 request block',
'004CC270-004CC330':'No-argument command-object getter (function ends A0)',
'00559140-005595A0':'Command lookup: compares protected skill ID; returns -1 on failure; larger excerpt continues beyond function',
'004C1D30-004C1EC0':'Qualification wrapper and unchanged four-argument delegation',
'004D9040-004D9200':'Common qualification and MP comparison',
'004D9536-004D957E':'MP cost lookup, read, subtraction and commit',
'004ED1D0-004ED2D7':'Pending-state request complete function',
'004EDAC0-004EDC00':'Pending-state packet serialization complete function',
'004EDA70-004EDAB6':'Each vector integer encoded via 4ED2E0',
'004ED2E0-004ED3F0':'Integer encoding excerpt; larger values continue after excerpt',
'004ED490-004ED660':'Integer-vector decoding; decoder ends52D',
'008C1A30-008C1CE0':'Packet verification and word-opcode switch dispatcher',
'008C2162-008C23FC':'Opcode-5 read/decode/object application and pending acknowledgment',
'008C5E64-008C5F44':'DATA: 56-address opcode jump table, not instructions',
'00748C40-00748DB4':'Complete six-case class factory',
'00748DB4-00748DCC':'DATA: 6-address class factory jump table, not instructions',
'007469B0-00746A30':'Swordman constructor entry/class argument/vtable write',
'00746F50-00746FC0':'Fighter constructor entry/class argument/vtable write',
'00747510-00747910':'Gunner constructor entry: boolean variant chooses2/5, same vtable',
'00747B70-00747BE0':'Mage constructor entry/class argument/vtable write',
'007488E0-00748950':'Priest constructor entry/class argument/vtable write',
'00746670-00746AC0':'Common constructor takes job+variant, forwards to7456C0',
'007456C0-00746670':'Common constructor forwards job+variant to4E1E80 at745B0A; excerpt contains subsequent functions',
'004E1E80-004E1FA0':'Job-index resource registration lookup and load call4DA140',
'00693960-00693A80':'Fighter skill qualification override delegates to4C1D30, then skill33 branch',
'006A36F8-006A373E':'Fighter skill1 command and AL-success request state47',
'006A3C95-006A3CD5':'Fighter skill5 command and AL-success request state30',
'006D55E5-006D56E5':'Shared CNGunner skill3 state gate/command alternative/AL-success request state19 vector3',
'006D56E5-006D5793':'Shared CNGunner skill4 state gate/command/AL-success request state20 vector4',
'006F0BD7-006F0CC3':'Mage constants/state gate/skill4 command/AL-success request state22 vector4',
'006F29F2-006F2A97':'Mage skill12 command/AL-success request state23 vector12',
'0071036D-007103E2':'Priest state gate/skill1 command/AL-success request state20',
'007103E2-00710445':'Priest state gate/skill11 command/AL-success request state26',
}
evidence=[]
for name,purpose in curated.items():
    record=json.loads((ROOT/(name+'.json')).read_text(encoding='utf8'))
    chunk=(ROOT/(name+'.bin')).read_bytes(); assert digest(chunk)==record['chunk_sha256']
    assert chunk==bs(record['start_va'],record['length'])
    evidence.append({'id':name,'purpose':purpose,**record,'asm_file':name+'.asm','bin_file':name+'.bin'})
anchors={0x72accd:'6a05',0x72acd9:'e862e4e2ff',0x72acef:'6a05',0x72acf3:'ff9068070000',0x72ad5a:'6a14',0x72ad5e:'ff928c020000',0x4ed29a:'8986a0040000',0x8c2395:'ff902c020000',0x8c23e4:'ff9294020000',0x8c23f6:'ff9298020000'}
for va,h in anchors.items():assert bs(va,len(bytes.fromhex(h))).hex()==h,(hex(va),h)
assert ptr(0x8c5e64+5*4)==0x8c2162
assert ptr(0x748db4+5*4)==0x748d71
for row in rows:
    write=bytes.fromhex(row['constructor_vtable_write']['hex']);assert write[:2]==bytes.fromhex('c706');assert int.from_bytes(write[2:],'little')==int(row['vtable_va'],16)
    assert ptr(int(row['vtable_va'],16)+0x28c)==0x4ed1d0
(ROOT/'evidence-index.json').write_text(json.dumps({'source':source,'evidence':evidence},ensure_ascii=False,indent=2),encoding='utf8')
validation={'source_sha256':source['sha256'],'all_curated_excerpts_match_source':True,'curated_excerpt_count':len(evidence),'anchor_count':len(anchors),'factory_six_cases_verified':True,'opcode5_branch_verified':True,'constructor_vtable_writes_verified':6,'checked_by':'build_report.py','runtime_validation':False}
if (ROOT/'local-dispatch-paths.json').exists():
    paths=json.loads((ROOT/'local-dispatch-paths.json').read_text(encoding='utf8'))['paths']
    for x in paths:
        chunk=bytes.fromhex(x['path_bytes_hex']);o=x['path_bytes_file_offset'];assert raw[o:o+len(chunk)]==chunk;assert digest(chunk)==x['path_bytes_sha256']
    validation['local_success_fallthrough_paths_verified_against_source']=len(paths)
(ROOT/'verification.json').write_text(json.dumps(validation,indent=2),encoding='utf8')
print(json.dumps(validation,indent=2))
