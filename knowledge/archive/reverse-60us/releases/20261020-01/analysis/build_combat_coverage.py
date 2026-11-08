"""Source-linked checkpoint matrix; never upgrades a controller from resource names."""
from pathlib import Path
import csv
import hashlib
import json
from collections import Counter

ROOT=Path(__file__).resolve().parent.parent
OUT=ROOT/'analysis/combat_progress'
OUT.mkdir(exist_ok=True)

def read(path):return json.loads((ROOT/path).read_text(encoding='utf-8'))

skills=read('analysis/combat_catalog/skills.json')
dispatch=read('analysis/combat_skill_dispatch/local-dispatch-paths.json')
casts=read('analysis/combat_cast_state/phase-animation-contract.json')
preview=read('combat-preview/contracts.json')
spawn=read('combat-preview/spawn-contract.json')
native={'Swordman':[0],'Fighter':[1],'Gunner_variants_2_5':[2,5],
        'Mage':[3],'Priest':[4]}
# This is a conditional candidate association for the shared Gunner controller.
for row in dispatch['paths']:
    if row['native_class'] not in native:
        raise ValueError('Unreviewed native class '+row['native_class'])
rows=[]
for s in skills:
    key=(s['class_id'],s['skill_id'])
    paths=[p for p in dispatch['paths'] if p['skill_id']==s['skill_id']
           and s['class_id'] in native[p['native_class']]]
    phases=[(b,v) for b in casts['bindings'] if b['skill_id']==s['skill_id']
            for v in b['variants'] if v['class_id']==s['class_id'] and v.get('registered',True)]
    fragments=[c for c in preview['skills'] if (c['class_id'],c['skill_id'])==key]
    rows.append(dict(class_id=s['class_id'],class_label=s['class_label'],skill_id=s['skill_id'],
        path=s['path'],source_sha256=s['source']['sha256'],
        native_local_request_count=len(paths),
        native_local_states=sorted({p['state'] for p in paths}),
        request_scope='conditional shared Gunner class candidates' if paths and key[0] in (2,5) else
                      ('local success paths only' if paths else 'unresolved'),
        phase_body_ani_count=sum(len(v['phases']) for _,v in phases),
        phase_variant_guard=sorted({v['variant_guard_status'] for _,v in phases}),
        executable_partial_fragments=[c['variant'] for c in fragments]+(['phase0-resource-timeline'] if key==(0,32) else []),
        spawned_object_contract='analysis/combat_spawned_object/preview-contract.json' if key==(0,32) else None,
        full_controller='unresolved',
        original_game_comparison='not_observed'))
sources={}
for path in ['analysis/combat_catalog/skills.json','analysis/combat_skill_dispatch/local-dispatch-paths.json',
             'analysis/combat_cast_state/phase-animation-contract.json','combat-preview/contracts.json','combat-preview/spawn-contract.json',
             'analysis/combat_hit_lifecycle/history-contract.json','analysis/combat_motion/motion-contract.json',
             'analysis/combat_motion/owner/owner-contract.json','analysis/combat_reaction_motion/reaction-motion-contract.json',
             'analysis/combat_native_collision/scene-destruction-contract.json',
             'analysis/combat_native_collision/scene-specialized-contract.json',
             'analysis/combat_spawned_object/scalar/scalar-contract.json']:
    sources[path]=hashlib.sha256((ROOT/path).read_bytes()).hexdigest()
summary=dict(source_exe_sha256=preview['source_exe_sha256'],source_pvf_sha256=preview['source_pvf_sha256'],
    skill_rows=len(rows),native_local_request_paths=len(dispatch['paths']),
    native_local_unique_class_skill_state=len({(p['native_class'],p['skill_id'],p['state']) for p in dispatch['paths']}),
    phase_request_paths=casts['binding_count'],phase_registered_variants=casts['registered_variant_count'],
    phase_registered_resources=sum(len(v['phases']) for b in casts['bindings'] for v in b['variants'] if v.get('registered',True)),
    phase_unregistered_variant_candidates=casts['unregistered_variant_count'],
    executable_partial_fragments=sum(len(r['executable_partial_fragments']) for r in rows),
    full_controllers=0,
    subsystem_previews=dict(scene_object_ids=[221,224,244],scene_input='explicit native-event fixtures; no automatic damage or particles',
        reaction_motion='explicit decoded inputs and dt; horizontal free axis only; no automatic state exit',
        movement_owner='bounded source-derived model; not integrated into skill execution',
        hit_history='static install/reset/canonical ownership contract; full lifecycle not integrated'),
    warning='Counts describe different evidence layers. Do not add them or infer complete skill support.',
    source_reports=sources)
(OUT/'coverage.json').write_text(json.dumps(dict(summary=summary,skills=rows),ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
with (OUT/'coverage.csv').open('w',encoding='utf-8-sig',newline='') as stream:
    writer=csv.DictWriter(stream,fieldnames=list(rows[0]));writer.writeheader()
    for row in rows:writer.writerow({k:json.dumps(v,ensure_ascii=False) if isinstance(v,list) else v for k,v in row.items()})
print(json.dumps(summary,ensure_ascii=False))
