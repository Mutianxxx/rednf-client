"""Read-only bindings and event sampler for an independent scene preview.

No browser/app files, archive contents, original binaries or resources are
modified. Resource normalization is explicitly a report-loader policy.
"""
from pathlib import Path
from dataclasses import asdict
import hashlib
import json
import re

from scene_state_model import SceneState, selected_config, SELECTED

ROOT = Path(__file__).resolve().parent
PVF_SHA256 = '23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98'


class ScenePreviewCatalog:
    def __init__(self, resource_report=ROOT / 'scene-resources.json'):
        self.report_path = Path(resource_report).resolve()
        self.root = self.report_path.parent
        self.report = json.loads(self.report_path.read_text(encoding='utf8'))
        if self.report['archive_sha256'] != PVF_SHA256:
            raise ValueError('Preview bindings belong to a different PVF archive')
        self.rows = {r['path']: r for r in self.report['resources']}
        self.contract = json.loads((self.root / 'scene-specialized-contract.json').read_text(encoding='utf8'))
        self._verified = set()

    def raw_bytes(self, path):
        """Return source-bound exported bytes, checking the export against SHA."""
        row = self.rows[path.lower()]
        data = (self.root / row['raw_export']).read_bytes()
        if hashlib.sha256(data).hexdigest() != row['sha256']:
            raise ValueError(f'Resource export hash mismatch: {path}')
        self._verified.add(row['path'])
        return data

    def resource(self, path):
        row = self.rows[path.lower()]
        if row['path'] not in self._verified:
            self.raw_bytes(row['path'])
        return {
            'pvf_path': row['path'], 'source_sha256': row['sha256'],
            'source_size': row['size'], 'encoding': row['encoding'],
            'raw_export': str(self.root / row['raw_export']),
            'utf8_export': str(self.root / row['text_export']),
            'entry_crc_verified_in_extractor': row['entry_crc_verified'],
            'export_sha256_checked_now': True,
        }

    def animation(self, path):
        """Expose exact ordered ANI fields; no timer or rendering reinterpretation."""
        binding = self.resource(path)
        fields = self.rows[path.lower()]['fields']
        headers = []
        frames = []
        current = None
        for node in fields:
            match = re.fullmatch(r'FRAME(\d+)', node['tag'], flags=re.IGNORECASE)
            if match:
                current = {'index': int(match.group(1)), 'declared_tag': node['tag'],
                           'source_line': node['line'], 'ordered_fields': []}
                frames.append(current)
            elif current is None:
                headers.append(node)
            else:
                current['ordered_fields'].append(node)
        header_map = {n['tag'].upper(): n['values'] for n in headers}
        return {**binding, 'declared_loop': header_map.get('LOOP'),
                'declared_frame_max': header_map.get('FRAME MAX'),
                'ordered_header_fields': headers, 'frames': frames,
                'timing_policy': 'Raw PVF delay values retained; use independently recovered native ANI clock semantics.'}

    def object(self, object_id):
        """OBJ, all basic/etc ANI, ordered parameters and initial counter state."""
        config = selected_config(object_id, self.report)
        identity = next(r for r in self.contract['factory']['selected'] if r['id'] == object_id)
        basic = self.animation(config.path(config.basic))
        etc = [self.animation(config.path(raw)) if raw else None for raw in config.etc]
        state = SceneState(config)
        parameters = {
            'native_hp_initial': state.hp,
            'native_max_hp_initial': state.max_hp,
            'native_count_initial': state.count,
            'ordered_int_data': config.ints,
            'ordered_string_data': config.strings,
        }
        if config.kind == 'grass':
            parameters.update({'contact_count_threshold': 2 if config.etc and config.etc[0] else 1,
                               'particle_absolute_z': config.ints[0] if config.ints else 0,
                               'pass_all': config.pass_all,
                               'hit_count_uses_hp': False,
                               'bend_initially_enabled': state.bend_enabled,
                               'requires_input': 'native_accepted_contact'})
        else:
            parameters.update({'count_equality_trigger': config.ints[0],
                               'count_limit': config.ints[1],
                               'destroy_after_count_limit': bool(config.ints[2]),
                               'particle_xyz_offset': config.ints[3:6],
                               'requires_input': 'native_absolute_hp_write'})
        return {
            'object_id': object_id, 'native_identity': identity,
            'obj': self.resource(config.source_path),
            'config': asdict(config), 'parameters': parameters,
            'basic_ani': basic, 'etc_ani': etc,
            'initial_state': state.snapshot(),
            'contract': str(self.root / 'scene-specialized-contract.json'),
            'resolver_policy': self.report['resolver_policy'],
            'particle_policy': 'PTL dispatch only; internal particle simulation remains unknown.',
        }

    def sampler(self, object_id, *, local_authority=True, xyz=(0, 0, 0)):
        # Verify original OBJ and ANI exports before exposing an initial scene.
        self.object(object_id)
        return SceneEventSampler(SceneState(selected_config(object_id, self.report),
                                             local_authority=local_authority, xyz=tuple(xyz)))


class SceneEventSampler:
    def __init__(self, state):
        self.state = state

    def snapshot(self):
        return self.state.snapshot()

    def sample(self, event):
        """Apply one explicit native event and return ordered output plus state.

        Supported kinds deliberately exclude elapsed-time, overlap and damage.
        Caller may keep its own provenance in event['input_provenance'].
        """
        kind = event['kind']
        if kind == 'native_absolute_hp_write':
            outputs = self.state.on_native_hp_write(event['new_absolute_hp'])
        elif kind == 'native_accepted_contact':
            outputs = self.state.on_native_accepted_contact()
        elif kind == 'native_hit_visual_gate':
            outputs = self.state.on_native_hit_visual_gate(event['qualifies'])
        elif kind == 'native_ani_ended':
            outputs = self.state.on_native_frame_ended()
        elif kind == 'native_bend_direction':
            outputs = self.state.on_native_bend_direction(event['direction'])
        elif kind == 'native_self_removed':
            outputs = self.state.on_native_removed()
        else:
            raise ValueError(f'Unsupported scene event {kind!r}; supply an explicit native event, not overlap/damage/elapsed time')
        return {'input': dict(event), 'output_events': outputs, 'state': self.snapshot()}


def load_selected_catalog():
    catalog = ScenePreviewCatalog()
    return {'archive_sha256': catalog.report['archive_sha256'],
            'objects': [catalog.object(object_id) for object_id in SELECTED]}


if __name__ == '__main__':
    # stdout only; callers decide where to retain a derived catalog, if needed.
    print(json.dumps(load_selected_catalog(), ensure_ascii=False, indent=2))
