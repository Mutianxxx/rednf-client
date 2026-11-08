"""Executable, evidence-limited scene counters for current 60US OBJ221/224/244.

Inputs represent native events that have already happened. This module never
turns an AABB overlap into an accepted contact or computes numeric damage.
PTL output is an instruction to the still-unrecovered particle implementation.
"""
from dataclasses import dataclass, field, asdict
from pathlib import Path
import json
import posixpath

ROOT = Path(__file__).resolve().parent
SELECTED = {
    221: ('mapobject', 'passiveobject/mapobject/breakableobject/barrel.obj'),
    224: ('actiontree', 'passiveobject/mapobject/breakableobject/actiontree2lorien.obj'),
    244: ('grass', 'passiveobject/mapobject/breakableobject/smallgrasslorien.obj'),
}


@dataclass
class SceneConfig:
    object_id: int
    kind: str
    source_path: str
    source_sha256: str
    ints: list
    strings: list
    basic: str
    etc: list
    pass_all: bool
    hp_destroy: bool = False

    def path(self, raw):
        # This is the same explicit report resolver policy as scene-resources.
        # It is not a recovered native normalization implementation.
        return posixpath.normpath(posixpath.join(posixpath.dirname(self.source_path), raw)).lower() if raw else ''


def selected_config(object_id, report=None):
    if report is None:
        report = json.loads((ROOT / 'scene-resources.json').read_text(encoding='utf8'))
    kind, source = SELECTED[object_id]
    row = next(r for r in report['resources'] if r['path'] == source)
    fields = {n['tag']: n['values'] for n in row['fields']}
    ints = fields.get('int data', [])
    strings = fields.get('string data', [])
    if kind != 'grass' and (len(ints) < 7 or len(strings) < 6):
        raise ValueError('Counter subset requires seven ints and six strings; native short-vector behavior is not emulated')
    return SceneConfig(object_id, kind, source, row['sha256'], ints, strings,
                       fields['basic motion'][0], fields.get('etc motion', []),
                       fields.get('pass type') == ['[pass all]'],
                       fields.get('hp destroy') == [1])


