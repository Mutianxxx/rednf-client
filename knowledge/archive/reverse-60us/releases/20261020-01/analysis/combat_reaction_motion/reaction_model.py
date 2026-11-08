"""Bounded ports of decoded-input 60US reaction arithmetic.

Inputs are explicit runtime values, not values guessed from MOB/ATK names.
This module does not accept hits, change HP, choose ACT instructions or advance
the state machine. Native-instruction comparisons live in native_verify.py.
"""
from dataclasses import asdict, dataclass
import math
import struct


def f32(value):
    return struct.unpack('<f', struct.pack('<f', value))[0]


def i32(value):
    return (int(value) + 2**31) % 2**32 - 2**31


def trunc32(value):
    """The verified finite/int32 domain of C01544; reject unverified overflow."""
    if not math.isfinite(value) or not -2**31 <= math.trunc(value) < 2**31:
        raise ValueError('Outside the verified finite signed-int32 truncation domain')
    return math.trunc(value)


def idiv(a, b):
    a, b = i32(a), i32(b)
    if b == 0 or (a == -2**31 and b == -1):
        raise ValueError('Native integer division would fault')
    q = abs(a) // abs(b)
    return -q if (a < 0) != (b < 0) else q


def effective_stat(base, multiplier):
    """4BDD40 / 4BDDC0 style: int -> float32 memory -> x87 multiply -> trunc."""
    return trunc32(f32(i32(base)) * f32(multiplier))


def payload_scale(integer):
    """4BB094..4BB0AF, including the source float32 .01 and final spill."""
    return f32(i32(integer) * f32(.01))


@dataclass(frozen=True)
class Horizontal:
    speed: int
    acceleration: int
    duration: int
    deceleration_duration: int


def horizontal(kind, special_flag, scale, stat218, stat220, motion_enabled):
    """4BA620. Five stack args include scale; Ghidra omitted that final float.

    stat218/stat220 are decoded values from actor.v344(3). For the ordinary
    branch, both native reads must see this same pair. Returns positive speed
    before the separate direction setter, plus signed integer acceleration.
    motion_enabled is decoded actor+18D8, not a guessed superarmor rule.
    """
    kind, scale = i32(kind), f32(scale)
    if kind in (1, 2):
        speed = 800 if kind == 1 else 400
        duration = decel = trunc32(scale * f32(333.0))
    else:
        if special_flag:
            speed, cap = 0, 0
        elif kind == -1:
            speed, cap = 0, 30
        else:
            speed, cap = 400, 150
        difference = i32(2000 - effective_stat(stat218, stat220))
        base = trunc32((difference if difference > 0 else 0) * f32(.25))
        duration = trunc32(base * scale)
        decel = min(cap, duration)
    if not motion_enabled:
        speed, acceleration = 0, 0
    else:
        acceleration = idiv(i32(speed * -1000), decel) if decel else 0
    return Horizontal(speed, acceleration, duration, decel)


def gravity(fixed_base, actor163c, stat238, stat240, *, map_present=False,
            map9dc=0, actor1660=0):
    """4B9FA0 decoded-input port. Map offsets apply only with a map data ptr.

    True uses -1500 plus optional map offset, without stat scaling. False uses
    protected actor+163C and stat238/stat240; zero base skips the map offset.
    """
    value = -1500 if fixed_base else i32(actor163c)
    if fixed_base or value != 0:
        if map_present:
            value = i32(value + i32(map9dc + actor1660))
    if fixed_base:
        return value
    return idiv(i32(effective_stat(stat238, stat240) * value), 100)


def impulse(param1, param2, param3):
    """4B98F0; return float32 at the caller spill. Not a lift->velocity alias."""
    numerator = i32(i32(param1) * 4000)
    quotient = idiv(i32(i32(param2) * 100), param3)
    denominator = i32(quotient - 10000) * f32(.0121) + f32(2100.0)
    if denominator == 0:
        raise ValueError('Outside the finite impulse domain')
    return f32(numerator / denominator)


def sample_horizontal(kind, special_flag, scale_integer, stat218, stat220,
                      motion_enabled, dt_steps, *, direction=1, initial_xyz=(0, 0, 0)):
    """Free-axis X/Y demonstration with explicit deltas; no map or state exit.

    It intentionally preserves the existing Z coordinate without simulating
    state3's separate gravity. For full state3, caller must install gravity,
    owner constraints, clocks, animation and the exit-state request.
    """
    import sys
    from pathlib import Path
    motion_dir = str(Path(__file__).resolve().parents[1] / 'combat_motion')
    if motion_dir not in sys.path:
        sys.path.insert(0, motion_dir)
    from motion_model import Axis, axis_config, step_axis
    result = horizontal(kind, special_flag, payload_scale(scale_integer),
                        stat218, stat220, motion_enabled)
    # 4BB172 / 4BB1A3 install raw mode 0, scale 1000 and stop-when-decelerating.
    axes = [axis_config(result.speed, result.speed, result.acceleration,
                        direction, 1000, stop_when_decelerating=True,
                        position=initial_xyz[0]), Axis(initial_xyz[1]), Axis(initial_xyz[2])]
    rows, elapsed = [], 0
    for delta in dt_steps:
        elapsed += delta
        code = step_axis(axes, 0, delta)
        rows.append(dict(time_input=elapsed, x_axis=asdict(axes[0]), result_code=code,
                         duration_reached=elapsed >= result.duration))
    return dict(parameters=asdict(result), samples=rows,
                scope='free horizontal axis only; explicit runtime stats/deltas; no automatic hit or state transition')
