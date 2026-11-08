"""Produce a reviewable, source-bound state-10 phase ANI contract."""
from pathlib import Path
import hashlib, json, struct
import static_scan as s

ROOT = Path(__file__).resolve().parent
CATALOG = ROOT.parent / 'combat_catalog'
characters = json.loads((CATALOG / 'characters.json').read_text(encoding='utf-8'))
skills = json.loads((CATALOG / 'skills.json').read_text(encoding='utf-8'))
requests = json.loads((ROOT / 'state10-request-vectors.json').read_text(encoding='utf-8'))['paths']

def hx(n):
    return f'0x{n:08x}'

rea = []
for number in [15, 42, 43, 44, 45, 46]:
    files = list((ROOT.parent / 'rea' / 'results').glob(f'{number:03}-*.json'))
    for file in files:
        envelope = json.loads(file.read_text(encoding='utf-8-sig'))
        d = envelope['structuredContent']
        rea.append({'file': str(file), 'evidence_id': d['evidence_id'], 'parameters': d.get('parameters')})

# Regions are intentionally focused; skipdata output in a region is not code
# reachability evidence. Assertions below select exact instruction anchors.
regions = [
 (0x7307b0,0x66),(0x7318a6,0x36),(0x73a168,0x2a),(0x73d504,47*4),(0x73d5c0,9*4),
 (0x4c5730,0x75),(0x4de370,0x69),(0x4de4a9,0x302),(0x4de7af,0x12a),(0x4deedb,0x14),
 (0x4bc645,0x82),(0x726150,0x2e),(0x4bf9d0,0xed),(0x4dc8b0,0x86),
 (0x4dcce4,0x330),(0x4de314,47),(0x4d80f0,0x119),(0x71cab0,0x5e),
 (0x745b80,0x3a),(0x747fd0,0x74),(0x4daaf0,0x20b),
 (0x88be23,0x148),(0xe1e968,0x13e),(0x468430,0x2d),
 (0x73b42c,0x55),(0x73c180,0x160),(0x69d4f0,0x100),(0x6cfc30,0x100),
 (0x6a367c,0xc2),(0x6d5069,0xd0),
]
for row in requests:
    regions.append((int(row['previous_path_start_va'],0), row['previous_path_length']))
excerpts = [s.save(start,length) for start,length in regions]

table = []
for index in range(4):
    for phase in [0,1]:
        tag = f'throw motion {index+1}-{phase+1}'
        parser_va = [0x88be23,0x88be4c,0x88be75,0x88be9e,0x88bec7,0x88bef0,0x88bf19,0x88bf42][index*2+phase]
        tag_va = [0xe1ea80,0xe1ea58,0xe1ea30,0xe1ea08,0xe1e9e0,0xe1e9b8,0xe1e990,0xe1e968][index*2+phase]
        table.append({'index': index, 'phase': phase, 'pvf_tag': tag, 'parser_branch_va': hx(parser_va), 'tag_string_va': hx(tag_va), 'template_offset': hx((0xb68 if phase==0 else 0xb78)+index*4), 'runtime_offset': hx((0x1be0 if phase==0 else 0x1bf0)+index*4)})

