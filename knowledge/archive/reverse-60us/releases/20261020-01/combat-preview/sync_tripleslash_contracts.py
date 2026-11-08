"""Generate bounded, manual per-segment previews from current native evidence."""
from pathlib import Path
import copy
import hashlib
import json

ROOT=Path(__file__).resolve().parent
source=ROOT.parent/'analysis/combat_tripleslash/tripleslash-contract.json'
raw=source.read_bytes();data=json.loads(raw)
path=ROOT/'contracts.json';preview=json.loads(path.read_text(encoding='utf-8'))
assert data['source_exe']['sha256']==preview['source_exe_sha256']
assert data['source_pvf']['sha256']==preview['source_pvf_sha256']
preview['skills']=[c for c in preview['skills'] if not(c['class_id']==0 and c['skill_id']==8)]
level_base=copy.deepcopy(preview['skills'][0]['level_consumption'])
for segment in data['segments_by_count']['3']:
    number=segment['segment']
    level=copy.deepcopy(level_base)
    level.update(column=segment['level_column'],install='0x732B66..0x732BCE',
                 evidence='analysis/combat_tripleslash/tripleslash-contract.json')
    preview['skills'].append(dict(class_id=0,skill_id=8,variant=f'three-segment-{number}',
        label=f'普通三段斩 · 第 {number+1} 段',status='partial_segment_inspection',
        preview_scope='manual independent segment; native movement, continuation and hit acceptance not executed',
        state=22,segment=number,segment_count=3,continuation_min_frame=segment['continuation_min_frame'],
        required_context=dict(mode='dungeon',baseline_animation_speed=1,
            segment_selected_manually=True,body_frame_zero_is_preview_policy=True),
        motion=dict(tag='etc motion',index=segment['body_motion_slot']),
        attack_info=dict(tag='etc attack info',index=segment['attack_info_slot']),
        effect_scale=None,level_consumption=level,
        effects=[dict(layer=e['attach_key'],path=e['animation']['path'],offset=[0,0,0]) for e in segment['effects']],
        evidence=['analysis/combat_tripleslash/tripleslash-contract.json',
                  'analysis/combat_native_skill_slots/hardattack-equipment-contract.json'],
        derivation=dict(source_contract_sha256=hashlib.sha256(raw).hexdigest()),
        unknown=data['limitations']))
path.write_text(json.dumps(preview,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('Added manual ordinary TripleSlash segment fragments: 3')
