"""Compile explicitly evidenced controller fragments to a portable preview scene.

No name-based skill/animation matching; source identity and CHR slots are checked.
The returned scene is a partial reconstruction, not an emulation of damage/states.
"""
from __future__ import annotations
import json
from pathlib import Path

from catalog import resolve_relative
from pvf_model import node_record
from executable_source import inspect_executable


class Controllers:
    def __init__(self, catalog, executable, contracts_path=None):
        self.catalog=catalog
        path=Path(contracts_path or Path(__file__).with_name('contracts.json'))
        self.data=json.loads(path.read_text(encoding='utf-8'))
        self.executable_source=inspect_executable(executable)
        self.exe_sha256=self.executable_source['observed_sha256']
        self.evidence_sha256=self.executable_source['static_evidence_sha256']
        self.compatible=(self.data['source_pvf_sha256']==catalog.source['sha256'] and
                         self.data['source_exe_sha256']==self.evidence_sha256)

    def summary(self):
        return dict(**self.data,source_compatible=self.compatible,
                    observed_exe_sha256=self.exe_sha256,
                    executable_source=self.executable_source,
                    supported_full_controllers=0,
                    partial_controller_variants=len(self.data['skills']) if self.compatible else 0)

    def scene(self,class_id,skill_id,variant='normal-no-charge',equipment=None,level=1):
        if not self.compatible:
            raise ValueError('当前 EXE/PVF 与合同来源不匹配，不能套用此原生状态合同')
        contract=next((c for c in self.data['skills'] if
                       (c['class_id'],c['skill_id'],c['variant'])==(class_id,skill_id,variant)),None)
        if contract is None:raise ValueError('此技能分支尚无可执行预览合同')
        char=next(c for c in self.catalog.characters if c['class_id']==class_id)
        skill=next(s for s in self.catalog.skills if s['class_id']==class_id and s['skill_id']==skill_id)
        if not isinstance(level,int) or isinstance(level,bool) or level<1:
            raise ValueError('技能等级必须为正整数')
        def slot(ref):
            found=[s for s in char['slots'] if s['tag']==ref['tag'] and s['index']==ref['index']]
            if len(found)!=1 or found[0]['empty'] or not found[0]['exists']:
                raise ValueError('原 CHR 槽缺失或不唯一，停止套用合同')
            return found[0]
        motion=slot(contract['motion']);attack=slot(contract['attack_info'])
        # Native fild/fmul/fstp, using the observed float32 multiplier.
        import struct
        scale_spec=contract['effect_scale']
        scale=None
        if scale_spec:
            nodes=self.catalog.document(skill['path']).find(scale_spec['tag'],scope=tuple(scale_spec['scope']))
            if len(nodes)!=1:raise ValueError('原 SKL 特效 scale 字段不唯一')
            scale=struct.unpack('<f',struct.pack('<f',nodes[0].data[scale_spec['index']]*scale_spec['multiplier_float32']))[0]
        level_spec=contract['level_consumption']
        level_nodes=self.catalog.document(skill['path']).find(level_spec['tag'],scope=tuple(level_spec['scope']))
        if len(level_nodes)!=1:raise ValueError('原 SKL level info 字段不唯一')
        values=level_nodes[0].data
        columns=values[0] if values else 0
        if not isinstance(columns,int) or columns<=0 or (len(values)-1)%columns:
            raise ValueError('level info 列数与原生分列表不符')
        rows=(len(values)-1)//columns
        if level>rows:raise ValueError('等级超出此分支原 PVF 的等级表')
        if not 0<=level_spec['column']<columns:raise ValueError('技能等级列不存在')
        raw=values[1+(level-1)*columns+level_spec['column']]
        if not isinstance(raw,int):raise ValueError('level info 当前样本要求整数')
        installed=raw-100
        level_info=dict(level=level,available_levels=rows,column=level_spec['column'],raw_value=raw,
                        installed_atk_bonus=installed,mathematical_early_ratio=raw/100,
                        float32_constant=level_spec['multiplier_float32'],
                        field=node_record(level_nodes[0]),contract=level_spec,
                        note='原 PVF 基准参数与早期倍率；未执行运行时修正和完整伤害公式')
        tracks=[dict(role='body',path=motion['path'],clock='body',layer=0,offset=[0,0,0],
                     binding=motion,source=self.catalog.identity(motion['path']))]
        equipment_info=None
        if equipment:
            # An initially bounded, independently traced EQU→LAY sample.
            # Additional equipment is enabled only after its layer records are checked.
            allowed='equipment/character/swordman/weapon/club/n_club_axshauta.equ'
            if equipment!=allowed:raise ValueError('这件装备尚未核对其层绑定；当前可选择 n_club_axshauta.equ')
            equ=self.catalog.document(equipment)
            variation=equ.find('variation')
            if len(variation)!=1 or variation[0].data!=[2,6]:raise ValueError('装备 variation 与已核对样本不符')
            equipment_info=dict(path=equipment,source=self.catalog.identity(equipment),
                                variation=variation[0].data,layers=[])
            for order,record in enumerate(equ.find('layer variation')):
                values=record.data
                if len(values)!=4 or values[2]!='<include>' or values[3]!='equipment/character/swordman.lay':
                    raise ValueError('装备 layer/include 格式与已核对样本不符')
                lay=self.catalog.document(values[3]);motions=lay.find('etc motion')
                if len(motions)!=1:raise ValueError('LAY etc motion 不唯一')
                token=motions[0].values[contract['motion']['index']]
                path=resolve_relative(equipment,token.text.replace('%s',values[1]))
                layer=dict(role='equipment',path=path,clock='body',layer=values[0],offset=[0,0,0],
                           variation=variation[0].data,source_order=order,
                           binding=dict(equipment=equipment,record=node_record(record),
                                        layer_source=self.catalog.identity(values[3]),motion_token=token.to_dict()),
                           source=self.catalog.identity(path))
                tracks.append(layer);equipment_info['layers'].append(layer)
        for effect in contract['effects']:
            tracks.append(dict(role='effect',clock='elapsed',image_rate_override=[scale,scale] if scale is not None else None,
                               source=self.catalog.identity(effect['path']),**effect))
        return dict(contract=contract,character_source=char['source'],skill_source=skill['source'],
                    tracks=tracks,attack_info=dict(binding=attack,source=self.catalog.identity(attack['path']),
                    fields=[node_record(n) for n in self.catalog.document(attack['path']).events]),
                    equipment=equipment_info,
                    level_consumption=level_info,
                    geometry_status='native XYZ AABB only; hit acceptance and reaction not executed',
                    equipment_status='EQU→LAY same-motion layers, native ascending order and body-frame timing' if equipment else
                                     'No equipment selected; body and generated effects have no attack boxes')

    def monster_resources(self,path):
        if not path.lower().endswith('.mob'):raise ValueError('需要当前 PVF 的 .mob 路径')
        doc=self.catalog.document(path)
        refs=[]
        for node in doc.events:
            name=node.name.lower()
            if not ('motion' in name or 'action' in name):continue
            for token in node.values:
                if token.kind!='string' or not token.text.endswith(('.ani','.act')):continue
                target=resolve_relative(path,token.text)
                refs.append(dict(tag=node.name,path=target,token=token.to_dict(),scope=list(node.scope),
                                 exists=target in self.catalog.pvf.by_path,
                                 kind='animation' if target.endswith('.ani') else 'action'))
        return dict(path=path,source=self.catalog.identity(path),resources=refs,
                    die_effect=[node_record(n) for n in doc.find('die effect')],
                    notice='原 MOB 资源引用；选择播放用于检查，尚未执行受击/死亡状态机和 ACT 触发器')