bindings = []
for request in requests:
    native = request['native_class']
    jobs = {'Swordman':[0], 'Fighter':[1], 'Gunner_variants_2_5':[2,5]}[native]
    variants = []
    for job in jobs:
        ch = next(c for c in characters if c['class_id']==job)
        skill = next((c for c in skills if c['class_id']==job and c['skill_id']==request['skill_id']), None)
        phases = []
        for phase in [0,1]:
            tag = f"throw motion {request['casting_animation_index']+1}-{phase+1}"
            slot = next((v for v in ch['slots'] if v['tag']==tag), None)
            assert slot and slot['exists']
            phases.append({'phase':phase, 'pvf_tag':tag, 'ani_path':slot['path'], 'chr_source_path':ch['path'], 'chr_source':ch['source'], 'source_token':slot['source_token'], 'guard':{'state':10, 'mode':0, 'stored_skill_id':request['skill_id'], 'stored_animation_index':request['casting_animation_index'], 'phase':phase}, 'scope':'phase_body_animation_only'})
        variants.append({'class_id':job, 'class_label':ch['label'], 'registered':skill is not None, 'registration_status':'registered_in_current_pvf' if skill else 'not_registered_in_current_pvf_do_not_offer_as_skill', 'skill_path_candidate':skill['path'] if skill else None, 'skill_registration_source':skill['registration_source'] if skill else None, 'skill_source':skill['source'] if skill else None, 'variant_guard_status':'unresolved_shared_gunner_job_2_or_5' if native=='Gunner_variants_2_5' else 'native_controller_class_confirmed', 'phases':phases})
    bindings.append({'native_class':native, 'skill_id':request['skill_id'], 'request_state':10, 'initial_phase':0, 'mode':0, 'animation_index':request['casting_animation_index'], 'request_call_va':request['request_call_va'], 'consume_call_va':request['consume_call_va'], 'request_path_sha256':request['previous_path_bytes_sha256'], 'rea_body_evidence_id':request['rea_body_evidence_id'], 'variants':variants, 'status':'native_phase_ani_binding_static', 'full_skill_controller_status':'unresolved', 'attack_binding_status':'unresolved', 'effect_binding_status':'unresolved', 'upstream_guards':'Input, previous-state, learned-skill, cooldown and variant gates are not fully recovered; request path is a conditional local success path, not unconditional skill availability.'})

fields = [
 (0,'phase','0x2420','State-10 phase; 0 initial, 1 release, 2 target-selection branch. Nonzero requests reuse stored phase-0 fields.'),
 (1,'mode','0x2428','Mode selector. Mode 0 enables Swordman job-specific effects; modes 1/2 use shared configured-object path. Do not name these with enums from another version.'),
 (2,'skill_id','0x242c','Stored skill ID. Native consumer, getter 0x745E80 and observed request literal agree.'),
 (3,'initial_phase_duration_raw','0x2434','Compared against elapsed state timer in phase 0; scaled by *1000 / protected this+0x1620. Exact semantic source of all dynamic call values remains separately unresolved.'),
 (4,'release_phase_duration_raw','0x243c','Compared against elapsed state timer in phase 1; -1 disables this timed completion; otherwise scaled by *1000 / this+0x1620.'),
 (5,'animation_index','0x2444','Phase 0 uses +0x5E0; phase 1 uses +0x5E4 with this index. Mode 2 substitutes +0x36C.'),
 (6,'initial_animation_control','local','Passed twice as first arguments to virtual +0x494 during phase 0. Value 4 triggers +0x554(duration,0); exact enum semantics not recovered.'),
 (7,'release_animation_control','0x2448','Passed twice as first arguments to +0x494 during phase 1; exact enum semantics not recovered.'),
 (8,'initial_animation_scale','local','Optional, defaults 1000; passed twice to +0x494 during phase 0. Do not interpret as time without tracing +0x494.'),
 (9,'release_animation_scale','0x244c','Optional, defaults 1000; passed twice to +0x494 during phase 1.'),
 (10,'target_selection_limit','0x2450','Optional, defaults -1; -1 goes directly to +0x784(1,0) after phase-0 wait, otherwise shared target search 0x4D5EB0/selection logic participates.'),
]

controllers=[]
for name,vt in [('Swordman',0xd80f94),('Fighter',0xd81774),('Gunner_variants_2_5',0xd81f54),('Mage',0xd82734),('Priest',0xd82f64)]:
    slots={hx(slot):hx(struct.unpack('<I',s.chunk(vt+slot,4)[0])[0]) for slot in [0x188,0x22c,0x36c,0x5e0,0x5e4,0x670,0x718,0x784]}
    controllers.append({'native_class':name, 'vtable_va':hx(vt), 'slots':slots})

