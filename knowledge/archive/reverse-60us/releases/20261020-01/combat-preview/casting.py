"""Manual body-ANI inspection of source-bound native state-10 phases.

The user chooses the phase. No durations, passive objects, attacks or post-cast
skill effects are inferred from these bindings.
"""
import json
from pathlib import Path


class CastPhases:
    def __init__(self,catalog,exe_sha256,contract_path=None):
        self.catalog=catalog
        self.data=json.loads(Path(contract_path or Path(__file__).with_name(
            'cast-contracts.json')).read_text(encoding='utf-8'))
        self.compatible=(self.data['pvf_sha256']==catalog.source['sha256']
                         and self.data['source_sha256']==exe_sha256)

    def summary(self):
        registered={(s['class_id'],s['skill_id']) for s in self.catalog.skills}
        return dict(source_compatible=self.compatible,scope=self.data['scope'],
                    native_request_bindings=len(self.data['bindings']),
                    unregistered_variant_candidates=[dict(class_id=v['class_id'],skill_id=b['skill_id'])
                        for b in self.data['bindings'] for v in b['variants']
                        if (v['class_id'],b['skill_id']) not in registered],
                    entries=[dict(class_id=v['class_id'],skill_id=b['skill_id'],
                        variant_guard_status=v['variant_guard_status'],
                        phases=[dict(phase=p['phase'],path=p['ani_path'],tag=p['pvf_tag']) for p in v['phases']])
                        for b in self.data['bindings'] for v in b['variants']
                        if (v['class_id'],b['skill_id']) in registered] if self.compatible else [])

    def phase(self,class_id,skill_id,phase):
        if not self.compatible:raise ValueError('EXE/PVF 与施法阶段证据来源不匹配')
        matches=[(b,v,p) for b in self.data['bindings'] if b['skill_id']==skill_id
                 for v in b['variants'] if v['class_id']==class_id
                 for p in v['phases'] if p['phase']==phase]
        if len(matches)!=1:raise ValueError('此技能没有唯一核对的施法主体阶段')
        binding,variant,entry=matches[0]
        char=next(c for c in self.catalog.characters if c['class_id']==class_id)
        skills=[s for s in self.catalog.skills if s['class_id']==class_id and s['skill_id']==skill_id]
        if len(skills)!=1 or skills[0]['path']!=variant['skill_path_candidate']:
            raise ValueError('当前注册技能与阶段证据不符')
        if self.catalog.identity(skills[0]['path'])['sha256']!=variant['skill_source']['sha256']:
            raise ValueError('当前 SKL 与阶段证据不符')
        if char['path']!=entry['chr_source_path'] or char['source']['sha256']!=entry['chr_source']['sha256']:
            raise ValueError('当前 CHR 与阶段证据不符')
        slots=[s for s in char['slots'] if s['tag']==entry['pvf_tag'] and s['index']==0]
        if len(slots)!=1 or slots[0]['path']!=entry['ani_path'] or not slots[0]['exists']:
            raise ValueError('当前 CHR throw motion 槽与原生阶段证据不符')
        conditional=variant['variant_guard_status']!='native_controller_class_confirmed'
        return dict(class_id=class_id,skill_id=skill_id,phase=phase,
                    animation_path=entry['ani_path'],animation_source=self.catalog.identity(entry['ani_path']),
                    binding=binding,variant=variant,phase_binding=entry,
                    conditional_variant=conditional,full_controller=False,
                    notice=('枪手共享控制器的职业分支条件待恢复；此处只检查所选 CHR 的资源候选。' if conditional else '')+
                    '仅检查该施法阶段的主体动画；阶段时长、速度、装备、攻击和技能效果未执行')
