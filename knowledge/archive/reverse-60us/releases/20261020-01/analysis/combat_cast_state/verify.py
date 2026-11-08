"""Verify saved evidence and the intentionally narrow phase-resource contract."""
from pathlib import Path
import hashlib, json, struct
import static_scan as s

ROOT=Path(__file__).resolve().parent
index=json.loads((ROOT/'evidence-index.json').read_text(encoding='utf8'))
contract=json.loads((ROOT/'phase-animation-contract.json').read_text(encoding='utf8'))
vectors=json.loads((ROOT/'state10-request-vectors.json').read_text(encoding='utf8'))
assert hashlib.sha256(s.RAW).hexdigest()==index['source_sha256']==contract['source_sha256']
for row in index['excerpts']:
    raw,offset=s.chunk(row['start_va'],row['length'])
    saved=(ROOT/f"{row['start_va']:08X}-{row['start_va']+row['length']:08X}.bin").read_bytes()
    assert offset==row['file_offset'] and raw==saved
    assert hashlib.sha256(raw).hexdigest()==row['chunk_sha256']

anchors={
 0x73a17a:'e8b1b5d8ff', # job apply -> shared apply
 0x4c579b:'e8d08b0100', # shared apply -> character apply
 0x726173:'e85898d9ff', # Swordman tick -> common processing
 0x4bfab8:'e863c70100', # common processing -> character tick
 0x4de602:'ff93e0050000', # phase0 getter
 0x4de60b:'ff93f0000000', # animation install
 0x4de7dd:'ff97e4050000', # phase1 getter
 0x4de7e6:'ff97f0000000', # animation install
 0x4dcd52:'ff9084070000', # phase0 -> callback
 0x4d81e1:'ff928c020000', # callback -> pending request
 0x4dcfb6:'ff9284070000', # phase1 -> callback(-1,0)
 0x71caf0:'ff908c020000', # Swordman74 end override
 0x72617e:'33db',         # Swordman constant EBX
 0x6a373c:'33ff',         # Fighter join constant EDI
 0x6d50ab:'33ff',         # Gunner branch constant EDI
 0x6d511b:'33ff',         # Gunner other branch constant EDI
}
for va,hexbytes in anchors.items():
    assert s.chunk(va,len(bytes.fromhex(hexbytes)))[0].hex()==hexbytes,(hex(va),s.chunk(va,len(bytes.fromhex(hexbytes)))[0].hex(),hexbytes)
assert struct.unpack('<I',s.chunk(0x73d504+2*4,4)[0])[0]==0x73a168
assert struct.unpack('<I',s.chunk(0x73d5c0+4*4,4)[0])[0]==0x73b42c
assert s.chunk(0x4de334+10,1)[0]==b'\x02'
assert struct.unpack('<I',s.chunk(0x4de314+2*4,4)[0])[0]==0x4dcce4
for controller in contract['controllers']:
    vtable=int(controller['vtable_va'],0)
    for off,entry in controller['slots'].items():
        assert struct.unpack('<I',s.chunk(vtable+int(off,0),4)[0])[0]==int(entry,0)
for tag in contract['chr_tag_mapping']:
    raw=(f"[{tag['pvf_tag']}]"+'\0').encode('utf-16le')
    assert s.chunk(int(tag['tag_string_va'],0),len(raw))[0]==raw
for row in vectors['paths']:
    raw,_=s.chunk(int(row['previous_path_start_va'],0),row['previous_path_length'])
    assert hashlib.sha256(raw).hexdigest()==row['previous_path_bytes_sha256']
    values=row['append_values']
    assert row['append_count']==len(values) and values[0]['expression']==values[1]['expression']==0
    assert values[2]['expression']==row['skill_id'] and values[5]['expression']==row['casting_animation_index']
    assert len(values)==(11 if row['native_class']=='Swordman' and row['skill_id']==23 else 8)
assert contract['binding_count']==len(contract['bindings'])==len(vectors['paths'])==18
for row in contract['bindings']:
    assert row['mode']==row['initial_phase']==0
    assert row['full_skill_controller_status']==row['attack_binding_status']==row['effect_binding_status']=='unresolved'
    for variant in row['variants']:
        assert len(variant['phases'])==2
        assert variant['registered']==(variant['skill_source'] is not None)
        if not variant['registered']:
            assert variant['class_id']==5 and row['skill_id'] in [54,70]
        for phase in variant['phases']:
            assert phase['pvf_tag']==f"throw motion {row['animation_index']+1}-{phase['phase']+1}"
            assert phase['scope']=='phase_body_animation_only'
            assert phase['chr_source']['archive_sha256']==contract['pvf_sha256']

out={'source_sha256':contract['source_sha256'],'byte_excerpts_verified':len(index['excerpts']),'instruction_anchors_verified':len(anchors),'controller_vtable_slots_verified':sum(len(c['slots']) for c in contract['controllers']),'native_tag_strings_verified':len(contract['chr_tag_mapping']),'state10_request_paths_verified':len(vectors['paths']),'phase_resource_rows_verified':sum(len(v['phases']) for r in contract['bindings'] for v in r['variants']),'registered_variant_count':contract['registered_variant_count'],'registered_phase_resource_count':sum(len(v['phases']) for r in contract['bindings'] for v in r['variants'] if v['registered']),'unregistered_variant_count':contract['unregistered_variant_count'],'observed_execution':False,'status':'static_evidence_and_contract_checks_passed'}
(ROOT/'verification.json').write_text(json.dumps(out,indent=2),encoding='utf8')
print(json.dumps(out,indent=2))
