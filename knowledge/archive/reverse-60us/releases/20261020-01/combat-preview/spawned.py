"""Source-bound visual/attack-entity resource timelines, independent of HP rules."""
from pathlib import Path
import json


class SpawnedScenes:
    def __init__(self,catalog,exe_sha256,cast_phases,contract_path=None):
        self.catalog=catalog
        self.cast_phases=cast_phases
        self.data=json.loads(Path(contract_path or Path(__file__).with_name(
            'spawn-contract.json')).read_text(encoding='utf-8'))
        source=self.data['source']
        self.compatible=(source['executable_sha256']==exe_sha256 and
                         source['pvf_sha256']==catalog.source['sha256'])

    def summary(self):
        return dict(source_compatible=self.compatible,full_controllers=0,
                    entries=[dict(class_id=0,skill_id=32,variant='phase0-resource-timeline',
                        label='裂波斩：两条视觉轨与独立攻击实体',
                        contract='../analysis/combat_spawned_object/preview-contract.json')]
                        if self.compatible else [])

    def scene(self,class_id,skill_id,spawn_gate=True):
        if not self.compatible:raise ValueError('EXE/PVF 与生成物证据来源不符')
        if (class_id,skill_id)!=(0,32):raise ValueError('此技能的生成物时间轨尚未核对')
        identity=self.data['identity']
        for path,digest in [(identity['skill_path'],identity['skill_sha256']),
                            (identity['obj_path'],identity['obj_sha256'])]:
            if self.catalog.identity(path)['sha256']!=digest:
                raise ValueError('技能/OBJ 与当前绑定证据不符')
        phase=self.cast_phases.phase(0,32,0)
        tracks=[dict(role='body',path=phase['animation_path'],clock='frozen',layer=0,
                     offset=[0,0,0],source=phase['animation_source'],binding=phase['phase_binding'])]
        for index,record in enumerate(self.data['tracks']):
            if self.catalog.identity(record['path'])['sha256']!=record['sha256']:
                raise ValueError('ANI 与生成物证据来源不符')
            invisible=record['role']=='spawned_invisible_attack_entity'
            if invisible and not spawn_gate:continue
            layer=record.get('attach_stack_args',[0])[0]
            tracks.append(dict(role='spawned_attack' if invisible else 'effect',
                path=record['path'],clock='elapsed',layer=layer,offset=[0,0,0],
                source=self.catalog.identity(record['path']),
                end_behavior='remove' if invisible else 'hold',
                # The interval models source DELAY at baseline rate. Native
                # transport/tick may apply removal later than the ANI ended bit.
                end_time_ms=record['frame_delay_sum'] if invisible else None,
                native_role=record['role'],binding={k:v for k,v in record.items() if k!='frames'}))
        boundaries=sorted({v for t in self.data['tracks'] for f in t['frames']
                           for v in (f['start'],f['end'])})
        return dict(contract=dict(class_id=0,skill_id=32,variant='phase0-resource-timeline',
                    label='裂波斩 phase0 效果轨',full_controller=False,
                    source_contract='../analysis/combat_spawned_object/preview-contract.json'),
                    tracks=tracks,duration_ms=max(boundaries),sample_times=boundaries,
                    body_clock='frozen-phase0-reference',spawn_gate_assumed=bool(spawn_gate),
                    attack_info=self.data['action_binding']['attack_info'],
                    source_delay_model=True,native_clock_observed=False,
                    notice='主体冻结在 phase0 第0帧作为位置参考；两条视觉与攻击实体独立播放。'
                           '时间采用源 DELAY、基准速率，归属门通过由预览选项指定。'
                           '未执行实际命中、动态伤害、受击或状态切换。',
                    geometry_status='Invisible attack entity geometry; eligibility/HP/reaction unresolved')