@dataclass
class SceneState:
    config: SceneConfig
    local_authority: bool = True
    xyz: tuple = (0, 0, 0)
    hp: int = 0
    max_hp: int = 0
    count: int = 0
    current_ani: str = ''
    restore_basic_on_end: bool = False
    bend_enabled: bool = False
    bend_direction: int = 4
    active: bool = True
    events: list = field(default_factory=list)

    def __post_init__(self):
        c = self.config
        self.current_ani = c.path(c.basic)
        if c.kind == 'grass':
            self.bend_enabled = len(c.etc) > 2 and bool(c.etc[1]) and bool(c.etc[2])
        else:
            self.hp = self.max_hp = int(c.ints[6])

    def emit(self, kind, at, **values):
        self.events.append({'kind': kind, 'native_site': at, **values})

    def _active(self):
        if not self.active:
            raise ValueError('Native removal was applied; this model instance is inactive')

    def _ani(self, raw, at, reset=False):
        self.current_ani = self.config.path(raw)
        self.emit('select_ani', at, path=self.current_ani, reset=reset)

    def _particle(self, raw, xyz, at):
        if raw:
            self.emit('particle_dispatch', at, raw_path=raw,
                      report_resolved_path=self.config.path(raw), xyz=list(xyz),
                      internal_simulation_recovered=False)

    def _sound(self, raw, at):
        if raw:
            self.emit('sound_request', at, name=raw)

    def _remove(self, argument, at):
        # Request is not an observed deactivation or cleanup notification.
        self.emit('removal_request', at, argument=argument, actual_removal_applied=False)

    def on_native_hp_write(self, new_absolute_hp):
        """State1 HP has been applied. Runs the recovered MapObject HP callback.

        Do not call this with a damage delta or an invented preview damage value.
        """
        self._active()
        if self.config.kind == 'grass':
            raise ValueError('Grass stage count advances on native contact, independently of HP')
        if type(new_absolute_hp) is not int:
            raise TypeError('Expected native signed integer absolute HP')
        start = len(self.events)
        self.hp = new_absolute_hp
        self.emit('native_hp_written', '0x49D832', new_absolute_hp=self.hp)
        c = self.config
        if c.hp_destroy and self.max_hp > 0 and self.hp <= 0:
            self._remove(0, '0x49D114')
        if self.hp <= 0 and self.count < c.ints[1]:
            self.count += 1
            self.emit('counter_increment', '0x5F5B7E', count=self.count)
            if self.count == c.ints[0]:
                self.emit('counter_trigger', '0x5F5AF7',
                          slot394='0x60C660 -> 0x5F7750' if c.kind == 'actiontree' else '0x5F7750',
                          auxiliary_outputs='Not synthesized; selected initial vectors are empty')
                if c.etc and c.etc[0]:
                    self._ani(c.etc[0], '0x5F5B25', reset=False)
            self.hp = self.max_hp
            self.emit('hp_reset_to_max', '0x5F5B9C', absolute_hp=self.hp)
        elif len(c.etc) > 1 and c.etc[1]:
            self.restore_basic_on_end = True
            self._ani(c.etc[1], '0x5F5BEA', reset=True)
        if self.count >= c.ints[1] and bool(c.ints[2]):
            x, y, z = self.xyz
            dx, dy, dz = c.ints[3:6]
            self._particle(c.strings[2], (x + dx, y + dy, z + dz), '0x5F5F29')
            self._sound(c.strings[5], '0x5F5F75')
            if self.local_authority:
                self._remove(0, '0x5F5F8C')
        return self.events[start:]

    def on_native_hit_visual_gate(self, qualifies):
        """Optional MapObject received-hit ATK visual gate, supplied explicitly.

        This gate is evaluated before numeric HP processing in5F5FB0. It cannot
        be inferred from overlap, HP depletion or the scene counter.
        """
        self._active()
        if self.config.kind == 'grass':
            raise ValueError('MapObject hit visual gate is not a Grass controller input')
        start = len(self.events)
        if qualifies:
            c = self.config
            x, y, z = self.xyz
            dx, dy, dz = c.ints[3:6]
            self._particle(c.strings[1], (x + dx, y + dy, z + dz), '0x5F608C')
            self._sound(c.strings[4], '0x5F60D8')
        return self.events[start:]

    def on_native_accepted_contact(self):
        """Execute Grass5F33C0 after an explicit native accepted-contact input.

        Generic49F310 is maxHP-gated for the selected Grass. The subclass stage
        still advances independently of that generic method's return value.
        """
        self._active()
        if self.config.kind != 'grass':
            raise ValueError('MapObject count requires an explicit native absolute-HP write')
        start = len(self.events)
        c = self.config
        self.count += 1
        self.emit('counter_increment', '0x5C86F0', count=self.count)
        threshold = 2 if c.etc and c.etc[0] else 1
        if self.count < threshold:
            self._ani(c.etc[0], '0x5F32EB', reset=False)
        else:
            self._remove(int(c.pass_all), '0x5F3426')
        self._grass_particle_and_sounds()
        self.bend_enabled = False
        return self.events[start:]

    def _grass_particle_and_sounds(self):
        c = self.config
        self._particle(c.strings[0] if c.strings else '',
                       (self.xyz[0], self.xyz[1], c.ints[0] if c.ints else 0), '0x5F34AD / 0x5F3BC3')
        for raw in c.strings[1:3]:
            self._sound(raw, '0x5F33AE')

    def on_native_bend_direction(self, native_direction):
        """Grass direction is the result of native5F31A0, not a position guess."""
        self._active()
        if self.config.kind != 'grass':
            raise ValueError('Bend input belongs to Grass')
        start = len(self.events)
        if self.bend_enabled and native_direction != self.bend_direction:
            c = self.config
            raw = c.basic if native_direction == 4 else c.etc[1 if native_direction == 0 else 2]
            self._ani(raw, '0x5F332E / 0x5F334F', reset=True)
            self.bend_direction = native_direction
        return self.events[start:]

    def on_native_frame_ended(self):
        """Supplied currentANI.byte13A==1; never advances the ANI clock itself."""
        self._active()
        start = len(self.events)
        if self.config.kind != 'grass' and self.restore_basic_on_end:
            self.restore_basic_on_end = False
            self._ani(self.config.basic, '0x5F6C86', reset=True)
        return self.events[start:]

    def on_native_removed(self):
        """Apply the actual native self-removal notification, once supplied."""
        self._active()
        start = len(self.events)
        if self.config.kind == 'grass':
            threshold = 2 if self.config.etc and self.config.etc[0] else 1
            if self.count < threshold:
                self._grass_particle_and_sounds()
                self.count = threshold
        self.active = False
        self.emit('native_removed', '0x5F3B00 / 0x5F5CA0', generic_last_action_contract='scene-destruction-contract.json')
        return self.events[start:]

    def snapshot(self):
        d = asdict(self)
        d.pop('events')
        return d


