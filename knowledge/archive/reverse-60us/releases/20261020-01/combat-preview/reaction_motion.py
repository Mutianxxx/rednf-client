"""Explicit-input free horizontal reaction samples; no automatic combat events."""
from pathlib import Path
import json
import math
import sys

EVIDENCE = Path(__file__).resolve().parents[1]/'analysis/combat_reaction_motion'
if str(EVIDENCE) not in sys.path:
    sys.path.insert(0, str(EVIDENCE))
from reaction_model import sample_horizontal


class ReactionMotion:
    def __init__(self, executable_sha256):
        self.contract = json.loads((EVIDENCE/'reaction-motion-contract.json').read_text(encoding='utf8'))
        if executable_sha256 != self.contract['source_sha256']:
            raise ValueError('受击运动合同与当前 EXE 不符')

    def horizontal(self, *, kind=0, special_flag=False, scale_integer=100,
                   stat218=1000, stat220=1.0, motion_enabled=True,
                   step_delta=16, steps=40, direction=1):
        for name,value in [('kind',kind),('scale_integer',scale_integer),('stat218',stat218)]:
            if type(value) is not int or not -2**31 <= value < 2**31:
                raise ValueError(name+' 需要 int32 输入')
        if (direction not in (0,1) or not 1 <= step_delta <= 1000 or
                not 1 <= steps <= 128 or not 0 <= scale_integer <= 10000 or
                not math.isfinite(stat220) or not -100 <= stat220 <= 100):
            raise ValueError('超出受击采样的有界输入范围')
        result = sample_horizontal(kind,special_flag,scale_integer,stat218,stat220,
                                   motion_enabled,[step_delta]*steps,direction=direction)
        return dict(**result, inputs=dict(kind=kind,special_flag=special_flag,
            scale_integer=scale_integer,stat218=stat218,stat220=stat220,
            motion_enabled=motion_enabled,step_delta=step_delta,steps=steps,direction=direction),
            total_input_time=step_delta*steps, source_sha256=self.contract['source_sha256'],
            native_runtime_observed=False, native_state_machine_executed=False,
            notice='明确参数的自由水平轴采样；Z、地图碰撞、hit pause、状态退出未执行。动画与运动共用预览时间用于检查，原生同步尚未验证。')