contract = {
 'schema_version':1,'source':str(s.SOURCE),'source_sha256':hashlib.sha256(s.RAW).hexdigest(),
 'pvf_sha256':characters[0]['source']['archive_sha256'],'observed_execution':False,
 'scope':'18 observed local request paths with native state-10 phase body ANI bindings; not 18 complete skill implementations. Gunner resources remain conditional job-2/job-5 candidates. Two class-5 candidates have no current skill registration and must be excluded from skill selection.',
 'registered_variant_count':sum(v['registered'] for row in bindings for v in row['variants']),
 'unregistered_variant_count':sum(not v['registered'] for row in bindings for v in row['variants']),
 'rea_evidence':rea,'request_vector_ledger':'state10-request-vectors.json','binding_count':len(bindings),
 'vector_layout':[{'index':i,'name':name,'stored_at':off,'meaning':meaning,'consumer':'0x4de370'} for i,name,off,meaning in fields],
 'chr_tag_mapping':table,'controllers':controllers,'bindings':bindings,
 'phase_chain':[
  {'stage':'apply job handler','entry':'0x7307b0','native_class':'Swordman','state10_pre_switch_target':'0x73a168','shared_call':'0x73a17a -> 0x4c5730 -> 0x4de370'},
  {'stage':'phase0 ANI','entry':'0x4de4c2','call':'0x4de602 +0x5e0(index) then 0x4de60b +0xf0(ANI)','guard':'phase==0; mode!=2'},
  {'stage':'phase0 timer','entry':'0x4dcce4','call':'0x4dcd52 +0x784(1,0), or target-selection branch','guard':'49C090 true; elapsed(this+1564)>=scaled duration(this+2434); duration!=-1'},
  {'stage':'phase request','entry':'0x4d80f0','call':'0x4d81e1 +0x28c(10, [next_phase, optional target+44 ID],0,0,0)','guard':'49C090 true; next_phase!=-1; job override may intercept'},
  {'stage':'phase1 ANI','entry':'0x4de7af','call':'0x4de7dd +0x5e4(index) then 0x4de7e6 +0xf0(ANI)','guard':'phase==1; mode!=2'},
  {'stage':'Swordman effect','entry':'0x73b42c','call':'job handler after shared apply; stored skill ID and phase branches','guard':'state10 and mode==0; full effect behavior not recovered in this contract'},
  {'stage':'phase1 timer end','entry':'0x4dcf6c','call':'0x4dcfb6 or 0x4dd009 +0x784(-1,0)','guard':'elapsed>=scaled this+243c and duration!=-1; mode1/2 additionally require this+246c!=0'},
  {'stage':'end request','entry':'0x4d811b','call':'state0 on ground, state6 with [1,0,0] in air','guard':'next_phase==-1; Swordman mode0 skill74 redirects to state41 at 0x71caf0'},
 ],
 'limitations':[
  'No observed execution, packet recording or original-client screenshot comparison.',
  'Shared function call graph and local byte disassembly do not prove complete runtime reachability.',
  'Do not infer skill effects, projectiles, hitboxes, attack acceptance, cooldown, target choice or all job guards from phase ANI bindings.',
  'Timer reset is controlled by apply argument 3 in 0x4BAD60; that flag and packet/local-application route must be honored.',
  'Mage +5E0/+5E4 overrides select runtime this+2DE8 when 0x6DE720 is true; no Mage skill binding supplied here.',
  'No constants or enums imported from dnf-rebuild or another client version.',
 ],
}
(ROOT / 'phase-animation-contract.json').write_text(json.dumps(contract,ensure_ascii=False,indent=2),encoding='utf-8')
(ROOT / 'evidence-index.json').write_text(json.dumps({'source_sha256':contract['source_sha256'],'excerpts':excerpts,'rea_evidence':rea},ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'bindings':len(bindings),'variant_records':sum(len(v['variants']) for v in bindings),'phase_resources':sum(len(x['phases']) for v in bindings for x in v['variants']),'excerpts':len(excerpts),'rea_records':len(rea)}))