def demonstration():
    """Deterministic native-input traces, not a native gameplay capture."""
    traces = []
    barrel = SceneState(selected_config(221), xyz=(100, 200, 0))
    barrel.on_native_hit_visual_gate(True)
    barrel.on_native_hp_write(0)
    assert barrel.hp == 1 and barrel.count == 1 and barrel.active
    assert any(e['kind'] == 'removal_request' for e in barrel.events)
    barrel.on_native_removed()
    traces.append({'case': 'barrel explicit HP zero then actual removal', 'state': barrel.snapshot(), 'events': barrel.events})
    tree = SceneState(selected_config(224))
    tree.on_native_hp_write(0)
    tree.on_native_frame_ended()
    tree.on_native_hp_write(0)
    tree.on_native_hp_write(0)
    assert tree.count == 2 and tree.hp == 0 and tree.active
    assert tree.current_ani.endswith('actiontree2-1.ani')
    assert not any(e['kind'] == 'removal_request' for e in tree.events)
    traces.append({'case': 'tree counter cap and no inferred ANI restoration', 'state': tree.snapshot(), 'events': tree.events})
    grass = SceneState(selected_config(244), xyz=(100, 200, 50))
    grass.on_native_bend_direction(0)
    grass.on_native_accepted_contact()
    assert grass.count == 1 and grass.active and grass.hp == 0
    assert grass.on_native_frame_ended() == []
    assert grass.on_native_bend_direction(1) == []
    grass.on_native_accepted_contact()
    assert grass.count == 2 and grass.active
    assert sum(e['kind'] == 'particle_dispatch' for e in grass.events) == 2
    assert all(e['xyz'][2] == 32 for e in grass.events if e['kind'] == 'particle_dispatch')
    grass.on_native_removed()
    assert sum(e['kind'] == 'particle_dispatch' for e in grass.events) == 2
    traces.append({'case': 'grass two explicit contacts; ANI end does not remove; PTL Z is absolute int0', 'state': grass.snapshot(), 'events': grass.events})
    remote = SceneState(selected_config(221), local_authority=False)
    remote.on_native_hp_write(0)
    assert any(e['kind'] == 'particle_dispatch' for e in remote.events)
    assert not any(e['kind'] == 'removal_request' for e in remote.events)
    traces.append({'case': 'remote barrel visual dispatch without local removal request', 'state': remote.snapshot(), 'events': remote.events})
    return {'schema': '60us-scene-counter-native-input-traces-v1',
            'scope': 'Deterministic source-derived model fixtures; no original-client execution or PTL simulation.',
            'traces': traces}


if __name__ == '__main__':
    result = demonstration()
    (ROOT / 'scene-model-cases.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf8')
    print(json.dumps({'cases': len(result['traces']), 'output': str(ROOT / 'scene-model-cases.json')}, ensure_ascii=False))
