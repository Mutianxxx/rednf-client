"""Decoded-input ports of 4AF540 and its current +3E4 implementation 4AC440.

All properties below are declared getter/field results. They do not stand for
an observed monster configuration. This module neither accepts hits nor applies
requested states, damage, animation, hit pause or movement.
"""
from dataclasses import dataclass


@dataclass(frozen=True)
class Inputs:
    reaction: int
    victim_categories: tuple[int, ...]
    type211: bool
    type111: bool
    monster_cast: bool
    monster_template3c: bool
    protected4bc: int
    protected4c4: int
    fallback_mode: int
    result_v310: int
    dead_v3dc: bool
    flag_v4f0: bool
    flag_v5a0: bool
    state155c: int
    pending4a0: int
    byte508: bool
    status14: bool
    status1: bool
    attacker_v1b8: bool
    flag1_v410: bool
    flag7_v410: bool
    scalar_v204: int
    height_v9c: int
    down_v378: bool
    down_v3a0: bool
    damage0_v374: bool
    damage1_v374: bool
    protected1720: int
    atk_push_f0: int
    atk_lift_f8: int
    atk118: int
    atk130: int
    attacker_v31c: int


@dataclass(frozen=True)
class Selection:
    state: int
    death_variant: int
    down_flag: int
    branch: str
    death_helper_args: tuple[int, int] | None = None


def death_state(v: Inputs, current_state: int, flag: bool) -> int:
    """4AC440. The actual method takes two stack arguments (ret 8)."""
    if not v.dead_v3dc:
        return 4
    if current_state == 5 or v.pending4a0 == 5:
        return -1
    if v.type111 or not v.type211:
        return 4
    if (flag or current_state == 9) and not v.flag_v5a0:
        return 5
    return 4 if v.down_v378 or v.down_v3a0 else 5


def select(v: Inputs, death_variant=0, down_flag=0) -> Selection:
    """4AF540, with stable getter results and unchanged out params preserved."""
    def result(state, branch, *, variant=death_variant, down=down_flag, args=None):
        return Selection(state, variant, down, branch, args)

    reaction = v.reaction
    if reaction == 3:
        if 0x12 in v.victim_categories:
            return result(-1, 'reaction3/category12')
        reaction = 1
    elif reaction == 0:
        return result(-1, 'reaction0/early-return')

    mode = v.protected4c4 if v.protected4bc != 0 else v.fallback_mode
    if mode != 2 and v.result_v310 in (1, 2):
        mode = 1

    if v.dead_v3dc:
        flag = v.flag_v4f0 if v.type211 else False
        args = (v.state155c, int(flag))
        state = death_state(v, *args)
        if state != 5:
            return result(state, 'dead/delegate', args=args)
        if v.atk_push_f0 < 150 and v.atk118 != 1:
            variant = 2 if v.atk_lift_f8 < 400 else 5
        else:
            variant = 3 if v.attacker_v31c != 0 else 4
        return result(5, 'dead/state5-variant', variant=variant, args=args)

    if mode != 0:
        exempt = (v.byte508 and v.status14 and v.attacker_v1b8)
        exempt |= (v.byte508 and v.status1 and v.attacker_v1b8)
        exempt |= (v.type211 and v.monster_cast and
                   v.monster_template3c and v.attacker_v1b8)
        if not exempt:
            return result(-1, 'alive/mode-suppression')
    if v.flag1_v410 or v.flag7_v410:
        return result(-1, 'alive/status1-or7')

    if reaction == 1:
        down = ((v.scalar_v204 <= 0 and v.height_v9c > 0) or v.state155c == 4)
    elif reaction == 2:
        down = True
    else:
        return result(-1, 'alive/unsupported-reaction')
    if down and (v.down_v378 or v.down_v3a0):
        extra = down_flag
        if v.state155c == 4 and v.protected1720 >= 1 and v.atk130 == 0:
            extra = 1
        return result(4, 'alive/down-resource', down=extra)
    if not v.damage0_v374 and not v.damage1_v374:
        return result(-1, 'alive/no-damage-resource')
    return result(3, 'alive/damage-resource')
