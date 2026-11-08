"""Current-source scene bindings and explicit-event inspection, without damage guesses."""
from pathlib import Path
import sys

EVIDENCE = Path(__file__).resolve().parents[1]/'analysis/combat_native_collision'
if str(EVIDENCE) not in sys.path:
    sys.path.insert(0, str(EVIDENCE))
from scene_preview_loader import ScenePreviewCatalog


class SceneObjects:
    def __init__(self, catalog, executable_sha256):
        self.catalog = catalog
        self.bindings = ScenePreviewCatalog()
        if (executable_sha256 != self.bindings.contract['source']['sha256'] or
                catalog.source['sha256'] != self.bindings.report['archive_sha256']):
            raise ValueError('场景状态合同与当前 EXE/PVF 身份不符')
        self.objects = {}
        for object_id in (221, 224, 244):
            obj = self.bindings.object(object_id)
            for resource in [obj['obj'], obj['basic_ani'], *obj['etc_ani']]:
                if resource and catalog.identity(resource['pvf_path'])['sha256'] != resource['source_sha256']:
                    raise ValueError('场景资源与当前 PVF 不符: '+resource['pvf_path'])
            self.objects[object_id] = obj

    def summary(self):
        return dict(objects=[dict(object_id=i, path=o['obj']['pvf_path'],
            kind=o['config']['kind'], parameters=o['parameters']) for i,o in self.objects.items()],
            scope='明确输入事件后的场景状态采样；几何接触不自动产生事件，PTL 仅记录调用')

    def inspect(self, object_id, events):
        if object_id not in self.objects:
            raise ValueError('仅核对了场景 ID 221/224/244')
        if not isinstance(events, list) or len(events) > 64:
            raise ValueError('场景采样需要最多 64 个明确事件')
        sampler = self.bindings.sampler(object_id)
        trace = []
        for event in events:
            if not isinstance(event, dict) or not isinstance(event.get('kind'), str):
                raise ValueError('每个场景事件需要明确 kind')
            if event['kind'] == 'native_absolute_hp_write':
                value = event.get('new_absolute_hp')
                if type(value) is not int or not -2**31 <= value < 2**31:
                    raise ValueError('HP 输入必须是新的绝对 int32 值')
            if event['kind'] == 'native_hit_visual_gate' and type(event.get('qualifies')) is not bool:
                raise ValueError('视觉 gate 需要明确布尔值')
            if event['kind'] == 'native_bend_direction' and event.get('direction') not in (0,1,2,3,4):
                raise ValueError('方向输入需要 0..4')
            trace.append(sampler.sample({**event, 'input_provenance':'explicit preview fixture; not a captured game event'}))
        current = sampler.snapshot()
        return dict(binding=self.objects[object_id], events=events, trace=trace,
            current=current, animation_path=current['current_ani'] if current['active'] else None,
            notice='手动事件采样；已恢复计数与资源切换。未自动接受命中或计算伤害；粒子和音效只列出调用。',
            native_runtime_observed=False, native_animation_clock_executed=False)
