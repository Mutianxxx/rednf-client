"""Source-bound resource routing, separate from an executing reaction state machine.

Only the base Active state 0/3/4 selectors recovered from this EXE are used.
ACT instructions never execute here; a BASE ANI view is explicitly identified.
"""
from __future__ import annotations
import json
from pathlib import Path, PurePosixPath
import posixpath

from catalog import normalize_path, resolve_relative
from pvf_model import node_record


class MonsterRoutes:
    def __init__(self, catalog, executable_sha256, contract_path=None):
        self.catalog = catalog
        self.contract = json.loads(Path(contract_path or Path(__file__).with_name(
            'monster-contract.json')).read_text(encoding='utf-8'))
        self.compatible = (catalog.source['sha256'] == self.contract['source_pvf_sha256']
                           and executable_sha256 == self.contract['source_exe_sha256'])

    def _reference(self, owner, tag):
        nodes = self.catalog.document(owner).find(tag, scope=())
        if not nodes:
            return None
        if len(nodes) != 1 or len(nodes[0].values) != 1 or nodes[0].values[0].kind != 'string':
            raise ValueError('资源字段不唯一或格式未核对: '+tag)
        token = nodes[0].values[0]
        if not token.text:
            return None
        path = resolve_relative(owner, token.text)
        return dict(tag=tag, path=path, token=token.to_dict(),
                    exists=path in self.catalog.pvf.by_path)

    def _action_view(self, ref):
        if ref is None or not ref['exists']:
            return None
        path = ref['path']
        doc = self.catalog.document(path)
        nodes = doc.find('BASE ANI', scope=('MOTION',))
        result = dict(reference=ref, source=self.catalog.identity(path),
                      instructions_executed=False, base_ani=None,
                      scope='ACT initial BASE ANI inspection only')
        if len(nodes) != 1 or len(nodes[0].values) != 1 or nodes[0].values[0].kind != 'string':
            result['unresolved'] = 'ACT 没有唯一的 MOTION / BASE ANI，不能推断当前动画'
            return result
        token = nodes[0].values[0]
        # Native appends the ACT directory and the literal BASE ANI string.
        joined = normalize_path(str(PurePosixPath(path).parent) + '/' + token.text)
        candidate = joined
        policy = 'literal native directory concatenation'
        if candidate not in self.catalog.pvf.by_path:
            candidate = posixpath.normpath(joined)
            policy = 'preview dot-segment normalization; native normalization site unresolved'
        exists = candidate in self.catalog.pvf.by_path
        result['base_ani'] = dict(path=candidate, exists=exists, native_concatenation=joined,
                                  lookup_policy=policy, field=node_record(nodes[0]),
                                  source=self.catalog.identity(candidate) if exists else None)
        return result

    def route(self, path, state=3, variant=0):
        if not self.compatible:
            raise ValueError('当前 EXE/PVF 与怪物选择合同来源不符')
        path = normalize_path(path)
        if not path.endswith('.mob'):
            raise ValueError('需要当前 PVF 的 .mob 路径')
        if state not in (0, 3, 4):
            raise ValueError('仅核对了状态 0/3/4 的资源选择；死亡状态尚未恢复')
        if variant not in (0, 1):
            raise ValueError('受击 variant 必须为原生索引 0 或 1')
        role = 'waiting' if state == 0 else ('down' if state == 4 else 'damage'+str(variant+1))
        motion_tag = f'damage motion {variant+1}' if state == 3 else role+' motion'
        action_tag = f'damage action {variant+1}' if state == 3 else role+' action'
        motion = self._reference(path, motion_tag)
        action = self._reference(path, action_tag)
        action_view = self._action_view(action)
        motion_ready = bool(motion and motion['exists'])
        action_ready = bool(action_view and action_view.get('base_ani')
                            and action_view['base_ani']['exists'])
        result = dict(path=path, source=self.catalog.identity(path), state=state,
                      variant=variant, role=role, contract=self.contract,
                      candidates=dict(motion=motion, action_reference=action, action=action_view),
                      animation_path=None, selection=None, state_machine_executed=False,
                      notice='手动核对原生资源选择；未执行接受命中、物理、ACT 条件和状态退出')
        if any(ref and not ref['exists'] for ref in (motion, action)):
            result['unresolved'] = 'MOB 声明了缺失资源，原生加载失败行为尚未核对，停止选择'
            return result
        # Native slot374 first resolves motion, or ACT.currentANI when motion is null.
        if state == 3 and not (motion_ready or action_ready):
            result['unresolved'] = '原生 state3 的 slot374 动画前置条件未满足，保留当前动画'
            return result
        if action and action['exists']:
            result['selection'] = 'action'
            result['notice'] += '；ACT 优先，此处仅播放其初始 BASE ANI'
            if action_ready:
                result['animation_path'] = action_view['base_ani']['path']
            else:
                result['unresolved'] = 'ACT 已存在，其当前动画未解析；不能回退到 motion 伪装执行结果'
            return result
        if motion_ready:
            result['selection'] = 'motion'
            result['animation_path'] = motion['path']
            return result
        if state == 4:
            sit = self._reference(path, 'sit motion')
            result['candidates']['sit_motion'] = sit
            if sit and sit['exists']:
                result['selection'] = 'sit_motion_fallback'
                result['animation_path'] = sit['path']
                return result
        result['unresolved'] = '未找到可用资源；不补造动画'
        return result
