"""Executable bounded port of 60US 50FDE0; no client or resource mutation.

The ordinary-axis path and float32 memory stores are represented. Python double
intermediates do not promise bit identity to all x87 control words or extreme
values. native_verify.py runs extracted native instructions for recorded vectors.
"""
from dataclasses import asdict, dataclass
import argparse
import json
import math
import struct


def f32(value):
    return struct.unpack("<f", struct.pack("<f", value))[0]


def i32(value):
    return (int(value) + 2**31) % 2**32 - 2**31


TICK_TO_VELOCITY = f32(0.001)
EPSILON = 2**-23


@dataclass
class Axis:
    position: float = 0.0
    velocity: float = 0.0
    acceleration: int = 0
    remaining: int = -1

    def __post_init__(self):
        self.position = f32(self.position)
        self.velocity = f32(self.velocity)
        self.acceleration = i32(self.acceleration)


def effective_mode2_stat(base_stat, multiplier):
    """4B55A0: the integer is first spilled to float32 before multiplication."""
    return max(1, math.trunc(f32(int(base_stat)) * f32(multiplier)))


def axis_config(v1, v2, acceleration, direction, scale, use_v2=False,
                stop_when_decelerating=False, position=0.0, local_owner=True):
    """4B99C0 normal setter branch; local-owner gate must be satisfied."""
    if not local_owner:
        raise ValueError("511040/511DD0 require owner gate 49C090; pass the existing axis state instead")
    sign = -1.0 if direction in (0, 2) else 1.0 if direction in (1, 3) else 0.0
    factor = sign if scale == 1000 else f32(int(scale) * sign * TICK_TO_VELOCITY)
    velocity = f32(int(v2 if use_v2 else v1) * factor)
    accel = i32(math.trunc(int(acceleration) * factor))
    remaining = -1
    if stop_when_decelerating and velocity * accel < 0:
        remaining = math.trunc(velocity * f32(-1000.0) / accel)
    return Axis(position, velocity, accel, remaining)


def tripleslash_axes(scale, direction=1, position=(0.0, 0.0, 0.0)):
    """Preview helper; axis 2 is a fresh placeholder, not written by state22.

    Integration into an actor must preserve its existing z-axis state instead.
    """
    return [axis_config(600, 600, -1000, direction, scale,
                        stop_when_decelerating=True, position=position[0]),
            axis_config(0, 0, 0, 4, scale, position=position[1]),
            Axis(position[2])]


def position_round(value, half=0.5):
    """447FF0 with protected global half initialized to 0.5."""
    value = f32(value)
    return math.trunc(value + half if value >= 0 else value - half)


def step_axis(axes, axis, dt, can_move=None, external_controller=False):
    """Port one 50FDE0 call; mutate one Axis and return its native result code.

    axes is [x,y,z]. A can_move(axis, integer_xyz) callback is the owner +AC/+A8
    admissibility probe and may return bool. Its side effects and +274 collision
    response are outside this function. Absence of a callback means no owner.
    """
    if external_controller:
        raise NotImplementedError("M+78 external controller resolution in 511400 is not modeled")
    if axis not in (0, 1, 2) or not isinstance(dt, int) or not 0 <= dt <= 0x7fffffff:
        raise ValueError("axis must be 0..2 and dt a nonnegative signed int32 gameplay-clock delta")
    state = axes[axis]
    if state.remaining < -1:
        raise ValueError("countdown values below -1 have no validated ordinary-axis contract")
    v0, a0, r0 = state.velocity, state.acceleration, state.remaining
    if v0 == 0.0 and a0 == 0:
        return 0
    if a0 == 0:
        mean = v0
    elif r0 == -1 or dt <= r0:
        state.velocity = f32(v0 + i32(a0 * dt) * TICK_TO_VELOCITY)
        mean = (v0 + state.velocity) * f32(0.5)
        if r0 != -1:
            state.remaining = i32(r0 - dt)
            if state.remaining == 0:
                state.acceleration = 0
    else:
        state.velocity = f32(v0 + i32(a0 * r0) * TICK_TO_VELOCITY)
        early_mean = f32((v0 + state.velocity) * f32(0.5))
        mean = (r0 * early_mean + state.velocity * (dt - r0)) / dt
        state.remaining = 0
        state.acceleration = 0
    displacement = f32(dt * mean * TICK_TO_VELOCITY)
    displacement = min(2000.0, max(-2000.0, displacement))
    if can_move is not None:
        probe = [position_round(s.position) for s in axes]
        target = position_round(f32(state.position + displacement))
        while probe[axis] != target:
            previous = probe[axis]
            probe[axis] += 1 if probe[axis] < target else -1
            if not can_move(axis, tuple(probe)):
                state.position = f32(previous)
                return 4
    state.position = f32(state.position + displacement)
    if state.acceleration == 0:
        return 0 if state.velocity == 0.0 else 2
    return 1 if state.velocity * state.acceleration < 0 else 3


def step(axes, dt, can_move=None, external_controller=False):
    """511400 ordinary part: axis order x, then y, then z."""
    return [step_axis(axes, axis, dt, can_move, external_controller) for axis in range(3)]


def ani_rate(scale, installation=False, global_install_factor=100.0):
    """4B9EB0 refresh versus 4B4DA0/4ACF80 installation paths."""
    if installation:
        rate = f32(f32(int(scale)) * f32(global_install_factor) * TICK_TO_VELOCITY)
    else:
        rate = f32(int(scale) * f32(0.1))
    # A29C70 substitutes 1 only for effectively zero rate (finite inputs).
    return 1.0 if rate == 0.0 else rate


def frame_duration(delay, rate):
    """A27870 deadline increment is -trunc((delay / rate) * -100)."""
    rate = f32(rate)
    if rate == 0.0:
        rate = 1.0
    if rate < 0 or not math.isfinite(rate) or delay < 0:
        raise ValueError("positive finite ANI rate and nonnegative frame delay are required")
    return -math.trunc(int(delay) / rate * f32(-100.0))


def frame_deadlines(delays, rate):
    total, deadlines = 0, []
    for delay in delays:
        total += frame_duration(delay, rate)
        deadlines.append(total)
    return deadlines


def simulate(scale=1000, direction=1, dts=(100, 100, 100, 100, 100, 100, 100)):
    axes = tripleslash_axes(scale, direction)
    rows = [dict(time=0, axes=[asdict(s) for s in axes])]
    elapsed = 0
    for dt in dts:
        codes = step(axes, dt)
        elapsed += dt
        rows.append(dict(time=elapsed, axes=[asdict(s) for s in axes], result_codes=codes))
    rate = ani_rate(scale)
    return dict(kind="bounded native-derived simulation; not original-client runtime capture",
                scale_input=scale, direction=direction,
                assumptions=["local owner gate true", "no collision owner/controller", "z axis initially stationary"],
                clock="delta of selected pausable/scaled gameplay clock derived from timeGetTime milliseconds",
                rate_percent=rate, body_frame_deadlines=frame_deadlines([70, 70, 70, 70, 300], rate),
                samples=rows)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--scale", type=int, default=1000)
    parser.add_argument("--direction", type=int, choices=range(5), default=1)
    parser.add_argument("--dt", type=int, nargs="+", default=[100] * 7)
    args = parser.parse_args()
    print(json.dumps(simulate(args.scale, args.direction, args.dt), ensure_ascii=False, indent=2))
