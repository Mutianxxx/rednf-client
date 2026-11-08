"""4B28D0's final state request, after upstream hit/damage decisions.

No default runtime scale, RNG, getter values or resource pointers are inferred.
These functions describe request payloads, not immediate state application.
"""
import math
import struct


def i32(value):
    return (int(value) + 2**31) % 2**32 - 2**31


def f32(value):
    return struct.unpack('<f', struct.pack('<f', value))[0]


def signed_remainder(value, divisor):
    value = i32(value)
    return (abs(value) % divisor) * (-1 if value < 0 else 1)


def damage_variant(*, motion0, motion1, act0, act1, state155c,
                   old_variant16bc, rng_result):
    if not motion1 and act1:
        return 0
    if not motion0 and act0:
        return 1
    if state155c == 3:
        return i32(1 - old_variant16bc)
    return signed_remainder(rng_result, 2)


def scale_integer(*, atk188, attack_type18, global1003404):
    """4B32DB..4B3371, finite float32 getter domain.

    CAB8F0 is double -1.0, CAB8E8 is 2^-23, CCB9DC is float32 .7.
    The sentinel is approximately -1, not zero. Preserve the caller float spill.
    """
    factor = f32(atk188)
    global_value = f32(global1003404)
    if not math.isfinite(factor) or not math.isfinite(global_value):
        raise ValueError('Non-finite provider result is outside the verified domain')
    if abs(factor - (-1.0)) <= abs(factor) * 2**-23:
        factor = 1.0
    if attack_type18 == 1:
        factor = f32(factor * f32(.7))
    value = global_value * factor
    truncated = math.trunc(value)
    if not -2**31 <= truncated < 2**31:
        raise ValueError('C01544 overflow is outside the verified domain')
    return dict(factor=factor, integer=truncated)


def request(*, selected_state, death_variant, down_flag, direction31c,
            pending4a0, motion0, motion1, act0, act1, state155c,
            old_variant16bc, rng_result, atk188, attack_type18,
            global1003404, atk178, atk118, atk130, push_f0, lift_f8,
            lift_extra50_gate):
    """4B31DA..4B3640. lift_extra50_gate is the explicit 4E9160 result."""
    state = selected_state
    if state == 3:
        if pending4a0 in (4, 5):
            return None
        variant = damage_variant(motion0=motion0, motion1=motion1,
            act0=act0, act1=act1, state155c=state155c,
            old_variant16bc=old_variant16bc, rng_result=rng_result)
        scale = scale_integer(atk188=atk188, attack_type18=attack_type18,
                              global1003404=global1003404)['integer']
        payload = [i32(direction31c), scale, variant, i32(atk178)]
        if atk118 != 0:
            payload.append(i32(atk118))
    elif state == 4:
        kind = 2 if atk130 != 0 and down_flag == 0 else 1
        payload = [i32(direction31c), i32(down_flag), kind,
                   i32(push_f0), i32(lift_f8 + (50 if lift_extra50_gate else 0))]
    elif state == 5:
        payload = [i32(death_variant)]
    else:
        return None
    return dict(state=state, payload=payload, request_tail=[3, 0, 0],
                native_slot='0x28C', state_applied=False)
